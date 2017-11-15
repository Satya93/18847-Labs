/*
 * Example to demonstrate thread definition, semaphores, and thread sleep.
 */
#include <FreeRTOS_ARM.h>
#include "PowerDueLED.h"
#include "Ml.h"

void setup() {
  pd_rgb_led_init();
  pd_rgb_led(PD_OFF);
  SerialUSB.begin(9600);
  while(!SerialUSB){
  }
  Ml ml;
  ml.clear_all();
  //ml.append(200);
  //ml.append(100);
  //ml.append(300);
  ml.sample(100);
  pd_rgb_led(PD_RED);
  ml.regression(100);
  pd_rgb_led(PD_OFF);

}
//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
  // Not used.
}
