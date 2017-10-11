#include <SPI.h>
#include "FXOS8700CQ.h"

FXOS8700CQ sensor;
uint8_t value;

void setup() {
  // Initialize SerialUSB 
  SerialUSB.begin(9600);
  while(!SerialUSB);
  
  // Initialize SPI
  SPI.begin();

  // Initialize sensor
  sensor = FXOS8700CQ();
  sensor.init();
  
  //value = sensor.readReg(FXOS8700CQ_WHO_AM_I);

  // TODO: Check the sensor's WhoAmI value
  //sensor.active();
  delay(500);
}

void loop() {
  delay(1000);
  //sensor.checkWhoAmI();
  sensor.init();
  //sensor.readMagData();
  //delay(500);
  //sensor.standby();
  //sensor.init();
  
  // TO DO: Read Mag data. Get all parameters 
  
}

