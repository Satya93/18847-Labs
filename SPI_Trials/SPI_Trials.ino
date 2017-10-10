#include <SPI.h>
#include "FXOS8700CQ.h"

FXOS8700CQ sensor;

void setup() {
  // Initialize SerialUSB 
  SerialUSB.begin(9600);
  while(!SerialUSB);
  
  // Initialize SPI
  SPI.begin();

  // Initialize sensor
  sensor = FXOS8700CQ();
  sensor.init();

  // TODO: Check the sensor's WhoAmI value

}

void loop() {
  // TO DO: Read Mag data. Get all parameters 
  
}

