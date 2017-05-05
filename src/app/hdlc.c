#include <Drive_Lib.h>
#include "hdlc.h"
#include "serial.h"
#include"data.h"
#include "sml.h"
#include "sym.h"
#include "tls.h"
#include "aes.h"
#define TEST 1
#undef TEST
typedef int16_t  (*Hdlc_back_function)();
extern int16_t tls_back_fun(void);
#define HDLC_READ(buf,len) Serial_Read(0,buf,len)
#define HDLC_WRITE(buf,len) (Serial_Write(0,buf,len))
#define HDLS_STATUS				Serial_Status(0)
Hdlc_back_function hdlc_back;
uint8_t i_Meter_Addr;
uint8_t i_Meter_Prot,i_Meter_Prot_old;
uint8_t b_Lmn_List[MAX_GW_LMN_NUM];
uint8_t b_seq;
uint16_t i_rx_len;
uint16_t i_send_len;
#if 0
uint8_t b_Hdlc_buf[1024]={0x7E,0xA0,0x74,0x88,0x03,0x02,0x03,0x10,0xAA,0xC6,0x16,0x03,0x01,0x00,0x64,0x01,
0x00,0x00,0x60,0x03,0x03,0xE6,0x69,0x0E,0x9D,0x0A,0x94,0xE5,0xC7,0xBF,0x64,0x1E,
0xD6,0xE0,0xBA,0x37,0xE7,0x50,0x3F,0xBA,0x3B,0xD4,0x91,0x5F,0x41,0x44,0x8F,0xF2,
0x32,0x0B,0xF3,0xF5,0xCA,0x00,0x00,0x0A,0xC0,0x23,0xC0,0x24,0xC0,0x2B,0xC0,0x2C,
0x00,0xFF,0x01,0x00,0x00,0x2D,0x00,0x0B,0x00,0x04,0x03,0x00,0x01,0x02,0x00,0x0A,
0x00,0x0C,0x00,0x0A,0x00,0x17,0x00,0x18,0x00,0x1A,0x00,0x1B,0x00,0x1C,0x00,0x23,
0x00,0x00,0x00,0x0D,0x00,0x08,0x00,0x06,0x04,0x03,0x05,0x03,0x06,0x03,0x00,0x0F,
0x00,0x01,0x01,0x65,0xD8,0x7E};
#else
uint8_t b_Hdlc_buf[1024];
#endif

