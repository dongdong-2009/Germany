#ifndef __TYPE_H__
#define __TYPE_H__
#include <stdint.h>
#include	"TypeE2p.h"
//#include	"TypeDFls.h"
#include "RsComm.h"

#define BCD_INTER_TYPE 0x50
#define RAM_INTER_TYPE 0x60
#define RAM_TYPE 0x70
#define E2P_TYPE 0x80
#define FUN_TYPE 0x90

#define MAX_MENU_PTR  3
//*******************************************************************
// Data type define
//*******************************************************************
typedef unsigned char BCD1[1];
typedef unsigned char BCD2[2];
typedef unsigned char BCD3[3];
typedef unsigned char BCD4[4];
typedef unsigned char BCD5[5];
typedef unsigned char BCD6[6];
typedef unsigned char BCD7[7];
typedef unsigned char BCD8[8];
//*******************************************************************
// Data type define
//*******************************************************************
typedef unsigned short  	u16;
typedef signed short  		s16;

/* Adjust Data of Energy & Time */

typedef struct
{
	short	Crys_Offs;
} ADJ;

/* Time Stamp */
typedef struct
{
   BCD1 	Sec;
   BCD1 	Min;
   BCD1 	Hour;
   BCD1 	Day;
   BCD1 	Mon;
   BCD1 	Year;
} YMDhms;


typedef struct
{
	
#if 1	
	BCD2	RAlarm_Control;	//����������(2)	
	
	BCD6  Pp0;
	BCD6  Pp1;
	BCD6  Pp2;
	BCD6  Pp3;
	BCD6  Pp4;
	BCD6  Pptmp;
	BCD6  Pn0;
	BCD6  Pntmp;
	uint8_t p_flag;
//	uint64_t Pp0;
//	uint64_t Pn0;
  uint32_t meter_sts;
#if 0	
	BCD2	RVolt_Valve;		//���ࣨʧѹ����ѹ��ֵ(2)
	BCD2	RAmper_Valve;		//���ࣨʧѹ��������ֵ(2)
	BCD2	Ue;				//��ѹ��ֵ(2)
	unsigned char Tu;		//����״̬�ȶ�ʱ��(1)
	unsigned char TuMagnet ;		//����״̬�ȶ�ʱ��(1)
	
//	BCD2	I0;				//������ڴ˵���Ϊ�޸��أ����ж���(2)�����������ż�ֵ
	BCD4	PtABC;				//������   0000.0000kw
	BCD4	PnABC;				//������	0000.0000kw
	BCD4	PtABS;				//�����й�����(3)����ֵ����	0000.0000kw
#endif	

	BCD4	Pa;				//A���й�����(3)
	BCD4	Pb;				//B���й�����(3)
	BCD4	Pc;				//C���й�����(3)
	
	BCD4 	Pt;				//�����й�����(3)�����͹��� 0000.0000kw

	BCD4	Ua;				//A���ѹ(2) ����000000.00V ����00000.000V 
	BCD4	Ub;				//B���ѹ(2)
	BCD4	Uc;				//C���ѹ(2)	
	
	BCD4	Ia;				//A�����(2)  ����00000.000A ����0000.0000A
	BCD4	Ib;				//B�����(2)
	BCD4	Ic;				//C�����(2)

	BCD2	Pfa;			//A�๦������(2) ��λС�� Pfa[1] = 09 Pfa[0] = 99  ��ʾ��������Ϊ0.999
	BCD2	Pfb;			//B�๦������(2)
	BCD2	Pfc;			//C�๦������(2)
	
	BCD2	Freq;
	//uint64_t Freq;			//Ƶ��(2)
	uint64_t servrid;
	uint64_t P0_day;
	uint64_t P0_week;
	uint64_t P0_month;
	uint64_t P0_year;
	uint64_t P0_last;
	
	BCD2 	Pangleba;
	BCD2  Pangleca;
	BCD2	Panglea;			//A��Ƕ�(2) һλС�� Panglea[1] = 15 Panglea[0] = 12 ��ʾ��������Ϊ151.2��
	BCD2	Pangleb;			//B��Ƕ�(2)
	BCD2	Panglec;			//C��Ƕ�(2)
	unsigned char 	RDspInv;		// ѭ��ʱ��(1)

	unsigned short	RTCDota0;		// RTCУ���Ĵ���(2)
#if 0
	unsigned short 	ESavetime;	// �ֶ�����ʱ������(2) ��	

  unsigned char 	RMaxT;			// �����������(1)
	unsigned char 	RMaxDT;			// ��������(1)
	
	unsigned char 	RPrgDLY;		// ��̿�����ʱ(1)
	unsigned char 	RPrgPurview; 	// ���Ȩ��(1)
#endif	
#if( SecurityCheck == YesCheck )		
	unsigned char 	RECClrMode; 	// ��������ģʽ(1)	
#endif	
//	unsigned char 	RPJLmode;		// ���ܼ���ģʽ(1)	
#if 0
	unsigned char 	RAutoDisMode;	// ��ʾģʽ(1) 
	unsigned char 	RDisDigitNum;	// ����С��λ��(1) 
	unsigned char 	RPRGRMByte;	//��̰���(1)
#endif	
	unsigned char 	TestModeCnt;	// ����ģʽʱ��(1)
#if 0	
	unsigned char 	Beginspeed;	// RS485��ʼ������(1) ��	
#endif	
#if 0
	
	BCD2	LCDOffSTime;	//Һ���ر���ʾ��ʼʱ��(2) 
	BCD2	LCDOffETime;	//Һ���ر���ʾ����ʱ��(2) 
	


	BCD2	Panglea;			//A��Ƕ�(2) һλС�� Panglea[1] = 15 Panglea[0] = 12 ��ʾ��������Ϊ151.2��
	BCD2	Pangleb;			//B��Ƕ�(2)
	BCD2	Panglec;			//C��Ƕ�(2)
	
	unsigned char SFlag;	//����״̬,bit3=1,������(1) 
							//BIT0 = 1  A�๦�ʴ���1%Ib 
							//BIT1 = 1  B�๦�ʴ���1%Ib 
							//BIT2 = 1  C�๦�ʴ���1%Ib 
	unsigned char PWFlag;	//�й����޹����ʷ���(1) 
	unsigned char IabcFlag;	//���������־(1)	
	BCD3 PWFlagbuff;	//�й����޹����ʷ���(1) 
	
	BCD3 	Seg[10];		// ʱ�α�
	BCD3 	RelaySeg[10];		// �̵���	
#endif	
	uint32_t StatusWord;
	unsigned int pval;
	unsigned int p_plus;
	unsigned int p_count;
#else
	uint64_t Pp0;
	uint64_t Pn0;
  uint64_t meter_sts;
	
	uint64_t 	Pt;				//�����й�����(3)�����͹��� 0000.0000kw

	uint64_t	Ua;				//A���ѹ(2) ����000000.00V ����00000.000V 
	uint64_t	Ub;				//B���ѹ(2)
	uint64_t	Uc;				//C���ѹ(2)	
	
	uint64_t	Ia;				//A�����(2)  ����00000.000A ����0000.0000A
	uint64_t	Ib;				//B�����(2)
	uint64_t	Ic;				//C�����(2)
	
	uint64_t Freq;			//Ƶ��(2)
	uint64_t servrid;
	uint64_t P0_day;
	uint64_t P0_week;
	uint64_t P0_month;
	uint64_t P0_year;
	uint64_t P0_last;
#endif

} PARA;

/*******************************************************************
	Global data in RAM that not cleared when Reset
*******************************************************************/

