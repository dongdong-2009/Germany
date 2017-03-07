#include "iec1107.h"
#include "serial.h"
#include "hdlc.h"
#include "tls.h"
#include "data.h"

#define IEC1107_READ(buf,len) Serial_Read(1,buf,len)
#define IEC1107_WRITE(buf,len) (Serial_Write(1,buf,len))
#define IEC1107_STATUS				Serial_Status(1)
uint8_t iec1107_buf[64];
uint8_t iec1107_buf_pos;
struct iec1107_s
{
	uint8_t iec1107_code[16];
	uint32_t ramaddr; 
	uint8_t deci;
};
#define IEC1107_TABLE_NUM    17
struct iec1107_s iec1107_table[IEC1107_TABLE_NUM]=
{
	"0.0.0",(uint32_t)&Para.servrid,16,
	"1.8.0",(uint32_t)&Para.Pp0,10,
	"2.8.0",(uint32_t)&Para.Pn0,10,
	"32.07.00",(uint32_t)&Para.Ua,10,
	"52.07.00",(uint32_t)&Para.Ub,10,
	"72.07.00",(uint32_t)&Para.Uc,10,
	"31.07.00",(uint32_t)&Para.Ia,10,
	"51.07.00",(uint32_t)&Para.Ib,10,
	"71.07.00",(uint32_t)&Para.Ic,10,
	"16.7.0",(uint32_t)&Para.Pt,10,
	"15.07.00",(uint32_t)&Para.Freq,10,
	"F.F",(uint32_t)&Para.meter_sts,16,
	"1.8.00.60",(uint32_t)&Para.P0_day,10,
	"1.8.00.61",(uint32_t)&Para.P0_week,10,
	"1.8.00.62",(uint32_t)&Para.P0_month,10,
	"1.8.00.63",(uint32_t)&Para.P0_year,10,
	"1.8.00.65",(uint32_t)&Para.P0_last,10,
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
void iec1107_read(void)
{
	uint8_t len,pos,i,j,k,p;
	uint64_t tmp;
	if(iec1107_buf_pos>60)
		iec1107_buf_pos=0;
	len=IEC1107_READ(iec1107_buf+iec1107_buf_pos,64-iec1107_buf_pos);
	if(len)
	{
		len +=iec1107_buf_pos;
		for(i=0;i<len && (len-i)>5;)
		{
			if(iec1107_buf[i]==0x0d && iec1107_buf[i+1]==0x0a)  //找到开头的
			{
				
				//if(iec1107_buf[i+2]==0x0d && iec1107_buf[i+3]==0x0a)
				while(iec1107_buf[i+2]==0x0d && iec1107_buf[i+3]==0x0a)
				{
					i+=2;
				}
				for(j=i+6;j<len;)
				{
					if(iec1107_buf[j]==0x0d && iec1107_buf[j+1]==0x0a)  //找到结尾的
					{
						break;
					}
					else
					{
						++j;
					}
				}
				if(j>=len)  //没找到结尾退出
				{
					break;
				}
				else
				{
					if(iec1107_buf[2]=='/' || iec1107_buf[2]=='!')
					{
						i +=(j+2);
						continue;
					}
					k=i+1;
					while(k<j)
					{
						if(iec1107_buf[k]=='(')
						{
							break;
						}
						++k;
					}
					//iec1107_buf_pos+=j+1;
					if(k>=j)
						break;
					for(p=0;p<IEC1107_TABLE_NUM;++p)
					{
						if(!memcmp(iec1107_table[p].iec1107_code,iec1107_buf+i+2,k-(i+2)))
						{
							switch(p)
							{
								case 0:
									tmp=strtoint(iec1107_buf+k+1+6,j-1-k-6,iec1107_table[p].deci);
									if(tmp!=Para.servrid)
									{
										Para.servrid=tmp;
										memcpy(m_lmn_info.b_sub_identification+5,&tmp,5);
										Cm_Ram_Inter(m_lmn_info.b_sub_identification+5,5);
										E2P_WData( Server_ID,m_lmn_info.b_sub_identification, 10 );
									}
									break;
								default:
								*(uint64_t *)iec1107_table[p].ramaddr=strtoint(iec1107_buf+k+1,j-1-k,iec1107_table[p].deci);
								break;
							}
								
							break;
						}
					}
					i +=(j);
				}
			}
			else
			{
				++i;
			}
		}
		if(len>i)
		{	
			memcpy(iec1107_buf,iec1107_buf+i,len-i);
			iec1107_buf_pos=len-i;
		}
		else
		{
			iec1107_buf_pos=0;
		}
	}
	return;
}
