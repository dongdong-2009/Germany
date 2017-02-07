#define  _LcdDrive_GLOBALS
#include <Drive_Lib.h>


#define		LNumb_a		0x08
#define		LNumb_b		0x80
#define		LNumb_c		0x20
#define		LNumb_d		0x01
#define		LNumb_e		0x02
#define		LNumb_f		0x04
#define		LNumb_g		0x40
//#define		LNumb_x		BIT7

//#define		LNumb2_a		0x08
//#define		LNumb2_b		0x08
//#define		LNumb2_c		0x08
//#define		LNumb2_d		0x08
//#define		LNumb2_e		0x08
//#define		LNumb2_f		0x08
//#define		LNumb2_g		0x08

//static char code LCD_NNumber[18] = 
const unsigned char LCD_NNumber[18] = 
{
	LNumb_a+LNumb_b+LNumb_c+LNumb_d+LNumb_e+LNumb_f,			// 0
	LNumb_b+LNumb_c,											// 1
	LNumb_a+LNumb_b+LNumb_d+LNumb_e+LNumb_g,					// 2
	LNumb_a+LNumb_b+LNumb_c+LNumb_d+LNumb_g,					// 3
	LNumb_b+LNumb_c+LNumb_f+LNumb_g,							// 4
	LNumb_a+LNumb_c+LNumb_d+LNumb_f+LNumb_g,					// 5
	LNumb_a+LNumb_c+LNumb_d+LNumb_e+LNumb_f+LNumb_g,			// 6
	LNumb_a+LNumb_b+LNumb_c,									// 7
	LNumb_a+LNumb_b+LNumb_c+LNumb_d+LNumb_e+LNumb_f+LNumb_g,	// 8
	LNumb_a+LNumb_b+LNumb_c+LNumb_d+LNumb_f+LNumb_g,			// 9
	LNumb_a+LNumb_b+LNumb_c+LNumb_e+LNumb_f+LNumb_g,			// a
	LNumb_c+LNumb_d+LNumb_e+LNumb_f+LNumb_g,					// b
	LNumb_a+LNumb_d+LNumb_e+LNumb_f,							// c
	LNumb_b+LNumb_c+LNumb_d+LNumb_e+LNumb_g,					// d
	LNumb_a+LNumb_d+LNumb_e+LNumb_f+LNumb_g,					// e
	LNumb_a+LNumb_e+LNumb_f+LNumb_g,							// f
    LNumb_f+LNumb_e+LNumb_d,                                    // L
    LNumb_e+LNumb_g                                           	// r
};

/*************************液晶低层显示部分*********************************/
void  fnLcd_Init(void)
{
    u8	i;
	LCD->CTRL = 0x0;
	#if  !DL645SOFT_DEBUG
    for(i=0;i<200;i++)
	{
		if(!(LCD->STA & 0x40)) break;
		SystemDelay(1);
	}
   	#endif
   	for(i=0;i<26;i++) {LCDMEM[i]=0x00;LCD->BUF[i] = 0x0;}
 //   LCD->CTRL = 0x1e7;
 #if ( Threephase == YesCheck ) //三相  
//    LCD->CTRL = 0xAf9;
//    LCD->CLKDIV = 0x2a;

    LCD->CTRL = 0x2e9;
    LCD->CLKDIV = 0x2a;	
 #else
    LCD->CTRL = 0x2e7;
    LCD->CLKDIV = 0x3f;
#endif
    
 
  
    LCD->BLINK = 0x000001;
}



/*全屏*/
void fnLcd_AllOnhalf(void)
{
   	u8 i;
	for(i=0;i<13;i++)
    {LCD->BUF[i] = 0xff;LCD->BUF[i+13] = 0;}
}

/*全屏*/
void fnLcd_AllOn(void)
{
   	u8 i;
	for(i=0;i<26;i++)
    {LCDMEM[i]=0xff;LCD->BUF[i] = 0xff;}
}
/*清屏*/
void fnLcd_ClrScr(void)
{
  	u8 i;
  	for(i=0;i<26;i++) //LCDMEM[i]=0x00;
	{LCDMEM[i]=0;LCD->BUF[i] = 0;}
  	return;
}
/******************************************
                    八段显示0~9，A~F字符      
1、点亮或灭掉指定段，B=0时为熄灭,B=1时为点亮
2、nSegment为各段的定义位置，详见包含文件Basic.h
*******************************************/
/*
void fnLcd_SetSegment(u8 nSegment,u8 B)
{
  	
  	u8 dot,i;
	if(nSegment>=192)  return;  // 8com
  	dot=0x01<<(nSegment%8);
  	i = nSegment/8;
//  	if (B)
//  	{
// 		LCDMEM[i] |=dot;
//  	}
//  	else
//  	{
//  		LCDMEM[i] &=(~dot);
//  	}
	return;
}
*/

