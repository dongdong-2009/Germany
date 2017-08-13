#include"data.h"
#include "typeE2p.h"
#include "sml.h"

SMLRECORD SMLRecord[8];
ORDERRECORD	OrderRecord[16];
ORDERRECORD	OrderRecord0100[10];
SIGNATURE Signatrue;
extern const SMLATTENTIONNUMBER SMLAttentionNumber[];
extern const SMLOBISTAB	SMLOBISTab[];
SMLCOMM	SMLComm;


void CmSet_SML_Recevie_Buf(uint8_t *buf,uint16_t len)
{
	SMLCommInit();
	//memcpy((void *)SMLComm.RecBuf,(const void*)buf,(unsigned int)len);
	SMLComm.RecBuf = buf;
	SMLComm.RecLg=len;
}

uint16_t CmGet_SML_Send_Buf(uint8_t *buf)
{
	uint16_t Len;
	Len=SMLComm.SendPtr;
	if(Len)
	{
	//	memcpy(buf,SMLComm.SendBuf,Len);
		SMLCommInit();
	}
	return Len;
}
//�յ������Ľ�������,���:���ָ��,����,����:���Ȳ�ȫ����0,������-1,��ȷ����1//
signed AnalyseOrder(uint16_t BufAd,uint16_t DataLg,uint8_t LayerNo)
{
  uint16_t i,j;
	uint8_t Buff[15];
  uint16_t Ptr;
  uint8_t LayerNum,CID1bNum=0;
  uint16_t Temp;
  uint16_t	NeedAnaLg;//��Ҫ���������ݳ���ָ������ߵĵ�һ���//
  uint16_t TempLg;
  TempLg=BufAd+DataLg;//�������ǰ���Խ�������������BUFF�е�λ��//
  Ptr=BufAd;								//Ptrָ��Ҫ����������//
  if((SMLComm.RecBuf[Ptr]&0xf0)!=0x70) //return -1;//�����һ�����ݲ���7X�ͷ��ش�//
  {
    if((SMLRecord[LayerNo].SMLOrder == Close_Req)||(SMLRecord[LayerNo].SMLOrder == Open_Req))
      return -1;
    for(i=0;i<DataLg;i++)
    {
      Ptr++;
      if(Ptr>(TempLg-4)) return -1;	
      if((SMLComm.RecBuf[Ptr] == 0x63)&&(SMLComm.RecBuf[Ptr+3] == 0x00)&&(SMLComm.RecBuf[Ptr+4] == 0x76))
      {	
        SMLComm.AnaOrderAd=Ptr-1;
        SMLComm.WrongTypeNum = LayerNo;
        return 1;
      }
    }
  }	
  LayerNum=SMLComm.RecBuf[Ptr]&0x0f;	//��ȡ����//
  for(i=0;i<LayerNum;i++)
  {
    Ptr++;
    if(Ptr>TempLg) return 0;
    Temp=SMLComm.RecBuf[Ptr];
    
    if(SMLRecord[LayerNo].SMLOrder == Open_Req)
    {
      
      switch(i)
      {
      case 1:
      case 2:
        if(SMLComm.RecBuf[Ptr] == 0x01)
          return -1;
        break;	
      case 3:	
        if(SMLComm.RecBuf[Ptr] == 0x01)
          SMLComm.OpenFlag |= F_ServerID_No;
        else{	
          E2P_RData( Buff,Server_ID, 10 ); 
          if(( Data_Comp( &SMLComm.RecBuf[Ptr+1],Buff, 10) != 0 ) && ((Flag.ClrFlag & F_SSET_EN) == 0))
            return -1;
          
        }
        break;
      case 4:	
        if(SMLComm.RecBuf[Ptr] == 0x01)
          SMLComm.OpenFlag |= F_Username_No;
        else 
          SMLComm.Flag |= F_Attention_Open;	
        break;
      case 5:	
        if(SMLComm.RecBuf[Ptr] == 0x01)
        {	
          SMLComm.OpenFlag |= F_Password_No;
        }
        else 
          SMLComm.Flag |= F_Attention_Open;	
        break;
      default:break;		
      }		
    }	
    if((SMLRecord[LayerNo].SMLOrder != Open_Req) &&(SMLRecord[LayerNo].SMLOrder != Close_Req))
    {
      
      switch(i)
      {
      case 0:
        if(SMLComm.OpenFlag & F_ServerID_No)
        {
          if(SMLComm.RecBuf[Ptr] != 0x01)
          {	
            SMLComm.Flag |= F_SendOpenClose;
            SMLComm.OpenFlag &=~ F_ServerID_No;
          }
        }else if(SMLComm.RecBuf[Ptr] == 0x01)
        {
          SMLComm.Flag |= F_Attention_ERR17;
          SMLComm.OpenFlag &=~ F_ServerID_No;
          
        }else{
          E2P_RData( Buff,Server_ID, 10 ); 
          if(( Data_Comp( &SMLComm.RecBuf[Ptr+1],Buff, 10) != 0 )&&((Flag.ClrFlag & F_SSET_EN) == 0))
            SMLComm.Flag |= F_SendOpenClose;
        }	
        break;
      case 1:	
        if((SMLComm.OpenFlag & F_Username_No) &&(SMLComm.RecBuf[Ptr] != 0x01))
        {
          SMLComm.Flag |= F_Attention_Fall;
          SMLComm.OpenFlag &=~ F_Username_No;
        }		
        break;
      case 2:	
        if((SMLComm.OpenFlag & F_Password_No) &&(SMLComm.RecBuf[Ptr] != 0x01))
        {
          SMLComm.Flag |= F_Attention_Fall;
          SMLComm.OpenFlag &=~ F_Password_No;
        }
        break;
      default:break;		
      }		
    }	
    if((SMLRecord[LayerNo].SMLOrder == Open_Req) && (i == 1) && (SMLComm.RecBuf[Ptr] > 0x05))	//in the open for Client ID
    {
      if((Temp&0x80)!=0)
      {
        Ptr++;
        if(Ptr>TempLg) return 0;
        NeedAnaLg=(Temp&0x0f)*16+SMLComm.RecBuf[Ptr];
        Temp=Ptr+NeedAnaLg+2;//�������һ���������ڽ��ջ������е�λ��//
        if(Temp>TempLg) return 0;
        for(j=0;j<NeedAnaLg+4;j++ )
        {
          if(SMLComm.RecBuf[Ptr+1+j] == 0x1b)
            CID1bNum++;
          else
            CID1bNum=0;
          if(CID1bNum == 8)
          {	
            SMLComm.OpenClientID1BPrt = Ptr+j-3;
            SMLComm.Flag |= F_ClientAdd4 + F_Client1BCRC;
            //						RAM_Write( (uint8_t*)&SMLComm.RecBuf[Ptr-2+j], (uint8_t*)&SMLComm.RecBuf[Ptr+2+j], NeedAnaLg+4-j );
            break;
          }
          if((CID1bNum < 8)&&(CID1bNum > 3)&&((NeedAnaLg+4) == (j + 1)))
            return -1;	
        }
        if(SMLComm.OpenClientID1BPrt != 0)
          Ptr=Ptr+NeedAnaLg+2;//ָ��ָ����һ������һ�ֽ�//
        else
          Ptr=Ptr+NeedAnaLg-2;//ָ��ָ����һ������һ�ֽ�//	
      }		
      else
      {
        NeedAnaLg=Temp&0x0f;
        Temp=Ptr+NeedAnaLg+3;//�������һ���������ڽ��ջ������е�λ��//
        if(Temp>TempLg) return 0;
        for(j=0;j<NeedAnaLg+4;j++ )
        {
          if(SMLComm.RecBuf[Ptr+1+j] == 0x1b)
            CID1bNum++;
          else
            CID1bNum=0;
          if(CID1bNum == 8)
          {	
            SMLComm.OpenClientID1BPrt = Ptr+j-2;
            SMLComm.Flag |= F_ClientAdd4 + F_Client1BCRC;
            //						RAM_Write( (uint8_t*)&SMLComm.RecBuf[Ptr-2+j], (uint8_t*)&SMLComm.RecBuf[Ptr+2+j], NeedAnaLg+4-j );
            break;
          }
          if((CID1bNum < 8)&&(CID1bNum > 3)&&((NeedAnaLg+4) == (j + 1)))
            return -1;	
        }	
        if(SMLComm.OpenClientID1BPrt != 0)
          Ptr=Ptr+NeedAnaLg+3;//ָ��ָ����һ������һ�ֽ�//
        else
          Ptr=Ptr+NeedAnaLg-1;//ָ��ָ����һ������һ�ֽ�//
      }	
      
    }else{	
      if(i == 0)
        //SMLComm.OpenClientID1BPrt = 0;
        SMLComm.Flag &=~  F_Client1BCRC;
      if((Temp&0xf0)==0x70)
      {
        LayerNum=LayerNum+(Temp&0x0f);//�����������Ƕ��ʱ������Ҫ����Ƕ�׵Ĳ���//
        
      }	
      else if((Temp&0x80)!=0)
      {
        Ptr++;
        if(Ptr>TempLg) return 0;
        NeedAnaLg=(Temp&0x0f)*16+(SMLComm.RecBuf[Ptr]&0xf);
				//zzl 20170629 add 
				if(SMLComm.RecBuf[Ptr]&0x80)
				{
					Ptr++;
					NeedAnaLg=NeedAnaLg*16+(SMLComm.RecBuf[Ptr]&0xf);
					NeedAnaLg -= 1;
				}
				//zzl end
        Temp=Ptr+NeedAnaLg-2;//�������һ���������ڽ��ջ������е�λ��//
        if(Temp>TempLg) return 0;
        Ptr=Ptr+NeedAnaLg-2;//ָ��ָ����һ������һ�ֽ�//
      }		
      else
      {
        NeedAnaLg=Temp&0x0f;
        Temp=Ptr+NeedAnaLg-1;//�������һ���������ڽ��ջ������е�λ��//
        if(Temp>TempLg) return 0;
        Ptr=Ptr+NeedAnaLg-1;//ָ��ָ����һ������һ�ֽ�//
      }	
    }					
  }	
  if(i==LayerNum)
  {
    SMLComm.AnaOrderAd=Ptr;//���������������ָ��λ��//
    return 1;
  }
  return 0;
}	

