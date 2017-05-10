
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include <includes.h>
#include "type.h"
#include "data.h"
#include "port.h"
#include "serial.h"
#include "hdlc.h"
#include "aes.h"
#include "wmbus.h"
#include "AESGCM.h"
#include "uECC.h"
#include "mbedtls/sha256.h"
#include <stdlib.h>
#include "iec1107.h"
#include "GetMeterData.h"
#include "MeterDataType.h"

void run_test(void)
{
	#if 1
	if(GPIO->PB&P_YGLED)
	{
		GPIO->PBCLR |= P_YGLED;
	}
	else
	{
		GPIO->PBSET |= P_YGLED;
	}
	#else
	if(GPIO->PA&1<<26)
	{
		GPIO->PACLR |= (1<<26);
	}
	else
	{
		GPIO->PASET |= (1<<26);
	}
	#endif
}
#if 1
uint8_t buf[256];
void serial_test(void)
{

	uint16_t i;
	for(i=0;i<32;++i)
	{
		buf[i]=i;
	}
	Serial_Write(1,buf,10);
	//CmGprs_Write(buf,32);
	//Serial_Read(buf,512);
	// CM_HDLC_Receive();
}
#endif
void ProcHalfSec(void)
{
	
	Flag.Clk &= ~F_HalfSec;
//	serial_test();
//	run_test();
//	CM_HDLC_Receive();
}

extern uint32_t sec;
void Cm_Ram_Inter(uint8_t *buf,uint16_t Len);
void Signature_Measure(void);
void ProcSec(void)
{
	int i;
	uint64_t m_me;
	uint8_t *m_malloc_buf;
	Flag.Clk &= ~F_Sec;
//	serial_test();
#if 0	
	E2P_RData(&m_me,CMon_EC_Pp0,8);
	Cm_Ram_Inter((uint8_t *)&m_me,8);
	m_me++;
	Cm_Ram_Inter((uint8_t *)&m_me,8);
	E2P_WData(CMon_EC_Pp0,&m_me,8);
	
	E2P_RData(&m_me,CMon_EC_Pn0,8);
	Cm_Ram_Inter((uint8_t *)&m_me,8);
	m_me++;
	Cm_Ram_Inter((uint8_t *)&m_me,8);
	E2P_WData(CMon_EC_Pn0,&m_me,8);
#endif	
/*	Para.Pp0++;
	Para.Pn0++;
	Para.Ua=220;
	Para.Ub=221;
	Para.Uc=219;
	Para.Pt=2000;*/
	Signature_Measure();
	Comm.SecPulseCnt++;
	sec++;
	Judge_Cryto();
	//ID_Read(&Para.Ua[0],0x0085,DLen_3);
//	SynData1s();
//m_malloc_buf = malloc(10);
//free(m_malloc_buf);
//	serial_test();
//	CmWmbus_Read(buf,32);
//	for(i=0;i<32;++i)
//	{
	//	buf[i]=i;
//	}
//	CmWmbus_Write(0x61,buf,32);
}	

void ProcMin(void)
{
		Flag.Clk &= ~F_Min;
	// serial_test();
} 
/***************************************************
	Working for Every Minute
	1. Decreasing Minute Timer
***************************************************/
void ProcHour(void)
{
	Flag.Clk &= ~F_Hour;
}

void ProcDay(void)
{
	Flag.Clk &= ~F_Day;
}	
//#define TEST 1
#ifdef TEST
//uint8_t plaintext[24]="123456789001234033333336";
//uint8_t keytext[16]="0000000000000000";
uint8_t plaintext[24]={0x01,0x00,0x00,0x00,0x19,0xff,0xff,0xff,0xff};
//uint8_t plaintext[24]={0x80,0x00,0x00,0x00,0x0,0,0,0,0,0,0,0,0};
//uint8_t keytext[16]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//ISK PUBLIC KEY
uint8_t keytext[16]={0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};
//uint32_t iv=0;
extern uint8_t iv[16];//={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t cix[32];
uint8_t pix[32];
uint8_t tag[32]={0xD0,0x70,0x07,0xf7,0x83,0x67,0xbd,0x90,0x4c,0x58,0x02,0x16,0x07,0x1a,0xbc,0x76,0xD0,0x70,0x07,0xf7,0x83,0x67,0xbd,0x90,0x4c,0x58,0x02,0x16,0x07,0x1a,0xbc,0x76};
uint32_t addr=(0x0D020D74);
uint32_t tx_seq=0x1;
extern	struct S_Hdlc_LMN_Info m_lmn_info;
	extern	int mbedtls_aes_self_test( int verbose );
#endif
	extern	struct S_Hdlc_LMN_Info m_lmn_info;
	extern uint32_t ms_count;
	extern uint8_t keytext[16];
	extern uint8_t Kenc[16],Kmac[16],Lenc[16],Lmac[16];
	#if 0
