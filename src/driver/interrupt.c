#define  _Drive_ALLINT
#include <Drive_Lib.h>

#include <Scom.h>
#include <Dl645_Bkgrd.h>

#include "TypeMeter.h"
#include "TypeE2p.h"
//#include "msp430f6736.h"
#include "Measure.h"
#include "Port.h"
#include "Type.h"
#include "Mem.h"
#include "Data.h"
#include "General.h"
//#include "Interrupt.h"
#include "RsComm.h"
#include "Display.h"
#include "keychuli.h"
#include "Time.h"
#include "Power.h"
#include "Display.h"
extern uint32_t gprs_ms;
extern uint32_t ms_count;
extern uint32_t sml_tx_rx_time;
void TC1_HANDLER(void)    //0.5ms
{
	TC1->STA = 0x0f;
}

void TC0_HANDLER(void)    //ϵͳ������.1ms
{
	TC0->STA = 0x0f;
	ms_count++;
	if(gprs_ms)
	{
		gprs_ms--;
	//	if(gprs_ms==0)
		//	DMA->C0CTRL |= 1;
	}
	if(sml_tx_rx_time)
	{
		sml_tx_rx_time--;
	}
	if(Comm8213.CommDly != 0)
		Comm8213.CommDly--; 	
#if 0
	Clk.Sec_64++;

	if( Clk.Sec_64 >= 64 )
	{				
		// 1/64 Second
		Clk.Sec_64 = 0;				//V1001
		Flag.Clk |= F_Sec;
		_BCD1INC(Clk.Sec);
		if( Clk.Sec[0] >= 0x60 )
		{				
			// Second
			Clk.Sec[0] = 0;
			Flag.Clk |= F_Min;
			_BCD1INC(Clk.Min);
			if( Clk.Min[0] >= 0x60 )
			{			// Minute
				Clk.Min[0] = 0;
				Flag.Clk |= F_Hour;
				_BCD1INC(Clk.Hour);
				if( Clk.Hour[0] >= 0x24 )
				{		// Hour
					Clk.Hour[0] = 0;
					Flag.Clk |= F_Day;
					Clk.Week[0]++;
					//SM.TimeSet_Days++;
					if( Clk.Week[0] > 6 ) Clk.Week[0] = 0;				// Week
					DayInc( &Clk.Day[0] );
				}
			}
		}
	}

	if((Clk.Sec_64 == 0 )||( Clk.Sec_64 == 32 ))		
	{															
		Flag.Clk |= F_HalfSec;	
	}
#endif
	return;
}

void CMP_HANDLER(void)
{

}

void VCH_HANDLER(void)
{

}

