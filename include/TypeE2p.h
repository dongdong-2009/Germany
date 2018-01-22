#include "TypeMeter.h"
//#define CMonItems	123		//��ǰ�µ���������������ʱ��������
//#define	CMonLength	574		//��ǰ�µ���������������ʱ���ܳ���

//����洢���б��浱ǰ���е�������һ������(ռǰ4ҳ 4*2*128 )
//�͵�ǰ�й����򡢵�ǰ�й����򡢵�ǰ���ڡ�һ����������������������������60���ӡ�120�ֽڣ����ޱ���(��4ҳ 4*2*128)
/***********************************************/


// ��һƬ24C64�д洢�����ݣ�������������

#if ( Threephase == YesCheck ) //����			
/*
//	Current Month EC Date
#define	CMon_EC_Pp0 		0x00				//��ǰ�ܵ���1.8.0
#define	CMon_EC_Pp1		CMon_EC_Pp0 + 7*1	  
#define	CMon_EC_Pp2		CMon_EC_Pp0 + 7*2
#define	CMon_EC_Pp3		CMon_EC_Pp0 + 7*3
#define	CMon_EC_Pp4		CMon_EC_Pp0 + 7*4 

#define	CMon_EC_PL1 		CMon_EC_Pp4 + 7					//��ǰ�ܵ���L1 ������� 21.8.0
#define	CMon_EC_PL2		CMon_EC_PL1 + 7*1				//��ǰ�ܵ���L2������� 41.8.0
#define	CMon_EC_PL3		CMon_EC_PL1 + 7*2 				//��ǰ�ܵ���L3������� 61.8.0
#define	CMon_EC_Pn0 		CMon_EC_PL1 + 7*3				//��ǰ�����ܵ���2.8.0
#define	CMon_EC_PL1R		CMon_EC_PL1 + 7*4	  			//��ǰ�ܵ���L1 ������� 22.8.0
#define	CMon_EC_PL2R		CMon_EC_PL1 + 7*5				//��ǰ�ܵ���L2������� 42.8.0
#define	CMon_EC_PL3R		CMon_EC_PL1 + 7*6 				//��ǰ�ܵ���L3������� 62.8.0
#define	CMon_EC_PpMa		CMon_EC_PL1 + 7*7 				//��ǰ�ܵ����ų�Ӱ�� 1.8.139

#define CMon_MD_Pp0		CMon_EC_PpMa + 7	//��ǰ������ // 15.6.0 	(4)
#define CMon_MD_Pp1		CMon_MD_Pp0 + 4*1	//��ǰ������ // 15.6.0
#define CMon_MD_Pp2		CMon_MD_Pp0 + 4*2	//��ǰ������ // 15.6.0
#define CMon_MD_Pp3		CMon_MD_Pp0 + 4*3	//��ǰ������ // 15.6.0
#define CMon_MD_Pp4		CMon_MD_Pp0 + 4*4	//��ǰ������ // 15.6.0
#define CMon_MD_Pn			CMon_MD_Pp0 + 4*5	//��ǰ������ // 2.6.0

#define CMon_MDT_Pp0		CMon_MD_Pn + 4			//��ǰ������ʱ��    (6)
#define CMon_MDT_Pp1		CMon_MDT_Pp0 + 6*1		//��ǰ������ʱ��
#define CMon_MDT_Pp2		CMon_MDT_Pp0 + 6*2		//��ǰ������ʱ��
#define CMon_MDT_Pp3		CMon_MDT_Pp0 + 6*3		//��ǰ������ʱ��
#define CMon_MDT_Pp4		CMon_MDT_Pp0 + 6*4		//��ǰ������ʱ��
#define CMon_MDT_Pn		CMon_MDT_Pp0 + 6*5		//��ǰ������ʱ��

//����������
#define ECBufPp_Ptr		CMon_MDT_Pn+6		//�й����򻺴�������ָ��(2) //0x86
#define ECBufPp1_Ptr		ECBufPp_Ptr + 2*1	//�й����򻺴�������ָ��(2)
#define ECBufPp2_Ptr		ECBufPp_Ptr + 2*2	//�й����򻺴�������ָ��(2)
#define ECBufPp3_Ptr		ECBufPp_Ptr + 2*3	//�й����򻺴�������ָ��(2)
#define ECBufPp4_Ptr		ECBufPp_Ptr + 2*4	//�й����򻺴�������ָ��(2)

#define ECBufPL1_Ptr		ECBufPp4_Ptr + 2	//�й����򻺴�������ָ��(2)
#define ECBufPL2_Ptr		ECBufPL1_Ptr + 2*1	//�й����򻺴�������ָ��(2)
#define ECBufPL3_Ptr		ECBufPL1_Ptr + 2*2	//�й����򻺴�������ָ��(2)
#define ECBufPn_Ptr		ECBufPL1_Ptr + 2*3	//�й����򻺴�������ָ��(2)
#define ECBufPL1R_Ptr	ECBufPL1_Ptr + 2*4	//�й����򻺴�������ָ��(2)
#define ECBufPL2R_Ptr	ECBufPL1_Ptr + 2*5	//�й����򻺴�������ָ��(2)
#define ECBufPL3R_Ptr	ECBufPL1_Ptr + 2*6	//�й����򻺴�������ָ��(2)
#define ECBufPpMa_Ptr	ECBufPL1_Ptr + 2*7	//�й����򻺴�������ָ��(2)


#define ECBufPp		ECBufPpMa_Ptr + 2		//�й����򻺴���(128)	//0x009E
#define ECBufPp1		ECBufPp + 128*1		//�й����򻺴���(128)
#define ECBufPp2    	ECBufPp + 128*2		//�й����򻺴���(128)
#define ECBufPp3		ECBufPp + 128*3		//�й����򻺴���(128)
#define ECBufPp4		ECBufPp + 128*4		//�й����򻺴���(128)

#define ECBufPL1		ECBufPp4 + 128		//�й����򻺴���(128)	
#define ECBufPL2    	ECBufPL1 + 128*1		//�й����򻺴���(128)
#define ECBufPL3		ECBufPL1 + 128*2		//�й����򻺴���(128)
#define ECBufPn		ECBufPL1 + 128*3		//�й����򻺴���(128)	
#define ECBufPL1R	ECBufPL1 + 128*4		//�й����򻺴���(128)
#define ECBufPL2R	ECBufPL1 + 128*5		//�й����򻺴���(128)
#define ECBufPL3R	ECBufPL1 + 128*6		//�й����򻺴���(128)
#define ECBufPpMa	ECBufPL1 + 128*7		//�й����򻺴���(128)
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~�����������ݴ��ⲿE��
#define	CMon_EC_Pp0 		0x00				//��ǰ�ܵ���15.8.0
#define	CMon_EC_Pp1		CMon_EC_Pp0 + 8*1	  
#define	CMon_EC_Pp2		CMon_EC_Pp0 + 8*2
#define	CMon_EC_Pp3		CMon_EC_Pp0 + 8*3
#define	CMon_EC_Pp4		CMon_EC_Pp0 + 8*4 
#define	CMon_EC_Pn0 	CMon_EC_Pp0 + 8*5 				//��ǰ�����ܵ���2.8.0

#define	CMon_EC_Pn1		CMon_EC_Pn0 + (8)*1
#define	CMon_EC_Pn2 	CMon_EC_Pn0 + (8)*2
#define	CMon_EC_Pn3		CMon_EC_Pn0 + (8)*3
#define	CMon_EC_Pn4 	CMon_EC_Pn0 + (8)*4

#define CMon_MD_Pp0		CMon_EC_Pp4 + 7		//��ǰ������ // 15.6.0 	(4)
#define CMon_MD_Pp1		CMon_MD_Pp0 + 4*1	//��ǰ������ // 15.6.0
#define CMon_MD_Pp2		CMon_MD_Pp0 + 4*2	//��ǰ������ // 15.6.0
#define CMon_MD_Pp3		CMon_MD_Pp0 + 4*3	//��ǰ������ // 15.6.0
#define CMon_MD_Pp4		CMon_MD_Pp0 + 4*4	//��ǰ������ // 15.6.0

#define CMon_MDT_Pp0		CMon_MD_Pp4 + 4			//��ǰ������ʱ��    (6)
#define CMon_MDT_Pp1		CMon_MDT_Pp0 + 6*1		//��ǰ������ʱ��
#define CMon_MDT_Pp2		CMon_MDT_Pp0 + 6*2		//��ǰ������ʱ��
#define CMon_MDT_Pp3		CMon_MDT_Pp0 + 6*3		//��ǰ������ʱ��
#define CMon_MDT_Pp4		CMon_MDT_Pp0 + 6*4		//��ǰ������ʱ��


#define ECBufPp_Ptr		CMon_MDT_Pp4+6		//�й����򻺴�������ָ��(2)
#define ECBufPp1_Ptr	ECBufPp_Ptr + 2*1	//�й����򻺴�������ָ��(2)
#define ECBufPp2_Ptr	ECBufPp_Ptr + 2*2	//�й����򻺴�������ָ��(2)
#define ECBufPp3_Ptr	ECBufPp_Ptr + 2*3	//�й����򻺴�������ָ��(2)
#define ECBufPp4_Ptr	ECBufPp_Ptr + 2*4	//�й����򻺴�������ָ��(2)
#define ECBufPn_Ptr	ECBufPp_Ptr + 2*5	//�й����򻺴�������ָ��(2)

#define ECBufPp		ECBufPp4_Ptr + 2		//�й����򻺴���(128)	//0x267
#define ECBufPp1		ECBufPp + 128*1		//�й����򻺴���(128)
#define ECBufPp2    	ECBufPp + 128*2		//�й����򻺴���(128)
#define ECBufPp3		ECBufPp + 128*3		//�й����򻺴���(128)
#define ECBufPp4		ECBufPp + 128*4		//�й����򻺴���(128)
#define ECBufPn		ECBufPp + 128*5		//�й����򻺴���(128)	

//-------------------------------------------------- 24C256 RN8213�ڲ�E��
#define ChooseSdb  		0x00			//�����л����ʻ��棨2��
#define TempClkAdd		ChooseSdb+2		//��������ʱ�� �޸�ʱ�仺�� ��8��
#define ManuJsHour		TempClkAdd+8 	//�ֶ�����ʱ�� ��4��
//#define ComplexSd1Name	ManuJsHour+4
//#define ComplexSd2Name	ComplexSd1Name+9
//#define ComplexSd3Name	ComplexSd2Name+9
#define SimpleSd1Name	ManuJsHour+9
#define SimpleSd2Name	SimpleSd1Name+9
#define SimpleSd3Name	SimpleSd2Name+9
#define SimpleSd4Name	SimpleSd3Name+9
#define SimpleSd5Name	SimpleSd4Name+9
#define SimpleSd6Name	SimpleSd5Name+9
#define	SimpleDaySdb1	SimpleSd6Name+9
#define	SimpleDaySdb2	SimpleDaySdb1+25*1
#define	SimpleDaySdb3	SimpleDaySdb1+25*2
#define	SimpleDaySdb4	SimpleDaySdb1+25*3
#define	SimpleDaySdb5	SimpleDaySdb1+25*4
#define	SimpleDaySdb6	SimpleDaySdb1+25*5

#define	ComplexSd1Name	SimpleDaySdb6+25
#define	IrreguHoli11	ComplexSd1Name+9
#define	IrreguHoli12	IrreguHoli11+21*1	
#define	IrreguHoli13	IrreguHoli11+21*2	
#define	IrreguHoli14	IrreguHoli11+21*3	
#define	IrreguHoli15	IrreguHoli11+21*4	
#define	IrreguHoli16	IrreguHoli11+21*5	
#define	IrreguHoli17	IrreguHoli11+21*6	
#define	IrreguHoli18	IrreguHoli11+21*7	
//#define	IrreguHoli19	IrreguHoli11+21*8
//#define	IrreguHoli110	IrreguHoli11+21*9
//#define	IrreguHoli111	IrreguHoli11+21*10
//#define	IrreguHoli112	IrreguHoli11+21*11
//#define	IrreguHoli113	IrreguHoli11+21*12
//#define	IrreguHoli114	IrreguHoli11+21*13
//#define	IrreguHoli115	IrreguHoli11+21*14
#define	ReguHoli1		IrreguHoli18+21	
#define	SeasonSdb1		ReguHoli1+31		
#define	WeekSdb11		SeasonSdb1+17
#define	WeekSdb12		WeekSdb11+8*1
#define	WeekSdb13		WeekSdb11+8*2
#define	WeekSdb14		WeekSdb11+8*3
#define	ComplDaySdb11	WeekSdb11+8*4
#define	ComplDaySdb12	ComplDaySdb11+25*1
#define	ComplDaySdb13	ComplDaySdb11+25*2
#define	ComplDaySdb14	ComplDaySdb11+25*3
#define	ComplDaySdb15	ComplDaySdb11+25*4
#define	ComplDaySdb16	ComplDaySdb11+25*5

//---------
#define	ComplexSd2Name	ComplDaySdb16+25
#define	IrreguHoli21	ComplexSd2Name+9
#define	IrreguHoli22	IrreguHoli21+21*1	
#define	IrreguHoli23	IrreguHoli21+21*2	
#define	IrreguHoli24	IrreguHoli21+21*3	
#define	IrreguHoli25	IrreguHoli21+21*4	
#define	IrreguHoli26	IrreguHoli21+21*5	
#define	IrreguHoli27	IrreguHoli21+21*6	
#define	IrreguHoli28	IrreguHoli21+21*7
//#define	IrreguHoli29	IrreguHoli21+21*8
//#define	IrreguHoli210	IrreguHoli21+21*9
//#define	IrreguHoli211	IrreguHoli21+21*10
//#define	IrreguHoli212	IrreguHoli21+21*11
//#define	IrreguHoli213	IrreguHoli21+21*12
//#define	IrreguHoli214	IrreguHoli21+21*13
//#define	IrreguHoli215	IrreguHoli21+21*14	
#define	ReguHoli2		IrreguHoli28+21	
#define	SeasonSdb2		ReguHoli2+31		
#define	WeekSdb21		SeasonSdb2+17
#define	WeekSdb22		WeekSdb21+8*1
#define	WeekSdb23		WeekSdb21+8*2
#define	WeekSdb24		WeekSdb21+8*3
#define	ComplDaySdb21	WeekSdb21+8*4
#define	ComplDaySdb22	ComplDaySdb21+25*1
#define	ComplDaySdb23	ComplDaySdb21+25*2
#define	ComplDaySdb24	ComplDaySdb21+25*3
#define	ComplDaySdb25	ComplDaySdb21+25*4
#define	ComplDaySdb26	ComplDaySdb21+25*5
//---------
#define	ComplexSd3Name	ComplDaySdb26+25
#define	IrreguHoli31	ComplexSd3Name+9
#define	IrreguHoli32	IrreguHoli31+21*1	
#define	IrreguHoli33	IrreguHoli31+21*2	
#define	IrreguHoli34	IrreguHoli31+21*3	
#define	IrreguHoli35	IrreguHoli31+21*4	
#define	IrreguHoli36	IrreguHoli31+21*5	
#define	IrreguHoli37	IrreguHoli31+21*6	
#define	IrreguHoli38	IrreguHoli31+21*7
//#define	IrreguHoli39	IrreguHoli31+21*8
//#define	IrreguHoli310	IrreguHoli31+21*9
//#define	IrreguHoli311	IrreguHoli31+21*10
//#define	IrreguHoli312	IrreguHoli31+21*11
//#define	IrreguHoli313	IrreguHoli31+21*12	
//#define	IrreguHoli314	IrreguHoli31+21*13
//#define	IrreguHoli315	IrreguHoli31+21*14
#define	ReguHoli3		IrreguHoli38+21	
#define	SeasonSdb3		ReguHoli3+31		
#define	WeekSdb31		SeasonSdb3+17
#define	WeekSdb32		WeekSdb31+8*1
#define	WeekSdb33		WeekSdb31+8*2
#define	WeekSdb34		WeekSdb31+8*3
#define	ComplDaySdb31	WeekSdb31+8*4
#define	ComplDaySdb32	ComplDaySdb31+25*1
#define	ComplDaySdb33	ComplDaySdb31+25*2
#define	ComplDaySdb34	ComplDaySdb31+25*3
#define	ComplDaySdb35	ComplDaySdb31+25*4
#define	ComplDaySdb36	ComplDaySdb31+25*5

#define	CurrRunSdName	ComplDaySdb36+25
#define	Lxcsadd1		CurrRunSdName+9	
#define	Lxcsadd2		Lxcsadd1+ 5*1
#define	Lxcsadd3		Lxcsadd1+ 5*2  
#define	Lxcsadd4		Lxcsadd1+ 5*3                                   
#define	Lxcsadd5		Lxcsadd1+ 5*4                                   
#define	Lxcsadd6		Lxcsadd1+ 5*5                                   
#define	Lxcsadd7		Lxcsadd1+ 5*6                                   
#define	Lxcsadd8		Lxcsadd1+ 5*7                                   
#define	Lxcsadd9		Lxcsadd1+ 5*8   
                                
#define	SumWinSwitch		Lxcsadd1+ 5*9
#define	MagFlag			SumWinSwitch+2		//(2)
#define	KGFlag        		MagFlag+2			//(2)
#define	KDFlag			KGFlag+2			//(2)
#define	ReverseFlag		KDFlag+2		//(2)

#define	LastJsr			ReverseFlag+2	//(4)
#define	LastSdName		LastJsr+4				//(9)
#define	RtcShiftYear		LastSdName+9		//(4)

#define	Password0		RtcShiftYear+4	//����0(5)
//#define	Password1		Password0+5*1			//����1(5)
//#define	Password2		Password0+5*2			//����2(5)
//#define	Password3		Password0+5*3			//����3(5)
//
//#define	ClkBuf1			Password0+5				//ʱ�仺����1(7)
//#define	ClkBuf2			ClkBuf1+7*1				//ʱ�仺����2(7)
//#define	ClkBuf3			ClkBuf1+7*2				//ʱ�仺����3(7)
//#define	ClkBuf4			ClkBuf1+7*3				//ʱ�仺����4(7)
//#define	ClkBuf5			ClkBuf1+7*4				//ʱ�仺����4(7)
//#define	ClkBuf6			ClkBuf1+7*5				//ʱ�仺����4(7)
//#define	ClkBuf7			ClkBuf1+7*6				//ʱ�仺����4(7)
//#define	ClkBuf8			ClkBuf1+7*7				//ʱ�仺����4(7)

//174+1220+30+61

//#define	ECrys_Offs		Password0+5				//Ƶ�ʵ�У����(3)ppmֵ
//#define	EDx_Valve		ECrys_Offs+3			//���෧ֵ��ѹ����(4)
//#define	ECMode			ECrys_Offs+3			//���������ۼ�ģʽ(2) 0:��������ӡ�1:����ֵ���

#define LoadCtrlByte	Password0+9//ECrys_Offs+3				//���ɼ�¼������(2)
#define LoadRecState	LoadCtrlByte+2			//��ǰ���ɼ�¼״̬(6)
//#define TamperRecState	LoadRecState+6			//��ǰ�¼���¼״̬(4)

#define	EMeter_No	LoadRecState+6				//����(21)
#define	PCB_No		EMeter_No+21				//pcb��(13)
#define	Serial_No	PCB_No+13					//���к�(21)
//#define	EDev_Ads		EUser_No+7				//�豸��(7)
//#define	Meter_PConst	EUser_No+7				//����й�����(4)
//#define	Meter_QConst	Meter_PConst+4			//����޹�����(4)
//#define	EMaxT			Meter_PConst+4			//��������(2)
//#define	EMaxDT			EMaxT+2					//����ʱ��(2)
//#define 	AmPOver_Valve 	EMaxDT+2				//������ֵ(3)
//#define	EVA_Valve		EMaxDT+2			//��ѹ\������ֵBCD�룬���ֽ���ǰ����ѹ��ǰ   (5)
#define	ESave_Day		Serial_No+21				//������(4)
//#define	Special_Day		ESave_Day+4				//������(2)		
#define	EDspInv			ESave_Day+4//Special_Day+2			//��ʾ���(2)
//#define EDisHours		EDspInv+2				//ͣ�����ʾСʱ��(3) 9999�����ر�
//#define EDisDays		EDspInv+2				//ͣ�����ʾ����(2) 
//#define EBatComHours	EDisDays+2				//ͣ���ͣ�����ά��Сʱ��(3) 
//#define EAddress		EDisHours+3				//��ַ(2)
////#define EBandRateMode	EDisDays+2				//�����ʸı�ģʽ(2) 0������ 1������Ӧ
////#define	Meter_Ident		EBandRateMode+2			//�������ʶ���(2)
////#define	EVolt_Valve		Meter_Ident+2			//��ѹ��ֵ����(2)
////#define Dis_Off_Time	EVolt_Valve+2			//ͣ��ʱ��(5) 
////#define AutoDisMode		Dis_Off_Time+5			//�Զ�����ģʽ(2)
////#define EZJAddress		AutoDisMode+2			//����ַ(2)
//#define EAwakeDisDays	EZJAddress+2			//ͣ�绽��֧��ʱ��(2)	16����	//V30


//#define	ETu				EAwakeDisDays+2				//����״̬�ȶ�ʱ��(2)
//#define	EUe				ETu+2					//��ѹ��ֵ(3)
//#define EIx				EUe+3					//���������ֵ(3)

#define DisSwitch		EDspInv+2					//��ʾ����(3)
//#define	EPJLmode		DisSwitch+3				//�й����������ģʽ(3) 
												//�ڶ��ֽ� 0��ֻ���й����򣬷��򲻼�
												//1:�й�������ϼƣ����򲻼�
												//2:�й�ֻ�����򣬷����¼
												//3:�й�������ϼƣ������¼
#define Alarm_Control	DisSwitch+3				//����������(3)
//#define LabPrgTime		Alarm_Control+3			//ʵ���Ҽ���̿�����Чʱ��(7)												
//#define PrgPurview		LabPrgTime+7			//���Ȩ��(3)
//#define ECClrMode		PrgPurview+3			//��������ģʽ(2)
#define DisDigitNum		Alarm_Control+3				//С��λ��(2)

//#define ECClrCount	DisDigitNum+2			//�����������(2)
//#define Pre1Prg_Data	ECClrCount+2			//�����һ�α��ʱ���¼(8)
//#define Pre2Prg_Data	Pre1Prg_Data+8*1		//����ڶ��α��ʱ���¼(8)
//#define Pre3Prg_Data	Pre1Prg_Data+8*2		//��������α��ʱ���¼(8)

//#define LastPrgTime6	Pre3Prg_Data+8			//���һ�α��ʱ��(7)

//#define RunOverStartTime	LastPrgTime6+7		//������ʼʱ��(6)
//#define RunOverSumTime		RunOverStartTime+6	//�����ۼ�ʱ��(4)

//174+1220+30+61+63+74

//#define	MD_Reset_CT		RunOverSumTime+4		//������λ����(3)
//#define	Prg_Count		MD_Reset_CT+3			//��̴���(3)
//#define	Pdown_CT		Prg_Count+3				//�µ����(3)
#define LastEC_Pt				DisDigitNum+2			//��ǰ��ʷ������¼��ַָ��(3)
#define	Last_Mon_Tm				LastEC_Pt+3				//���½���ʱ��(3)
#define GeneralLoadCurAddr 		Last_Mon_Tm+3			//��ͨ�������ߵ�ǰ��¼�׵�ַ(5)
#define GeneralMonCurAddr 		GeneralLoadCurAddr+5	//��ʷ���ݵ�ǰ��¼�׵�ַ(5)
#define GeneralTamperCurAddr 	GeneralLoadCurAddr+5*2	//�¼���¼��ǰ��¼�׵�ַ(5)
#define	EMeter_No_Bit			GeneralTamperCurAddr+5	//д����ʹ��(2)
#define	Serial_No_Bit			EMeter_No_Bit+2			//д���к�ʹ��(2)
#define	CE_Clr_Bit				EMeter_No_Bit+2*2		//��������ʹ��(2)
#define	Meter_type_Bit			EMeter_No_Bit+2*3		//�����ͺ���ʹ��(2)

#define	User_ID					Meter_type_Bit+2			//�û�ID��9��
#define	Opencover_Time		User_ID+9				//��6��
#define	OpenTcover_Time		Opencover_Time+6				//��6��
#define	PRGRMByte		OpenTcover_Time+6				//��2��
#define	ParameterDataStata		PRGRMByte+2				//��2��
#define	NewTariffDataStata		PRGRMByte+2*2			//��2��

//#define	ClockAdj		PRGRMByte+2*3				//��2��

#define	MeterRestCnt		NewTariffDataStata+2				//��3��
#define	PhaseL1Cnt		MeterRestCnt+3				//��3��
#define	PhaseL2Cnt		MeterRestCnt+3*2				//��3��
#define	PhaseL3Cnt		MeterRestCnt+3*3				//��3��
#define	OpenTCoverCnt		MeterRestCnt+3*4			//��3��
#define	OpenCoverCnt		MeterRestCnt+3*5				//��3��
#define	MagneticONCnt		MeterRestCnt+3*6				//��3��
#define	E2P_PSet_Cnt		MeterRestCnt+3*7				//��3��

#define	FristOTCover_Time	E2P_PSet_Cnt+3				//��7��
#define	FristOCover_Time	FristOTCover_Time+7				//��7��
#define	FristMagnetic_Time	FristOCover_Time+7				//��7��
#define 	ESetparaTime		FristMagnetic_Time+7	//��������ʱ��(7)	

#define MD_Over_Valve	ESetparaTime + 7		//(4)
#define Lcdvoltage		MD_Over_Valve + 4		//(2)0x09CD

#define	JsCount					Lcdvoltage+2			//�������(3)

#define EDisplayA1		JsCount + 3		//(31)
#define EDisplayA2		EDisplayA1 + 31		//(31)
#define EDisplayA3		EDisplayA2 + 31		//(31)
#define EDisplayM1		EDisplayA3 + 31		//(31)
#define EDisplayM2		EDisplayM1 + 31		//(31)
#define EDisplayM3		EDisplayM2 + 31		//(31)

#define	LcdAutime					EDisplayM3+31			//����ʱ��(2) 	�����ַ0x0A8E

#define	LoadLOADC					LcdAutime+2			//���ɼ�¼��Ŀ״̬��(4) 
#define	LoadLOADE					LoadLOADC+4			//���ɼ�¼ʹ��״̬��(2) 00ʹ��01�ر�
#define	DisHistNum					LoadLOADE+4			//��ʷ��ʾ����(2)

//#define	NewTariffDataStata		PRGRMByte+2*2				//��2��

//#define ECOperationlTime		DisHistNum +2			//T����ʱ��(6)
//#define T1OperationlTime		ECOperationlTime + 6		//T1����ʱ��(6)
//#define T2OperationlTime		T1OperationlTime + 6		//T2����ʱ��(6)
//#define REVOperationlTime	T2OperationlTime + 6		//T��������ʱ��(6)

#define T1OperationlTime		DisHistNum + 2			//T1����ʱ��(6)
#define T2OperationlTime		T1OperationlTime + 6		//T2����ʱ��(6)
#define T3OperationlTime		T2OperationlTime + 6		//T3����ʱ��(6)
#define T4OperationlTime		T3OperationlTime + 6		//T4����ʱ��(6)

#define ECOperationlTime		T4OperationlTime + 6		//T����ʱ��(6)
#define REVOperationlTime	ECOperationlTime + 6		//T��������ʱ��(6)
#define MagnetOperationlTime	REVOperationlTime + 6		//�ų�����ʱ��(6)

#define PAFailCnt		MagnetOperationlTime + 6			//L1ʧѹ����(5)
#define PBFailCnt		PAFailCnt + 5*1				//L2ʧѹ����(5)
#define PCFailCnt		PAFailCnt + 5*2				//L3ʧѹ����(5)
#define OpCoverCnt		PAFailCnt + 5*3				//���Ǵ���(5)
#define OpTCoverCnt		PAFailCnt + 5*4				//���˴���(5)
#define ReverseCnt		PAFailCnt + 5*5				//�������(5)

#define MOnCnt		ReverseCnt + 5				//�ų����Ŵ���(6)

#define LastPTime		MOnCnt + 6				//���һ�α��ʱ��(6)
#define LastRTime		LastPTime + 6				//���һ�ζ�����ʱ��(6)
#define LastRTCTime		LastRTime + 6				//���һ��ʱ������ʱ��(6)
#define BatteryWorkTime	LastRTCTime+6			//(6)��ع���ʱ��

#define TamperRecState	BatteryWorkTime+6			//��ǰ�¼���¼״̬(4)
#define TamperRecState1	TamperRecState+4			//��ǰ�¼���¼״̬(4)
#define TamperRecState2	TamperRecState1+4			//��ǰ�¼���¼״̬(4)
#define TamperRecState3	TamperRecState2+4			//��ǰ�¼���¼״̬(4)
#define TamperRecState4	TamperRecState3+4			//��ǰ�¼���¼״̬(4)
#define TamperRecState5	TamperRecState4+4			//��ǰ�¼���¼״̬(4)

#define Metertype_No	TamperRecState5+4					//�����ͺ���(7)
#define Constantled 	Metertype_No + 7				//LED���峣��(5)
#define Constants0	Constantled + 5				//S0���峣��(5)
#define Tariffsnumber  Constants0 + 5				//������2˫���ʡ�1������(2)	 //14.2.9wwl
#define TamperSwitch  Tariffsnumber + 2				//(2)

#define Eventdelay		TamperSwitch+2			//�¼���¼���ʱ��(2)

#define PAFailCntMon		Eventdelay + 2					//L1ʧѹ����(5)
#define PBFailCntMon		PAFailCntMon + 5*1				//L2ʧѹ����(5)
#define PCFailCntMon		PAFailCntMon + 5*2				//L3ʧѹ����(5)

#define CRCCheck  PCFailCntMon + 5				//����CRC ֵ(3)
#if 0
#define Widthimpulse  CRCCheck + 3				//������ms(2)   //14.2.9wwl
#define ECMode	Widthimpulse + 2				//������ʽ0 ������ 1����ֵ(2)  //13.3.6wwl
#define LedMode  ECMode + 2				//Led �������ģʽ 01:�޸���ʱ����; 00���������淽ʽ(2)	 //14.2.19wwl
#define MDT_Pp0  LedMode + 2				//���һ������ʱ��(6)
#define JOINTTYPE  MDT_Pp0 + 6				//������������(2) 00 ר��01 ����
#else
#define Server_BABID	CRCCheck+3 
#endif

#define	Server_ID			Server_BABID+12		//(11)�豸��
#define	PublicKey_X		Server_ID+14				//(25)
#define	PublicKey_Y		PublicKey_X+25				//(25)
#define	Private_Key		PublicKey_Y+65				//(25)
#define	Magnetic_Bit		Private_Key+34				//�ų����(2)

#define	DisPINAdd			Magnetic_Bit+2				//��4��
#define	DisHisAdd			DisPINAdd+4				//��2��
#define	DisPINEnAdd		DisHisAdd+2				//��2��
#define	ActivTariffXAdd		DisPINEnAdd+2				//��2��

#define	E2P_INF0							ActivTariffXAdd+2				//��2��
#define	E2P_ModeEDL40					E2P_INF0+2				//��2��
#define	E2P_ResHistorical			E2P_ModeEDL40+2				//��2��
#define	E2P_DisHistorical			E2P_ResHistorical+2			//��2��
#define	E2P_ProtectionPINCode	E2P_DisHistorical+2			//��2��
#define	E2P_SetMSB						E2P_ProtectionPINCode+2			//��2��
#define	E2P_OResHisButton			E2P_SetMSB+2				//��2��
#define	E2P_DisPINCode				E2P_OResHisButton+2			//��2��
#define	E2P_DisPActive				E2P_OResHisButton+4			//��2��
#define	E2P_HisDAY1						E2P_DisPActive+3			//��6��
#define	E2P_HisDAY7						E2P_HisDAY1+8				//��6��
#define	E2P_HisDAY30					E2P_HisDAY7+8				//��6��
#define	E2P_HisDAY365					E2P_HisDAY30+8				//��6��
#define	E2P_LastReset					E2P_HisDAY365+8				//��6��
#define	E2P_SMLTime						E2P_LastReset+8				//��6��
#define	E2P_ConManipulation		E2P_SMLTime+6				//��5��
#define	E2P_DisTariff					E2P_ConManipulation+5			//��5��
#define	E2P_ChangeTariff			E2P_DisTariff+5				//��2��
#define	E2P_SATEWORD					E2P_ChangeTariff+2			//��4��
#define	Last_EC_Pp0						E2P_SATEWORD+4				//��9��
#define	E2P_NumSwitchProgramm	Last_EC_Pp0+9				//��7��
#define	E2P_TextAusgabe				E2P_NumSwitchProgramm+7			//��10��
#define	E2P_DisDataSetFlag		E2P_TextAusgabe+10			//��1��
#define E2P_ManiDetectFlag    E2P_DisDataSetFlag+1     // 1
#define E2P_DeviceClass				E2P_ManiDetectFlag+1     //6
#define E2P_Mechanical				E2P_DeviceClass+6       //1
#define E2P_FirmwareVer				E2P_DeviceClass+1       //6
#define E2P_FirmWareCheck     E2P_FirmwareVer+7    //3
#define E2P_HardwareVer				E2P_FirmWareCheck+3   //6
#define	E2P_PrivateKey				E2P_HardwareVer+6   //32
#define E2P_SymmetricalKey    E2P_PrivateKey+68   //16
#define E2P_ResetCrypoto   		E2P_SymmetricalKey+18   //1
#define E2P_OrderPlusA  			E2P_ResetCrypoto+2   //1
#define E2P_OrderDecA  				E2P_OrderPlusA+2   //1
#define E2P_MaxFragLen				E2P_OrderDecA+2   //2
#define E2P_Manufactor_ID     E2P_OrderDecA+4  //10
#define E2P_Director     			E2P_Manufactor_ID+16 // 1
#define E2P_Default_Mkey     	E2P_Director+4 		// 16
#define E2P_Default_PKey     	E2P_Default_Mkey+32 		// 32
#define E2P_LMN_Certi					E2P_Default_PKey+0x44 //E2P_MaxFragLen+4   //528
#define E2P_SMGW_Certi				E2P_LMN_Certi+530




//#define PowerDownSave		LedMode + 6			//�µ�˲��Ҫ���������(13)//St0x0B05
//#define PowerDownSave		MDT_Pp0 + 6			//�µ�˲��Ҫ���������(13)//St0x0B05

#define PowerDownSave			0x1000			//�µ�˲��Ҫ���������(13)//St0x0B05
#define PowerDownSave1		PowerDownSave + 64			//�µ�˲��Ҫ���������(13)//St0x0B05

#define	CalibrationRecord		0x1FC0				//�ڲ�E��У���������
 
#define E2P_PGLEN		0x0B00      //0xAAA//0x1554		//���ݱ���ҳ����


#define E2P_PGLENRN8213	0x2000//0xAAA//0x1554		//�ڲ�E�����ݱ���ҳ����
#define	LoadRecord_Time		0x6000//0x1554 //��̲���������
					
#else
/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~�����������ݴ��ⲿE��
#define	CMon_EC_Pp0 		0x00				//��ǰ�ܵ���15.8.0
#define	CMon_EC_Pp1		CMon_EC_Pp0 + 7*1	  
#define	CMon_EC_Pp2		CMon_EC_Pp0 + 7*2
#define	CMon_EC_Pp3		CMon_EC_Pp0 + 7*3
#define	CMon_EC_Pp4		CMon_EC_Pp0 + 7*4 
#define	CMon_EC_Pn0 		CMon_EC_Pp0 + 7*5 
//#define	CMon_EC_PpMa		CMon_EC_Pp0 + 7*5 				//��ǰ�ܵ����ų�Ӱ�� 1.8.139

#define CMon_MD_Pp0		CMon_EC_Pn0 + 7		//��ǰ������ // 15.6.0 	(4)
#define CMon_MD_Pp1		CMon_MD_Pp0 + 4*1	//��ǰ������ // 15.6.0
#define CMon_MD_Pp2		CMon_MD_Pp0 + 4*2	//��ǰ������ // 15.6.0
#define CMon_MD_Pp3		CMon_MD_Pp0 + 4*3	//��ǰ������ // 15.6.0
#define CMon_MD_Pp4		CMon_MD_Pp0 + 4*4	//��ǰ������ // 15.6.0
#define CMon_MD_Pn			CMon_MD_Pp0 + 4*5	//��ǰ������ // 2.6.0

#define CMon_MDT_Pp0		CMon_MD_Pn + 4			//��ǰ������ʱ��    (6)
#define CMon_MDT_Pp1		CMon_MDT_Pp0 + 6*1		//��ǰ������ʱ��
#define CMon_MDT_Pp2		CMon_MDT_Pp0 + 6*2		//��ǰ������ʱ��
#define CMon_MDT_Pp3		CMon_MDT_Pp0 + 6*3		//��ǰ������ʱ��
#define CMon_MDT_Pp4		CMon_MDT_Pp0 + 6*4		//��ǰ������ʱ��
#define CMon_MDT_Pn		CMon_MDT_Pp0 + 6*5		//��ǰ������ʱ��


#define ECBufPp_Ptr		CMon_MDT_Pn+6		//�й����򻺴�������ָ��(2)
#define ECBufPp1_Ptr		ECBufPp_Ptr + 2*1	//�й����򻺴�������ָ��(2)
#define ECBufPp2_Ptr		ECBufPp_Ptr + 2*2	//�й����򻺴�������ָ��(2)
#define ECBufPp3_Ptr		ECBufPp_Ptr + 2*3	//�й����򻺴�������ָ��(2)
#define ECBufPp4_Ptr		ECBufPp_Ptr + 2*4	//�й����򻺴�������ָ��(2)
#define ECBufPn_Ptr		ECBufPp_Ptr + 2*5	//�й����򻺴�������ָ��(2)
//#define ECBufPpMa_Ptr	ECBufPp_Ptr + 2*5	//�й����򻺴�������ָ��(2)

#define ECBufPp		ECBufPn_Ptr + 2		//�й����򻺴���(128)	//0x267
#define ECBufPp1		ECBufPp + 128*1		//�й����򻺴���(128)
#define ECBufPp2    	ECBufPp + 128*2		//�й����򻺴���(128)
#define ECBufPp3		ECBufPp + 128*3		//�й����򻺴���(128)
#define ECBufPp4		ECBufPp + 128*4		//�й����򻺴���(128)
#define ECBufPn		ECBufPp + 128*5			//�й����򻺴���(128)	//������ַ:0x0368
//#define ECBufPpMa	ECBufPp + 128*5		//�й����򻺴���(128)
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~�����������ݴ��ⲿE��
#define	CMon_EC_Pp0 		0x00				//��ǰ�ܵ���15.8.0
#define	CMon_EC_Pp1		CMon_EC_Pp0 + 7*1	  
#define	CMon_EC_Pp2		CMon_EC_Pp0 + 7*2
#define	CMon_EC_Pp3		CMon_EC_Pp0 + 7*3
#define	CMon_EC_Pp4		CMon_EC_Pp0 + 7*4 
#define	CMon_EC_Pn0 		CMon_EC_Pp0 + 7*5 				//��ǰ�����ܵ���2.8.0

#define CMon_MD_Pp0		CMon_EC_Pp4 + 7		//��ǰ������ // 15.6.0 	(4)
#define CMon_MD_Pp1		CMon_MD_Pp0 + 4*1	//��ǰ������ // 15.6.0
#define CMon_MD_Pp2		CMon_MD_Pp0 + 4*2	//��ǰ������ // 15.6.0
#define CMon_MD_Pp3		CMon_MD_Pp0 + 4*3	//��ǰ������ // 15.6.0
#define CMon_MD_Pp4		CMon_MD_Pp0 + 4*4	//��ǰ������ // 15.6.0

#define CMon_MDT_Pp0		CMon_MD_Pp4 + 4			//��ǰ������ʱ��    (6)
#define CMon_MDT_Pp1		CMon_MDT_Pp0 + 6*1		//��ǰ������ʱ��
#define CMon_MDT_Pp2		CMon_MDT_Pp0 + 6*2		//��ǰ������ʱ��
#define CMon_MDT_Pp3		CMon_MDT_Pp0 + 6*3		//��ǰ������ʱ��
#define CMon_MDT_Pp4		CMon_MDT_Pp0 + 6*4		//��ǰ������ʱ��


#define ECBufPp_Ptr		CMon_MDT_Pp4+6		//�й����򻺴�������ָ��(2)
#define ECBufPp1_Ptr	ECBufPp_Ptr + 2*1	//�й����򻺴�������ָ��(2)
#define ECBufPp2_Ptr	ECBufPp_Ptr + 2*2	//�й����򻺴�������ָ��(2)
#define ECBufPp3_Ptr	ECBufPp_Ptr + 2*3	//�й����򻺴�������ָ��(2)
#define ECBufPp4_Ptr	ECBufPp_Ptr + 2*4	//�й����򻺴�������ָ��(2)
#define ECBufPn_Ptr	ECBufPp_Ptr + 2*5	//�й����򻺴�������ָ��(2)

#define ECBufPp		ECBufPp4_Ptr + 2		//�й����򻺴���(128)	//0x267
#define ECBufPp1		ECBufPp + 128*1		//�й����򻺴���(128)
#define ECBufPp2    	ECBufPp + 128*2		//�й����򻺴���(128)
#define ECBufPp3		ECBufPp + 128*3		//�й����򻺴���(128)
#define ECBufPp4		ECBufPp + 128*4		//�й����򻺴���(128)
#define ECBufPn		ECBufPp + 128*5		//�й����򻺴���(128)	

/*
#define	CMon_EC_Pp0 		0x00				//��ǰ�ܵ���15.8.0
#define	CMon_EC_Pp1		CMon_EC_Pp0 + 7*1	  
#define	CMon_EC_Pp2		CMon_EC_Pp0 + 7*2
#define	CMon_EC_Pp3		CMon_EC_Pp0 + 7*3
//#define	CMon_EC_Pp4		CMon_EC_Pp0 + 7*4 
#define	CMon_EC_Pn0 		CMon_EC_Pp0 + 7*4 
#define	CMon_EC_PpMa		CMon_EC_Pp0 + 7*5 				//��ǰ�ܵ����ų�Ӱ�� 1.8.139

#define CMon_MD_Pp0		CMon_EC_PpMa + 7		//��ǰ������ // 15.6.0 	(4)
#define CMon_MD_Pp1		CMon_MD_Pp0 + 4*1	//��ǰ������ // 15.6.0
#define CMon_MD_Pp2		CMon_MD_Pp0 + 4*2	//��ǰ������ // 15.6.0
#define CMon_MD_Pp3		CMon_MD_Pp0 + 4*3	//��ǰ������ // 15.6.0
#define CMon_MD_Pp4		CMon_MD_Pp0 + 4*4	//��ǰ������ // 15.6.0
#define CMon_MD_Pn			CMon_MD_Pp0 + 4*5	//��ǰ������ // 2.6.0

#define CMon_MDT_Pp0		CMon_MD_Pn + 4			//��ǰ������ʱ��    (6)
#define CMon_MDT_Pp1		CMon_MDT_Pp0 + 6*1		//��ǰ������ʱ��
#define CMon_MDT_Pp2		CMon_MDT_Pp0 + 6*2		//��ǰ������ʱ��
#define CMon_MDT_Pp3		CMon_MDT_Pp0 + 6*3		//��ǰ������ʱ��
#define CMon_MDT_Pp4		CMon_MDT_Pp0 + 6*4		//��ǰ������ʱ��
#define CMon_MDT_Pn		CMon_MDT_Pp0 + 6*5		//��ǰ������ʱ��


#define ECBufPp_Ptr		CMon_MDT_Pn+6		//�й����򻺴�������ָ��(2)
#define ECBufPp1_Ptr		ECBufPp_Ptr + 2*1	//�й����򻺴�������ָ��(2)
#define ECBufPp2_Ptr		ECBufPp_Ptr + 2*2	//�й����򻺴�������ָ��(2)
#define ECBufPp3_Ptr		ECBufPp_Ptr + 2*3	//�й����򻺴�������ָ��(2)
//#define ECBufPp4_Ptr		ECBufPp_Ptr + 2*4	//�й����򻺴�������ָ��(2)
#define ECBufPn_Ptr		ECBufPp_Ptr + 2*4	//�й����򻺴�������ָ��(2)
#define ECBufPpMa_Ptr	ECBufPp_Ptr + 2*5	//�й����򻺴�������ָ��(2)

#define ECBufPp		ECBufPpMa_Ptr + 2		//�й����򻺴���(128)	//0x267
#define ECBufPp1		ECBufPp + 128*1		//�й����򻺴���(128)
#define ECBufPp2    	ECBufPp + 128*2		//�й����򻺴���(128)
#define ECBufPp3		ECBufPp + 128*3		//�й����򻺴���(128)
//#define ECBufPp4		ECBufPp + 128*4		//�й����򻺴���(128)
#define ECBufPn		ECBufPp + 128*4			//�й����򻺴���(128)	//������ַ:0x0368
#define ECBufPpMa	ECBufPp + 128*5		//�й����򻺴���(128)
*/

