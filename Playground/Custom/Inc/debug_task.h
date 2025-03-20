#ifndef INC_DEBUG_TASK_H_
#define INC_DEBUG_TASK_H_

#include "cmsis_os.h"

void create_debug_task(void);
void debug_task_code(void *pvParameters);
void debug_print_from_isr(const char *myMessage);

typedef struct
{
	char message[50];
}
DebugMessage_t;

#endif /* INC_DEBUG_TASK_H_ */