unsigned char plaintext1[576]={
0x03,0x00,0x00,0x02,0x29,0x00,0x00,0x01,0x67,0x18,0xC6,0xEC,0x7C,0x09,0x06,0x97,
0xEC,0x3D,0xEF,0x8E,0x45,0xD6,0x57,0x0C,0x0C,0xED,0x45,0xFD,0x72,0x72,0x60,0xE4,
0x51,0x1A,0x48,0x30,0xF1,0x3B,0x81,0xB8,0xB0,0x63,0x65,0x95,0x2C,0x79,0xE6,0x35,
0xB6,0x30,0xE0,0xA0,0x1C,0x35,0x44,0x46,0x0E,0xFD,0xFB,0x4B,0x32,0x1E,0x46,0x63,
0x4F,0x6D,0x32,0xEA,0x01,0x54,0x83,0xD3,0xA9,0x7D,0x46,0x14,0xA2,0xD2,0x4B,0x34,
0x61,0x8C,0x64,0x83,0xE4,0x5C,0x4C,0x25,0xF9,0x16,0x89,0xFD,0x96,0x63,0xB0,0xAE,
0x48,0xBD,0xC7,0xE6,0xCE,0x7C,0x27,0x54,0xD1,0xA5,0x64,0xA5,0xA5,0xB9,0x72,0x1E,
0x0C,0x21,0x70,0x6E,0x86,0xC3,0xCF,0x05,0xA3,0x41,0xFB,0x49,0xA7,0xA5,0xF2,0x07,
0x93,0xE8,0x89,0xD3,0x4A,0xAE,0x20,0x96,0xD0,0x78,0x2F,0x36,0xA4,0x24,0x7F,0x25,
0x7A,0x3C,0x0A,0x6B,0xF8,0x73,0x2F,0x5F,0xF7,0x21,0x80,0x99,0xF9,0xD4,0xC7,0xCA,
0x72,0x9F,0x79,0x5E,0x6A,0x0C,0x3B,0xB7,0xEC,0x6B,0x9F,0x11,0x15,0xDB,0x0B,0x3F,
0x2A,0xC3,0x20,0xC3,0x27,0x5D,0x64,0xAF,0xAA,0x76,0x18,0x92,0x32,0xDB,0x6D,0x48,
0x21,0x81,0x56,0xC5,0x01,0xE4,0xA4,0x27,0x56,0xBA,0xA9,0xA6,0x23,0xA0,0x5E,0xBB,
0xFB,0xF8,0xDF,0xF8,0xCC,0xCB,0x8B,0x8C,0xCA,0x7A,0x8C,0x9A,0xBC,0xA0,0x4F,0x58,
0xC4,0x07,0x9B,0x4C,0xD9,0x1A,0xD5,0x9F,0x83,0x36,0x99,0xBF,0xB0,0x58,0x99,0xE0,
0x6F,0xAD,0x14,0x35,0x13,0xEB,0xC3,0x6D,0xAD,0x98,0x63,0x25,0x2F,0xFC,0x99,0x1F,
0x25,0x8B,0xD9,0x12,0xC4,0xD6,0x01,0xFA,0x94,0x80,0xF7,0xE0,0x23,0xBD,0x48,0x01,
0x4C,0x7A,0x08,0xD4,0xE4,0xB7,0xC6,0x7C,0xA4,0x58,0xBE,0x59,0xCB,0x6F,0xEB,0x8E,
0x97,0x9B,0xB9,0x67,0x73,0x57,0xF0,0x9B,0x8B,0x8C,0x4E,0x27,0xD5,0x27,0x4A,0xE4,
0xBB,0xFE,0x75,0x96,0xD9,0x0F,0x3F,0xB4,0x0E,0x5B,0x78,0xD0,0xE8,0x7F,0xD4,0x9C,
0x73,0xA5,0x41,0x7E,0x20,0xC2,0xF9,0xFD,0x56,0x74,0x8D,0x7A,0x2C,0x0D,0x85,0x0A,
0xB1,0xFA,0xEB,0xE6,0xAA,0xD5,0x1B,0x19,0xD1,0xAC,0xE5,0xD6,0x70,0x2C,0xD7,0x55,
0x59,0x57,0x63,0x03,0x7B,0xBA,0x33,0x3B,0xF8,0x46,0x86,0x25,0x7F,0x68,0xB4,0xF2,
0x3E,0xF5,0x18,0xF3,0x03,0x7A,0xC1,0xEC,0xBE,0xA0,0x78,0xE8,0x70,0x66,0xCA,0xA2,
0xB2,0x9A,0x40,0x24,0x56,0x64,0x61,0xFB,0xDF,0x8B,0xB8,0xA5,0xA6,0x08,0xDD,0xC7,
0x0A,0xB4,0x11,0x4C,0x9F,0x16,0xEB,0xE4,0xEF,0x11,0x20,0x65,0xBD,0x04,0x64,0xD4,
0xCB,0x84,0xD2,0x9F,0x87,0xB5,0xA8,0xE9,0x52,0x89,0x66,0x4B,0x90,0x86,0xE9,0x4C,
0x07,0xCA,0x59,0x58,0xF8,0xC8,0xBE,0x7B,0x37,0x2D,0x20,0x9D,0xE7,0x9C,0x87,0xF2,
0x8D,0xB1,0xF5,0x58,0xD4,0x82,0xA6,0xC2,0x60,0x0C,0x1A,0x70,0x15,0x54,0x97,0xC8,
0x4F,0xB1,0x0C,0xFC,0x9D,0x0B,0x98,0xD8,0x91,0x3D,0x00,0x85,0xBA,0x02,0x89,0xD6,
0xB4,0xA9,0x54,0xFB,0xAA,0x60,0x44,0x25,0x52,0x13,0xCC,0x09,0x93,0x56,0x56,0xDD,
0x61,0x81,0xA9,0x46,0xD6,0xC4,0x07,0x51,0x7A,0xAD,0x4A,0xB9,0x84,0xB3,0x32,0x0F,
0xE8,0xD8,0xA9,0x80,0xFF,0xFD,0xB2,0xFD,0x50,0x85,0xCD,0x8C,0x4F,0xEC,0x95,0xFE,
0xCF,0x45,0x65,0x35,0xC5,0x07,0x96,0x6E,0x67,0xB4,0x67,0x73,0xF0,0x9D,0xF5,0x34,0x74,0x22,0x88,0x61,0x1B,0x78,0x2B,0x06,0xE8
/*0x03,0x00,0x00,0x02,0x39,0x00,0x00,0x01,0x6B,0x64,0x16,0x0F,0xEC,0xB2,0x0C,0xE0,
0x42,0x28,0xF5,0x29,0x5E,0xFF,0x66,0x22,0xB6,0xE1,0xFE,0x99,0x35,0x86,0x79,0xF7,
0x1B,0x17,0x03,0xD5,0x8F,0x88,0x00,0xC8,0xF0,0x43,0x59,0xA7,0x51,0x05,0x47,0x55,
0xA5,0x5A,0x60,0x7A,0xAB,0xCE,0xC0,0x6E,0x34,0x4D,0x8F,0x4E,0x5C,0x8D,0x6C,0xBC,
0x99,0x46,0x84,0x8B,0x72,0x96,0xFD,0xFB,0x5D,0xC6,0x32,0xA1,0x3E,0x16,0x8A,0xBF,
0x9E,0x2D,0x2F,0xDF,0x67,0x64,0x9E,0x35,0x9C,0x0E,0xD8,0xD5,0x0F,0xA4,0xEF,0x77,
0xEE,0xEB,0xB8,0x70,0x44,0x1A,0xAD,0xFA,0x95,0xE9,0x11,0xC8,0x3A,0xC2,0x81,0x53,
0x28,0x1A,0x4C,0xCD,0xC8,0x69,0x81,0xCE,0x85,0xB0,0x5E,0x3B,0xC3,0x69,0xCA,0xDD,
0x6A,0xF0,0x70,0x22,0x08,0x00,0x4C,0x90,0x8A,0x35,0x9C,0x46,0x60,0x98,0x92,0x01,
0x7F,0xC3,0x46,0x08,0xA1,0x09,0x68,0x29,0xFE,0x0A,0x68,0xA7,0xFD,0x08,0xED,0x01,
0xEC,0xEC,0x3E,0x39,0x4A,0x51,0x84,0x0B,0xC8,0x47,0x89,0x3D,0x56,0xCF,0xF2,0x07,
0x9F,0xFA,0xF7,0x65,0x43,0x81,0x4D,0xF3,0x53,0x12,0xDB,0xE1,0xDD,0x1A,0x8B,0x01,
0xF3,0xEF,0x9C,0x10,0x6E,0xB8,0x53,0x78,0x7B,0xA2,0x23,0x6F,0x09,0x93,0x95,0xEC,
0x07,0xCE,0x0D,0x27,0xF6,0x63,0x27,0x80,0xA2,0xA0,0x76,0x9F,0xA4,0x54,0x38,0x72,
0x65,0xCB,0xD4,0x77,0xA6,0x8E,0x77,0xF3,0x43,0xA2,0x6C,0x8F,0x16,0xE1,0x16,0x37,
0x1B,0x18,0x7B,0x16,0xC5,0x8C,0x95,0x44,0xCA,0x92,0x0C,0x8F,0x28,0xC8,0x33,0x71,
0xF7,0xD8,0x56,0x06,0x5D,0x94,0xBE,0xBF,0xDD,0xB2,0xF4,0xFD,0x06,0xA0,0x33,0x92,
0xBD,0xA8,0xD0,0x79,0xB5,0x08,0x09,0x8C,0xE0,0x58,0x14,0x3D,0x9A,0xE0,0xE0,0xD1,
0x93,0x27,0xBE,0xA6,0xA4,0x94,0x06,0x70,0xFD,0x37,0xBA,0x7F,0x35,0x5A,0xF1,0x11,
0x29,0xBA,0xC5,0x6D,0x55,0x66,0xCD,0x7E,0xEE,0x56,0x94,0xA6,0x53,0xAA,0xD8,0xBD,
0x2C,0xF1,0x77,0x15,0xB3,0xDB,0x58,0x31,0x04,0x32,0xB0,0x66,0x57,0xDA,0x9D,0x21,
0x38,0xEC,0x8C,0x9C,0x70,0x05,0x30,0x35,0x12,0x3D,0xFE,0xC6,0xA4,0x74,0x15,0xE9,
0xD2,0x5B,0x53,0x22,0x91,0x86,0xCA,0xCE,0x05,0x2B,0x69,0x18,0xCB,0xD8,0x02,0x67,
0x9D,0x37,0xB9,0x2F,0x51,0x11,0xB7,0xFE,0x47,0x0C,0xCF,0x00,0xD5,0x6B,0xD3,0x3F,
0xB7,0x76,0xEA,0xE1,0x01,0x41,0x3A,0x0A,0x08,0x17,0xCA,0x58,0xC4,0x15,0x6D,0x6C,
0x1A,0xA2,0xA7,0xF8,0x1D,0xE4,0xD5,0x27,0xD2,0xB1,0xAD,0xEA,0xB5,0xD5,0xEF,0x75,
0x1F,0xEB,0xEE,0x39,0x4F,0xED,0x49,0xE7,0x5B,0x69,0x6E,0x40,0x1E,0x29,0xE7,0xD8,
0xFF,0xC0,0x93,0x96,0x6D,0x34,0xEC,0x4D,0xBC,0x07,0x74,0x20,0xC2,0xBC,0x49,0x38,
0x1D,0xA5,0x7A,0x1B,0x0A,0xA4,0xDF,0x8B,0x59,0xD6,0xDF,0x6E,0x56,0xBA,0x6F,0x95,
0x3F,0xE7,0xCB,0xBC,0x15,0xA9,0x8E,0x01,0xCB,0x13,0x10,0xA0,0xAF,0xA0,0x14,0x22,
0x76,0xDF,0x74,0xB5,0xC3,0x88,0xB5,0x44,0x58,0xA4,0x12,0x32,0xE2,0x45,0x9D,0xC2,
0xA0,0x95,0x10,0x16,0xE2,0xE4,0x78,0x9E,0x70,0xF7,0x9C,0xFC,0x52,0x13,0x74,0xE8,
0xDC,0x82,0xCD,0x42,0xC9,0x78,0xAC,0x46,0x41,0x00,0x81,0xB9,0x95,0x8A,0xAC,0x9E,
0xDE,0xCF,0x41,0xC3,0xDC,0x01,0x77,0xC2,0x5B,0xB6,0xBE,0x20,0x30,0xCD,0xB5,0x89,
0xA1,0xE1,0x82,0xE0,0xBE,0xEB,0x4E,0xF9,0xAC,0x9D,0x1B,0x26,0x49,0xBA,0x6F,0x82,
0x5E,0x1C,0x63,0x67,0x45,0x13,0x62,0xF5,0x02*/
/*0x03,0x00,0x00,0x02,0x39,0x00,0x00,0x01,0x6F,0x68,0xD6,0xC6,0x6E,0x25,0x7F,0xB3,
0xAB,0x07,0xFB,0x32,0x7B,0x14,0x6B,0xA5,0xA2,0x9F,0x32,0xE5,0x96,0xBE,0xBB,0x7C,
0x35,0x07,0x15,0xA1,0x9C,0x1F,0x6F,0x01,0x28,0x63,0x5A,0x82,0xC1,0xAD,0x2B,0x23,
0xEB,0x61,0x09,0x98,0x10,0xD2,0x01,0x90,0x89,0x7A,0x9E,0x0A,0xF3,0x27,0x6C,0x56,
0xB2,0xC0,0xCA,0x34,0xFD,0xA9,0x33,0xE5,0x96,0x15,0xEC,0x18,0xFC,0xC7,0x18,0x61,
0x08,0xEE,0x33,0x5D,0x32,0x2D,0xA8,0xFD,0x9F,0xEF,0x0E,0x1A,0x06,0xA5,0xDB,0x94,
0x35,0x55,0xAC,0x92,0x17,0xD6,0x4E,0xBD,0xEA,0x56,0x55,0xD7,0xE3,0x05,0xD4,0x03,
0x15,0x30,0x68,0x57,0x52,0xFE,0x88,0xEE,0x44,0x54,0x90,0x39,0x5D,0x72,0x99,0xDD,
0x47,0x49,0x1A,0x0F,0xC1,0xE2,0x51,0x71,0xC7,0xD2,0xD6,0xE6,0xC8,0xB1,0x8A,0x49,
0x49,0x84,0x67,0x4D,0x49,0xBA,0xAD,0xAD,0xFB,0xFE,0x4F,0x2F,0x86,0x70,0x77,0x26,
0xC8,0xA5,0x50,0x9B,0xD2,0x35,0x6F,0x8C,0xEF,0xCD,0x50,0x90,0x56,0x14,0x56,0x97,
0x02,0xF9,0x60,0x93,0x4A,0xE5,0x1B,0xD6,0xD8,0x3F,0xC9,0xE4,0xED,0x60,0x20,0x5E,
0x3F,0x85,0xAB,0xC9,0xF6,0x6F,0xA4,0x66,0xF1,0xA2,0x32,0x6A,0xAB,0xDD,0x6A,0x60,
0xAA,0x7F,0x1C,0x6E,0x10,0x22,0x81,0x6B,0xA8,0xCB,0x57,0xD3,0x28,0x12,0x90,0x85,
0xA6,0xBF,0xE9,0xBA,0x62,0xC8,0x50,0xC8,0x6B,0x82,0x4A,0x42,0xC0,0x70,0xF0,0x55,
0xA0,0x56,0xFD,0xAF,0x9A,0x85,0x9C,0xD5,0x85,0x44,0xDD,0x4E,0xA1,0xC6,0x50,0xCB,
0xF7,0xB3,0x92,0x43,0x3B,0xDA,0x56,0x08,0x63,0xC6,0xF2,0xE2,0xE6,0x65,0x22,0xDF,
0x1F,0xC6,0x16,0x30,0x6F,0x17,0x83,0x74,0x1E,0x52,0xDC,0xF2,0xB0,0x84,0x87,0xCE,
0xD4,0xDC,0x6D,0x5F,0xBF,0x5F,0x21,0x86,0x03,0x3C,0x6E,0x36,0x8A,0x02,0x0F,0x54,
0x29,0x6C,0x9C,0x1D,0x2A,0x4A,0x08,0x10,0xDA,0xAB,0xF3,0x25,0xEC,0xFE,0x17,0xEF,
0x5F,0x8A,0x8A,0xD1,0x9B,0x83,0x7F,0xC7,0xBA,0xBE,0x7A,0x46,0xD1,0x70,0xD3,0xC4,
0xEC,0x36,0xDF,0xBE,0x07,0xA1,0xBB,0x61,0xBB,0x7C,0x05,0xD2,0x24,0xB4,0xBC,0xF1,
0xF6,0xF8,0xA1,0x79,0x58,0x3C,0x98,0x70,0x43,0x1E,0x33,0x7D,0xB9,0xD5,0x21,0x37,
0xF0,0x86,0xB2,0xA0,0x84,0x9C,0x23,0x48,0xCB,0xEC,0xCD,0xA2,0x70,0x52,0x3C,0xA0,
0x1C,0xE0,0x97,0x08,0xE3,0x68,0x5B,0x3C,0xF3,0x15,0xBD,0xEB,0x99,0x47,0x38,0xA0,
0x2C,0xC3,0x41,0xAE,0x26,0x2A,0x4E,0x99,0x25,0x09,0x94,0x8F,0x43,0x14,0x77,0x8B,
0xB6,0x97,0x65,0x8B,0xC2,0x42,0x74,0xC9,0xC6,0x9E,0x32,0xB2,0xD9,0xFC,0xEA,0x7D,
0xAE,0x24,0xCB,0x17,0xA6,0xAD,0xA9,0x9F,0xD7,0xAE,0x2A,0x78,0x01,0x16,0x11,0x16,
0xDD,0x1D,0x88,0xE2,0x49,0xDF,0x2D,0xD2,0x64,0x06,0x82,0xC2,0x11,0x9D,0xBF,0x3F,
0x24,0x1A,0x27,0xC2,0x9B,0x4A,0x7F,0x09,0x16,0x50,0xC5,0xAA,0x2E,0xFC,0xDB,0x24,
0xBC,0xA9,0x6F,0x98,0x16,0x99,0x4D,0x17,0x7F,0xEC,0x27,0x6C,0x35,0x36,0x1F,0xC5,
0x73,0x45,0x3B,0xC3,0xE4,0x70,0xC2,0x01,0x30,0x7A,0x2A,0xCA,0x0E,0x49,0x82,0x37,
0x23,0x7A,0xFE,0x90,0x2D,0x34,0x64,0x37,0x42,0x0E,0x10,0x84,0x79,0xBF,0x6C,0x22,
0x4B,0x71,0x69,0x67,0x8C,0x86,0x06,0x0A,0x88,0x05,0xB5,0x67,0x93,0x0F,0x91,0x4B,
0xCF,0x7F,0x95,0x61,0xFF,0x41,0x38,0x31,0x7B,0xBF,0x00,0xF5,0x5F,0x0B,0x33,0x5D,
0xFD,0xEC,0x6C,0x76,0xD0,0x3D,0xAE,0xBC,0xE2*/
/*
0x04,0x00,0x00,0x01,0xB9,0x00,0x00,0x01,0x69,0xFB,0xF6,0xC3,0x35,0x0B,0xB7,0x6C,
0xE7,0xFA,0x29,0xC9,0xD6,0x45,0xC5,0x4A,0xE6,0xD4,0xB0,0x4A,0x85,0x38,0x69,0xD8,
0x46,0xB3,0xBC,0xAF,0xD6,0xCA,0x8D,0xE9,0x59,0xDA,0x94,0xF5,0x4A,0x3E,0x65,0x77,
0xF5,0x48,0x54,0x47,0x75,0x59,0x3F,0xB7,0xAD,0x31,0x69,0xC9,0x00,0xE9,0x79,0x81,
0x1B,0x17,0xEC,0x49,0xE4,0x47,0x5F,0x9E,0x3A,0x71,0xC5,0x5D,0xEF,0x32,0x40,0xC1,
0xF6,0x59,0x6D,0xCB,0xFD,0x0C,0xBA,0x93,0xB4,0x95,0x39,0xD2,0x06,0x90,0xD3,0x5B,
0x28,0x96,0xD1,0x33,0x76,0xB3,0x39,0x4C,0xCA,0xC3,0xDD,0x0B,0xA7,0x5C,0x29,0x1F,
0xAE,0xC7,0x4A,0x2D,0xDE,0x13,0x06,0x09,0x67,0xD2,0xFC,0xF9,0x83,0x1C,0xC9,0xA7,
0xAF,0x7A,0x87,0xE2,0x91,0xC4,0xFD,0xF4,0xDA,0xBD,0x92,0x11,0x20,0x73,0xD9,0xC3,
0x17,0x6D,0x5C,0x3D,0x2E,0x92,0xD8,0x72,0xA8,0xC9,0xED,0x6C,0xBC,0x92,0x74,0x89,
0xBA,0x55,0xC2,0x90,0xCC,0x50,0x56,0x7B,0x23,0x53,0xE0,0xDB,0x34,0x30,0x62,0xDA,
0x20,0x41,0x2E,0x22,0xBD,0x67,0x4F,0x36,0x4B,0x14,0x03,0x72,0xDA,0x7B,0xF4,0x62,
0x62,0x4F,0x5F,0xEF,0xAE,0x6E,0x24,0xFB,0x83,0x24,0xA6,0x9E,0xD4,0x2E,0x29,0x50,
0x6B,0x94,0x25,0xE2,0x64,0xC6,0xCA,0x96,0xC5,0x08,0x69,0x7A,0xAD,0xEF,0x6E,0x2D,
0xE5,0x15,0x8E,0x61,0x20,0xA1,0x31,0xF9,0xFA,0xD5,0xB4,0x64,0x38,0x63,0x6D,0x90,
0xF5,0xE7,0x3B,0x55,0xFC,0x80,0x7C,0xED,0x2B,0x1A,0x16,0x31,0xAB,0x72,0x9B,0xDC,
0x1C,0x8B,0x36,0x1B,0xDD,0xB8,0xD9,0xD8,0x6D,0x0A,0xBC,0xE2,0x9D,0x18,0xBA,0x0D,
0xD1,0x1C,0x55,0x5E,0x89,0x41,0x10,0x15,0xE7,0xB7,0x67,0x64,0x4C,0x01,0x20,0x37,
0xDC,0x72,0x41,0x3F,0xBF,0xF1,0x02,0xE2,0x8E,0xAA,0xCB,0x9B,0x7F,0xFB,0xA8,0xB1,
0x6D,0x79,0xB0,0x70,0x4E,0x0B,0x54,0x85,0x63,0xB3,0x68,0xC7,0x4E,0x06,0xAC,0x23,
0x8F,0x25,0xD9,0x3E,0xDF,0x7A,0x35,0xA1,0xB4,0xEB,0x57,0x45,0x51,0x3B,0xD7,0x1E,
0xA5,0x1F,0x6E,0xDA,0xBE,0x4F,0x15,0xC2,0xD2,0x24,0xC2,0x9A,0x77,0xA9,0xCB,0xDC,
0xD2,0xDB,0xFB,0xFE,0x7F,0xA8,0xDD,0xD5,0x7D,0x6D,0xB1,0xF9,0x06,0xAA,0xF1,0xF2,
0x82,0x6D,0x29,0x60,0x37,0x7F,0x1F,0xF9,0x9A,0x92,0xB8,0x31,0x10,0x92,0x91,0x68,
0x89,0x92,0xC9,0x6E,0x59,0x66,0x18,0xB0,0x0C,0x2D,0xC5,0x9A,0xDF,0x65,0x70,0x33,
0x48,0x20,0x8B,0xAE,0xC9,0xC7,0x09,0x37,0x51,0xA7,0xF8,0x9E,0xF9,0xE3,0x81,0x6C,
0x23,0xF3,0xF4,0x07,0x78,0x55,0x1E,0x0F,0x2C,0xB7,0x00,0x27,0x30,0x0B,0x29,0x35,
0x14,0x36,0xE0,0xA7,0xD7,0x9F,0x48,0xE7,0xAE*/
/*
0x03,0x00,0x00,0x02,0x29,0x00,0x00,0x01,0x73,0xD3,0xA2,0x23,0xAC,0x7F,0x09,0x1B,
0x46,0x02,0xA3,0xBD,0x59,0x1E,0x6C,0xF1,0x2F,0xEC,0x38,0xA9,0x5D,0x03,0x0C,0x7A,
0x22,0x19,0xBC,0x64,0xBB,0x0F,0x43,0x54,0x0F,0x8F,0x09,0xD5,0x18,0xD7,0xC4,0xE0,
0x58,0x1D,0x4B,0x67,0x1C,0xA3,0x5D,0xCF,0x51,0xF7,0x65,0x4C,0x97,0x08,0xF0,0x81,
0x13,0x86,0xA2,0x90,0x1D,0xA9,0x81,0xC6,0x4C,0xC3,0xE7,0xBA,0x56,0xFF,0x96,0xB3,
0xBF,0x44,0xB2,0xA7,0xEA,0xDE,0xD5,0x96,0x0D,0x0D,0xDB,0x19,0x6F,0x35,0xD7,0x46,
0x76,0x44,0x7B,0x55,0x93,0xB0,0x8C,0xB2,0x14,0xC0,0xB8,0x9E,0x11,0x49,0x59,0xE0,
0xA0,0x8D,0xAD,0x4D,0x37,0x8E,0x44,0x80,0x6A,0x3B,0x85,0xA4,0xEF,0xCA,0x02,0x38,
0x74,0x96,0x78,0xB0,0x27,0x58,0x98,0x00,0x17,0x66,0xC9,0xC0,0xC3,0x1F,0x7A,0x5F,
0x5F,0x59,0x2A,0x9E,0x9C,0x31,0x6B,0xAF,0x50,0xAF,0x5A,0xA8,0x4D,0xEF,0xAB,0xDF,
0x28,0x9C,0x27,0xF5,0xAC,0x7E,0x9D,0x05,0x4F,0xAB,0x94,0x59,0x48,0x34,0xA8,0x5A,
0xB5,0x10,0xA9,0x51,0x8E,0xAB,0xAF,0x10,0xC6,0xF1,0xA7,0x4D,0xDF,0xAC,0x9E,0x4E,
0x07,0xA5,0xAF,0x6E,0xEB,0x64,0xDA,0xCB,0x0E,0xD3,0xE3,0x5C,0x23,0x63,0x28,0xC0,
0x1A,0x58,0xF0,0x3D,0xB1,0x5A,0x38,0x49,0x7B,0x1A,0xE1,0x3A,0xBC,0xBD,0x77,0x8E,
0x36,0x63,0x49,0x8C,0xCE,0xD8,0x93,0xB3,0xFB,0xB6,0x92,0x40,0xA8,0x9F,0x9E,0x95,
0x66,0x9A,0xCB,0x7B,0xCA,0xDB,0x07,0x19,0xD7,0x84,0x83,0xAE,0xD9,0x56,0xC6,0x4A,
0x5E,0xC9,0x38,0xD5,0x1A,0xC9,0x39,0x03,0xF2,0xC9,0x00,0x74,0x5B,0x34,0xB6,0x55,
0x8A,0xD6,0x1D,0xD9,0xEF,0x51,0x7A,0x8B,0xBC,0x29,0x62,0xE0,0x0A,0x8A,0xBA,0x7A,
0xDC,0xF8,0x2C,0x5F,0xFF,0xB7,0x7D,0xC0,0x02,0x03,0xF8,0x6D,0xF8,0xC4,0x29,0x55,
0x83,0x6A,0x87,0xD0,0x3A,0x56,0xCF,0xC9,0x04,0xE0,0xF8,0xA2,0x91,0x13,0xC7,0xFB,
0x5D,0xF7,0x93,0x50,0x2E,0xB9,0x74,0x37,0x1E,0x48,0xFB,0xD7,0x47,0x5D,0x66,0xC2,
0xBF,0x14,0xEC,0xC4,0x4F,0x8F,0xDF,0x7E,0x00,0xB9,0xF0,0x95,0x6E,0xB1,0x51,0x2C,
0x0F,0xFB,0xEF,0x2C,0x7C,0x45,0xD6,0x1F,0x29,0x7E,0xD1,0x1C,0x20,0x08,0xE9,0xA0,
0x35,0xAB,0xCD,0x4B,0x38,0x4F,0xE1,0xFA,0x09,0x2C,0xB3,0xCC,0xB2,0x8A,0x07,0x38,
0xB4,0x42,0x6C,0xBA,0x63,0xA1,0x5E,0xDE,0xDD,0x77,0x6D,0x2E,0xC6,0xD9,0x6C,0x4A,
0x61,0x35,0xB7,0x89,0xC6,0xBC,0x7F,0x66,0xFE,0x9A,0xD9,0x36,0x0C,0x8B,0x44,0x00,
0x87,0x2E,0xCF,0xB8,0x45,0x18,0xED,0xBD,0x0E,0xE5,0xA4,0xCC,0x42,0xFB,0xB7,0x67,
0xC8,0x61,0xEB,0x7B,0xCF,0xB9,0x83,0x44,0x3E,0x94,0xB5,0xFB,0x7A,0x18,0xBF,0x24,
0xF9,0x0D,0x22,0xE3,0x33,0x93,0xA9,0xCB,0x83,0xD6,0xC3,0x9E,0x8B,0xB7,0x5A,0x28,
0xCC,0x92,0xF1,0x7A,0x71,0x7B,0xE6,0x46,0x6C,0xE2,0xCB,0x78,0x17,0xE8,0x88,0xB7,
0x70,0xEE,0xBC,0x48,0x79,0x0B,0x85,0xCB,0x13,0x9D,0xEC,0x3A,0xEB,0x67,0x14,0x36,
0x27,0x10,0x7C,0x02,0x6C,0x53,0x3B,0x4A,0xEC,0x91,0x11,0xC0,0x74,0x3D,0x51,0xFC,
0xB8,0xBE,0x3B,0xE8,0x22,0xDB,0x81,0xE6,0x4D,0x6C,0x22,0x53,0x99,0x27,0xA8,0x86,
0x4B,0x3F,0x7D,0x8E,0x99,0xDE,0xC0,0xF8,0x12,0x5C,0x64,0xC4,0x80,0x10,0xAA,0xD4,
0x71,0xA3,0x64,0xFF,0xA1,0xE8,0x42,0x61,0xC6*/
/*0x03,0x00,0x00,0x02,0x39,0x00,0x00,0x01,0x75,0xBE,0x00,0x3F,0x19,0xB5,0x55,0x6B,
0x33,0x78,0x2A,0x26,0x51,0xFE,0x9E,0x1F,0xBF,0x74,0x0B,0x5C,0x94,0xD3,0x1F,0xC2,
0xBE,0x18,0x7D,0x2E,0xF8,0x3D,0xCF,0x3E,0xCF,0x4A,0x85,0xE3,0xA2,0x16,0x9E,0x8D,
0x92,0xFF,0x0A,0xC8,0x84,0x2A,0x59,0x22,0x14,0xD0,0x54,0x29,0xB2,0x24,0x92,0x9A,
0x83,0xF0,0xDA,0xAC,0xBA,0x93,0xB7,0x01,0x4F,0x55,0x52,0x49,0xAF,0x8D,0x74,0x4B,
0x24,0x12,0xFC,0x85,0xEC,0xD3,0x75,0x5C,0xDC,0x9A,0xFB,0x53,0xE1,0x50,0x22,0x43,
0x82,0x63,0x6B,0x5C,0xA9,0xFD,0x3F,0xB8,0xDC,0xF3,0x20,0x19,0x3A,0x01,0xF6,0xF7,
0x19,0x9F,0x18,0x56,0x44,0xC0,0x67,0xA1,0xB8,0x98,0x7C,0x82,0x38,0x29,0x91,0x48,
0xE7,0x20,0xE5,0x40,0xB9,0x1B,0xB0,0xFE,0xE8,0x6F,0x95,0xEF,0xEA,0xEA,0xD8,0xC7,
0x94,0x33,0xA9,0x2F,0xAB,0x33,0xCF,0x5B,0xA2,0xAB,0x98,0x56,0xE6,0xE6,0x0E,0xD4,
0x08,0x62,0xE6,0x21,0xE9,0x8F,0x5D,0x67,0x0E,0x33,0x9C,0xA7,0xD5,0xD0,0xE9,0x7D,
0x16,0x9C,0xAA,0x29,0xD3,0x57,0xB0,0x16,0xDC,0xDF,0x89,0x17,0xA9,0xB1,0x29,0xBC,
0x07,0xA5,0x19,0x70,0x2C,0xE1,0x3F,0x75,0xA5,0x77,0xF6,0xEF,0xA2,0x6B,0x42,0xB8,
0xF9,0xD4,0xC1,0x63,0x9A,0x69,0x64,0x6E,0x25,0x15,0x27,0xCE,0xB5,0x76,0xF3,0x3C,
0x60,0xC5,0x21,0x65,0x3A,0xA8,0x72,0x98,0x4E,0xA4,0x21,0x42,0x9F,0x20,0x33,0x50,
0x26,0xF5,0x9D,0x8A,0xF7,0x96,0xD7,0x00,0x2F,0x9B,0x35,0x48,0x87,0x68,0x77,0x51,
0xE0,0x20,0x6C,0x05,0x80,0x98,0x00,0x6F,0x93,0xC1,0x7E,0x16,0x6D,0x0D,0x89,0x30,
0x44,0xE5,0x23,0x38,0x2B,0xAA,0x93,0xAA,0xE1,0x1E,0x20,0x6E,0xC6,0x83,0x62,0xD1,
0xEC,0x67,0x04,0x29,0xA4,0xBC,0x07,0xE1,0xFC,0x89,0xC9,0x8C,0xD6,0xE3,0x38,0x65,
0x68,0x36,0x17,0x1B,0x61,0xBC,0xF9,0xED,0x7C,0x52,0x38,0xBD,0x37,0xD8,0x68,0x90,
0x24,0xEF,0x7F,0x1B,0x00,0x10,0xE5,0x31,0x44,0xC3,0x40,0xE0,0xDD,0x82,0x8F,0x5E,
0x4D,0x67,0x81,0xC2,0x8D,0xCF,0x44,0x7B,0x40,0x91,0xE5,0x8D,0x5B,0xAB,0x2B,0x25,
0x52,0xF4,0xE7,0xCA,0x9D,0xA1,0x32,0xA9,0xF6,0x62,0x2F,0xCF,0xD2,0x0E,0x31,0x14,
0xE6,0xEB,0xAD,0x26,0x95,0x02,0xF6,0x04,0xC2,0x5E,0xC6,0x00,0x94,0xE0,0x9E,0xD6,
0xB5,0x44,0x52,0xD2,0x09,0x85,0x5E,0x40,0x2D,0x68,0x7A,0x5F,0x4C,0x91,0xA8,0x51,
0x0E,0x85,0x1F,0x52,0xC2,0xDA,0x71,0xA6,0xFE,0xDB,0xC6,0x76,0xCE,0x44,0x8B,0x48,
0xCC,0x6E,0xC9,0xEB,0x48,0xAB,0x9D,0x09,0xC0,0x1A,0x59,0x7C,0x9E,0xE9,0xA7,0x1B,
0x5B,0xFF,0x73,0x24,0x7E,0xF7,0xA9,0x7D,0x28,0xD4,0x1A,0x2E,0xA2,0x16,0x02,0x26,
0x53,0xDD,0xB5,0xE8,0xF0,0x0B,0x6B,0x93,0x27,0xFB,0x59,0x00,0x7B,0xA7,0x98,0x84,
0x61,0x7E,0xBE,0xC8,0xE0,0x9D,0xD4,0x0A,0xD3,0x40,0xBA,0x69,0x32,0xE4,0x70,0x61,
0x2C,0x46,0xF7,0x0E,0x0E,0xC6,0x9E,0x03,0xCD,0x00,0xFE,0xD6,0x74,0x28,0x70,0x3D,
0x62,0x7A,0x10,0x37,0xE3,0x77,0x1C,0xF1,0xBD,0x0A,0x17,0x14,0x58,0xE8,0x5A,0xBF,
0x54,0x4F,0x2C,0x73,0x13,0x85,0xB9,0x0E,0x24,0xDD,0xBC,0xC4,0x14,0xE9,0xE9,0x17,
0xCF,0xE7,0x81,0x3C,0xFF,0xBC,0x8E,0x60,0x26,0x89,0xD5,0x55,0xBE,0xF4,0x1C,0x6E,
0xC4,0xA4,0x0A,0xD9,0x17,0x28,0x51,0xF1,0x91,0xC4,0xCD,0x95,0x58,0x24,0x13,0x6E,
0x36,0xCB,0xCA,0xF5,0x3E,0xC2,0x72,0xA2,0x5E*/
};
unsigned char sym4[576]={
	/*0x04,0x00,0x00,0x01,0xB9,0x00,0x00,0x01,0x75,0xBE,0x00,0x3F,0x19,0xB5,0x55,0x6B,
0x33,0x78,0x2A,0x26,0x51,0xFE,0x9E,0x1F,0xBF,0xF7,0xAE,0xD3,0x53,0xA3,0xF2,0xD9,
0x9E,0xF3,0x55,0x36,0x33,0x25,0x58,0x53,0xB6,0xC9,0x6C,0x1E,0x8A,0x66,0xCA,0x1D,
0x7D,0xFB,0x0F,0x33,0x60,0x05,0xDE,0x12,0xFF,0x46,0x33,0x57,0x17,0xC5,0x54,0x24,
0xD0,0xD5,0x2A,0x8C,0x27,0xA6,0x45,0x80,0x09,0xE2,0x52,0x72,0x05,0xF8,0xCD,0xB6,
0xAC,0xE6,0x5B,0x56,0xAE,0xBE,0xDC,0x9A,0x6A,0xEE,0xBF,0x90,0x8E,0x3C,0xFD,0x65,
0x60,0xB0,0x11,0xA5,0xF6,0x65,0xA0,0xD0,0x16,0x76,0xF7,0xEF,0x5B,0x95,0x68,0xD4,
0x2B,0x75,0x4F,0xA8,0x71,0x19,0xE7,0xB0,0xC8,0xD0,0x80,0xD0,0xAE,0xE5,0xFA,0x0A,
0x89,0xA4,0x7D,0xCD,0xA3,0x6A,0x74,0x77,0x65,0x3C,0xA2,0x80,0xD2,0xB0,0x3F,0x3D,
0x54,0xA8,0xB1,0xC9,0xE2,0x2E,0x88,0xD7,0x7A,0x6B,0x00,0xB4,0x13,0x81,0xDD,0xF0,
0x6C,0x60,0x85,0xF3,0xBE,0x69,0x94,0x6D,0x6C,0x2E,0x8F,0x51,0x06,0x0D,0x36,0xD2,
0x85,0xC2,0x64,0x22,0xDF,0x12,0x3F,0x57,0x10,0x7C,0x63,0x17,0xCE,0x24,0xD0,0x06,
0xB2,0x3B,0x35,0xFC,0xF1,0x11,0xC2,0x4E,0xCB,0x09,0xC7,0x81,0xE5,0x13,0xD1,0xEF,
0xEE,0xBD,0x3E,0xC6,0x85,0x5A,0x85,0x6E,0x94,0x62,0xA1,0x45,0xE2,0x0D,0x45,0x3C,
0x27,0x70,0x79,0xC1,0xF5,0xE6,0x22,0xED,0xD3,0xCA,0x0E,0x7D,0x2B,0xB8,0x93,0x8A,
0xB3,0x6A,0x56,0x4E,0x0B,0x6E,0x3F,0x9B,0x2E,0x97,0x65,0xA4,0xE4,0xC6,0x54,0xFC,
0x9E,0x9A,0x2E,0x70,0xDA,0x54,0x82,0x18,0x89,0x55,0xA4,0x6C,0xAB,0xFC,0x7D,0x09,
0x82,0x13,0x32,0x6B,0xF1,0xA9,0xDB,0x09,0xDD,0x12,0xD8,0x02,0xF0,0x9A,0x77,0xFC,
0xA9,0x28,0xCF,0xBF,0x50,0xEB,0x45,0x10,0x6E,0x8E,0x2B,0x4C,0xCB,0x2B,0x29,0xF9,
0x97,0x35,0x19,0xEA,0x0B,0x22,0x66,0xFC,0x0E,0x90,0x07,0x9C,0x2F,0x36,0x87,0x90,
0x96,0x4E,0x1F,0xEF,0x09,0xE8,0xF9,0x27,0x59,0x67,0x30,0xDC,0x43,0x5F,0xC1,0x2D,
0xF9,0xAC,0xEE,0x32,0x3D,0xC8,0x84,0x40,0x08,0x5E,0x4B,0xC0,0xCD,0x57,0x6D,0xEB,
0x01,0xFA,0x6A,0xA5,0xA7,0xBA,0x35,0x02,0x38,0x31,0x52,0xAB,0x8C,0x88,0xD5,0x58,
0x68,0xF0,0x87,0xC8,0x80,0xB7,0xB6,0x14,0x71,0xA2,0xA4,0xAA,0x36,0x98,0x80,0x0D,
0xDB,0xCA,0xF0,0xBE,0x9B,0x57,0xB0,0x0F,0x9B,0xD6,0xA2,0x77,0x34,0x96,0xDF,0x0B,
0x3F,0xF2,0x70,0x86,0x2E,0x63,0xAA,0xBD,0x6A,0x3D,0x65,0x20,0x9D,0x02,0x09,0x70,
0xF3,0x64,0x7F,0x04,0x3E,0xDD,0xE2,0x13,0x8C,0xCA,0x15,0xDA,0xCB,0xEB,0x45,0xB9,
0xD3,0x9B,0x84,0xCC,0xEB,0xFD,0x61,0xA3,0x45*/
0x04,0x00,0x00,0x01,0xB9,0x00,0x00,0x01,0x69,0xFB,0xF6,0xC3,0x35,0x0B,0xB7,0x6C,
0xE7,0xFA,0x29,0xC9,0xD6,0x45,0xC5,0x4A,0xE6,0xD4,0xB0,0x4A,0x85,0x38,0x69,0xD8,
0x46,0xB3,0xBC,0xAF,0xD6,0xCA,0x8D,0xE9,0x59,0xDA,0x94,0xF5,0x4A,0x3E,0x65,0x77,
0xF5,0x48,0x54,0x47,0x75,0x59,0x3F,0xB7,0xAD,0x31,0x69,0xC9,0x00,0xE9,0x79,0x81,
0x1B,0x17,0xEC,0x49,0xE4,0x47,0x5F,0x9E,0x3A,0x71,0xC5,0x5D,0xEF,0x32,0x40,0xC1,
0xF6,0x59,0x6D,0xCB,0xFD,0x0C,0xBA,0x93,0xB4,0x95,0x39,0xD2,0x06,0x90,0xD3,0x5B,
0x28,0x96,0xD1,0x33,0x76,0xB3,0x39,0x4C,0xCA,0xC3,0xDD,0x0B,0xA7,0x5C,0x29,0x1F,
0xAE,0xC7,0x4A,0x2D,0xDE,0x13,0x06,0x09,0x67,0xD2,0xFC,0xF9,0x83,0x1C,0xC9,0xA7,
0xAF,0x7A,0x87,0xE2,0x91,0xC4,0xFD,0xF4,0xDA,0xBD,0x92,0x11,0x20,0x73,0xD9,0xC3,
0x17,0x6D,0x5C,0x3D,0x2E,0x92,0xD8,0x72,0xA8,0xC9,0xED,0x6C,0xBC,0x92,0x74,0x89,
0xBA,0x55,0xC2,0x90,0xCC,0x50,0x56,0x7B,0x23,0x53,0xE0,0xDB,0x34,0x30,0x62,0xDA,
0x20,0x41,0x2E,0x22,0xBD,0x67,0x4F,0x36,0x4B,0x14,0x03,0x72,0xDA,0x7B,0xF4,0x62,
0x62,0x4F,0x5F,0xEF,0xAE,0x6E,0x24,0xFB,0x83,0x24,0xA6,0x9E,0xD4,0x2E,0x29,0x50,
0x6B,0x94,0x25,0xE2,0x64,0xC6,0xCA,0x96,0xC5,0x08,0x69,0x7A,0xAD,0xEF,0x6E,0x2D,
0xE5,0x15,0x8E,0x61,0x20,0xA1,0x31,0xF9,0xFA,0xD5,0xB4,0x64,0x38,0x63,0x6D,0x90,
0xF5,0xE7,0x3B,0x55,0xFC,0x80,0x7C,0xED,0x2B,0x1A,0x16,0x31,0xAB,0x72,0x9B,0xDC,
0x1C,0x8B,0x36,0x1B,0xDD,0xB8,0xD9,0xD8,0x6D,0x0A,0xBC,0xE2,0x9D,0x18,0xBA,0x0D,
0xD1,0x1C,0x55,0x5E,0x89,0x41,0x10,0x15,0xE7,0xB7,0x67,0x64,0x4C,0x01,0x20,0x37,
0xDC,0x72,0x41,0x3F,0xBF,0xF1,0x02,0xE2,0x8E,0xAA,0xCB,0x9B,0x7F,0xFB,0xA8,0xB1,
0x6D,0x79,0xB0,0x70,0x4E,0x0B,0x54,0x85,0x63,0xB3,0x68,0xC7,0x4E,0x06,0xAC,0x23,
0x8F,0x25,0xD9,0x3E,0xDF,0x7A,0x35,0xA1,0xB4,0xEB,0x57,0x45,0x51,0x3B,0xD7,0x1E,
0xA5,0x1F,0x6E,0xDA,0xBE,0x4F,0x15,0xC2,0xD2,0x24,0xC2,0x9A,0x77,0xA9,0xCB,0xDC,
0xD2,0xDB,0xFB,0xFE,0x7F,0xA8,0xDD,0xD5,0x7D,0x6D,0xB1,0xF9,0x06,0xAA,0xF1,0xF2,
0x82,0x6D,0x29,0x60,0x37,0x7F,0x1F,0xF9,0x9A,0x92,0xB8,0x31,0x10,0x92,0x91,0x68,
0x89,0x92,0xC9,0x6E,0x59,0x66,0x18,0xB0,0x0C,0x2D,0xC5,0x9A,0xDF,0x65,0x70,0x33,
0x48,0x20,0x8B,0xAE,0xC9,0xC7,0x09,0x37,0x51,0xA7,0xF8,0x9E,0xF9,0xE3,0x81,0x6C,
0x23,0xF3,0xF4,0x07,0x78,0x55,0x1E,0x0F,0x2C,0xB7,0x00,0x27,0x30,0x0B,0x29,0x35,
0x14,0x36,0xE0,0xA7,0xD7,0x9F,0x48,0xE7,0xAE
};
unsigned char M[576] = {
          0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
          0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
          0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c,
          0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
          0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11,
          0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
          0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17,
          0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10
      };