//����������
//#define MDBuf_Pp	ECBufPn + 128

//#define EE_CAL_IA			 ECBufPn+128			//IA(3)
#define EE_CAL_IA			 0x3D0			//IA(3)
#define EE_CAL_IB			 EE_CAL_IA+3		//IB(3)
#define EE_CAL_PA			 EE_CAL_IA+3*2		//PA(3)
#define EE_CAL_PB			 EE_CAL_IA+3*3		//PB(3)
#define EE_CAL_V			 EE_CAL_IA+3*4		//V(3)

#define EE_PHADJ_A			 EE_CAL_IA+3*5		//A����λ(3)
#define EE_PHADJ_B			 EE_CAL_IA+3*6		//B����λ(3)
#define EE_Offset_A			 EE_CAL_IA+3*7		//A��Offset(3)
#define EE_Offset_B			 EE_CAL_IA+3*8		//B��Offset(3)

#define EMUStatusJY			 EE_Offset_B+3		//У���(5)  //������ַ:0x0388

#define	ClockAdj		EMUStatusJY+5				//��2��//������ַ:0x038A


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~�����������֣���RN8213�ڲ�E��


#define ChooseSdb  		0x00
#define TempClkAdd		ChooseSdb+2	//��ʱ���ʱ�� 8
#define ManuJsHour		TempClkAdd+8 	//�ֶ�����ʱ�� 4
//#define ComplexSd1Name	ManuJsHour+4
//#define ComplexSd2Name	ComplexSd1Name+9
//#define ComplexSd3Name	ComplexSd2Name+9
#define SimpleSd1Name	ManuJsHour+9
#define SimpleSd2Name	SimpleSd1Name+9
#define SimpleSd3Name	SimpleSd2Name+9
#define SimpleSd4Name	SimpleSd3Name+9
#define SimpleSd5Name	SimpleSd4Name+9
#define SimpleSd6Name	SimpleSd5Name+9
#define	SimpleDaySdb1	SimpleSd6Name+9
#define	SimpleDaySdb2	SimpleDaySdb1+25*1
#define	SimpleDaySdb3	SimpleDaySdb1+25*2
#define	SimpleDaySdb4	SimpleDaySdb1+25*3
#define	SimpleDaySdb5	SimpleDaySdb1+25*4
#define	SimpleDaySdb6	SimpleDaySdb1+25*5

