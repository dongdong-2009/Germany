//#include "Common.h"
#include "TypeMeter.h"
#include "TypeE2p.h"
//#include "msp430f6736.h"
#include "Measure.h"
//#include "In430.h"
#include "Type.h"
#include "Data.h"
#include "General.h"
#include "Mem.h"
#include "General.h"
#include "Initial.h"
#include "RsComm.h"
#include "Display.h"
#include "Time.h"
#include "Power.h"
#include <Drive_Lib.h>
#define  _RTCDrive_GLOBALS



//函数功能：RTC读取数据
//入口参数：Dst读取数据缓冲区目标指针
//出口参数：SUCCESS成功，ERROR失败
ErrorStatus fnRTCDrive_Read(u8 *Dst)
{
	Dst[0]=RTC->SC;    
	Dst[1]=RTC->MN;    
	Dst[2]=RTC->HR;    
	Dst[4]=RTC->DT;    
	Dst[5]=RTC->MO;    
	Dst[6]=RTC->YR;    
	Dst[3]=RTC->DW;
	return(SUCCESS);
}

//函数功能：RTC写入数据
//入口参数：Dst写数缓冲区源指针，Repeat失败重复次数
//出口参数：SUCCESS成功，ERROR失败
ErrorStatus fnRTCDrive_Write(u8 *Dst , u8 Repeat)
{
	u8 Buffer[7],i;
	RTC->CTRL |= 0x00000100;		//RTC Write enable
	for(;Repeat>0;Repeat--)
	{
		if(!(RTC->CTRL & 0x200)) break;
		fnRTCDrive_Delay();
	}
	if(RTC->CTRL & 0x200) return(ERROR);
	RTC->DW = Dst[3];
	fnRTCDrive_Delay();  
	RTC->YR = Dst[6];
	fnRTCDrive_Delay(); 
	RTC->MO = Dst[5];
	fnRTCDrive_Delay(); 
	RTC->DT = Dst[4];
	fnRTCDrive_Delay(); 
	RTC->HR = Dst[2];
	fnRTCDrive_Delay(); 
	RTC->MN = Dst[1];
	fnRTCDrive_Delay(); 
	RTC->SC = Dst[0];
	fnRTCDrive_Delay(); 
	if(!fnRTCDrive_Read(Buffer))return(ERROR);
	for(i=6;i>0;i--)
	{
		if(Buffer[i]!=Dst[i]) 
			return(ERROR);
	}
	RTC->CTRL &= 0xfffffeff;      // RTC Write Disable
	return(SUCCESS);
}


//函数功能：RTC初始化函数
//入口参数：无
//出口参数：SUCCESS成功，ERROR失败
ErrorStatus fnRTCDrive_Init(void)
{
	u16 AddingTimes=0;
	RTC->CTRL = 0x100;
	while(RTC->CTRL & 0x200)
	{
		if(++AddingTimes>65000)return(ERROR); //防止死循环
	}
	RTC->CTRL = 0x100;
	fnRTCDrive_Delay(); 
	RTC->CTRL = 0x101;
	fnRTCDrive_Delay(); 

	return(SUCCESS);
}

//函数功能：系统时钟读取
//入口参数：Clock目标指针
//出口参数：SUCCESS成功，ERROR失败
//ErrorStatus fnSysClock_Read(sDF01 *Clock)
ErrorStatus fnSysClock_Read(unsigned char* RAM_Addr)
{
	u8 Buffer[7];
	if(!fnRTCDrive_Read(Buffer))return(ERROR);
//	Clock->Second=(Buffer[0])& 0x7f;    
//	Clock->Minute=(Buffer[1])& 0x7f;    
//	Clock->Hour=(Buffer[2]) & 0x3f;    
//	Clock->Day=(Buffer[4]) & 0x3f;    
//	Clock->Month=(Buffer[5]) & 0x1f;    
//	Clock->Year=(Buffer[6]);    
//	Clock->Week=(Buffer[3])&0x07;
	*(RAM_Addr+0)=(Buffer[0])& 0x7f;    
	*(RAM_Addr+1)=(Buffer[1])& 0x7f;    
	*(RAM_Addr+2)=(Buffer[2]) & 0x3f;    
	*(RAM_Addr+4)=(Buffer[4]) & 0x3f;    
	*(RAM_Addr+5)=(Buffer[5]) & 0x1f;    
	*(RAM_Addr+6)=(Buffer[6]);    
	*(RAM_Addr+3)=(Buffer[3])&0x07;
	return(SUCCESS);
}

