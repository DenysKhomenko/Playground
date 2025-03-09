#ifndef LED_CONTROL_TASK_H
#define LED_CONTROL_TASK_H

#include <stdint.h>
#include "cmsis_os.h"

void create_led_control_task(void);
void led_control_task_code(void *pvParameters);
void notify_task_from_isr(uint32_t notification_val);

typedef enum
{
    NOTIFY_TOGGLE_LED = (1 << 0),
    NOTIFY_RFU_1      = (1 << 1),  // Bit 1 - Reserved for Future Use
    NOTIFY_RFU_2      = (1 << 2)
    //...
    //Should be 32 in total since notifications value is uint32t
}e_led_control_notification_t;

#endif // LED_CONTROL_TASK_H