uint8_t b_Hdlc_sendbuf[1024];
#if 0
uint8_t sml_test[256]={0x1B,0x1B,0x1B,0x1B,0x01,0x01,0x01,0x01,0x76,0x05,0x01,0x02,0x03,0x04,0x62,0x00,
0x62,0x00,0x72,0x65,0x00,0x00,0x01,0x01,0x76,0x01,0x0B,0x45,0x53,0x2D,0x48,0x44,
0x4C,0x43,0x2D,0x42,0x72,0x05,0x01,0x02,0x03,0x04,0x0B,0x0A,0x01,0x45,0x4D,0x48,
0x00,0x00,0x5B,0x2F,0x56,0x01,0x01,0x63,0xD6,0x70,0x00,0x76,0x05,0x01,0x02,0x03,
0x04,0x62,0x00,0x62,0x00,0x72,0x65,0x00,0x00,0x05,0x01,0x73,0x0B,0x0A,0x01,0x45,
0x4D,0x48,0x00,0x00,0x5B,0x2F,0x56,0x72,0x0A,0x01,0x00,0x60,0x05,0x00,0xFF,0x00,
0x01,0x00,0x03,0x00,0x02,0x73,0x0A,0x01,0x00,0x60,0x05,0x00,0xFF,0x00,0x01,0x00,
0x01,0x71,0x73,0x03,0x00,0x02,0x72,0x62,0x01,0x65,0x00,0x00,0x00,0x00,0x01,0x63,
0x01,0xB1,0x00,0x76,0x05,0x01,0x02,0x03,0x04,0x62,0x00,0x62,0x00,0x72,0x65,0x00,
0x00,0x02,0x01,0x71,0x01,0x63,0xBB,0xB5,0x00,0x00,0x00,0x00,0x1B,0x1B,0x1B,0x1B,
0x1A,0x03,0x11,0x9B};
#endif
uint8_t ControlByte,oldControlByte;
uint8_t Connected;
uint8_t b_short_frame[16];
struct S_Hdlc_LMN_Info m_lmn_info;
extern SMLCOMM	SMLComm;
uint8_t ui_flag;
uint32_t ms_count=0,res_count;
uint32_t gprs_ms;
extern uint8_t keytext[16];
extern void udelay(uint32_t us);
void mdelay(uint32_t ms)
{
	gprs_ms=ms;
	while(gprs_ms)udelay(1);
}
void InitServerId(void)
{
	i_rx_len=0;
	i_send_len=0;
	Connected=0;
	b_seq=0x10;
	ControlByte=0;
	oldControlByte=0;
	res_count=0;
	//memset(b_Hdlc_buf,0,512);
	memset(b_Hdlc_sendbuf,0,512);
	hdlc_back=0;
#ifdef TEST	
	hdlc_back=tls_back_fun;
#endif
	//i_rx_len=120;
	
	m_lmn_info.b_sub_identification[0]=0x0A;
	m_lmn_info.b_sub_identification[1]=0x01;
#if 0	
	/*m_lmn_info.b_sub_identification[2]='S';
	m_lmn_info.b_sub_identification[3]='U';
	m_lmn_info.b_sub_identification[4]='N';
	m_lmn_info.b_sub_identification[2]='I';
	m_lmn_info.b_sub_identification[3]='S';
	m_lmn_info.b_sub_identification[4]='K';
	m_lmn_info.b_sub_identification[9]=0x18;*/
	m_lmn_info.b_sub_identification[2]=0x45;
	m_lmn_info.b_sub_identification[3]=0x4D;
	m_lmn_info.b_sub_identification[4]=0x48;
	m_lmn_info.b_sub_identification[5]=0x00;
	m_lmn_info.b_sub_identification[6]=0x00;
	m_lmn_info.b_sub_identification[7]=0x5B;
	m_lmn_info.b_sub_identification[8]=0x2F;
	m_lmn_info.b_sub_identification[9]=0x56;
	m_lmn_info.b_sensor_identification[0]=0x0A;
	m_lmn_info.b_sensor_identification[1]=0x01;
	m_lmn_info.b_sensor_identification[2]='S';
	m_lmn_info.b_sensor_identification[3]='U';
	m_lmn_info.b_sensor_identification[4]='N';
	m_lmn_info.b_sensor_identification[2]='I';
	m_lmn_info.b_sensor_identification[3]='S';
	m_lmn_info.b_sensor_identification[4]='K';
#else
	memcpy(m_lmn_info.b_sub_identification+2,Manufacture,3);
	memcpy(m_lmn_info.b_sub_identification+7,"STC",3);
	memcpy(m_lmn_info.b_sensor_identification,m_lmn_info.b_sub_identification,9);
#endif	
	m_lmn_info.b_sensor_identification[9]=0x18;
	m_lmn_info.b_hdlc_LMN_Addr=2;
	i_Meter_Addr = 68;
	m_lmn_info.b_hdlc_slot = 1;
	//E2P_WData(E2P_Manufactor_ID,"STC",3);
	E2P_WData(E2P_Manufactor_ID,"LOG",3);
	//E2P_WData(E2P_Manufactor_ID,"STC0063539421",14);
	memcpy(b_Hdlc_sendbuf,"1.0.00",6);
	E2P_WData(E2P_FirmwareVer,b_Hdlc_sendbuf,6);
#if 0	
	for(i_rx_len=0,i_send_len=0;i_send_len<6;++i_send_len)
	{
		i_rx_len+=b_Hdlc_sendbuf[i_send_len];
	}
#endif	
	i_rx_len=DoCrc16(0xffff,b_Hdlc_sendbuf,6);
	//gprs_ms+=1;
//	E2P_WData(E2P_FirmWareCheck,(unsigned char*)&i_rx_len,2);
	E2P_WData(E2P_FirmWareCheck,b_Hdlc_sendbuf,2);
	i_rx_len=1;
	E2P_WData(E2P_Director,(unsigned char*)&i_rx_len,1);
	i_rx_len=0;
	i_send_len=0;
	E2P_WData( Server_ID,m_lmn_info.b_sub_identification, 10 ); 
//	E2P_RData(keytext,E2P_SymmetricalKey,16);
//	E2P_WData(E2P_SymmetricalKey,keytext,16);
}
#if 1
unsigned int MP_FCS(uint16_t fcs,uint16_t c)
{
  uint16_t FS1,FS2,FS3,FS;
  
  FS1=(fcs)^(c);
  FS2=FS1&0x00FF;
  FS3=Crc16tab[FS2];
  FS=(fcs>>8)^FS3;
  
  return FS;
}
uint16_t DoCrc16(uint16_t RegInit, uint8_t *pucData, uint16_t usDataLen) 
//unsigned int GetCheckCode_16BitFcs(uint8_t *pucData,uint16_t usDataLen)
{
  uint16_t crc;
  crc = 0xffff;
  while( usDataLen-- > 0 )
    crc = MP_FCS(crc,*pucData++);
  crc ^= 0xFFFF;
  
  return crc;
}
#endif