//函数功能：系统时钟写入
//入口参数：Clock源指针
//出口参数：SUCCESS成功，ERROR失败
//ErrorStatus fnSysClock_Write(sDF01 *Clock)
ErrorStatus fnSysClock_Write(unsigned char* RAM_Addr)
{
	u8 Buffer[7];
//	Buffer[0]=(Clock->Second)& 0x7f;
//	Buffer[1]=(Clock->Minute)& 0x7f;
//	Buffer[2]=(Clock->Hour) & 0x3f;
//	Buffer[3]=(Clock->Week)&0x07;
//	Buffer[4]=(Clock->Day) & 0x3f;
//	Buffer[5]=(Clock->Month) & 0x1f;
//	Buffer[6]=(Clock->Year);
	
	Buffer[0]=*(RAM_Addr+0)& 0x7f;
	Buffer[1]=*(RAM_Addr+1)& 0x7f;
	Buffer[2]=*(RAM_Addr+2) & 0x3f;
	Buffer[3]=*(RAM_Addr+6)&0x07;
	Buffer[4]=*(RAM_Addr+3) & 0x3f;
	Buffer[5]=*(RAM_Addr+4) & 0x1f;
	Buffer[6]=*(RAM_Addr+5);
	
	return(fnRTCDrive_Write(Buffer, 3));
}
//****************************************************************
void ProcRTCSumWin(void)
{
	unsigned char Buff[10],Season;
		
	E2P_RData(Buff,SumWinSwitch,1);
	if(Buff[0])
	{
		Season=SummerORwinter();
		{
			if(Season==0)
			{
				E2P_RData(Buff,RtcShiftYear,3);
				if(Buff[0]==Clk.Year[0])
					return;
				else
				{
					Buff[0]=Clk.Year[0];
					Buff[1]=0xff;
					Buff[2]=0x00;
					E2P_WData(RtcShiftYear,Buff,3);	
					Clr_bitwinter	
//					SumMin=GetGmMin(&Clk.Min[0]);
//					SumMin+=60;
//					Min_Date(Buff, SumMin);
//					RAM_Write(&Clk.Hour[0],&Buff[2],4);
					RtcAdd1Hour(&Clk.Hour[0]);  //加1小时
					RAM_Write( Buff,&Clk.Sec[0],3);
					Buff[3]=Clk.Week[0];
					RAM_Write( &Buff[4],&Clk.Day[0],3);
//#if( RTCCHIP == RX8025 )								
//					E2Pwrite( 0x0, Buff, 7, RTCAds );
//#else
//					TimeDataTurn(Buff);
//					E2Pwrite( TimeAddr, Buff, 7, S35390AAds );
//#endif					
					fnSysClock_Write(&Clk.Sec[0]);

//					TamperRecord(0x12);//冬夏令切换记录
				}		
			}
			else if(Season==0x1)
			{
				E2P_RData(Buff,RtcShiftYear,3);
				if(Buff[1]==Clk.Year[0])
				return;
				else
				{
					Buff[1]=Clk.Year[0];
					Buff[2]=0x01;
					E2P_WData(RtcShiftYear,Buff,3);	
					Set_bitwinter
					RtcSub1Hour(&Clk.Hour[0]);  //减1小时
//					SumMin=GetGmMin(&Clk.Min[0]);
//					SumMin-=60;
//					Min_Date(Buff, SumMin);
//					RAM_Write(&Clk.Hour[0],&Buff[2],4);
					RAM_Write( Buff,&Clk.Sec[0],3);
					Buff[3]=Clk.Week[0];
					RAM_Write( &Buff[4],&Clk.Day[0],3);
//#if( RTCCHIP == RX8025 )								
//					E2Pwrite( 0x0, Buff, 7, RTCAds );
//#else
//					TimeDataTurn(Buff);
//					E2Pwrite( TimeAddr, Buff, 7, S35390AAds );
//#endif					
					fnSysClock_Write(&Clk.Sec[0]);
//					TamperRecord(0x12);//冬夏令切换记录
				}
			}	
		}
	}
}

//-------------------------------------
void ProShiftFlag(void)
{
	unsigned char Buff[5];
	
	if(SummerORwinter()==0)
	{
		Buff[0]=Clk.Year[0];
		Buff[1]=0xff;
		Buff[2]=0x00;
		Clr_bitwinter	
	}
	else
	{
		Buff[0]=0xff;
		Buff[1]=Clk.Year[0];
		Buff[2]=0x01;
		Set_bitwinter
	}	
	E2P_WData(RtcShiftYear,Buff,3);	
}

