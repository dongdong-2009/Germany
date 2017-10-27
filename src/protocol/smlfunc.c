#include <string.h>
#include "GetMeterData.h"
#include "MeterDataType.h"
#include "data.h"
#include "aes.h"
#include "sml.h"
#include "tls.h"
#include "sym.h"
#include "smlfunc.h"
#include "TypeE2p.h"
extern SMLCOMM	SMLComm;
extern ORDERRECORD	OrderRecord[16];
extern SMLRECORD SMLRecord[4];
struct S_Measure_{
	uint64_t value;
	uint32_t capture_time;
	uint32_t sts;
	uint8_t  signature_val[64];
};
struct S_Measure_ m_Mesure;
struct S_Measure_ m_Mesure_n;
uint8_t sign_buf[96];
uint8_t signature_flag[2];
void Cm_Signature(const uint8_t *pri,uint8_t *in,uint32_t Len,uint8_t *out);
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
#if 1
const uint8_t  data_sign_pri[32]={0x9D,0xEB,0xC6,0xDE,0x97,0x57,0xDE,0x9D,0x99,0x4E,0x45,0xFC,0xD8,0x5D,0x47,0x62,
0xB0,0x28,0xFC,0x24,0x0D,0x14,0xA5,0xA0,0x2A,0x35,0x00,0x6E,0x59,0xDC,0xFD,0x07};
#else
const uint8_t  data_sign_pri[32]={0x07,0xFD,0xDC,0x59,0x6E,0x00,0x35,0x2A,0xA0,0xA5,0x14,0x0D,0x24,0xFC,0x28,0xB0,
0x62,0x47,0x5D,0xD8,0xFC,0x45,0x4E,0x99,0x9D,0xDE,0x57,0x97,0xDE,0xC6,0xEB,0x9D};
#endif
void Signature_Measure(void)
{
	//uint8_t privateK[32];
	uint64_t tmp;
	const uint8_t *privateK;
	//uint8_t flag;
	//signature_flag[0]=1;
	if(signature_flag[0] || signature_flag[1])
	{	
		//E2P_RData(privateK,E2P_PrivateKey,32);
		//privateK=Cm_Get_ECC_Addr();
		privateK=data_sign_pri;
		memset(sign_buf,0,96);
		E2P_RData(sign_buf,Server_ID,10);
	}
	//E2P_RData(&flag,E2P_OrderPlusA,1);
	//if(flag)
	if(signature_flag[0])
	{	
		//flag=0;
		//E2P_WData(E2P_OrderPlusA,&flag,1);
		signature_flag[0]=0;
		memcpy(sign_buf+14,&Comm.SecPulseCnt,4);
		Cm_Ram_Inter(sign_buf+14,4);
		memcpy(&m_Mesure.capture_time,sign_buf+14,4);
		Cm_Ram_Inter(sign_buf+14,4); //test
		//E2P_RData(sign_buf+18,E2P_SATEWORD,4);
		memcpy(sign_buf+18,&Para.meter_sts,4);
		Cm_Ram_Inter(sign_buf+18,4);
		memcpy(&m_Mesure.sts,sign_buf+18,4);
		Cm_Ram_Inter(sign_buf+18,4); //test
		sign_buf[22]=0x01,sign_buf[23]=0x0,sign_buf[24]=0x1,sign_buf[25]=0x08,sign_buf[26]=0x0,sign_buf[27]=0xff,
		sign_buf[28]=Unit_Wh;sign_buf[29]=0xff;
		//E2P_RData(sign_buf+30,CMon_EC_Pp0,8);
#if 0		
		memcpy(sign_buf+30,&Para.Pp0,8);
#else
	//*(unsigned long *)(sign_buf+30)=BCD4_Long(Para.Pp0);
		tmp = BCD2_Word(Para.Pp0+4)*100000000;
		tmp +=BCD4_Long(Para.Pp0);
//		tmp = tmp*10;
		memcpy(sign_buf+30,&tmp,8);
#endif		
		Cm_Ram_Inter(sign_buf+30,8);
		memcpy(&m_Mesure.value,sign_buf+30,8);
		Cm_Ram_Inter(sign_buf+30,8);  //test
		//Cm_Ram_Inter(sign_buf,96); //test
		Cm_Signature(privateK,sign_buf,96,m_Mesure.signature_val);
#if 0			
		Cm_Ram_Inter(m_Mesure.signature_val,32);
		Cm_Ram_Inter(m_Mesure.signature_val+32,32);
#endif		
	}
	//E2P_RData(&flag,E2P_OrderDecA,1);
	//if(flag)
	if(signature_flag[1])
	{
		signature_flag[1]=0;
		//flag=0;
		//E2P_WData(E2P_OrderDecA,&flag,1);
	memcpy(sign_buf+14,&Comm.SecPulseCnt,4);
	Cm_Ram_Inter(sign_buf+14,4);
	memcpy(&m_Mesure_n.capture_time,sign_buf+14,4);
	Cm_Ram_Inter(sign_buf+14,4);  //test
	//E2P_RData(sign_buf+18,E2P_SATEWORD,4);
	memcpy(sign_buf+18,&Para.meter_sts,4);
	Cm_Ram_Inter(sign_buf+18,4);
	memcpy(&m_Mesure_n.sts,sign_buf+18,4);
	Cm_Ram_Inter(sign_buf+18,4);
	sign_buf[22]=0x01,sign_buf[23]=0x0,sign_buf[24]=0x2,sign_buf[25]=0x08,sign_buf[26]=0x0,sign_buf[27]=0xff,
	sign_buf[28]=Unit_Wh;sign_buf[29]=0xff;
	//E2P_RData(sign_buf+30,CMon_EC_Pn0,8);
#if 0		
	memcpy(sign_buf+30,&Para.Pn0,8);
#else
	//*(unsigned long *)(sign_buf+30)=BCD4_Long(Para.Pn0);
		//tmp = BCD4_Long(Para.Pn0);
		tmp = BCD2_Word(Para.Pn0+4)*100000000;
		tmp +=BCD4_Long(Para.Pn0);
	//	tmp = tmp*10;
		memcpy(sign_buf+30,&tmp,8);
#endif		
	Cm_Ram_Inter(sign_buf+30,8);
	memcpy(&m_Mesure_n.value,sign_buf+30,8);
	Cm_Ram_Inter(sign_buf+30,8);
//	Cm_Ram_Inter(sign_buf,96); //test
	Cm_Signature(privateK,sign_buf,96,m_Mesure_n.signature_val);
#if 0	
	Cm_Ram_Inter(m_Mesure_n.signature_val,32);
	Cm_Ram_Inter(m_Mesure_n.signature_val+32,32);
#endif	
	}
}