#if 0
void UART0_HANDLER(void)
{
	u32  status;
	status = UART0->STA;
#if 0
	/* UART error irq */
	if((UART0->CTRL & 0x8) && (status & 0x3c))
	{
		UART0->STA = status;
	}	
	if((UART0->CTRL & 0x4) && (status & 0x1))
	{
		if( Comm.Ptr0 >= RS_MaxSize )
			{
				Comm.Ptr0 = 0;
			}
			Comm.Buf0[50+Comm.Ptr0++] = UART0->RXD;
			Comm.BTime0 = MS600;
			Comm.Delay0 = MS400;
			
			if(Comm.Buf0[49+Comm.Ptr0] !=0xa) return;
			if((Comm.Buf0[48+Comm.Ptr0] ==0xd)&&(Comm.Buf0[40+Comm.Ptr0] ==0x61)&&(Comm.Buf0[41+Comm.Ptr0] ==0x63))
				{
				Comm.State0= 1;
				Flag.Run0 |= F_ComOK;
				}
			Comm.Ptr0 = 0;		
		}		
		if((UART0->CTRL & 0x2) && (status & 0x2))
		{			
			if(Comm.SendLen0 == 0)
				{
					Comm.Ptr0 = 0;
					Flag.Run0 |= F_ComOK;
					Comm.FTime0 = TM_120s;
					UART0->CTRL &=0xfffd;		//���η����ж�
					UART0->STA = 0x02;		//�巢���жϱ�־

					UART0->CTRL |=0x0c; 	//��������ж�,������մ����ж�
					UART0->STA = 0x3d;		//������жϱ�־�����մ����־
						
					Comm.Buf0[0] = 0;
					Comm.TXLAST_Delay0 = 2;
					if(Comm.BlockNo0)
						Comm.TX_Delay0 = 0;
					else	
						Comm.TX_Delay0 = 2;					
					}
				else
					{
						Comm.Ptr0++;
						UART0->TXD = Comm.Buf0[Comm.Ptr0] ;		
						Comm.SendLen0--;
					}
		}
		#endif
		UART0->STA = status;
		return;
}
#endif
#if 0
void UART1_HANDLER(void)
	{
	u32  status;
	//	u8	 temp;
	status = UART1->STA;

	/* UART error irq */
	if((UART1->CTRL & 0x8) && (status & 0x3c))
	{
	//		ComPack[SCOM_PORT_IR].RxLen=0;
	//		ComPack[SCOM_PORT_IR].EFlag=SCOMPK_EFLAG_IDLE;
	UART1->STA = status;
	}


	//	switch (UCA2IV)
	//	switch (status & 0x3)
	if((UART1->CTRL & 0x4) && (status & 0x1))
	{
	//   	case 2:					//����
	UART1->STA = 0x1;			// clear receive IF	
	if( Comm.Ptr1 >= RS_MaxSize )
	{
	Comm.Ptr1 = 0;
	return;
	}
	//			Comm.Buf1[Comm.Ptr1++] = UCA2RXBUF;
	Comm.Buf1[Comm.Ptr1++] = UART1->RXD;

	Comm.BTime1 = MS600;
	Comm.Delay1 = MS400;
	switch ( Comm.Buf1[0] )
	{
	case NAK: 	Comm.State1 = 3; break;
	case ACK: 	if( Comm.State1 == 1 )
				{
					if( Comm.Buf1[Comm.Ptr1 - 1] != LF )	return;
					Comm.State1 = 2;
				}		
			else  Comm.State1 = 3; 
			break;
	case SOH:	if( Comm.Ptr1 <= 3 ) return;
			if(( Comm.Buf1[Comm.Ptr1 - 2] != EOT ) && ( Comm.Buf1[Comm.Ptr1 - 2] != ETX )) return;
			Comm.State1 = 3;
			break;
	case StartCode:	if( Comm.Buf1[Comm.Ptr1 - 1] != LF ) return;
				Comm.Rdout300bps1=0x0;
				Comm.State1 = 1;
					break;	
	default:  Comm.Ptr1 = 0;
					return;
	}	
	Flag.Run1 |= F_ComOK;
	Comm.FTime1 = TM_120s;
	SM.KeyDly = 30;
	Comm.RecTmr1 = 2;
	//			UCA2IE &= ~UCRXIE;//�رս����ж�//
	UART1->CTRL &=0xfff3; 	//���ν����ж�,���ν��մ����ж�
	UART1->STA = 0x3d;		//������жϱ�־�����մ����־
	}	
	//    		break;
	//    	case 4:					//����
	if((UART1->CTRL & 0x2) && (status & 0x2))
	{			UART1->STA = 0x2;
	Comm.Rdout300bps1=0x0;
	switch ( Comm.State1 )
	{
	case 1: //if( Comm.Buf[Comm.Ptr-1] != LF  )
		//	{
		//		U0TXBUF = Comm.Buf[Comm.Ptr++] ;
		//		return;
		//	}	
		//	else break;
		
	//		   				UCA2TXBUF = Comm.Buf1[Comm.Ptr1++] ;
		UART1->TXD = Comm.Buf1[Comm.Ptr1++] ;

		if( Comm.Buf1[Comm.Ptr1-1] != LF  ) return;
		break;
	case 3: if(( Comm.Buf1[0] == ACK ) || ( Comm.Buf1[0] == NAK )) break;
	case 2:
			if(Comm.BlockNo1)
				{
	//		   					if(Comm.SendLen1>0)
				Comm.SendLen1--;
				if(Comm.SendLen1!=0)
					{
	//		   						UCA2TXBUF = Comm.Buf1[Comm.Ptr1++] ;	
				UART1->TXD= Comm.Buf1[Comm.Ptr1++] ;
					return;}	
				}
			else
				{
	//		   			 		UCA2TXBUF = Comm.Buf1[Comm.Ptr1++] ;
			UART1->TXD= Comm.Buf1[Comm.Ptr1++] ;

			if(( Comm.Buf1[Comm.Ptr1-2] != EOT ) && ( Comm.Buf1[Comm.Ptr1-2] != ETX )) return;
			}	
		break;
	default: return;
	}
	Flag.Run1 |= F_ComOK;
	Comm.FTime1 = TM_120s;
	//	ME1 &= ~UTXE0;
	//			UCA2IE &= ~UCTXIE;//�رշ����ж�//
	UART1->CTRL &=0xfffd;		//���η����ж�
	UART1->STA = 0x02;		//�巢���жϱ�־

	Comm.Buf1[0] = 0;
	Comm.TXLAST_Delay1 = 2;
	//	Comm.TX_Delay = 0;
	if(Comm.BlockNo1)
	Comm.TX_Delay1 = 0;
	else	
	Comm.TX_Delay1 = 2;		
	//		break;
	//	default: break;
	}

	UART1->STA = status;

	return;
}

