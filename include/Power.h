

//====================================================
short PowerCheck(void);
void EventCntADD(unsigned short Add);
void EventCnt4ADD(unsigned short Add);
void TamperCheck( void );
short PhaseRev( void );
//int CBypasChk( void );
//int NeutralChk( void );
//int MissCurrent( void );
unsigned char MissPotent(void);
//int CurrentRev( void );
void GetCurrent( short* Ia,short* Ib, short* Ic);
//void GetVA( unsigned char*Dest );
//void TampRecord( int Temp,unsigned char Bytebit );
void TampRecord( short i, unsigned char Temp,short End );
//void TampRecord( int Tamp_No, unsigned char Temp,unsigned char End );
//void LoadRecord( void );
unsigned char ECRev( void );
void Data_Save( short Source, short DataLength, short CycleCnt );
unsigned char PhFail(void);
unsigned char CUFail(void);
unsigned char AmperOver(void);
unsigned char Rev( void );
unsigned char APhBk(void);
unsigned char BPhBk(void);
unsigned char CPhBk(void);
unsigned char PhBreak( short PhaseNo );
void TamperSumTime( void );
short VACompare( unsigned char* Source, unsigned char* Dest );
/*#if( AllFailChk == YesCheck )		
void AllFailRec( void );
#else
#endif
*/
void SumAmpHour( void );
void SumPhFailEC( void );
void GetMaxCurrent( void );
short LoadRecord( void );//void LoadRecord( void );
short LoadPtrChk( long Type );//int LoadPtrChk( unsigned char* LoadPara, int Type );
short ReadLoadRecord( unsigned char* Dest ,long Ptr);
void SetLoadPara( void );//void SetLoadPara( unsigned char* Source );
void GetMeterState(void);
unsigned char PhFailState( short PhaseNo );
unsigned char CuFailState( short PhaseNo );
unsigned char PhAFail(void);
unsigned char PhBFail(void);
unsigned char PhCFail(void);
unsigned char CuAFail(void);
unsigned char CuBFail(void);
unsigned char CuCFail(void);

unsigned char CoverOpen(void);
unsigned char TCoverOpen(void);
unsigned char MeterResetOpen(void);
unsigned char MagnetOnOpen(void);

//short ReadTamperRecord( unsigned char* Dest ,short Ptr, unsigned char Tamper_no);
short ReadTamperRecord( unsigned char* Dest ,short Ptr);
short ReadLoadRecordByDate( unsigned char* Dest ,unsigned char* StartDate ,unsigned char* CloseDate );

void GetRunOverState(void);
//short TamperPtrChk( short Type , unsigned char Tamper_no);
short TamperPtrChk( short Type );

//short TamperRecord( unsigned char Tamper_no ,unsigned char End);
short TamperRecord( unsigned char Tamper_no );

void SetTamperPara( void );
void GetGLoadCurAdr( unsigned long* LoadCurAdr ,unsigned char Type );






