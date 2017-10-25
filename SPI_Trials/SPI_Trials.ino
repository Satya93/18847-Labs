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
  while(!SerialUSB);

  pd_rgb_led_init();
  
  // Initialize SPI
  SPI.begin();

  // Initialize sensor
  sensor = FXOS8700CQ();
  sensor.init();
  sensor.calibrate();
  sensor.enableInt();
  //sensor.disableInt();

  //Check Who Am I value
  //value = sensor.readReg(FXOS8700CQ_WHO_AM_I);
  
  //Attach Pin 51 to interrupt
  //pinMode(interruptPin, INPUT);
  attachInterrupt(interruptPin, collect_data, RISING);
  
  delay(500);
}

void collect_data(){
  detachInterrupt(interruptPin);
  //sensor.disableInt();
  SerialUSB.println("Interrupt!");
  sensor.readMagData();
  process_data();
  //sensor.clearLatch();
  //sensor.enableInt();
  attachInterrupt(interruptPin, collect_data, FALLING);
}

void process_data(){
  count++;
  SerialUSB.print("Interrupt Count is : ");
  SerialUSB.println(count);
}

void loop() {
  //sensor.readMagData();
  //delay(200);
}