/*
//-------------------------------------
//返回00是夏季，不是00是冬季	
//Switching should be as in FW for Lithuania: 
//o	winter/summer time period on last Sunday of March at 2 AM (2->3)
//o	summer/winter time period on last Sunday of October at 3 (3->2). 
unsigned char SummerORwinter(void)
{
	unsigned char HexYear,Buff[20];

	E2P_RData(Buff,RtcShiftYear,3);	
	if(Buff[2])
		Set_bitwinter
	else
		Clr_bitwinter		
		
	HexYear=BCD_Byte(Clk.Year[0]);
		
	Buff[0]=0x00;
	Buff[1]=0x02;
	Buff[2]=LastSunTab[HexYear].MarSun;
	Buff[3]=0x03;
	if(Data_Comp(Buff,&Clk.Min[0],4)>0)
		{return(0x11);}
	Buff[0]=0x00;
	Buff[1]=0x03;
	if(bitwinter)
		{Buff[1]=0x02;}//已经是冬季，把时改成2
	Buff[2]=LastSunTab[HexYear].OctSun;
	Buff[3]=0x10;		//winter season

	if(Data_Comp(Buff,&Clk.Min[0],4)>0)
		return(0x00);	//summer season
	else
		return(0x01);	//winter season
}*/
//-------------------------------------
//返回00是夏季，不是00是冬季	
//Switching should be as in FW for Lithuania: 
//o	winter/summer time period on last Sunday of March at 3 AM (3->4)
//o	summer/winter time period on last Sunday of October at 4 (4->3). 
unsigned char SummerORwinter(void)
{
	unsigned char HexYear,Buff[20];

	E2P_RData(Buff,RtcShiftYear,3);	
	if(Buff[2])
		Set_bitwinter
	else
		Clr_bitwinter		
		
	HexYear=BCD_Byte(Clk.Year[0]);
		
	Buff[0]=0x00;
	Buff[1]=0x02;
	Buff[2]=LastSunTab[HexYear].MarSun;
	Buff[3]=0x03;
	if(Data_Comp(Buff,&Clk.Min[0],4)>0)
		{return(0x11);}
	Buff[0]=0x00;
	Buff[1]=0x03;
	if(bitwinter)
		{Buff[1]=0x02;}//已经是冬季，把时改成2
	Buff[2]=LastSunTab[HexYear].OctSun;
	Buff[3]=0x10;		//winter season

	if(Data_Comp(Buff,&Clk.Min[0],4)>0)
		return(0x00);	//summer season
	else
		return(0x01);	//winter season
		
//	E2P_RData(Buff,RtcShiftYear,3);	
//	if(Buff[2])
//		Set_bitwinter
//	else
//		Clr_bitwinter		
//		
//	HexYear=BCD_Byte(Clk.Year[0]);
//		
//	Buff[0]=0x00;
//	Buff[1]=0x00;
//	Buff[2]=0x01;
//	Buff[3]=0x04;
//	if(Data_Comp(Buff,&Clk.Min[0],4)>0)
//		{return(0x11);}
//	Buff[0]=0x00;
//	Buff[1]=0x00;
//	Buff[2]=0x01;
//	Buff[3]=0x11;		//winter season
//	if(bitwinter)
//	{
//		Buff[0]=0x00;
//		Buff[1]=0x23;
//		Buff[2]=0x31;
//		Buff[3]=0x10;		//winter season
//		
//	}//已经是冬季，把时改成2
//
//	if(Data_Comp(Buff,&Clk.Min[0],4)>0)
//		return(0x00);	//summer season
//	else
//		return(0x01);	//winter season	
		
}
/*****************************************************************
 	Temperature
 	T = (N*2500/4096-986)/3.55)*10	// 1 decimal 
*****************************************************************/
/*
void Temperature(void)
{
	Clk.Temp = ( (long)SM.DetTemp*2500 - (long)986*4096 )/1454;	// 10/(4096*3.55)= 1/1454;
	Word_BCD( Real.Temp, Clk.Temp );
}
*/
/*****************************************************************
 	Calculate Clock Adjust Fact
	 	T_ppm = (0.034*(T-25)*(T-25))*100	// 2 decimal
 		O_ppm = ppm (Set parameter)			// 2 decimal
 			ppm = 0.01 (minimun)
 		Clk_Adj = 1000000/( O_ppm - T_ppm )
 		Pus_Adj = SMCLK / Clk_Adj		(SMCLK=32768*128)
*****************************************************************/
/*
void ClkAdjFact(void)
{
	Clk.Adj_Fact = Adj.Crys_Offs - ((long)Clk.Temp-250)*((long)Clk.Temp-250)*34/1000;
	if( Clk.Adj_Fact > -24 && Clk.Adj_Fact < 24 ){
		Clk.Adj_Fact = 0;
		Clk.PsAdj_Fact = 0;
	}else{
		Clk.Adj_Fact = 1000000*100 / Clk.Adj_Fact;
		Clk.PsAdj_Fact = (32768*128) / Clk.Adj_Fact;
	}
}
*/
//*****************************************************************
/*****************************************************************/
/*
void ClkAdjFact(void)
{
	short Temp,Temp2;
	unsigned char Temp3,ClockAdj_base;
	
	Temp = Clk.Temp;
	E2P_RData( (unsigned char*)&ClockAdj_base,ClockAdj, 1 );
	
	Temp2 = (( unsigned long)Temp-23)*(Temp-23)*35/1017;	
	Temp3 = Temp2;
	Temp = 0 - Temp2;
	
	ClockAdj_base &=~ 0x80;
	if(ClockAdj_base >= 64)
	{
		ClockAdj_base = 128 - ClockAdj_base;
		if(Temp3 > ClockAdj_base)
		{
			Temp3 -= ClockAdj_base;
			if(Temp3 > 60)
				Temp3 /= 3;
			else
				Temp3 |= 0x80;	 
			
		}else{
			Temp3 = ClockAdj_base - Temp3;
			Temp3 = 128 - Temp3;
			Temp3 |= 0x80;
		}	
		
	}else{
		Temp3 += ClockAdj_base;
		if(Temp3 > 60)
				Temp3 /= 3;
			else
				Temp3 |= 0x80;	
	}	
//	Temp3 |= 0x80;
	if( Temp3 != Clk.RTCOffset ) 
	{
		//Temp3 = Clk.RTCOffset;
		Clk.RTCOffset = Temp3;
		E2Pwrite( JZAddr, (unsigned char*)&Temp3, 1, S35390AAds );		//设频率修正
	}
*/
	
