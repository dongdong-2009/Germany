//#include "TypeMeter.h"
#include "TypeE2p.h"
#include "Type.h"
#include "Data.h"
//#include "Display.h"
//#include "RsComm.h"
//#include "Measure.h"
//#include "Power.h"
//#include "Port.h"
#include "MeterDataType.h"
//#include "Display.h"


const METERDATATAB MeterDataTab[] =
{
	0x0001,	0x01,0x00,0x01,0x08,0x00,0xFF,	CMon_EC_Pp0,	DLen_6,		F_DRS_ReadEN+F_DRS_SYNData+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//0
	0x0002,	0x01,0x00,0x01,0x08,0x01,0xFF,	CMon_EC_Pp1,	DLen_6,		F_DRS_ReadEN+F_DRS_SYNData+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//1
	0x0003,	0x01,0x00,0x01,0x08,0x02,0xFF,	CMon_EC_Pp2,	DLen_6,		F_DRS_ReadEN+F_DRS_SYNData+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//2
	0x0004,	0x01,0x00,0x01,0x08,0x03,0xFF,	CMon_EC_Pp3,	DLen_6,		F_DRS_ReadEN+F_DRS_SYNData+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//3
	0x0005,	0x01,0x00,0x01,0x08,0x04,0xFF,	CMon_EC_Pp4,	DLen_6,		F_DRS_ReadEN+F_DRS_SYNData+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//4
//	0x0006,	0x0100010805FF,	CMon_EC_Pp5,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//5
//	0x0007,	0x0100010806FF,	CMon_EC_Pp6,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//6
//	0x0008,	0x0100010807FF,	CMon_EC_Pp7,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//7
//	0x0009,	0x0100010808FF,	CMon_EC_Pp8,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//8
	
	0x000A,	0x01,0x00,0x02,0x08,0x00,0xFF,	CMon_EC_Pn0,	DLen_6,		F_DRS_ReadEN+F_DRS_SYNData+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//9
	0x000B,	0x01,0x00,0x02,0x08,0x01,0xFF,	CMon_EC_Pn1,	DLen_6,		F_DRS_ReadEN+F_DRS_SYNData+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//10
	0x000C,	0x01,0x00,0x02,0x08,0x02,0xFF,	CMon_EC_Pn2,	DLen_6,		F_DRS_ReadEN+F_DRS_SYNData+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//11
	0x000D,	0x01,0x00,0x02,0x08,0x03,0xFF,	CMon_EC_Pn3,	DLen_6,		F_DRS_ReadEN+F_DRS_SYNData+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//12
	0x000E,	0x01,0x00,0x02,0x08,0x04,0xFF,	CMon_EC_Pn4,	DLen_6,		F_DRS_ReadEN+F_DRS_SYNData+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//13
//	0x000F,	0x0100020805FF,	CMon_EC_Pn5,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//14
//	0x0010,	0x0100020806FF,	CMon_EC_Pn6,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//15
//	0x0011,	0x0100020807FF,	CMon_EC_Pn7,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//16
//	0x0012,	0x0100020808FF,	CMon_EC_Pn8,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kwh,	//17
	
//	0x0013,	0x0100030800FF,	CMon_EC_Qp0,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹��ܵ���,	1,	$15
//	0x0014,	0x0100030801FF,	CMon_EC_Qp1,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�T1,	1,	$15
//	0x0015,	0x0100030802FF,	CMon_EC_Qp2,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�T2,	1,	$15
//	0x0016,	0x0100030803FF,	CMon_EC_Qp3,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�T3,	1,	$15
//	0x0017,	0x0100030804FF,	CMon_EC_Qp4,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�T4,	,	$15
//	0x0018,	0x0100030805FF,	CMon_EC_Qp5,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�T5,	,	$15
//	0x0019,	0x0100030806FF,	CMon_EC_Qp6,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�T6,	,	$15
//	0x001A,	0x0100030807FF,	CMon_EC_Qp7,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�T7,	,	$15
//	0x001B,	0x0100030808FF,	CMon_EC_Qp8,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�T8,	,	$15
//	0x001C,	0x0100040800FF,	CMon_EC_Qn0,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹������ܵ���,	,	$15
//	0x001D,	0x0100040801FF,	CMon_EC_Qn1,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�����T1,	,	$15
//	0x001E,	0x0100040802FF,	CMon_EC_Qn2,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�����T2,	,	$15
//	0x001F,	0x0100040803FF,	CMon_EC_Qn3,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�����T3,	,	$15
//	0x0020,	0x0100040804FF,	CMon_EC_Qn4,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�����T4,	,	$15
//	0x0021,	0x0100040805FF,	CMon_EC_Qn5,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�����T5,	,	$15
//	0x0022,	0x0100040806FF,	CMon_EC_Qn6,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�����T6,	,	$15
//	0x0023,	0x0100040807FF,	CMon_EC_Qn7,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�����T7,	,	$15
//	0x0024,	0x0100040808FF,	CMon_EC_Qn8,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹�����T8,	,	$15
//	0x0025,	0x0100050800FF,	CMon_EC_Q10,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���һ�����ܵ���,	,	$15
//	0x0026,	0x0100050801FF,	CMon_EC_Q11,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���һ����T1,	,	$15
//	0x0027,	0x0100050802FF,	CMon_EC_Q12,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���һ����T2,	,	$15
//	0x0028,	0x0100050803FF,	CMon_EC_Q13,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���һ����T3,	,	$15
//	0x0029,	0x0100050804FF,	CMon_EC_Q14,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���һ����T4,	,	$15
//	0x002A,	0x0100050805FF,	CMon_EC_Q15,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���һ����T5,	,	$15
//	0x002B,	0x0100050806FF,	CMon_EC_Q16,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���һ����T6,	,	$15
//	0x002C,	0x0100050807FF,	CMon_EC_Q17,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���һ����T7,	,	$15
//	0x002D,	0x0100050808FF,	CMon_EC_Q18,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���һ����T8,	,	$15
//	0x002E,	0x0100060800FF,	CMon_EC_Q20,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹��ڶ������ܵ���,	,	$15
//	0x002F,	0x0100060801FF,	CMon_EC_Q21,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹��ڶ�����T1,	,	$15
//	0x0030,	0x0100060802FF,	CMon_EC_Q22,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹��ڶ�����T2,	,	$15
//	0x0031,	0x0100060803FF,	CMon_EC_Q23,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹��ڶ�����T3,	,	$15
//	0x0032,	0x0100060804FF,	CMon_EC_Q24,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹��ڶ�����T4,	,	$15
//	0x0033,	0x0100060805FF,	CMon_EC_Q25,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹��ڶ�����T5,	,	$15
//	0x0034,	0x0100060806FF,	CMon_EC_Q26,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹��ڶ�����T6,	,	$15
//	0x0035,	0x0100060807FF,	CMon_EC_Q27,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹��ڶ�����T7,	,	$15
//	0x0036,	0x0100060808FF,	CMon_EC_Q28,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹��ڶ�����T8,	,	$15
//	0x0037,	0x0100070800FF,	CMon_EC_Q30,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹����������ܵ���,	,	$15
//	0x0038,	0x0100070801FF,	CMon_EC_Q31,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T1,	,	$15
//	0x0039,	0x0100070802FF,	CMon_EC_Q32,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T2,	,	$15
//	0x003A,	0x0100070803FF,	CMon_EC_Q33,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T3,	,	$15
//	0x003B,	0x0100070804FF,	CMon_EC_Q34,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T4,	,	$15
//	0x003C,	0x0100070805FF,	CMon_EC_Q35,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T5,	,	$15
//	0x003D,	0x0100070806FF,	CMon_EC_Q36,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T6,	,	$15
//	0x003E,	0x0100070807FF,	CMon_EC_Q37,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T7,	,	$15
//	0x003F,	0x0100070808FF,	CMon_EC_Q38,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T8,	,	$15
//	0x0040,	0x0100080800FF,	CMon_EC_Q40,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹����������ܵ���,	,	$15
//	0x0041,	0x0100080801FF,	CMon_EC_Q41,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T1,	,	$15
//	0x0042,	0x0100080802FF,	CMon_EC_Q42,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T2,	,	$15
//	0x0043,	0x0100080803FF,	CMon_EC_Q43,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T3,	,	$15
//	0x0044,	0x0100080804FF,	CMon_EC_Q44,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T4,	,	$15
//	0x0045,	0x0100080805FF,	CMon_EC_Q45,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T5,	,	$15
//	0x0046,	0x0100080806FF,	CMon_EC_Q46,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T6,	,	$15
//	0x0047,	0x0100080807FF,	CMon_EC_Q47,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T7,	,	$15
//	0x0048,	0x0100080808FF,	CMon_EC_Q48,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	�޹���������T8,	,	$15
//	0x0049,	0x0100210800FF,	CMon_EC_PpA,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	A���й��ܵ���,	,	$15
//	0x004A,	0x0100220800FF,	CMon_EC_PnA,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	A���й��������,	,	$15
//	0x004B,	0x0100410800FF,	CMon_EC_PpB,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	B���й��ܵ���,	,	$15
//	0x004C,	0x0100420800FF,	CMon_EC_PnB,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	B���й��������,	,	$15
//	0x004D,	0x0100610800FF,	CMon_EC_PpC,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	C���й��ܵ���,	,	$15
//	0x004E,	0x0100620800FF,	CMon_EC_PnC,	DLen_6,		F_DRS_ReadEN+DRS_Energy, 	DLen_9,	DLen_3,		DDU_kvarh,	//EEPROM:000000000.0;RAM:,	<0.1,	R,	ʵʱ��ʾ��Kwh,	C���й��������,	,	$15
	
//	0x004F,	0x0100010800FF,	CMon_MD_Pp0,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kw,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�й����������,	,	$14,	$15
//	0x0050,	0x0100010800FF,	CMon_MD_Pp1,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kw,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�й��������T1,	,	$14,	$15
//	0x0051,	0x0100010800FF,	CMon_MD_Pp2,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kw,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�й��������T2,	,	$14,	$15
//	0x0052, 0x0100010800FF,	CMon_MD_Pp3,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kw,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�й��������T3,	,	$14,	$15
//	0x0053,	0x0100010800FF,	CMon_MD_Pp4,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kw,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�й��������T4,	,	$14,	$15
//	0x0054,	0x0100010800FF,	CMon_MD_Pp5,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kw,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�й��������T5,	,	$14,	$15
//	0x0055,	0x0100010800FF,	CMon_MD_Pp6,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kw,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�й��������T6,	,	$14,	$15
//	0x0056,	0x0100010800FF,	CMon_MD_Pp7,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kw,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�й��������T7,	,	$14,	$15
//	0x0057,	0x0100010800FF,	CMon_MD_Pp8,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kw,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�й��������T8,	,	$14,	$15
//	0x0058,	0x0100010800FF,	CMon_MD_Qp0,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹����������,	,	$14,	$15
//	0x0059,	0x0100010800FF,	CMon_MD_Qp1,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹��������T1,	,	$14,	$15
//	0x005A,	0x0100010800FF,	CMon_MD_Qp2,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹��������T2,	,	$14,	$15
//	0x005B,	0x0100010800FF,	CMon_MD_Qp3,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹��������T3,	,	$14,	$15
//	0x005C,	0x0100010800FF,	CMon_MD_Qp4,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹��������T4,	,	$14,	$15
//	0x005D,	0x0100010800FF,	CMon_MD_Qp5,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹��������T5,	,	$14,	$15
//	0x005E,	0x0100010800FF,	CMon_MD_Qp6,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹��������T6,	,	$14,	$15
//	0x005F,	0x0100010800FF,	CMon_MD_Qp7,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹��������T7,	,	$14,	$15
//	0x0060,	0x0100010800FF,	CMon_MD_Qp8,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹��������T8,	,	$14,	$15
//	0x0061,	0x0100010800FF,	CMon_MD_Q10,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q1���������,	,	$14,	$15
//	0x0062,	0x0100010800FF,	CMon_MD_Q11,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q1�������T1,	,	$14,	$15
//	0x0063,	0x0100010800FF,	CMon_MD_Q12,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q1�������T2,	,	$14,	$15
//	0x0064,	0x0100010800FF,	CMon_MD_Q13,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q1�������T3,	,	$14,	$15
//	0x0065,	0x0100010800FF,	CMon_MD_Q14,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q1�������T4,	,	$14,	$15
//	0x0066,	0x0100010800FF,	CMon_MD_Q15,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q1�������T5,	,	$14,	$15
//	0x0067,	0x0100010800FF,	CMon_MD_Q16,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q1�������T6,	,	$14,	$15
//	0x0068,	0x0100010800FF,	CMon_MD_Q17,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q1�������T7,	,	$14,	$15
//	0x0069,	0x0100010800FF,	CMon_MD_Q18,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q1�������T8,	,	$14,	$15
//	0x006A,	0x0100010800FF,	CMon_MD_Q20,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q2���������,	,	$14,	$15
//	0x006B,	0x0100010800FF,	CMon_MD_Q21,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q2�������T1,	,	$14,	$15
//	0x006C,	0x0100010800FF,	CMon_MD_Q22,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q2�������T2,	,	$14,	$15
//	0x006D,	0x0100010800FF,	CMon_MD_Q23,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q2�������T3,	,	$14,	$15
//	0x006E,	0x0100010800FF,	CMon_MD_Q24,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q2�������T4,	,	$14,	$15
//	0x006F,	0x0100010800FF,	CMon_MD_Q25,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q2�������T5,	,	$14,	$15
//	0x0070,	0x0100010800FF,	CMon_MD_Q26,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q2�������T6,	,	$14,	$15
//	0x0071,	0x0100010800FF,	CMon_MD_Q27,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q2�������T7,	,	$14,	$15
//	0x0072,	0x0100010800FF,	CMon_MD_Q28,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q2�������T8,	,	$14,	$15
//	0x0073,	0x0100010800FF,	CMon_MD_Q30,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q3���������,	,	$14,	$15
//	0x0074,	0x0100010800FF,	CMon_MD_Q31,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q3�������T1,	,	$14,	$15
//	0x0075,	0x0100010800FF,	CMon_MD_Q32,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q3�������T2,	,	$14,	$15
//	0x0076,	0x0100010800FF,	CMon_MD_Q33,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q3�������T3,	,	$14,	$15
//	0x0077,	0x0100010800FF,	CMon_MD_Q34,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q3�������T4,	,	$14,	$15
//	0x0078,	0x0100010800FF,	CMon_MD_Q35,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q3�������T5,	,	$14,	$15
//	0x0079,	0x0100010800FF,	CMon_MD_Q36,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q3�������T6,	,	$14,	$15
//	0x007A,	0x0100010800FF,	CMon_MD_Q37,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q3�������T7,	,	$14,	$15
//	0x007B,	0x0100010800FF,	CMon_MD_Q38,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q3�������T8,	,	$14,	$15
//	0x007C,	0x0100010800FF,	CMon_MD_Q40,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q4���������,	,	$14,	$15
//	0x007D,	0x0100010800FF,	CMon_MD_Q41,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q4�������T1,	,	$14,	$15
//	0x007E,	0x0100010800FF,	CMon_MD_Q42,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q4�������T2,	,	$14,	$15
//	0x007F,	0x0100010800FF,	CMon_MD_Q43,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q4�������T3,	,	$14,	$15
//	0x0080,	0x0100010800FF,	CMon_MD_Q44,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q4�������T4,	,	$14,	$15
//	0x0081,	0x0100010800FF,	CMon_MD_Q45,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q4�������T5,	,	$14,	$15
//	0x0082,	0x0100010800FF,	CMon_MD_Q46,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q4�������T6,	,	$14,	$15
//	0x0083,	0x0100010800FF,	CMon_MD_Q47,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q4�������T7,	,	$14,	$15
//	0x0084,	0x0100010800FF,	CMon_MD_Q48,	DLen_4,		F_DRS_ReadEN+DRS_Eeprom2, 		DLen_5,		DLen_3,		DDU_kvar,	//EEPROM:00000.000,	R,	��ʱˢ�£�Kw,	�޹�Q4�������T8,	$13,	$14,	$15
	0x0085,	0x01,0x00,0x20,0x07,0x00,0xff,	(unsigned long)&Para.Ua[0],	DLen_3,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_4,		DLen_2,		DDU_V,	//RAM:0000.00,	R,	��ʱˢ�£�V,	A���ѹ,	,	$14,	$15
	0x0086,	0x01,0x00,0x34,0x07,0x00,0xff,	(unsigned long)&Para.Ub[0],	DLen_3,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_4,		DLen_2,		DDU_V,	//RAM:0000.00,	R,	��ʱˢ�£�V,	B���ѹ,	,	$14,	$15
	0x0087,	0x01,0x00,0x48,0x07,0x00,0xff,	(unsigned long)&Para.Uc[0],	DLen_3,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_4,		DLen_2,		DDU_V,	//RAM:0000.00,	R,	��ʱˢ�£�V,	C���ѹ,	,	$14,	$15
	0x0088,	0x01,0x00,0x1F,0x07,0x00,0xff,	(unsigned long)&Para.Ia[0],	DLen_3,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_3,		DLen_3,		DDU_A,	//RAM:000.000,	R,	��ʱˢ�£�A,	A�����,	,	$14,	$15
	0x0089,	0x01,0x00,0x33,0x07,0x00,0xff,	(unsigned long)&Para.Ib[0],	DLen_3,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_3,		DLen_3,		DDU_A,	//RAM:000.000,	R,	��ʱˢ�£�A,	B�����,	,	$14,	$15
	0x008A,	0x01,0x00,0x47,0x07,0x00,0xff,	(unsigned long)&Para.Ic[0],	DLen_3,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_3,		DLen_3,		DDU_A,	//RAM:000.000,	R,	��ʱˢ�£�A,	C�����,	,	$14,	$15
	0x008B,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.Freq[0],	DLen_2,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_2,		DLen_2,		DDU_Hz,	//RAM:00.00,	R,	��ʱˢ�£�Hz,	����Ƶ��,	,	$14,	$15
	0x008C,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.Freq[0],	DLen_2,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_2,		DLen_2,		DDU_Hz,	//RAM:00.00,	R,	��ʱˢ�£�Hz,	A��Ƶ��,	,	$14,	$15
	0x008D,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.Freq[0],	DLen_2,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_2,		DLen_2,		DDU_Hz,	//RAM:00.00,	R,	��ʱˢ�£�Hz,	B��Ƶ��,	,	$14,	$15
//	0x008E,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.P[0],		DLen_2,		F_DRS_ReadEN+DRS_instantaneous, 	DLen_2,		DLen_2,		DDU_Hz,	//RAM:00.00,	R,	��ʱˢ�£�Hz,	C��Ƶ��,	,	$14,	$15
	0x008F,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.Pa[0],	DLen_4,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_5,		DLen_3,		DDU_kw,	//RAM:00000.000,	R,	��ʱˢ�£�Kw,	A�๦��,	,	$14,	$15
	0x0090,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.Pb[0],	DLen_4,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_5,		DLen_3,		DDU_kw,	//RAM:00000.000,	R,	��ʱˢ�£�Kw,	B�๦��,	,	$14,	$15
	0x0091,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.Pc[0],	DLen_4,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_5,		DLen_3,		DDU_kw,	//RAM:00000.000,	R,	��ʱˢ�£�Kw,	C�๦��,	,	$14,	$15
//	0x0092,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.P[0],		DLen_4,		F_DRS_ReadEN+DRS_instantaneous, 	DLen_5,		DLen_3,		DDU_kw,	//RAM:00000.000,	R,	��ʱˢ��,	���๦��,	,	$14,	$15
	0x0093,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.Pfa[0],	DLen_2,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_2,		DLen_2,		0,	//RAM:00.00,	R,	��ʱˢ��,	A�๦������,	,	$14,	$15
	0x0094,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.Pfb[0],	DLen_2,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_2,		DLen_2,		0,	//RAM:00.00,	R,	��ʱˢ��,	B�๦������,	,	$14,	$15
	0x0095,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.Pfc[0],	DLen_2,		F_DRS_ReadEN+DRS_instantaneous+F_DRS_SYNData, 	DLen_2,		DLen_2,		0,	//RAM:00.00,	R,	��ʱˢ��,	C�๦������,	,	$14,	$15
//	0x0096,	0x01,0x00,0x01,0x08,0x00,0xFF,	(unsigned long)&Para.Pf[0],	DLen_2,		F_DRS_ReadEN+DRS_instantaneous, 	DLen_2,		DLen_2,		0,	//RAM:00.00,	R,	��ʱˢ��,	���๦������,	,	$14,	$15
	
	0x0097,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+DRS_Ram, 			DLen_4,		DLen_0,		0,	//RAM:0000,	R,	,	A��ÿ��������,	,	$14,	$15
	0x0098,	0x01,0x00,0x01,0x08,0x00,0xFF, 0x0000,		DLen_2,		F_DRS_ReadEN+DRS_Ram, 			DLen_4,		DLen_0,		0,	//RAM:0000,	R,	,	B��ÿ��������,	,	$14,	$15
	0x0099,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+DRS_Ram, 			DLen_4,		DLen_0,		0,	//RAM:0000,	R,	,	C��ÿ��������,	,	$14,	$15
	0x00A0,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+DRS_Ram, 			DLen_4,		DLen_0,		0,	//RAM:0000,	R,	,	����ÿ��������,	,	$14,	$15
	0x00A1, 0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+DRS_Ram, 			DLen_2,		DLen_0,		0,	//RAM:00,	R,	,	������״̬��,	,	$14,	$15
	0x00A2,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+DRS_Ram, 			DLen_2,		DLen_0,		0,	//RAM:00,	R,	,	��ѹ״̬��,	,	$14,	$15
	0x00A3,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+DRS_Ram, 			DLen_2,		DLen_0,		0,	//RAM:00,	R,	,	����״̬�֣������ͷ���,	,	$14,	$15
	0x00A4,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+DRS_instantaneous, 	DLen_3,		DLen_1,		0,	//RAM:000.0,	R,	,	����оƬ�¶�,	,	$14,	$15
	0x00A5,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_20,	F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2,	DLen_20,	DLen_0,		0,	//EEPROM:,	R/W,	,	���,	,	$14,	$15
	0x00A6,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+DRS_Ram, 			DLen_4,		DLen_0,		0,	//RAM:0000,	R,	,	�������״̬��1,	,	$14,	$15
	0x00A7,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+DRS_Ram, 			DLen_4,		DLen_0,		0,	//RAM:0000,	R,	,	�������״̬��2,	,	$14,	$15
	0x00A8,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+DRS_Ram, 			DLen_4,		DLen_0,		0,	//RAM:0000,	R/W,	,	�������״̬��3,	,	$14,	$15
	0x00A9,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+DRS_Ram, 			DLen_4,		DLen_0,		0,	//RAM:0000,	R,	,	����״̬��1,	,	$14,	$15
	0x00AA,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+DRS_Ram, 			DLen_4,		DLen_0,		0,	//RAM:0000,	R,	,	����״̬��2,	,	$14,	$15
	0x00AB,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+DRS_Ram, 			DLen_2,		DLen_0,		0,	//RAM:00,	R,	,	����״̬��,	,	$14,	$15
	0x00AC,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+DRS_Ram, 			DLen_2,		DLen_0,		0,	//RAM:00,	R,	,	���ǿ���״̬��,	,	$14,	$15
	0x00AD,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_7,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Ram+F_DRS_SYNData, 	DLen_6,		DLen_0,		DDU_Time,	//RAM:SSMMHH,	R/W,	,	ʱ��,	,	$14,	$15
	0x00AE,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_3,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Ram+F_DRS_SYNData, 	DLen_6,		DLen_0,		DDU_Date,	//RAM:DDMMYY,	R/W,	,	����,	,	$14,	$15
	0x00AF,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2, 	DLen_2,		DLen_0,		0,	//RAM:00-(00����01�ģ�,	R/W,	,	������ʱ״̬��,	,	$14,	$15
	0x00B0,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2, 	DLen_2,		DLen_0,		0,	//RAM:00,	R/W,	,	����״̬��,	,	$14,	$15
	0x00B1,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_30,	F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2, 	DLen_30,	DLen_0,		0,	//RAM:,	R/W,	,	����ʱ�α�,	,	$14,	$15
	0x00B2,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2, 	DLen_2,		DLen_0,		0,	//RAM:00,	R/W,	,	��������ģʽ,	,	$14,	$15
	0x00B3,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2, 	DLen_2,		DLen_0,		0,	//RAM:00,	R/W,	,	��������,	,	$14,	$15
	0x00B4,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2, 	DLen_2,		DLen_0,		0,	//RAM:00,	R/W,	,	��������ʱ��,	,	$14,	$15
	0x00B5,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2, 	DLen_2,		DLen_0,		0,	//RAM:00,	R/W,	,	��������ģʽ,	,	$14,	$15
	0x1007,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2+F_DRS_SYNData, 	DLen_2,		DLen_0,		0,	//RAM:00,	R/W,	,	��ʾģʽ,	,	$14,	$15
	0x1008,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2+F_DRS_SYNData, 	DLen_2,		DLen_0,		0,	//RAM:00,	R/W,	,	��ʾλ��,	,	$14,	$15
	0x1009,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_1,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2+F_DRS_SYNData, 	DLen_2,		DLen_0,		0,	//RAM:00,	R/W,	,	��ʾ����ʱ��,	,	$14,	$15
	0x100a,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_30,	F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2+F_DRS_SYNData, 	DLen_30,	DLen_0,		0,	//RAM,	R/W,	,	��ʾ�б�,	,	$14,	$15
	0x00C0,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_40,	F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2, 	DLen_40,	DLen_0,		0,	//RAM,	R/W,	,	����������ʾ��,	,	$14,	$15
	0x00C1,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_40,	F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom2, 	DLen_40,	DLen_0,		0,	//RAM,	R/W,	,	���������ʾ,	,	$14,	$15
	0x00C2,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_30,	F_DRS_ReadEN+DRS_Eeprom2, 		DLen_30,	DLen_0,		0,	//RAM,	R,	,	�¼���¼(����ģ����ص��¼���,	,	$14,	$15
	
	///-------У��---------------------
	//----------1p meter---------
	0xF1C1,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////  ��ѹ
	0xF1C2,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////������Чֵƫ��       
	0xF1C3,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////����            
	0xF1C4,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////��������          
	0xF1C5,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////����ƫ��                    
	0xF1C6,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////��λ            
	0xF1C7,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////��һ�η����Եķֽ��    
	0xF1C8,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////�ڶ��η����Եķֽ��
	0xF1C9,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////�����η����Եķֽ��  
	0xF1CA,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////��һ���ֽ�����µ���λУ׼            
	0xF1CB,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////��һ���ֽ��������ڶ����ֽ��            
	0xF1CC,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////�ڶ����ֽ��������������ֽ��          
	0xF1CD,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////�������ֽ�����ϵ���λУ׼ֵ                    
	0xF1CE,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////У���           
	///---------3p meter+F_DRS_SYNData
	0xF3C1,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_6,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_6,	DLen_0,		0,	////A��B��C���ѹУ׼��׼(7)   
	0xF3C2,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_6,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_6,	DLen_0,		0,	////У�����ϵ��(7)            
	0xF3C3,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_6,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_6,	DLen_0,		0,	////У���ѹϵ��(7)            
	0xF3C4,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_6,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_6,	DLen_0,		0,	////У���й�offset(7)          
	0xF3C5,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_6,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_6,	DLen_0,		0,	////��λ(7)                    
	0xF3C6,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_6,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_6,	DLen_0,		0,	////У���޹�offset(7)            
	0xF3C7,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_6,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_6,	DLen_0,		0,	////�޹���λ(7)    
	0xF3C8,	0x01,0x00,0x01,0x08,0x00,0xFF,	0x0000,		DLen_2,		F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	////ʱ�Ӿ���

	0x1001,0x01,0x01,0x00,0x00,0x01,0x80,	0x0000,	DLen_30,	F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	//���Ե�һ����ʾ 
	0x1002,0x01,0x02,0x00,0x00,0x01,0x80,	0x0000,	DLen_30,	F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	//���Եڶ�����ʾ 
	0x1003,0x01,0x03,0x00,0x00,0x01,0x80,	0x0000,	DLen_30,	F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	//���Ե�������ʾ 
	0x1004,0x01,0x04,0x00,0x00,0x01,0x80,	0x0000,	DLen_30,	F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	//���Ե�һ�� ,
	0x1005,0x01,0x05,0x00,0x00,0x01,0x80,	0x0000,	DLen_30,	F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	//���Եڶ��� ,
	0x1006,0x01,0x06,0x00,0x00,0x01,0x80,	0x0000,	DLen_30,	F_DRS_ReadEN+F_DRS_WriteEN+DRS_Eeprom1+F_DRS_SYNData, 		DLen_2,	DLen_0,		0,	//���Ե����� ,
};