void UART3_HANDLER(void)
{
	u32  status;
//	u8	 temp;
  	status = UART3->STA;
  
  	/* UART error irq */
	if((UART3->CTRL & 0x8) && (status & 0x3c))
	{
//		ComPack[SCOM_PORT_ZBCOM].RxLen=0;
//		ComPack[SCOM_PORT_ZBCOM].EFlag=SCOMPK_EFLAG_IDLE;
		UART3->STA = status;
	}



#if ( Threephase == YesCheck ) //����	
#if( MEASCHIP == RN8207 )

//	switch (status & 0x3)
	if((UART3->CTRL & 0x4) && (status & 0x1))		
  	{
 //   	case 1:					//����
		
            if(Comm8207.Ptr8207==0x01)
            {// Comm8207.RecBuf8207[Comm8207.Ptr8207]=UCA1RXBUF;
              Comm8207.RecBuf8207[Comm8207.Ptr8207]= UART3->RXD;
            } 
                          
            if(Comm8207.NeedRecCnt==0)
			{//	Comm8207.RecBuf8207[Comm8207.Ptr8207]=UCA1RXBUF;
				Comm8207.RecBuf8207[Comm8207.Ptr8207]=UART3->RXD;
				Comm8207.CommOk=0x55;	
//				UCA1IE &= ~UCRXIE;//�رս����ж�//
				UART3->CTRL &=0xfff3; 	//���ν����ж�,���ν��մ����ж�
				UART3->STA = 0x3d;		//������жϱ�־�����մ����־
				
				if(Comm8207.SendBuf8207[1] == ENERGYP3) 
				{
					switch(Comm8207.SendBuf8207[0])
					{
						case CHIPIDA:
							RAM_Write_Dev((unsigned char*)&SM.PowerA1SCnt1[1],(unsigned char*)&SM.PowerA1SCnt1[0],6);
							SM.PowerA1SCnt1[0] = SM.PowerA1S;
//							SM.PowerA1SCnt = SM.PowerA1S;
							SM.PowerA1S = 0;
							break;
						case CHIPIDB:
							RAM_Write_Dev((unsigned char*)&SM.PowerB1SCnt1[1],(unsigned char*)&SM.PowerB1SCnt1[0],6);
							SM.PowerB1SCnt1[0] = SM.PowerB1S;
//							SM.PowerB1SCnt = SM.PowerB1S;
							SM.PowerB1S = 0;
							break;
						case CHIPIDC:
							RAM_Write_Dev((unsigned char*)&SM.PowerC1SCnt1[1],(unsigned char*)&SM.PowerC1SCnt1[0],6);
							SM.PowerC1SCnt1[0] = SM.PowerC1S;
//							SM.PowerC1SCnt = SM.PowerC1S;
							SM.PowerC1S = 0;
							break;		
						default: break;
					}
					
				}	
			}
			else
			{	//Comm8207.RecBuf8207[Comm8207.Ptr8207]=UCA1RXBUF;
				Comm8207.RecBuf8207[Comm8207.Ptr8207]=UART3->RXD;
				Comm8207.Ptr8207++;
				Comm8207.NeedRecCnt--;
			}		
		UART3->STA = 0x1;			// clear receive IF	
		}
 //   		break;
 //   	case 2:					//����
    	if((UART3->CTRL & 0x2) && (status & 0x2))
    		{
				
			if(Comm8207.NeedSendCnt==0)
			{
				Comm8207.Ptr8207=0;
//				UCA1IE &= ~UCTXIE;//�رշ����ж�//
				UART3->CTRL &=0xfffd;		//���η����ж�
				UART3->STA = 0x02;		//�巢���жϱ�־
				
//				UCA1IE |= UCRXIE;//�򿪽����ж�// 
				UART3->CTRL |=0x0c; 	//��������ж�,������մ����ж�
				UART3->STA = 0x3d;		//������жϱ�־�����մ����־
				
				Comm8207.CommOk=0x5a;//������÷��͵�����//
			}	
			else
			{
				Comm8207.Ptr8207++;//����ָ���1//
//				UCA1TXBUF = Comm8207.SendBuf8207[Comm8207.Ptr8207];//����һ�ֽ�//
				UART3->TXD = Comm8207.SendBuf8207[Comm8207.Ptr8207];//����һ�ֽ�//
				
				Comm8207.NeedSendCnt--;//��Ҫ���͵����ݼ�һ//
				
//				if(Comm8207.SendBuf8207[1] == ENERGYP2) 
//				{
//					switch(Comm8207.SendBuf8207[0])
//					{
//						case CHIPIDA:
//							SM.PowerA1SCnt = SM.PowerA1S;
//							SM.PowerA1S = 0;
//							break;
//						case CHIPIDB:
//							SM.PowerB1SCnt = SM.PowerB1S;
//							SM.PowerB1S = 0;
//							break;
//						case CHIPIDC:
//							SM.PowerC1SCnt = SM.PowerC1S;
//							SM.PowerC1S = 0;
//							break;		
//						default: break;
//					}
//					
//				}
			}		
    			UART3->STA = 0x2;
//    		break;
//		default: break;
    		}
		
#endif 
#endif      
	return;



	
  
	/* receive data complete irq */
/*	
  	if((UART3->CTRL & 0x4) && (status & 0x1))
  	{
    	temp = UART3->RXD;
    	if(ComPack[SCOM_PORT_ZBCOM].EFlag == SCOMPK_EFLAG_IDLE)
    	{
    		if(temp == 0x68) 
    		{
    			ComPack[SCOM_PORT_ZBCOM].RxBuf[ComPack[SCOM_PORT_ZBCOM].RxLen++]=temp;
    			ComPack[SCOM_PORT_ZBCOM].EFlag=SCOMPK_EFLAG_RXHEAD1;
    			ComPack[SCOM_PORT_ZBCOM].TimeOutStamp=SysStamp?SysStamp:(SysStamp-1);
    		}
    	}
    	else if(ComPack[SCOM_PORT_ZBCOM].EFlag == SCOMPK_EFLAG_RXHEAD1)
    	{
    		if(ComPack[SCOM_PORT_ZBCOM].RxLen>6) 
    		{
    			if(temp == 0x68) 
    			{
    				ComPack[SCOM_PORT_ZBCOM].EFlag=SCOMPK_EFLAG_RXHEAD2;
    				ComPack[SCOM_PORT_ZBCOM].RxBuf[ComPack[SCOM_PORT_ZBCOM].RxLen++]=temp;
    				ComPack[SCOM_PORT_ZBCOM].TimeOutStamp=SysStamp?SysStamp:(SysStamp-1);
    			}
    			else ComPack[SCOM_PORT_ZBCOM].RxLen=0x0;
    		}
    		else 
    		{
    			ComPack[SCOM_PORT_ZBCOM].RxBuf[ComPack[SCOM_PORT_ZBCOM].RxLen++]=temp;
    			ComPack[SCOM_PORT_ZBCOM].TimeOutStamp=SysStamp?SysStamp:(SysStamp-1);
    		}
    	}
    	else if(ComPack[SCOM_PORT_ZBCOM].EFlag == SCOMPK_EFLAG_RXHEAD2)
    	{
    		ComPack[SCOM_PORT_ZBCOM].RxBuf[ComPack[SCOM_PORT_ZBCOM].RxLen++]=temp;
    		ComPack[SCOM_PORT_ZBCOM].TimeOutStamp=SysStamp?SysStamp:(SysStamp-1);
    		if(ComPack[SCOM_PORT_ZBCOM].RxLen>8) ComPack[SCOM_PORT_ZBCOM].EFlag=SCOMPK_EFLAG_RXDATALEN;
    	}
    	else if(ComPack[SCOM_PORT_ZBCOM].EFlag == SCOMPK_EFLAG_RXDATALEN)
    	{
    		
    		ComPack[SCOM_PORT_ZBCOM].RxBuf[ComPack[SCOM_PORT_ZBCOM].RxLen++]=temp;
    		ComPack[SCOM_PORT_ZBCOM].TimeOutStamp=SysStamp?SysStamp:(SysStamp-1);
    		if(ComPack[SCOM_PORT_ZBCOM].RxLen>(ComPack[SCOM_PORT_ZBCOM].RxBuf[9]+10)) ComPack[SCOM_PORT_ZBCOM].EFlag=SCOMPK_EFLAG_RXEND;
    	}
    	else if(ComPack[SCOM_PORT_ZBCOM].EFlag == SCOMPK_EFLAG_RXEND)
    	{
    		if(temp == 0x16) 
			{
				ComPack[SCOM_PORT_ZBCOM].EFlag=SCOMPK_EFLAG_RXFINISH;
				ComPack[SCOM_PORT_ZBCOM].RxBuf[ComPack[SCOM_PORT_ZBCOM].RxLen++]=temp;
				ComPack[SCOM_PORT_ZBCOM].TimeOutStamp=SysStamp?SysStamp:(SysStamp-1);
			}
			else ComPack[SCOM_PORT_ZBCOM].RxLen=0x0;
    	}
    	UART3->STA = 0x1;			// clear receive IF
  	}
  	*/
  	/* transmit data complete irq */
	/*
  	if((UART3->CTRL & 0x2) && (status & 0x2))
  	{
    	if(ComPack[SCOM_PORT_ZBCOM].EFlag==SCOMPK_EFLAG_TXBUSY)
		{
			if(ComPack[SCOM_PORT_ZBCOM].TxLen>0)
			{
				UART3->TXD=*(ComPack[SCOM_PORT_ZBCOM].pTx++);
				ComPack[SCOM_PORT_ZBCOM].TxLen--;
			}
			else
			{
				ComPack[SCOM_PORT_ZBCOM].EFlag=SCOMPK_EFLAG_TXFINISH;
//				fnScomPk_Init(SCOM_PORT_ZBCOM);//�˴������ӵģ�����������ɺ��ʼ��
			}
		}
    	UART3->STA = 0x2;
  	}
*/


	
//  	return;
}
#endif
#if 0

