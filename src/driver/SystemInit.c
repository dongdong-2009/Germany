#define  _SystemInit_GLOBALS
#include <Drive_Lib.h>
#include "port.h"
//#include <Scom.h> 

void fnRTCDrive_Delay(void)
{
	SystemDelay(10);
}

void SystemDelay(unsigned short t)
{
	unsigned  short i;
	while(t--)
	{
		for (i = 0;i < 200;i++)
		  ;
		WDT->EN = 0xbb;
	}
}

void fnWDT_Restart( void )
{
	WDT->EN = 0xbb;		/* restart watch dog timer */
}


void fnRCC_Configuration(void)	
{
    fnDl645MainClock_Init();
}

void fnGPIO_Configuration(void)
{
	GPIO->PMA = 0xfb75ff3f;		     // 输入输出配置
//	GPIO->PUA = 0xfb00fce0;             //上拉选择
	GPIO->PIMA = 0;				    // P1.0 TURN P1.1 UP_OVER 
	GPIO->PCA0 = 0x36000A20;	    // P2.0 RXD P2.1 TXD P2.2 IR_RXD P2.3 IR_TXD P2.4 STA P2.5 SWDIO P2.6 RXD3 P2.7 TXD3   复用口配置
	//GPIO->PCA1 = 0x00000020;	    // P3.2 SP(RTC) 复用口配置
	GPIO->PCA1 = 0x00000000;
	GPIO->PIEA = 0xfffffc00;            //输入使能
	

//	GPIO->PB |=0x00000008;              //输出寄存器BACKLED
	//GPIO->PB = 0;              //输出寄存器BACKLED
	GPIO->PB  &= ~(1<<3);
	GPIO->PMB &= ~(1<<3);
	GPIO->PCB &= ~(1<<3);
	GPIO->PBSET |= (1<<3);
	GPIO->PMB &=~ P_YGLED;
	GPIO->PCB |=(1<<12)|(1<<13);
#if 0	
//	GPIO->PB &=0xffffa71f;             
	GPIO->PMB = 0x0000fcf7;		    //输入输出配置
	GPIO->PUB = 0x00000300;			// 上下拉选择
	GPIO->PCB = 0xFFFF0000;	        // P6.0 - P6.7 P7.0 - P7.7 SEG、 PF
	GPIO->PIMB = 0x000000F0;		// 
	GPIO->PIEB = 0xffff7ff8;
	GPIO->PMB &=~ P_YGLED;
	
	
	GPIO->PMC = 0xfffff000;		    	// P8.0 - P8.7 P9.0 - P9.3 SEG
	GPIO->PUC = 0;				// P8.0 - P8.7 P9.0 - P9.7
	GPIO->PCC = 0x00000FFF;	        	// P8.0 - P8.7 P9.0 - P9.3 
		   					   	
	GPIO->PIEC = 0xFFFFFFFF;	
	GPIO->PCE = 0x00000003;	
#endif
}

//---UART------------------------------------------------------
//函数功能：串口初始化
//入口参数：UsartPort串口类型,Cfg串口参数
//出口参数：无
//======================================
//负控协议 透明转发通讯控制字定义
//bit7~bit5:Baud(bps):0-7依次标示:300,600,1200,2400,4800,7200,9600,19200
//bit4:0/1:1/2停止位
//bit3:0/1:无/有校验
//bit2:0/1:偶/奇校验
//bit1,bit0:0-3:5-8位数
//======================================
const u32 BpsTable[] = {300 , 600 , 1200 , 2400 , 4800 , 7200 , 9600 , 19200};
/*
void fnUsart_Init(u8 ComPort , u8 Cfg)  //所有的通讯口初始化
{	
	if(ComPort >= SCOM_PORT_MAX) return;
	
	switch(ComPort)
	{
  	case SCOM_PORT_IR:	//红外通信口
		fnUSART_IRCom_Init(Cfg);
		break;
  	case SCOM_PORT_RS485A:	//第一个Rs485通信口
  		fnUSART_RS485_Init(Cfg);
		break;
	case SCOM_PORT_ZBCOM:
		fnUSART_ZBCOM_Init(Cfg);
		break;
	default: return;
	}

	USART_ITConfig(ComPort , USART_IT_RX , ENABLE);         //接收中断使能
	return;
}
*/
//---------------------------------------------------------
void INTP_Init( void )
{
	INTC->MODE = 0x04; 			// INTP1 fail SEL
	INTC->CTRL = 0x02;
	INTC->MASK = 0x02;
	INTC->STA = 0xff;
}

//定时器初始化 用做1MS中断
void fnINTTC0_Init( void )
{
    TC0->CCFG = 0;
		TC0->CNT = 0;
    TC0->PS = 255;
    //TC0->DN = 13;
		//TC0->DN = 93;
		//TC0->DN = 1799;
		TC0->DN = (fnDl645MainClock_Get()/255000);  //1ms
	//	TC0->DN = (fnDl645MainClock_Get()/2550000);  //100us
    TC0->CTRL = 0x03;		// star TC0
    TC0->IE = 0x01;			// IRQ enable
}

void Stop_Tc0(void)
{
	TC0->CTRL = 0x00;		// star TC0
//  TC0->IE = 0x00;			// IRQ enable
}
void fnLVD_Init(void)
{
//	MADC->LVD_CTRL = 0x00000180;			 // enable LVD
	MADC->LVD_CTRL = 0x00000000;			 // enable LVD
	MADC->LVD_STAT = 0x01ff;
}

void fnINTTCAll_Init( void )
{
	fnINTTC0_Init();
}

void fnINTRTC_Init( void )
{
	RTC->CTRL |= 0x00000100;		//RTC Write enable
	fnRTCDrive_Delay();
	RTC->CTRL = 0x00000159;
	fnRTCDrive_Delay();
	SystemDelay(5);
//	RTC->CNT1 = 0x00; //秒定时
	RTC->CNT2 = 0x03; // 1/64秒定时
	fnRTCDrive_Delay();
	SystemDelay(5);
//	RTC->IE = 0x02;//定时器1
	RTC->IE = 0x04;//定时器2
	fnRTCDrive_Delay();
}

//函数功能：计算时戳(每个定时器节拍，SysStamp累加一次)
//入口参数：Ago需要比较的节拍
//出口参数：返回SysStamp与Ago间的节拍数
/*
u16 fnStamp_Through(u16 Ago)
{
	extern u16	SysStamp;
	if (SysStamp >= Ago)
		{return (SysStamp - Ago);}
	else
		{return ( (0xffff - Ago) + SysStamp);}
}
*/
/*
void SystemInit(void)
{

}
*/
//---------------------------------------------------------
//函数功能：硬件系统初始化
//入口参数：无
//出口参数：无
void fnTarget_Init(void)
{
	fnRCC_Configuration();
	fnGPIO_Configuration();
	fnLVD_Init();
	fnINTTCAll_Init();
	fnINTRTC_Init(); 
	INTP_Init();
#if 0	
	fnLcd_Init();
	fnLcd_ClrScr();
#endif		
	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART1_IRQn);
	NVIC_EnableIRQ(UART3_IRQn);
	NVIC_EnableIRQ(UART5_IRQn);
	NVIC_EnableIRQ(TC0_IRQn);
#if 0
	NVIC_DisableIRQ(KBI_IRQn);
	NVIC_EnableIRQ(CMP_IRQn);
#endif
//	NVIC_DisableIRQ(RTC_IRQn);	
	NVIC_EnableIRQ(RTC_IRQn);
	NVIC_EnableIRQ(VCH_IRQn);
	NVIC_EnableIRQ(DMA_IRQn);
}