//����һ��SML,MESSAGE�ṹ���:���ָ��,���ݳ���,���(��ǰ������SML MESSAGE)//
//����:���Ȳ�ȫ����0,������-1,��ȷ����1//
signed AnalyseSMLMes(uint16_t BufAd,uint16_t DataLg,uint8_t LayerNo)
{
  uint8_t i;
  uint16_t Ptr;
  uint8_t LayerNum;
  uint16_t Temp;
  uint16_t	NeedAnaLg;//��Ҫ���������ݳ���ָ������ߵĵ�һ���//
  uint16_t TempLg;//�������㵱ǰ��Ҫ���������ݵ�λ��//
  uint16_t TempLgSub;//����������ݳ���,�ڵ��������ӳ���ʱ������������//
  uint16_t BufAdSub;//�ڵ����ӳ���ʱ������������ݵ�BUFF�е�λ��//
  uint16_t	Crc16,CRC16P;
  signed  Temp1;
  
  Ptr=BufAd;
  TempLg=BufAd+DataLg;//�������ǰ���Խ�������������BUFF�е�λ��//
  if(SMLComm.RecBuf[Ptr]!=0x76) return -1;  //�ṹ�������б����6��
  SMLRecord[LayerNo].StartAdd=Ptr;//������һ��SML MESSAGE����ʼ��ַ//
  LayerNum=6;
  for(i=0;i<LayerNum;i++)
  {
    if(i==3)//����SML MESSAGE BODY//
    {
      SMLRecord[LayerNo].OrderAdd=Ptr;//����������һ���ǰһ������һ�ֽڵ�λ��,��д��������ʱ��//
      Ptr++;
      if(Ptr>TempLg) return 0;
      //if((SMLComm.RecBuf[Ptr]&0xf0)!=0x70) return -1;
      if((SMLComm.RecBuf[Ptr])!=0x72) //return -1;
      {	
        if(SMLRecord[LayerNo].SMLOrder == Open_Req)
          return -1;
        SMLComm.WrongTypeNum = LayerNo;
      }		
      Ptr++;
      if(Ptr>TempLg) return 0;
      if((SMLComm.RecBuf[Ptr]!=0x63)&&(SMLComm.RecBuf[Ptr]!=0x65)) return -1;
      if(SMLComm.RecBuf[Ptr]==0x63)//������Ϊ2�ֽ�ʱ//
      {	
        Ptr++;
        if(Ptr>TempLg) return 0;
        Ptr++;
        if(Ptr>TempLg) return 0;//ָ��������ֽ�//
        SMLRecord[LayerNo].SMLOrder=SMLComm.RecBuf[Ptr]+(SMLComm.RecBuf[Ptr-1])*256;//��������//
        SMLRecord[LayerNo].OrderEndAdd=SMLRecord[LayerNo].OrderAdd+4;//��¼������������һ�ֽ�//
        //SMLComm.RecBuf[Ptr] = 0x01;
      }
      else if(SMLComm.RecBuf[Ptr]==0x65)//������Ϊ4�ֽ�ʱ//
      {
        Ptr++;
        if(Ptr>TempLg) return 0;
        Ptr++;
        if(Ptr>TempLg) return 0;//ָ��������ֽ�//
        Ptr++;
        if(Ptr>TempLg) return 0;
        Ptr++;
        if(Ptr>TempLg) return 0;//ָ��������ֽ�//	
        SMLRecord[LayerNo].SMLOrder=SMLComm.RecBuf[Ptr]+(SMLComm.RecBuf[Ptr-1])*256;//��������//
        SMLRecord[LayerNo].OrderEndAdd=SMLRecord[LayerNo].OrderAdd+6;//��¼������������һ�ֽ�//
        
        //SMLRecord[LayerNo].OrderEndAdd=SMLRecord[LayerNo].OrderAdd+4;//��¼������������һ�ֽ�//
        //SMLComm.RecBuf[Ptr-4] = 0x63;
        //SMLComm.RecBuf[Ptr-3] = SMLComm.RecBuf[Ptr-1];
        //SMLComm.RecBuf[Ptr-1] = 0x01;
      }
      if(LayerNo == 0)
      {
        if(SMLRecord[LayerNo].SMLOrder != Open_Req)
          SMLComm.Flag |= F_Attention_Only;
      }	
      
      BufAdSub=Ptr+1;//������ý��������ӳ���ʱ�õ�������λ��//
      TempLgSub=TempLg-Ptr;//������ý��������ӳ���ʱ�õ������ݳ���//
      Temp1=AnalyseOrder(BufAdSub,TempLgSub,LayerNo);//����������//
      if(Temp1==-1)
      {
        //if(SMLRecord[LayerNo].SMLOrder == Open_Req)
        return -1;
        //SMLComm.WrongTypeNum = LayerNo;
      }
      else if(Temp1==0)
      {
        return 0;
      }		
      else	//����������ȷ//
      {
        Ptr=SMLComm.AnaOrderAd;//���淵�ص�BUFF��λ��//
      }	
    }
    else if(i==4)//�˶�CRC//
    {
      if((Ptr+3)>TempLg) return 0;
      Ptr++;
      if(SMLComm.RecBuf[Ptr]!=0x63)	return -1;
      Crc16=SMLComm.RecBuf[Ptr+2]*256+SMLComm.RecBuf[Ptr+1];
      if((SMLRecord[LayerNo].SMLOrder == Open_Req) && (SMLComm.Flag & F_Client1BCRC))
      {
        CRC16P = DoCrc16(0xffff,&(SMLComm.RecBuf[SMLRecord[LayerNo].StartAdd]),SMLComm.OpenClientID1BPrt-SMLRecord[LayerNo].StartAdd);	
        CRC16P = DoCrc16(Comm.CRCRegInit,&(SMLComm.RecBuf[SMLComm.OpenClientID1BPrt + 4]),Ptr-SMLComm.OpenClientID1BPrt-4);
      }else
        CRC16P = DoCrc16(0xffff,&(SMLComm.RecBuf[SMLRecord[LayerNo].StartAdd]),Ptr-SMLRecord[LayerNo].StartAdd);
      if(Crc16!= CRC16P)
      {
        if(SMLRecord[LayerNo].SMLOrder == Close_Req)
          SMLComm.Flag |= F_SendOpenClose;
        else if(SMLRecord[LayerNo].SMLOrder != Open_Req)
          SMLComm.Flag |= F_MCRC_Err;
        else		
          return -1;
      }
      Ptr+=2;
      
    }		
    else if(i==5)//�˶�SML�Ľ���//
    {
      Ptr++;
      if(Ptr>TempLg) return 0;
      if(SMLComm.RecBuf[Ptr]!=0x00)	return -1;
      SMLRecord[LayerNo].EndAdd=Ptr;
      //�ڴ˼��������Ļظ�//
      //needaddprogram//
      return 1; 
    }
    else
    {
      Ptr++;
      if(Ptr>TempLg) return 0;
      if(i==0x02)
      {
        if((SMLComm.RecBuf[Ptr])!=0x62)
        {	
          if(SMLRecord[LayerNo].SMLOrder == Open_Req)
            return -1;
          SMLComm.WrongTypeNum = LayerNo;	
        }
        SMLRecord[LayerNo].AbortOnError = SMLComm.RecBuf[Ptr+1];
        Temp++;
      }		
      if(i==0x01)
      {
        if((SMLComm.RecBuf[Ptr])!=0x62)
        {	
          if(SMLRecord[LayerNo].SMLOrder == Open_Req)
            return -1;
          SMLComm.WrongTypeNum = LayerNo;	
        }
        SMLRecord[LayerNo].GroupNo = SMLComm.RecBuf[Ptr+1];
        Temp++;
      }		
      Temp=SMLComm.RecBuf[Ptr];
      if((Temp&0x80)!=0)  //���������Լ�����
      {
        Ptr++;
        if(Ptr>TempLg) return 0;
        NeedAnaLg=(Temp&0x0f)*16+(SMLComm.RecBuf[Ptr]&0xf);
				//zzl 20170629 add 
				if(SMLComm.RecBuf[Ptr]&0x80)
				{
					Ptr++;
					NeedAnaLg=NeedAnaLg*16+(SMLComm.RecBuf[Ptr]&0xf);
					NeedAnaLg -= 1;
				}
				//add end
        Temp=Ptr+NeedAnaLg-2;//�������һ���������ڽ��ջ������е�λ��//
        if(Temp>TempLg) return 0;
        Ptr=Ptr+NeedAnaLg-2;//ָ��ָ����һ������һ�ֽ�//
      }		
      else
      {
        NeedAnaLg=Temp&0x0f;
        Temp=Ptr+NeedAnaLg-1;//�������һ���������ڽ��ջ������е�λ��//
        if(Temp>TempLg) return 0;
        Ptr=Ptr+NeedAnaLg-1;//ָ��ָ����һ������һ�ֽ�//
      }	
    } 
  }	
  if(i==LayerNum)
  {
    return 1;//������ɷ���1;//
  }
  return 0;
}	

//CRC16�������ֽڵĽ������ͨ�ŵ�˳��//
void DoCrc161(uint8_t *Dest,uint16_t RegInit, uint8_t *message, uint16_t len) 
{
  uint16_t CrcReg;
  uint8_t *PTemp;
  
  CrcReg=DoCrc16(RegInit,message,len); 
  PTemp=(uint8_t *)&CrcReg;
  *Dest=*PTemp;
  *(Dest+1)=*(PTemp+1);
}

//ֻ�ǽ������ݣ�����д��������//
void AnalyseSMLData(void)
{
  uint8_t i;
  uint16_t	Ptr;
  uint16_t	NeedAnaLg;
  uint16_t Crc16;
  uint8_t	Num0;
  signed	Temp;
  
  if(SMLComm.RecLg<9) return;
  Temp=0;
  SMLComm.RecLgA=SMLComm.RecLg;//������յ�����//
  if(SMLComm.LayerNumR==0x00)//������һ��SML MESSAGE//
  {
    Ptr=8;
    NeedAnaLg=SMLComm.RecLgA-8;//��Ҫ���������ݳ���//		
    Temp=AnalyseSMLMes(Ptr,NeedAnaLg,SMLComm.LayerNumR);//����һ��SML MESSAGE//
    if(Temp==-1)
    {
      SMLCommInit();//����//
      return;
    }			
    else if(Temp==0)	return;
    else
    {
      SMLComm.LayerNumR++;//������һ��SML MESSAGE��ȷ//
      //WriteSendBufStr();	//��д���ͻ�������ͷ//
      //GetSendData();			//�˴��������һ��SML MESSAGE��д���ͻ�����//
    }		
  }	
  
  while(SMLComm.RecLgA>SMLRecord[SMLComm.LayerNumR-1].EndAdd)
  {	
    Ptr=SMLRecord[SMLComm.LayerNumR-1].EndAdd+1;//������һ��������ɵ�SML��¼ָ����Ҫ����������//			
    NeedAnaLg=SMLComm.RecLgA-Ptr;//��Ҫ���������ݳ���//
    if((SMLComm.RecBuf[Ptr]==0x00)||(SMLComm.RecBuf[Ptr]==0x1b)||((Comm.BTime3 == 0)&&((Ptr+8)>SMLComm.RecLgA)))//������SML MESSAGE���������ַ�//
    {
      Num0=Ptr%4;//����SML�������ļӵ�0�ĸ���;//
      if(Num0!=0)
      {
        Num0=4-Num0;
      }		 
      if(((Ptr+Num0+8)>SMLComm.RecLgA)&&(Comm.BTime3 != 0)) return;//�����յ�����û���յ�����ʱ�˳�//
      if(SMLComm.RecBuf[Ptr+Num0+4]!=0x1a)		
      {
        SMLComm.Flag |= F_SendOpenClose;
        //SMLCommInit();
        //return;
      }
      for(i=0;i<4;i++)
      {
        if(SMLComm.RecBuf[Ptr+Num0]!=0x1b)
        {
          SMLComm.Flag |= F_SendOpenClose;
          //SMLCommInit();
          //return;
        }
      }	
      Crc16=SMLComm.RecBuf[Ptr+Num0+6]+SMLComm.RecBuf[Ptr+Num0+7]*256;
      if(Crc16!=DoCrc16(0xffff,&(SMLComm.RecBuf[0]),SMLComm.RecLgA-2))
      {
        SMLComm.Flag |= F_SendOpenClose;
        //SMLCommInit();
        //return;
      }			
      SMLRecord[SMLComm.LayerNumR-1].EndAdd = SMLComm.RecLgA;			
      //WriteSendBufEnd(Num0);	//��д���ͻ�������ͷ///�˴����뷢�ͻ������Ľ����ַ�����д�뷢������//
      //Comm.TX_Delay2 = 30;
      //SendStartup();                                                    
      SMLComm.SLayerNumR = 0;
      SMLComm.Flag |= F_AnalyseSML_OK;
      return;
    }		
    else
    {
      Temp=AnalyseSMLMes(Ptr,NeedAnaLg,SMLComm.LayerNumR);
      if(Temp==-1)
      {
        //SMLComm.Flag |= F_MCRC_Err;
        SMLCommInit();//����//
        return;
      }			
      //else 
      if(Temp==0)	return;
      else
      {
        SMLComm.LayerNumR++;//������һ��SML MESSAGE��ȷ//
        //GetSendData();//�˴��������һ��SML MESSAGE��д���ͻ�����//
        //if((SMLComm.Flag & F_SendEvent) == F_SendEvent)
        //{	
        //  SMLComm.SendEventDataNum += SMLComm.SendPtr;
        //  Comm.TX_Delay2 = 30;
        //  return;
        //}
      }		
    }
  }
}	

