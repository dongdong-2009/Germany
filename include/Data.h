//#if ( ZjProtocol == YesCheck)
//#define ZjComNum	64
//#else
//#endif
#ifndef __DATA_H__
#define __DATA_H__
#include "type.h"
#if ( Threephase == YesCheck ) //三相		
#define CPTSumItem  9//126//132//128//150//146		//CDParaTab 中总项数
#elif ( SinglePhase == YesCheck ) //单相
//#define CPTSumItem  143		//CDParaTab 中总项数
#define CPTSumItem  139//127//133//152		//CDParaTab 中总项数
#endif

#if ( Threephase == YesCheck ) //三相		
#define ECUnitNum	6//12//51//8		//电量计量项数
#define MDUnitNum	5//5//14		//需量计量项数			//反向需量不计
//#define DisNum		297//117		//DisTab中总项数
#elif ( SinglePhase == YesCheck ) //单相
#define ECUnitNum	6//5//8		//电量计量项数
#define MDUnitNum	5//5//		//需量计量项数			//反向需量不计
//#define DisNum		141//117		//DisTab中总项数
#endif

#if ( TariffSwitch == YesCheck )	 
#define DisNum		12// 3//117		//DisTab中总项数
#else   
#define DisNum		12//117		//DisTab中总项数	
#endif	

#if ( Threephase == YesCheck )	 
#define TamperNum	7		//TamperTab 中总项数
#else   
#define TamperNum	7		//TamperTab 中总项数
#endif	

#define ComNum		209		//通讯条数
//#define DisNum		297//117		//DisTab中总项数


//#ifndef  _DL645_GLOBALS_H
//#define  _DL645_GLOBALS_H

//#ifdef   _DL645_GLOBALS
//	#define  DL645_EXT
//#else
//	#define  DL645_EXT  extern 
//#endif
//#define	FLSBLK	0x1200
//#define	FLSBAK	0x3000	//
//
//#define	INFOBLK	0x1000
//#define	INFOBAK	0x0080	//



extern  PARA	Para;				// 电表参数
extern  COMM	Comm;
extern  COMM8207	Comm8207;

extern 	CLK		Clk;
extern 	ADJ		Adj;
extern 	DISKEY		Disk;
extern 	FLAG			Flag;
extern 	SRAM SM;
extern 	MEASURE7053	Measure7053;
extern 	MEASURE8207	Measure8207;
//extern  COMM8213		Comm8213;

//extern 	STDATETIME *PSTDATETIME;
//extern 	STDATETIME;

//extern		int32_t __initial_sp;
//#endif	//_DL645_GLOBALS_H

/*
DL645_EXT  PARA	Para;				// 电表参数
DL645_EXT  COMM	Comm;
DL645_EXT  COMM8207	Comm8207;

DL645_EXT 	CLK		Clk;
DL645_EXT 	ADJ		Adj;
DL645_EXT 	DISKEY		Disk;
DL645_EXT 	FLAG			Flag;
DL645_EXT 	SRAM SM;
DL645_EXT 	MEASURE7053	Measure7053;
DL645_EXT 	MEASURE8207	Measure8207;
//DL645_EXT		int32_t __initial_sp;
*/

//----- 

#define clrbit0 0xfe
#define	clrbit1 0xfd
#define	clrbit2 0xfb
#define	clrbit3 0xf7
#define	clrbit4 0xef
#define	clrbit5 0xdf
#define	clrbit6 0xbf
#define	clrbit7 0x7f

#define bitsetkey  (Flag.Key &0x1)
#define Set_bitsetkey {Flag.Key |=0x1;}
#define Clr_bitsetkey {Flag.Key &=clrbit0;}

#define bitlgset (Flag.Key &0x2)
#define Set_bitlgset {Flag.Key |=0x2;}
#define Clr_bitlgset {Flag.Key &=clrbit1;}

#define bitscroll (Flag.Key &0x4)
#define Set_bitscroll {Flag.Key |=0x4;}
#define Clr_bitscroll {Flag.Key &=clrbit2;}

#define bitUpRollKey (Flag.Key &0x8)
#define Set_bitUpRollKey {Flag.Key |=0x8;}
#define Clr_bitUpRollKey {Flag.Key &=clrbit3;}

#define bitDownRollKey (Flag.Key &0x10)
#define Set_bitDownRollKey {Flag.Key |=0x10;}
#define Clr_bitDownRollKey {Flag.Key &=clrbit4;}

#define bitstset (Flag.Key &0x20)
#define Set_bitstset {Flag.Key |=0x20;}
#define Clr_bitstset {Flag.Key &=clrbit5;}

#define bitsfsttolg (Flag.Key &0x40)
#define Set_bitsfsttolg {Flag.Key |=0x40;}
#define Clr_bitsfsttolg {Flag.Key &=clrbit6;}

#define bitxfsttolg (Flag.Key &0x80)
#define Set_bitxfsttolg {Flag.Key |=0x80;}
#define Clr_bitxfsttolg {Flag.Key &=clrbit7;}
//--------------------
#define bitlgsfkey  (Flag.Key1 &0x1)
#define Set_bitlgsfkey {Flag.Key1 |=0x1;}
#define Clr_bitlgsfkey {Flag.Key1 &=clrbit0;}

#define bitlgxfkey  (Flag.Key1 &0x2)
#define Set_bitlgxfkey {Flag.Key1 |=0x2;}
#define Clr_bitlgxfkey {Flag.Key1 &=clrbit1;}

#define bitwinter	(Flag.Key1 &0x4)
#define Set_bitwinter	{Flag.Key1 |=0x4;}
#define Clr_bitwinter	{Flag.Key1 &=~0x4;}

