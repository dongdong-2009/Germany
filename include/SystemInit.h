#ifndef  _SystemInit_H
#define  _SystemInit_H

//#define	NEW_201265
#define	PLL_Clock

typedef enum
{
	GPIO_MODE_OUT	= 0,
	GPIO_MODE_IN	= 1
} eGPIOMode_TypeDef;



#define	fnDelay_1us()			{__NOP();__NOP();__NOP();__NOP();}
// ��������
#define PinRead_KeyPrg(x)		((GPIO->PB&0x00008000) ? (0x01) : (0x00))		// p5.7
#define PinRead_KeyTurn(x)		((GPIO->PA&0x00000100) ? (0x01) : (0x00))		// p1.0
#define PinRead_KeyShell(x)		((GPIO->PA&0x00000200) ? (0x01) : (0x00))		// p1.1

//����ָʾ��
#define PinWrite_AlarmLed(x)       ( (x) ? (GPIO->PB |= 0x00000020 , GPIO->PMB &= 0xffffffdf) : (GPIO->PB &= 0xffffffdf , GPIO->PMB &= 0xffffffdf) )	// p4.5
//�̵���ָʾ��
#define PinWrite_RelayLed(x)       ( (x) ? (GPIO->PB |= 0x00000800 , GPIO->PMB &= 0xfffff7ff) : (GPIO->PB &= 0xfffff7ff , GPIO->PMA &= 0xfffff7ff) )	// p5.3    ��բָʾ��
//#define	PinWrite_LCDLight(x)	   ( (x) ? (GPIO->PB |= 0x00004000 , GPIO->PMB &= 0xffffbfff) : (GPIO->PB &= 0xffffbfff , GPIO->PMB &= 0xffffbfff) ) 	// p5.6   ����
#define	PinWrite_LCDLight(x)	   ( (x) ? (GPIO->PB |= 0x00000008 , GPIO->PMB &= 0xfffffff7) : (GPIO->PB &= 0xfffffff7 , GPIO->PMB &= 0xfffffff7) ) 	// p5.6   ����
// UART

#define PinMode_RS485RX(x) 		( (x == GPIO_MODE_OUT) ? (GPIO->PMA &= 0xfffeffff) : (GPIO->PMA |= 0x00010000) )	// P2.0
#define PinMode_RS485TX(x) 		( (x == GPIO_MODE_OUT) ? (GPIO->PMA &= 0xfffdffff) : (GPIO->PMA |= 0x00020000) )	// P2.1

#define PinMode_IRRX(x) 		( (x == GPIO_MODE_OUT) ? (GPIO->PMA &= 0xfffbffff) : (GPIO->PMA |= 0x00040000) )	// P2.2
#define PinMode_IRTX(x) 		( (x == GPIO_MODE_OUT) ? (GPIO->PMA &= 0xfff7ffff) : (GPIO->PMA |= 0x00080000) )	// P2.3

#define PinMode_ZBRX(x) 		( (x == GPIO_MODE_OUT) ? (GPIO->PMA &= 0xffbfffff) : (GPIO->PMA |= 0x00400000) )	// P2.6
#define PinMode_ZBTX(x) 		( (x == GPIO_MODE_OUT) ? (GPIO->PMA &= 0xff7fffff) : (GPIO->PMA |= 0x00800000) )	// P2.7


extern void fnINTRTC_Init1S( void );

extern	void fnTarget_Init(void);
//extern	u16 fnStamp_Through(u16 Ago);
//extern	void fnUsart_Init(u8 ComPort , u8 Cfg);
extern	void SystemInit(void);
extern	void fnINTTC0_Init( void );
extern	void fnINTTC1_Star( void );
extern	void fnINTTC1_Stop( void );
extern	void fnINTTC2_Star( void );
extern	void fnINTTC2_Stop( void );
extern	void fnRTCDrive_Delay(void);
extern	void fnWDT_Restart( void );
extern  void fnINTTC0_RCInit( void );
//extern	void SystemDelay(u16 t);
extern  void SystemDelay(unsigned short t);
#endif
