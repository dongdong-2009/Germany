
#define  _DL645CLOCK_GLOBALS
#include <Drive_Lib.h>

//*********主时钟切换到外部高速晶振模式***********
void fnDl645MainClock_Init( void )
{
	uint32_t bsts;
	SYSCTL->SYS_PS = 0x82;
	//bsts=SysModeChg(2,1);//3	//3.6864Mhz
	if((SYS_CLK==SYS_CLK_29M) || (SYS_CLK==SYS_CLK_14M))
	{
		SYSCTL->OSC_CTRL2 = 0x00000013; //外部晶振，f=29.4912MHz
	}

	SystemDelay(100);
	if(SYS_CLK==SYS_CLK_3M)
	{
		bsts=SysModeChg(2,1);
	}
	else if(SYS_CLK==SYS_CLK_29M)
	{	
		bsts=SysModeChg(3,0);
	} 
	else if(SYS_CLK==SYS_CLK_14M)	
	{
		bsts=SysModeChg(3,1);
	}
	else
	{
		bsts=SysModeChg(2,1);
	}
	SYSCTL->SYS_PD = 0x0018;
	//SYSCTL->MOD0_EN = 0x3b54;
	//SYSCTL->MOD0_EN = 0x0b54;
	//SYSCTL->MOD0_EN = 0x0b5c;
	//SYSCTL->MOD1_EN = 0x0fe0;
#if 0	
	SYSCTL->MOD0_EN = (1<<8)|(1<<4)|(1<<3)|(1<<2);
	SYSCTL->MOD0_EN |= (1<<7);
//	SYSCTL->MOD0_EN = (1<<8)|(1<<3)|(1<<2);
	SYSCTL->MOD1_EN = (1<<10)|(1<<9)|(1<<5);
	//SYSCTL->MOD1_EN = (1<<9)|(1<<5);
	SYSCTL->MOD1_EN |=(1<<4) | (1<<0);
#else
	SYSCTL->MOD0_EN = (1<<4)|(1<<3)|(1<<2);
	SYSCTL->MOD0_EN |= (1<<7)|(1<<9);
//	SYSCTL->MOD0_EN = (1<<8)|(1<<3)|(1<<2);
	SYSCTL->MOD1_EN = (1<<10)|(1<<9)|(1<<5);
	//SYSCTL->MOD1_EN = (1<<9)|(1<<5);
	SYSCTL->MOD1_EN |=(1<<4) | (1<<0);
#endif	
//	SYSCTL->INTC_EN = 0x01ff;
	SYSCTL->KBI_EN = 0x0000;
	SYSCTL->SYS_RST = 0x0000;   
	SystemDelay(10);
	WDT->CTRL |= (7<<1);
	SYSCTL->SYS_PS = 0x00;
	while(bsts);
	return;
}

//*******主时钟切换到32768HZ低功耗模式********
void fnDl645SubClock_Init( void )
{
	SysModeChg(0,0);
}

void fnDl645RCClock_Init( void )
{
	SysModeChg(1,0);
}

//*******获取当前系统时钟频率********
u32 fnDl645MainClock_Get( void )
{
	u32  freq = 1618496;
	if(((SYSCTL->OSC_CTRL1 >> 8) & 0x7) == 0x3)
		freq = 32768;
    else if(((SYSCTL->OSC_CTRL1 >> 8) & 0x7) == 0x2)
		freq = 1843200;
    else if(((SYSCTL->OSC_CTRL1 >> 8) & 0x7) == 0x1)
    	freq = 3686400;
    else if(((SYSCTL->OSC_CTRL1 >> 8) & 0x7) == 0x0)
    	freq = 7372800;
    else if(((SYSCTL->OSC_CTRL1 >> 8) & 0x7) == 0x4)
    	freq = 14745600;
    else if(((SYSCTL->OSC_CTRL1 >> 8) & 0x7) == 0x5)
    	freq = 29491200;
  	if(SYSCTL->OSC_CTRL1 & 0x00000020)	freq = 1843200-224704;
  	return freq;
}