uint8_t SetPrivateKey(uint16_t Flag)
{
	uint8_t *keytext;
	if(Flag==SetPropP_Res)
	{
		keytext=Cm_Get_ECC_Addr();
		E2P_RData(keytext,E2P_PrivateKey,32);
		Cm_Ram_Inter(keytext,32);
//		Cm_Make_Public_Key();
	}
	return ReturnOK;
}
void SetKeyTime(int timesec);
uint8_t SetMKey(uint16_t Flag)
{
	uint8_t *keytext;
	if(Flag==SetPropP_Res)
	{
#if 0		
		keytext=GetMKey();
		/*E2P_RData(sign_buf,E2P_SymmetricalKey,16);
		AES_CMAC(keytext,sign_buf,16,sign_buf+16);*/
		AES_CMAC(keytext,Z1_M,16,sign_buf+16);
		memcpy(keytext,sign_buf+16,16);
		SetKeyTime(120);
#else
	Generate_New_Key();		
#endif		
	}
	return ReturnOK;
}
uint16_t Get_LMN_Cert_Len(uint8_t *recvbuf,uint16_t ret);

uint8_t Get_PublicKey(uint16_t Flag)
{
	int rd_ptr,rd_len;
	int flag;
	unsigned char public_key_buf[66];
	if(Flag==GetPropP_Req)
	{
			E2P_RData(public_key_buf,PublicKey_Y,64);
#if 1
			flag=64;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|((flag+2)>>4);
			SMLComm.SendBuf[SMLComm.SendPtr++]=((flag+2))&0xf;
      memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],public_key_buf,64);
		 SMLComm.SendPtr +=64;
#else		
			flag=0;
			if(public_key_buf[0]&0x80)
				flag++;
			if(public_key_buf[32]&0x80)
				flag++;
			flag +=0x46;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|((flag+2)>>4);
			SMLComm.SendBuf[SMLComm.SendPtr++]=((flag+2))&0xf;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x30;
			SMLComm.SendBuf[SMLComm.SendPtr++]=flag;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x02;
		if(public_key_buf[0]&0x80)
		{
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x21;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x00;
		}
		else
		{
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x20;
		}
		memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],public_key_buf,32);
		SMLComm.SendPtr+=32;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x02;
	if(public_key_buf[32]&0x80)
	{
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x21;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x00;
	}
	else
	{
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x20;
	}
		memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],public_key_buf+32,32);
		SMLComm.SendPtr+=32;
#endif	
	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
	}
	return ReturnOK;
}

