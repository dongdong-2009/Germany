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
#include "Power.h"
#include "RsComm.h"
#include "Time.h"
#include <Drive_Lib.h>


short PowerCheck(void)
{	
	unsigned char Buff[20];
	unsigned char* Point;
		return 0;	
}	



void TamperCheck( void )
{
	
}	

void EventCntADD(unsigned short Add)
{
	unsigned char DataBuff[5];
//	unsigned int CntData;
	
	E2P_RData( DataBuff, Add, 2 );
//	CntData = BCD2_Word(DataBuff)+1;
//	Word_BCD(DataBuff,CntData);
	_BCD2INC(DataBuff);
	E2P_WData( Add, DataBuff, 2 );
}


void EventCnt4ADD(unsigned short Add)
{
	unsigned char DataBuff[5];
	unsigned long CntData;

	if(Add==MOnCnt)
		{
		E2P_RData( DataBuff, Add, 5 );
		CntData=BCD4_Long(DataBuff);
		CntData++;
		if(CntData>99999999)	
			{
			CntData = 0;
			DataBuff[4] +=1;
			}
		Long_BCD4(DataBuff, CntData);
		E2P_WData(  Add,DataBuff,  5 );		
		}
	else
		{
		E2P_RData( (unsigned char*)&CntData, Add, 4 );
		CntData++;
		E2P_WData(  Add,(unsigned char*)&CntData ,  4 );
		}
}


void TampRecord( short Tamp_No, unsigned char Temp,short End )
//void TampRecord( int Tamp_No, unsigned char Temp,unsigned char End )
{
	unsigned char Buff[6];
	unsigned char* Point;
//	int LastPt;
//	int i;
	
//	ECSumptr = &SM.PhAFail_ECPpASum;

	Flag.Disk |= F_KeyInt;//刷新显示

	Point = Buff;
	RAM_Fill( Point, 2 );
	*Point = 1;
	switch( Tamp_No )
	{
		
		case Cover_No:
		case TCover_No:
//			if((Flag.Power & F_PwrUp) != 0)
//				TamperRecord( Tamp_No , End);//TamperPtrChk(  End );	
			if( End )break;
//			if((Flag.AlarmFlg & (F_AlarmCoverOpen+Tamp_No)) == 0)

			if(Tamp_No == TCover_No)	
				TamperRecord(4);		
			
			Tamp_No -=3;
			E2P_WData( FristOCover_Time-(7*Tamp_No), Clk.Sec, 6 );
			Flag.AlarmFlg[0] |= (F_AlarmCoverOpen+Tamp_No);
			E2P_WData( KGFlag+(2*Tamp_No), Point, 1 );	
			E2P_RData( Point, Opencover_Time+(6*Tamp_No), 5 );
			if(((Flag.Power & F_PwrUp) == 0) && (*(Point + 4) == 0))
				E2P_WData( Opencover_Time+(6*Tamp_No), Clk.Min, 5 );	
			EventCntADD(OpenCoverCnt-(3*Tamp_No));

			EventCnt4ADD(OpCoverCnt+Tamp_No*5);

			if(((Flag.Power & F_PwrUp) != 0)&&(Tamp_No == 0)) 
			Flag.AlarmFlg[3] |= F_EventCoverOpen;
			if(((Flag.Power & F_PwrUp) != 0)&&(Tamp_No == 1)) 
			Flag.AlarmFlg[3] |= F_EventTCoverOpen;		
			
					
		break;
		
#if ( Threephase == YesCheck ) //三相				
		case PhAFail_No:
//			TamperRecord( Tamp_No , End);
			if( End == 0 )
				{
				EventCnt4ADD(PAFailCnt);
				EventCnt4ADD(PAFailCntMon);					
				EventCntADD(PhaseL1Cnt);
				}
		break;	
		case PhBFail_No:
//			TamperRecord( Tamp_No , End);
			if( End == 0 )
				{
				EventCnt4ADD(PBFailCnt);
				EventCnt4ADD(PBFailCntMon);					
				EventCntADD(PhaseL2Cnt);		
				}
		break;
		case PhCFail_No:
//			TamperRecord( Tamp_No , End);
			if( End == 0 )
				{
				EventCnt4ADD(PCFailCnt);
				EventCnt4ADD(PCFailCntMon);					
				EventCntADD(PhaseL3Cnt);		
				}
		break;
//		case MeterReset_No:
//			if(! End ) TamperRecord(  11 );//TamperPtrChk( 11 );	
//			if( End == 0 )EventCntADD(MeterRestCnt);		
//		break;
#endif

		case MagnetOn_No:
//			TamperRecord( Tamp_No  , End);//TamperPtrChk( 12 + End );
//			TamperRecord( 12+End, End);//TamperPtrChk( 12 + End );
//			TamperRecord( 12 + End );			
			if(End)break;
//			if((Flag.AlarmFlg & F_AlarmMagnet) == 0)	
				E2P_WData( FristMagnetic_Time, Clk.Sec, 6 );
			Flag.AlarmFlg[0] |= F_AlarmMagnet;	
			E2P_WData( MagFlag, Point, 1 );
			EventCntADD(MagneticONCnt);		
			EventCnt4ADD(MOnCnt);	

			if((Flag.Power & F_PwrUp) != 0) 
			Flag.AlarmFlg[3] |= F_EventMagnet;
			
		break;
		case Rev_No:
			if( End )break;
			
			Flag.AlarmFlg[0] |= F_AlarmReverse;
			E2P_WData( ReverseFlag, Point, 1 );
			
			EventCnt4ADD(ReverseCnt);	
			
		break;
		
		

		default: break;		
	}	

}	


