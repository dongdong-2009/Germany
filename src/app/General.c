#include "TypeMeter.h"
#include "TypeE2p.h"
//#include "msp430f6736.h"
#include "Measure.h"
#include "Type.h"
#include "Data.h"
#include "General.h"
#include "Mem.h"
#include "Port.h"
#include "Display.h"
#include "RsComm.h"
#include "Initial.h"
#include "Time.h"
#include "Power.h"
#include <Includes.h>

//**********************************************************************
// Delay
//**********************************************************************
void Delay(unsigned short i)
{
//	int i = 1000;
	while( i > 0)
	{
		i--;	
	}	
}
	
/**********************************************************************
	Calculate the checksum Of Data in RAM
**********************************************************************/
unsigned char ChkNum( unsigned char *Ptr, short Len )
{
	unsigned char Num = 0xA5;
   
   	while( Len > 0 )
   	{
    	Num += *Ptr++;
      	Len--;
   	}
   	return Num;
}

unsigned short ChkNumShort( unsigned short *Ptr, short Len )
{
	unsigned short Num = 0xA5A5;
   
   	while( Len > 0 )
   	{
    	Num += *Ptr++;
      	Len--;
   	}
   	return Num;
}

unsigned char ChkNumAdd( unsigned char *Ptr, short Len )
{
	unsigned char Num = 0x0;
   
   	while( Len > 0 )
   	{
    	Num += *Ptr++;
      	Len--;
   	}
   	return Num;
}

//**********************************************************************
// turn byte data to BCD data
//**********************************************************************
unsigned char Byte_BCD(unsigned char Data)
{
   if (Data>=99) return 0x99;
   return( Data/10*0x10 + Data%10 );
}

//**********************************************************************
// turn word data to BCD data
//**********************************************************************
void Word_BCD(unsigned char *Ptr, unsigned short Data)
{
   if (Data>=9999){
      *(Ptr+1) = 0x99;
      *Ptr = 0x99;
      return;
   }

   *(Ptr+1) = Byte_BCD( (unsigned char)(Data/100) );
   *Ptr = Byte_BCD( (unsigned char)(Data%100) );
}

//**********************************************************************
// turn long data to BCD3 data
//**********************************************************************
/*
void Long_BCD3(unsigned char *Ptr, unsigned long Data)
{
	if (Data>=999999){
      	*(Ptr+2) = 0x99;
      	*(Ptr+1) = 0x99;
      	*Ptr = 0x99;
      	return;
   	}
   	*(Ptr+2) = Data/100000*0x10 + Data/10000;
   	Word_BCD(Ptr, (unsigned int)(Data%10000));
}
*/

//**********************************************************************
// turn long data to BCD4 data
//**********************************************************************
void Long_BCD4(unsigned char *Ptr, unsigned long Data)
{
	if (Data>=99999999){
      	*(Ptr+3) = 0x99;
      	*(Ptr+2) = 0x99;
      	*(Ptr+1) = 0x99;
      	*Ptr = 0x99;
      	return;
   	}
	Word_BCD(Ptr+2, Data/10000);
	Word_BCD(Ptr, Data%10000);
}

//**********************************************************************
// 
//**********************************************************************
short IsBCD(unsigned char Data)
{
	if(((( Data >> 4) & 0x0f) > 9 )||( ( Data & 0x0f ) > 9 )) return 1;
	return 0;
}
 
//**********************************************************************
// turn BCD data to byte data
//**********************************************************************
unsigned char BCD_Byte(unsigned char Data)
{
   return(((Data>>4)&0x0f)*10+(Data&0x0f));
}

//**********************************************************************
// turn BCD2 data to word data
//**********************************************************************
unsigned short BCD2_Word(unsigned char *Ptr)
{
   return(  (short)BCD_Byte(*Ptr)+
            (short)BCD_Byte(*(Ptr+1))*100 );
}

//**********************************************************************
// turn BCD3 data to word data
//**********************************************************************
void Long_BCD3(unsigned char *Ptr, unsigned long Data)
{
	if (Data>=999999){
      	*(Ptr+2) = 0x99;
      	*(Ptr+1) = 0x99;
      	*Ptr = 0x99;
      	return;
   	}
//   	*(Ptr+2) = Data/100000*0x10 + Data/10000;
	*(Ptr+2) = Byte_BCD(Data/10000);		//13.01.10
   	Word_BCD(Ptr, (unsigned short)(Data%10000));
}

