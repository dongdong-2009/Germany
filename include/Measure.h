//#if ( SinglePhase==YesCheck )
//#include "SOC library\sd16_lib.h"
//#endif

#if ( Threephase == YesCheck ) //����
#if(MEASCHIP == ATT7053)
//7053
/*
#define SpI_I1		0x00
#define SpI_I2		0x01
#define SpI_U		0x02
#define Rms_I1		0x06
#define Rms_I2		0x07
#define Rms_U		0x08
#define Freq_U		0x09
#define PowerP1		0x0A
#define PowerQ1		0x0B
#define Power_S		0x0C
#define Energy_P	0x0D
#define Energy_Q	0x0E
#define Energy_S	0x0F
#define PowerP2		0x10
#define PowerQ2		0x11
#define BackupData	0x16
#define COMChecksum	0x17
#define SUMChecksum	0x18
#define EMUSR		0x19
#define SYSSTA		0x1A
#define IDCode		0x1B


#define EMUIE		0x30
#define EMUIF		0x31
#define WPREG		0x32
#define SRSTREG		0x33

#define EMUCFG		0x40
#define FrreqCFG	0x41
#define ModuleEn	0x42
#define ANAEN		0x43
#define IOCFG		0x45

#define GP1		0x50
#define GQ1		0x51
#define GS1		0x52

#define GP2		0x54
#define GQ2		0x55
#define GS2		0x56

#define QPhsCal		0x58
#define ADCCON		0x59
#define I2Gain		0x5B
#define I1Off		0x5C
#define I2Off		0x5D
#define UOff		0x5E
#define PQStart		0x54

#define HFConst		0x61
#define CHK		0x62
#define IPTAMP		0x63
#define P1OFFSET	0x65
#define P2OFFSET	0x66
#define Q1OFFSET	0x67
#define Q2OFFSET	0x68
#define I1RMSOFFSET	0x69
#define I2RMSOFFSET	0x6A

#define ZCrossCurrent	0x6C
#define GPhs1		0x6D
#define GPhs2		0x6E
#define PFCnt		0x6F
#define QFCnt		0x70
#define SFCnt		0x71

//#define	PDATAP		0x0b000000
//#define	PDATAN		0x01000000
//#define	PDATA0		0x06000000
//#define	PDATAPN		0x05000000
*/
/*****ATT7053********/
#define	PDATAP		0x0b000000 
#define	PDATAN		0x01000000
#define	PDATA0		0x06000000
#define	PDATAPN		0x05000000
#define PhPW4Imax   92000     //230*4*100=92000
#define PW4Imax     276000     //230*4*100*3=276000


#elif( MEASCHIP == RN8207 )
//define 8207 register//
#define		SYSCON3		0		//	2	ϵͳ���ƼĴ���	//                
#define		EMUCON3		1                       //	2	�������ƼĴ���	//                
#define		HFCONST3	2                       //	2	����Ƶ�ʼĴ���	//                
#define		PSTART3		3                       //	2	�й�������������	//        
#define		QSTART3		4                       //	2	�޹�������������	//        
#define		GPQA3		5                       //	2	ͨ��a����У��	//                
#define		GPQB3		6                       //	2	ͨ��b����У��	//                
#define		PHSA3		7                       //	1	ͨ��a��λУ��	//                
#define		PHSB3		8                       //	1	ͨ��b��λУ��	//                
#define		QPHSCAL3	9                       //	2	�޹���λ����	//                
#define		APOSA3		10                      //	2	ͨ��a�й�����offsetУ��	//        
#define		APOSB3		11                      //	2	ͨ��b�й�����offsetУ��	//        
#define		RPOSA3		12                      //	2	ͨ��a�޹�����offsetУ��	//        
#define		RPOSB3		13                      //	2	ͨ��b�޹�����offsetУ��	//        
#define		IARMSOS3	14                      //	2	����ͨ��a��ЧֵoffsetУ��	//
#define		IBRMSOS3	15                      //	2	����ͨ��b��ЧֵoffsetУ��	//
#define		IBGAIN3		16                      //	2	����ͨ��b��������У��	//        
#define		PFCNT3		32                      //	2	�����й��������	//        
#define		QFCNT3		33                      //	2	�����޹��������	//        
#define		IARMS3		34                      //	3	ͨ��a������Чֵ	//                
#define		IBRMS3		35                      //	3	ͨ��b������Чֵ	//                
#define		URMS3		36                      //	3	��ѹ��Чֵ	//                
#define		UFREQ3		37                      //	2	��ѹƵ��	//                
#define		POWERP3		38                      //	4	ͨ��a�й�����	//                
#define		POWERPB3	39                      //	4	ͨ��b�й�����	//                
#define		POWERQ3		40                      //	4	�޹�����	//                
#define		ENERGYP3	41                      //	3	�й��������������㣩	//        
#define		ENERGYP23	42              //	3	�й��������������㣩	//        
#define		ENERGYQ3	43                      //	3	�޹��������������㣩	//        
#define		ENERGYQ23	44              //	3	�޹��������������㣩	//        
#define		EMUSTATUS3	45              //	3	����״̬��У��ͼĴ���	//        
#define		ZXCNT3		52              //	2	��ѹ��������Ĵ���	//        
#define		SYSSTATUS3	67              //	1	ϵͳ״̬�Ĵ���	//                
#define		RDATA3		68                      //	4	��һ�ζ���������	//        
#define		WDATA3		69                      //	2	��һ��д�������	//        
#define		DEVICEID3	127             //	3	820900h,���к�	//    