uint16_t Cm_Handle_Assign_Addr(uint8_t* buf,uint16_t len)
{
	uint16_t i,j;
	struct S_Hdlc_LMN_Info *p_info;
	uint8_t flag;
	uint8_t Addr_Num;
	if(len%32)
		return 0;
	flag=0;
	for(Addr_Num=0,i=0;i<len;i+=32)
	{
		p_info=(struct S_Hdlc_LMN_Info *)(buf+i);
		b_Lmn_List[Addr_Num]=p_info->b_hdlc_LMN_Addr;
		Addr_Num++;
		if(Data_Comp(buf+i+2,((uint8_t *)&m_lmn_info)+2,30)==0)
		{
			m_lmn_info.b_hdlc_LMN_Addr=i_Meter_Addr=p_info->b_hdlc_LMN_Addr;
			m_lmn_info.b_hdlc_slot = p_info->b_hdlc_slot;
			i_Meter_Addr = m_lmn_info.b_hdlc_LMN_Addr;
			flag=1;
			break;
		}
	}
	if(flag)
	{
		return 0;
	}
	//m_lmn_info.b_hdlc_slot=Addr_Num+1;
	for(j=0;j<MAX_GW_LMN_NUM;++j)
	{
		if(Addr_Num>j)
		{
			i_Meter_Addr=b_Lmn_List[0]+1;
		}
		else
		{
			//i_Meter_Addr=35+j*10;
			i_Meter_Addr = rand();
		}
		for(i=0,flag=1;i<Addr_Num;++i)
		{
			if(i_Meter_Addr==b_Lmn_List[i])
			{
				flag=0;
				break;
			}
		}
		if((i_Meter_Addr<3) || (i_Meter_Addr>0x7e))
			flag=0;
		
		if(flag)
			break;
	}
	m_lmn_info.b_hdlc_slot=0;
	m_lmn_info.b_hdlc_LMN_Addr=i_Meter_Addr;
	return 1;
}

uint8_t GetMeterAddress(uint8_t* ComBuf,uint8_t* ClientAddr,uint8_t* LMN_Addr, uint8_t* Proto_Index)
{
	/*
	uint8_t i;
	uint8_t Len=0;
	for(i=3;i<7;i++ )
  {
    Len++;
    if(( *(ComBuf+i) & 0x01 ) != 0 ) break;		
  }
	if(Len!=2)
	{
		return 1;
	}*/
	*LMN_Addr=ComBuf[3]>>1;
	*Proto_Index=ComBuf[4]>>1;
	*ClientAddr=ComBuf[5];
	//*Proto_Index=ComBuf[4]>>1;
	return 0;
}


uint8_t GetControlByte(uint8_t SControlByte )
{
  uint8_t ControlByte;
  
  ControlByte = SControlByte;
  
  if(( ControlByte & 0x11 ) == 0x10 ) ControlByte = HDLC_I;				//I 帧
  else if(( ControlByte & 0x1f ) == 0x11 ) ControlByte = HDLC_RR;			//RR 帧
  else if(( ControlByte & 0x1f ) == 0x15 ) ControlByte = HDLC_RNR;		//RNR 帧
  else
  {
    switch( ControlByte )
    {
    case HDLC_SNRM:	
    case HDLC_DISC:				
    case HDLC_UI:
    case HDLC_UI_N:
      break;			
    default: 
      ControlByte = HDLC_FRMR;		
      break;		
    }	
  }	
  return ControlByte;
}

