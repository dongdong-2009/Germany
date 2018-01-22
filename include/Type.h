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
	BCD2	RAlarm_Control;	//报警控制字(2)	
	
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
	BCD2	RVolt_Valve;		//断相（失压）电压阀值(2)
	BCD2	RAmper_Valve;		//断相（失压）电流阀值(2)
	BCD2	Ue;				//过压阀值(2)
	unsigned char Tu;		//断相状态稳定时间(1)
	unsigned char TuMagnet ;		//断相状态稳定时间(1)
	
//	BCD2	I0;				//三相低于此电流为无负载，不判断流(2)不断流上限门槛值
	BCD4	PtABC;				//正向功率   0000.0000kw
	BCD4	PnABC;				//反向功率	0000.0000kw
	BCD4	PtABS;				//合相有功功率(3)绝对值功率	0000.0000kw
#endif	

	BCD4	Pa;				//A相有功功率(3)
	BCD4	Pb;				//B相有功功率(3)
	BCD4	Pc;				//C相有功功率(3)
	
	BCD4 	Pt;				//合相有功功率(3)代数和功率 0000.0000kw

	BCD4	Ua;				//A相电压(2) 三相000000.00V 单相00000.000V 
	BCD4	Ub;				//B相电压(2)
	BCD4	Uc;				//C相电压(2)	
	
	BCD4	Ia;				//A相电流(2)  三相00000.000A 单相0000.0000A
	BCD4	Ib;				//B相电流(2)
	BCD4	Ic;				//C相电流(2)

	BCD2	Pfa;			//A相功率因数(2) 三位小数 Pfa[1] = 09 Pfa[0] = 99  表示功率因数为0.999
	BCD2	Pfb;			//B相功率因数(2)
	BCD2	Pfc;			//C相功率因数(2)
	
	BCD2	Freq;
	//uint64_t Freq;			//频率(2)
	uint64_t servrid;
	uint64_t P0_day;
	uint64_t P0_week;
	uint64_t P0_month;
	uint64_t P0_year;
	uint64_t P0_last;
	
	BCD2 	Pangleba;
	BCD2  Pangleca;
	BCD2	Panglea;			//A相角度(2) 一位小数 Panglea[1] = 15 Panglea[0] = 12 表示功率因数为151.2°
	BCD2	Pangleb;			//B相角度(2)
	BCD2	Panglec;			//C相角度(2)
	unsigned char 	RDspInv;		// 循显时间(1)

	unsigned short	RTCDota0;		// RTC校正寄存器(2)
#if 0
	unsigned short 	ESavetime;	// 手动结算时间限制(2) 、	

  unsigned char 	RMaxT;			// 最大需量周期(1)
	unsigned char 	RMaxDT;			// 滑差周期(1)
	
	unsigned char 	RPrgDLY;		// 编程开关延时(1)
	unsigned char 	RPrgPurview; 	// 编程权限(1)
#endif	
#if( SecurityCheck == YesCheck )		
	unsigned char 	RECClrMode; 	// 电量清零模式(1)	
#endif	
//	unsigned char 	RPJLmode;		// 电能计量模式(1)	
#if 0
	unsigned char 	RAutoDisMode;	// 显示模式(1) 
	unsigned char 	RDisDigitNum;	// 电量小数位数(1) 
	unsigned char 	RPRGRMByte;	//编程按键(1)
#endif	
	unsigned char 	TestModeCnt;	// 测试模式时间(1)
#if 0	
	unsigned char 	Beginspeed;	// RS485开始波特率(1) 、	
#endif	
#if 0
	
	BCD2	LCDOffSTime;	//液晶关闭显示起始时间(2) 
	BCD2	LCDOffETime;	//液晶关闭显示结束时间(2) 
	


	BCD2	Panglea;			//A相角度(2) 一位小数 Panglea[1] = 15 Panglea[0] = 12 表示功率因数为151.2°
	BCD2	Pangleb;			//B相角度(2)
	BCD2	Panglec;			//C相角度(2)
	
	unsigned char SFlag;	//相序状态,bit3=1,逆相序(1) 
							//BIT0 = 1  A相功率大于1%Ib 
							//BIT1 = 1  B相功率大于1%Ib 
							//BIT2 = 1  C相功率大于1%Ib 
	unsigned char PWFlag;	//有功和无功功率方向(1) 
	unsigned char IabcFlag;	//分相电流标志(1)	
	BCD3 PWFlagbuff;	//有功和无功功率方向(1) 
	
	BCD3 	Seg[10];		// 时段表
	BCD3 	RelaySeg[10];		// 继电器	
#endif	
	uint32_t StatusWord;
	unsigned int pval;
	unsigned int p_plus;
	unsigned int p_count;
#else
	uint64_t Pp0;
	uint64_t Pn0;
  uint64_t meter_sts;
	
	uint64_t 	Pt;				//合相有功功率(3)代数和功率 0000.0000kw

	uint64_t	Ua;				//A相电压(2) 三相000000.00V 单相00000.000V 
	uint64_t	Ub;				//B相电压(2)
	uint64_t	Uc;				//C相电压(2)	
	
	uint64_t	Ia;				//A相电流(2)  三相00000.000A 单相0000.0000A
	uint64_t	Ib;				//B相电流(2)
	uint64_t	Ic;				//C相电流(2)
	
	uint64_t Freq;			//频率(2)
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
//	int ManuCode;				//厂家编码
//	BCD2 UserCode;				//用户编码	
	unsigned char Mode;					// 模式字
//	unsigned char KeyTmr;				// 按键扫描定时
//	unsigned char KeyLPCT;				// 按键长延时计数器
    unsigned char FlsCT;				// 闪烁计数器
    unsigned char DisInv;				// 轮显间隔计数器
 //   unsigned char ItemPtr;				// 轮显表指针
     unsigned short ItemPtr;				// 轮显表指针   
