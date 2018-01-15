#include "iec1107.h"
#include "serial.h"
#include "hdlc.h"
#include "tls.h"
#include "data.h"

#define IEC1107_READ(buf,len) Serial_Read(1,buf,len)
#define IEC1107_WRITE(buf,len) (Serial_Write(1,buf,len))
#define IEC1107_STATUS				Serial_Status(1)
uint8_t iec1107_buf[256];
uint8_t iec1107_sendbuf[8];
uint8_t iec1107_buf_pos;
struct iec1107_s
{
	uint8_t iec1107_code[16];
	uint32_t ramaddr; 
	uint8_t deci;
	uint8_t Len;
};
uint8_t ieccmd_ptr;
extern uint8_t firmware_version[];
#define IEC1107_TABLE_NUM    28
const struct iec1107_s iec1107_table[IEC1107_TABLE_NUM]=
{
	"1-0:96.1.0*255",(uint32_t)&Para.servrid,10,16,
	"1-0:1.8.0*255",(uint32_t)&Para.Pp0[0],16,5,
	"1-0:1.8.0*255",(uint32_t)&Para.Pp1[0],16,5,
	"1-0:1.8.0*255",(uint32_t)&Para.Pp2[0],16,5,
	"1-0:1.8.0*255",(uint32_t)&Para.Pp3[0],16,5,
	"1-0:1.8.0*255",(uint32_t)&Para.Pp4[0],16,5,
	"1-0:2.8.0*255",(uint32_t)&Para.Pn0[0],16,5,
	"1-0:16.7.0*255",(uint32_t)&Para.Pt[0],16,3,
	"1-0:32.7.0*255",(uint32_t)&Para.Ua[0],16,2,
	"1-0:52.7.0*255",(uint32_t)&Para.Ub[0],16,2,
	"1-0:72.7.0*255",(uint32_t)&Para.Uc[0],16,2,
	"1-0:31.7.0*255",(uint32_t)&Para.Ia[0],16,3,
	"1-0:51.7.0*255",(uint32_t)&Para.Ib[0],16,3,
	"1-0:71.7.0*255",(uint32_t)&Para.Ic[0],16,3,
	"1-0:71.7.0*255",(uint32_t)&Para.Pangleba[0],16,2,
	"1-0:71.7.0*255",(uint32_t)&Para.Pangleca[0],16,2,
	"1-0:71.7.0*255",(uint32_t)&Para.Panglea[0],16,2,
	"1-0:71.7.0*255",(uint32_t)&Para.Pangleb[0],16,2,
	"1-0:71.7.0*255",(uint32_t)&Para.Panglec[0],16,2,
	"1-0:14.7.0*255",(uint32_t)&Para.Freq[0],16,2,
	"1-0:1.8.00*60",(uint32_t)&Para.P0_day,10,3,
	"1-0:1.8.00*61",(uint32_t)&Para.P0_week,10,3,
	"1-0:1.8.00*62",(uint32_t)&Para.P0_month,10,3,
	"1-0:1.8.00*63",(uint32_t)&Para.P0_year,10,3,
	"1-0:1.8.00*65",(uint32_t)&Para.P0_last,10,3,	
	"1-0:1.8.00*65",(uint32_t)firmware_version,10,7,	
	"1-0:1.8.00*65",(uint32_t)SM.CPUCRC_M,10,2,	
	"1-0:97.97.0*255",(uint32_t)&Para.meter_sts,16,4,
};
uint64_t strtoint(uint8_t *buf,uint8_t len,uint8_t deci)
{
	uint64_t ret;
	uint8_t i;
	for(i=0,ret=0;i<len;++i)
	{
		if(buf[i]>='0' &&  buf[i]<='9')
		{
			ret *=deci;
			ret +=(buf[i]-'0');
		}
		else if(buf[i]>='a' &&  buf[i]<='f')
		{
			ret *=deci;
			ret +=(buf[i]-'a')+10;
		}
		else if(buf[i]>='A' &&  buf[i]<='F')
		{
			ret *=deci;
			ret +=(buf[i]-'A')+10;
		}
		else if(buf[i]=='*')
			break;
	}
	return ret;
}
extern struct S_Hdlc_LMN_Info m_lmn_info;
unsigned char iec_flag;
extern uint8_t Connected;
void iec1107_write(void)
{
	switch(ieccmd_ptr)
	{
		case 0:
			Serial_Open(1,9600,8,SERIAL_CHECK_NO);
			memcpy(iec1107_sendbuf,"/2!",3);
			iec1107_sendbuf[1]+=Connected+Get_Tls_status();
		  iec1107_sendbuf[3]=0x0d;
		  iec1107_sendbuf[4]=0x0a;
			IEC1107_WRITE(iec1107_sendbuf,5);
			ieccmd_ptr++;
			Comm.BTime2=50;
			iec_flag=0;
			break;
		default:
			ieccmd_ptr++;
			Comm.BTime2=32;
			break;
	}
}