//返回-1：无接收，
//返回大于0接收到的字节数，
//返回0，接收正确
int16_t Hdlc_Check(uint8_t *buf,uint16_t len)
{
	uint16_t i,frame_len;
	int16_t ret;
	uint16_t i_crc;
	
	if(len<11)
		return len;
	ret=len;
	for(i=0;(i)<len;++i)
	{
		if((buf[i]!=0x7e) || ((buf[i+1]&0xF0)!=0xA0))
		{
			ret--;
			continue;
		}
		frame_len=buf[i+1]&0x7;
		frame_len<<=8;
		frame_len+=buf[i+2];
		if((frame_len+2)>(len-i))   //判断接收的长度
		{
			ret=len-i;
			break;
		}
		else
		{
			if(buf[i+frame_len+1]==0x7e)
			{
#if 1
				i_crc=DoCrc16(0xffff,buf+i+1,frame_len-2);
				if(i_crc == (buf[frame_len+i-1] | (buf[frame_len+i]<<8)))
				{	
					ret=0;
					break;
				}
#else 
			ret=0;
			break;
#endif
			}
			else
			{
				ret=-1;
				break;
			}
		}
	}
	
	if(buf[i]!=0x7e)
	{
		ret=-1;
	}
	else
	{
		if(i)
			memcpy(buf,buf+i,len-i);
	}
	return ret;
}

