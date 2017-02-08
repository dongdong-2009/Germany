#include <stdint.h>
#include <Drive_Lib.h>
#include "TypeE2p.h"
#include "aes.h"
#include "sym.h"
#include "ram.h"
#include "hdlc.h"
#include "tls.h"


//static uint32_t  Trans_Counter=0x0164;
static uint32_t  Trans_Counter=0x0166;
//static uint32_t  Trans_Counter=0x016e;
//static uint32_t  Trans_Counter=0x0174;
//uint8_t keytext[16]={0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};
uint8_t keytext[16]={0xA4,0x45,0x7D,0x73,0xF3,0xA8,0xED,0x56,0xB7,0x22,0x68,0xD9,0xB5,0x23,0x0F,0x7A};
extern struct S_Hdlc_LMN_Info m_lmn_info;
uint8_t Kenc[16],Kmac[16],Lenc[16],Lmac[16];
static uint8_t b_lmn_cert[512];
static uint8_t b_gw_cert[256];
uint8_t *Get_LMN_Cert(void)
{
	return b_lmn_cert;
}
uint8_t * Get_SMGW_Cert(void)
{
	return b_gw_cert;
}
uint32_t Word_Long(uint8_t *buf)
{
	uint32_t tmp,i;
	tmp=0;
	for(i=0;i<4;++i)
	{
		tmp=tmp*256+buf[i];
	}
	return tmp;
}


void Long_Word(uint8_t *buf,uint32_t Val)
{
	uint8_t i;
	for(i=0;i<4;++i)
	{
		buf[i]=(Val>>((3-i)*8))&0xff;
	}
}

int16_t Sym1(uint8_t *recvbuf,uint8_t *sendbuf,uint16_t len)
{
	int16_t ret;
	uint32_t tmp;
	ret=0;
	if(Word_Long(recvbuf+1)==0x19 && Word_Long(recvbuf+5)==0xffffffff)
	{
		sendbuf[0] = 0x81;
		Long_Word(sendbuf+1,0x19);
		Long_Word(sendbuf+5,Trans_Counter);
		ret = 9;
	}
	return ret;
}

int16_t Sym2(uint8_t *recvbuf,uint8_t *sendbuf,uint16_t len)
{
	int16_t ret;
	ret=0;
	if(Word_Long(recvbuf+1)==0x19 && Word_Long(recvbuf+5)==(Trans_Counter+1))
	{
		sendbuf[0] = 0x82;
		Trans_Counter+=2;
		Long_Word(sendbuf+5,Trans_Counter);
	//	CM_Mess2020_Key_Calculate(keytext,0x1,Trans_Counter,m_lmn_info.b_sub_identification,Kmac);
		//CM_Mess2020_Key_Calculate(keytext,0x0,Trans_Counter,m_lmn_info.b_sub_identification,Kenc);
		ret = 9;
		len = 9;
		/*sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x23; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x24; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x25; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x26; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x27; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x28; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x29; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x2A; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256*/
		
		/*sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x2B; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x2C; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x2D; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x2E; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x2F; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x30; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x31; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0xC0;
		sendbuf[ret++] = 0x32; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		*/
		sendbuf[len++] = 0xFF;
		sendbuf[len++] = 0xFF; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x00;
		sendbuf[len++] = 0x01; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x04;
		sendbuf[len++] = 0xC0; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x23;
		sendbuf[len++] = 0xC0; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x2B;
		sendbuf[len++] = 0xC0; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x2C;
		sendbuf[len++] = 0xC0; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x24;
		sendbuf[len++] = 0x05; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x00;
		sendbuf[len++] = 0x1C; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x00;
		sendbuf[len++] = 0x18; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x00;
		sendbuf[len++] = 0x1b; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x00;
		sendbuf[len++] = 0x17; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x00; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[len++] = 0x1a; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		/*sendbuf[ret++] = 0x08; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0x08; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0x08; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0x08; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0x08; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0x08; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0x08; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		sendbuf[ret++] = 0x08; //TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
		*/
		ret+=CmEnAES128(Kenc,0,0,sendbuf+9,len-ret,sendbuf+9);
		Long_Word(sendbuf+1,ret+16);
	}
	return ret;
}

int16_t Sym3(uint8_t *recvbuf,uint8_t *sendbuf,uint16_t len)
{
	int16_t ret;
	uint8_t *ecc_addr;
	ret=0;
	if(Word_Long(recvbuf+5)==(Trans_Counter+1))
	{
		//CmDeAES128(Lenc,0,0,recvbuf+9,len-9,recvbuf+9);
		CmDeAES128(Lenc,0,0,recvbuf+9,len-25,recvbuf+9);
		len-=9;
		//memcpy(b_lmn_cert,recvbuf+9,528);
		if((recvbuf[9]==0x30) && (recvbuf[10]==0x82))
		{
			ecc_addr=Cm_Get_ECC_Addr();
			ret=recvbuf[11]<<8 | recvbuf[12];
			memcpy(b_lmn_cert,recvbuf+9,ret+4);
			memcpy(ecc_addr,recvbuf+ret+20,32);    //+9+ret+4+7
			E2P_WData( PublicKey_Y,recvbuf+ret+70,64);
			for(len=0;len<16;++len)
			{
				ecc_addr[len] ^= ecc_addr[31-len];
				ecc_addr[31-len] ^= ecc_addr[len];
				ecc_addr[len] ^= ecc_addr[31-len];
			}
			E2P_WData( E2P_LMN_Certi,recvbuf+9,len-25);
		}
	//	else
		//	return 0;
		/*wr_len=0;
		while(len)
		{
			if(len>128)
				ret=128;
			else
				ret=len;
			E2P_WData( E2P_LMN_Certi+wr_len,recvbuf+9+wr_len,ret);
			wr_len+=ret;
			len -= ret;
			WDT->EN = 0xbb;	
		}*/
		
		sendbuf[0] = 0x83;
		Trans_Counter+=2;
		Long_Word(sendbuf+5,Trans_Counter);
		ret = 9; 
		Long_Word(sendbuf+1,ret+16);
	}
	return ret;
}