#define	ComplexSd1Name	SimpleDaySdb6+25
#define	IrreguHoli11	ComplexSd1Name+9
#define	IrreguHoli12	IrreguHoli11+21*1	
#define	IrreguHoli13	IrreguHoli11+21*2	
#define	IrreguHoli14	IrreguHoli11+21*3	
#define	IrreguHoli15	IrreguHoli11+21*4	
#define	IrreguHoli16	IrreguHoli11+21*5	
#define	IrreguHoli17	IrreguHoli11+21*6	
#define	IrreguHoli18	IrreguHoli11+21*7	
//#define	IrreguHoli19	IrreguHoli11+21*8
//#define	IrreguHoli110	IrreguHoli11+21*9
//#define	IrreguHoli111	IrreguHoli11+21*10
//#define	IrreguHoli112	IrreguHoli11+21*11
//#define	IrreguHoli113	IrreguHoli11+21*12
//#define	IrreguHoli114	IrreguHoli11+21*13
//#define	IrreguHoli115	IrreguHoli11+21*14
#define	ReguHoli1		IrreguHoli18+21	
#define	SeasonSdb1		ReguHoli1+31		
#define	WeekSdb11		SeasonSdb1+17
#define	WeekSdb12		WeekSdb11+8*1
#define	WeekSdb13		WeekSdb11+8*2
#define	WeekSdb14		WeekSdb11+8*3
#define	ComplDaySdb11	WeekSdb11+8*4
#define	ComplDaySdb12	ComplDaySdb11+25*1
#define	ComplDaySdb13	ComplDaySdb11+25*2
#define	ComplDaySdb14	ComplDaySdb11+25*3
#define	ComplDaySdb15	ComplDaySdb11+25*4
#define	ComplDaySdb16	ComplDaySdb11+25*5

