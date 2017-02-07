#include "Mem.h"
#include "General.h"
#include "TypeE2P.h"
#include "TypeMeter.h"
#include "Type.h"

#include "Data.h"
#include "MeterDataType.h"
//#include <App.h>
//#include <RN8213.h>
#define  _FM24CXX_GLOBALS

#include <Drive_Lib.h>
#include "Initial.h"

//����


//����
#define	RD8213DLY	100//42//42//��д8207ʱ�õ��ĵȴ�ʱ��//
#define	READ8213OK	0x55
#define	WRITE8213OK 0x5a

//* RAM_Dest :��ȡ���ݷ���RAMָ��
//SYN_Src: ��ȡ����ID��
//Lenth ����ȡ���ݳ���
//����0 :ͬ����д����
//����1: ͬ����д����
int SYNData_Read( unsigned char* RAM_Dest,unsigned int SYN_Src, int Lenth )
{
	short i;
	unsigned char* ptr;	
	unsigned char CheckNum;
	for(i=0;i<3;i++)
	{
		fnWDT_Restart();
		Comm8213.CommDly=RD8213DLY;//ͨ�ŵȴ�ʱ��//
		Comm8213.SendBuf8213[0]= 0xA6;//��Ҫ���͵�������ʼλ//
		Comm8213.SendBuf8213[1]=F_DRS_ReadEN;//��д������//
		Comm8213.SendBuf8213[2]= SYN_Src&0x00FF;	//��д��ַ
		Comm8213.SendBuf8213[3]= SYN_Src>>8;
		Comm8213.SendBuf8213[4]= 0x00;	//���ݳ���
		Comm8213.SendBuf8213[5]= ChkNum(Comm8213.SendBuf8213,5);
		Comm8213.SendBuf8213[6]= 0xAB;	//ͨѶ������
		Comm8213.NeedRecCnt= Lenth+7;//��Ҫ���յ����ݳ���//
		Comm8213.NeedSendCnt=6;//��Ҫ���͵����ݳ���(��ȥ���ĵ�һ�ֽ�)//
		Comm8213.CommOk=0;//ͨ����ɱ�־��0//
		Comm8213.Ptr8213=0;

		RAM_Fill(Comm8213.RecBuf8213,50);

	//	UART5->CTRL &=0xfff3; 	//���ν����ж�,���ν��մ����ж�
		UART5->STA = 0x3d;		//������жϱ�־�����մ����־
		
		UART5->CTRL |=0x02;		//�������ж�
		UART5->STA = 0x02;		//�巢���жϱ�־
		UART5->TXD= Comm8213.SendBuf8213[0];//����һ�ֽ�//
	//	Comm8213.CommDly=RD8213DLY;
		
		while(Comm8213.CommDly>0)//���ȴ�ʱ��û��ʱһֱ�ȴ�//
		{
			SystemDelay(1);
			if(Comm8213.CommOk == READ8213OK)
			{
				RAM_Write(&(Comm8213.SendBuf8213[0]),Comm8213.RecBuf8213,Lenth+7);
				CheckNum = ChkNum(Comm8213.RecBuf8213,Lenth+5);
				
				if(Comm8213.RecBuf8213[Lenth+5] == CheckNum)
				{	
					ptr = Comm8213.RecBuf8213;
					RAM_Write(RAM_Dest,ptr+5,Lenth);							
					return 0;
				}
			}
			
			fnWDT_Restart();
		}
		Comm8213.Ptr8213=0;
	}
	return 1;
}
//����

