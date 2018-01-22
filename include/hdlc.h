#ifndef __HDLC_H__
#define __HDLC_H__
#include <stdint.h>

#define HDLC_I 		0x10
#define HDLC_RR 	0x11
#define HDLC_RNR	0x15
#define HDLC_SNRM	0x93
#define HDLC_DISC	0x53
#define HDLC_UA		0x73
#define HDLC_DM		0x1F
#define HDLC_FRMR	0x97
#define HDLC_UI		0x13
#define HDLC_UI_N	0x03		//无回码

//单点命令
#define HDLC_I_PROTOCOL_TLS_COSEM					0x1
#define HDLC_I_PROTOCOL_TLS_NOCONTENT    	0x2
#define HDLC_I_PROTOCOL_SML_COSEM					0x3
#define HDLC_I_PROTOCOL_SML_EDL						0x4
#define HDLC_I_PROTOCOL_SML_SYM2					0x5
#define HDLC_I_PROTOCOL_SYM								0x6
#define HDLC_I_PROTOCOL_TLS_SML_EDL				0x7
#define HDLC_I_PROTOCOL_TLS_SMLSYM2				0x8

//广播命令
#define HDLC_UI_PROTOCOL_ADDR_ASSIGN			0x1
#define HLDC_UI_PROTOCOL_ADDR_VERIFY			0x2

struct S_Hdlc_LMN_Info
{
	uint8_t b_hdlc_LMN_Addr;
	uint8_t b_hdlc_slot;
	uint8_t b_sub_identification[14];
	uint8_t b_sensor_identification[14];
	uint8_t b_reserved[2];
};


#define MAX_GW_LMN_NUM 8
void CM_HDLC_Receive(void);
uint16_t HDLC_Assemble(uint8_t *buf,uint16_t Len);
#endif

