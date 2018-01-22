/**********************************
	Baut rate Define (SMCLK=8M)
**********************************/	
/*
#define Baut_300L		0x2A	
#define Baut_300H		0x68
#define Baut_600L		0x15
#define Baut_600H		0x34
#define Baut_1200L	0x0B
#define Baut_1200H	0x1A
#define Baut_2400L	0x05
#define Baut_2400H	0x0D
#define Baut_9600L	0x41
#define Baut_9600H	0x03
#define Baut_19200L	0xA1
#define Baut_19200H	0x01
*/
#define CMonItems	164		//当前月电量、需量、需量时间、累计需量总项数		//V2.0

/**********************************
	Baut rate Define (SMCLK=4M)
**********************************/
/*
#if ( Threephase == YesCheck ) //三相	
*/
/*******SMCLK = 12MHz*******/
////#define Baut_300L	0x9D	
//#define Baut_300L	0xDD	
//#define Baut_300H	0xA3
////#define Baut_300M	0xFF
////#define Baut_300M	0x55
//#define Baut_300M	0x00
//
//#define Baut_600L	0xEA
//#define Baut_600H	0x51
////#define Baut_600M	0x55
//#define Baut_600M	0x00
//
//#define Baut_1200L	0xF2
//#define Baut_1200H	0x28
////#define Baut_1200M	0x0D
//#define Baut_1200M	0x00
//
//#define Baut_2400L	0x79
//#define Baut_2400H	0x14
////#define Baut_2400M	0xEF
//#define Baut_2400M	0x00
//
//#define Baut_4800L	0x3B
//#define Baut_4800H	0x0A
////#define Baut_4800M	0xEF
//#define Baut_4800M	0x00
//
//#define Baut_9600L	0x1C
//#define Baut_9600H	0x05
////#define Baut_9600M	0xFF
//#define Baut_9600M	0x00
//
//#define Baut_19200L	0x8E
//#define Baut_19200H	0x02
////#define Baut_19200M	0x55
//#define Baut_19200M	0x00
//
//#define Baut_38400L	0x47
//#define Baut_38400H	0x01
////#define Baut_19200M	0x55
//#define Baut_38400M	0x00

/***SMCLK = 4MHz***/
//#define Baut_300L	0x9D	
/*
#define Baut_300L	0x9f	
#define Baut_300H	0x36
//#define Baut_300M	0xFF
//#define Baut_300M	0x55
#define Baut_300M	0x00

#define Baut_600L	0x4E
#define Baut_600H	0x1B
//#define Baut_600M	0x55
#define Baut_600M	0x00

#define Baut_1200L	0xA6
#define Baut_1200H	0x0D
//#define Baut_1200M	0x0D
#define Baut_1200M	0x00

#define Baut_2400L	0xD3
#define Baut_2400H	0x06
//#define Baut_2400M	0xEF
#define Baut_2400M	0x00

#define Baut_4800L	0x69
#define Baut_4800H	0x03
//#define Baut_4800M	0xEF
#define Baut_4800M	0x00

#define Baut_9600L	0xB4
#define Baut_9600H	0x01
//#define Baut_9600M	0xFF
#define Baut_9600M	0x00

#define Baut_19200L	0xDA
#define Baut_19200H	0x00
//#define Baut_19200M	0x55
#define Baut_19200M	0x00

#define Baut_38400L	0x6D
#define Baut_38400H	0x00
//#define Baut_19200M	0x55
#define Baut_38400M	0x00
#endif
*/
/**********************************
	Baut rate Define (SMCLK=16.777216M)
**********************************/	
/*
#if ( SinglePhase == YesCheck )
#define Baut_300L	0x60	
#define Baut_300H	0xDA
#define Baut_300M	0x00

#define Baut_600L	0x30
#define Baut_600H	0x6D
#define Baut_600M	0x00

#define Baut_1200L	0x98
#define Baut_1200H	0x36
#define Baut_1200M	0x00

#define Baut_2400L	0x4C
#define Baut_2400H	0x1B
#define Baut_2400M	0x00

#define Baut_4800L	0xA6
#define Baut_4800H	0x0D
#define Baut_4800M	0x00

#define Baut_9600L	0xD3
#define Baut_9600H	0x06
#define Baut_9600M	0x00

#define Baut_19200L	0x69
#define Baut_19200H	0x03
#define Baut_19200M	0x00

#define Baut_38400L	0xB5
#define Baut_38400H	0x01
#define Baut_38400M	0x00
#endif
*/