#define	RD8207DLY	32//42//42//��д8207ʱ�õ��ĵȴ�ʱ��//
#define	CHIPIDA		0x88	
#define	CHIPIDB		0x99
#define	CHIPIDC		0xaa
#define	CHIPIDABC	0xbb

#define	ISTARTDATA	0x500//����������HEX��//

#define	READ8207OK	0x55
#define	WRITE8207OK 0x5a


#define	PDATAP		0x0b00000000
#define	PDATAN		0x0100000000
#define	PDATA0		0x0600000000
#define	PDATAPN		0x0500000000

//#define	PDATAP		0x1500000000
//#define	PDATAN		0x0100000000
//#define	PDATA0		0x0B00000000
//#define	PDATAPN		0x0A00000000

#define	PDLY400		2000//2000//�����������ζ����ܵļ����//

#define PS32        1000//100			//���峣�� = 3200imp/kwh
#define MeterConst	0x10		//���峣��ʮ������

//�������ķ���//
#define	Phase3	0x00
#define	Phase1	0x01

	
#define	PhaseType	Phase3

#define	WorkCal	0x00
#define	WorkNotCal	0x01

#define	WorkType		WorkNotCal//����״̬,У��״̬������״̬//

//#define	WGMeasure	YesCheck
#define	WGMeasure	NoCheck

#endif
#endif