#endif
/*			
uint8_t test_message[]={0x16,0x03,0x01,0x00,0x64,0x01,0x00,0x00,0x60,0x03,0x03,0xF3,0x38,0x75,0x05,0x64,
0x2D,0x5D,0x81,0x1E,0x77,0xF3,0xFC,0x49,0xF1,0xA2,0x86,0x40,0x6B,0x7C,0x5A,0x90,
0x1C,0xDF,0xF6,0x4D,0x38,0xA4,0x3C,0xD2,0xF5,0xE8,0xC6,0x00,0x00,0x0A,0xC0,0x23,
0xC0,0x24,0xC0,0x2B,0xC0,0x2C,0x00,0xFF,0x01,0x00,0x00,0x2D,0x00,0x0B,0x00,0x04,
0x03,0x00,0x01,0x02,0x00,0x0A,0x00,0x0C,0x00,0x0A,0x00,0x17,0x00,0x18,0x00,0x1A,
0x00,0x1B,0x00,0x1C,0x00,0x23,0x00,0x00,0x00,0x0D,0x00,0x08,0x00,0x06,0x04,0x03,
0x05,0x03,0x06,0x03,0x00,0x0F,0x00,0x01,0x01};*/
#if 0			
uint8_t test_message[]={
0x7E,0xA0,0x74,0x88,0x03,0x02,0x03,0x10,0xAA,0xC6,0x16,0x03,0x01,0x00,0x64,0x01,
0x00,0x00,0x60,0x03,0x03,0xE6,0x69,0x0E,0x9D,0x0A,0x94,0xE5,0xC7,0xBF,0x64,0x1E,
0xD6,0xE0,0xBA,0x37,0xE7,0x50,0x3F,0xBA,0x3B,0xD4,0x91,0x5F,0x41,0x44,0x8F,0xF2,
0x32,0x0B,0xF3,0xF5,0xCA,0x00,0x00,0x0A,0xC0,0x23,0xC0,0x24,0xC0,0x2B,0xC0,0x2C,
0x00,0xFF,0x01,0x00,0x00,0x2D,0x00,0x0B,0x00,0x04,0x03,0x00,0x01,0x02,0x00,0x0A,
0x00,0x0C,0x00,0x0A,0x00,0x17,0x00,0x18,0x00,0x1A,0x00,0x1B,0x00,0x1C,0x00,0x23,
0x00,0x00,0x00,0x0D,0x00,0x08,0x00,0x06,0x04,0x03,0x05,0x03,0x06,0x03,0x00,0x0F,
0x00,0x01,0x01,0x65,0xD8,0x7E};
#endif
extern uint8_t b_Hdlc_sendbuf[1024];
int  main ( void )
{
//	unsigned short i;
	//const struct uECC_Curve_t * p_curve;
   int16_t i,j;
	// uint8_t test_buf[16];
	// uint8_t key1[16];
	// uint8_t plaintext1[32];
//	 uint8_t Kmac[16],Kenc[16],Lmac[16],Lenc[16];
#if 0
	unsigned char L[16];
//  unsigned char	K1[16]={0x86,0x1e,0x70,0xa7,0xfc,0x6b,0xfa,0x12,0x43,0x0d,0x47,0x0a,0x78,0xbf,0xd2,0x34};
//  unsigned char	K2[16]={0x09,0x1b,0x08,0xf9,0xc9,0x3a,0xf1,0x96,0xf7,0x81,0x38,0x91,0x01,0xdf,0xb2,0xff};
	//unsigned char T[16], TT[12];
      
     /* unsigned char key[16] = {
          0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
          0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
      };*/
#endif
		//	uint32_t Len=0x166;
			//uint32_t Len=0x167;
//	uint32_t Len=0x169;
			/* //82408571c3e2424540207f833b6dda69
		unsigned char key[16] = {
          0xff,0xff,0xff,0xff,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
      };
		unsigned char plaintext[16]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};*/
			//0336763e966d92595a567cc9ce537f5e
	/*unsigned char key[16] = {	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	unsigned char iv[16]={0xf3,0x44,0x81,0xec,0x3c,0xc6,0x27,0xba,0xcd,0x5d,0xc3,0xfb,0x08,0xf2,0x73,0xe6};
	unsigned char plaintext[16]={	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};*/
	/*unsigned char key[16] = {	0x9d,0xc2,0xc8,0x4a,0x37,0x85,0x0c,0x11,0x69,0x98,0x18,0x60,0x5f,0x47,0x95,0x8c};
	unsigned char plaintext[16]={0x2e,0x58,0x66,0x92,0xe6,0x47,0xf5,0x02,0x8e,0xc6,0xfa,0x47,0xa5,0x5a,0x2a,0xab};		
   unsigned char iv[16]={0x25,0x69,0x53,0xb2,0xfe,0xab,0x2a,0x04,0xae,0x01,0x80,0xd8,0x33,0x5b,0xbe,0xd6};*/
	 /*unsigned char plaintext[16]={0x81,0x00,0x00,0x00,0x19,0x00,0x00,0x01,0x64};
	 unsigned char plaintext1[64]={0x82,0x00,0x00,0x00,0x39,0x00,0x00,0x01,0x66,0x29,0xF2,0x4C,0x90,0x58,0x21,0x9C,0x14,0x5D,0x34,0x0A,0xE4,0x0D,0x87,0x93,0x6F,0x0C,0xFB,0x3A,0x67,0xC8,0x7B,0xD4,0x56,0x11,0xF4,0x80,0xCC,0x98,0x96,0xF0,0x13};
	*/
	//unsigned char plaintext1[64]={0x85,0x00,0x00,0x00,0x29,0x00,0x00,0x01,0x6C,0xD5,0x20,0x33,0xFE,0x20,0xE2,0x5A,0x3F,0xA9,0x5D,0xCD,0x48,0xE1,0x0C,0xF0,0x7A};
		//	unsigned char T[16];
	__disable_irq();
	
#if 0
	SYSCTL->SYS_PS = 0x82;
	SYSCTL->MOD1_EN = 0xa5800fe0;
#ifdef SYS_CLK_7M
	SYSCTL->OSC_CTRL2 |= 0x10; 	 //外部晶振，f=7.3728MHz
#else
	SYSCTL->OSC_CTRL2 = 0x00000013; //外部晶振，f=29.4912MHz
#endif
	SYSCTL->SYS_PS = 0x00;
#endif
	SystemDelay(1000);  // 等待第1次上电的稳定
	fnWDT_Restart();
	fnTarget_Init();
	//cacheOff();
	//fnLcd_Init();
	__enable_irq();
	Serial_Open(0,921600,8,0);
	//Serial_Open(115200,8,0);
	//CmWmbus_Init(0);
	InitServerId();
	
//	CM_Mess2020_Key_Calculate(keytext,0x1,Len,m_lmn_info.b_sub_identification,Kmac);
//	CM_Mess2020_Key_Calculate(keytext,0x0,Len,m_lmn_info.b_sub_identification,Kenc);
/*CM_Mess2020_Key_Calculate(keytext,0x11,Len,m_lmn_info.b_sub_identification,Kmac);
	CM_Mess2020_Key_Calculate(keytext,0x10,Len,m_lmn_info.b_sub_identification,Kenc);
	//AES_CMAC(K1,plaintext1,41,T);
//	AES_CMAC(Kmac,plaintext1,537,L);
	//CmDeAES128(Kenc,0,0,plaintext1+9,528,M);
	AES_CMAC(Kmac,plaintext1,425,L);
	CmDeAES128(Kenc,0,0,plaintext1+9,416,M);*/
//	CmEnAES128(Kenc,0,0,M,528,M);
	
//	CmDeAES128(key,0,0,T,16,T);
#ifdef TEST
	//AES_128(keytext,plaintext,cix);
	//	m_SubKeyGenerate(key,K1,K2);
		AES_CMAC(key,M,40,T);
		CM_Mess2020_Key_Calculate(keytext,0x11,~0,m_lmn_info.b_sub_identification,Lmac);
		CM_Mess2020_Key_Calculate(keytext,0x1,~0,m_lmn_info.b_sub_identification,Kmac);
		//CM_Mess2020_Key_Calculate(keytext,0x11,0xffffffff,m_lmn_info.b_sub_identification,Lmac);
		//CM_Mess2020_Key_Calculate(keytext,0x11,0xffffffff,m_lmn_info.b_sub_identification,Lmac);
		AES_CMAC(Kmac,plaintext,9,pix);
		AES_CMAC(Lmac,plaintext,9,cix);
	
//	AES_CMAC(keytext,plaintext,9,key1);
	//	CmEnAES128(key1,iv,tag,plaintext,9,pix);
	//	CmDeAES128(key1,iv,tag,pix,16,cix);
	//Encrypt_ByteData(keytext,16,0,0,0,0,plaintext,1,pix,tag);
//	Decrypt_ByteData(keytext,0,0,0,pix,9,tag,cix);
	//CmEnAES128(keytext,iv,tag,plaintext1,16,key1);
	
//	CmEnAES128(key1,iv,tag,plaintext,9,pix);
	//CmDeAES128(key1,iv,tag,pix,16,cix);
	//CmDeAES128(keytext,iv,tag,pix,9,cix);
	//mbedtls_sha256_self_test(0);
#endif
#if  0
		SystemDelay(2000);
		HDLC_Assemble(test_buf,0);
		Serial_Write(test_buf,11);
#endif
	
	//fnWDT_Restart();
	//CmSym(plaintext1,b_Hdlc_sendbuf+10,0x0229);
//	fnWDT_Restart();
//	CmSym(sym4,b_Hdlc_sendbuf+10,0x01b9);
	tls_Init();
	fnWDT_Restart();
//	Cm_Tls_Analys(test_message+10,105,b_Hdlc_sendbuf+10);
	fnWDT_Restart();
	Flag.StatusWord = 0x04040404;
	//Cm_SpiInit(2000000,0,0);
	//Cm_SpiInit(1000000,1,1);
	//Cm_SpiInit(1000000,0,1);
	//Cm_SpiInit(1000000,1,0);
//	Read_FlashID(&Len);
	//Read_DataFlash(test_message,4096,32);
	//DataFlash_Write1(4096,test_message+32,32);
	//Read_DataFlash(test_message,4096,32);
	//SX127x_init();
//	fnUSART5_Init(0xe0);
	Serial_Open(1,600,7,SERIAL_CHECK_EVEN);
	while(1)
	{
		fnWDT_Restart();
		//SystemDelay(2000);
#if 0
		if(ms_count>500)
		{
			ms_count=0;
			HDLC_Assemble(test_buf,0);
			Serial_Write(test_buf,11);
		}
#endif
	//	if (Flag.Clk & F_HalfSec) ProcHalfSec();
		if (Flag.Clk & F_Sec) ProcSec();
		if (Flag.Clk & F_Min) ProcMin();
	//	if (Flag.Clk & F_Hour) ProcHour();
	//	if (Flag.Clk & F_Day) ProcDay();
		CM_HDLC_Receive();
		iec1107_read();
	}
}



