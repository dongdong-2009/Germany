#define YesCheck	0x00
#define NoCheck		0x01

#define PWUPTIME	50	//上电检测延时
/*
#define Cover_No		4	//开盖
#define TCover_No		5	//开端
#define PhAFail_No		0	//A相断相
#define PhBFail_No		1	//B相断相
#define PhCFail_No		2	//C相断相
//#define MeterReset_No		5	//电表上电
#define MagnetOn_No		3	//磁场
*/


//#define RELAY_OFF 	0x01	//继电器拉合闸
//#define RELAY_ON 	0x00
#define RELAY_OFF 	0x00	//继电器拉合闸
#define RELAY_ON 	0x01

#define MONMDLENGTH	36//55
#define LOADLENGTH	23//8//40
#define MAXPTR		24000//39000//15000//798	FLASH前200页


#define TAMPERLENGTH	15//12//40
//#define MAX_TAMPER_PTR		100//15//22//evn
#define MAX_TAMPER_PTR		15//15//22//evn

//#define ProfEAds    0xA2	//负荷曲线 + 事件记录 EEPROM 24C512 
#define ProfEAds    0xA8	//负荷曲线 + 事件记录 EEPROM 24C512 
#define ECDataEAds    0xA2	//#define DataEAds    0xA4	//数据 EEPROM 24C512 电量数据


#define RTCAds		0x64	//RTC8025时钟芯片地址
#define TCN75Ads	0x9E	//温度传感器地址
#define DS3231Ads	0xD0	//时钟芯片DS3231地址
#define S35390AAds	0x60	//时钟芯片S35390A地址

#define ADE7758		0x00	
#define ATT7022		0x01
#define ATT7053		0x02
#define ADE7755		0x03
#define RN8207		0x04
//#define MEASCHIP	ADE7758	//选择计量芯片类型	
//#define MEASCHIP	ATT7022	//选择计量芯片类型	
//#define MEASCHIP	ATT7053	//选择计量芯片类型	
//#define MEASCHIP	ADE7755	//选择计量芯片类型	
#define MEASCHIP	RN8207	//选择计量芯片类型	

#define UCLOCKBATL	0x20
#define UCLOCKBATH	0x03	//时钟电池阀值3.2V

#define RX8025		0x00	//
#define DS3231		0x01	//
#define RX8025T		0x02	//
#define S35390A		0x03	//S35390A
#define RN8213Z		0x04	//RN8213Z
#define RTCCHIP		RN8213Z	// 选择时钟芯片类型
//#define RTCCHIP		S35390A	// 选择时钟芯片类型
//#define RTCCHIP		DS3231	// 选择时钟芯片类型

#define Phase3Wire4	0x0			//三相四线
#define Phase3Wire3	0x1			//三相三线

#define LinkMode 	Phase3Wire4		////三相四线
//#define LinkMode 	Phase3Wire3		////三相三线

#define  Threephase 	YesCheck	//三相
//#define  Threephase 	NoCheck		//三相

//#define  SinglePhase	YesCheck	//单相
#define  SinglePhase	NoCheck		//单相

#define  Lcd8com 	YesCheck	//三相
//#define  Lcd8com 	NoCheck		//三相

//#define  Lcd4com 	YesCheck	//三相
#define  Lcd4com 	NoCheck		//三相

//#define	SecurityCheck	YesCheck 	//有安全认证
#define	SecurityCheck	NoCheck 	//无安全认证

#define TariffSwitch	 YesCheck	//外部费率切换T2
//#define TariffSwitch	 NoCheck	//外部费率切换T1


#if ( Threephase == YesCheck ) //三相			
#define DataEAds    0xA0	//#define DataEAds    0xA4	//数据 EEPROM 24C64
#define AdjEAds     0xAE	//#define AdjEAds     0xA0	//校表参数 EEPROM 24C04
#define	FMAds		0xA6	//当前电量和需量缓存 FM24C16	
#endif

