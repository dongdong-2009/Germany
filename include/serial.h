#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <Drive_Lib.h>

#define SERIAL_CHECK_NO 0
#define SERIAL_CHECK_ODD 1
#define SERIAL_CHECK_EVEN 2
#define SERIAL_BUFFER_LEN	1024
#define SERIAL_CH0_LEN 1024
#define SERIAL_CH1_LEN 256

struct S_Serial_
{
	//uint8_t serial_tx_buf[16];
	//uint8_t serial_rx_buf[SERIAL_BUFFER_LEN];
	uint8_t *serial_tx_buf;
	uint8_t *serial_rx_buf;
	uint16_t send_len;
	uint16_t send_pos;
	uint16_t rx_len;
	uint16_t rx_pos;
	uint8_t pre_len;
	uint8_t pre_pos;
};


int8_t Serial_Open(uint8_t ch,uint32_t baud,uint8_t bits,uint8_t check);
int16_t Serial_Write(uint8_t ch,uint8_t *buf,uint16_t len);
uint16_t Serial_Read(uint8_t ch,uint8_t *buf,uint16_t len);
uint16_t Serial_Status(uint8_t ch);
#endif
