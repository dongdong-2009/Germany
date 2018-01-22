#ifndef __SYM_H__
#define __SYM_H__

#include <stdint.h>

int16_t CmSym(uint8_t *recvbuf,uint8_t *sendbuf,uint16_t len);
uint8_t *Get_LMN_Cert(void);
uint8_t *Get_SMGW_Cert(void);
#endif
