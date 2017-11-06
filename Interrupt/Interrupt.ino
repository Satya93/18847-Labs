#include <SPI.h>
#include "PowerDueLED.h"
#include "FXOS8700CQ.h"

FXOS8700CQ sensor;
uint8_t value;
uint8_t count;
int interruptPin = 51;

void setup() {
  // Initialize SerialUSB 
  SerialUSB.begin(9600);
  while(!SerialUSB);

  // 
  
  //Attach Pin 51 to interrupt
  //pinMode(interruptPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), collect_data, CHANGE);
  
  // Initialize SPI
  SPI.begin();
  pd_rgb_led_init();

  // Initialize sensor
  sensor = FXOS8700CQ();
  //sensor.reset();
  sensor.init();
  //
  //sensor.enableInt();
  //sensor.disableInt();
  delay(500);
  //Check Who Am I valu
  value = sensor.readReg(FXOS8700CQ_WHO_AM_I);
  SerialUSB.println(value);
  sensor.active();
  //sensor.calibrate();
  
}

void collect_data(){
  sensor.disableInt();
  SerialUSB.println("Interrupt!");
  process_data();
  attachInterrupt(digitalPinToInterrupt(interruptPin), collect_data, CHANGE);
  sensor.enableInt();
}

void process_data(){
  count++;
  SerialUSB.println(count);
}

void loop() {
  sensor.readMagData();
  delay(200);
}

