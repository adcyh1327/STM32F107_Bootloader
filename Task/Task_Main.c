#include "main.h"
#include "Task_TCPIP.h"
#include "Task_ModbusTCp.h"
#include "Task_MQTT.h"
#include "Task_HTTP.h"
#include "Task_IO.h"
//#include "Task_LED.h"
#include "transport.h"

#define STKSIZE_IO                     	 STK_SIZE_64
#define STKSIZE_LEDR                     STK_SIZE_32
#define STKSIZE_LEDG                     STK_SIZE_32
#define STKSIZE_TCPIP                    STK_SIZE_512
#define STKSIZE_MBTCP                    STK_SIZE_256
#define STKSIZE_MQTT                     STK_SIZE_1024                   
#define STKSIZE_HTTP                     STK_SIZE_512
#define STKSIZE_BACKGRD                  STK_SIZE_1024

typedef  void (*FunVoidType)(void);
#define ApplicationMsp          0x8008000 
#define ApplicationVect         (ApplicationMsp+4)

OS_STK STK_IO[STKSIZE_IO];
OS_STK STK_ledR[STKSIZE_LEDR];
OS_STK STK_ledG[STKSIZE_LEDG];
#ifdef TCPIP_ENABLE
OS_STK STK_TCPIP[STKSIZE_TCPIP];
#endif
#ifdef MBTCP_ENABLE
OS_STK STK_MBTCP[STKSIZE_MBTCP];
#endif
#ifdef MQTT_ENABLE
OS_STK STK_MQTT[STKSIZE_MQTT];
#endif
#ifdef HTTP_ENABLE
OS_STK STK_HTTP[STKSIZE_HTTP];
#endif

OS_STK STK_BACKGRD[STKSIZE_BACKGRD];

static uint16_t Background_Timer;

void f_GenSoftwareReset(void);
void Task_BackGround(void *p_arg);

// #pragma arm section code=".ARM.__at_0x08000000"
// void f_JumpAppl(void)
// {
//     u32   m_JumpAddress;	
//     FunVoidType JumpToApplication;          /* call this function to jump to appl */
//     if (((*(vu32*)ApplicationMsp) & 0x2FFE0000 ) == 0x20000000)/*MSP check*/
//     {
//         /* Jump to user application */
//         m_JumpAddress = *(vu32*) (ApplicationVect);
//         JumpToApplication = (FunVoidType) m_JumpAddress;
//         /* Initialize user application's Stack Pointer */
//         __MSR_MSP(*(vu32*) ApplicationMsp);
//         JumpToApplication();	 
//         while(1);	  
//     }
// }
// #pragma arm section



void f_GenSoftwareReset(void)
{
    __set_FAULTMASK(1);
	SCB->AIRCR = AIRCR_VECTKEY_MASK | (u32)0x04;
}

