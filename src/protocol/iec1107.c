#include "iec1107.h"
#include "serial.h"
#include "hdlc.h"
#include "tls.h"
#include "data.h"

#define IEC1107_READ(buf,len) Serial_Read(1,buf,len)
#define IEC1107_WRITE(buf,len) (Serial_Write(1,buf,len))
#define IEC1107_STATUS				Serial_Status(1)
uint8_t iec1107_buf[128];
uint8_t iec1107_sendbuf[64];
uint8_t iec1107_buf_pos;
struct iec1107_s
{
	uint8_t iec1107_code[16];
	uint32_t ramaddr; 
	uint8_t deci;
};
uint8_t ieccmd_ptr;
#define IEC1107_TABLE_NUM    17
struct iec1107_s iec1107_table[IEC1107_TABLE_NUM]=
{
	"96.1.0",(uint32_t)&Para.servrid,16,
	//"0.0.0",(uint32_t)&Para.servrid,16,
	"1.8.0",(uint32_t)&Para.Pp0,10,
	"2.8.0",(uint32_t)&Para.Pn0,10,
	/*"32.07.00",(uint32_t)&Para.Ua,10,
	"52.07.00",(uint32_t)&Para.Ub,10,
	"72.07.00",(uint32_t)&Para.Uc,10,
	"31.07.00",(uint32_t)&Para.Ia,10,
	"51.07.00",(uint32_t)&Para.Ib,10,
	"71.07.00",(uint32_t)&Para.Ic,10,*/
	"32.7.0",(uint32_t)&Para.Ua,10,
	"52.7.0",(uint32_t)&Para.Ub,10,
	"72.7.0",(uint32_t)&Para.Uc,10,
	"31.7.0",(uint32_t)&Para.Ia,10,
	"51.7.0",(uint32_t)&Para.Ib,10,
	"71.7.0",(uint32_t)&Para.Ic,10,
	"16.7.0",(uint32_t)&Para.Pt,10,
	"14.7.0",(uint32_t)&Para.Freq,10,
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
void iec1107_write(void)
{
	switch(ieccmd_ptr)
	{
		case 0:
			Serial_Open(1,600,7,SERIAL_CHECK_EVEN);
			memcpy(iec1107_sendbuf,"/?!",3);
		  iec1107_sendbuf[3]=0x0d;
		  iec1107_sendbuf[4]=0x0a;
			IEC1107_WRITE(iec1107_sendbuf,5);
			ieccmd_ptr++;
			Comm.BTime2=60;
			break;
		case 1:
			iec1107_sendbuf[0]=0x06;
		  iec1107_sendbuf[1]=0x30;
			iec1107_sendbuf[2]=0x31;
			//iec1107_sendbuf[2]=0x35;
			iec1107_sendbuf[3]=0x30;
			iec1107_sendbuf[4]=0x0d;
		  iec1107_sendbuf[5]=0x0a;
			ieccmd_ptr++;
			IEC1107_WRITE(iec1107_sendbuf,6);
			Comm.BTime2=45;
		  break;
		default:
			ieccmd_ptr++;
			Comm.BTime2=128;
			//Serial_Open(1,9600,7,SERIAL_CHECK_EVEN);
			break;
	}
}
void iec1107_read(void)
{
	uint8_t len,pos,i,j,k,p,kk;
	uint64_t tmp;
	if(iec1107_buf_pos>100)
		iec1107_buf_pos=0;
	len=IEC1107_READ(iec1107_buf+iec1107_buf_pos,128-iec1107_buf_pos);
	if(len)
	{
		Comm.BTime2=128;
		len +=iec1107_buf_pos;
		if((iec1107_buf[len-2]!=0x0d) || (iec1107_buf[len-1]!=0x0a))
		{
			iec1107_buf_pos=len;
			return;
		}	
#if 1		
		for(i=0;i<len;++i)
		{
			WDT->EN = 0xbb;
		//	if((iec1107_buf[i]==0x0d && iec1107_buf[i+1]==0x0a) || (iec1107_buf[i]==0x02))  //找到开头的
			{
				
				//if(iec1107_buf[i+2]==0x0d && iec1107_buf[i+3]==0x0a)
				/*while(iec1107_buf[i+2]==0x0d && iec1107_buf[i+3]==0x0a)
				{
					i+=2;
					if(i>=len)
						break;
				}*/
#if 1				
				for(j=i+1;j<len;++j)
				{
					if(iec1107_buf[j]==0x0d && iec1107_buf[j+1]==0x0a)  //找到结尾的
					{
						break;
					}
				}
#else
				j=i+1;
#endif
			
				if(j>=len)  //没找到结尾退出
				{
					break;
				}
				else
				{
					if(iec1107_buf[2]=='/' || iec1107_buf[2]=='!')
					{
						i +=(j+1);
						break;
					}
					k=i+1;
#if 1					
					while(k<j && k<len)
					{
						if(iec1107_buf[k]=='(')
						{
							break;
						}
						++k;
					}
#endif					
					//iec1107_buf_pos+=j+1;
					if(k>=j)
					{
						i=j+1;
						continue;
						//break;
					}
#if 1					
					for(p=0;p<IEC1107_TABLE_NUM;++p)
					{
						if(iec1107_buf[i]==0x02)
							i++;
						if(k<=i)
							break;
						if(!memcmp(iec1107_table[p].iec1107_code,iec1107_buf+i,k-(i)))
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
#endif					
					i +=(j+1);
				}
			}
			/*else
			{
				++i;
			}*/
		}
#else
		i=0;
#endif
#if 0		
		if(len>i)
		{	
			memcpy(iec1107_buf,iec1107_buf+i,len-i);
			iec1107_buf_pos=len-i;
#if 0			
			for(i=0;i<iec1107_buf_pos;++i)
			{
				if(iec1107_buf[i]==ETX)
				{
					iec1107_buf_pos=0;
					ieccmd_ptr=0;
					break;
				}
			}
#endif			
		}
		else
		{
			iec1107_buf_pos=0;
		}
#else
	iec1107_buf_pos=0;		
#endif		
	}
	else
	{
		
		if((IEC1107_STATUS==0) && (ieccmd_ptr<3) && ((Comm.BTime2<10)))
		{
			iec1107_buf_pos=0;
			iec1107_write();
		}
		/*if(Comm.BTime2==0)
		{
		}*/
	}
	
	return;
}
