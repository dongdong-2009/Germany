#include "TypeMeter.h"
#include "Port.h"
#include "Type.h"
#include "TypeE2P.h"
#include "Data.h"
#include "RsComm.h"

#include "Mem.h"
#include "General.h" 
#include "Measure.h"
#include "Power.h"
#include "Time.h"
#include "Initial.h"
#include "math.h"


#include <App.h>

#include "serial.h"

void fnUSART5_Init(unsigned char Cfg)
{
	u32	ClkDiv;
	ClkDiv = fnDl645MainClock_Get();
	switch(Cfg & 0xE0)
	{	case 0x00:		//300
			ClkDiv=ClkDiv/(300*16)-1;
			break;
	  	case 0x20:		//600
			ClkDiv=ClkDiv/(600*16)-1;
			break;
	  	case 0x40:	//1200
			ClkDiv=ClkDiv/(1200*16)-1;
			break;
		case 0x60:	//2400
			ClkDiv=ClkDiv/(2400*16)-1;
			break;
		case 0x80:	//4800
			ClkDiv=ClkDiv/(4800*16)-1;
			break;
		case 0xc0:	//9600
			ClkDiv=ClkDiv/(9600*16)-1;
			break;
		case 0xE0:	//19200
			ClkDiv=ClkDiv/(19200*16)-1;
			break;	
		default:	
			ClkDiv=ClkDiv/(300*16)-1;		//300
			break;
	}
	//UART0用于RS485口1通讯.
	UART5->BAUD = ClkDiv;
	UART5->CTRL = (1 << 0)	|   /* uart enable */
                  (3 << 5)	|	/* data bit: 8 */
//                  (2 << 5)	|	/* data bit: 7 */
                  (2 << 7);	/* even  */
	//GPIO->PCA0 |=0x02000000;		//GPIO选择UART0
	PinMode_DualRX(GPIO_MODE_IN);
	PinMode_DualTX(GPIO_MODE_OUT);
//	Comm8213.Ptr8213=0;

			UART5->CTRL &=0xfffd;		//屏蔽发送中断
			UART5->STA = 0x02;		//清发送中断标志
		
			UART5->CTRL |=0x0c; 	//允许接收中断,允许接收错误中断
			UART5->STA = 0x3d;		//清接收中断标志及接收错误标志
	return;
}
#if 0
//计算CCITT-CRC16.（前称CRC-CCITT。ITU的前身是CCITT。）//
//计算的初值用0XFFFF，计算好后与0XFFFF异或，					//
//通信中接收的CRC	值是低在前，高在后的,//
//此值用作通信时的比较时要倒一下（高字节与低字节）//
unsigned short DoCrc16(unsigned short RegInit, unsigned char *message, unsigned short len) 
{
    unsigned short CrcReg = RegInit; 
    while (len--) 
       { CrcReg = (CrcReg >> 8) ^ Crc16tab[(CrcReg ^ *message++) & 0xff];}
//    Comm.CRCRegInit = CrcReg;
    CrcReg=CrcReg^0xffff;    
    return CrcReg;
} 
#endif

void Read_CPU_CRC( unsigned char* Dest )
{
	unsigned short CRC;
	unsigned char *Addr;
	Addr = Read_Flash;
	CRC = DoCrc16(0xFFFF, Addr, 0x28000);	
	RAM_Write( Dest, (unsigned char*)&CRC, 2 );
}



void CommInit(unsigned char COM_No)
{
	switch( COM_No )
	{
		case 1:
			if( Comm.Delay1 == 0 ) 
			{	
				Comm.Mode1 = 1;
				Comm.Ptr1 = 0;
				Flag.Run1 &= ~(F_T485 + F_THW + F_ComOK);
			}
			break;	
		default: 
			break;		
	}
}				

void CommRest(unsigned char COM_No)					//恢复至初始状态
{	
//	u32	ClkDiv2;
	switch( COM_No )
	{
		case 0:	
			break;
		case 1:	
			Serial_Open(1,600,7,SERIAL_CHECK_EVEN);
			Comm.State1 = 0;			
			Comm.Mode1 = 0;
			Comm.BTime1 = 0;					// 字符间定时
			Comm.FTime1 = 0;					// 帧间定时	
			Comm.TX_Delay1 = 0;				//发送延时
			Comm.BlockNo1 = 0;
			Flag.Run1 &= ~(F_AdsOk + F_MimaOk0+F_MimaOk1);
			break;	
		case 2:
			break;	
		default:
			break;
	}		
	CommInit(COM_No);
}	

short GetXorCheck( unsigned char* XorCheck, short* CheckAds,unsigned char *ComBuf)
{
	short	i,j;
	*XorCheck = 0;
	for( i=0;i<RS_MaxSize;i++)
	{
		if(( *(ComBuf+i) == SOH ) || ( *(ComBuf+i) == STX )) 
		break;
	}
	for( j=i+1;j<RS_MaxSize;j++ )
	{
		*XorCheck ^= *(ComBuf+j); 
		if(( *(ComBuf+j) == ETX ) || ( *(ComBuf+j) == EOT ))
		{
			*CheckAds = j + 1;
			return 0;	
		}	
	}	
	return -1;
}	
#define IEC1107_READ(buf,len) Serial_Read(1,buf,len)
#define IEC1107_WRITE(buf,len) (Serial_Write(1,buf,len))
#define IEC1107_STATUS				Serial_Status(1)
void CommMode(unsigned char COM_No)
{
	unsigned char* ComMode;
	unsigned char* ComPtr;
	unsigned char* ComBTime;
	unsigned char* ComRun;	
	unsigned char* ComBlockNo;
	int rclen;
	
	ComMode = CommPara[COM_No].Mode;
	ComPtr = CommPara[COM_No].Ptr;
	ComBTime = CommPara[COM_No].BTime;
	ComRun = CommPara[COM_No].Run; 
	ComBlockNo = BlockCommPara[COM_No].BlockNo;

	if( Comm.Ptr1 >= RS_MaxSize )
		{
			Comm.Ptr1 = 0;
			return;
		}

		rclen=IEC1107_READ(CommPara[COM_No].Buf+*CommPara[COM_No].Ptr,100);
		if(rclen)
		{
			*CommPara[COM_No].Ptr +=rclen;
		//	Comm.BTime1 = MS600;
			Comm.Delay1 = 20;
			switch (CommPara[COM_No].Buf[0])
			{
			case NAK: 	
				Comm.State1 = 3; 
				break;
			case ACK: 	
				if( Comm.State1 == 1 )
				{
					if( CommPara[COM_No].Buf[*CommPara[COM_No].Ptr - 1] != LF )	
						return;
					Comm.State1 = 2;
				}		
				else  
					Comm.State1 = 3; 
				break;
			case SOH:	
				if( Comm.Ptr1 <= 3 ) 
					return;
				if(( CommPara[COM_No].Buf[*CommPara[COM_No].Ptr - 2] != EOT ) && ( CommPara[COM_No].Buf[*CommPara[COM_No].Ptr  - 2] != ETX )) 
					return;
				Comm.State1 = 3;
				break;
			case StartCode:	
				if( CommPara[COM_No].Buf[*CommPara[COM_No].Ptr  - 1] != LF ) 
					return;
				Comm.Rdout300bps1=0x0;
				Comm.State1 = 1;
				break;	
			default:  
				Comm.Ptr1 = 0;
				return;
		}	
		Flag.Run1 |= F_ComOK;
		(*ComMode)=1;
		Comm.BTime2=64;
	}
	switch( *ComMode )
	{
		case 0: 
			CommInit(COM_No); break;	
		case 1: 
				if( *ComPtr == 0 ) 
				{
					CommInit(COM_No);	
					break;
				}
				if(( *ComRun & F_ComOK ) == 0 )
				{
					if( *ComBTime == 0 ) 
					{
						CommInit(COM_No);	
					}
				}	
				else 
					CommModeRec(COM_No);
				break;
		case 2: 
			//	if(( *ComRun & F_ComOK ) != 0 )
				if(( *ComRun & F_AdsOk ) != 0 )
				{
					if(*ComBlockNo && (Comm.Delay1==0))
					{
						//Comm.TX_Delay1 = MS400+5;
						Comm.Delay1 = MS400;
						SendNextBlock(COM_No);
						Comm.FTime1=2;
					}
					else 
						CommInit(COM_No);
				}					
		default: 
			break;				
	}	
}	
//----------------------
void EendRDmode0(unsigned char COM_No)
{  
	{
	//	if(Comm.TXLAST_Delay1 == 0)
		{
			Comm.BlockNo1=0;
	    CommRest(1);
		}
	}
}

const READOUT RDMode9Tab[]=
{
	SendAllNO,SendBCC,EendRDmode0		
};


const READOUT ReadOutTab[]=
{
	SendErrorCode,
	SendConstant,	SendVersion,
	SendBCC,EendRDmode0
};



