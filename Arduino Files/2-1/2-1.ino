/*
 * Example to demonstrate thread definition, semaphores, and thread sleep.
 */
#include <FreeRTOS_ARM.h>
#include "PowerDueLED.h"

// Declare a semaphore handle.
SemaphoreHandle_t sem;  //
String input = "";
//------------------------------------------------------------------------------
/*
 * ThreadRed, turn the Red LED on for 500 ms. Other colors added to other threads too.
 * This is part 2-1.
 */
static void ThreadRed(void* arg) {
  //Turn on red led.
  SerialUSB.println("Turning on Red LED");
  pd_rgb_led(PD_RED);

  //sleep for 500ms
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);

  //turn off red led.
  SerialUSB.println("Turning off Red LED");
  pd_rgb_led(PD_OFF);

  //sleep for 500ms
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);

  //done with thread
  SerialUSB.println("Done");
  while (1);
}

static void ThreadGreen(void* arg) {
  //Turn on red led.
  SerialUSB.println("Turning on Green LED");
  pd_rgb_led(PD_GREEN);

  //sleep for 500ms
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);

  //turn off red led.
  SerialUSB.println("Turning off Green LED");
  pd_rgb_led(PD_OFF);

  //sleep for 500ms
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);

  //done with thread
  SerialUSB.println("Done");
  while (1);
}

static void ThreadBlue(void* arg) {
  //Turn on red led.
  SerialUSB.println("Turning on Blue LED");
  pd_rgb_led(PD_BLUE);

  //sleep for 500ms
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);

  //turn off red led.
  SerialUSB.println("Turning off Blue LED");
  pd_rgb_led(PD_OFF);

  //sleep for 500ms
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);

  //done with thread
  SerialUSB.println("Done");
  while (1);
}
//------------------------------------------------------------------------------
void setup() {
  // initialize pins for LEDs as output
  pinMode(PD_RED, OUTPUT);
  pinMode(PD_GREEN, OUTPUT);
  pinMode(PD_BLUE, OUTPUT);

  digitalWrite(PD_RED, LOW);
  digitalWrite(PD_GREEN, LOW);
  digitalWrite(PD_BLUE, LOW);

  SerialUSB.begin(9600);
  while (!SerialUSB);
  SerialUSB.println("program starting\n");
  SerialUSB.flush();

  SerialUSB.println(configMINIMAL_STACK_SIZE);
  SerialUSB.println(configTICK_RATE_HZ);

  portBASE_TYPE s1, s2, s3;
    s1 = xTaskCreate(ThreadRed, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    s2 = xTaskCreate(ThreadGreen, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    s3 = xTaskCreate(ThreadBlue, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    
    if (s1 != pdPASS || s2 != pdPASS || s3 != pdPASS ) {
    Serial.println(F("Creation problem"));
    while(1);
  }
  vTaskStartScheduler();
}

// the loop function runs over and over again forever
void loop() {

}