uint8_t Get_Certificate(uint16_t Flag)
{
	uint8_t *b_lmn_cert;
	int rd_ptr,rd_len;
	if(Flag==GetPropP_Req)
	{
		b_lmn_cert=Get_LMN_Cert();
		if(b_lmn_cert[2]==0)
		{
			//SMLComm.SendBuf[SMLComm.SendPtr-1]=0x01;
			SMLComm.SendBuf[++SMLComm.SendPtr]=0x01;
		}
		else
		if(b_lmn_cert[2])
		{
			/*for(rd_ptr=0,rd_len=0x197;rd_ptr<30;++rd_ptr)
			{
				if(b_lmn_cert[rd_ptr]==0x82)
				{
					rd_len=(b_lmn_cert[rd_ptr+1]<<8)|b_lmn_cert[rd_ptr+2];
					rd_len +=4;
					break;
				}
			}*/
			rd_len=(b_lmn_cert[2]<<8)|b_lmn_cert[3];
			if(rd_len>500)
			{
				rd_len=Get_LMN_Cert_Len(b_lmn_cert+4,rd_len);
			}
			
			if(rd_len<15)
			{
				SMLComm.SendBuf[SMLComm.SendPtr++]=rd_len;
			}
			else if(rd_len<253)
			{
				SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|(((rd_len+2+4)>>4)&0xf);
				SMLComm.SendBuf[SMLComm.SendPtr++]=((rd_len+2+4)&0xf);
				//SMLComm.SendPtr++;
			}
			else
			{
				rd_len=296;
				SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|(((rd_len+3+4)>>8)&0xf);
				SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|(((rd_len+3+4)>>4)&0xf);
				SMLComm.SendBuf[SMLComm.SendPtr++]=((rd_len+3+4)&0xf);
				//SMLComm.SendPtr++;
			}
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],b_lmn_cert,rd_len+4);
			SMLComm.SendPtr+=rd_len+4;
			SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
		}
	}
	return ReturnOK;
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
		memcpy(&SMLComm.SendBuf[SMLComm.SendPtr-8],&m_Mesure_n.value,8);
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
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x52;SMLComm.SendBuf[SMLComm.SendPtr++]=0xff;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=Unit_Wh;//0x1;
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
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],&m_Mesure_n.sts,4);
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
#if 1		
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|((64+2)>>4);
		SMLComm.SendBuf[SMLComm.SendPtr++]=((64+2))&0xf;
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],m_Mesure_n.signature_val,64);
			memset(m_Mesure_n.signature_val,0,64);
			SMLComm.SendPtr+=64;
#else
		flag=0;
	if(m_Mesure_n.signature_val[0]&0x80)
		flag++;
	if(m_Mesure_n.signature_val[32]&0x80)
		flag++;
	flag +=0x46;
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|((flag+2)>>4);
	SMLComm.SendBuf[SMLComm.SendPtr++]=((flag+2))&0xf;
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x30;
	SMLComm.SendBuf[SMLComm.SendPtr++]=flag;
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x02;
	if(m_Mesure_n.signature_val[0]&0x80)
	{
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x21;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x00;
	}
	else
	{
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x20;
	}
	memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],m_Mesure_n.signature_val,32);
	SMLComm.SendPtr+=32;
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x02;
	if(m_Mesure_n.signature_val[32]&0x80)
	{
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x21;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x00;
	}
	else
	{
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x20;
	}
	memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],m_Mesure_n.signature_val+32,32);
	SMLComm.SendPtr+=32;
	memset(m_Mesure_n.signature_val,0,64);
#endif
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
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x52;SMLComm.SendBuf[SMLComm.SendPtr++]=0xff;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=Unit_Wh;//0x1;
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
#if 1		
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|((64+2)>>4);
		SMLComm.SendBuf[SMLComm.SendPtr++]=((64+2))&0xf;
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],m_Mesure.signature_val,64);
			memset(m_Mesure.signature_val,0,64);
			SMLComm.SendPtr+=64;
#else
		flag=0;
	if(m_Mesure.signature_val[0]&0x80)
		flag++;
	if(m_Mesure.signature_val[32]&0x80)
		flag++;
	flag +=0x46;
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|((flag+2)>>4);
	SMLComm.SendBuf[SMLComm.SendPtr++]=((flag+2))&0xf;
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x30;
	SMLComm.SendBuf[SMLComm.SendPtr++]=flag;
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x02;
	if(m_Mesure.signature_val[0]&0x80)
	{
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x21;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x00;
	}
	else
	{
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x20;
	}
	memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],m_Mesure.signature_val,32);
	SMLComm.SendPtr+=32;
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x02;
	if(m_Mesure.signature_val[32]&0x80)
	{
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x21;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x00;
	}
	else
	{
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x20;
	}
	memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],m_Mesure.signature_val+32,32);
	SMLComm.SendPtr+=32;
	memset(m_Mesure.signature_val,0,64);