//    unsigned char ItemSum;			// 显示项总数
    unsigned char ItemNo;				// 显示项序号
    unsigned char ItemANo;				// 自动显示项序号
    unsigned char ItemMNo;				// 按键显示项序号
    unsigned char ItemSNo;				// 小项显示项序号
    unsigned char HisMon;				// 显示第几月的历史数据
    unsigned char RotPhase;				//L1,L2,L3交替闪烁
    unsigned char DisHisMun;				// 显示历史数据项数
		unsigned char info;
		unsigned char ec_ptr;
    
    unsigned char PoweoffNo;				// 停电后需要显示的总项数
    unsigned char PoweoffPtr;				// 停电后显示的项目指针   
		unsigned char power_ptr;
		unsigned char power_no;
		unsigned int  volt_code;
//    unsigned char LXItemSum;			// 轮显项总数

//    unsigned char LXTab[20];			// LCD段位缓存
	uint16_t DisECModeCnt;			//显示电量模式计时
	uint16_t DisECT1ModeCnt;			//显示电量模式计时
	unsigned char vol_cnt;
	  unsigned char com_No;
	uint16_t DoEDL40Cnt;
	uint16_t DisFeeCnt;
	uint16_t Dis022Cnt;
	uint16_t DisMUC_CCnt;
	uint8_t TextDisTmr;			// text显示定时
	
} DISKEY;

/*******************************************************************
	Even Log Profile Information Structure Define
*******************************************************************/
/*
// Bit Flag
	// Power flags define
#define  F_PwrUp     	0x02
#define  F_IrmsCheck	0x01		//0:测电流；1：电流校准
#define  F_AllFail		0x04		//0:非全失压;1:全失压
#define  F_ErrMeas		0x08		//计量芯片出错
#define  F_FailIrmsMeas	0x10		//校完表后第一次电流检测 0：已检测过；1：未检测
#define	 F_NCheckLoss	0x20		//零线检测。0：正常，1：掉零线
*/

#define  F_Relay1     		0x01
#define  F_Relay2     		0x02

#define  F_PwrUp     	0x02
//#define  F_IrmsCheck	0x01		//0:测电流；1：电流校准
#define  F_BatteryPwrUp	0x01		//9V电压：0:无；1：有
#define  F_EDMeasure		0x04		//0:下电不计量;1:下电计量
//#define  F_AllFail		0x04		//0:非全失压;1:全失压
#define  F_Loadrecord		0x08		//下电负荷曲线记录
#define  F_ByPass 		0x40		//电流旁路报警 
//#define  F_ErrMeas		0x08		//计量芯片出错
//#define  F_FailIrmsMeas	0x10		//校完表后第一次电流检测 0：已检测过；1：未检测
#define  F_DoLoadrecord	0x10		//下电发生过负荷记录
//#define	 F_DoEDMeasure	0x20		//零线检测。0：正常，1：掉零线
#define	 F_DoTariffDataRomove	0x20		//费率数据确认
#define	 F_DoParaDataRomove	0x40		//参数数据确认
//#define	 F_NCheckLoss	0x20		//零线检测。0：正常，1：掉零线
#define  F_DoCalU			0x80		//校电压电流
	// Run flags define
#define  F_ComOK    0x01
#define	 F_THW		0x02	//红外和485独立
//#define  F_ComOK3   0x02
//#define  F_Batt     0x04
#define  F_MonSave     0x04
#define	 F_T485		0x08	//红外和485独立
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
#define  F_LoadRecord   0x20	//负荷记录
#define  F_HalfSec      0x40
#define  F_641Sec       0x80	
	// DisK Flag Bit
#define  F_KeyInt    	0x80
#define  F_DspALT		0x40
#define  F_KeyStart    	0x20
#define  F_OpButtonEDL40    	0x10	//EDL40显示

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
//#define  F_ErrMeasMin	0x01		//计量芯片出错 分判飞走
#define  F_ErrMeasSec	0x02		//计量芯片出错 秒判飞走
#define  F_ErrMeasFlashDis	0x04	//开盖后液晶一直闪烁
#define  F_ErrOpenCoverDis	0x08	//开盖后液晶一直闪烁
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
#define  F_AlarmPhFail	0x01		//断相报警
#define  F_AlarmCuFail	0x02		//断流报警
#define  F_AlarmBatLow  0x08		//电池低电压报警
#define  F_AlarmPhs 	0x10		//逆相序报警 
#define  F_AlarmNLine 	0x20		//掉零线报警 
#define  F_AlarmByPass 	0x40		//电流旁路报警 
*/

	// AlarmFlg[0] Register flags define
#define  F_AlarmCoverOpen	0x01		//开盖报警//#define  F_AlarmPhFail	0x01		//断相报警
#define  F_AlarmTCoverOpen	0x02		//开盖报警//#define  F_AlarmAllCuFail	0x02		//全断流报警
#define  F_AlarmMagnet	0x04		//磁场报警//#define  F_AlarmMeas	0x04		//计量芯片出错
#define  F_AlarmCRCFail	0x08		//CRC校验错误
#define  F_AlarmPhs 	0x10		//逆相序报警 
#define  F_AlarmReverse	0x20		//功率反向报警
#define  F_AlarmClock	0x40		// 32768Hz Crystal Error
#define  F_AlarmE2P   	0x80

//#define  F_AlarmCuFail	0x20		//断流报警
//#define  F_AlarmBatLow  0x08		//电池低电压报警
//#define  F_AlarmNLine 	0x20	//掉零线报警 
//#define  F_AlarmByPass 	0x40	//电流旁路报警 


	// AlarmFlg[1] Register flags define        
