#include <Servo.h>
// output variables
Servo engine[4];


/*
 * Sets escs' pin mode to output
 */
void setupESC() {

  engine[FRL].attach(3); // (pin, min pulse width, max pulse width in microseconds)
  engine[FRR].attach(5); // (pin, min pulse width, max pulse width in microseconds)
  engine[BKL].attach(6); // (pin, min pulse width, max pulse width in microseconds)
  engine[BKR].attach(9); // (pin, min pulse width, max pulse width in microseconds)
  engine[FRL].writeMicroseconds(IO_MIN); // Send the signal to the ESC
  engine[FRR].writeMicroseconds(IO_MIN); // Send the signal to the ESC
  engine[BKL].writeMicroseconds(IO_MIN); // Send the signal to the ESC
  engine[BKR].writeMicroseconds(IO_MIN); // Send the signal to the ESC
  escArmingLed();
  Serial.print("esc setup completed.\n");
  delay(WAIT);
  switchLed(&redLed);
}

/*
* Limits the output to the admitted range
*/
void limitPower(){
  if (escOutput[FRL]>MAX_MOTOR_POWER)escOutput[FRL]=MAX_MOTOR_POWER;
  if (escOutput[FRR]>MAX_MOTOR_POWER)escOutput[FRR]=MAX_MOTOR_POWER;
  if (escOutput[BKL]>MAX_MOTOR_POWER)escOutput[BKL]=MAX_MOTOR_POWER;
  if (escOutput[BKR]>MAX_MOTOR_POWER)escOutput[BKR]=MAX_MOTOR_POWER;
  if (escOutput[FRL]<0)escOutput[FRL]=0;
  if (escOutput[FRR]<0)escOutput[FRR]=0;
  if (escOutput[BKL]<0)escOutput[BKL]=0;
  if (escOutput[BKR]<0)escOutput[BKR]=0;
}

/*
* Some sums
*/
void outputCalculation(){
  escOutput[FRL] = userInput[THR] -offset[X] +offset[Y] +offset[Z];
  escOutput[FRR] = userInput[THR] +offset[X] +offset[Y] -offset[Z];
  escOutput[BKL] = userInput[THR] -offset[X] -offset[Y] -offset[Z];
  escOutput[BKR] = userInput[THR] +offset[X] -offset[Y] +offset[Z];
  limitPower();
  escOutput[FRL] = map(escOutput[FRL], 0, MAX_MOTOR_POWER, IO_MIN, IO_MAX);
  escOutput[FRR] = map(escOutput[FRR], 0, MAX_MOTOR_POWER, IO_MIN, IO_MAX);
  escOutput[BKL] = map(escOutput[BKL], 0, MAX_MOTOR_POWER, IO_MIN, IO_MAX);
  escOutput[BKR] = map(escOutput[BKR], 0, MAX_MOTOR_POWER, IO_MIN, IO_MAX);
}

/**
 * Converts our comfortable values to output values and sends them to the escs.
 */
void writeESC() {
  if(!shutdown){
  motorsRunning();
  engine[FRL].writeMicroseconds(escOutput[FRL]); // Send the signal to the ESC
  engine[FRR].writeMicroseconds(escOutput[FRR]); // Send the signal to the ESC
  engine[BKL].writeMicroseconds(escOutput[BKL]); // Send the signal to the ESC
  engine[BKR].writeMicroseconds(escOutput[BKR]); // Send the signal to the ESC
  }else{
    motorsStopped();
    engine[FRL].writeMicroseconds(IO_MIN); // Send the signal to the ESC
    engine[FRR].writeMicroseconds(IO_MIN); // Send the signal to the ESC
    engine[BKL].writeMicroseconds(IO_MIN); // Send the signal to the ESC
    engine[BKR].writeMicroseconds(IO_MIN); // Send the signal to the ESC
  }
}

