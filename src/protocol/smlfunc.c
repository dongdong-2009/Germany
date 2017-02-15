#include "GetMeterData.h"
#include "MeterDataType.h"
#include "data.h"
#include "sml.h"
#include "smlfunc.h"
#include "TypeE2p.h"
extern SMLCOMM	SMLComm;
extern ORDERRECORD	OrderRecord[16];
struct S_Measure_{
	uint64_t value;
	uint32_t capture_time;
	uint32_t sts;
	uint8_t  signature_val[64];
};
struct S_Measure_ m_Mesure;
struct S_Measure_ m_Mesure_n;
uint8_t sign_buf[128];
void Cm_Signature(uint8_t *pri,uint8_t *in,uint32_t Len,uint8_t *out);
void Cm_Ram_Inter(uint8_t *buf,uint16_t Len);
/*{
	uint16_t i;
	uint8_t tmp;
	if(Len<2)
		return;
	for(i=0;i<Len/2;++i)
	{
		tmp = buf[i];
		buf[i] = buf[Len-1-i];
		buf[Len-1-i]=tmp;
	}
}*/

void Signature_Measure(void)
{
	uint8_t privateK[32];
	uint8_t flag;
	E2P_RData(privateK,E2P_PrivateKey,32);
	memset(sign_buf,0,100);
	E2P_RData(sign_buf,Server_ID,10);
	E2P_RData(&flag,E2P_OrderPlusA,1);
	if(flag)
	{	
		flag=0;
		E2P_WData(E2P_OrderPlusA,&flag,1);
		memcpy(sign_buf+14,&Comm.SecPulseCnt,4);
		Cm_Ram_Inter(sign_buf+14,4);
		memcpy(&m_Mesure.capture_time,sign_buf+14,4);
	
		E2P_RData(sign_buf+18,E2P_SATEWORD,4);
		Cm_Ram_Inter(sign_buf+18,4);
		memcpy(&m_Mesure.sts,sign_buf+18,4);
		sign_buf[22]=0x01,sign_buf[23]=0x0,sign_buf[24]=0x1,sign_buf[25]=0x08,sign_buf[26]=0x0,sign_buf[27]=0xff,
		sign_buf[28]=00,sign_buf[29]=0x23;
		E2P_RData(sign_buf+30,CMon_EC_Pp0,8);
		Cm_Ram_Inter(sign_buf+30,8);
		memcpy(&m_Mesure.value,sign_buf+14,4);
		Cm_Signature(privateK,sign_buf,95,m_Mesure.signature_val);
		Cm_Ram_Inter(m_Mesure.signature_val,32);
		Cm_Ram_Inter(m_Mesure.signature_val+32,32);
	}
	E2P_RData(&flag,E2P_OrderDecA,1);
	if(flag)
	{
		flag=0;
		E2P_WData(E2P_OrderDecA,&flag,1);
	memcpy(sign_buf+14,&Comm.SecPulseCnt,4);
	Cm_Ram_Inter(sign_buf+14,4);
	memcpy(&m_Mesure_n.capture_time,sign_buf+14,4);
	
	E2P_RData(sign_buf+18,E2P_SATEWORD,4);
	Cm_Ram_Inter(sign_buf+18,4);
	memcpy(&m_Mesure_n.sts,sign_buf+18,4);
	sign_buf[22]=0x01,sign_buf[23]=0x0,sign_buf[24]=0x1,sign_buf[25]=0x08,sign_buf[26]=0x0,sign_buf[27]=0xff,
	sign_buf[28]=00,sign_buf[29]=0x23;
	E2P_RData(sign_buf+30,CMon_EC_Pn0,8);
	Cm_Ram_Inter(sign_buf+30,8);
	memcpy(&m_Mesure_n.value,sign_buf+14,4);
	Cm_Signature(privateK,sign_buf,95,m_Mesure_n.signature_val);
	Cm_Ram_Inter(m_Mesure_n.signature_val,32);
	Cm_Ram_Inter(m_Mesure_n.signature_val+32,32);
	}
}
uint8_t GetN_Signature(uint16_t Flag)
{
	//int i;
	uint8_t flag;
/*	E2P_RData(&flag,E2P_Director,1);
	if((flag&1)==0)
		return ReturnERR15;*/
	if(Flag==GetPropP_Req)
	{
		memcpy(&SMLComm.SendBuf[SMLComm.SendPtr-8],&m_Mesure.value,8);
		SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
		
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
			/*SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;*/
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],&m_Mesure.sts,4);
			SMLComm.SendPtr+=4;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x73;
		//++SMLComm.SendPtr;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[8].OLStartAdd]),OrderRecord[8].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[7].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x65;
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],&m_Mesure_n.capture_time,4);
			SMLComm.SendPtr+=4;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x73;
		//++SMLComm.SendPtr;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[9].OLStartAdd]),OrderRecord[9].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[7].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|((64+2)>>4);
		SMLComm.SendBuf[SMLComm.SendPtr++]=((64+2))&0xf;
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],m_Mesure_n.signature_val,64);
			SMLComm.SendPtr+=64;
		SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
	}
	return ReturnOK;
}

