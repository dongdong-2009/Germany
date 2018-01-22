/*****************************************************************
	RAM.c
*****************************************************************/
void RAM_DataFill( unsigned char* Dest, short Len,unsigned char Data);

void RAM_Write( unsigned char *Dest, unsigned char *Src, short Len );
void RAM_Write_Dev( unsigned  char *Dest, unsigned char *Src, short Len );
void RAM_WriteInter( unsigned char *Dest, unsigned char *Src, short Len );
//void RAM_Fill( char* Dest, int Len, char Data);
void RAM_Fill( unsigned char* Dest, short Len);
short Data_Comp( unsigned char *Data1, unsigned char *Data2, short Len);

/*****************************************************************
	Flash_CPU.c
*****************************************************************/
/*
void Fls_SegClr( char *Dest );
void Fls_wb( char *Dest, char Data );
void Fls_Write( char *Dest, char *Src, int Len );

void FlsInfo_Write( char *Dest, char *Src, int Len );
void Fls2_Write( char *Dest, char *Src, int Len );
void Flash_Write( char *Dest, char *Src, int Len );
void Flash_Fill( char *Dest, int Lenth, char Data );
*/
/*****************************************************************
	Flash_Data.c
*****************************************************************/
#if ( FlashAT45DB == YesCheck )
short DataFlash_Read( unsigned char *RAM_Dest, unsigned long Fls_Src, short Lenth);
short DataFlash_Write( unsigned long Fls_Dest, unsigned char *RAM_Src, short Lenth );
short Read_FlashD(unsigned char *RAM_Dest, unsigned short Page_Addr, unsigned short Buf_Addr, short Lenth);
#else
short DataFlash_Read( unsigned char *RAM_Dest, unsigned long Fls_Src, unsigned long Fls_Sta, unsigned long Fls_End, unsigned short Lenth );
short DataFlash_Write( unsigned long Fls_Dest, unsigned char *RAM_Src, unsigned long Fls_Sta, unsigned long Fls_End, unsigned short Lenth );
short Read_FlashD( unsigned char *RAM_Dest, unsigned long Fls_Src, unsigned short Lenth);
#endif

short Flash_On( void );
short BlockErase(unsigned long Fls_Src);

void Flash_Reset(void);
char Read_Status(void);
short Read_Buffer1( char* RAM_Dest,  unsigned short Buf_Src, short Lenth);

short Write_Buffer1( unsigned short Buf_Dest, char* RAM_Src, short Lenth);
short Fls_Buf1( unsigned short Page_Add );
short Buf1_Fls( unsigned short Page_Add );
unsigned short Read_BufPg( void );
short Write_BufPg( unsigned short Page_Addr);

short DFlash_Read( char *RAM_Dest, unsigned long Fls_Src, short Lenth);
short DFlash_Write( unsigned long Fls_Dest, char *RAM_Src, short Lenth);
void DFlash_Fill( unsigned long Dest, short Lenth, char Data );

/*****************************************************************
	E2PROM.c
*****************************************************************/
extern short E2PRead( unsigned char* RAM_Addr, unsigned short E2P_Addr, unsigned short Lenth, unsigned short Devads);
extern short E2Pwrite( unsigned short E2P_Addr, unsigned char* RAM_Addr, unsigned short Lenth,unsigned short Devads );

extern short E2P_Write( unsigned short E2P_Dest, unsigned char* RAM_Src, short Lenth, short Dev_Ads );
extern short E2P_Read( unsigned char* RAM_Dest, unsigned short E2P_Src, short Lenth, short Dev_Ads );
void E2P_E2P( unsigned short Dest, unsigned short Src, short Len, short Dev_Ads );
void E2P_Fill( unsigned short Dest, short Len, unsigned char Data, short Dev_Ads );
//extern int E2P_RData( unsigned char* RAM_Dest,unsigned int E2P_Src, int Lenth );
//extern u32  E2P_RData( unsigned char* RAM_Dest,unsigned int E2P_Src, int Lenth );
//extern int E2P_WData( unsigned int E2P_Dest, unsigned char* RAM_Src, int Lenth );

extern short E2P_RData( unsigned char* RAM_Dest,unsigned short E2P_Src,  short Lenth );
extern short E2P_WData( unsigned short E2P_Dest, unsigned char* RAM_Src,  short Lenth );

extern short E2P_RECData( unsigned char* RAM_Dest,unsigned short E2P_Src,  short Lenth );
extern short E2P_WECData( unsigned short E2P_Dest, unsigned char* RAM_Src,  short Lenth );

//extern u32 E2P_WData( unsigned int E2P_Dest, unsigned char* RAM_Src, int Lenth );
short E2P_RMDBuf( unsigned char* RAM_Dest, unsigned short E2P_Src, short Lenth );
short E2P_WMDBuf( unsigned short E2P_Dest, unsigned char* RAM_Src, short Lenth );
extern short E2P_RAdj( unsigned char* RAM_Dest,unsigned short E2P_Src, short Lenth );
extern short E2P_WAdj( unsigned short E2P_Src, unsigned char* RAM_Dest, short Lenth );
short E2P_RFM( unsigned char* RAM_Dest,unsigned short E2P_Src, short Lenth );
short E2P_WFM( unsigned short E2P_Dest, unsigned char* RAM_Src, short Lenth );
short E2P_PRData( unsigned char* RAM_Dest,unsigned short E2P_Src, short Lenth );
short E2P_PWData( unsigned short E2P_Dest, unsigned char* RAM_Src,short Lenth );

void WorkRelay(unsigned char relayNo,unsigned char Mode);

void T0_INT(void);
unsigned char TX_FRAME(unsigned char Num);
unsigned char RX_FRAME(unsigned char Addr,unsigned char Num);
void WAIT25(void);
void TX_ONEBYTE(unsigned char TxData);
unsigned char RX_ONEBYTE(void);
void StandBy(void);
void TX_SYNC(void);
void TXZERO_MAN(void);
void TXONE_MAN(void);
unsigned char RX_MAN(void);
void TX8BITDATA(unsigned char TxData);
unsigned char Get_TxData_P(unsigned char TxData);
void TX_P(unsigned char TxData);
void TURNROUND1(void);
void RX_SR(void);
unsigned char RX8BITDATA(void);
void RX_P(unsigned char RxData);
void TX_MR(void);
void RX_P2(unsigned char RxData_P);
void TX_P2(unsigned char TxData_P);
void Read_8203(void);


