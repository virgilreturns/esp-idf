#include <stdio.h>
#include "freertos.FreeRTOS.h"

void app_main(void)
{
    char *taskName = pcTaskGetName(NULL);
    ESPLOG(taskName, "Hello, starting up!\n");

    while(1);

}