//---------------------
#define bitsetsdb (Flag.Event &0x01)
#define Set_bitsetsdb {Flag.Event |=0x01;}
#define Clr_bitsetsdb {Flag.Event &=clrbit0;}

#define bitsetsdbSW (Flag.Event &0x04)
#define Set_bitsetsdbSW {Flag.Event |=0x04;}
#define Clr_bitsetsdbSW {Flag.Event &=clrbit2;}

#define bitSetJsr (Flag.Event &0x02)
#define Set_bitSetJsr {Flag.Event |=0x02;}
#define Clr_bitSetJsr {Flag.Event &=clrbit1;}

#define bitSetJsrSW (Flag.Event &0x08)
#define Set_bitSetJsrSW {Flag.Event |=0x08;}
#define Clr_bitSetJsrSW {Flag.Event &=clrbit3;}

//extern 	#define bitsetkey  (Flag.Key &0x1)
//extern 	#define Set_bitsetkey {Flag.Key |=0x1;}
//extern 	#define Clr_bitsetkey {Flag.Key &=clrbit0;}
//
//extern 	#define bitlgset (Flag.Key &0x2)
//extern 	#define Set_bitlgset {Flag.Key |=0x2;}
//extern 	#define Clr_bitlgset {Flag.Key &=clrbit1;}
//
//extern 	#define bitscroll (Flag.Key &0x4)
//extern 	#define Set_bitscroll {Flag.Key |=0x4;}
//extern 	#define Clr_bitscroll {Flag.Key &=clrbit2;}
//
//extern 	#define bitUpRollKey (Flag.Key &0x8)
//extern 	#define Set_bitUpRollKey {Flag.Key |=0x8;}
//extern 	#define Clr_bitUpRollKey {Flag.Key &=clrbit3;}
//
//extern 	#define bitDownRollKey (Flag.Key &0x10)
//extern 	#define Set_bitDownRollKey {Flag.Key |=0x10;}
//extern 	#define Clr_bitDownRollKey {Flag.Key &=clrbit4;}
//
//extern 	#define bitstset (Flag.Key &0x20)
//extern 	#define Set_bitstset {Flag.Key |=0x20;}
//extern 	#define Clr_bitstset {Flag.Key &=clrbit5;}
//
//extern 	#define bitsfsttolg (Flag.Key &0x40)
//extern 	#define Set_bitsfsttolg {Flag.Key |=0x40;}
//extern 	#define Clr_bitsfsttolg {Flag.Key &=clrbit6;}
//
//extern 	#define bitxfsttolg (Flag.Key &0x80)
//extern 	#define Set_bitxfsttolg {Flag.Key |=0x80;}
//extern 	#define Clr_bitxfsttolg {Flag.Key &=clrbit7;}
//
//
//extern 	#define bitsetsdb (Flag.Event |=0x01)
//extern 	#define Set_bitsetsdb {Flag.Event |=0x01;}
//extern 	#define Clr_bitsetsdb {Flag.Event &=clrbit0;}
//
//extern 	#define bitSetJsr (Flag.Event |=0x02)
//extern 	#define Set_bitSetJsr {Flag.Event |=0x02;}
//extern 	#define Clr_bitSetJsr {Flag.Event &=clrbit1;}

extern 	const unsigned char TimeMaxTab[3];
extern 	const unsigned char DateMaxTab[4];

extern 	const char 			MonTab[13];
extern 	const unsigned char BCDMonTab[13];
extern 	const unsigned char WeekTab[12];
extern  const E2Para E2PTab[4]; 

extern  const ECRg 			ECRgTab[ECUnitNum];
//extern  const unsigned char BautTab[21];
extern 	const unsigned char NumSeg[16];
extern  const TAMPER TamperTab[TamperNum];
//extern  const PTPARA PointTab[7];
//extern  const unsigned char ItemLenTab[32];
extern 	const unsigned short	ByteBit[16];
extern 	const unsigned char 	CByteBit[8];

extern 	const DISTAB 	DisTab[DisNum];
//extern	const DISMENUTAB KeyMenuTab[16];
//extern	const unsigned short TariffTab[9];
extern	const COMPLEXSD Complexsd[3];
extern	const SIMPLESD Simplesd[6];

//extern 	const COMTAB 	ComTab[ComNum];
//#if ( CPUCHIP == MSPF449 )
//extern  const COMMPARA CommPara[3];
//#else
//extern  const COMMPARA CommPara[2];
//#endif
extern  const MDPARA MDPara[MDUnitNum];

extern  const COMMPARA CommPara[2];
extern  const BLOCKCOMMPARA BlockCommPara[2];

extern	const MEASREG MeasReg[5];

//extern  const unsigned char LCDHWBrowseTab[26];
//extern  const unsigned char LCDM2BrowseTab[7];
//extern  const unsigned char LCDM4BrowseTab[7];
//extern  const unsigned long LCDSWTab[21];
extern  const unsigned long YMPTab[6];

extern 	const COMDISTAB 	ComDisTab[3];			//V2.0
extern 	const CDPARATAB 	CDParaTab[CPTSumItem];//CDParaTab[98];
//extern  const LCDROLL		 LcdRoll[9];
extern	const LASTSUNDAY LastSunTab[36];
//#if ( ZjProtocol == YesCheck)
//extern const ZJCOMTAB ZjComTab[ZjComNum];
//#if ( CPUCHIP == MSPF449 )
//extern  const ZJCOMMPARA ZjCommPara[3];
//#else
//extern  const ZJCOMMPARA ZjCommPara[2];
//#endif
//#else
//#endif

//extern  const unsigned char LCDRollOrderTab[21];
//extern  const short DayTab[13];
extern  const EXECUTETAB ExecuteTab[1];
extern  const unsigned short Crc16tab[256];
extern const uint8_t Manufacture[4];
extern uint8_t Z1_M[16];
#endif
