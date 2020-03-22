/*
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-21			ice					 implement some proc in Task 10ms and 20ms
 */
 
#include <Process.h>

static const PRC_PTR c_Taskx1[] =
{
prc_preRun_x1,
prc_main_x1,
prc_postRun_x1,
RT_NULL
};

static const PRC_PTR c_Taskx2[] =
{
prc_preRun_x2,
prc_main_x2,
prc_postRun_x2,
RT_NULL
};

void prc_preRun_x1(void)
{
	rt_kprintf("proc main of x1 is running.\n");
}

void prc_main_x1(void)
{
	rt_int8_t count = 0;
	while(count < 5)
	{
		count++;
		rt_kprintf("%d: 12345\n", count);
	}
}

void prc_postRun_x1(void)
{
}

void prc_preRun_x2(void)
{
	rt_kprintf("proc main of x2 is running.\n");
}

void prc_main_x2(void)
{
	rt_int8_t count = 0;
	while(count < 5)
	{
	count++;
	rt_kprintf("%d: abcdefghijklmnopqlmnabcdefghijklmnopqlmnabcdefghijklmnopqlmnabcdefghijklmnopqlmnabcdefghijklmnopqlmn\n", count);
	}
}

void prc_postRun_x2(void)
{
}

void Run_prc_x1(void)
{
	rt_kprintf("proc x1 is running.\n");
	rt_uint8_t proc_id;
	
	proc_id = 0;
	while(c_Taskx1[proc_id] != RT_NULL)
	{
		c_Taskx1[proc_id]();
		proc_id++;
	}
	
}
	
void Run_prc_x2(void)
{
	rt_kprintf("proc x2 is running. \n");
	rt_uint8_t proc_id;
	
	proc_id = 0;
	while(c_Taskx2[proc_id] != RT_NULL)
	{
		c_Taskx2[proc_id]();
		proc_id++;
	}
	
}