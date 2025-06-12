#include <stdio.h>
#include <stdint.h>
#include "freertos/freertos.h"
#include "driver/gpio.h"

typedef enum {
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET = 1
};

gpio_num_t LED_Pin = GPIO_NUM_2;
bool btn_off = false;
TaskHandle_t h_blinky_task;

void blinky_task(){
  
    gpio_set_direction(LED_Pin, GPIO_MODE_OUTPUT);

    if(btn_off){
        vTaskSuspend(NULL); // null indicates current task
    };

    while(1) {
        gpio_set_level(LED_Pin, GPIO_PIN_SET);
        vTaskDelay(500/portTICK_PERIOD_MS);
        gpio_set_level(LED_Pin, GPIO_PIN_RESET);
        vTaskDelay(500/portTICK_PERIOD_MS);
    } // end while
}

void app_main(void) {

    xTaskCreate (
        blinky_task, 
        "Blinky Task",
        2048,
        NULL,
        1,
        &h_blinky_task
    );

    while(1) {
        // enter low power mode
        

    } //end while
}