//**********************************************************************
// turn BCD4 data to word data
//**********************************************************************
unsigned long BCD4_Long(unsigned char *Ptr)
{
   return(  (long)BCD_Byte(*Ptr)+
            (long)BCD_Byte(*(Ptr+1))*100+
            (long)BCD_Byte(*(Ptr+2))*10000+
            (long)BCD_Byte(*(Ptr+3))*1000000 );
}


//**********************************************************************
// BCD2 ADD BCD5 to BCD5 data
//**********************************************************************
void _BCD2TO5ADD(unsigned char *dest,unsigned char *Ptr) 
{
//	unsigned long int data1;
	unsigned long long data1;
        unsigned short Buff_data = 0,data2;
        short i;//unsigned char i;
        for(i=0;i<2;i++)
        {
        	data1 = (long)BCD2_Word(dest+2*i) + (long)BCD2_Word(Ptr)*(1-i) + (long)Buff_data;
        	Buff_data = 0;
        	if(data1 > 9999)
        	{	
        		Buff_data =data1 / 10000;
        		data1 -= 10000;         	
        	}   
        	Word_BCD(dest+2*i,(unsigned short)data1);
        	if(Buff_data == 0) return;
        }
        data2 = (unsigned short)BCD_Byte(*(dest+4)) + (unsigned short)Buff_data;
        if(data2 > 99)
        	data2 = 0;
    	*(dest+2*i) = Byte_BCD((unsigned char)data2);
	
}

void _BCD6INC(unsigned char *dest) 
{
	unsigned long data1;
	unsigned short Buff_data;
	
	data1 = (long)BCD2_Word(dest) + 1;
	Buff_data=0;
	if(data1 > 9999)
  {	
		Buff_data = data1 / 10000;
    data1 -= 10000;         	
	}
	Word_BCD(dest,(unsigned short)data1);
	
	data1 = (long)BCD2_Word(dest+2)+Buff_data;
	Buff_data=0;
	if(data1 > 9999)
  {	
		Buff_data = data1 / 10000;
    data1 -= 10000;         	
	}
	Word_BCD(dest+2,(unsigned short)data1);
	
	data1 = (long)BCD2_Word(dest+4)+Buff_data;
	if(data1 > 9999)
	{
		data1=0;
	}
	Word_BCD(dest+4,(unsigned short)data1);
}

//**********************************************************************
// BCD1 ADD 1 to BCD1 data
//**********************************************************************
void _BCD1INC(unsigned char *dest)
{
	unsigned char Data;
	Data=BCD_Byte(*dest);
	if(Data<99)*dest=Byte_BCD(Data+1);
	else *dest=0;

}

void _BCD1DEC(unsigned char *dest)
{
	unsigned char Data;
	Data=BCD_Byte(*dest);
	if(Data<100)*dest=Byte_BCD(Data-1);
	else *dest=0;

}

void _BCD2INC(unsigned char *dest)
{
	unsigned short Data;
	Data=BCD2_Word(dest);
	if(Data<9999)Word_BCD(dest,Data+1);
	else *dest=0;

}

//**********************************************************************
void _BCD12_ASC3132(unsigned char *Dest, unsigned char *Src, unsigned char Lenth)
{
	unsigned char TempAcc;
	
//	Src += Lenth;
//	Src--;
	while(Lenth>0)
	{	TempAcc = *Src;
		TempAcc >>= 4;
		if(TempAcc<10)	
			TempAcc += 0x30;
		else  TempAcc += 0x37;
		*Dest = TempAcc;
		Dest++;
		
		TempAcc = *Src;
		TempAcc	&= 0x0f;
		if(TempAcc<10)	
			TempAcc += 0x30;
		else  TempAcc += 0x37;
		*Dest = TempAcc;
		Dest++;
		
		Src++;
		Lenth--;	
	}
}

//**********************************************************************
void _BCD_ASC(unsigned char *Dest, unsigned char *Src, unsigned char Lenth)
{
	unsigned char TempAcc;
	
	Src += Lenth;
	Src--;
	while(Lenth>0)
	{	TempAcc = *Src;
		TempAcc >>= 4;
		if(TempAcc<10)	
			TempAcc += 0x30;
		else  TempAcc += 0x37;
		*Dest = TempAcc;
		Dest++;
		TempAcc = *Src;
		TempAcc	&= 0x0f;
		if(TempAcc<10)	
			TempAcc += 0x30;
		else  TempAcc += 0x37;
		*Dest = TempAcc;
		Dest++;
		
		Src--;
		Lenth--;	
	}
}
//**********************************************************************
	
