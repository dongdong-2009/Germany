/*******************************************************************
	Display format define table
*******************************************************************/

/* Static Display Infomation */
/*
// Cum bit
#define D_Cum       	0x8000		// Cum

// Dot Display
#define D_Dot       	0x7000

#define D_Dot0			0*0x1000
#define D_Dot1			1*0x1000
#define D_Dot2			2*0x1000
#define D_Dot3			3*0x1000
#define D_Dot4			4*0x1000

// Display Mon
#define D_LM	    	0x0800   	// Prev

// Data type
#define D_Type		   0x0700

#define D_Num			0*0x0100		// 数据
#define D_EC			1*0x0100   	// 电量(dot0,1,2)
#define D_MD			2*0x0100   	// 需量(dot0,1,2,3,4)，MD
#define D_MDTM			3*0x0100   	// 需量发生时间，MD, Time
#define D_Date			4*0x0100   	// 日期, Date
#define D_Time			5*0x0100   	// 时间, Time

// Display Dir
#define D_Dir			0x0080

#define D_Rp      	0x0000
#define D_Rn      	0x0080		// Resv

// Display Fee
#define D_Fee	    	0x0070

#define D_F0    		1*0x0010   // Total
#define D_F1         2*0x0010   // 尖, Tarrif 1
#define D_F2         3*0x0010   // 峰, Tarrif 2
#define D_F3         4*0x0010   // 平, Tarrif 3
#define D_F4         5*0x0010   // 谷, Tarrif 4

#define D_Rst			6*0x0010   // Reset
#define D_Cont			7*0x0010   // Const

// Display Unit
#define D_Unit			0x000F

#define D_kWh        1*0x0001
#define D_MWh        2*0x0001
#define D_kvarh      3*0x0001
#define D_Mvarh      4*0x0001
#define D_kVAh       5*0x0001
#define D_MVAh       6*0x0001
#define D_kW         7*0x0001
#define D_MW         8*0x0001
#define D_kvar       9*0x0001
#define D_Mvar       10*0x0001
#define D_kVA        11*0x0001
#define D_MVA        12*0x0001
#define D_V      		13*0x0001
#define D_A        	14*0x0001
#define D_Hz       	15*0x0001
*/
/* Active Display Infomation */
/*
// Display A B C phase
#define D_Ph         0x70
#define D_PhA        0x10
#define D_PhB        0x20
#define D_PhC        0x40
#define D_PhAB       0x30
#define D_PhAC       0x50
#define D_PhBC       0x60
#define D_PhABC      0x70

// display lenth
#define D_Len        0x0007
#define D_Len1       0x0001
#define D_Len2       0x0002
#define D_Len3       0x0003
#define D_Len4       0x0004
#define D_Len5       0x0005
#define D_Len6       0x0006
#define D_Len7       0x0007

// Repeat type
#define D_RptType    0xF000
#define D_RptNorm    0x0000
#define D_RptTam     0x1000
#define D_RptLoad    0x2000

#define D_RptNum     0x0FFF

*/
/*
#define	D_Sa0	0x01     //时间
#define	D_Sa1	0x02     //华立商标
#define	D_Sa2	0x04     //COS
#define	D_Sa3	0x08     ///O/
#define	D_Sa4	0x10		//O
#define	D_Sa5	0x20		//A1  
#define	D_Sa6	0x40		//A4
#define	D_Sa7	0x80		//Hz

#define	D_Sb0	0x01		//A10
#define	D_Sb1	0x02		//A9
#define	D_Sb2	0x04		//A8
#define	D_Sb3	0x08		//A7
#define	D_Sb4	0x10		//A3
#define	D_Sb5	0x20		//A2
#define	D_Sb6	0x40		//A5
#define	D_Sb7	0x80		//A6

#define	D_Sc0	0x01       	//N
#define	D_Sc1	0x02	        //C
#define	D_Sc2	0x04   	        //B
#define	D_Sc3	0x08   	        //A

//华立液晶
#define NewDs	0x80		//有电状态下该项随时刷新
#define Digit0	0x00		//0位小数
#define Digit1	0x10		//1位小数
#define Digit2	0x20		//2位小数
#define Digit3	0x30		//3位小数
#define Digit4	0x40		//4位小数

//显示数据长度字节数

#define Len1	0x01		//1字节
#define	Len2	0x02		//2字节
#define	Len3	0x03		//3字节
#define	Len4	0x04		//4字节
#define	Len5	0x05		//5字节
#define	Len6	0x06		//6字节
*/

