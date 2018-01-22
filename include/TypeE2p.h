#include "TypeMeter.h"
//#define CMonItems	123		//当前月电量、需量、需量时间总项数
//#define	CMonLength	574		//当前月电量、需量、需量时间总长度

//铁电存储器中保存当前所有电量，有一个备份(占前4页 4*2*128 )
//和当前有功正向、当前有功反向、当前视在、一、二、三、四象限需量缓存区（60分钟、120字节），无备份(后4页 4*2*128)
/***********************************************/


// 第一片24C64中存储的内容：电量、需量、

#if ( Threephase == YesCheck ) //三相			
/*
//	Current Month EC Date
#define	CMon_EC_Pp0 		0x00				//当前总电量1.8.0
#define	CMon_EC_Pp1		CMon_EC_Pp0 + 7*1	  
#define	CMon_EC_Pp2		CMon_EC_Pp0 + 7*2
#define	CMon_EC_Pp3		CMon_EC_Pp0 + 7*3
#define	CMon_EC_Pp4		CMon_EC_Pp0 + 7*4 

#define	CMon_EC_PL1 		CMon_EC_Pp4 + 7					//当前总电量L1 正向电量 21.8.0
#define	CMon_EC_PL2		CMon_EC_PL1 + 7*1				//当前总电量L2正向电量 41.8.0
#define	CMon_EC_PL3		CMon_EC_PL1 + 7*2 				//当前总电量L3正向电量 61.8.0
#define	CMon_EC_Pn0 		CMon_EC_PL1 + 7*3				//当前反向总电量2.8.0
#define	CMon_EC_PL1R		CMon_EC_PL1 + 7*4	  			//当前总电量L1 反向电量 22.8.0
#define	CMon_EC_PL2R		CMon_EC_PL1 + 7*5				//当前总电量L2反向电量 42.8.0
#define	CMon_EC_PL3R		CMon_EC_PL1 + 7*6 				//当前总电量L3反向电量 62.8.0
#define	CMon_EC_PpMa		CMon_EC_PL1 + 7*7 				//当前总电量磁场影响 1.8.139

#define CMon_MD_Pp0		CMon_EC_PpMa + 7	//当前总需量 // 15.6.0 	(4)
#define CMon_MD_Pp1		CMon_MD_Pp0 + 4*1	//当前总需量 // 15.6.0
#define CMon_MD_Pp2		CMon_MD_Pp0 + 4*2	//当前总需量 // 15.6.0
#define CMon_MD_Pp3		CMon_MD_Pp0 + 4*3	//当前总需量 // 15.6.0
#define CMon_MD_Pp4		CMon_MD_Pp0 + 4*4	//当前总需量 // 15.6.0
#define CMon_MD_Pn			CMon_MD_Pp0 + 4*5	//当前总需量 // 2.6.0

#define CMon_MDT_Pp0		CMon_MD_Pn + 4			//当前总需量时间    (6)
#define CMon_MDT_Pp1		CMon_MDT_Pp0 + 6*1		//当前总需量时间
#define CMon_MDT_Pp2		CMon_MDT_Pp0 + 6*2		//当前总需量时间
#define CMon_MDT_Pp3		CMon_MDT_Pp0 + 6*3		//当前总需量时间
#define CMon_MDT_Pp4		CMon_MDT_Pp0 + 6*4		//当前总需量时间
#define CMon_MDT_Pn		CMon_MDT_Pp0 + 6*5		//当前总需量时间

//电量缓存区
#define ECBufPp_Ptr		CMon_MDT_Pn+6		//有功正向缓存区数据指针(2) //0x86
#define ECBufPp1_Ptr		ECBufPp_Ptr + 2*1	//有功反向缓存区数据指针(2)
#define ECBufPp2_Ptr		ECBufPp_Ptr + 2*2	//有功反向缓存区数据指针(2)
#define ECBufPp3_Ptr		ECBufPp_Ptr + 2*3	//有功反向缓存区数据指针(2)
#define ECBufPp4_Ptr		ECBufPp_Ptr + 2*4	//有功反向缓存区数据指针(2)

#define ECBufPL1_Ptr		ECBufPp4_Ptr + 2	//有功反向缓存区数据指针(2)
#define ECBufPL2_Ptr		ECBufPL1_Ptr + 2*1	//有功反向缓存区数据指针(2)
#define ECBufPL3_Ptr		ECBufPL1_Ptr + 2*2	//有功反向缓存区数据指针(2)
#define ECBufPn_Ptr		ECBufPL1_Ptr + 2*3	//有功反向缓存区数据指针(2)
#define ECBufPL1R_Ptr	ECBufPL1_Ptr + 2*4	//有功反向缓存区数据指针(2)
#define ECBufPL2R_Ptr	ECBufPL1_Ptr + 2*5	//有功反向缓存区数据指针(2)
#define ECBufPL3R_Ptr	ECBufPL1_Ptr + 2*6	//有功反向缓存区数据指针(2)
#define ECBufPpMa_Ptr	ECBufPL1_Ptr + 2*7	//有功反向缓存区数据指针(2)


#define ECBufPp		ECBufPpMa_Ptr + 2		//有功正向缓存区(128)	//0x009E
#define ECBufPp1		ECBufPp + 128*1		//有功正向缓存区(128)
#define ECBufPp2    	ECBufPp + 128*2		//有功正向缓存区(128)
#define ECBufPp3		ECBufPp + 128*3		//有功正向缓存区(128)
#define ECBufPp4		ECBufPp + 128*4		//有功正向缓存区(128)

#define ECBufPL1		ECBufPp4 + 128		//有功正向缓存区(128)	
#define ECBufPL2    	ECBufPL1 + 128*1		//有功正向缓存区(128)
#define ECBufPL3		ECBufPL1 + 128*2		//有功正向缓存区(128)
#define ECBufPn		ECBufPL1 + 128*3		//有功反向缓存区(128)	
#define ECBufPL1R	ECBufPL1 + 128*4		//有功正向缓存区(128)
#define ECBufPL2R	ECBufPL1 + 128*5		//有功正向缓存区(128)
#define ECBufPL3R	ECBufPL1 + 128*6		//有功正向缓存区(128)
#define ECBufPpMa	ECBufPL1 + 128*7		//有功正向缓存区(128)
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电量需量数据存外部E方
#define	CMon_EC_Pp0 		0x00				//当前总电量15.8.0
#define	CMon_EC_Pp1		CMon_EC_Pp0 + 8*1	  
#define	CMon_EC_Pp2		CMon_EC_Pp0 + 8*2
#define	CMon_EC_Pp3		CMon_EC_Pp0 + 8*3
#define	CMon_EC_Pp4		CMon_EC_Pp0 + 8*4 
#define	CMon_EC_Pn0 	CMon_EC_Pp0 + 8*5 				//当前反向总电量2.8.0

#define	CMon_EC_Pn1		CMon_EC_Pn0 + (8)*1
#define	CMon_EC_Pn2 	CMon_EC_Pn0 + (8)*2
#define	CMon_EC_Pn3		CMon_EC_Pn0 + (8)*3
#define	CMon_EC_Pn4 	CMon_EC_Pn0 + (8)*4

#define CMon_MD_Pp0		CMon_EC_Pp4 + 7		//当前总需量 // 15.6.0 	(4)
#define CMon_MD_Pp1		CMon_MD_Pp0 + 4*1	//当前总需量 // 15.6.0
#define CMon_MD_Pp2		CMon_MD_Pp0 + 4*2	//当前总需量 // 15.6.0
#define CMon_MD_Pp3		CMon_MD_Pp0 + 4*3	//当前总需量 // 15.6.0
#define CMon_MD_Pp4		CMon_MD_Pp0 + 4*4	//当前总需量 // 15.6.0

#define CMon_MDT_Pp0		CMon_MD_Pp4 + 4			//当前总需量时间    (6)
#define CMon_MDT_Pp1		CMon_MDT_Pp0 + 6*1		//当前总需量时间
#define CMon_MDT_Pp2		CMon_MDT_Pp0 + 6*2		//当前总需量时间
#define CMon_MDT_Pp3		CMon_MDT_Pp0 + 6*3		//当前总需量时间
#define CMon_MDT_Pp4		CMon_MDT_Pp0 + 6*4		//当前总需量时间


#define ECBufPp_Ptr		CMon_MDT_Pp4+6		//有功正向缓存区数据指针(2)
#define ECBufPp1_Ptr	ECBufPp_Ptr + 2*1	//有功反向缓存区数据指针(2)
#define ECBufPp2_Ptr	ECBufPp_Ptr + 2*2	//有功反向缓存区数据指针(2)
#define ECBufPp3_Ptr	ECBufPp_Ptr + 2*3	//有功反向缓存区数据指针(2)
#define ECBufPp4_Ptr	ECBufPp_Ptr + 2*4	//有功反向缓存区数据指针(2)
#define ECBufPn_Ptr	ECBufPp_Ptr + 2*5	//有功反向缓存区数据指针(2)

#define ECBufPp		ECBufPp4_Ptr + 2		//有功正向缓存区(128)	//0x267
#define ECBufPp1		ECBufPp + 128*1		//有功正向缓存区(128)
#define ECBufPp2    	ECBufPp + 128*2		//有功正向缓存区(128)
#define ECBufPp3		ECBufPp + 128*3		//有功正向缓存区(128)
#define ECBufPp4		ECBufPp + 128*4		//有功正向缓存区(128)
#define ECBufPn		ECBufPp + 128*5		//有功反向缓存区(128)	

//-------------------------------------------------- 24C256 RN8213内部E方
#define ChooseSdb  		0x00			//按键切换费率缓存（2）
#define TempClkAdd		ChooseSdb+2		//按键设置时钟 修改时间缓存 （8）
#define ManuJsHour		TempClkAdd+8 	//手动结算时间 （4）
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

#define	Password0		RtcShiftYear+4	//密码0(5)
//#define	Password1		Password0+5*1			//密码1(5)
//#define	Password2		Password0+5*2			//密码2(5)
//#define	Password3		Password0+5*3			//密码3(5)
//
//#define	ClkBuf1			Password0+5				//时间缓存区1(7)
//#define	ClkBuf2			ClkBuf1+7*1				//时间缓存区2(7)
//#define	ClkBuf3			ClkBuf1+7*2				//时间缓存区3(7)
//#define	ClkBuf4			ClkBuf1+7*3				//时间缓存区4(7)
//#define	ClkBuf5			ClkBuf1+7*4				//时间缓存区4(7)
//#define	ClkBuf6			ClkBuf1+7*5				//时间缓存区4(7)
//#define	ClkBuf7			ClkBuf1+7*6				//时间缓存区4(7)
//#define	ClkBuf8			ClkBuf1+7*7				//时间缓存区4(7)

//174+1220+30+61

//#define	ECrys_Offs		Password0+5				//频率调校因子(3)ppm值
//#define	EDx_Valve		ECrys_Offs+3			//断相阀值电压设置(4)
//#define	ECMode			ECrys_Offs+3			//合相能量累加模式(2) 0:代数和相加、1:绝对值相加

#define LoadCtrlByte	Password0+9//ECrys_Offs+3				//负荷记录控制字(2)
#define LoadRecState	LoadCtrlByte+2			//当前负荷记录状态(6)
//#define TamperRecState	LoadRecState+6			//当前事件记录状态(4)

#define	EMeter_No	LoadRecState+6				//电表号(21)
#define	PCB_No		EMeter_No+21				//pcb号(13)
#define	Serial_No	PCB_No+13					//序列号(21)
//#define	EDev_Ads		EUser_No+7				//设备号(7)
//#define	Meter_PConst	EUser_No+7				//电表有功常数(4)
//#define	Meter_QConst	Meter_PConst+4			//电表无功常数(4)
//#define	EMaxT			Meter_PConst+4			//需量周期(2)
//#define	EMaxDT			EMaxT+2					//滑差时间(2)
//#define 	AmPOver_Valve 	EMaxDT+2				//过流阀值(3)
//#define	EVA_Valve		EMaxDT+2			//电压\电流阀值BCD码，低字节在前，电压在前   (5)
#define	ESave_Day		Serial_No+21				//结算日(4)
//#define	Special_Day		ESave_Day+4				//代表日(2)		
#define	EDspInv			ESave_Day+4//Special_Day+2			//显示间隔(2)
//#define EDisHours		EDspInv+2				//停电后显示小时数(3) 9999永不关闭
//#define EDisDays		EDspInv+2				//停电后显示天数(2) 
//#define EBatComHours	EDisDays+2				//停电后停抄检测维持小时数(3) 
//#define EAddress		EDisHours+3				//地址(2)
////#define EBandRateMode	EDisDays+2				//波特率改变模式(2) 0：可设 1：自适应
////#define	Meter_Ident		EBandRateMode+2			//电表单三相识别号(2)
////#define	EVolt_Valve		Meter_Ident+2			//电压阀值比例(2)
////#define Dis_Off_Time	EVolt_Valve+2			//停显时间(5) 
////#define AutoDisMode		Dis_Off_Time+5			//自动轮显模式(2)
////#define EZJAddress		AutoDisMode+2			//浙规地址(2)
//#define EAwakeDisDays	EZJAddress+2			//停电唤醒支持时间(2)	16进制	//V30


//#define	ETu				EAwakeDisDays+2				//断相状态稳定时间(2)
//#define	EUe				ETu+2					//过压阀值(3)
//#define EIx				EUe+3					//断相电流阀值(3)

#define DisSwitch		EDspInv+2					//显示开关(3)
//#define	EPJLmode		DisSwitch+3				//有功正反向计量模式(3) 
												//第二字节 0：只记有功正向，反向不计
												//1:有功正反向合计，反向不计
												//2:有功只记正向，反向记录
												//3:有功正反向合计，反向计录
#define Alarm_Control	DisSwitch+3				//报警控制字(3)
//#define LabPrgTime		Alarm_Control+3			//实验室及编程开关有效时间(7)												
//#define PrgPurview		LabPrgTime+7			//编程权限(3)
//#define ECClrMode		PrgPurview+3			//电量清零模式(2)
#define DisDigitNum		Alarm_Control+3				//小数位数(2)

//#define ECClrCount	DisDigitNum+2			//电量清零次数(2)
//#define Pre1Prg_Data	ECClrCount+2			//最近第一次编程时间记录(8)
//#define Pre2Prg_Data	Pre1Prg_Data+8*1		//最近第二次编程时间记录(8)
//#define Pre3Prg_Data	Pre1Prg_Data+8*2		//最近第三次编程时间记录(8)

//#define LastPrgTime6	Pre3Prg_Data+8			//最近一次编程时间(7)

//#define RunOverStartTime	LastPrgTime6+7		//飞走起始时间(6)
//#define RunOverSumTime		RunOverStartTime+6	//飞走累计时间(4)

//174+1220+30+61+63+74

//#define	MD_Reset_CT		RunOverSumTime+4		//需量复位次数(3)
//#define	Prg_Count		MD_Reset_CT+3			//编程次数(3)
//#define	Pdown_CT		Prg_Count+3				//下电次数(3)
#define LastEC_Pt				DisDigitNum+2			//当前历史电量记录首址指针(3)
#define	Last_Mon_Tm				LastEC_Pt+3				//上月结算时间(3)
#define GeneralLoadCurAddr 		Last_Mon_Tm+3			//普通负荷曲线当前记录首地址(5)
#define GeneralMonCurAddr 		GeneralLoadCurAddr+5	//历史数据当前记录首地址(5)
#define GeneralTamperCurAddr 	GeneralLoadCurAddr+5*2	//事件记录当前记录首地址(5)
#define	EMeter_No_Bit			GeneralTamperCurAddr+5	//写电表号使能(2)
#define	Serial_No_Bit			EMeter_No_Bit+2			//写序列号使能(2)
#define	CE_Clr_Bit				EMeter_No_Bit+2*2		//电量清零使能(2)
#define	Meter_type_Bit			EMeter_No_Bit+2*3		//表类型号码使能(2)

#define	User_ID					Meter_type_Bit+2			//用户ID（9）
#define	Opencover_Time		User_ID+9				//（6）
#define	OpenTcover_Time		Opencover_Time+6				//（6）
#define	PRGRMByte		OpenTcover_Time+6				//（2）
#define	ParameterDataStata		PRGRMByte+2				//（2）
#define	NewTariffDataStata		PRGRMByte+2*2			//（2）

//#define	ClockAdj		PRGRMByte+2*3				//（2）

#define	MeterRestCnt		NewTariffDataStata+2				//（3）
#define	PhaseL1Cnt		MeterRestCnt+3				//（3）
#define	PhaseL2Cnt		MeterRestCnt+3*2				//（3）
#define	PhaseL3Cnt		MeterRestCnt+3*3				//（3）
#define	OpenTCoverCnt		MeterRestCnt+3*4			//（3）
#define	OpenCoverCnt		MeterRestCnt+3*5				//（3）
#define	MagneticONCnt		MeterRestCnt+3*6				//（3）
#define	E2P_PSet_Cnt		MeterRestCnt+3*7				//（3）

#define	FristOTCover_Time	E2P_PSet_Cnt+3				//（7）
#define	FristOCover_Time	FristOTCover_Time+7				//（7）
#define	FristMagnetic_Time	FristOCover_Time+7				//（7）
#define 	ESetparaTime		FristMagnetic_Time+7	//参数设置时间(7)	

#define MD_Over_Valve	ESetparaTime + 7		//(4)
#define Lcdvoltage		MD_Over_Valve + 4		//(2)0x09CD

#define	JsCount					Lcdvoltage+2			//结算次数(3)

#define EDisplayA1		JsCount + 3		//(31)
#define EDisplayA2		EDisplayA1 + 31		//(31)
#define EDisplayA3		EDisplayA2 + 31		//(31)
#define EDisplayM1		EDisplayA3 + 31		//(31)
#define EDisplayM2		EDisplayM1 + 31		//(31)
#define EDisplayM3		EDisplayM2 + 31		//(31)

#define	LcdAutime					EDisplayM3+31			//轮显时间(2) 	结算地址0x0A8E

#define	LoadLOADC					LcdAutime+2			//负荷记录项目状态字(4) 
#define	LoadLOADE					LoadLOADC+4			//负荷记录使能状态字(2) 00使能01关闭
#define	DisHistNum					LoadLOADE+4			//历史显示项数(2)

//#define	NewTariffDataStata		PRGRMByte+2*2				//（2）

//#define ECOperationlTime		DisHistNum +2			//T运行时间(6)
//#define T1OperationlTime		ECOperationlTime + 6		//T1运行时间(6)
//#define T2OperationlTime		T1OperationlTime + 6		//T2运行时间(6)
//#define REVOperationlTime	T2OperationlTime + 6		//T反向运行时间(6)

#define T1OperationlTime		DisHistNum + 2			//T1运行时间(6)
#define T2OperationlTime		T1OperationlTime + 6		//T2运行时间(6)
#define T3OperationlTime		T2OperationlTime + 6		//T3运行时间(6)
#define T4OperationlTime		T3OperationlTime + 6		//T4运行时间(6)

#define ECOperationlTime		T4OperationlTime + 6		//T运行时间(6)
#define REVOperationlTime	ECOperationlTime + 6		//T反向运行时间(6)
#define MagnetOperationlTime	REVOperationlTime + 6		//磁场运行时间(6)

#define PAFailCnt		MagnetOperationlTime + 6			//L1失压次数(5)
#define PBFailCnt		PAFailCnt + 5*1				//L2失压次数(5)
#define PCFailCnt		PAFailCnt + 5*2				//L3失压次数(5)
#define OpCoverCnt		PAFailCnt + 5*3				//开盖次数(5)
#define OpTCoverCnt		PAFailCnt + 5*4				//开端次数(5)
#define ReverseCnt		PAFailCnt + 5*5				//反向次数(5)

#define MOnCnt		ReverseCnt + 5				//磁场干扰次数(6)

#define LastPTime		MOnCnt + 6				//最后一次编程时间(6)
#define LastRTime		LastPTime + 6				//最后一次读数据时间(6)
#define LastRTCTime		LastRTime + 6				//最后一次时钟设置时间(6)
#define BatteryWorkTime	LastRTCTime+6			//(6)电池工作时间

#define TamperRecState	BatteryWorkTime+6			//当前事件记录状态(4)
#define TamperRecState1	TamperRecState+4			//当前事件记录状态(4)
#define TamperRecState2	TamperRecState1+4			//当前事件记录状态(4)
#define TamperRecState3	TamperRecState2+4			//当前事件记录状态(4)
#define TamperRecState4	TamperRecState3+4			//当前事件记录状态(4)
#define TamperRecState5	TamperRecState4+4			//当前事件记录状态(4)

#define Metertype_No	TamperRecState5+4					//表类型号码(7)
#define Constantled 	Metertype_No + 7				//LED脉冲常数(5)
#define Constants0	Constantled + 5				//S0脉冲常数(5)
#define Tariffsnumber  Constants0 + 5				//费率数2双费率、1单费率(2)	 //14.2.9wwl
#define TamperSwitch  Tariffsnumber + 2				//(2)

#define Eventdelay		TamperSwitch+2			//事件记录检测时间(2)

#define PAFailCntMon		Eventdelay + 2					//L1失压次数(5)
#define PBFailCntMon		PAFailCntMon + 5*1				//L2失压次数(5)
#define PCFailCntMon		PAFailCntMon + 5*2				//L3失压次数(5)

#define CRCCheck  PCFailCntMon + 5				//程序CRC 值(3)
#if 0
#define Widthimpulse  CRCCheck + 3				//脉冲宽度ms(2)   //14.2.9wwl
#define ECMode	Widthimpulse + 2				//计量方式0 代数和 1绝对值(2)  //13.3.6wwl
#define LedMode  ECMode + 2				//Led 脉冲输出模式 01:无负载时点亮; 00及其他常规方式(2)	 //14.2.19wwl
#define MDT_Pp0  LedMode + 2				//最后一次需量时间(6)
#define JOINTTYPE  MDT_Pp0 + 6				//加入网络类型(2) 00 专网01 公网
#else
#define Server_BABID	CRCCheck+3 
#endif

#define	Server_ID			Server_BABID+12		//(11)设备号
#define	PublicKey_X		Server_ID+14				//(25)
#define	PublicKey_Y		PublicKey_X+25				//(25)
#define	Private_Key		PublicKey_Y+65				//(25)
#define	Magnetic_Bit		Private_Key+34				//磁场标记(2)

#define	DisPINAdd			Magnetic_Bit+2				//（4）
#define	DisHisAdd			DisPINAdd+4				//（2）
#define	DisPINEnAdd		DisHisAdd+2				//（2）
#define	ActivTariffXAdd		DisPINEnAdd+2				//（2）

#define	E2P_INF0							ActivTariffXAdd+2				//（2）
#define	E2P_ModeEDL40					E2P_INF0+2				//（2）
#define	E2P_ResHistorical			E2P_ModeEDL40+2				//（2）
#define	E2P_DisHistorical			E2P_ResHistorical+2			//（2）
#define	E2P_ProtectionPINCode	E2P_DisHistorical+2			//（2）
#define	E2P_SetMSB						E2P_ProtectionPINCode+2			//（2）
#define	E2P_OResHisButton			E2P_SetMSB+2				//（2）
#define	E2P_DisPINCode				E2P_OResHisButton+2			//（2）
#define	E2P_DisPActive				E2P_OResHisButton+4			//（2）
#define	E2P_HisDAY1						E2P_DisPActive+3			//（6）
#define	E2P_HisDAY7						E2P_HisDAY1+8				//（6）
#define	E2P_HisDAY30					E2P_HisDAY7+8				//（6）
#define	E2P_HisDAY365					E2P_HisDAY30+8				//（6）
#define	E2P_LastReset					E2P_HisDAY365+8				//（6）
#define	E2P_SMLTime						E2P_LastReset+8				//（6）
#define	E2P_ConManipulation		E2P_SMLTime+6				//（5）
#define	E2P_DisTariff					E2P_ConManipulation+5			//（5）
#define	E2P_ChangeTariff			E2P_DisTariff+5				//（2）
#define	E2P_SATEWORD					E2P_ChangeTariff+2			//（4）
#define	Last_EC_Pp0						E2P_SATEWORD+4				//（9）
#define	E2P_NumSwitchProgramm	Last_EC_Pp0+9				//（7）
#define	E2P_TextAusgabe				E2P_NumSwitchProgramm+7			//（10）
#define	E2P_DisDataSetFlag		E2P_TextAusgabe+10			//（1）
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




//#define PowerDownSave		LedMode + 6			//下电瞬间要保存的数据(13)//St0x0B05
//#define PowerDownSave		MDT_Pp0 + 6			//下电瞬间要保存的数据(13)//St0x0B05

#define PowerDownSave			0x1000			//下电瞬间要保存的数据(13)//St0x0B05
#define PowerDownSave1		PowerDownSave + 64			//下电瞬间要保存的数据(13)//St0x0B05

#define	CalibrationRecord		0x1FC0				//内部E方校表参数备份
 
#define E2P_PGLEN		0x0B00      //0xAAA//0x1554		//数据备份页长度


#define E2P_PGLENRN8213	0x2000//0xAAA//0x1554		//内部E方数据备份页长度
#define	LoadRecord_Time		0x6000//0x1554 //编程参数缓存区
					
#else
/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电量需量数据存外部E方
#define	CMon_EC_Pp0 		0x00				//当前总电量15.8.0
#define	CMon_EC_Pp1		CMon_EC_Pp0 + 7*1	  
#define	CMon_EC_Pp2		CMon_EC_Pp0 + 7*2
#define	CMon_EC_Pp3		CMon_EC_Pp0 + 7*3
#define	CMon_EC_Pp4		CMon_EC_Pp0 + 7*4 
#define	CMon_EC_Pn0 		CMon_EC_Pp0 + 7*5 
//#define	CMon_EC_PpMa		CMon_EC_Pp0 + 7*5 				//当前总电量磁场影响 1.8.139

#define CMon_MD_Pp0		CMon_EC_Pn0 + 7		//当前总需量 // 15.6.0 	(4)
#define CMon_MD_Pp1		CMon_MD_Pp0 + 4*1	//当前总需量 // 15.6.0
#define CMon_MD_Pp2		CMon_MD_Pp0 + 4*2	//当前总需量 // 15.6.0
#define CMon_MD_Pp3		CMon_MD_Pp0 + 4*3	//当前总需量 // 15.6.0
#define CMon_MD_Pp4		CMon_MD_Pp0 + 4*4	//当前总需量 // 15.6.0
#define CMon_MD_Pn			CMon_MD_Pp0 + 4*5	//当前总需量 // 2.6.0

#define CMon_MDT_Pp0		CMon_MD_Pn + 4			//当前总需量时间    (6)
#define CMon_MDT_Pp1		CMon_MDT_Pp0 + 6*1		//当前总需量时间
#define CMon_MDT_Pp2		CMon_MDT_Pp0 + 6*2		//当前总需量时间
#define CMon_MDT_Pp3		CMon_MDT_Pp0 + 6*3		//当前总需量时间
#define CMon_MDT_Pp4		CMon_MDT_Pp0 + 6*4		//当前总需量时间
#define CMon_MDT_Pn		CMon_MDT_Pp0 + 6*5		//当前总需量时间


#define ECBufPp_Ptr		CMon_MDT_Pn+6		//有功正向缓存区数据指针(2)
#define ECBufPp1_Ptr		ECBufPp_Ptr + 2*1	//有功反向缓存区数据指针(2)
#define ECBufPp2_Ptr		ECBufPp_Ptr + 2*2	//有功反向缓存区数据指针(2)
#define ECBufPp3_Ptr		ECBufPp_Ptr + 2*3	//有功反向缓存区数据指针(2)
#define ECBufPp4_Ptr		ECBufPp_Ptr + 2*4	//有功反向缓存区数据指针(2)
#define ECBufPn_Ptr		ECBufPp_Ptr + 2*5	//有功反向缓存区数据指针(2)
//#define ECBufPpMa_Ptr	ECBufPp_Ptr + 2*5	//有功反向缓存区数据指针(2)

#define ECBufPp		ECBufPn_Ptr + 2		//有功正向缓存区(128)	//0x267
#define ECBufPp1		ECBufPp + 128*1		//有功正向缓存区(128)
#define ECBufPp2    	ECBufPp + 128*2		//有功正向缓存区(128)
#define ECBufPp3		ECBufPp + 128*3		//有功正向缓存区(128)
#define ECBufPp4		ECBufPp + 128*4		//有功正向缓存区(128)
#define ECBufPn		ECBufPp + 128*5			//有功反向缓存区(128)	//结束地址:0x0368
//#define ECBufPpMa	ECBufPp + 128*5		//有功正向缓存区(128)
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电量需量数据存外部E方
#define	CMon_EC_Pp0 		0x00				//当前总电量15.8.0
#define	CMon_EC_Pp1		CMon_EC_Pp0 + 7*1	  
#define	CMon_EC_Pp2		CMon_EC_Pp0 + 7*2
#define	CMon_EC_Pp3		CMon_EC_Pp0 + 7*3
#define	CMon_EC_Pp4		CMon_EC_Pp0 + 7*4 
#define	CMon_EC_Pn0 		CMon_EC_Pp0 + 7*5 				//当前反向总电量2.8.0

#define CMon_MD_Pp0		CMon_EC_Pp4 + 7		//当前总需量 // 15.6.0 	(4)
#define CMon_MD_Pp1		CMon_MD_Pp0 + 4*1	//当前总需量 // 15.6.0
#define CMon_MD_Pp2		CMon_MD_Pp0 + 4*2	//当前总需量 // 15.6.0
#define CMon_MD_Pp3		CMon_MD_Pp0 + 4*3	//当前总需量 // 15.6.0
#define CMon_MD_Pp4		CMon_MD_Pp0 + 4*4	//当前总需量 // 15.6.0

#define CMon_MDT_Pp0		CMon_MD_Pp4 + 4			//当前总需量时间    (6)
#define CMon_MDT_Pp1		CMon_MDT_Pp0 + 6*1		//当前总需量时间
#define CMon_MDT_Pp2		CMon_MDT_Pp0 + 6*2		//当前总需量时间
#define CMon_MDT_Pp3		CMon_MDT_Pp0 + 6*3		//当前总需量时间
#define CMon_MDT_Pp4		CMon_MDT_Pp0 + 6*4		//当前总需量时间


#define ECBufPp_Ptr		CMon_MDT_Pp4+6		//有功正向缓存区数据指针(2)
#define ECBufPp1_Ptr	ECBufPp_Ptr + 2*1	//有功反向缓存区数据指针(2)
#define ECBufPp2_Ptr	ECBufPp_Ptr + 2*2	//有功反向缓存区数据指针(2)
#define ECBufPp3_Ptr	ECBufPp_Ptr + 2*3	//有功反向缓存区数据指针(2)
#define ECBufPp4_Ptr	ECBufPp_Ptr + 2*4	//有功反向缓存区数据指针(2)
#define ECBufPn_Ptr	ECBufPp_Ptr + 2*5	//有功反向缓存区数据指针(2)

#define ECBufPp		ECBufPp4_Ptr + 2		//有功正向缓存区(128)	//0x267
#define ECBufPp1		ECBufPp + 128*1		//有功正向缓存区(128)
#define ECBufPp2    	ECBufPp + 128*2		//有功正向缓存区(128)
#define ECBufPp3		ECBufPp + 128*3		//有功正向缓存区(128)
#define ECBufPp4		ECBufPp + 128*4		//有功正向缓存区(128)
#define ECBufPn		ECBufPp + 128*5		//有功反向缓存区(128)	

/*
#define	CMon_EC_Pp0 		0x00				//当前总电量15.8.0
#define	CMon_EC_Pp1		CMon_EC_Pp0 + 7*1	  
#define	CMon_EC_Pp2		CMon_EC_Pp0 + 7*2
#define	CMon_EC_Pp3		CMon_EC_Pp0 + 7*3
//#define	CMon_EC_Pp4		CMon_EC_Pp0 + 7*4 
#define	CMon_EC_Pn0 		CMon_EC_Pp0 + 7*4 
#define	CMon_EC_PpMa		CMon_EC_Pp0 + 7*5 				//当前总电量磁场影响 1.8.139

#define CMon_MD_Pp0		CMon_EC_PpMa + 7		//当前总需量 // 15.6.0 	(4)
#define CMon_MD_Pp1		CMon_MD_Pp0 + 4*1	//当前总需量 // 15.6.0
#define CMon_MD_Pp2		CMon_MD_Pp0 + 4*2	//当前总需量 // 15.6.0
#define CMon_MD_Pp3		CMon_MD_Pp0 + 4*3	//当前总需量 // 15.6.0
#define CMon_MD_Pp4		CMon_MD_Pp0 + 4*4	//当前总需量 // 15.6.0
#define CMon_MD_Pn			CMon_MD_Pp0 + 4*5	//当前总需量 // 2.6.0

#define CMon_MDT_Pp0		CMon_MD_Pn + 4			//当前总需量时间    (6)
#define CMon_MDT_Pp1		CMon_MDT_Pp0 + 6*1		//当前总需量时间
#define CMon_MDT_Pp2		CMon_MDT_Pp0 + 6*2		//当前总需量时间
#define CMon_MDT_Pp3		CMon_MDT_Pp0 + 6*3		//当前总需量时间
#define CMon_MDT_Pp4		CMon_MDT_Pp0 + 6*4		//当前总需量时间
#define CMon_MDT_Pn		CMon_MDT_Pp0 + 6*5		//当前总需量时间


#define ECBufPp_Ptr		CMon_MDT_Pn+6		//有功正向缓存区数据指针(2)
#define ECBufPp1_Ptr		ECBufPp_Ptr + 2*1	//有功反向缓存区数据指针(2)
#define ECBufPp2_Ptr		ECBufPp_Ptr + 2*2	//有功反向缓存区数据指针(2)
#define ECBufPp3_Ptr		ECBufPp_Ptr + 2*3	//有功反向缓存区数据指针(2)
//#define ECBufPp4_Ptr		ECBufPp_Ptr + 2*4	//有功反向缓存区数据指针(2)
#define ECBufPn_Ptr		ECBufPp_Ptr + 2*4	//有功反向缓存区数据指针(2)
#define ECBufPpMa_Ptr	ECBufPp_Ptr + 2*5	//有功反向缓存区数据指针(2)

#define ECBufPp		ECBufPpMa_Ptr + 2		//有功正向缓存区(128)	//0x267
#define ECBufPp1		ECBufPp + 128*1		//有功正向缓存区(128)
#define ECBufPp2    	ECBufPp + 128*2		//有功正向缓存区(128)
#define ECBufPp3		ECBufPp + 128*3		//有功正向缓存区(128)
//#define ECBufPp4		ECBufPp + 128*4		//有功正向缓存区(128)
#define ECBufPn		ECBufPp + 128*4			//有功反向缓存区(128)	//结束地址:0x0368
#define ECBufPpMa	ECBufPp + 128*5		//有功正向缓存区(128)
*/