//* RAM_Dest :��ȡ���ݷ���RAMָ��
//SYN_Src: ��ȡ����ID��
//Lenth ����ȡ���ݳ���
//����0 :ͬ����д����
//����1: ͬ����д����
int SYNData_Write( unsigned int SYN_Dest, unsigned char* RAM_Src, int Lenth)
{
	short i;
	unsigned char CheckNum;
	for(i=0;i<3;i++)
	{
//		WDTCTL = WDT_ARST_1000;
		fnWDT_Restart();

		Comm8213.CommDly=RD8213DLY;//ͨ�ŵȴ�ʱ��//
		Comm8213.SendBuf8213[0]= 0xA6;//��Ҫ���͵�������ʼλ//
		Comm8213.SendBuf8213[1]=F_DRS_WriteEN;//��д������//
		Comm8213.SendBuf8213[2]= SYN_Dest&0xFF;	//��д��ַ
		Comm8213.SendBuf8213[3]= SYN_Dest>>8;
		Comm8213.SendBuf8213[4]= Lenth;	//���ݳ���
		RAM_Write(Comm8213.SendBuf8213+5,RAM_Src,Lenth);
		Comm8213.SendBuf8213[5+Lenth]= ChkNum(Comm8213.SendBuf8213,5+Lenth);
		Comm8213.SendBuf8213[6+Lenth]= 0xAB;	//ͨѶ������
		Comm8213.NeedRecCnt= 1;//��Ҫ���յ����ݳ���//
		Comm8213.NeedSendCnt=6+Lenth;//��Ҫ���͵����ݳ���(��ȥ���ĵ�һ�ֽ�)//
		Comm8213.CommOk=0;//ͨ����ɱ�־��0//
		Comm8213.Ptr8213=0;

		UART5->CTRL &=0xfff3; 	//���ν����ж�,���ν��մ����ж�
		UART5->STA = 0x3d;		//������жϱ�־�����մ����־
		UART5->CTRL |=0x02;		//�������ж�
		UART5->STA = 0x02;		//�巢���жϱ�־
		
		UART5->TXD= Comm8213.SendBuf8213[0];//����һ�ֽ�//
		

		while(Comm8213.CommDly>0)//���ȴ�ʱ��û��ʱһֱ�ȴ�//
		{
			if(Comm8213.CommOk == READ8213OK)
			{
				
				if(Comm8213.RecBuf8213[0] == 0x06)
				{						
					return 0;
				}
			}
			fnWDT_Restart();
		}
	}
	return 1;
}
void SynData500ms (void)
{
		
}
//����
void SynData1s (void)
{
	unsigned char Buff[30]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,
					0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,};
	unsigned char stater;
	int i,j;
	unsigned int ID_Src,Len;
	unsigned char* RAM_Dest;
//	stater =SYNData_Read( Buff,1, 6 );
	stater =SYNData_Write( 0x1001,Buff, 30 );
	if(stater == 0)
		stater = 1;
	else
		stater = 0;	
	for(j=0;j<MeterRealTabNum;++j)
	{
		ID_Src = RealTab[j].DataID;
		for( i=0;i<MeterDataTabNum;i++)
		{
			if( MeterDataTab[i].DataID == ID_Src )
			{
				RAM_Dest = (unsigned char *)MeterDataTab[i].DataAdd;
				break;
			}				
		}
		if(i<MeterDataTabNum)
			ID_Read(RAM_Dest,ID_Src,RealTab[j].len);
	}
}

void Read_CMonEC( unsigned char* Dest, short ECRgAds )
{

}

////����
//int SYNDataDown_Read( unsigned char* RAM_Dest,unsigned int SYN_Src, int Lenth )
//{
//	
//	
//	return 0;
//}
////����
//int SYNDataDown_Write( unsigned int SYN_Dest, unsigned char* RAM_Src, int Lenth)
//{
//	
//	return 0;
//}

//* RAM_Dest :��ȡ���ݷ���RAMָ��
//ID_Src: ��ȡ����ID��
//Lenth ����ȡ���ݳ���

