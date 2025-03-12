
#include "debug_task.h"
#include "FreeRTOS.h"
#include "main.h"


#define DEBUG_TASK_STACK_SIZE 200
#define DEBUG_TASK_PRIORITY osPriorityAboveNormal

StaticTask_t xDebugTaskBuffer;
StackType_t xDebugTaskStack[DEBUG_TASK_STACK_SIZE];

TaskHandle_t xDebugTaskHandle = NULL;

void create_debug_task(void)
{

	xDebugTaskHandle = xTaskCreateStatic(debug_task_code, /* Function that implements the task. */
			"DEBUG_TASK", /* Text name for the task. */
			DEBUG_TASK_STACK_SIZE, /* Number of indexes in the xStack array. */
			( void * ) 1, /* Parameter passed into the task. */
			DEBUG_TASK_PRIORITY, /* Priority at which the task is created. */
			xDebugTaskStack, /* Array to use as the task's stack. */
			&xDebugTaskBuffer /* Variable to hold the task's data structure. */
	);
}


void debug_task_code(void *pvParameters)
{

	/* The parameter value is expected to be 1 as 1 is passed in the
       pvParameters value in the call to xTaskCreateStatic(). */
    configASSERT( ( uint32_t ) pvParameters == 1UL );


    for (;;)
    {
    	osDelay(500);
    }

}