//需量缓存区
//#define MDBuf_Pp	ECBufPn + 128

//#define EE_CAL_IA			 ECBufPn+128			//IA(3)
#define EE_CAL_IA			 0x3D0			//IA(3)
#define EE_CAL_IB			 EE_CAL_IA+3		//IB(3)
#define EE_CAL_PA			 EE_CAL_IA+3*2		//PA(3)
#define EE_CAL_PB			 EE_CAL_IA+3*3		//PB(3)
#define EE_CAL_V			 EE_CAL_IA+3*4		//V(3)

#define EE_PHADJ_A			 EE_CAL_IA+3*5		//A相相位(3)
#define EE_PHADJ_B			 EE_CAL_IA+3*6		//B相相位(3)
#define EE_Offset_A			 EE_CAL_IA+3*7		//A相Offset(3)
#define EE_Offset_B			 EE_CAL_IA+3*8		//B相Offset(3)

#define EMUStatusJY			 EE_Offset_B+3		//校验和(5)  //结束地址:0x0388

#define	ClockAdj		EMUStatusJY+5				//（2）//结束地址:0x038A


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~基本参数部分，放RN8213内部E方


#define ChooseSdb  		0x00
#define TempClkAdd		ChooseSdb+2	//临时存放时间 8
#define ManuJsHour		TempClkAdd+8 	//手动结算时间 4
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

