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

}

void loop() {
  //SerialUSB.println(value);
  sensor.checkWhoAmI();
  delay(2000);
  // TO DO: Read Mag data. Get all parameters 
  
}

