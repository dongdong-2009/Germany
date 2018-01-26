#ifndef __WMBUS_H__
#define __WMBUS_H__
#include <stdint.h>

typedef struct S_Wmbus_Para
{
	uint8_t Mode;
	uint8_t Role;
	uint8_t DEV;
	uint8_t ID[4];
}S_WMBUS_PARA;

int16_t CmWmbus_Init(uint8_t Serial_no);
int16_t CmWmbus_SetPara(uint8_t type,uint8_t *para);
int16_t CmWmbus_Read(uint8_t *buf,uint16_t len);
int16_t CmWmbus_Write(uint8_t CI,uint8_t *buf,uint16_t len);

#endif