///------˫��ͨ��----------
void UART5_HANDLER(void)
{
	u32  status;
//	u8	 temp;
	status = UART5->STA;
  
	/* UART error irq */
	if((UART5->CTRL & 0x8) && (status & 0x3c))
	{
		UART5->STA = status;
	}

	if((UART5->CTRL & 0x4) && (status & 0x1))
	{				  
			if(Comm8213.NeedRecCnt<=1)
			{
				Comm8213.RecBuf8213[Comm8213.Ptr8213]=UART5->RXD;
				Comm8213.CommOk=0x55;	
	//			UART5->CTRL &=0xfff3;	//���ν����ж�,���ν��մ����ж�
				UART5->STA = 0x3d;		//������жϱ�־�����մ����־	
			}
			else
			{
				Comm8213.RecBuf8213[Comm8213.Ptr8213]=UART5->RXD;
				if(Comm8213.RecBuf8213[0] != 0xA6)
					{	
						Comm8213.Ptr8213 = 0;
						return;
					}else{
						Comm8213.Ptr8213++;
						Comm8213.NeedRecCnt--;
					}
			}		
			UART5->STA = 0x1;
		}		

		if((UART5->CTRL & 0x2) && (status & 0x2))
		{
	//--------------------------------------------------------------			
			UART5->STA = 0x2;		
			if(Comm8213.NeedSendCnt==0)
			{
				Comm8213.Ptr8213=0;
				UART5->CTRL &=0xfffd;		//���η����ж�
				UART5->STA = 0x02;		//�巢���жϱ�־
			
				UART5->CTRL |=0x0c; 	//��������ж�,������մ����ж�
				UART5->STA = 0x3d;		//������жϱ�־�����մ����־
			
				Comm8213.CommOk=0x5a;//������÷��͵�����//
			}	
			else
			{
				Comm8213.Ptr8213++;//����ָ���1//
				UART5->TXD = Comm8213.SendBuf8213[Comm8213.Ptr8213];//����һ�ֽ�//
				Comm8213.NeedSendCnt--;//��Ҫ���͵����ݼ�һ//
			}		
		}
		
	return;
}
#endif
void KBI_HANDLER(void)
{


	if((KBI->DATA&0x03) !=0)
	{
/*	
	fnDl645RCClock_Init();	

	SYSCTL->SYS_PS = 0x82;		
	eepromWakeup();
	SYSCTL->MOD0_EN = 0x0004;//��E��ģ��		
   	SYSCTL->SYS_PS = 0x00;	
	
	SM.RDisDays = 60;
	LCD->CTRL |= 0x01;
	SM.menustep=0;

	if((KBI->DATA&0x01) !=0)
	Disk.DisInv = 0;		

//	ProcessUpScroll();
//	if((KBI->DATA&0x02) !=0)

//       ProcessDownScroll();
	RTC->IF = 0xff;
	fnINTRTC_Init1S();
	NVIC_EnableIRQ(RTC_IRQn);
	
	SYSCTL->SYS_PS = 0x82;	
	eepromStandby();
	SYSCTL->MOD0_EN = 0x0000;//��E��ģ��		
	SYSCTL->SYS_PS = 0x00;	
	
	fnDl645SubClock_Init();

*/


	
//		RTC->IF = 0xff;
//		fnINTRTC_Init1S();
//		NVIC_EnableIRQ(RTC_IRQn);	

		Flag.Disk |=(F_Key1+F_Key2);	
		Disk.PoweoffNo = 0xA5;//TEST LCD					
		Disk.PoweoffPtr = 0;//TEST LCD	
	
		fnDl645SubClock_Init();
	
	}

	KBI->DATA = 0xff;

//	if(KBI->DATA&0x01) 
//	{
//		Dl645Inactive.InactiveFlag.fChange |=0x01;
//	}
//	if(KBI->DATA&0x02) Dl645Inactive.InactiveFlag.fChange |=0x04;
//	KBI->DATA = 0xff;

}

