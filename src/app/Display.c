//#include "msp430f6736.h"
#include "TypeMeter.h"
#include "Port.h"
#include "Type.h"
#include "Data.h"
#include "General.h"
#include "Mem.h"
#include "Power.h"
#include "Display.h"
#include "Rscomm.h"
#include "Measure.h"
#include "TypeE2p.h"
#include "Time.h"

//#define  _LcdDrive_GLOBALS
#include <Drive_Lib.h>

/*
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
*/




void ECDisplayMove( unsigned char* Data )
{
	unsigned char Databuff;
	short i;
	Databuff = 0;
	for(i=0;i<7;i++)
	{
		if(i == 6)
			Databuff = 0;
		else	
			Databuff = *(Data + i + 1);
		Databuff <<= 4;
		*(Data + i) >>= 4;
		*(Data + i) |= Databuff;
	}

}
 
const unsigned char DisplayStation[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //v1.0 

void DspNum( unsigned char *Addr, short Lenth, unsigned char *SegPtr ,short Digit)
{
	short i;
#if ( SinglePhase == YesCheck ) //单相  
	unsigned char DataBuff;
	unsigned char PlaceN,PlaceB;
	unsigned char Temp;
#endif	

	if( Lenth > 4) return;


 #if ( Threephase == YesCheck ) //三相  	
/*
#define		DS_a		0x01
#define		DS_b		0x04
#define		DS_c		0x40
#define		DS_d		0x20
#define		DS_e		0x80
#define		DS_f		0x02
#define		DS_g		0x08
#define		DS_h		0x10

*/
	if( Digit != 0 )
	{
		*(SegPtr +Digit) |= DS_h;		
	}		
	
	for(i=0;i < Lenth*2; i++)
   	 {	
//		PlaceN = DisplayStation[i*2];
//		PlaceB = DisplayStation[i*2+1];;
//		DataBuff = NumSeg[((*Addr) >>(4*(i&0x01)))& 0x0F];
//		Temp = 0;
//		Temp |= (DataBuff&0x07)<<1;//a,b,c,	
//		*(SegPtr + PlaceN) |= Temp;
//		Temp = 0;		
//		Temp |= (DataBuff&0xF0)>>3;//f,g,e,d
//		*(SegPtr + PlaceB) |= Temp;	

		*(SegPtr++) |= NumSeg[((*Addr) >>(4*(i&0x01)))& 0x0F];
		
		if(i&0x01)
			Addr++; 	  		
   	 }		
 #else	
/*
#define		DS_a		0x01
#define		DS_b		0x02
#define		DS_c		0x04
#define		DS_d		0x80
#define		DS_e		0x40
#define		DS_f		0x10
#define		DS_g		0x20
#define		DS_h		0x08
*/
	if( Digit != 0 )
	{
		*(SegPtr +Digit*2) |= DS_f;		
	}		
	
	for(i=0;i < Lenth*2; i++)
   	 {	
//   	 	if( i>=7 ) break;
		PlaceN = DisplayStation[i*2];
		PlaceB = DisplayStation[i*2+1];;

		DataBuff = NumSeg[((*Addr) >>(4*(i&0x01)))& 0x0F];
		
		Temp = 0;
		Temp |= (DataBuff&0x07)<<1;//a,b,c,	
		*(SegPtr + PlaceN) |= Temp;

		Temp = 0;		
		Temp |= (DataBuff&0xF0)>>3;//f,g,e,d
		*(SegPtr + PlaceB) |= Temp;	
									
		if(i&0x01)
			Addr++; 	  		
   	 }		

#endif


}



/*
void ZeroDark( unsigned char *LCDSeg )
{
	int i,Temp;
	unsigned char Temp2;
	for( i=0; i<7; i++ )
	{
		Temp = DS_BDig - 7 + i;
		if( LCDSeg[Temp] == 0 ) continue;
		Temp2 = LCDSeg[Temp] & (~DS_Chr_Dot);
	   	if(( Temp2 == NumSeg[0] ) && (( LCDSeg[Temp] & DS_Chr_Dot ) == 0)) LCDSeg[Temp] = 0;
	   	else break;
	}
}
*/

void ActiveDisp(  unsigned char *LCDSeg, unsigned char *FLCDSeg )
{	
	unsigned char Buff[10];
//	unsigned char* Point;
	unsigned char *PowerLCDSeg;
//    	int i;
   	unsigned long ActivePt;
// 	unsigned long ActiveQt;
    
//	Point = Buff;
//	*(LCDSeg  ) = 0;

//	if( Disk.ItemPtr == 12 ) return;	//全屏时

//	LCDSeg[16] |= ByteBit[ SM.FeeNo - 1 ];
	
//	if(( (Flag.Power & F_PwrUp) == 0)&&( Comm.BatOnDly == 0 )) FLCDSeg[16] |= ByteBit[ SM.FeeNo - 1 ];
	
//	Flag.Disk ^= F_Flash;
	
////	if( SM.PowerRev != 0) *LCDSeg |= 0x08;

//#if ( Threephase == YesCheck ) //三相	//13.2.25wwl	
//	if((PIN_BATCH & P_BATCH )==0) 	*(FLCDSeg+25) |= DS_a;		// 电池欠压	
//	else *(FLCDSeg+25) &=~ DS_a;
//#else//13.2.25wwl	
//	if((PIN_BATCH & P_BATCH )==0) 	*(FLCDSeg+27) |= DS_a;		// 电池欠压	
//	else *(FLCDSeg+27) &=~ DS_a;
//#endif	//13.2.25wwl	
	
//#if (Threephase == YesCheck) 
//	if(((Flag.Power & F_PwrUp) == 0) && ( Comm.BatOnDly != 0 ))*(LCDSeg + 10 ) |= DS_f;//*(LCDSeg + 2 ) |= DS_h;	//停抄	v04
//#else
//	if(((Flag.Power & F_PwrUp) == 0) && ( Comm.BatOnDly != 0 ))*(LCDSeg + 12 ) |= DS_g;//*(LCDSeg + 2 ) |= DS_h;	//停抄  v05
//#endif	

	if((Flag.Power & F_PwrUp) != 0)
	{
#if ( Threephase == YesCheck ) //三相		
#if( MEASCHIP == ATT7053 )		
		if((Para.SFlag & 0x0F) == 0x08)
		{
			switch(Disk.RotPhase)
			{
				case 1:
			 		*(LCDSeg  ) |= DS_f;	
			 		break;
			 	case 2:
			 		*(LCDSeg  ) |= DS_g;	
			 		break;
			 	default:
			 		*(LCDSeg  ) |= DS_e;	
			 		Disk.RotPhase=0;
			 		break;
			}
		
		}else{	
			if((Para.SFlag & 0x01) != 0x01)
			{	 
				if((Para.PWFlag & 0x01) != 0x01) *(LCDSeg  ) |= DS_f;	
					else *(FLCDSeg  ) |= DS_f;
			}
			else *(LCDSeg  ) &=~ DS_f;
		
			if((Para.SFlag & 0x02) != 0x02) 
			{
				if((Para.PWFlag & 0x02) != 0x02) 
					*(LCDSeg  ) |= DS_g;
				else 
					*(FLCDSeg ) |= DS_g;
			}	
			else 
				*(LCDSeg  ) &=~ DS_g;
	
			if((Para.SFlag & 0x04) != 0x04) 
			{	
				if((Para.PWFlag & 0x04) != 0x04) 
					*(LCDSeg  ) |= DS_e;
				else	
					*(FLCDSeg  ) |= DS_e;
			}
			else *(LCDSeg  ) &=~ DS_e;
		}
#elif(( MEASCHIP == ADE7755 )||( MEASCHIP == RN8207 ))	
		if( Flag.AlarmFlg[0] & F_AlarmPhs )
		{
			switch(Disk.RotPhase)
			{
				case 1:
			 		*(LCDSeg + 12) |= 0x10;	//L3
			 		break;
			 	case 2:
			 		*(LCDSeg + 13) |= 0x10;	//L2
			 		break;
			 	default:
			 		*(LCDSeg + 13) |= 0x20;	//L1
			 		Disk.RotPhase=0;
			 		break;
			}
		
		}
		else
		{				
//			if(Para.PreUa != 0)
			if((Para.SFlag & 0x01) != 0x01)		
			{	 
				if((Para.PWFlag & 0x01) != 0x01) 
					*(LCDSeg + 13) |= 0x20;	
				else 
					*(FLCDSeg + 13 ) |= 0x20;
			}
			else *(LCDSeg + 13) &=~ 0x20;
		
//			if(Para.PreUb != 0)
			if((Para.SFlag & 0x02) != 0x02) 		
			{ 
				if((Para.PWFlag & 0x02) != 0x02) *(LCDSeg + 13) |= 0x10;
					else *(FLCDSeg + 13) |= 0x10;
			}	
			else *(LCDSeg + 13) &=~ 0x10;
	
//			if(Para.PreUc != 0)
			if((Para.SFlag & 0x04) != 0x04) 		
			{	
				if((Para.PWFlag & 0x04) != 0x04) *(LCDSeg + 12) |= 0x10;
					else	*(FLCDSeg + 12) |= 0x10;
			}
			else *(LCDSeg + 12) &=~ 0x10;
		}
#endif				
//		Read_ATTValue(  ATPWPZ, Point );			//正向功率
//		ActivePt = BCD4_Long( Para.Pt);	//功率条
//		ActivePt = BCD4_Long( Para.Pt)/10;	//功率条代数和		
		ActivePt = BCD4_Long( Para.PtABS)/10;	//功率条绝对值		
		if((Para.PWFlag & 0x07) == 0x00) 
			PowerLCDSeg = LCDSeg;
		else 
			PowerLCDSeg = FLCDSeg;
		

		if(ActivePt > 2)*(PowerLCDSeg + 18 ) |= 0x10;	
		if(ActivePt >= 24)*(PowerLCDSeg + 18) |= 0x20;
		if(ActivePt >= 96)*(PowerLCDSeg + 18 ) |= 0x40;
		if(ActivePt >= 384)*(PowerLCDSeg+ 18 ) |= 0x80;
		if(ActivePt >= 1536)*(PowerLCDSeg+ 19 ) |= 0x40;
		if(ActivePt >= 6144)*(PowerLCDSeg+ 19 ) |= 0x20;
		if(ActivePt >= 24476)*(PowerLCDSeg+ 19 ) |= 0x10;	

//		ActivePt = BCD4_Long( Para.Pt)/10;	//功率条代数和	
		if(ActivePt > 2)
			{
			if(Measure8207.FlagDireABC & F_ABCDire) 
			*(LCDSeg+19) |= 0x80;//反向X9
			else 
			*(LCDSeg+14) |= 0x10;//正向X13			
			}		


		if((Flag.AlarmFlg[1] &  F_AlarmBATCH) != 0) *(FLCDSeg + 15) |= 0x80;			//v05//电池符号X3
		
//		if( SM.ENCount != 0 ) *(LCDSeg + 14) |= 0x80;//编程符号X8
//		if(( Comm.RecTmr0 != 0 )||(Comm.Mode0 > 1)||(Comm.RecTmr1 != 0 )||(Comm.Mode1 > 1)) 	
//		*(LCDSeg+14) |= 0x40;	//X2
		if((Comm.State0 == 1)&&(Flag.Run0 & F_ComOK))*(LCDSeg+14) |= 0x40;	//X2

/*
	if((SM.Tariffsnu != 0x11)&&(SM.Tariffsnu != 0x22))
	{		
		*(LCDSeg+19) |= 0x08;//T

		if(SM.FeeNo == 1)	
		{
		*(LCDSeg+16) |= 0x60;		
		}
		if(SM.FeeNo == 2)	
		{
		*(LCDSeg+16) |= 0xB0;		
		*(LCDSeg+17) |= 0x60;		
		}
		if(SM.FeeNo == 3)
		{
		*(LCDSeg+16) |= 0xF0;		
		*(LCDSeg+17) |= 0x20;		
		}
		if(SM.FeeNo == 4)	
		{
		*(LCDSeg+16) |= 0x60;		
		*(LCDSeg+17) |= 0x30;		
		}
		
	}
*/

	if((SM.Tariffsnu != 0x11)&&(SM.Tariffsnu != 0x22)&&(SM.Tariffsnu != 0))
	{		
		
		if(SM.FeeNo == (SM.Tariffsnu&0x0F))	
		{
//		*(LCDSeg + 13) |= 0x80;//S9
		*(LCDSeg + 14) |= 0x80;//S8		
		}
		else
		{
		*(LCDSeg + 13) |= 0x40;//S10
		}	
		
	}
	


	if(Flag.ClrFlag & F_SSET_EN) *(FLCDSeg + 7) |= ( *(LCDSeg + 7) & 0xEF);//8 1
	if(Flag.ClrFlag & F_MSET_EN) *(FLCDSeg + 6) |= ( *(LCDSeg + 6) & 0xEF);//8 2
	if(Flag.ClrFlag & F_ECClr_EN) *(FLCDSeg + 5) |= ( *(LCDSeg + 5) & 0xEF);//8 3
	
#elif ( SinglePhase == YesCheck )		

//		Read_ATTValue(  ATPWPZ, Point );			//正向功率
//		ActivePt = BCD4_Long( Para.Pt);	//功率条
		ActivePt = BCD4_Long( Para.Pt)/10;	//功率条		
		if((Para.PWFlag & 0x07) == 0x00) PowerLCDSeg = LCDSeg;
		else PowerLCDSeg = FLCDSeg;
		
		if(ActivePt > 1)*(PowerLCDSeg + 29 ) |= 0x20;	
		if(ActivePt >= 8)*(PowerLCDSeg + 28 ) |= 0x20;
		if(ActivePt >= 32)*(PowerLCDSeg + 27 ) |= 0x20;
		if(ActivePt >= 128)*(PowerLCDSeg+ 26 ) |= 0x20;
		if(ActivePt >= 512)*(PowerLCDSeg+ 25 ) |= 0x20;
		if(ActivePt >= 2048)*(PowerLCDSeg+ 24 ) |= 0x20;
		if(ActivePt >= 8192)*(PowerLCDSeg+ 23 ) |= 0x20;


		if(ActivePt > 1)
			{
////			*(LCDSeg + 10) |=0x04;//中间点			
			if((Para.PWFlag & 0x07) != 0x00)
			*(LCDSeg+17) |= 0x01;//反向x9
			else 
			*(LCDSeg+14) |= 0x01;//正向x13	
			}
		
		if((Flag.Power &  F_BatteryPwrUp) != 0) *(FLCDSeg + 27) |= 0x01;			//v05//电池符号

//		if( SM.ENCount != 0 ) *(LCDSeg + 10) |= DS_b;//编程符号
		if(( Comm.RecTmr0 != 0 )||(Comm.Mode0 > 1)||(Comm.RecTmr1 != 0 )||(Comm.Mode1 > 1)) 	
		*(LCDSeg+28) |= 0x01;	
		
/*
	if((SM.Tariffsnu != 0x11)&&(SM.Tariffsnu != 0x22))
	{		
		*(LCDSeg+0) |= 0x10;//T

		if(SM.FeeNo == 1)	
		{
		*(LCDSeg+1) |= 0x60;		
		}
		if(SM.FeeNo == 2)	
		{
		*(LCDSeg+0) |= 0x60;		
		*(LCDSeg+1) |= 0xD0;		
		}
		if(SM.FeeNo == 3)
		{
		*(LCDSeg+0) |= 0x40;		
		*(LCDSeg+1) |= 0xF0;		
		}
		if(SM.FeeNo == 4)	
		{
		*(LCDSeg+0) |= 0xC0;		
		*(LCDSeg+1) |= 0x60;		
		}
		
	}
*/

	if((SM.Tariffsnu != 0x11)&&(SM.Tariffsnu != 0x22)&&(SM.Tariffsnu != 0))
	{		
		
		if(SM.FeeNo == (SM.Tariffsnu&0x0F))	
		{
//		*(LCDSeg + 14) |= 0x10;//S12
		*(LCDSeg + 19) |= 0x20;//S11		
		}
		else
		{
//		*(LCDSeg + 12) |= 0x10;//S13
		*(LCDSeg + 14) |= 0x10;//S12		
		}	
		
	}

	if(Flag.ClrFlag & F_SSET_EN) *(FLCDSeg + 25) |= 0x01;//X5
	if(Flag.ClrFlag & F_MSET_EN) *(FLCDSeg + 26) |= 0x01;//X4
	if(Flag.ClrFlag & F_ECClr_EN) *(FLCDSeg + 23) |= 0x01;//X7
	
		
#endif
	

	
//	if((Flag.RelayState & F_Relay2)&&(SM.Tariffsnu == 0)) *(LCDSeg+12) |= DS_b;	//继电器标志
		
	}

 #if ( Threephase == YesCheck ) //三相  	
	E2P_RData( Buff, TamperSwitch, 1 );	

//	if(( Flag.AlarmFlg[0] & F_AlarmCoverOpen )&&((Buff[0]&0x02)==0x02))	*(LCDSeg + 12) |= 0x02;//开盖指示x18
//	if(( Flag.AlarmFlg[0] & F_AlarmTCoverOpen )&&((Buff[0]&0x04)==0x04))	*(LCDSeg + 12) |= 0x04;		//开端指示X19

//	if(( Flag.AlarmFlg[0] & F_AlarmMagnet )&&((Buff[0]&0x01)==0x01))	*(LCDSeg + 14 ) |= 0x20;				//磁场指示X1
	if(( Flag.AlarmFlg[0] & F_AlarmMagnet )&&((Buff[0]&0x10)==0x10))	*(LCDSeg + 14 ) |= 0x20;				//磁场指示X1	
//	if(( Flag.AlarmFlg[0] & F_AlarmCoverOpen )&&((Buff[0]&0x02)==0x02))	*(LCDSeg + 13) |= 0x40;//开盖指示S10
//	if(( Flag.AlarmFlg[0] & F_AlarmCoverOpen )&&((Buff[0]&0x02)==0x02))	*(LCDSeg + 13) |= 0x80;//开盖指示S9	
//	if(( Flag.AlarmFlg[0] & F_AlarmTCoverOpen )&&((Buff[0]&0x04)==0x04))	*(LCDSeg + 14) |= 0x80;		//开端指示S8	

//	if(( Flag.AlarmFlg[0] & (F_AlarmCoverOpen+F_AlarmTCoverOpen+F_AlarmMagnet))) 
//		{
//		*(LCDSeg+0) |= 0xE0;		
//		*(LCDSeg+1) |= 0x80;	
//		}

	if(((PIN_KGJC & P_KGJC) == 0)||((PIN_KDJC & P_KDJC) == 0)||((( PIN_CCJC& P_CCJC) == 0)&&((Flag.Power & F_PwrUp) != 0)))
		{
		*(LCDSeg+16) |= 0x10;		
		*(LCDSeg+17) |= 0x70;	
		}
 #else	
	E2P_RData( Buff, TamperSwitch, 1 );	

//	if(( Flag.AlarmFlg[0] & F_AlarmCoverOpen )&&((Buff[0]&0x02)==0x02))	*(LCDSeg + 12) |= 0x02;//开盖指示x18
//	if(( Flag.AlarmFlg[0] & F_AlarmTCoverOpen )&&((Buff[0]&0x04)==0x04))	*(LCDSeg + 12) |= 0x04;		//开端指示X19

//	if(( Flag.AlarmFlg[0] & F_AlarmMagnet )&&((Buff[0]&0x01)==0x01))	*(LCDSeg + 29 ) |= 0x01;				//磁场指示
	if(( Flag.AlarmFlg[0] & F_AlarmMagnet )&&((Buff[0]&0x10)==0x10))	*(LCDSeg + 29 ) |= 0x01;				//磁场指示	
//	if(( Flag.AlarmFlg[0] & F_AlarmCoverOpen )&&((Buff[0]&0x02)==0x02))	*(LCDSeg + 16) |= 0x10;//开盖指示S8
//	if(( Flag.AlarmFlg[0] & F_AlarmTCoverOpen )&&((Buff[0]&0x04)==0x04))	*(LCDSeg + 17) |= 0x20;		//开端指示S9	

//	if(( Flag.AlarmFlg[0] & (F_AlarmCoverOpen+F_AlarmTCoverOpen+F_AlarmMagnet))) 
//		{
//		*(LCDSeg+0) |= 0xE0;		
//		*(LCDSeg+1) |= 0x80;	
//		}

	if(((PIN_KGJC & P_KGJC) == 0)||((PIN_KDJC & P_KDJC) == 0)||((( PIN_CCJC& P_CCJC) == 0)&&((Flag.Power & F_PwrUp) != 0)))
		{
		*(LCDSeg+20) |= 0x02;		
		*(LCDSeg+21) |= 0x0E;	
		}
#endif


	
}
/*
//------------------------
void FillDisChar (unsigned char *SegPtr,unsigned char Item)
{
	unsigned char i,*Point;
	
	Point=(unsigned char*)&KeyMenuTab[Item].Char1;
	for(i=0;i<8;i++)
	{
		if(	*Point != 0xff)
		{	
			*SegPtr = *Point;
		}
		
		Point++;
		SegPtr++;	
	}	
}
*/
//-------------------------
const TARINAMCONVERT TariffNamDisTab[]=
{
	0xfc,DS_Chr_0,	
	0x0c,DS_Chr_1,	
	0xda,DS_Chr_2,
	0x9e,DS_Chr_3,
	0x2e,DS_Chr_4,
	0xb6,DS_Chr_5,
	0xf6,DS_Chr_6,
	0x8c,DS_Chr_7,
	0xfe,DS_Chr_8,
	0xbe,DS_Chr_9,
	0xf0,DS_Chr_C,
	0x5e,DS_Chr_d,
	0xf4,DS_Chr_G,
	0x42,DS_Chr_r,
	0xee,DS_Chr_A,
	0x76,DS_Chr_b,
	0xf2,DS_Chr_E,
	0x02,DS_g,
	0x54,DS_Chr_w,
};

unsigned char TariffNameConvert(unsigned char Data)
{
	unsigned char i;
	for(i=0;i<19;i++)
	{
		if(Data==TariffNamDisTab[i].OldTariDis)
		{
			return(TariffNamDisTab[i].NewTariDis);
		}
	}
	return(0x00);		
}

/*
const unsigned char DisplayCharecter1[5]={DS_Chr_N,DS_Chr_A,DS_Chr_r,DS_Chr_A,DS_Chr_P};	//"PArAM"
const unsigned char DisplayCharecter2[8]={DS_Chr_C,DS_Chr_A,DS_Chr_u,DS_Chr_0,DS_Chr_r,DS_Chr_E,DS_Chr_2};	//"ZErOvAC"
const unsigned char DisplayCharecter3[5]={DS_Chr_r,DS_Chr_A,DS_Chr_G,DS_Chr_E,DS_Chr_2};	//"ZEGAr"
const unsigned char DisplayCharecter4[4]={DS_Chr_E,DS_Chr_N,DS_Chr_0,DS_Chr_d};	//"d0NE"

const unsigned char DisplayCharecter5[2]={DS_Chr_y,DS_Chr_d};	//"dy"
const unsigned char DisplayCharecter6[2]={DS_Chr_n,DS_Chr_d};	//"dn"
const unsigned char DisplayCharecter7[2]={DS_Chr_d,DS_Chr_d};	//"dd"
const unsigned char DisplayCharecter8[2]={DS_Chr_H,DS_Chr_t};	//"tH"
const unsigned char DisplayCharecter9[2]={DS_Chr_n,DS_Chr_t};	//"tn"
const unsigned char DisplayCharecter10[2]={DS_Chr_5,DS_Chr_t};	//"tS"
*/

/*
const unsigned char DisplayCharecter1[5]={DS_Chr_P,DS_Chr_A,DS_Chr_r,DS_Chr_A,DS_Chr_N};	//"PArAM"
const unsigned char DisplayCharecter2[8]={DS_Chr_2,DS_Chr_E,DS_Chr_r,DS_Chr_0,DS_Chr_u,DS_Chr_A,DS_Chr_C};	//"ZErOvAC"
const unsigned char DisplayCharecter3[5]={DS_Chr_2,DS_Chr_E,DS_Chr_G,DS_Chr_A,DS_Chr_r};	//"ZEGAr"
const unsigned char DisplayCharecter4[4]={DS_Chr_d,DS_Chr_0,DS_Chr_N,DS_Chr_E};	//"d0NE"

const unsigned char DisplayCharecter5[2]={DS_Chr_d,DS_Chr_y};	//"dy"
const unsigned char DisplayCharecter6[2]={DS_Chr_d,DS_Chr_n};	//"dn"
const unsigned char DisplayCharecter7[2]={DS_Chr_d,DS_Chr_d};	//"dd"
const unsigned char DisplayCharecter8[2]={DS_Chr_t,DS_Chr_H};	//"tH"
const unsigned char DisplayCharecter9[2]={DS_Chr_t,DS_Chr_n};	//"tn"
const unsigned char DisplayCharecter10[2]={DS_Chr_t,DS_Chr_5};	//"tS"
*/

 #if ( Threephase == YesCheck ) //三相  	

 #else	
void NumberConvert(unsigned char *Point,unsigned char *DisTabObs)
{
	unsigned char Temp;

/*
#define		DS_a		0x08
#define		DS_b		0x04
#define		DS_c		0x02
#define		DS_d		0x10
#define		DS_e		0x20
#define		DS_f		0x80
#define		DS_g		0x40
#define		DS_h		0x02
*/
 
	Temp = 0;
	Temp |= (*DisTabObs&0x0F)<<1;//a,b,c,'.'	
//	Temp |= (*DisTabObs&0x08)>>3;//'.'	
	*Point  |= Temp;	
	
	Temp = 0;		
	Temp |= (*DisTabObs&0xF0)>>3;//f,g,e,d
	*(Point + 1) |= Temp;			

	
}

#endif



void NumberConvert1(unsigned char *Point,unsigned char *DisTabObs)
{
	unsigned char Temp;

 #if ( Threephase == YesCheck ) //三相  	
/*
#define		DS_a		0x01
#define		DS_b		0x04
#define		DS_c		0x40
#define		DS_d		0x20
#define		DS_e		0x80
#define		DS_f		0x02
#define		DS_g		0x08
#define		DS_h		0x10
*/

	
	Temp = 0;
	Temp |= (*DisTabObs&0x01);//a
	Temp |= (*DisTabObs&0x04)>>1;//b
	Temp |= (*DisTabObs&0x20)>>2;//d
	Temp |= (*DisTabObs&0x40)>>4;//c	
	*Point  |= Temp;	
	
	Temp = 0;		
	Temp |= (*DisTabObs&0x02)>>1;//f
	Temp |= (*DisTabObs&0x08)>>2;//g
	Temp |= (*DisTabObs&0x80)>>5;//e		
	*(Point + 1) |= Temp;	

	*(Point - 1) |= (*DisTabObs&0x10)>>1;//. 
 #else	
 
/*
#define		DS_a		0x08
#define		DS_b		0x04
#define		DS_c		0x02
#define		DS_d		0x10
#define		DS_e		0x20
#define		DS_f		0x80
#define		DS_g		0x40
#define		DS_h		0x02
*/
 
	Temp = 0;
	Temp |= (*DisTabObs&0x0F)<<1;//a,b,c,'.'	
	*Point  |= Temp;	
	
	Temp = 0;		
	Temp |= (*DisTabObs&0xF0)>>3;//f,g,e,d
	*(Point + 1) |= Temp;	
#endif

	
	
}


//===============================
void Display(void)
{
	short i;
   	unsigned char LCDSeg[32], FLCDSeg[32];
//   	unsigned char Buff[10],Buff1[10],TempAcc;
   	unsigned char Buff[10],Buff1[10];
   	unsigned char* Point;
   	unsigned short Addr,Temp;
	unsigned short Length,Digit,Unit,Hismon,RWMode;
	unsigned long LongData;
   	
   	Point = Buff;
	
//	if( SM.TestDisCnt != 0 ) 
//	{	
//////		for( i=0; i<16; i++ )
//		for( i=0; i<40; i++ ) 
//   		{
//			LCDMEM[i] = 0xFF;
//		}
//		return;
//   	}   	

////	for( i=16; i<20; i++ ) 
////	{
////		LCDMEM[i] = 0x0;
////	}
/*	
	if( ( Disk.ItemPtr == 0 )&&((Flag.Disk & F_KeyInt) == 0) )
	{			
		if(( Flag.ErrFlg & F_ErrMeasSec )&&( Para.RAlarm_Control[0] & 0x10 ))
		{
			if(( Flag.Clk & F_Sec ) != 0 )
			{
				if( Flag.Disk & F_Flash ) Temp = 0x0;
				else Temp = 0xff;
				for( i=0; i<16; i++ ) 
   				{
					LCDMEM[i] = Temp;
				}
			}	
			return;
		}
	}
*/
//	if(( Disk.ItemPtr == 11 )&&( Disk.DisInv != 0 ))
//	{
//		for( i=0; i<19; i++ ) 
//   		{
//			LCDMEM[i] = 0xFF;
//		}
//		return;
//	}	
   	for( i=0; i<32; i++ ) 
   	{
		LCDSeg[i] = 0;
  		FLCDSeg[i] = 0;
   	}
   	
 //  	if( SM.TestDisCntButton != 0 ) 
//	{	

//		for( i=0; i<30; i++ ) 
  // 		{
//			LCDMEM[i] = 0xFF;
			
//		}
//		fnLcd_RefreshLcdBuf();
//		return;
	
//   	}
   	
   	if( SM.TestDisCnt != 0 ) 
	{	
////		for( i=0; i<16; i++ )
//		for( i=0; i<40; i++ ) 
//   		{
//			LCDMEM[i] = 0xFF;
//		}
//		return;

		if(SM.TestDisCnt > 4)
		{	
			for(i=0;i<30;i++)	//8com	
	   		{
				LCDMEM[i] = 0xFF;
			}
			fnLcd_RefreshLcdBuf();
		}
		else if(SM.TestDisCnt > 2)
		{

			for(i=0;i<30;i++)	//8com	
	   		{
				LCDMEM[i] = 0;
			}
			fnLcd_RefreshLcdBuf();
			
		}
/*		
		else if(SM.TestDisCnt > 2)
		{

#if ( Threephase == YesCheck ) //三相		
			*(Point+1)=0x00;
			*(Point+0)=0x11;	
#else
			*(Point+1)=0x00;
			*(Point+0)=0x11;	
#endif

			DspNum( Point, 2, &LCDSeg[DS_BDig] , 0 );	
			DisObisCode(&LCDSeg[0],10);				
			LcdTxtDisplay( LCDSeg, FLCDSeg );		
					
		}
*/
		else 
		{
		
//			*(Point+1)=CRCH;
//			*(Point+0)=CRCL;
			RAM_Write( Point, SM.CPUCRC, 2 );
			
			DspNum( Point, 2, &LCDSeg[DS_BDig] , 0 );	
			DisObisCode(&LCDSeg[0],11);				
			LcdTxtDisplay( LCDSeg, FLCDSeg );		
					
		}		
		return;
   	}   	


/*
	if(SM.menustep2 > 0)
	{
   		for( i=0; i<4; i++ ) 
	   		{
//				LCDSeg[DS_BDig + i] = DisplayCharecter4[i];
				Buff[i] = DisplayCharecter4[i];
				NumberConvert(&LCDSeg[14 - 2*i],&Buff[i]);		
			}
			LcdTxtDisplay( LCDSeg, FLCDSeg );
   			return;	
	}	



 	if((SM.menustep3<7)&&(SM.menustep3!=0))
	{   	
			E2P_RData(Point,TempClkAdd,7);
			switch(SM.menustep3)
			{
			case 1:
					*(Point+1)=0x20;
					DspNum( Point, 2, &LCDSeg[DS_BDig] ,0);
   					for( i=0; i<2; i++ ) 
	   				{
					Buff[i] = DisplayCharecter5[i];
					NumberConvert(&LCDSeg[14 - 2*i],&Buff[i]);		
					}					
					break;		
			case 2:
					*(Point)=0x00;
					DspNum( Point, 2, &LCDSeg[DS_BDig] ,0);
					
					*(LCDSeg + 2 )&= ~(DS_f+DS_e+DS_d);	//高位不显示
					*(LCDSeg + 3 )&= ~(DS_f+DS_e+DS_d+DS_b);	//高位不显示	
					
					*(LCDSeg + 0 )&= ~(DS_f+DS_e+DS_d);	//高位不显示
					*(LCDSeg + 1 )&= ~(DS_f+DS_e+DS_d+DS_b);	//高位不显示	
					
					*(LCDSeg + 0 )|=DS_e;
					*(LCDSeg + 2 )|=DS_e;
					
   					for( i=0; i<2; i++ ) 
	   				{
					Buff[i] = DisplayCharecter6[i];
					NumberConvert(&LCDSeg[14 - 2*i],&Buff[i]);		
					}	
					break;				
			case 3:
					*(Point)=*(Point+2);				
					DspNum( Point, 1, &LCDSeg[DS_BDig] ,0);	
					
					*(LCDSeg + 4 )|=DS_e;
					*(LCDSeg + 6 )|=DS_e;
					
   					for( i=0; i<2; i++ ) 
	   				{
					Buff[i] = DisplayCharecter7[i];
					NumberConvert(&LCDSeg[14 - 2*i],&Buff[i]);		
					}			
					break;
			case 4:
      				    	 *(Point)=0x00;
         				 *(Point+1)=*(Point+4);
					DspNum( Point, 2, &LCDSeg[DS_BDig] ,0);	
					
					*(LCDSeg + 2 )&= ~(DS_f+DS_e+DS_d);	//高位不显示
					*(LCDSeg + 3 )&= ~(DS_f+DS_e+DS_d+DS_b);	//高位不显示	
					
					*(LCDSeg + 0 )&= ~(DS_f+DS_e+DS_d);	//高位不显示
					*(LCDSeg + 1 )&= ~(DS_f+DS_e+DS_d+DS_b);	//高位不显示	
					
					*(LCDSeg + 0 )|=DS_e;
					*(LCDSeg + 2 )|=DS_e;
					
   					for( i=0; i<2; i++ ) 
	   				{
					Buff[i] = DisplayCharecter8[i];
					NumberConvert(&LCDSeg[14 - 2*i],&Buff[i]);		
					}			
					break;
			case 5:
					DspNum( Point+5, 1, &LCDSeg[DS_BDig] ,0);	
					
					*(LCDSeg + 4 )|=DS_e;
					*(LCDSeg + 6 )|=DS_e;
					
   					for( i=0; i<2; i++ ) 
	   				{
					Buff[i] = DisplayCharecter9[i];
					NumberConvert(&LCDSeg[14 - 2*i],&Buff[i]);		
					}								
					break;
			case 6:
					DspNum( Point+6, 1, &LCDSeg[DS_BDig] ,0);	
					
					*(LCDSeg + 4 )|=DS_e;
					*(LCDSeg + 6 )|=DS_e;
					
   					for( i=0; i<2; i++ ) 
	   				{
					Buff[i] = DisplayCharecter10[i];
					NumberConvert(&LCDSeg[14 - 2*i],&Buff[i]);		
					}				
					break;
			default:break;
			}	
			LcdTxtDisplay( LCDSeg, FLCDSeg );	
			return;
	}





   	switch( SM.menustep1 )
   	{
   		case 1:
   			for( i=0; i<5; i++ ) 
	   		{
//				Buff[DS_BDig + 9 - i] = DisplayCharecter1[i];
//				NumberConvert(&LCDSeg[i],&Buff[i]);		
				Buff[i] = DisplayCharecter1[i];
				NumberConvert(&LCDSeg[14 - 2*i],&Buff[i]);			
			}
			LcdTxtDisplay( LCDSeg, FLCDSeg );
   			return;
   		case 2:
   			for( i=0; i<7; i++ ) 
	   		{
//				LCDSeg[DS_BDig + i] = DisplayCharecter2[i];
				Buff[i] = DisplayCharecter2[i];
				NumberConvert(&LCDSeg[14 - 2*i],&Buff[i]);							
			}
			LcdTxtDisplay( LCDSeg, FLCDSeg );
   			return;
   		case 3:
   			for( i=0; i<5; i++ ) 
	   		{
//				LCDSeg[DS_BDig + i] = DisplayCharecter3[i];
				Buff[i] = DisplayCharecter3[i];
				NumberConvert(&LCDSeg[14 - 2*i],&Buff[i]);						
			}
			LcdTxtDisplay( LCDSeg, FLCDSeg );
   			return;
//   		case 4:
// 			for( i=0; i<4; i++ ) 
//	   		{
////				LCDSeg[DS_BDig + i] = DisplayCharecter4[i];
//				Buff[i] = DisplayCharecter4[i];
//				NumberConvert(&LCDSeg[DS_BDig + 2*i],&Buff[i]);		
//			}
//			LcdTxtDisplay( LCDSeg, FLCDSeg );
// 			return;	

   		default: 
   			SM.menustep1 = 0;
   			break;	
   	}

*/
	
/*
	if(SM.menustep)
	{
		if(SM.menustep==5)
		{
			if(SM.setkey_sum<15)
			{
//				if(SM.setkey_sum==0)
//					{Mon_Read(Buff,Disk.HisMon,6,6);}
//				else if(SM.setkey_sum==1)	
//					{Mon_Read(Buff,Disk.HisMon,6,12);}
//				else if(SM.setkey_sum==2)	
//					{Mon_Read(Buff,Disk.HisMon,6,18);}
//				else if(SM.setkey_sum==3)	
//					{Mon_Read(Buff,Disk.HisMon,6,24);}
//				else if(SM.setkey_sum==4)	
//					{Mon_Read(Buff,Disk.HisMon,6,30);}

				if(SM.setkey_sum<10)
				Mon_Read(Buff,Disk.HisMon , 6 , 6*(SM.setkey_sum + 1));	
				else 
				Mon_Read(Buff,Disk.HisMon , 6 , 186+6*(SM.setkey_sum - 10));	
				
					
//				LongData = BCD4_Long( Point ) / 10;
//				Long_BCD4( Point, LongData );	
				RAM_Write(Point,Point + 1, 6);				
				DspNum( Point, 4, &LCDSeg[DS_BDig], 1 );
				
			
				*(LCDSeg + 7 )|=0x21;	//
				*(LCDSeg + 6 )|=0x21;	//
				*(LCDSeg + 5 )|=0x21;	//
				*(LCDSeg + 2 )|=0x20;	//
				*(LCDSeg + 1 )|=0x21;	//
				*(LCDSeg + 0 )|=0x10;	//						
#if (FWCity == Gdansk)							
#else
//				LCDSeg[2]=0;	//电量最高位显示？
#endif
			}
			else if(SM.setkey_sum==15)
			{
				//历史日期
				Mon_Read(Buff,Disk.HisMon,3,3);
				Buff[3]=0x20;
				DspNum( Point, 4, &LCDSeg[DS_BDig] ,2 );
				LCDSeg[8] |= DS_b;	//'.'
			}
			else if(SM.setkey_sum==16)
			{
				//历史时间				
				Mon_Read(Buff,Disk.HisMon,3,0);
				DspNum( Point, 3, &LCDSeg[DS_BDig] ,0 );
				LCDSeg[8] |= DS_a;	//':'	//v04
				LCDSeg[4] |= DS_a;	//':'
			}
			else if(SM.setkey_sum==17)
				{//历史最大需量
//				Mon_Read(Buff,Disk.HisMon,3,36);
				Mon_Read(Buff,Disk.HisMon , 3 , 216);	
				LongData = BCD4_Long( Point ) / 10;
				Long_BCD4( Point, LongData );	
				DspNum( Point, 3, &LCDSeg[DS_BDig] , 4 ); //三位小数
//				LCDSeg[4] = 0;	//'.'
			}
//			else if(SM.setkey_sum==18)
//				{//历史TOP10的和
//				Mon_Read(Buff,Disk.HisMon,4,41);
//				DspNum( &Buff[1], 3, &LCDSeg[DS_BDig] , 2 );
////				LCDSeg[4] = 0;	//'.'
//			}
//			else if(SM.setkey_sum==19)
//				{//历史次数
//				Mon_Read(Buff,Disk.HisMon,2,39);
//				DspNum( Point, 2, &LCDSeg[DS_BDig] , 0 );
//			}
			
			DisObisCode(&LCDSeg[0],SM.setkey_sum);//obis code
	
			LcdTxtDisplay( LCDSeg, FLCDSeg );
				
//			return 1;	
			return ;				
		}	

		LcdTxtDisplay( LCDSeg, FLCDSeg );
			
//		return 1;		
		return ;			
	}

*/
/*
	if(( Flag.Power & F_PwrUp) == 0 )
		{
//		LongData=SYSCTL->OSC_CTRL1;
//		LongData=SYSCTL->SYS_PD;
//		LongData=SYSCTL->OSC_CTRL2;
//		LongData=SYSCTL->MOD0_EN;
//		LongData=SYSCTL->MOD1_EN;
//		LongData=SYSCTL->INTC_EN;

		LongData=SM.PowerPp;
		RAM_Write(Point,(unsigned char *)&LongData,4);
		DspNum( Point, 4, &LCDSeg[DS_BDig] , 0 );
		LcdTxtDisplay( LCDSeg, FLCDSeg );			
		return;
		}
*/


//	if(( Disk.DisInv == 0) || ( (Flag.Disk & F_KeyInt) != 0)|| ((( Flag.Power & F_PwrUp ) != 0 ))
//	||((( Flag.Clk & F_DisSec ) != 0 ) && (( Disk.ItemPtr == 10 ) || ( Disk.ItemPtr == 11 )||
//		((( Flag.Power & F_PwrUp) != 0 )&& ((Disk.ItemPtr == 0 )||(Disk.ItemPtr<5))))));
//	if(( Disk.DisInv == 0) || ( (Flag.Disk & F_KeyInt) != 0)
//	||((( Flag.Clk & F_DisSec ) != 0 ) && (( Disk.ItemPtr == 14 ) || ( Disk.ItemPtr == 15 )||
//		((( Flag.Power & F_PwrUp) != 0 )&& ((Disk.ItemPtr == 0 )||(Disk.ItemPtr<7))))));	
//	if(( Disk.DisInv == 0) || ( (Flag.Disk & F_KeyInt) != 0)||( Flag.Clk & F_DisSec ) != 0 ) 
	if(( Disk.DisInv == 0) || ( (Flag.Disk & F_KeyInt) != 0)) 		
		;		
	else
	{
		if(Disk.ItemPtr != 9)
		LcdStateDisplay( LCDSeg, FLCDSeg );
		return;
	}	  
	
	if((( Disk.ItemPtr == 5 )||(  Disk.ItemPtr == 6 ))&&(( Flag.Power & F_PwrUp ) == 0 )) GetTime();
	
	  
//	if(((Flag.Disk & F_KeyInt) == 0) && ( Flag.Clk & F_Sec ) == 0 )   return;
//	if(((Flag.Disk & F_KeyInt) == 0) && ( Flag.Clk & F_DisSec ) == 0 )   return;
	Flag.Disk &= ~F_KeyInt;
  
   	if( Disk.DisInv == 0 )
   	{

 //  		Disk.DisInv = ConstInv;//Para.RDspInv;	
// 		if(( Flag.Power & F_PwrUp ) == 0 )		
//     			Disk.DisInv = Para.RDspInv+1;//Para.RDspInv;			
//		else
     			Disk.DisInv = Para.RDspInv;//Para.RDspInv;				

     		
//   		Disk.ItemPtr ++;
//		if(Disk.ItemPtr >= 21 ) Disk.ItemPtr =0;
   		Flag.Disk &=~ F_KeyStart;
   		GetNextCode(0);
   		
//		Disk.ItemPtr = 0;
//		Disk.ItemNo = 0;
//		Disk.DisInv = 60;	
   	}	
	
//   	Disk.ItemPtr = 0;

/*
	if(((Temp & 0xf0)== Mperr1)&&(Flag.AlarmFlg[0]&(F_AlarmCoverOpen+F_AlarmTCoverOpen + F_AlarmMagnet)))
	{
		Disk.ItemPtr++;
		Temp = DisTab[Disk.ItemPtr].Length;	
	}

	if(((Temp & 0xf0)== Mperr )&&((Flag.AlarmFlg[0] & F_AlarmE2P)==F_AlarmE2P))
	{
		Disk.ItemPtr++;
		Temp = DisTab[Disk.ItemPtr].Length;			
	}
*/
	
//	if(((Temp & 0xf0)== Mperr1)&&((Flag.AlarmFlg[0]&(F_AlarmCoverOpen+F_AlarmTCoverOpen + F_AlarmMagnet)) == 0))
//	{
//		Disk.ItemPtr++;
//		Temp = DisTab[Disk.ItemPtr].Length;	
//	}
//
//	if(((Temp & 0xf0)== Mperr )&&(((Flag.AlarmFlg[0] & F_AlarmE2P)==F_AlarmE2P)== 0))
//	{
//		Disk.ItemPtr++;
//		Temp = DisTab[Disk.ItemPtr].Length;			
//	}


//	if(SM.TestCnt)
//		Disk.ItemPtr = SM.FeeNoTestCnt;	


//	if(SM.TestCnt)
//		if((SM.TestCnt)&&(SM.menustep2 == 0))
		if((SM.TestCnt)&&(SM.menustep2 == 0)&&(( Flag.Power & F_PwrUp ) != 0 ))			
		{
		
		if((SM.Tariffsnu != 0x11)&&(SM.Tariffsnu != 0x22))
			Disk.ItemPtr = SM.FeeNo;
		else
			Disk.ItemPtr = 0;	
		
		}
	
//	if((Flag.AlarmFlg[0] & F_AlarmE2P)==F_AlarmE2P)
	if((Flag.AlarmFlg[0] & (F_AlarmE2P+F_AlarmCRCFail))!=0)		
	{
		Disk.ItemPtr = 8;			
	}
	
	if((Disk.ItemPtr == 8)&&(SM.menustep2 == 0))
		{
			if((Flag.AlarmFlg[0] & (F_AlarmE2P+F_AlarmCRCFail)) == 0)		
			{
   				GetNextCode(0);	
			}
		}
	
	Temp = DisTab[Disk.ItemPtr].Length;
	Addr = (unsigned short)DisTab[Disk.ItemPtr].Addr;
	Length = DisTab[Disk.ItemPtr].Length & 0x0f;
	Unit = DisTab[Disk.ItemPtr].State5;//单位
	Hismon = DisTab[Disk.ItemPtr].ComID2 & 0x3F;//历史月份
	RWMode = DisTab[Disk.ItemPtr].ComID2 & 0xC0;//DisE2P/DisFLA/	DisROM
	
	switch( Temp & 0xf0 )
	{
		case 0x00: //电量
				if(RWMode == DisE2P)
				Read_CMonEC( Point, Addr );
				else
//				Mon_Read(Point,3-Hismon,6,Addr);
				Mon_Read(Point,15-Hismon,6,Addr);				
				
				if(SM.TestCnt)
				{
					Digit = 3;	
				}
				else if( (Para.RDisDigitNum&0x0F) == 0 )
				{
					Digit = 0;
//					LongData = BCD4_Long( Point ) / 1000;
//					Long_BCD4( Point, LongData );	
					RAM_Write(Point,Point + 1, 6);	
					ECDisplayMove(Point);						
				}
				else if( (Para.RDisDigitNum&0x0F) == 1 )
				{
					Digit = 1;
//					LongData = BCD4_Long( Point ) / 100;
//					Long_BCD4( Point, LongData );
					RAM_Write(Point,Point + 1, 6);	
				}
				else if((Para.RDisDigitNum&0x0F) == 2)
				{
					 Digit = 2;
//					 LongData = BCD4_Long( Point ) / 10;
//					 Long_BCD4( Point, LongData );	
					 ECDisplayMove(Point);
				} 
				else 
				{
					Digit = 3;		
				}	
					 
				DspNum( Point, 4, &LCDSeg[DS_BDig], Digit );

#if ( Threephase == YesCheck ) //三相		
				switch((Para.RDisDigitNum&0x0F)+(((Para.RDisDigitNum)>>4)&0x0F))
					{
					case 0x05: //5位
						*(LCDSeg + 5 )&= ~0xEF;	//高位不显示					
					case 0x06: //6位
						*(LCDSeg + 6 )&= ~0xEF;	//高位不显示
					case 0x07: //7位
						*(LCDSeg + 7 )&= ~0xEF;	//高位不显示
					break;

					default: break;
					}
				
//				if(Unit == Unit_Kw)
//				{/****kWh****/	
				*(LCDSeg + 12)|=0x20;	//k
				*(LCDSeg + 12)|=0xC0;	//W
				*(LCDSeg + 11)|=0xF0;	//W		
				*(LCDSeg + 9)|=0x30;	//h				
//				}
//				else	  
//				{/****kvarh****/	
//				*(LCDSeg + 11)|=0x20;	//k
//				*(LCDSeg + 10)|=0x01;	//v
//				*(LCDSeg + 9)|=0x01;	//a		
//				*(LCDSeg + 8)|=0x01;	//a		
//				*(LCDSeg + 7)|=0x21;	//a	
//				*(LCDSeg + 6)|=0x01;	//a					
//				*(LCDSeg + 5)|=0x01;	//r						
//				*(LCDSeg + 4)|=0x20;	//h		
//				}
#else
				switch((Para.RDisDigitNum&0x0F)+(((Para.RDisDigitNum)>>4)&0x0F))
					{
					case 0x05: //5位
						*(LCDSeg + 10 )&= ~0x0E;	//高位不显示
						*(LCDSeg + 11 )&= ~0x1E;	//高位不显示					
					case 0x06: //6位
						*(LCDSeg + 12 )&= ~0x0E;	//高位不显示
						*(LCDSeg + 13 )&= ~0x1E;	//高位不显示
					case 0x07: //7位
						*(LCDSeg + 14 )&= ~0x0E;	//高位不显示
						*(LCDSeg + 15 )&= ~0x1E;	//高位不显示
					break;

					default: break;
					}
				
				if(Unit == Unit_Kw)
				{/****kWh****/	
				*(LCDSeg + 11)|=0x20;	//k
				*(LCDSeg + 10)|=0x21;	//W
				*(LCDSeg + 9)|=0x21;	//W		
				*(LCDSeg + 8)|=0x20;	//W		
				*(LCDSeg + 3)|=0x20;	//W		
				*(LCDSeg + 5)|=0x21;	//h				
				}
				else	  
				{/****kvarh****/	
				*(LCDSeg + 11)|=0x20;	//k
				*(LCDSeg + 10)|=0x01;	//v
				*(LCDSeg + 9)|=0x01;	//a		
				*(LCDSeg + 8)|=0x01;	//a		
				*(LCDSeg + 7)|=0x21;	//a	
				*(LCDSeg + 6)|=0x01;	//a					
				*(LCDSeg + 5)|=0x01;	//r						
				*(LCDSeg + 4)|=0x20;	//h		
				}
				
#endif		
				
				break;
		case Mpmax:  //最大需量
				if(RWMode == DisE2P)	//if(Disk.ItemPtr < 84)
				E2P_RECData( Point, Addr, Length);		
				else
//				Mon_Read(Point,3-Hismon,3,Addr);	
				Mon_Read(Point,15-Hismon,3,Addr);					
				
				*(Point+3) = 0;
				
				LongData = BCD4_Long( Point ) / 10;
				Long_BCD4( Point, LongData );	
				
				DspNum( Point, Length, &LCDSeg[DS_BDig] , 3 );

#if ( Threephase == YesCheck ) //三相		
				*(LCDSeg + 5 )&= ~0xEF;	//高位不显示			
			
				/****kW****/	
				*(LCDSeg + 12)|=0x20;	//k
				*(LCDSeg + 12)|=0xC0;	//W
				*(LCDSeg + 11)|=0xF0;	//W			
#else
				*(LCDSeg + 10 )&= ~0x0E;	//高位不显示
				*(LCDSeg + 11 )&= ~0x1E;	//高位不显示				
			
				/****kW****/	
				*(LCDSeg + 11)|=0x20;	//k
				*(LCDSeg + 10)|=0x21;	//W
				*(LCDSeg + 9)|=0x21;	//W		
				*(LCDSeg + 8)|=0x20;	//W		
				*(LCDSeg + 3)|=0x20;	//W		
#endif

		
				break;			
		case MpIns:  //合相正反向功率
#if ( Threephase == YesCheck ) //三相				
				RAM_Write(Point,Para.PtABC+Addr,4);
#else
				RAM_Write(Point,Para.Pt,4);
#endif

//				*(Point+3) = 0;
//				LongData = BCD4_Long( Point ) / 10;
//				Long_BCD4( Point, LongData );		
				
				DspNum( Point+1, Length, &LCDSeg[DS_BDig] , 2 );

#if ( Threephase == YesCheck ) //三相		
				/****kW****/	
				*(LCDSeg + 12)|=0x20;	//k
				*(LCDSeg + 12)|=0xC0;	//W
				*(LCDSeg + 11)|=0xF0;	//W		
#else
				/****kW****/	
				*(LCDSeg + 11)|=0x20;	//k
				*(LCDSeg + 10)|=0x21;	//W
				*(LCDSeg + 9)|=0x21;	//W		
				*(LCDSeg + 8)|=0x20;	//W		
				*(LCDSeg + 3)|=0x20;	//W		
#endif
		
				break;

		case MpInsF:  //分相功率


//				if(((Para.PWFlag & 0x01)&&(DisTab[Disk.ItemPtr].ComID4 == 0x28)) 
//					||((Para.PWFlag & 0x02)&&(DisTab[Disk.ItemPtr].ComID4 == 0x29))
//					||((Para.PWFlag & 0x04)&&(DisTab[Disk.ItemPtr].ComID4 == 0x2A))
//					||(((Para.PWFlag & 0x01)==0)&&(DisTab[Disk.ItemPtr].ComID4 == 0x18))
//					||(((Para.PWFlag & 0x02)==0)&&(DisTab[Disk.ItemPtr].ComID4 == 0x19))
//					||(((Para.PWFlag & 0x04)==0)&&(DisTab[Disk.ItemPtr].ComID4 == 0x1A)))
				if(((Para.PWFlag & 0x01)&&(DisTab[Disk.ItemPtr].ComID4 == 0xA6)) 
					||((Para.PWFlag & 0x02)&&(DisTab[Disk.ItemPtr].ComID4 == 0xB6))
					||((Para.PWFlag & 0x04)&&(DisTab[Disk.ItemPtr].ComID4 == 0xC6))
					||(((Para.PWFlag & 0x01)==0)&&(DisTab[Disk.ItemPtr].ComID4 == 0xA7))
					||(((Para.PWFlag & 0x02)==0)&&(DisTab[Disk.ItemPtr].ComID4 == 0xB7))
					||(((Para.PWFlag & 0x04)==0)&&(DisTab[Disk.ItemPtr].ComID4 == 0xC7)))					
					RAM_Write(Point,Para.Pa+Addr,4);
				else
					RAM_Fill(Point, 4);
				
//				*(Point+3) = 0;
//				LongData = BCD4_Long( Point ) / 10;
//				Long_BCD4( Point, LongData );		
				
				DspNum( Point+1, Length, &LCDSeg[DS_BDig] , 2 );

#if ( Threephase == YesCheck ) //三相		
				/****kW****/	
				*(LCDSeg + 12)|=0x20;	//k
				*(LCDSeg + 12)|=0xC0;	//W
				*(LCDSeg + 11)|=0xF0;	//W		
#else
				/****kW****/	
				*(LCDSeg + 11)|=0x20;	//k
				*(LCDSeg + 10)|=0x21;	//W
				*(LCDSeg + 9)|=0x21;	//W		
				*(LCDSeg + 8)|=0x20;	//W		
				*(LCDSeg + 3)|=0x20;	//W		
#endif
				
				break;

		case Mua:  //电压电流
		/*
				if(RWMode == DisROM)	//if(Disk.ItemPtr < 106)
				RAM_Write( Point, Para.Ua+Addr, 3);		//电压		
				else
				{
				RAM_Write( Point, Para.Ia+Addr, 4);		//电流		
				LongData = BCD4_Long( Point ) / 10;
				Long_BCD4( Point, LongData );					
				}
				
				DspNum( Point, Length, &LCDSeg[DS_BDig] , 2 );
				
				*(LCDSeg + 10 )&= ~(DS_f+DS_e+DS_d);	//高位不显示
				*(LCDSeg + 11 )&= ~(DS_f+DS_e+DS_d+DS_b);	//高位不显示
		*/		

				if(RWMode == DisROM)	//if(Disk.ItemPtr < 106)
					{
#if ( Threephase == YesCheck ) //三相							
					RAM_Write( Point, Para.Ua+Addr, 4);		//电压		
#else
					RAM_Write( Point, Para.Ua, 4);		//电压	
					LongData = BCD4_Long( Point ) / 10;
					Long_BCD4( Point, LongData );							
#endif
					DspNum( Point+1, 2, &LCDSeg[DS_BDig] , 0 );				
					*(LCDSeg + 3 )&= ~0xEF;	//高位不显示		
					
					}
				else
					{
#if ( Threephase == YesCheck ) //三相							
					RAM_Write( Point, Para.Ia+Addr, 4);		//电流		
#else
					RAM_Write( Point, Para.Ia, 4);		//电流		
					LongData = BCD4_Long( Point ) / 10;
					Long_BCD4( Point, LongData );							
#endif

					DspNum( Point+1, 2, &LCDSeg[DS_BDig] , 1 );							
					}
				
#if ( Threephase == YesCheck ) //三相		
				if(Unit == Unit_V)
					{
					/****V****/	
					*(LCDSeg + 12)|=0xC0;	//V
					}
				else	  
					{
					/****A****/	
					*(LCDSeg + 9 )|=0x40;	//	
					*(LCDSeg + 10 )|=0x50;	//						
					*(LCDSeg + 11 )|=0x70;	//						
					}
				
#else
				if(Unit == Unit_V)
					{
					/****V****/	
					*(LCDSeg + 10)|=0x21;	//V
					}
				else	  
					{
					/****A****/	
					*(LCDSeg + 3 )|=0x20;	//	
					*(LCDSeg + 6 )|=0x021;	//						
					*(LCDSeg + 7 )|=0x01;	//						
					*(LCDSeg + 8 )|=0x20;	//	
					*(LCDSeg + 9 )|=0x01;	//	
					}
				
#endif				
				
				break;

		case Mvbat:  //电池电压

				RAM_Write( Point, Para.UClockBat, 2);		//电压		
				
				DspNum( Point, Length, &LCDSeg[DS_BDig] , 2 );
#if ( Threephase == YesCheck ) //三相						
					/****V****/	
					*(LCDSeg + 12)|=0xC0;	//V
#else
					/****V****/	
					*(LCDSeg + 10)|=0x21;	//V
#endif					
				break;		
				
		case MTbat:  //电池工作时间
/*								
				E2P_RData( Point, Addr, Length);	//XXXXXX:XX (hours)			
				DspNum( Point, 4, &LCDSeg[DS_BDig] , 0 );

#if ( Threephase == YesCheck ) //三相						
				*(LCDSeg + 8)|=0x40;	//:
#else
				*(LCDSeg + 0)|=0x10;	//:
#endif	
*/			
//				E2P_RData( Buff, BatteryWorkTime, 5);//XXXXXX.XX (days)
				E2P_RData( Point, Addr, Length);		

				LongData = BCD4_Long( &Buff[1] );
				Buff[0] = Byte_BCD(LongData%24);
				LongData = LongData/24;
				Long_BCD4( &Buff[1] , LongData );	
				
				DspNum( Point, 4, &LCDSeg[DS_BDig] , 2 );						

				break;	

		case Mevent:  //事件次数
		
				E2P_RData( (unsigned char *)&LongData, Addr, Length);	
				
				Long_BCD4( Point, LongData );	
								
				DspNum( Point, 4, &LCDSeg[DS_BDig] , 0 );
				
				break;		
				
		case Mpara:  //参数
				E2P_RData( Point, Addr, Length);				
				if( Length > 4 ) 
				{	
//					Length = 4; 	//表号
					_ASC_BCD( Buff1, Point, 4 );	
					DspNum( Buff1, 4, &LCDSeg[DS_BDig] , 0 );
				}
				else
					DspNum( Point, Length, &LCDSeg[DS_BDig] , 0 );
				break;
//		case Mperr1: //F.F.1			
//				RAM_Fill( Point, 10);	
//				DspNum( Point, 4, &LCDSeg[DS_BDig], 0 );							
//				if( Flag.AlarmFlg[0] & F_AlarmCoverOpen )	//开盖指示
//				{
//					LCDSeg[2] |= 0x0E;	
//					LCDSeg[3] |= 0x1E;						
//				}
//				
//				if( Flag.AlarmFlg[0] & F_AlarmTCoverOpen )	//开端指示	
//				{
//					LCDSeg[4] |= 0x0E;	
//					LCDSeg[5] |= 0x1E;							
//				}
//					
//				if( Flag.AlarmFlg[0] & F_AlarmMagnet )	//磁场指示	
//				{
//					LCDSeg[6] |= 0x0E;	
//					LCDSeg[7] |= 0x1E;			
////					#if (Threephase == YesCheck) //13.2.25wwl
////					LCDSeg[27] |= DS_a;
////					#else//13.2.25wwl
//					LCDSeg[13] |= DS_a;
////					#endif//13.2.25wwl
//				}				
//				break;
		case Mperr: //F.F.0				
					
				RAM_Fill( Point, 10);	

				if(Addr == 0x01)
					{			
						if( Flag.AlarmFlg[0] & F_AlarmCoverOpen )	//开盖指示
						{
						*(Point+0) |= 0x10;
						}
						if( Flag.AlarmFlg[0] & F_AlarmTCoverOpen )	//开端指示
						{
						*(Point+1) |= 0x01;
						}		
						if( Flag.AlarmFlg[0] & F_AlarmMagnet)	//磁场指示
						{
						*(Point+1) |= 0x10;
						}		
						if( Flag.AlarmFlg[0] & F_AlarmReverse)	//反向指示
						{
						*(Point+2) |= 0x01;
						}					
					}
				else
					{
						if((Flag.AlarmFlg[0] & F_AlarmCRCFail)==F_AlarmCRCFail)
							{
							*(Point+2) = 0x10;
							}
						if((Flag.AlarmFlg[0] & F_AlarmE2P)==F_AlarmE2P)
							{
							*(Point+2) = 0x01;
							}		
						
					}
				
				DspNum( Point, 4, &LCDSeg[DS_BDig], 0 );


				break;	
		case Mdate:  //年、月、日 	
				if(RWMode == DisROM)	//if(Disk.ItemPtr == 95)
				RAM_Write( Point, Clk.Day, 3);		//日期
				else if(RWMode == DisE2P)	//if(Disk.ItemPtr < 84)
				{
				E2P_RECData( Point, Addr, 5);	
				RAM_Write( Point+0, Point+2, 3);		//日期
				}
				else
				Mon_Read(Point,15-Hismon/2,3,Addr);	
//				Mon_Read(Point,15-Hismon,3,Addr);					
				
				*(Point+3)=0x20;				
				
				DspNum( Point, 4, &LCDSeg[DS_BDig] ,2 );			

#if ( Threephase == YesCheck ) //三相						
				LCDSeg[4] |= 0x10;	//'.'
#else
				LCDSeg[8] |= 0x10;	//'.'
#endif	

				break;	
		case Mtime:  //时、分、秒
				
				if(RWMode == DisROM)	//if(Disk.ItemPtr == 96)
				RAM_Write( Point, Clk.Sec, 3);		//时间
				else if(RWMode == DisE2P)	//if(Disk.ItemPtr < 84)
				{
				E2P_RECData( Point+1, Addr, 5);	
				*(Point+0)=0;
				}
				else
				Mon_Read(Point,15-Hismon/2,3,Addr);		
//				Mon_Read(Point,15-Hismon,3,Addr);						
				
				DspNum( Point, 3, &LCDSeg[DS_BDig] ,0 );
#if ( Threephase == YesCheck ) //三相						
				LCDSeg[8] |= 0xC0;	//':'	
#else
				LCDSeg[0] |= 0x10;	//':'	
				LCDSeg[10] |= 0x10;	//':'
#endif					
				break;	
//		case Mpjscnt:
//				E2P_RData( Point, Addr, Length);
//				DspNum( Point, 1, &LCDSeg[DS_BDig] ,0 );
////				LCDSeg[0] |= DS_h;
//				break;	

		case MpCRC:  //CRC

				if(Addr == 1)
					{
					*(Point+1)=CRCH;
					*(Point+0)=CRCL;
					}
				else
					{
#if ( Threephase == YesCheck ) //三相		
					*(Point+1)=0x00;
					*(Point+0)=0x11;	
#else
					*(Point+1)=0x00;
					*(Point+0)=0x11;	
#endif			
					}
				DspNum( Point, Length, &LCDSeg[DS_BDig] , 0 );
				break;	
				
		case MFull:  //全屏

				for( i=0; i<30; i++ ) 	
   				{	
					LCDMEM[i] = 0xFF;
				}	
				fnLcd_RefreshLcdBuf();
				return;	
				
		case Mtari:  //时段方案名称
				E2P_RData( Point, CurrRunSdName, 8);	
#if ( Threephase == YesCheck ) //三相		
				LCDSeg[0]=TariffNameConvert(*Point++);
				LCDSeg[1]=TariffNameConvert(*Point++);
				LCDSeg[2]=TariffNameConvert(*Point++);
				LCDSeg[3]=TariffNameConvert(*Point);
#else
				Buff1[0]=TariffNameConvert(*Point++);
				Buff1[1]=TariffNameConvert(*Point++);
				Buff1[2]=TariffNameConvert(*Point++);
				Buff1[3]=TariffNameConvert(*Point);
				NumberConvert(&LCDSeg[0],&Buff1[0]);		
				NumberConvert(&LCDSeg[2],&Buff1[1]);	
				NumberConvert(&LCDSeg[4],&Buff1[2]);	
				NumberConvert(&LCDSeg[6],&Buff1[3]);	
#endif	
	
				break;	
		default: break;	
	}	
//		if(( Temp & 0xF0 ) != Mtest )
	DisObisCode(&LCDSeg[0],Disk.ItemPtr);	
	LcdTxtDisplay( LCDSeg, FLCDSeg );
}


//void DisObisCode(unsigned char *Point,unsigned char DisItem)
void DisObisCode(unsigned char *Point,unsigned short DisItem)	
{
#if ( Threephase == YesCheck ) //三相		
	NumberConvert1(Point+8,(unsigned char*)&DisTab[DisItem].Obis0);
	
	NumberConvert1(Point+10,(unsigned char*)&DisTab[DisItem].Obis1);
	
	NumberConvert1(Point+12,(unsigned char*)&DisTab[DisItem].Obis2);

	NumberConvert1(Point+14,(unsigned char*)&DisTab[DisItem].Obis3);
	
	NumberConvert1(Point+16,(unsigned char*)&DisTab[DisItem].Obis4);
	
	NumberConvert1(Point+18,(unsigned char*)&DisTab[DisItem].Obis5);//
#else
	NumberConvert1(Point+16,(unsigned char*)&DisTab[DisItem].Obis0);
	
	NumberConvert1(Point+18,(unsigned char*)&DisTab[DisItem].Obis1);
	
	NumberConvert1(Point+22,(unsigned char*)&DisTab[DisItem].Obis2);

	NumberConvert1(Point+24,(unsigned char*)&DisTab[DisItem].Obis3);
	
	NumberConvert1(Point+26,(unsigned char*)&DisTab[DisItem].Obis4);
	
	NumberConvert1(Point+28,(unsigned char*)&DisTab[DisItem].Obis5);//
#endif	

}


void LcdStateDisplay( unsigned char *LCDSeg, unsigned char *FLCDSeg )
{
	short i;
	
	ActiveDisp( LCDSeg, FLCDSeg );

	for(i=0;i<30;i++)	//8com	
	{
//		if(( Flag.Power & F_PwrUp ) == 0 )LCDSeg[i] = Disk.LXTab[i];
		LCDSeg[i] |= FLCDSeg[i];
		LCDMEM[i] |= LCDSeg[i];
//		if(( Flag.Disk & F_Flash ) == 0) 
		if(( Flag.Disk & F_Flash ) == 0) 
		{	
//			if((Flag.ErrFlg & F_ErrMeasFlashDis) == F_ErrMeasFlashDis)
//				LCDMEM[i] = 0;
//			else	
				LCDMEM[i] ^=  FLCDSeg[i];
			
		}	
	}

	fnLcd_RefreshLcdBuf();
//#if (Threephase == YesCheck) 	
//	if( Flag.AlarmFlg[0] & F_AlarmPhs )
//	{//逆相序	
//		LCDMEM[16] &=~ (DS_c + DS_b + DS_g); 
//		LCDMEM[16] |= LCDSeg[16];
//	}
////#else
////	LCDMEM[16] &=~ (DS_c + DS_b + DS_g); 
////	LCDMEM[16] |= LCDSeg[16];
//#endif
}	
void LcdTxtDisplay( unsigned char *LCDSeg, unsigned char *FLCDSeg )
{
	short i;
	
	ActiveDisp( LCDSeg, FLCDSeg );
	for(i=0;i<30;i++)	//8com	
	{
		
		LCDSeg[i] |= FLCDSeg[i];
//		Disk.LXTab[i] = LCDSeg[i];
		if(( Flag.Disk & F_Flash ) == 0)  //LCDSeg[i] ^=  FLCDSeg[i];
		{	
			LCDSeg[i] ^=  FLCDSeg[i];
//			if((Flag.ErrFlg & F_ErrMeasFlashDis) == F_ErrMeasFlashDis)
//				LCDSeg[i] = 0;
		}
		LCDMEM[i] = LCDSeg[i];
	}	
	fnLcd_RefreshLcdBuf();
}	



void GetNextCode( unsigned Mode )	//Mode = 0 为自动论显，其他的按键轮显
{
//	unsigned char i;
	unsigned short i;	
	unsigned char Temp,DisSNum;
//	unsigned char Buff[4];
	

//	Temp = (unsigned long)Para.RDisSwitch[2] * 65536 +(unsigned short)Para.RDisSwitch[1] * 256 + Para.RDisSwitch[0];	//显示开关
	Flag.Disk |= F_KeyInt;
	
	if(Disk.ItemSNo != 0)
	{
		if(Mode == 0)
		{	

			Temp = Para.RDisASwitch[89 - Disk.ItemANo];
			if(Temp == 0xFF )
			{
				Disk.ItemANo = 0;
				Temp = Para.RDisASwitch[89];
				if(Temp == 0xFF)
					Temp = 0x10;
			}
				
		}
		else
		{
			Temp = Para.RDisMSwitch[89 - Disk.ItemMNo];
			if(Temp == 0xFF )
			{
				Disk.ItemMNo = 0;
				Temp = Para.RDisMSwitch[89];
				if(Temp == 0xFF)
					Temp = 0x10;
			}
			
		}
		for(i=0;i<DisNum;i++)
		{
			if(DisTab[i].ComID4 == Temp)break;
		}
		if(i == DisNum)
			i = 0;
//		if((Temp >= 0xD0)&&(Temp <= 0xDF))
		if(((Temp >= 0xD0)&&(Temp <= 0xDF))||((Temp >= 0xE1)&&(Temp <= 0xE4)))			
		{	
			if(Temp == 0xDF)
//				DisSNum = Disk.DisHisMun*2;
				DisSNum = Disk.DisHisMun*2-1;			
			else	
//				DisSNum = Disk.DisHisMun;
				DisSNum = Disk.DisHisMun-1;
		}else		
			DisSNum = DisTab[i].ComID2&0x3F;
	
		if(i == DisNum) i = 0;
		
//		if(DisSNum < Disk.ItemSNo)
//		{	
		
		Disk.ItemPtr++;
		if((Disk.ItemPtr <= (DisSNum + i))&&(Disk.ItemPtr >= i))
//		if((Disk.ItemPtr < (DisSNum + i))&&(Disk.ItemPtr >= i))			
		{		
//			Disk.ItemSNo--;
			return;	
		}

			
		
//		Disk.ItemPtr++;	
//		if(Disk.ItemPtr > DisNum - 1) Disk.ItemPtr = 0;
//		Disk.ItemSNo--;	
	}
//	else
//	{
		if(Mode == 0)
		{	
			Disk.ItemANo++;
			if( Disk.ItemANo >= 90 ) Disk.ItemANo = 0;
				
			Temp = Para.RDisASwitch[89 - Disk.ItemANo];
			if(Temp == 0xFF )
			{
				Disk.ItemANo = 0;
				Temp = Para.RDisASwitch[89];
				if(Temp == 0xFF)
					Temp = 0x10;
			}
				
//			Disk.ItemANo++;
//			if( Disk.ItemANo >= 90 ) Disk.ItemANo = 0;
		}
		else
		{
			Disk.ItemMNo++;
			if( Disk.ItemMNo >= 90 ) Disk.ItemMNo = 0;
				
			Temp = Para.RDisMSwitch[89 - Disk.ItemMNo];
			if(Temp == 0xFF )
			{
				Disk.ItemMNo = 0;
				Temp = Para.RDisMSwitch[89];
				if(Temp == 0xFF)
					Temp = 0x10;
			}
//			Disk.ItemMNo++;
//			if( Disk.ItemMNo >= 90 ) Disk.ItemMNo = 0;
			
		}
		for(i=0;i<DisNum;i++)
		{
			if(DisTab[i].ComID4 == Temp)break;
		}
		if(i == DisNum)
			i = 0;
//		if((Temp >= 0xD0)&&(Temp <= 0xDF))
		if(((Temp >= 0xD0)&&(Temp <= 0xDF))||((Temp >= 0xE1)&&(Temp <= 0xE4)))						
		{	
			if(Temp == 0xDF)
//				Disk.ItemSNo =	Disk.DisHisMun*2;
				Disk.ItemSNo = Disk.DisHisMun*2-1;		
			else	
//				Disk.ItemSNo =	Disk.DisHisMun;
				Disk.ItemSNo =	Disk.DisHisMun-1;			
		}else		
			Disk.ItemSNo = DisTab[i].ComID2&0x3F;
	
		if(i == DisNum) i = 0;
		Disk.ItemPtr = i;	
//	}
		
}	

void GetPreCode( unsigned Mode )	
{
//	unsigned char i,y;
	unsigned char y;	
	unsigned short i;	
	unsigned char Temp,DisSNum;

//	unsigned char Buff[4];
	

//	Temp = (unsigned long)Para.RDisSwitch[2] * 65536 +(unsigned short)Para.RDisSwitch[1] * 256 + Para.RDisSwitch[0];	//显示开关
	Flag.Disk |= F_KeyInt;
	
	if(Disk.ItemSNo != 0)
	{
		if(Mode == 0)
		{	
			for(i=0;i<90;i++)
			{
				if( Disk.ItemANo == 0 ) 
				{	
					for(y=0;y<90;y++)
					{
						Temp = Para.RDisASwitch[89 - y];
	
						if(Temp == 0xFF )
							break;	
					}
					if(y==0) Disk.ItemANo = 0;
					else
					Disk.ItemANo = y-1;	
					
				}
//				else Disk.ItemANo--;
				
				Temp = Para.RDisASwitch[89 - Disk.ItemANo];
	
				if(Temp != 0xFF )
					break;
				
			}	
			if(i == 90) Temp =0x10;
			
		}
		else{
			
			for(i=0;i<90;i++)
			{
				if( Disk.ItemMNo == 0 ) 
				{	
					for(y=0;y<90;y++)
					{
						Temp = Para.RDisMSwitch[89 - y];
	
						if(Temp == 0xFF )
							break;	
					}
					if(y==0) Disk.ItemMNo = 0;
					else
					Disk.ItemMNo = y-1;	
				}//else Disk.ItemMNo--;
				
				Temp = Para.RDisMSwitch[89 - Disk.ItemMNo];
	
				if(Temp != 0xFF )
					break;
				
			}	
			if(i == 90) Temp =0x10;
			
		}			
			
		
		for(i=0;i<DisNum;i++)
		{
			if(DisTab[i].ComID4 == Temp)break;
		}
		if(i == DisNum) 
			i = 0;
//		if((Temp >= 0xD0)&&(Temp <= 0xDF))
		if(((Temp >= 0xD0)&&(Temp <= 0xDF))||((Temp >= 0xE1)&&(Temp <= 0xE4)))						
		{	
			if(Temp == 0xDF)
//				DisSNum = Disk.DisHisMun*2;
				DisSNum = Disk.DisHisMun*2-1;			
			else	
//				DisSNum = Disk.DisHisMun;
				DisSNum = Disk.DisHisMun-1;			
		}else			
			DisSNum = DisTab[i].ComID2&0x3F;
		if(i == DisNum)
			i = 0;
		
		if(Disk.ItemPtr == 0) Disk.ItemPtr = DisNum-1;
		else Disk.ItemPtr--;
		if(Disk.ItemPtr >= i)
//		if(Disk.ItemPtr > i)			
		{
//			Disk.ItemSNo--;
			return;	
		}
		
//		if(Disk.ItemPtr == 0) Disk.ItemPtr = DisNum-1;
//		else Disk.ItemPtr--;	
//		Disk.ItemSNo--;	
	}
//	else{
	
		
		if(Mode == 0)
		{	
			for(i=0;i<90;i++)
			{
				if( Disk.ItemANo == 0 ) 
				{	
					for(y=0;y<90;y++)
					{
						Temp = Para.RDisASwitch[89 - y];
	
						if(Temp == 0xFF )
							break;	
					}
					if(y==0) Disk.ItemANo = 0;
					else
					Disk.ItemANo = y-1;	
					
				}
				else Disk.ItemANo--;
				
				Temp = Para.RDisASwitch[89 - Disk.ItemANo];
	
				if(Temp != 0xFF )
					break;
				
			}	
			if(i == 90) Temp =0x10;
			
		}
		else{
			
			for(i=0;i<90;i++)
			{
				if( Disk.ItemMNo == 0 ) 
				{	
					for(y=0;y<90;y++)
					{
						Temp = Para.RDisMSwitch[89 - y];
	
						if(Temp == 0xFF )
							break;	
					}
					if(y==0) Disk.ItemMNo = 0;
					else
					Disk.ItemMNo = y-1;	
				}else Disk.ItemMNo--;
				
				Temp = Para.RDisMSwitch[89 - Disk.ItemMNo];
	
				if(Temp != 0xFF )
					break;
				
			}	
			if(i == 90) Temp =0x10;
			
		}			
			
		
		for(i=0;i<DisNum;i++)
		{
			if(DisTab[i].ComID4 == Temp)break;
		}
		if(i == DisNum) 
			i = 0;
//		if((Temp >= 0xD0)&&(Temp <= 0xDF))
		if(((Temp >= 0xD0)&&(Temp <= 0xDF))||((Temp >= 0xE1)&&(Temp <= 0xE4)))						
		{	
			if(Temp == 0xDF)
//				Disk.ItemSNo =	Disk.DisHisMun*2;
				Disk.ItemSNo =	Disk.DisHisMun*2-1;			
			else	
//				Disk.ItemSNo =	Disk.DisHisMun;
				Disk.ItemSNo =	Disk.DisHisMun-1;			
		}else			
			Disk.ItemSNo = DisTab[i].ComID2&0x3F;
		if(Disk.ItemSNo != 0)
			i = i + Disk.ItemSNo;
		if(i == DisNum)
			i = 0;
		Disk.ItemPtr = i;
//	}	
}	


void GetRotIterm(void)
{
//	unsigned short Temp;
	unsigned char Buff[4];
	
//	Temp=LcdRoll[SM.RollItemPt].RollItemAdd;//读出轮显项和轮显时间
//	E2P_RData(Buff,Temp,4);
//	Para.RDisSwitch[2]=Buff[0];
//	Para.RDisSwitch[1]=Buff[1];
//	Para.RDisSwitch[0]=Buff[2];
//	Para.RDspInv = 	Buff[3];
	
//	E2P_RData(&Para.RDspInv,LcdAutime,1);	
//	Disk.DisInv = Para.RDspInv;

	E2P_RData(Buff,LcdAutime,1);	
	Para.RDspInv=BCD_Byte(Buff[0]);
	if(Para.RDspInv == 0) Para.RDspInv = 6;
//	Disk.DisInv = Para.RDspInv;
	
	E2P_RData(Para.RDisASwitch +60,EDisplayA1,30);
	E2P_RData(Para.RDisASwitch +30,EDisplayA2,30);
	E2P_RData(Para.RDisASwitch ,EDisplayA3,30);
	E2P_RData(Para.RDisMSwitch +60,EDisplayM1,30);
	E2P_RData(Para.RDisMSwitch +30,EDisplayM2,30);
	E2P_RData(Para.RDisMSwitch ,EDisplayM3,30);
	
}
/*
void ShiftRight4Bit( unsigned char *Source )
{
	unsigned long Temp;
	
	Temp = BCD4_Long( Source )/10;	
	Long_BCD4( Source, Temp);	
}	
*/

//void KeyProce( void )
//{
//	unsigned char Buff[4];
//	unsigned char* Point;
//	//int i,Temp;
	
//	Point = Buff;
	
//	switch( SM.KbCount )
//	{
////		case P_KEYXF: 	GetNextCode( ); break;
////		case P_KEYSF: 	GetPreCode( ); break;
//		case P_KEYSF: 	GetNextCode( ); break;
//		case P_KEYXF: 	GetPreCode( ); break;
////		case P_PRGRM: if((Flag.Power & F_PwrUp) != 0)
////					  {
////						if( SM.PrgDly == 0 ) SM.PrgDly = Para.RPrgDLY;//SM.PrgDly = 10;
////						else SM.PrgDly = 0;
////						Flag.Disk |= F_KeyInt;
////						SM.KbCount = 0;
////						SM.BJGDly = BGDISDELAY;
////					  }	
//		default:return; 	
//	}
//	SM.KeyDly = KEYDISDELAY;
//	SM.KbCount = 0;
//	Disk.DisInv = KEYDISDELAY;	
//	Flag.Disk |= F_KeyInt;
//	SM.BJGDly = BGDISDELAY;
//}	










