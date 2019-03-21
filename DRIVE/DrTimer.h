#ifndef __DR_TIMER_H
#define __DR_TIMER_H	  



/* 中断服务程序 */
void TIM3_IRQ(void);
void TIM3_Config();

/***************************初始化*******************************/
void DrTimer_Init(void);


#endif