//�������ϴν����뱾�ν����м�û�����ݽ���ʱ�˳�//
//���ܵĽ�������С�ڽ��յ���һ��SML MESSAGE��76ʱ�˳�//
void AnalyseSML(uint8_t *sendbuf)
{
  uint8_t	Num0;
  SMLComm.SendBuf=sendbuf;
	if(sendbuf==0)
		return;
  if((SMLComm.Flag & F_AnalyseSML_OK) == 0)
  {	
    AnalyseSMLData();
    if((SMLComm.Flag & F_AnalyseSML_OK) == 0)
      return;
  }
  if((SMLComm.Flag & F_SendEvent) == F_SendEvent)	//�¼���¼
  {
    SMLComm.SendPtr = 0;
    SMLComm.SendBuf[0] = 0x00;
    GetProfLRes();
    if((SMLComm.Flag & F_SendEvent) == F_SendEvent)
    {	
      SMLComm.SendEventDataNum += SMLComm.SendPtr;
      Comm.TX_Delay2 = 2;
      return;
    }
  }
  if(SMLComm.SLayerNumR==0x00)//������һ��SML MESSAGE//
  {
    SMLComm.SLayerNumR++;//������һ��SML MESSAGE��ȷ//
    WriteSendBufStr();	//��д���ͻ�������ͷ//
    GetSendData();			//�˴��������һ��SML MESSAGE��д���ͻ�����//	
  }	
  while(SMLComm.LayerNumR > SMLComm.SLayerNumR)
  {
    SMLComm.SLayerNumR++;//������һ��SML MESSAGE��ȷ//
    GetSendData();//�˴��������һ��SML MESSAGE��д���ͻ�����//
    if((SMLComm.Flag & F_SendEvent) == F_SendEvent)
    {	
      SMLComm.SendEventDataNum += SMLComm.SendPtr;
      Comm.TX_Delay2 = 30;
      return;
    }		 
  }
  
  if(SMLComm.LayerNumR <= SMLComm.SLayerNumR)//������SML MESSAGE���������ַ�//
  {		
    WriteSendBufEnd(Num0);	//��д���ͻ�������ͷ///�˴����뷢�ͻ������Ľ����ַ�����д�뷢������//
    SMLComm.Flag &=~ F_AnalyseSML_OK;
    Comm.TX_Delay2 = 30;                                                 
    return;                                      
  }
}	
//SMLͨ�ŵĳ�ʼ��//
void	SMLCommInit(void)
{
	int i;
  SMLComm.LayerNumR=0;//��ʼ�����յ����ݳ���,����,�����Ĳ�����//
  SMLComm.RecLg=0;
  SMLComm.RecLgA=0;
  SMLComm.LayerNumA=0;
  SMLComm.OpenClientID1BPrt = 0;
  SMLComm.Flag &=~ (F_SOrR + F_SendEvent + F_SendOpenClose + F_MCRC_Err + F_AnalyseSML_OK +  F_ClientAdd4 + F_Client1BCRC);
  SMLComm.Flag &=~ (F_Attention_Fall+ F_Attention_Open+F_Attention_List + F_Attention_Only + F_Attention_NotDoneGroup+F_Attention_NotDoneALL);
  SMLComm.OpenFlag = 0;
  SMLComm.WrongTypeNum = 0xFF;
  for(i=0;i<16;++i)
	{
		OrderRecord[i].OLStartAdd=0;
		OrderRecord[i].OLLength=0;
	}
  
  SMLRecord[0].LayerNum=0;//���һ��������¼//
  SMLRecord[0].StartAdd=0;
  SMLRecord[0].EndAdd=0;
  SMLRecord[0].SMLOrder=0;
  SMLRecord[0].Flag=0;
  SMLComm.EndNum=0;
}	
//���ͻ������е�ͷ����д//
void	WriteSendBufStr(void)
{
  uint16_t i;
  for(i=0;i<4;i++)
  {
    SMLComm.SendBuf[i]=0x1b;
  }	
  for(i=0;i<4;i++)
  {
    SMLComm.SendBuf[i+4]=0x01;
  }	
  SMLComm.SendPtr=0x07;//׼����8������//
}	

void	WriteSendBufEnd(uint8_t Num0)
{
  uint8_t i,j;
  if((SMLComm.Flag & F_CRCEvent) == F_CRCEvent)
    i = (SMLComm.SendEventDataNum + SMLComm.SendPtr + 1) % 4;
  else
    i=(SMLComm.SendPtr+1)%4;
  if(i!=0)
  {i=4-i;}
  SMLComm.SendPtr++;
  for(j=0;j<i;j++)
  {
    SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
    SMLComm.SendPtr++;
  }	
  
  for(j=0;j<4;j++)
  {
    SMLComm.SendBuf[SMLComm.SendPtr]=0x1B;
    SMLComm.SendPtr++;
  }	
  SMLComm.SendBuf[SMLComm.SendPtr]=0x1A;
  SMLComm.SendPtr++;	
  SMLComm.SendBuf[SMLComm.SendPtr]=i;
  
  SMLComm.SendPtr++;
  if((SMLComm.Flag & F_CRCEvent) == F_CRCEvent)
    DoCrc161(&(SMLComm.SendBuf[SMLComm.SendPtr]),Comm.CRCEventInit,&(SMLComm.SendBuf[0]),SMLComm.SendPtr);
  else	
    DoCrc161(&(SMLComm.SendBuf[SMLComm.SendPtr]),0xffff,&(SMLComm.SendBuf[0]),SMLComm.SendPtr);
  SMLComm.SendPtr+=2;
  SMLComm.Flag &=~ F_CRCEvent;	
}	

//��������׼������//
void GetSendData(void)
{
  uint16_t SMLOrder;
  uint16_t LayerNum;
  LayerNum=SMLComm.SLayerNumR-1;
  SMLOrder=SMLRecord[LayerNum].SMLOrder;
  switch (SMLOrder)
  {
  case Open_Req:
    OpenRes();	
    break;
  case Close_Req:	
    CloseRes();
    break;
  case GetProfP_Req:	
    if((SMLComm.Flag & F_SendOpenClose) == 0) GetProfPRes();
    break;
  case GetProfL_Req:	
    if((SMLComm.Flag & F_SendOpenClose) == 0)GetProfLRes();
    break;
  case GetPropP_Req:	
    if((SMLComm.Flag & F_SendOpenClose) == 0)GetPropPRes();
    break;
  case SetPropP_Req:	
    if((SMLComm.Flag & F_SendOpenClose) == 0)SetPropPRes();
    break;
  case GetL_Req:	
    if((SMLComm.Flag & F_SendOpenClose) == 0)GetLRes();
    break;  
  default: 
    break;
  }
}	
//SMLComm.SendLgһ��ָ����õ����һ���ֽ�//
void	OpenRes(void)
{
  uint16_t i;
  uint16_t	StartAdd;
  
  uint8_t	LayerNum;
  //	uint8_t	OrderLayerNum;//�����еĳ���//
  uint16_t	OrderEndAdd;
  
  uint16_t	SStartAdd;//���ͻ������е���ʼ��ַ��0X76//
  uint16_t	CID1BAdd;//���ͻ������е���ʼ��ַ��0X76//
  uint16_t 	SendPtrBAK;
  
  LayerNum=SMLComm.SLayerNumR-1;
  StartAdd=SMLRecord[LayerNum].StartAdd;
  
  OrderEndAdd=SMLRecord[LayerNum].OrderEndAdd;
  i=OrderEndAdd-StartAdd+1;//��76�����������λ��//
  SStartAdd=SMLComm.SendPtr+1;//����76��λ��//
  RAM_Write(&(SMLComm.SendBuf[SStartAdd]),&(SMLComm.RecBuf[StartAdd]),i);
  if(SMLComm.RecBuf[OrderEndAdd - 2] == 0x63)
  {	
    SMLComm.SendPtr+=i;//���ͻ�������ָ��	
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    //		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
  }else{
#if 0
    SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
#else
		SMLComm.SendPtr+=i;
		SMLComm.SendBuf[SMLComm.SendPtr-4]=0x65;
		SMLComm.SendBuf[SMLComm.SendPtr-3]=SMLComm.SendBuf[SMLComm.SendPtr-3];
		SMLComm.SendBuf[SMLComm.SendPtr-2]=SMLComm.SendBuf[SMLComm.SendPtr-2];
		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr-1];
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
#endif		
  }
  
  SendPtrBAK = SMLComm.SendPtr;
  
  AnaOrderData(OrderEndAdd,Order0100);//��ȡ��һ�������ÿһ��Ŀ�ʼ������ַ//
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x76;////
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//REQָ����RESָ��//
  if((SMLComm.OpenClientID1BPrt != 0)&& (SMLComm.OpenClientID1BPrt > OrderRecord0100[1].OLStartAdd))
  {
    CID1BAdd = SMLComm.SendPtr+1 + SMLComm.OpenClientID1BPrt - OrderRecord0100[1].OLStartAdd;
  }else 	CID1BAdd = 0;
  RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr+1]),&(SMLComm.RecBuf[OrderRecord0100[1].OLStartAdd]),OrderRecord0100[1].OLLength);
  SMLComm.SendPtr+=OrderRecord0100[1].OLLength;//��дClient_ID//
  RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr+1]),&(SMLComm.RecBuf[OrderRecord0100[2].OLStartAdd]),OrderRecord0100[2].OLLength);
  SMLComm.SendPtr+=OrderRecord0100[2].OLLength;//��дFile_ID//
  //	RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr+1]),&(SMLComm.RecBuf[OrderRecord0100[3].OLStartAdd]),OrderRecord0100[3].OLLength);
  //	
  //	SMLComm.SendBuf[SMLComm.SendPtr+2] = 'Z';
  //	SMLComm.SendBuf[SMLComm.SendPtr+3] = 'P';
  //	SMLComm.SendBuf[SMLComm.SendPtr+4] = 'A';
  //	RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr+1]),&(SMLComm.RecBuf[OrderRecord0100[3].OLStartAdd]),1);
  SMLComm.SendBuf[SMLComm.SendPtr+1] = 0x0B;
  E2P_RData( &(SMLComm.SendBuf[SMLComm.SendPtr+2]),Server_ID, 10 ); 
  
  //	SMLComm.SendPtr+=OrderRecord0100[3].OLLength;//��дServer_ID//
  SMLComm.SendPtr+=11;
  SMLComm.SendPtr++;
	//zzl 20170629 add 
#if 0
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//��дReftime//
  SMLComm.SendPtr++;
#else	
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x72;//��дReftime//
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x62;
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x01;
	SMLComm.SendBuf[SMLComm.SendPtr++]=0x65;
	SMLComm.SendBuf[SMLComm.SendPtr++]=Comm.SecPulseCnt>>24;
	SMLComm.SendBuf[SMLComm.SendPtr++]=Comm.SecPulseCnt>>16;
	SMLComm.SendBuf[SMLComm.SendPtr++]=Comm.SecPulseCnt>>8;
	SMLComm.SendBuf[SMLComm.SendPtr++]=Comm.SecPulseCnt;