//====================================
void SendNextBlock(unsigned char COM_No)
{	
//	unsigned char i,TempAcc,Buff[10];

	unsigned char* ComBlockNo;
	unsigned char* ComRun;
	unsigned char* ComPtr;
	unsigned char* ComBuf;
	unsigned char* ComSendLen;	
		
	ComSendLen = BlockCommPara[COM_No].SendLen;
	
	ComBlockNo = BlockCommPara[COM_No].BlockNo;
	ComPtr = CommPara[COM_No].Ptr;
	ComRun = CommPara[COM_No].Run; 
	ComBuf = CommPara[COM_No].Buf;
	
	switch(Comm.RdoutContent[COM_No])
	{		
		case Read0Mode:	
				if(*ComBlockNo<4)
					return;
			ReadOutTab[*ComBlockNo-4].p(COM_No);			
			if((*ComBlockNo == 0))
				return;		
			break;
		default:
	   		*ComBlockNo=0;
	    	CommRest(COM_No);
	    	return;						
	}
			

	(*ComBlockNo)++;	

	*ComRun &= ~F_ComOK; 
	
	*ComPtr = 1;
						
	if(COM_No == 0)		
	{			
		UART0->TXD= *ComBuf;
		UART0->CTRL |=0x02;		//允许发送中断
		UART0->STA = 0x02;		//清发送中断标志
	}
	else
	{
		*ComPtr = 0;
		IEC1107_WRITE(ComBuf,*ComSendLen);
		*ComSendLen=0;
	}
}

//-----------------------------------
void SendEvent(unsigned char COM_No)
{

}

//*************************************
void CalcuBCC(unsigned char *Point,unsigned char Len,unsigned char COM_No)
{
	unsigned char i;
	unsigned char* ComBcc;  
	
	ComBcc = CommPara[COM_No].Bcc;
				
	for(i=0;i<Len;i++)	
	{
		*ComBcc ^= *Point;
		Point++;
	}
}

const unsigned char ErrObisTab[]="F.F(000000";
void SendErrorCode(unsigned char COM_No)
{
	unsigned char i;
	unsigned char* ComBuf; 
	
	ComBuf = CommPara[COM_No].Buf;	

	for(i=0;i<10;i++)
	{
		*(ComBuf+i)=ErrObisTab[i];
	}
	_BCD_ASC(ComBuf+4,(unsigned char*)&Para.meter_sts,3);
/*	if((Flag.AlarmFlg[0] & F_AlarmE2P)==F_AlarmE2P)
	{			
		*(ComBuf+7) = '1';	
	}*/

	SendCRLFBCC(13,COM_No);
}

const unsigned char SecObisTab[]="0.9.3(000000";
void SendSecCode(unsigned char COM_No)
{
	unsigned char i;
	unsigned char* ComBuf;
	unsigned char buf[8];
	
	ComBuf = CommPara[COM_No].Buf;	

	for(i=0;i<10;i++)
	{
		*(ComBuf+i)=SecObisTab[i];
	}
//	Long_BCD4(buf,Comm.SecPulseCnt);
	RAM_Write(buf,(unsigned char*)&Comm.SecPulseCnt,4);
	_BCD_ASC(ComBuf+6,buf,4);
	SendCRLFBCC(17,COM_No);
}

//-----------------------
const unsigned char  CheatTab[]="F.F.1(000000";
void SendCheatEvent(unsigned char COM_No)
{
	unsigned char i;
	unsigned char* ComBuf; 
	
	ComBuf = CommPara[COM_No].Buf;
		
	for(i=0;i<12;i++)
	{
		*(ComBuf+i)=CheatTab[i];
	}
	
	if( Flag.AlarmFlg[0] & F_AlarmCoverOpen )	*(ComBuf+10) |= '8';	//开盖指示
	if( Flag.AlarmFlg[0] & F_AlarmTCoverOpen )	*(ComBuf+9) |= '8';		//开端指示		
	if( Flag.AlarmFlg[0] & F_AlarmMagnet )		*(ComBuf+8) |= '8';		//磁场指示

	SendCRLFBCC(15,COM_No);//SendCRLFBCC(&Comm.Buf[12],15);
}	

//-----------------------
void SendAllNO(unsigned char COM_No)
{
	unsigned char* ComBuf; 
	
	ComBuf = CommPara[COM_No].Buf;

	*ComBuf = '(';
	E2P_RData(ComBuf+1,EMeter_No,8);
	*(ComBuf+9) = ')';	
	*(ComBuf+10) = 0xd;	
	*(ComBuf+11) = 0xa;	
					
/*	Comm.Buf[12] = '(';
	E2P_RData(&Comm.Buf[13],Serial_No,20);
	Comm.Buf[23] = ')';	
	Comm.Buf[24] = 0xd;	
	Comm.Buf[25] = 0xa;	
	
	Comm.Buf[36] = '(';
	E2P_RData(&Comm.Buf[37],PCB_No,12);
	
	SendCRLFBCC(52);//SendCRLFBCC(&Comm.Buf[43],46);
*/	
	*(ComBuf+12) = '(';
	E2P_RData(ComBuf+13,Serial_No,8);
	*(ComBuf+21) = ')';	
	*(ComBuf+22) = 0xd;	
	*(ComBuf+23) = 0xa;	
	*(ComBuf+24) = '(';
	
	E2P_RData(ComBuf+25,PCB_No,12);
	
	SendCRLFBCC(40,COM_No);//SendCRLFBCC(&Comm.Buf[43],46);
}

//-----------------------
//const unsigned char CusNumTab[]="C.1.0(";
const unsigned char CusNumTab[]="0.0.0(";
//const unsigned char CusNumTab1[]="C.90.1(";

void SendCusNum(unsigned char COM_No)
{

}

//-----------------------
const unsigned char RTCTimeTab[]="0.9.1(";

void SendRtcTime(unsigned char COM_No)
{
	unsigned char i;
	unsigned char* ComBuf; 
	unsigned char tmpbuf[4];
	                                           
	ComBuf = CommPara[COM_No].Buf;	
	
	for(i=0;i<6;i++)
	{
		*(ComBuf+i)=RTCTimeTab[i];
	}	
	
	GetTime();
	tmpbuf[0]=Byte_BCD(Clk.Sec[0]);
	tmpbuf[1]=Byte_BCD(Clk.Min[0]);
	tmpbuf[2]=Byte_BCD(Clk.Hour[0]);
	_BCD_ASC(ComBuf+6,tmpbuf,3);
	//_BCD_ASC(ComBuf+6,&Clk.Sec[0],3);
	
	*(ComBuf+13)= *(ComBuf+11);
	*(ComBuf+12)= *(ComBuf+10);
	*(ComBuf+11)= ':';
	*(ComBuf+10)= *(ComBuf+9);
	*(ComBuf+9)= *(ComBuf+8);
	*(ComBuf+8)= ':';

	SendCRLFBCC(17,COM_No);//SendCRLFBCC(&Comm.Buf[14],17);
}

//----------------------
//void SendCRLFBCC(unsigned char *Point,unsigned char Len)
//{
//	*Point++ = ')';	
//	*Point++ = 0xd;	
//	*Point = 0xa;
//	Comm.SendLen = Len;
//	CalcuBCC(&Comm.Buf[0],Len);	
//}

void SendCRLFBCC(unsigned char Len,unsigned char COM_No)
{
	unsigned char* ComBuf;        
	unsigned char* ComSendLen;
		                              
	ComBuf = CommPara[COM_No].Buf;
	ComSendLen = BlockCommPara[COM_No].SendLen;		
	
	*(ComBuf+Len-3) = ')';	
	*(ComBuf+Len-2) = 0xd;	
	*(ComBuf+Len-1) = 0xa;
	*ComSendLen = Len;
	CalcuBCC(ComBuf,Len,COM_No);	
}

//----------------------
const unsigned char RTCDateTab[]="0.9.2(";
void SendRtcDate(unsigned char COM_No)
{
	unsigned int i;//Buff[15];
	unsigned char* ComBuf; 
	unsigned char tmpbuf[4];
		                                        
	ComBuf = CommPara[COM_No].Buf;              
	
	for(i=0;i<6;i++)
	{
		*(ComBuf+i)=RTCDateTab[i];
	}	
#if 0	
	GetTime();
	_BCD_ASC(ComBuf+6,&Clk.Day[0],3);
#else
	i=Comm.SecPulseCnt/86400;
	i=i%30;
	tmpbuf[0]=Byte_BCD(i);
	
	i=Comm.SecPulseCnt/2592000;
	i=i%12;
	tmpbuf[1]=Byte_BCD(i);
	
	i=Comm.SecPulseCnt/31536000;
	tmpbuf[2]=Byte_BCD(i);
	_BCD_ASC(ComBuf+6,tmpbuf,3);
#endif	
	
	*(ComBuf+13)= *(ComBuf+11);
	*(ComBuf+12)= *(ComBuf+10);
	*(ComBuf+11)= '-';
	*(ComBuf+10)= *(ComBuf+9);
	*(ComBuf+9)= *(ComBuf+8);
	*(ComBuf+8)= '-';

//	Comm.Buf[14]= ')';
//	Comm.Buf[15]= 0xd;
//	Comm.Buf[16]= 0xa;
//	Comm.SendLen= 0x11;
//	CalcuBCC(&Comm.Buf[0],17);	
	SendCRLFBCC(17,COM_No);//SendCRLFBCC(&Comm.Buf[14],17);	
}

