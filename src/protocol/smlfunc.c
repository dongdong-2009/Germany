#include "GetMeterData.h"
#include "MeterDataType.h"
#include "sml.h"
#include "smlfunc.h"
extern SMLCOMM	SMLComm;
extern ORDERRECORD	OrderRecord[16];
struct S_Measure_{
	uint64_t value;
	uint32_t capture;
	
};
uint8_t GetP_Signature(uint16_t Flag)
{
	//int i;
	uint8_t flag;
/*	E2P_RData(&flag,E2P_Director,1);
	if((flag&1)==0)
		return ReturnERR15;*/
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
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x73;
	//	++SMLComm.SendPtr;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[7].OLStartAdd]),OrderRecord[7].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[7].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x65;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x73;
		//++SMLComm.SendPtr;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[8].OLStartAdd]),OrderRecord[8].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[7].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x65;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x73;
		//++SMLComm.SendPtr;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[9].OLStartAdd]),OrderRecord[9].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[7].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|((64+2)>>4);
		SMLComm.SendBuf[SMLComm.SendPtr++]=((64+2))&0xf;;
			SMLComm.SendPtr+=64;
		SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
	}
	return ReturnOK;
}

uint8_t GetEC_Pp0(unsigned char *input,unsigned char *output)
{
	//int i;
	uint8_t flag;
	E2P_RData(&flag,E2P_Director,1);
	if((flag&1)==0)
		return ReturnERR15;
	if(input)
	{
			return ReturnOK;
	}
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
	uint8_t flag;
	E2P_RData(&flag,E2P_Director,1);
	if((flag&2)==0)
		return ReturnERR15;
	if(input)
		return ReturnOK;
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
	if(input)
		return ReturnOK;
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
	if(input)
		return ReturnOK;
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
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	output[7] = 220;
	return ReturnOK;
}

uint8_t Judge_P(unsigned char *input,unsigned char *output)
{
	uint8_t flag;
	//if(input)
	//	return ReturnOK;
	if(input==0)
	{
		return ReturnOK;
	}
	E2P_RData(&flag,E2P_Director,1);
	if((flag&1)==0)
	{
		ReturnERR18;
	}
	//E2P_RData(&flag,E2P_OrderPlusA,1);
	//if(flag==input[0])
	//	return ReturnERR18;
	return ReturnOK;
}

uint8_t Judge_N(unsigned char *input,unsigned char *output)
{
	uint8_t flag=0;
	if(input==0)
	{
		return ReturnOK;
	}
	E2P_RData(&flag,E2P_Director,1);
	if((flag&2)==0)
	{
		ReturnERR18;
	}
//	E2P_RData(&flag,E2P_OrderDecA,1);
//	if(flag==input[0])
//		return ReturnERR18;
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
	if(input)
		return ReturnOK;
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