#define  F_AlarmFlash	0x01		//FLASH报警 
#define  F_AlarmXT1		0x02		//XT1晶振报警
#define  F_AlarmBATCH	0x04		//电池报警
#define  F_EventPhs		0x08		//逆相序事件发生过

	// AlarmFlg[3] Register flags define
#define  F_EventKEYSF	0x01		//按过上翻键
#define  F_EventKEYXF	0x02		//按过下翻键
#define  F_EventKEYPF	0x04		//按过编程键
#define  F_EventCoverOpen	0x08		//按过开盖检测键
#define  F_EventTCoverOpen	0x10		//按过开端检测键
#define  F_EventMagnet		0x20		//按过磁场检测键
#define  F_EventFLQH			0x40		//按过费率切换键1
#define  F_EventFLQH1		0x80		//按过费率切换键2


	// FirstFlg Register flags define
#define  F_PhAFail	0x04		//第一次A相断相未记录
#define  F_PhBFail	0x08		//第一次B相断相未记录
#define  F_PhCFail	0x10		//第一次C相断相未记录
#define  F_CuAFail	0x20		//第一次A相断流未记录	//改为A相高速脉冲标志
#define  F_CuBFail	0x40		//第一次A相断流未记录	//改为B相高速脉冲标志
#define  F_CuCFail	0x80		//第一次A相断流未记录	//改为C相高速脉冲标志

/*
#define  F_ErrRAM    0x01
#define  F_ErrMeas   0x02		//计量芯片出错
#define  F_ErrE2P    0x04
#define  F_ErrDFls   0x08
#define  F_ErrCry1 	0x10		// 32768Hz Crystal Error
#define  F_ErrCry2 	0x20		// 8MHz Crystal Error
#define  F_WatchDog	0x40
#define  F_ErrANY    0x80
*/
//LoadFlag Register flags define   
#define  F_LoadCom	0x01		//通讯模式3中下一次分块数据发送为日负荷数据
#define  F_TampCom	0x02  		//通讯模式3中下一次分块数据发送为窃电记录数据
   
//BatState Register flags define   
#define  F_ClockBat	0x01		//时钟电池状态  0:欠压；1：正常 
#define  F_CommBat	0x02		//停抄电池状态   
#define	 F_E2PCheck	0x04		//读三次E2PROM是否正确。0：正确，1：三次校验和均错。	//EC	
   
//ClrFlag Register flags define   
#define  F_ECClr	0x01		//电量清零
#define  F_EventClr	0x02		//事件清零
#define  F_ECClr_EN	0x04		//电量清零使能
#define  F_MSET_EN	0x08		//表号设置使能
#define  F_SSET_EN	0x10		//序列号设置使能
#define  F_Save_EN	0x80		//月第一次上电结算使能
//#define  F_SD16AInit_EN	0x40		//初始计量使能
#define  F_Metertype_EN	0x40		//表类型设置状态

//MDState Register flags define   
#define  F_MDOVER	0x01		//需量超出
//MeterState Register flags define   
#define	 F_RelayState	0x01
#define  F_BatterTest	0x04
 
// 事件记录
#if 0
//////////////////////////////////
#define Cover_No			3	//开盖
#define TCover_No			4	//开端
#define PhAFail_No			0	//A相断相
#define PhBFail_No			1	//B相断相
#define PhCFail_No			2	//C相断相
#endif

#define MagnetOn_No			5	//磁场
#define TimeSET_No			6	//系统时间设置
#define TimeAsynchronous_No		7	//时间异步标志
#define ManipulationRecognized_No	8	//操作


#define	READ	0x8000
#define	WRITE	0x4000
#define	PERMIT	0x2000
#define XPERMIT 0x1000

typedef struct
{
	unsigned int	StatusWord;	//电表运行状态8 Status word
	unsigned char 	Power;
	unsigned char	Clk;
	unsigned char	Disk;
	unsigned char	ClrFlag;
	unsigned char   Key1;
	unsigned char RevState;		//电流反向状态字节 0：不反向，0x01:A相反向, 0x02:B相反向 , 0x04:C相反向
	unsigned char RevOldSte;	//前电流反向状态字节 0：不反向，0x01:A相反向, 0x02:B相反向 , 0x04:C相反向
	unsigned char   AlarmFlg[4];
	

   	unsigned char 	Run0;
   	unsigned char 	Run1;

	unsigned char 	BatState;
	unsigned char 	MDState;
	
	unsigned char	MeterState;	//电表状态
	unsigned char	NetState;	//电网状态
	unsigned char	BautState;
//	unsigned char 	PwDirP;		//有功功率方向
//	unsigned char 	PwDirQ;		//无功功率方向
	unsigned char 	PwDirPQ;	//有功无功功率方向
	unsigned char 	PwDirPQ2;	//有功无功功率方向
	unsigned char 	PwDirPQ3;	//有功无功功率方向	
	unsigned char   FirstFlg;	//第一次事件标志； 0：已记录；1：未记录 //改为三相电流表矢
   	unsigned char 	LoadFlg;
		
    	unsigned char 	ErrFlg;

	unsigned char   Event;
	unsigned char   Key;

	unsigned char 	VolFlg;	//电压失压标志//
	unsigned char 	CurrStar;		
	
	unsigned char Prgtariff;	//费率编程记录标志
	
	unsigned long DoClear ;		
	unsigned long DoClockTest;
} FLAG;

