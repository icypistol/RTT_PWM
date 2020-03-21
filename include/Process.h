/*
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-21			ice					 implement some proc in Task 10ms and 20ms
 */

#include <rtthread.h>

typedef void (*PRC_PTR)(void);

void prc_preRun_x1(void);
void prc_main_x1(void);
void prc_postRun_x1(void);

void prc_preRun_x2(void);
void prc_main_x2(void);
void prc_postRun_x2(void);

void Run_prc_x1(void);
void Run_prc_x2(void);