uint16_t HDLC_Assemble(uint8_t *buf,uint16_t Len)
{
	uint16_t ptr;
	uint16_t i_crc;
	uint8_t txseq,rxseq;
	ptr=0;
	buf[ptr++]=0x7e;
	ptr +=2;
	if(Len)
	{
		buf[1] = 0xA0 | (((Len+11))>>8)&0x3f;
		buf[2]=(((Len+11)))&0xff;
	}
	else
	{
		buf[1] = 0xA0 | (((Len+9))>>8)&0x3f;
		buf[2]=(((Len+9)))&0xff;
	}
	buf[ptr++]= 2;
	buf[ptr++]=(i_Meter_Prot<<1)|0x1;
	buf[ptr++]=(i_Meter_Addr<<1)&0xFE;
	buf[ptr++]=(i_Meter_Prot<<1)|0x1;
	switch(ControlByte)
	{
		case HDLC_I:
			{
				rxseq = (b_seq>>5)&0x7;
				txseq = (b_seq>>1)&0x7;
			//	rxseq++;
				//rxseq%=8;
				/*txseq++;
				txseq%=8;*/
				b_seq = (rxseq<<5)|(txseq<<1);
				b_seq |=0x10;
				buf[ptr++]=b_seq;
				/*rxseq++;
				rxseq%=8;*/
				txseq++;
				txseq%=8;
				b_seq = (rxseq<<5)|(txseq<<1);
				b_seq |=0x10;
			}
			break;
		case HDLC_UI:
			ui_flag=1;
			buf[ptr++]=HDLC_UI;
			break;
		case HDLC_RR:
		//	txseq = b_seq&7;
			/*rxseq = txseq-1;
			rxseq %=8;*/
		//	if(ms_count>1500)
		//	{
		//		oldControlByte=HDLC_UI;
		//	}
			//ms_count=0;
			if(i_send_len)
			{
				//mdelay(1);
				ptr=i_send_len;
				//i_send_len=0;
				return ptr;
			}
			//return 0;
			//if(Connected==0)
			{
				//b_seq = (b_seq&0xf0)| ((b_Hdlc_buf[7]>>4)&0xe);
				//buf[ptr++]=HDLC_I|(b_seq);
			//	Len=20;
		//		memset(buf+10,0x1b,Len);
				
				//buf[ptr++]=HDLC_I|(b_seq-0x2);
				//break;
			}
			//if(oldControlByte==HDLC_RR) // || oldControlByte==HDLC_I)
			//	return 0;
			/*if(Connected==0)
			{
			//	buf[ptr++]=HDLC_RR;
				buf[ptr++]=HDLC_DM;
			}
			else*/
			{
			//	if(oldControlByte==HDLC_UI)
				//	return 0;
		/*		if(oldControlByte==HDLC_RR)
				{	//buf[ptr++]=HDLC_UA;
					//return 0;
					//buf[ptr++]=HDLC_DISC;
					rxseq = (b_seq>>5)&0x7;
					txseq = (b_seq>>1)&0x7;
					b_seq = (rxseq<<5)|(txseq<<1);
					b_seq |=0x10;
					buf[ptr++]=b_seq;
					txseq++;
					txseq%=8;
					b_seq = (rxseq<<5)|(txseq<<1);
					b_seq |=0x10;
				}
				else*/
				//b_seq = (b_seq&0xf0)| ((b_Hdlc_buf[7]>>4)&0xe);
				//buf[ptr++]=HDLC_RR|((b_seq+0x20)&0xf0);
				buf[ptr++]=HDLC_RR|((b_seq)&0xf0);
				//buf[ptr++]=HDLC_I|(b_seq);
			}

#if 0			
			if(oldControlByte==HDLC_SNRM) 
			{
				buf[ptr++]=HDLC_RNR|(b_seq&0xf0);
			}
		/*	else if(oldControlByte==HDLC_UI)
			{
				rxseq = (b_seq>>5)&0x7;
				rxseq++;
				rxseq%=8;
				buf[ptr++]=HDLC_RNR|((rxseq<<5)&0xf0);
			}*/
			else if(/*(txseq == (buf[ptr]>>5)&0x7) ||*/ (oldControlByte==HDLC_UI))
			{
				//if(i_send_len)
				//	return i_send_len;
				
				//Serial_Write(b_Hdlc_sendbuf,i_send_len);
				buf[ptr++]=HDLC_RNR|(b_seq&0xf0);
				//b_seq=0x10;
				//buf[ptr++]=HDLC_DM;
			}
			else
				return 0;
#endif
			//else
			//if((txseq == (buf[ptr]>>5)&0x7))// || (rxseq == (buf[ptr]>>5)&0x7))
			//	buf[ptr++]=HDLC_RR|(b_seq&0xf0);
		//	else
		//	{
	//			b_seq=0x10;
		//		buf[ptr++]=HDLC_DM;
	//		}
			break;
		case HDLC_RNR:
			//buf[ptr++]=HDLC_RNR|((b_seq+0x20)&0xf0);
			buf[ptr++]=HDLC_RNR|(b_seq&0xf0);
			break;
		case HDLC_SNRM:
			b_seq=0x10;
			Connected=255;
			ui_flag=1;
			buf[ptr++]=HDLC_UA;
			Close_tls();
		#if 0
		  buf[10+Len]=0x81;Len++;
			buf[10+Len]=0x80;Len++;
			buf[10+Len]=0x12;Len++;
			buf[10+Len]=0x05;Len++;buf[10+Len]=0x01;Len++;buf[10+Len]=0xFE;Len++;
			buf[10+Len]=0x06;Len++;buf[10+Len]=0x01;Len++;buf[10+Len]=0xFE;Len++;
			buf[10+Len]=0x07;Len++;buf[10+Len]=0x04;Len++;buf[10+Len]=00;Len++;buf[10+Len]=00;Len++;buf[10+Len]=00;Len++;buf[10+Len]=01;Len++;
			buf[10+Len]=0x08;Len++;buf[10+Len]=0x04;Len++;buf[10+Len]=00;Len++;buf[10+Len]=00;Len++;buf[10+Len]=00;Len++;buf[10+Len]=01;Len++;
		#endif
			break;
		case HDLC_DISC:
			b_seq=0x10;
			Connected=0;
			buf[ptr++]=HDLC_DM;
			break;
		default:
			b_seq=0x10;
			buf[ptr++]=HDLC_DM;
			break;
	}
	i_crc = DoCrc16(0xffff,buf+1,ptr-1);
	buf[ptr++] = i_crc&0xff;
	buf[ptr++] = (i_crc>>8)&0xff;
	if(Len)
	{
		ptr += Len;
		i_crc = DoCrc16(0xffff,buf+1,ptr-1);
		buf[ptr++] = i_crc&0xff;
		buf[ptr++] = (i_crc>>8)&0xff;
	}
	/*
	buf[1] = 0xA0 | (((ptr-1))>>8)&0x3f;
	buf[2]=(ptr-1)&0xff;*/
	buf[ptr++]=0x7E;
	return ptr;
}