#endif	
  //zzl add end
	
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//��дsml_Version//
  
  if(SMLComm.Flag & F_Attention_Open)
  {
    SMLComm.SendPtr = SendPtrBAK;
    ReturnSetOK(ReturnERR05);
  }
  
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x63;//��дCRC//
  SMLComm.SendPtr++;
  if((CID1BAdd == 0)||(SMLComm.Flag & F_Attention_Open))
    DoCrc161(&(SMLComm.SendBuf[SMLComm.SendPtr]),0xffff,&(SMLComm.SendBuf[SStartAdd]),SMLComm.SendPtr-SStartAdd-1);
  else{
    DoCrc161(&(SMLComm.SendBuf[SMLComm.SendPtr]),0xffff,&(SMLComm.SendBuf[SStartAdd]),CID1BAdd-SStartAdd);
    DoCrc161(&(SMLComm.SendBuf[SMLComm.SendPtr]),Comm.CRCRegInit,&(SMLComm.SendBuf[CID1BAdd+4]),SMLComm.SendPtr-CID1BAdd-5);
  }	
  SMLComm.SendPtr+=2;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;//MESSAGE������־//
}		
void	CloseRes(void)
{
  uint16_t i;
  uint16_t	StartAdd;
  
  uint8_t	LayerNum;
  
  uint16_t	OrderEndAdd;
  
  uint16_t	SStartAdd;//���ͻ������е���ʼ��ַ��0X76//
  uint8_t	PtrNum;
  
  LayerNum=SMLComm.SLayerNumR-1;
  StartAdd=SMLRecord[LayerNum].StartAdd;
  
  OrderEndAdd=SMLRecord[LayerNum].OrderEndAdd;
  i=OrderEndAdd-StartAdd+1;//��76�����������λ��//
  SStartAdd=SMLComm.SendPtr+1;//����76��λ��//
  RAM_Write(&(SMLComm.SendBuf[SStartAdd]),&(SMLComm.RecBuf[StartAdd]),i);
  PtrNum = (SMLComm.SendBuf[SStartAdd+1] & 0x0F) + 1;
  if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
  {
    SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
    SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
  }
  PtrNum += SMLComm.SendBuf[SStartAdd+PtrNum] & 0x0F ;
  if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
  {
    SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
    SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
  }
  
  if((SMLComm.Flag & F_SendOpenClose) == F_SendOpenClose)
    SMLComm.SendBuf[SStartAdd + 2]  = 0x02;
  //	SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
  //	SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
  //	SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
  if(SMLComm.RecBuf[OrderEndAdd - 2] == 0x63)
  {	
    SMLComm.SendPtr+=i;//���ͻ�������ָ��	
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    //		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
  }else{
		#if 0
    SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
		#else
		SMLComm.SendPtr+=i;
		SMLComm.SendBuf[SMLComm.SendPtr-4]=0x65;
		SMLComm.SendBuf[SMLComm.SendPtr-3]=SMLComm.SendBuf[SMLComm.SendPtr-3];
		SMLComm.SendBuf[SMLComm.SendPtr-2]=SMLComm.SendBuf[SMLComm.SendPtr-2];
		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr-1];
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
		#endif
  }
  if(SMLComm.WrongTypeNum == LayerNum)
  {	
    ReturnSetOK(ReturnERR05);
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x63;//��дCRC//
    SMLComm.SendPtr++;
    DoCrc161(&(SMLComm.SendBuf[SMLComm.SendPtr]),0xffff,&(SMLComm.SendBuf[SStartAdd]),SMLComm.SendPtr-SStartAdd-1);
    SMLComm.SendPtr+=2;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x00;//MESSAGE������־//
    
    LayerNum=SMLComm.SLayerNumR-1;
    StartAdd=SMLRecord[LayerNum].StartAdd;
    
    OrderEndAdd=SMLRecord[LayerNum].OrderEndAdd;
    i=OrderEndAdd-StartAdd+1;//��76�����������λ��//
    SStartAdd=SMLComm.SendPtr+1;//����76��λ��//
    RAM_Write(&(SMLComm.SendBuf[SStartAdd]),&(SMLComm.RecBuf[StartAdd]),i);
    PtrNum = (SMLComm.SendBuf[SStartAdd+1] & 0x0F) + 1;
    if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
    {
      SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
      SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
    }
    PtrNum += SMLComm.SendBuf[SStartAdd+PtrNum] & 0x0F ;
    if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
    {
      SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
      SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
    }
    //	SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
    //	SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    //	SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    //	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
    if(SMLComm.RecBuf[OrderEndAdd - 2] == 0x63)
    {	
      SMLComm.SendPtr+=i;//���ͻ�������ָ��	
      SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
      //		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr];//REQָ����RESָ��//
      SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
    }else{
      SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
      SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
      SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
      SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
    }
    SMLComm.SendBuf[SMLComm.SendPtr-3]=0x72;//��д���ݰ�ͷ
    
  }
  if(SMLRecord[0].SMLOrder != Open_Req)
  {
    ReturnSetOK(ReturnERR05);
    SMLComm.SendPtr++;
  }else{	
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x71;//��дsml_Version//
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//��дsml_Version//
    SMLComm.SendPtr++;
  }
  SMLComm.SendBuf[SMLComm.SendPtr]=0x63;//��дCRC//
  SMLComm.SendPtr++;
  //	if((SMLComm.Flag & F_CRCEvent) == F_CRCEvent)
  //	{	
  //		DoCrc161(&(SMLComm.SendBuf[SMLComm.SendPtr]),Comm.CRCRegInit,&(SMLComm.SendBuf[0]),SMLComm.SendPtr);
  //		
  //	}
  DoCrc161(&(SMLComm.SendBuf[SMLComm.SendPtr]),0xffff,&(SMLComm.SendBuf[SStartAdd]),SMLComm.SendPtr-SStartAdd-1);
  SMLComm.SendPtr+=2;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;//MESSAGE������־//
}	
void	GetProfPRes(void)
{
}	
void	GetProfLRes(void)
{
  uint16_t i;
  uint16_t	StartAdd;
  uint8_t	LayerNum;
  uint16_t	OrderEndAdd;
  uint16_t	SStartAdd;//���ͻ������е���ʼ��ַ��0X76//
  uint16_t 	SendPtrBAK;
  uint8_t	PtrNum;
  LayerNum=SMLComm.SLayerNumR-1;
  StartAdd=SMLRecord[LayerNum].StartAdd;
  OrderEndAdd=SMLRecord[LayerNum].OrderEndAdd;
  i=OrderEndAdd-StartAdd+1;//��76�����������λ��//
  SStartAdd=SMLComm.SendPtr+1;//����76��λ��//
  RAM_Write(&(SMLComm.SendBuf[SStartAdd]),&(SMLComm.RecBuf[StartAdd]),i);
  PtrNum = (SMLComm.SendBuf[SStartAdd+1] & 0x0F) + 1;
  if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
  {
    SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
    SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
  }
  PtrNum += SMLComm.SendBuf[SStartAdd+PtrNum] & 0x0F ;
  if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
  {
    SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
    SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
  }
  //	SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
  //	SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
  //	SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
  if(SMLComm.RecBuf[OrderEndAdd - 2] == 0x63)
  {	
    SMLComm.SendPtr+=i;//���ͻ�������ָ��	
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    //		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
  }else{
		#if 0
    SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
		#else
		SMLComm.SendPtr+=i;
		SMLComm.SendBuf[SMLComm.SendPtr-4]=0x65;
		SMLComm.SendBuf[SMLComm.SendPtr-3]=SMLComm.SendBuf[SMLComm.SendPtr-3];
		SMLComm.SendBuf[SMLComm.SendPtr-2]=SMLComm.SendBuf[SMLComm.SendPtr-2];
		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr-1];
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
		#endif
  }
  SendPtrBAK = SMLComm.SendPtr;
  AnaOrderData(OrderEndAdd,OrderNot0100);//��ȡ��һ�������ÿһ��Ŀ�ʼ������ַ//
  //	TempAdd=(OrderRecord[4].OLStartAdd)+1;//OBIS�����ڵĲ���//
  //	OBISNo=SearchOBIS(&(SMLComm.RecBuf[TempAdd]));//����OBIS�������������//
  DoProPListOBIS();//����OBIS����д����//
  
  if(SMLComm.Flag & F_Attention_List)
  {
    SMLComm.SendPtr = SendPtrBAK;
    ReturnSetOK(ReturnERR05);
  }
  if(SMLComm.Flag & F_Attention_ERR17)
  {
    SMLComm.SendPtr = SendPtrBAK;
    ReturnSetOK(ReturnERR17);
    SMLComm.Flag &=~ F_Attention_ERR17;
  }
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x63;//��дCRC//
  SMLComm.SendPtr++;
  
  DoCrc161(&(SMLComm.SendBuf[SMLComm.SendPtr]),0xffff,&(SMLComm.SendBuf[SStartAdd]),SMLComm.SendPtr-SStartAdd-1);
  SMLComm.SendPtr+=2;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;//MESSAGE������־//
  if((SMLComm.Flag & (F_CRCEvent + F_SendEvent)) == (F_CRCEvent + F_SendEvent))
  {	
    DoCrc161((uint8_t*)&Comm.CRCEventInit,Comm.CRCEventInit,&(SMLComm.SendBuf[0]),SMLComm.SendPtr);
    Comm.CRCEventInit = Comm.CRCRegInit;
  }
}	
void	GetPropPRes(void)
{
  uint16_t i;
  uint16_t	StartAdd;
  uint8_t	LayerNum;
  uint16_t	OrderEndAdd;
  uint16_t	SStartAdd;//���ͻ������е���ʼ��ַ��0X76//
  uint8_t	OBISNo,ReturnNo;
  uint16_t	TempAdd;
  uint16_t 	SendPtrBAK;
  uint8_t	PtrNum;
  
  LayerNum=SMLComm.SLayerNumR-1;
  StartAdd=SMLRecord[LayerNum].StartAdd;
  OrderEndAdd=SMLRecord[LayerNum].OrderEndAdd;
  i=OrderEndAdd-StartAdd+1;//��76�����������λ��//
  SStartAdd=SMLComm.SendPtr+1;//����76��λ��//
  RAM_Write(&(SMLComm.SendBuf[SStartAdd]),&(SMLComm.RecBuf[StartAdd]),i);
  PtrNum = (SMLComm.SendBuf[SStartAdd+1] & 0x0F) + 1;
  if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
  {
    SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
    SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
  }
  PtrNum += SMLComm.SendBuf[SStartAdd+PtrNum] & 0x0F ;
  if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
  {
    SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
    SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
  }
  //	SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
  //	SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
  //	SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
  if(SMLComm.RecBuf[OrderEndAdd - 2] == 0x63)
  {	
    SMLComm.SendPtr+=i;//���ͻ�������ָ��	
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    //		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
  }else{
		#if 0
    SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
		#else
		SMLComm.SendPtr+=i;
		SMLComm.SendBuf[SMLComm.SendPtr-4]=0x65;
		SMLComm.SendBuf[SMLComm.SendPtr-3]=SMLComm.SendBuf[SMLComm.SendPtr-3];
		SMLComm.SendBuf[SMLComm.SendPtr-2]=SMLComm.SendBuf[SMLComm.SendPtr-2];
		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr-1];
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
		#endif
  }
  
  SendPtrBAK = SMLComm.SendPtr;
  AnaOrderData(OrderEndAdd,OrderNot0100);//��ȡ��һ�������ÿһ��Ŀ�ʼ������ַ//
  TempAdd=(OrderRecord[4].OLStartAdd)+1;//OBIS�����ڵĲ���//
  OBISNo=SearchOBIS(&(SMLComm.RecBuf[TempAdd]));//����OBIS�������������//
  if(OBISNo == 0xFF)
    ReturnSetOK(ReturnERR05);
  else if(SMLComm.WrongTypeNum == LayerNum)
    ReturnSetOK(ReturnERR05);	
	//zzl 20170629 add 
	else if((SMLRecord[LayerNum].GroupNo==1) || (SMLRecord[LayerNum].AbortOnError==1))
	{
		ReturnSetOK(ReturnERR15);
	}
	//zzl add end
  else{	
    ReturnNo = DoProPOBIS(OBISNo);//����OBIS����д����//
    
    if(ReturnNo != ReturnOK)
    {
      SMLComm.SendPtr = SendPtrBAK;
      ReturnSetOK(ReturnNo);
    }
  }
  if((SMLComm.Flag & F_MCRC_Err)||(SMLRecord[0].SMLOrder != Open_Req))
  {
    SMLComm.SendPtr = SendPtrBAK;
    ReturnSetOK(ReturnERR05);
  }
  if(SMLComm.Flag & F_Attention_ERR17)
  {
    SMLComm.SendPtr = SendPtrBAK;
    ReturnSetOK(ReturnERR17);
    SMLComm.Flag &=~ F_Attention_ERR17;
  }
  if(SMLComm.Flag & F_Attention_Fall)
  {
    SMLComm.SendPtr = SendPtrBAK;
    ReturnSetOK(ReturnERR03);
    SMLComm.Flag &=~ F_Attention_Fall;
  }
  
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x63;//��дCRC//
  SMLComm.SendPtr++;
  DoCrc161(&(SMLComm.SendBuf[SMLComm.SendPtr]),0xffff,&(SMLComm.SendBuf[SStartAdd]),SMLComm.SendPtr-SStartAdd-1);
  SMLComm.SendPtr+=2;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;//MESSAGE������־// 
}	
void SetPropPRes(void)
{
  uint16_t i;
  uint16_t	StartAdd;
  uint8_t	LayerNum;
  uint16_t	OrderEndAdd;
  uint16_t	SStartAdd;//���ͻ������е���ʼ��ַ��0X76//
  uint8_t	OBISNo,ReturnNo;
  uint16_t	TempAdd;
  uint8_t	PtrNum;
  
  LayerNum=SMLComm.SLayerNumR-1;
  StartAdd=SMLRecord[LayerNum].StartAdd;
  OrderEndAdd=SMLRecord[LayerNum].OrderEndAdd;
  i=OrderEndAdd-StartAdd+1;//��76�����������λ��//
  SStartAdd=SMLComm.SendPtr+1;//����76��λ��//
  RAM_Write(&(SMLComm.SendBuf[SStartAdd]),&(SMLComm.RecBuf[StartAdd]),i);
  PtrNum = (SMLComm.SendBuf[SStartAdd+1] & 0x0F) + 1;
  if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
  {
    SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
    SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
  }
  PtrNum += SMLComm.SendBuf[SStartAdd+PtrNum] & 0x0F ;
  if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
  {
    SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
    SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
  }

  if(SMLComm.RecBuf[OrderEndAdd - 2] == 0x63)
  {	
    SMLComm.SendPtr+=i;//���ͻ�������ָ��	
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    //		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
  }else{
		#if 0
    SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
		#else
		SMLComm.SendPtr+=i;
		SMLComm.SendBuf[SMLComm.SendPtr-4]=0x65;
		SMLComm.SendBuf[SMLComm.SendPtr-3]=00;
		SMLComm.SendBuf[SMLComm.SendPtr-2]=00;
		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr-1];
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
		#endif
  }
  
  if((SMLComm.Flag & F_MCRC_Err)||(SMLRecord[0].SMLOrder != Open_Req))
  {
    ReturnSetOK(ReturnERR05);
  }else if(SMLComm.Flag & F_Attention_Fall)
  {
    ReturnSetOK(ReturnERR03);
    SMLComm.Flag &=~ F_Attention_Fall;
  }else if(SMLComm.WrongTypeNum == LayerNum)
    ReturnSetOK(ReturnERR05);	
  else if(SMLComm.Flag & F_Attention_ERR17)
  {
    ReturnSetOK(ReturnERR17);
    SMLComm.Flag &=~ F_Attention_ERR17;
  }else{
    AnaOrderData(OrderEndAdd,OrderNot0100);//��ȡ��һ�������ÿһ��Ŀ�ʼ������ַ//
    TempAdd=(OrderRecord[4].OLStartAdd)+1;
    OBISNo=SearchOBIS(&(SMLComm.RecBuf[TempAdd]));//����OBIS�������������//
    if(OBISNo == 0xFF)
      ReturnSetOK(ReturnERR05);	
    else	
      ReturnNo = DoProSOBIS(OBISNo);//����OBIS����д����//
    
    ReturnSetOK(ReturnNo);
  }
  
 /* if((OBISNo == 14) && ( SMLComm.RecBuf[OrderRecord[9].OLStartAdd + 1]  >= 0x03))//����00 00 60 0E 00 FF ���⴦��
  {
    SMLComm.SendBuf[SMLComm.SendPtr-5] = 0xFE;
    SMLComm.SendBuf[SMLComm.SendPtr-4] = 0x09;
  }	*/
  
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x63;//��дCRC//
  SMLComm.SendPtr++;
  DoCrc161(&(SMLComm.SendBuf[SMLComm.SendPtr]),0xffff,&(SMLComm.SendBuf[SStartAdd]),SMLComm.SendPtr-SStartAdd-1);
  SMLComm.SendPtr+=2;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;//MESSAGE������־//
}	
void GetLRes(void)
{
  uint16_t i;
  uint16_t	StartAdd;
  uint8_t	LayerNum;
  uint16_t	OrderEndAdd;
  uint16_t	SStartAdd;//���ͻ������е���ʼ��ַ��0X76//
  uint8_t	PtrNum;
  LayerNum=SMLComm.SLayerNumR-1;
  StartAdd=SMLRecord[LayerNum].StartAdd;
  OrderEndAdd=SMLRecord[LayerNum].OrderEndAdd;
  i=OrderEndAdd-StartAdd+1;//��76�����������λ��//
  SStartAdd=SMLComm.SendPtr+1;//����76��λ��//
  RAM_Write(&(SMLComm.SendBuf[SStartAdd]),&(SMLComm.RecBuf[StartAdd]),i);
  PtrNum = (SMLComm.SendBuf[SStartAdd+1] & 0x0F) + 1;
  if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
  {
    SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
    SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
  }
  PtrNum += SMLComm.SendBuf[SStartAdd+PtrNum] & 0x0F ;
  if((SMLComm.SendBuf[SStartAdd+PtrNum] & 0xF0) != 0x60)
  {
    SMLComm.SendBuf[SStartAdd+PtrNum] &=~0xF0;
    SMLComm.SendBuf[SStartAdd+PtrNum] |= 0x60;
  }
  //	SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
  //	SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
  //	SMLComm.SendBuf[SMLComm.SendPtr]=SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
  if(SMLComm.RecBuf[OrderEndAdd - 2] == 0x63)
  {	
    SMLComm.SendPtr+=i;//���ͻ�������ָ��	
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    //		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
  }else{
	#if 0
    SMLComm.SendPtr+=i-2;//���ͻ�������ָ��
    SMLComm.SendBuf[SMLComm.SendPtr-2]=0x63;//SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr+1];//REQָ����RESָ��//
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;//SMLComm.SendBuf[SMLComm.SendPtr+2];//REQָ����RESָ��//
	#else
		SMLComm.SendPtr+=i;
		SMLComm.SendBuf[SMLComm.SendPtr-4]=0x65;
		SMLComm.SendBuf[SMLComm.SendPtr-3]=SMLComm.SendBuf[SMLComm.SendPtr-3];
		SMLComm.SendBuf[SMLComm.SendPtr-2]=SMLComm.SendBuf[SMLComm.SendPtr-2];
		SMLComm.SendBuf[SMLComm.SendPtr-1]=SMLComm.SendBuf[SMLComm.SendPtr-1];
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
	#endif
  }
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x79;
  
  AnaOrderData(OrderEndAdd,OrderNot0100);//��ȡ��һ�������ÿһ��Ŀ�ʼ������ַ//
  SMLComm.SendPtr++;
  RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[0].OLStartAdd]),OrderRecord[0].OLLength);
  SMLComm.SendPtr+=OrderRecord[0].OLLength;//��дserver-id//
}	

