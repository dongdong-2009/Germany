#define	TM_20ms		4+1
#define	TM_500ms	100+1
#define	TM_1000ms	200+1
#define TM_120s		8//24//8

__interrupt void Int_RTC(void);
__interrupt void Int_LCD_C(void);
__interrupt void Int_Timer3A1(void);
__interrupt void Int_Timer3A0(void);
__interrupt void Int_Port2(void);
__interrupt void Int_Timer2A1(void);
__interrupt void Int_Timer2A0(void);
__interrupt void Int_Port1(void);
__interrupt void Int_Timer1A1(void);
__interrupt void Int_Timer1A0(void);
__interrupt void Int_DMA(void);
__interrupt void Int_AUX(void);
__interrupt void Int_UartA2(void);
__interrupt void Int_UartA1(void);
__interrupt void Int_Timer0A1(void);
__interrupt void Int_Timer0A0(void);
__interrupt void Int_SD24B(void); 
__interrupt void Int_ADC(void);
__interrupt void Int_USCIB0(void);
__interrupt void Int_UartA0(void);
__interrupt void Int_WDT(void);
__interrupt void Int_UNMI(void);
__interrupt void Int_SYSNMI(void);
__interrupt void Int_RESET(void);

extern void _WKUP(void);

void HwTxInitial(void);
void HwRxInitial(void);
void CreatPulse( void );
void CountPulseA( void );
void CountPulseB( void );
void CountPulseC( void );
void IT_P1YJB( void );
void HWint(void);