//新三相分时表液晶
/*
#define	D_Sa0	0x01     	//时
#define	D_Sa1	0x02     	//间
#define	D_Sa2	0x04     	//段
#define	D_Sa3	0x08     	//表号
#define	D_Sa4	0x10		//KW1
#define	D_Sa5	0x20		//H1 
#define	D_Sa6	0x40		//KW2
#define	D_Sa7	0x80		//H2

#define	D_Sc0	0x01		//失
#define	D_Sc1	0x02		//压
#define	D_Sc2	0x04		//流
#define	D_Sc3	0x08		//V
#define	D_Sc4	0x10		//量
#define	D_Sc5	0x20		//电
#define	D_Sc6	0x40		//需
#define	D_Sc7	0x80		//月

#define	D_Sb0	0x01		//尖
#define	D_Sb1	0x02		//峰
#define	D_Sb2	0x04		//平
#define	D_Sb3	0x08		//谷
#define	D_Sb4	0x10		//反向
#define	D_Sb5	0x20		//当前
#define	D_Sb6	0x40		//上
#define	D_Sb7	0x80		//总

#define	D_Sd0	0x01		//15A
#define	D_Sd1	0x02		//15B
#define	D_Sd2	0x04		//15C
#define	D_Sd3	0x08		//16BC
#define	D_Sd4	0x10		//15F
#define	D_Sd5	0x20		//15G
#define	D_Sd6	0x40		//15E
#define	D_Sd7	0x80		//15D

#define	Mpara	0x1000		//参数
#define	Mpwtm	0x2000		//需量、需量时间
#define	Mbcod	0x3000		//表号
#define	Mdate	0x4000		//年、月、日
#define	Mbpas	0x5000		//常数
#define	Mseg	0x6000		//时段
#define	Mtest	0x7000		//全屏测试显示
#define	Mua		0x8000		//电压、电流
*/


//32位位定义
#define   BBIT31 	0x80000000		
#define   BBIT30 	0x40000000		
#define   BBIT29 	0x20000000		
#define   BBIT28 	0x10000000		
#define   BBIT27 	0x08000000		
#define   BBIT26 	0x04000000		
#define   BBIT25 	0x02000000		
#define   BBIT24 	0x01000000		
#define   BBIT23 	0x00800000		
#define   BBIT22 	0x00400000		
#define   BBIT21 	0x00200000		
#define   BBIT20 	0x00100000		
#define   BBIT19	0x00080000		
#define   BBIT18 	0x00040000		
#define   BBIT17 	0x00020000		
#define   BBIT16 	0x00010000	
#define   BBIT15	0x00008000		
#define   BBIT14 	0x00004000		
#define   BBIT13 	0x00002000		
#define   BBIT12 	0x00001000	
#define   BBIT11	0x00000800		
#define   BBIT10 	0x00000400		
#define   BBIT9 	0x00000200		
#define   BBIT8 	0x00000100	
#define   BBIT7	0x00000080		
#define   BBIT6 	0x00000040		
#define   BBIT5 	0x00000020		
#define   BBIT4 	0x00000010	
#define   BBIT3	0x00000008		
#define   BBIT2 	0x00000004		
#define   BBIT1 	0x00000002		
#define   BBIT0 	0x00000001	


//浙江统一表3485液晶