//����һ�������������Ĳ�����//
//ÿһ������ݵ���ʼ��ַ�����ݳ�����OrderRecord[]��//
//��������Ƕ��ʱ,���������Ƕ�׵Ĳ���//
uint8_t 	AnaOrderData(uint16_t StartAdd,uint8_t OrerType)
{
  uint16_t	Ptr;
  uint16_t	LayerNum;
  uint8_t Temp,i;
  Ptr=StartAdd+1;
  LayerNum=SMLComm.RecBuf[Ptr]&0x0f;	//��ȡ����//
  for(i=0;i<LayerNum;i++)
  {
    Ptr++;
    Temp=SMLComm.RecBuf[Ptr];
    if((Temp&0xf0)==0x70)
    {
      LayerNum=LayerNum+(Temp&0x0f);//��������Ƕ��ʱ,��������Ƕ�׵Ĳ���//
      if(OrerType==Order0100)
      {	
        OrderRecord0100[i].OLStartAdd=Ptr;//���濪ʼ��ַ//
        OrderRecord[i].OLLength=0x01;
      }
      else
      {
        OrderRecord[i].OLStartAdd=Ptr;//���濪ʼ��ַ//
        OrderRecord[i].OLLength=0x01;
      }
    }		
    else if((Temp&0x80)!=0)
    {
      if(OrerType==Order0100)
      {	
        OrderRecord0100[i].OLStartAdd=Ptr;//���濪ʼ��ַ//
      }
      else
      {
        OrderRecord[i].OLStartAdd=Ptr;//���濪ʼ��ַ//
      }	
      Ptr++;
      Temp=(Temp&0x0f)*16;
      Temp=Temp+SMLComm.RecBuf[Ptr];//�������һ�����ݵĳ���//
      if(OrerType==Order0100)
      {	
        if((SMLComm.Flag & F_ClientAdd4) && (i == 1))
        {	
          Temp += 4 ;//���������ַ//
          SMLComm.Flag &=~ F_ClientAdd4;
        }
        OrderRecord0100[i].OLLength=Temp;//���������ַ//
      }	
      else
      {
        OrderRecord[i].OLLength=Temp;//���������ַ//
      }		
      Ptr=Ptr+Temp-2;//�������һ���������ڽ��ջ������е�λ��//
    }		
    else
    {
      if(OrerType==Order0100)
      {	
        OrderRecord0100[i].OLStartAdd=Ptr;//���濪ʼ��ַ
      }
      else
      {
        OrderRecord[i].OLStartAdd=Ptr;//���濪ʼ��ַ
      }		
      Temp=(Temp&0x0f);
      if(OrerType==Order0100)
      {	
        if((SMLComm.Flag & F_ClientAdd4) && (i == 1))
        {	
          Temp += 4 ;//���������ַ//
          SMLComm.Flag &=~ F_ClientAdd4;
        }
        OrderRecord0100[i].OLLength=Temp;//���������ַ//
      }
      else
      {
        OrderRecord[i].OLLength=Temp;//���������ַ//
      }		
      Ptr=Ptr+(Temp&0x0f)-1;//ָ��ָ����һ������һ�ֽ�//
    }						
  }
  return LayerNum;//���ز���//
}	 

//�Ѳ��ұ�ó�OBIS�����ͺ�//
uint8_t SearchOBIS(uint8_t *POBIS)
{
  uint8_t i,j;
  uint8_t *POBIS1;
  uint16_t m_Class;
  for(i=0;i<MaxOBISNum;i++)
  {
    POBIS1=(uint8_t *)&(SMLOBISTab[i].OBIS0);
    for(j=0;j<6;j++)
    {
      if(*(POBIS+j)!=*(POBIS1+j))
        break;
    }	
    if(j==0x06)
    {
			m_Class=POBIS[6];
			m_Class=(m_Class<<8)|POBIS[7];
			if(m_Class==SMLOBISTab[i].Class || SMLOBISTab[i].Class==0x100)
				return i;
    }
  }	
  return (0xFF);
}	

