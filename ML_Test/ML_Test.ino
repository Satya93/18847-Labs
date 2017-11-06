/*
 * Example to demonstrate thread definition, semaphores, and thread sleep.
 */
#include <FreeRTOS_ARM.h>
#include "PowerDueLED.h"
#include "Ml.h"

void setup() {
  SerialUSB.begin(9600);
  while(!SerialUSB){
  }
  Ml ml;

  ml.clear_all();
  //ml.append(200);
  //ml.append(100);
  //ml.append(300);
  ml.sample(100);
  ml.regression();

}
//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
  // Not used.
}
