//#include "msp430f6736.h"
#include "TypeMeter.h"
#include "TypeE2p.h"
#include "Measure.h"
//#include "In430.h"
#include "Mem.h"
#include "Type.h"
#include "Data.h"
#include "General.h" 
#include "RsComm.h"
#include "Port.h"
#include "Power.h"
#include "math.h"
#include "Time.h"
#include "Display.h"
#include <Drive_Lib.h>

//函数功能：时钟电池电压测量
//入口参数：无
//出口参数：无
void fnFront_ClockBatCalculate(void)
{
	u32 ClockBat;
	u8	i;

if(( Flag.Disk & F_Flash ) == 0) 
{
//	ResetLoRa(0);
/*
	for(i=0;i<150;i++)
	{
		if(MADC->AD_STAT&0x01)  break;
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}

	if(i != 150)
	{	
		ClockBat = MADC->AD_DATA;
		ClockBat = (ClockBat * 100)/269;	
		Word_BCD(Para.UCommBat, (unsigned short)ClockBat);
	}
*/
	for(i=0;i<255;i++)
	{
		if(!(MADC->AD_STAT&0x02))  break;
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
	MADC->AD_CTRL = 0x01;									// set ADCChannel 2  vbat  0.5倍增益
	MADC->AD_START = 0x01;									// star ADC
//	SystemDelay(1);
//	for(i=0;i<150;i++)
//	{
//		if(MADC->AD_STAT&0x01)  break;
//		__NOP();
//		__NOP();
//		__NOP();
//		__NOP();
//	}

}
else
{

	for(i=0;i<150;i++)
	{
		if(MADC->AD_STAT&0x01)  break;
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
	
	if(i != 150)
		{
		ClockBat = MADC->AD_DATA;
		ClockBat = (ClockBat * 508)/1024;
				
		if(ClockBat>300) 
			Flag.Power &=~F_BatteryPwrUp;		
		else 
			Flag.Power |= F_BatteryPwrUp;		
	
		Word_BCD(Para.UClockBat, (unsigned short)ClockBat);

	
		// 当前温度值
		ClockBat = RTC->TEMP;
		ClockBat &= 0x3ff;
		if(ClockBat&0x200) 
		{	
			ClockBat = 0x3ff - ClockBat;
			ClockBat = (ClockBat*10)/4;
			Word_BCD(Para.Temperature, (unsigned short)ClockBat);
			*(Para.Temperature+1) |= 0x80;
		}
		else
			{
			ClockBat = (ClockBat*10)/4;
			Word_BCD(Para.Temperature, (unsigned short)ClockBat);
			}

	}
//~~~~~~~~~~~~~计算时钟芯片电池电压
/*
	for(i=0;i<255;i++)
	{
		if(!(MADC->AD_STAT&0x02))  break;
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
//	MADC->AD_CTRL = 0x0C;									// set ADC VIN2  1 陪增益
	MADC->AD_CTRL = 0x04;									// set ADC VIN2  1 陪增益	
	MADC->AD_START = 0x01;									// star ADC
//	SystemDelay(1);
//	for(i=0;i<150;i++)
//	{
//		if(MADC->AD_STAT&0x01)  break;
//		__NOP();
//		__NOP();
//		__NOP();
//		__NOP();
//	}
*/


}

	
}



#if ( Threephase == YesCheck )
#if(MEASCHIP == ATT7053)
void ATT7053WtReg(  unsigned char Cmd, unsigned char* Data )
{
	unsigned char Checksum;
	short i,Delaysum;
	
//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();
	for(i=0;i<3;i++)
	{

		Comm.Buf1[4] = 0x6A;
//		PDIR_CSC |= P_CSC;
//		PDIR_CSB |= P_CSB;
		Comm.Buf1[0] = 0x6A;
		Comm.Buf1[1] = Cmd + 0x80;
		Comm.Buf1[4] += Cmd + 0x80;
		Comm.Buf1[2] = *Data;
		Comm.Buf1[4] += *Data;
		Comm.Buf1[3] = *(Data + 1);
		Comm.Buf1[4] += *(Data + 1);
		Comm.Buf1[4] = ~Comm.Buf1[4];
		Comm.State1 |= ATT7053Set;
		Comm.State1 &=~ (ATT7053CommOK + ATT7053Read);
		Delaysum = 30000;
		Comm.Ptr1 = 1;
		UCA1TXBUF = Comm.Buf1[0];		
		UCA1IE &=~ UCRXIE;
		UCA1IE |= UCTXIE;
		while((Comm.State1 & ATT7053CommOK) != ATT7053CommOK)
		{
			Delay(3);
			Delaysum--;
			if(Delaysum == 0)
				break;
		}
		if(Comm.Buf1[0] == 0x54)
//		{	
//			Delaysum = 30000;
			break;
//		}else Delaysum = 30000;
	}
	Comm.State1 &=~ ATT7053Read;
	
}
unsigned char ATT7053RdReg(  unsigned char Cmd, unsigned char* Data )
{
	unsigned char Checksum;
	short i,Delaysum;
	
//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();
	for(i=0;i<3;i++)
	{

		UCA1IE &=~ (UCRXIE + UCTXIE);
		Checksum = 0x6A;
//		PDIR_CSC |= P_CSC;
//		PDIR_CSB |= P_CSB;
		Comm.Buf1[0] = 0x6A;
		Comm.Buf1[1] = Cmd;
		Checksum += Cmd;
		Comm.State1 |= ATT7053Read;
		Comm.State1 &=~ (ATT7053CommOK + ATT7053Set);
		Delaysum = 30000;
		Comm.Ptr1 = 1;
		UCA1TXBUF = Comm.Buf1[0];		
		UCA1IE &=~ UCRXIE;
		UCA1IE |= UCTXIE;
		while((Comm.State1 & ATT7053CommOK) != ATT7053CommOK)
		{
			Delay(3);
			Delaysum--;
			if(Delaysum == 0)
			{
				RAM_Fill(Comm.Buf1, 3 );
				return 1;	
				break;
			}
		}
		Checksum += (Comm.Buf1[0] + Comm.Buf1[1] + Comm.Buf1[2]);
		Checksum = ~Checksum;
		if(Checksum == Comm.Buf1[3])
			break;
		else
			RAM_Fill(Comm.Buf1, 3 );	
	}
	*Data = Comm.Buf1[2];
	*(Data + 1)= Comm.Buf1[1];
	*(Data + 2)= Comm.Buf1[0];
	Comm.State1 &=~ ATT7053Read;
	return 0;
}
void ATT7053Int(void)
{
	unsigned char i,j,datbuff[5];
	unsigned char* Point;
	
	Point = datbuff;
//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();
	
//	PDIR_RST7053U |= P_RST7053U;
//	Delay(1000);
//	PDIR_RST7053U &=~ P_RST7053U;
//	Delay(1000);
	for(i=0;i<3;i++)
	{
		switch(i)
		{
			case 0:
				PDIR_CSA &=~ P_CSA;
				PDIR_CSC |= P_CSC;
				PDIR_CSB |= P_CSB;
				break;
			case 1:
				PDIR_CSA |= P_CSA;
				PDIR_CSC |= P_CSC;
				PDIR_CSB &=~ P_CSB;
				break;
			default:	
				PDIR_CSA |= P_CSA;
				PDIR_CSC &=~ P_CSC;
				PDIR_CSB |= P_CSB;
				break;	
		}
		Delay(1000);
//	//	WPCFG = 0xBC：表示写保护打开，只能操作40H到45H的校表参数寄存器，不可操作50H到71H的校表参数寄存器//
//	//	WPCFG = 0xA6：表示写保护打开，只能操作50H到71H的校表参数寄存器，不可操作40H到45H的校表参数寄存器。//
		datbuff[0]=0x00;
		datbuff[1]=0xBC;
		ATT7053WtReg(WPREG,Point);	//使能40-45写操作//
		
		datbuff[0]=0x00;
		datbuff[1]=0x02;
//		datbuff[2]=0x03;
		ATT7053WtReg(EMUIE,Point);	//电压过零中断//
		
		datbuff[0]=0x00;
		datbuff[1]=0x03;
//		datbuff[2]=0x03;
		ATT7053WtReg(ANAEN,Point);	//ADC开关寄存器//
		datbuff[0]=0x00;
		datbuff[1]=0xA6;
		ATT7053WtReg(WPREG,Point);	//使能50-71写操作//
//		ATT7053RdReg(WPREG,Point);	//使能50-71写操作//
//		readep(&rambuf[1],address,4,eplxjbcs);	//顺序要按长短排列//
		E2P_RAdj( datbuff, AGPBase + i*3, 2 );
//		datbuff[0]=0x13;
//		datbuff[1]=0x20;
		ATT7053WtReg(GP1,Point);	//eeprom 3字节，实际使用2字节//
//		ATT7053RdReg(GP1,Point);	//eeprom 3字节，实际使用2字节//
		ATT7053WtReg(GP2,Point);	//eeprom 3字节，实际使用2字节//
		
		//需要定死的寄存器//
		datbuff[0]=0;
		datbuff[1]=0;
		ATT7053WtReg(ADCCON,Point);	//电流1放大1倍，电压放大1倍,电流2放大1倍//
		
//		readep(&rambuf[1],EE_HFCONST,3,eplxjbcs);
//		rambuf[1]=rambuf[1]&0x07;
//		ramhfconst=(uint)rambuf[1]*256+rambuf[2];
//		rambuf[0]=0x00;
//		jchkprg(&rambuf[1]);
//		wr7053(rambuf,0x61+0X80,3);
//////////////////////////////////////////////////////////////////
			
			
//		readep(&rambuf[2],EE_APOSA,3,eplxjbcs);
//		rambuf[0]=0x00;
//		rambuf[1]=0x00;
//		jchkprg(&rambuf[1]);
//		wr7053(rambuf,0x65+0X80,3);//小电流补偿值//
			
			
			
//光电压无电流，读出电流1原始值0x0002bd,电流2原始值0x0001a8,、、//
//        	rambuf[0]=0x00;
//        	rambuf[1]=0x00;
//        	rambuf[2]=0x0e;
//		jchkprg(&rambuf[1]);
//		wr7053(rambuf,0x69+0X80,3);//电流1有效值偏移量//
//        	rambuf[0]=0x00;
//        	rambuf[1]=0x00;
//        	rambuf[2]=0x05;
//		jchkprg(&rambuf[1]);
//		wr7053(rambuf,0x6a+0X80,3);//电流2有效值偏移量//
			
			
		E2P_RAdj( datbuff, AGPhs + i*3, 2 );
		ATT7053WtReg(GPhs1,Point);
			
//        	readep(&rambuf[1],EE_PHSA_7053,3,eplxjbcs);
//		rambuf[0]=0;
//		jchkprg(&rambuf[1]);
//		wr7053(rambuf,0x6d+0X80,3);	//相位校准
			
		datbuff[0]=0x00;
		datbuff[1]=0x00;
		datbuff[2]=0x00;
		ATT7053WtReg(WPREG,Point);	//关闭使能
		
	}
	PDIR_CSA &=~ P_CSA;
	PDIR_CSC &=~ P_CSC;
	PDIR_CSB &=~ P_CSB;
	Flag.Power &=~ F_Reset7053;
	
}
void ReadATT7053_V(void)
{
	if(Read_ATTValue( Rms_U, Para.Ua ,0 ) != 0xFF)
	{	
		if(Para.Ua[1] < 0x05)
		{	
			Para.SFlag |= 0x01;
			Para.PWFlag &=~ ByteBit[0];
		}else	
			Para.SFlag &=~ 0x01;
	}
	if(Read_ATTValue( Rms_U, Para.Ub ,1 ) != 0xFF)
	{	
		if(Para.Ub[1] < 0x05)
		{	
			Para.SFlag |= 0x02;
			Para.PWFlag &=~ ByteBit[1];
		}else	
			Para.SFlag &=~ 0x02;
	}
	if(Read_ATTValue( Rms_U, Para.Uc ,2 ) != 0xFF)
	{	
		if(Para.Uc[1] < 0x05)
		{	
			Para.SFlag |= 0x04;
			Para.PWFlag &=~ ByteBit[2];
		}else	
			Para.SFlag &=~ 0x04;
	}
}
void ReadATT7053_P(void)
{
	unsigned char Databuff[4];
	short State;
	unsigned long int Power; 
	
	State = Read_ATTValue( PowerP1, Databuff ,0 );
	if(State != 0xFF)
	{
		if(State == 0)
		{	
			Para.IabcFlag |= ByteBit[0];
			Para.PWFlag |= ByteBit[0];
		}else{ 	
			Para.IabcFlag |= ByteBit[0];
			Para.PWFlag &=~ ByteBit[0];
		}
		Power = BCD4_Long(Databuff);
		Power *= 2;
		Measure7053.APowerPulP = Power;
	}else{
		Power = Measure7053.APowerPulP;
		
	}
	
	State = Read_ATTValue( PowerP1, Databuff ,1 );
	if(State != 0xFF)
	{
		if(State == 0)
		{	
			Para.IabcFlag |= ByteBit[1];
			Para.PWFlag |= ByteBit[1];
		}else{ 	
			Para.IabcFlag |= ByteBit[1];
			Para.PWFlag &=~ ByteBit[1];
		}
		Measure7053.BPowerPulP = BCD4_Long(Databuff);
		Measure7053.BPowerPulP *= 2;
		Power += Measure7053.BPowerPulP;
	}else{
		Power += Measure7053.BPowerPulP;
	}
//	Power += BCD4_Long(Databuff);
	State = Read_ATTValue( PowerP1, Databuff ,2 );
	if(State != 0xFF)
	{
		if(State == 0)
		{	
			Para.IabcFlag |= ByteBit[2];
			Para.PWFlag |= ByteBit[2];
		}else{ 	
			Para.IabcFlag |= ByteBit[2];
			Para.PWFlag &=~ ByteBit[2];
		}
		Measure7053.CPowerPulP = BCD4_Long(Databuff);
		Measure7053.CPowerPulP *=2;
		Power += Measure7053.CPowerPulP;
	}else{
		Power += Measure7053.CPowerPulP;
	}
//	Power += BCD4_Long(Databuff);
//	Power = 0x1000000;
	Measure7053.ABCPowerPulP = Power;
	if(Measure7053.ABCPowerPulP != 0)
		_NOP();
	Long_BCD4( Para.Pt, Power/93);
	
	
}

void Reset7053IE(void)
{
	unsigned char Data[3];
	
	PDIR_CSA &=~ P_CSA;
	PDIR_CSC &=~ P_CSC;
	PDIR_CSB &=~ P_CSB;
	SM.PhsCnt = 0x00;
	SM.PhsCnt1 = 0x00;
	SM.PhsCnt2 = 0x00;
	SM.PhsCnt3 = 0x00;
	P1IFG = 0x00;
	P1IE  &=~ (P_PLUSE1A + P_PLUSE1B +P_PLUSE1C);//0x00;
	Delay(1000);
	ATT7053RdReg(EMUIF,Data);	//
	
	P1IFG = 0x00;
	P1IE  = P_PLUSE1A + P_PLUSE1B +P_PLUSE1C;//0x00;
	
}
#elif( MEASCHIP == ADE7755 )
void AD7755Init( void )
{
	_DINT();
	E2P_RAdj( (unsigned char*)&SM.RYaBase, EYBase, 6 );
	E2P_RAdj( (unsigned char*)&SM.RUaBase, EUBase, 6 );
	_EINT();
	SM.RYBaseCheck = SM.RYaBase+SM.RYbBase+SM.RYcBase+0x5A5A;

	if((SM.RUaBase > 7000) || (SM.RUaBase < -7000)) SM.RUaBase = 0;
	if((SM.RUbBase > 7000) || (SM.RUbBase < -7000)) SM.RUbBase = 0;
	if((SM.RUcBase > 7000) || (SM.RUcBase < -7000)) SM.RUcBase = 0;		
	 
	SM.RUBaseCheck = SM.RUaBase+SM.RUbBase+SM.RUcBase+0x5A5A; 
////	P3DIR |= P_CTLYWG;
}
#endif

#if( MEASCHIP == RN8207 )
/*
8207的读操作，
*/
unsigned char Read8207(unsigned char Chipid,unsigned char Addr,unsigned char lg)
{
	short i;
	unsigned char CheckNum;
	
	for(i=0;i<3;i++)
	{
//		WDTCTL = WDT_ARST_1000;
		fnWDT_Restart();

		Comm8207.CommDly=RD8207DLY;//通信等待时间//
		Comm8207.SendBuf8207[0]=Chipid;//将要发送的数据//
		Comm8207.SendBuf8207[1]=Addr;
		Comm8207.NeedRecCnt=lg;//需要接收的数据长度//
		Comm8207.NeedSendCnt=1;//需要发送的数据长度(除去发的第一字节)//
		Comm8207.CommOk=0;//通信完成标志清0//
		Comm8207.Ptr8207=0;
//		UCA1IE &= ~UCRXIE; //关闭接收中断//

		UART3->CTRL &=0xfff3; 	//屏蔽接收中断,屏蔽接收错误中断
		UART3->STA = 0x3d;		//清接收中断标志及接收错误标志
		
//		UCA1TXBUF = Comm8207.SendBuf8207[0];//发送一字节//
		
		UART3->TXD= Comm8207.SendBuf8207[0];//发送一字节//
//		UCA1IE |= UCTXIE; //启动通信//

		UART3->CTRL |=0x02;		//允许发送中断
		UART3->STA = 0x02;		//清发送中断标志

		while(Comm8207.CommDly>0)//当等待时间没完时一直等待//
		{
			if(Comm8207.CommOk == READ8207OK)
			{
				RAM_Write(&(Comm8207.SendBuf8207[2]),Comm8207.RecBuf8207,lg);
				CheckNum = ChkNumAdd(Comm8207.SendBuf8207,lg+2);
				CheckNum = ~ CheckNum;
				if(Comm8207.RecBuf8207[lg] == CheckNum)
				{	
//					if((Comm8207.SendBuf8207[1] == ENERGYP2)&&(i != 0))
//						return 0;
//					else	
						return 1;
				}
//				else if(Comm8207.SendBuf8207[1] == ENERGYP)
//				{
//					switch(Comm8207.SendBuf8207[0])	//读错后还需要把本次的时间段记录下来（待改）
//					{
//						case CHIPIDA:
//							RAM_Write((unsigned char*)&SM.PowerA1SCnt1[0],(unsigned char*)&SM.PowerA1SCnt1[1],6);
//							break;
//						case CHIPIDB:
//							RAM_Write((unsigned char*)&SM.PowerB1SCnt1[0],(unsigned char*)&SM.PowerB1SCnt1[1],6);
//							break;
//						case CHIPIDC:
//							RAM_Write((unsigned char*)&SM.PowerC1SCnt1[0],(unsigned char*)&SM.PowerC1SCnt1[1],6);
//							break;		
//						default: break;
//					}
//				}	
			}

			if( SM.PowerUpTime < PWUPTIME )
				break;
			
//	                WDTCTL = WDT_ARST_1000;
			fnWDT_Restart();
		}
	}		
	return 0;
}	
/*
	8207的写操作
*/
unsigned char Write8207(unsigned char *Source,unsigned char Chipid,unsigned char Addr,unsigned char lg)
{
//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();
	Comm8207.CommDly=RD8207DLY;//通信等待时间//
	Comm8207.SendBuf8207[0]=Chipid;//将要发送的数据//
	Comm8207.SendBuf8207[1]=Addr;
	RAM_Write(&(Comm8207.SendBuf8207[2]),Source,lg);
	Comm8207.SendBuf8207[lg+2]=ChkNumAdd(Comm8207.SendBuf8207,lg+2);//计算和//
	Comm8207.SendBuf8207[lg+2]=~Comm8207.SendBuf8207[lg+2];//校验和取反//
	Comm8207.NeedRecCnt=0;//需要接收的数据长度//
	Comm8207.NeedSendCnt=lg+2;//需要发送的数据长度(除去发的第一字节)//
	Comm8207.CommOk=0;//通信完成标志清0//
	Comm8207.Ptr8207=0;
//   IE &= ~UCRXIE; //关闭接收中断//

	UART3->CTRL &=0xfff3; 	//屏蔽接收中断,屏蔽接收错误中断
	UART3->STA = 0x3d;		//清接收中断标志及接收错误标志
	
//CA1TXBUF = Comm8207.SendBuf8207[0];//发送一字节//
	UART3->TXD= Comm8207.SendBuf8207[0];//发送一字节//
	
//CA1IE |= UCTXIE; //启动通信//

	UART3->CTRL |=0x02;		//允许发送中断
	UART3->STA = 0x02;		//清发送中断标志
		
	while(Comm8207.CommDly>0)//当等待时间没完时一直等待//
	{
		if(Comm8207.CommOk==WRITE8207OK)
		{return 1;}
		
		if( SM.PowerUpTime < PWUPTIME )
			break;		
  //              WDTCTL = WDT_ARST_1000;
		  fnWDT_Restart();
	}		
	return 0;
}

/*
//读ABC的电流有效值//
void ReadABCIARMS(void)
{
	if(Measure8207.AStartM==1)
					{
						ReadAIARMS();
					}else	Flag.CurrStar|=0x01;
#if ( PhaseType == Phase3 )
					if(Measure8207.BStartM==1)
					{
						ReadBIARMS();
					}else	Flag.CurrStar|=0x02;	
					if(Measure8207.CStartM==1)
					{
						ReadCIARMS();
					}else	Flag.CurrStar|=0x04;
#endif	
}

//读A的电流有效值//
unsigned char ReadAIARMS(void)
{
	unsigned long IData;	       
	if(Read8207(CHIPIDA,IARMS,3)==0x00) 
	{	
		Flag.CurrStar|=0x01;
		return 0;
	}
	IData=((unsigned long)Comm8207.RecBuf8207[0]*256+Comm8207.RecBuf8207[1])*256+Comm8207.RecBuf8207[2];
	if(IData<ISTARTDATA)	//判断电流是否小于启动电流//
	{Flag.CurrStar|=0x01;}
	else
	{Flag.CurrStar&=0xfe;}	
	RAM_Write(SM.Testram11,&Comm8207.RecBuf8207[0],3);
    return 1;

}		
//读B的电流有效值//
unsigned char ReadBIARMS(void)
{
	unsigned long IData;	       
	if(Read8207(CHIPIDB,IARMS,3)==0x00) 
	{	
		Flag.CurrStar|=0x02;
		return 0;
	}
	IData=((unsigned long)Comm8207.RecBuf8207[0]*256+Comm8207.RecBuf8207[1])*256+Comm8207.RecBuf8207[2];
	if(IData<ISTARTDATA)	//判断电流是否小于启动电流//
	{Flag.CurrStar|=0x02;}
	else
	{Flag.CurrStar&=0xfd;}	
	
	RAM_Write(SM.Testram,&Comm8207.RecBuf8207[0],3);
        return 1;

}		
//读C的电流有效值//
unsigned char ReadCIARMS(void)
{
	unsigned long IData;
	if(Read8207(CHIPIDC,IARMS,3)==0x00) 
	{	
		Flag.CurrStar|=0x04;
		return 0;
	}
	IData=((unsigned long)Comm8207.RecBuf8207[0]*256+Comm8207.RecBuf8207[1])*256+Comm8207.RecBuf8207[2];
	if(IData<ISTARTDATA)	//判断电流是否小于启动电流//
	{Flag.CurrStar|=0x04;}
	else
	{Flag.CurrStar&=0xfc;}	
	RAM_Write(SM.Testram,&Comm8207.RecBuf8207[0],3);
        return 1;

}		
*/

void ReadABCIARMS(void)
{
//	unsigned char Power;

	if((Measure8207.AStartM==1) && ((Flag.VolFlg & F_PhAFail) != F_PhAFail))
	{	
		Read_ATTValue( IARMS3, Para.Ia,CHIPIDA );
//		Power = BCD4_Long( Para.Pa);
//		if( Power < 2 )
//		{
//			RAM_Fill( Para.Ia, 4);	
//		}
	}
	else
	{
		RAM_Fill( Para.Ia, 4);		
	}
	
	if((Measure8207.BStartM==1) && ((Flag.VolFlg & F_PhBFail) != F_PhBFail))
	{
		Read_ATTValue( IARMS3, Para.Ib,CHIPIDB );
//		Power = BCD4_Long( Para.Pb);
//		if( Power < 2 )
//		{
//			RAM_Fill( Para.Ib, 4);	
//		}		
	}
	else
	{
		RAM_Fill( Para.Ib, 4);	
	}
	
	if((Measure8207.CStartM==1) && ((Flag.VolFlg & F_PhCFail) != F_PhCFail))
	{	
		Read_ATTValue( IARMS3, Para.Ic,CHIPIDC );
//		Power = BCD4_Long( Para.Pc);
//		if( Power < 2 )
//		{
//			RAM_Fill( Para.Ic, 4);	
//		}		
	}
	else
	{
		RAM_Fill( Para.Ic, 4);
	}		
}

void ReadMeasVolt(void)
{	unsigned char Rambuf1[5];
	unsigned long Value;
	unsigned short ZXCNTA,ZXCNTB,ZXCNTC;
	
	if((Measure8207.AStartM==1) && ((Flag.VolFlg & F_PhAFail) != F_PhAFail))
	{
		Read_ATTValue( URMS3, Para.Ua,CHIPIDA );
	}
	else
	{
		RAM_Fill( Para.Ua, 4);
	}
	Value = BCD4_Long(Para.Ua);
	if(Value < 16100)
	{
		Para.SFlag |= 0x01;
		Para.PWFlag &=~ ByteBit[0];
	}
	else
	{
		Para.SFlag &=~ 0x01;
		if((Para.SFlag & 0x08)==0x08)
			{		
			if(Read8207(CHIPIDA,ZXCNT3,2)==1) 	
			RAM_WriteInter((unsigned char*)&ZXCNTA, (unsigned char*)&Comm8207.RecBuf8207[0], 2);
			}
	}
	if((Measure8207.BStartM==1) && ((Flag.VolFlg & F_PhBFail) != F_PhBFail))
	{
		Read_ATTValue( URMS3, Para.Ub,CHIPIDB );
	}
	else
	{
		RAM_Fill( Para.Ub, 4);
	}	
	Value = BCD4_Long(Para.Ub);
	if(Value < 16100)
	{
		Para.SFlag |= 0x02;
		Para.PWFlag &=~ ByteBit[1];
	}
	else
	{
		Para.SFlag &=~ 0x02;
		if((Para.SFlag & 0x08)==0x08)
			{			
			if(Read8207(CHIPIDB,ZXCNT3,2)==1) 	
			RAM_WriteInter((unsigned char*)&ZXCNTB, (unsigned char*)&Comm8207.RecBuf8207[0], 2);
			}
	}
	if((Measure8207.CStartM==1) && ((Flag.VolFlg & F_PhCFail) != F_PhCFail))
	{	
		Read_ATTValue( URMS3, Para.Uc,CHIPIDC );
	}
	else
	{
		RAM_Fill( Para.Uc, 4);
	}	
	Value = BCD4_Long(Para.Uc);
	if(Value < 16100)
	{
		Para.SFlag |= 0x04;
		Para.PWFlag &=~ ByteBit[2];
	}
	else
	{
		Para.SFlag &=~ 0x04;	
		if((Para.SFlag & 0x08)==0x08)
			{	
			if(Read8207(CHIPIDC,ZXCNT3,2)==1) 	
			RAM_WriteInter((unsigned char*)&ZXCNTC, (unsigned char*)&Comm8207.RecBuf8207[0], 2);		
			}
	}

	if((Para.SFlag & 0x07)==0)
	{
	
	if((Para.SFlag & 0x08)==0x08)		
	{
	
	if(((ZXCNTA<ZXCNTB)&&(ZXCNTA<ZXCNTC)&&(ZXCNTB<ZXCNTC))||((ZXCNTB<ZXCNTC)&&(ZXCNTB<ZXCNTA)&&(ZXCNTC<ZXCNTA))
		||((ZXCNTC<ZXCNTA)&&(ZXCNTC<ZXCNTB)&&(ZXCNTA<ZXCNTB)))
		{
	        Flag.AlarmFlg[0] &=~ F_AlarmPhs;
		}
	else
		{
	      	Flag.AlarmFlg[1] |= F_EventPhs;	
//		if(SM.L1L2L3MODE != 1)	
	        Flag.AlarmFlg[0] |= F_AlarmPhs;
		}
	
	}
		
	}
	else
	{
	 Flag.AlarmFlg[0] &=~ F_AlarmPhs;	
	}

	
	if((Para.SFlag & 0x07)==0)
	{
	Rambuf1[0]=0xe5;
	Write8207(Rambuf1,CHIPIDABC,0xea,1);	//0xea,0xe5,使能写操作//
	
	Rambuf1[0]=0x7c;
	Write8207(Rambuf1,CHIPIDABC,0xea,1);	//0xea,0x7c,广播命令启动过零计数
	
	Rambuf1[0]=0xdc;
	Write8207(Rambuf1,CHIPIDABC,0xea,1);	//0xea,0xdc,关闭写操作//
	
	Para.SFlag |= 0x08;
	}
	else
		{
		Para.SFlag &= ~0x08;		
		}

	
}

	
#if ( WGMeasure== YesCheck ) 


//读A相电能// 无功
unsigned char ReadAPowern(void)
{
//	unsigned int Dcnt1s;
  	unsigned short AdjData;
    	unsigned long long APower;
 	unsigned long long APowerPulP = 0;
// 	unsigned long PhAPulse;
// 	unsigned char PhAEMUStatus;	//判断起动用

//   	unsigned long long APowerPulPFirst=0,APowerPulPNow = 0;
//	unsigned char GetPowerNo;
//	unsigned char* PointP;
//    	unsigned char* PointPFirst;

 	APower = 0;
 	APowerPulP = 0;
// 	PhAPulse = 0;
// 	PhAEMUStatus = 0;

//   	PointP = (unsigned char*)&APowerPulP; 
//   	PointPFirst = (unsigned char*)&APowerPulPFirst;  	
//	RAM_Fill(Comm8207.RecBuf8207, 4 );

//	if(Read8207(CHIPIDA,EMUSTATUS3,3)==0x00)	return 0;
//	RAM_WriteInter((unsigned char*)&APower,(unsigned char*)&Comm8207.RecBuf8207[0],3);
//	if(APower&0x100000) 
//	{Measure8207.APowerPulPn = 0;
//	return 0;
//	}
		

	if(Read8207(CHIPIDA,POWERQ3,4)==0x00)
	{

//		return 0;
		if(Read8207(CHIPIDA,POWERQ3,4)==0x00)
		{

			return 0;
		}	
		else
		{
			if((Comm8207.RecBuf8207[0]&0x80)==0)
			{	
				Measure8207.FlagDireABCn &=~ F_ADire;//正向
	//			Para.PWFlag &=~ ByteBit[0];		
			}
			else
			{	
				Measure8207.FlagDireABCn |= F_ADire;	//反向//
	//			Para.PWFlag |= ByteBit[0];
				Comm8207.RecBuf8207[0] ^= 0xff;
				Comm8207.RecBuf8207[1] ^= 0xff;
				Comm8207.RecBuf8207[2] ^= 0xff;
				Comm8207.RecBuf8207[3] ^= 0xff;	
			}
			
			RAM_WriteInter((unsigned char*)&APower,(unsigned char*)&Comm8207.RecBuf8207[0],4);
		}
	}	
	else
	{
		if((Comm8207.RecBuf8207[0]&0x80)==0)
		{	
			Measure8207.FlagDireABCn &=~ F_ADire;//正向
//			Para.PWFlag &=~ ByteBit[0];		
		}
		else
		{	
			Measure8207.FlagDireABCn |= F_ADire;	//反向//
//			Para.PWFlag |= ByteBit[0];
			Comm8207.RecBuf8207[0] ^= 0xff;
			Comm8207.RecBuf8207[1] ^= 0xff;
			Comm8207.RecBuf8207[2] ^= 0xff;
			Comm8207.RecBuf8207[3] ^= 0xff;	
		}
		
		RAM_WriteInter((unsigned char*)&APower,(unsigned char*)&Comm8207.RecBuf8207[0],4);
	}		


//	if((((Measure8207.PhAPower*10)/APower)<13)||(((APower*10)/Measure8207.PhAPower)<13))	//两次读的功率之差小于13%累加
	if((((Measure8207.PhAPower*10)/APower)>13)||(((APower*10)/Measure8207.PhAPower)>13))	//两次读的功率之差小于13%累加	
	{
//		Measure8207.PhAPower += APower;
		Measure8207.PhARPWRCnt++;	//A相读能量次数	
		if( Measure8207.PhARPWRCnt > 1 )
		{
//			Measure8207.PhAPower /= Measure8207.PhARPWRCnt;
//			APower = Measure8207.PhAPower;
//			Measure8207.PhAPower = 0;
			Measure8207.PhARPWRCnt = 0;
		}	
	  	else
	  	{
	  		return 0;
	  	}						    		
	}
	else
	{
//			Measure8207.PhAPower = 0;
			Measure8207.PhARPWRCnt = 0;
	}


	Measure8207.PhAPower = APower;

  	AdjData=(unsigned short)Measure8207.AAdjust[1]*256+Measure8207.AAdjust[0];
//	APowerPulP = (unsigned long long)((APowerPulP*AdjData*PDLY400 )/Dcnt1s);
	APower = (unsigned long long)APower*AdjData/10370;// /10000;
	

//	if((APower>860000)&&(APowerPulP == 0))		//大电流切换到小电流过程中避免发脉冲
//	{
//		APower = 0;				
//	}	
	
	APowerPulP = APower;

	if(APowerPulP < 55000)
	{		
		Measure8207.FlagDireABCn&=~F_ADire;//正向
//		Para.PWFlag &=~ ByteBit[0];	
		APowerPulP = 0;
	}
	
	if((Measure8207.AnPowerPulPBak!=0)&&(APowerPulP==0))//为了虑除偶尔读成0//
	{
		Measure8207.AnPowerPulPBak = (unsigned long)APowerPulP;
		return 0; 
	}
	if((Measure8207.AnPowerPulPBak == 0)&&(APowerPulP!=0))//为了虑除偶尔读成0//
	{
		Measure8207.AnPowerPulPBak = (unsigned long)APowerPulP;
		return 0; 
	}
	Measure8207.AnPowerPulPBak = (unsigned long)APowerPulP;
	
    	Measure8207.APowerPulPn = (unsigned long)APowerPulP;

//	Long_BCD4(Para.Qa,(unsigned long)Measure8207.APowerPulPn/23930);	
	Long_BCD4(Para.Qa,(unsigned long)Measure8207.APowerPulPn/5590);
	return 1;
}
//读B相电能// 无功
unsigned char ReadBPowern(void)
{
//	unsigned int Dcnt1s;
  	unsigned short AdjData;
    	unsigned long long APower;
 	unsigned long long APowerPulP = 0;
// 	unsigned long PhAPulse;
// 	unsigned char PhAEMUStatus;	//判断起动用

//   	unsigned long long APowerPulPFirst=0,APowerPulPNow = 0;
//	unsigned char GetPowerNo;
//	unsigned char* PointP;
//    	unsigned char* PointPFirst;

 	APower = 0;
 	APowerPulP = 0;
// 	PhAPulse = 0;
// 	PhAEMUStatus = 0;

//   	PointP = (unsigned char*)&APowerPulP; 
//   	PointPFirst = (unsigned char*)&APowerPulPFirst;  	
//	RAM_Fill(Comm8207.RecBuf8207, 4 );

//	if(Read8207(CHIPIDB,EMUSTATUS3,3)==0x00)	return 0;
//	RAM_WriteInter((unsigned char*)&APower,(unsigned char*)&Comm8207.RecBuf8207[0],3);
//	if(APower&0x100000) 
//	{Measure8207.BPowerPulPn = 0;
//	return 0;
//	}

	if(Read8207(CHIPIDB,POWERQ3,4)==0x00)
	{
//		Measure8207.FlagDireABC&=~F_ADire;//读错定为正向
//		Measure8207.FlagDireABC |= F_ADire;//读错定为正向	//TEST
//		return 0;
		if(Read8207(CHIPIDB,POWERQ3,4)==0x00)
		{
			return 0;
		}	
		else
		{
			if((Comm8207.RecBuf8207[0]&0x80)==0)
			{	
				Measure8207.FlagDireABCn &=~ F_BDire;//正向
	//			Para.PWFlag &=~ ByteBit[0];		
			}
			else
			{	
				Measure8207.FlagDireABCn |= F_BDire;	//反向//
	//			Para.PWFlag |= ByteBit[0];
				Comm8207.RecBuf8207[0] ^= 0xff;
				Comm8207.RecBuf8207[1] ^= 0xff;
				Comm8207.RecBuf8207[2] ^= 0xff;
				Comm8207.RecBuf8207[3] ^= 0xff;	
			}
			
			RAM_WriteInter((unsigned char*)&APower,(unsigned char*)&Comm8207.RecBuf8207[0],4);
		}
	}	
	else
	{
		if((Comm8207.RecBuf8207[0]&0x80)==0)
		{	
			Measure8207.FlagDireABCn &=~ F_BDire;//正向
//			Para.PWFlag &=~ ByteBit[0];		
		}
		else
		{	
			Measure8207.FlagDireABCn |= F_BDire;	//反向//
//			Para.PWFlag |= ByteBit[0];
			Comm8207.RecBuf8207[0] ^= 0xff;
			Comm8207.RecBuf8207[1] ^= 0xff;
			Comm8207.RecBuf8207[2] ^= 0xff;
			Comm8207.RecBuf8207[3] ^= 0xff;	
		}
		
		RAM_WriteInter((unsigned char*)&APower,(unsigned char*)&Comm8207.RecBuf8207[0],4);
	}		


//	if((((Measure8207.PhBPower*10)/APower)<13)||(((APower*10)/Measure8207.PhBPower)<13))	//两次读的功率之差小于13%累加
	if((((Measure8207.PhBPower*10)/APower)>13)||(((APower*10)/Measure8207.PhBPower)>13))	//两次读的功率之差小于13%累加	
	{
//		Measure8207.PhBPower += APower;
		Measure8207.PhBRPWRCnt++;	//A相读能量次数	
		if( Measure8207.PhBRPWRCnt > 1 )
		{
//			Measure8207.PhBPower /= Measure8207.PhBRPWRCnt;
//			APower = Measure8207.PhBPower;
//			Measure8207.PhBPower = 0;
			Measure8207.PhBRPWRCnt = 0;
		}	
	  	else
	  	{
	  		return 0;
	  	}						    		
	}
	else
	{
//			Measure8207.PhBPower = 0;
			Measure8207.PhBRPWRCnt = 0;
	}

	Measure8207.PhBPower = APower;

  	AdjData=(unsigned short)Measure8207.BAdjust[1]*256+Measure8207.BAdjust[0];
//	APowerPulP = (unsigned long long)((APowerPulP*AdjData*PDLY400 )/Dcnt1s);
	APower = (unsigned long long)APower*AdjData/10370;// /10000;
	

//	if((APower>860000)&&(APowerPulP == 0))		//大电流切换到小电流过程中避免发脉冲
//	{
//		APower = 0;				
//	}	
	
	APowerPulP = APower;

	if(APowerPulP < 55000)
	{		
		Measure8207.FlagDireABCn&=~F_BDire;//正向
//		Para.PWFlag &=~ ByteBit[0];	
		APowerPulP = 0;
	}
	
	if((Measure8207.BnPowerPulPBak!=0)&&(APowerPulP==0))//为了虑除偶尔读成0//
	{
		Measure8207.BnPowerPulPBak = (unsigned long)APowerPulP;
		return 0; 
	}
	if((Measure8207.BnPowerPulPBak == 0)&&(APowerPulP!=0))//为了虑除偶尔读成0//
	{
		Measure8207.BnPowerPulPBak = (unsigned long)APowerPulP;
		return 0; 
	}
	Measure8207.BnPowerPulPBak = (unsigned long)APowerPulP;

    	Measure8207.BPowerPulPn = (unsigned long)APowerPulP;

//	Long_BCD4(Para.Qa,(unsigned long)Measure8207.APowerPulPn/23930);
	Long_BCD4(Para.Qb,(unsigned long)Measure8207.APowerPulPn/5590);	
	return 1;
}
//读C相电能// 无功
unsigned char ReadCPowern(void)
{
//	unsigned int Dcnt1s;
  	unsigned short AdjData;
    	unsigned long long APower;
 	unsigned long long APowerPulP = 0;
// 	unsigned long PhAPulse;
// 	unsigned char PhAEMUStatus;	//判断起动用

//   	unsigned long long APowerPulPFirst=0,APowerPulPNow = 0;
//	unsigned char GetPowerNo;
//	unsigned char* PointP;
//    	unsigned char* PointPFirst;

 	APower = 0;
 	APowerPulP = 0;
// 	PhAPulse = 0;
// 	PhAEMUStatus = 0;

//   	PointP = (unsigned char*)&APowerPulP; 
//   	PointPFirst = (unsigned char*)&APowerPulPFirst;  	
//	RAM_Fill(Comm8207.RecBuf8207, 4 );

//	if(Read8207(CHIPIDC,EMUSTATUS3,3)==0x00)	return 0;
//	RAM_WriteInter((unsigned char*)&APower,(unsigned char*)&Comm8207.RecBuf8207[0],3);
//	if(APower&0x100000) 
//	{Measure8207.CPowerPulPn = 0;
//	return 0;
//	}

	if(Read8207(CHIPIDC,POWERQ3,4)==0x00)
	{
//		Measure8207.FlagDireABC&=~F_ADire;//读错定为正向
//		Measure8207.FlagDireABC |= F_ADire;//读错定为正向	//TEST
//		return 0;
		if(Read8207(CHIPIDC,POWERQ3,4)==0x00)
		{

			return 0;
		}	
		else
		{
			if((Comm8207.RecBuf8207[0]&0x80)==0)
			{	
				Measure8207.FlagDireABCn &=~ F_CDire;//正向
	//			Para.PWFlag &=~ ByteBit[0];		
			}
			else
			{	
				Measure8207.FlagDireABCn |= F_CDire;	//反向//
	//			Para.PWFlag |= ByteBit[0];
				Comm8207.RecBuf8207[0] ^= 0xff;
				Comm8207.RecBuf8207[1] ^= 0xff;
				Comm8207.RecBuf8207[2] ^= 0xff;
				Comm8207.RecBuf8207[3] ^= 0xff;	
			}
			
			RAM_WriteInter((unsigned char*)&APower,(unsigned char*)&Comm8207.RecBuf8207[0],4);
		}		
	}	
	else
	{
		if((Comm8207.RecBuf8207[0]&0x80)==0)
		{	
			Measure8207.FlagDireABCn &=~ F_CDire;//正向
//			Para.PWFlag &=~ ByteBit[0];		
		}
		else
		{	
			Measure8207.FlagDireABCn |= F_CDire;	//反向//
//			Para.PWFlag |= ByteBit[0];
			Comm8207.RecBuf8207[0] ^= 0xff;
			Comm8207.RecBuf8207[1] ^= 0xff;
			Comm8207.RecBuf8207[2] ^= 0xff;
			Comm8207.RecBuf8207[3] ^= 0xff;	
		}
		
		RAM_WriteInter((unsigned char*)&APower,(unsigned char*)&Comm8207.RecBuf8207[0],4);
	}		

//	if((((Measure8207.PhCPower*10)/APower)<13)||(((APower*10)/Measure8207.PhCPower)<13))	//两次读的功率之差小于13%累加
	if((((Measure8207.PhCPower*10)/APower)>13)||(((APower*10)/Measure8207.PhCPower)>13))	//两次读的功率之差小于13%累加	
	{
//		Measure8207.PhCPower += APower;
		Measure8207.PhCRPWRCnt++;	//A相读能量次数	
		if( Measure8207.PhCRPWRCnt > 1 )
		{
//			Measure8207.PhCPower /= Measure8207.PhCRPWRCnt;
//			APower = Measure8207.PhCPower;
//			Measure8207.PhCPower = 0;
			Measure8207.PhCRPWRCnt = 0;
		}	
	  	else
	  	{
	  		return 0;
	  	}						    		
	}
	else
	{
//			Measure8207.PhCPower = 0;
			Measure8207.PhCRPWRCnt = 0;
	}

	Measure8207.PhCPower = APower;

  	AdjData=(unsigned short)Measure8207.CAdjust[1]*256+Measure8207.CAdjust[0];
//	APowerPulP = (unsigned long long)((APowerPulP*AdjData*PDLY400 )/Dcnt1s);
	APower = (unsigned long long)APower*AdjData/10370;// /10000;
	

//	if((APower>860000)&&(APowerPulP == 0))		//大电流切换到小电流过程中避免发脉冲
//	{
//		APower = 0;				
//	}	
	
	APowerPulP = APower;

	if(APowerPulP < 55000)
	{		
		Measure8207.FlagDireABCn&=~F_CDire;//正向
//		Para.PWFlag &=~ ByteBit[0];	
		APowerPulP = 0;
	}
	
	if((Measure8207.CnPowerPulPBak!=0)&&(APowerPulP==0))//为了虑除偶尔读成0//
	{
		Measure8207.CnPowerPulPBak = (unsigned long)APowerPulP;
		return 0; 
	}
	if((Measure8207.CnPowerPulPBak == 0)&&(APowerPulP!=0))//为了虑除偶尔读成0//
	{
		Measure8207.CnPowerPulPBak = (unsigned long)APowerPulP;
		return 0; 
	}
	Measure8207.CnPowerPulPBak = (unsigned long)APowerPulP;

    	Measure8207.CPowerPulPn = (unsigned long)APowerPulP;

//	Long_BCD4(Para.Qa,(unsigned long)Measure8207.APowerPulPn/23930);
	Long_BCD4(Para.Qc,(unsigned long)Measure8207.APowerPulPn/5590);	
	return 1;
}

//计算ABC三相的合相用来发脉冲的无功功率//
void ReadABCPowern(void)
{
	signed long ABCPowerSum;
	//unsigned char *ppp;
	if((Measure8207.AStartM==1) && ((Flag.VolFlg & F_PhAFail) != F_PhAFail))
	{
		ReadAPowern();
	}else{
		Measure8207.APowerPulPn = 0;	
		Measure8207.AStartM = 0;
		RAM_Fill( Para.Qa, 4 );
	}
	
#if ( PhaseType == Phase3 )
	if((Measure8207.BStartM==1) && ((Flag.VolFlg & F_PhBFail) != F_PhBFail))
	{
		ReadBPowern();
	}else{
		Measure8207.BPowerPulPn = 0;	
		Measure8207.BStartM = 0;
		RAM_Fill( Para.Qb, 4 );
	}
	if((Measure8207.CStartM==1) && ((Flag.VolFlg & F_PhCFail) != F_PhCFail))
	{
		ReadCPowern();
	}else{
		Measure8207.CPowerPulPn = 0;
		Measure8207.CStartM = 0;
		RAM_Fill( Para.Qc, 4 );
	}
#endif

	if(((Measure8207.FlagDireABCn&F_ADire)!=0) && (Measure8207.ModePN != 4))
	{
		if(Measure8207.ModePN != 1)
			ABCPowerSum=0-Measure8207.APowerPulPn/10;	
		else
			ABCPowerSum = 0;	
	}	
	else
	{
		if(Measure8207.ModePN != 3)
			ABCPowerSum=Measure8207.APowerPulPn/10;
	}
			
#if ( PhaseType == Phase3 )							
	if(((Measure8207.FlagDireABCn&F_BDire)!=0) && (Measure8207.ModePN != 4))
	{
		if(Measure8207.ModePN != 1)
			ABCPowerSum=ABCPowerSum-Measure8207.BPowerPulPn/10;
	}	
	else
	{
		if(Measure8207.ModePN != 3)
		ABCPowerSum=ABCPowerSum+Measure8207.BPowerPulPn/10;
	}
	
	if(((Measure8207.FlagDireABCn&F_CDire)!=0) && (Measure8207.ModePN != 4))
	{
		if(Measure8207.ModePN != 1)	
			ABCPowerSum=ABCPowerSum-Measure8207.CPowerPulPn/10;
	}	
	else
	{
		if(Measure8207.ModePN != 3)
			ABCPowerSum=ABCPowerSum+Measure8207.CPowerPulPn/10;
	}
//			ABCPowerSum=0xa59a0000;
//			ppp=(unsigned char *)&ABCPowerSum;
//			RAM_Write(SM.Testram11,ppp,4);
#endif

	if(ABCPowerSum>=0)
	{
//		_DINT();
		__disable_irq();
		Measure8207.FlagDireABCn&=~F_ABCDire;//合相为正相//
		Measure8207.ABCPowerPulPn=ABCPowerSum;
//		Measure8207.ABCPowerPulPn=ABCPowerSum/10;	//Test
		Measure8207.APowerPulPPn=Measure8207.APowerPulPn;
		Measure8207.BPowerPulPPn=Measure8207.BPowerPulPn;
		Measure8207.CPowerPulPPn=Measure8207.CPowerPulPn;
//		_EINT();
		__enable_irq();
	}
	else
	{
		ABCPowerSum=0-ABCPowerSum;
//		_DINT();
		__disable_irq();
		Measure8207.ABCPowerPulPn=ABCPowerSum;
//		Measure8207.ABCPowerPulPn=ABCPowerSum/10;	//Test
		Measure8207.FlagDireABCn|=F_ABCDire;
		Measure8207.APowerPulPPn=Measure8207.APowerPulPn;
		Measure8207.BPowerPulPPn=Measure8207.BPowerPulPn;
		Measure8207.CPowerPulPPn=Measure8207.CPowerPulPn;
//		_EINT();
		__enable_irq();
	}
	
	Measure8207.ABCPower = ABCPowerSum/559;//ABCPowerSum/2393;	//保留一位小数
//	Measure8207.ABCPower = (Measure8207.ABCPower+5)/10;	//四舍五入取整
	Measure8207.ABCPower = (Measure8207.ABCPower+5);	//四舍五入取整
	Long_BCD4(Para.Qt,Measure8207.ABCPower);	
//	Long_BCD4(Measure8207.ABCPower,ABCPowerSum/20000);
	
//	if( Measure8207.ABCPowerPulP == 0 )	PDIR_YGLED |= P_YGLED;	 
	
//	Measure8207.ABCPower = ABCPowerSum/2393;	//保留一位小数
//	Measure8207.ABCPower = (Measure8207.ABCPower+5)/10;	//四舍五入取整
//	Long_BCD4(Para.Pt,Measure8207.ABCPower);	
		
//	ppp=(unsigned char *)&ABCPowerSum;
//	RAM_Write(SM.Testram11,ppp,4);			
//	if(Measure8207.ABCPower == 0 )Comm.PPIntervalTime = 0;
}


#endif

//计算ABC三相的合相用来发脉冲的电能量//
void ReadABCPower(void)
{
	signed long ABCPowerSum;
	signed long ABCPowerSumn;
	//unsigned char *ppp;
	if((Measure8207.AStartM==1) && ((Flag.VolFlg & F_PhAFail) != F_PhAFail))
	{
		ReadAPower();
	}else{
		Measure8207.APowerPulP = 0;	
		Measure8207.AStartM = 0;
		RAM_Fill( Para.Pa, 4 );
	}
	
#if ( PhaseType == Phase3 )
	if((Measure8207.BStartM==1) && ((Flag.VolFlg & F_PhBFail) != F_PhBFail))
	{
		ReadBPower();
	}else{
		Measure8207.BPowerPulP = 0;	
		Measure8207.BStartM = 0;
		RAM_Fill( Para.Pb, 4 );
	}
	if((Measure8207.CStartM==1) && ((Flag.VolFlg & F_PhCFail) != F_PhCFail))
	{
		ReadCPower();
	}else{
		Measure8207.CPowerPulP = 0;
		Measure8207.CStartM = 0;
		RAM_Fill( Para.Pc, 4 );
	}
#endif

	if(((Measure8207.FlagDireABC&F_ADire)!=0) && (Measure8207.ModePN != 4))
	{
		if(Measure8207.ModePN != 1)
			ABCPowerSum=0-Measure8207.APowerPulP;	
		else
			ABCPowerSum = 0;	
	}	
	else
	{
		if(Measure8207.ModePN != 3)
			ABCPowerSum=Measure8207.APowerPulP;
	}
			
#if ( PhaseType == Phase3 )							
	if(((Measure8207.FlagDireABC&F_BDire)!=0) && (Measure8207.ModePN != 4))
	{
		if(Measure8207.ModePN != 1)
			ABCPowerSum=ABCPowerSum-Measure8207.BPowerPulP;
	}	
	else
	{
		if(Measure8207.ModePN != 3)
		ABCPowerSum=ABCPowerSum+Measure8207.BPowerPulP;
	}
	
	if(((Measure8207.FlagDireABC&F_CDire)!=0) && (Measure8207.ModePN != 4))
	{
		if(Measure8207.ModePN != 1)	
			ABCPowerSum=ABCPowerSum-Measure8207.CPowerPulP;
	}	
	else
	{
		if(Measure8207.ModePN != 3)
			ABCPowerSum=ABCPowerSum+Measure8207.CPowerPulP;
	}
//			ABCPowerSum=0xa59a0000;
//			ppp=(unsigned char *)&ABCPowerSum;
//			RAM_Write(SM.Testram11,ppp,4);
#endif

	if(ABCPowerSum>=0)
	{
//		_DINT();
		__disable_irq();
		Measure8207.FlagDireABC&=~F_ABCDire;//合相为正相//
		Measure8207.ABCPowerPulPAL=ABCPowerSum;
//		Measure8207.ABCPowerPulPAL=ABCPowerSum/10;	//Test
		Measure8207.APowerPulPP=Measure8207.APowerPulP;
		Measure8207.BPowerPulPP=Measure8207.BPowerPulP;
		Measure8207.CPowerPulPP=Measure8207.CPowerPulP;
//		_EINT();
		__enable_irq();
	}
	else
	{
		ABCPowerSum=0-ABCPowerSum;
//		_DINT();
		__disable_irq();
		Measure8207.ABCPowerPulPAL=ABCPowerSum;
//		Measure8207.ABCPowerPulPAL=ABCPowerSum/10;	//Test
		Measure8207.FlagDireABC|=F_ABCDire;
		Measure8207.APowerPulPP=Measure8207.APowerPulP;
		Measure8207.BPowerPulPP=Measure8207.BPowerPulP;
		Measure8207.CPowerPulPP=Measure8207.CPowerPulP;
//		_EINT();
		__enable_irq();
	}	
//	Long_BCD4(Measure8207.ABCPower,ABCPowerSum/20000);
	
//	if( Measure8207.ABCPowerPulP == 0 )	PDIR_YGLED |= P_YGLED;	 
//	if( Measure8207.ABCPowerPulPAL == 0 )	GPIO->PBSET |= P_YGLED;  	
			  	
//	Measure8207.ABCPower = ABCPowerSum/559;//ABCPowerSum/2393;	//保留一位小数
//	Measure8207.ABCPower = ABCPowerSum/1119;//ABCPowerSum/2393;	//保留一位小数	
	Measure8207.ABCPower = ABCPowerSum/1450;//ABCPowerSum/2393;	//保留一位小数		
	
//	Measure8207.ABCPower = (Measure8207.ABCPower+5)/10;	//四舍五入取整
	Measure8207.ABCPower = (Measure8207.ABCPower+5);	//四舍五入取整
	Long_BCD4(Para.Pt,Measure8207.ABCPower);	
	
	//绝对值累加
//	if((Measure8207.FlagDireABC&F_ADire)!=0) 
//	{
//		ABCPowerSum=0-Measure8207.APowerPulP;	
//	}	
//	else
//	{
		ABCPowerSum=Measure8207.APowerPulP;
//	}
			
#if ( PhaseType == Phase3 )							
//	if((Measure8207.FlagDireABC&F_BDire)!=0) 
//	{
//		ABCPowerSum=ABCPowerSum-Measure8207.BPowerPulP;
//	}	
//	else
//	{
		ABCPowerSum=ABCPowerSum+Measure8207.BPowerPulP;
//	}
	
//	if((Measure8207.FlagDireABC&F_CDire)!=0)
//	{
//		ABCPowerSum=ABCPowerSum-Measure8207.CPowerPulP;
//	}	
//	else
//	{
		ABCPowerSum=ABCPowerSum+Measure8207.CPowerPulP;
//	}

#endif


	if(ABCPowerSum>=0)
	{
//		_DINT();
		__disable_irq();
		Measure8207.ABCPowerPulP=ABCPowerSum;
//		Measure8207.ABCPowerPulP=ABCPowerSum/10;	//Test

//		_EINT();
		__enable_irq();
	}
	else
	{
		ABCPowerSum=0-ABCPowerSum;	
//		_DINT();
		__disable_irq();
//		Measure8207.ABCPowerPulP=ABCPowerSum;
		Measure8207.ABCPowerPulP=ABCPowerSum;	//Test
//		_EINT();
		__enable_irq();
	}	
	

//	if( Measure8207.ABCPowerPulP < 0x49A0000)
//	{	
//		Measure8207.ABCPowerPulP = 0;
//	}	
//	Measure8207.ABCPower = ABCPowerSum/559;//ABCPowerSum/2393;	//保留一位小数
//	Measure8207.ABCPower = ABCPowerSum/1119;//ABCPowerSum/2393;	//保留一位小数	
	Measure8207.ABCPower = ABCPowerSum/1450;//ABCPowerSum/2393;	//保留一位小数		
	
	Measure8207.ABCPower = (Measure8207.ABCPower+5);	//四舍五入取整
//	Measure8207.ABCPower = (Measure8207.ABCPower+5)/10;	//四舍五入取整
	Long_BCD4(Para.PtABS,Measure8207.ABCPower);



	//正反向功率的计算
	if((Measure8207.FlagDireABC&F_ADire)!=0) 
	{
		ABCPowerSumn=Measure8207.APowerPulP;	
		ABCPowerSum =0;
	}	
	else
	{
		ABCPowerSum=Measure8207.APowerPulP;
		ABCPowerSumn=0;
	}
			
#if ( PhaseType == Phase3 )							
	if((Measure8207.FlagDireABC&F_BDire)!=0) 
	{
		ABCPowerSumn=ABCPowerSumn+Measure8207.BPowerPulP;
	}	
	else
	{
		ABCPowerSum=ABCPowerSum+Measure8207.BPowerPulP;
	}
	
	if((Measure8207.FlagDireABC&F_CDire)!=0)
	{
		ABCPowerSumn=ABCPowerSumn+Measure8207.CPowerPulP;
	}	
	else
	{
		ABCPowerSum=ABCPowerSum+Measure8207.CPowerPulP;
	}

#endif

//	Measure8207.ABCPowerPulPAL=ABCPowerSum;

//	Measure8207.ABCPower = ABCPowerSum/559;//ABCPowerSum/2393;	//保留一位小数
//	Measure8207.ABCPower = ABCPowerSum/1119;//ABCPowerSum/2393;	//保留一位小数	
	Measure8207.ABCPower = ABCPowerSum/1450;//ABCPowerSum/2393;	//保留一位小数		
	
	Measure8207.ABCPower = (Measure8207.ABCPower+5);	//四舍五入取整
	Long_BCD4(Para.PtABC,Measure8207.ABCPower);

//	Measure8207.ABCPower = ABCPowerSumn/559;//ABCPowerSum/2393;	//保留一位小数
//	Measure8207.ABCPower = ABCPowerSumn/1119;//ABCPowerSum/2393;	//保留一位小数	
	Measure8207.ABCPower = ABCPowerSumn/1450;//ABCPowerSum/2393;	//保留一位小数	
	
	Measure8207.ABCPower = (Measure8207.ABCPower+5);	//四舍五入取整
	Long_BCD4(Para.PnABC,Measure8207.ABCPower);	



}

//读A相电能// 
unsigned char ReadAPower(void)
{
//	unsigned int Dcnt1s;
  	unsigned short AdjData;
    	unsigned long long APower;
 	unsigned long long APowerPulP = 0;
// 	unsigned long PhAPulse;
// 	unsigned char PhAEMUStatus;	//判断起动用

//   	unsigned long long APowerPulPFirst=0,APowerPulPNow = 0;
//    unsigned long long APowerPulPFirst=0;
//	unsigned char GetPowerNo;
//	unsigned char* PointP;
//    	unsigned char* PointPFirst;

 	APower = 0;
 	APowerPulP = 0;
// 	PhAPulse = 0;
// 	PhAEMUStatus = 0;

//   	PointP = (unsigned char*)&APowerPulP; 
//   	PointPFirst = (unsigned char*)&APowerPulPFirst;  	
	RAM_Fill(Comm8207.RecBuf8207, 4 );	
//	if(Read8207(CHIPIDA,ENERGYP3,3)==0x00) return 0;
//	
//	RAM_WriteInter( (unsigned char*)&APowerPulPFirst, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//	*(PointPFirst + 2) = 0;
//	
//	if(Read8207(CHIPIDA,ENERGYP3,3)==0x00)
//	{	 
//		RAM_Write((unsigned char*)&SM.PowerA1SCnt1[0],(unsigned char*)&SM.PowerA1SCnt1[1],6);
//		return 0;
//	}
//	
//	RAM_WriteInter( (unsigned char*)&APowerPulP, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//	*(PointP + 2) = 0;
//	    	
//	if(*(PointP + 1) == *(PointPFirst + 1) )
//	{
//		GetPowerNo = 1;
//		APowerPulP = APowerPulPFirst;	    	   			
//	}
//	else
//	{    	
//		GetPowerNo = 2;  	
//	}	
//    
//	APowerPulPNow = APowerPulP;
//	
//	if(SM.APowerPulPL > APowerPulP)	*(PointP + 2) = 1;
//	
//	APowerPulP -= SM.APowerPulPL;
//	
//	SM.APowerPulPL = APowerPulPNow;
//    
//	Dcnt1s = SM.PowerA1SCnt1[1];
//	
//	if(GetPowerNo == 2)
//	{	
//		Dcnt1s += SM.PowerA1SCnt1[0];   	
//	}
//	
//	if(SM.GetLAPowerNo == 1)
//	{	
//		Dcnt1s += SM.PowerA1SCnt1[2];
//	}
//	SM.GetLAPowerNo = GetPowerNo;

	
	if(Read8207(CHIPIDA,POWERP3,4)==0x00)
	{
//		Measure8207.FlagDireABC&=~F_ADire;//读错定为正向
//		Measure8207.FlagDireABC |= F_ADire;//读错定为正向	//TEST
//		return 0;
		if(Read8207(CHIPIDA,POWERP3,4)==0x00)
		{

			return 0;
		
		}	
		else
		{
			Para.IabcFlag |= ByteBit[0];
			if((Comm8207.RecBuf8207[0]&0x80)==0)
			{	
				Measure8207.FlagDireABC&=~F_ADire;//正向
				Para.PWFlag &=~ ByteBit[0];		
			}
			else
			{	
				Measure8207.FlagDireABC|=F_ADire;	//反向//
				Para.PWFlag |= ByteBit[0];
				Comm8207.RecBuf8207[0]^=0xff;
				Comm8207.RecBuf8207[1]^=0xff;
				Comm8207.RecBuf8207[2]^=0xff;
				Comm8207.RecBuf8207[3]^=0xff;	
			}
			
			RAM_WriteInter((unsigned char*)&APower,(unsigned char*)&Comm8207.RecBuf8207[0],4);
		}
	}	
	else
	{
		Para.IabcFlag |= ByteBit[0];
		if((Comm8207.RecBuf8207[0]&0x80)==0)
		{	
			Measure8207.FlagDireABC&=~F_ADire;//正向
			Para.PWFlag &=~ ByteBit[0];		
		}
		else
		{	
			Measure8207.FlagDireABC|=F_ADire;	//反向//
			Para.PWFlag |= ByteBit[0];
			Comm8207.RecBuf8207[0]^=0xff;
			Comm8207.RecBuf8207[1]^=0xff;
			Comm8207.RecBuf8207[2]^=0xff;
			Comm8207.RecBuf8207[3]^=0xff;	
		}
		
		RAM_WriteInter((unsigned char*)&APower,(unsigned char*)&Comm8207.RecBuf8207[0],4);
	}		

//	if((((Measure8207.PhAPower*10)/APower)<13)||(((APower*10)/Measure8207.PhAPower)<13))	//两次读的功率之差小于13%累加
//	{
//		Measure8207.PhAPower += APower;
//		Measure8207.PhARPWRCnt++;	//A相读能量次数	
//		if( Measure8207.PhARPWRCnt > 1 )
//		{
//			Measure8207.PhAPower /= Measure8207.PhARPWRCnt;
//			APower = Measure8207.PhAPower;
//			Measure8207.PhAPower = 0;
//			Measure8207.PhARPWRCnt = 0;
//		}	
//	  	else
//	  	{
//	  		return 0;
//	  	}						    		
//	}
//	else
//	{
//			Measure8207.PhAPower = 0;
//			Measure8207.PhARPWRCnt = 0;
//	}

  	AdjData=(unsigned short)Measure8207.AAdjust[1]*256+Measure8207.AAdjust[0];
//	APowerPulP = (unsigned long long)((APowerPulP*AdjData*PDLY400 )/Dcnt1s);
	APower = (unsigned long long)(APower*AdjData)/2000;
//	APower = (unsigned long long)(APower*AdjData)/10360; //* 528/Dcnt1s;
//	APowerPulP = (unsigned long long)APowerPulP*AdjData/10260 * 528/Dcnt1s;
//	APowerPulP = (unsigned long long)APowerPulP*AdjData/Dcnt1s * 494;
	
//	if(Read8207(CHIPIDA,EMUSTATUS,3)!=0x00)
//	{
//		PhAEMUStatus = Comm8207.RecBuf8207[0];		
//	}	
	
//	if(Read8207(CHIPIDA,ENERGYP2,3)!=0x00)
//	{
//		RAM_WriteInter((unsigned char*)&PhAPulse,(unsigned char*)&Comm8207.RecBuf8207[0],3);
//	}	
	
//	if(PhAEMUStatus&0x08)
//	{
//		APower = 0;	
//	}		
//	else 
//	if((APower>860000)&&(APowerPulP == 0))		//大电流切换到小电流过程中避免发脉冲
//	{
//		APower = 0;				
//	}	
	
	APowerPulP = APower;
	
//	if(APowerPulP < 100)
//	if(APowerPulP < 55000)
//	if(APowerPulP <= 3625000)//20140124 小于等于25W		
	if(APowerPulP <= 333500)// 小于等于2.3W			
	{		
		Measure8207.FlagDireABC&=~F_ADire;//正向
		Para.PWFlag &=~ ByteBit[0];	
		if(APowerPulP < 145000)
		APowerPulP = 0;
	}
	
	if((Measure8207.APowerPulPBak!=0)&&(APowerPulP==0))//为了虑除偶尔读成0//
	{
		Measure8207.APowerPulPBak = (unsigned long)APowerPulP;
		Measure8207.MeaOneA = 0;
		return 0; 
	}
	if((Measure8207.APowerPulPBak == 0)&&(APowerPulP!=0))//为了虑除偶尔读成0//
	{
		Measure8207.APowerPulPBak = (unsigned long)APowerPulP;
		Measure8207.MeaOneA = 0;
		return 0; 
	}
	      	
    	Measure8207.APowerPulPBak = (unsigned long)APowerPulP;
   	Measure8207.APowerPulP = (unsigned long)APowerPulP/10;
 
//	Measure8207.APowerPulN=0;
//	Measure8207.APowerPulNBak=0;
//	Measure8207.MeaOneA = 0;
//	Long_BCD4(Para.Pa,(unsigned long)Measure8207.APowerPulP/23930);	
//	Long_BCD4(Para.Pa,(unsigned long)Measure8207.APowerPulP/559);	
//	Long_BCD4(Para.Pa,(unsigned long)Measure8207.APowerPulP/1119);	
	Long_BCD4(Para.Pa,(unsigned long)Measure8207.APowerPulP/1450);	

	return 1;
}

//读B相电能//
unsigned char ReadBPower(void)
{
//	unsigned int Dcnt1s;
  	unsigned short AdjData;
	unsigned long long BPower;
 	unsigned long long BPowerPulP;
// 	unsigned long PhBPulse;
// 	unsigned long PhBEMUStatus;	//判断起动用

//	unsigned long long BPowerPulPFirst=0,BPowerPulPNow=0;
//	unsigned long long BPowerPulPFirst=0;
//	unsigned char GetPowerNo;
//	unsigned char* PointP;
//    unsigned char* PointPFirst;
	
	BPower = 0;
	BPowerPulP = 0;
//	PhBPulse = 0;
//	PhBEMUStatus = 0;

//    PointP = (unsigned char*)&BPowerPulP; 
//   	PointPFirst = (unsigned char*)&BPowerPulPFirst; 
	RAM_Fill(Comm8207.RecBuf8207, 4 );
	
//    if(Read8207(CHIPIDB,ENERGYP3,3)==0x00) return 0;
//    	
//    RAM_WriteInter( (unsigned char*)&BPowerPulPFirst, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//    *(PointPFirst + 2) = 0;
//    
//    if(Read8207(CHIPIDB,ENERGYP3,3)==0x00)
//    {	 
//		RAM_Write((unsigned char*)&SM.PowerB1SCnt1[0],(unsigned char*)&SM.PowerB1SCnt1[1],6);
//		return 0;
//    }
//    
//    RAM_WriteInter( (unsigned char*)&BPowerPulP, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//    *(PointP + 2) = 0;
//    
//    if(*(PointP + 1) == *(PointPFirst + 1) )
//    {
//    	GetPowerNo = 1;
//    	BPowerPulP = BPowerPulPFirst;
//    }
//    else
//    {
//    	GetPowerNo = 2;  	
//    }
//    	
//    BPowerPulPNow = BPowerPulP;
//    if(SM.BPowerPulPL > BPowerPulP)	*(PointP + 2) = 1;
//    	
//	BPowerPulP -= SM.BPowerPulPL;
//    
//    SM.BPowerPulPL = BPowerPulPNow;
//    
//    Dcnt1s = SM.PowerB1SCnt1[1];
//    if(GetPowerNo == 2)
//    	Dcnt1s += SM.PowerB1SCnt1[0];
//    if(SM.GetLBPowerNo == 1)
//    	Dcnt1s += SM.PowerB1SCnt1[2];
//    SM.GetLBPowerNo = GetPowerNo;

	if(Read8207(CHIPIDB,POWERP3,4)==0x00)
	{
//		Measure8207.FlagDireABC&=~F_BDire;//读错正向
//		Measure8207.FlagDireABC |= F_BDire;//读错定为正向	//TEST
//		return 0;
		if(Read8207(CHIPIDB,POWERP3,4)==0x00)
		{

			return 0;
		}	
		else
		{
			Para.IabcFlag |= ByteBit[1];
			if((Comm8207.RecBuf8207[0]&0x80)==0)
			{
				Measure8207.FlagDireABC&=~F_BDire;//正向
				Para.PWFlag &= ~ByteBit[1];		
			}
			else
			{
				Measure8207.FlagDireABC|=F_BDire;	//反向//
				Para.PWFlag |= ByteBit[1];
				Comm8207.RecBuf8207[0]^=0xff;
				Comm8207.RecBuf8207[1]^=0xff;
				Comm8207.RecBuf8207[2]^=0xff;
				Comm8207.RecBuf8207[3]^=0xff;
			}
			
	    		RAM_WriteInter( (unsigned char*)&BPower, (unsigned char*)&Comm8207.RecBuf8207[0], 4 );	   	
		}
	}	
	else
	{
		Para.IabcFlag |= ByteBit[1];
		if((Comm8207.RecBuf8207[0]&0x80)==0)
		{
			Measure8207.FlagDireABC&=~F_BDire;//正向
			Para.PWFlag &= ~ByteBit[1];		
		}
		else
		{
			Measure8207.FlagDireABC|=F_BDire;	//反向//
			Para.PWFlag |= ByteBit[1];
			Comm8207.RecBuf8207[0]^=0xff;
			Comm8207.RecBuf8207[1]^=0xff;
			Comm8207.RecBuf8207[2]^=0xff;
			Comm8207.RecBuf8207[3]^=0xff;
		}
		
    		RAM_WriteInter( (unsigned char*)&BPower, (unsigned char*)&Comm8207.RecBuf8207[0], 4 );	   	
	}		

//	if((((Measure8207.PhBPower*10)/BPower)<13)||(((BPower*10)/Measure8207.PhBPower)<13))	//两次读的功率之差小于13%累加
//	{
//    	Measure8207.PhBPower += BPower;
//		Measure8207.PhBRPWRCnt++;	//B相读能量次数	 				    		
//		if( Measure8207.PhBRPWRCnt > 1 )
//		{
//			Measure8207.PhBPower /= Measure8207.PhBRPWRCnt;
//			BPower = Measure8207.PhBPower;
//			Measure8207.PhBPower = 0;
//			Measure8207.PhBRPWRCnt = 0;
//		}	
//	  	else
//	  	{
//	  		return 0;
//	  	}
//	}
//	else
//	{
//			Measure8207.PhBPower = 0;
//			Measure8207.PhBRPWRCnt = 0;
//	}	

  	AdjData=(unsigned short)Measure8207.BAdjust[1]*256+Measure8207.BAdjust[0];

//	BPowerPulP = (unsigned long long)BPowerPulP*AdjData/10260 * 528/Dcnt1s;// 
//	BPowerPulP = (unsigned long long)BPowerPulP*AdjData/Dcnt1s *494;// 
//	BPower = (unsigned long long)(BPower*AdjData)/10360 ;//* 528/Dcnt1s;// /10000;
	BPower = (unsigned long long)(BPower*AdjData)/2000 ;//* 528/Dcnt1s;// /10000;
//	if(Read8207(CHIPIDB,EMUSTATUS,3)!=0x00)
//	{
//		PhBEMUStatus = Comm8207.RecBuf8207[0];		
//	}	
	
//	if(Read8207(CHIPIDB,ENERGYP2,3)!=0x00)
//	{
//		RAM_WriteInter((unsigned char*)&PhBPulse,(unsigned char*)&Comm8207.RecBuf8207[0],3);
//	}	
	
//	if(PhBEMUStatus&0x08)
//	{
//		BPower = 0;	
//	}
//	else 
//	if((BPower>860000)&&(BPowerPulP == 0))		//大电流切换到小电流过程中避免发脉冲
//	{
//		BPower = 0;				
//	}

	BPowerPulP = BPower;
	
//	if(BPowerPulP < 100)
//	if(BPowerPulP < 55000)		
//	if(BPowerPulP <= 3625000)//20140124 小于等于25W			
	if(BPowerPulP <= 333500)// 小于等于2.3W		
	{	
		Measure8207.FlagDireABC&=~F_BDire;//正向
		Para.PWFlag &= ~ByteBit[1];
		if(BPowerPulP < 145000)		
		BPowerPulP = 0;	
	}
	
	
	if((Measure8207.BPowerPulPBak!=0)&&(BPowerPulP==0))//为了虑除偶尔读成0//
	{
		Measure8207.BPowerPulPBak = (unsigned long)BPowerPulP;
		Measure8207.MeaOneB = 0;
		return 0;		
	}
	if((Measure8207.BPowerPulPBak == 0)&&(BPowerPulP !=0))//为了虑除偶尔读成0//
	{
		Measure8207.BPowerPulPBak = (unsigned long)BPowerPulP;
		Measure8207.MeaOneB = 0;
		return 0;		
	}

	Measure8207.BPowerPulPBak = (unsigned long)BPowerPulP;
	Measure8207.BPowerPulP = (unsigned long)BPowerPulP/10;

//	Measure8207.BPowerPulN=0;
//	Measure8207.BPowerPulNBak=0;
//	Measure8207.MeaOneB = 0;
//	Long_BCD4(Para.Pb,(unsigned long)Measure8207.BPowerPulP/23930);	
//	Long_BCD4(Para.Pb,(unsigned long)Measure8207.BPowerPulP/559);
//	Long_BCD4(Para.Pb,(unsigned long)Measure8207.BPowerPulP/1119);
	Long_BCD4(Para.Pb,(unsigned long)Measure8207.BPowerPulP/1450);

	return 1;
}


//读c相电能//
unsigned char ReadCPower(void)
{
//	unsigned int Dcnt1s;
  	unsigned short AdjData;
    unsigned long long CPower;
 	unsigned long long CPowerPulP;
// 	unsigned long PhCPulse;
// 	unsigned long PhCEMUStatus;	//判断起动用 
 	   
//    unsigned long long CPowerPulPFirst=0,CPowerPulPNow=0;
//    unsigned long long CPowerPulPFirst=0;
//	unsigned char GetPowerNo;
//    unsigned char* PointP;
//   	unsigned char* PointPFirst;
  
  	CPower = 0;
  	CPowerPulP = 0;
//  	PhCPulse = 0;
//  	PhCEMUStatus = 0;
  	
//	PointP = (unsigned char*)&CPowerPulP; 
//	PointPFirst = (unsigned char*)&CPowerPulPFirst; 
	RAM_Fill(Comm8207.RecBuf8207, 4 ); 

//	if(Read8207(CHIPIDC,ENERGYP3,3)==0x00) 	return 0;
//	
//	RAM_WriteInter( (unsigned char*)&CPowerPulPFirst, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//	*(PointPFirst + 2) = 0;
//	
//	if(Read8207(CHIPIDC,ENERGYP3,3)==0x00)
//	{	 
//		RAM_Write((unsigned char*)&SM.PowerC1SCnt1[0],(unsigned char*)&SM.PowerC1SCnt1[1],6);
//		return 0;
//	}
//	
//	RAM_WriteInter( (unsigned char*)&CPowerPulP, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//	*(PointP + 2) = 0;
//
//	if(*(PointP + 1) == *(PointPFirst + 1) )
//	{
//		GetPowerNo = 1;
//		CPowerPulP = CPowerPulPFirst;	
//	}
//	else
//	{
//		GetPowerNo = 2;	
//	}
//		
//	CPowerPulPNow = CPowerPulP;
//	if(SM.CPowerPulPL > CPowerPulP)
//	*(PointP + 2) = 1;
//	
//	CPowerPulP -= SM.CPowerPulPL;	
//	SM.CPowerPulPL = CPowerPulPNow;
//	
//	Dcnt1s = SM.PowerC1SCnt1[1];
//	
//	if(GetPowerNo == 2)
//	Dcnt1s += SM.PowerC1SCnt1[0];
//	
//	if(SM.GetLCPowerNo == 1)
//	Dcnt1s += SM.PowerC1SCnt1[2];
//	
//	SM.GetLCPowerNo = GetPowerNo;
	 	 
	if(Read8207(CHIPIDC,POWERP3,4)==0x00)
	{
//		Measure8207.FlagDireABC&=~F_CDire;//读错正向
//		Measure8207.FlagDireABC |= F_CDire;//读错定为正向	//TEST
//		return 0;
		if(Read8207(CHIPIDC,POWERP3,4)==0x00)
		{

			return 0;
		}	
		else
		{
			Para.IabcFlag |= ByteBit[2];
						
			if((Comm8207.RecBuf8207[0]&0x80)==0)
			{
				Measure8207.FlagDireABC&=~F_CDire;//正向
				Para.PWFlag &=~ ByteBit[2];	
			}
			else
			{
				Measure8207.FlagDireABC|=F_CDire;	//反向//
				Para.PWFlag |= ByteBit[2];
				Comm8207.RecBuf8207[0]^=0xff;
				Comm8207.RecBuf8207[1]^=0xff;
				Comm8207.RecBuf8207[2]^=0xff;
				Comm8207.RecBuf8207[3]^=0xff;
			}
			
	    		RAM_WriteInter( (unsigned char*)&CPower, (unsigned char*)&Comm8207.RecBuf8207[0], 4 );
		}
	}	
	else
	{
		Para.IabcFlag |= ByteBit[2];
					
		if((Comm8207.RecBuf8207[0]&0x80)==0)
		{
			Measure8207.FlagDireABC&=~F_CDire;//正向
			Para.PWFlag &=~ ByteBit[2];	
		}
		else
		{
			Measure8207.FlagDireABC|=F_CDire;	//反向//
			Para.PWFlag |= ByteBit[2];
			Comm8207.RecBuf8207[0]^=0xff;
			Comm8207.RecBuf8207[1]^=0xff;
			Comm8207.RecBuf8207[2]^=0xff;
			Comm8207.RecBuf8207[3]^=0xff;
		}
		
    		RAM_WriteInter( (unsigned char*)&CPower, (unsigned char*)&Comm8207.RecBuf8207[0], 4 );
	}		

//	if((((Measure8207.PhCPower*10)/CPower)<13)||(((CPower*10)/Measure8207.PhCPower)<13))	//两次读的功率之差小于13%累加
//	{
//    	Measure8207.PhCPower += CPower;			
//		Measure8207.PhCRPWRCnt++;		//C相读能量次数		
//		if( Measure8207.PhCRPWRCnt>1 )
//		{
//			Measure8207.PhCPower /= Measure8207.PhCRPWRCnt;
//			CPower = Measure8207.PhCPower;
//			Measure8207.PhCPower = 0;
//			Measure8207.PhCRPWRCnt = 0;
//		}	
//	  	else
//	  	{
//	  		return 0;
//	  	}				    		
//	}
//	else
//	{
//			Measure8207.PhCPower = 0;
//			Measure8207.PhCRPWRCnt = 0;
//	}
 	  	
 	AdjData=(unsigned short)Measure8207.CAdjust[1]*256+Measure8207.CAdjust[0];

//	CPowerPulP=(unsigned long long)CPowerPulP*AdjData/10260 * 528/Dcnt1s;//
//	CPowerPulP=(unsigned long long)CPowerPulP*AdjData/Dcnt1s * 494;//
//	CPowerPulP = (unsigned long long)((CPowerPulP*AdjData*PDLY400)/Dcnt1s);
//	CPower = (unsigned long long)(CPower*AdjData)/10360 ;//* 528/Dcnt1s;// /10000;
	CPower = (unsigned long long)(CPower*AdjData)/2000 ;//* 528/Dcnt1s;// /10000;	
//	if(Read8207(CHIPIDC,EMUSTATUS,3)!=0x00)
//	{
//		PhCEMUStatus = Comm8207.RecBuf8207[0];		
//	}	
	
//	if(Read8207(CHIPIDC,ENERGYP2,3)!=0x00)
//	{
//		RAM_WriteInter((unsigned char*)&PhCPulse,(unsigned char*)&Comm8207.RecBuf8207[0],3);
//	}	
	
//	if(PhCEMUStatus&0x08)		
//	{
//		CPowerPulP = 0;	
//	}	
//	else 
//	if((CPower>860000)&&(CPowerPulP == 0))		//大电流切换到小电流过程中避免发脉冲
//	{
//		CPower = 0;				
//	}

	CPowerPulP = CPower;	
	
//	if(CPowerPulP < 100)
//	if(CPowerPulP < 55000)
//	if(CPowerPulP <= 3625000)//20140124 小于等于25W		
	if(CPowerPulP <= 333500)// 小于等于2.3W			
	{	
		Measure8207.FlagDireABC&=~F_CDire;//正向
		Para.PWFlag &=~ ByteBit[2];
		if(CPowerPulP < 145000)			
		CPowerPulP = 0;	
	}	

	
    if((Measure8207.CPowerPulPBak!=0)&&(CPowerPulP==0))//为了虑除偶尔读成0//
    {
    	Measure8207.CPowerPulPBak = (unsigned long)CPowerPulP;
    	Measure8207.MeaOneC = 0;
    	return 0;
    }
    if((Measure8207.CPowerPulPBak==0)&&(CPowerPulP!=0))//为了虑除偶尔读成0//
    {
    	Measure8207.CPowerPulPBak = (unsigned long)CPowerPulP;
    	Measure8207.MeaOneC = 0;
    	return 0;
    }

    Measure8207.CPowerPulPBak = (unsigned long)CPowerPulP;
    Measure8207.CPowerPulP = (unsigned long)CPowerPulP/10;
//	Measure8207.CPowerPulN=0;
//	Measure8207.CPowerPulNBak=0;
//	Measure8207.MeaOneC = 0;
//	Long_BCD4(Para.Pc,(unsigned long)Measure8207.CPowerPulP/23930);	
//	Long_BCD4(Para.Pc,(unsigned long)Measure8207.CPowerPulP/559);	
//	Long_BCD4(Para.Pc,(unsigned long)Measure8207.CPowerPulP/1119);	
	Long_BCD4(Para.Pc,(unsigned long)Measure8207.CPowerPulP/1450);	

	return 1;
}



////读A相电能//
//unsigned char ReadAPower(void)
//{
//	unsigned int Dcnt1s;
//  	unsigned int AdjData;
//    unsigned long long APowerPulP=0,APowerPulPFirst=0,APowerPulPNow = 0;
//	unsigned char RecBuf8207[10],GetPowerNo;//,*ppp;
//	unsigned char* PointP;
//    unsigned char* PointPFirst;
//       	
//   	PointP = (unsigned char*)&APowerPulP; 
//   	PointPFirst = (unsigned char*)&APowerPulPFirst; 
//	RAM_Fill(Comm8207.RecBuf8207, 4 );
//    if(Read8207(CHIPIDA,ENERGYP,3)==0x00) return 0;
//    RAM_WriteInter( (unsigned char*)&APowerPulPFirst, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//    *(PointPFirst + 2) = 0;
//    if(Read8207(CHIPIDA,ENERGYP,3)==0x00)
//    {	 
//		RAM_Write((unsigned char*)&SM.PowerA1SCnt1[0],(unsigned char*)&SM.PowerA1SCnt1[1],6);
//		return 0;
//    }
//    RAM_WriteInter( (unsigned char*)&APowerPulP, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//    *(PointP + 2) = 0;
//            	
//    if(*(PointP + 1) == *(PointPFirst + 1) )
//    {
//	    GetPowerNo = 1;
//	    APowerPulP = APowerPulPFirst;	    	   			
//    }
//    else
//    {    	
//	   GetPowerNo = 2;  	
//    }	
//    
//    APowerPulPNow = APowerPulP;
//    
//    if(SM.APowerPulPL > APowerPulP)	*(PointP + 2) = 1;
//    	
//	APowerPulP -= SM.APowerPulPL;
//    
//    Measure8207.APowerPulPBak = (unsigned long)APowerPulP;	//2012.8.25
//    
//    SM.APowerPulPL = APowerPulPNow;
//    Dcnt1s = SM.PowerA1SCnt1[1];
//    
//    if(GetPowerNo == 2)
//    {	
//    	Dcnt1s += SM.PowerA1SCnt1[0];   	
//    }
//    	
//    if(SM.GetLAPowerNo == 1)
//    {	
//    	Dcnt1s += SM.PowerA1SCnt1[2];
//    }
//    	
//    SM.GetLAPowerNo = GetPowerNo;
//                
////	if(Read8207(CHIPIDA,ENERGYP2,3)==0x00) 
////		return 0;
////	if((Comm8207.RecBuf8207[2] < 0x20) && ((Comm8207.RecBuf8207[1] != 0)||(Comm8207.RecBuf8207[0] != 0)))
////	{	
////		Comm8207.ReadPowerState |= F_APowerReadHM;
////		return 0;
////	}		
//
//
////	RAM_Write(RecBuf8207,(unsigned char*)&Comm8207.RecBuf8207[0],3);
//	
//	if(Read8207(CHIPIDA,POWERP,4)==0x00)
//	{
////		Measure8207.FlagDireABC&=~F_ADire;//读错定为正向
////		Measure8207.FlagDireABC |= F_ADire;//读错定为正向	//TEST
//	}	
//	else
//	{
//		if((Comm8207.RecBuf8207[0]&0x80)==0)
//		{	
//			Measure8207.FlagDireABC&=~F_ADire;//正向
//			Para.PWFlag &=~ ByteBit[0];		
//		}
//		else
//		{	
//			Measure8207.FlagDireABC|=F_ADire;	//反向//
//			Para.PWFlag |= ByteBit[0];
//		}
//	}		
//
//	Para.IabcFlag |= ByteBit[0];
//  
//  	AdjData=(unsigned int)Measure8207.AAdjust[1]*256+Measure8207.AAdjust[0];
////	APowerPulP=(unsigned long long)((unsigned long long)RecBuf8207[0]*256+(unsigned long long)RecBuf8207[1])*256+RecBuf8207[2];
////	APowerPulP = 0;
////	RAM_WriteInter( (unsigned char*)&APowerPulP, RecBuf8207, 3 );
////	APowerPulP=(unsigned long long)APowerPulP*AdjData /SM.PowerA1SCnt*PDLY400;
////	APowerPulP=(unsigned long long)APowerPulP*AdjData /Dcnt1s*PDLY400;
//	APowerPulP = (unsigned long long)((APowerPulP*AdjData*PDLY400 )/Dcnt1s);
//	
//	if(APowerPulP < 100)
//	{		
//		Measure8207.FlagDireABC&=~F_ADire;//正向
//		Para.PWFlag &=~ ByteBit[0];	
//	}
//	if((Measure8207.APowerPulPBak!=0)&&(APowerPulP==0))//为了虑除偶尔读成0//
//    {
//		Measure8207.APowerPulPBak = (unsigned long)APowerPulP;
//		Measure8207.MeaOneA = 0;
//        	return 0; 
//    }
//	      	
////    Measure8207.APowerPulPBak = (unsigned long)APowerPulP;
//    Measure8207.APowerPulP = (unsigned long)APowerPulP;
//	Measure8207.APowerPulN=0;
//	Measure8207.APowerPulNBak=0;
//	Measure8207.MeaOneA = 0;
//
//	return 1;
//}
////读B相电能//
//unsigned char ReadBPower(void)
//{
//	unsigned int Dcnt1s;
//  	unsigned int AdjData;
//	unsigned long long BPowerPulP=0,BPowerPulPFirst=0,BPowerPulPNow=0;
//	unsigned char RecBuf8207[10],GetPowerNo;;//*ppp;
//	unsigned char* PointP;
//    unsigned char* PointPFirst;
//        
//    PointP = (unsigned char*)&BPowerPulP; 
//   	PointPFirst = (unsigned char*)&BPowerPulPFirst; 
//	RAM_Fill(Comm8207.RecBuf8207, 4 );
//    if(Read8207(CHIPIDB,ENERGYP,3)==0x00) return 0;
//    RAM_WriteInter( (unsigned char*)&BPowerPulPFirst, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//    *(PointPFirst + 2) = 0;
//    if(Read8207(CHIPIDB,ENERGYP,3)==0x00)
//    {	 
//		RAM_Write((unsigned char*)&SM.PowerB1SCnt1[0],(unsigned char*)&SM.PowerB1SCnt1[1],6);
//		return 0;
//    }
//    RAM_WriteInter( (unsigned char*)&BPowerPulP, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//    *(PointP + 2) = 0;
//    
//    if(*(PointP + 1) == *(PointPFirst + 1) )
//    {
//    	GetPowerNo = 1;
//    	BPowerPulP = BPowerPulPFirst;
//    }
//    else
//    {
//    	GetPowerNo = 2;
//    	
//    }	
//    BPowerPulPNow = BPowerPulP;
//    if(SM.BPowerPulPL > BPowerPulP)	*(PointP + 2) = 1;
//    	
//	BPowerPulP -= SM.BPowerPulPL;
//    
//    SM.BPowerPulPL = BPowerPulPNow;
//    Dcnt1s = SM.PowerB1SCnt1[1];
//    if(GetPowerNo == 2)
//    	Dcnt1s += SM.PowerB1SCnt1[0];
//    if(SM.GetLBPowerNo == 1)
//    	Dcnt1s += SM.PowerB1SCnt1[2];
//    SM.GetLBPowerNo = GetPowerNo;
//          
////	if(Read8207(CHIPIDB,ENERGYP2,3)==0x00) return 0;
////	if((Comm8207.RecBuf8207[2] < 0x20) && ((Comm8207.RecBuf8207[1] != 0)||(Comm8207.RecBuf8207[0] != 0)))
////	{	
////		Comm8207.ReadPowerState |= F_BPowerReadHM;
////		return 0;
////	}	
//////	if(Measure8207.MeaOneB==0)
//////        {Measure8207.MeaOneB=1;return 0;}
//////  	Dcnt1s=SM.PowerB1S;
//////	SM.PowerB1S=0;
////	RAM_Write(RecBuf8207,(unsigned char*)&Comm8207.RecBuf8207[0],3);
//	if(Read8207(CHIPIDB,POWERP,4)==0x00)
//	{
////		Measure8207.FlagDireABC&=~F_BDire;//读错正向
////		Measure8207.FlagDireABC |= F_BDire;//读错定为正向	//TEST
//	}	
//	else
//	{
//		if((Comm8207.RecBuf8207[0]&0x80)==0)
//		{
//			Measure8207.FlagDireABC&=~F_BDire;//正向
//			Para.PWFlag &= ~ByteBit[1];		
//		}
//		else
//		{
//			Measure8207.FlagDireABC|=F_BDire;	//反向//
//			Para.PWFlag |= ByteBit[1];
//		}
//	}		
//
//	Para.IabcFlag |= ByteBit[1];
//  
//  	AdjData=(unsigned int)Measure8207.BAdjust[1]*256+Measure8207.BAdjust[0];
////	BPowerPulP = (unsigned long long)((unsigned long long)RecBuf8207[0]*256+(unsigned long long)RecBuf8207[1])*256+RecBuf8207[2];
////	BPowerPulP = 0;
////	RAM_WriteInter( (unsigned char*)&BPowerPulP, RecBuf8207, 3 );
////	BPowerPulP=(unsigned long long)BPowerPulP*AdjData /Dcnt1s*PDLY400;
//	BPowerPulP = (unsigned long long)((BPowerPulP*AdjData*PDLY400)/Dcnt1s);
//	
//	if(BPowerPulP < 100)
//	{	
//		Measure8207.FlagDireABC&=~F_BDire;//正向
//		Para.PWFlag &= ~ByteBit[1];		
//	}
//	
//	//ppp=(unsigned char *)&Measure8207.APowerPulP;
//	
///*
//			if(Measure8207.BPowerPulPBak==0)
//			{Measure8207.BPowerPulPBak=	BPowerPulP;}
//			
//			if((RecBuf8207[0]==0)&&(RecBuf8207[1]==0))
//		        { 
//			  			BPowerPulP=(BPowerPulP+Measure8207.BPowerPulPBak)/2;
//						}
//		  if(BPowerPulP>0x0b00000000)
//		        BPowerPulP=0x000000000;
//*/	
////	if (Measure8207.BPowerPulPBak > BPowerPulP)
////        	BPowerPulPV = Measure8207.BPowerPulPBak - BPowerPulP;
////        else
////        	BPowerPulPV = 0;
//	if((Measure8207.BPowerPulPBak!=0)&&(BPowerPulP==0))//为了虑除偶尔读成0//
//	{
//		Measure8207.BPowerPulPBak = (unsigned long)BPowerPulP;
//		Measure8207.MeaOneB = 0;
//		return 0;
//		
//	}
////	if(Measure8207.BPowerPulPBak > 2*BPowerPulPV)
////	{
////		if(Measure8207.MeaOneB > 1)
////		{	
////			Measure8207.BPowerPulPBak = (unsigned long)BPowerPulP;
////			Measure8207.MeaOneB = 0;
////		}else{
////			Measure8207.MeaOneB++;
////			return 0;
////		}
////	}
//
//	Measure8207.BPowerPulPBak = (unsigned long)BPowerPulP;
//	Measure8207.BPowerPulP = (unsigned long)BPowerPulP;
//	Measure8207.BPowerPulN=0;
//	Measure8207.BPowerPulNBak=0;
//	Measure8207.MeaOneB = 0;
//
//
////	_EINT();
//	//ppp=(unsigned char *)&Dcnt1s;
////	RAM_Write(SM.Testram,&Comm8207.RecBuf8207[0],3);
//	return 1;
//}
//
//
////读c相电能//
//unsigned char ReadCPower(void)
//{
//	unsigned int Dcnt1s;
//  	unsigned int AdjData;
//    unsigned long long CPowerPulP=0,CPowerPulPFirst=0,CPowerPulPNow=0;
//	unsigned char RecBuf8207[10],GetPowerNo;;//*ppp;
//    unsigned char* PointP;
//   	unsigned char* PointPFirst;
//        
//	PointP = (unsigned char*)&CPowerPulP; 
//	PointPFirst = (unsigned char*)&CPowerPulPFirst; 
//	RAM_Fill(Comm8207.RecBuf8207, 4 );
//	
//	if(Read8207(CHIPIDC,ENERGYP,3)==0x00) 	return 0;
//	
//	RAM_WriteInter( (unsigned char*)&CPowerPulPFirst, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//	*(PointPFirst + 2) = 0;
//	
//	if(Read8207(CHIPIDC,ENERGYP,3)==0x00)
//	{	 
//		RAM_Write((unsigned char*)&SM.PowerC1SCnt1[0],(unsigned char*)&SM.PowerC1SCnt1[1],6);
//		return 0;
//	}
//	
//	RAM_WriteInter( (unsigned char*)&CPowerPulP, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//	*(PointP + 2) = 0;
//
//	if(*(PointP + 1) == *(PointPFirst + 1) )
//	{
//		GetPowerNo = 1;
//		CPowerPulP = CPowerPulPFirst;	
//	}
//	else
//	{
//		GetPowerNo = 2;	
//	}
//		
//	CPowerPulPNow = CPowerPulP;
//	if(SM.CPowerPulPL > CPowerPulP)
//	*(PointP + 2) = 1;
//	
//	CPowerPulP -= SM.CPowerPulPL;
//	
//	SM.CPowerPulPL = CPowerPulPNow;
//	Dcnt1s = SM.PowerC1SCnt1[1];
//	
//	if(GetPowerNo == 2)
//	Dcnt1s += SM.PowerC1SCnt1[0];
//	
//	if(SM.GetLCPowerNo == 1)
//	Dcnt1s += SM.PowerC1SCnt1[2];
//	
//	SM.GetLCPowerNo = GetPowerNo;
//        
////	if(Read8207(CHIPIDC,ENERGYP2,3)==0x00) return 0;
////	if((Comm8207.RecBuf8207[2] < 0x20) && ((Comm8207.RecBuf8207[1] != 0)||(Comm8207.RecBuf8207[0] != 0)))
////	{	
////		Comm8207.ReadPowerState |= F_CPowerReadHM;
////		return 0;
////	}	
////	if(Measure8207.MeaOneC==0)
////        {Measure8207.MeaOneC=1;return 0;}
////  	Dcnt1s=SM.PowerC1S;
////	SM.PowerC1S=0;
//	RAM_Write(RecBuf8207,(unsigned char*)&Comm8207.RecBuf8207[0],3);
//	if(Read8207(CHIPIDC,POWERP,4)==0x00)
//	{
////		Measure8207.FlagDireABC&=~F_CDire;//读错正向
////		Measure8207.FlagDireABC |= F_CDire;//读错定为正向	//TEST
//	}	
//	else
//	{
//		if((Comm8207.RecBuf8207[0]&0x80)==0)
//		{
//			Measure8207.FlagDireABC&=~F_CDire;//正向
//			Para.PWFlag &=~ ByteBit[2];	
//		}
//		else
//		{
//			Measure8207.FlagDireABC|=F_CDire;	//反向//
//			Para.PWFlag |= ByteBit[2];
//		}
//	}		
//
//	Para.IabcFlag |= ByteBit[2];
//  
// 	AdjData=(unsigned int)Measure8207.CAdjust[1]*256+Measure8207.CAdjust[0];
////	CPowerPulP = (unsigned long long)((unsigned long long)RecBuf8207[0]*256+(unsigned long long)RecBuf8207[1])*256+RecBuf8207[2];
////	CPowerPulP = 0;
////	RAM_WriteInter( (unsigned char*)&CPowerPulP, RecBuf8207, 3 );
////	CPowerPulP=(unsigned long long)CPowerPulP*AdjData /Dcnt1s*PDLY400;
//	CPowerPulP = (unsigned long long)((CPowerPulP*AdjData*PDLY400)/Dcnt1s);
//
//	if(CPowerPulP < 100)
//	{	
//		Measure8207.FlagDireABC&=~F_CDire;//正向
//		Para.PWFlag &=~ ByteBit[2];	
//	}	
//	//ppp=(unsigned char *)&Measure8207.APowerPulP;
///*	
//			if(Measure8207.CPowerPulPBak==0)
//			{Measure8207.CPowerPulPBak=	CPowerPulP;}
//			
//			if((RecBuf8207[0]==0)&&(RecBuf8207[1]==0))
//		        { 
//			  			CPowerPulP=(CPowerPulP+Measure8207.CPowerPulPBak)/2;
//						}
//		  if(CPowerPulP>0x0b00000000)
//		        CPowerPulP=0x000000000;
//*/	
////        if (Measure8207.CPowerPulPBak > CPowerPulP)
////        	CPowerPulPV = Measure8207.CPowerPulPBak - CPowerPulP;
////        else
////        	CPowerPulPV = 0;	
//    if((Measure8207.CPowerPulPBak!=0)&&(CPowerPulP==0))//为了虑除偶尔读成0//
//    {
//    	Measure8207.CPowerPulPBak = (unsigned long)CPowerPulP;
//    	Measure8207.MeaOneC = 0;
//    	return 0;
//    }
////        if(Measure8207.CPowerPulPBak > 2*CPowerPulPV)
////        {
////        	if(Measure8207.MeaOneC > 1)
////        	{	
////        		Measure8207.CPowerPulPBak = (unsigned long)CPowerPulP;
////        		Measure8207.MeaOneC = 0;
////        	}
////        	else{ 
////        		Measure8207.MeaOneC++;
////        		return 0;
////        	}
////        }
//    Measure8207.CPowerPulPBak = (unsigned long)CPowerPulP;
//    Measure8207.CPowerPulP = (unsigned long)CPowerPulP;
//	Measure8207.CPowerPulN=0;
//	Measure8207.CPowerPulNBak=0;
//	Measure8207.MeaOneC = 0;
//
////	_EINT();
//	//ppp=(unsigned char *)&Dcnt1s;
////	RAM_Write(SM.Testram,&Comm8207.RecBuf8207[0],3);
//	return 1;
//}



void ResetA8209(void)
{
	unsigned char Rambuf[20];
//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();
	
	RAM_DataFill( Rambuf, 20, 0x00);
	
	Rambuf[0]=0xe5;
	Write8207(Rambuf,CHIPIDA,0xea,1);	//0xea,0xe5,使能写操作//

//	Rambuf[0]= 0x00;
//	Rambuf[1] = 0x00;
//	Write8207(Rambuf,CHIPIDA,SYSCON+0x80,2);

//	Rambuf[0]=0x00;
//	Rambuf[1]=0x1f;
//	Write8207(Rambuf,CHIPIDABC,EMUCON+0X80,2);
//	RAM_DataFill( Rambuf, 5, 0x00);
	
	Rambuf[0]=0x7f;
	Rambuf[1]=0x00;
//	Rambuf[1]=0xff;	
	Write8207(Rambuf,CHIPIDA,GPQA3+0x80,2);	//eeprom 3字节，实际使用2字节//
	
	Rambuf[0]=0x00;
	Rambuf[1]=0x01;
//	Rambuf[0]=0x02;
//	Rambuf[1]=0xEB;
	Write8207(Rambuf,CHIPIDA,HFCONST3+0x80,2);

	Rambuf[0]=0x00;		//2012.8.26
	Rambuf[1]=0x6E;
	Write8207(Rambuf,CHIPIDA,PSTART3+0x80,2);		
	Write8207(Rambuf,CHIPIDA,QSTART3+0x80,2);	
	
//	RAM_DataFill( Rambuf, 5, 0x00);
//	Rambuf[0] = 0x0F;		//2012.8.9
//	Rambuf[1] = 0x51;		
	E2P_RAdj( Rambuf, EAPOS, 6 );
	SwapChar( Rambuf, 1 );
	Write8207(Rambuf,CHIPIDA,APOSA3+0x80,2);
	
	
//	Rambuf[0]=0xf6;
//	Rambuf[1]=0x3B;	
//	Rambuf[0]=0xeb;//0.009
//	Rambuf[1]=0xa4;		

//	Rambuf[0]=0xE6;//0.000
//	Rambuf[1]=0x36;		
	Rambuf[0]=0xFD;//0.000
	Rambuf[1]=0x7F;	
	Write8207(Rambuf,CHIPIDA,IARMSOS3+0x80,2);
	
//	RAM_DataFill( Rambuf, 5, 0x00);
//	Rambuf[0]=0xf9;
	E2P_RAdj( Rambuf, EPHSA, 6 );
	SwapChar( Rambuf, 1 );
	Write8207(Rambuf,CHIPIDA,PHSA3+0x80,1);
	
	E2P_RAdj( Rambuf, EAPOSn, 6 );
	SwapChar( Rambuf, 1 );
	Write8207(Rambuf,CHIPIDA,RPOSA3+0x80,2);
	
	E2P_RAdj( Rambuf, EPHSAn, 6 );
	SwapChar( Rambuf, 1 );
	Write8207(Rambuf,CHIPIDA,QPHSCAL3+0x80,1);
	
	Rambuf[0]=0xdc;
	Write8207(Rambuf,CHIPIDA,0xea,1);	//0xea,0xdc,关闭写操作//
	
	Measure8207.AStartM=0;	
	Read8207(CHIPIDA,ENERGYP3,3);
	SM.APowerPulPL = 0;
//	RAM_WriteInter( (unsigned char*)&SM.APowerPulPL, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//	SM.APowerPulPL %= 0x10000;
	SM.GetLAPowerNo = 2;
}

void ResetB8209(void)
{
	unsigned char Rambuf[20];
	
//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();
	
	RAM_DataFill( Rambuf, 20, 0x00);
	
	Rambuf[0]=0xe5;
	Write8207(Rambuf,CHIPIDB,0xea,1);	//0xea,0xe5,使能写操作//
	
//	Rambuf[0]= 0x00;
//	Rambuf[1] = 0x00;
//	Write8207(Rambuf,CHIPIDB,SYSCON+0x80,2);
	
//	Rambuf[0]=0x00;
//	Rambuf[1]=0x1f;
//	Write8207(Rambuf,CHIPIDABC,EMUCON+0X80,2);
//	RAM_DataFill( Rambuf, 5, 0x00);
	
	Rambuf[0]=0x7f;
	Rambuf[1]=0x00;
//	Rambuf[1]=0xff;		
	Write8207(Rambuf,CHIPIDB,GPQA3+0x80,2);	//eeprom 3字节，实际使用2字节//
	
	Rambuf[0]=0x00;
	Rambuf[1]=0x01;
	Write8207(Rambuf,CHIPIDB,HFCONST3+0x80,2);

	Rambuf[0]=0x00;		//2012.8.26
	Rambuf[1]=0x6E;
	Write8207(Rambuf,CHIPIDB,PSTART3+0x80,2);	
	Write8207(Rambuf,CHIPIDB,QSTART3+0x80,2);	
	
//	RAM_DataFill( Rambuf, 5, 0x00);
//	Rambuf[0] = 0x0F;		//2012.8.9
//	Rambuf[1] = 0x51;	
	E2P_RAdj( Rambuf, EAPOS, 6 );
	SwapChar( Rambuf+2, 1 );
	Write8207(Rambuf+2,CHIPIDB,APOSA3+0x80,2);
	
//	Rambuf[0]=0xf6;
//	Rambuf[1]=0x3B;	
//	Rambuf[0]=0xeb;//0.009
//	Rambuf[1]=0xa4;		
//	Rambuf[0]=0xE6;//0.000
//	Rambuf[1]=0x36;		
	Rambuf[0]=0xFD;//0.000
	Rambuf[1]=0x7F;		
	Write8207(Rambuf,CHIPIDB,IARMSOS3+0x80,2);
	
//	RAM_DataFill( Rambuf, 5, 0x00);
//	Rambuf[0]=0xf9;
	E2P_RAdj( Rambuf, EPHSA, 6 );
	SwapChar( Rambuf+2, 1 );
	Write8207(Rambuf+2,CHIPIDB,PHSA3+0x80,1);
	
	E2P_RAdj( Rambuf, EAPOSn, 6 );
	SwapChar( Rambuf+2, 1 );
	Write8207(Rambuf+2,CHIPIDA,RPOSA3+0x80,2);
	
	E2P_RAdj( Rambuf, EPHSAn, 6 );
	SwapChar( Rambuf+2, 1 );
	Write8207(Rambuf+2,CHIPIDA,QPHSCAL3+0x80,1);
	
	Rambuf[0]=0xdc;
	Write8207(Rambuf,CHIPIDB,0xea,1);	//0xea,0xdc,关闭写操作//
	
	Measure8207.BStartM=0;	
	Read8207(CHIPIDB,ENERGYP3,3);
	SM.BPowerPulPL = 0;
//	RAM_WriteInter( (unsigned char*)&SM.BPowerPulPL, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//	SM.BPowerPulPL %= 0x10000;
	SM.GetLBPowerNo = 2;
}

void ResetC8209(void)
{
	unsigned char Rambuf[20];
	
//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();
	
	RAM_DataFill( Rambuf, 20, 0x00);
	
	Rambuf[0]=0xe5;
	Write8207(Rambuf,CHIPIDC,0xea,1);	//0xea,0xe5,使能写操作//

//	Rambuf[0]= 0x00;
//	Rambuf[1] = 0x00;
//	Write8207(Rambuf,CHIPIDC,SYSCON+0x80,2);
	
//	Rambuf[0]=0x00;
//	Rambuf[1]=0x1f;
//	Write8207(Rambuf,CHIPIDABC,EMUCON+0X80,2);
//	Read8207(CHIPIDC,0x43,1);	//test 
//	RAM_DataFill( Rambuf, 5, 0x00);
	
	Rambuf[0]=0x7f;
	Rambuf[1]=0x00;
//	Rambuf[1]=0xff;		
	Write8207(Rambuf,CHIPIDC,GPQA3+0x80,2);	//eeprom 3字节，实际使用2字节//
	
	Rambuf[0]=0x00;
	Rambuf[1]=0x01;
//	Rambuf[0]=0x02;
//	Rambuf[1]=0xEB;		
	Write8207(Rambuf,CHIPIDC,HFCONST3+0x80,2);

	Rambuf[0]=0x00;		//2012.8.26
	Rambuf[1]=0x6E;
	Write8207(Rambuf,CHIPIDC,PSTART3+0x80,2);	
	Write8207(Rambuf,CHIPIDC,QSTART3+0x80,2);	
	
//	RAM_DataFill( Rambuf, 5, 0x00);
//	Rambuf[0] = 0x0F;		//2012.8.9
//	Rambuf[1] = 0x51;	
	E2P_RAdj( Rambuf, EAPOS, 6 );
	SwapChar( Rambuf+4, 1 );		
	Write8207(Rambuf+4,CHIPIDC,APOSA3+0x80,2);
	
//	Rambuf[0]=0xf6;
//	Rambuf[1]=0x3B;	
//	Rambuf[0]=0xeb;//0.009
//	Rambuf[1]=0xa4;		
//	Rambuf[0]=0xE6;//0.000
//	Rambuf[1]=0x36;		
	Rambuf[0]=0xFD;//0.000
	Rambuf[1]=0x7F;	
	Write8207(Rambuf,CHIPIDC,IARMSOS3+0x80,2);
	
//	RAM_DataFill( Rambuf, 5, 0x00);
//	Rambuf[0]=0xf9;
	E2P_RAdj( Rambuf, EPHSA, 6 );
	SwapChar( Rambuf+4, 1 );	
	Write8207(Rambuf+4,CHIPIDC,PHSA3+0x80,1);
	
	E2P_RAdj( Rambuf, EAPOSn, 6 );
	SwapChar( Rambuf+4, 1 );
	Write8207(Rambuf+4,CHIPIDA,RPOSA3+0x80,2);
	
	E2P_RAdj( Rambuf, EPHSAn, 6 );
	SwapChar( Rambuf+4, 1 );
	Write8207(Rambuf+4,CHIPIDA,QPHSCAL3+0x80,1);
//	Read8207(CHIPIDC,GPQA,2);	//test 
//	Read8207(CHIPIDC,HFCONST,2);	//test 
                
	Rambuf[0]=0xdc;
	Write8207(Rambuf,CHIPIDC,0xea,1);	//0xea,0xdc,关闭写操作//
	
	Measure8207.CStartM=0;	
	Read8207(CHIPIDC,ENERGYP3,3);  
	SM.CPowerPulPL = 0;
//	RAM_WriteInter( (unsigned char*)&SM.CPowerPulPL, (unsigned char*)&Comm8207.RecBuf8207[0], 3 );
//	SM.CPowerPulPL %= 0x10000;
	SM.GetLCPowerNo = 2;
}
//三相一起无条件芯片初始化//
void Reset8209All(void)
{
	ResetA8209();
#if ( PhaseType == Phase3 )
	ResetB8209();
	ResetC8209();
#endif	
}	
//A，B，C三相的复位在芯片上电复位后或芯片其它原因复位后的初始化//
void	Reset8209(void)
{
	unsigned char Rambuf[20];
	
//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();

	RAM_DataFill( Rambuf, 20, 0x00);
	
//	if(((Flag.VolFlg & F_PhAFail) != F_PhAFail) && (Read8207(CHIPIDA,HFCONST3,2)==1)) 
	if(Read8207(CHIPIDA,HFCONST3,2)==1) 				
	{
		if(Comm8207.RecBuf8207[0]==0x10)
		{ResetA8209();}
		Measure8207.AReadOKCnt++;
		if(Measure8207.AReadOKCnt>2)
		{
			Measure8207.AStartM=1;
			Flag.VolFlg &= ~F_PhAFail;			
		}
		Measure8207.AReadErrCnt=0;	
	}
	else
	{
		Measure8207.AStartM = 0;
		Measure8207.AReadOKCnt = 0;
		Measure8207.AReadErrCnt++;
//		if((Measure8207.AReadErrCnt>2) || ((Flag.VolFlg & F_PhAFail) == F_PhAFail))
		if(Measure8207.AReadErrCnt>2) 				
		{
			Flag.VolFlg |= F_PhAFail;		
			Measure8207.APowerPulP=0;
			Measure8207.APowerPulPBak=0;	
		}		
		
	}		
#if ( PhaseType == Phase3 )
//	if(((Flag.VolFlg & F_PhBFail) != F_PhBFail) && (Read8207(CHIPIDB,HFCONST3,2)==1))
	if(Read8207(CHIPIDB,HFCONST3,2)==1)				
	{
		if(Comm8207.RecBuf8207[0]==0x10)
		{ResetB8209();}
		Measure8207.BReadOKCnt++;
		if(Measure8207.BReadOKCnt>2)
		{
			Measure8207.BStartM=1;
			Flag.VolFlg &= ~F_PhBFail;				
		}
		Measure8207.BReadErrCnt=0;
			
	}
	else
	{
		Measure8207.BStartM=0;
		Measure8207.BReadOKCnt = 0;
		Measure8207.BReadErrCnt++;
//		if((Measure8207.BReadErrCnt>2) || ((Flag.VolFlg & F_PhBFail) == F_PhBFail))
		if(Measure8207.BReadErrCnt>2)				
		{
			Flag.VolFlg |= F_PhBFail;				
			Measure8207.BPowerPulP=0;
			Measure8207.BPowerPulPBak=0;
		}		
	}		
//	if(((Flag.VolFlg & F_PhCFail) != F_PhCFail) && (Read8207(CHIPIDC,HFCONST3,2)==1))
	if(Read8207(CHIPIDC,HFCONST3,2)==1)				
	{
		if(Comm8207.RecBuf8207[0]==0x10)
		{ResetC8209();}
		Measure8207.CReadOKCnt++;
		if(Measure8207.CReadOKCnt>2)
		{
			Measure8207.CStartM=1;
			Flag.VolFlg &= ~F_PhCFail;		
		}
		Measure8207.CReadErrCnt=0;	
	}
	else
	{
		Measure8207.CStartM=0;
		Measure8207.CReadOKCnt = 0;
		Measure8207.CReadErrCnt++;
//		if((Measure8207.CReadErrCnt>2) || ((Flag.VolFlg & F_PhCFail) == F_PhCFail))
		if(Measure8207.CReadErrCnt>2) 				
		{
			Flag.VolFlg |= F_PhCFail;				
			Measure8207.CPowerPulP=0;
			Measure8207.CPowerPulPBak=0;	
		}			
	}
#endif	
}		
#endif
#endif


const unsigned char  JoinPrivateNetwork[]="mac join abp";
const unsigned char  JoinPublicNetwork[]="mac join otaa";
const unsigned char  SendDataLoRa[]="mac tx uncnf 3 ";
void ResetLoRa(unsigned char Mode)
{
	unsigned char Buff[30],Buff1[30],Buff2[30],i;
	unsigned char* Point;
	unsigned long DATAM,EnergyP0,EnergyPn;		
	unsigned long DATA1,DATA2,DATA3,DATA4;	
	
	Point = Buff;
		
	switch(Mode)
	{
		case 0:
			for(i=0;i<12;i++)
			{
				Comm.Buf0[i]=JoinPrivateNetwork[i];
			}
			Comm.Buf0[12]  = 0xd;	
			Comm.Buf0[13]  = 0xa;			
			Comm.SendLen0 = 13;//除去发送的第一个字节		
			break;
		case 1:
			for(i=0;i<13;i++)
			{
				Comm.Buf0[i]=JoinPublicNetwork[i];
			}		
			Comm.Buf0[13]  = 0xd;	
			Comm.Buf0[14]  = 0xa;				
			Comm.SendLen0 = 14;//除去发送的第一个字节				
			break;
		case 2:
			for(i=0;i<15;i++)
			{
				Comm.Buf0[i]=SendDataLoRa[i];
			}		
			Comm.Buf0[45]  = 0xd;	
			Comm.Buf0[46]  = 0xa;	
			Comm.SendLen0 = 46;//除去发送的第一个字节	
			DATA1 = 0;
			DATA2 = 0;
			DATA3 = 0;
			DATA4 = 0;			
			E2P_RData( Point, EMeter_No, 16 );

// 1HLY1234567890
// 1
			if(*(Point+0) > 0x39) 
				Buff1[0] = *(Point+0)-0x41+10;
			else
				Buff1[0] = *(Point+0)-0x30;

// HLY
			for(i=0;i<3;i++)
			{
				if(*(Point+1+i) > 0x39) 
					Buff1[1+i] = *(Point+1+i)-0x41;
				else
					Buff1[1+i] = *(Point+1+i)-0x30+26;
			}
/*		
// H
			if(*(Point+1) > 0x39) 
				Buff1[1] = *(Point+1)-0x41;
			else
				Buff1[1] = *(Point+1)-0x30+26;
// L
			if(*(Point+2) > 0x39) 
				Buff1[2] = *(Point+2)-0x41;
			else
				Buff1[2] = *(Point+2)-0x30+26;
// Y
			if(*(Point+3) > 0x39) 
				Buff1[3] = *(Point+3)-0x41;
			else
				Buff1[3] = *(Point+3)-0x30+26;		
*/			
// 12
			for(i=0;i<2;i++)
			{
				if(*(Point+4+i) > 0x39) 
					Buff1[4+i] = *(Point+4+i)-0x41+10;
				else
					Buff1[4+i] = *(Point+4+i)-0x30;
			}
/*			
// 1
			if(*(Point+4) > 0x39) 
				Buff1[4] = *(Point+4)-0x41+10;
			else
				Buff1[4] = *(Point+4)-0x30;
// 2
			if(*(Point+5) > 0x39) 
				Buff1[5] = *(Point+5)-0x41+10;
			else
				Buff1[5] = *(Point+5)-0x30;		
*/			
/*
// 34567890
			for(i=0;i<8;i++)
			{
				Buff1[6+i] = *(Point+6+i)-0x31;
			}
*/
// 34567890
			for(i=0;i<4;i++)
			{
//				Buff1[6+i] = (((*(Point+6+i)-0x31)<<4)|(*(Point+7+i)-0x31));
				Buff1[9-i] = (((*(Point+6+2*i)-0x30)<<4)|(*(Point+7+2*i)-0x30));				
			}
			DATAM = BCD4_Long( &Buff1[6]);
			
			Read_CMonEC(Point+16 , CMon_EC_Pp0 );
			ECDisplayMove(Point+16);//转为2位小数
			EnergyP0 = BCD4_Long( Point+16);
			
//			Read_CMonEC(&Buff1[16] , CMon_EC_Pp0);
			Read_CMonEC(&Buff1[16] , CMon_EC_Pn0);			
			ECDisplayMove(&Buff1[16]);//转为2位小数
			EnergyPn = BCD4_Long( &Buff1[16]);
						
/*			
			DATA1 = ((Buff1[0])<< 3)|
					((Buff1[1])<< 7)|
					((Buff1[2])<< 13)|
					((Buff1[3])<< 19)|
					((Buff1[4])<< 25)|	
					((Buff1[5]&0x07)<< 29);

			DATA2 = (((Buff1[5]&0x08)>>3)<< 0)|
					((DATAM&0x07FFFFFF)<< 1)|	
					((EnergyP0&0x0F)<< 28);
					
			DATA3 = (((EnergyP0>>4)&0x007FFFFF)<< 0)|
					((EnergyPn&0x000001FF)<< 23);

			DATA4 = (((EnergyPn>>9)&0x0003FFFF)<< 0);			
*/

			DATA1 = ((Buff1[0])<< 2)|
					((Buff1[1])<< 6)|
					((Buff1[2])<< 12)|
					((Buff1[3])<< 18)|
					((Buff1[4])<< 24)|	
					((Buff1[5]&0x0F)<< 28);

			DATA2 = ((DATAM&0x07FFFFFF)<< 0)|	
					((EnergyP0&0x1F)<< 27);
					
			DATA3 = (((EnergyP0>>5)&0x003FFFFF)<< 0)|
					((EnergyPn&0x000003FF)<< 22);

			DATA4 = (((EnergyPn>>10)&0x0001FFFF)<< 0);	
			
			RAM_WriteInter(&Buff2[0], (unsigned char *)&DATA1, 4);	
			_BCD_ASC( &Comm.Buf0[15], &Buff2[0], 4 );
			RAM_WriteInter(&Buff2[0], (unsigned char *)&DATA2, 4);	
			_BCD_ASC( &Comm.Buf0[23], &Buff2[0], 4 );
			RAM_WriteInter(&Buff2[0], (unsigned char *)&DATA3, 4);	
			_BCD_ASC( &Comm.Buf0[31], &Buff2[0], 4 );
			RAM_WriteInter(&Buff2[0], (unsigned char *)&DATA4, 3);	
			_BCD_ASC( &Comm.Buf0[39], &Buff2[0], 3 );
			

/*
			DATA1 = ((Buff1[0])<< 2)|
					((Buff1[1])<< 6)|
					((Buff1[2])<< 12)|
					((Buff1[3])<< 18)|
					((Buff1[4])<< 24)|	
					((Buff1[5]&0x0F)<< 28);

			DATA2 = ((DATAM<< 5)&0xFFFFFFE0)|	
					((EnergyP0>>22)&0x1F);
					
			DATA3 = ((EnergyP0&0x003FFFFF)<< 10)|
					((EnergyPn>>17)&0x000003FF);

			DATA4 = ((EnergyPn&0x0001FFFF)<< 15);	


			RAM_WriteInter(&Buff2[0], (unsigned char *)&DATA1, 4);
			_BCD_ASC( &Comm.Buf0[15], &Buff2[0], 4 );

			_BCD_ASC( &Comm.Buf0[23], (unsigned char *)&DATA2, 4 );
			_BCD_ASC( &Comm.Buf0[31], (unsigned char *)&DATA3, 4 );		
			_BCD_ASC( &Comm.Buf0[39], (unsigned char *)&DATA4, 3 );
*/			
			break;	
			
		case 5:
			for(i=0;i<15;i++)
			{
			Comm.Buf0[i]  = 0x55;				
			}			
//			Comm.Buf0[0]  = 0x55;	
//			Comm.Buf0[1]  = 0xd;	
//			Comm.Buf0[2]  = 0xa;			
			Comm.SendLen0 = 14;//除去发送的第一个字节		
			break;	
			
		default:			
		return;	
	//	break;



	}

	Comm.Ptr0 = 0;
	
	UART0->CTRL &=0xfff3; 	//屏蔽接收中断,屏蔽接收错误中断
	UART0->STA = 0x3d;		//清接收中断标志及接收错误标志
	
	UART0->TXD= Comm.Buf0[0] ;//发送一字节//
	

	UART0->CTRL |=0x02;		//允许发送中断
	UART0->STA = 0x02;		//清发送中断标志


}

void ResetLoRaData(unsigned char *Ptr,unsigned char lg)
{
	Comm.Ptr0 = 0;
	Comm.SendLen0 = lg;//除去发送的第一个字节		
	
	UART0->CTRL &=0xfff3; 	//屏蔽接收中断,屏蔽接收错误中断
	UART0->STA = 0x3d;		//清接收中断标志及接收错误标志
	
	UART0->TXD= Comm.Buf0[0] ;//发送一字节//
	

	UART0->CTRL |=0x02;		//允许发送中断
	UART0->STA = 0x02;		//清发送中断标志	
}


/*
void ATT7022WtReg(  unsigned char Cmd, unsigned char* Data )
{
	unsigned char Buff[3];
	unsigned char* Point;
	int i;
	
	Point = Buff;
	WDTCTL = WDT_ARST_1000;
	for( i=0;i<3;i++)
	{
		*Point = 0;
		*(Point+1) = 0;
		*(Point+2) = 0;
   		//_ATT7022WR( 0xC6, Point );	   	
	    _ATT7022WR( 0xC6, Point, 3 );	   	
	    //_ATT7022WR( Cmd, Data );
   		_ATT7022WR( Cmd, Data, 3 );
   		//_ATT7022Rd( ATSPIWBuffA, Point );
		_ATT7022Rd( ATSPIWBuffA, Point, 3 );
		if( Data_Comp(Data, Point, 3) == 0 ) break;
		//else if( i>=2 ) Flag.ErrFlg |= F_ErrMeas;	
		//else if( i>=2 ) Flag.Power |= F_ErrMeas;
		else if( i>=2 )	Flag.AlarmFlg |= F_AlarmMeas;
	}
	
//   _ATT7022WR( Cmd, Data );
}

void ATT7022RdReg(  unsigned char Cmd, unsigned char* Data )
{
	unsigned char Buff[3];
	unsigned char* Point;
	int i;
	
	Point = Buff;
	WDTCTL = WDT_ARST_1000;
//	for( i=0;i<2;i++)
	for( i=0;i<3;i++)				//Test
	{
		*Point = 0;
		*(Point+1) = 0;
		*(Point+2) = 0;
	   	//_ATT7022WR( 0xC6, Point );	   	
	   	_ATT7022WR( 0xC6, Point, 3 );	   	
	   	//_ATT7022Rd( Cmd, Data );
   		_ATT7022Rd( Cmd, Data,3 );
   		//_ATT7022Rd( ATSPIRBuff, Point );
		_ATT7022Rd( ATSPIRBuff, Point,3 );
		if( Data_Comp(Data, Point, 3) == 0 ) break;
//		else if( i>= 2 ) RAM_Fill( Data, 3 ); //RAM_Fill( Data, 3, 0);
		else if( i>= 2 ) RAM_Fill( Data, 3 ); //RAM_Fill( Data, 3, 0);		//Test
	}

//  	_ATT7022Rd( Cmd, Data );
}
*/

/*
void ATT7022Init(void)
{
	unsigned char Buff[6];
	unsigned char* Point;
	int RegAds,EpAds;
	
//	if((SM.CalibCount == CALIBCOUNT1)&&((Flag.Power & F_IrmsCheck) == 0)) return;	//处于校表状态，上电不进行AT7022初始化
	if(SM.CalibCount == CALIBCOUNT1) return;	//处于校表状态，上电不进行AT7022初始化
	
	Point = Buff;
	//Flag.ErrFlg &= ~F_ErrMeas;	
	//Flag.Power &= ~F_ErrMeas;
	Flag.AlarmFlg &= ~F_AlarmMeas;
	
	P3DIR &= ~P_CTLYWG;
	
	P1OUT &= ~P_ADSCLK;
	P1DIR |= P_ADSCLK;
//	P2OUT &= ~(P_MDOUT+P_ADCS);
	P2OUT &= ~P_MDOUT;
	P1OUT &= ~P_ADCS;
	
	P2OUT &= ~(P_ADREST+P_MDOUT+P_ADDIN);
	P2DIR |= P_ADREST;
//	P2DIR &= ~(P_ADDIN+P_MDOUT+P_ADCS);
	P2DIR &= ~(P_ADDIN+P_MDOUT);
	P1DIR &= ~P_ADCS;

	for( RegAds=0;RegAds<20;RegAds++ )
	{
		_NOP();	
	}		
	
	P2DIR &= ~P_ADREST;

	for( RegAds=0;RegAds<300;RegAds++ )
	{
		_NOP();	
	}		
	
	*(Point+3) =0;
	*(Point+4) =0;
	*(Point+5) =0;
	
	ATT7022WtReg( 0xC9, Point+3 );
//	ATT7022WtReg( 0xD3, Point+3 );
	ATT7022WtReg( 0xC3, Point+3 );
	ATT7022WtReg( 0x80, Point+3 );

	// *Point = 0x13;
	// *(Point+1) = 0x01;
	*Point = HFConstL;
	*(Point+1) = HFConstH;
	*(Point+2) = 0x0;	
	ATT7022WtReg( HFConst+128, Point );	//高频脉冲输出

	*Point = 0x02;						
	*(Point+1) = 0x55;
	*(Point+2) = 0x46;	
	ATT7022WtReg( UADCPga+128, Point );	//电压通道八倍增益	//ATT7022B
	
	for( RegAds=PgainA0;RegAds<=(EnergyAddMode-2);RegAds++ )
	{
//		if( PowerCheck() == 0 ) return;
		EpAds = ((RegAds - 6) * 4);
		if(( RegAds > UgainC )&&( RegAds < IgainA ))	continue; 
		if( RegAds >= IgainA ) EpAds = EpAds - 8*4;
		E2P_RAdj( Point, EpAds, 3 );

		ATT7022WtReg( RegAds+128, Point );
	} 	

	SetFailVoltage();
	SetEnergyAddMode();
	P3DIR |= P_CTLYWG;
}
*/

/*
void SetFailVoltage(void)
{
	unsigned char Buff[4];
	unsigned char* Point;
	unsigned long Value;
//	int i;
	
	Point = Buff;
	
	WDTCTL = WDT_ARST_1000;	
	//E2P_RData( Point, EVA_Valve, 4 ); 
	// *(Point+2) = 0;
	// *(Point+3) = 0;
	//Value = BCD2_Word(Point);

	E2P_RData( Point,EVolt_Valve, 1 );
	Value = V100Un * BCD_Byte( *Point ) / 100;
	Value = Value * 819;		//8192/10=819

	RAM_Fill( Point, 4 );
	ATT7022WtReg( 0xC9, Point );
	ATT7022WtReg( 0x80, Point );
	ATT7022WtReg( FailVoltage+128, (unsigned char*)&Value );  	
}
*/
/*
void SetEnergyAddMode(void)
{
	unsigned char Buff[3];
	unsigned char* Point;

	Point = Buff;
	*Point = 0;
	*(Point+1) = 0;
	*(Point+2) = 0;
	ATT7022WtReg( 0xC9, Point );
	ATT7022WtReg( 0x80, Point );
	E2P_RData( Point, ECMode, 1 );	//不全部代数和
	SM.OldRECMode = *Point;
#if( LinkMode == Phase3Wire4 )	
	if( *Point != 0 ) *Point = 0;
	else *Point = 1;
	// *Point = 1;							//全部代数和
#else
	if( *Point != 0 ) *Point = 1;
	// *Point = 0;							//全部代数和	
#endif		
	ATT7022WtReg( EnergyAddMode+128, Point );
}
*/		
/*
//Mode = 0:代数和
//Mode = 1:绝对值
void SetAddMode(unsigned char Mode)
{
	unsigned char Buff[3];
	unsigned char* Point;

	Point = Buff;
	*Point = 0;
	*(Point+1) = 0;
	*(Point+2) = 0;
	ATT7022WtReg( 0xC9, Point );
	ATT7022WtReg( 0x80, Point );
//	E2P_RData( Point, ECMode, 1 );	//不全部代数和
	SM.OldRECMode = Mode;
#if( LinkMode == Phase3Wire4 )	
	if( Mode != 0 ) *Point = 0;
	else *Point = 1;
	// *Point = 1;							//全部代数和
#else
	if( Mode != 0 ) *Point = 1;
	// *Point = 0;							//全部代数和	
#endif		
	ATT7022WtReg( EnergyAddMode+128, Point );
}		
*/

#if ( SinglePhase == YesCheck )

/*****************************************************************************
** Function name:	fnEMU_Init(void)
**
** Description:		计量EMU初始化函数，写入校表寄存器
**
** Parameters:		NONE
**
** Returned value:	NONE
**
******************************************************************************/
void fnEMU_Init(void)
{	unsigned  short read_buff;

	SYSCTL->SYS_PS = 0x82;
	SYSCTL->ADC_CTRL = 0x0003;							// 将I1通道配置为16倍增益
	SYSCTL->SYS_PS = 0x00;
	EMU->SPCMD = 0xe5;			 							// 写使能位
	
//	EMU->HFConst 	= 	0x0F00;
	EMU->HFConst 	= 	0x019C;	
	

//	EMU->IAGAIN 	= 	0x1FFF;
//	EMU->IBGAIN 	= 	0x1FFF;
//	EMU->UGAIN 		= 	0x1FFF;

  	E2P_RAdj( (unsigned char*)&read_buff, EE_CAL_PA, 2 );
	EMU->GPQA		= 	read_buff;
	E2P_RAdj( (unsigned char*)&read_buff, EE_CAL_PB, 2 );
	EMU->GPQB		= 	read_buff;
	
  	E2P_RAdj( (unsigned char*)&read_buff, EE_PHADJ_A, 2 );	
	EMU->PhsA 		= 	read_buff;

  	E2P_RAdj( (unsigned char*)&read_buff, EE_PHADJ_B, 2 );	
	EMU->PhsB 		= 	read_buff;
	
  	E2P_RAdj( (unsigned char*)&read_buff, EE_Offset_A, 2 );	
	EMU->APOSA 	= 	read_buff;
	
  	E2P_RAdj( (unsigned char*)&read_buff, EE_Offset_B, 2 );
	EMU->APOSB 	= 	read_buff;
/*
  	E2P_RAdj( (unsigned char*)&Para.IArmsK, EE_CAL_IA, 2 );	
	
	EMU->IAGAIN 	= 	0;
	
  	E2P_RAdj( (unsigned char*)&Para.UArmsK, EE_CAL_V, 2 );	
	EMU->UGAIN 		= 	0;

*/
  	E2P_RAdj( (unsigned char*)&read_buff, EE_CAL_IA, 2 );	
	
	EMU->IAGAIN 	= 	read_buff;
	
  	E2P_RAdj( (unsigned char*)&read_buff, EE_CAL_V, 2 );	
	EMU->UGAIN 		= 	read_buff;
	

	
	
//	EMU->PStart 	= 	0x0010;
//	EMU->QStart 	= 	0x0010;
	EMU->PStart 	= 	0x0032;
	EMU->QStart 	= 	0x0032;
	
	
//	EMU->IF  = 0xFFFFFF;//清发脉冲标志 
	EMU->IE  = 0x02;//使能有功脉冲中断
	NVIC_EnableIRQ(EMU_IRQn);
//	EMU->IARMSOS 	= 	Dl645FirmPara.IARMSOS;
//	EMU->IARMSOS 	= 	0x00;

//	EMU->IBRMSOS 	= 	Dl645FirmPara.IBRMSOS;
	EMU->SPCMD 		= 	0xdc; 							// 写保护
	

}

void SOCInit( void )
{	unsigned char j;
	unsigned long ChkSum;	
	
	NVIC_DisableIRQ(EMU_IRQn);	
        fnEMU_Init();
        SystemDelay(10);
        for(j=0;j<5;j++)
        {
        	if(!(EMU->EMUStatus & 0x01000000))	break;
        	SystemDelay(10);
        }
        fnWDT_Restart();

    fnWDT_Restart();
	
    ChkSum = EMU->EMUStatus & 0x00ffffff;
    E2P_WAdj( EMUStatusJY, (unsigned char*)&ChkSum,  4 );//保存校验和	
    E2P_WData( CalibrationRecord+EMUStatusJY-0x03D0, (unsigned char*)&ChkSum,  4 );//保存校验和	 
     
//    fnFront_ClockBatCalculate();
    fnWDT_Restart();
}


/*
void SOCInit( void )
{  
      	E2P_RAdj( (unsigned char*)&phase_calibration.V_rms_scale_factor, EV_rms_scale_factor, 2 );
      	phase_calibration.initial_v_dc_estimate.val=0;
    	E2P_RAdj( (unsigned char*)&phase_calibration.current.I_rms_scale_factor, ECurrent_I_rms_scale_factor, 2 );
    	phase_calibration.current.I_ac_offset=0;
    	phase_calibration.current.initial_I_dc_estimate.val=0;
		E2P_RAdj( (unsigned char*)&phase_calibration.current.P_scale_factor, ECurrent_P_scale_factor, 2 );	
		E2P_RAdj( (unsigned char*)&phase_calibration.current.P_ac_offset, ECurrent_P_ac_offset, 2 );			    	
//    	phase_calibration.current.P_ac_offset=0;//-10
		E2P_RAdj( (unsigned char*)&phase_calibration.current.phase_correction[0], ECurrent_phase_correction, 2 );
//		E2P_RAdj( (unsigned char*)&phase_calibration.current.I_region_stages1, ECurrent_I_region_stages1, 2 );
//		E2P_RAdj( (unsigned char*)&phase_calibration.current.I_region_stages2, ECurrent_I_region_stages2, 2 );
//		E2P_RAdj( (unsigned char*)&phase_calibration.current.I_region_stages3, ECurrent_I_region_stages3, 2 );  			
//		E2P_RAdj( (unsigned char*)&phase_calibration.current.phase_cal_val0, ECurrent_phase_cal_val0, 2 );
//		E2P_RAdj( (unsigned char*)&phase_calibration.current.phase_cal_val1, ECurrent_phase_cal_val1, 2 );
//		E2P_RAdj( (unsigned char*)&phase_calibration.current.phase_cal_val2, ECurrent_phase_cal_val2, 2 );
//		E2P_RAdj( (unsigned char*)&phase_calibration.current.phase_cal_val3, ECurrent_phase_cal_val3, 2 );
				
		phase_calibration.current.I_region_stages1=0;
		phase_calibration.current.I_region_stages2=0;
		phase_calibration.current.I_region_stages3=0;
		phase_calibration.current.phase_cal_val0=0;
		phase_calibration.current.phase_cal_val1=0;
		phase_calibration.current.phase_cal_val2=0;
		phase_calibration.current.phase_cal_val3=0;

		phase_calibration.neutral.I_rms_scale_factor=0;
		phase_calibration.neutral.I_ac_offset=0;
		phase_calibration.neutral.initial_I_dc_estimate.val=0;
		phase_calibration.neutral.P_scale_factor=0;
		phase_calibration.neutral.P_ac_offset=0;
		phase_calibration.neutral.phase_correction[0]=0;   
		phase_calibration.neutral.I_region_stages1=0;
		phase_calibration.neutral.I_region_stages2=0;
		phase_calibration.neutral.I_region_stages3=0;
		phase_calibration.neutral.phase_cal_val0=0;
		phase_calibration.neutral.phase_cal_val1=0;
		phase_calibration.neutral.phase_cal_val2=0;
		phase_calibration.neutral.phase_cal_val3=0;
		                    
		phase_calibration.calib_sum1=SOC_Cal_Datachksum();
		E2P_WAdj(Ecalib_sum1,(unsigned char*)&phase_calibration.calib_sum1,2);
		init_AD_Power();
		_DINT();			//2012.8.10
		SingleEnergyInit(&phase_readings,&phase_metrology,&phase_calibration, &phase_config);
		Delay(6000);		
		SD24BMEML0 = 0;
		SD24BMEMH0 = 0;
		SD24BMEML1 = 0;
		SD24BMEMH1 = 0;
		SD24BMEML2 = 0;		
		SD24BMEMH2 = 0;
//		SD24BCCTL0 &= ~SD24IFG0;		//2012.8.10
//		SD24BCCTL1 &= ~SD24IFG1;		//2012.8.10
//		SD24BCCTL2 &= ~SD24IFG2;		//2012.8.10				
		_EINT();			//2012.8.10	                                   			
}
	
unsigned int SOC_Cal_Datachksum(void)
{
		unsigned int CalDatachksum;
		
		CalDatachksum=phase_calibration.V_rms_scale_factor+phase_calibration.initial_v_dc_estimate.val+
									phase_calibration.current.I_rms_scale_factor+phase_calibration.current.I_ac_offset+
									phase_calibration.current.initial_I_dc_estimate.val+phase_calibration.current.P_scale_factor+
									phase_calibration.current.P_ac_offset+phase_calibration.current.phase_correction[0]+
									phase_calibration.current.I_region_stages1+phase_calibration.current.I_region_stages2+
									phase_calibration.current.I_region_stages3+
									phase_calibration.current.phase_cal_val0+phase_calibration.current.phase_cal_val1+
									phase_calibration.current.phase_cal_val2+phase_calibration.current.phase_cal_val3+
									phase_calibration.neutral.I_rms_scale_factor+phase_calibration.neutral.I_ac_offset+
									phase_calibration.neutral.initial_I_dc_estimate.val+phase_calibration.neutral.P_scale_factor+
									phase_calibration.neutral.P_ac_offset+phase_calibration.neutral.phase_correction[0]+
									phase_calibration.neutral.I_region_stages1+phase_calibration.neutral.I_region_stages2+
									phase_calibration.neutral.I_region_stages3+
									phase_calibration.neutral.phase_cal_val0+phase_calibration.neutral.phase_cal_val1+
									phase_calibration.neutral.phase_cal_val2+phase_calibration.neutral.phase_cal_val3;										
		return CalDatachksum;		
}

void init_AD_Power(void)
{
	phase_readings.current.power=0;
	phase_readings.current.power_factor = 0;
	phase_readings.V_rms=0;
	phase_readings.current.I_rms=0;
    phase_readings.current.consumed_energy=0;
    phase_readings.current.consumed_reactive_energy=0;
    phase_readings.current.VA_power=0;
    phase_readings.current.reactive_power=0;   

	phase_metrology.V_dc_estimate[0] = 0;
    RAM_Fill( (unsigned char*)&phase_metrology.V_history[0], 64);    
    RAM_Fill( (unsigned char*)&phase_metrology.current.I_history[0][0], 4);
    
    phase_metrology.current.I_dc_estimate[0] = 0;
    
    phase_metrology.current.P_accum[0][2] = 0;
    phase_metrology.current.P_accum[0][1] = 0;
    phase_metrology.current.P_accum[0][0] = 0;
    phase_metrology.current.P_accum_logged[0][2] = 0;
    phase_metrology.current.P_accum_logged[0][1] = 0;
    phase_metrology.current.P_accum_logged[0][0] = 0;                        

	phase_readings.neutral.power=0;  
    phase_readings.neutral.consumed_energy=0;
    	
    RAM_Fill( (unsigned char*)&phase_metrology.neutral.I_history[0][0], 4); 
    phase_metrology.neutral.I_dc_estimate[0] = 0;

    RAM_Fill( (unsigned char*)&phase_metrology.neutral.P_accum[0][0], 6); 
    RAM_Fill( (unsigned char*)&phase_metrology.neutral.P_accum_logged[0][0], 6); 
	
    phase_metrology.power = 0;
    phase_metrology.neutral_power = 0;
    phase_metrology.power_counter = 0;
    phase_metrology.power_counter_pulse = 0;	
    phase_metrology.total_power_counter = 0;
    phase_metrology.total_power_consumed_energy = 0; 
    
    phase_metrology.energy_pulse_remaining_time = 0;
    
    phase_metrology.reactive_power = 0;
    phase_metrology.reactive_power_counter = 0;
         	
	phase_metrology.current.in_phase_correction.step = 0;
	phase_metrology.last_V_sample = 0;
    phase_metrology.sample_count_logged = 0;
    phase_metrology.cycle_sample_count = 0;
    phase_metrology.mains_period = 0;
    phase_metrology.residual_power_cutoff = 0;
    phase_metrology.since_last = 0;
    phase_metrology.V_history_index = 0;
    phase_metrology.V_endstops = 0;
     
    RAM_Fill( (unsigned char*)&phase_metrology.current.P_reactive_accum[0][0], 6); 
    RAM_Fill( (unsigned char*)&phase_metrology.current.P_reactive_accum_logged[0][0], 6); 
    
	RAM_Fill( (unsigned char*)&phase_metrology.adc_buffer[0], 6); 
	
    phase_metrology.sample_count = 0;  
    phase_metrology.cycle_sample_count =0;

    RAM_Fill( (unsigned char*)&phase_metrology.V_sq_accum[0], 6);     
    RAM_Fill( (unsigned char*)&phase_metrology.V_sq_accum_logged[0], 6); 

    RAM_Fill( (unsigned char*)&phase_metrology.current.I_sq_accum[0][0], 6); 
    RAM_Fill( (unsigned char*)&phase_metrology.current.I_sq_accum_logged[0][0], 6); 
}

void init_energy_pulse_indicator(void)
{
	  _NOP();
}

void set_energy_pulse_indicator(void)
{
	PDIR_YGOUT |= P_YGOUT;	
	PDIR_YGLED |= P_YGLED;	
	
	if(phase_readings.status.bits.LIVE_POWER_REVERSED==1)	
	{
		SM.YPulse_Cumn++;
	}
	else
	{
		SM.YPulse_CumA++;		
	}
	
	SM.YPulse_Cum++;
  	_NOP();
}

void clr_energy_pulse_indicator(void)
{
	PDIR_YGOUT &= ~P_YGOUT;	
	PDIR_YGLED &= ~P_YGLED;	
	_NOP();
}

void init_reactive_energy_pulse_indicator(void)
{
	  _NOP();
}

void set_reactive_energy_pulse_indicator(void)
{	
	_NOP();
}

void clr_reactive_energy_pulse_indicator(void)
{
	_NOP();
}

void uint_energy_increase(void)
{
//    static uint32_t total_energy;
    _NOP();
//    total_energy += phase_readings.current.consumed_energy;
//    phase_readings.current.consumed_energy = 0;
}

void uint_reactive_energy_increase(void)
{
    _NOP();
}

void set_voltage_zero_cross_indicator(void)
{
	_NOP();
}

void clr_voltage_zero_cross_indicator(void)
{
	_NOP();
}
*/
#endif





////void EC_Meas(void)
////{
//////	unsigned char Buff[6];
//////	unsigned char* Point;
//////	unsigned char* Pulse_Cum;
////	unsigned char YPulse_Cum;
//////	unsigned char WPulse_Cum;
////	
//////	int	Meter_Quad,i;
////	int	i;
////
////	WDTCTL = WDT_ARST_1000;
////	
////	_DINT();
////	YPulse_Cum = SM.YPulse_Cum;
//////	WPulse_Cum = SM.WPulse_Cum;
////	SM.YPulse_Cum = 0;
//////	SM.WPulse_Cum = 0;
////	_EINT();
////	
////	//Meter_Quad = GetMQuad( Para.PWFlag,3 );		//取当前象限		
//////	Meter_Quad = GetMQuad( Para.PWFlag,3 );		//取当前象限		
/////*	if( Para.PWFlag & 0x08 ) Meter_Quad = 2;
////	else Meter_Quad = 1;
////	if( YPulse_Cum !=0 )
////	{
////		switch (Meter_Quad )
////		{
////			case 2:
////			case 3:	if( SM.RECMode == 0 )
////					{
////						SM.PL_CumPn +=  YPulse_Cum;
////						SM.MD_CumPn += YPulse_Cum;
////					}	
////				//	if ( Para.RPJLmode !=0 ) break;		//正反向合计？ 	
////			case 1:
////			case 4: SM.PL_CumPp +=  YPulse_Cum; 
////					SM.MD_CumPp += YPulse_Cum;
////					break;
////			default: break;
////		}
////	}	
////*/	
////	
/////*	if( WPulse_Cum !=0 )
////	{
////		*MDPara[Meter_Quad+3].MDCum += WPulse_Cum;
////		switch (Meter_Quad )
////		{
////			case 1: SM.PL_CumQ1 += WPulse_Cum; break; 	
////			case 2:	SM.PL_CumQ2 += WPulse_Cum; Meter_Quad = 3;break; 	
////			case 3: SM.PL_CumQ3 += WPulse_Cum; Meter_Quad = 4;break; 	
////			case 4: SM.PL_CumQ4 += WPulse_Cum; Meter_Quad = 2;break;		
////			default: break;
////		}
////		
////		if( Para.RQJLmode & ByteBit[Meter_Quad -1])
////		{
////			SM.PL_CumQp += WPulse_Cum;			//正向无功四象限随机组合而成
////			SM.MD_CumQp += WPulse_Cum;
////		}
////		if( Para.RQJLmode & ByteBit[Meter_Quad +3] )
////		{
////			SM.PL_CumQn += WPulse_Cum;			//反向无功四象限随机组合而成
////			SM.MD_CumQn += WPulse_Cum;
////		}		
////	}	
////*/	
////	for( i=0;i<ECUnitNum;i++ )								//大于0.01度写铁电存储器
////	{
////		while( *ECRgTab[i].ECRamBufAds >= PS32 )
////		{
////			_DINT();
////			*ECRgTab[i].ECRamBufAds -= PS32;
////			_EINT();
////			ECRgSum( i, 0);
////		}						
////	}		
////}	

#if ( Threephase == YesCheck ) //三相				

/*
void EC_Meas(void)
{
//	unsigned char Buff[6];
//	unsigned char* Point;
//	unsigned char* Pulse_Cum;
	unsigned char YPulse_Cum;
//	unsigned char YPulse_CumAL;
	unsigned char YPulse_CumA;
	unsigned char YPulse_CumB;
	unsigned char YPulse_CumC;
//	unsigned char WPulse_Cum;
// 	short i,Pulse_Repair,Pulse_RepairZ;
	
	
//	int	Meter_Quad,i;
//	short i,y;
	short i;

//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();

	if(SM.PL_CumCheck != ChkNum((unsigned char*)&SM.PL_CumPp,26))
	{
		RAM_Fill( (unsigned char*)&SM.PL_CumPp, 29 );
		SM.PL_CumCheck = 0xA5;
	}

//	if((SM.YPulse_Cum != 0)||(SM.YPulse_CumAL != 0)||(SM.WPulse_Cum != 0)||(SM.YPulse_CumA != 0)||(SM.YPulse_CumB != 0)||(SM.YPulse_CumC != 0))
	if((SM.YPulse_Cum != 0)||(SM.YPulse_CumA != 0)||(SM.YPulse_CumB != 0)||(SM.YPulse_CumC != 0))		
	{
//		_DINT();
		__disable_irq();
		YPulse_Cum = SM.YPulse_Cum;//SM.PL_CumPp += SM.YPulse_Cum;//
//		YPulse_CumAL = SM.YPulse_CumAL;//SM.PL_CumPp += SM.YPulse_Cum;//
		YPulse_CumA = SM.YPulse_CumA;
		YPulse_CumB = SM.YPulse_CumB;
		YPulse_CumC = SM.YPulse_CumC;
//		WPulse_Cum = SM.WPulse_Cum;
		SM.YPulse_Cum = 0;
		SM.YPulse_CumAL = 0;
		SM.YPulse_CumA = 0;
		SM.YPulse_CumB = 0;
		SM.YPulse_CumC = 0;
		SM.WPulse_Cum = 0;
//		_EINT();
		__enable_irq();
		SM.ILoadPulseSumP += YPulse_Cum;	//负荷记录电量差
		
		for(i=0;i<5 ;i++)
		{
		   if(( i == 0 ) || ( i == SM.FeeNo ))
		   {
//		      	*ECRgTab[i].ECRamBufAds += YPulse_Cum;
//		     	if(i == 0)
		     		*MDPara[i].MDCum += YPulse_Cum;	
		   }
		}
		
//		if((Flag.AlarmFlg[0] & F_AlarmMagnet)&&((PIN_CCJC & P_CCJC) == 0))	
//		{
//		      	*ECRgTab[12].ECRamBufAds += YPulse_Cum;
//		}
				
			  
		if(Measure8207.FlagDireABC & F_ADire)
			{
			*ECRgTab[8].ECRamBufAds += YPulse_CumA;
		     	*MDPara[5].MDCum += YPulse_CumA;				
			*ECRgTab[9].ECRamBufAds += YPulse_CumA;
			}
		else
			{
			*ECRgTab[0].ECRamBufAds += YPulse_CumA;
			*ECRgTab[SM.FeeNo].ECRamBufAds += YPulse_CumA;
			*ECRgTab[5].ECRamBufAds += YPulse_CumA;	
				if((Flag.AlarmFlg[0] & F_AlarmMagnet)&&((PIN_CCJC & P_CCJC) == 0))	
				{
				      	*ECRgTab[12].ECRamBufAds += YPulse_CumA;
				}			
			}
		
		if(Measure8207.FlagDireABC & F_BDire)
			{
			*ECRgTab[8].ECRamBufAds += YPulse_CumB;	
		     	*MDPara[5].MDCum += YPulse_CumB;				
			*ECRgTab[10].ECRamBufAds += YPulse_CumB;
			}
		else
			{
			*ECRgTab[0].ECRamBufAds += YPulse_CumB;
			*ECRgTab[SM.FeeNo].ECRamBufAds += YPulse_CumB;			
			*ECRgTab[6].ECRamBufAds += YPulse_CumB;
				if((Flag.AlarmFlg[0] & F_AlarmMagnet)&&((PIN_CCJC & P_CCJC) == 0))	
				{
				      	*ECRgTab[12].ECRamBufAds += YPulse_CumB;
				}	
			
			}
		
		if(Measure8207.FlagDireABC & F_CDire)
			{
			*ECRgTab[8].ECRamBufAds += YPulse_CumC;		
		     	*MDPara[5].MDCum += YPulse_CumC;				
			*ECRgTab[11].ECRamBufAds += YPulse_CumC;
			}
		else
			{
			*ECRgTab[0].ECRamBufAds += YPulse_CumC;
			*ECRgTab[SM.FeeNo].ECRamBufAds += YPulse_CumC;			
			*ECRgTab[7].ECRamBufAds += YPulse_CumC;	
				if((Flag.AlarmFlg[0] & F_AlarmMagnet)&&((PIN_CCJC & P_CCJC) == 0))	
				{
				      	*ECRgTab[12].ECRamBufAds += YPulse_CumC;
				}				
			}



		Pulse_Repair = SM.PL_CumPL1 + SM.PL_CumPL2 + SM.PL_CumPL3;
		Pulse_Repair = Pulse_Repair %100;//Pulse_Repair = Pulse_Repair %1000;
		Pulse_RepairZ = SM.PL_CumPp %100;//Pulse_RepairZ = SM.PL_CumPp %1000;
		Pulse_RepairZ = Pulse_RepairZ - Pulse_Repair;
		i = 0;
//		while((Pulse_RepairZ > 5) && (Pulse_RepairZ < 800)&&((Para.IabcFlag & 0x70) != 0))
		while((Pulse_RepairZ > 2) && (Pulse_RepairZ < 80)&&((Para.PWFlag & 0x07) != 0))
//		while(Pulse_RepairZ > 2) //&& (Pulse_RepairZ < 100))
		{
			if(Para.IabcFlag & ByteBit[i])
			{	
				if(Para.PWFlag & ByteBit[i])
				{	
//					*ECRgTab[6].ECRamBufAds += 1 ;
//					*ECRgTab[i + 7].ECRamBufAds += 1;
				}else{ 
					*ECRgTab[i + 5].ECRamBufAds += 1 ;
					Pulse_RepairZ--; 
				}
			}
			i++;	
			if(i >= 3) i = 0;
		}
	
		Pulse_Repair = SM.PL_CumPL1 + SM.PL_CumPL2 + SM.PL_CumPL3+ SM.PL_CumPL1R+ SM.PL_CumPL2R+ SM.PL_CumPL3R;
		Pulse_Repair = Pulse_Repair %1000;
		Pulse_RepairZ = SM.PL_CumPp %1000;
		Pulse_RepairZ = Pulse_RepairZ - Pulse_Repair;
		i = 0;
		while((Pulse_RepairZ > 5) && (Pulse_RepairZ < 800)&&((Para.PWFlag & 0x70) != 0))
//		while(Pulse_RepairZ > 2) //&& (Pulse_RepairZ < 100))
		{
			if(Para.PWFlag & ByteBit[i+4])
			{	
				if(Para.PWFlag & ByteBit[i])
				{	
					*ECRgTab[6].ECRamBufAds += 1 ;
					*ECRgTab[i + 7].ECRamBufAds += 1;
				}else *ECRgTab[i + 3].ECRamBufAds += 1 ;
				Pulse_RepairZ--; 
			}
			i++;	
			if(i >= 3) i = 0;
		}	

	

				

		for( i=0;i<ECUnitNum;i++ )								//大于0.01度写铁电存储器
//		for( i=0;i<20;i++ )								//大于0.01度写铁电存储器		
		{
			while( *ECRgTab[i].ECRamBufAds >= PS32 )
			{
//				_DINT();
//				__disable_irq();
				*ECRgTab[i].ECRamBufAds -= PS32;
//				_EINT();
//				__enable_irq();
				ECRgSum( i, 0);
			}						
		}
		SM.PL_CumCheck = ChkNum((unsigned char*)&SM.PL_CumPp,26);				
		Flag.Disk |= F_KeyInt;		
	}	
			
}
*/

void EC_Meas(void)
{
//	unsigned char Buff[6];
//	unsigned char* Point;
//	unsigned char* Pulse_Cum;
	unsigned short YPulse_Cum;
//	unsigned char WPulse_Cum;
	unsigned short YPulse_CumA;
	unsigned short YPulse_CumB;
	unsigned short YPulse_CumC;
	
//	int	Meter_Quad,i;
//	short i,y;
	short i;

//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();

//	if(SM.PL_CumCheck != ChkNum((unsigned char*)&SM.PL_CumPp,10))
//	{
//		RAM_Fill( (unsigned char*)&SM.PL_CumPp, 10 );
//		SM.PL_CumCheck = 0xA5;
//	}
	
//	if((SM.YPulse_Cum != 0)||(SM.WPulse_Cum != 0))
	if((SM.YPulse_Cum != 0)||(SM.YPulse_CumA != 0)||(SM.YPulse_CumB != 0)||(SM.YPulse_CumC != 0))			
	{
//		_DINT();
		__disable_irq();
		YPulse_Cum = SM.YPulse_Cum;//SM.PL_CumPp += SM.YPulse_Cum;//
		YPulse_CumA = SM.YPulse_CumA;
		YPulse_CumB = SM.YPulse_CumB;
		YPulse_CumC = SM.YPulse_CumC;			
//		WPulse_Cum = SM.WPulse_Cum;
		SM.YPulse_Cum = 0;
		SM.WPulse_Cum = 0;
		SM.YPulse_CumA = 0;
		SM.YPulse_CumB = 0;
		SM.YPulse_CumC = 0;		
	
		SM.PL_PowerOffCheck = ChkNumShort((unsigned short*)&SM.YPulse_Cum,6);			
//		_EINT();
		__enable_irq();
		SM.ILoadPulseSumP += YPulse_Cum;	//负荷记录电量差
		for(i=0;i<5 ;i++)
		{
		   if(( i == 0 ) || ( i == SM.FeeNo ))
		   {
		      	*ECRgTab[i].ECRamBufAds += YPulse_Cum;
//		     	if(i == 0)
		     	*MDPara[i].MDCum += YPulse_Cum;	
		   }
		}				

		if(Measure8207.FlagDireABC & F_ADire)
			{
			*ECRgTab[5].ECRamBufAds += YPulse_CumA;
			}

		
		if(Measure8207.FlagDireABC & F_BDire)
			{
			*ECRgTab[5].ECRamBufAds += YPulse_CumB;	
			}

		
		if(Measure8207.FlagDireABC & F_CDire)
			{
			*ECRgTab[5].ECRamBufAds += YPulse_CumC;		
			}






		for( i=0;i<ECUnitNum;i++ )								//大于0.01度写铁电存储器
//		for( i=0;i<20;i++ )								//大于0.01度写铁电存储器		
		{
			while( *ECRgTab[i].ECRamBufAds >= PS32 )
			{
//				_DINT();
//				__disable_irq();
				*ECRgTab[i].ECRamBufAds -= PS32;
//				_EINT();
//				__enable_irq();
				ECRgSum( i, 0);
			}						
		}
		
//		SM.PL_CumCheck = ChkNum((unsigned char*)&SM.PL_CumPp,10);	
		SM.PL_CumCheck = DoCrc16(0xFFFF,(unsigned char*)&SM.PL_CumPp,12);	
	Flag.Disk |= F_KeyInt;
	
	}	
			
}

#elif ( SinglePhase == YesCheck )


void EC_Meas(void)
{
//	unsigned char Buff[6];
//	unsigned char* Point;
//	unsigned char* Pulse_Cum;
	unsigned short YPulse_Cum;
//	unsigned char WPulse_Cum;
	
//	int	Meter_Quad,i;
//	short i,y;
	short i;

//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();

//	if(SM.PL_CumCheck != ChkNum((unsigned char*)&SM.PL_CumPp,10))
//	{
//		RAM_Fill( (unsigned char*)&SM.PL_CumPp, 10 );
//		SM.PL_CumCheck = 0xA5;
//	}
	
	if((SM.YPulse_Cum != 0)||(SM.WPulse_Cum != 0))
	{
//		_DINT();
		__disable_irq();
		YPulse_Cum = SM.YPulse_Cum;//SM.PL_CumPp += SM.YPulse_Cum;//
//		WPulse_Cum = SM.WPulse_Cum;
		SM.YPulse_Cum = 0;
		SM.WPulse_Cum = 0;
//		_EINT();
		__enable_irq();
		SM.ILoadPulseSumP += YPulse_Cum;	//负荷记录电量差
		for(i=0;i<5 ;i++)
		{
		   if(( i == 0 ) || ( i == SM.FeeNo ))
		   {
		      	*ECRgTab[i].ECRamBufAds += YPulse_Cum;
//		     	if(i == 0)
		     	*MDPara[i].MDCum += YPulse_Cum;	
		   }
		}				

		if(Para.PWFlag & 0x01)
			*ECRgTab[5].ECRamBufAds += YPulse_Cum;
	
		for( i=0;i<ECUnitNum;i++ )								//大于0.01度写铁电存储器
//		for( i=0;i<20;i++ )								//大于0.01度写铁电存储器		
		{
			while( *ECRgTab[i].ECRamBufAds >= PS32 )
			{
//				_DINT();
//				__disable_irq();
				*ECRgTab[i].ECRamBufAds -= PS32;
//				_EINT();
//				__enable_irq();
				ECRgSum( i, 0);
			}						
		}
		
//		SM.PL_CumCheck = ChkNum((unsigned char*)&SM.PL_CumPp,10);		
		SM.PL_CumCheck = DoCrc16(0xFFFF,(unsigned char*)&SM.PL_CumPp,12);	
	Flag.Disk |= F_KeyInt;
	
	}	
			
}




#endif



////void ECRgSum( int ECItem, int Type)
////{
////	unsigned char Buff[8];
////	unsigned char* Point;
////	unsigned int ECRgAds;
////	unsigned int ECBufAdsPtr;
////	unsigned int ECBufAds;
////	unsigned char ECBufPtr;
//////	int i;
////	
////	Point = Buff;
////	ECRgAds = ECRgTab[ECItem].ECRgAds;
////	ECBufAdsPtr = ECRgTab[ECItem].ECBufAdsPtr;
////	ECBufAds = ECRgTab[ECItem].ECBufAds;
////	
////	E2P_RData( &ECBufPtr,ECBufAdsPtr, 1 ); 
////	if( ECBufPtr > 63 ) ECBufPtr = 0;
////	E2P_RData( Point,ECBufAds + ECBufPtr * 2, 1 ); 	
////	*(Point + 1) = 0x00;
////	switch( Type )
////	{
////		case 0: _BCD1INC( Point );						//计量
////				if( *Point != 0 ) break;
////				*(Point + 1) = 0x01;				
////		case 1: 
////				/*
////				for(i=0;i<5 ;i++)
////		        {
////		        	if(( i == 0 ) || ( i == SM.FeeNo ))
////		            {
////		            	E2P_RData( Point+2, ECRgAds + i*6, 5 );		//存储
////		        	    _BCD2TO5ADD( Point+2, Point);
////			            E2P_WData( ECRgAds + i*6, Point+2, 5 );		//总电量
////		            }
////		            if( ECItem >= 8 ) break;			//分相电量无费率
////				}
////				*/
////            	E2P_RData( Point+2, ECRgAds, 4 );		//存储
////        	    _BCD2TO4ADD( Point+2, Point);
////	            E2P_WData( ECRgAds, Point+2, 4 );		//总电量
////
////		        *Point = 0;
////		        ECBufPtr++;
////				if( ECBufPtr > 63 ) ECBufPtr = 0;
////				E2P_WData( ECBufAdsPtr, &ECBufPtr, 1 ); 		 
////		        break;	
////		default: break;
////	}	
////	E2P_WData( ECBufAds + ECBufPtr * 2, Point, 1 ); 	//1度以下电量写回缓存
////}
void ECRgSum( short ECItem, short Type)
{
	unsigned char Buff[10];
	unsigned char* Point;
	unsigned short ECRgAds;
	unsigned short ECBufAdsPtr;
	unsigned short ECBufAds;
	unsigned char ECBufPtr;
//	int i;
	
	Point = Buff;
	ECRgAds = ECRgTab[ECItem].ECRgAds;
	ECBufAdsPtr = ECRgTab[ECItem].ECBufAdsPtr;
	ECBufAds = ECRgTab[ECItem].ECBufAds;

		#if ( Threephase == YesCheck ) //三相				
				E2P_RECData( &ECBufPtr,ECBufAdsPtr, 1 ); 		
		#elif ( SinglePhase == YesCheck )
				E2P_RECData( &ECBufPtr,ECBufAdsPtr, 1 ); 
		#endif	
//	E2P_RECData( &ECBufPtr,ECBufAdsPtr, 1 ); 
	if( ECBufPtr > 63 ) ECBufPtr = 0;
		#if ( Threephase == YesCheck ) //三相				
				E2P_RECData( Point,ECBufAds + ECBufPtr * 2, 1 ); 		
		#elif ( SinglePhase == YesCheck )
				E2P_RECData( Point,ECBufAds + ECBufPtr * 2, 1 ); 	
		#endif	
//	E2P_RECData( Point,ECBufAds + ECBufPtr * 2, 1 ); 	
	*(Point + 1) = 0x00;
	switch( Type )
	{
		case 0: _BCD1INC( Point );						//计量
				if( *Point != 0 ) break;
				*(Point + 1) = 0x01;				
		case 1: 
				
////				for(i=0;i<5 ;i++)
////		        {
////		        	if(( i == 0 ) || ( i == SM.FeeNo ))
////		            {
////		            	E2P_RData( Point+2, ECRgAds + i*6, 6 );		//存储
////		        	    _BCD2TO5ADD( Point+4, Point);
////			            E2P_WData( ECRgAds + i*6, Point+2, 6 );		//总电量
////		            }
////		            if( ECItem >= 8 ) break;			//分相电量无费率
////				}


		#if ( Threephase == YesCheck ) //三相				
				E2P_RECData( Point+2, ECRgAds, 6 );		//存储	
		#elif ( SinglePhase == YesCheck )
				E2P_RECData( Point+2, ECRgAds, 6 );		//存储
		#endif	
//            	E2P_RECData( Point+2, ECRgAds, 6 );		//存储

        	    _BCD2TO5ADD( Point+3, Point);
		
		#if ( Threephase == YesCheck ) //三相				
				E2P_WECData( ECRgAds, Point+2, 6 );		//总电量
		#elif ( SinglePhase == YesCheck )
				E2P_WECData( ECRgAds, Point+2, 6 );		//总电量
		#endif		
//	            E2P_WECData( ECRgAds, Point+2, 6 );		//总电量

		        *Point = 0;
		        ECBufPtr++;
				if( ECBufPtr > 63 ) ECBufPtr = 0;
				
		#if ( Threephase == YesCheck ) //三相				
				E2P_WECData( ECBufAdsPtr, &ECBufPtr, 1 ); 	
		#elif ( SinglePhase == YesCheck )
				E2P_WECData( ECBufAdsPtr, &ECBufPtr, 1 ); 		 
		#endif	
//				E2P_WECData( ECBufAdsPtr, &ECBufPtr, 1 ); 	

		        break;	
		default: break;
	}	
		#if ( Threephase == YesCheck ) //三相				
				E2P_WECData( ECBufAds + ECBufPtr * 2, Point, 1 ); 	//度以下电量写回缓存
		#elif ( SinglePhase == YesCheck )
				E2P_WECData( ECBufAds + ECBufPtr * 2, Point, 1 ); 	//度以下电量写回缓存		 
		#endif	
	
//	E2P_WECData( ECBufAds + ECBufPtr * 2, Point, 1 ); 	//度以下电量写回缓存
}
void Read_CMonEC( unsigned char* Dest, short ECRgAds )
{
	unsigned char Buff[2];
	unsigned char* Point;
	unsigned short Temp;
	unsigned short BufItem;
	
	Point = Buff;

		#if ( Threephase == YesCheck ) //三相				
				E2P_RECData( Dest, ECRgAds, 6 );
		#elif ( SinglePhase == YesCheck )
				E2P_RECData( Dest, ECRgAds, 6 );
		#endif	

// 	E2P_RECData( Dest, ECRgAds, 6 );//E2P_RData( Dest, ECRgAds, 5 );

//// 	if( ECRgAds >= CMon_EC_PpA ) 
//// 	{
//// 		Temp = 0; 	
//// 		BufItem = ECRgAds;
//// 		BufItem -= CMon_EC_PpA;	
////// 		BufItem = ( BufItem / 5 ) + 8;
//////// 		BufItem = ( BufItem / 5 ) + 2;	//无无功总及四象限电量
////		BufItem = ( BufItem / 7 ) + 2;	//无无功总及四象限电量
//// 	}	
////	else 
////	{	
////		Temp = (ECRgAds / 7) % 7;
		Temp = 0;
		BufItem = ECRgAds / 7;	
////		Temp = 0;					//无费率电量
////		BufItem = ECRgAds / 5;		//无费率电量
////	}	
	if(( Temp == 0 ) || ( Temp == SM.FeeNo ))		//为总电量或当前费率电量
	{
		#if ( Threephase == YesCheck ) //三相				
				E2P_RECData( (unsigned char*)&Temp,ECRgTab[BufItem].ECBufAdsPtr, 1 ); 
		#elif ( SinglePhase == YesCheck )
				E2P_RECData( (unsigned char*)&Temp,ECRgTab[BufItem].ECBufAdsPtr, 1 ); 
		#endif	
		
//		E2P_RECData( (unsigned char*)&Temp,ECRgTab[BufItem].ECBufAdsPtr, 1 ); 

		if( Temp > 63 ) Temp = 0;
		
		#if ( Threephase == YesCheck ) //三相				
				E2P_RECData( Point,ECRgTab[BufItem].ECBufAds + Temp * 2, 1 ); 
		#elif ( SinglePhase == YesCheck )
				E2P_RECData( Point,ECRgTab[BufItem].ECBufAds + Temp * 2, 1 ); 
		#endif	
		
//		E2P_RECData( Point,ECRgTab[BufItem].ECBufAds + Temp * 2, 1 ); 	

		*(Point + 1) = 0x00;
		_BCD2TO5ADD( Dest+1, Point);
#if( PS32 == 1000 )		
		*Dest = Byte_BCD(*(&SM.PL_CumPp + BufItem)/10);
#else
		*Dest = Byte_BCD(*(&SM.PL_CumPp + BufItem));
#endif	
	}	
}
/*
void Read_CMonEC( unsigned char* Dest, int ECRgAds )
{
	unsigned char Buff[2];
	unsigned char* Point;
	unsigned int Temp;
	unsigned int BufItem;
	
	Point = Buff;
 	E2P_RData( Dest, ECRgAds, 4 );
 	if( ECRgAds >= CMon_EC_PpA ) 
 	{
 		Temp = 0; 	
 		BufItem = ECRgAds;
 		BufItem -= CMon_EC_PpA;	
 		BufItem = ( BufItem / 5 ) + 8;
 	}	
	else 
	{	
		Temp = (ECRgAds / 5) % 5;
		BufItem = ECRgAds / 25;	
	}	
	if(( Temp == 0 ) || ( Temp == SM.FeeNo ))		//为总电量或当前费率电量
	{
		E2P_RData( (unsigned char*)&Temp,ECRgTab[BufItem].ECBufAdsPtr, 1 ); 
		if( Temp > 63 ) Temp = 0;
		E2P_RData( Point,ECRgTab[BufItem].ECBufAds + Temp * 2, 1 ); 	
		*(Point + 1) = 0x00;
		_BCD2TO4ADD( Dest, Point);
	}	
}	
*/
/*
void Read_CMonEC( unsigned char* Dest, int ECRgAds )
{
	unsigned char Buff[2];
	unsigned char* Point;
	unsigned int Temp;
	unsigned int BufItem;
	
	Point = Buff;
 	E2P_RData( Dest, ECRgAds, 4 );
	Temp = (ECRgAds / 5) % 5;
	BufItem = ECRgAds / 25;	
	if(( Temp == 0 ) || ( Temp == SM.FeeNo ))		//为总电量或当前费率电量
	{
		E2P_RData( (unsigned char*)&Temp,ECRgTab[BufItem].ECBufAdsPtr, 1 ); 
		if( Temp > 63 ) Temp = 0;
		E2P_RData( Point,ECRgTab[BufItem].ECBufAds + Temp * 2, 1 ); 	
		*(Point + 1) = 0x00;
		_BCD2TO4ADD( Dest, Point);
	}	
}	
*/
////void Read_CMonEC( unsigned char* Dest, int ECRgAds )
////{
////	unsigned char Buff[2];
////	unsigned char* Point;
////	unsigned int Temp;
////	unsigned int BufItem;
////	
////	Point = Buff;
//// 	E2P_RData( Dest, ECRgAds, 4 );
//// 	if( ECRgAds >= CMon_EC_PpA ) 
//// 	{
//// 		Temp = 0; 	
//// 		BufItem = ECRgAds;
//// 		BufItem -= CMon_EC_PpA;	
////// 		BufItem = ( BufItem / 5 ) + 8;
//// 		BufItem = ( BufItem / 5 ) + 2;	//无无功总及四象限电量
//// 	}	
////	else 
////	{	
//////		Temp = (ECRgAds / 5) % 5;
//////		BufItem = ECRgAds / 25;	
////		Temp = 0;					//无费率电量
////		BufItem = ECRgAds / 5;		//无费率电量
////	}	
////	if(( Temp == 0 ) || ( Temp == SM.FeeNo ))		//为总电量或当前费率电量
////	{
////		E2P_RData( (unsigned char*)&Temp,ECRgTab[BufItem].ECBufAdsPtr, 1 ); 
////		if( Temp > 63 ) Temp = 0;
////		E2P_RData( Point,ECRgTab[BufItem].ECBufAds + Temp * 2, 1 ); 	
////		*(Point + 1) = 0x00;
////		_BCD2TO4ADD( Dest, Point);
////	}	
////}	
/*
void Read_CMonEC( unsigned char* Dest, int ECRgAds )
{
	unsigned char Buff[2];
	unsigned char* Point;
	unsigned int Temp;
	unsigned int BufItem;
	
	Point = Buff;
 	E2P_RData( Dest, ECRgAds, 4 );
 	if( ECRgAds >= CMon_EC_PpA ) 
 	{
 		if( Read_CMonECPpnC( Dest, ECRgAds ) == 0 ) return;
 		Temp = 0; 	
 		BufItem = ECRgAds;
 		BufItem -= CMon_EC_PpA;	
// 		BufItem = ( BufItem / 5 ) + 8;
 		BufItem = ( BufItem / 5 ) + 2;	//无无功总及四象限电量
 	}	
	else 
	{	
//		Temp = (ECRgAds / 5) % 5;
//		BufItem = ECRgAds / 25;	
		Temp = 0;					//无费率电量
		BufItem = ECRgAds / 5;		//无费率电量
	}	
	if(( Temp == 0 ) || ( Temp == SM.FeeNo ))		//为总电量或当前费率电量
	{
		E2P_RData( (unsigned char*)&Temp,ECRgTab[BufItem].ECBufAdsPtr, 1 ); 
		if( Temp > 63 ) Temp = 0;
		E2P_RData( Point,ECRgTab[BufItem].ECBufAds + Temp * 2, 1 ); 	
		*(Point + 1) = 0x00;
		_BCD2TO4ADD( Dest, Point);
	}	
}	

int Read_CMonECPpnC( unsigned char* Dest, int ECRgAds )
{
	unsigned long Value;
	unsigned int Addr1;
	unsigned int Addr2;
	unsigned int Addr3;
	
	switch( ECRgAds )
	{
		case CMon_EC_PpC: 
			Addr1 = CMon_EC_Pp0;
			Addr2 = CMon_EC_PpA;
			Addr3 = CMon_EC_PpB;
			break;
		case CMon_EC_PnC:
			Addr1 = CMon_EC_Pn0;
			Addr2 = CMon_EC_PnA;
			Addr3 = CMon_EC_PnB;
			break;
		default:
			return 1;
	}	
	Read_CMonEC( Dest, Addr1 );
	Value = BCD4_Long( Dest );	 		
	Read_CMonEC( Dest, Addr2 );
	Value = Value - BCD4_Long( Dest );	 		
	Read_CMonEC( Dest, Addr3 );
	Value = Value - BCD4_Long( Dest );	 		
	Long_BCD4( Dest, Value );
	return 0;
}
*/
/*
int GetMQuad( unsigned char PWFlag, int Reg )
{
    int Quad=1;
        
	PWFlag = PWFlag >> Reg;	
	PWFlag &= 0x11;
	switch( PWFlag )
	{
		case 0: Quad = 1; break;	
		case 0x01: Quad = 2; break;	
		case 0x11: Quad = 3; break;	
		case 0x10: Quad = 4; break;	
		default: break;
	}	
	return 	Quad;
}

int GetStablyQuad( void )
{
	int Quad;
	
	Quad = GetMQuad( Para.PWFlag, 3 );
	
	if(( Quad == GetMQuad( Flag.PwDirPQ, 3 ))&&( Quad == GetMQuad( Flag.PwDirPQ2, 3 ) ))return Quad;
	else return 0;
	
}	

*/

short MD_MeasB( void )							//补需量计量
{
	unsigned char Buff[5],Buff1[4];
	unsigned char* Point;
//	unsigned short i,j,k,m,FreeNoData;
 	unsigned short i,j,k;
//	unsigned short PulseCum[MDUnitNum*5];
//	unsigned short PulseCum[MDUnitNum*2];	
//	unsigned short* PulseCumPt;
//	unsigned long Value1=0,Value2=0;			//V10	
	unsigned long Value1=0;			//V10	
	
	Point = Buff;

	E2P_RData( Point, MDT_Pp0 , 5);
/*
	for(i=0;i<15;i++)
	{
	_BCD1INC(Point);		
	if( *(Point+0) >= 0x60 )
	   {			// Minute
	   	 *(Point+0) = 0;
		_BCD1INC(Point+1);
		if( *(Point+1) >= 0x24 )
		{		// Hour
        		*(Point+1) = 0;
			DayInc( Point+2);
	    	}	
	   }		
	}		

	
	if( Data_Comp( Point,(unsigned char*)&Clk.Min[0], 5) == 1 )	 return 0;		//固定每15分钟算一次	
		
	E2P_WData( MDT_Pp0 , &Clk.Min[0], 5);		//写需量发生时间
	
	for(i=0;i<MDUnitNum;i++)
	{
		j = CMon_MD_Pp0 + i*4;
		k = CMon_MDT_Pp0 + i*6;

			RAM_Fill( &Buff1[0], 4 );																		//V10
			Value1 = ((*MDPara[i].MDCum * SM.MD_60T * 100 ) / (PS32/10));				//V10	
			*MDPara[i].MDCum = 0;
			Long_BCD4( &Buff1[0], Value1 );

			MD_CompB( Point, &Buff1[0], j , k );

	}	
*/		

for(i=0;i<15;i++)
{
	_BCD1INC(Point);		
	if( *(Point+0) >= 0x60 )
	   {			// Minute
	   	 *(Point+0) = 0;
		_BCD1INC(Point+1);
		if( *(Point+1) >= 0x24 )
		{		// Hour
        		*(Point+1) = 0;
			DayInc( Point+2);
	    	}	
	   }		
		

	
//	if( Data_Comp( Point,(unsigned char*)&Clk.Min[0], 5) == 1 )	 return 0;		//固定每15分钟算一次	
	if( Data_Comp( Point,(unsigned char*)&Clk.Min[0], 5) == 1 )	 break;		//固定每15分钟算一次	
	
	if(( BCD_Byte(*(Point+0)) % 15 ) == 0)
		{
			E2P_WData( MDT_Pp0 , Point, 5);		//写需量发生时间
			
			for(i=0;i<MDUnitNum;i++)
			{
				j = CMon_MD_Pp0 + i*4;
				k = CMon_MDT_Pp0 + i*6;

					RAM_Fill( &Buff1[0], 4 );																		//V10
					Value1 = ((*MDPara[i].MDCum * SM.MD_60T * 100 ) / (PS32/10));				//V10	
					*MDPara[i].MDCum = 0;
					Long_BCD4( &Buff1[0], Value1 );

					MD_CompB( Point, &Buff1[0], j , k );

			}	
			break;	
		}

}
	
	return 0;
}	

void MD_CompB( unsigned char* Pointtime,unsigned char* PointSrc, short MD_Ads, short MDT_Ads )
{
	unsigned char Buff[4];
	unsigned char* Point;

	Point = Buff;
	
#if ( Threephase == YesCheck ) //三相		
	E2P_RECData( Point, MD_Ads , 3);
	if( Data_Comp( PointSrc, Point, 3 ) == 1)
	{
		E2P_WECData( MD_Ads , PointSrc, 3);				//写最大需量
		E2P_WECData( MDT_Ads , Pointtime, 5);		//写需量发生时间
	}
#elif ( SinglePhase == YesCheck )
	E2P_RECData( Point, MD_Ads , 3);
	if( Data_Comp( PointSrc, Point, 3 ) == 1)
	{
		E2P_WECData( MD_Ads , PointSrc, 3);				//写最大需量
		E2P_WECData( MDT_Ads , Pointtime, 5);		//写需量发生时间
	}	
	
#endif		
	
}



short MD_Meas( void )							//需量计量
{
	unsigned char Buff[4];
	unsigned char* Point;
//	unsigned short i,j,k,m,FreeNoData;
 	unsigned short i,j,k;
//	unsigned short PulseCum[MDUnitNum*5];
//	unsigned short PulseCum[MDUnitNum*2];	
//	unsigned short* PulseCumPt;
//	unsigned long Value1=0,Value2=0;			//V10	
	unsigned long Value1=0;			//V10	
	
	Point = Buff;
//	PulseCumPt = PulseCum;

/*
//	for( i=0;i<MDUnitNum*5;i++ )
	for( i=0;i<MDUnitNum*2;i++ )		
	{
		*(PulseCumPt + i) = 0;
	}	
	
//	FreeNoData = SM.FeeNo;
//	FreeNoData <<= 12;
	
	SM.MD_BufAds++;
	if( SM.MD_BufAds >= 60 ) SM.MD_BufAds = 0;
	for( i=0;i<MDUnitNum;i++ )
	{
//		*MDPara[i].MDCum |= FreeNoData;

		#if ( Threephase == YesCheck ) //三相				
				E2P_WECData( MDPara[i].MDBufAds + SM.MD_BufAds * 3, (unsigned char*)MDPara[i].MDCum, 2 );
		#elif ( SinglePhase == YesCheck )
//				E2P_WData( MDPara[i].MDBufAds + SM.MD_BufAds * 3, (unsigned char*)MDPara[i].MDCum, 2 );
				E2P_WECData( MDPara[i].MDBufAds + SM.MD_BufAds * 3, (unsigned char*)MDPara[i].MDCum, 2 );		
		#endif	
//		E2P_WECData( MDPara[i].MDBufAds + SM.MD_BufAds * 3, (unsigned char*)MDPara[i].MDCum, 2 );

		*MDPara[i].MDCum = 0;
	}	
	

	SM.MD_Cunt++;
	SM.MDPMinCT++;
	SM.MD_CuntT++;
	
//	if( SM.MDPMinCT < Para.RMaxDT ) return 0;
	if( BCD_Byte(Clk.Min[0]) % 15 ) return 0;		//固定每15分钟算一次

//	if(((Flag.ClrFlag & F_MD_EN) != F_MD_EN)&&(BCD_Byte(Clk.Min[0]) % 15)) 
//	if(((Flag.ClrFlag & F_MD_EN) != F_MD_EN)&&((Flag.ClrFlag & F_MDSave_EN) != F_MDSave_EN)&&(BCD_Byte(Clk.Min[0]) % 15)) 		
//	return 0;		//固定每15分钟算一次
			
	SM.MDPMinCT = 0;
	
	if( SM.MD_Cunt > Para.RMaxT ) SM.MD_Cunt = Para.RMaxT;
	if( SM.MD_CuntT > Para.RMaxT ) SM.MD_CuntT = Para.RMaxT;
		
	for( i=0;i<MDUnitNum;i++ )
	{
		for( j=0;j<SM.MD_Cunt;j++)
		{
//			if( SM.MD_BufAds < j ) k = SM.MD_BufAds + 60; 
//			else k = SM.MD_BufAds;
//			E2P_RData( Point, MDPara[i].MDBufAds + ( k - j )*3 , 2);
//			k = *(Point+1)*256 + *Point;
//			FreeNoData = k;
//			k &=~ 0xF000;
//			FreeNoData >>= 12;
//			if((FreeNoData > 0) && (FreeNoData < 5))
//				*(PulseCumPt + i*2 + FreeNoData ) += k;
			
//			*(PulseCumPt + i*2 ) += k;
////			if( SM.MD_CuntT > j ) *(PulseCumPt + i*2 + 1 ) += k;


			if( SM.MD_BufAds < j ) k = SM.MD_BufAds + 60; 
			else k = SM.MD_BufAds;

		#if ( Threephase == YesCheck ) //三相				
				E2P_RECData( Point, MDPara[i].MDBufAds + ( k - j )*3 , 2);
		#elif ( SinglePhase == YesCheck )
//				E2P_RData( Point, MDPara[i].MDBufAds + ( k - j )*3 , 2);
				E2P_RECData( Point, MDPara[i].MDBufAds + ( k - j )*3 , 2);		
		#endif	
			
//			E2P_RECData( Point, MDPara[i].MDBufAds + ( k - j )*3 , 2);

			
			k = *(Point+1)*256 + *Point;
			*(PulseCumPt + i*2 ) += k;
			if( SM.MD_CuntT > j ) *(PulseCumPt + i*2 + 1 ) += k;

		}		
	}
	SM.MD_Cunt = 0;	
*/




//	SM.MD_Cunt++;
//	SM.MDPMinCT++;
//	SM.MD_CuntT++;
	
//	if( SM.MDPMinCT < Para.RMaxDT ) return 0;
	if( BCD_Byte(Clk.Min[0]) % 15 ) return 0;		//固定每15分钟算一次

	E2P_WData( MDT_Pp0 , &Clk.Min[0], 5);		//写需量发生时间
	
	for(i=0;i<MDUnitNum;i++)
	{
		j = CMon_MD_Pp0 + i*4;
		k = CMon_MDT_Pp0 + i*6;
/*
		for( m=0;m<5;m++)
		{
//			Long_BCD4( Point, ((unsigned long)*(PulseCumPt + 2*i + m) * SM.MD_60T * 100 ) / (PS32/10) );		
			RAM_Fill( Point, 4 );																		//V10
			Value1 = ((unsigned long)*(PulseCumPt + 2*i + m) * SM.MD_60T * 100 ) / (PS32/10);				//V10																					//V10
			Long_BCD4( Point, Value1 );
			
//			if( m == 0 )	MD_Comp( Point, j , k );
//			else MD_Comp( Point, j + (SM.FeeNo * 4), k + (SM.FeeNo * 6) );
			MD_Comp( Point, j + (m * 4), k + (m * 6) );	
		}
*/		

//		m = 0;
//		for( m=0;m<5;m++)
//		{
//			Long_BCD4( Point, ((unsigned long)*(PulseCumPt + 2*i + m) * SM.MD_60T * 100 ) / (PS32/10) );		
			RAM_Fill( Point, 4 );																		//V10
//			Value1 = ((unsigned long)*(PulseCumPt + 2*i + m) * SM.MD_60T * 100 ) / (PS32/10);				//V10																					//V10
			Value1 = ((*MDPara[i].MDCum * SM.MD_60T * 100 ) / (PS32/10));				//V10	
			*MDPara[i].MDCum = 0;
			Long_BCD4( Point, Value1 );
			
//			if( m == 0 )	MD_Comp( Point, j , k );
//			else MD_Comp( Point, j + (SM.FeeNo * 4), k + (SM.FeeNo * 6) );
//			MD_Comp( Point, j + (m * 4), k + (m * 6) );	
			MD_Comp( Point, j , k );
//		}
		
/*		
		j = CMon_MD_Pp0 + i*4;			//无费率需量
		k = CMon_MDT_Pp0 + i*5;
		m = 0;
//		Long_BCD4( Point, ((unsigned long)*(PulseCumPt + 2*i + m) * SM.MD_60T * 100 ) / PS32 );	
		RAM_Fill( Point, 4 );																		//V10
		Value1 = ((unsigned long)*(PulseCumPt + 2*i + m) * SM.MD_60T * 100 ) / (PS32/10);				//V10
																							//V10
		Long_BCD4( Point, Value1 );																	//V10		
			
		MD_Comp( Point, j , k );
*/		
		}	
	
//		if((Flag.ClrFlag & F_MD_EN) == F_MD_EN)		
//		Flag.ClrFlag &=~ F_MD_EN;
		
//		if((Flag.ClrFlag & F_MDSave_EN) == F_MDSave_EN)		
//		Flag.ClrFlag &=~ F_MDSave_EN;		
		
	return 0;
}	

void MD_Comp( unsigned char* PointSrc, short MD_Ads, short MDT_Ads )
{
	unsigned char Buff[4];
	unsigned char* Point;

	Point = Buff;
	
#if ( Threephase == YesCheck ) //三相		

//	if(MD_Ads >= CMon_MD_Pp0P)	
//	{
//		E2P_WECData( MD_Ads , PointSrc, 3);				//写最大需量
//		E2P_WECData( MDT_Ads , &Clk.Min[0], 5);		//写需量发生时间
//	}
//	else
//	{
//		E2P_RECData( Point, MD_Ads , 3);
//	
//	if( Data_Comp( PointSrc, Point, 3 ) == 1)
//	{
//		E2P_WECData( MD_Ads , PointSrc, 3);				//写最大需量
//		E2P_WECData( MDT_Ads , &Clk.Min[0], 5);		//写需量发生时间
//	}	
//	}
	E2P_RECData( Point, MD_Ads , 3);
	if( Data_Comp( PointSrc, Point, 3 ) == 1)
	{
		E2P_WECData( MD_Ads , PointSrc, 3);				//写最大需量
		E2P_WECData( MDT_Ads , &Clk.Min[0], 5);		//写需量发生时间
	}
	
#elif ( SinglePhase == YesCheck )
	E2P_RECData( Point, MD_Ads , 3);
	if( Data_Comp( PointSrc, Point, 3 ) == 1)
	{
		E2P_WECData( MD_Ads , PointSrc, 3);				//写最大需量
		E2P_WECData( MDT_Ads , &Clk.Min[0], 5);		//写需量发生时间
	}	
	
#endif		
	
}

/*

int MD_Comp( unsigned char* PointSrc, int MD_Ads, int MDT_Ads )	
{
	unsigned char Buff[4],MDZ_BUFF[4],MDHour_BUFF[4],Date_Buff[5];
	unsigned char* Point;
	unsigned char* PointHour;
	int i;

	Point = Buff;
	PointHour = MDHour_BUFF;
	
	RAM_Write(Date_Buff,Clk.Min,5);
	if(Clk.Min[0] <15)
	{	
		RtcSub1Hour(Date_Buff+1);
		*Date_Buff = 0x45;
	}
	else *Date_Buff = Byte_BCD(BCD_Byte(*Date_Buff) - 15);
	
	E2P_RData( PointHour, CHour_MD_Pp0 , 3);
	if( Data_Comp( PointSrc, PointHour, 3 ) == 1)
	{
		E2P_WData( CHour_MD_Pp0 , PointSrc, 3);				//写最大需量
		E2P_WData( CHour_MDT_Pp0 , Date_Buff, 5);
		RAM_Write(PointHour,PointSrc,3);
	}
	
	E2P_RData( Point, MD_Ads , 3);
	if( Data_Comp( PointHour, Point, 3 ) == 1)
	{
		E2P_WData( MD_Ads , PointHour, 3);				//写最大需量
		E2P_WData( MDT_Ads , Date_Buff, 5);		//写需量发生时间
	}	
	
	*Point = 0;
	E2P_RData( Point + 1, MD_Over_Valve , 2);
	if(Data_Comp( PointHour, Point, 3 ) == 1)
	{
		if((!(Flag.MDState & F_MDOVER)) && ((*(Point + 1) != 0) || (*(Point + 2) != 0)))
		{
			E2P_RData( Point, CMon_MD_Cnt , 2);
			_BCD2INC(Point);
			E2P_WData( CMon_MD_Cnt , Point, 2);
			Flag.MDState |= F_MDOVER;
		}
		
		if(Clk.Min[0] != 0) return 0;
		for(i=0;i<10;i++)
		{
			E2P_RData( Point, CMon_MD_Top10 - i*4 , 3);
			if( Data_Comp( PointHour, Point, 3 ) == -1)
			{
				if(i == 0 )break;
				E2P_DataMove( CMon_MD_Top10 - (i-1)*4, CHour_MD_Pp0,3, 1 );
				E2P_DataMove( CMon_MDT_Top10 - (i-1)*6, CHour_MDT_Pp0,5, 1 );	
				break;
				
			}else if(i < 9 )
				{
		
					E2P_DataMove( CMon_MD_Top10 - i*4, CMon_MD_Top10 - (i + 1)*4,3, 1 );
					E2P_DataMove( CMon_MDT_Top10 - i*6, CMon_MDT_Top10 - (i+1)*6 ,5, 1 );
				}else{
					E2P_DataMove( CMon_MD_Top10 - i*4, CHour_MD_Pp0,3, 1 );
					E2P_DataMove( CMon_MDT_Top10 - i*6, CHour_MDT_Pp0,5, 1 );
				}	
		}
		
		RAM_Fill(MDZ_BUFF,4);
		for(i=0;i<10;i++)
		{
			*Point = 0;
			E2P_RData( Point + 1, MD_Over_Valve , 2);
			E2P_RData( PointHour, CMon_MD_Top10 - i*4 , 3);
			if( Data_Comp( PointHour, Point, 3 ) == 1)
			{
				_BCD4SUB(PointHour, Point);
//			RAM_Write(Point,PointHour,3);
//			*(Point + 3) = 0;	
				*(PointHour + 3) = 0;		 
//			E2P_RData( MDZ_BUFF, CMon_MD_Ppz , 4);
				_BCD4ADD(MDZ_BUFF, PointHour);
//			E2P_WData( CMon_MD_Ppz , MDZ_BUFF, 4);
			}
		
		}
		E2P_WData( CMon_MD_Ppz , MDZ_BUFF, 4);
		Flag.MDState &=~ F_MDOVER;
		
		
	}else Flag.MDState &=~ F_MDOVER;
	if(Clk.Min[0] != 0) return 0;	
	Clr_E2PData( CHour_MD_Pp0 , 3,1);				//写最大需量
	Clr_E2PData( CHour_MDT_Pp0 , 5,1);		//写需量发生时间	
	Flag.Power &=~ F_EDMeasure;	
	return 0;	
}*/
		


/*
void PhaseEcMease( void )					//计算分相电量
{
	unsigned char Buff[4];
	unsigned char* Point;
	unsigned char* Pulse_Buf; 
	int i;
	
	Point = Buff;
//	Pulse_Buf = &SM.Pulse_CumPpA;
	Pulse_Buf = &SM.PL_CumPpA;
	
	for( i=0;i<3;i++ )
	{
		Read_ATTValue( ATPA + i , Point );
		if( *Point > 0x99 ) *Point = 0;
		if( *Point == 0 ) continue;
		*Point = BCD_Byte(*Point);
		switch( Read_ATTValue( ATPWPA + i , Point+1 ) )
		{
			case 1:	*(Pulse_Buf + 3 + i ) += *Point;
					if ( Para.RPJLmode !=0 ) break;		//正反向合计？ 	
			case 0: *(Pulse_Buf + i) += *Point;
			default:break;
		}	
	}	
}
*/
/*
视在电量的计算：
1.每秒钟读取一次总的视在功率。并累加。
	（W1+W2+W3+... ）x (1/3600) 单位：Wh
	直到累加到（1/脉冲常数）度即 (1000/脉冲常数)x1 Wh时相当于有一电量脉冲，累计进脉冲计数器。
2.两边同乘以3600得出当（W1+W2+W3+...）== 1000 x 3600 / 脉冲常数   时产生一个脉冲。
3.因Read_ATTValue( ATPWSZ, Point) 读回来的数字为了显示方便，
  已经乘了10，系数改为1000 x 3600 x 10 / 脉冲常数。	
*/
/*
void SMEcMease( void )					//计算视在电量
{
	unsigned char Buff[4];
	unsigned char* Point;
	
	Point = Buff;
	
	if( SM.TestDisCnt != 0 ) return;
	Read_ATTValue( ATPWSZ, Point);
	SM.SMEcSum += BCD3_Long( Point );	
	//if( SM.SMEcSum >= (unsigned long)SMEcConst )
	while( SM.SMEcSum >= (unsigned long)SMEcConst )
	{
		SM.SMEcSum -= (unsigned long)SMEcConst;
		SM.SPulse_Cum++;	
	}	 
}	
*/





