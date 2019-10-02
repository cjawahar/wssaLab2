/*
 * Example to demonstrate thread definition, semaphores, and thread sleep.
 */
#include <FreeRTOS_ARM.h>
#include "PowerDueLED.h"

// Declare a semaphore handle.
SemaphoreHandle_t green, blue, red, brown, purple, white, teal, yellow;  //
String input = "";
//------------------------------------------------------------------------------
/*
 * ThreadRed, turn the Red LED on for 500 ms. Other colors added to this thread too.
 * This is part 2-2 with the semaphores.
 */
static void ThreadRed(void* arg) {
  while (1){
      xSemaphoreTake(red, portMAX_DELAY);

      //Turn on red led.
      SerialUSB.println("Turning on red LED");
      pd_rgb_led(PD_RED);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      //turn off.
      SerialUSB.println("Turning off red LED");
      pd_rgb_led(PD_OFF);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      SerialUSB.println("Done");
      xSemaphoreGive(green);
    }
}

static void ThreadBlue(void* arg) {
  while (1){
      xSemaphoreTake(blue, portMAX_DELAY);

      //Turn on blue led.
      SerialUSB.println("Turning on blue LED");
      pd_rgb_led(PD_BLUE);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      //turn off.
      SerialUSB.println("Turning off blue LED");
      pd_rgb_led(PD_OFF);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      SerialUSB.println("Done");
      xSemaphoreGive(yellow);
    }
}

static void ThreadGreen(void* arg) {
  while (1){
      xSemaphoreTake(green, portMAX_DELAY);

      //Turn on green led.
      SerialUSB.println("Turning on green LED");
      pd_rgb_led(PD_GREEN);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      //turn off.
      SerialUSB.println("Turning off green LED");
      pd_rgb_led(PD_OFF);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      SerialUSB.println("Done");
      xSemaphoreGive(blue);
    }
}

static void ThreadRedBlue(void* arg) {
  while (1){
      xSemaphoreTake(purple, portMAX_DELAY);

      //Turn on red and blue leds.
      SerialUSB.println("Turning on red and blue LEDs");
      pd_rgb_led(PD_PURPLE);
  
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      //turn off
      SerialUSB.println("Turning off red and blue leds");
      pd_rgb_led(PD_OFF);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      //done with thread
      SerialUSB.println("Done");
      xSemaphoreGive(teal);
    }
}

static void ThreadBlueGreen(void* arg) {
  while (1){
      xSemaphoreTake(teal, portMAX_DELAY);

      //Turn on blue and green led.
      SerialUSB.println("Turning on blue and green LED");
      pd_rgb_led(PD_TIEL);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      //turn off
      SerialUSB.println("Turning off blue and green LED");
      pd_rgb_led(PD_OFF);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      //done with thread
      SerialUSB.println("Done");
      xSemaphoreGive(white);
    }
}

static void ThreadRedGreen(void* arg) {
  while (1){
      xSemaphoreTake(yellow, portMAX_DELAY);

      //Turn on red and green led.
      SerialUSB.println("Turning on red and green LED");
      pd_rgb_led(PD_YELLOW);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      //turn off
      SerialUSB.println("Turning off red and green LED");
      pd_rgb_led(PD_OFF);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      //done with thread
      SerialUSB.println("Done");
      xSemaphoreGive(purple);
    }
}

static void ThreadWhite(void* arg) {
  while (1){
      xSemaphoreTake(white, portMAX_DELAY);
    
      //Turn on white led.
      SerialUSB.println("Turning on white LED");
      pd_rgb_led(PD_WHITE);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      //turn off
      SerialUSB.println("Turning off white LED");
      pd_rgb_led(PD_OFF);
    
      //sleep for 500ms
      vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    
      //done with thread
      SerialUSB.println("Done");
      xSemaphoreGive(red);
    }
}
//------------------------------------------------------------------------------
void setup() {
  
  SerialUSB.begin(9600);
  while (!SerialUSB);
  SerialUSB.println("program starting\n");
  SerialUSB.flush();

  SerialUSB.println(configMINIMAL_STACK_SIZE);
  SerialUSB.println(configTICK_RATE_HZ);

  pd_rgb_led_init();

  // initialize semaphore
  red = xSemaphoreCreateCounting(1, 0);
  green = xSemaphoreCreateCounting(1, 0);
  blue = xSemaphoreCreateCounting(1, 1);
  purple = xSemaphoreCreateCounting(1, 0);
  teal = xSemaphoreCreateCounting(1, 0);
  yellow = xSemaphoreCreateCounting(1, 0);
  white = xSemaphoreCreateCounting(1, 0);

  portBASE_TYPE s1, s2, s3, s4, s5, s6, s7;
    s1 = xTaskCreate(ThreadRed, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    s2 = xTaskCreate(ThreadBlue, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    s3 = xTaskCreate(ThreadGreen, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    s4 = xTaskCreate(ThreadRedBlue, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    s5 = xTaskCreate(ThreadBlueGreen, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    s6 = xTaskCreate(ThreadRedGreen, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    s7 = xTaskCreate(ThreadWhite, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    
  vTaskStartScheduler();
}

// the loop function runs over and over again forever
void loop() {

}
