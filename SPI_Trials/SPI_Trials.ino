#include <SPI.h>
#include "PowerDueLED.h"
#include "FXOS8700CQ.h"

FXOS8700CQ sensor;
uint8_t value;

void setup() {
  // Initialize SerialUSB 
  //SerialUSB.begin(9600);
  //while(!SerialUSB);
  
  // Initialize SPI
  SPI.begin();
  pd_rgb_led_init();

  // Initialize sensor
  sensor = FXOS8700CQ();
  sensor.init();
  
  //value = sensor.readReg(FXOS8700CQ_WHO_AM_I);

  // TODO: Check the sensor's WhoAmI value
  //sensor.active();
  delay(500);
}

void loop() {
  int i = 0;
  pd_rgb_led(PD_OFF);

  while(i<10000)
  {
  //sensor.checkWhoAmI();
  //sensor.init();
  sensor.readMagData();
  i++;
  }

  pd_rgb_led(PD_WHITE);
  delay(1000);
  //delay(50);
  //sensor.standby();
  //sensor.init();
  
  // TO DO: Read Mag data. Get all parameters 
  
}