typedef struct
{
	short Init_Flag;		//初始标记	
	unsigned char FeeNo;
	unsigned char CoverOpenState;	//电表开盖状态字节 0：不开盖，0x01:开盖,   
	unsigned char CoverOpenOldSte;	//电表开盖状态字节 0：不开盖，0x01:开盖,
	unsigned char TCoverOpenState;	//电表开端状态字节 0：不开端，0x01:开端,   
	unsigned char TCoverOpenOldSte;	//电表开端状态字节 0：不开端，0x01:开端,   
	unsigned char MeterResetState;	//电表上电状态字节 0：不上电，0x01:上电,   
	unsigned char MeterResetOldSte;	//电表上电状态字节 0：不上电，0x01:上电,   
	unsigned char MagnetOnState;	//电表磁场状态字节 0：磁场不影响，0x01:磁场影响,   
	unsigned char MagnetOnOldSte;	//电表磁场状态字节 0：磁场不影响，0x01:磁场影响, 
	unsigned char PhAFailState;	//电表A相失压状态字节 0：不失压，0x01:A相失压,   
	unsigned char PhAFailOldSte;//电表A相失压状态字节 0：不失压，0x01:A相失压,   
	unsigned char PhBFailState;	//电表B相失压状态字节 0：不失压，0x02:B相失压,   
	unsigned char PhBFailOldSte;//电表B相失压状态字节 0：不失压，0x02:B相失压,   
	unsigned char PhCFailState;	//电表C相失压状态字节 0：不失压，0x04:C相失压,   
	unsigned char PhCFailOldSte;//电表C相失压状态字节 0：不失压，0x04:C相失压, 
	unsigned char MagnetOnStateTime;  
	unsigned char CPUCRC[2];	//CPU代码程序CRC值
	unsigned char CPUCRC_M[2];	//CPU代码程序CRC值
#if 0	
	unsigned long long APowerPulPL;	//上次读取能量值//8207 有功
	unsigned long long BPowerPulPL;
	unsigned long long CPowerPulPL;
	

	unsigned long PowerPp;			//一分钟累计功率（每秒）
   	

	unsigned long	ILoadPulseSumP;	//负荷记录有功脉冲计数器
#endif
#if 0
#if ( Threephase == YesCheck ) //三相
#if (( MEASCHIP == ADE7755 )||( MEASCHIP == RN8207 ))
	unsigned long	IPulseDirSumP;	//总有功判瞬时功率方向中断电量高速脉冲计数器
	unsigned long	IPulseDirSumPA;	//A相总有功判瞬时功率方向中断电量高速脉冲计数器
	unsigned long	IPulseDirSumPB;	//B相总有功判瞬时功率方向中断电量高速脉冲计数器
	unsigned long	IPulseDirSumPC;	//C相总有功判瞬时功率方向中断电量高速脉冲计数器

	unsigned long	IPulseSumP;		//总有功中断电量高速脉冲计数器	   	
	unsigned long	IPulseSumPA;	//A相总有功中断电量高速脉冲计数器	   	
	unsigned long	IPulseSumPB;	//B相总有功中断电量高速脉冲计数器	   	
	unsigned long	IPulseSumPC;	//C相总有功中断电量高速脉冲计数器	
	
	unsigned long	IPulseDirSumPn;	//总有功判瞬时功率方向中断电量高速脉冲计数器
	unsigned long	IPulseDirSumPnA;	//A相总有功判瞬时功率方向中断电量高速脉冲计数器
	unsigned long	IPulseDirSumPnB;	//B相总有功判瞬时功率方向中断电量高速脉冲计数器
	unsigned long	IPulseDirSumPnC;	//C相总有功判瞬时功率方向中断电量高速脉冲计数器

	unsigned long	IPulseSumPn;		//总有功中断电量高速脉冲计数器	   	
	unsigned long	IPulseSumPnA;	//A相总有功中断电量高速脉冲计数器	   	
	unsigned long	IPulseSumPnB;	//B相总有功中断电量高速脉冲计数器	   	
	unsigned long	IPulseSumPnC;	//C相总有功中断电量高速脉冲计数器
	
	
	unsigned long 	SecIPulseSumP;   	
	short	RUaBase;		//A相电压基准
	short RUbBase;		//B相电压基准
	short	RUcBase;		//C相电压基准
	short	RUBaseCheck;	//电能脉冲基准校验和

	unsigned short	RYaBase;		//A相电能脉冲基准
	unsigned short	RYbBase;		//B相电能脉冲基准
	unsigned short	RYcBase;		//C相电能脉冲基准
	unsigned short	RYBaseCheck;	//电能脉冲基准校验和
#endif
#endif
#endif

//	unsigned long 	RRunOverSumTime;	//飞走累计时间		//0701

//	unsigned short 	RUcVolt;		//C相电压AD值，用于相序检测
//	unsigned char 	PhsStata;		//用于相序检测	
//	unsigned char 	PhsCnt;			//用于相序检测	
//	unsigned char 	PhsCnt1;			//用于相序检测	
//	unsigned char 	PhsCnt2;			//用于相序检测
//	unsigned char 	PhsCnt3;			//用于相序检测		

//	int BJGDly;			//背光显示时间
//	int RDisHours;		//停电后显示小时数停 9999永不关闭

// 	int RBatComHours;	//停电后停抄检测维持小时数(3) 	
	short KeyXPushDly;	//X按键按下累计时间，单位1/64秒   大于8秒后触发停抄，大于20秒后不再触发
	//short KeySPushDly;	//Y按键按下累计时间，单位1/64秒   大于8秒后触发停抄，大于20秒后不再触发
//	short KeyDly;

//	int SampleCnt;		//采样点数记数器
//	int Init_Flag;		//初始标记		

//	unsigned short ReadMeasTime;	//定时读计量芯片计数器
	
#if( SecurityCheck == YesCheck )				
	short LabDelay;		//48小时定时
#else
#endif
 	unsigned short PhABCFailState;
#if 0
	unsigned long	MD_CumPp;		//1分钟内有功正向脉冲数
	unsigned long MD_CumPp1;		//1分钟内有功正向脉冲数
	unsigned long MD_CumPp2;		//1分钟内有功正向脉冲数
	unsigned long MD_CumPp3;		//1分钟内有功正向脉冲数
	unsigned long MD_CumPp4;		//1分钟内有功正向脉冲数	

	unsigned long MD_CumPpPR;		
	unsigned long MD_CumPpPpMin;	
	unsigned short MD_CumPpPpMin1;	
	unsigned short MD_CumPpMin[60];		// 15.4.0
#endif	

 	unsigned short PowerA1S;		//读能量时的A相的定时1S//8207
	unsigned short PowerB1S;
	unsigned short PowerC1S;
	unsigned short PowerA1SCnt;		//读能量时的A相的定时1S//
	unsigned short PowerB1SCnt;
	unsigned short PowerC1SCnt;
	unsigned short PowerA1SCnt1[4];		//读能量时的A相的定时1S//
	unsigned short PowerB1SCnt1[4];
	unsigned short PowerC1SCnt1[4];
	unsigned short ReadPowerCnt;

	unsigned char CRESET_ENCnt;		//客户清零使能计时
	
#if ( Threephase == YesCheck ) //三相
#if (( MEASCHIP == ADE7755 )||( MEASCHIP == RN8207 ))
	unsigned char 	SecSumPluse;	//0701
	unsigned char 	SecPluseCnt;	//平均功率计时器	//0701
#endif		
#endif

	unsigned char PowerRev;		//功率反向//0701

#if( SecurityCheck == YesCheck )				
	unsigned char	LabStateCnt;	//有功实验室状态寄存器
	unsigned char	LabState;		//电表实验室状态寄存器
	unsigned char	NewLabState;	//电表实验室新状态寄存器
#else
#endif
	unsigned char 	CalibCnt;		//校表计时
//  BCD2    Wendu;	
//	unsigned char ZoneNo;			//时区号

//总需量缓存区计数器在费率切换时不清零，费率需量缓存区计数器在费率切换时清零
	unsigned char MD_Cunt;		//整分钟计算需量时需要向前调取整分钟脉冲缓存区个数
	unsigned char MD_CuntT;		//整分钟计算费率需量时需要向前调取整分钟脉冲缓存区个数
	unsigned char MD_BufAds;	//当前需量缓存区地址
	
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


	unsigned short YPulse_Cum;//绝对值
	unsigned short YPulse_CumAL;//代数和
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
	
	unsigned char StateFailState;	//电表C相失压状态字节 0：不失压，0x04:C相失压,   
	unsigned char StateFailOldSte;//电表C相失压状态字节 0：不失压，0x04:C相失压,   
	
	unsigned char FeeNoDelay;
  unsigned char RelayState;	//继电器状态		
	unsigned char MDPCT;		//整个需量周期内完成需量滑差时间次数：滑差片数
	unsigned char MD_PCT;		//滑差片数计数器	
	unsigned char MDPMinCT;		//需量滑差时间内分钟计数器
	unsigned char MD_60T;		//60分钟/需量周期
#if 0
	unsigned char PulWidthled;			//脉冲宽度//
	unsigned char PulWidthS0;			//脉冲宽度//

	unsigned int Constled;	//LED脉冲常数14.2.9wwl
	unsigned int Consts0;	//s0脉冲常数
	unsigned char Tariffsnu;	//费率数
	

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
	
	unsigned char ENCount;		//编程使能
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
	unsigned char ECFlashDly;		//"电量"闪烁定时
	unsigned char FeeNoTestCnt;		//"电量"闪烁定时	

	unsigned char TestDisCnt;  
  unsigned char TestDisCntButton;  
	unsigned char RDisDays;			//停电后显示小时数(6天=144小时) 
	unsigned char RAwakeDisDays;	//停电唤醒支持时间  //V30
	
	unsigned short PoffPassword;	//停电后计时用

    unsigned char PowerUpTime;
    unsigned char BatUpTime;
 	unsigned char RECMode;			//0:代数和，1:绝对值 参数	
 	unsigned char OldRECMode;		//电表当前计量方式  0:代数和，1:绝对值
//	unsigned char PassWd_ErrCnt;
#if 0
	unsigned char ECPulseWidthCnt;
	unsigned char PulseWidthCnt;
    unsigned char RPulseOutMode;
//    unsigned char SecPulseCnt;		//秒脉冲记数 
//    unsigned char MDResetForbid;
    unsigned char ErrPhsCunt;		//逆相序滤波计数器
    unsigned char HWBGDelay;
//    unsigned char ADTimeCnt;		//AD采样时间间隔(以250us为单位)
//	unsigned char AmperOverDelay;	//过载检测延时时间
	unsigned char RevDelay;			//电流反向检测延时时间
	unsigned char ECRevDelay;		//电能反向检测延时时间
	unsigned char ADSampleMode;		//AD采样模式  0：有电流采样；1：只采样电池电压
//	unsigned char ADChannelNo;		//AD采样通道号
	unsigned char DataRomoveMode;
#endif	
	unsigned char ECLedModeCnt;		//有功脉冲灯显示模式计时
	
	unsigned char Load_time;	
	unsigned char SD16ACount;//上电初始计量时间
	
	unsigned char setkey_sum;
	unsigned char menustep;
	
	unsigned char menustep1;	//模式
	unsigned char menustep2;	//done	
	unsigned char menustep3;	//set time 
	unsigned char menustep4;	//时钟设置时候长按键标志 
	
	unsigned char Key_Map;
	unsigned char PrgKeyState;
	unsigned char ErrCode;
	unsigned char RollItemPt;
	unsigned char BatteryWTime[5];
	unsigned char TestCnt;	//testmode 定时3小时

	unsigned char Testram[10];		//液晶PIN_CODE输入
	unsigned char Testram11[10];  //液晶PIN_CODE
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
#if ( Threephase == YesCheck ) //三相		
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

// 	ZjState					// 浙江省通讯规约处理过程状态
#define zjIdle			0	// 通讯空闲
#define zjBufBusy		1	// 开始收数据，通讯缓存忙
#define zjRead			2	// 收完数据
#define zjDataSend1Wait	3	// 数据包1发送等待
#define zjDataSend2		4	// 数据包2发送
#define zjDataSend2Wait	5	// 数据包2发送等待
#define zjDataSend3		6	// 数据包3发送
#define zjDataSend3Wait	7	// 数据包3发送等待
#define zjDataSend4		8	// 数据包4发送
#define zjDataSend4Wait	9	// 数据包4发送等待
#define zjExit			10	// 通讯退出

//Comm.State1 
#define ATT7053Set	0x01	//ATT7053设置
#define ATT7053Read	0x02	//ATT7053读取
#define ATT7053CommOK	0x04	//ATT7053通信成功

	// Run flags define
#define  FComOK0   0x01		//串口0操作完毕标志(发送或接收)
#define  FComOK1   0x02		//串口1操作完毕标志(发送或接收)
#define  FComOK2   0x04		//串口2操作完毕标志(发送或接收)
#define  FComOK3   0x08		//串口3操作完毕标志(发送或接收)
	// INFORunFlag flags define
#define  FStatu_One   0x01		//statu one byte

typedef struct
{  	
	uint32_t	SecPulseCnt;			//上电秒计时
	uint32_t	TimeSecPulseCnt;		//EDL40时间秒计时
	uint16_t	CRCRegInit;		//infor CRC	
	uint16_t	CRCEventInit;		//event CRC	
	uint16_t 	BTime3;				// 485口3字符间定时
	uint16_t 	BTime2;				// 485口3字符间定时
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

//8207的Uart通信//
typedef struct
{
	unsigned char NeedRecCnt;			//需要接收的数据长度//
	unsigned char NeedSendCnt;		//需要发送的长度//
	unsigned char RecBuf8207[10];	//接收缓冲区//
	unsigned char SendBuf8207[10];	//发送缓冲区//
	unsigned char PhaType;			//相别，1=A相，2=B相，3=C相//
	unsigned char CommOk;			//通信完成标志，0X55=通信完成//
	unsigned char Ptr8207;			//8207通信时的指针//
	unsigned short CommDly;			//通信定时，超过这个时间表明通信出错//
	unsigned char ReadPowerState;
	
}COMM8207;

typedef struct
{
	unsigned char *Buf;				// 通讯缓存器
	unsigned char *Buf2;			// 通讯缓存器2
	unsigned char *Mode;			// 通讯模式
	unsigned char *State;			// 通讯状态	
	unsigned char *Ptr;				// 缓存器指针
	unsigned char *BTime;			// 字符间定时
 	unsigned char *Bcc;				//发送数据校验和 
	unsigned char *RecTmr;			// 接收记录延时
	unsigned char *PrgTmr;			// 编程记录延时
	unsigned char *Run;				// 运行标志 
	unsigned char *TXLAST_Delay;
  unsigned char *Delay;
}COMMPARA;

typedef struct
{
	unsigned long  *LoadPtr;			// 负荷数据通讯标志		
	long  *LoadPtrend;			// 负荷数据通讯结束指针	
	unsigned char *BlockNo;			//发第几块数据（用在分块发送）
	unsigned char *SendLen;			//发送长度（用在分块发送）
//	unsigned char *HisMonth;		//读第几月的历史数据
//	unsigned char *EventCode;		//读那条事件
	unsigned char *ProfDate;		//负荷曲线起始、结束时间 
//	unsigned char *Top10;			//发送TOP10时的指针	
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
//	unsigned char 	*Buf;			// 通讯缓存器
//	unsigned char 	*Mode;			// 部规约通讯模式
//  	unsigned char 	*Ptr;			// 缓存器指针
//  	unsigned int 	*BTime;			// 字符间定时
//  	unsigned char 	*SendDTime;		// 发送延时
//}COMMPARA;

#if( ZjProtocol	== YesCheck )		// 有浙江通讯规约
typedef struct
{
	unsigned char 	*Buf;			// 通讯缓存器
	unsigned char 	*Mode;			// 部规约通讯模式
  	unsigned char 	*Ptr;			// 缓存器指针
  	unsigned short 	*BTime;			// 字符间定时
  	unsigned char 	*SendDTime;		// 发送延时
	unsigned char	*ZjState;		// 浙江规约通讯状态
	unsigned char	*ZjLength;		// 浙江规约每包数据发送长度
	unsigned char	*ZjCheck;		// 浙江规约每包数据校验和
}ZJCOMMPARA;
#else
#endif

typedef struct
{
//	unsigned short 	MDBufAds;		// 需量缓存区首址
//	unsigned short 	*MDCum;			// 1分钟累计脉冲数
#if ( Threephase == YesCheck ) //三相		
	unsigned long 	*MDCum;			// 1分钟累计脉冲数
#else
	unsigned long 	*MDCum;			// 1分钟累计脉冲数
#endif
	
}MDPARA;

//typedef struct
//{
//	unsigned long* 	SampleSum;		// n个周期内采样点数的累加和
//	unsigned char* 	Irms;			// 相电流有效值
//}IRMSPARA;

typedef struct
{
	unsigned short 	ECAddr;			//季节冻结首址
  	unsigned short 	EnterDay;		//进入季节日期
	unsigned short	OutDay;			//退出季节日期
	unsigned char*  ZoneNo;			//当前时区号
}SEASONPARA;

typedef struct
{
	unsigned char 	ADERgAddr;		//7758寄存器地址
  	unsigned char 	Length;			//寄存器字节长度
}ADEPara;

typedef struct
{
	unsigned char*  RamRgAddr;		//瞬时值RAM地址		
	unsigned char 	ATTRgAddr;		//ATT7022寄存器地址
  	unsigned char 	Length;			//寄存器字节长度
}RamPara;

typedef struct
{
	short CommID;		//通讯编码
	short Length;		//块长度
  	short Cycle;		//块数量
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
}I2CPARA;							//I2C接口芯片在CPU上的IO口配置参数

typedef struct
{
	unsigned char RegAddr;
	unsigned char Length;
}MEASREG;

typedef struct
{
	unsigned long	long ABCPowerPulSum;	//三相的用来发脉冲的能量的累计和//绝对值
	unsigned long	long APowerPulSum;	//A相的用来发脉冲的能量的累计和//
	unsigned long	long BPowerPulSum;	//B相的用来发脉冲的能量的累计和//
	unsigned long	long CPowerPulSum;	//C相的用来发脉冲的能量的累计和//
	
//	unsigned long APowerPulPP;	//A相用来发脉冲的已乘上校表参数后的正向数据中断中用//
//	unsigned long BPowerPulPP;	//B相用来发脉冲的已乘上校表参数后的正向数据中断中用//
//	unsigned long CPowerPulPP;	//C相用来发脉冲的已乘上校表参数后的正向数据中断中用//
//	
//	unsigned char APower[4];	//A相功率数组//
//	unsigned char BPower[4];	//B相功率数组//
//	unsigned char CPower[4];	//C相功率数组//
//	unsigned long ABCPower;	//ABC相功率数组//
	unsigned long APowerPulP;	//A相用来发脉冲的已乘上校表参数后的正向数据//
	unsigned long BPowerPulP;	//B相用来发脉冲的已乘上校表参数后的正向数据//
	unsigned long CPowerPulP;	//C相用来发脉冲的已乘上校表参数后的正向数据//
	unsigned long ABCPowerPulP;	//三相用来发脉冲的已乘上校表参数后的正向数据//

	unsigned long APowerPulPBak;	//A相用来发脉冲的已乘上校表参数后的正向上次数据//
	unsigned long BPowerPulPBak;	//B相用来发脉冲的已乘上校表参数后的正向上次数据//
	unsigned long CPowerPulPBak;	//C相用来发脉冲的已乘上校表参数后的正向上次数据//


//	unsigned long APowerPulN;	//A相用来发脉冲的已乘上校表参数后的负向数据//
//	unsigned long BPowerPulN;	//B相用来发脉冲的已乘上校表参数后的负向数据//
//	unsigned long CPowerPulN;	//C相用来发脉冲的已乘上校表参数后的负向数据//
//	unsigned long ABCPowerPulN;	//三相用来发脉冲的已乘上校表参数后的负向数据//
//
//	unsigned long APowerPulNBak;	//A相用来发脉冲的已乘上校表参数后的负向上次数据//
//	unsigned long BPowerPulNBak;	//B相用来发脉冲的已乘上校表参数后的负向上次数据//
//	unsigned long CPowerPulNBak;	//C相用来发脉冲的已乘上校表参数后的负向上次数据//

//	unsigned char FlagDireABC;	//ABC三相的方向//
//	unsigned char ModePN;	//计量方式//
//
//
//	unsigned char AAdjust[2];	//A相校表参数数组//
//	unsigned char BAdjust[2];	//B相校表参数数组//
//	unsigned char CAdjust[2];	//C相校表参数数组//
//	
//	unsigned char AdjustSum[2];	//校表参数校验和//

	unsigned char	AStartM;
	unsigned char	BStartM;
	unsigned char	CStartM;
	
//	unsigned char	AReadErrCnt;//读8207出错的次数，当三次都出错时，当芯片没上电，用作计量的值清0//
//	unsigned char	BReadErrCnt;
//	unsigned char	CReadErrCnt;
//        
  	unsigned char	MeaOneA;//判断某相失压用在15毫秒内判有几个高的//
	unsigned char	MeaOneB;
	unsigned char	MeaOneC;
	unsigned char 	PulWidth;				//脉冲宽度//
	unsigned char 	PulS0Width;				//脉冲宽度//
	
}MEASURE7053;	

#define	F_ADire		0x01		//A相的方向//
#define	F_BDire		0x02		//B相的方向//
#define	F_CDire		0x04		//C相的方向//
#define	F_ABCDire	0x08		//合相的方向//

typedef struct
{
	unsigned long long ABCPowerPulSum;	//三相的用来发脉冲的能量的累计和//
	unsigned long long ABCPowerPulSumAL;	//三相的用来发脉冲的能量的累计和//代数和
	unsigned long long APowerPulSum;	//A相的用来发脉冲的能量的累计和//
	unsigned long long BPowerPulSum;	//B相的用来发脉冲的能量的累计和//
	unsigned long long CPowerPulSum;	//C相的用来发脉冲的能量的累计和//
	
	unsigned long long ABCRPowerPulSum;	//三相的用来发脉冲的能量的累计和//
	
	unsigned long long PhAPower; 	//A相功率	从寄存器读出的值
	unsigned long long PhBPower;	//B相功率	从寄存器读出的值
	unsigned long long PhCPower;	//C相功率	从寄存器读出的值
	
	unsigned long ABCPower;	//ABC相功率数组//
	unsigned long APowerPulP;	//A相用来发脉冲的已乘上校表参数后的正向数据//
	unsigned long BPowerPulP;	//B相用来发脉冲的已乘上校表参数后的正向数据//
	unsigned long CPowerPulP;	//C相用来发脉冲的已乘上校表参数后的正向数据//
	unsigned long ABCPowerPulP;	//三相用来发脉冲的已乘上校表参数后的正向数据//
	unsigned long ABCPowerPulPAL;	//三相用来发脉冲的已乘上校表参数后的正向数据//

	unsigned long APowerPulPBak;	//A相用来发脉冲的已乘上校表参数后的正向上次数据//
	unsigned long BPowerPulPBak;	//B相用来发脉冲的已乘上校表参数后的正向上次数据//
	unsigned long CPowerPulPBak;	//C相用来发脉冲的已乘上校表参数后的正向上次数据//
	
	unsigned long AnPowerPulPBak;	//A相用来发脉冲的已乘上校表参数后的正向上次数据//
	unsigned long BnPowerPulPBak;	//B相用来发脉冲的已乘上校表参数后的正向上次数据//
	unsigned long CnPowerPulPBak;	//C相用来发脉冲的已乘上校表参数后的正向上次数据//

	unsigned long APowerPulN;	//A相用来发脉冲的已乘上校表参数后的负向数据//
	unsigned long BPowerPulN;	//B相用来发脉冲的已乘上校表参数后的负向数据//
	unsigned long CPowerPulN;	//C相用来发脉冲的已乘上校表参数后的负向数据//
	unsigned long ABCPowerPulN;	//三相用来发脉冲的已乘上校表参数后的负向数据//

	unsigned long APowerPulNBak;	//A相用来发脉冲的已乘上校表参数后的负向上次数据//
	unsigned long BPowerPulNBak;	//B相用来发脉冲的已乘上校表参数后的负向上次数据//
	unsigned long CPowerPulNBak;	//C相用来发脉冲的已乘上校表参数后的负向上次数据//

	unsigned long APowerPulPP;	//A相用来发脉冲的已乘上校表参数后的正向数据中断中用//
	unsigned long BPowerPulPP;	//B相用来发脉冲的已乘上校表参数后的正向数据中断中用//
	unsigned long CPowerPulPP;	//C相用来发脉冲的已乘上校表参数后的正向数据中断中用//
	
	unsigned char FlagDireABC;	//ABC三相的方向//
	unsigned char FlagDireABCn;	//ABC三相的方向//
	unsigned char ModePN;	//计量方式//
	
	unsigned long ABCPowern;	//ABC相功率数组//
	unsigned long APowerPulPn;	//A相用来发脉冲的已乘上校表参数后的正向数据//
	unsigned long BPowerPulPn;	//B相用来发脉冲的已乘上校表参数后的正向数据//
	unsigned long CPowerPulPn;	//C相用来发脉冲的已乘上校表参数后的正向数据//
	unsigned long ABCPowerPulPn;	//三相用来发脉冲的已乘上校表参数后的正向数据//
	
	unsigned long APowerPulPPn;	//A相用来发脉冲的已乘上校表参数后的正向数据中断中用//
	unsigned long BPowerPulPPn;	//B相用来发脉冲的已乘上校表参数后的正向数据中断中用//
	unsigned long CPowerPulPPn;	//C相用来发脉冲的已乘上校表参数后的正向数据中断中用//
	
//	unsigned char APower[4];	//A相功率数组//
//	unsigned char BPower[4];	//B相功率数组//
//	unsigned char CPower[4];	//C相功率数组//

	unsigned char AAdjust[2];	//A相校表参数数组//
	unsigned char BAdjust[2];	//B相校表参数数组//
	unsigned char CAdjust[2];	//C相校表参数数组//
	
	unsigned char AdjustSum[2];	//校表参数校验和//
	
	unsigned char AStartM;
	unsigned char BStartM;
	unsigned char CStartM;
	
	unsigned char AReadErrCnt;//读8207出错的次数，当三次都出错时，当芯片没上电，用作计量的值清0//
	unsigned char BReadErrCnt;
	unsigned char CReadErrCnt;
	              
	unsigned char AReadOKCnt;//初始8207的次数，当三次都正常时，当芯片上电，用作计量的值//
	unsigned char BReadOKCnt;
	unsigned char CReadOKCnt;
                  
//  unsigned char AVolCnt;//判断某相失压用在15毫秒内判有几个高的//
//	unsigned char BVolCnt;
//	unsigned char CVolCnt;
                  
  	unsigned char MeaOneA;//判断某相失压用在15毫秒内判有几个高的//
	unsigned char MeaOneB;
	unsigned char MeaOneC;
	unsigned char PulWidth;			//脉冲宽度//
	unsigned char PulS0Width;			//脉冲宽度//
	unsigned char PhARPWRCnt;		//A相读能量次数
	unsigned char PhBRPWRCnt;		//B相读能量次数
	unsigned char PhCRPWRCnt;		//C相读能量次数	
	unsigned char RPulWidth;			//脉冲宽度//	
}MEASURE8207;


typedef struct
{
	int flag;
	unsigned char PubKey_X[25];//公共密钥X//
	unsigned char PubKey_Y[25];//公共密钥Y//
	unsigned char Pri_Key[25];//私人密钥//
	char message[50];
	char hashmessage[50];
	char sign_rs[100];
//	unsigned int MSBNeedSendLg;//MSB需要发送长度//
//	unsigned char MSBTime;//MSB时间//
//	unsigned char Flag;//解析标志//
//	unsigned char	EndNum;
		
}SIGNATURE;
//双核的Uart通信//
typedef struct
{
	unsigned char NeedRecCnt;			//需要接收的数据长度//
	unsigned char NeedSendCnt;		//需要发送的长度//
	unsigned char RecBuf8213[32];	//接收缓冲区//
	unsigned char SendBuf8213[32];	//发送缓冲区//
	unsigned char PhaType;			//相别，1=A相，2=B相，3=C相//
	unsigned char CommOk;			//通信完成标志，0X55=通信完成//
	unsigned char Ptr8213;			//8207通信时的指针//
	unsigned short CommDly;			//通信定时，超过这个时间表明通信出错//
	unsigned char ReadPowerState;
	
}COMM8213;

 typedef struct
 {
	u16  DataID;		 //ID码
	unsigned char	 Logical_Name[6];
	unsigned char	 len;
 } ID_OBIS;
#endif







