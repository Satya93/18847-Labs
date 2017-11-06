#include <SPI.h>
#include "PowerDueLED.h"
#include "FXOS8700CQ.h"

FXOS8700CQ sensor;
uint8_t value;
uint8_t count;
int interruptPin = 51;
int cs = 22;
boolean flag = LOW;

void setup() {
  // Initialize SerialUSB 
  //SerialUSB.begin(9600);
  //while(!SerialUSB);

  pd_rgb_led_init();
  
  // Initialize SPI
  SPI.begin();

  // Initialize sensor
  sensor = FXOS8700CQ();
  while(1){
    SerialUSB.println("Loop");
    sensor.init();
    delay(5000);
  }
  sensor.checkWhoAmI();
  //sensor.standby();
  //sensor.calibrate();
  //sensor.enableInt();
  //sensor.active();
  //sensor.disableInt();

  //Check Who Am I value
  
  //Attach Pin 51 to interrupt
  //attachInterrupt(interruptPin, collect_data, FALLING);
  
  delay(500);
}

void collect_data(){
  detachInterrupt(interruptPin);
  SerialUSB.println("Interrupt!");
  process_data();
  sensor.clearLatch();
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
}