#define	Password0		RtcShiftYear+4	//密码0(5)
//#define	Password1		Password0+5*1			//密码1(5)
//#define	Password2		Password0+5*2			//密码2(5)
//#define	Password3		Password0+5*3			//密码3(5)
//
//#define	ClkBuf1			Password0+5				//时间缓存区1(7)
//#define	ClkBuf2			ClkBuf1+7*1				//时间缓存区2(7)
//#define	ClkBuf3			ClkBuf1+7*2				//时间缓存区3(7)
//#define	ClkBuf4			ClkBuf1+7*3				//时间缓存区4(7)
//#define	ClkBuf5			ClkBuf1+7*4				//时间缓存区4(7)
//#define	ClkBuf6			ClkBuf1+7*5				//时间缓存区4(7)
//#define	ClkBuf7			ClkBuf1+7*6				//时间缓存区4(7)
//#define	ClkBuf8			ClkBuf1+7*7				//时间缓存区4(7)

//174+1220+30+61

//#define	ECrys_Offs		Password0+5				//频率调校因子(3)ppm值
//#define	EDx_Valve		ECrys_Offs+3			//断相阀值电压设置(4)
//#define	ECMode			ECrys_Offs+3			//合相能量累加模式(2) 0:代数和相加、1:绝对值相加