#if ( Threephase == YesCheck ) //三相		
#define PhAFail_No		0	//A相断相
#define PhBFail_No		1	//B相断相
#define PhCFail_No		2	//C相断相
#define Cover_No		3	//开盖
#define TCover_No		4	//开端
//#define MeterReset_No		5	//电表上电
#define MagnetOn_No		5	//磁场
#define Rev_No		6	//反向
#else
#define PhAFail_No		0	//A相断相
#define PhBFail_No		1	//B相断相
#define PhCFail_No		2	//C相断相
#define Cover_No		3	//开盖
#define TCover_No		4	//开端
//#define MeterReset_No		5	//电表上电
#define MagnetOn_No		5	//磁场
#define Rev_No		6	//反向
#endif


#define RS_MaxSize  99		//等待接收的最大字节数
#define CPTInsItem 	28		//CDParaTab 中瞬时值项数 
#define MS600		39		//600MS
#define MS400		26		//400MS
#define TM485		6		//500MS

#define	SIOSYNC		0x09	//1001

#define	NAK		0x15
#define	ACK		0x06
#define	SOH		0x01
#define LF		0x0A
#define	CR		0x0D
#define STX		0x02
#define ETX		0x03
#define EOT		0x04
#define StartCode 	0x2F	//"/"
#define EndCode	0x21		//"!"
#define REQ		0x3F		//"?"
//READOUT 类型定义
#define Read9Mode	0x09
#define Read0Mode	0x00
#define ReadHistory	0x0A
#define ReadEvent	0x0B
#define ReadLoad		0x0C
///////////////////////////
//     ComBuf define     //
///////////////////////////
#define RS_HeadPtr   0
#define RS_AddrPtr   1
#define RS_Head0Ptr  7
#define RS_CtlPtr    8
#define RS_LenPtr    9

#define RS_Cmd			10
#define RS_CmdLPtr   10
#define RS_CmdHPtr   11
#define RS_DPtr      12

#define Rs_Head     	Comm.Buf[0]
#define Rs_Addr     	Comm.Buf[1]
#define Rs_Addr0    	Comm.Buf[1]
#define Rs_Addr1    	Comm.Buf[2]
#define Rs_Addr2    	Comm.Buf[3]
#define Rs_Addr3    	Comm.Buf[4]
#define Rs_Addr4    	Comm.Buf[5]
#define Rs_Addr5    	Comm.Buf[6]
#define Rs_Head0    	Comm.Buf[7]
#define Rs_Ctl      	Comm.Buf[8]
#define Rs_Len      	Comm.Buf[9]

#define Rs_IDL    	Comm.Buf[10]
#define Rs_IDH     	Comm.Buf[11]
#define Rs_Data    	Comm.Buf[12]

#define Rs_CRC      	Comm.Buf[RS_Cmd+Rs_Len]
#define Rs_End      	Comm.Buf[RS_Cmd+Rs_Len+1]

// ComInfo define
#define EN_WR		0xC000
#define EN_W		0x8000
#define EN_R		0x4000

#define RS_REG		0x3800
#define REG_RAM		0*0x0800
#define REG_IFlash 	1*0x0800
#define REG_Eeprom	2*0x0800
#define REG_DFlash	3*0x0800
#define REG_CMD 	4*0x0800

#define RS_LEN		0x00FF

#define CALIBCOUNT	60
#define CALIBCOUNT1	61

#define BGDISDELAY 	30
#define KEYDISDELAY 20
#define TESTDISCNT	7//9//7//9//8

#define BATONDLY	30

//efine RS_CMD			0x0700

#define CMD_CLK1				0x0000
#define CMD_CLK2  			0x0001

#define CMD_LP_ReadRec   	0x0010
#define CMD_LP_Channel   	0x0011
#define CMD_LP_RegCode   	0x0012
#define CMD_LP_TimeInv   	0x0013
#define CMD_LP_MaxRecNum  	0x0014
#define CMD_LP_ReadPtr   	0x0015
#define CMD_LP_RecNum   	0x0016
#define CMD_LP_CRecTime   	0x0017

#define CMD_EL_ReadRec   	0x0020
#define CMD_EL_ReadData   	0x0021
#define CMD_EL_EvenCode   	0x0022
#define CMD_EL_MaxRecNum  	0x0023
#define CMD_EL_ReadPtr   	0x0024
#define CMD_EL_RecNum   	0x0025

/////////////////////////
// Control byte define //
/////////////////////////
#define RS_CTL_Read     0x01
#define RS_CTL_ReadCont 0x02
#define RS_CTL_ReRead   0x03
#define RS_CTL_Write    0x04
#define RS_CTL_AdjTime  0x08
#define RS_CTL_WrMetID  0x0A
#define RS_CTL_ChgBaut  0x0C
#define RS_CTL_ChgPswd  0x0F
#define RS_CTL_RstMD    0x10

