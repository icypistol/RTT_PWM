/*
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-19			ice					 implement cyclic tasks of 10ms and 20ms
 */
 
#include <Tasks.h>
#include <Process.h>

struct rt_timer TIM_x1;
struct rt_timer TIM_x2;

struct rt_semaphore Taskx1_run_sem;
struct rt_semaphore Taskx2_run_sem;

struct rt_thread thread_BaseX1;
struct rt_thread thread_x2;

struct rt_device_pwm *pwm_dev;

//static rt_uint32_t factor_ms = 1*1000000;
//static rt_uint32_t factor_s = 1*1000*1000000;
static rt_uint32_t period = 50*Factor_ms;
static rt_uint32_t pulse = 50*Factor_ms;

rt_uint8_t tim_count = 0;

TASK_BODY(BaseX1)
{
	rt_int8_t count = 0;
	while(count<5)
	{
			rt_sem_take(&Taskx1_run_sem, RT_WAITING_FOREVER);
			Run_prc_x1();
			count++;
			//rt_kprintf("BaseX1 is running for %d times \n.", count);
			//rt_kprintf("%d: 12345\n", count);
			//rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, 40*Factor_ms);
	}
	
}

TASK_BODY(X2)
{
	rt_int8_t count = 0;
	while(count<5)
	{
		rt_sem_take(&Taskx2_run_sem, RT_WAITING_FOREVER);
		Run_prc_x2();
		count++;
		//rt_kprintf("x2 is running for %d times \n.", count);
		//rt_kprintf("%d: abcdefghijklmnopqlmnabcdefghijklmnopqlmnabcdefghijklmnopqlmnabcdefghijklmnopqlmnabcdefghijklmnopqlmn\n", count);
		
		//rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, 10*Factor_ms);
	}
	
}

TIM_BODY(X1)
{
	rt_sem_release(&Taskx1_run_sem);
//	tim_count++;
//	if(tim_count < 15)
//	{
//	rt_kprintf("%d: timer x1 is running.\n", tim_count);
//	}
}

TIM_BODY(X2)
{
	rt_sem_release(&Taskx2_run_sem);
//	tim_count++;
//	if(tim_count < 20)
//	{
//	
//	rt_kprintf("%d: timer x2 is running.\n", tim_count);
//	}
}


ALIGN(RT_ALIGN_SIZE)
static char Taskx1_stack[1024];
static char Taskx2_stack[1024];

void Task_init(void)
{
	rt_timer_init(&TIM_x1, "timer1",
                    TIM_NAME(X1), 
                    RT_NULL, 
                    10, 
                    RT_TIMER_FLAG_PERIODIC);
							 
	rt_timer_init(&TIM_x2, "timer2",
                    TIM_NAME(X2), 
                    RT_NULL, 
                    20, 
                    RT_TIMER_FLAG_PERIODIC);
	
	rt_sem_init(&Taskx1_run_sem, "Taskx1_sem", 0, RT_IPC_FLAG_FIFO);
	rt_sem_init(&Taskx2_run_sem, "Taskx2_sem", 0, RT_IPC_FLAG_FIFO);
	
	rt_thread_init(&thread_BaseX1,
							 "TaskX1",
							 //Func_thread_BaseX1,
							 TASK_NAME(BaseX1),
							 RT_NULL,
							 &Taskx1_stack[0],
							 sizeof(Taskx1_stack),
							 11, THREAD_TIMESLICE);
	rt_thread_init(&thread_x2,
							 "TaskX2",
							 TASK_NAME(X2),
							 RT_NULL,
							 &Taskx2_stack[0],
							 sizeof(Taskx2_stack),
							 12, THREAD_TIMESLICE);
}

INIT_COMPONENT_EXPORT(Task_init);

void	CallTasks(void)
{
	pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
	if (pwm_dev == RT_NULL)
	{
			rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
//			return RT_ERROR;
	}

	rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, 40*Factor_ms);
	rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
							 
  rt_timer_start(&TIM_x1);
  rt_timer_start(&TIM_x2);
	
	rt_thread_startup(&thread_BaseX1);
	rt_thread_startup(&thread_x2);
							 
	
}
MSH_CMD_EXPORT(CallTasks, Task sample);

void	ReTasks(void)
{
	rt_thread_resume(&thread_BaseX1);
	rt_thread_resume(&thread_x2);
}
MSH_CMD_EXPORT(ReTasks, Task sample 2);	