void CM_HDLC_Receive(void)
{
	uint16_t i_rx_length;
	int16_t i;
	uint16_t i_send_length;
	uint8_t ClientAddr,LMN_Addr,Proto_Index;
//	uint8_t seqbak;
	//uint8_t ControlByte;
	//uint8_t *send_ptr;
#ifdef TEST	
	if(hdlc_back)
	{
		i_send_len=hdlc_back();
		hdlc_back=0;
	}
#endif
/*	if(res_count&&ms_count<100)
	{
		return;
	}*/
	//test end
#if 1	
	if(hdlc_back && (ControlByte==HDLC_RR) && (HDLS_STATUS==0))
	{
		i_send_len=hdlc_back();
		hdlc_back=0;
		ControlByte=HDLC_I;
	}
#endif	
	i_rx_length=1024-i_rx_len;
	if(i_rx_length>1024)
	{
		i_rx_len=0;
		i_rx_length=1024;
	}
	i_rx_length=HDLC_READ(b_Hdlc_buf+i_rx_len,i_rx_length);
	/*if(i_rx_len)
	{
		if(i_rx_len>2)
		{
			i_rx_length = b_Hdlc_buf[2]+2;
			i_rx_length -= i_rx_len;
		}
		i_rx_length=Serial_Read(b_Hdlc_buf+i_rx_len,i_rx_length);
	}
	else
	{
		i_rx_length=Serial_Read(b_Hdlc_buf,11);
	}*/
	#if 1 //test delete
	if(i_rx_length==0)
	{
		return;
	}
	#endif
	i_rx_len+=i_rx_length;
	if(i_rx_len<11)
		return;

	i=Hdlc_Check(b_Hdlc_buf,i_rx_len);
	if(i>0)
	{
		i_rx_len=i;
		return;
	}
	i_rx_len=0;
	if(i<0)
	{
	//	i_rx_len=0;
		return;
	}
	
//	if(i==0)
	{
		if(GetMeterAddress(b_Hdlc_buf,&ClientAddr,&LMN_Addr,&Proto_Index)) 
		{
		//	i_rx_len=0;
			return;
		}
		i_Meter_Prot_old=i_Meter_Prot;
		i_Meter_Prot=Proto_Index;
		if(i_Meter_Prot<HDLC_I_PROTOCOL_TLS_COSEM || i_Meter_Prot>HDLC_I_PROTOCOL_TLS_SMLSYM2)
							return;
		oldControlByte=ControlByte;
		ControlByte=GetControlByte(b_Hdlc_buf[7]);
		i_rx_length=b_Hdlc_buf[1]&0x7;
		i_rx_length<<=8;
		i_rx_length+=b_Hdlc_buf[2];
		i_rx_length-=9;
		if(i_rx_length>0)
			i_rx_length-=2;
	//	SystemDelay(5);
		//udelay(250);
		//mdelay(1);
		//gprs_ms=5;
		
		//mdelay(1);
		if(i_Meter_Addr==LMN_Addr && ControlByte!=HDLC_I)
	//	 if(1)
		{
			//udelay(25);
					//SystemDelay(100);
					/*if(ms_count>1500)
					{
						oldControlByte=HDLC_UI;
						//ms_count=0;
					}*/
					/*if(i_send_len && ControlByte==HDLC_RR && oldControlByte==HDLC_RR)
					{	
						Serial_Write(b_Hdlc_sendbuf,i_send_len);
						i_send_len=0;
					}
					else *///if((oldControlByte==HDLC_SNRM) || (ControlByte!=HDLC_RR) || (oldControlByte==HDLC_UI) /*|| (oldControlByte!=HDLC_I)*/)
					{
						/*if(ms_count>50000)
							i_send_len=0;*/
						//mdelay(5);
						/*if(res_count>10)
						{
							mdelay(10);
							res_count-=10;
						}*/
						
						if(ControlByte==HDLC_RR && oldControlByte!=HDLC_I)
						{	
							if((b_seq&0xe) == (b_Hdlc_buf[7]>>4&0xe))
							{
								if(i_send_len)
								{
									oldControlByte=HDLC_I;
									i_send_len=0;
								}
							}
							if(hdlc_back)
							{
								i_send_len=hdlc_back();
								hdlc_back=0;
								res_count=1;
							//	b_seq = b_seq-0x20;
							}
						}
						if(ControlByte==HDLC_RR  && i_send_len)
						{
							ControlByte=HDLC_I;
							b_seq = (b_seq&0xf0)| ((b_Hdlc_buf[7]>>4)&0xe);
#if 0							
							if(res_count)
							{
								ui_flag=0;
								/*seqbak=b_seq;
								ControlByte=HDLC_RNR;
								i_send_length=HDLC_Assemble(b_short_frame,0);
								Serial_Write(b_short_frame,i_send_length);
								b_seq=seqbak;
								ControlByte=HDLC_I;
								Serial_Read(b_Hdlc_buf,256);
								res_count=0;
								ms_count=0;
								return;*/
								i_send_length=HDLC_Assemble(b_Hdlc_sendbuf,i_send_len);
								
							}
							else
#endif								
							{
								//mdelay(1);
								ControlByte=HDLC_I;
								i_send_length=HDLC_Assemble(b_Hdlc_sendbuf,i_send_len);
								ControlByte=HDLC_RR;
							//	i_send_len=0;
							}
							res_count=0;
							ms_count=0;
						}
						else
							i_send_length=HDLC_Assemble(b_Hdlc_sendbuf,0);					
						if(i_send_length)
						{
							HDLC_WRITE(b_Hdlc_sendbuf,i_send_length);
							i_send_length=0;
						}
					}
		}
		else if(i_Meter_Addr==LMN_Addr && ControlByte==HDLC_I) //地址匹配
		{
			ms_count=0;
			res_count=1;
			hdlc_back=0;
		//	udelay(50);
			//SystemDelay(300);
			//seqbak = (((b_Hdlc_buf[7]>>5)&7)<<1) | ((((b_Hdlc_buf[7]>>1))&7)<<5);
			/*if(ui_flag)
			{
				ui_flag=0;
				b_seq=b_seq-0x20;
				HDLC_Assemble(b_short_frame,0);
				Serial_Write(b_short_frame,11);
			}*/
				b_seq = (((b_Hdlc_buf[7]>>5)&7)<<1) | ((((b_Hdlc_buf[7]>>1))&7)<<5);
			  b_seq +=0x20;
		//	b_seq = (((((b_seq>>5)&0x7)+1)%8)<<5) | (b_seq&0x1e);
#if 1		 //TEST delete	
			ControlByte=HDLC_RNR;
			i_send_length=HDLC_Assemble(b_short_frame,0);
			HDLC_WRITE(b_short_frame,i_send_length);
			ControlByte=HDLC_I;
#endif			
			switch(i_Meter_Prot)
			{
				case HDLC_I_PROTOCOL_TLS_COSEM:
					i_send_len=Cm_Tls_Analys(b_Hdlc_buf+10,i_rx_length,b_Hdlc_sendbuf+10,&hdlc_back);
				/*	if(i_send_len<70)
					{
						i_send_length=HDLC_Assemble(b_Hdlc_sendbuf,i_send_len);
						Serial_Write(b_Hdlc_sendbuf,i_send_length);
					//i_send_len=0;
					}*/
					break;
		//		case HDLC_I_PROTOCOL_TLS_NOCONTENT:
		//			break;
				case HDLC_I_PROTOCOL_SML_COSEM:
#if 1 //test					
					i_send_length=0;
					if(i_rx_length)
					{
						CmSet_SML_Recevie_Buf(b_Hdlc_buf+10,i_rx_length);
						/*oldControlByte=HDLC_I;
						ControlByte=HDLC_RR;
						//b_seq ^= seqbak;
						//seqbak ^= b_seq;
					//	b_seq ^= seqbak;
						i_send_length=HDLC_Assemble(b_Hdlc_buf,0);
						Serial_Write(b_Hdlc_buf,i_send_length);
						ControlByte=HDLC_I;*/
					//	b_seq = seqbak;
						/*ControlByte=HDLC_RNR;
						seqbak=b_seq;
						HDLC_Assemble(b_short_frame,0);
						Serial_Write(b_short_frame,11);
						b_seq = seqbak;
						ControlByte=HDLC_I;*/
						AnalyseSML(b_Hdlc_sendbuf+10);
						i_send_len=CmGet_SML_Send_Buf(b_Hdlc_sendbuf+10);
					}
#else
					memcpy(b_Hdlc_sendbuf+10,sml_test,164);
					i_send_len=164;
				/*	seqbak=b_seq;
					i_send_length=HDLC_Assemble(b_Hdlc_sendbuf,i_send_len);
					b_seq=seqbak;
					Serial_Write(b_Hdlc_sendbuf,i_send_length);*/
#endif					
					//i_rx_length=Serial_Read(b_Hdlc_buf,256);
					//if(i_rx_length>0)
				/*	{
						ControlByte=HDLC_RNR;
						seqbak=b_seq;
						HDLC_Assemble(b_short_frame,0);
						Serial_Write(b_short_frame,11);
						b_seq = seqbak;
						ControlByte=HDLC_I;
					}*/
				/*	while(ms_count<500) udelay(1);
					Stop_Tc0();
					ms_count=0;
					fnINTTC0_Init();*/
					/*seqbak=b_seq;
					i_send_length=HDLC_Assemble(b_Hdlc_sendbuf,i_send_len);
					b_seq=seqbak;
					Serial_Write(b_Hdlc_sendbuf,i_send_length);*/
				//	i_send_len=0;
					break;
	//			case HDLC_I_PROTOCOL_SML_EDL:
	//				break;
	//			case HDLC_I_PROTOCOL_SML_SYM2:
		//			break;
				case HDLC_I_PROTOCOL_SYM:
					i_send_len=CmSym(b_Hdlc_buf+10,b_Hdlc_sendbuf+10,i_rx_length);
				/*	if(i_send_len)
					{
						i_send_len=HDLC_Assemble(b_Hdlc_sendbuf,i_send_len);
						Serial_Write(b_Hdlc_sendbuf,i_send_len);
					//	i_send_len=0;
					}*/
					break;
		//		case HDLC_I_PROTOCOL_TLS_SML_EDL:
		//			break;
		//		case HDLC_I_PROTOCOL_TLS_SMLSYM2:
			//		break;
				default:
					break;
			}
			/*
			if(i_send_len==0)
			{
				//ControlByte=HDLC_DISC;
				i_send_length=HDLC_Assemble(b_short_frame,0);
				HDLC_WRITE(b_short_frame,i_send_length);
			}*/
			res_count=ms_count+1;
	//		Serial_Read(b_Hdlc_buf,256);
			/*if(res_count>5000)
			{
				ControlByte=HDLC_RNR;
				i_send_length=HDLC_Assemble(b_short_frame,0);
				Serial_Write(b_short_frame,i_send_length);
				ControlByte=HDLC_I;
			}*/
		}
		else if(LMN_Addr==0x7F  && ControlByte==HDLC_UI) //广播地址
		{
		//	ms_count=0;
			i_send_len=0;
			hdlc_back=0;
		//	gprs_ms=6;
			i_send_length=Cm_Handle_Assign_Addr(b_Hdlc_buf+10,i_rx_length);
			//mdelay(50);
			mdelay(5);
#if 1
			switch(i_Meter_Prot)
			{
				case HDLC_UI_PROTOCOL_ADDR_ASSIGN:
					mdelay(rand()%10);
					break;
				case HLDC_UI_PROTOCOL_ADDR_VERIFY:
					//mdelay(5);
					if(m_lmn_info.b_hdlc_slot && m_lmn_info.b_hdlc_slot<100)
						mdelay((m_lmn_info.b_hdlc_slot-1)*10);
					break;
				default:
					return;
			}
			RAM_Write(b_Hdlc_sendbuf+10,(uint8_t *)&m_lmn_info,32);
			i_send_length=HDLC_Assemble(b_Hdlc_sendbuf,32);
			HDLC_WRITE(b_Hdlc_sendbuf,i_send_length);
#else
			//i_send_length=Cm_Handle_Assign_Addr(b_Hdlc_buf+10,i_rx_length);
			//if(((i_Meter_Prot==HDLC_UI_PROTOCOL_ADDR_ASSIGN)&&i_send_length) || ((i_Meter_Prot==HLDC_UI_PROTOCOL_ADDR_VERIFY)&&(i_send_length==0)))
			{
				if(i_Meter_Prot==HLDC_UI_PROTOCOL_ADDR_VERIFY)
				{
					mdelay(5);
				//	mdelay((m_lmn_info.b_hdlc_slot-1)*10);
				}
				RAM_Write(b_Hdlc_sendbuf+10,(uint8_t *)&m_lmn_info,32);
				i_send_length=HDLC_Assemble(b_Hdlc_sendbuf,32);
				Serial_Write(b_Hdlc_sendbuf,i_send_length);
			}
#endif
		}
	}
	//memset(b_Hdlc_buf,0,256);
	return;
}