#define	D_Sa0	0x01     	//上
#define	D_Sa1	0x02     	//当前
#define	D_Sa2	0x04     	//C
#define	D_Sa3	0x08     	//<-
#define	D_Sa4	0x10		//上月
#define	D_Sa5	0x20		//A 
#define	D_Sa6	0x40		//B
#define	D_Sa7	0x80		//

#define	D_Sb0	0x01		//需
#define	D_Sb1	0x02		//电
#define	D_Sb2	0x04		//量
#define	D_Sb3	0x08		//压
#define	D_Sb4	0x10		//逆相序
#define	D_Sb5	0x20		//局号
#define	D_Sb6	0x40		//时间
#define	D_Sb7	0x80		//流

#define	D_Sc0	0x01		//KW
#define	D_Sc1	0x02		//h
#define	D_Sc2	0x04		//V
#define	D_Sc3	0x08		//A
#define	D_Sc4	0x10		//imp/
#define	D_Sc5	0x20		//
#define	D_Sc6	0x40		//
#define	D_Sc7	0x80		//

#define	DisE2P	0x40		//EEPROM
#define	DisFLA	0x80		//FLASH
#define	DisROM	0xC0		//ROM


#define	Mpara	0x10		//参数
#define	Muec	0x20		//上月电量等
#define	Mdate	0x30		//年、月、日
#define	Mtime	0x40		//时分秒
#define	Mtari	0x50		//时段方案名称
#define	Mua		0x60		//电压、电流
#define	Mpmax	0x70		//最大需量
#define	MpCRC	0x80             //CRC
//#define	Mpsum	0x80
#define	MpIns	0x90		//功率
#define	MFull	0xA0		//全屏
#define	Mperr	0xB0		//读写E2错误
#define	MpInsF	0xC0		//分相功率
#define	Mvbat	0xD0		//电池电压
#define	MTbat	0xE0		//电池工作时间
#define	Mevent	0xF0		//事件次数

//#define	Mpara	0x10		//参数
//#define	Muec	0x20		//上月电量等
//#define	Mdate	0x30		//年、月、日
//#define	Mtime	0x40		//时分秒
//#define	Mperr	0x50		//开盖、端标志
//#define	Mua		0x60		//电压、电流
//#define	Mpjscnt	0x70		//结算次数
//#define	Mperr1	0x80		//读写E2错误
//#define	MFull	0x90		//全屏


//#define	Mbcod	0x3000		//表号
//#define	Mbpas	0x5000		//常数
//#define	Mseg	0x6000		//时段


/*
 #if ( Lcd8com == YesCheck )  
#define DS_BDig		18//9
 #else	  
#define DS_BDig		6//9
#endif
*/
#define DS_BDig		0//0//9

#define MenuItem	0
#define ClockItem	4
#define EobItem		4+6
#define	ClrSucItem	4+6+5
#define	ConstInv	8
//显示数据长度字节数

#define Len1	0x01		//1字节
#define	Len2	0x02		//2字节
#define	Len3	0x03		//3字节
#define	Len4	0x04		//4字节
#define	Len5	0x05		//5字节
#define	Len6	0x06		//6字节
#define	Len7	0x07		//7字节
#define	Len8	0x08		//8字节
#define	Len9	0x09		//9字节
#define	Len10	0x0a		//10字节
#define	Len11	0x0b		//11字节