//----------------------
const unsigned char  ZECTab[]="1.8.0";
void SendZEC(unsigned char COM_No)
{
	unsigned char i,y;
	unsigned char* ComBuf; 
	unsigned char* ComBuf2;  	                     
	unsigned char* ComBlockNo;
			                                        
	ComBuf = CommPara[COM_No].Buf;	
	ComBuf2 = CommPara[COM_No].Buf2;
	ComBlockNo = BlockCommPara[COM_No].BlockNo;
		
	for(i=0;i<5;i++)
	{
		*(ComBuf+i)=ZECTab[i];
	}


	i =(*ComBlockNo - 7);
	y = 5+i;
	if(i > 0) 
	{
		*(ComBuf+0) += 1;	
		i = i-1;
	//	Long_BCD4(ComBuf2+6*y,Para.Pn0);
		RAM_Write(ComBuf2+6*y,Para.Pn0,6);
	}
	else
	{
	//	Long_BCD4(ComBuf2+6*y,Para.Pp0);
		RAM_Write(ComBuf2+6*y,Para.Pp0,6);
	}
	*(ComBuf+4) += i;	
	SendECComm( ComBuf2+6*y,0,1,COM_No);	
}
//----------------------
void SendECComm(unsigned char *Point,unsigned char Numb, unsigned char COM_Mode, unsigned char COM_No)
{
//	unsigned char i,Buff[20];
	unsigned char Buff[20];
	unsigned char* ComBuf;
	
	ComBuf = CommPara[COM_No].Buf;	
			
	*(ComBuf+5+Numb)='(';
	_BCD_ASC(Buff,Point,6);
#if 0	
	Buff[12]=Buff[11];
	Buff[11]=Buff[10];
	Buff[10]=Buff[9];
	Buff[9]='.';
#else
	Buff[12]=Buff[11];
	Buff[11]=Buff[10];
	Buff[10]=Buff[9];
	Buff[9]=Buff[8];
	Buff[8]='.';
#endif	

//	if(Para.RDisDigitNum == 0)   //13.2.2wwl 电量返回同液晶显示
//		i = 0;
//	else
//		i = 1;
//	if( Para.RDisDigitNum > 3)
//		Para.RDisDigitNum = 3;
//	
//	RAM_Write(ComBuf+6,&Buff[2+ Para.RDisDigitNum], i+7);	
//	
//	if(SM.TestCnt)
//	{
//		RAM_Write(ComBuf+6,&Buff[5], 8);	//进入TEST模式，读出电量4 integrated+3 decimal
//		i=1;
//	}

/*
	RAM_Write(ComBuf+6+Numb,&Buff[2], 11);	
	if(COM_Mode == 1)
	{	
		*(ComBuf+17+Numb)='*';	
		*(ComBuf+18+Numb)='k';
		*(ComBuf+19+Numb)='W';
		*(ComBuf+20+Numb)='h';	
		SendCRLFBCC(24+Numb,COM_No);//SendCRLFBCC(&Comm.Buf[i+4],i+7 );	
	
	}else{
		*(ComBuf+17+Numb)='*';	
		*(ComBuf+18+Numb)='k';
		*(ComBuf+19+Numb)='v';
		*(ComBuf+20+Numb)='a';
		*(ComBuf+21+Numb)='r';	
		*(ComBuf+22+Numb)='h';		
		SendCRLFBCC(26+Numb,COM_No);//SendCRLFBCC(&Comm.Buf[i+4],i+7 );		
		
	}	
*/
/*
	RAM_Write(ComBuf+6+Numb,&Buff[2], 9);	//0000000.0
	if(COM_Mode == 1)
	{	
		*(ComBuf+15+Numb)='*';	
		*(ComBuf+16+Numb)='k';
		*(ComBuf+17+Numb)='W';
		*(ComBuf+18+Numb)='h';	
		SendCRLFBCC(22+Numb,COM_No);//SendCRLFBCC(&Comm.Buf[i+4],i+7 );	
	
	}
	else
	{
		*(ComBuf+15+Numb)='*';	
		*(ComBuf+16+Numb)='k';
		*(ComBuf+17+Numb)='v';
		*(ComBuf+18+Numb)='a';
		*(ComBuf+19+Numb)='r';	
		*(ComBuf+20+Numb)='h';		
		SendCRLFBCC(24+Numb,COM_No);//SendCRLFBCC(&Comm.Buf[i+4],i+7 );		
		
	}	
*/	

	RAM_Write(ComBuf+6+Numb,&Buff[2], 11);	//0000000.000
	if(COM_Mode == 1)
	{	
		*(ComBuf+17+Numb)='*';	
		*(ComBuf+18+Numb)='k';
		*(ComBuf+19+Numb)='W';
		*(ComBuf+20+Numb)='h';	
		SendCRLFBCC(24+Numb,COM_No);//SendCRLFBCC(&Comm.Buf[i+4],i+7 );	
	
	}
	else
	{
		*(ComBuf+17+Numb)='*';	
		*(ComBuf+18+Numb)='k';
		*(ComBuf+19+Numb)='v';
		*(ComBuf+20+Numb)='a';
		*(ComBuf+21+Numb)='r';	
		*(ComBuf+22+Numb)='h';		
		SendCRLFBCC(26+Numb,COM_No);//SendCRLFBCC(&Comm.Buf[i+4],i+7 );		
		
	}		
}
//----------------------
void MoveKWToRAM(unsigned char* Dest,unsigned char mun)
{
	*Dest = '.';
	*(Dest + mun) = '*';
	*(Dest + mun + 1) = 'k';
	*(Dest + mun + 2) = 'W';
	
}
//----------------------
void MoveKvarToRAM(unsigned char* Dest,unsigned char mun)
{
	*Dest = '.';
	*(Dest + mun) = '*';
	*(Dest + mun + 1) = 'k';
	*(Dest + mun + 2) = 'v';
	*(Dest + mun + 3) = 'a';
	*(Dest + mun + 4) = 'r';
	
}

const unsigned char MaxDemTab[]="15.6.0(";
//const unsigned char MaxDemTab[]="1.6.0.0(";
//const unsigned char MaxDemTab[]="1.6.0(";
void SendMaxDemand(unsigned char COM_No)
{
}



//const unsigned char PowerTab[]="1.7.0(";
//const unsigned char PowerTab[]="15.4.0(";
const unsigned char PowerTab[]="15.7.0(";
void SendPower(unsigned char COM_No)
{
	unsigned char i,Buff[5];
	unsigned char* ComBuf;          	
	
	ComBuf = CommPara[COM_No].Buf;	

	for(i=0;i<7;i++)
	{
		*(ComBuf+i)=PowerTab[i];
	}
	RAM_Write(Buff,Para.Pt,3);

	_BCD_ASC((ComBuf+7),Buff,3);
	*(ComBuf+12)=*(ComBuf+11);
	*(ComBuf+11)=*(ComBuf+10);
	*(ComBuf+10)=*(ComBuf+9);

	MoveKWToRAM((ComBuf+9),4);
	SendCRLFBCC(19,COM_No);
}

//----------------------
const unsigned char SyJsDateTab[]="0.1.2(";
void SendSyBillingTimeDate(unsigned char COM_No)
{
//	unsigned char i,y,Buff[20];
	unsigned char i,Buff[20];
	unsigned char* ComBuf;          
//	unsigned char* ComBlockNo;
	
	ComBuf = CommPara[COM_No].Buf;	
//	ComBlockNo = BlockCommPara[COM_No].BlockNo;

	for(i=0;i<6;i++)
		{*(ComBuf+i)=SyJsDateTab[i];}
	
	Mon_Read(Buff,1,6,0);
	_BCD_ASC(&Buff[8],Buff,6);
	
	*(ComBuf+6)=Buff[8];
	*(ComBuf+7)=Buff[9];
	*(ComBuf+8)= '-';
	*(ComBuf+9)=Buff[10];
	*(ComBuf+10)=Buff[11];
	*(ComBuf+11)= '-';
	*(ComBuf+12)=Buff[12];
	*(ComBuf+13)=Buff[13];
	*(ComBuf+14)= ' ';
	*(ComBuf+15)=Buff[14];
	*(ComBuf+16)=Buff[15];
	*(ComBuf+17)= ':';
	*(ComBuf+18)=Buff[16];
	*(ComBuf+19)=Buff[17];
	*(ComBuf+20)= ':';
	*(ComBuf+21)=Buff[18];
	*(ComBuf+22)=Buff[19];
	SendCRLFBCC(26,COM_No);//SendCRLFBCC(&Comm.Buf[23],26);
	
}

const unsigned char PowerABSTab[]="15.5.0(";
void SendPowerABS(unsigned char COM_No)
{

}



//----------------------
const unsigned char  VoltageTab[]="32.7.0(";

