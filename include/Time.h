
void ClkAdjFact(void);
void Temperature(void);
//void Clock(void);
//void ClkChk(void);
//void SetClkBak( void );
//unsigned int GetBillMon( char* Addr );
//unsigned int GetGmDay( char* Addr );
//unsigned long GetGmSec( char* Addr );
unsigned long GetGmMin( char* Addr );
//char GetWeek( void );
void Min_Date( char* Sec, unsigned long Min );
//char GetFeeNo( void );
unsigned long GetSec( unsigned char* Addr );
//int TimeValueCheck( unsigned char* Source );
short TimeValueCheck( unsigned char* Source );
short DateValueCheck( unsigned char* Source );
void GetTime( void );
void SetClkBak( void );
void SetClk( void );
unsigned char WeekDay20( unsigned char* Addr );		//V40
unsigned char SummerORwinter(void);
void ProcRTCSumWin(void);
void ProShiftFlag(void);
void RtcSub1Hour(unsigned char *Phour);
void RtcAdd1Hour(unsigned char *Phour);
void RtcAdd15Min(unsigned char *Min);
void TimeDataTurn(unsigned char* Data);
void OpenLM75(void);
void CloseLM75(void);


