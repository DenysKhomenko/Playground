
#include "FreeRTOS.h"
#include "main.h"
#include "led_control_task.h"
#include "cmsis_os.h"
#include <limits.h>
#include <stdbool.h>

#define LED_CONTROL_TASK_STACK_SIZE 200
#define LED_CONTROL_TASK_PRIORITY osPriorityAboveNormal

StaticTask_t xLedControlTaskBuffer;
StackType_t xLedControlTaskStack[LED_CONTROL_TASK_STACK_SIZE];

TaskHandle_t xLedControlTaskHandle = NULL;

void create_led_control_task(void)
{

	xLedControlTaskHandle = xTaskCreateStatic(led_control_task_code, /* Function that implements the task. */
			"LED_CONTROL_TASK", /* Text name for the task. */
			LED_CONTROL_TASK_STACK_SIZE, /* Number of indexes in the xStack array. */
			( void * ) 1, /* Parameter passed into the task. */
			LED_CONTROL_TASK_PRIORITY, /* Priority at which the task is created. */
			xLedControlTaskStack, /* Array to use as the task's stack. */
			&xLedControlTaskBuffer /* Variable to hold the task's data structure. */
	);
}


void led_control_task_code(void *pvParameters)
{
	uint32_t notification_val;

	/* The parameter value is expected to be 1 as 1 is passed in the
       pvParameters value in the call to xTaskCreateStatic(). */
    configASSERT( ( uint32_t ) pvParameters == 1UL );


    for (;;)
    {
        xTaskNotifyWait(
            pdFALSE,         /* Don't clear any notification bits on entry. */
            ULONG_MAX,       /* Reset the notification value to 0 on exit. */
            &notification_val,
            portMAX_DELAY    /* Block indefinitely until notified */
        );

        if (notification_val & NOTIFY_TOGGLE_LED)
        {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
        }
    }

}

void notify_task_from_isr(uint32_t notification_val)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if (xLedControlTaskHandle != NULL)
	{
		xTaskNotifyFromISR(xLedControlTaskHandle, /* xTaskToNotify parameter */
			           notification_val,
					   eSetBits, /* eAction parameter. */
	                   &xHigherPriorityTaskWoken );

		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);  /* Ensure a context switch if necessary */
	}
}

