/*****************************************************************
	Asm.s43 (ASM)
*****************************************************************/

// BCD Calculation Subroutine
extern void _BCD1INC(unsigned char *Dest);
extern void _BCD2INC(unsigned char *Dest);
extern void _BCD3INC(unsigned char *Dest);
extern void _BCD4INC(unsigned char *Dest);
extern void _BCD1DEC(unsigned char *Dest);

extern void _BCD1ADD(unsigned char *Dest, unsigned char *Src);
extern void _BCD2ADD(unsigned char *Dest, unsigned char *Src);
extern void _BCD3ADD(unsigned char *Dest, unsigned char *Src);
extern void _BCD4ADD(unsigned char *Dest, unsigned char *Src);

extern void _BCD2SUB(unsigned char *Dest, unsigned char *Src);
extern void _BCD4SUB(unsigned char *Dest, unsigned char *Src);

extern void _BCD12_ASC3132(unsigned char *Dest, unsigned char *Src, unsigned char Lenth);
extern void _BCD_ASC(unsigned char *Dest, unsigned char *Src, unsigned char Lenth);
extern void _ASC_BCD(unsigned char *Dest, unsigned char *Src, unsigned char Lenth);

extern void _BTOWADD(unsigned char *Dest, unsigned char *Src);
extern void _BCD2TO4ADD(unsigned char *Dest, unsigned char *Src);
extern void _BCD2TO5ADD(unsigned char *Dest, unsigned char *Src);
void _BCD6INC(unsigned char *dest);

extern void _SUB4(short Dest, short *Src);
extern void _ADD4(short Dest, short *Src);
extern void _ADD2(short *Dest, unsigned char *Src);
extern short _E2Pwrite( unsigned short E2P_Addr, unsigned char* RAM_Addr, short Lenth,short Devads );
extern short _E2PRead( unsigned char* RAM_Addr, unsigned short E2P_Addr, short Lenth, short Devads);
//*****************************************************************
// General.c
//*****************************************************************
unsigned char Byte_BCD( unsigned char Data );
void Word_BCD( unsigned char *Ptr, unsigned short Data );
void Long_BCD3( unsigned char *Ptr, unsigned long Data );
void Long_BCD4( unsigned char *Ptr, unsigned long Data );

short IsBCD(unsigned char Data);
unsigned char BCD_Byte( unsigned char Data );
unsigned short BCD2_Word( unsigned char *Ptr );
//unsigned long BCD3_Long( unsigned char *Ptr );
unsigned long BCD4_Long( unsigned char *Ptr );

unsigned char ChkNum( unsigned char *Ptr, short Len );
unsigned char ChkNumAdd( unsigned char *Ptr, short Len );
unsigned short ChkNumShort( unsigned short *Ptr, short Len );

void Reset(void);
void WDTReset(void);

void Delay(unsigned short i);
//void OpenADC12(void);
void CloseADC12(void);
void GetBatVolt( void );


unsigned char GetNo(unsigned char* Point,unsigned char* Source,short ItemNums);
short GetDaySeg(void);
void ClrMDBuf(void);
void GetFeeNo(void);
void RpaInit(void);
short Mon_Save(void);
void MonData_Save(unsigned char* Date);
void GetATAngle( unsigned char Addr, unsigned char* Data );
void GetVoltAmper( void );
void ADCStart(  short Mode  );
void OpenADC12(  short Mode  );
//void IAdjust(unsigned char* source);
//void IOSAdjust(unsigned char* Source );
//void SeasonFreeze( int Number );
//void FreezeEC( unsigned int Dest, int Cycle );
void FreezeEC(void);
void ChangeSeason(void);
void MD_Rest( void );
void Recd_ADD1( unsigned short CtAds, unsigned short DataLenth);
void E2P_DataMove( unsigned short Dest, unsigned short Source,short DataLenth, short Cycle );
void Recd_Ct_Tm( unsigned short CtAds, short Time);
void ADCEnd( void );
short SeasonJust( short StartTime, short EndTime, short Type );
void SeasonFreeze( short Season, short Type );
void Get24HourEC( void );
#if( LinkMode == Phase3Wire4 )	
void StartNCheck( void );
void EndNCheck( void );
#else
#endif
void E2P_MoveTwoCycle( unsigned short Source,short DataLenth );		//用于最近三次记录
//void GetPrgRecd(unsigned int Com_ID);
void Recd_MDPrg( unsigned short Addr );
void GetSeg( unsigned char Num );
void E2P_E2PMoveTwoCycle( unsigned short Dest, unsigned short Source,short DataLenth );
void E2P_RAMMoveTwoCycle( unsigned short Dest, unsigned char* Source,short DataLenth );		//用于最近三次记录
short GetLcdState(void);
void SumPower( void );
void RunOutCheck(void);
void CheckLabState( void );
void OpenLabState( void );
void CloseLabState( void );
void SwapChar( unsigned char* Source, short Cycle );
void SwapWord( unsigned char* Source, short Cycle );

void ParameterBCC(void);

void InitPara(void);			//V2

unsigned char CmpSdSolution(unsigned char*Cmp1,unsigned char*Cmp2);
//unsigned char CmpSeason(unsigned char *Ptr);
unsigned char GetSeasonNo(unsigned char*Point);
//unsigned char GetSeasonNo(void);
unsigned char GetComplexDaySdb(unsigned char ComplexSoluN0);
//unsigned char GetComplexDaySdb(void);
short Mon_Read(unsigned char* Ram_Addr,unsigned char Mon,unsigned char length,unsigned char stata);
void TariffDataRomove(void);
void IncBatteryWorkTime( void );
void InitMeasPara(void);	//2012.12.31
void OperationalTimeInc(void);

//unsigned long	SubDateTime_Second(STDATETIME *pstLDateTime,STDATETIME	*pstRDateTime);
	