void _ASC_BCD(unsigned char *Dest, unsigned char *Src, unsigned char Lenth)
{
	unsigned char TempL,TempH;
	
	TempL = (Lenth<<1);
	Src += (TempL-1);
	while(Lenth>0)
	{
//		Src -= 2;
		TempL = *Src;
		if(TempL>0x40)
			TempL -= 0x37;
		TempL &=0x0f;	
//		*Dest = Temp;	
		Src--;
		TempH = *Src;
		if(TempH>0x40)
			TempH -= 0x37;
		TempH &=0x0f;	
		TempH = (TempH<<4); 
		TempH |= TempL;
		*Dest = TempH;		
		Src--;
		Dest++;
		Lenth--;
	}
}



//------------------------------
unsigned char CmpSdSolution(unsigned char*Cmp1,unsigned char*Cmp2)
{
	unsigned char i;
//	for(i=0;i<8;i++)
	for(i=0;i<4;i++)		
		{if(*Cmp1 != *Cmp2)
			return(1);
		Cmp1++;
		Cmp2++;  	
		}	
	return(0);	
}

unsigned char GetSeasonNo(unsigned char*Point)
{
	unsigned char temp;
	if(Data_Comp(&Clk.Hour[0],Point+1,3)>=0)
		temp=*(Point);	//取最后一个时区
	else if(Data_Comp(&Clk.Hour[0],Point+5,3)>=0)
		temp=*(Point+4);	//取上一个时区
	else if(Data_Comp(&Clk.Hour[0],Point+9,3)>=0)
		temp=*(Point+4+4);	//取上一个时区
	else if(Data_Comp(&Clk.Hour[0],Point+13,3)>=0)
		temp=*(Point+4+8);	//取上一个时区
	else
//		temp=*(Point+12);	//取上一个时区
		temp=*(Point);	//取上一个时区
	return(temp);		
		
}	

//-------------------
unsigned char GetComplexDaySdb(unsigned char ComplexSoluN0)
{
	unsigned char Buff[40],i,j,*Point,TempAcc,*Point2;	
	unsigned short TempAddr;
	
	
	return(*Point); //返回日时段表	
}	


/*
short GetDaySeg(void)
{
	unsigned char Buff[40];
	unsigned char* Point;
	unsigned char Temp,TempAcc,i;
	unsigned short TempAddr;
	
	Point = Buff;
	SM.RollItemPt=0;
		
//	E2P_RData( Point,CurrRunSdName,16); 
	E2P_RData( Point,CurrRunSdName,8); 	
	TempAcc=GetComplexDaySdb(2) - 1;
	TempAddr=Complexsd[2].DaySdb1;
	TempAddr += TempAcc*37;//	TempAcc*25;
	E2P_RData((unsigned char*)&Para.RelaySeg[0],TempAddr, 36 );//relay
		
	for(i=0;i<2;i++)
		{
//		E2P_RData( &Buff[20],Complexsd[i].SolutionName,16); 	
		E2P_RData( &Buff[20],Complexsd[i].SolutionName,8); 			
		Temp = CmpSdSolution(Buff,&Buff[20]);
		if(	Temp==0)
			{TempAcc=GetComplexDaySdb(i) - 1;
			TempAddr=Complexsd[i].DaySdb1;
//			E2P_RData((unsigned char*)&Para.RelaySeg[0],TempAddr+185, 36 );	//relay
			TempAddr += TempAcc*37;//	TempAcc*25;
			E2P_RData((unsigned char*)&Para.Seg[0],TempAddr, 36 );//E2P_RData((unsigned char*)&Para.Seg[0],TempAddr, 24 );	
			return(0);
			}
		SM.RollItemPt++;	//轮显项选择指针 	
		}
		SM.RollItemPt++;
	for(i=0;i<9;i++)
		{
//		E2P_RData( &Buff[20],Simplesd[i].SolutionName,16); 		
		E2P_RData( &Buff[20],Simplesd[i].SolutionName,8); 				
		Temp = CmpSdSolution(Buff,&Buff[20]);
		if(Temp==0)
			{TempAddr=Simplesd[i].DaySdb1;
//			TempAddr+=	TempAcc*25;
			E2P_RData((unsigned char*)&Para.Seg[0],TempAddr, 36 );//E2P_RData((unsigned char*)&Para.Seg[0],TempAddr, 24 );
			return(0);	
			}	
		SM.RollItemPt++;	//轮显项选择指针 	
		}
	SM.RollItemPt=0;	//默认轮显项	
	return(-1);		
}
*/