/*
#define Iregion1	0x02
#define Iregion2	0x03
#define Iregion3	0x04
#define Iregion4	0x05
#define PgainA0		0x06
#define PgainB0		0x07
#define PgainC0		0x08
#define PgainA1		0x09
#define PgainB1		0x0A
#define PgainC1		0x0B
#define PhsregA0	0x0C
#define PhsregA1	0x0D
#define PhsregA2	0x0E
#define PhsregA3	0x0F
#define PhsregA4	0x10
#define PhsregB0	0x11
#define PhsregB1	0x12
#define PhsregB2	0x13
#define PhsregB3	0x14
#define PhsregB4	0x15
#define PhsregC0	0x16
#define PhsregC1	0x17
#define PhsregC2	0x18
#define PhsregC3	0x19
#define PhsregC4	0x1A
#define UgainA		0x1B
#define UgainB		0x1C
#define UgainC		0x1D
#define Iregchg		0x1E
#define Istartup	0x1F
#define HFConst		0x20
#define IgainA		0x26
#define IgainB		0x27
#define IgainC		0x28
#define FailVoltage	0x29
#define EnergyAddMode	0x2A

#define GainADC7	0x2B
#define GCtrlTADC7	0x2C

#define UADCPga		0x3F			//ATT7022B
#define PFlag		0x3D
#define EnUAngle	0x2E

#define EPgainA0	( 0x06 - 6 ) * 4
#define EPgainB0	( 0x07 - 6 ) * 4
#define EPgainC0	( 0x08 - 6 ) * 4
#define EPgainA1	( 0x09 - 6 ) * 4
#define EPgainB1	( 0x0A - 6 ) * 4
#define EPgainC1	( 0x0B - 6 ) * 4
#define EPhsregA0	( 0x0C - 6 ) * 4
#define EPhsregA1	( 0x0D - 6 ) * 4
#define EPhsregA2	( 0x0E - 6 ) * 4
#define EPhsregA3	( 0x0F - 6 ) * 4
#define EPhsregA4	( 0x10 - 6 ) * 4
#define EPhsregB0	( 0x11 - 6 ) * 4
#define EPhsregB1	( 0x12 - 6 ) * 4
#define EPhsregB2	( 0x13 - 6 ) * 4
#define EPhsregB3	( 0x14 - 6 ) * 4
#define EPhsregB4	( 0x15 - 6 ) * 4
#define EPhsregC0	( 0x16 - 6 ) * 4
#define EPhsregC1	( 0x17 - 6 ) * 4
#define EPhsregC2	( 0x18 - 6 ) * 4
#define EPhsregC3	( 0x19 - 6 ) * 4
#define EPhsregC4	( 0x1A - 6 ) * 4
#define EUgainA		( 0x1B - 6 ) * 4
#define EUgainB		( 0x1C - 6 ) * 4
#define EUgainC		( 0x1D - 6 ) * 4
#define EIgainA		( 0x26 - 14 ) * 4
#define EIgainB		( 0x27 - 14 ) * 4
#define EIgainC		( 0x28 - 14 ) * 4

#define ATPWPA		0x01
#define ATPWPB		0x02
#define ATPWPC		0x03
#define ATPWPZ		0x04
#define ATPWQA		0x05
#define ATPWQB		0x06
#define ATPWQC		0x07
#define ATPWQZ		0x08
#define ATPWSA		0x09
#define ATPWSB		0x0A
#define ATPWSC		0x0B
#define ATPWSZ		0x0C
#define ATUrmsA		0x0D
#define ATUrmsB		0x0E
#define ATUrmsC		0x0F
#define ATIrmsA		0x10
#define ATIrmsB		0x11
#define ATIrmsC		0x12
#define ATIrmsZ		0x13
#define ATFactorA	0x14
#define ATFactorB	0x15
#define ATFactorC	0x16
#define ATFactorZ	0x17
#define ATAngleA	0x18
#define ATAngleB	0x19
#define ATAngleC	0x1A
#define ATAngleZ	0x1B
#define ATFreq		0x1C
#define ATSPIRBuff	0x28
#define ATVoltFlag	0x2C
#define ATSPIWBuffA	0x2D
#define ATSPIWBuffB	0x2E
#define ATState		0x30
#define ATPA		0x31
#define ATPB		0x32
#define ATPC		0x33
#define ATPZ		0x34
#define ATQA		0x35
#define ATQB		0x36
#define ATQC		0x37
#define ATQZ		0x38
#define ATInPA		0x60
#define ATInPB		0x61
#define ATInPC		0x62
#define ATInPZ		0x63
#define ATOutPA		0x64
#define ATOutPB		0x65
#define ATOutPC		0x66
#define ATOutPZ		0x67
#define ATLPA		0x68
#define ATLPB		0x69
#define ATLPC		0x6A
#define ATLPZ		0x6B
#define ATCPA		0x6C
#define ATCPB		0x6D
#define ATCPC		0x6E
#define ATCPZ		0x6F

#define RmsADC7		0x29

#define ADJStart	0x80		//��������
#define ClrADJData	0xC3
#define ATRest		0xD3

#define ATYUaUb		0x5C
#define ATYUaUc		0x5D
#define ATYUbUc		0x5E

//ADE7758
#define	AWATTHR		0x01
#define BWATTHR		0x02
#define CWATTHR		0x03
#define AVARHR		0x04
#define BVARHR		0x05
#define CVARHR		0x06
#define AVAHR		0x07
#define BVAHR		0x08
#define CVAHR		0x09

#define AIRMS		0x0A
#define BIRMS		0x0B
#define CIRMS		0x0C

#define AVRMS		0x0D
#define BVRMS		0x0E
#define CVRMS		0x0F

#define FREQ		0x10
#define TEMP		0x11
#define WFORM		0x12
#define OPMODE		0x13
#define MMODE		0x14
#define WAVMODE		0x15
#define COMPMODE	0x16

#define LCYCMODE	0x17
#define MASK		0x18
#define STATUS		0x19
#define RSTATUS		0x1A
#define ZXTOUT		0x1B

#define LINCYC		0x1C
#define SAGCYC		0x1D
#define SAGLVL		0x1E
#define VPINTLVL	0x1F
#define IPINTLVL	0x20
#define VPEAK		0x21
#define IPEAK		0x22
#define GAIN		0x23


#define AVRMSGAIN	0x24
#define BVRMSGAIN	0x25
#define CVRMSGAIN	0x26

#define AIGAIN		0x27
#define BIGAIN		0x28
#define CIGAIN		0x29

#define AWG			0x2A
#define BWG			0x2B
#define CWG			0x2C

#define AVARG		0x2D
#define BVARG		0x2E
#define CVARG		0x2F

#define AVAG		0x30
#define BVAG		0x31
#define CVAG		0x32

#define AVRMSOS		0x33
#define BVRMSOS		0x34
#define CVRMSOS		0x35

#define AIRMSOS		0x36
#define BIRMSOS		0x37
#define CIRMSOS		0x38

#define AWATTOS		0x39
#define BWATTOS		0x3A
#define CWATTOS		0x3B

#define AVAROS		0x3C
#define BVAROS		0x3D
#define CVAROS		0x3E

#define APHCAL		0x3F
#define BPHCAL		0x40
#define CPHCAL		0x41

#define WDIV		0x42

#define VARDIV		0x43
#define VADIV		0x44

#define APCFNUM		0x45
#define APCFDEN		0x46

#define VARCFNUM	0x47
#define VARCFDEN	0x48
#define CHKSUM		0x7E
#define VERSION		0x7F

#define   STANDBY_STA		1
#define   TXSYNC_STA		2
#define   TX8BITDATA_STA	3
#define   TXP_STA		4
#define   TR_STA1		5
#define   RXSR_STA		6
#define   RX8BITDATA_STA	7
#define   RXP_STA		8
#define   TXMR_STA		9
#define   WAIT25_STA		10

#define   INT_NOP_STA		0
#define   INT_STAND_STA		1
#define   INT_RECEIVE_STA	2
#define   INT_FINISH_STA	3
#define   INT_ERR_STA		4
*/