//*******************************************************************
// LCD character bitmap
//          0                a
//        -----            -----
//       |     |          |     |
//      4|     |1        f|     |b
//       |  5  |          |  g  |
//        -----            -----
//       |     |          |     |
//      6|     |2        e|     |c
//       |  7  |          |  d  |
//        -----  *3        -----  *dp
//*******************************************************************
/*华立液晶							//	dcbahegf
#define DS_Chr_0     0xF5 // 0: 11110101b
#define DS_Chr_1     0x60 // 1: 01100000b
#define DS_Chr_2     0xB6 // 2: 10110110b
#define DS_Chr_3     0xF2 // 3: 11110010b
#define DS_Chr_4     0x63 // 4: 01100011
#define DS_Chr_5     0xD3 // 5: 
#define DS_Chr_6     0xD7 // 6: 
#define DS_Chr_7     0x70 // 7: 
#define DS_Chr_8     0xF7 // 8: 
#define DS_Chr_9     0xF3 // 9: 
#define DS_Chr_A     0x77 // A: 
#define DS_Chr_b     0xC7 // B: 
#define DS_Chr_C     0x95 // C: 
#define DS_Chr_d     0xE6 // D: 
#define DS_Chr_E     0x97 // E: 
#define DS_Chr_F     0x17 // F: 

#define DS_Chr_Dot   0x08 // .: 
#define DS_Chr_Neg   0x02 // -: 
#define DS_Chr_c     0x86 // c: 
#define DS_Chr_h     0x47 // h: 
#define DS_Chr_H     0x67 // H: 
#define DS_Chr_L     0x95 // C: 
#define DS_Chr_o     0xC6 // o: 
#define DS_Chr_P     0x37 // P: 
#define DS_Chr_N     0x75 // N: 
#define DS_Chr_n     0x46 // n: 
#define DS_Chr_r     0x06 // r: 

*/

/*
//新三相分时表液晶		
#define	DS_a	0x01
#define	DS_b	0x02
#define	DS_c	0x04
#define	DS_d	0x80
#define	DS_e	0x40
#define	DS_f	0x10
#define	DS_g	0x20
#define	DS_h	0x08
*/

/*
//三相表液晶3485		
#define	DS_a	0x08//0x10
#define	DS_b	0x80//0x20
#define	DS_c	0x20//0x40
#define	DS_d	0x01//0x08
#define	DS_e	0x02//0x04
#define	DS_f	0x04//0x01
#define	DS_g	0x40//0x02
#define	DS_h	0x10//0x80
*/

//单相表液晶5891		
//#define	DS_a	0x01//0x10//0x10
//#define	DS_b	0x02//0x20//0x20
//#define	DS_c	0x04//0x40//0x40
//#define	DS_d	0x08//0x80//0x08
//#define	DS_e	0x40//0x04//0x04
//#define	DS_f	0x10//0x01//0x01
//#define	DS_g	0x20//0x02//0x02
//#define	DS_h	0x80//0x08//0x80
/*
#define		LNumb_a		0x01
#define		LNumb_b		0x02
#define		LNumb_c		0x04
#define		LNumb_d		0x80
#define		LNumb_e		0x40
#define		LNumb_f		0x10
#define		LNumb_g		0x20
*/


//#define	DS_a	0x01//0x10//0x10
//#define	DS_f	0x02//0x01//0x01
//#define	DS_e	0x04//0x04//0x04
//#define	DS_d	0x08//0x80//0x08
//#define	DS_b	0x10//0x20//0x20
//#define	DS_g	0x20//0x02//0x02
//#define	DS_c	0x40//0x40//0x40
//#define	DS_h	0x80//0x08//0x80


#if ( Threephase == YesCheck ) //三相	

#define		DS_a		0x01
#define		DS_b		0x04
#define		DS_c		0x40
#define		DS_d		0x20
#define		DS_e		0x80
#define		DS_f		0x02
#define		DS_g		0x08
#define		DS_h		0x10


#elif ( SinglePhase== YesCheck ) //单相	
 
#define		DS_a		0x01
#define		DS_b		0x02
#define		DS_c		0x04
#define		DS_d		0x80
#define		DS_e		0x40
#define		DS_f		0x10
#define		DS_g		0x20
#define		DS_h		0x08

#endif


#define Unit_Kw	 	DS_a
#define Unit_Kva	 	DS_b
#define Unit_h	 	DS_g
#define Unit_V	 	DS_c
#define Unit_A	 	DS_d



