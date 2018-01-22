#ifndef __GPRS_H__
#define __GPRS_H__

#include <stdint.h>

#define GPRS_BUF_LEN	512

typedef struct {
	uint8_t Host_ip[4];
	uint16_t Host_port;
	uint8_t Apn[16];
	uint8_t User[16];
	uint8_t Password[16];
}S_GPRS_PARA;

typedef struct {
	int8_t  Modem_status;
	uint8_t Gprs_signals;
	uint8_t Terminal_ip[4];
	uint8_t Sim_ccid[24];
}S_GPRS_STATUS;

typedef struct {
	char Gprs_tx_buf[GPRS_BUF_LEN];
	char Gprs_rx_buf[GPRS_BUF_LEN];
	uint16_t Gprs_tx_pos;
	uint16_t Gprs_rx_pos;
}S_GPRS_BUF;

//GPRS 执行的步骤
#define GPRS_RESET	0
#define GPRS_AT			1
#define GPRS_CCID 	2
#define GPRS_CSQ		3
#define	GPRS_APN		4
#define GPRS_USER		5
#define GPRS_ACT		6
#define GPRS_SRV		7
#define GPRS_OPEN		8	

//GPRS 参数
#define GPRS_PARA_ALL		0
#define GPRS_PARA_IP		1
#define GPRS_PARA_PORT	2
#define GPRS_PARA_APN		3
#define GPRS_PARA_USER	4
#define GPRS_PARA_PASS	5


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


int8_t CmGprs_Init(void);
int8_t CmGprs_SetPara(uint8_t *para,uint8_t flag);
int8_t CmGprs_GetPara(uint8_t *para,uint8_t flag);
int8_t CmGprs_GetStatus(uint8_t *sts,uint8_t flag);
int16_t CmGprs_Write(uint8_t *buf,uint16_t len);
int16_t CmGprs_Read(uint8_t *buf,uint16_t len);

#endif
