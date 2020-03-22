/*
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-19			ice					 implement cyclic tasks of 10ms and 20ms
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED0 pin: PB5 */
#define LED0_PIN    GET_PIN(B, 5)
/* defined the LED0 pin: PE5 */
#define LED1_PIN    GET_PIN(E, 5)

#define PWM_DEV_NAME            "pwm3"
#define PWM_DEV_CHANNEL         1
#define Factor_us								1000
#define Factor_ms								1000000
#define Factor_s								1000000000
#define TASK_BODY(x)  static void Func_thread_##x(void *param)
#define TASK_NAME(x)  Func_thread_##x
#define TIM_BODY(x)  static void Func_timer_##x(void *param)
#define TIM_NAME(x)  Func_timer_##x

#define THREAD_PRIORITY         15
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

void CallTasks(void);
void Task_init(void);

TASK_BODY(BaseX1);
TASK_BODY(X2);

TIM_BODY(X1);
TIM_BODY(X2);

extern struct rt_thread thread_BaseX1;
extern struct rt_thread thread_x2;

extern struct rt_semaphore Taskx1_run_sem;
extern struct rt_semaphore Taskx2_run_sem;
extern struct rt_device_pwm *pwm_dev;