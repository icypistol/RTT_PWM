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



extern struct rt_device_pwm *pwm_dev;

void	CallTasks(void);
static void Func_thread_BaseX1(void *param);
static void Func_thread_X2(void *param);


#define THREAD_PRIORITY         15      /* ????? */
#define THREAD_STACK_SIZE       512     /* ????? */
#define THREAD_TIMESLICE        5       /* ??????? */
//ALIGN(RT_ALIGN_SIZE)
//static char Taskx1_stack[256];
//static char Taskx2_stack[256];
extern struct rt_thread thread_BaseX1;
extern struct rt_thread thread_x2;

extern struct rt_semaphore Taskx1_run_sem;
extern struct rt_semaphore Taskx2_run_sem;