//����0 :��д����
//����1:��д����
int ID_Read( unsigned char* RAM_Dest,unsigned int ID_Src, int Lenth )
{
	unsigned int 	i;
	unsigned int	DataID;			//ID��
	unsigned long 	DataAdd;		//��ַ
	unsigned char 	DataLen;		//���ݳ���
	unsigned char 	DataRWENStorage;	//���ݶ�дȨ�޺ʹ洢����
	
	for( i=0;i<MeterDataTabNum;i++)
	{
		if( MeterDataTab[i].DataID == ID_Src )
		{
			DataAdd = MeterDataTab[i].DataAdd;
			DataLen = MeterDataTab[i].DataLen;	
			DataRWENStorage = MeterDataTab[i].DataRWENStorage;
			break;
		}				
	}
	
	if((DataRWENStorage & F_DRS_ReadEN) == 0)
		return 1;
	if((DataRWENStorage & F_DRS_SYNData) == F_DRS_SYNData)	
	{
		if(SYNData_Read(RAM_Dest, ID_Src, DataLen ) == 0)
			return 0;
		else if(SYNData_Read(RAM_Dest, ID_Src, DataLen ) == 0)
			return 0;
		else return 1;	
	}	
	switch( DataRWENStorage & 0x1F )
	{	
		case DRS_Energy:
			Read_CMonEC( RAM_Dest, DataAdd );
			break;
		case DRS_instantaneous:
			
			break;
		case DRS_Eeprom1:
			if(E2P_RAdj( RAM_Dest,DataAdd,  DataLen ) != 0)
				return 1;
			break;
		case DRS_Eeprom2:
			if(E2P_RData( RAM_Dest,DataAdd,  DataLen ) != 0)
				return 1;
			break;
		case DRS_Eeprom3:
			if(E2P_RECData( RAM_Dest,DataAdd,  DataLen ) != 0)
				return 1;
			break;
		case DRS_Flash:
			
			break;
		case DRS_Ram:
			RAM_Write( RAM_Dest,(unsigned char*)DataAdd,DataLen);
			break;	
		case DRS_ferroelectric:
			
			break;
		case DRS_TimeIC:
			fnSysClock_Read(RAM_Dest);
			break;			
		default:
			break;		
	}
	return 0;
}

//* RAM_Dest :��ȡ���ݷ���RAMָ��
//ID_Src: ��ȡ����ID��
//Lenth ����ȡ���ݳ���
//����0 :��д����
//����1:��д����
int ID_Write( unsigned int ID_Dest, unsigned char* RAM_Src, int Lenth)
{
	unsigned int 	i;
	unsigned int	DataID;			//ID��
	unsigned long 	DataAdd;		//��ַ
	unsigned char 	DataLen;		//���ݳ���
	unsigned char 	DataRWENStorage;	//���ݶ�дȨ�޺ʹ洢����
	
	for( i=0;i<MeterDataTabNum;i++)
	{
		if( MeterDataTab[i].DataID == ID_Dest )
		{
			DataAdd = MeterDataTab[i].DataAdd;
			DataLen = MeterDataTab[i].DataLen;	
			DataRWENStorage = MeterDataTab[i].DataRWENStorage;
			break;
		}				
	}
	
	if((DataRWENStorage & F_DRS_WriteEN) == 0)
		return 1;
	if((DataRWENStorage & F_DRS_SYNData) == F_DRS_SYNData)	
	{
		if(SYNData_Write(ID_Dest, RAM_Src,DataLen ) == 0)
			return 0;
		else if(SYNData_Write(ID_Dest,RAM_Src,  DataLen ) == 0)
			return 0;
		else return 1;	
	}	
	switch( DataRWENStorage & 0x1F )
	{	
		case DRS_Energy:
//			Read_CMonEC( RAM_Dest, DataAdd );
			break;
		case DRS_instantaneous:
			
			break;
		case DRS_Eeprom1:
			if(E2P_WAdj( DataAdd,RAM_Src,  DataLen ) != 0)
				return 1;
			break;
		case DRS_Eeprom2:
			if(E2P_WData( DataAdd,RAM_Src,  DataLen ) != 0)
				return 1;
			break;
		case DRS_Eeprom3:
			if(E2P_WECData( DataAdd, RAM_Src, DataLen ) != 0)
				return 1;
			break;
		case DRS_Flash:
			
			break;
		case DRS_Ram:
			RAM_Write( (unsigned char*)DataAdd,RAM_Src,DataLen);
			break;	
		case DRS_ferroelectric:
			
			break;
		case DRS_TimeIC:
			fnSysClock_Write(&Clk.Sec[0]);
			break;			
		default:
			break;		
	}
	return 0;
	
}





