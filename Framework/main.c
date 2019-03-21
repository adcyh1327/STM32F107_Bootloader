#include "main.h"
#include "stm32f10x.h" 
#include <string.h>	   
#include "stdio.h"


#define APP_CRC_BASE            0x8024000 
#define APP_CRC_ADDR            0x8024000
#define ApplicationMsp          0x8008000 
#define ApplicationVect         (ApplicationMsp+4) 


typedef  void (*FunVoidType)(void);
typedef u32 (*FunWriteType)(u8*, u32, u16);	 

const unsigned long SystemFrequency = 72000000; /* 主频72Mhz */
const  u32   APPL_CRC __attribute__((at(APP_CRC_ADDR)));//={0x00}; 
static FunVoidType JumpToApplication;          /* call this function to jumo to appl */
static u32   m_JumpAddress;	  


vu8 cnt;

 void f_JumpAppl(void)
{
  if (((*(vu32*)ApplicationMsp) & 0x2FFE0000 ) == 0x20000000)/*MSP check*/
  {
    if(0xA1A2A3A4==APPL_CRC)
	{  
        #if 0
        TIM_DeInit(TIM5);
        TIM_Cmd(TIM5, DISABLE);
        USART_DeInit(UART4);
        USART_Cmd(UART4,DISABLE);
        USART_DeInit(UART5);
        USART_Cmd(UART5,DISABLE);
        RCC_RTCCLKCmd(DISABLE);
        #endif
      /* Jump to user application */
      m_JumpAddress = *(vu32*) (ApplicationVect);
      JumpToApplication = (FunVoidType) m_JumpAddress;
      /* Initialize user application's Stack Pointer */
      __MSR_MSP(*(vu32*) ApplicationMsp);
      JumpToApplication();	 
	  while(1);	  
	}
  }
}

/*
** main主函数
*/
int main(void)
{   
    SystemInit();
    Config_DrCommon();
    while(1)
    {
       cnt++;
            if(cnt >=200)
            {
                cnt = 0;
                f_JumpAppl();
            }
    }

    return 0;
}


/*
** UCOSII任务启动之前的初始化
*/
void Config_DrCommon(void)
{
    PERIPH_CLOCK_IO_ALL_ENABLE;
    TIM3_Config();
    DrUsart_Init();
    
}