#endif
		SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
	}
	return ReturnOK;
}


uint8_t GetEC_Pp0(unsigned char *input,unsigned char *output)
{
	//int i;
	uint8_t flag;
	uint64_t tmp;
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
	/*memset(output,0,8);
	output[7] = 123;*/
#if 0	
	memcpy(output,&Para.Pp0,8);
#endif
#if 0	
	if(SMLComm.RecBuf[OrderRecord[SMLRecord[1].record_num].OLStartAdd+2]==5)
	{
		*(output-1)=0x65;
		tmp=Comm.SecPulseCnt-1;
		memcpy(output,&tmp,4);
		Cm_Ram_Inter(output,4);
		SMLComm.SendPtr-=4;
	}
	else if(SMLComm.RecBuf[OrderRecord[SMLRecord[1].record_num].OLStartAdd+2]==3)
	{
	/*	
		*(output-1)=0x72;
		*(output)=0x62;*(output+1)=0x01;*/
		
		*(output-1)=0x72;
		*(output)=0x62;*(output+1)=0x03;
		*(output+2)=0x72;
		*(output+3)=0x62;*(output+4)=0x01;
		*(output+5)=0x72;
		*(output+6)=0x52;*(output+7)=0xff;
		*(output+8)=0x62;*(output+9)=Unit_Wh;
		SMLComm.SendPtr+=2;
	}
	else
#endif		
	{
		memset(output,0,8);
	//*(unsigned long *)(output+4)=BCD4_Long(Para.Pp0);
		tmp = BCD2_Word(Para.Pp0+4)*100000000;
		tmp +=BCD4_Long(Para.Pp0);
	//	tmp = tmp*10;
		memcpy(output,&tmp,8);
		Cm_Ram_Inter(output,8);
	}
	//ID_Read(output,0x0001,8);
	return ReturnOK;
}

uint8_t GetEC_Pn0(unsigned char *input,unsigned char *output)
{
	uint8_t flag;
	uint64_t tmp;
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
#if 0	
	memcpy(output,&Para.Pn0,8);
#endif
#if 0	
	if(SMLComm.RecBuf[OrderRecord[SMLRecord[1].record_num].OLStartAdd+2]==5)
	{
		*(output-1)=0x65;
		tmp=Comm.SecPulseCnt-1;
		memcpy(output,&tmp,4);
		Cm_Ram_Inter(output,4);
		SMLComm.SendPtr-=4;
	}
	else if(SMLComm.RecBuf[OrderRecord[SMLRecord[1].record_num].OLStartAdd+2]==3)
	{
		*(output-1)=0x72;
		*(output)=0x62;*(output+1)=0x03;
		*(output+2)=0x72;
		*(output+3)=0x62;*(output+4)=0x01;
		*(output+5)=0x72;
		*(output+6)=0x52;*(output+7)=0xff;
		*(output+8)=0x62;*(output+9)=Unit_Wh;
		SMLComm.SendPtr+=2;
	}
	else
#endif		
	{
		memset(output,0,8);
		//*(unsigned long *)(output+4)=BCD4_Long(Para.Pn0);
		tmp = BCD2_Word(Para.Pn0+4)*100000000;
		tmp +=BCD4_Long(Para.Pn0);
	//	tmp = tmp*10;
		memcpy(output,&tmp,8);
		Cm_Ram_Inter(output,8);
	}
	return ReturnOK;
}

uint8_t GetU_L1(unsigned char *input,unsigned char *output)
{
	unsigned int tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	
	memset(output,0,8);
	//memcpy(output+4,&Para.Ua,4);
	//*(unsigned long *)(output+4)=BCD4_Long(Para.Ua);
	tmp = BCD4_Long(Para.Ua);
//	tmp /=10;
	memcpy(output+4,&tmp,4);
	Cm_Ram_Inter(output+4,4);
	return ReturnOK;
}
uint8_t GetU_L2(unsigned char *input,unsigned char *output)
{
	unsigned int tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	//memcpy(output+4,&Para.Ub,4);
	//*(unsigned long *)(output+4)=BCD4_Long(Para.Ub);
	tmp = BCD4_Long(Para.Ub);
//	tmp /=10;
	memcpy(output+4,&tmp,4);
	Cm_Ram_Inter(output+4,4);
	return ReturnOK;
}
uint8_t GetU_L3(unsigned char *input,unsigned char *output)
{
	unsigned int tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	//memcpy(output+4,&Para.Uc,4);
	//*(unsigned long *)(output+4)=BCD4_Long(Para.Uc);
	tmp = BCD4_Long(Para.Uc);
	//tmp /=10;
	memcpy(output+4,&tmp,4);
	Cm_Ram_Inter(output+4,4);
	return ReturnOK;
}