void SendVoltageA(unsigned char COM_No)
{
	unsigned char i,y;
	unsigned char* ComBuf;                     
	unsigned char* ComBlockNo;
	                                           
	ComBuf = CommPara[COM_No].Buf;	
	ComBlockNo = BlockCommPara[COM_No].BlockNo;


#if ( Threephase == YesCheck ) //三相	
	y = (*ComBlockNo - 9);	//2010.4.10
#else
	y = (*ComBlockNo - 32);	//2010.4.10
#endif


	for(i=0;i<7;i++)
	{
		*(ComBuf+i)=VoltageTab[i];
	}
	*ComBuf += (2*y);	
	SendVolComm((unsigned char*)&Para.Ua+(4*y),COM_No);
}

//----------------------
void SendVolComm(unsigned char *Ptr,unsigned char COM_No)
{
	unsigned char Buff[10];
	unsigned char* ComBuf; 
	
	ComBuf = CommPara[COM_No].Buf;	

#if ( Threephase == YesCheck ) //三相	
	_BCD_ASC(Buff,Ptr,3);			//230.0
	RAM_Write(ComBuf+7,&Buff[1],3);
	*(ComBuf+10)='.';
	*(ComBuf+11)=Buff[4];	
	*(ComBuf+12)=Buff[5];
	//*(ComBuf+10)='.';
	//*(ComBuf+11)=Buff[5];
	*(ComBuf+13)='*';
	*(ComBuf+14)='V';
#else

	_BCD_ASC(Buff,Ptr,3);			//230.0
	RAM_Write(ComBuf+7,&Buff[0],3);		
	*(ComBuf+10)='.';
	*(ComBuf+11)=Buff[3];
//	*(ComBuf+10)=Buff[5];
	*(ComBuf+12)='*';
	*(ComBuf+13)='V';
#endif
	
	SendCRLFBCC(18,COM_No);
}

//----------------------
const unsigned char  CurrentTab[]="31.7.0(";

void SendCurrentA(unsigned char COM_No)
{
	unsigned char i,y;
	unsigned char* ComBuf;                     
	unsigned char* ComBlockNo;	                                           

	ComBuf = CommPara[COM_No].Buf;	
	ComBlockNo = BlockCommPara[COM_No].BlockNo;	
	
#if ( Threephase == YesCheck ) //三相	
	y = (*ComBlockNo - 12);	//2010.4.10
//	y = (*ComBlockNo - 17)/3;	//2010.4.10	
#else
	y = (*ComBlockNo - 33);	//2010.4.10
#endif

	for(i=0;i<7;i++)
	{
		*(ComBuf+i)=CurrentTab[i];
	}
	
	*ComBuf += (2*y); 
	SendCurComm((unsigned char*)&Para.Ia + (4*y),COM_No);
}

//----------------------
void SendCurComm(unsigned char *Ptr,unsigned char COM_No)
{
	unsigned char Buff[10];
	unsigned char* ComBuf;                     
	                                           
	ComBuf = CommPara[COM_No].Buf;	
#if ( Threephase == YesCheck ) //三相	
	_BCD_ASC(Buff,Ptr,4);			//00.00
	RAM_Write(ComBuf+7,&Buff[3],2);		
	*(ComBuf+9)='.';
	RAM_Write(ComBuf+10,&Buff[5],2);		
	*(ComBuf+12)='*';
	*(ComBuf+13)='A';
	SendCRLFBCC(17,COM_No);
#else
	_BCD_ASC(Buff,Ptr,4);			//00.00
	RAM_Write(ComBuf+7,&Buff[2],2);		
	*(ComBuf+9)='.';
	RAM_Write(ComBuf+10,&Buff[4],2);		
	*(ComBuf+12)='*';
	*(ComBuf+13)='A';
	SendCRLFBCC(17,COM_No);
	
#endif
}

const unsigned char  FreqTab[]="14.7.0(";

void SendFreq(unsigned char COM_No)
{	
	unsigned char Buff[10];
	unsigned char i;	
	unsigned char* ComBuf;
#if 0	
	unsigned long Data;
#endif                                         
	ComBuf = CommPara[COM_No].Buf;	
	
	for(i=0;i<7;i++)
	{
		*(ComBuf+i)=FreqTab[i];
	}
#if 0	
	Data = Para.Freq[1];
	Data = (Data<<8) | Para.Freq[0];
	Data /=10; 
	Word_BCD(Buff+6,Data);
	_BCD_ASC(Buff,(unsigned char*)Buff+6,2);
#endif	
	_BCD_ASC(Buff,(unsigned char*)&Para.Freq,2);
	RAM_Write(ComBuf+7,&Buff[0],2);		
	*(ComBuf+9)='.';
	RAM_Write(ComBuf+10,&Buff[2],2);	
	*(ComBuf+12)='*';
	*(ComBuf+13)='H';
	*(ComBuf+14)='z';	
	SendCRLFBCC(18,COM_No);
}




const unsigned char SendVFailObis[]="C.7.0(";

void SendVFail(unsigned char COM_No)
{
	
}




const unsigned char SendVFailAllTimeObis[]="C.7.10*00(";

void SendVFailAllTime(unsigned char COM_No)
{
	
}



//const unsigned char SendEventCntObis[]="C.53.1(";
const unsigned char SendEventCntObis[]="C.51.1(";

void SendEventCnt(unsigned char COM_No)
{
	
}


//const unsigned char SendEventDurationTimeObis[]="C.53.1(";
const unsigned char SendEventDurationTimeObis[]="C.51.1(";

void SendEventDurationTime(unsigned char COM_No)
{

}
//----------------------



const unsigned char SendLastProgObis[]="C.2.1(";

void SendLastProgTime(unsigned char COM_No)
{

}

const unsigned char BillingCounterTab[]="0.1.0(";

void SendBillingCounter(unsigned char COM_No)
{
//	unsigned char i,y,Qx,Buff[5];
	unsigned char i,Buff[5];
	unsigned char* ComBuf;          
//	unsigned char* ComBlockNo;
	
	ComBuf = CommPara[COM_No].Buf;	
//	ComBlockNo = BlockCommPara[COM_No].BlockNo;
	
	for(i=0;i<6;i++)
		{*(ComBuf+i)=BillingCounterTab[i];}
//	RAM_Fill(Buff, 1 );

	E2P_RData( Buff, JsCount , 1);
	_BCD_ASC((ComBuf+6),Buff,1);

	SendCRLFBCC(11,COM_No);//SendCRLFBCC(&Comm.Buf[17],20);	

}



//----------------------
const unsigned char  DqKGCSTab[]="C.51(";

void SendDqKGcs(unsigned char COM_No)
{
	unsigned char i,Buff[10],y;
	unsigned char* ComBuf;          
	unsigned char* ComBlockNo;	    
	                            
	ComBuf = CommPara[COM_No].Buf;	
	ComBlockNo = BlockCommPara[COM_No].BlockNo;	
	
#if (Threephase == NoCheck) 	
//	y = (Comm.BlockNo - 24)/2;//y = (Comm.BlockNo - 18)/2;
//	y = (Comm.BlockNo - 19)/2;	//2010.4.10
	y = (*ComBlockNo - 19)/2;	//2010.4.10
#else
//	y = (Comm.BlockNo - 28)/2;
//	y = (Comm.BlockNo - 23)/2;	//2010.4.10
	y = (*ComBlockNo - 23)/2;	//2010.4.10
#endif	
	for(i=0;i<5;i++)
	{
		*(ComBuf+i)=DqKGCSTab[i];
	}	
	
	*(ComBuf+3) += y;	
	
	_BCD_ASC(ComBuf+5,Buff,6);	
	
	SendKGDMAGComm(COM_No);
}

//-----------------------------
void SendKGDMAGComm(unsigned char COM_No)
{
	unsigned char* ComBuf;          
	                            
	ComBuf = CommPara[COM_No].Buf;	
	
	*(ComBuf+18) = *(ComBuf+16);
	*(ComBuf+17) = *(ComBuf+15);	
	*(ComBuf+16) = *(ComBuf+14);	
	*(ComBuf+15) = *(ComBuf+13);	
	*(ComBuf+14) = *(ComBuf+12);	
	*(ComBuf+13) = *(ComBuf+11);	
	*(ComBuf+12) = *(ComBuf+10);	
	*(ComBuf+11) = *(ComBuf+9);	
	*(ComBuf+10) = *(ComBuf+8);		
	*(ComBuf+9) = *(ComBuf+7);		
	*(ComBuf+8) = '(';
	*(ComBuf+7) = ')';
	
	SendCRLFBCC(22,COM_No);//SendCRLFBCC(&Comm.Buf[19],22);	
}


//----------------------
const unsigned char  BatWorkObis[]="C.6.0(";

void SendBatWorkTM(unsigned char COM_No)
{
	unsigned char i,Buff[10];
	unsigned char* ComBuf;          
	                                
	ComBuf = CommPara[COM_No].Buf;	

	for(i=0;i<6;i++)
	{
		*(ComBuf+i)=BatWorkObis[i];
	}
	
	E2P_RData( Buff, BatteryWorkTime, 4);
	_BCD_ASC(ComBuf+6,Buff,4);	
	RAM_Write(ComBuf+6, ComBuf+9, 5);
	*(ComBuf+11) = '*';
	*(ComBuf+12) = 'h';	
	SendCRLFBCC(16,COM_No);
} 