unsigned char CoverOpen(void)
{
	if((PIN_KGJC & P_KGJC) == 0) return 1;
	else return 0;	
}
unsigned char TCoverOpen(void)
{
	if((PIN_KDJC & P_KDJC) == 0) return 1;
	else return 0;	
}
unsigned char MeterResetOpen(void)
{
	if((Flag.Power & F_PwrUp) != 0) return 1;
	else return 0;
}
unsigned char MagnetOnOpen(void)
{
	if((PIN_CCJC & P_CCJC) == 0) return 1;
	else return 0;	
}


unsigned char PhAFail(void)
{
return 0;		
}	

unsigned char PhBFail(void)
{
 return 0;	
}	

unsigned char PhCFail(void)
{
return 0;	
}	

unsigned char Rev(void)
{
 return 0;		
}	


#if ( Threephase == YesCheck ) //三相
void GetMeterState(void)
{
//	int i;
//	unsigned char Buff[3],i;
//	unsigned char* Point;
//	unsigned char Temp;
	
//	Point = Buff;
	
	//Flag.PwDirPQ = 0;
//	Temp = 0;

//	Temp = Para.PWFlag;
#if( LinkMode == Phase3Wire3 )	
		//Flag.PwDirPQ &= 0xdd ;
		Temp &= 0xdd ;
#else
#endif	
		
}		
#elif ( SinglePhase == YesCheck )	//单相
void GetMeterState(void)
{
	unsigned long TempPt,TempPfa;
	short TempAngle;
//	unsigned short TempUa;
	unsigned short TempFreq;

	 fnFront_ClockBatCalculate();
	 
	E2P_RAdj( (unsigned char*)&TempPt, EMUStatusJY, 4 );
	if(TempPt != (EMU->EMUStatus & 0x00ffffff))//检验和不对则初始计量
		SOCInit();
	else
	{

 	 TempPt = EMU->EMUStatus;

	Para.EMUSta = TempPt;
	
	if(TempPt & 0x02000000) //判断功率方向是反的。
	{
		Para.PWFlag =0x01;
//		Para.PWFlag =0x00;//锰铜线焊反处理
		Flag.AlarmFlg[0] |= F_AlarmReverse;
	}
	else
	{
		Para.PWFlag =0x00;	
//		Para.PWFlag =0x01;//锰铜线焊反处理
//		Flag.AlarmFlg[0] &= ~F_AlarmReverse;
	}

	 Para.EMUSta1 = EMU->EMUStatus2;

	TempPt = EMU->PowerPA;
	if(TempPt&0x80000000) TempPt=(~TempPt)+1;		
	Para.Apower= TempPt;
	

//```````````功率
//	TempPt = (TempPt+50)/100;	 
//	TempPt =  TempPt / 4981;	//8192; 13.2.18wwl
//	Long_BCD4(Para.Pt, (unsigned long)TempPt);

	Long_BCD4(Para.Pt, (unsigned long)TempPt/533.43);

//	if(TempPt<8000)// <1.5W 为正
//	if(TempPt<61344)// <11.5W 为正50mA	
	if(TempPt<12269)// <2.3W 为正10mA	
	Para.PWFlag =0x00;


//	if(SM.PulWidthled==0x00)
	if((SM.PulWidthled==0x00)&&(Flag.DoClockTest != 0xA55AA55A))		
	{
	if(SM.LedMODE == 1) 
	{	
//	if(TempPt < 10668) 
	if(TempPt < 5334) 		// <1W 开灯
//	if((TempPt < 5334)&&((GPIO->PB&P_YGLED)==0)) 		// <1W 开灯
		{
		
		SM.CalibCount ++;
		if((TempPt < 5334)&&((GPIO->PB&P_YGLED)==0)&&(SM.CalibCount >= 3)&&(SM.PulWidthled==0x00)) 		// <1W 开灯		
			{
			SM.CalibCount = 0;
			GPIO->PBSET |= P_YGLED;              //输出寄存器、PF	
			}
		}
	else
		{
		SM.CalibCount = 0;		
	//	if(TempPt > 12269)     // >2.3W 关灯
		if((TempPt > 12269)&&((GPIO->PB&P_YGLED)==P_YGLED)&&(SM.PulWidthled==0x00))     // >2.3W 关灯	
			GPIO->PBCLR |= P_YGLED;              //输出寄存器、PF			
		}
	}
	else
		{
		if(((GPIO->PB&P_YGLED)==P_YGLED)&&(SM.PulWidthled==0x00))     // >2.3W 关灯	
			GPIO->PBCLR |= P_YGLED;              //输出寄存器、PF				
		}
	
	}

			

//```````````功率因数及角度		
	TempPfa = EMU->PFA;
       TempAngle = EMU->ANGLEA;
	
	TempPfa &=0x00ffffff; 
	if(TempPfa&0x00800000) TempPfa=((~TempPfa)&0x00ffffff)+1;
	
//	Long_BCD4(Para.Pfa, (unsigned long)TempPfa);
	Word_BCD(Para.Pfa, (unsigned short )((float)TempPfa/8388.608));		
	Word_BCD(Para.Angle,TempAngle*3600/32768); 
//	Long_BCD4(Para.Angle,(unsigned long)TempAngle); 


//```````````电压		
	TempPfa = EMU->URMS;	//13.1.24wwl 
//	if(TempPfa&0x00800000) TempPfa=0;
	Para.Avoltage = TempPfa;

//	TempPfa =  TempPfa  / 4.66;		
	TempPfa =  TempPfa  / 4.6466;		
	if(TempPfa <= 180000) //电压拉偏13.1.24wwl Para.Ua作为十进制
	Para.SFlag |= 0x01;
	else
	Para.SFlag &=~ 0x01;
	
	Long_BCD4(Para.Ua, TempPfa);//13.1.24wwl

//```````````电流
	TempPfa = EMU->IARMS;
	Para.Acurrent= TempPfa;

//	if(TempPfa&0x00800000) TempPfa=0;
	Long_BCD4(Para.Ia, TempPfa/3.76);
	

//```````````频率
 	TempFreq =  EMU->Ufreq;
	Word_BCD(Para.Freq,(unsigned short)(((unsigned long)184320000)/((unsigned long)4*TempFreq)));	


	
//	if(Para.RAutoDisMode == 0)
//		SM.RDisDays = 99;
//	else 	SM.RDisDays = 0;


	}
}
#endif