#define LoadCtrlByte	Password0+9//ECrys_Offs+3				//负荷记录控制字(2)
#define LoadRecState	LoadCtrlByte+2			//当前负荷记录状态(6)
//#define TamperRecState	LoadRecState+6			//当前事件记录状态(4)

#define	EMeter_No	LoadRecState+6				//电表号(21)
#define	PCB_No		EMeter_No+21					//pcb号(13)
#define	Serial_No	PCB_No+13					//序列号(21)
//#define	EDev_Ads		EUser_No+7				//设备号(7)
//#define	Meter_PConst	EUser_No+7				//电表有功常数(4)
//#define	Meter_QConst	Meter_PConst+4			//电表无功常数(4)
//#define	EMaxT			Meter_PConst+4			//需量周期(2)
//#define	EMaxDT			EMaxT+2					//滑差时间(2)
//#define 	AmPOver_Valve 	EMaxDT+2				//过流阀值(3)
//#define	EVA_Valve		EMaxDT+2			//电压\电流阀值BCD码，低字节在前，电压在前   (5)
#define	ESave_Day		Serial_No+21				//结算日(4)
//#define	Special_Day		ESave_Day+4				//代表日(2)		
#define	EDspInv			ESave_Day+4//Special_Day+2			//显示间隔(2)
//#define EDisHours		EDspInv+2				//停电后显示小时数(3) 9999永不关闭
//#define EDisDays		EDspInv+2				//停电后显示天数(2) 
//#define EBatComHours	EDisDays+2				//停电后停抄检测维持小时数(3) 
//#define EAddress		EDisHours+3				//地址(2)
////#define EBandRateMode	EDisDays+2				//波特率改变模式(2) 0：可设 1：自适应
////#define	Meter_Ident		EBandRateMode+2			//电表单三相识别号(2)
////#define	EVolt_Valve		Meter_Ident+2			//电压阀值比例(2)
////#define Dis_Off_Time	EVolt_Valve+2			//停显时间(5) 
////#define AutoDisMode		Dis_Off_Time+5			//自动轮显模式(2)
////#define EZJAddress		AutoDisMode+2			//浙规地址(2)
//#define EAwakeDisDays	EZJAddress+2			//停电唤醒支持时间(2)	16进制	//V30


