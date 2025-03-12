#ifndef INC_DEBUG_TASK_H_
#define INC_DEBUG_TASK_H_

#include "cmsis_os.h"

void create_debug_task(void);
void debug_task_code(void *pvParameters);


#endif /* INC_DEBUG_TASK_H_ */