typedef struct
{
	char		Sec_64;
   	BCD1 		Sec;
   	BCD1 		Min;
   	BCD1 		Hour;
   	BCD1 		Day;
   	BCD1 		Mon;
   	BCD1 		Year;
   	BCD1		Week;
} CLK;
	
// Display  & Key registers
typedef struct
{
//	int ManuCode;				//���ұ���
//	BCD2 UserCode;				//�û�����	
	unsigned char Mode;					// ģʽ��
//	unsigned char KeyTmr;				// ����ɨ�趨ʱ
//	unsigned char KeyLPCT;				// ��������ʱ������
    unsigned char FlsCT;				// ��˸������
    unsigned char DisInv;				// ���Լ��������
 //   unsigned char ItemPtr;				// ���Ա�ָ��
     unsigned short ItemPtr;				// ���Ա�ָ��   
//    unsigned char ItemSum;			// ��ʾ������
    unsigned char ItemNo;				// ��ʾ�����
    unsigned char ItemANo;				// �Զ���ʾ�����
    unsigned char ItemMNo;				// ������ʾ�����
    unsigned char ItemSNo;				// С����ʾ�����
    unsigned char HisMon;				// ��ʾ�ڼ��µ���ʷ����
    unsigned char RotPhase;				//L1,L2,L3������˸
    unsigned char DisHisMun;				// ��ʾ��ʷ��������
		unsigned char info;
		unsigned char ec_ptr;
    
    unsigned char PoweoffNo;				// ͣ�����Ҫ��ʾ��������
    unsigned char PoweoffPtr;				// ͣ�����ʾ����Ŀָ��   
		unsigned char power_ptr;
		unsigned char power_no;
		unsigned int  volt_code;
//    unsigned char LXItemSum;			// ����������

//    unsigned char LXTab[20];			// LCD��λ����
	uint16_t DisECModeCnt;			//��ʾ����ģʽ��ʱ
	uint16_t DisECT1ModeCnt;			//��ʾ����ģʽ��ʱ
	unsigned char vol_cnt;
	  unsigned char com_No;
	uint16_t DoEDL40Cnt;
	uint16_t DisFeeCnt;
	uint16_t Dis022Cnt;
	uint16_t DisMUC_CCnt;
	uint8_t TextDisTmr;			// text��ʾ��ʱ
	
} DISKEY;

/*******************************************************************
	Even Log Profile Information Structure Define
*******************************************************************/
/*
// Bit Flag
	// Power flags define
#define  F_PwrUp     	0x02
#define  F_IrmsCheck	0x01		//0:�������1������У׼
#define  F_AllFail		0x04		//0:��ȫʧѹ;1:ȫʧѹ
#define  F_ErrMeas		0x08		//����оƬ����
#define  F_FailIrmsMeas	0x10		//У�����һ�ε������ 0���Ѽ�����1��δ���
#define	 F_NCheckLoss	0x20		//���߼�⡣0��������1��������
*/

#define  F_Relay1     		0x01
#define  F_Relay2     		0x02

#define  F_PwrUp     	0x02
//#define  F_IrmsCheck	0x01		//0:�������1������У׼
#define  F_BatteryPwrUp	0x01		//9V��ѹ��0:�ޣ�1����
#define  F_EDMeasure		0x04		//0:�µ粻����;1:�µ����
//#define  F_AllFail		0x04		//0:��ȫʧѹ;1:ȫʧѹ
#define  F_Loadrecord		0x08		//�µ縺�����߼�¼
#define  F_ByPass 		0x40		//������·���� 
//#define  F_ErrMeas		0x08		//����оƬ����
//#define  F_FailIrmsMeas	0x10		//У�����һ�ε������ 0���Ѽ�����1��δ���
#define  F_DoLoadrecord	0x10		//�µ緢�������ɼ�¼
//#define	 F_DoEDMeasure	0x20		//���߼�⡣0��������1��������
#define	 F_DoTariffDataRomove	0x20		//��������ȷ��
#define	 F_DoParaDataRomove	0x40		//��������ȷ��
//#define	 F_NCheckLoss	0x20		//���߼�⡣0��������1��������
#define  F_DoCalU			0x80		//У��ѹ����
	// Run flags define
#define  F_ComOK    0x01
#define	 F_THW		0x02	//�����485����
//#define  F_ComOK3   0x02
//#define  F_Batt     0x04
#define  F_MonSave     0x04
#define	 F_T485		0x08	//�����485����
#define	 F_AdsOk	0x10
#define	 F_MimaOk0	0x20
#define	 F_MimaOk1	0x40		
#define  F_ComRest   	0x80//#define  F_Parity   	0x80

	// Clk flags define
#define  F_Sec       0x01
#define  F_Min       0x02
#define  F_Hour      0x04
#define  F_Day       0x08

#define  F_DisSec       0x10
#define  F_LoadRecord   0x20	//���ɼ�¼
#define  F_HalfSec      0x40
#define  F_641Sec       0x80	
	// DisK Flag Bit
#define  F_KeyInt    	0x80
#define  F_DspALT		0x40
#define  F_KeyStart    	0x20
#define  F_OpButtonEDL40    	0x10	//EDL40��ʾ

#define  F_Flash		0x08
//#define  F_KeyS	    	0x04

#define  F_Key       	0x04
#define  F_Key1      	0x01
#define  F_Key2      	0x02

	// E.C. Direction
//#define  F_Ph     0x70
//#define  F_PhA    0x10
//#define  F_PhB    0x20
//#define  F_PhC    0x40

#define  F_Ph     0x10	
#define  F_PhA    0x01
#define  F_PhB    0x02
#define  F_PhC    0x04

#define  F_nPhs    0x80	
#define  F_APhs    0x40
#define  F_BPhs    0x20
#define  F_CPhs    0x10

#define  F_Dir    0x03
#define  F_PDir	0x02
#define  F_QDir	0x01

#define  F_TamTmr    0xC0

	// TamFlg Register flags define
#define  F_TamStop   0x01
#define  F_TamDrop   0x02
#define  F_TamResv   0x04
#define  F_TamPole   0x08
#define  F_TamPass   0x10
#define  F_TamUout   0x20
#define  F_TamLoad   0x40
#define  F_TamSequ   0x80

	// ErrFlg Register flags define
//#define  F_ErrMeasMin	0x01		//����оƬ���� ���з���
#define  F_ErrMeasSec	0x02		//����оƬ���� ���з���
#define  F_ErrMeasFlashDis	0x04	//���Ǻ�Һ��һֱ��˸
#define  F_ErrOpenCoverDis	0x08	//���Ǻ�Һ��һֱ��˸
/*
#define  F_ErrBatLow   	0x02
#define  F_ErrDir   	0x04
#define  F_ErrPhs 		0x08		// 
#define  F_ErrBatOver	0x10		// 
#define  F_WatchDog		0x20
#define  F_ErrClock		0x40		// 32768Hz Crystal Error
#define  F_ErrE2P   	0x80
*/

/*	// AlarmFlg Register flags define
#define  F_AlarmPhFail	0x01		//���౨��
#define  F_AlarmCuFail	0x02		//��������
#define  F_AlarmBatLow  0x08		//��ص͵�ѹ����
#define  F_AlarmPhs 	0x10		//�����򱨾� 
#define  F_AlarmNLine 	0x20		//�����߱��� 
#define  F_AlarmByPass 	0x40		//������·���� 
*/

	// AlarmFlg[0] Register flags define