//��������
/*
//220(380V) 10(40A)     10A=80mv
//#define A005Ib		50		//0.05*10A*100=0.05A	
//#define	A020Ib		200		//0.2*10A*100=2.00A
#define	V150Un		3450	//1.50*220*10=3300V
#define V50Un		1100	//0.50*220*10=1100V		
#define PS32        04		//���峣�� = 400imp/kwh
#define MeterConst	0x04	//���峣�� = 400imp/kwh
#define HFConstL	0x54		//-3.3%		
#define HFConstH	0x00
#define VoltResumL	0x70	//220V��ʧѹ�ָ�ֵΪ187V=0x1870 
#define VoltResumH	0x18	//
*/
/*
//220(380V) 1.5(6A)     1.5A=80mv
//#define A002Ib      1
//#define A005Ib		7		//0.05*1.5A*100=7.5
//#define	A020Ib		30		//0.2*1.5A*100=30
//#define	A100Ib		150		//1.5A*100=150
#define	V150Un		3300	//1.50*220*10=3300V
#define V50Un		1100	//0.50*220*10=1100V		
#define PS32        32		//���峣�� = 3200imp/kwh
#define MeterConst	0x32		//���峣��ʮ������
#define HFConstL	0x49		//-3.3%		
#define HFConstH	0x00
#define VoltResumL	0x70	//220V��ʧѹ�ָ�ֵΪ187V=0x1870 
#define VoltResumH	0x18	//
*/
/*
//220(380V) 1.5(6A)     1.5A=80mv
#define	V100Un		22		//220*10=2200V /100 = 22
#define PS32        32		//���峣�� = 3200imp/kwh
#define MeterConst	0x32		//���峣��ʮ������
#define HFConstL	0x49		//-3.3%		
//#define HFConstL	0x24		//-3.3%		
#define HFConstH	0x00
#define VoltResumL	0x70	//220V��ʧѹ�ָ�ֵΪ187V=0x1870 
#define VoltResumH	0x18	//
#define PWConst		0x100
#define SMEcConst	360000/PS32		
#define IMAX3PLUSES	10
#define IB005PW		500		//220*1.5*3*0.05*10 = 500 = 50W 	��5%IbΪ��	
#define IB005PULSE	15		//220*1.5*3*0.05*3200/(1000*60) = 2.64��/���� 	6��ȡ15��
*/
/*
//220(380V) 5(20A)     1.5A=80mv
#define	V150Un		3300	//1.50*220*10=3300V
#define V50Un		1100	//0.50*220*10=1100V		
#define PS32        8		//���峣�� = 3200imp/kwh
#define MeterConst	0x8		//���峣��ʮ������
#define HFConstL	0x63		//-3.3%		
#define HFConstH	0x00
#define VoltResumL	0x70	//220V��ʧѹ�ָ�ֵΪ187V=0x1870 
#define VoltResumH	0x18	//
*/

/*
//220(380V) 20(100)A     20A=80mv
#define	V150Un		3300	//1.50*220*10=3300V
#define V50Un		1100	//0.50*220*10=1100V		
#define PS32        4		//���峣�� = 3200imp/kwh
#define MeterConst	0x4		//���峣��ʮ������
#define HFConstL	0x2C		//-3.3%		
#define HFConstH	0x00
#define VoltResumL	0x70	//220V��ʧѹ�ָ�ֵΪ187V=0x1870 
#define VoltResumH	0x18	//
*/
/*
//��������
//100V 1.5(6A)     1.5A=150mv
#define A002Ib		2		//0.02*1.5A*100=3	
#define A005Ib		7		//0.05*1.5A*100=7.5	
#define	A020Ib		30		//0.2*1.5A*100=30
#define	V150Un		1500	//1.50*100*10=1500V
#define V50Un		500	//0.50*100*10=500V		
#define PS32        64	//���峣�� = 6400imp/kwh
#define MeterConst	0x64	//���峣�� = 6400imp/kwh
//#define HFConstL	0x50		//-3.3%		
#define HFConstL	0x86		//-3.3%		
#define HFConstH	0x00
#define VoltResumL	0x50	//100V��ʧѹ�ָ�ֵΪ85V=0x0850 
#define VoltResumH	0x08	//
*/	
                            