/*
//----------------------
const unsigned char  BatWorkObis[]="C.6.0(";

void SendBatWorkTM(unsigned char COM_No)
{
	unsigned char i,Buff[10];
	unsigned char* ComBuf;          
	                                
	ComBuf = CommPara[COM_No].Buf;	

	for(i=0;i<6;i++)
	{
		*(ComBuf+i)=BatWorkObis[i];
	}
	
	E2P_RData( Buff, BatteryWorkTime, 5);
	_BCD_ASC(ComBuf+6,Buff,5);	
	
	SendCRLFBCC(19,COM_No);//SendCRLFBCC(&Comm.Buf[16],19);
}  */
//----------------------
#if ( Threephase == YesCheck ) //三相		
const unsigned char ConsTab[]=
{'0','.','3','.','0','(','1','0','0','0','0','*','i','m','p',0x5c,'k','W','h',')',0xd,0xa};
#else
const unsigned char ConsTab[]=
{'0','.','3','.','0','(','1','0','0','0','0','*','i','m','p',0x5c,'k','W','h',')',0xd,0xa};
#endif

void SendConstant(unsigned char COM_No)
{
	unsigned char i;
	unsigned char* ComBuf;        
	unsigned char* ComSendLen;
//	unsigned int constLed;
		                              
	ComBuf = CommPara[COM_No].Buf;
	ComSendLen = BlockCommPara[COM_No].SendLen;

#if ( Threephase == YesCheck ) //三相	
	
	for(i=0;i<22;i++)
		{*(ComBuf + i)=ConsTab[i];}
	/*constLed=SM.Constled;
	*(ComBuf+7)=(constLed/10000)+'0';
	constLed%=10000;
	*(ComBuf+8)=(constLed/1000)+'0';
	constLed%=1000;
	*(ComBuf+9)=(constLed/100)+'0';
	constLed%=100;
	*(ComBuf+10)=(constLed/10)+'0';
	constLed%=10;
	*(ComBuf+11)=(constLed)+'0';*/

	*ComSendLen = 22;
	CalcuBCC(ComBuf,22,COM_No);		
#else

	for(i=0;i<22;i++)
		{*(ComBuf + i)=ConsTab[i];}
	*ComSendLen = 22;
	CalcuBCC(ComBuf,22,COM_No);	
#endif
}



#if ( Threephase == YesCheck ) //三相		
const unsigned char VerTab[]=
//{'0','.','2','.','1','(','Z','E','3','1','2','.','v','0','6',',',' ','1','5','0','5','0','8',',',' ',CRCRead1,CRCRead2,CRCRead3,CRCRead4,')',0xd,0xa};
//{'0','.','2','.','1','(','Z','E','3','1','2','.','v','1','2',',',' ','1','5','0','7','1','4',',',' ',CRCRead1,CRCRead2,CRCRead3,CRCRead4,')',0xd,0xa};
//{'0','.','2','.','1','(','Z','E','3','1','4','.','v','0','8',',',' ','1','6','0','6','2','0',',',' ',CRCRead1,CRCRead2,CRCRead3,CRCRead4,')',0xd,0xa};
{'0','.','2','.','0','(','v','0','1',',',' ','1','7','1','1','2','7',',',' ',CRCRead1,CRCRead2,CRCRead3,CRCRead4,')',0xd,0xa};
//{'0','.','2','.','1','(','Z','E','3','1','2','.','v','7','6','_','1','6','8',')',0xd,0xa};
#else
const unsigned char VerTab[]=
//{'0','.','2','.','1','(','Z','E','1','1','4','.','v','0','6',',',' ','1','5','0','5','0','8',',',' ',CRCRead1,CRCRead2,CRCRead3,CRCRead4,')',0xd,0xa};
//{'0','.','2','.','1','(','Z','E','1','1','4','.','v','0','7',',',' ','1','5','0','7','1','4',',',' ',CRCRead1,CRCRead2,CRCRead3,CRCRead4,')',0xd,0xa};
{'0','.','2','.','1','(','Z','E','1','1','4','.','v','1','4',',',' ','1','6','0','7','1','2',',',' ',CRCRead1,CRCRead2,CRCRead3,CRCRead4,')',0xd,0xa};
//{'0','.','2','.','1','(','Z','E','1','1','4','.','v','7','2','_','0','6','8',')',0xd,0xa};
#endif	


 extern const uint8_t firmware_version[];
void SendVersion(unsigned char COM_No)
{
	unsigned char i;
	unsigned char* ComBuf;        
	unsigned char* ComSendLen;
		                              
	ComBuf = CommPara[COM_No].Buf;
	ComSendLen = BlockCommPara[COM_No].SendLen;	

	for(i=0;i<26;i++)
	{
		*(ComBuf+i)=VerTab[i];
	}
	memcpy(ComBuf+7,firmware_version,2);
	_BCD_ASC( ComBuf+19, SM.CPUCRC, 2 );
	*ComSendLen = 26;
	CalcuBCC(ComBuf,26,COM_No);
}
const unsigned char CRCMTab[]="F.F.1(12341234)\r\n";
void SendCRC_M(unsigned char COM_No)
{
	unsigned char i;
	unsigned char* ComBuf;        
	unsigned char* ComSendLen;
		                              
	ComBuf = CommPara[COM_No].Buf;
	ComSendLen = BlockCommPara[COM_No].SendLen;	

	for(i=0;i<17;i++)
	{
		*(ComBuf+i)=CRCMTab[i];
	}
	_BCD_ASC( ComBuf+6, SM.CPUCRC_M, 2 );
	_BCD_ASC( ComBuf+10, SM.CPUCRC, 2 );
	*ComSendLen = 17;
	CalcuBCC(ComBuf,17,COM_No);
}

const unsigned char SerialTab[]="0.0.1(0123456789ABCDEF)\r\n";
void SendSerial(unsigned char COM_No)
{
	unsigned char i;
	unsigned char* ComBuf;        
	unsigned char* ComSendLen;
		                              
	ComBuf = CommPara[COM_No].Buf;
	ComSendLen = BlockCommPara[COM_No].SendLen;	

	for(i=0;i<6;i++)
	{
		*(ComBuf+i)=SerialTab[i];
	}
	RAM_Fill(ComBuf+6,19);
	E2P_RData( ComBuf+6, Serial_No, 16 );
	for(i=6;i<25;++i)
	{
		if(ComBuf[i]==0)
			break;
	}
	*(ComBuf+i) = ')';
	*(ComBuf+i+1) = '\r';
	*(ComBuf+i+2) = '\n';
	*ComSendLen = i+3;
	CalcuBCC(ComBuf,*ComSendLen,COM_No);
}



const unsigned char TariNamObis[]="0.2.2(";

void SendTariName(unsigned char COM_No)
{

}

//----------------------
//const unsigned char  Lable1Tab[]=
//{'0','.','2','.','0','(','0','9','1','2','0','3','1',
// '4','x',CRCRead1,CRCRead2,CRCRead3,CRCRead4,')',0xd,0xa}; 
const unsigned char  Lable1Tab[]=
{'0','.','2','.','0','(',CRCRead1,CRCRead2,CRCRead3,CRCRead4,')',0xd,0xa}; 
void SendLable1(unsigned char COM_No)
{
	unsigned char i;
	unsigned char* ComBuf;
	unsigned char* ComSendLen;
	
	ComBuf = CommPara[COM_No].Buf;
	ComSendLen = BlockCommPara[COM_No].SendLen;

	for(i=0;i<14;i++)
	{
		*(ComBuf+i)=Lable1Tab[i];
	}
	
//	_BCD_ASC( ComBuf+6, SM.CPUCRC, 2 );
	
	*ComSendLen= 13;
	CalcuBCC(ComBuf,13,COM_No);		
}


//----------------------
const unsigned char  BlockEndTab[]={'!',0xd,0xa,0x03};
void SendBCC(unsigned char COM_No) 
{
	unsigned char i;
	unsigned char* ComBuf;
	unsigned char* ComBcc;
	unsigned char* ComSendLen;
		
	ComBuf = CommPara[COM_No].Buf;
	ComBcc = CommPara[COM_No].Bcc;
	ComSendLen = BlockCommPara[COM_No].SendLen;
			
	for(i=0;i<4;i++)
	{
		*(ComBuf+i)=BlockEndTab[i];
	}	
		
	CalcuBCC(ComBuf,4,COM_No);		
	*(ComBuf+4)=*ComBcc;
	*ComSendLen= 0x05;
}

