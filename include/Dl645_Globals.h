

#ifndef  _DL645_GLOBALS_H
#define  _DL645_GLOBALS_H

#ifdef   _DL645_GLOBALS
	#define  DL645_EXT
#else
	#define  DL645_EXT  extern 
#endif
/*
//--------------------------------------------
DL645_EXT 	u16		SysStamp;	 //系统主节拍.1ms
DL645_EXT	sDF01	SysClock;
DL645_EXT 	u16		SysStamp500;
DL645_EXT 	u16		GataSysStamp;	
//--------------------------------------------
//DL645_EXT 	u8 			LCDDMABuf[250] __attribute__(( at(0x10000100) ));
DL645_EXT	sDl645FrontTmp_TypeDef	Dl645FrontTmp;
DL645_EXT	sDl645Front_TypeDef		Dl645Front;
DL645_EXT 	sDl645Bkgrd_TypeDef 	Dl645Bkgrd;
DL645_EXT 	sComPack_TypeDef 		ComPack[SCOM_PORT_MAX];
DL645_EXT	sDl645B_Session_TYPE 	Dl645Session;
DL645_EXT	sDl645FirmParaFile_TypeDef	Dl645FirmPara;
DL645_EXT	sD645Inactive_TypeDef	Dl645Inactive;
DL645_EXT	u8	BufTemp[270];
DL645_EXT	u8	DispBuf[240];
DL645_EXT	u32	CMPFlag; 
DL645_EXT	u32	FlashAdMax;

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

//--------------------------------------------

#endif	//_DL645_GLOBALS_H

















