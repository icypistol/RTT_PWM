/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-08     obito0   first version
 * 2020-03-19			ice					 implement cyclic tasks of 10ms and 20ms
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <Tasks.h>

int main(void)
{
		CallTasks();
    return RT_EOK;
}