#define  F_AlarmCoverOpen	0x01		//���Ǳ���//#define  F_AlarmPhFail	0x01		//���౨��
#define  F_AlarmTCoverOpen	0x02		//���Ǳ���//#define  F_AlarmAllCuFail	0x02		//ȫ��������
#define  F_AlarmMagnet	0x04		//�ų�����//#define  F_AlarmMeas	0x04		//����оƬ����
#define  F_AlarmCRCFail	0x08		//CRCУ�����
#define  F_AlarmPhs 	0x10		//�����򱨾� 
#define  F_AlarmReverse	0x20		//���ʷ��򱨾�
#define  F_AlarmClock	0x40		// 32768Hz Crystal Error
#define  F_AlarmE2P   	0x80

//#define  F_AlarmCuFail	0x20		//��������
//#define  F_AlarmBatLow  0x08		//��ص͵�ѹ����
//#define  F_AlarmNLine 	0x20	//�����߱��� 
//#define  F_AlarmByPass 	0x40	//������·���� 


	// AlarmFlg[1] Register flags define        
#define  F_AlarmFlash	0x01		//FLASH���� 
#define  F_AlarmXT1		0x02		//XT1���񱨾�
#define  F_AlarmBATCH	0x04		//��ر���
#define  F_EventPhs		0x08		//�������¼�������

	// AlarmFlg[3] Register flags define
#define  F_EventKEYSF	0x01		//�����Ϸ���
#define  F_EventKEYXF	0x02		//�����·���
#define  F_EventKEYPF	0x04		//������̼�
#define  F_EventCoverOpen	0x08		//�������Ǽ���
#define  F_EventTCoverOpen	0x10		//�������˼���
#define  F_EventMagnet		0x20		//�����ų�����
#define  F_EventFLQH			0x40		//���������л���1
#define  F_EventFLQH1		0x80		//���������л���2


	// FirstFlg Register flags define
#define  F_PhAFail	0x04		//��һ��A�����δ��¼
#define  F_PhBFail	0x08		//��һ��B�����δ��¼
#define  F_PhCFail	0x10		//��һ��C�����δ��¼
#define  F_CuAFail	0x20		//��һ��A�����δ��¼	//��ΪA����������־
#define  F_CuBFail	0x40		//��һ��A�����δ��¼	//��ΪB����������־
#define  F_CuCFail	0x80		//��һ��A�����δ��¼	//��ΪC����������־

/*
#define  F_ErrRAM    0x01
#define  F_ErrMeas   0x02		//����оƬ����
#define  F_ErrE2P    0x04
#define  F_ErrDFls   0x08
#define  F_ErrCry1 	0x10		// 32768Hz Crystal Error
#define  F_ErrCry2 	0x20		// 8MHz Crystal Error
#define  F_WatchDog	0x40
#define  F_ErrANY    0x80
*/
//LoadFlag Register flags define   
#define  F_LoadCom	0x01		//ͨѶģʽ3����һ�ηֿ����ݷ���Ϊ�ո�������
#define  F_TampCom	0x02  		//ͨѶģʽ3����һ�ηֿ����ݷ���Ϊ�Ե��¼����
   
//BatState Register flags define   
#define  F_ClockBat	0x01		//ʱ�ӵ��״̬  0:Ƿѹ��1������ 
#define  F_CommBat	0x02		//ͣ�����״̬   
#define	 F_E2PCheck	0x04		//������E2PROM�Ƿ���ȷ��0����ȷ��1������У��;���	//EC	
   
//ClrFlag Register flags define   
#define  F_ECClr	0x01		//��������
#define  F_EventClr	0x02		//�¼�����
#define  F_ECClr_EN	0x04		//��������ʹ��
#define  F_MSET_EN	0x08		//�������ʹ��
#define  F_SSET_EN	0x10		//���к�����ʹ��
#define  F_Save_EN	0x80		//�µ�һ���ϵ����ʹ��
//#define  F_SD16AInit_EN	0x40		//��ʼ����ʹ��
#define  F_Metertype_EN	0x40		//����������״̬

//MDState Register flags define   
#define  F_MDOVER	0x01		//��������
//MeterState Register flags define   
#define	 F_RelayState	0x01
#define  F_BatterTest	0x04
 
// �¼���¼
#if 0
//////////////////////////////////
#define Cover_No			3	//����
#define TCover_No			4	//����
#define PhAFail_No			0	//A�����
#define PhBFail_No			1	//B�����
#define PhCFail_No			2	//C�����
#endif

#define MagnetOn_No			5	//�ų�
#define TimeSET_No			6	//ϵͳʱ������
#define TimeAsynchronous_No		7	//ʱ���첽��־
#define ManipulationRecognized_No	8	//����


#define	READ	0x8000
#define	WRITE	0x4000
#define	PERMIT	0x2000
#define XPERMIT 0x1000

typedef struct
{
	unsigned int	StatusWord;	//�������״̬8 Status word
	unsigned char 	Power;
	unsigned char	Clk;
	unsigned char	Disk;
	unsigned char	ClrFlag;
	unsigned char   Key1;
	unsigned char RevState;		//��������״̬�ֽ� 0��������0x01:A�෴��, 0x02:B�෴�� , 0x04:C�෴��
	unsigned char RevOldSte;	//ǰ��������״̬�ֽ� 0��������0x01:A�෴��, 0x02:B�෴�� , 0x04:C�෴��
	unsigned char   AlarmFlg[4];
	

   	unsigned char 	Run0;
   	unsigned char 	Run1;

	unsigned char 	BatState;
	unsigned char 	MDState;
	
	unsigned char	MeterState;	//���״̬
	unsigned char	NetState;	//����״̬
	unsigned char	BautState;
//	unsigned char 	PwDirP;		//�й����ʷ���
//	unsigned char 	PwDirQ;		//�޹����ʷ���
	unsigned char 	PwDirPQ;	//�й��޹����ʷ���
	unsigned char 	PwDirPQ2;	//�й��޹����ʷ���
	unsigned char 	PwDirPQ3;	//�й��޹����ʷ���	
	unsigned char   FirstFlg;	//��һ���¼���־�� 0���Ѽ�¼��1��δ��¼ //��Ϊ���������ʸ
   	unsigned char 	LoadFlg;
		
    	unsigned char 	ErrFlg;

	unsigned char   Event;
	unsigned char   Key;

	unsigned char 	VolFlg;	//��ѹʧѹ��־//
	unsigned char 	CurrStar;		
	
	unsigned char Prgtariff;	//���ʱ�̼�¼��־
	
	unsigned long DoClear ;		
	unsigned long DoClockTest;
} FLAG;