//#define	ETu				EAwakeDisDays+2				//断相状态稳定时间(2)
//#define	EUe				ETu+2					//过压阀值(3)
//#define EIx				EUe+3					//断相电流阀值(3)

#define DisSwitch		EDspInv+2					//显示开关(3)
//#define	EPJLmode		DisSwitch+3				//有功正反向计量模式(3) 
												//第二字节 0：只记有功正向，反向不计
												//1:有功正反向合计，反向不计
												//2:有功只记正向，反向记录
												//3:有功正反向合计，反向计录
#define Alarm_Control	DisSwitch+3				//报警控制字(3)
//#define LabPrgTime		Alarm_Control+3			//实验室及编程开关有效时间(7)												
//#define PrgPurview		LabPrgTime+7			//编程权限(3)
//#define ECClrMode		PrgPurview+3			//电量清零模式(2)
#define DisDigitNum		Alarm_Control+3				//小数位数(2)

//#define ECClrCount	DisDigitNum+2			//电量清零次数(2)
//#define Pre1Prg_Data	ECClrCount+2			//最近第一次编程时间记录(8)
//#define Pre2Prg_Data	Pre1Prg_Data+8*1		//最近第二次编程时间记录(8)
//#define Pre3Prg_Data	Pre1Prg_Data+8*2		//最近第三次编程时间记录(8)