uint8_t Judge_ResteCry(unsigned char *input,unsigned char *output)
{
	//uint8_t *b_lmn_cert;
	if(input==0)
	{
		return ReturnOK;
	}	
	if(input[0]==0)
		return ReturnERR05;
		
	if(ResetCryto())
	{
		return ReturnERR15;
	}
	return ReturnOK;
}

uint8_t Judge_P(unsigned char *input,unsigned char *output)
{
	uint8_t flag;
	if(input==0)
	{
		if(m_Mesure.signature_val[0])
			return ReturnOK;
		else
			return ReturnERR15;
	}
	
	if(input[0]==0)
		return ReturnERR05;
	E2P_RData(&flag,E2P_Director,1);
	if((flag&1)==0)
	{
		return ReturnERR15;
	}
	signature_flag[0]=1;
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
		if(m_Mesure_n.signature_val[0])
			return ReturnOK;
		else
			return ReturnERR15;
	}
	if(input[0]==0)
		return ReturnERR05;
	E2P_RData(&flag,E2P_Director,1);
	if((flag&2)==0)
	{
		return ReturnERR22;
	}
	signature_flag[1]=1;
//	E2P_RData(&flag,E2P_OrderDecA,1);
//	if(flag==input[0])
//		return ReturnERR18;
	return ReturnOK;
}


uint8_t GetU_back(uint16_t Flag)
{
	if(Flag==GetPropP_Req)
	{
		if(OrderRecord[SMLRecord[1].record_num+1].OLStartAdd && OrderRecord[SMLRecord[1].record_num+1].OLLength==3)
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
			//SMLComm.SendBuf[SMLComm.SendPtr++]=0x52;SMLComm.SendBuf[SMLComm.SendPtr++]=0x00;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x52;SMLComm.SendBuf[SMLComm.SendPtr++]=0xff;//0xfe;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=Unit_V;
			SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
		}
	}
	return ReturnOK;
}

uint8_t GetS(unsigned char *input,unsigned char *output)
{
	int64_t tmp;
	BCD4 tmp_data;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}

	//tmp = BCD4_Long(Para.Pt);
	//if(Para.StatusWord &(1<<11))
	//	tmp = tmp*-1;
	memcpy(tmp_data,Para.Pt,4);
	tmp_data[2] &=0x7f;
	tmp = BCD4_Long(tmp_data);
	if(Para.Pt[2]&0x80)
		tmp = tmp*-1;
	memcpy(output,&tmp,8);
	Cm_Ram_Inter(output,8);
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
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x52;SMLComm.SendBuf[SMLComm.SendPtr++]=0x0;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=Unit_W;
		SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
	}
	return ReturnOK;
}

uint8_t GetP_back(uint16_t Flag)
{
	int i;
	unsigned short short_Name;
	unsigned int tmp;
	if(Flag==GetPropP_Req)
	{
		for(i=6;i<9;++i)
		{
			if(OrderRecord[i].OLStartAdd && OrderRecord[i].OLLength==3)
			{
				short_Name = SMLComm.RecBuf[OrderRecord[i].OLStartAdd+1];
				short_Name = (short_Name<<8) | SMLComm.RecBuf[OrderRecord[i].OLStartAdd+2];
				switch(short_Name)
				{
					case 3:
						++SMLComm.SendPtr;
						SMLComm.SendBuf[SMLComm.SendPtr]=0x73;
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
						SMLComm.SendBuf[SMLComm.SendPtr++]=0x52;SMLComm.SendBuf[SMLComm.SendPtr++]=0xff;
						SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=Unit_Wh;
						SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
						break;
					case 4:
						++SMLComm.SendPtr;
						SMLComm.SendBuf[SMLComm.SendPtr++]=0x73;
						RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[7].OLStartAdd]),OrderRecord[7].OLLength);//дattri
						SMLComm.SendPtr+=OrderRecord[7].OLLength;
						SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
							SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
							SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
							SMLComm.SendBuf[SMLComm.SendPtr++]=0x65;

							memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],&Para.meter_sts,4);
							Cm_Ram_Inter(&SMLComm.SendBuf[SMLComm.SendPtr],4);
							SMLComm.SendPtr+=4;
						SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
						break;
					case 5:
						++SMLComm.SendPtr;
						SMLComm.SendBuf[SMLComm.SendPtr++]=0x73;
						RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[8].OLStartAdd]),OrderRecord[8].OLLength);//дattri
						SMLComm.SendPtr+=OrderRecord[7].OLLength;
						SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
						SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
						SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
						SMLComm.SendBuf[SMLComm.SendPtr++]=0x65;
						tmp = Comm.SecPulseCnt-1;
							memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],&tmp,4);
							Cm_Ram_Inter(&SMLComm.SendBuf[SMLComm.SendPtr],4);
							SMLComm.SendPtr+=4;
						SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
						break;
					default:
						break;
				}
			}
			else
				break;
		}