//#define I01IBIPLUSES	25000	//1%Ib 1�������յ���������Ȩ���ۼӺ�                     
//#define I01IBIPLUSES	50000	//1%Ib 1�������յ���������Ȩ���ۼӺ�                     
#define I01IBIPLUSES	16667	//1%Ib 1���е������յ���������Ȩ���ۼӺ�                     
#define I010IPLUSES		500000	//10%Ib 1���к������յ���������Ȩ���ۼӺ�                     
#define SECPLUSECNT		5		//�������ʱ����                    
#define NoECTime		170                           
//;================================================================================================	;**
//;================================================================================================
//;220x1.5(6)A;���峣��=3200      ��ѹ����=390K 1%   ����ȡ������=10ŷķ 1%  ����������1.5(6) 5mA ƥ�����20ŷķ
//;PS3200HL=(10000000/(((((220x1.5)/1000)x3200x3200)/3600)x6))x3200=5681818=56B29AH
//;------------------------------------------------------------------
//;PS3200L	EQU	0B29AH	;0.01kWh AD7755������=3200(���ֽ�)
//;PS3200H	EQU	56H	;0.01kWh AD7755������=3200(���ֽ�)
//;PSB3200L        EQU     04D66H          ;������������    
//;PSB3200H        EQU     0A9H            ;
//;PSF3200L        EQU     0B29AH          ;������������
//;PSF3200H        EQU     0156H           ;
//;PS32	EQU	32	;�ǵ�0.01kWh
//;PSPA    EQU     3200    ;���峣��
//;PS800L	EQU	0ACA6H	;AD7755������=800(���ֽ�)
//;PS800H	EQU	15H	;AD7755������=800(���ֽ�)
//;CONPSPA	EQU	3200H	;�������峣��
//;CONVOLT	EQU	2200	;220V*10 = 2200     	;һλС��
//;CONAMP	EQU	150	;1.5A*100= 150		;��λС��
//;DCPER	EQU	29	;0.2Ib=0.30*100=30	;������ֵ
//;FCPER	EQU	8	;0.05Ib=150*0.05=7.5	;ȫʧѹ������ֵ
/*
#define PS3200		0x56B29A	//0.01kWh AD7755������=3200
#define PSB3200		0xA94D66	//������������    
#define PSF3200		0x0156B29A	//������������    
#define PS32        32			//���峣�� = 3200imp/kwh
#define MeterConst	0x32		//���峣��ʮ������
#define VoltResumL	0x70	//220V��ʧѹ�ָ�ֵΪ187V=0x1870 
#define VoltResumH	0x18	//
#define VoltLow		2140	//220*0.97
#define	VoltHigh	2260	//220*1.03
#define	V100Un		22		//220*10=2200V /100 = 22
#define IMAX3PLUSES	53		//10.56*SECPLUSECNT = 53
#define PW010IbL	940		//(220*1.5*3/10)*10*0.95 = 940
#define PW010IbH	1040	//(220*1.5*3/10)*10*1.05 = 1040
#define PW010Ib		990		//(220*1.5*3/10)*10 = 990
*/
//;================================================================================================
//;220x5(20)A;���峣��=800      ��ѹ����=390K 1%   ����ȡ������=10ŷķ 1%  ����������5(20) 5mA ƥ�����20ŷķ
//;PS3200HL=(10000000/(((((220x5)/1000)x3200x800)/3600)x6))x3200=6818182=680986H
//;------------------------------------------------------------------
//#define PS3200		0x97F67A	//0.01kWh AD7755������=3200
//#define PSB3200		0xA94D66	//������������    
/*
#define PS3200		0x680986	//0.01kWh AD7755������=3200
#define PSB3200		0x97F67A	//������������    
#define PSF3200		0x01680986	//������������    
#define PS32        8			//���峣�� = 3200imp/kwh
#define MeterConst	0x8		//���峣��ʮ������
#define VoltResumL	0x70	//220V��ʧѹ�ָ�ֵΪ187V=0x1870 
#define VoltResumH	0x18	//
#define VoltLow		2140	//220*0.97
#define	VoltHigh	2260	//220*1.03
#define	V100Un		22		//220*10=2200V /100 = 22
#define IMAX3PLUSES	44		//8.8*SECPLUSECNT
#define PW010IbL	3135	//(220*5*3/10)*10*0.95 = 3135
#define PW010IbH	3465	//(220*5*3/10)*10*1.05 = 3465	
#define PW010Ib		3300	//(220*5*3/10)*10 = 3300	
*/
//;================================================================================================
//;220x1.5(6)A;���峣��=6400      ��ѹ����=390K 1%   ����ȡ������=10ŷķ 1%  ����������1.5(6) 5mA ƥ�����20ŷķ
//;PS3200HL=(10000000/(((((220x1.5)/1000)x3200x6400)/3600)x6))x3200=2840909=2B594DH
//;------------------------------------------------------------------
//;PS3200L	EQU	0594DH	;0.01kWh AD7755������=3200(���ֽ�)
//;PS3200H	EQU	2BH	;0.01kWh AD7755������=3200(���ֽ�)
//;PS32	EQU	64	;�ǵ�0.01kWh
//;PSPA    EQU     6400    ;���峣��
//;PS800L	EQU	0D653H	;AD7755������=800(���ֽ�)
//;PS800H	EQU	0AH	;AD7755������=800(���ֽ�)
//;CONPSPA	EQU	6400H	;�������峣��
//;================================================================================================
//;220x1(6)A;���峣��=3200        ��ѹ����=390K 1%   ����ȡ������=10ŷķ 1% ����������1(6) 5mA ƥ�����20ŷķ
//;PS3200HL=(10000000/(((((220x1)/1000)x3200x3200)/3600)x6))x3200=8522727=820BE7H
//;------------------------------------------------------------------
//;PS3200L	EQU	0BE7H	;0.01kWh AD7755������=3200(���ֽ�)
//;PS3200H	EQU	82H	;0.01kWh AD7755������=3200(���ֽ�)
//;PS32	EQU	32	;�ǵ�0.01kWh
//;PSPA  EQU     3200    ;���峣��
//;CONPSPA	EQU	3200H	;�������峣��
//;================================================================================================
//;63.5x1.5(6)A;���峣��=3200   ��ѹ����=110K 1%   ����ȡ������=10ŷķ 1% ����������1.5(6) 5mA ƥ�����20ŷķ       
//;PS3200HL=(10000000/(((((63.5x1.5)/1000)x3200x3200)/3600)x6))x3200=19685039=12C5EAF
//;------------------------------------------------------------------
//;PS3200L	EQU	5EAFH	;0.01kWh AD7755������=3200(���ֽ�)
//;PS3200H	EQU	12CH	;0.01kWh AD7755������=3200(���ֽ�)
//;PS32	EQU	32	;�ǵ�0.01kWh
//;PSPA  EQU     3200    ;���峣��
//;CONPSPA	EQU	3200H	;�������峣��
//;================================================================================================
//;63.5x1.5(6)A;���峣��=6400   ��ѹ����=110K 1%   ����ȡ������=10ŷķ 1% ����������1.5(6) 5mA ƥ�����20ŷķ       
//;PS3200HL=(10000000/(((((63.5x1.5)/1000)x3200x6400)/3600)x6))x3200=9842519=962f57
//;------------------------------------------------------------------
//;PS3200L	EQU	2F57H	;0.01kWh AD7755������=3200(���ֽ�)
//;PS3200H	EQU	96H	;0.01kWh AD7755������=3200(���ֽ�)
//;PS32	EQU	64	;�ǵ�0.01kWh
//;PSPA  EQU     6400    ;���峣��
//;CONPSPA	EQU	6400H	;�������峣��
//;================================================================================================
//;63.5x1(6)A;���峣��=3200   ��ѹ����=110K 1%   ����ȡ������=10ŷķ 1% ����������1(6) 5mA ƥ�����20ŷķ       
//;PS3200HL=(10000000/(((((63.5x1)/1000)x3200x3200)/3600)x6))x3200=29527559=1C28E07H
//;------------------------------------------------------------------
//;PS3200L	EQU	8E07H	;0.01kWh AD7755������=3200(���ֽ�)
//;PS3200H	EQU	1C2H	;0.01kWh AD7755������=3200(���ֽ�)
//;PS32	EQU	32	;�ǵ�0.01kWh
//;PSPA  EQU     3200    ;���峣��
//;CONPSPA	EQU	3200H	;�������峣��
//;================================================================================================
//;63.5x1(6)A;���峣��=6400   ��ѹ����=110K 1%   ����ȡ������=10ŷķ 1% ����������1(6) 5mA ƥ�����20ŷķ       
//;PS3200HL=(10000000/(((((63.5x1)/1000)x3200x6400)/3600)x6))x3200=14763779=0E14703H
//;------------------------------------------------------------------
//;PS3200L	EQU	4703H	;0.01kWh AD7755������=3200(���ֽ�)
//;PS3200H	EQU	0E1H	;0.01kWh AD7755������=3200(���ֽ�)
//;PS32	EQU	64	;�ǵ�0.01kWh
//;PSPA  EQU     6400    ;���峣��
//;CONPSPA	EQU	6400H	;�������峣��
//;================================================================================================
//;220x10(100)A;���峣��=200   ��ѹ����=390K 1% ����ȡ������=3ŷķ 1% ����������10(100) 10mA ƥ�����10ŷķ      
//;PS3200HL=(10000000/(((((220x10)/1000)x3200x200)/3600)x6))x3200=13636363=0D0130BH
//;------------------------------------------------------------------
//;PS3200L	EQU	0130BH	;0.01kWh AD7755������=3200(���ֽ�)
//;PS3200H	EQU	0D0H	;0.01kWh AD7755������=3200(���ֽ�)
//;PS32	EQU	2	;�ǵ�0.01kWh
//;PSPA    EQU     200    ;���峣��
//;PS800L	EQU	04C2H	;AD7755������=800(���ֽ�)
//;PS800H	EQU	34H	;AD7755������=800(���ֽ�)
//;CONPSPA	EQU	200H	;�������峣��
//;================================================================================================
//;220x20(80)A;���峣��=200   ��ѹ����=390K 1% ����ȡ������=3ŷķ 1% ����������20(80) 10mA ƥ�����10ŷķ      
//;PS3200HL=(10000000/(((((220x20)/1000)x3200x200)/3600)x6))x3200=6818182=680986H
//;------------------------------------------------------------------
//PS3200L	EQU	0986H	;0.01kWh AD7755������=3200(���ֽ�)
//PS3200H	EQU	68H	;0.01kWh AD7755������=3200(���ֽ�)
//PSB3200L        EQU     0F67AH          ;������������    
//PSB3200H        EQU     097H            ;
//PSF3200L        EQU     0986H           ;������������
//PSF3200H        EQU     0168H           ;
//PS32		EQU	2	;�ǵ�0.01kWh
//PSPA    	EQU     200    ;���峣��
//CONPSPA	EQU	200H	;�������峣��
//CONVOLT	EQU	2200	;220V*10 = 2200     	;һλС��
//CONAMP		EQU	2000	;20A*100= 2000		;��λС��
//DCPER		EQU	400	;0.2Ib=4*100=400	;������ֵ
//FCPER		EQU	100	;0.05Ib=2000*0.05=100	;ȫʧѹ������ֵ