/*
#if( RTCCHIP == RX8025 )
	Temp3 = (0 - Temp2/3) & ~0x80;
	if( Temp3 != Clk.RTCOffset ) 
	{
		//Temp3 = Clk.RTCOffset;
		Clk.RTCOffset = Temp3;
		_E2Pwrite( 0x70, &Clk.RTCOffset, 1, RTCAds );		//设频率修正
	}
#else
#endif	
*/	
//	Temp = Adj.Crys_Offs - (( unsigned long)Temp-25)*(Temp-25)*35/1000;
/*	if( Temp == 0 )
	{
		Clk.Adj_Fact = 0;
//		Clk.PsAdj_Fact = 0;
	}
	else
	{
		//Clk.Adj_Fact = 1000000*100 / Clk.Adj_Fact;
		Clk.Adj_Fact = 1000000 / Temp;
//		Clk.PsAdj_Fact = (32768*128) / Clk.Adj_Fact;
	}
	
}
*/

/*****************************************************************
*****************************************************************/
/*
void Temperature(void)
{
	unsigned char Buff[2];
	unsigned char* Point;
	int i;

	Point = Buff;
//	SM.RZeroMk = 986;
//	Clk.Temp = ((long)SM.RZeroMk*4096 - (long)SM.DetTemp*15000 )/14541;		//0.1度
	//Clk.Temp = ((unsigned long)SM.DetTemp*15000 - (unsigned long)SM.RZeroMk*4096 )/14541;		//0.1度
	
//	if((Flag.Power & F_PwrUp) != 0)
//	{
	*(Point+1) = 0;
	*Point = 0;
//#if( RTCCHIP == RX8025 )
	E2PRead( Point, 0x00, 2, TCN75Ads );
//#else				
//	_E2PRead( Point, 0x11, 2, DS3231Ads );		//DS3231 0.1度
//#endif
//	i = (((*Point)*256 + *(Point+1) )/128) & 0x1ff ;
//	if( i > 255 ) 
//	{
//		i = 512 - i;
//		i = i*5;
//		Clk.Temp = 0 - i;
//	}		
//	else Clk.Temp = i*5;
////	}
////	else
////	{	
//		//SM.RZeroMk = 9860;
//		//Clk.Temp = ((unsigned long)SM.DetTemp*15000 - (unsigned long)SM.RZeroMk*4096 )/14541;		//0.1度
////		Clk.Temp = ((long)SM.DetTemp*25000 - 40386560 )/14541;		//0.1度
////		Clk.Temp = ((long)SM.DetTemp*15000 - 40386560 )/14541;		//0.1度
////	}
	
	i = (*Point) ;
	if( i & 0x80) 
	{
		i = 256 - i;
		Clk.Temp = 0 - i;
	}		
	else Clk.Temp = i;
	
//	i = Clk.Temp;
//	if( i<0 ) i = 0 - i;
//	Word_BCD(&SM.Wendu[0], (unsigned int)i );
//	if( Clk.Temp < 0 ) SM.Wendu[1] |= 0x80; 
	ClkAdjFact();
}
*/
/*****************************************************************
*****************************************************************/
/*
void OpenLM75(void)
{
	unsigned char Buff[2];
	unsigned char* Point;

	Point = Buff;

	*Point = 0;
	E2Pwrite( 0x01, Point, 1, TCN75Ads );
}

void CloseLM75(void)
{
	unsigned char Buff[2];
	unsigned char* Point;

	Point = Buff;
	
	*Point = 1;
	E2Pwrite( 0x01, Point, 1, TCN75Ads );
}
*/
/*****************************************************************
 	Real Time Clock
*****************************************************************/
/*
void Clock(void)
{
	_BCD1INC((unsigned char*)&Clk.Sec[0]);
	if( Clk.Sec[0] >= 0x60 ){				// Second
		Clk.Sec[0] = 0;
		Flag.Clk |= F_Min;
		_BCD1INC((unsigned char*)&Clk.Min[0]);
		if( Clk.Min[0] >= 0x60 ){			// Minute
			Clk.Min[0] = 0;
			Flag.Clk |= F_Hour;
			_BCD1INC((unsigned char*)&Clk.Hour[0]);
			if( Clk.Hour[0] >= 0x24 ){		// Hour
				Clk.Hour[0] = 0;
  				Flag.Clk |= F_Day;
				Clk.Week[0]++;
				if( Clk.Week[0] > 6 ) Clk.Week[0] = 0;				// Week
				_BCD1INC((unsigned char*)&Clk.Day[0]);
				if( BCD_Byte(Clk.Day[0]) > ((( Clk.Mon[0]==2 ) && ( BCD_Byte(Clk.Year[0]) & 0x03 )==0 )? 29:MonTab[Clk.Mon[0]])){	// Day
					Clk.Day[0] = 1;
					_BCD1INC((unsigned char*)&Clk.Mon[0]);
					if( Clk.Mon[0] > 0x12 ){						// Month
						Clk.Mon[0] = 1;
						_BCD1INC((unsigned char*)&Clk.Year[0]);
						if( Clk.Year[0] > 0x99 ) Clk.Year[0] = 0;	// Year
  					}
  				}
  			}
  		}
  	}
//	if( Flag.Clk & F_Min ) Clk.Check = ChkNum( Clk.Min, 6 );
}
*/