//��дGETlist�¼�����//
void DoProPListOBIS(void)
{
  uint16_t TempAdd,TempLength;
  uint8_t DataBuff[20];
  uint8_t* Point;
  
  Point = DataBuff;
  //	Len = SMLOBISTab[OBISNo].Len;
  //	OBISType = SMLOBISTab[OBISNo].OBISType;
  //	Adder = SMLOBISTab[OBISNo].Adder;
  //	State = SMLOBISTab[OBISNo].State;
  if((SMLComm.Flag & F_SendEvent) == 0)
  {
    Comm.CRCEventInit = 0xffff;
    SMLComm.SendEventNum = 0;
    SMLComm.SendEventDataNum = 0;
    SMLComm.Flag |= F_SendEvent + F_CRCEvent;
    E2P_RData(DataBuff,E2P_ConManipulation,0x4);
    RAM_WriteInter((uint8_t*)&SMLComm.SendEventNum,DataBuff,4);
    if(SMLComm.SendEventNum == 0xFFFFFFFF)
      SMLComm.SendEventNum = 0;
    if(SMLComm.SendEventNum == 0)
      SMLComm.Flag |= F_Attention_List;
  }
  if(SMLComm.SendEventNum <= 1)
  {	
    SMLComm.Flag &=~ F_SendEvent;
  }	
  SMLComm.SendEventNum--;
  ReadTamperRecord( Point ,SMLComm.SendEventNum);
  
  //	SMLComm.SendEventNum--;
  
  //	if(SMLComm.Flag & F_SendEvent)
  //	{	
  //		SMLComm.Flag &=~ F_SendEvent;
  ////		SMLComm.LayerNumR++;
  //	}else{
  //		Comm.CRCRegInit = 0xffff;
  //		SMLComm.Flag |= F_SendEvent + F_CRCEvent;
  //	}
  
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x79;
  SMLComm.SendPtr++;
  TempAdd=OrderRecord[0].OLStartAdd;
  TempLength=OrderRecord[0].OLLength;
  //	RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[TempAdd]),TempLength);//дSERVERID//
  //	SMLComm.SendBuf[SMLComm.SendPtr+1] = 'Z';
  //	SMLComm.SendBuf[SMLComm.SendPtr+2] = 'P';
  //	SMLComm.SendBuf[SMLComm.SendPtr+3] = 'A';
  RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[TempAdd]),1);
  E2P_RData( &(SMLComm.SendBuf[SMLComm.SendPtr+1]),Server_ID, 10 ); 
  SMLComm.SendPtr+=TempLength;
  
  SMLComm.SendBuf[SMLComm.SendPtr]=0x65;
  SMLComm.SendPtr++;
  RAM_WriteInter( (uint8_t *)&SMLComm.SendBuf[SMLComm.SendPtr],(uint8_t*)&Comm.SecPulseCnt, 4 );
  SMLComm.SendPtr += 4;
  
  SMLComm.SendBuf[SMLComm.SendPtr]=0x65;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  
  SMLComm.SendBuf[SMLComm.SendPtr]=0x71;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x07;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x81;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x81;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0xC7;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x89;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0xE1;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0xFF;
  SMLComm.SendPtr++;
  
  
  SMLComm.SendBuf[SMLComm.SendPtr]=0x65;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  
  SMLComm.SendBuf[SMLComm.SendPtr]=0x63;
  SMLComm.SendPtr++;
  RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),(uint8_t*)&Flag.StatusWord+1,1);
  SMLComm.SendPtr++;
  RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),(uint8_t*)&Flag.StatusWord,1);
  SMLComm.SendPtr++;
  
  SMLComm.SendBuf[SMLComm.SendPtr]=0x73;
  //81 81 C7 89 E2 FF	
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x75;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x07;
  
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x81;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x81;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0xC7;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x89;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0xE2;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0xFF;
  
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x62;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x1E;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x52;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0xFF;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x65;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr] = *Point;//0x01;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  
  ////01 00 60 05 00 FF	
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x75;
  SMLComm.SendPtr++;
  if((*(Point+7) &0x0F) != 0) 
  {	
    SMLComm.SendBuf[SMLComm.SendPtr]=0x07;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=*(Point+1);//0x01;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=*(Point+2);//0x00;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=*(Point+3);//0x60;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=*(Point+4);//0x05;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=*(Point+5);//0x00;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=*(Point+6);//0xFF;
    
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x62;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0xFF;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x52;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
    SMLComm.SendPtr++;
    if(((*(Point+7) &0x0F) != 0) && ((*(Point+7) &0x0F) < 5))
    {	
      SMLComm.SendBuf[SMLComm.SendPtr]= (*(Point+7) &0x0F) + 0x61;////0x63;
      SMLComm.SendPtr++;
      
      RAM_Write( (uint8_t*)&SMLComm.SendBuf[SMLComm.SendPtr], (Point+8), *(Point+7) & 0x0F );
      SMLComm.SendPtr += *(Point+7);
    }else{
      SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
      SMLComm.SendPtr++;
    }
  }else{
    
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
    SMLComm.SendPtr++;
  }
  
  
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  //	SMLComm.SendPtr++;
  
  
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  //////	01 00 00 09 0B 00
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x75;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x07;
  
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x09;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x0B;
  SMLComm.SendPtr++;
  if(*(Point+6) == 0xFF)
    SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  else
    SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x62;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x07;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x52;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x65;
  SMLComm.SendPtr++;
  
  RAM_Write( (uint8_t*)&SMLComm.SendBuf[SMLComm.SendPtr], (Point+12), 4 );
  SMLComm.SendPtr += 4;
  
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  //	SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  ///////	01 00 00 09 0B 00
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x75;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x07;
  //
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x09;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x0B;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  //	
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x62;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x1E;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x52;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0xFF;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x65;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  ////	SMLComm.SendPtr++;
  ////	SMLComm.SendBuf[SMLComm.SendPtr]=0x00;
  //	SMLComm.SendPtr++;
  //	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  
  
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  
  
}	
const uint8_t DeviceID[]=
{
  0x73,0x07,0x81,0x81,0xC7,0x82,0x01,0xFF,0x01,
  0x75,0x73,0x07,0x81,0x81,0xC7,0x82,0x02,0xFF,
  0x72,0x62,0x01,0x07,0x81,0x81,0xC7,0x82,0x52,0xFF,0x01,
  0x73,0x07,0x81,0x81,0xC7,0x82,0x03,0xFF,
  0x72,0x62,0x01,0x04,0x5A,0x50,0x41,0x01,
  0x73,0x07,0x01,0x00,0x00,0x00,0x09,0xFF,
  0x72,0x62,0x01,0x0B,0x01,0x02,0x03,0x04,0x05,0x01,0x02,0x03,0x04,0x05,0x01,
  0x73,0x07,0x81,0x81,0xC7,0x82,0x05,0xFF,
  0x72,0x62,0x01,	//public key
  0x01,	
  0x73,0x07,0x01,0x00,0x00,0x02,0x00,0xFF,
  0x72,0x62,0x01,0x05,0x00,0x00,0x00,0x00,0x01};
uint8_t DoDeviceIdentification(void)
{
  int i;
  
  for(i=0;i<79;i++)
  {
    SMLComm.SendBuf[SMLComm.SendPtr++]=DeviceID[i];
  }
  E2P_RData( &SMLComm.SendBuf[SMLComm.SendPtr-22],Server_ID, 10 ); 
  
  for(i=0;i<50;i++)
  {
    //SMLComm.SendBuf[SMLComm.SendPtr++]=Comm.BufS[234+i];
  }
  for(i=0;i<17;i++)
  {
    SMLComm.SendBuf[SMLComm.SendPtr++]=DeviceID[79+i];
  }
  return 0;
}	
//����OBIS���������дGET����//
uint8_t DoProPOBIS(uint8_t OBISNo)
{
  uint16_t TempAdd,TempLength;
  uint16_t 	SendPtrBAK;
  uint32_t	Adder;
  uint16_t	State;
  uint32_t* 	PowerData;
  uint64_t	ECData = 0;
  uint8_t	Len;
  uint8_t	OBISType;
	uint8_t ret;
	uint8_t attri_num;
	uint16_t short_Name;
	sml_function sml_callback;
	sml_beforefun smal_callbefore;
  if(OBISNo==16)
		return ReturnERR15;
  Len = SMLOBISTab[OBISNo].Len;
  OBISType = SMLOBISTab[OBISNo].OBISType;
  Adder = SMLOBISTab[OBISNo].Adder;
  State = SMLOBISTab[OBISNo].State;
  sml_callback = SMLOBISTab[OBISNo].CallBack;
	smal_callbefore = SMLOBISTab[OBISNo].CallBefore;
	if((XPERMIT&State)==XPERMIT)
		return(ReturnERR15);
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x73;
  SMLComm.SendPtr++;
  TempAdd=OrderRecord[0].OLStartAdd;
  TempLength=OrderRecord[0].OLLength;
  //	RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[TempAdd]),TempLength);//дSERVERID//
  //	SMLComm.SendBuf[SMLComm.SendPtr+1] = 'Z';
  //	SMLComm.SendBuf[SMLComm.SendPtr+2] = 'P';
  //	SMLComm.SendBuf[SMLComm.SendPtr+3] = 'A';
  RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[TempAdd]),1);
  E2P_RData( &(SMLComm.SendBuf[SMLComm.SendPtr+1]),Server_ID, 10 ); 
  
  SMLComm.SendPtr+=TempLength;
	
#if 0	
  SMLComm.SendBuf[SMLComm.SendPtr]=0x72;
#else
	TempAdd=OrderRecord[4].OLStartAdd-1;
	
	attri_num=SMLComm.RecBuf[TempAdd];
	//if(attri_num==0x73 || attri_num==0x76)
	if(attri_num==0x73 || attri_num==0x76 || attri_num==0x75)
		SMLComm.SendBuf[SMLComm.SendPtr]=SMLComm.RecBuf[TempAdd];
	else
		SMLComm.SendBuf[SMLComm.SendPtr]=0x72;
#endif	
  SMLComm.SendPtr++;
	
  TempAdd=OrderRecord[4].OLStartAdd;
  TempLength=OrderRecord[4].OLLength;
  RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[TempAdd]),TempLength);//дOBIS//
  SMLComm.SendPtr+=TempLength;
  SendPtrBAK = SMLComm.SendPtr;
	RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[5].OLStartAdd]),OrderRecord[5].OLLength);//дattri
  SMLComm.SendPtr+=OrderRecord[5].OLLength;
#if 0
#else
	if(attri_num==0x73)
	{
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[6].OLStartAdd]),OrderRecord[6].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[6].OLLength;
	}
	else if(attri_num==0x76)
	{
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[6].OLStartAdd]),OrderRecord[6].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[6].OLLength;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[7].OLStartAdd]),OrderRecord[7].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[7].OLLength;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[8].OLStartAdd]),OrderRecord[8].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[8].OLLength;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[9].OLStartAdd]),OrderRecord[9].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[9].OLLength;
	}		
	else if(attri_num==0x75)
	{
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[6].OLStartAdd]),OrderRecord[6].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[6].OLLength;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[7].OLStartAdd]),OrderRecord[7].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[7].OLLength;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[8].OLStartAdd]),OrderRecord[8].OLLength);//дattri
		SMLComm.SendPtr+=OrderRecord[8].OLLength;
	}
#endif	
  SMLComm.SendBuf[SMLComm.SendPtr]=0x73;
  SMLComm.SendPtr++;
  RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[TempAdd]),TempLength);//дOBIS//
  SMLComm.SendPtr+=TempLength;
	SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
	SMLComm.SendPtr++;
#if 0	
	SMLComm.SendBuf[SMLComm.SendPtr]=0x71;
#else
	//if(attri_num==0x73 || attri_num==0x76)
	if(attri_num==0x73 || attri_num==0x76 || attri_num==0x75)
		SMLComm.SendBuf[SMLComm.SendPtr]=attri_num-1;
	else
		SMLComm.SendBuf[SMLComm.SendPtr]=0x71;
#endif	
  SMLComm.SendPtr++;
	/*if(attri_num==0x73 || attri_num==0x76)
	{
		SMLComm.SendBuf[SMLComm.SendPtr]=attri_num;
	}
	else*/
		SMLComm.SendBuf[SMLComm.SendPtr]=0x73;
  SMLComm.SendPtr++;
	
	RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[5].OLStartAdd]),OrderRecord[5].OLLength);//дattri
  SMLComm.SendPtr+=OrderRecord[5].OLLength;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x72;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x62;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
	
	short_Name = SMLComm.RecBuf[OrderRecord[5].OLStartAdd+1];
	short_Name = (short_Name<<8) | SMLComm.RecBuf[OrderRecord[5].OLStartAdd+2];
	SMLRecord[1].record_num = 5;
	if(short_Name==1)
	{
		SMLComm.SendBuf[++SMLComm.SendPtr]=0x7;
		SMLComm.SendBuf[++SMLComm.SendPtr]=SMLOBISTab[OBISNo].OBIS0;
		SMLComm.SendBuf[++SMLComm.SendPtr]=SMLOBISTab[OBISNo].OBIS1;
		SMLComm.SendBuf[++SMLComm.SendPtr]=SMLOBISTab[OBISNo].OBIS2;
		SMLComm.SendBuf[++SMLComm.SendPtr]=SMLOBISTab[OBISNo].OBIS3;
		SMLComm.SendBuf[++SMLComm.SendPtr]=SMLOBISTab[OBISNo].OBIS4;
		SMLComm.SendBuf[++SMLComm.SendPtr]=SMLOBISTab[OBISNo].OBIS5;
		SMLComm.SendBuf[++SMLComm.SendPtr]=0x01;
		
		SMLComm.SendBuf[++SMLComm.SendPtr]=0x73;
		SMLComm.SendPtr++;
		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[OrderRecord[6].OLStartAdd]),OrderRecord[6].OLLength);//��attri
		SMLComm.SendPtr+=OrderRecord[6].OLLength;
		SMLComm.SendBuf[SMLComm.SendPtr]=0x72;
		SMLComm.SendPtr++;
		SMLComm.SendBuf[SMLComm.SendPtr]=0x62;
		SMLComm.SendPtr++;
		SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
		SMLRecord[1].record_num = 6;
	}
  
  if((OBISType == 0x56)||(OBISType == 0x55))
  {
    SMLComm.SendBuf[SMLComm.SendPtr]=0x02;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x75;
    SMLComm.SendPtr++;
    RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[TempAdd]),TempLength);//дOBIS//
    SMLComm.SendPtr+=TempLength;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x62;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x1E;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0x52;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr]=0xFF;
    
  }
	if((State & READ) != READ)
		return(ReturnERR11);
  SMLComm.SendPtr++;
	if(Len>14)
	{
		SMLComm.SendBuf[SMLComm.SendPtr++]=0x80|((Len+2)>>4);
		SMLComm.SendBuf[SMLComm.SendPtr]=((Len+2))&0xf;
	}
	else
		SMLComm.SendBuf[SMLComm.SendPtr]=OBISType;
