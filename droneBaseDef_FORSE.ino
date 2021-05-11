#include "receiverInput.h"
#include "escOutput.h"
#include "flightProcedures.h"
#include "bnoInput.h"

long loop_timer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupESC();
  setupLed();
  setupReceiver();
  setupBNO();
  Serial.print("Drone is starting.\n");
  loop_timer = micros();
}

void loop() {
  // put your main code here, to run repeatedly:
  readBNO();
  readReceiver();
  inputConversion();
  //throttleCompensation();
  offsetGeneration();
  //offsetLimitation();
  outputCalculation();
  writeESC();
  
  //Serial.print("Throttle: ");Serial.print(userInput[THR]);
  //Serial.print("\tPitch: ");
  //Serial.print(angle[Y]);
  //Serial.print("\tInput y: ");Serial.print(userInput[Y]);
  //Serial.print("\tPitch correction: ");
  //Serial.print(offset[Y]);
  //Serial.print("\tOffset tot: ");Serial.print(offsetTot);
  //Serial.print("\tPitch offset: ");
  //Serial.print(offset[Y]);
  //Serial.print(" ");
  //Serial.print("\tRoll: ");
  //Serial.print(angle[X]);
  //Serial.print("\tInput x: ");Serial.print(userInput[X]);
  //Serial.print("\tRoll correction: ");
  //Serial.print(offset[X]);
  //Serial.print("\tRoll offset: ");
  //Serial.print(offset[X]);
  //Serial.print("\tYaw input: ");Serial.print(userInput[Z]);
  //Serial.print("\tYaw offset: ");Serial.print(offset[Z]);
  //Serial.print("\tescOffset[FRL]: ");Serial.print(escOffset[FRL]);
  //Serial.print("\tescOffset[FRR]: ");Serial.print(escOffset[FRR]);
  //Serial.print("\t[FRL]: ");Serial.print(escOutput[FRL]);
  //Serial.print("\t[FRR]: ");
  //Serial.print(escOutput[FRL]);
  //Serial.print("  ");
  //Serial.print(escOutput[BKL]);
  //Serial.print("\n");
  while(micros() - loop_timer < 10000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();
}