//---------
#define	ComplexSd2Name	ComplDaySdb16+25
#define	IrreguHoli21	ComplexSd2Name+9
#define	IrreguHoli22	IrreguHoli21+21*1	
#define	IrreguHoli23	IrreguHoli21+21*2	
#define	IrreguHoli24	IrreguHoli21+21*3	
#define	IrreguHoli25	IrreguHoli21+21*4	
#define	IrreguHoli26	IrreguHoli21+21*5	
#define	IrreguHoli27	IrreguHoli21+21*6	
#define	IrreguHoli28	IrreguHoli21+21*7
//#define	IrreguHoli29	IrreguHoli21+21*8
//#define	IrreguHoli210	IrreguHoli21+21*9
//#define	IrreguHoli211	IrreguHoli21+21*10
//#define	IrreguHoli212	IrreguHoli21+21*11
//#define	IrreguHoli213	IrreguHoli21+21*12
//#define	IrreguHoli214	IrreguHoli21+21*13
//#define	IrreguHoli215	IrreguHoli21+21*14	
#define	ReguHoli2		IrreguHoli28+21	
#define	SeasonSdb2		ReguHoli2+31		
#define	WeekSdb21		SeasonSdb2+17
#define	WeekSdb22		WeekSdb21+8*1
#define	WeekSdb23		WeekSdb21+8*2
#define	WeekSdb24		WeekSdb21+8*3
#define	ComplDaySdb21	WeekSdb21+8*4
#define	ComplDaySdb22	ComplDaySdb21+25*1
#define	ComplDaySdb23	ComplDaySdb21+25*2
#define	ComplDaySdb24	ComplDaySdb21+25*3
#define	ComplDaySdb25	ComplDaySdb21+25*4
#define	ComplDaySdb26	ComplDaySdb21+25*5
//---------
#define	ComplexSd3Name	ComplDaySdb26+25
#define	IrreguHoli31	ComplexSd3Name+9
#define	IrreguHoli32	IrreguHoli31+21*1	
#define	IrreguHoli33	IrreguHoli31+21*2	
#define	IrreguHoli34	IrreguHoli31+21*3	
#define	IrreguHoli35	IrreguHoli31+21*4	
#define	IrreguHoli36	IrreguHoli31+21*5	
#define	IrreguHoli37	IrreguHoli31+21*6	
#define	IrreguHoli38	IrreguHoli31+21*7
//#define	IrreguHoli39	IrreguHoli31+21*8
//#define	IrreguHoli310	IrreguHoli31+21*9
//#define	IrreguHoli311	IrreguHoli31+21*10
//#define	IrreguHoli312	IrreguHoli31+21*11
//#define	IrreguHoli313	IrreguHoli31+21*12	
//#define	IrreguHoli314	IrreguHoli31+21*13
//#define	IrreguHoli315	IrreguHoli31+21*14
#define	ReguHoli3		IrreguHoli38+21	
#define	SeasonSdb3		ReguHoli3+31		
#define	WeekSdb31		SeasonSdb3+17
#define	WeekSdb32		WeekSdb31+8*1
#define	WeekSdb33		WeekSdb31+8*2
#define	WeekSdb34		WeekSdb31+8*3
#define	ComplDaySdb31	WeekSdb31+8*4
#define	ComplDaySdb32	ComplDaySdb31+25*1
#define	ComplDaySdb33	ComplDaySdb31+25*2
#define	ComplDaySdb34	ComplDaySdb31+25*3
#define	ComplDaySdb35	ComplDaySdb31+25*4
#define	ComplDaySdb36	ComplDaySdb31+25*5