typedef struct
{
	short Init_Flag;		//��ʼ���	
	unsigned char FeeNo;
	unsigned char CoverOpenState;	//�����״̬�ֽ� 0�������ǣ�0x01:����,   
	unsigned char CoverOpenOldSte;	//�����״̬�ֽ� 0�������ǣ�0x01:����,
	unsigned char TCoverOpenState;	//�����״̬�ֽ� 0�������ˣ�0x01:����,   
	unsigned char TCoverOpenOldSte;	//�����״̬�ֽ� 0�������ˣ�0x01:����,   
	unsigned char MeterResetState;	//����ϵ�״̬�ֽ� 0�����ϵ磬0x01:�ϵ�,   
	unsigned char MeterResetOldSte;	//����ϵ�״̬�ֽ� 0�����ϵ磬0x01:�ϵ�,   
	unsigned char MagnetOnState;	//���ų�״̬�ֽ� 0���ų���Ӱ�죬0x01:�ų�Ӱ��,   
	unsigned char MagnetOnOldSte;	//���ų�״̬�ֽ� 0���ų���Ӱ�죬0x01:�ų�Ӱ��, 
	unsigned char PhAFailState;	//���A��ʧѹ״̬�ֽ� 0����ʧѹ��0x01:A��ʧѹ,   
	unsigned char PhAFailOldSte;//���A��ʧѹ״̬�ֽ� 0����ʧѹ��0x01:A��ʧѹ,   
	unsigned char PhBFailState;	//���B��ʧѹ״̬�ֽ� 0����ʧѹ��0x02:B��ʧѹ,   
	unsigned char PhBFailOldSte;//���B��ʧѹ״̬�ֽ� 0����ʧѹ��0x02:B��ʧѹ,   
	unsigned char PhCFailState;	//���C��ʧѹ״̬�ֽ� 0����ʧѹ��0x04:C��ʧѹ,   
	unsigned char PhCFailOldSte;//���C��ʧѹ״̬�ֽ� 0����ʧѹ��0x04:C��ʧѹ, 
	unsigned char MagnetOnStateTime;  
	unsigned char CPUCRC[2];	//CPU�������CRCֵ
	unsigned char CPUCRC_M[2];	//CPU�������CRCֵ
#if 0	
	unsigned long long APowerPulPL;	//�ϴζ�ȡ����ֵ//8207 �й�
	unsigned long long BPowerPulPL;
	unsigned long long CPowerPulPL;
	

	unsigned long PowerPp;			//һ�����ۼƹ��ʣ�ÿ�룩
   	

	unsigned long	ILoadPulseSumP;	//���ɼ�¼�й����������
#endif
#if 0
#if ( Threephase == YesCheck ) //����
#if (( MEASCHIP == ADE7755 )||( MEASCHIP == RN8207 ))
	unsigned long	IPulseDirSumP;	//���й���˲ʱ���ʷ����жϵ����������������
	unsigned long	IPulseDirSumPA;	//A�����й���˲ʱ���ʷ����жϵ����������������
	unsigned long	IPulseDirSumPB;	//B�����й���˲ʱ���ʷ����жϵ����������������
	unsigned long	IPulseDirSumPC;	//C�����й���˲ʱ���ʷ����жϵ����������������

	unsigned long	IPulseSumP;		//���й��жϵ����������������	   	
	unsigned long	IPulseSumPA;	//A�����й��жϵ����������������	   	
	unsigned long	IPulseSumPB;	//B�����й��жϵ����������������	   	
	unsigned long	IPulseSumPC;	//C�����й��жϵ����������������	
	
	unsigned long	IPulseDirSumPn;	//���й���˲ʱ���ʷ����жϵ����������������
	unsigned long	IPulseDirSumPnA;	//A�����й���˲ʱ���ʷ����жϵ����������������
	unsigned long	IPulseDirSumPnB;	//B�����й���˲ʱ���ʷ����жϵ����������������
	unsigned long	IPulseDirSumPnC;	//C�����й���˲ʱ���ʷ����жϵ����������������

	unsigned long	IPulseSumPn;		//���й��жϵ����������������	   	
	unsigned long	IPulseSumPnA;	//A�����й��жϵ����������������	   	
	unsigned long	IPulseSumPnB;	//B�����й��жϵ����������������	   	
	unsigned long	IPulseSumPnC;	//C�����й��жϵ����������������
	
	
	unsigned long 	SecIPulseSumP;   	
	short	RUaBase;		//A���ѹ��׼
	short RUbBase;		//B���ѹ��׼
	short	RUcBase;		//C���ѹ��׼
	short	RUBaseCheck;	//���������׼У���

	unsigned short	RYaBase;		//A����������׼
	unsigned short	RYbBase;		//B����������׼
	unsigned short	RYcBase;		//C����������׼
	unsigned short	RYBaseCheck;	//���������׼У���
#endif
#endif
#endif

//	unsigned long 	RRunOverSumTime;	//�����ۼ�ʱ��		//0701

//	unsigned short 	RUcVolt;		//C���ѹADֵ������������
//	unsigned char 	PhsStata;		//����������	
//	unsigned char 	PhsCnt;			//����������	
//	unsigned char 	PhsCnt1;			//����������	
//	unsigned char 	PhsCnt2;			//����������
//	unsigned char 	PhsCnt3;			//����������		

//	int BJGDly;			//������ʾʱ��
//	int RDisHours;		//ͣ�����ʾСʱ��ͣ 9999�����ر�

// 	int RBatComHours;	//ͣ���ͣ�����ά��Сʱ��(3) 	
	short KeyXPushDly;	//X���������ۼ�ʱ�䣬��λ1/64��   ����8��󴥷�ͣ��������20����ٴ���
	//short KeySPushDly;	//Y���������ۼ�ʱ�䣬��λ1/64��   ����8��󴥷�ͣ��������20����ٴ���
//	short KeyDly;

//	int SampleCnt;		//��������������
//	int Init_Flag;		//��ʼ���		

//	unsigned short ReadMeasTime;	//��ʱ������оƬ������
	
#if( SecurityCheck == YesCheck )				
	short LabDelay;		//48Сʱ��ʱ
#else
#endif
 	unsigned short PhABCFailState;
#if 0
	unsigned long	MD_CumPp;		//1�������й�����������
	unsigned long MD_CumPp1;		//1�������й�����������
	unsigned long MD_CumPp2;		//1�������й�����������
	unsigned long MD_CumPp3;		//1�������й�����������
	unsigned long MD_CumPp4;		//1�������й�����������	

	unsigned long MD_CumPpPR;		
	unsigned long MD_CumPpPpMin;	
	unsigned short MD_CumPpPpMin1;	
	unsigned short MD_CumPpMin[60];		// 15.4.0
#endif	

 	unsigned short PowerA1S;		//������ʱ��A��Ķ�ʱ1S//8207
	unsigned short PowerB1S;
	unsigned short PowerC1S;
	unsigned short PowerA1SCnt;		//������ʱ��A��Ķ�ʱ1S//
	unsigned short PowerB1SCnt;
	unsigned short PowerC1SCnt;
	unsigned short PowerA1SCnt1[4];		//������ʱ��A��Ķ�ʱ1S//
	unsigned short PowerB1SCnt1[4];
	unsigned short PowerC1SCnt1[4];
	unsigned short ReadPowerCnt;

	unsigned char CRESET_ENCnt;		//�ͻ�����ʹ�ܼ�ʱ
	
#if ( Threephase == YesCheck ) //����
#if (( MEASCHIP == ADE7755 )||( MEASCHIP == RN8207 ))
	unsigned char 	SecSumPluse;	//0701
	unsigned char 	SecPluseCnt;	//ƽ�����ʼ�ʱ��	//0701
#endif		
#endif

	unsigned char PowerRev;		//���ʷ���//0701

#if( SecurityCheck == YesCheck )				
	unsigned char	LabStateCnt;	//�й�ʵ����״̬�Ĵ���
	unsigned char	LabState;		//���ʵ����״̬�Ĵ���
	unsigned char	NewLabState;	//���ʵ������״̬�Ĵ���
#else
#endif
	unsigned char 	CalibCnt;		//У���ʱ
//  BCD2    Wendu;	
//	unsigned char ZoneNo;			//ʱ����

//�������������������ڷ����л�ʱ�����㣬���������������������ڷ����л�ʱ����
	unsigned char MD_Cunt;		//�����Ӽ�������ʱ��Ҫ��ǰ��ȡ���������建��������
	unsigned char MD_CuntT;		//�����Ӽ����������ʱ��Ҫ��ǰ��ȡ���������建��������
	unsigned char MD_BufAds;	//��ǰ������������ַ
	
	unsigned short PL_CumPp;
	unsigned short PL_CumPp1;
	unsigned short PL_CumPp2;
	unsigned short PL_CumPp3;
	unsigned short PL_CumPp4;

	unsigned short PL_CumPn;
	unsigned short PL_CumPn1;
	unsigned short PL_CumPn2;
	unsigned short PL_CumPn3;
	unsigned short PL_CumPn4;

	unsigned short PL_CumPz;
	unsigned short PL_CumPz1;
	unsigned short PL_CumPz2;
	unsigned short PL_CumPz3;
	unsigned short PL_CumPz4;
	
	unsigned short PL_CumCheck;


	unsigned short YPulse_Cum;//����ֵ
	unsigned short YPulse_CumAL;//������
	unsigned short WPulse_Cum;
	unsigned short YPulse_CumA;
	unsigned short YPulse_CumB;
	unsigned short YPulse_CumC;	
	unsigned short PL_PowerOffCheck;
	
	unsigned int CoverOpenCnt;
	unsigned int TCoverOpenCnt;
	unsigned int MagnetOnCnt;
	unsigned char MeterResetCnt;
//	unsigned char APhBkCnt;
//	unsigned char BPhBkCnt;
//	unsigned char CPhBkCnt;

	unsigned char PhAFailCnt;
	unsigned char PhBFailCnt;
	unsigned char PhCFailCnt;
	unsigned char StateFailCnt;
	
	unsigned char StateFailState;	//���C��ʧѹ״̬�ֽ� 0����ʧѹ��0x04:C��ʧѹ,   
	unsigned char StateFailOldSte;//���C��ʧѹ״̬�ֽ� 0����ʧѹ��0x04:C��ʧѹ,   
	
	unsigned char FeeNoDelay;
  unsigned char RelayState;	//�̵���״̬		
	unsigned char MDPCT;		//�������������������������ʱ�����������Ƭ��
	unsigned char MD_PCT;		//����Ƭ��������	
	unsigned char MDPMinCT;		//��������ʱ���ڷ��Ӽ�����
	unsigned char MD_60T;		//60����/��������
#if 0
	unsigned char PulWidthled;			//������//
	unsigned char PulWidthS0;			//������//

	unsigned int Constled;	//LED���峣��14.2.9wwl
	unsigned int Consts0;	//s0���峣��
	unsigned char Tariffsnu;	//������
	

	unsigned char YPulse_Mode;
//	unsigned char WPulse_Mode;
	unsigned char YPulse_Modeled;
	unsigned char YPulse_Modes0;
	unsigned char WPulse_Modeled;
	unsigned char WPulse_Modes0;
#endif	
	unsigned char Kb_Cnt2;
	unsigned short Kb_Cnt1;
	unsigned long  Kb_Cnt3;

#if 0	
	unsigned char Kb_Cnt3;
	unsigned char Kb_Cnt4;	
	unsigned char Kb_Cnt5;	
	unsigned char Kb_Cnt6;	
#endif	
	
	unsigned char ENCount;		//���ʹ��
	unsigned char ENCLRCount;
	unsigned char MenSetDly;
	unsigned char PrgDly;
	unsigned char MCloseBillingCount;
	unsigned char MClearBillingCount;
	unsigned char TestRelayCount;
	
	unsigned char CalibCount;

	unsigned char WKUPCT;
	unsigned char Relay1Time;
	unsigned char Relay2Time;
	unsigned char RelayTimeCnt;
	unsigned char RelayTestTimeCnt;
	unsigned char RelayDelTimeCnt;
	unsigned char ECFlashDly;		//"����"��˸��ʱ
	unsigned char FeeNoTestCnt;		//"����"��˸��ʱ	

	unsigned char TestDisCnt;  
  unsigned char TestDisCntButton;  
	unsigned char RDisDays;			//ͣ�����ʾСʱ��(6��=144Сʱ) 
	unsigned char RAwakeDisDays;	//ͣ�绽��֧��ʱ��  //V30
	
	unsigned short PoffPassword;	//ͣ����ʱ��

    unsigned char PowerUpTime;
    unsigned char BatUpTime;
 	unsigned char RECMode;			//0:�����ͣ�1:����ֵ ����	
 	unsigned char OldRECMode;		//���ǰ������ʽ  0:�����ͣ�1:����ֵ
//	unsigned char PassWd_ErrCnt;
#if 0
	unsigned char ECPulseWidthCnt;
	unsigned char PulseWidthCnt;
    unsigned char RPulseOutMode;
//    unsigned char SecPulseCnt;		//��������� 
//    unsigned char MDResetForbid;
    unsigned char ErrPhsCunt;		//�������˲�������
    unsigned char HWBGDelay;
//    unsigned char ADTimeCnt;		//AD����ʱ����(��250usΪ��λ)
//	unsigned char AmperOverDelay;	//���ؼ����ʱʱ��
	unsigned char RevDelay;			//������������ʱʱ��
	unsigned char ECRevDelay;		//���ܷ�������ʱʱ��
	unsigned char ADSampleMode;		//AD����ģʽ  0���е���������1��ֻ������ص�ѹ
//	unsigned char ADChannelNo;		//AD����ͨ����
	unsigned char DataRomoveMode;
#endif	
	unsigned char ECLedModeCnt;		//�й��������ʾģʽ��ʱ
	
	unsigned char Load_time;	
	unsigned char SD16ACount;//�ϵ��ʼ����ʱ��
	
	unsigned char setkey_sum;
	unsigned char menustep;
	
	unsigned char menustep1;	//ģʽ
	unsigned char menustep2;	//done	
	unsigned char menustep3;	//set time 
	unsigned char menustep4;	//ʱ������ʱ�򳤰�����־ 
	
	unsigned char Key_Map;
	unsigned char PrgKeyState;
	unsigned char ErrCode;
	unsigned char RollItemPt;
	unsigned char BatteryWTime[5];
	unsigned char TestCnt;	//testmode ��ʱ3Сʱ

	unsigned char Testram[10];		//Һ��PIN_CODE����
	unsigned char Testram11[10];  //Һ��PIN_CODE
	unsigned char RamEnger[10];
	unsigned char RamEngerT1[10];
	unsigned char RamEngerT2[10];
	unsigned char GetLAPowerNo;
	unsigned char GetLBPowerNo;
	unsigned char GetLCPowerNo;
	unsigned char ItemPtr;
	unsigned char mag_flag;
	unsigned char tcover_flag;
	
  unsigned short day_no;	
	unsigned short week_no;
	unsigned short month_no;
	unsigned short year_no;
} SRAM;