void TimeDataTurn(unsigned char* Data)
{
	unsigned char buff;
	short i;

	for(i=0;i<3;i++)
	{
		buff = *(Data + i);
		*(Data + i) = *(Data + 6 - i);
		*(Data + 6 - i) = buff;
	}

}

void GetTime( void )
{
	unsigned char Buff[8];
	unsigned char* Point;
	short i=5;

	Point = Buff;
	
	while( i > 0 )
	{
//#if( RTCCHIP == RX8025 )
//		if( E2PRead( Point, 0x0, 0x07, RTCAds ) != 0 ) Flag.AlarmFlg[0] |= F_AlarmClock;	//时钟错
//		else Flag.AlarmFlg[0] &= ~F_AlarmClock;	
//#else
//	#if(RTCCHIP==DS3231)
//		if( E2PRead( Point, 0x0, 0x07, DS3231Ads ) != 0 ) Flag.AlarmFlg[0] |= F_AlarmClock;	//时钟错
//		else Flag.AlarmFlg[0] &= ~F_AlarmClock;	
//	#else
//	#endif
//	
//	#if(RTCCHIP==S35390A)               //S35390A
//		if( E2PRead( Point, TimeAddr, 0x07, S35390AAds ) != 0 ) Flag.AlarmFlg[0] |= F_AlarmClock;	//时钟错
//		else Flag.AlarmFlg[0] &= ~F_AlarmClock;
//	#else
//	#endif	
//	
//	#if(RTCCHIP==RN8213Z)



	if( fnSysClock_Read(Point) != 0 ) 
		Flag.AlarmFlg[0] &= ~F_AlarmClock;			
	else
		Flag.AlarmFlg[0] |= F_AlarmClock;	//时钟错		

/*
	if(( Flag.Power & F_PwrUp ) != 0 )
		{
		if( E2PRead( Point, 0x0, 0x07, RTCAds ) != 0 ) Flag.AlarmFlg[0] |= F_AlarmClock;	//时钟错
		else Flag.AlarmFlg[0] &= ~F_AlarmClock;	
		}
	else
		{
		if( fnSysClock_Read(Point) != 0 ) Flag.AlarmFlg[1] |= F_AlarmClock8213;	//时钟错
		else Flag.AlarmFlg[1] &= ~F_AlarmClock8213;	
		}
*/	
	
//	#else
//	#endif
		
//#endif

//#if(RTCCHIP==S35390A)               //S35390A
	
////	*(Point+0) = *(Point35390+6);
////	*(Point+1) = *(Point35390+5);
////	*(Point+2) = *(Point35390+4);
////	*(Point+3) = *(Point35390+3);
////	*(Point+4) = *(Point35390+2);
////	*(Point+5) = *(Point35390+1);
////	*(Point+6) = *(Point35390+0);
//	TimeDataTurn(Point);
//	*(Point+2) &=~ 0xC0;
//#else
//#endif

	if(( TimeValueCheck( Point ) == 0 )&&( DateValueCheck( Point+3 ) == 0 )) 
		{
//			_DINT();	
			__disable_irq();
			Clk.Sec[0] = *Point;	
			Clk.Min[0] = *(Point+1);	
			Clk.Hour[0] = *(Point+2);	
			Clk.Week[0] = *(Point+3);	
//			if( Clk.Week[0] >= 7 ) Clk.Week[0] = 0;
			Clk.Day[0] = *(Point+4);	
			Clk.Mon[0] = *(Point+5);	
			Clk.Year[0] = *(Point+6);		
//			_EINT();
			__enable_irq();
			Clk.Week[0] = WeekDay20( Clk.Day );			//V40
			break;
		}	
		i -= 1;
	}	
}

/*-----------------------------------------------
2000年~2099年星期算法
--------------------------------------------------------*/
unsigned char WeekDay20( unsigned char* Addr )				//V40
{
	unsigned char week, day,d,m,y; 
	
	d = BCD_Byte(*Addr);
	m = BCD_Byte(*(Addr+1));
	y = BCD_Byte(*(Addr+2));
	
	week = m - 1;
	day = WeekTab[week];			//月表   
	week = day >> 5;				//月星期数 
	day &= 0x1f;					//月天数 
	if ((m < 3) && (y & 0x03))
	{								//平年   
		if (m == 2) day--;			//平年月天数   
		week++;						//平年月表+1  
	}  
	y = y + (y >> 2);				//年+年/4 
	week = (week +  y + d + 2) % 7;	//(星期=年+年/4+月表+2日)%7 
	return week;					//返回星期
}