#if 0		
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
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x52;SMLComm.SendBuf[SMLComm.SendPtr++]=0xff;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=Unit_Wh;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x73;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[7].OLStartAdd]),OrderRecord[7].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[7].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
			SMLComm.SendBuf[SMLComm.SendPtr++]=0x65;

			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],&Para.meter_sts,4);
			SMLComm.SendPtr+=4;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x73;
		
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[8].OLStartAdd]),OrderRecord[8].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[7].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x65;
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],&Comm.SecPulseCnt,4);
			Cm_Ram_Inter(&SMLComm.SendBuf[SMLComm.SendPtr],4);
			SMLComm.SendPtr+=4;
		SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
#endif		
	}
	return ReturnOK;
}

uint8_t GetI_back(uint16_t Flag)
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
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x52;SMLComm.SendBuf[SMLComm.SendPtr++]=0xfc;
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;SMLComm.SendBuf[SMLComm.SendPtr++]=Unit_A;
		SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
	}
	return ReturnOK;
}

uint8_t Judge_PINCODE(unsigned char *input,unsigned char *output)
{
	uint8_t i;
	if(input==0)
	{
		return ReturnOK;
	}	
	if(memcmp(input,"0000",4)==0)
	{
		return ReturnERR14;
	}
	
	for(i=0;i<4;++i)
	{
		if((input[i]<'0') || (input[i]>'9'))
			return ReturnERR14;
	}
	
	return ReturnOK;
}


uint8_t ReSetDay(uint16_t Flag)
{
	if(Flag==SetPropP_Res)
	{
		Para.P0_day = 0;
		Para.P0_week = 0;
		Para.P0_month = 0;
		Para.P0_year = 0;
	}
	return ReturnOK;
}

uint8_t ReSetLast(uint16_t Flag)
{
	if(Flag==SetPropP_Res)
	{
		Para.P0_last = -1;
	}
	return ReturnOK;
}