//====================================
#if ( Threephase == YesCheck ) //三相13.2.27wwl
const unsigned char CommFistString[]=
//{'/','Z','P','A','5','L','K','1','3','B','O','4','0','2','0','0','7',0x0D,0x0A};//2012.12.29
//{'/','Z','P','A','5','Z','E','3','1','4','.','v','1','0',0x0D,0x0A};
//{'/','Z','P','A','5','Z','E','3','1','4','.','v','1','0',0x0D,0x0A};
//{'/','Z','P','A','5','Z','E','3','1','2','.','v','8','9','_','1','2','8',0x0D,0x0A};
//{'/','Z','P','A','5','Z','E','3','1','4','.','v','5','2','_','0','8','8',0x0D,0x0A};
{'/','L','O','G','5','L','K','3','3','B','M','1','0','1','0','0','1',0x0D,0x0A};
#elif ( SinglePhase == YesCheck )
const unsigned char CommFistString[]=
//{'/','L','O','G','5','L','K','1','1','B','L','4','0','2','0','0','8',0x0D,0x0A};//2013.2.27wwl
//{'/','Z','P','A','5','Z','E','1','1','4','.','v','1','0',0x0D,0x0A};
{'/','Z','P','A','5','Z','E','1','1','4','.','v','5','1','_','0','7','8',0x0D,0x0A};
#endif
short CommModeRec(unsigned char COM_No)
{
	unsigned char Buff[16];
	unsigned char* Point;
	unsigned char XorCheck;
	short CheckAds;
	short i;
	u32	ClkDiv1;

	unsigned char* ComBuf;
	unsigned char* ComMode;
	unsigned char* ComPtr;
	unsigned char* ComRun;
	unsigned char* ComState;
	unsigned char* ComBcc;
	unsigned char* ComBlockNo;
	unsigned char* ComSendLen;
	unsigned char* ComRecTmr;
	
	ComBuf = CommPara[COM_No].Buf;
	ComMode = CommPara[COM_No].Mode;
	ComPtr = CommPara[COM_No].Ptr;
	ComRun = CommPara[COM_No].Run;
	ComState = CommPara[COM_No].State;
	ComBcc = CommPara[COM_No].Bcc;
	ComRecTmr = CommPara[COM_No].RecTmr;
	ComBlockNo = BlockCommPara[COM_No].BlockNo;
	ComSendLen = BlockCommPara[COM_No].SendLen;
		
	Point = Buff;
	*ComBlockNo=0x0;
	
	switch( *ComState )
	{
		case 1: 
				if( *(ComBuf+2) != EndCode )
				{
					if(( *(ComBuf+1) != 0x3F ) || ( *(ComBuf+12) != LF ) || ( *(ComBuf+10) != EndCode ) || ( *(ComBuf+11) != CR ))  
					{ 
						CommInit(COM_No); 
						return 0; 
					}
				}
				else
				{
					if(( *(ComBuf+1) != 0x3F ) || ( *(ComBuf+4) != LF ) || ( *(ComBuf+2) != EndCode ) || ( *(ComBuf+3) != CR ))  
					{ 
						CommInit(COM_No); 
						return 0; 
					}	
				}
				if( *(ComBuf+2) != EndCode )
				{
					E2P_RData( Point, EMeter_No, 8 );			
					if( Data_Comp( Point, ComBuf+2, 8 ) != 0) 
					{
						CommInit(COM_No);
						return 0;
					}	
				}
				
				if( COM_No == 1 )
				{
					if(Comm.Delay1)	
					{
						return 0;
					}
					Comm.Rdout300bps1=0x0;					
				}
				
				*ComRun |= F_AdsOk;
				
				for(i=0;i<20;i++)
				{
					*(ComBuf+i)=CommFistString[i];
				}	
				
				if((Flag.ClrFlag & F_Metertype_EN) == F_Metertype_EN)	
					E2P_RData( ComBuf+11, Metertype_No, 6 );	
				break;
		case 2: 
				if((( *ComRun & F_AdsOk ) == 0 ) || ( *(ComBuf+4) != CR ) || ( *(ComBuf+5) != LF ) || ( *(ComBuf+2) > 0x37 ) )
				{
					CommInit(COM_No);
					return 0;
				}	
				i = *(ComBuf+2) - 0x30  ;
				switch(COM_No)
				{
					case 1:
						if(Comm.Delay1)	
						{
							return 0;
						}	//延时400ms后,切换波特率	
						
						Serial_Open(1,300*pow(2,i),7,SERIAL_CHECK_EVEN);;										  								
						break;
					default:break;		
				}
	
				switch(*(ComBuf+3))
				{
				case '0':	
				case '9':					
					Comm.RdoutContent[COM_No] = Read0Mode;
					*ComBlockNo=0x4;
					*ComSendLen=0x1;
					*ComBuf = STX;
					*ComBcc=0x0;
					break;
				case '1':
					Buff[0]=Clk.Sec_64;
					Buff[1]=Clk.Sec[0]+Clk.Sec_64;
					_BCD_ASC(ComBuf+5,Buff,2);
					*(ComBuf+0) = SOH;
					*(ComBuf+1) = 0x50;
					*(ComBuf+2) = 0x30;
					*(ComBuf+3) = 0x2;
					*(ComBuf+4) = 0x28;
					*(ComBuf+9) = 0x29;
					*(ComBuf+10) = 0x3;
					GetXorCheck( &XorCheck, &CheckAds,ComBuf);
					*(ComBuf+CheckAds) = XorCheck;
				 *ComSendLen=CheckAds+1;
					break;		
				default:
					CommInit(COM_No);	
					return 0;
				}
				break;		
		case 3:	if(( *ComRun & F_AdsOk ) == 0 ) 
				{
					CommInit(COM_No);
					return 0;
				}	
				if(( *ComBuf == SOH )&& ( *(ComBuf+1) == 'B' ))
				{
					*ComBuf = ACK;
					*ComRun |= F_ComRest;
					break;
				}	
				if( *ComBuf == NAK ) 
				{
					*ComBuf = STX;
					break;	
				}
				 
				if( *ComBuf == ACK )
				{
					CommInit(COM_No);
					return 0;		
				}	 
				if(( GetXorCheck( &XorCheck, &CheckAds,ComBuf) == 0) && ( *(ComBuf+CheckAds) == XorCheck ))
				{
					if( Proc_Comm(COM_No) != 0 ) 
					{       
					        *ComBuf = 0;
//					        CommInit();						//V3.0
							CommRest(COM_No);						//V3.0
							return 0;
					}        
					if( *ComBuf == ACK ) break;
					GetXorCheck( &XorCheck, &CheckAds,ComBuf);
					*(ComBuf+CheckAds) = XorCheck;
						if(*ComSendLen==0)
						{	
							*ComSendLen=CheckAds+1;		
						}
					break;
				}	
				else *ComBuf = NAK;
				break;	
		default: CommInit(COM_No);
				 return 0;
	}
	
	*ComRecTmr = 2;
	(*ComMode)++;
	*ComRun  &= ~F_ComOK; 
	if(Comm.SendLen1==0)
		{
			for(i=0;i<30;i++)
			{
				if(ComBuf[i]==0x0d && ComBuf[i+1]==0x0a)
				{
					i+=2;
					break;
				}
			}
			if(i>29)
				i=0;
			if(ComBuf[0]==STX || ComBuf[0]==ACK)
				i=1;
		}
		else
			i=Comm.SendLen1;
	IEC1107_WRITE(ComBuf,(uint16_t)i);
	Comm.SendLen1=0;
	Comm.FTime1=2;
	Comm.Ptr1 = 0;
	ComBuf[0]=0;
	return 0;
}	

/*	0.正常，含有数据
	1.密码错
	2.通讯编码错
	3.无返回码
*/
#define PassWDError		1
#define	ComCodeError	2
#define NoDataBack		3
const unsigned char FixPasswordcommand[5]=
//{'E','L','1','a','v','e'};
//{'M','A','N','S','P','1'};
{'C','0','8','8','0',};
const unsigned char FixPassword3button[5]=
//{'E','L','1','a','v','e'};
//{'M','A','N','S','P','1'};
{'9','0','0','0','2',};
const unsigned char FixPassword1[6]=
//{'E','L','1','a','v','e'};
//{'M','A','N','S','P','1'};
//{'M','O','N','G','O','5'};
{'L','O','D','Z','M','1'};
const unsigned char FixPassword[6]=
{'a','x','C','f','W','4'};

short Proc_Comm(unsigned char COM_No)
{
	unsigned char Buff[10];
	unsigned char* Point;
	unsigned short i;
  	unsigned char* ComBuf;
  	unsigned char* ComRun;
  	unsigned char* ComPrgTmr;
  
  	ComBuf = CommPara[COM_No].Buf;
  	ComRun = CommPara[COM_No].Run;
  	ComPrgTmr = CommPara[COM_No].PrgTmr;
  		
	Point = Buff;
	switch( *(ComBuf+1) )
	{
		case 'P': 	
					for(i=0;i<6;i++)
					{
						Buff[i]=FixPassword[i];
					}
					if( Data_Comp( ComBuf+5,Point, 6) == 0 )																
					{
						*ComRun |= F_MimaOk0;
//						Comm.Mima[COM_No] = (*(ComBuf+10)-0x30);
						Comm.PassWordErrCnt = 0;
						*ComBuf = ACK;
					}			
					else
					{
						*ComRun &= ~F_MimaOk0;
						*(ComBuf+0) = SOH;			//中止指令
					  *(ComBuf+1) = 0x42;
						*(ComBuf+2) = 0x30;
					  *(ComBuf+3) = 0x3;
						*(ComBuf+4) = 0x71;	
					}	  		
					break;			 
		case 'R':
					if(( *ComRun & F_MimaOk0 ) != 0 ) return Proc_Read(COM_No);		//V2.0				
					else 
						return PassWDError;									//V2.0
		case 'W':
					if(( *ComRun & F_MimaOk0 ))
					{
						*ComPrgTmr = 2; 
						if(SM.ENCount != 0)
							SM.ENCount = 120;        				
						return Proc_Write(COM_No);	
					}	
					return PassWDError;
		case 'E':	
			return Proc_Execute(COM_No);
		default:	
			break;
	}
	return 0;	
}	


