#ifndef __SPI_H__
#define __SPI_H__
#include <Drive_Lib.h>
int Cm_SpiInit(unsigned int baud,unsigned char CPHA,unsigned char CPOL);
int Cm_SpiRead(unsigned char *buf,int len);
int Cm_SpiWrite(unsigned char *buf,int len);
int Cm_SpiWriteAndRead(unsigned char *sendbuf,int sendlen,unsigned char *recvbuf,int recvlen);
#endif