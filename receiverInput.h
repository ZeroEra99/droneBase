#include "parameters.h"

/**
* map function converted to work with float data
*/
float mapf(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
* Sets receiver's pin mode to input
*/
void setupReceiver(){
receiverStartingLed();
delay(WAIT);
pinMode(userPitch,INPUT);
pinMode(userRoll,INPUT);
pinMode(userYaw,INPUT);
pinMode(userThrottle,INPUT);

Serial.print("Receiver setup complete.\n");
switchLed(&redLed);
delay(WAIT);
}


/**
* Checks if the receiver is connected (pulseIn returns 0 if there is no response in us from the receiver).
* Returns a boolean.
*/
void isConnected(){
  if(userInput[Y]==0 || userInput[X]==0 || userInput[Z]==0 || userInput[THR]==0){
    shutdown=true;
  }else return;
}

bool TurnOn(){
  if(
    userInput[THR]<(IO_MIN+ARMING_RANGE) && userInput[Z]<(IO_MIN+ARMING_RANGE)
    &&
    userInput[Y]<(IO_MIN+ARMING_RANGE) && userInput[X]>(IO_MAX-ARMING_RANGE)
    )return true;
  else return false;
}

bool Shutdown(){
  if(
    userInput[THR]<(IO_MIN+ARMING_RANGE) && userInput[Z]>(IO_MAX-ARMING_RANGE)
    &&
    userInput[Y]<(IO_MIN+ARMING_RANGE) && userInput[X]<(IO_MIN+ARMING_RANGE)
    )return true;
  else return false;
}


/**
* Reads the input (in microseconds) from the receiver
*/
void readReceiver(){
  userInput[Y]=pulseIn(userPitch,HIGH,30000);//Da provare con 15000
  userInput[X]=pulseIn(userRoll,HIGH,30000);
  userInput[Z]=pulseIn(userYaw,HIGH,30000);
  userInput[THR]=pulseIn(userThrottle,HIGH,30000);
  if(Shutdown())shutdown=true;
  if(TurnOn())shutdown=false;
  isConnected();
}

/*
* In case of small variations from the idle or excessive values sets the input to default.
* 
*/
void smoothInput(){
  //La seconda parte sembra rallentare il tutto
  if(abs(userInput[Y]-IO_MID)<IDLE || userInput[Y]>(IO_MAX+IDLE))userInput[Y]=IO_MID;
  if(abs(userInput[X]-IO_MID)<IDLE || userInput[X]>(IO_MAX+IDLE))userInput[X]=IO_MID;
  if(abs(userInput[Z]-IO_MID)<IDLE || userInput[Z]>(IO_MAX+IDLE))userInput[Z]=IO_MID;
  if((userInput[THR]-IO_MIN)<IDLE || userInput[THR]>(IO_MAX+IDLE))userInput[THR]=IO_MIN;
}

/*
* Modules pitch and roll inputs if their Pythagorean addition is higher than the maximum inclination
 */
void inputLimitation(){
  float inputTot=hypot(userInput[X], userInput[Y]);
    if (inputTot > MAX_INCLINATION) {
        userInput[Y] *= (MAX_INCLINATION / inputTot);
        userInput[X] *= (MAX_INCLINATION / inputTot);
    }
}

/*
* Converts the input values to some more confortable ones..
*/
void inputConversion(){
    smoothInput();
    userInput[Y]=mapf(userInput[Y],IO_MIN,IO_MAX, -MAX_INCLINATION, MAX_INCLINATION);
    userInput[X]=mapf(userInput[X],IO_MIN,IO_MAX, -MAX_INCLINATION, MAX_INCLINATION);
    userInput[Z]=mapf(userInput[Z],IO_MIN,IO_MAX, -MAX_ROTATION_FORCE, MAX_ROTATION_FORCE);
    userInput[THR]=mapf(userInput[THR],IO_MIN,IO_MAX, 0, MAX_MOTOR_POWER);
    inputLimitation();
}