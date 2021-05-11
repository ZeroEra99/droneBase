#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);
sensors_event_t event;


void setupBNO(){
  mpuStartingLed();
  delay(WAIT);
  Serial.print("Orientation Sensor Test");
  Serial.print("\n");
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  Serial.print("mpu setup completed.\n");
  switchLed(&redLed);
  delay(1000);
  bno.setExtCrystalUse(true);
}

void readBNO(){
  bno.getEvent(&event);
  angle[Y]=event.orientation.pitch;
  angle[X]=event.orientation.heading;
  angle[Z]=event.orientation.roll;
}