//#define LastPrgTime6	Pre3Prg_Data+8			//最近一次编程时间(7)

//#define RunOverStartTime	LastPrgTime6+7		//飞走起始时间(6)
//#define RunOverSumTime		RunOverStartTime+6	//飞走累计时间(4)

//174+1220+30+61+63+74

//#define	MD_Reset_CT		RunOverSumTime+4		//需量复位次数(3)
//#define	Prg_Count		MD_Reset_CT+3			//编程次数(3)
//#define	Pdown_CT		Prg_Count+3				//下电次数(3)
#define LastEC_Pt				DisDigitNum+2			//当前历史电量记录首址指针(3)
#define	Last_Mon_Tm				LastEC_Pt+3				//上月结算时间(3)
#define GeneralLoadCurAddr 		Last_Mon_Tm+3			//普通负荷曲线当前记录首地址(5)
#define GeneralMonCurAddr 		GeneralLoadCurAddr+5	//历史数据当前记录首地址(5)
#define GeneralTamperCurAddr 	GeneralLoadCurAddr+5*2	//事件记录当前记录首地址(5)
#define	EMeter_No_Bit			GeneralTamperCurAddr+5	//写电表号使能(2)
#define	Serial_No_Bit			EMeter_No_Bit+2			//写序列号使能(2)
#define	CE_Clr_Bit				EMeter_No_Bit+2*2		//电量清零使能(2)
#define	Meter_type_Bit			EMeter_No_Bit+2*3		//表类型号码使能(2)

