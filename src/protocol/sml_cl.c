#include "typeE2p.h" 
#include "sml.h"
#include "data.h"


#define SML_READ(buf,len) Serial_Read(buf,len)
#define SML_WRITE(buf,len) (Serial_Write(buf,len))
#define SML_STATUS				Serial_Status()

SMLCOMM sml_cl_com;
uint8_t tabNo;
#define GET_NUM     3
const SMLOBISTAB	SMLGetOBISTab[]=
{
	0x01,0x00,0x20,0x07,0x00,0xFF, Len8,0x69,(uint32_t)&Para.Ua,				RAM_INTER_TYPE+READ,			3,0,0,
	0x01,0x00,0x34,0x07,0x00,0xFF, Len8,0x69,(uint32_t)&Para.Ub,				RAM_INTER_TYPE+READ,			3,0,0,
	0x01,0x00,0x48,0x07,0x00,0xFF, Len8,0x69,(uint32_t)&Para.Uc,				RAM_INTER_TYPE+READ,			3,0,0,
};
const uint8_t SML_CONST_HEAD[8]={0x1b,0x1b,0x1b,0x1b,0x01,0x01,0x01,0x01};
const uint8_t SML_CONST_END[5]={0x1b,0x1b,0x1b,0x1b,0x1a};
int16_t CM_Sml_Message_Esc(void)
{
	int i;
	for(i=0;i<4;++i)
		sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x1b;
	for(i=0;i<4;++i)
		sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x01;
	return i;
}

int16_t CM_Sml_Message_head(uint32_t SML_MessageBody)
{
	int i;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x76;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x05;
	for(i=0;i<4;++i)
		sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=i+1;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x62;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x00;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x62;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x00;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x72;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x65;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=(SML_MessageBody>>24)&0xff;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=(SML_MessageBody>>16)&0xff;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=(SML_MessageBody>>8)&0xff;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=(SML_MessageBody)&0xff;
	return i;
}

int16_t CM_Sml_Message_Open_Req()
{
	int i;
	uint16_t	StartAdd;
	CM_Sml_Message_Esc();
	StartAdd = sml_cl_com.SendPtr;
	CM_Sml_Message_head(Open_Req);
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x77;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x01;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x0B;
	E2P_RData( &(sml_cl_com.SendBuf[sml_cl_com.SendPtr]),Server_ID, 10 ); 
	sml_cl_com.SendPtr +=10;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x05;
	for(i=0;i<4;++i)
		sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=i+1;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x0B;
	E2P_RData( &(sml_cl_com.SendBuf[sml_cl_com.SendPtr]),Server_ID, 10 ); 
	sml_cl_com.SendPtr +=10;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x01;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x01;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x01;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x63;//ÃÓ–¥CRC//
	DoCrc161(&(sml_cl_com.SendBuf[sml_cl_com.SendPtr]),0xffff,&(sml_cl_com.SendBuf[StartAdd]),sml_cl_com.SendPtr-StartAdd-1);
	sml_cl_com.SendPtr+=2;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0;
	return i;
}

int16_t CM_Sml_Message_Close_Req()
{
	int i;
	uint16_t	StartAdd;
	StartAdd = sml_cl_com.SendPtr;
	CM_Sml_Message_head(Close_Req);
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x71;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x01;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x63;//ÃÓ–¥CRC//
	DoCrc161(&(sml_cl_com.SendBuf[sml_cl_com.SendPtr]),0xffff,&(sml_cl_com.SendBuf[StartAdd]),sml_cl_com.SendPtr-StartAdd-1);
	sml_cl_com.SendPtr+=2;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0;
	return i;
}


int16_t CM_Sml_Message_GetProc_Req()
{
	int i;
	uint16_t	StartAdd;
	StartAdd = sml_cl_com.SendPtr;
	CM_Sml_Message_head(GetPropP_Req);
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x75;
	
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x0B;
	E2P_RData( &(sml_cl_com.SendBuf[sml_cl_com.SendPtr]),Server_ID, 10 ); 
	sml_cl_com.SendPtr +=10;
	
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x01;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x01;
	
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x72;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x0A;
	//for(i=0;i<6;++i)
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=SMLGetOBISTab[tabNo].OBIS0;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=SMLGetOBISTab[tabNo].OBIS1;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=SMLGetOBISTab[tabNo].OBIS2;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=SMLGetOBISTab[tabNo].OBIS3;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=SMLGetOBISTab[tabNo].OBIS4;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=SMLGetOBISTab[tabNo].OBIS5;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=(SMLGetOBISTab[tabNo].Class>>8)&0xff;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=(SMLGetOBISTab[tabNo].Class)&0xff;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=3;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=2;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=1;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x63;//ÃÓ–¥CRC//
	DoCrc161(&(sml_cl_com.SendBuf[sml_cl_com.SendPtr]),0xffff,&(sml_cl_com.SendBuf[StartAdd]),sml_cl_com.SendPtr-StartAdd-1);
	sml_cl_com.SendPtr+=2;
	sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0;
	return i;
}