typedef struct
{
	unsigned short SolutionName;
	unsigned short Irreguholi1;
//	unsigned int Irreguholi2;
//	unsigned int Irreguholi3;
//	unsigned int Irreguholi4;
//	unsigned int Irreguholi5;
//	unsigned int Irreguholi6;
//	unsigned int Irreguholi7;
//	unsigned int Irreguholi8;
	unsigned short Reguholi;
	unsigned short Season;
	unsigned short WeekSdb1;
//	unsigned int WeekSdb2;
//	unsigned int WeekSdb3;
//	unsigned int WeekSdb4;
	unsigned short DaySdb1;
//	unsigned int DaySdb2;
//	unsigned int DaySdb3;
//	unsigned int DaySdb4;
//	unsigned int DaySdb5;
//	unsigned int DaySdb6;
} COMPLEXSD;


typedef struct
{
	unsigned short SolutionName;	
	unsigned short DaySdb1;
}SIMPLESD;

//typedef struct
//{
//	unsigned short RollItemAdd;	
//}LCDROLL;

typedef struct
{
	unsigned short ECBufAds;
	unsigned short ECBufAdsPtr;
	unsigned short ECRgAds;
#if ( Threephase == YesCheck ) //����		
//	unsigned char* ECRamBufAds;
	unsigned short* ECRamBufAds;
#else
	unsigned short* ECRamBufAds;	
#endif

} ECRg;