// 事件记录
//short TamperRecord( unsigned char Tamper_no ,unsigned char End)
short TamperRecord( unsigned char Tamper_no )
{
	unsigned char Buff[TAMPERLENGTH];
	unsigned char* Point;
	short TamperPtr; 

	Point = Buff;
	RAM_Fill( Point, TAMPERLENGTH );
	TamperPtr = (unsigned long)TamperPtrChk( -1 ) * TAMPERLENGTH + Tamper_Data_Addr;
	RAM_Write( Point, Clk.Min, 5 );	
	*(Point + 5) =  Tamper_no;
	E2P_RData( Point + 6, User_ID, 8 );
	E2P_WData( TamperPtr, Point, TAMPERLENGTH - 1 );

	return 1;	
}	
	
//int LoadPtrChk( unsigned char* LoadPara, int Type )
//short TamperPtrChk( short Type, unsigned char Tamper_no )
short TamperPtrChk( short Type )
{
	unsigned char Buff[3];
	unsigned char* Point;
	short MaxPtr;
	short CurrentPtr;
	short Temp;
	Point = Buff;
	
//	E2P_RData( Point, TamperRecState + 4*(Tamper_no), 3 );
	E2P_RData( Point, TamperRecState, 3 );	
	MaxPtr = MAX_TAMPER_PTR;
	Temp = *(Point+1)*256 + *Point;
	CurrentPtr = MaxPtr - Temp;
	if( Type == -1)
	{
//		CurrentPtr--;
//		if( CurrentPtr == -1 ) 	CurrentPtr = MaxPtr;
//		Temp = MaxPtr - CurrentPtr;
//		RAM_Write( Point, (unsigned char*)&Temp, 2 );		
//		if(CurrentPtr == MaxPtr) *(Point+2) += 1;
//		E2P_WData( TamperRecState + 4*(Tamper_no), Point, 3 );

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//解决第100条事件覆盖了第99条事件问题
		CurrentPtr--;
		if( CurrentPtr == 0 ) 	CurrentPtr = MaxPtr;
		Temp = MaxPtr - CurrentPtr;
		RAM_Write( Point, (unsigned char*)&Temp, 2 );	
		if(CurrentPtr == MaxPtr) *(Point+2) += 1;
//		E2P_WData( TamperRecState + 4*(Tamper_no), Point, 3 );
		E2P_WData( TamperRecState, Point, 3 );		
				
	}	  
	else
	{
		if((Type>MaxPtr)||((*(Point+2) == 0)&&(Type>=Temp))) return -1;	//读取的记录超限
		CurrentPtr += Type;
		if(CurrentPtr > MaxPtr )  CurrentPtr -= MaxPtr;		
	}		
	return CurrentPtr;
}