short GetDaySeg(void)
{

	return(-1);		
}

void GetFeeNo(void)
{

}	





#if (RelayHW == YesCheck)	
void WorkRelay(unsigned char relayNo,unsigned char Mode)
{
	switch(relayNo)
	{
#if (HWVer3P == NoCheck)		
		case 1:			
			POUT_RELAY1OFF &=~ (P_RELAY1OFF + P_RELAY1ON);
			if(Mode == 2)
			{	
				POUT_RELAY1OFF &=~ P_RELAY1ON;
				Flag.AlarmFlg[0] |= F_AlarmRelay;
			}else{
				POUT_RELAY1OFF &=~ P_RELAY1OFF;	
				Flag.AlarmFlg[0] &=~ F_AlarmRelay;
			}
			SM.Relay1Time = 150;	
			break;
//		case 2:
//				P1OUT &=~ P_RELAY2ON;
//				P3OUT &=~ P_RELAY2OFF;
//			if(Mode == 2)
//				P1OUT |= P_RELAY2ON;
//			else
//				P3OUT |= P_RELAY2OFF;
//			SM.Relay2Time = 150;
//			break;
#else
		case 1:			
			POUT_RELAY1OFF |= (P_RELAY1OFF + P_RELAY1ON);
			if(Mode == 2)
			{	
				POUT_RELAY1OFF &=~ P_RELAY1ON;
				Flag.AlarmFlg[0] |= F_AlarmRelay;
			}else{
				POUT_RELAY1OFF &=~ P_RELAY1OFF;	
				Flag.AlarmFlg[0] &=~ F_AlarmRelay;
			}
			SM.Relay1Time = 150;	
			break;
//		case 2:
//			P1OUT |= P_RELAY2ON;
//			P3OUT |= P_RELAY2OFF ;
//			if(Mode == 2)
//				P1OUT &=~ P_RELAY2ON;
//			else
//				P3OUT &=~ P_RELAY2OFF;
//			SM.Relay2Time = 150;
//			break;
		
#endif		
		default: break;			
	}	
}
void GetRelayState(void)
{
	unsigned char Temp;
//	int i;
	if(( Flag.Power & F_PwrUp ) != 0 )
	{
		Temp = GetNo( (unsigned char*)&Para.RelaySeg[0], (unsigned char*)&Clk.Min[0], 12 );
		
		if( Temp != 1 ) Temp = 2;
		if( SM.RelayState != Temp )
		{	
			WorkRelay(1,Temp);
			WorkRelay(2,Temp);
		}
		SM.RelayState = Temp;
	}
}
#endif
short GetLcdState(void)
{
	return 0;
}	


/*
void CalcuParameterBCC(unsigned char *Point,unsigned char Ptr,unsigned char Len)
{
	unsigned char i,i_bits;	
	unsigned char carry;
	for(i=0;i<Len;i++)	
	{
		Comm.ParameterBcc[Ptr] ^= *Point;
		Point++;
//		if((Comm.ParameterBcc[Ptr] & 0x01) == 0x01)
//		{	
//			Comm.ParameterBcc[Ptr] += 2 * Len + 0x95;
//			Comm.ParameterBcc[Ptr] ^= 0xA5;
//		}
		for (i_bits = 0; i_bits < 8; i_bits++)
        {
			carry = Comm.ParameterBcc[Ptr] & 1;
			Comm.ParameterBcc[Ptr] = Comm.ParameterBcc[Ptr] / 2;
			if (carry == 1)
            {
            	Comm.ParameterBcc[Ptr] = Comm.ParameterBcc[Ptr] ^ 0x84;
			}
        }
	}
}
*/

void ParameterBCC(void)
{

	
}