#if ( Threephase == YesCheck ) //����
#if( MEASCHIP == ADE7755 )
#define PS3200		0x680986	//0.01kWh AD7755������=3200
#define PSB3200		0x97F67A	//������������    
#define PSF3200		0x01680986	//������������    
//#define PS32        100			//���峣�� = 3200imp/kwh
#define MeterConst	0x10		//���峣��ʮ������
#define VoltResumL	0x70	//220V��ʧѹ�ָ�ֵΪ187V=0x1870 
#define VoltResumH	0x18	//
#define VoltLow		2140	//220*0.97
#define	VoltHigh	2260	//220*1.03
#define	V100Un		22		//220*10=2200V /100 = 22
#define IMAX3PLUSES	44		//8.8*SECPLUSECNT
#define PW010IbL	12540	//(220*20*3/10)*10*0.95 = 12540
#define PW010IbH	13860	//(220*20*3/10)*10*1.05 = 13860	
#define PW010Ib		13200	//(220*20*3/10)*10 = 13200	
#define POWERCNTTIME	2		//1s
#endif
#endif

#if ( SinglePhase == YesCheck )
#define PS32        1000			//���峣�� = 3200imp/kwh
//#define PS32        100			//���峣�� = 3200imp/kwh 13.2.27wwl
#endif

