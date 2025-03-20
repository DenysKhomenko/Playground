
#include "debug_task.h"
#include "FreeRTOS.h"
#include "main.h"
#include <string.h>

#define DEBUG_TASK_STACK_SIZE 200
#define DEBUG_TASK_PRIORITY osPriorityAboveNormal

#define QUEUE_LENGTH    10
#define MESSAGE_LENGTH 50
#define MESSAGE_SIZE (MESSAGE_LENGTH * sizeof(uint8_t))


/* The variable used to hold the queue's data structure. */
static StaticQueue_t xStaticQueue;
uint8_t ucQueueStorageArea[ QUEUE_LENGTH * MESSAGE_SIZE ];
QueueHandle_t xQueue;

StaticTask_t xDebugTaskBuffer;
StackType_t xDebugTaskStack[DEBUG_TASK_STACK_SIZE];
TaskHandle_t xDebugTaskHandle = NULL;

extern UART_HandleTypeDef huart2;

void create_debug_task(void)
{

    xQueue = xQueueCreateStatic( QUEUE_LENGTH,
    							MESSAGE_SIZE,
                                 ucQueueStorageArea,
                                 &xStaticQueue );

    /* pxQueueBuffer was not NULL so xQueue should not be NULL. */
    configASSERT( xQueue );


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

    DebugMessage_t receivedMsg;
    BaseType_t xStatus;

    for (;;)
    {

    	/* This call should always find the queue empty because this task will
    	immediately remove any data that is written to the queue. */
    	if( uxQueueMessagesWaiting( xQueue ) != 0 )
    	{
    		//Handle later
    	}

    	xStatus = xQueueReceive( xQueue, receivedMsg.message, portMAX_DELAY);
    	if( xStatus == pdPASS )
    	{
    		/* Data was successfully received from the queue, print out the
    	 	received value. */
    		HAL_UART_Transmit_DMA(&huart2, (uint8_t *) receivedMsg.message, MESSAGE_SIZE);
    	}

    }

}

void debug_print_from_isr(const char *myMessage)
{
BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	DebugMessage_t msg;

	strncpy(msg.message, myMessage, sizeof(msg.message));

	xQueueSendToBackFromISR(xQueue,
	&msg,
	 &xHigherPriorityTaskWoken );

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}