//void MinInc(unsigned int E2Paddress)
void MinInc(unsigned short E2Paddress)	
{
	unsigned char Buff[8];
	unsigned char* Point;
	Point = Buff;
	
	E2P_RData( Point,E2Paddress, 5);
	_BCD1INC(Point);
	if( *Point >= 0x60 )
	{				// Minute
		*Point = 0;
		_BCD1INC(Point + 1);
		if( *(Point + 1) >= 0x24 )
		{			// Hour
			*(Point + 1) = 0;
			_BCD1INC(Point + 2);
			if( *(Point + 2) >= 0x30 )
			{		// DAY
				*(Point + 2) = 0;
				_BCD1INC(Point + 3);
				if(*(Point + 3) >= 0x12)
				{		//month
					*(Point + 3) = 0;
					_BCD1INC(Point + 4);
				}		
			}
		}
	}
	E2P_WData( E2Paddress , Point,5);
	
}


void OperationalTimeInc(void)
{
}



void RpaInit(void)			//V2
{
//	SetConstPara();
	//InitPara();
#if ( Threephase == YesCheck ) //三相
#if( MEASCHIP == RN8207 )	
	InitMeasPara();
#endif
#endif		
}	

#if ( Threephase == YesCheck ) //三相
void InitMeasPara(void)
{	
}
#endif

//const unsigned char LcdMTab[]=
//{0x88,0x47,0x67,0x87,0x57,0x77,0x97,0x17,0x18,0x19,0x1A,0x27,0x28,0x29,0x2A,0x63,0x60,0xC0,0xC1,0xC2,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

//void RpaInit(void)
#if 1
void InitPara(void)			//V2
{
	unsigned char Buff[14];
	unsigned char* Point;
	
	Point = Buff;
	E2P_RData( Point,E2P_DisDataSetFlag, 1 );
	SM.ECLedModeCnt=*Point;
}
#endif
unsigned char GetNo(unsigned char* Point, unsigned char* Source, short ItemNums)
{
	unsigned char Temp;
	short i,j;
	
	Temp = *(Point+(ItemNums-1)*3);

	for( i=ItemNums;i>0;i-- )
	{
		j = (i-1)*3;
		if( Data_Comp( Source, Point+j+1, 2) >= 0 )
		{
			Temp = *(Point+j);	
			break;				
		}	
	}
	return Temp;
}

void IncBatteryWorkTime( void )
{
	 
}

void IncYearMonth( unsigned char* TMon )
{
	_BCD1INC(TMon);			//测试时间月加1
	if( *TMon > 0x12 )
	{
		*TMon = 1; 			//月为1月
		_BCD1INC(TMon+1);	//年加1
	}	 
}

short Mon_Save(void)
{
	unsigned char Buff[6],Write_Buff[6];//Write_Buff[65];
	unsigned char* Point;
	short Temp,Temp_Mon,Last_Mon;
//	unsigned int i;
//	unsigned long Addr;
	
	Point = Buff;
	
	E2P_RData( Point, Last_Mon_Tm, 2 );
	E2P_RData( Point+2, ESave_Day, 3 );
	*(Point+5) = *(Point+2);
	*(Point+2) = *(Point+4);
	*(Point+4) = *(Point+5);
//	*(Point+4) = *(Point+5);

	*(Point+1) = BCD_Byte( *(Point+1) );
	*(Point+4) = BCD_Byte( *(Point+4) );
	if(*(Point+4) == 0)return 0;
	Temp_Mon = (short)BCD_Byte( Clk.Mon[0] );
//	Last_Mon = (int)BCD_Byte( *Point );
	Last_Mon =  *(Point+1);
	
	Temp = Temp_Mon - Last_Mon;//Temp = Temp_Mon - *(Point+1);
	if( Temp < 0 )  Temp += 12;
	
	Write_Buff[0] = 0x00;
	Write_Buff[1] = 0x00;
	RAM_Write(Write_Buff+2,Point+2,2 );
	RAM_Write(Write_Buff+4,Clk.Mon,2 );	
		
//	if( Temp < 2)
	if(( Temp < *(Point+4)+1) ||(((Temp_Mon/ *(Point+4) -Last_Mon/ *(Point+4)) > 0) && ((Temp_Mon/ *(Point+4)) != 0)   ))	
	{
		switch(*(Point+4))
		{
//			case 1:
//				break;
			case 2:
				if(Temp_Mon%2 )return 0;
			
				break;
			case 3:
				if(Temp_Mon%3 )return 0;
				break;
			case 6:
				if(Temp_Mon%6 )return 0;
				break;	
			default: break;
		}
		if( Data_Comp( ( unsigned char*)(Point+2), ( unsigned char*)&Clk.Hour[0], 2 ) == 1 ) return 0;
		if( Temp == 0 )
		{
			if( *Point >= *( Point + 3 ) ) return 0;	
		}			
	}
	else {
		if(Temp_Mon > *(Point+4))Write_Buff[4] = Byte_BCD(Last_Mon + *(Point+4));//Byte_BCD(Temp_Mon - *(Point+4));
		else {
			Write_Buff[4] = Byte_BCD(12 + Temp_Mon - *(Point+4));
			_BCD1DEC(Write_Buff + 5);
		}
	}

//	if(Temp_Mon% *(Point+4))
//	{
//		if(Temp_Mon > (Temp_Mon% *(Point+4)))Write_Buff[4] = Byte_BCD(Temp_Mon - Temp_Mon% *(Point+4));
//		else {
//			Write_Buff[4] = Byte_BCD(12 + Temp_Mon - Temp_Mon% *(Point+4));
//			_BCD1DEC(Write_Buff + 5);
//		}	
//	}
//	
//	if(*(Point+2) == 0  )
//	{
//		RtcSub1Hour(Write_Buff + 2);
//	}else _BCD1DEC(Write_Buff + 2);	
//	MonData_Save(Write_Buff);
	MonData_Save(&Clk.Sec[0]);

//	E2P_RData( Point, JsCount , 1);
//	_BCD1INC( Point );
//	E2P_WData( JsCount , Point, 1);
	
	E2P_WData( Last_Mon_Tm, &Clk.Day[0], 2 );
//	MD_Rest(0);	

	return 0;
}

