/*
 * Example to demonstrate thread definition, semaphores, and thread sleep.
 */
#include <FreeRTOS_ARM.h>
#include "PowerDueLED.h"

QueueHandle_t input_q;
//------------------------------------------------------------------------------
/*
 * Task 1 -- Get inputs from read buffer.
 */
static void GetInputSeq(void* arg) {
  while (1){
    if (SerialUSB.available()) {
     char colors= SerialUSB.read();
      // Same as xQueueSendToBack? -- Posts an item to the back of queue.
      xQueueSend(input_q, &colors, portMAX_DELAY);
    }
    vTaskDelay(500);
  }
}

static void BlinkLeds(void* arg) {
  while (1){
      char inputColor;
      pd_rgb_led(PD_OFF);

      xQueueReceive(input_q, &inputColor, portMAX_DELAY);

      switch (inputColor){
        case 'r':
          pd_rgb_led(PD_RED);
          vTaskDelay(500);
          pd_rgb_led(PD_OFF);
          vTaskDelay(500);
          break;

        case 'g':
          pd_rgb_led(PD_GREEN);
          vTaskDelay(500);
          pd_rgb_led(PD_OFF);
          vTaskDelay(500);
          break;

        case 'b':
          pd_rgb_led(PD_BLUE);
          vTaskDelay(500);
          pd_rgb_led(PD_OFF);
          vTaskDelay(500);
          break;

        case 'y':
          pd_rgb_led(PD_YELLOW);
          vTaskDelay(500);
          pd_rgb_led(PD_OFF);
          vTaskDelay(500);
          break;

        case 'p':
          pd_rgb_led(PD_PURPLE);
          vTaskDelay(500);
          pd_rgb_led(PD_OFF);
          vTaskDelay(500);
          break;

        case 't':
          pd_rgb_led(PD_TIEL);
          vTaskDelay(500);
          pd_rgb_led(PD_OFF);
          vTaskDelay(500);
          break;

        case 'w':
          pd_rgb_led(PD_WHITE);
          vTaskDelay(500);
          pd_rgb_led(PD_OFF);
          vTaskDelay(500);
          break;
    }
    vTaskDelay(500);
    }
}

void setup() {
  portBASE_TYPE s1, s2;

  SerialUSB.begin(9600);
  while(!SerialUSB);
  input_q = xQueueCreate(10, 1);
  pd_rgb_led_init();

  // initialize semaphore
  
  // create task to read user input
  s1 = xTaskCreate(GetInputSeq, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  // create task to blink corresponding leds
  s2 = xTaskCreate(BlinkLeds, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);

  // start scheduler
  vTaskStartScheduler();
  Serial.println("Insufficient RAM");
  while(1);
}
//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
  // Not used.
}
