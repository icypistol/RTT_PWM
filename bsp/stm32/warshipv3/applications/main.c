/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-08     obito0   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <Tasks.h>

/* defined the LED0 pin: PB5 */
#define LED0_PIN    GET_PIN(B, 5)
/* defined the LED0 pin: PE5 */
#define LED1_PIN    GET_PIN(E, 5)

#define PWM_DEV_NAME            "pwm3"
#define PWM_DEV_CHANNEL         1
#define Factor_us								1000
#define Factor_ms								1000000
#define Factor_s								1000000000


static rt_thread_t tid1 = RT_NULL;      /* ???? */
struct rt_device_pwm *pwm_dev;          /* PWM???? */
//static rt_uint32_t factor_ms = 1*1000000;
//static rt_uint32_t factor_s = 1*1000*1000000;
static rt_uint32_t period = 50*Factor_ms;
static rt_uint32_t pulse = 50*Factor_ms;

/* ?? pwm_entry ????? */
static void pwm_entry(void *parameter)
{
    rt_uint32_t count = 0;

    while (1)
    {
			count++;
			rt_thread_mdelay(2000); //This function will let current thread delay for some milliseconds.
        /* set period and pulse, unit is ns */
        //rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
			if(count%2 ==1) 
			{
				rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, 40*Factor_ms);
				rt_kprintf("pwm pulse is odd, equals to %d \n", count);
			}
			//pulse-=500*Factor_ms;
			//if(pulse <= 1*Factor_ms) pulse=2*Factor_s;

			else 
			{
				rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, 10*Factor_ms);
				rt_kprintf("pwm pulse is even, equals to %d \n", count);
			}
    }
    /* step 3??????????,???? PWM ????? */
    rt_pwm_disable(pwm_dev, PWM_DEV_CHANNEL);
}



int main(void)
{
    /* step 1.1??? PWM ?? */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }

    /* step 1.2??? PWM ?????????? */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, 40*Factor_ms);
    /* step 1.3??? PWM ??????? */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);

    /* ????,??? pwm_thread ,??? pwm_entry*/
    tid1 = rt_thread_create("pwm_thread",
                             pwm_entry,
                             RT_NULL,
                             THREAD_STACK_SIZE,
                             THREAD_PRIORITY,
                             THREAD_TIMESLICE);

    /* ?????????,?????? */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

//		CallTasks();
    return RT_EOK;
}