//;================================================================================================
//;220x10(40)A;���峣��=400   ��ѹ����=390K 1% ����ȡ������=3ŷķ 1% ����������10(60) 10mA ƥ�����10ŷķ      
//;PS3200HL=(10000000/(((((220x10)/1000)x3200x400)/3600)x6))x3200=6818182=680986H
//;------------------------------------------------------------------
//;PS3200L	EQU	0986H	;0.01kWh AD7755������=3200(���ֽ�)
//;PS3200H	EQU	68H	;0.01kWh AD7755������=3200(���ֽ�)
//;PSB3200L        EQU     0F67AH          ;������������    
//;PSB3200H        EQU     097H            ;
//;PSF3200L        EQU     0986H           ;������������
//;PSF3200H        EQU     0168H           ;
//;PS32	EQU	4	;�ǵ�0.01kWh
//;PSPA    EQU     400    ;���峣��
//;CONPSPA	EQU	400H	;�������峣��
//;CONVOLT	EQU	2200	;220V*10 = 2200     	;һλС��
//;CONAMP	EQU	1000	;10A*100= 1000		;��λС��
//;DCPER	EQU	200	;0.2Ib=2*100=200	;������ֵ
//;FCPER	EQU	50	;0.05Ib=1000*0.05=50	;ȫʧѹ������ֵ
/*
#define PS3200		0x680986	//0.01kWh AD7755������=3200
#define PSB3200		0x97F67A	//������������    
#define PSF3200		0x01680986	//������������    
#define PS32        4			//���峣�� = 3200imp/kwh
#define MeterConst	0x4		//���峣��ʮ������
#define VoltResumL	0x70	//220V��ʧѹ�ָ�ֵΪ187V=0x1870 
#define VoltResumH	0x18	//
#define VoltLow		2140	//220*0.97
#define	VoltHigh	2260	//220*1.03
#define	V100Un		22		//220*10=2200V /100 = 22
#define IMAX3PLUSES	44		//8.8*SECPLUSECNT
#define PW010IbL	6270	//(220*10*3/10)*10*0.95 = 6270
#define PW010IbH	6930	//(220*10*3/10)*10*1.05 = 6930
#define PW010Ib		6600	//(220*10*3/10)*10 = 6600
*/
//;================================================================================================
//;================================================================================================