#if ( SinglePhase == YesCheck )
#define DataEAds    0xA0	//#define DataEAds    0xA4	//数据 EEPROM 24C64
#define AdjEAds     0xA6	//#define AdjEAds     0xA0	//校表参数 EEPROM 24C02
#define	FMAds		0xAE	//当前电量和需量缓存 FM24C16	
#endif

#if ( Threephase == YesCheck ) //三相	
#define MONLENGTH	100//146
#else
#define MONLENGTH	100//92//146
#endif


//DS3231
#define RS1			0x0008
#define RS2			0x0010
#define EN32kHz		0x0800
#define INTCN		0x0004

//S35390A
#define TimeAddr		0x04	//C2C1C0: 010x
#define State0Addr		0x00	//C2C1C0: 000x
#define State1Addr		0x02	//C2C1C0: 001x
#define INT1Addr		0x08	//C2C1C0: 100x
#define INT2Addr		0x0A	//C2C1C0: 101x	
#define JZAddr			0x0C	//C2C1C0: 110x	

//8025
#define	Hour24		0x0020
#define CLEN1		0x0800
#define CLEN2		0x0010
#define CT0			0x0001
#define CT1			0x0002
#define CT2			0x0003
#define	XST			0x2000

#if ( RTCCHIP == RX8025 )
#define EN32K1Hz	XST+Hour24+CT0+CT1		//0x2023	32kHz+秒脉冲输出
#define EN32K		XST+Hour24				//0x2020	32kHz+无脉冲输出
#define DisEn32K1Hz	XST+Hour24+CLEN1+CLEN2	//0x2830	无输出

#elif ( RTCCHIP == RX8025T )				//V1000	
#define EN32K1Hz	CSEL0+UIE				//0x6000	32kHz+秒脉冲输出 2秒刷新温度系数
#define EN32K		CSEL0					//0x4000	32kHz+无脉冲输出

#elif (RTCCHIP == DS3231)
#define EN32K1Hz	EN32kHz				//0x0800		32kHz+秒脉冲输出
#define EN32K		EN32kHz+INTCN		//0x0804		32kHz+无脉冲输出
#define DisEn32K1Hz	INTCN				//0x0004		无输出

#elif (RTCCHIP == S35390A)
#define EN32K1Hz	EN32kHz				//0x0800		32kHz+秒脉冲输出
#define EN32K		EN32kHz+INTCN		//0x0804		32kHz+无脉冲输出
#define DisEn32K1Hz	INTCN				//0x0004		无输出
#endif

#define RecordSAds	0xC000	//24C512中
#define RecordEAds	0xD5E0	//24C512中
#define LoadBLen	26		//2+2+2+2+2+2+2+4+4+3=25 +1(校验) = 26
#define RecordBLen	28		//6+1(校验)+1+1+2+2+2+2+2+2+2+4+1(校验) = 28	

//#define FlashChip		NoCheck		//FLASH芯片
////#define FlashChip		YesCheck
//
//#define FlashAT45DB		NoCheck		//ATMEL的AT25DF041A系列芯片 AT26DF081、AT26DF161
//#define FlashAT161Series	YesCheck	//ATMEL的AT45161芯片 容量2M字节
//
//#define CommType_JHw	YesCheck		//近红外
//
//#define	Gliwice		00
//#define	Krakov		01
//#define	Gdansk		02
//#define	Warsaw		03
//
//#define FWCity		Warsaw
//
//#if ( Threephase == YesCheck )
//#define	CRCH		0x3F
//#define	CRCL		0x97
//#define	CRCRead1		'3'
//#define	CRCRead2		'F'
//#define	CRCRead3		'9'
//#define	CRCRead4		'7'
//#else
//#define	CRCH		0x92
//#define	CRCL		0xE7
//#define	CRCRead1		'9'
//#define	CRCRead2		'2'
//#define	CRCRead3		'E'
//#define	CRCRead4		'7'
//#endif
//