#define DS_Chr_0     DS_a+DS_b+DS_c+DS_d+DS_e+DS_f		// 0:
#define DS_Chr_1     DS_b+DS_c 							// 1:	
#define DS_Chr_2     DS_a+DS_b+DS_d+DS_e+DS_g 			// 2:
#define DS_Chr_3     DS_a+DS_b+DS_c+DS_d+DS_g			// 3:
#define DS_Chr_4     DS_b+DS_c+DS_f+DS_g 				// 4: 
#define DS_Chr_5     DS_a+DS_c+DS_d+DS_f+DS_g 			// 5: 
#define DS_Chr_6     DS_a+DS_c+DS_d+DS_e+DS_f+DS_g 		// 6: 
#define DS_Chr_7     DS_a+DS_b+DS_c 					// 7: 
#define DS_Chr_8     DS_a+DS_b+DS_c+DS_d+DS_e+DS_f+DS_g // 8: 
#define DS_Chr_9     DS_a+DS_b+DS_c+DS_d+DS_f+DS_g 		// 9: 
#define DS_Chr_A     DS_a+DS_b+DS_c+DS_e+DS_f+DS_g 		// A: 
#define DS_Chr_b     DS_c+DS_d+DS_e+DS_f+DS_g 			// b: 
#define DS_Chr_C     DS_a+DS_d+DS_e+DS_f 				// C: 
#define DS_Chr_d     DS_b+DS_c+DS_d+DS_e+DS_g 			// d: 
#define DS_Chr_E     DS_a+DS_d+DS_e+DS_f+DS_g 			// E: 
#define DS_Chr_F     DS_a+DS_e+DS_f+DS_g 				// F: 

#define DS_Chr_J     DS_b+DS_c+DS_d+DS_e 				// J: 
#define DS_Chr_t     DS_f+DS_g+DS_d+DS_e 				// J: 
#define DS_Chr_y	 DS_b+DS_c+DS_d+DS_f+DS_g
#define DS_Chr_Dot   DS_h 						// .: 
#define DS_Chr_Neg   DS_g 						// -: 
#define DS_Chr_c     DS_d+DS_e+DS_g 			// c: 
#define DS_Chr_h     DS_c+DS_e+DS_f+DS_g 		// h: 
#define DS_Chr_H     DS_b+DS_c+DS_e+DS_f+DS_g 	// H: 
#define DS_Chr_L     DS_d+DS_e+DS_f 			// L: 
#define DS_Chr_o     DS_c+DS_d+DS_e+DS_g 		// o: 
#define DS_Chr_P     DS_a+DS_b+DS_e+DS_f+DS_g 	// P: 
#define DS_Chr_N     DS_a+DS_b+DS_c+DS_e+DS_f 	// N: 
#define DS_Chr_n     DS_c+DS_e+DS_g 			// n: 
#define DS_Chr_r     DS_e+DS_g 					// r: 
#define DS_Chr_T	 DS_d+DS_e+DS_f+DS_g
#define DS_Chr_G	 DS_a+DS_c+DS_d+DS_e+DS_f
#define DS_Chr_Y	 DS_b+DS_c+DS_d+DS_f+DS_g
#define DS_Chr_S	 DS_a+DS_c+DS_d+DS_f+DS_g
#define DS_Chr_I	 DS_e
#define DS_Chr_w	 DS_c+DS_d+DS_e	
#define DS_Chr_U	 DS_b+DS_c+DS_d+DS_e+DS_f	
#define DS_Chr_wh	 DS_a+DS_b+DS_e+DS_g	//字符"?"