#if 0
  switch(OBISType)
  {
		case 0x65:
			RAM_Write(&(SMLComm.SendBuf[++SMLComm.SendPtr]),(uint8_t*)Adder,Len);
			break;
		case 0x0A:
			if(Disk.TextDisTmr != 0)
      E2P_RData(&SMLComm.SendBuf[++SMLComm.SendPtr],Adder,Len);
    else{
      SMLComm.SendBuf[SMLComm.SendPtr] = 0x01;
      //				SMLComm.SendBuf[SMLComm.SendPtr+1] = 0x00;
      Len = 1	;	
    }
    break;
  case 0x63:
    RAM_Write(&(SMLComm.SendBuf[++SMLComm.SendPtr]),(uint8_t*)&Flag.StatusWord+1,1);
    RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr])+1,(uint8_t*)&Flag.StatusWord,1);
    break;
  case 0x55:
    //			SMLComm.SendBuf[++SMLComm.SendPtr]=0x04;
    //			SMLComm.SendBuf[SMLComm.SendPtr+1]=0x03;
    //			SMLComm.SendBuf[SMLComm.SendPtr+2]=0x02;
    //			SMLComm.SendBuf[SMLComm.SendPtr+3]=0x01;
    PowerData = &Measure8207.APowerPulP + Adder;
    *PowerData /= 23930;//23874;
    RAM_WriteInter( (uint8_t *)&SMLComm.SendBuf[++SMLComm.SendPtr],(uint8_t *)PowerData, 4 );
    //			RAM_WriteInter( (uint8_t *)&SMLComm.SendBuf[++SMLComm.SendPtr],(uint8_t *)&Measure8207.APowerPulP + Adder*4, 4 );
    break;	
  case 0x56:
    E2P_RData((uint8_t *)&ECData,Adder,Len);
    ECData = (long long int) BCD4_Long(((uint8_t *)&ECData) +1 );
    RAM_WriteInter( (uint8_t *)&SMLComm.SendBuf[++SMLComm.SendPtr],(uint8_t *)&ECData, 5);
    break;	
  case 0x59:
    Read_CMonEC( (uint8_t *)&ECData,Adder);
    ECData = (long long int) BCD4_Long((uint8_t *)&ECData + 2)/10;
    RAM_WriteInter( (uint8_t *)&SMLComm.SendBuf[++SMLComm.SendPtr],(uint8_t *)&ECData, 8 );
    
    break;		
    //		case 0x85:
    //			SMLComm.SendBuf[SMLComm.SendPtr] = 0x65;
    ////			if((Flag.StatusWord & 0x0008) == 0)
    //			if((Flag.Disk & F_OpButtonEDL40)==0)	
    //			{	
    //				SMLComm.SendBuf[++SMLComm.SendPtr]=0xFF;
    //				SMLComm.SendBuf[SMLComm.SendPtr+1]=0xFF;
    //				SMLComm.SendBuf[SMLComm.SendPtr+2]=0xFF;
    //				SMLComm.SendBuf[SMLComm.SendPtr+3]=0xFF;
    //				return(ReturnERR05);
    //
    //			}
    //			RAM_WriteInter((uint8_t*)&SMLComm.SendBuf[++SMLComm.SendPtr],(uint8_t*)&Comm.TimeSecPulseCnt,4);
    //			break;
  default:
    //			SMLComm.SendPtr++;
    E2P_RData(&SMLComm.SendBuf[++SMLComm.SendPtr],Adder,Len);
    break;
  }
#endif
	if(smal_callbefore)
	{
		if((State & FUN_TYPE)==FUN_TYPE)
		{
			SMLComm.SendPtr++;
		}
		ret=smal_callbefore(0,&SMLComm.SendBuf[SMLComm.SendPtr]);
		if(ret!=ReturnOK)
		{
			SMLComm.SendPtr--;
			return ret;
		}
	}
  switch(State & 0x00FF)
  {
		case RAM_INTER_TYPE:
			RAM_WriteInter(&(SMLComm.SendBuf[++SMLComm.SendPtr]),(uint8_t*)Adder,Len);
			break;
		case RAM_TYPE:
			RAM_Write(&(SMLComm.SendBuf[++SMLComm.SendPtr]),(uint8_t*)Adder,Len);
			break;
		case E2P_TYPE:
			E2P_RData(&SMLComm.SendBuf[++SMLComm.SendPtr],Adder,Len);
			break;
#if 0		
  case 0x10:
    SMLComm.SendBuf[SMLComm.SendPtr] = 0x65;
    if((Flag.StatusWord & 0x0008) == 0)
    //if((Flag.Disk & F_OpButtonEDL40)==0)	
    {	
      SMLComm.SendBuf[++SMLComm.SendPtr]=0xFF;
      SMLComm.SendBuf[SMLComm.SendPtr+1]=0xFF;
      SMLComm.SendBuf[SMLComm.SendPtr+2]=0xFF;
      SMLComm.SendBuf[SMLComm.SendPtr+3]=0xFF;
      return(ReturnERR11);
      
    }
    RAM_WriteInter((uint8_t*)&SMLComm.SendBuf[SMLComm.SendPtr],(uint8_t*)&Comm.TimeSecPulseCnt,4);
    break;
  case 0x04:
    RAM_Write( (uint8_t *)&SMLComm.SendBuf[SMLComm.SendPtr],(uint8_t *)&Signatrue.message[17], 8 );
    break;
  case 0x05:
    //			RAM_Write( (uint8_t *)&SMLComm.SendBuf[SMLComm.SendPtr],(uint8_t *)&Signatrue.message[17], 8 );
    SMLComm.SendBuf[SMLComm.SendPtr] = 0x5A;
    SMLComm.SendBuf[SMLComm.SendPtr+1] = 0x50;
    SMLComm.SendBuf[SMLComm.SendPtr+2] = 0x41;
    Disk.DisMUC_CCnt = 2880;
    break;	
  case 0x09:
    SMLComm.SendPtr = SendPtrBAK;
    DoDeviceIdentification();
    //			Disk.DoEDL40Cnt = 450;
    //			Flag.StatusWord |= 0x0008;
    //			Flag.Disk |= F_OpButtonEDL40;
    Len = 0;
    //			SMLComm.SendBuf[SMLComm.SendPtr] = 0x45;
    //			SMLComm.SendBuf[SMLComm.SendPtr+1] = 0x44;
    //			SMLComm.SendBuf[SMLComm.SendPtr+2] = 0x4C;
    //			SMLComm.SendBuf[SMLComm.SendPtr+3] = 0x33;
    //			SMLComm.SendBuf[SMLComm.SendPtr+4] = 0x32;
    //			SMLComm.SendBuf[SMLComm.SendPtr+2] = 0x31;
    break;	
#endif	
  default:
    break;
  }
  SMLComm.SendPtr += Len;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
/*  if((OBISType == 0x56)||(OBISType == 0x55))
  {
    SMLComm.SendBuf[++SMLComm.SendPtr]=0x01;
  }*/
#if 0
#else
/*	
	if(attri_num==0x73)
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
	}*/