typedef struct
{
	short DevAds;
	short NextPage;
	unsigned char BakNum;
	unsigned char CorrectMode;
} E2Para;


typedef struct
{
	unsigned char (*p)(void);
	unsigned char	* State;		 
	unsigned char	* OldState;
	unsigned int * Cunt;	
	unsigned int  E2Addr;
}TAMPER;	

typedef struct
{
	unsigned short PtAddr;
	unsigned short StartAddr;
	unsigned char RecdCunt;
	unsigned char RecdLenth;	
	unsigned char Items;
	unsigned char InArrayAddr;
} PTPARA;	

// 	ZjState					// �㽭ʡͨѶ��Լ�������״̬
#define zjIdle			0	// ͨѶ����
#define zjBufBusy		1	// ��ʼ�����ݣ�ͨѶ����æ
#define zjRead			2	// ��������
#define zjDataSend1Wait	3	// ���ݰ�1���͵ȴ�
#define zjDataSend2		4	// ���ݰ�2����
#define zjDataSend2Wait	5	// ���ݰ�2���͵ȴ�
#define zjDataSend3		6	// ���ݰ�3����
#define zjDataSend3Wait	7	// ���ݰ�3���͵ȴ�
#define zjDataSend4		8	// ���ݰ�4����
#define zjDataSend4Wait	9	// ���ݰ�4���͵ȴ�
#define zjExit			10	// ͨѶ�˳�

//Comm.State1 
#define ATT7053Set	0x01	//ATT7053����
#define ATT7053Read	0x02	//ATT7053��ȡ
#define ATT7053CommOK	0x04	//ATT7053ͨ�ųɹ�

	// Run flags define
#define  FComOK0   0x01		//����0������ϱ�־(���ͻ����)
#define  FComOK1   0x02		//����1������ϱ�־(���ͻ����)
#define  FComOK2   0x04		//����2������ϱ�־(���ͻ����)
#define  FComOK3   0x08		//����3������ϱ�־(���ͻ����)
	// INFORunFlag flags define
#define  FStatu_One   0x01		//statu one byte

typedef struct
{  	
	uint32_t	SecPulseCnt;			//�ϵ����ʱ
	uint32_t	TimeSecPulseCnt;		//EDL40ʱ�����ʱ
	uint16_t	CRCRegInit;		//infor CRC	
	uint16_t	CRCEventInit;		//event CRC	
	uint16_t 	BTime3;				// 485��3�ַ��䶨ʱ
	uint16_t 	BTime2;				// 485��3�ַ��䶨ʱ
	uint8_t		INFORunFlag;
	uint8_t 	TX_Delay2;
//	uint8_t   Rdout300bps0;
	uint8_t   Rdout300bps1;
	uint8_t   Delay1;
//	uint8_t   Delay0;
	uint8_t   PassWordErrCnt;
	uint8_t   BlockNo1;
//	uint8_t   BlockNo0;
//	uint8_t   TXLAST_Delay0;
	uint8_t   Ptr1;
	uint8_t   TX_Delay1;
	uint8_t   Mode1;
	uint8_t   FTime1;
	uint8_t   BTime1;
	uint8_t   State1;
	uint8_t   SendLen1;
	uint8_t   Bcc1;
	uint8_t   RecTmr1;
	uint8_t   PrgTmr1;
	uint8_t   TXLAST_Delay1;
	unsigned char	RdoutContent[2];
} COMM;

//8207��Uartͨ��//
typedef struct
{
	unsigned char NeedRecCnt;			//��Ҫ���յ����ݳ���//
	unsigned char NeedSendCnt;		//��Ҫ���͵ĳ���//
	unsigned char RecBuf8207[10];	//���ջ�����//
	unsigned char SendBuf8207[10];	//���ͻ�����//
	unsigned char PhaType;			//���1=A�࣬2=B�࣬3=C��//
	unsigned char CommOk;			//ͨ����ɱ�־��0X55=ͨ�����//
	unsigned char Ptr8207;			//8207ͨ��ʱ��ָ��//
	unsigned short CommDly;			//ͨ�Ŷ�ʱ���������ʱ�����ͨ�ų���//
	unsigned char ReadPowerState;
	
}COMM8207;

typedef struct
{
	unsigned char *Buf;				// ͨѶ������
	unsigned char *Buf2;			// ͨѶ������2
	unsigned char *Mode;			// ͨѶģʽ
	unsigned char *State;			// ͨѶ״̬	
	unsigned char *Ptr;				// ������ָ��
	unsigned char *BTime;			// �ַ��䶨ʱ
 	unsigned char *Bcc;				//��������У��� 
	unsigned char *RecTmr;			// ���ռ�¼��ʱ
	unsigned char *PrgTmr;			// ��̼�¼��ʱ
	unsigned char *Run;				// ���б�־ 
	unsigned char *TXLAST_Delay;
  unsigned char *Delay;
}COMMPARA;

typedef struct
{
	unsigned long  *LoadPtr;			// ��������ͨѶ��־		
	long  *LoadPtrend;			// ��������ͨѶ����ָ��	
	unsigned char *BlockNo;			//���ڼ������ݣ����ڷֿ鷢�ͣ�
	unsigned char *SendLen;			//���ͳ��ȣ����ڷֿ鷢�ͣ�
//	unsigned char *HisMonth;		//���ڼ��µ���ʷ����
//	unsigned char *EventCode;		//�������¼�
	unsigned char *ProfDate;		//����������ʼ������ʱ�� 
//	unsigned char *Top10;			//����TOP10ʱ��ָ��	
}BLOCKCOMMPARA; 

typedef struct
{
	void (*p)(unsigned char );	
}READOUT;

typedef struct
{
	unsigned char 	ComID1;
	unsigned char 	ComID2;	
	unsigned char 	ComID3;
	unsigned char 	ComID4;
	unsigned char 	ComID5;
	unsigned short 	Len;
	unsigned short 	Addr;
	unsigned short	State;
}COMDISTAB;

typedef struct
{
	unsigned char 	ComID1;
	unsigned char 	ComID2;	
	unsigned char 	ComID3;
	unsigned char 	ComID4;
	unsigned char 	ComID5;
	unsigned short 	Len;
//	unsigned short 	Addr;
//	unsigned long	 	Addr;	
	unsigned long		Addr;	
	unsigned short	State;
}CDPARATAB;

typedef struct
{
	unsigned char 	OldTariDis;		
	unsigned char 	NewTariDis;	
}TARINAMCONVERT;

typedef struct
{
	unsigned short 	ComID;
	unsigned short 	Addr;
  	unsigned short 	ComInfo;
}COMTAB;

typedef struct
{
	unsigned char MarSun;
	unsigned char OctSun;	
}LASTSUNDAY;

/*
typedef struct
{
	unsigned int 	DisID;
	unsigned int 	Addr;
	unsigned char 	Length;
	unsigned char	State1;
	unsigned char	State2;
	unsigned char	State3;	
	unsigned char	State4;
	unsigned char	State5;
}DISTAB;
*/
/*
typedef struct
{
	unsigned int 	Addr1;
	unsigned int 	Addr2;
	unsigned char	State1;
	unsigned char	State2;
	unsigned char	State3;
	unsigned char	State4;
}DISTAB;
*/