uint16_t CCIT(uint8_t *pucData, uint16_t usDataLen)
{
	uint16_t Generator=0x1021;
	uint16_t Crc;
	uint8_t bit;
	Crc=0;
	while( usDataLen-- > 0 )
  {
		Crc ^= *pucData<<8;
		pucData++;
		for(bit=0;bit<8;bit++)
		{
			if((Crc&0x8000)!=0)
			{
				Crc<<=1;
				Crc^=Generator;
			}
			else
			{
				Crc<<=1;
			}
		}	
	}
	return Crc;
}

uint16_t k,kk;
void iec1107_read(void)
{
	uint16_t len,pos,i,j,p;
	uint64_t tmp;
	
	if(iec1107_buf_pos>250)
		iec1107_buf_pos=0;
	len=IEC1107_READ(iec1107_buf+iec1107_buf_pos,250-iec1107_buf_pos);
	if(len)
	{
		Comm.BTime2=32;
		len +=iec1107_buf_pos;
		iec1107_buf_pos=len;
		if(len>20)
		{
			pos=BCD_Byte(iec1107_buf[17]);
			pos=(pos*100)+BCD_Byte(iec1107_buf[18]);
		//	pos=BCD2_Word(iec1107_buf+17);
			if(len==(pos+19))
			{
#if 1				
				kk=pos-2;
				k=CCIT(iec1107_buf+19,kk);
				kk=iec1107_buf[17+pos];
				kk=kk<<8|iec1107_buf[18+pos];
#endif				
				if(k==kk)
				{
					for(i=19,p=0;i<(len-2) && p<IEC1107_TABLE_NUM;i+=iec1107_table[p++].Len)
					{
						if(p==0)
						{
							tmp=strtoint(iec1107_buf+i+6,10,iec1107_table[p].deci);
							if(tmp!=Para.servrid)
							{
								Para.servrid=tmp;
								memcpy(m_lmn_info.b_sensor_identification,m_lmn_info.b_sub_identification,5);
								memcpy(m_lmn_info.b_sensor_identification+5,&tmp,5);
								Cm_Ram_Inter(m_lmn_info.b_sensor_identification+5,5);
								memcpy(m_lmn_info.b_sub_identification,m_lmn_info.b_sensor_identification,10);
								E2P_WData( Server_ID,m_lmn_info.b_sub_identification, 10 );
							}
						}
						else if(p==25)
						{
							((unsigned char *)iec1107_table[p].ramaddr)[0]=(iec1107_buf[i+4]>>4)+0x30;
							((unsigned char *)iec1107_table[p].ramaddr)[1]=(iec1107_buf[i+4]&0xf)+0x30;
							((unsigned char *)iec1107_table[p].ramaddr)[2]=(iec1107_buf[i+5]>>4)+0x30;
							((unsigned char *)iec1107_table[p].ramaddr)[3]=(iec1107_buf[i+5]&0xf)+0x30;
							((unsigned char *)iec1107_table[p].ramaddr)[4]=(iec1107_buf[i+6]>>4)+0x30;
							((unsigned char *)iec1107_table[p].ramaddr)[5]=(iec1107_buf[i+6]&0xf)+0x30;
							
						}
						else
						{
							memcpy((unsigned char *)iec1107_table[p].ramaddr,iec1107_buf+i,iec1107_table[p].Len);
							Cm_Ram_Inter((unsigned char *)iec1107_table[p].ramaddr,iec1107_table[p].Len);
						}
					}
					Para.meter_sts |=0x4;
				}
		//		memset(iec1107_buf,0,128);
				Comm.BTime2=20;
				ieccmd_ptr=0;
			}
			else
			{
				return;
			}
		}
	}
	else
	{
		if((IEC1107_STATUS==0) && (ieccmd_ptr<2) && ((Comm.BTime2==0)))
		{
			iec1107_buf_pos=0;
			Para.p_count=0;
			iec1107_write();
		}
	}

	return;
}