void MonData_Save(unsigned char* Date)
{

}

///  Mon 为读取月份， Length 为读取长度， stata 为读取位置， 数据未记录返回全0
short Mon_Read(unsigned char* Ram_Addr,unsigned char Mon,unsigned char length,unsigned char stata)
{
	unsigned char Buff[6],Read_Buff[100];
	unsigned char* Point;
//	unsigned long Flash_Addr;

/*
#if ( FlashAT45DB == YesCheck )
#else
	unsigned long MonCurAdr;
#endif	
	
	Point = Buff;
	RAM_Fill(Ram_Addr, length);
	E2P_RData( Buff, LastEC_Pt , 2);
	if(Mon > 0) Mon -= 1;
	if((*(Point+1) == 0 ) &&(*Point == 0 )) return 0;	
//	if(Mon > *Point) 
	if(Mon >= *Point)
	{
		if(*(Point+1) == 0 ) return 0;
		*Point += 16 - Mon;
		if(*Point >= 16)*Point -= 16;
	}
	else 	*Point -=  Mon;
//	Flash_Addr = (*Point)* MONLENGTH + Mon_Data_Addr + stata;
#if (FlashChip == YesCheck)

#if ( FlashAT45DB == YesCheck )
		Flash_Addr = (*Point)* MONLENGTH + Mon_Data_Addr + stata;
		DataFlash_Read( Ram_Addr, Flash_Addr , length );	
#else
//		Flash_Addr = (*Point);
		Flash_Addr = (unsigned long)Mon *MONLENGTH ;
		GetGLoadCurAdr( &MonCurAdr ,1);
		if(( Flash_Addr + GeneralMonCurveSta ) > MonCurAdr )
		{
			Flash_Addr = GeneralMonCurveEnd - GeneralMonCurveSta + MonCurAdr - Flash_Addr;	
		}	
		else Flash_Addr = MonCurAdr - Flash_Addr;
		Flash_Addr += stata;
		if( Flash_Addr >= GeneralMonCurveEnd ) Flash_Addr = Flash_Addr - GeneralMonCurveEnd + GeneralMonCurveSta;		
		DataFlash_Read( Ram_Addr, Flash_Addr, GeneralMonCurveSta, GeneralMonCurveEnd, length ); 	
#endif
#else
		Flash_Addr = (*Point)* MONLENGTH + Mon_Data_Addr + stata;
//		_E2PRead( Ram_Addr, Flash_Addr , length , DataEAds);
#endif

//	DataFlash_Read( Ram_Addr, Flash_Addr , length );
	return 0 ;
*/


	Point = Buff;
	RAM_Fill(Ram_Addr, length);
	E2P_RData( Buff, LastEC_Pt , 2);
	if(Mon > 0) Mon -= 1;
	if((*(Point+1) == 0 ) &&(*Point == 0 )) return 0;	
	if(Mon >= *Point)
	{
		if(*(Point+1) == 0 ) return 0;
		*Point += 16 - Mon;
		if(*Point >= 16)*Point -= 16;
	}
	else 	*Point -=  Mon;

		E2P_RData( Read_Buff, (*Point)* (MONLENGTH+1)  + Mon_Data_Addr , MONLENGTH);
	RAM_Write(Ram_Addr,&Read_Buff[stata], length);
	return 0 ;	
	
	
}