//int ReadTamperRecord( unsigned char* Dest )
//short ReadTamperRecord( unsigned char* Dest ,short Ptr, unsigned char Tamper_no)
short ReadTamperRecord( unsigned char* Dest ,short Ptr)
{
	short TamperPtr;
//	unsigned long TamperAdr;
	
	TamperPtr = Ptr;
	RAM_Fill( Dest, TAMPERLENGTH - 1 );
//	TamperPtr = TamperPtrChk( TamperPtr ,Tamper_no);
//	TamperPtr = TamperPtrChk( TamperPtr ,(Tamper_no-12));	
	TamperPtr = TamperPtrChk( TamperPtr );
	if( TamperPtr != -1 ) 
//		E2P_RData( Dest, TamperPtr*TAMPERLENGTH + Tamper_Data_Addr + (Tamper_no-12) * E2P_TamperDataLong, TAMPERLENGTH - 1 );
		E2P_RData( Dest, TamperPtr*TAMPERLENGTH + Tamper_Data_Addr, TAMPERLENGTH - 1 );	
	else return 0;

	return (TAMPERLENGTH - 1);
	
}	



void SetTamperPara( void )
{

	Clr_E2PData( TamperRecState, 3, 6 );
//	Clr_E2PData( GeneralTamperCurAddr, 4, 1 );
//	BlockErase( GeneralTamperCurveSta );	
}		

void TamperRecordData(int Tamp_No,unsigned char* NewTime)
{
	unsigned char Buff[15];
	unsigned char* Point;
	Point = Buff;
	RAM_Fill( Point, 15 );
	*Point = 1;
	switch( Tamp_No )
	{
		
		case TimeSET_No:
			*Point = 0x0E;
			*(Point + 1) = 0x01;
			*(Point + 2) = 0x00;
			*(Point + 3) = 0x00;
			*(Point + 4) = 0x09;
			*(Point + 5) = 0x0B;
			*(Point + 6) = 0x00;
			
			*(Point + 7) = 0x04;		//数据长度
			RAM_Write(Point+8,NewTime,4);
			TamperRecord( *Point );//TamperPtrChk( 5 + End );
		
			break;
		case TimeAsynchronous_No:
			*Point = 0x0F;
			*(Point + 1) = 0x01;
			*(Point + 2) = 0x00;
			*(Point + 3) = 0x00;
			*(Point + 4) = 0x09;
			*(Point + 5) = 0x0B;
			*(Point + 6) = 0x00;
			
			*(Point + 7) = 0x00;		//数据长度
			TamperRecord( *Point );//TamperPtrChk( 5 + End );
			
			break;
		case ManipulationRecognized_No:	
			*Point = 0x11;
			*(Point + 1) = 0x01;
			*(Point + 2) = 0x00;
			*(Point + 3) = 0x60;
			*(Point + 4) = 0x05;
			*(Point + 5) = 0x00;
			*(Point + 6) = 0xFF;
			
			*(Point + 7) = 0x00;		//数据长度
			
			TamperRecord( *Point );//TamperPtrChk( 5 + End );
			
			break;
		default: break;		
	}	

}	
	
	
	
	