#if 0
typedef struct
{
//	unsigned char* 	Addr;
	unsigned short Addr;	
	
//	unsigned char	State1;
//	unsigned char	State2;
//	unsigned char	State3;	
	unsigned char	ComID2;	
	unsigned char 	Length;
//#if (Threephase == YesCheck) 	//13.2.25wwl
//	unsigned char	State4;	
	unsigned char	ComID4;	
//#else//13.2.25wwl
//#endif//13.2.25wwl
	unsigned char	Obis0;	
	unsigned char	Obis1;	
	unsigned char	Obis2;	
	unsigned char	Obis3;	
	unsigned char	Obis4;	
	unsigned char	Obis5;		
	unsigned char	State5;	
	unsigned char	State6;	
}DISTAB;
#else
typedef struct
{
	unsigned char	Obis0;	
	unsigned char	Obis1;	
	unsigned char	Obis2;
	unsigned char Length;
	unsigned char dotnum;
	unsigned char uint;
	unsigned char attri;
	unsigned int  Addr;	
}DISTAB;
#endif

typedef struct
{
	unsigned char	Char1;
	unsigned char	Char2;
	unsigned char	Char3;
	unsigned char	Char4;
	unsigned char	Char5;
	unsigned char	Char6;
	unsigned char	Char7;	
	unsigned char	Char8;
}DISMENUTAB;

//typedef struct
//{
//	unsigned char 	*Buf;			// ͨѶ������
//	unsigned char 	*Mode;			// ����ԼͨѶģʽ
//  	unsigned char 	*Ptr;			// ������ָ��
//  	unsigned int 	*BTime;			// �ַ��䶨ʱ
//  	unsigned char 	*SendDTime;		// ������ʱ
//}COMMPARA;

#if( ZjProtocol	== YesCheck )		// ���㽭ͨѶ��Լ
typedef struct
{
	unsigned char 	*Buf;			// ͨѶ������
	unsigned char 	*Mode;			// ����ԼͨѶģʽ
  	unsigned char 	*Ptr;			// ������ָ��
  	unsigned short 	*BTime;			// �ַ��䶨ʱ
  	unsigned char 	*SendDTime;		// ������ʱ
	unsigned char	*ZjState;		// �㽭��ԼͨѶ״̬
	unsigned char	*ZjLength;		// �㽭��Լÿ�����ݷ��ͳ���
	unsigned char	*ZjCheck;		// �㽭��Լÿ������У���
}ZJCOMMPARA;
#else
#endif

typedef struct
{
//	unsigned short 	MDBufAds;		// ������������ַ
//	unsigned short 	*MDCum;			// 1�����ۼ�������
#if ( Threephase == YesCheck ) //����		
	unsigned long 	*MDCum;			// 1�����ۼ�������
#else
	unsigned long 	*MDCum;			// 1�����ۼ�������
#endif
	
}MDPARA;

//typedef struct
//{
//	unsigned long* 	SampleSum;		// n�������ڲ����������ۼӺ�
//	unsigned char* 	Irms;			// �������Чֵ
//}IRMSPARA;

typedef struct
{
	unsigned short 	ECAddr;			//���ڶ�����ַ
  	unsigned short 	EnterDay;		//���뼾������
	unsigned short	OutDay;			//�˳���������
	unsigned char*  ZoneNo;			//��ǰʱ����
}SEASONPARA;

typedef struct
{
	unsigned char 	ADERgAddr;		//7758�Ĵ�����ַ
  	unsigned char 	Length;			//�Ĵ����ֽڳ���
}ADEPara;

typedef struct
{
	unsigned char*  RamRgAddr;		//˲ʱֵRAM��ַ		
	unsigned char 	ATTRgAddr;		//ATT7022�Ĵ�����ַ
  	unsigned char 	Length;			//�Ĵ����ֽڳ���
}RamPara;

typedef struct
{
	short CommID;		//ͨѶ����
	short Length;		//�鳤��
  	short Cycle;		//������
}ADESwapPara;

#if ( ZjProtocol == YesCheck)
typedef struct
{
	unsigned short 	ComID;
	unsigned char* 	Addr;
  	unsigned short 	ComInfo;
}ZJCOMTAB;
#else
#endif


typedef struct
{
	unsigned char 	ComID1;
	unsigned char 	ComID2;	
	unsigned char 	ComID3;
	unsigned char 	ComID4;
	unsigned short 	Len;
	unsigned short 	Addr;
	unsigned short	State;
}EXECUTETAB;

typedef struct
{
	unsigned char* SDA_DIR;
	unsigned char* SCL_DIR;
	unsigned char* SDA_IN;
	unsigned char SDA;
	unsigned char SCL;
}I2CPARA;							//I2C�ӿ�оƬ��CPU�ϵ�IO�����ò���

typedef struct
{
	unsigned char RegAddr;
	unsigned char Length;
}MEASREG;

typedef struct
{
	unsigned long	long ABCPowerPulSum;	//�����������������������ۼƺ�//����ֵ
	unsigned long	long APowerPulSum;	//A���������������������ۼƺ�//
	unsigned long	long BPowerPulSum;	//B���������������������ۼƺ�//
	unsigned long	long CPowerPulSum;	//C���������������������ۼƺ�//
	
//	unsigned long APowerPulPP;	//A��������������ѳ���У�����������������ж�����//
//	unsigned long BPowerPulPP;	//B��������������ѳ���У�����������������ж�����//
//	unsigned long CPowerPulPP;	//C��������������ѳ���У�����������������ж�����//
//	
//	unsigned char APower[4];	//A�๦������//
//	unsigned char BPower[4];	//B�๦������//
//	unsigned char CPower[4];	//C�๦������//
//	unsigned long ABCPower;	//ABC�๦������//
	unsigned long APowerPulP;	//A��������������ѳ���У����������������//
	unsigned long BPowerPulP;	//B��������������ѳ���У����������������//
	unsigned long CPowerPulP;	//C��������������ѳ���У����������������//
	unsigned long ABCPowerPulP;	//����������������ѳ���У����������������//

	unsigned long APowerPulPBak;	//A��������������ѳ���У�������������ϴ�����//
	unsigned long BPowerPulPBak;	//B��������������ѳ���У�������������ϴ�����//
	unsigned long CPowerPulPBak;	//C��������������ѳ���У�������������ϴ�����//


//	unsigned long APowerPulN;	//A��������������ѳ���У�������ĸ�������//
//	unsigned long BPowerPulN;	//B��������������ѳ���У�������ĸ�������//
//	unsigned long CPowerPulN;	//C��������������ѳ���У�������ĸ�������//
//	unsigned long ABCPowerPulN;	//����������������ѳ���У�������ĸ�������//
//
//	unsigned long APowerPulNBak;	//A��������������ѳ���У�������ĸ����ϴ�����//
//	unsigned long BPowerPulNBak;	//B��������������ѳ���У�������ĸ����ϴ�����//
//	unsigned long CPowerPulNBak;	//C��������������ѳ���У�������ĸ����ϴ�����//

//	unsigned char FlagDireABC;	//ABC����ķ���//
//	unsigned char ModePN;	//������ʽ//
//
//
//	unsigned char AAdjust[2];	//A��У���������//
//	unsigned char BAdjust[2];	//B��У���������//
//	unsigned char CAdjust[2];	//C��У���������//
//	
//	unsigned char AdjustSum[2];	//У�����У���//

	unsigned char	AStartM;
	unsigned char	BStartM;
	unsigned char	CStartM;
	
//	unsigned char	AReadErrCnt;//��8207����Ĵ����������ζ�����ʱ����оƬû�ϵ磬����������ֵ��0//
//	unsigned char	BReadErrCnt;
//	unsigned char	CReadErrCnt;
//        
  	unsigned char	MeaOneA;//�ж�ĳ��ʧѹ����15���������м����ߵ�//
	unsigned char	MeaOneB;
	unsigned char	MeaOneC;
	unsigned char 	PulWidth;				//������//
	unsigned char 	PulS0Width;				//������//
	
}MEASURE7053;	