/*	
void GetTime(void)
{
	unsigned char Buff[12];
	unsigned char* Point;
	int i;

	Point = Buff;

	RAM_Fill( Point, 12);
	if(( TimeValueCheck( Clk.Sec ) == 1 )||( DateValueCheck( Clk.Day ) == 1 ))
	{
		_DINT();
		if((( Flag.Clk & F_Min ) == 0 )&&( Clk.Check != ChkNum( Clk.Min , 6 )))
		{
			E2P_RData( Point, ClkBuf1, 6 );
			for( i=1;i<7;i++ )
			{
				E2P_RData( Point+6, ClkBuf1 + i*7, 6 );
				if(( TimeValueCheck( Point+6 ) == 1 )||( DateValueCheck( Point+6+3 ) == 1 )) continue;				
				if( Data_Comp( Point+6, Point, 6 ) > 0 )
				RAM_Write( Point, Point+6, 6 );
				else break;
			}		
			RAM_Write( &Clk.Min[0], Point, 6 );
		}	
		_EINT();
	}	
}

void SetClkBak( void )
{
	int Temp;
	unsigned char Buff[4];
	unsigned char* Point;
	
	Point = Buff;
	
	RAM_Write( Point+1, Clk.Day, 3 );
	*Point = Clk.Week[0];
	if(( TimeValueCheck( Clk.Sec ) == 0 )&&( DateValueCheck( Point ) == 0 ))
	{
		Clk.Check = ChkNum( (unsigned char*)&Clk.Min[0] , 6 );
//		if((Flag.Power & F_PwrUp) != 0)
//		{
		Temp = (( BCD_Byte( Clk.Min[0] ) & 0x07 ) * 7 ) + ClkBuf1  ;
		E2P_WData( Temp, (unsigned char*)&Clk.Min[0], 6 );
//		}
	}	
}	

void SetClk( void )
{
	int i;
	
	Clk.Check = ChkNum( (unsigned char*)&Clk.Min[0] , 6 );
	
	for( i=0;i<8;i++ )
	{
		E2P_WData( ClkBuf1+i*7, (unsigned char*)&Clk.Min[0], 6 );	
	}	
}	
*/

short TimeValueCheck( unsigned char* Source )
{
	short i;
	
	for( i=0;i<3;i++ )
	{
		if( IsBCD( *(Source+i) ) != 0 ) return 1;
		if( *(Source+i) > TimeMaxTab[i] ) return 1;	
	}	 
	return 0;
}	

////int DateValueCheck( unsigned char* Source )
////{
////	int i;
////	
////	for( i=0;i<4;i++ )
////	{
////		if( IsBCD( *(Source+i) ) != 0 ) return 1;
////		if( *(Source+i) > DateMaxTab[i] ) return 1;	
////	}	 
////	if(( *(Source+1) == 0 )||(*(Source+2) == 0)) return 1;
////	return 0;
////}
	
short DateValueCheck( unsigned char* Source )
{
	short i;
	
	for( i=0;i<4;i++ )
	{
		if( IsBCD( *(Source+i) ) != 0 ) return 1;
		if( *(Source+i) > DateMaxTab[i] ) return 1;	
	}	 
	if(( *(Source+1) == 0 )||(*(Source+2) == 0)) return 1;
//	if( ((*(Source+3) & 0x03 )== 0)&&(*(Source+2) == 2)&&(*(Source+1) == 0x29)) return 0;	//闰年2月29日	//V40
	if( ((BCD_Byte(*(Source+3)) & 0x03 )== 0)&&(*(Source+2) == 2)&&(*(Source+1) == 0x29)) return 0;	//闰年2月29日	//V40
	if( BCD_Byte(*(Source+1)) > MonTab[BCD_Byte(*(Source+2))] ) return 1; //判大月小月						//V40
	return 0;
}	