#define	CurrRunSdName	ComplDaySdb36+25
#define	Lxcsadd1		CurrRunSdName+9	
#define	Lxcsadd2		Lxcsadd1+ 5*1
#define	Lxcsadd3		Lxcsadd1+ 5*2  
#define	Lxcsadd4		Lxcsadd1+ 5*3                                   
#define	Lxcsadd5		Lxcsadd1+ 5*4                                   
#define	Lxcsadd6		Lxcsadd1+ 5*5                                   
#define	Lxcsadd7		Lxcsadd1+ 5*6                                   
#define	Lxcsadd8		Lxcsadd1+ 5*7                                   
#define	Lxcsadd9		Lxcsadd1+ 5*8   
                                
#define	SumWinSwitch		Lxcsadd1+ 5*9
#define	MagFlag			SumWinSwitch+2		//(2)
#define	KGFlag        		MagFlag+2			//(2)
#define	KDFlag			KGFlag+2		//(2)
#define	ReverseFlag		KDFlag+2		//(2)

#define	LastJsr			ReverseFlag+2	//(4)
#define	LastSdName		LastJsr+4	//9
#define	RtcShiftYear		LastSdName+9			//(4)

#define	Password0		RtcShiftYear+4	//����0(5)
//#define	Password1		Password0+5*1			//����1(5)
//#define	Password2		Password0+5*2			//����2(5)
//#define	Password3		Password0+5*3			//����3(5)
//
//#define	ClkBuf1			Password0+5				//ʱ�仺����1(7)
//#define	ClkBuf2			ClkBuf1+7*1				//ʱ�仺����2(7)
//#define	ClkBuf3			ClkBuf1+7*2				//ʱ�仺����3(7)
//#define	ClkBuf4			ClkBuf1+7*3				//ʱ�仺����4(7)
//#define	ClkBuf5			ClkBuf1+7*4				//ʱ�仺����4(7)
//#define	ClkBuf6			ClkBuf1+7*5				//ʱ�仺����4(7)
//#define	ClkBuf7			ClkBuf1+7*6				//ʱ�仺����4(7)
//#define	ClkBuf8			ClkBuf1+7*7				//ʱ�仺����4(7)