#define	F_ADire		0x01		//A��ķ���//
#define	F_BDire		0x02		//B��ķ���//
#define	F_CDire		0x04		//C��ķ���//
#define	F_ABCDire	0x08		//����ķ���//

typedef struct
{
	unsigned long long ABCPowerPulSum;	//�����������������������ۼƺ�//
	unsigned long long ABCPowerPulSumAL;	//�����������������������ۼƺ�//������
	unsigned long long APowerPulSum;	//A���������������������ۼƺ�//
	unsigned long long BPowerPulSum;	//B���������������������ۼƺ�//
	unsigned long long CPowerPulSum;	//C���������������������ۼƺ�//
	
	unsigned long long ABCRPowerPulSum;	//�����������������������ۼƺ�//
	
	unsigned long long PhAPower; 	//A�๦��	�ӼĴ���������ֵ
	unsigned long long PhBPower;	//B�๦��	�ӼĴ���������ֵ
	unsigned long long PhCPower;	//C�๦��	�ӼĴ���������ֵ
	
	unsigned long ABCPower;	//ABC�๦������//
	unsigned long APowerPulP;	//A��������������ѳ���У����������������//
	unsigned long BPowerPulP;	//B��������������ѳ���У����������������//
	unsigned long CPowerPulP;	//C��������������ѳ���У����������������//
	unsigned long ABCPowerPulP;	//����������������ѳ���У����������������//
	unsigned long ABCPowerPulPAL;	//����������������ѳ���У����������������//

	unsigned long APowerPulPBak;	//A��������������ѳ���У�������������ϴ�����//
	unsigned long BPowerPulPBak;	//B��������������ѳ���У�������������ϴ�����//
	unsigned long CPowerPulPBak;	//C��������������ѳ���У�������������ϴ�����//
	
	unsigned long AnPowerPulPBak;	//A��������������ѳ���У�������������ϴ�����//
	unsigned long BnPowerPulPBak;	//B��������������ѳ���У�������������ϴ�����//
	unsigned long CnPowerPulPBak;	//C��������������ѳ���У�������������ϴ�����//

	unsigned long APowerPulN;	//A��������������ѳ���У�������ĸ�������//
	unsigned long BPowerPulN;	//B��������������ѳ���У�������ĸ�������//
	unsigned long CPowerPulN;	//C��������������ѳ���У�������ĸ�������//
	unsigned long ABCPowerPulN;	//����������������ѳ���У�������ĸ�������//

	unsigned long APowerPulNBak;	//A��������������ѳ���У�������ĸ����ϴ�����//
	unsigned long BPowerPulNBak;	//B��������������ѳ���У�������ĸ����ϴ�����//
	unsigned long CPowerPulNBak;	//C��������������ѳ���У�������ĸ����ϴ�����//

	unsigned long APowerPulPP;	//A��������������ѳ���У�����������������ж�����//
	unsigned long BPowerPulPP;	//B��������������ѳ���У�����������������ж�����//
	unsigned long CPowerPulPP;	//C��������������ѳ���У�����������������ж�����//
	
	unsigned char FlagDireABC;	//ABC����ķ���//
	unsigned char FlagDireABCn;	//ABC����ķ���//
	unsigned char ModePN;	//������ʽ//
	
	unsigned long ABCPowern;	//ABC�๦������//
	unsigned long APowerPulPn;	//A��������������ѳ���У����������������//
	unsigned long BPowerPulPn;	//B��������������ѳ���У����������������//
	unsigned long CPowerPulPn;	//C��������������ѳ���У����������������//
	unsigned long ABCPowerPulPn;	//����������������ѳ���У����������������//
	
	unsigned long APowerPulPPn;	//A��������������ѳ���У�����������������ж�����//
	unsigned long BPowerPulPPn;	//B��������������ѳ���У�����������������ж�����//
	unsigned long CPowerPulPPn;	//C��������������ѳ���У�����������������ж�����//
	
//	unsigned char APower[4];	//A�๦������//
//	unsigned char BPower[4];	//B�๦������//
//	unsigned char CPower[4];	//C�๦������//

	unsigned char AAdjust[2];	//A��У���������//
	unsigned char BAdjust[2];	//B��У���������//
	unsigned char CAdjust[2];	//C��У���������//
	
	unsigned char AdjustSum[2];	//У�����У���//
	
	unsigned char AStartM;
	unsigned char BStartM;
	unsigned char CStartM;
	
	unsigned char AReadErrCnt;//��8207����Ĵ����������ζ�����ʱ����оƬû�ϵ磬����������ֵ��0//
	unsigned char BReadErrCnt;
	unsigned char CReadErrCnt;
	              
	unsigned char AReadOKCnt;//��ʼ8207�Ĵ����������ζ�����ʱ����оƬ�ϵ磬����������ֵ//
	unsigned char BReadOKCnt;
	unsigned char CReadOKCnt;
                  
//  unsigned char AVolCnt;//�ж�ĳ��ʧѹ����15���������м����ߵ�//
//	unsigned char BVolCnt;
//	unsigned char CVolCnt;
                  
  	unsigned char MeaOneA;//�ж�ĳ��ʧѹ����15���������м����ߵ�//
	unsigned char MeaOneB;
	unsigned char MeaOneC;
	unsigned char PulWidth;			//������//
	unsigned char PulS0Width;			//������//
	unsigned char PhARPWRCnt;		//A�����������
	unsigned char PhBRPWRCnt;		//B�����������
	unsigned char PhCRPWRCnt;		//C�����������	
	unsigned char RPulWidth;			//������//	
}MEASURE8207;


typedef struct
{
	int flag;
	unsigned char PubKey_X[25];//������ԿX//
	unsigned char PubKey_Y[25];//������ԿY//
	unsigned char Pri_Key[25];//˽����Կ//
	char message[50];
	char hashmessage[50];
	char sign_rs[100];
//	unsigned int MSBNeedSendLg;//MSB��Ҫ���ͳ���//
//	unsigned char MSBTime;//MSBʱ��//
//	unsigned char Flag;//������־//
//	unsigned char	EndNum;
		
}SIGNATURE;
//˫�˵�Uartͨ��//
typedef struct
{
	unsigned char NeedRecCnt;			//��Ҫ���յ����ݳ���//
	unsigned char NeedSendCnt;		//��Ҫ���͵ĳ���//
	unsigned char RecBuf8213[32];	//���ջ�����//
	unsigned char SendBuf8213[32];	//���ͻ�����//
	unsigned char PhaType;			//���1=A�࣬2=B�࣬3=C��//
	unsigned char CommOk;			//ͨ����ɱ�־��0X55=ͨ�����//
	unsigned char Ptr8213;			//8207ͨ��ʱ��ָ��//
	unsigned short CommDly;			//ͨ�Ŷ�ʱ���������ʱ�����ͨ�ų���//
	unsigned char ReadPowerState;
	
}COMM8213;

 typedef struct
 {
	u16  DataID;		 //ID��
	unsigned char	 Logical_Name[6];
	unsigned char	 len;
 } ID_OBIS;
#endif