#define RS_State_IVData	0x01		//非法数据
#define RS_State_IVID	0x02		//数据标识错
#define RS_State_PswE	0x04		//密码错 or 操作非法 

#define Current		0	//当前项				//V3.0
#define Next		-1	//下一项				//V3.0


#define 	USART_BPS_300 		 0x00,	//波特率
#define 	USART_BPS_600 		 0x20,
#define 	USART_BPS_1200 	 0x40,
#define 	USART_BPS_2400 		 0x60,
#define 	USART_BPS_4800 		 0x80,
#define 	USART_BPS_7200 		 0xa0,
#define 	USART_BPS_9600 		 0xc0,	
#define 	USART_BPS_19200 	 0xe0	

//extern void fnUSART_IRCom_Init(unsigned char Cfg);
//extern void fnUSART_RS485_Init(unsigned char Cfg);
//extern void fnUSART_ZBCOM_Init(unsigned char Cfg);


 void fnUSART_IRCom_Init(unsigned char Cfg);
 void fnUSART_RS485_Init(unsigned char Cfg);
 void fnUSART_ZBCOM_Init(unsigned char Cfg);


short Proc_Comm(unsigned char COM_No);
void CommInit(unsigned char COM_No);
void CommRest(unsigned char COM_No);
short GetXorCheck( unsigned char* XorCheck, short* CheckAds,unsigned char *ComBuf);
void CommMode(unsigned char COM_No);
short CommModeRec(unsigned char COM_No);
short Proc_Read(unsigned char COM_No);	
short Proc_Write(unsigned char COM_No);	
//int Read_ATTValue( unsigned char Cmd, unsigned char* Data );
short Read_ATTValue( unsigned char Cmd, unsigned char* Data ,unsigned char phase );
void DayInc( unsigned char* Data );
void DayDec( unsigned char* Data );
unsigned short SumLoadAds(unsigned char* Dest );
void LoadBCD_ASC( unsigned char* Dest, unsigned char* Src, unsigned char* Ptr, short Length);
short LoadTimeChk(void);
short GetRecordAds( unsigned char* Dest, unsigned short PtrAds );
short JustDay( unsigned char* Dest, short i, short PtrAds );
//int GetRecordData( unsigned char* Point,int Type);							//V3.0
short GetRecordData( unsigned char* Point );							//V3.0
short GetLoadData(unsigned char* Point, short Type);
//int GetLoadPWData( unsigned char* Point,int Type);
//int LoadPWJustDay( unsigned char* Dest, long RdItemAds, long PtrAds );
//long GetLoadPWAds( unsigned char* Dest, unsigned long PtrAds );

//int LoadPWJustDay( unsigned char* Dest, long RdItemAds, LOADPARA* LoadPara );
//long GetLoadPWAds( unsigned char* Dest, LOADPARA* LoadPara );
short GetLoadPWData( unsigned char* Point,short Type, short ChannalNo );
void ManualMDRest( void );

void Clr_E2PData( short Addr, short DataLenth, short Cylcle );
void Clr_E2PECData( short Addr, short DataLenth, short Cylcle );
unsigned short PtAddrChk( unsigned short RecNo, short Type );						//V3.0
short BroadC_Time( unsigned char* Source );
void Clr_EC( void );

void SendNextBlock(unsigned char COM_No);
void SendErrorCode(unsigned char COM_No);
void SendCusNum(unsigned char COM_No);
void SendSerNum(unsigned char COM_No);
void CalcuBCC(unsigned char *Point,unsigned char Len,unsigned char COM_No);
void SendBCC(unsigned char COM_No) ;
void SendRtcDate(unsigned char COM_No);
void SendRtcTime(unsigned char COM_No);
void SendZEC(unsigned char COM_No);
void SendZ4QEC(unsigned char COM_No);
void SendZAbsEC(unsigned char COM_No);
void SendZ3PEC(unsigned char COM_No);

void SendT1EC(void);
void SendT2EC(void);
void SendT3EC(void);
void SendT4EC(void);
void SendECComm(unsigned char *Point,unsigned char Numb, unsigned char COM_Mode, unsigned char COM_No);
void SendConstantS0(unsigned char COM_No);
void SendConstant(unsigned char COM_No);
void SendVersion(unsigned char COM_No);
void SendTariName(unsigned char COM_No);