//174+1220+30+61

//#define	ECrys_Offs		Password0+5				//Ƶ�ʵ�У����(3)ppmֵ
//#define	EDx_Valve		ECrys_Offs+3			//���෧ֵ��ѹ����(4)
//#define	ECMode			ECrys_Offs+3			//���������ۼ�ģʽ(2) 0:��������ӡ�1:����ֵ���

#define LoadCtrlByte	Password0+9//ECrys_Offs+3				//���ɼ�¼������(2)
#define LoadRecState	LoadCtrlByte+2			//��ǰ���ɼ�¼״̬(6)
//#define TamperRecState	LoadRecState+6			//��ǰ�¼���¼״̬(4)

#define	EMeter_No	LoadRecState+6				//����(21)
#define	PCB_No		EMeter_No+21					//pcb��(13)
#define	Serial_No	PCB_No+13					//���к�(21)
//#define	EDev_Ads		EUser_No+7				//�豸��(7)
//#define	Meter_PConst	EUser_No+7				//����й�����(4)
//#define	Meter_QConst	Meter_PConst+4			//����޹�����(4)
//#define	EMaxT			Meter_PConst+4			//��������(2)
//#define	EMaxDT			EMaxT+2					//����ʱ��(2)
//#define 	AmPOver_Valve 	EMaxDT+2				//������ֵ(3)
//#define	EVA_Valve		EMaxDT+2			//��ѹ\������ֵBCD�룬���ֽ���ǰ����ѹ��ǰ   (5)
#define	ESave_Day		Serial_No+21				//������(4)
//#define	Special_Day		ESave_Day+4				//������(2)		
#define	EDspInv			ESave_Day+4//Special_Day+2			//��ʾ���(2)
//#define EDisHours		EDspInv+2				//ͣ�����ʾСʱ��(3) 9999�����ر�
//#define EDisDays		EDspInv+2				//ͣ�����ʾ����(2) 
//#define EBatComHours	EDisDays+2				//ͣ���ͣ�����ά��Сʱ��(3) 
//#define EAddress		EDisHours+3				//��ַ(2)
////#define EBandRateMode	EDisDays+2				//�����ʸı�ģʽ(2) 0������ 1������Ӧ
////#define	Meter_Ident		EBandRateMode+2			//�������ʶ���(2)
////#define	EVolt_Valve		Meter_Ident+2			//��ѹ��ֵ����(2)
////#define Dis_Off_Time	EVolt_Valve+2			//ͣ��ʱ��(5) 
////#define AutoDisMode		Dis_Off_Time+5			//�Զ�����ģʽ(2)
////#define EZJAddress		AutoDisMode+2			//����ַ(2)
//#define EAwakeDisDays	EZJAddress+2			//ͣ�绽��֧��ʱ��(2)	16����	//V30