//===================================================================

void fnFront_ClockBatCalculate(void);

void ATT7022RdReg( unsigned char Cmd, unsigned char* Data  );
void ATT7022WtReg( unsigned char Cmd, unsigned char* Data  );
void ATT7022Init(void);
void SetFailVoltage(void);
void SetEnergyAddMode(void);
//int GetMQuad( unsigned char ActPwReg, unsigned char ReActPwReg);
void PhaseEcMease( void );
//int GetMQuad( int Reg );
short GetMQuad( unsigned char PWFlag, short Reg );
void EC_Meas(void);
void ECRgSum( short ECItem, short Type);
void Read_CMonEC( unsigned char* Dest, short ECRgAds );
//void FMBuf_RWAdd( int Dest, unsigned char* Src );
//int GetMQuad(void);
short MD_Meas( void );
short MD_MeasB( void );
//int CumBuffPls( int BuffAds );
void MD_Comp( unsigned char* PointSrc, short MD_Ads, short MDT_Ads );
void MD_CompB(unsigned char* Pointtime, unsigned char* PointSrc, short MD_Ads, short MDT_Ads );
//void SMEcMease( void );
//void ECBuf_Read( unsigned char* Dest, unsigned int Src );
//void ECBuf_Write( unsigned int Dest, unsigned char* Scr );
short GetStablyQuad( void );
void SetAddMode(unsigned char Mode);
short Read_CMonECPpnC( unsigned char* Dest, short ECRgAds );
void AD7755Init( void );
void RN8203Init( void );
void ReadValueVI( void );

unsigned char Read8207(unsigned char Chipid,unsigned char Addr,unsigned char lg);
unsigned char Write8207(unsigned char *Source,unsigned char Chipid,unsigned char Addr,unsigned char lg);
unsigned char ReadAPower(void);
unsigned char ReadBPower(void);
unsigned char ReadCPower(void);
void ReadABCPower(void);

void ReadABCIARMS(void);
void ReadMeasVolt(void);
unsigned char ReadAIARMS(void);
unsigned char ReadBIARMS(void);
unsigned char ReadCIARMS(void);

void ResetA8209(void);
void ResetB8209(void);
void ResetC8209(void);
void Reset8209(void);
void Reset8209All(void);
void ReadABCPowern(void);
void ResetLoRa(unsigned char Mode);
void ResetLoRaData(unsigned char *Ptr,unsigned char lg);



//#if ( SinglePhase == YesCheck ) //����
///*����ģ��ǰ�˳�ʼ������������ʼ������*/
//#define SingleEnergyInit(s,w,x,y) 				SingleEnergyInit_SD16A(s,w,x,y)           //ģ��ǰ��Ϊ3·sd16��sd16_A�����ú���
////#define SingleEnergyInit(s,w,x,y,z) 				SingleEnergyInit_SD16_2(s,w,x,y,z)           //ģ��ǰ��Ϊ2·sd16�����ú���

///*������Ӧ�ò�ӿڵ�AP����*/
//#define SingleEnergyAP(w,x,y,z)             SingleEnergyAP_Neutral_ReactiveSupport(w,x,y,z)       //����2·�������й����ʡ��޹�����
////#define SingleEnergyAP(w,x,y,z)             SingleEnergyAP_ReactiveSupport(w,x,y,z)              //����1·�������й����ʡ��޹�����

///*����sd16�жϺ���*/
//#define SingleEnergyBG(x,y,z)     		    SingleEnergyBG_Neutral_ReactiveSupport(x,y,z)                  //����2·�������й����ʡ��޹�����
////#define SingleEnergyBG(x,y,z)     		  SingleEnergyBG_ReactiveSupport(x,y,z)                          //����1·�������й����ʡ��޹�����

///*ֹͣsd16������ת�����رղο���ѹ*/
//#define SingleEnergyStop(void)                  disable_analog_front_end(void)

//extern phase_readings_s phase_readings;
//extern phase_metrology_s phase_metrology;
//extern phase_calibration_s phase_calibration;
//extern const phase_config_s phase_config;

void SOCInit( void );
//unsigned int SOC_Cal_Datachksum(void);
//void init_AD_Power(void);
//#endif