void SendEventPSet(unsigned char COM_No);	
void SendCEventCnt(unsigned char COM_No);
void SendVEventCnt(unsigned char COM_No);

void SendSyLSBillingTimeDate(unsigned char COM_No);
void SendLsBillingTimeDate(unsigned char COM_No);
void SendLsBillingTimeDateRO(unsigned char COM_No);

void SendLsEC(unsigned char COM_No);
void SendLsDemandData(unsigned char COM_No);
void SendLsTP101_10(unsigned char COM_No);
//void SendLsTP10_2(void);
//void SendLsTP10_3(void);
//void SendLsTP10_4(void);
//void SendLsTP10_5(void);
//void SendLsTP10_6(void);
//void SendLsTP10_7(void);
//void SendLsTP10_8(void);
//void SendLsTP10_9(void);
//void SendLsTP10_10(void);
void SendTop10Comm(unsigned char *Point ,unsigned char COM_No);
void SendMaxDemand(unsigned char COM_No);
void SendSumOvLim(void);
//void SendSyBillingTimeDate(void);
//void SendLsECComm(unsigned char *Point);
//void SendSyZEC(void);
//void SendSyT1EC(void);
//void SendSyT2EC(void);
//void SendSyT3EC(void);
//void SendSyT4EC(void);
void SendSyZEC(unsigned char COM_No);
void SendLsZEC(unsigned char COM_No);
void SendLsT1EC(void);
void SendLsT2EC(void);
void SendLsT3EC(void); 
void SendLsT4EC(void);
void SendLsECComm(unsigned char *Ptr,unsigned char COM_No);
void SendHisPointer(unsigned char COM_No);

void SendSyMaxDemand(unsigned char COM_No);
void SendSySumOvLim(void);
void SendEvent(unsigned char COM_No);
void SendEventData(unsigned char *Point,unsigned char COM_No);
short Proc_Execute(unsigned char COM_No);
void SendProfile(unsigned char COM_No);
void SendAllNO(unsigned char COM_No);
//void SendCRLFBCC(unsigned char *Point,unsigned char Len);
void SendCRLFBCC(unsigned char Len,unsigned char COM_No);
void SendLable1(unsigned char COM_No);
void SendLable2(unsigned char COM_No);
void SendSdNumber(unsigned char COM_No);
void SendKGDMAGComm(unsigned char COM_No);
void SendDqKGcs(unsigned char COM_No);
void SendDqMagcs(unsigned char COM_No);
void SendLsKGDMAGComm(unsigned char *Ptr,unsigned char COM_No);
void SendLsMagcs(void);
void SendLsKDcs(unsigned char COM_No);
void SendLsKGcs(unsigned char COM_No);
void SendDqKDcs(void);
//void SendVoltage(void);
//void SendCurrent(void);
void SendPower(unsigned char COM_No);
void SendPowerLn(unsigned char COM_No);
void SendAngleA(unsigned char COM_No);

void SendLsCurrentA(unsigned char COM_No);
void SendLsVoltageA(unsigned char COM_No);

void SendCurrentA(unsigned char COM_No);
void SendCurrentB(unsigned char COM_No);
void SendCurrentC(unsigned char COM_No);
void SendCurComm(unsigned char *Ptr,unsigned char COM_No);
void SendVoltageA(unsigned char COM_No);
void SendVoltageB(unsigned char COM_No);
void SendVoltageC(unsigned char COM_No);
void SendVolComm(unsigned char *Ptr,unsigned char COM_No);
void SendCheatEvent(unsigned char COM_No);
void SendBatWorkTM(unsigned char COM_No);
void SendBatVoltage(unsigned char COM_No);

void SendMDDate(unsigned char COM_No);
void SendLsMDDate(unsigned char COM_No);

unsigned short DoCrc16(unsigned short RegInit, unsigned char *message, unsigned short len);
void Read_CPU_CRC( unsigned char* Dest );	//2012.9.26

void MoveKWToRAM(unsigned char* Dest,unsigned char mun);
void MoveKvarToRAM(unsigned char* Dest,unsigned char mun);

void SendPowerLast(unsigned char COM_No);
void SendPower4Q(unsigned char COM_No);
void SendPowerABS(unsigned char COM_No);
void SendBillingCounter(unsigned char COM_No);

void SendOTime(unsigned char COM_No);
void SendFailCnt(unsigned char COM_No);
void SendLsFailCnt(unsigned char COM_No);

void SendLastTimeDay(unsigned char COM_No);
void SendMagneticCnt(unsigned char COM_No);

void RelayDrive( unsigned char ChannelNo,unsigned char DriveType ); //13.1.13 wwl