void MD_Rest( void )
{

}	


void E2P_DataMove( unsigned short Dest, unsigned short Source,short DataLenth, short Cycle )
{
	unsigned char Buff[40];
	unsigned char* Point;
	short i;
	
	Point = Buff;
	for( i=0;i<Cycle;i++ )
	{
		E2P_RData( Point, Source, DataLenth );
		E2P_WData( Dest, Point , DataLenth );
		Dest += DataLenth +1;
		Source += DataLenth +1;	
	}
}	


#if ( Threephase == YesCheck ) //三相
#if( MEASCHIP == ADE7755 )
void SumPower( void )
{

	unsigned long Value=0;
	
	if(SM.SecPluseCnt >= POWERCNTTIME)
  		{
  			Value = SM.SecSumPluse;
  			Value = Value * 10000 +  SM.SecIPulseSumP  /( PS3200/ 10000);
  			
  			SM.PowerPp = Value * 36 /PS32; 	//value ·???00±?

  			Long_BCD4(Para.Pt, SM.PowerPp );
  			SM.SecPluseCnt = 0;
  		}

}
#endif
#endif
/*
void CumCRC( unsigned char* Dest, unsigned int Item )
{
	int i;
	unsigned int Temp;
	
//	WDTCTL = WDT_ARST_1000;
	fnWDT_Restart();
	for( i=0;i<Item;i++ )
	{
		RAM_Write( (unsigned char*)&Temp, Dest, 2 );
		CRCDI = Temp;
		Dest += 2;
	}	
}	
*/
/*
void Read_Para_CRC( unsigned char* Dest )						//11.11.05
{
	unsigned int i;
    unsigned char Buff[200];
    unsigned char* Ptr;
	   
    Ptr = Buff;
	
	CRCINIRES = 0xFFFF;
	E2P_RData( Ptr,Serial_No, 16 );
		
	E2P_RData( Ptr+16,EMeter_No, 10 );	
	
	E2P_RData( Ptr+26,PCB_No, 12 );
	
	E2P_RData( Ptr+38,User_ID, 8 );
	CumCRC( Ptr, 23 );	

	i = CRCINIRES;
	RAM_Write( Dest, (unsigned char*)&i, 2 );
}
*/
#if( SecurityCheck == YesCheck )				
void CheckLabState( void )
{
	short i,j;
	unsigned short Temp;
	unsigned char Buff[4];
	unsigned char* Point;
	unsigned char* Ptr;
	
	unsigned long Value;
	
	Point = Buff;
	Ptr = &SM.CuIb10OkCnt;
	Value = SM.ILabPulseSumP;
	SM.ILabPulseSumP = 0;
	
//	if( Para.RSecurityCheck == 0 )	return;
		
	for( i=0;i<3;i++ )
	{
		Temp = BCD2_Word( Para.Ua+i*2 );
		if(( Temp > VoltHigh )||( Temp < VoltLow ))	
		{
			*Ptr = 0;
			*(Ptr+1) = 0;
			*(Ptr+2) = 0;
			return;
		}	
	}
		
	for( j=0;j<3;j++ )
	{
/*		for( i=0;i<3;i++ )
		{
			Temp = BCD2_Word( Para.Ia+i*2 );
			Temp2 = BCD2_Word( Para.Pfa+i*2 );
			if(( Temp > SecurityPara[j].CuHigh )||( Temp < SecurityPara[j].CuLow )
				||(Temp2 > SecurityPara[j].CosHigh)||(Temp2 < SecurityPara[j].CosLow))	break;
		}	
		if( i != 3 ) { *(Ptr+j) = 0; continue; }			 
*/
		if(( Value < YMPTab[j*2] )||( Value > YMPTab[j*2+1] )) { *(Ptr+j) = 0; continue; }			 
		*(Ptr+j) += 1;
//		if( *(Ptr+j) > 5 ) 
		if( *(Ptr+j) > 30 ) 
		{
//			if( SM.EnterLabState == 0 ) SM.EnterLabDly = 15;
			SM.EnterLabState |= ByteBit[j];
		}	
	}
	
	if(((( Para.RECClrMode == 0x01 )||( Para.RECClrMode == 0x09 ))&&( (SM.EnterLabState & 0x03) == 0x03 )) 
		||((( Para.RECClrMode == 0x02 )||( Para.RECClrMode == 0x0A ))&&( (SM.EnterLabState & 0x07) == 0x07 ))) 
	{	
		if( SM.LabDelay == 0 ) OpenLabState();
	}	
}	