uint8_t Judge_Day(unsigned char *input,unsigned char *output)
{
	unsigned char Write_Buff[8];
	uint64_t LongData;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	memcpy(Write_Buff,&Para.P0_day,6);
  LongData = BCD2_Word(Write_Buff+4)*100000000;
	LongData +=BCD4_Long(Write_Buff);
	//LongData = LongData>>8;
	if(LongData==0)
	{
		return ReturnERR23;
	}
//	LongData = LongData*10;
	memcpy(output,&LongData,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}

uint8_t Judge_Week(unsigned char *input,unsigned char *output)
{
	unsigned char Write_Buff[8];
	uint64_t LongData;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	memcpy(Write_Buff,&Para.P0_week,6);
  LongData = BCD2_Word(Write_Buff+4)*100000000;
	LongData +=BCD4_Long(Write_Buff);
	//LongData = LongData>>8;
	if(LongData==0)
	{
		return ReturnERR23;
	}
//	LongData = LongData*10;
	memcpy(output,&LongData,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}

uint8_t Judge_Month(unsigned char *input,unsigned char *output)
{
	unsigned char Write_Buff[8];
	uint64_t LongData;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	memcpy(Write_Buff,&Para.P0_month,6);
  LongData = BCD2_Word(Write_Buff+4)*100000000;
	LongData +=BCD4_Long(Write_Buff);
	//LongData = LongData>>8;
	if(LongData==0)
	{
		return ReturnERR23;
	}
	//LongData = LongData*10;
	memcpy(output,&LongData,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}

uint8_t Judge_Year(unsigned char *input,unsigned char *output)
{
	unsigned char Write_Buff[8];
	uint64_t LongData;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	memcpy(Write_Buff,&Para.P0_year,6);
  LongData = BCD2_Word(Write_Buff+4)*100000000;
	LongData +=BCD4_Long(Write_Buff);
	//LongData = LongData>>8;
	if(LongData==0)
	{
		return ReturnERR23;
	}
	//LongData = LongData*10;
	memcpy(output,&LongData,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}

uint8_t Judge_MaxLen(unsigned char *input,unsigned char *output)
{
	if(input==0)
	{
		return ReturnOK;
	}	
	return ReturnERR15;
}

uint8_t GetAngle1(unsigned char *input,unsigned char *output)
{
	int64_t tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	tmp = BCD2_Word(Para.Pangleba);
	tmp /=10;
	if(tmp>180)
		tmp=(360-tmp)*(-1);
	memcpy(output,&tmp,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}

uint8_t GetAngle2(unsigned char *input,unsigned char *output)
{
	int64_t tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	tmp = BCD2_Word(Para.Pangleca);
	tmp /=10;
	if(tmp>180)
		tmp=(360-tmp)*(-1);
	memcpy(output,&tmp,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}

uint8_t GetAngle3(unsigned char *input,unsigned char *output)
{
	int64_t tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	tmp = BCD2_Word(Para.Panglea);
	tmp /=10;
	if(tmp>180)
		tmp=(360-tmp)*(-1);
	memcpy(output,&tmp,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}

uint8_t GetAngle4(unsigned char *input,unsigned char *output)
{
	int64_t tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	tmp = BCD2_Word(Para.Pangleb);
	tmp /=10;
	if(tmp>180)
		tmp=(360-tmp)*(-1);
	memcpy(output,&tmp,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}

uint8_t GetAngle5(unsigned char *input,unsigned char *output)
{
	int64_t tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	tmp = BCD2_Word(Para.Panglec);
	tmp /=10;
	if(tmp>180)
		tmp=(360-tmp)*(-1);
	memcpy(output,&tmp,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}


uint8_t GetIa(unsigned char *input,unsigned char *output)
{
	unsigned int tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	tmp = BCD4_Long(Para.Ia);
	memcpy(output+4,&tmp,4);
	Cm_Ram_Inter(output+4,4);
	return ReturnOK;
}

uint8_t GetIb(unsigned char *input,unsigned char *output)
{
	unsigned int tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	tmp = BCD4_Long(Para.Ib);
	memcpy(output+4,&tmp,4);
	Cm_Ram_Inter(output+4,4);
	return ReturnOK;
}

uint8_t GetIc(unsigned char *input,unsigned char *output)
{
	unsigned int tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	tmp = BCD4_Long(Para.Ic);
	memcpy(output+4,&tmp,4);
	Cm_Ram_Inter(output+4,4);
	return ReturnOK;
}

uint8_t SetManFlag(uint16_t Flag)
{
	uint8_t tmp_z[4];
	if(Flag==SetPropP_Res)
	{
		SM.MagnetOnCnt=0;
		memset(tmp_z,0,4);
		E2P_WData(MagneticONCnt,tmp_z,2);
	}
	return ReturnOK;
}

uint8_t SetCoverFlag(uint16_t Flag)
{
	uint8_t tmp_z[4];
	if(Flag==SetPropP_Res)
	{
		SM.CoverOpenCnt=0;
		SM.TCoverOpenCnt=0;
		memset(tmp_z,0,4);
		E2P_WData(OpenTCoverCnt,tmp_z,2);
		E2P_WData(OpenCoverCnt,tmp_z,2);
	}
	return ReturnOK;
}
uint8_t GetFre(unsigned char *input,unsigned char *output)
{
	unsigned int tmp;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	//memcpy(output+4,&Para.Pt,4);
//*(unsigned long *)(output+4)=BCD4_Long(Para.Pt);
//	Para.Pc[0]&=0xf0;
	tmp = BCD2_Word(Para.Freq);
	memcpy(output+4,&tmp,4);
	Cm_Ram_Inter(output+4,4);
	return ReturnOK;
}
uint8_t GetSa(unsigned char *input,unsigned char *output)
{
	int64_t tmp;
	BCD4 tmp_data;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
//	memset(output,0,8);
	//memcpy(output+4,&Para.Pt,4);
//*(unsigned long *)(output+4)=BCD4_Long(Para.Pt);
//	Para.Pa[0]&=0xf0;
	//tmp = BCD4_Long(Para.Pa);
	//if(Para.StatusWord &(1<<12))
	//	tmp = tmp*-1;
	//tmp /=10;
	memcpy(tmp_data,Para.Pa,4);
	tmp_data[2] &=0x7f;
	tmp = BCD4_Long(tmp_data);
	if(Para.Pa[2]&0x80)
		tmp = tmp*-1;
	memcpy(output,&tmp,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}

uint8_t GetSb(unsigned char *input,unsigned char *output)
{
	int64_t tmp;
	BCD4 tmp_data;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
//	memset(output,0,8);
	//memcpy(output+4,&Para.Pt,4);
//*(unsigned long *)(output+4)=BCD4_Long(Para.Pt);
	//Para.Pb[0]&=0xf0;
//	tmp = BCD4_Long(Para.Pb);
	//tmp /=10;
	//if(Para.StatusWord &(1<<13))
	//	tmp = tmp*-1;
	memcpy(tmp_data,Para.Pb,4);
	tmp_data[2] &=0x7f;
	tmp = BCD4_Long(tmp_data);
	if(Para.Pb[2]&0x80)
		tmp = tmp*-1;
	memcpy(output,&tmp,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}

uint8_t GetSc(unsigned char *input,unsigned char *output)
{
	int64_t tmp;
	BCD4 tmp_data;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
//	memset(output,0,8);
	//memcpy(output+4,&Para.Pt,4);
//*(unsigned long *)(output+4)=BCD4_Long(Para.Pt);
	//Para.Pc[0]&=0xf0;
	//tmp = BCD4_Long(Para.Pc);
//	tmp /=10;
//	if(Para.StatusWord &(1<<14))
//		tmp = tmp*-1;
	memcpy(tmp_data,Para.Pc,4);
	tmp_data[2] &=0x7f;
	tmp = BCD4_Long(tmp_data);
	if(Para.Pc[2]&0x80)
		tmp = tmp*-1;
	memcpy(output,&tmp,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}

uint8_t Get_Certificate1(unsigned char *input,unsigned char *output)
{
	uint8_t *b_lmn_cert;
	int rd_ptr,rd_len;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
		b_lmn_cert=Get_LMN_Cert();
		SMLComm.SendPtr--;
		if(b_lmn_cert[2]==0)
		{
			SMLComm.SendBuf[++SMLComm.SendPtr]=0x01;
		}
		else
		if(b_lmn_cert[2])
		{
			rd_len=(b_lmn_cert[2]<<8)|b_lmn_cert[3];
			if(rd_len>500)
			{
				rd_len=Get_LMN_Cert_Len(b_lmn_cert+4,rd_len);
			}
			
			if(rd_len<15)
			{
				SMLComm.SendBuf[SMLComm.SendPtr++]=rd_len;
			}
			else if(rd_len<253)
			{
				SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|(((rd_len+2+4)>>4)&0xf);
				SMLComm.SendBuf[SMLComm.SendPtr++]=((rd_len+2+4)&0xf);
			}
			else
			{
				//rd_len=296;
				SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|(((rd_len+3+4)>>8)&0xf);
				SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|(((rd_len+3+4)>>4)&0xf);
				SMLComm.SendBuf[SMLComm.SendPtr++]=((rd_len+3+4)&0xf);
			}
			memcpy(&SMLComm.SendBuf[SMLComm.SendPtr],b_lmn_cert,rd_len+4);
			SMLComm.SendPtr+=rd_len+4;
		}
		return ReturnOK;
}
uint8_t Get_P_Sig_val(unsigned char *input,unsigned char *output)
{
	if(m_Mesure.signature_val[0])
	{
		memcpy(output,&m_Mesure.value,8);
		return ReturnOK;
	}
	else
		return ReturnERR15;
		
}

uint8_t Get_P_Sig_sts(unsigned char *output)
{
	memcpy(output,&m_Mesure.sts,4);
}

uint8_t Get_P_Sig_time(unsigned char *output)
{
	memcpy(output,&m_Mesure.capture_time,4);
}


uint8_t Get_P_Signature(unsigned char *output)
{
	memcpy(output,m_Mesure.signature_val,64);
}


uint8_t Get_N_Sig_val(unsigned char *input,unsigned char *output)
{
	if(m_Mesure_n.signature_val[0])
	{
		memcpy(output,&m_Mesure_n.value,8);
		return ReturnOK;
	}
	else
		return ReturnERR15;
		
}

uint8_t Get_N_Sig_sts(unsigned char *output)
{
	memcpy(output,&m_Mesure_n.sts,4);
}

uint8_t Get_N_Sig_time(unsigned char *output)
{
	memcpy(output,&m_Mesure_n.capture_time,4);
}


uint8_t Get_N_Signature(unsigned char *output)
{
	memcpy(output,m_Mesure_n.signature_val,64);
}

uint8_t GetLastPn(unsigned char *input,unsigned char *output)
{
	unsigned char Write_Buff[8];
	uint64_t LongData;
	if(input)
		return ReturnOK;
	if(!output)
	{
		return ReturnERR03;
	}
	memset(output,0,8);
	memcpy(Write_Buff,&Para.P0_last,6);
  LongData = BCD2_Word(Write_Buff+4)*100000000;
	LongData +=BCD4_Long(Write_Buff);
	//LongData = LongData>>8;
	if(LongData==0)
	{
		return ReturnERR23;
	}
//	LongData = LongData*10;
	memcpy(output,&LongData,8);
	Cm_Ram_Inter(output,8);
	return ReturnOK;
}