#define Ob0H		DS_a+DS_d+DS_e+DS_f		     
#define Ob0L		DS_b+DS_c
#define Ob1H		0x00
#define Ob1L		DS_b+DS_c			       
#define Ob2H		DS_a+DS_d+DS_e		     
#define Ob2L		DS_b+DS_g
#define Ob3H		DS_a+DS_d
#define Ob3L		DS_b+DS_c+DS_g		     
#define Ob4H		DS_f
#define Ob4L		DS_b+DS_c+DS_g			   
#define Ob5H		DS_a+DS_d+DS_f		     
#define Ob5L		DS_c+DS_g
#define Ob6H		DS_a+DS_d+DS_e+DS_f
#define Ob6L		DS_c+DS_g		       
#define Ob7H		DS_a
#define Ob7L		DS_b+DS_c			 
#define Ob8H		DS_a+DS_d+DS_e+DS_f		 
#define Ob8L		DS_b+DS_c+DS_g
#define Ob9H		DS_a+DS_d+DS_f		       
#define Ob9L		DS_b+DS_c+DS_g
#define ObfH		DS_a+DS_e+DS_f		       
#define ObfL		DS_g
#define ObDOT		0x10//0x01
/*
// Display digit
#define DS_Unit		1
#define DS_BDig		7
#define DS_SDig    	11

// Display Unit Segment
#define Unit_kWh        0x9E	// 10011110
#define Unit_MWh        0x9D	// 10011101
#define Unit_kvarh      0xF6	// 11110110
#define Unit_Mvarh      0xF5	// 11110101
#define Unit_kVAh       0xB6	// 10110110
#define Unit_MVAh       0xB5	// 10110101
#define Unit_kW         0x1E	// 00011110
#define Unit_MW         0x1D	// 00011101
#define Unit_kvar       0x76	// 01110110
#define Unit_Mvar       0x75 	// 01110101
#define Unit_kVA        0x36	// 00110110
#define Unit_MVA        0x35	// 00110101
#define Unit_V      	0x04	// 00000100
#define Unit_A        	0x30	// 00110000
#define Unit_Hz       	0x80	// 10000000+00000001

// Display Fee
#define Fee_A1       	0x01
#define Fee_A2       	0x02
#define Fee_A3       	0x04
#define Fee_A4       	0x08
#define Fee_1       		0x10
#define Fee_2     	  	0x20
#define Fee_3  	     	0x40
#define Fee_4	    		0x80
*/
/*******************************************************************
 	Display & Key Operating Bit
*******************************************************************/
/*
// Operating Mode
#define  Dis_Auto			0
#define  Dis_Manu			1

#define  Adj_Gain0_S    10
#define  Adj_Gain0_E    11
#define  Adj_Ofst_S     12
#define  Adj_Ofst_E     13
#define  Adj_Gain_S     14
#define  Adj_Gain_E     15
#define  Adj_Err        16
#define  Adj_End        17
#define  Adj_PhA      	18
*/
void fnLcd_AllOnhalf(void);
void  fnLcd_AllOn(void);
void LcdOn(void);
void LcdOff(void);
void DspNum( unsigned char *Addr, short Lenth, unsigned char *SegPtr ,short Digit);
void ActiveDisp( unsigned char *LCDSeg, unsigned char *FLCDSeg );
//void ActiveDisp( void );
void Display(void);
void ProcKey(void);
void GetItemSum(void);
//int GetPreCode( unsigned char* UserCode, int Type);
//int GetNextCode( unsigned char* UserCode, int Type);
void GetNextCode( unsigned Mode );	
void GetPreCode(unsigned Mode);
void KeyProce( void );
void ShiftRight4Bit( unsigned char* Source);
void LcdStateDisplay( unsigned char *LCDSeg, unsigned char *FLCDSeg );
void LcdTxtDisplay( unsigned char *LCDSeg, unsigned char *FLCDSeg );
void FillDisChar (unsigned char *SegPtr,unsigned char Item);
unsigned char TariffNameConvert(unsigned char Data);
//void DisObisCode(unsigned char *Point,unsigned char DisItem);
void DisObisCode(unsigned char *Point,unsigned short DisItem);
void GetRotIterm(void);
void ECDisplayMove( unsigned char* Data );