int16_t Sym4(uint8_t *recvbuf,uint8_t *sendbuf,uint16_t len)
{
	int16_t ret;
	ret=0;
	if(Word_Long(recvbuf+5)==(Trans_Counter+1))
	{
		//CmDeAES128(Lenc,0,0,recvbuf+9,len-9,recvbuf+9);
		CmDeAES128(Lenc,0,0,recvbuf+9,len-25,recvbuf+9);
		len-=25;
		E2P_WData( E2P_SMGW_Certi,recvbuf+9,len-25);
		memcpy(b_gw_cert,recvbuf+9,len-25);
		/*wr_len=0;
		while(len)
		{
			if(len>128)
				ret=128;
			else
				ret=len;
			E2P_WData( E2P_LMN_Certi+wr_len,recvbuf+9+wr_len,ret);
			wr_len+=ret;
			len -= ret;
			WDT->EN = 0xbb;	
		}*/
		sendbuf[0] = 0x84;
		Trans_Counter+=2;
		Long_Word(sendbuf+5,Trans_Counter);
		ret = 9; 
		Long_Word(sendbuf+1,ret+16);
	}
	return ret;
}

int16_t Sym5(uint8_t *recvbuf,uint8_t *sendbuf,uint16_t len)
{
	int16_t ret;
	
	if(Word_Long(recvbuf+5)==(Trans_Counter+1))
	{
		sendbuf[0] = 0x85;
		Trans_Counter+=2;
		Long_Word(sendbuf+5,Trans_Counter);
		ret = 9;
		len = 9;
		//Long_Word(sendbuf+ret,2048);
		//ret += 4; 
		sendbuf[len++]=0x08;
		sendbuf[len++]=0x00;
		while(len<25)
			sendbuf[len++]=0x0E;
		
		ret += CmEnAES128(Kenc,0,0,sendbuf+9,len-ret,sendbuf+9);
		Long_Word(sendbuf+1,ret+16);
	}
	return ret;
}

int16_t CmSym(uint8_t *recvbuf,uint8_t *sendbuf,uint16_t len)
{
	int16_t ret;
	uint8_t mac[16];
	//uint8_t Kmac[16];
	//uint8_t Lmac[16];
	uint32_t Len;
	Len = Word_Long(recvbuf+5);
	/*switch(recvbuf[0])
	{
		case 1:
		case 2:
		case 3:*/
			CM_Mess2020_Key_Calculate(keytext,0x11,Len,m_lmn_info.b_sub_identification,Lmac);
			CM_Mess2020_Key_Calculate(keytext,0x10,Len,m_lmn_info.b_sub_identification,Lenc);
		/*	break;
		default:
			break;
	}*/
	
	Len = Word_Long(recvbuf+1);
	AES_CMAC(Lmac,recvbuf,Len-16,mac);
	if(ret==0 || Data_Comp(mac,&recvbuf[Len-16],16))
		return 0;
	switch(recvbuf[0])
	{
		case 1:
			Len = Trans_Counter;
			CM_Mess2020_Key_Calculate(keytext,0x1,Len,m_lmn_info.b_sub_identification,Kmac);
			CM_Mess2020_Key_Calculate(keytext,0x0,Len,m_lmn_info.b_sub_identification,Kenc);
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			Len = Trans_Counter+2;
			CM_Mess2020_Key_Calculate(keytext,0x1,Len,m_lmn_info.b_sub_identification,Kmac);
			CM_Mess2020_Key_Calculate(keytext,0x0,Len,m_lmn_info.b_sub_identification,Kenc);
			break;
		default:
			break;
			
	}
	switch(recvbuf[0])
	{
		case 1:
			ret=Sym1(recvbuf,sendbuf,len);
			break;
		case 2:
			ret=Sym2(recvbuf,sendbuf,len);
			break;
		case 3:
			ret=Sym3(recvbuf,sendbuf,len);
			break;
		case 4:
			ret=Sym4(recvbuf,sendbuf,len);
			break;
		case 5:
			ret=Sym5(recvbuf,sendbuf,len);
			break;
		default:
			break;
	}
	if(ret>0)
	{
		/*if(recvbuf[0]==1)
		{
				Len = Word_Long(sendbuf+5);
				CM_Mess2020_Key_Calculate(keytext,0x1,Len,m_lmn_info.b_sub_identification,Kmac);
				CM_Mess2020_Key_Calculate(keytext,0x0,Len,m_lmn_info.b_sub_identification,Kenc);
		}*/
		
		Len = Word_Long(sendbuf+1);		
		AES_CMAC(Kmac,sendbuf,Len-16,mac);
		
		/*if(recvbuf[0]==2)
		{
			Len = Word_Long(sendbuf+5);
			CM_Mess2020_Key_Calculate(keytext,0x1,Len,m_lmn_info.b_sub_identification,Kmac);
			CM_Mess2020_Key_Calculate(keytext,0x0,Len,m_lmn_info.b_sub_identification,Kenc);
		}*/

		memcpy(sendbuf+ret,mac,16);
		ret+=16;
	}
	return ret;
}
