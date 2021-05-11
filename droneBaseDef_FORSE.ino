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
  
  while(micros() - loop_timer < 10000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();
}
