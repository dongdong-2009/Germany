#include "GetMeterData.h"
#include "MeterDataType.h"
#include "sml.h"
#include "smlfunc.h"
extern SMLCOMM	SMLComm;
extern ORDERRECORD	OrderRecord[16];
uint8_t GetEC_Pp0(unsigned char *input,unsigned char *output)
{
	//int i;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	output[7] = 123;
	//ID_Read(output,0x0001,8);
	return ReturnOK;
}

uint8_t GetEC_Pn0(unsigned char *input,unsigned char *output)
{
	if(!output)
	{
		return ReturnERR03;
	}
	//ID_Read(output,0x000A,8);
	memset(output,0,8);
	output[7] = 124;
	return ReturnOK;
}

uint8_t GetU_L1(unsigned char *input,unsigned char *output)
{
	if(!output)
	{
		return ReturnERR03;
	}
	
	memset(output,0,8);
	output[7] = 220;
	return ReturnOK;
}
uint8_t GetU_L2(unsigned char *input,unsigned char *output)
{
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	output[7] = 220;
	return ReturnOK;
}
uint8_t GetU_L3(unsigned char *input,unsigned char *output)
{
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	output[7] = 220;
	return ReturnOK;
}

uint8_t GetU_back(uint16_t Flag)
{
	if(Flag==GetPropP_Req)
	{
		SMLComm.SendBuf[++SMLComm.SendPtr]=0x73;
		++SMLComm.SendPtr;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[6].OLStartAdd]),OrderRecord[6].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[6].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=0x03;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x52;SMLComm.SendBuf[SMLComm.SendPtr++]=0x00;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=0x23;//0x1;
		SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
	}
}

uint8_t GetS(unsigned char *input,unsigned char *output)
{
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	output[7] = 1127;
	return ReturnOK;
}

uint8_t GetS_back(uint16_t Flag)
{
	if(Flag==GetPropP_Req)
	{
		SMLComm.SendBuf[++SMLComm.SendPtr]=0x73;
		++SMLComm.SendPtr;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[6].OLStartAdd]),OrderRecord[6].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[6].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=0x03;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x52;SMLComm.SendBuf[SMLComm.SendPtr++]=0x00;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=27;//0x1;
		SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
	}
}

