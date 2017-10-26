#include <SPI.h>
#include "PowerDueLED.h"
#include "FXOS8700CQ.h"

FXOS8700CQ sensor;
uint8_t value;
uint8_t count;
int chip_select = 4;
int interruptPin = 51;
boolean flag = LOW;

void setup() {
  // Initialize SerialUSB 
  SerialUSB.begin(9600);
  while(!SerialUSB);

  pd_rgb_led_init();
  
  // Initialize SPI
  SPI.begin();

  // Initialize sensor
  sensor = FXOS8700CQ();
  sensor.calibrate();
  sensor.init();
  sensor.standby();
  sensor.enableInt();
  sensor.active();
  //sensor.disableInt();

  //Check Who Am I value
  //value = sensor.readReg(FXOS8700CQ_WHO_AM_I);
  
  //Attach Pin 51 to interrupt
  attachInterrupt(interruptPin, collect_data, FALLING);
  
  delay(500);
}

void collect_data(){
  detachInterrupt(interruptPin);
  flag = HIGH;
  attachInterrupt(interruptPin, collect_data, FALLING);
}

void process_data(){
  count++;
  SerialUSB.print("Interrupt Count is : ");
  SerialUSB.println(count);
}

void loop() {
  sensor.readMagData();
  delay(200);
  if(flag==HIGH){
    SerialUSB.println("Interrupt!");
    //sensor.readMagData();
    process_data();
    sensor.clearLatch();
    flag=LOW;
  }
}