const unsigned char DigitNum1[19]={
//	0	 1   2    3    4    5    6    7    8    9
0xf5,0x05,0xd3,0x97,0x27,0xb6,0xf6,0x15,0xf7,0xb7,
// A	b	 C   d    E    F          -   r	
0x77,0xe6,0xc2,0xc7,0xf2,0x72,0x00,0x02,0x42
};

const unsigned char MemAddress[9]={13,21,19,17,15,13,4,2,0};
/*
void fnLcd_SetDigit(u8 nDigit,u8 B,u8 *Buf)
{
	nDigit--;
	if (nDigit>9)return;  //数值范围1---9
	if(nDigit == 0x08)
	{
		nDigit = 0x00;
	}
	else   nDigit++;
	
	if(nDigit == 0)
	{
		LCDMEM[MemAddress[nDigit] ] = ((DigitNum1[B] & 0x0f)|(LCDMEM[MemAddress[nDigit]] & 0x08)) + (LCDMEM[MemAddress[nDigit]] & 0xf0);
		LCDMEM[MemAddress[nDigit] + 1 ] = ((DigitNum1[B]>>4) & 0x0f) + (LCDMEM[MemAddress[nDigit] + 1] & 0xf0);
	}
	else if(nDigit == 6)
	{
		LCDMEM[MemAddress[nDigit] ] = (((DigitNum1[B]<<4) & 0xf0)|(LCDMEM[MemAddress[nDigit]] & 0x80)) + (LCDMEM[MemAddress[nDigit]] & 0x0f);
		LCDMEM[MemAddress[nDigit] + 8 ] = (DigitNum1[B] & 0xf0) + (LCDMEM[MemAddress[nDigit] + 8] & 0x0f);
	}
	else
	{
		LCDMEM[MemAddress[nDigit] ] = (((DigitNum1[B]<<4) & 0xf0)|(LCDMEM[MemAddress[nDigit]] & 0x80)) + (LCDMEM[MemAddress[nDigit]] & 0x0f);
		LCDMEM[MemAddress[nDigit] + 1 ] = (DigitNum1[B] & 0xf0) + (LCDMEM[MemAddress[nDigit] + 1] & 0x0f);
	}
	return;
}
*/
void fnLcd_SetDigit(u8 nDigit,u8 B,u8 *Buf)
{	
//	u8 *Buff;
//	Buff = Buf;
	B=8;
	if (nDigit>4)return;  //数值范围1---9
	
	while( nDigit>0 )
	{
	  LCDMEM[B--] |= ((LCD_NNumber[*Buf & 0x0F])>>4)& 0x0F;
	  LCDMEM[B] |= ((LCD_NNumber[*Buf & 0x0F])<<4)& 0xF0;
	  LCDMEM[B--] |=((LCD_NNumber[((*Buf)>>4) & 0x0F])>>4)& 0x0F;
	  LCDMEM[B] |= ((LCD_NNumber[((*Buf)>>4) & 0x0F])<<4)& 0xF0;
   	 Buf++;
	 nDigit--;
   	 }
	
//	if(nDigit == 0)
//	{
//		LCDMEM[MemAddress[nDigit] ] = ((DigitNum1[B] & 0x0f)|(LCDMEM[MemAddress[nDigit]] & 0x08)) + (LCDMEM[MemAddress[nDigit]] & 0xf0);
//		LCDMEM[MemAddress[nDigit] + 1 ] = ((DigitNum1[B]>>4) & 0x0f) + (LCDMEM[MemAddress[nDigit] + 1] & 0xf0);
//	}
//	else if(nDigit == 6)
//	{
//		LCDMEM[MemAddress[nDigit] ] = (((DigitNum1[B]<<4) & 0xf0)|(LCDMEM[MemAddress[nDigit]] & 0x80)) + (LCDMEM[MemAddress[nDigit]] & 0x0f);
//		LCDMEM[MemAddress[nDigit] + 8 ] = (DigitNum1[B] & 0xf0) + (LCDMEM[MemAddress[nDigit] + 8] & 0x0f);
//	}
//	else
//	{
//		LCDMEM[MemAddress[nDigit] ] = (((DigitNum1[B]<<4) & 0xf0)|(LCDMEM[MemAddress[nDigit]] & 0x80)) + (LCDMEM[MemAddress[nDigit]] & 0x0f);
//		LCDMEM[MemAddress[nDigit] + 1 ] = (DigitNum1[B] & 0xf0) + (LCDMEM[MemAddress[nDigit] + 1] & 0x0f);
//	}
	
	return;
}


void fnLcd_RefreshLcdBuf(void)
{
	u8 i;
	for(i=0;i<26;i++)  
		LCD->BUF[i] = LCDMEM[i];
	return;
}
//---------------------------------------------------
