//---------------------------------
short Proc_Execute(unsigned char COM_No)
{
	unsigned char Buff[35];
	unsigned char* Point;
//	short	i,Temp,TabMima;
	short	i,Temp;
    unsigned char* ComBuf;
    unsigned char* ComRun;
	
    ComBuf = CommPara[COM_No].Buf;	
    ComRun = CommPara[COM_No].Run;
		
	Point = Buff;
	
	RAM_Write(Point, ComBuf+4, 5);
	
	for( i= 0;i< 1;i++ )
	{
		if( Data_Comp( Point, (unsigned char*)&ExecuteTab[i].ComID1, 4 ) == 0 ) break;	
	}
		
	if(i==1) return ComCodeError;
	
		
	Temp=(unsigned char)ExecuteTab[i].State; //& 0x00ff;
	
	 if(( *ComRun & F_MimaOk0 ) == 0 )
	{	
		return PassWDError;
	 }
	
	switch( Temp )
	{
		case 12: //全屏测试
			E2P_WData(CRCCheck,SM.CPUCRC,2);
		  SM.ErrCode=0;
			break;
		default:
			break;			
	}
	*ComBuf = ACK;
	return 0;	
}
//---------------------------------
short Proc_Read(unsigned char COM_No)
{
	unsigned char Buff[60];
//	unsigned char LoadBuff[LOADLENGTH];
	unsigned char* Point,Length,ReadMode;
	short	i,Temp,TempAddr;
	unsigned char TempAcc;
	unsigned short TempStAddr;	
//	unsigned long TempStAddrFlash;	
	unsigned char* ComBuf;      
	unsigned char* ComBlockNo;
	unsigned char* ComSendLen;
	unsigned char* ComBcc;
 	unsigned char* ComRun;	
	unsigned char* ComProfDate;
	unsigned long* ComLoadPtr,FirsLoadNum;
	unsigned long TempStAddrFlash;	
	long* ComLoadPtrend;


	ComBuf = CommPara[COM_No].Buf;
	ComBcc = CommPara[COM_No].Bcc;	
	ComBlockNo = BlockCommPara[COM_No].BlockNo;
	ComSendLen = BlockCommPara[COM_No].SendLen;
	ComRun = CommPara[COM_No].Run;
	ComLoadPtr = BlockCommPara[COM_No].LoadPtr;
	ComProfDate = BlockCommPara[COM_No].ProfDate;
	ComLoadPtrend = BlockCommPara[COM_No].LoadPtrend;	

	Point = Buff;
	
//	_ASC_BCD( Point, &Comm.Buf[4], 2);
	RAM_Write(Point, ComBuf+4, 5);
	ReadMode=*(ComBuf+2);
	RAM_Write( ComBuf+1, ComBuf+4, 18 );		//移命令，假设最长负荷命令18
	*ComBuf = STX;
	switch( *(ComBuf+1) )
	{
		case '5':	
				for( i=0;i<CPTSumItem;i++ )
				{
					if( Data_Comp( Point, (unsigned char*)&CDParaTab[i].ComID1, 5 ) == 0 ) break;	
				}	
				if( i == CPTSumItem ) return ComCodeError; 					    
			    Length = CDParaTab[i].Len;
				_BCD_ASC( ComBuf+7, (unsigned char*)CDParaTab[i].Addr, Length );
				i = 7 + ( Length * 2 );
				*(ComBuf+i) = ')';
				*(ComBuf+i+1) = ETX;
				break;
		default:
				for( i= 0;i< CPTSumItem;i++ )
				{
					if( Data_Comp( Point, (unsigned char*)&CDParaTab[i].ComID1, 5 ) == 0 ) break;	
				}
					
				if(( i == CPTSumItem ) || (( CDParaTab[i].State & READ ) == 0 )) return ComCodeError; 
				
				Length = CDParaTab[i].Len;
				
				TempAddr = 	CDParaTab[i].Addr;
				
				Temp=(unsigned char)CDParaTab[i].State;
				
				if(((CDParaTab[i].State & 0x0080)!=0) || ((CDParaTab[i].State & 0x0040)!=0)) 
				{					
					switch( Temp )
					{
						case 0x0081:	
								//	Getclk();
									RAM_Write( Point, &Clk.Sec[0], 3);
									*(Point+3)=Clk.Week[0];
									RAM_Write( Point+4, &Clk.Day[0], 3);
									break;
						case 0x0084://calibration
#if ( Threephase == YesCheck ) //三相		
									E2P_RAdj( Point, TempAddr, Length );
									SwapWord( Point, 3 );
#elif ( SinglePhase == YesCheck )									
									E2P_RAdj( Point, TempAddr, Length );
#endif
									break;					
						case 0x0083 :
							//if(CDParaTab[i].ComID5 =='2') __NOP();
							E2P_RData( Point, CDParaTab[i].Addr, Length );
							Cm_Ram_Inter(Point,Length);
							break;		
						case 0x0085:
							E2P_RData( Point+30, CDParaTab[i].Addr, Length ); 
						  RAM_WriteInter(Point,Point+30,Length);
							break;
						case 0x0089 :
							E2P_RAdj( Point, CDParaTab[i].Addr, Length );
							break;	
						case 0x008b:
							RAM_Write(Point,(unsigned char *)&Comm.SecPulseCnt,4);
							break;
						case 0x0082:
							RAM_Write(Point,(unsigned char *)&SM.day_no,2);
							break;
								
						case 0x0040://read out CRC			
									RAM_Write( Point, SM.CPUCRC, 2 );
									RAM_Write( Point+2, SM.CPUCRC_M, 2 );
									break;
						case 0x0041:	
								RAM_Write( Point, (unsigned char*)(&Para.Ua + TempAddr*4),4);
								break;	
						case 0x0042:
								RAM_Write(Point, Flag.AlarmFlg ,4);
								if(( PIN_KEYPR& P_KEYPR) == 0) 	
									*(Point+1)  |= 0x80;		// *Point |= 0x80;	
								else
									*(Point+1)  &= ~0x80;		// *Point |= 0x80;	
									
								*(Point+2) = 0x00;
								if((PIN_KGJC & P_KGJC) == 0)	
									*(Point+2)  |= 0x01;		// *Point |= 0x01;
								if((PIN_KDJC & P_KDJC) == 0)
									*(Point+2)  |= 0x02;		// *Point |= 0x02;	
//								if(( PIN_SETEN & P_SETEN ) == 0) 	
//									*(Point+2)  |= 0x04;		// *Point |= 0x04;	
//								if(( PIN_FLQH & P_FLQH ) == 0) 	
//									*(Point+2)  |= 0x08;		// *Point |= 0x08;					
								if(( PIN_SETEN & P_SETEN ) == 0) 	
									*(Point+2)  |= 0x10;		// *Point |= 0x10;											
								if(( PIN_CCJC& P_CCJC) == 0) 	
									*(Point+2)  |= 0x20;		// *Point |= 0x20;	
//								if(( PIN_KEYSF& P_KEYSF) == 0) 	
//									*(Point+2)  |= 0x40;		// *Point |= 0x40;	
								if(( PIN_KEYXF& P_KEYXF) == 0) 	
									*(Point+2)  |= 0x80;		// *Point |= 0x80;			
								break;	
						case 0x0043:
							//	RAM_Write( Point+2, SM.CPUCRC_C, 2 );
							//	ParameterBCC();
							//	RAM_Write( Point, Comm.ParameterBcc, 2 );	
									RAM_Write( Point, (unsigned char*)&Para.meter_sts,4);						
								break;		
						default:  	
								E2P_RData( Point, CDParaTab[i].Addr, Length ); 
								break;
					}
					_BCD_ASC( ComBuf+7, Point, Length );	
					TempAcc = 7 + ( Length * 2 );
					*(ComBuf+TempAcc) = ')';
					*(ComBuf+TempAcc+1) = ETX;
				}	
				else if((CDParaTab[i].State & 0x0020)!=0)
				{
					switch( Temp )
					{
						case 0x0021:
									E2P_RData( ComBuf+7, CDParaTab[i].Addr, Length );
									i = 7+Length;
									break;
						case 0x0022:
									E2P_RData( ComBuf+7, CDParaTab[i].Addr, Length );
									i = 7+Length;
									break;
						case 0x0023:
									E2P_RData( ComBuf+7, CDParaTab[i].Addr, Length );
									i = 7+Length;
									break;									
						case 0x0024:	
						case 0x0025:	
									E2P_RData( Point, CDParaTab[i].Addr, Length );
									_BCD_ASC( ComBuf+7, Point,4);
									RAM_Write(ComBuf+15, Point+4 , 4);
									i = 19;
									break;
						case 0x0026:	
							if((Flag.ClrFlag & F_Metertype_EN) == F_Metertype_EN)	
							{
								E2P_RData( ComBuf+7, CDParaTab[i].Addr, Length );
								i = 13;
							}
							else
							{
								i = 7;									
							}
							break;	
						case 0x0027:
							_ASC_BCD((unsigned char*)&TempStAddr, ComBuf+7, 2 );		
							if(TempAddr==0x0000)//外部E方
							{
#if ( Threephase == YesCheck ) //三相	
								E2PRead( Point, TempStAddr, Length, DataEAds );
#else
								E2PRead( Point, TempStAddr, Length, DataEAds );
#endif			
							}
							else//内部E方
							{
								for(i=0;i<Length;i++)
								{
									*(Point+i) = *(Read_EEPROM + TempStAddr + i);
								}	
							}
							_BCD12_ASC3132(ComBuf+7, Point, Length );																	
							i = 7 + ( Length * 2 );				
							break;	
						case 0x0028:	
							for(i=7;i<18;i++)
							{
								*(ComBuf+i)=VerTab[i-1];
							}
							memcpy(ComBuf+8,firmware_version,2);
							i = 18;	
							break;				
						default:  	
							E2P_RData( Point, CDParaTab[i].Addr, Length );
							RAM_Write(ComBuf+7,Point, Length );
							i=7+Length;	
							break;
					}
					for(Length=7;Length<i;++Length)
					{
						if(*(ComBuf+Length)==0)
							break;
					}
					i=Length;
					*(ComBuf+i) = ')';
					*(ComBuf+i+1) = ETX;
				}
	}				
	return 0;	
}	