#define	User_ID					Meter_type_Bit+2			//用户ID（9）
#define	Opencover_Time		User_ID+9				//（6）
#define	OpenTcover_Time		Opencover_Time+6				//（6）
#define	PRGRMByte		OpenTcover_Time+6				//（2）
#define	ParameterDataStata		PRGRMByte+2				//（2）
#define	NewTariffDataStata		PRGRMByte+2*2			//（2）

//#define	ClockAdj		PRGRMByte+2*3				//（2）

#define	MeterRestCnt		NewTariffDataStata+2				//（3）
#define	PhaseL1Cnt			MeterRestCnt+3				//（3）
#define	PhaseL2Cnt			MeterRestCnt+3*2				//（3）
#define	PhaseL3Cnt			MeterRestCnt+3*3				//（3）
#define	OpenTCoverCnt		MeterRestCnt+3*4			//（3）
#define	OpenCoverCnt		MeterRestCnt+3*5				//（3）
#define	MagneticONCnt		MeterRestCnt+3*6				//（3）
#define	E2P_PSet_Cnt		MeterRestCnt+3*7				//（3）

#define	FristOTCover_Time	E2P_PSet_Cnt+3				//（7）
#define	FristOCover_Time	FristOTCover_Time+7				//（7）
#define	FristMagnetic_Time	FristOCover_Time+7				//（7）
#define 	ESetparaTime		FristMagnetic_Time+7	//参数设置时间(7)	


#define MD_Over_Valve	ESetparaTime + 7		//(4)
#define Lcdvoltage		MD_Over_Valve + 4		//(2)0x09CD

#define	JsCount					Lcdvoltage+2			//结算次数(3)

#define EDisplayA1		JsCount + 3		//(31)
#define EDisplayA2		EDisplayA1 + 31		//(31)
#define EDisplayA3		EDisplayA2 + 31		//(31)
#define EDisplayM1		EDisplayA3 + 31		//(31)
#define EDisplayM2		EDisplayM1 + 31		//(31)
#define EDisplayM3		EDisplayM2 + 31		//(31)

#define	LcdAutime					EDisplayM3+31			//轮显时间(2) 	结算地址0x0A8E

#define	LoadLOADC					LcdAutime+2			//负荷记录项目状态字(4) 
#define	LoadLOADE					LoadLOADC+4			//负荷记录使能状态字(2) 00使能01关闭
#define	DisHistNum					LoadLOADE+4			//历史显示项数(2) 

#define T1OperationlTime		DisHistNum + 2			//T1运行时间(6)
#define T2OperationlTime		T1OperationlTime + 6		//T2运行时间(6)
#define T3OperationlTime		T2OperationlTime + 6		//T3运行时间(6)
#define T4OperationlTime		T3OperationlTime + 6		//T4运行时间(6)

#define ECOperationlTime		T4OperationlTime + 6		//T运行时间(6)
#define REVOperationlTime	ECOperationlTime + 6		//T反向运行时间(6)
#define MagnetOperationlTime	REVOperationlTime + 6		//磁场运行时间(6)

#define PAFailCnt		MagnetOperationlTime + 6			//L1失压次数(5)
#define PBFailCnt		PAFailCnt + 5*1				//L2失压次数(5)
#define PCFailCnt		PAFailCnt + 5*2				//L3失压次数(5)
#define OpCoverCnt		PAFailCnt + 5*3				//开盖次数(5)
#define OpTCoverCnt		PAFailCnt + 5*4				//开端次数(5)
#define ReverseCnt		PAFailCnt + 5*5				//反向次数(5)

#define MOnCnt		ReverseCnt + 5				//磁场干扰次数(6)

#define LastPTime		MOnCnt + 6				//最后一次编程时间(6)
#define LastRTime		LastPTime + 6				//最后一次读数据时间(6)
#define LastRTCTime		LastRTime + 6				//最后一次时钟设置时间(6)
#define BatteryWorkTime	LastRTCTime+6			//(6)电池工作时间

#define TamperRecState	BatteryWorkTime+6			//当前事件记录状态(4)
#define TamperRecState1	TamperRecState+4			//当前事件记录状态(4)
#define TamperRecState2	TamperRecState1+4			//当前事件记录状态(4)
#define TamperRecState3	TamperRecState2+4			//当前事件记录状态(4)
#define TamperRecState4	TamperRecState3+4			//当前事件记录状态(4)
#define TamperRecState5	TamperRecState4+4			//当前事件记录状态(4)

#define Metertype_No	TamperRecState5+4					//表类型号码(7)
#define Constantled 	Metertype_No + 7				//LED脉冲常数(5)
#define Constants0	Constantled + 5				//S0脉冲常数(5)
#define Tariffsnumber  Constants0 + 5				//费率数2双费率、1单费率(2)	 //14.2.9wwl
#define TamperSwitch  Tariffsnumber + 2				//(2)

#define Eventdelay		TamperSwitch+2			//事件记录检测时间(2)

#define PAFailCntMon		Eventdelay + 2					//L1失压次数(5)
#define PBFailCntMon		PAFailCntMon + 5*1				//L2失压次数(5)
#define PCFailCntMon		PAFailCntMon + 5*2				//L3失压次数(5)

#define CRCCheck  PCFailCntMon + 5				//程序CRC 值(3)	 //14.2.19wwl
#define Widthimpulse  CRCCheck + 3				//脉冲宽度ms(2)   //14.2.9wwl
#define ECMode	Widthimpulse + 2				//计量方式0 代数和 1绝对值(2)  //13.3.6wwl
#define LedMode  ECMode + 2				//Led 脉冲输出模式 01:无负载时点亮; 00及其他常规方式(2)	 //14.2.19wwl

#define MDT_Pp0  LedMode + 2				//最后一次需量时间(6)

#define JOINTTYPE  MDT_Pp0 + 6				//加入网络类型(2) 00 专网01 公网

#define	Server_ID			JOINTTYPE+1				//(11)设备号
#define	PublicKey_X		Server_ID+11				//(25)
#define	PublicKey_Y		PublicKey_X+25				//(25)
#define	Private_Key		PublicKey_Y+25				//(25)

//#define PowerDownSave		MDT_Pp0 + 6			//下电瞬间要保存的数据(13)

#define PowerDownSave		0x1000			//下电瞬间要保存的数据(13)//St0x0B05
#define PowerDownSave1		PowerDownSave + 64			//下电瞬间要保存的数据(13)//St0x0B05