/*
int TimeValueCheck( unsigned char* Source )
{
	int i;
	
	for( i=0;i<7;i++ )
	{
		if( *(Source+i) > TimeMaxTab[i] ) return 1;	
	}	 
	return 0;
}	

void ClkChk(void)
{
	unsigned char Buff[12];
	unsigned char* Point;
	int i;

	Point = Buff;

	//RAM_Fill( Point, 12, 0);
	RAM_Fill( Point, 12 );
	_DINT();
	if((( Flag.Clk & F_Min ) == 0 )&&( Clk.Check != ChkNum( Clk.Min , 6 ))) 		
	{
		E2P_RData( Point, ClkBuf1, 6 );
		for( i=1;i<4;i++ )
		{
			E2P_RData( Point+6, ClkBuf1 + i*7, 6 );
			if( Data_Comp( Point+6, Point, 6 ) > 0 )
				RAM_Write( Point, Point+6, 6 );
			else break;
		}		
		RAM_Write( &Clk.Min[0], Point, 6 );
		Clk.Check = ChkNum( (unsigned char*)&Clk.Min[0] , 6 );		
	}	
	_EINT();
}

void SetClkBak( void )
{
	int Temp;
	
	Clk.Check = ChkNum( (unsigned char*)&Clk.Min[0] , 6 );
	
	if((Flag.Power & F_PwrUp) != 0)
	{
		Temp = (( BCD_Byte( Clk.Min[0] ) & 0x03 ) * 7 ) + ClkBuf1  ;
		E2P_WData( Temp, (unsigned char*)&Clk.Min[0], 6 );
	}	
}	
*/
/*
unsigned long GetSec( unsigned char* Addr )
{
	return (unsigned long)BCD_Byte(*Addr) 
		+ (unsigned long)BCD_Byte(*(Addr+1))*60
		+ (unsigned long)BCD_Byte(*(Addr+2))*3600;
}
*/
/**********************************************************************/
// Change YYMMDD to Bill Month
/**********************************************************************/
/*
unsigned int GetBillMon( char* Addr )
{
   unsigned int Tmp;

   Tmp=BCD_Byte(*(Addr+1))+12*BCD_Byte(*(Addr+2));
   if( Para.ZeroDT[0]>0 && Para.ZeroDT[0]<=0x31 && *Addr>=Para.ZeroDT[0] ) Tmp++;   
   return Tmp;
}
*/
/**********************************************************************/
// Change YYMMDD to GmDay
/**********************************************************************/
/*
unsigned int GetGmDay( char* Addr )
{
   	unsigned int Day,Mon,Year;

	Mon = BCD_Byte(*(Addr+1));
	Year= BCD_Byte(*(Addr+2));
	Day = BCD_Byte(*Addr) + DayTab[Mon] + Year*365 + (Year>>2) + 1;
	if( (Year&0x03)==0 && Mon<=2 ) Day--;
   	return Day;
}
*/
/**********************************************************************
	Change YYMMDDhhmmss to GmSec
**********************************************************************/
/*
unsigned long GetGmSec( char* Addr )
{
	return (unsigned long)BCD_Byte(*Addr) 
		+ (unsigned long)BCD_Byte(*(Addr+1))*60
		+ (unsigned long)BCD_Byte(*(Addr+2))*60*60
		+ (unsigned long)GetGmDay(Addr+3)*60*60*24;
}
*/
/**********************************************************************
	Change YYMMDDhhmmss to GmMin
**********************************************************************/
/*
unsigned long GetGmMin( unsigned char* Addr )
{
	return (unsigned long)BCD_Byte(*Addr) 
		+ (unsigned long)BCD_Byte(*(Addr+1))*60
		+ (unsigned long)GetGmDay(Addr+2)*60*24;
}
*/
/**********************************************************************
	Get the Week of Today
**********************************************************************/
/*char GetWeek( void )
{
   return ( GetGmDay( Clk.Day ) + 5 ) % 7;
}

*/
//**********************************************************************
// Change GmMin to YYMMDDhhmm
//**********************************************************************
/*
void Min_Date( char* Sec, unsigned long Min )
{
	unsigned long Tmp;
	int Y1,Y2,i;
	
	*(Sec+1) = Min % 60;				// Minute
	Tmp = Min / 60;
	*(Sec+2) = Tmp % 24;				// Hour
	Tmp /= 24;
	
	Y1 = Tmp / (365*4+1);
	Y2 = Tmp % (365*4+1);
	if( Y2 > 366 ){
	 	*(Sec+5) = Y1*4 + (Y2-1)/365;	// Year
	 	Y2 = (Y2-1)%365;
	 }
	else *(Sec+5) = Y1*4;
	for(Y1=13;Y1>0;Y1--) 
		if((Y2-DayTab[Y1])>0) break;
//	*(Sec+4) = Y1-1;					// Month
//	*(Sec+3) = Y2 - 1 - DayTab[Y1];		// Day
	*(Sec+4) = Y1;					// Month
	*(Sec+3) = Y2 -1 - DayTab[Y1];		// Day
	for(i=1;i<6;i++)
	{	
		*(Sec+i)=Byte_BCD(*(Sec+i));
	}
	
}
*/

//****************************************************************
void RtcSub1Hour(unsigned char *Phour)
{
		unsigned char i,Buff[5],Temp;
		for(i=0;i<4;i++)
			{Buff[i]=*(Phour+i);}
		if(Buff[0])
			{_BCD1DEC(&Buff[0]);}	//hour
		else	
			{Buff[0]=0x23;	//hour
			if(	Buff[1]!=1)
				{_BCD1DEC(&Buff[1]);}//day
			else
				{if(Buff[2]==3)	//month
					{Temp=Buff[3];//year
					if(BCD_Byte(Temp)&03)
						{Buff[1]=0x28;}
					else
						{Buff[1]=0x29;}	
					}
				else
					{Temp=BCD_Byte(Buff[2]);
					Temp--;
					Buff[1]=BCDMonTab[Temp]; 	
					}	
				if(Buff[2]==1)	
					{Buff[2]=0x12;
					_BCD1DEC(&Buff[3]);	//year sub 1
					}
				else
					_BCD1DEC(&Buff[2]);	//month sub 1	
				}	
			}
		for(i=0;i<4;i++)
			{*(Phour+i)=Buff[i];}	
}

