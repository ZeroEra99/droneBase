#define flashInterval 250

typedef struct LedLight{
  const int Pin;
  bool Status;
};

struct LedLight redLed={11,false};
struct LedLight greenLed={12,false};

void switchLed(struct LedLight *led){
  if(led->Status==false){
    digitalWrite(led->Pin,HIGH);
    led->Status=true;
  }else{
    digitalWrite(led->Pin,LOW);
    led->Status=false;
  }
}

void blinkLed(struct LedLight *led, int count, int interval){
  int i;
  for(i=0;i<3;i++){
    switchLed(led);
    delay(flashInterval);
    switchLed(led);
    delay(flashInterval);
  }
}

void setupLed(){
  delay(1000);
  Serial.print("Led setup in progress...\n");
  pinMode(redLed.Pin,OUTPUT);
  pinMode(greenLed.Pin,OUTPUT);

  switchLed(&redLed);
  switchLed(&greenLed);
  Serial.print("Led setup completed.\n");
  delay(2000);
  switchLed(&redLed);
  switchLed(&greenLed);
}

void receiverStartingLed(){
  delay(1000);
  Serial.print("Receiver setup in progress...\n");
  blinkLed(&redLed, 3, flashInterval);
  /*
  int i;
  for(i=0;i<3;i++){
    switchLed(&redLed);
    delay(flashInterval);
    switchLed(&redLed);
    delay(flashInterval);
  }*/
  switchLed(&redLed);
}

void mpuStartingLed(){
  delay(1000);
  Serial.print("mpu setup in progress..\n");
  int i;
  for(i=0;i<2;i++){
    switchLed(&redLed);
    delay(flashInterval);
    switchLed(&redLed);
    delay(flashInterval);
  }
    switchLed(&greenLed);
    delay(flashInterval);
    switchLed(&greenLed);
    delay(flashInterval);

  switchLed(&redLed);
}

void escArmingLed(){
  delay(1000);
  Serial.print("esc setup in progress..\n");
  int i;

  switchLed(&redLed);
  delay(flashInterval);
  switchLed(&redLed);
  delay(flashInterval);
  
  for(i=0;i<2;i++){
    switchLed(&greenLed);
    delay(flashInterval);
    switchLed(&greenLed);
    delay(flashInterval);
  }
  switchLed(&redLed);
}

void motorsRunning(){
    digitalWrite(greenLed.Pin,HIGH);
    digitalWrite(redLed.Pin,LOW);
}

void motorsStopped(){
    digitalWrite(redLed.Pin,HIGH);
    digitalWrite(greenLed.Pin,LOW);
}