void OpenLabState( void )
{
	unsigned char* Point;
	unsigned char Buff[6];

	Point = Buff;

	SM.LabDelay = 0;
	SM.CuIb10OkCnt = 0;
	SM.CuIb05LOkCnt = 0;
	SM.Cu01Ib10OkCnt = 0;
//	SM.EnterLabState = 0;
//	SM.EnterLabDly = 0;	
	switch( Para.RECClrMode )
	{
		case 0x09: 
		case 0x0A: 
		case 0x01:
		case 0x02:	
			SM.ECClr_Count = 1; break;
		default: break;	
	}

	SM.PassWd_ErrCnt = 0;
//	SM.LabDelay = 48*60;
	E2P_RData( Point, LabPrgTime, 6 );
	SM.LabDelay = BCD2_Word( Point );
}	

void CloseLabState( void )
{	
	SM.LabDelay = 0;
	SM.CuIb10OkCnt = 0;
	SM.CuIb05LOkCnt = 0;
	SM.Cu01Ib10OkCnt = 0;
	SM.EnterLabState = 0;
//	SM.EnterLabDly = 0;
}	
#else
#endif	

void SwapChar( unsigned char* Source, short Cycle )
{
	unsigned char Temp;
	short i;
	
	for( i=0;i<Cycle;i++ )
	{
		Temp = *Source;
		*Source = *(Source+1);
		*(Source+1) = Temp;
		Source += 2; 		
	}	
}
	
void SwapWord( unsigned char* Source, short Cycle )
{
	unsigned char Temp[2];
	short i,Cnt;
	Cnt = (Cycle + 1) /2;
	for( i=0;i<Cnt;i++ )
	{
		RAM_Write(Temp,Source+ 2*i,2);
		RAM_Write(Source + 2*i ,Source+(Cycle-1-i)*2,2);
		RAM_Write(Source+(Cycle-1-i)*2,Temp,2);
//		Source += 2; 		
	}	
}



void TariffDataRomove(void)
{
	
}



void DayInc( unsigned char* Data )
{
	_BCD1INC( Data );
	if( BCD_Byte(*Data) > ((( *(Data+1)==2 ) && ( BCD_Byte(*(Data+2)) & 0x03 )==0 )? 29:MonTab[BCD_Byte(*(Data+1))]))
	{
		*Data = 1;
		_BCD1INC( Data+1 );
		if( *(Data+1) > 0x12 )
		{						// Month
			*(Data+1) = 1;
			_BCD1INC( Data+2);
			if( *(Data+2) > 0x99 ) *(Data+2) = 0;	// Year
		}
	}		
}
void Clr_E2PData( short Addr, short DataLenth, short Cylcle )
{
//  	unsigned char Buff[24];
  	unsigned char Buff[60];
  	unsigned char* Point;
  	short i;
  	
  	Point = Buff;
	
	RAM_Fill( Point, DataLenth );
	
	for( i=0;i<Cylcle;i++ )
	{
   		E2P_WData( Addr, Point, DataLenth );
   		Addr += DataLenth+1;
	}	
}
void Clr_E2PECData( short Addr, short DataLenth, short Cylcle )
{
//  	unsigned char Buff[24];
  	unsigned char Buff[60];
  	unsigned char* Point;
  	short i;
  	
  	Point = Buff;
	
	RAM_Fill( Point, DataLenth );
	
	for( i=0;i<Cylcle;i++ )
	{
		#if ( Threephase == YesCheck ) //三相				
		E2P_WECData( Addr, Point, DataLenth );
		#elif ( SinglePhase == YesCheck )
		E2P_WECData( Addr, Point, DataLenth );
		#endif
	
 //  		E2P_WECData( Addr, Point, DataLenth );
   		Addr += DataLenth+1;
	}	
}