const ID_OBIS ECTab[]=
{
	0x0001,	0x01,0x00,0x01,0x08,0x00,0xFF,DLen_6,
	0x0002,	0x01,0x00,0x01,0x08,0x01,0xFF,DLen_6,
	0x0003,	0x01,0x00,0x01,0x08,0x02,0xFF,DLen_6,
	0x0004,	0x01,0x00,0x01,0x08,0x03,0xFF,DLen_6,
	0x0005,	0x01,0x00,0x01,0x08,0x04,0xFF,DLen_6,
	
	0x000a,	0x01,0x00,0x02,0x08,0x00,0xFF,DLen_6,
	0x000b,	0x01,0x00,0x02,0x08,0x01,0xFF,DLen_6,
	0x000c,	0x01,0x00,0x02,0x08,0x02,0xFF,DLen_6,	
	0x000d,	0x01,0x00,0x02,0x08,0x03,0xFF,DLen_6,
	0x000e,	0x01,0x00,0x02,0x08,0x04,0xFF,DLen_6,
	
	0x0013,	0x01,0x00,0x03,0x08,0x00,0xFF,DLen_6,
	0x0014,	0x01,0x00,0x03,0x08,0x01,0xFF,DLen_6,
	0x0015,	0x01,0x00,0x03,0x08,0x02,0xFF,DLen_6,
	0x0016,	0x01,0x00,0x03,0x08,0x03,0xFF,DLen_6,
	0x0017,	0x01,0x00,0x03,0x08,0x04,0xFF,DLen_6,
	
	0x001c,	0x01,0x00,0x04,0x08,0x00,0xFF,DLen_6,
	0x001d,	0x01,0x00,0x04,0x08,0x01,0xFF,DLen_6,
	0x001e,	0x01,0x00,0x04,0x08,0x02,0xFF,DLen_6,
	0x001f, 0x01,0x00,0x04,0x08,0x03,0xFF,DLen_6,
	0x0020,	0x01,0x00,0x04,0x08,0x04,0xFF,DLen_6,
};

const ID_OBIS RealTab[]=
{
	0x0085,	0x01,0x00,0x20,0x07,0x00,0xff,DLen_3,
	0x0086,	0x01,0x00,0x34,0x07,0x00,0xff,DLen_3,
	0x0087,	0x01,0x00,0x48,0x07,0x00,0xff,DLen_3,
	0x0088,	0x01,0x00,0x1F,0x07,0x00,0xff,DLen_3,
	0x0089,	0x01,0x00,0x33,0x07,0x00,0xff,DLen_3,
	0x008A,	0x01,0x00,0x47,0x07,0x00,0xff,DLen_3,
};







	