void RTC_HANDLER(void)
{	
//	unsigned char i;
	if(RTC->IF&0x04)        // ��ʱ2   1/64���ж�
	{	
		Clk.Sec_64++;

		if( Clk.Sec_64 >= 64 )
		{				
			// 1/64 Second
			Clk.Sec_64 = 0;				//V1001
			Flag.Clk |= F_Sec;
			_BCD1INC(Clk.Sec);
			if( Clk.Sec[0] >= 0x60 )
			{				
				// Second
				Clk.Sec[0] = 0;
				Flag.Clk |= F_Min;
				_BCD1INC(Clk.Min);
				if( Clk.Min[0] >= 0x60 )
				{			// Minute
					Clk.Min[0] = 0;
					Flag.Clk |= F_Hour;
					_BCD1INC(Clk.Hour);
					if( Clk.Hour[0] >= 0x24 )
					{		// Hour
						Clk.Hour[0] = 0;
						Flag.Clk |= F_Day;
						Clk.Week[0]++;
						//SM.TimeSet_Days++;
						if( Clk.Week[0] > 6 ) Clk.Week[0] = 0;				// Week
						DayInc( &Clk.Day[0] );
					}
				}
			}
		}

		if((Clk.Sec_64 == 0 )||( Clk.Sec_64 == 32 )) 				//PWMD					
		{															//PWMD
			Flag.Clk |= F_HalfSec;	//V1001							//PWMD		
			Flag.Disk |= F_KeyInt;	
		}
		if(Comm.BTime2)
		{
			Comm.BTime2--;
			if(Comm.BTime2==0)
			{
extern uint8_t ieccmd_ptr;				
				ieccmd_ptr=0;
			}
		}
	}
	RTC->IF = 0xff;
}


void NMI_Handler(void)
{
	WDT->EN = 0xbc;
}

void HardFault_Handler(void)
{
	WDT->EN = 0xbc;
}

void SVC_Handler(void)
{
	WDT->EN = 0xbc;
}

void PendSV_Handler(void)
{
	WDT->EN = 0xbc;
}

void SysTick_Handler(void)
{
	WDT->EN = 0xbc;
}

void EMU_HANDLER(void)
{	
	u32  status1;

	status1 = EMU->IF;

	EMU->SPCMD = 0xe5;			 							// дʹ��λ

	EMU->IF  = status1;//�巢�����־ 

	EMU->SPCMD = 0xdc; 							// д����
	__NOP();
}

void MADC_HANDLER(void)
{
	WDT->EN = 0xbc;
}

void EXT6_HANDLER(void)//����
{	

	WDT->EN = 0xbc;	
	INTC->STA = 0xff;
}

void EXT7_HANDLER(void)//����
{	
	WDT->EN = 0xbc;	
	INTC->STA = 0xff;		
}


//---------------------------------------------------


