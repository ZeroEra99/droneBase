#include "math.h"

int signOf(double number){
  if (number>=0)return 1;
  else return -1;
}

/*
* Increases throttle to compensate vertical thrust power loss due to the tilt of the drone
*/
void throttleCompensation(){
  float InputTHRbackup=userInput[THR];
  float angleTot=hypot(angle[X],angle[Y]);
  userInput[THR]-=2*(userInput[THR]/maxInclAx - userInput[THR]);

  if(angleTot<MAX_INCLINATION){
    userInput[THR]+=InputTHRbackup/cos(angleTot*DEGtoRAD) - InputTHRbackup;
  }else userInput[THR]+=2*(userInput[THR]/maxInclAx - userInput[THR]);
}

/*
* Generates the offset that will be applied to the motors
*/
void offsetGeneration(){
  timePrev = time;  // the previous time is stored before the actual time read
  time = millis();  // actual time read
  elapsedTime = (time - timePrev) / 1000;  

  correction[Y] = angle[Y]-userInput[Y];
  correction[X] = angle[X]-userInput[X];

  pidOffset[Y][P]=pidConstant[Y][P]*correction[Y];
  pidOffset[X][P]=pidConstant[X][P]*correction[X];
  
  if(-min_error < correction[Y] <min_error){
    pidOffset[Y][I] += (pidConstant[Y][I]*correction[Y]);
  }

  if(-min_error < correction[X] <min_error){
    pidOffset[X][I] += (pidConstant[X][I]*correction[X]);
  }

  pidOffset[Y][D] = pidConstant[Y][D]*((correction[Y] - last_correction[Y])/elapsedTime);
  pidOffset[X][D] = pidConstant[X][D]*((correction[X] - last_correction[X])/elapsedTime);

  offset[Y] = pidOffset[Y][P] + pidOffset[Y][I] + pidOffset[Y][D];
  offset[X] = pidOffset[X][P] + pidOffset[X][I] + pidOffset[X][D];

  if(offset[Y] < -pidMax){offset[Y]=-pidMax;}
  if(offset[Y] > pidMax){offset[Y]=pidMax;} 
  if(offset[X] < -pidMax){offset[X]=-pidMax;}
  if(offset[X] > pidMax){offset[X]=pidMax;} 

  offset[Y]=(map(offset[Y],-pidMax,pidMax,-MAX_OFFSET,MAX_OFFSET))*userInput[THR]/100;
  offset[X]=(map(offset[X],-pidMax,pidMax,-MAX_OFFSET,MAX_OFFSET))*userInput[THR]/100;
  offset[Z] = (userInput[Z]*(MAX_OFFSET)/100)*userInput[THR]/100;

  last_correction[Y]=correction[Y];
  last_correction[X]=correction[X];
}

/*
* Calculates the total XYZ offset and reduces the single ones to respect the MAX_OFFSET parameter
*/
void offsetLimitation(){//da testare
  float offsetTot=fabs(offset[Y])+fabs(offset[X])+fabs(offset[Z]);
    if (offsetTot >= MAX_OFFSET) {
        offset[Y] *= (MAX_OFFSET / offsetTot);
        offset[X] *= (MAX_OFFSET / offsetTot);
        offset[Z] *= (MAX_OFFSET / offsetTot);
    }
}