short Proc_Write(unsigned char COM_No)
{
	unsigned char Buff[80],Length;
	unsigned char* Point;
	unsigned char Temp;
	unsigned short i,j,TempAddr;
	unsigned char* ComBuf;                     	
	uint32_t tmp;
	ComBuf = CommPara[COM_No].Buf;
	Point = Buff;
	RAM_Write( Point, ComBuf+4, 5);

	for( i= 0; i< CPTSumItem; i++ )
	{
		if( Data_Comp( Point, (unsigned char*)&CDParaTab[i].ComID1, 5 ) == 0 ) 
			break;	
	}	
	if( i == CPTSumItem )
		return ComCodeError;
	else	
	{
		if(( CDParaTab[i].State & WRITE )!= 0)
		{
        	Temp=(unsigned char)CDParaTab[i].State; //& 0x00ff;
        	if((CDParaTab[i].State & 0x0080)!=0)   //0x008X
					{
						if(Temp == 0x8C)//设置显示项
						{
							for( j= 0; j< 60; j+=2 )
							{
								if((*(ComBuf+10+j) == 0x46)&&(*(ComBuf+11+j) == 0x46))
									break;	
							}	
							if(j < 60)
								RAM_DataFill(ComBuf+10+j , 60-j, 0x46);
						}

        		Length = CDParaTab[i].Len;	
        		TempAddr = 	CDParaTab[i].Addr;
		        _ASC_BCD( Point, ComBuf+10, Length );	
				

		        switch( Temp )
		        {
			    	case 0x0081:
			    				//*(Point+3) = 1;
			    				if(( TimeValueCheck( Point ) != 0 )||( DateValueCheck( Point+3 ) != 0 )) 
			    					return ComCodeError;
								
//								TamperRecord(0x10);//记录修改前时间
								
			    					RAM_Write( &Clk.Sec[0],Point,3);
			    					RAM_Write( &Clk.Day[0],Point+4,3);
								Clk.Week[0] = WeekDay20( Clk.Day );
								
								RAM_Write( Buff,Point,3);
								Buff[3]=Clk.Week[0];
								RAM_Write( &Buff[4],Point+4,3);
																
								fnSysClock_Write(&Clk.Sec[0]);
		
								
								ProShiftFlag();	//处理冬夏令时标志
								
//								MonData_Save(&Clk.Sec[0]);//当前时间作为结算时间
//								E2P_WData( Last_Mon_Tm, &Clk.Hour[0], 2 );
								E2P_WData( Last_Mon_Tm, &Clk.Day[0], 2 );

								SM.MD_PCT = 0;
								SM.MDPMinCT = 0;
								SM.MD_Cunt = 0;
								SM.MD_CuntT = 0;
								SM.MD_BufAds = 0;
								RpaInit();
								break;
						case 0x0083:
								Cm_Ram_Inter(Point,Length);
								E2P_WData( CDParaTab[i].Addr, Point, Length );
								break;

			        case 0x0084:	//calibration
#if ( Threephase == YesCheck ) //三相						        
#if( MEASCHIP == ATT7053 )									
								E2P_WAdj( TempAddr, Point, Length );
								Flag.Power |= F_Reset7053;							
								RpaInit();
#elif( MEASCHIP == RN8207 )		
								SwapWord( Point, 3 );
								E2P_WAdj( TempAddr, Point, 6 );	
								E2P_WData(CalibrationRecord+TempAddr-0x0FC0,Point,6); 							
								RpaInit();	
						//		Reset8209All();
#elif( MEASCHIP == ADE7755 )
								SwapWord( Point, 3 );
								E2P_WAdj( TempAddr, Point, 6 );
								AD7755Init();
#endif								
#elif ( SinglePhase == YesCheck )
								E2P_WAdj( TempAddr, Point, 2);
//								E2P_WData(CalibrationRecord+TempAddr-0x03D0,Point,2); 
								E2P_WData(CalibrationRecord+TempAddr-0x0FC0,Point,2); 								
								
								SOCInit();	
#endif
								break;
					case 0x0087:
								E2P_WData(TempAddr + LoadRecord_Time,Point,Length);
								break;
					case 0x008b:
								RAM_Write((unsigned char *)&Comm.SecPulseCnt,Point,4);
								__disable_irq();
								tmp = Comm.SecPulseCnt%60;
								Clk.Sec[0]=Byte_BCD(tmp);
								tmp = Comm.SecPulseCnt/60;
								tmp = tmp%60;
								Clk.Min[0]=Byte_BCD(tmp);
								tmp = Comm.SecPulseCnt/3600;
								tmp = tmp%24;
								Clk.Hour[0]=Byte_BCD(tmp);
								__enable_irq();
								fnSysClock_Write(&Clk.Sec[0]);
								break;
					case 0x0082:
							RAM_Write((unsigned char *)&SM.day_no,Point,2);
							break;
					case 0x0089:
								E2P_WAdj( CDParaTab[i].Addr, Point, Length );
#if ( Threephase == YesCheck ) //三相	
								E2P_WData(CalibrationRecord+CDParaTab[i].Addr-0x0FC0,Point,Length); 
#else
//								E2P_WData(CalibrationRecord+CDParaTab[i].Addr-0x03D0,Point,Length); 
								E2P_WData(CalibrationRecord+CDParaTab[i].Addr-0x0FC0,Point,Length); 
#endif

								E2P_RAdj((unsigned char*)&Para.RTCDota0,ClockAdj,2);
								RtcWriteDota(Para.RTCDota0);

//								RpaInit();
								break;		

					case 0x008C:
								E2P_WData(TempAddr + LoadRecord_Time,Point,Length);
								break;

					default:  	
//					        E2P_WData( CDParaTab[i].Addr, Point, Length ); 
							
					        if((CDParaTab[i].ComID1 == '9') && (CDParaTab[i].ComID2 == '8')&&(CDParaTab[i].ComID3 != '6'))
					        	E2P_WData( CDParaTab[i].Addr + LoadRecord_Time, Point, Length ); 
					        else	
					        	E2P_WData( CDParaTab[i].Addr, Point, Length ); 		
							
					        RpaInit();
									if((CDParaTab[i].ComID1 == 'C') && (CDParaTab[i].ComID4 == '8')&&(CDParaTab[i].ComID5 == '4'))
										Write_PublicKey();
									break;
				}				
			}	
			else if((CDParaTab[i].State & 0x0020)!=0)   //0x002X
			{
						Length = CDParaTab[i].Len;
        		TempAddr = 	CDParaTab[i].Addr;
        		switch( Temp )
		        {						
						case 0x0023:
							if(Temp == 0x0023)
							{	
								Buff[0]=0x1;
								Set_Lmn_Dev_Id(ComBuf+10);
							}
							for(i=0;i<Length;++i)
							{
								if(ComBuf[10+i]==')')
									break;
							}
							RAM_Fill(ComBuf+10+i,Length-i);
							E2P_WData(TempAddr,ComBuf+10,Length);
							RpaInit();
						break;
					case 0x0024:
						_ASC_BCD( Point, ComBuf+10,4);
						RAM_Write( Point+4, ComBuf+18,4);
						E2P_WData(TempAddr + LoadRecord_Time,Point,Length);
						break;
					default:
						for(i=0;i<Length;++i)
						{
							if(ComBuf[10+i]==')')
								break;
						}
						RAM_Fill(ComBuf+10+i,Length-i);
						E2P_WData(TempAddr,ComBuf+10,Length);
						RpaInit();
						break;								
				}			
			}				
		}	
		*ComBuf = ACK;
	}       
	return 0;
}