//#define	ETu				EAwakeDisDays+2				//����״̬�ȶ�ʱ��(2)
//#define	EUe				ETu+2					//��ѹ��ֵ(3)
//#define EIx				EUe+3					//���������ֵ(3)

#define DisSwitch		EDspInv+2					//��ʾ����(3)
//#define	EPJLmode		DisSwitch+3				//�й����������ģʽ(3) 
												//�ڶ��ֽ� 0��ֻ���й����򣬷��򲻼�
												//1:�й�������ϼƣ����򲻼�
												//2:�й�ֻ�����򣬷����¼
												//3:�й�������ϼƣ������¼
#define Alarm_Control	DisSwitch+3				//����������(3)
//#define LabPrgTime		Alarm_Control+3			//ʵ���Ҽ���̿�����Чʱ��(7)												
//#define PrgPurview		LabPrgTime+7			//���Ȩ��(3)
//#define ECClrMode		PrgPurview+3			//��������ģʽ(2)
#define DisDigitNum		Alarm_Control+3				//С��λ��(2)

//#define ECClrCount	DisDigitNum+2			//�����������(2)
//#define Pre1Prg_Data	ECClrCount+2			//�����һ�α��ʱ���¼(8)
//#define Pre2Prg_Data	Pre1Prg_Data+8*1		//����ڶ��α��ʱ���¼(8)
//#define Pre3Prg_Data	Pre1Prg_Data+8*2		//��������α��ʱ���¼(8)

//#define LastPrgTime6	Pre3Prg_Data+8			//���һ�α��ʱ��(7)

//#define RunOverStartTime	LastPrgTime6+7		//������ʼʱ��(6)
//#define RunOverSumTime		RunOverStartTime+6	//�����ۼ�ʱ��(4)

//174+1220+30+61+63+74

//#define	MD_Reset_CT		RunOverSumTime+4		//������λ����(3)
//#define	Prg_Count		MD_Reset_CT+3			//��̴���(3)
//#define	Pdown_CT		Prg_Count+3				//�µ����(3)
#define LastEC_Pt				DisDigitNum+2			//��ǰ��ʷ������¼��ַָ��(3)
#define	Last_Mon_Tm				LastEC_Pt+3				//���½���ʱ��(3)
#define GeneralLoadCurAddr 		Last_Mon_Tm+3			//��ͨ�������ߵ�ǰ��¼�׵�ַ(5)
#define GeneralMonCurAddr 		GeneralLoadCurAddr+5	//��ʷ���ݵ�ǰ��¼�׵�ַ(5)
#define GeneralTamperCurAddr 	GeneralLoadCurAddr+5*2	//�¼���¼��ǰ��¼�׵�ַ(5)
#define	EMeter_No_Bit			GeneralTamperCurAddr+5	//д����ʹ��(2)
#define	Serial_No_Bit			EMeter_No_Bit+2			//д���к�ʹ��(2)
#define	CE_Clr_Bit				EMeter_No_Bit+2*2		//��������ʹ��(2)
#define	Meter_type_Bit			EMeter_No_Bit+2*3		//�����ͺ���ʹ��(2)

#define	User_ID					Meter_type_Bit+2			//�û�ID��9��
#define	Opencover_Time		User_ID+9				//��6��
#define	OpenTcover_Time		Opencover_Time+6				//��6��
#define	PRGRMByte		OpenTcover_Time+6				//��2��
#define	ParameterDataStata		PRGRMByte+2				//��2��
#define	NewTariffDataStata		PRGRMByte+2*2			//��2��

//#define	ClockAdj		PRGRMByte+2*3				//��2��

#define	MeterRestCnt		NewTariffDataStata+2				//��3��
#define	PhaseL1Cnt			MeterRestCnt+3				//��3��
#define	PhaseL2Cnt			MeterRestCnt+3*2				//��3��
#define	PhaseL3Cnt			MeterRestCnt+3*3				//��3��
#define	OpenTCoverCnt		MeterRestCnt+3*4			//��3��
#define	OpenCoverCnt		MeterRestCnt+3*5				//��3��
#define	MagneticONCnt		MeterRestCnt+3*6				//��3��
#define	E2P_PSet_Cnt		MeterRestCnt+3*7				//��3��

#define	FristOTCover_Time	E2P_PSet_Cnt+3				//��7��
#define	FristOCover_Time	FristOTCover_Time+7				//��7��
#define	FristMagnetic_Time	FristOCover_Time+7				//��7��
#define 	ESetparaTime		FristMagnetic_Time+7	//��������ʱ��(7)	


#define MD_Over_Valve	ESetparaTime + 7		//(4)
#define Lcdvoltage		MD_Over_Valve + 4		//(2)0x09CD

#define	JsCount					Lcdvoltage+2			//�������(3)

#define EDisplayA1		JsCount + 3		//(31)
#define EDisplayA2		EDisplayA1 + 31		//(31)
#define EDisplayA3		EDisplayA2 + 31		//(31)
#define EDisplayM1		EDisplayA3 + 31		//(31)
#define EDisplayM2		EDisplayM1 + 31		//(31)
#define EDisplayM3		EDisplayM2 + 31		//(31)

#define	LcdAutime					EDisplayM3+31			//����ʱ��(2) 	�����ַ0x0A8E

#define	LoadLOADC					LcdAutime+2			//���ɼ�¼��Ŀ״̬��(4) 
#define	LoadLOADE					LoadLOADC+4			//���ɼ�¼ʹ��״̬��(2) 00ʹ��01�ر�
#define	DisHistNum					LoadLOADE+4			//��ʷ��ʾ����(2) 

#define T1OperationlTime		DisHistNum + 2			//T1����ʱ��(6)
#define T2OperationlTime		T1OperationlTime + 6		//T2����ʱ��(6)
#define T3OperationlTime		T2OperationlTime + 6		//T3����ʱ��(6)
#define T4OperationlTime		T3OperationlTime + 6		//T4����ʱ��(6)

#define ECOperationlTime		T4OperationlTime + 6		//T����ʱ��(6)
#define REVOperationlTime	ECOperationlTime + 6		//T��������ʱ��(6)
#define MagnetOperationlTime	REVOperationlTime + 6		//�ų�����ʱ��(6)

#define PAFailCnt		MagnetOperationlTime + 6			//L1ʧѹ����(5)
#define PBFailCnt		PAFailCnt + 5*1				//L2ʧѹ����(5)
#define PCFailCnt		PAFailCnt + 5*2				//L3ʧѹ����(5)
#define OpCoverCnt		PAFailCnt + 5*3				//���Ǵ���(5)
#define OpTCoverCnt		PAFailCnt + 5*4				//���˴���(5)
#define ReverseCnt		PAFailCnt + 5*5				//�������(5)

#define MOnCnt		ReverseCnt + 5				//�ų����Ŵ���(6)

#define LastPTime		MOnCnt + 6				//���һ�α��ʱ��(6)
#define LastRTime		LastPTime + 6				//���һ�ζ�����ʱ��(6)
#define LastRTCTime		LastRTime + 6				//���һ��ʱ������ʱ��(6)
#define BatteryWorkTime	LastRTCTime+6			//(6)��ع���ʱ��

#define TamperRecState	BatteryWorkTime+6			//��ǰ�¼���¼״̬(4)
#define TamperRecState1	TamperRecState+4			//��ǰ�¼���¼״̬(4)
#define TamperRecState2	TamperRecState1+4			//��ǰ�¼���¼״̬(4)
#define TamperRecState3	TamperRecState2+4			//��ǰ�¼���¼״̬(4)
#define TamperRecState4	TamperRecState3+4			//��ǰ�¼���¼״̬(4)
#define TamperRecState5	TamperRecState4+4			//��ǰ�¼���¼״̬(4)

#define Metertype_No	TamperRecState5+4					//�����ͺ���(7)
#define Constantled 	Metertype_No + 7				//LED���峣��(5)
#define Constants0	Constantled + 5				//S0���峣��(5)
#define Tariffsnumber  Constants0 + 5				//������2˫���ʡ�1������(2)	 //14.2.9wwl
#define TamperSwitch  Tariffsnumber + 2				//(2)