//------------------------------------------------
void RtcAdd1Hour(unsigned char *Phour)
{
	unsigned char i,Buff[5],Temp;
	for(i=0;i<4;i++)
		{Buff[i]=*(Phour+i);}		
	if(Buff[0]<0x23)
		{_BCD1INC(&Buff[0]);} //hour+1
	else
		{Buff[0]=0x00;	//hour
		switch(Buff[2]) //month	
			{case 2:
				if(BCD_Byte(Buff[3])&03)//年转化成HEX
					{Temp=0x28;}
				else
					{Temp=0x29;}
				break;						
			case 4:
			case 6:
			case 9:
			case 0x11:
				Temp=0x30;
				break;
			default:
				Temp=0x31;					
				break;
			}
		if(Buff[1]<Temp)
			{_BCD1INC(&Buff[1]);}//day+1	
		else
			{Buff[1]=0x1;	//day
			if(	Buff[2]<0x12)
				{_BCD1INC(&Buff[2]);}//month+1	
			else
				{Buff[2]=0x1;//month
				_BCD1INC(&Buff[3]);	//year+1
				}	
			}	
		}
	for(i=0;i<4;i++)
		{*(Phour+i)=Buff[i];}	
}
//------------------------------------------------
void RtcAdd15Min(unsigned char *Min)
{
	unsigned char i,Buff[6],Temp;
	for(i=0;i<5;i++)
	{
		Buff[i]=*(Min+i);
	}		
	if(Buff[0] < 0x45)
	{
		Buff[0] = BCD_Byte(Buff[0]) + 15;
		Buff[0] = Byte_BCD(Buff[0]);
	}else if(Buff[1]<0x23)
	{
		Buff[0] = BCD_Byte(Buff[0]) -45;
		Buff[0] = Byte_BCD(Buff[0]);
		_BCD1INC(&Buff[1]);
		} //hour+1
	else
	{
		Buff[1]=0x00;	//hour
		switch(Buff[3]) //month	
			{case 2:
				if(BCD_Byte(Buff[4])&03)//年转化成HEX
					{Temp=0x28;}
				else
					{Temp=0x29;}
				break;						
			case 4:
			case 6:
			case 9:
			case 0x11:
				Temp=0x30;
				break;
			default:
				Temp=0x31;					
				break;
			}
		if(Buff[2]<Temp)
			{_BCD1INC(&Buff[2]);}//day+1	
		else
			{Buff[2]=0x1;	//day
			if(	Buff[2]<0x12)
				{_BCD1INC(&Buff[2]);}//month+1	
			else
				{Buff[2]=0x1;//month
				_BCD1INC(&Buff[4]);	//year+1
				}	
			}	
		}
	for(i=0;i<5;i++)
		{*(Min+i)=Buff[i];}	
}
/**********************************************************************
	Get the Fee rate Number
**********************************************************************/
/*
#define  MaxHoli	100
#define  MaxSeas	8
#define  MaxSeg	12

char GetFeeNo( void )
{
	unsigned int	Now, Int;
   char 	i, TabNo=12;
   char 	Num;
   
   Num = BCD_Byte( (char)FeeGrp.HoliNum );
   if( Num > MaxHoli ) Num = MaxHoli;
   for( i=0; i<Num; i++ ) {
      if( FeeGrp.Holi[i][0]==(char)Clk.Day && FeeGrp.Holi[i][1]==(char)Clk.Mon ) {
         TabNo = FeeGrp.Holi[i][2];
         break;
      }
   }
	
	if( TabNo>=12 ){
	   Num = (char)FeeGrp.SeasNum;
	   if( Num > MaxSeas ) Num = MaxSeas;
      ((char*)&Now)[0] = (char)Clk.Day;
      ((char*)&Now)[1] = (char)Clk.Mon;
	   for( i=0; i<Num; i++ ) {
         ((char*)&Int)[0] = (char)FeeGrp.Seas[i][0];
         ((char*)&Int)[1] = (char)FeeGrp.Seas[i][1];
         if( Now<Int ) break;
		}	   	
		if( i==0 || i>=Num ) i = Num-1;
		else i = i-1;
		TabNo = FeeGrp.Seas[i][2];
	}
	if((TabNo<8) && (FeeGrp.WeekEnd & ByteBit[(char)Clk.Week])) TabNo = (char)FeeGrp.Week[TabNo];
	if( TabNo<8 ) {
		Num = BCD_Byte( (char)FeeGrp.SegNum[TabNo] );	      
		if( Num>MaxSeg ) Num = MaxSeg;
	   ((char*)&Now)[0]=(char)Clk.Min;
  		((char*)&Now)[1]=(char)Clk.Hour;
		for( i=0; i<Num; i++ ){
      	((char*)&Int)[0]=FeeGrp.Seg[TabNo][i][0];
  	   	((char*)&Int)[1]=FeeGrp.Seg[TabNo][i][1];
  	   	if( Now<Int ) break;
  		}
		if( i==0 || i>=Num ) i = Num-1;
		else i = i-1;
		return ( FeeGrp.Seg[TabNo][i][2] & 3 );
	}
	return ( (TabNo-8) & 3 );
}

*/