#endif	
	if(sml_callback)
	{
		sml_callback(GetPropP_Req);
	}
  return(ReturnOK);
  
}	
//����OBIS���������дSET����//
uint8_t DoProSOBIS(uint8_t OBISNo)
{
  uint16_t SecCntBuff;
  uint16_t TempAdd,TempLength,TextLen;
  uint16_t	Len;
  uint8_t	OBISType;
  uint32_t	Adder;
  uint16_t	State;
//  uint8_t RamBuf[10];
  sml_function sml_callback;
	sml_beforefun smal_callbefore;
	uint8_t ret;
	//if(OBISNo==16  || (OBISNo==19) || (OBISNo==20))
/*	if(OBISNo==16)
		return ReturnERR15;*/
	
  Len = SMLOBISTab[OBISNo].Len;
  OBISType = SMLOBISTab[OBISNo].OBISType;
  Adder = SMLOBISTab[OBISNo].Adder;
  State = SMLOBISTab[OBISNo].State;
	sml_callback = SMLOBISTab[OBISNo].CallBack;
	smal_callbefore = SMLOBISTab[OBISNo].CallBefore;
	TempAdd=OrderRecord[14].OLStartAdd;
  TempLength=OrderRecord[14].OLLength;
	if(smal_callbefore)
	{
		ret=smal_callbefore(&SMLComm.RecBuf[TempAdd+1],&SMLComm.SendBuf[SMLComm.SendPtr]);
		if(ret!=ReturnOK)
			return ret;
	}
	if((XPERMIT&State)==XPERMIT)
		return(ReturnERR15);
	if((State & WRITE) != WRITE)
		return(ReturnERR10);
  
 // TempAdd=OrderRecord[9].OLStartAdd;
  //TempLength=OrderRecord[9].OLLength;
	
	if(((SMLComm.RecBuf[TempAdd]&0x70)!=(OBISType&0x70)) && ((PERMIT&State)!=PERMIT))
	{
		return ReturnERR20;
	}
	if(SMLComm.RecBuf[TempAdd]&0x80)
	{
		TextLen=(SMLComm.RecBuf[TempAdd]&0xf)<<4;
		TextLen=TextLen|(SMLComm.RecBuf[TempAdd+1]&0xf);
		if(SMLComm.RecBuf[TempAdd+1]&0x80)
		{
			TextLen = (TextLen<<4)+(SMLComm.RecBuf[TempAdd+2]&0xf);
			TextLen -=1;
		}
		TextLen-=2;
		//TempAdd++;
	}
	else
	{
		TextLen=(SMLComm.RecBuf[TempAdd]&0xf);
		TextLen-=1;
	}
	if(((PERMIT&State)==PERMIT) && (TextLen==Len))
		return(ReturnERR10);
	
	if((PERMIT&State)==PERMIT)
	{
		Len=TextLen;
	}
	
	if((TextLen!=Len) && (Len!=255))
		return ReturnERR14;
	if(TextLen<Len)
	{
		return ReturnERR14;
	}
		
  if((SMLComm.Flag & F_Attention_NotDoneALL) == F_Attention_NotDoneALL)
  {
    return(ReturnERR15);	
  }	
  if((SMLComm.Flag & F_Attention_NotDoneGroup) == F_Attention_NotDoneGroup)
  {
    if(SMLRecord[SMLComm.SLayerNumR-1].GroupNo == SMLRecord[SMLComm.SLayerNumR-2].GroupNo)
      return(ReturnERR15);
    else
      SMLComm.Flag &=~ F_Attention_NotDoneGroup;	
  }	
  if((State & 0x00FF) == 0x10)
  {
    if(SMLComm.RecBuf[TempAdd+4] != OBISType)
    {	
      if(SMLRecord[OBISNo].AbortOnError == 0x01)
        SMLComm.Flag |= F_Attention_NotDoneGroup;
      if(SMLRecord[OBISNo].AbortOnError == 0xFF)
        SMLComm.Flag |= F_Attention_NotDoneALL;	
      return(ReturnERR03);
      
    }
  }else if((SMLComm.RecBuf[TempAdd] != OBISType) && (Len!=255) &&  ((PERMIT&State)!=PERMIT))
  {	
    if((SMLComm.RecBuf[TempAdd]  <= 9) && (OBISType == 0x0A))
    {
      
    }else{	
      if(SMLRecord[OBISNo].AbortOnError == 0x01)
        SMLComm.Flag |= F_Attention_NotDoneGroup;
      if(SMLRecord[OBISNo].AbortOnError == 0xFF)
        SMLComm.Flag |= F_Attention_NotDoneALL;	
      return(ReturnERR03);
    }
    
  }
	
	if(SMLComm.RecBuf[TempAdd]&0x80)
	{
		if(SMLComm.RecBuf[TempAdd+1]&0x80)
		{
			TempAdd++;
			Len=TextLen;
		}
		TempAdd++;
	}
	
//	if(SMLComm.RecBuf[TempAdd]
//  if((State & WRITE) != WRITE)
  //  return(ReturnERR03);
  //	if(OBISType == 0xF1)
  //	{
  //		RAM_Write(RamBuf,&(SMLComm.RecBuf[TempAdd]),TempLength);//дSERVERID//
  //		RamBuf[5]=(RamBuf[1]&0X0F)*16+(RamBuf[2]&0X0F);
  //		RamBuf[6]=(RamBuf[3]&0X0F)*16+(RamBuf[4]&0X0F);
  //		E2P_WData(DisPINAdd,&RamBuf[5],0x2);
  //		
  //	}else	
  //		E2P_WData(Adder,&(SMLComm.RecBuf[TempAdd+1]),Len);
#if 0	
  switch(State & 0x00FF)
  {
  case 0x10:	//Time SETTING
    RAM_WriteInter((uint8_t*)&SecCntBuff,(uint8_t*)&SMLComm.RecBuf[TempAdd+5],4);
    if((SecCntBuff > Comm.SecPulseCnt + 27) || ( SecCntBuff + 27 < Comm.SecPulseCnt))
    {
      //Set time record
      TamperRecordData(TimeSET_No,(uint8_t*)&SMLComm.RecBuf[TempAdd+4]);
      //				TamperRecordData(ManipulationRecognized_No,(uint8_t*)&SMLComm.RecBuf[TempAdd+4]);
    }	
    if(Disk.DisMUC_CCnt != 0)
      Disk.DisMUC_CCnt = 2880;
    Flag.StatusWord |= 0x0008;
    Comm.TimeSecPulseCnt = SecCntBuff;
    SM.MagnetOnStateTime = 48;
    E2P_WData(Adder,&(SMLComm.RecBuf[TempAdd+1]),Len);
    InitPara();
    return(ReturnERR10);
    break;
  case 0x02:
    if(SMLComm.RecBuf[TempAdd+4] == 0x01)
    {	
      Disk.DisECModeCnt = 0;//450;
      Disk.DisECT1ModeCnt = 450;
      //				Disk.DisFeeCnt = 0;
      if((Flag.Disk & F_OpButtonEDL40) == 0)	Comm.INFORunFlag &=~ FStatu_One;
    }else if(SMLComm.RecBuf[TempAdd+4] == 0x03)
    {	
      //				Disk.DisFeeCnt = 60;//450;
      Disk.DisECModeCnt = 450;//450;
      Disk.DisECT1ModeCnt = 0;
      if((Flag.Disk & F_OpButtonEDL40) == 0) Comm.INFORunFlag &=~ FStatu_One;
      
    }else if(SMLComm.RecBuf[TempAdd+4] == 0x00)
    {	
      Disk.DisECT1ModeCnt = 0;
      Disk.DisECModeCnt = 0;
    }else{
      Disk.DisECT1ModeCnt = 0;
      Disk.DisECModeCnt = 0;
      InitPara();
      return(ReturnERR14);
      //				Disk.DisFeeCnt = 0;
    }
    break;
  case 0x03:
    
    Disk.DisFeeCnt = 60;//450;
    //			Disk.DisECModeCnt = 60;//450;
    Disk.Dis022Cnt = 60;//450;
    RamBuf[0] = 0;
    RamBuf[1] = 0;
    RamBuf[2] = 0;
    RamBuf[3] = 3;
    E2P_WData(E2P_DisTariff,RamBuf,4);
    E2P_WData(Adder,&(SMLComm.RecBuf[TempAdd+1]),Len);
    if((SMLComm.RecBuf[TempAdd+1] > 0)&&(SMLComm.RecBuf[TempAdd+1] < 3))
      SM.FeeNo = SMLComm.RecBuf[TempAdd+1];
    else
      return(ReturnERR15);	
    InitPara();
    return(ReturnERR14);
    break;	
  case 0x60:
    if((Flag.ClrFlag & F_SSET_EN) == 0)	
      return(ReturnERR00);
    RamBuf[0] = 1;	
    E2P_WData(Serial_No_Bit,RamBuf,1);
    Flag.ClrFlag &=~ F_SSET_EN;
		//E2P_WData(TempAdd,SMLComm.RecBuf[TempAdd+1],TempLength);
    break;	
  case 0x06:
    Disk.DoEDL40Cnt = 450;
    if(SMLComm.RecBuf[TempAdd+1] != 1)
    {	
      TamperRecordData(TimeAsynchronous_No,RamBuf);
      Disk.DoEDL40Cnt = 0;
    }
    E2P_WData(Adder,&(SMLComm.RecBuf[TempAdd+1]),Len);
    InitPara();
    return(ReturnERR03);
    break;	
  case 0x07:
    //if(PIN_EN & P_EN)
     // return(ReturnERR00);
    break;
  case 0x0A:
    if(SMLComm.RecBuf[TempAdd+1] != 1)
    {	
      Clr_E2PData( Magnetic_Bit, 1, 1 );
      Flag.StatusWord &=~ 0x0040;
      return(ReturnOK);
    }else	
      return(ReturnERR00);
    break;	
  case 0x0B:
    Disk.TextDisTmr = 30;
    if(SMLComm.RecBuf[TempAdd] != 0x0A)
    {
      RAM_DataFill( RamBuf, 9,0xFF );
      TextLen = SMLComm.RecBuf[TempAdd] -1;
      RAM_Write(RamBuf+9-TextLen,&(SMLComm.RecBuf[TempAdd+1]),TextLen);
      E2P_WData(Adder,RamBuf,Len);
    }else	
      E2P_WData(Adder,&(SMLComm.RecBuf[TempAdd+1]),Len);
    InitPara();
    return(ReturnOK);	
  case 0x0C:
    RAM_Write(RamBuf,&(SMLComm.RecBuf[TempAdd]),TempLength);//дSERVERID//
    RamBuf[5]=(RamBuf[1]&0X0F)*16+(RamBuf[2]&0X0F);
    RamBuf[6]=(RamBuf[3]&0X0F)*16+(RamBuf[4]&0X0F);
    E2P_WData(DisPINAdd,&RamBuf[5],0x2);
    InitPara();
    return(ReturnOK);	
    
  default:
    break;
  }
#endif  
  switch(State & 0x00FF)
  {	
		case RAM_INTER_TYPE:
			RAM_WriteInter((unsigned char*)Adder,&(SMLComm.RecBuf[TempAdd+1]),Len);
			break;
		case RAM_TYPE:
			RAM_Write((unsigned char*)Adder,&(SMLComm.RecBuf[TempAdd+1]),Len);
			break;
		case E2P_TYPE:
			E2P_WData(Adder,&(SMLComm.RecBuf[TempAdd+1]),Len);
			break;
		default:
			break;
  }
  InitPara();
	if(sml_callback)
	{
		sml_callback(SetPropP_Res);
	}
  return(ReturnOK);
}


//�����÷���һ����ȷ����Ӧ//
void	ReturnSetOK(uint8_t Number)
{
  uint16_t TempAdd;
  uint16_t TempLength;
  //SMLComm.SendBuf[SMLComm.SendPtr-3]=0x72;//���ݰ�ͷ//
  SMLComm.SendBuf[SMLComm.SendPtr-1]=0xff;//д����FF01//
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x74;
  SMLComm.SendPtr++;
  TempAdd=OrderRecord[0].OLStartAdd;
  TempLength=OrderRecord[0].OLLength;
  //	RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[TempAdd]),TempLength);//дSERVERID//
  //	SMLComm.SendBuf[SMLComm.SendPtr+1] = 'Z';
  //	SMLComm.SendBuf[SMLComm.SendPtr+2] = 'P';
  //	SMLComm.SendBuf[SMLComm.SendPtr+3] = 'A';
  //	if(SMLComm.RecBuf[TempAdd] == 0)
  SMLComm.SendBuf[SMLComm.SendPtr] = 0x0B;
  //	else	
  //		RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[TempAdd]),1);
  E2P_RData( &(SMLComm.SendBuf[SMLComm.SendPtr+1]),Server_ID, 10 ); 
  
  SMLComm.SendPtr+=11;
  SMLComm.SendBuf[SMLComm.SendPtr] = 0x07;
  SMLComm.SendPtr++;
  if(Number == 0xFF)
  {
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLComm.RecBuf[(OrderRecord[4].OLStartAdd)+1];//0x81;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLComm.RecBuf[(OrderRecord[4].OLStartAdd)+2];//0x81;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLComm.RecBuf[(OrderRecord[4].OLStartAdd)+3];//0xC7;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLComm.RecBuf[(OrderRecord[4].OLStartAdd)+4];//0xC7;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLComm.RecBuf[(OrderRecord[4].OLStartAdd)+5];//0xFD;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLComm.RecBuf[(OrderRecord[4].OLStartAdd)+6];//0x00;
  }/*else if(Number==ReturnERR03)
	{
		SMLComm.SendBuf[SMLComm.SendPtr] = 0x81;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = 0x81;//0x81;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = 0xc7;//0xC7;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = 0xc7;//0xC7;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = 0xfe;//0xFD;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = 0x05;//0x00;
	}*/
	else{	
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLAttentionNumber[Number].OBIS0;//0x81;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLAttentionNumber[Number].OBIS1;//0x81;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLAttentionNumber[Number].OBIS2;//0xC7;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLAttentionNumber[Number].OBIS3;//0xC7;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLAttentionNumber[Number].OBIS4;//0xFD;
    SMLComm.SendPtr++;
    SMLComm.SendBuf[SMLComm.SendPtr] = SMLAttentionNumber[Number].OBIS5;//0x00;
  }
  SMLComm.SendPtr++;

  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
  
}	

//attention number//
void ReturnAttentionNumber(uint8_t Number)
{
  uint16_t TempAdd;
  uint16_t TempLength;
  uint16_t i;
  SMLComm.SendBuf[SMLComm.SendPtr-1]=0xff;//д����FF01//
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x74;
  SMLComm.SendPtr++;
  TempAdd=OrderRecord[0].OLStartAdd;
  TempLength=OrderRecord[0].OLLength;

  if(SMLComm.RecBuf[TempAdd] == 0)
    SMLComm.SendBuf[SMLComm.SendPtr] = 0x0B;
  else	
    RAM_Write(&(SMLComm.SendBuf[SMLComm.SendPtr]),&(SMLComm.RecBuf[TempAdd]),1);
  
  E2P_RData( &(SMLComm.SendBuf[SMLComm.SendPtr+1]),Server_ID, 10 ); 
  
  SMLComm.SendPtr+=TempLength;
  for(i=0;i<6;i++)
  {
    SMLComm.SendBuf[SMLComm.SendPtr++]= *(&(SMLAttentionNumber[Number].OBIS0)+i);
    
  }
  
  SMLComm.SendBuf[SMLComm.SendPtr]=0x03;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x4F;
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x4B;
  
  
  SMLComm.SendPtr++;
  SMLComm.SendBuf[SMLComm.SendPtr]=0x01;
} 

