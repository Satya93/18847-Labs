/*
 * Example to demonstrate thread definition, semaphores, and thread sleep.
 */
#include <FreeRTOS_ARM.h>
#include "PowerDueLED.h"
#include "Wire.h"
#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"
int i;

LSM303C myIMU;

// Declare a semaphore handle.
SemaphoreHandle_t sem,sem2;
//------------------------------------------------------------------------------
/*
 * Thread 1, turn the LED off when signalled by thread 2.
 */
// Declare the thread function for thread 1.
static void Thread1(void* arg) {
  while (1) {
    xSemaphoreTake(sem, portMAX_DELAY);
    i = 0;
    pd_rgb_led(PD_OFF);
    // Wait for signal from thread 2.
    while(i<10000)
    {
    myIMU.WhoAmI();
    i++;
    }
    SerialUSB.println("Thread 1");
    

    
    // Turn LED off.
    
    xSemaphoreGive(sem2);
  }
}
//------------------------------------------------------------------------------
/*
 * Thread 2, turn the LED on and signal thread 1 to turn the LED off.
 */
// Declare the thread function for thread 2.
static void Thread2(void* arg) {

  // Initialize the PowerDue LED
  pd_rgb_led_init();

  while (1) {
    xSemaphoreTake(sem2, portMAX_DELAY);
    // Turn RED LED On.
    pd_rgb_led(PD_RED);
    //SerialUSB.println("Thread 2");
    //SerialUSB.println(" ");
    // Sleep for 200 milliseconds.
    vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);

    // Signal thread 1 to turn LED off.
    xSemaphoreGive(sem);

    // Sleep for 200 milliseconds.
    vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
  }
}
//------------------------------------------------------------------------------
void setup() {
  portBASE_TYPE s1, s2;

  //SerialUSB.begin(40000000);
  //while(!(SerialUSB));
  //SerialUSB.println("Begin Code");

  if (myIMU.begin(
                ///// Interface mode options
                  //MODE_SPI,
                  MODE_I2C,

                ///// Magnetometer output data rate options
                  //MAG_DO_0_625_Hz,
                  //MAG_DO_1_25_Hz,
                  //MAG_DO_2_5_Hz,
                  //MAG_DO_5_Hz,
                  //MAG_DO_10_Hz,
                  //MAG_DO_20_Hz,
                  MAG_DO_40_Hz,
                  //MAG_DO_80_Hz,

                ///// Magnetic field full scale options
                  //MAG_FS_4_Ga,
                  //MAG_FS_8_Ga,
                  //MAG_FS_12_Ga,
                  MAG_FS_16_Ga,
                  
                ///// Magnetometer block data updating options
                  //MAG_BDU_DISABLE,
                  MAG_BDU_ENABLE,

                ///// Magnetometer X/Y axes ouput data rate
                  //MAG_OMXY_LOW_POWER,
                  //MAG_OMXY_MEDIUM_PERFORMANCE,
                  MAG_OMXY_HIGH_PERFORMANCE,
                  //MAG_OMXY_ULTRA_HIGH_PERFORMANCE,

                ///// Magnetometer Z axis ouput data rate
                  //MAG_OMZ_LOW_PW,
                  //MAG_OMZ_MEDIUM_PERFORMANCE,
                  MAG_OMZ_HIGH_PERFORMANCE,
                  //MAG_OMZ_ULTRA_HIGH_PERFORMANCE,

                ///// Magnetometer run mode
                  MAG_MD_CONTINUOUS,
                  //MAG_MD_SINGLE,
                  //MAG_MD_POWER_DOWN_1,
                  //MAG_MD_POWER_DOWN_2,

                ///// Acceleration full scale
                  ACC_FS_2g,
                  //ACC_FS_4g,
                  //ACC_FS_8g,

                ///// Accelerometer block data updating
                  //ACC_BDU_DISABLE,
                  ACC_BDU_ENABLE,

                ///// Enable X, Y, and/or Z axis
                  //ACC_DISABLE_ALL,
                  //ACC_X_ENABLE,
                  //ACC_Y_ENABLE,
                  //ACC_Z_ENABLE,
                  //ACC_X_ENABLE|ACC_Y_ENABLE,
                  //ACC_X_ENABLE|ACC_Z_ENABLE,
                  //ACC_Y_ENABLE|ACC_Z_ENABLE,
                  ACC_X_ENABLE|ACC_Y_ENABLE|ACC_Z_ENABLE,

                ///// Accelerometer output data rate
                  //ACC_ODR_POWER_DOWN
                  //ACC_ODR_10_Hz
                  //ACC_ODR_50_Hz
                  ACC_ODR_100_Hz
                  //ACC_ODR_200_Hz
                  //ACC_ODR_400_Hz
                  //ACC_ODR_800_Hz
                ) != IMU_SUCCESS)
  {
    SerialUSB.println("Failed setup.");
    while(1);
  }

  if(myIMU.WhoAmI()!= IMU_SUCCESS){
     SerialUSB.println("Interface Problem");
     while(1)
     {
      SerialUSB.println("Interface Problem");
      SerialUSB.println(myIMU.WhoAmI());
     }
  }
  // initialize semaphore
  sem = xSemaphoreCreateCounting(1, 0);
  sem2 = xSemaphoreCreateCounting(1, 0);

  // create task at priority two
  s1 = xTaskCreate(Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);

  // create task at priority one
  s2 = xTaskCreate(Thread2, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  // check for creation errors
  if (sem== NULL || s1 != pdPASS || s2 != pdPASS ) {
    SerialUSB.println(F("Creation problem"));
    while(1);
  }
  
  SerialUSB.println("Scheduler Start RAM");
  xSemaphoreGive(sem);
  // start scheduler
  vTaskStartScheduler();
  SerialUSB.println("Insufficient RAM");
  while(1);
}
//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
  // Not used.
}