#define Eventdelay		TamperSwitch+2			//�¼���¼���ʱ��(2)

#define PAFailCntMon		Eventdelay + 2					//L1ʧѹ����(5)
#define PBFailCntMon		PAFailCntMon + 5*1				//L2ʧѹ����(5)
#define PCFailCntMon		PAFailCntMon + 5*2				//L3ʧѹ����(5)

#define CRCCheck  PCFailCntMon + 5				//����CRC ֵ(3)	 //14.2.19wwl
#define Widthimpulse  CRCCheck + 3				//������ms(2)   //14.2.9wwl
#define ECMode	Widthimpulse + 2				//������ʽ0 ������ 1����ֵ(2)  //13.3.6wwl
#define LedMode  ECMode + 2				//Led �������ģʽ 01:�޸���ʱ����; 00���������淽ʽ(2)	 //14.2.19wwl

#define MDT_Pp0  LedMode + 2				//���һ������ʱ��(6)

#define JOINTTYPE  MDT_Pp0 + 6				//������������(2) 00 ר��01 ����

#define	Server_ID			JOINTTYPE+1				//(11)�豸��
#define	PublicKey_X		Server_ID+11				//(25)
#define	PublicKey_Y		PublicKey_X+25				//(25)
#define	Private_Key		PublicKey_Y+25				//(25)

//#define PowerDownSave		MDT_Pp0 + 6			//�µ�˲��Ҫ���������(13)

#define PowerDownSave		0x1000			//�µ�˲��Ҫ���������(13)//St0x0B05
#define PowerDownSave1		PowerDownSave + 64			//�µ�˲��Ҫ���������(13)//St0x0B05

//#define	NewTariffDataStata		PRGRMByte+2*2				//��2��


#define	CalibrationRecord		0x1FC0				//�ڲ�E��У���������

                         
#define E2P_PGLEN		0x0B00//0xAAA//0x1554		//���ݱ���ҳ����

#define E2P_PGLENRN8213	0x2000//0xAAA//0x1554		//�ڲ�E�����ݱ���ҳ����
#define	LoadRecord_Time		0x6000//0x1554 //��̲���������

#endif	

//#endif                                                                                          
                                                                                                
#define RelayHW		NoCheck		
//#define RelayHW			YesCheck	//�̵���
#define FlashChip		NoCheck		//FLASHоƬ
//#define FlashChip		YesCheck
//Ӳ���汾
//#define HWVerCT		YesCheck	//������
#define HWVerCT		NoCheck			//SHUNT
//���߰汾
#define HWVer3P		YesCheck	//����
//#define HWVer3P		NoCheck			//����

//#define HWVer2PCB		YesCheck	//˫���
#define HWVer2PCB		NoCheck			//�����

#define	Gliwice		00
#define	Krakov		01
#define	Gdansk		02
#define	Warsaw		03
#define	Bialystok	04

#define FWCity		Krakov

#if ( Threephase == YesCheck ) //����
#define	CRCH		0xED
#define	CRCL		0x13
#define	CRCRead1		'E'
#define	CRCRead2		'D'
#define	CRCRead3		'1'
#define	CRCRead4		'3'
#else 
#define	CRCH		0x20
#define	CRCL		0x7C
#define	CRCRead1		'2'
#define	CRCRead2		'0'
#define	CRCRead3		'7'
#define	CRCRead4		'C'

#endif

///////////   FLASH	//ǰ300ҳΪ���ɼ�¼
#if (FlashChip == YesCheck)
#define	Mon_Data_Addr	 0x25800//0x19000	//(1840)��ҳ��

#else 

//#define	 E2P_TamperDataLong		0x05E0//0x127//0x1554		//����
#define	Mon_Data_Addr	 		0x4000//0x19000	//(1840)��ҳ��
#define	Tamper_Data_Addr	 0x5000	//(6000)
#define	Tamper_Data_Addr1	 Tamper_Data_Addr + 0x127	//(6000)
#define	Tamper_Data_Addr2	 Tamper_Data_Addr1 + 0x127	//(6000)
#define	Tamper_Data_Addr3	 Tamper_Data_Addr2 + 0x127	//(6000)
#define	Tamper_Data_Addr4	 Tamper_Data_Addr3 + 0x127	//(6000)
#define	Tamper_Data_Addr5	 Tamper_Data_Addr4 + 0x127	//(6000)

#endif



#define FlashAT45DB		NoCheck		//ATMEL��AT25DF041Aϵ��оƬ AT26DF081��AT26DF161
#define FlashAT161Series	YesCheck	//ATMEL��AT45161оƬ ����2M�ֽ�

#define GeneralLoadCurveSta		0x00000000		//0
#define GeneralLoadCurveEnd		0x00090000		//384K  ��ͨ�������߷�Χ��
#define GeneralMonCurveSta		0x00090000		//0
#define GeneralMonCurveEnd		0x000A0000		//64K  ��ʷ���ݷ�Χ��
#define GeneralTamperCurveSta	0x000A0000		//0
#define GeneralTamperCurveEnd	0x000B0000		//64K  �¼���¼��Χ��


/*******У��24C04�洢�ռ䶨��(ҳд)*******/ 
#if ( Threephase == YesCheck ) //����
#if ( MEASCHIP == ATT7053 )
#define	AGPBase		0x00			//A��B��C���ѹУ׼��׼(7)  
#define	BGPBase		AGPBase+3		//A��B��C���ѹУ׼��׼(7)  
#define	CGPBase		AGPBase+3*2		//A��B��C���ѹУ׼��׼(7)  
#define	AGPhs		CGPBase+3		//A��B��C���ѹУ׼��׼(7)  
#define	BGPhs		AGPhs+3			//A��B��C���ѹУ׼��׼(7)  
#define	CGPhs		AGPhs+3*2		//A��B��C���ѹУ׼��׼(7) 
#elif ( MEASCHIP == ADE7755 )
#define	EUBase		0x00			//A��B��C���ѹУ׼��׼(7)  
#define	EYBase		EUBase+7		//A��B��C���й���������У׼��׼(7) 
#elif ( MEASCHIP == RN8207 )

//#define	EYBase		0x00			//A��B��C���ѹУ׼��׼(7) 
#define	EYBase		0x0FC0			//A��B��C���ѹУ׼��׼(7) 
#define	EIrmsK		EYBase+7		//У�����ϵ��(7)
#define	EUrmsK		EIrmsK+7		//У���ѹϵ��(7)
#define 	EAPOS		EUrmsK+7		//У���й�offset(7)
#define	EPHSA		EAPOS+7			//��λ(7)

#define 	EAPOSn		EPHSA+7		//У���޹�offset(7)
#define	EPHSAn		EAPOSn+7			//�޹���λ(7)

#define	ClockAdj		EPHSAn+7				//��2��

//#define	CalibrationRecord		0x7000				//�ڲ�E��У���������

#endif
#elif ( SinglePhase == YesCheck )	//����
//SOCУ�����  ����λ����
//#define  EV_rms_scale_factor       		0x00						//��ѹ
//#define  ECurrent_I_ac_offset			EV_rms_scale_factor+3*1		//������Чֵƫ��
//#define  ECurrent_I_rms_scale_factor    EV_rms_scale_factor+3*2		//����
//#define  ECurrent_P_scale_factor        EV_rms_scale_factor+3*3		//��������
//#define  ECurrent_P_ac_offset  			EV_rms_scale_factor+3*4     //����ƫ��
//#define  ECurrent_phase_correction      EV_rms_scale_factor+3*5		//��λ
//#define  ECurrent_I_region_stages1     	EV_rms_scale_factor+3*6     //��һ�η����Եķֽ��
//#define  ECurrent_I_region_stages2     	EV_rms_scale_factor+3*7     //�ڶ��η����Եķֽ��
//#define  ECurrent_I_region_stages3   	EV_rms_scale_factor+3*8     //�����η����Եķֽ��
//#define  ECurrent_phase_cal_val0 		EV_rms_scale_factor+3*9  	//��һ���ֽ�����µ���λУ׼
//#define  ECurrent_phase_cal_val1      	EV_rms_scale_factor+3*10	//��һ���ֽ��������ڶ����ֽ��
//#define  ECurrent_phase_cal_val2     	EV_rms_scale_factor+3*11 	//�ڶ����ֽ��������������ֽ��
//#define  ECurrent_phase_cal_val3  		EV_rms_scale_factor+3*12	//�������ֽ�����ϵ���λУ׼ֵ
//#define  Ecalib_sum1       				EV_rms_scale_factor+3*13	//У���

//#define EE_CAL_IA			 0x0000			//IA(3)
//#define EE_CAL_IB			 EE_CAL_IA+3		//IB(3)
//#define EE_CAL_PA			 EE_CAL_IA+3*2		//PA(3)
//#define EE_CAL_PB			 EE_CAL_IA+3*3		//PB(3)
//#define EE_CAL_V			 EE_CAL_IA+3*4		//V(3)

//#define EE_PHADJ_A			 EE_CAL_IA+3*5		//A����λ(3)
//#define EE_PHADJ_B			 EE_CAL_IA+3*6		//B����λ(3)
//#define EE_Offset_A			 EE_CAL_IA+3*5		//A��Offset(3)
//#define EE_Offset_B			 EE_CAL_IA+3*6		//B��Offset(3)

//#define EMUStatusJY			 EE_Offset_B+3		//У���(5)
#endif  