uint8_t GetP_Signature(uint16_t Flag)
{
	//int i;
	uint8_t flag;
/*	E2P_RData(&flag,E2P_Director,1);
	if((flag&1)==0)
		return ReturnERR15;*/
	if(Flag==GetPropP_Req)
	{
		memcpy(&SMLComm.SendBuf[SMLComm.SendPtr-8],&m_Mesure.value,8);
			//SMLComm.SendPtr+=8;
		SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
		
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
			/*SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0;*/
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],&m_Mesure.sts,4);
			SMLComm.SendPtr+=4;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x73;
		//++SMLComm.SendPtr;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[8].OLStartAdd]),OrderRecord[8].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[7].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x65;
			/*SMLComm.SendBuf[SMLComm.SendPtr++]=(Comm.SecPulseCnt>>24)&0xff;
			SMLComm.SendBuf[SMLComm.SendPtr++]=(Comm.SecPulseCnt>>16)&0xff;
			SMLComm.SendBuf[SMLComm.SendPtr++]=(Comm.SecPulseCnt>>8)&0xff;
			SMLComm.SendBuf[SMLComm.SendPtr++]=(Comm.SecPulseCnt)&0xff;*/
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],&m_Mesure.capture_time,4);
			SMLComm.SendPtr+=4;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x73;
		//++SMLComm.SendPtr;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[9].OLStartAdd]),OrderRecord[9].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[7].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|((64+2)>>4);
		SMLComm.SendBuf[SMLComm.SendPtr++]=((64+2))&0xf;
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],m_Mesure.signature_val,64);
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
	{
		return ReturnERR15;
	}
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

uint8_t Judge_ResteCry(unsigned char *input,unsigned char *output)
{
	if(input==0)
	{
		return ReturnOK;
	}	
	if(input[0]==0)
		return ReturnERR05;
	return ReturnOK;
}

uint8_t Judge_P(unsigned char *input,unsigned char *output)
{
	uint8_t flag;
	E2P_RData(&flag,E2P_Director,1);
	
	if((flag&1)==0)
	{
		return ReturnERR15;
	}
	if(input==0)
	{
		return ReturnOK;
	}
	
	if(input[0]==0)
		return ReturnERR05;
	//E2P_RData(&flag,E2P_OrderPlusA,1);
	//if(flag==input[0])
	//	return ReturnERR18;
	return ReturnOK;
}

uint8_t Judge_N(unsigned char *input,unsigned char *output)
{
	uint8_t flag=0;
	E2P_RData(&flag,E2P_Director,1);
	if((flag&2)==0)
	{
		return ReturnERR15;
	}
	if(input==0)
	{
		return ReturnOK;
	}
	
	
	if(input[0]==0)
		return ReturnERR05;
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