//#define	NewTariffDataStata		PRGRMByte+2*2				//（2）


#define	CalibrationRecord		0x1FC0				//内部E方校表参数备份

                         
#define E2P_PGLEN		0x0B00//0xAAA//0x1554		//数据备份页长度

#define E2P_PGLENRN8213	0x2000//0xAAA//0x1554		//内部E方数据备份页长度
#define	LoadRecord_Time		0x6000//0x1554 //编程参数缓存区

#endif	

//#endif                                                                                          
                                                                                                
#define RelayHW		NoCheck		
//#define RelayHW			YesCheck	//继电器
#define FlashChip		NoCheck		//FLASH芯片
//#define FlashChip		YesCheck
//硬件版本
//#define HWVerCT		YesCheck	//互感器
#define HWVerCT		NoCheck			//SHUNT
//相线版本
#define HWVer3P		YesCheck	//三相
//#define HWVer3P		NoCheck			//单相

//#define HWVer2PCB		YesCheck	//双层板
#define HWVer2PCB		NoCheck			//单层板

#define	Gliwice		00
#define	Krakov		01
#define	Gdansk		02
#define	Warsaw		03
#define	Bialystok	04

#define FWCity		Krakov

#if ( Threephase == YesCheck ) //三相
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

///////////   FLASH	//前300页为负荷记录
#if (FlashChip == YesCheck)
#define	Mon_Data_Addr	 0x25800//0x19000	//(1840)三页多

#else 

//#define	 E2P_TamperDataLong		0x05E0//0x127//0x1554		//长度
#define	Mon_Data_Addr	 		0x4000//0x19000	//(1840)三页多
#define	Tamper_Data_Addr	 0x5000	//(6000)
#define	Tamper_Data_Addr1	 Tamper_Data_Addr + 0x127	//(6000)
#define	Tamper_Data_Addr2	 Tamper_Data_Addr1 + 0x127	//(6000)
#define	Tamper_Data_Addr3	 Tamper_Data_Addr2 + 0x127	//(6000)
#define	Tamper_Data_Addr4	 Tamper_Data_Addr3 + 0x127	//(6000)
#define	Tamper_Data_Addr5	 Tamper_Data_Addr4 + 0x127	//(6000)

#endif



#define FlashAT45DB		NoCheck		//ATMEL的AT25DF041A系列芯片 AT26DF081、AT26DF161
#define FlashAT161Series	YesCheck	//ATMEL的AT45161芯片 容量2M字节

#define GeneralLoadCurveSta		0x00000000		//0
#define GeneralLoadCurveEnd		0x00090000		//384K  普通负荷曲线范围，
#define GeneralMonCurveSta		0x00090000		//0
#define GeneralMonCurveEnd		0x000A0000		//64K  历史数据范围，
#define GeneralTamperCurveSta	0x000A0000		//0
#define GeneralTamperCurveEnd	0x000B0000		//64K  事件记录范围，


/*******校表24C04存储空间定义(页写)*******/ 
#if ( Threephase == YesCheck ) //三相
#if ( MEASCHIP == ATT7053 )
#define	AGPBase		0x00			//A相B相C相电压校准基准(7)  
#define	BGPBase		AGPBase+3		//A相B相C相电压校准基准(7)  
#define	CGPBase		AGPBase+3*2		//A相B相C相电压校准基准(7)  
#define	AGPhs		CGPBase+3		//A相B相C相电压校准基准(7)  
#define	BGPhs		AGPhs+3			//A相B相C相电压校准基准(7)  
#define	CGPhs		AGPhs+3*2		//A相B相C相电压校准基准(7) 
#elif ( MEASCHIP == ADE7755 )
#define	EUBase		0x00			//A相B相C相电压校准基准(7)  
#define	EYBase		EUBase+7		//A相B相C相有功电能脉冲校准基准(7) 
#elif ( MEASCHIP == RN8207 )

//#define	EYBase		0x00			//A相B相C相电压校准基准(7) 
#define	EYBase		0x0FC0			//A相B相C相电压校准基准(7) 
#define	EIrmsK		EYBase+7		//校表电流系数(7)
#define	EUrmsK		EIrmsK+7		//校表电压系数(7)
#define 	EAPOS		EUrmsK+7		//校表有功offset(7)
#define	EPHSA		EAPOS+7			//相位(7)

#define 	EAPOSn		EPHSA+7		//校表无功offset(7)
#define	EPHSAn		EAPOSn+7			//无功相位(7)

#define	ClockAdj		EPHSAn+7				//（2）

//#define	CalibrationRecord		0x7000				//内部E方校表参数备份

#endif
#elif ( SinglePhase == YesCheck )	//单相
//SOC校表参数  带相位补偿
//#define  EV_rms_scale_factor       		0x00						//电压
//#define  ECurrent_I_ac_offset			EV_rms_scale_factor+3*1		//电流有效值偏置
//#define  ECurrent_I_rms_scale_factor    EV_rms_scale_factor+3*2		//电流
//#define  ECurrent_P_scale_factor        EV_rms_scale_factor+3*3		//功率增益
//#define  ECurrent_P_ac_offset  			EV_rms_scale_factor+3*4     //功率偏置
//#define  ECurrent_phase_correction      EV_rms_scale_factor+3*5		//相位
//#define  ECurrent_I_region_stages1     	EV_rms_scale_factor+3*6     //第一段非线性的分界点
//#define  ECurrent_I_region_stages2     	EV_rms_scale_factor+3*7     //第二段非线性的分界点
//#define  ECurrent_I_region_stages3   	EV_rms_scale_factor+3*8     //第三段非线性的分界点
//#define  ECurrent_phase_cal_val0 		EV_rms_scale_factor+3*9  	//第一个分界点以下的相位校准
//#define  ECurrent_phase_cal_val1      	EV_rms_scale_factor+3*10	//第一个分界点以上与第二个分界点
//#define  ECurrent_phase_cal_val2     	EV_rms_scale_factor+3*11 	//第二个分界点以上与第三个分界点
//#define  ECurrent_phase_cal_val3  		EV_rms_scale_factor+3*12	//第三个分界点以上的相位校准值
//#define  Ecalib_sum1       				EV_rms_scale_factor+3*13	//校验和

//#define EE_CAL_IA			 0x0000			//IA(3)
//#define EE_CAL_IB			 EE_CAL_IA+3		//IB(3)
//#define EE_CAL_PA			 EE_CAL_IA+3*2		//PA(3)
//#define EE_CAL_PB			 EE_CAL_IA+3*3		//PB(3)
//#define EE_CAL_V			 EE_CAL_IA+3*4		//V(3)

//#define EE_PHADJ_A			 EE_CAL_IA+3*5		//A相相位(3)
//#define EE_PHADJ_B			 EE_CAL_IA+3*6		//B相相位(3)
//#define EE_Offset_A			 EE_CAL_IA+3*5		//A相Offset(3)
//#define EE_Offset_B			 EE_CAL_IA+3*6		//B相Offset(3)

//#define EMUStatusJY			 EE_Offset_B+3		//校验和(5)
#endif  
