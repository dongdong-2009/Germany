#define YesCheck	0x00
#define NoCheck		0x01

#define PWUPTIME	50	//�ϵ�����ʱ
/*
#define Cover_No		4	//����
#define TCover_No		5	//����
#define PhAFail_No		0	//A�����
#define PhBFail_No		1	//B�����
#define PhCFail_No		2	//C�����
//#define MeterReset_No		5	//����ϵ�
#define MagnetOn_No		3	//�ų�
*/


//#define RELAY_OFF 	0x01	//�̵�������բ
//#define RELAY_ON 	0x00
#define RELAY_OFF 	0x00	//�̵�������բ
#define RELAY_ON 	0x01

#define MONMDLENGTH	36//55
#define LOADLENGTH	23//8//40
#define MAXPTR		24000//39000//15000//798	FLASHǰ200ҳ


#define TAMPERLENGTH	15//12//40
//#define MAX_TAMPER_PTR		100//15//22//evn
#define MAX_TAMPER_PTR		15//15//22//evn

//#define ProfEAds    0xA2	//�������� + �¼���¼ EEPROM 24C512 
#define ProfEAds    0xA8	//�������� + �¼���¼ EEPROM 24C512 
#define ECDataEAds    0xA2	//#define DataEAds    0xA4	//���� EEPROM 24C512 ��������


#define RTCAds		0x64	//RTC8025ʱ��оƬ��ַ
#define TCN75Ads	0x9E	//�¶ȴ�������ַ
#define DS3231Ads	0xD0	//ʱ��оƬDS3231��ַ
#define S35390AAds	0x60	//ʱ��оƬS35390A��ַ

#define ADE7758		0x00	
#define ATT7022		0x01
#define ATT7053		0x02
#define ADE7755		0x03
#define RN8207		0x04
//#define MEASCHIP	ADE7758	//ѡ�����оƬ����	
//#define MEASCHIP	ATT7022	//ѡ�����оƬ����	
//#define MEASCHIP	ATT7053	//ѡ�����оƬ����	
//#define MEASCHIP	ADE7755	//ѡ�����оƬ����	
#define MEASCHIP	RN8207	//ѡ�����оƬ����	

#define UCLOCKBATL	0x20
#define UCLOCKBATH	0x03	//ʱ�ӵ�ط�ֵ3.2V

#define RX8025		0x00	//
#define DS3231		0x01	//
#define RX8025T		0x02	//
#define S35390A		0x03	//S35390A
#define RN8213Z		0x04	//RN8213Z
#define RTCCHIP		RN8213Z	// ѡ��ʱ��оƬ����
//#define RTCCHIP		S35390A	// ѡ��ʱ��оƬ����
//#define RTCCHIP		DS3231	// ѡ��ʱ��оƬ����

#define Phase3Wire4	0x0			//��������
#define Phase3Wire3	0x1			//��������

#define LinkMode 	Phase3Wire4		////��������
//#define LinkMode 	Phase3Wire3		////��������

#define  Threephase 	YesCheck	//����
//#define  Threephase 	NoCheck		//����

//#define  SinglePhase	YesCheck	//����
#define  SinglePhase	NoCheck		//����

#define  Lcd8com 	YesCheck	//����
//#define  Lcd8com 	NoCheck		//����

//#define  Lcd4com 	YesCheck	//����
#define  Lcd4com 	NoCheck		//����

//#define	SecurityCheck	YesCheck 	//�а�ȫ��֤
#define	SecurityCheck	NoCheck 	//�ް�ȫ��֤

#define TariffSwitch	 YesCheck	//�ⲿ�����л�T2
//#define TariffSwitch	 NoCheck	//�ⲿ�����л�T1


#if ( Threephase == YesCheck ) //����			
#define DataEAds    0xA0	//#define DataEAds    0xA4	//���� EEPROM 24C64
#define AdjEAds     0xAE	//#define AdjEAds     0xA0	//У����� EEPROM 24C04
#define	FMAds		0xA6	//��ǰ�������������� FM24C16	
#endif

#if ( SinglePhase == YesCheck )
#define DataEAds    0xA0	//#define DataEAds    0xA4	//���� EEPROM 24C64
#define AdjEAds     0xA6	//#define AdjEAds     0xA0	//У����� EEPROM 24C02
#define	FMAds		0xAE	//��ǰ�������������� FM24C16	
#endif

#if ( Threephase == YesCheck ) //����	
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
#define EN32K1Hz	XST+Hour24+CT0+CT1		//0x2023	32kHz+���������
#define EN32K		XST+Hour24				//0x2020	32kHz+���������
#define DisEn32K1Hz	XST+Hour24+CLEN1+CLEN2	//0x2830	�����

#elif ( RTCCHIP == RX8025T )				//V1000	
#define EN32K1Hz	CSEL0+UIE				//0x6000	32kHz+��������� 2��ˢ���¶�ϵ��
#define EN32K		CSEL0					//0x4000	32kHz+���������

#elif (RTCCHIP == DS3231)
#define EN32K1Hz	EN32kHz				//0x0800		32kHz+���������
#define EN32K		EN32kHz+INTCN		//0x0804		32kHz+���������
#define DisEn32K1Hz	INTCN				//0x0004		�����

#elif (RTCCHIP == S35390A)
#define EN32K1Hz	EN32kHz				//0x0800		32kHz+���������
#define EN32K		EN32kHz+INTCN		//0x0804		32kHz+���������
#define DisEn32K1Hz	INTCN				//0x0004		�����
#endif

#define RecordSAds	0xC000	//24C512��
#define RecordEAds	0xD5E0	//24C512��
#define LoadBLen	26		//2+2+2+2+2+2+2+4+4+3=25 +1(У��) = 26
#define RecordBLen	28		//6+1(У��)+1+1+2+2+2+2+2+2+2+4+1(У��) = 28	

//#define FlashChip		NoCheck		//FLASHоƬ
////#define FlashChip		YesCheck
//
//#define FlashAT45DB		NoCheck		//ATMEL��AT25DF041Aϵ��оƬ AT26DF081��AT26DF161
//#define FlashAT161Series	YesCheck	//ATMEL��AT45161оƬ ����2M�ֽ�
//
//#define CommType_JHw	YesCheck		//������
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
