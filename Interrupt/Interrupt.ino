#include <SPI.h>
#include "PowerDueLED.h"
#include "FXOS8700CQ.h"

FXOS8700CQ sensor;
uint8_t value;
uint8_t count;
int chip_select = 4;
int interruptPin = 51;

void setup() {
  // Initialize SerialUSB 
  SerialUSB.begin(9600);
  //while(!SerialUSB);

  // 
  
  //Attach Pin 51 to interrupt
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), collect_data, CHANGE);
  
  // Initialize SPI
  SPI.begin();
  pd_rgb_led_init();

  // Initialize sensor
  sensor = FXOS8700CQ();
  sensor.init();
  sensor.calibrate();
  sensor.enableInt();
  //sensor.disableInt();

  //Check Who Am I value
  //value = sensor.readReg(FXOS8700CQ_WHO_AM_I);
  
  delay(500);
}

void collect_data(){
  sensor.disableInt();
  SerialUSB.println("Interrupt!");
  //sensor.readMagData();
  process_data();
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