void	WriteSmlSendBufEnd(void)
{
  uint8_t i,j;
	
	i=(sml_cl_com.SendPtr)%4;
  if(i!=0)
  {
		i=4-i;
	}
  for(j=0;j<i;j++)
  {
    sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x00;
  }	
  
  for(j=0;j<4;j++)
  {
    sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x1B;
  }	
  sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=0x1A;	
  sml_cl_com.SendBuf[sml_cl_com.SendPtr++]=i;
	
	DoCrc161(&(sml_cl_com.SendBuf[sml_cl_com.SendPtr]),0xffff,&(sml_cl_com.SendBuf[0]),sml_cl_com.SendPtr);
  sml_cl_com.SendPtr+=2;	
}	

void Analysis_Sml_Data(uint32_t body_code,uint8_t *obis_code,uint16_t class_id,uint8_t *data)
{
	switch(body_code)
	{
		case Open_Res:
			break;
		case Close_Res:
			break;
		case GetProfP_Res:
			break;
		case GetProfL_Res:
			break;
		case GetPropP_Res:
			{
				if((memcmp(&SMLGetOBISTab[tabNo].OBIS0,obis_code,6)==0) && (class_id==SMLGetOBISTab[tabNo].Class))
				{
					switch(SMLGetOBISTab[tabNo].State & 0x00FF)
					{	
						case RAM_INTER_TYPE:
							RAM_WriteInter((unsigned char*)SMLGetOBISTab[tabNo].Adder,&(data[1]),SMLGetOBISTab[tabNo].Len);
							break;
						case RAM_TYPE:
							RAM_Write((unsigned char*)SMLGetOBISTab[tabNo].Adder,&(data[1]),SMLGetOBISTab[tabNo].Len);
							break;
						case E2P_TYPE:
							E2P_WData(SMLGetOBISTab[tabNo].Adder,&(data[1]),SMLGetOBISTab[tabNo].Len);
							break;
						default:
							break;
					}
				}
			}
			break;
		case SetPropP_Res:
			break;
		default:
			break;
	}
	return;
}

void Analysis_Sml(uint8_t *buf,uint16_t len)
{
	uint8_t *ptr,*obis_ptr;
	uint16_t class_id;
	uint16_t analysis_len;
	uint8_t type_len,type;
	uint32_t body_code;
	uint8_t layer;
	if(len<64)
		return;
	if(memcmp(buf,SML_CONST_HEAD,8))
		return;
	if(memcmp(buf+len-8,SML_CONST_END,5))
		return;
	len -= 3; //crc
	len = len-buf[len]-5; //ÃÓ≥‰
	for(ptr=buf+8,analysis_len=8,layer=0,body_code=0;analysis_len<len;)
	{
		if(buf[analysis_len]==0) //end
		{
			analysis_len++;
			body_code=0;
			layer=0;
			continue;
		}
		type=buf[analysis_len]&0x70;
		type_len=buf[analysis_len]&0x0f;
		if(type==SML_LIST_CODE)
		{
			analysis_len++;
			continue;
		}
		layer++;
/*		
		switch(type)
		{
			case SML_STR_CODE:
				break;
			case SML_BOOL_CODE:
				break;
			case SML_INT_CODE:
				break;
			case SML_UINT_CODE:
				break;
			case SML_LIST_CODE:
				type_len=1;
				break;
		}
		*/
		
		switch(layer)
		{
			case 4:
				if(type==SML_UINT_CODE)
				{
					if(type_len==3)
					{
						body_code=buf[analysis_len+1];
						body_code=(body_code<<8) | buf[analysis_len+2];
					}
					else if(type_len==5)
					{
						body_code=buf[analysis_len+1];
						body_code=(body_code<<8) | buf[analysis_len+2];
						body_code=(body_code<<8) | buf[analysis_len+3];
						body_code=(body_code<<8) | buf[analysis_len+4];
					}
				}
				break;
			case 8:
				obis_ptr = buf + analysis_len + 1;
			//	class_ptr = buf + analysis_len + 7;
				class_id =buf[analysis_len + 7];
				class_id = (class_id<<8) |buf[analysis_len + 8];
				break;
			case 14:
			case 15:
			case 16:
				if(body_code&&(buf[analysis_len-2]==0x62)&&(buf[analysis_len-1]==0x01))
				{
					Analysis_Sml_Data(body_code,obis_ptr,class_id,buf+analysis_len);
				}
				break;
			default:
				break;
		}
		analysis_len += type_len;
	}
}
  uint32_t sml_tx_rx_time;
	uint8_t tx_rx_flag=0;
	uint8_t sml_rx_buf[512];
	void CM_SML_COMM_Proc(void)
	{
		uint16_t Len;
		if(!sml_tx_rx_time)
		{
			sml_tx_rx_time=500;
			if(tx_rx_flag) //rx
			{
				Len=SML_READ(sml_rx_buf,512);
				Analysis_Sml(sml_rx_buf,Len);
			//	tabNo=0;
				tabNo++;
				tabNo %=GET_NUM;
			}
			else
			{
				sml_cl_com.SendBuf=sml_rx_buf;
				CM_Sml_Message_Open_Req();
				CM_Sml_Message_GetProc_Req();
				CM_Sml_Message_Close_Req();
				WriteSmlSendBufEnd();
				Len=sml_cl_com.SendPtr;
				sml_cl_com.SendPtr=0;
				SML_WRITE(sml_rx_buf,Len);
			}
			tx_rx_flag = !tx_rx_flag;
		}
	}
