#ifndef __TLS_H__
#define __TLS_H__
#include <stdint.h>
void Cm_Ram_Inter(uint8_t *buf,uint16_t Len);
typedef int16_t  (*Hdlc_back_function)(uint8_t *buf);
int tls_Init(void);
uint8_t *Cm_Get_ECC_Addr(void);
uint16_t  Cm_Tls_Analys(uint8_t *buf,uint16_t len,uint8_t *back,Hdlc_back_function *func);
int16_t  Cm_Tls_En(uint8_t *buf,uint16_t len,uint8_t *back);
int ResetCryto(void);
void Judge_Cryto(void);
uint8_t *GetMKey(void);
void Close_tls(void);
void Cm_Make_Public_Key(void);
void Generate_New_Key(void);
uint32_t GetTlsTime(void);
#endif
