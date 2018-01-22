#ifndef __AES_H__
#define __AES_H__
#include <stdint.h>
uint16_t CmEnAES128(uint8_t * pkey,uint8_t *iv,uint8_t *pOutTag,uint8_t *data,uint16_t len,uint8_t *pOutCiphertext);
uint16_t CmDeAES128(uint8_t * pkey,uint8_t *iv,uint8_t *pOutTag,uint8_t *data,uint16_t len,uint8_t *ptx);
void AES_128(uint8_t * pkey,uint8_t *input,uint8_t *output);
void AES_CMAC( unsigned char *key, unsigned char *input, int length,unsigned char *mac );
void CM_Mess2020_Key_Calculate(uint8_t *mk,uint8_t type,uint32_t C,uint8_t *m_Id,uint8_t *Key);
#endif
