#include "Mem.h"
#include "General.h"
#include "TypeE2P.h"
#include "TypeMeter.h"
#include "Type.h"
#include "Data.h"
//#include <App.h>
//#include <RN8213.h>
#define  _FM24CXX_GLOBALS

#include <Drive_Lib.h>

 unsigned char  zuhe;	//显示指针//testtest

#define	E2P_PAGE	32
//#define MAX_TMP 	50
#define MAX_TMP 	150
#define	e2d5us	2

#define	sda1		0x0800 		
#define	scl1		0x0400 

#define	sda2		0x0800	
#define	scl2		0x0400 

#define	sda3		0x0800 		
#define	scl3		0x0400 

#define	sda4		0x0800 		
#define	scl4		0x0400 

#define  sda1hight	{GPIO->PMB |= sda1; }
#define  sda1low	{GPIO->PMB &=~sda1;	GPIO->PB &=~ sda1;}
#define  scl1hight	{ GPIO->PMB |= scl1;}
#define  scl1low	{GPIO->PMB &=~scl1;	GPIO->PB &=~ scl1;}
#define  sda1in	        {GPIO->PMB |= sda1;GPIO->PIEB &=~ sda1; }
#define  sda1equhigh    (GPIO->PB & sda1)

#define  sda2hight	{GPIO->PMB |= sda2; }
#define  sda2low	{GPIO->PMB &=~sda2;	GPIO->PB &=~ sda2;}
#define  scl2hight	{ GPIO->PMB |= scl2;}
#define  scl2low	{GPIO->PMB &=~scl2;	GPIO->PB &=~ scl2;}
#define  sda2in	        {GPIO->PMB |= sda2;GPIO->PIEB &=~ sda2; }
#define  sda2equhigh    (GPIO->PB & sda2)

#define  sda3hight	{GPIO->PMB |= sda3; }
#define  sda3low	{GPIO->PMB &=~sda3;	GPIO->PB &=~ sda3;}
#define  scl3hight	{ GPIO->PMB |= scl3;}
#define  scl3low	{GPIO->PMB &=~scl3;	GPIO->PB &=~ scl3;}
#define  sda3in	        {GPIO->PMB |= sda3;GPIO->PIEB &=~ sda3; }
#define  sda3equhigh    (GPIO->PB & sda3)

#define  sda4hight	{GPIO->PMB |= sda4; }
#define  sda4low	{GPIO->PMB &=~sda4;	GPIO->PB &=~ sda4;}
#define  scl4hight	{ GPIO->PMB |= scl4;}
#define  scl4low	{GPIO->PMB &=~scl4;	GPIO->PB &=~ scl4;}
#define  sda4in	        {GPIO->PMB |= sda4;GPIO->PIEB &=~ sda4; }
#define  sda4equhigh    (GPIO->PB & sda4)

//#define  sda2hight	{P1IE |= sda2; P1OE |= sda2;}
//#define  sda2low	{P1OD&=~sda2;	P1OE &=~ sda2;}
//#define  scl2hight	{P1IE |= scl2; P1OE |= scl2;}
//#define  scl2low	{P1OD&=~scl2;	P1OE &=~ scl2;}
//#define  sda2in	        {P1IE |= sda2; P1OE |= sda2;}
//#define  sda2equhigh    (P1ID & sda2)

//#define  sda3hight	{P1IE |= sda3; P1OE |= sda3;}
//#define  sda3low	{P1OD&=~sda3;	P1OE &=~ sda3;}
//#define  scl3hight	{P1IE |= scl3; P1OE |= scl3;}
//#define  scl3low	{P1OD&=~scl3;	P1OE &=~ scl3;}
//#define  sda3in	        {P1IE |= sda3; P1OE |= sda3;}
//#define  sda3equhigh    (P1ID & sda3)

//#define  sda4hight	{P1IE |= sda4; P1OE |= sda4;}
//#define  sda4low	{P1OD&=~sda4;	P1OE &=~ sda4;}
//#define  scl4hight	{P1IE |= scl4; P1OE |= scl4;}
//#define  scl4low	{P1OD&=~scl4;	P1OE &=~ scl4;}
//#define  sda4in	        {P1IE |= sda4; P1OE |= sda4;}
//#define  sda4equhigh    (P1ID & sda4)




/*
**-----------------------------------------------------------------------------
**EEPROM存储器操作子程序
**-----------------------------------------------------------------------------
*/

bool fnCheckNVRAM(u8 DeviceNo,u16 Address,u8 *Buff,u8 Length)
{
	u8 i;
	u8 Data;

	for(i=0;i<Length;i++){
		Data=*(Read_EEPROM + Address + i);    
		if(Data!=Buff[i]){return false;}
	}
	return true;
}
//---------------------------------------------------
/************************
Address~AAddress+Length-1不可跨节，每节64Bytes
*************************/
ErrorStatus fnOperateNVRAM(BOOL Read_Write,u8 DeviceNo,u16 Address,u8 *Buff,u8 Length,u8 Repeat)
{
	u8 i;
	u8 ReReadTimes;
	if (Length==0) {return ERROR;}
	
	
	for(ReReadTimes=0;ReReadTimes<=Repeat;ReReadTimes++)
	{
		if(Read==Read_Write)
		{
			for(i=0;i<Length;i++)
			{
				*(Buff+i) = *(Read_EEPROM + Address + i);
			}
		}
		else
		{
			i = eepromProgram(EEPROM_MEMORY_BASE + Address , (uint32_t)Buff , Length);
			if(i) continue;
		}
		if((fnCheckNVRAM(DeviceNo,Address,Buff,Length)==true)||(ReReadTimes>Repeat)) {break; }
	}
 	
 	if(ReReadTimes>=Repeat){return ERROR;}
 	return(SUCCESS);
}

//---------------------------------------------------
//函数功能：I2C存储器读取数据，在此实现跨页操作
//入口参数：Dst取数缓冲区目标指针，Src取数源地址，DatLen要取的数据长度，Repeat失败重复次数
//出口参数：SUCCESS成功，ERROR失败
ErrorStatus fnFM24CXX_Read(u8 *Dst , u32 Src , u32 DatLen , u8 Repeat)
{
	
	unsigned char* Temp_Pt;
	unsigned long DatLen1,DatLen2,Src1;	
	
	u16 AddressL,AddressH;
	u8 B,Check;
	u16 AddingTimes=0;
#if 0
	unsigned char Buffer[MAX_TMP];
	Temp_Pt = Buffer;
	if (DatLen==0) return(ERROR);
	
	DatLen += 1;	
	if ( EEPROM_MAXSize <= (Src+DatLen))  return(ERROR);
	DatLen1 = DatLen;
	DatLen2 = DatLen;
	Src1 = Src+E2P_PGLENRN8213;
	
	
	while (DatLen)
	{
		if(++AddingTimes>600)return(ERROR); //防止死循环
		AddressH=(u16)(Src>>16);
		AddressL=(u16)Src;
		if ((((~AddressL)&EEPROM_PageSize)+1)>=DatLen)/*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
		{B=DatLen;}
		else
		{B=((~AddressL)&EEPROM_PageSize)+1;}

//		if(ERROR==fnOperateNVRAM(Read,AddressH,AddressL,Dst,B,Repeat))
		if(ERROR==fnOperateNVRAM(Read,AddressH,AddressL,Temp_Pt,B,Repeat))			
		{ 
			return(ERROR);
		}
		Temp_Pt+=B;
		Src+=B;
		DatLen-=B;
	}
	
	Temp_Pt = Buffer;		
	Check = *(Temp_Pt + DatLen2-1);
	if( Check != ChkNum( Temp_Pt, DatLen2-1) && DatLen2<16) 
	{
		if((Src1<Mon_Data_Addr)&&(Src1>=E2P_PGLENRN8213))
		{
			while (DatLen1)
			{
				if(++AddingTimes>600)return(ERROR); //防止死循环
					AddressH=(u16)(Src1>>16);
					AddressL=(u16)Src1;
				if ((((~AddressL)&EEPROM_PageSize)+1)>=DatLen1)/*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
				{
					B=DatLen1;
				}
				else
				{
					B=((~AddressL)&EEPROM_PageSize)+1;
				}

			//if(ERROR==fnOperateNVRAM(Read,AddressH,AddressL,Dst,B,Repeat))
				if(ERROR==fnOperateNVRAM(Read,AddressH,AddressL,Temp_Pt,B,Repeat))
					{ 
						return(ERROR);
					}
					Temp_Pt+=B;
					Src1+=B;
					DatLen1-=B;
				}
				Temp_Pt = Buffer;						
				Check = *(Temp_Pt + DatLen2-1);
				if( Check != ChkNum( Temp_Pt, DatLen2-1) ) 	
					return(ERROR); //防止死循环
				} 	
	}
	RAM_Write( Dst, Temp_Pt, DatLen2-1 );
#else
	u8 B_Check;
	
	if (DatLen==0) return(ERROR);
		
	if ( EEPROM_MAXSize <= (Src+DatLen))  return(ERROR);
	Temp_Pt = Dst;
	DatLen1 = DatLen;
	DatLen2 = DatLen;
	Src1 = Src;//+E2P_PGLENRN8213;
	while (DatLen1)
	{
		if(++AddingTimes>600)return(ERROR); //防止死循环
		AddressH=(u16)(Src1>>16);
		AddressL=(u16)Src1;
		if ((((~AddressL)&EEPROM_PageSize)+1)>=DatLen1)/*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
		{B=DatLen1;}
		else
		{B=((~AddressL)&EEPROM_PageSize)+1;}

		if(ERROR==fnOperateNVRAM(Read,AddressH,AddressL,Temp_Pt,B,Repeat))			
		{ 
			return(ERROR);
		}
		Temp_Pt+=B;
		Src1+=B;
		DatLen1-=B;
	}
	AddressH=(u16)(Src1>>16);
	AddressL=(u16)Src1;
	if(ERROR==fnOperateNVRAM(Read,AddressH,AddressL,&B_Check,1,Repeat))			
	{ 
		return(ERROR);
	}
#if 0
	Temp_Pt = Dst;
	if( B_Check != ChkNum( Temp_Pt,DatLen)) 
	{
		//Temp_Pt = Dst;
		DatLen1 = DatLen;
		Src1 = Src+E2P_PGLENRN8213;
		while (DatLen1)
		{
			if(++AddingTimes>600)return(ERROR); //防止死循环
			AddressH=(u16)(Src1>>16);
			AddressL=(u16)Src1;
			if ((((~AddressL)&EEPROM_PageSize)+1)>=DatLen1)/*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
			{
				B=DatLen1;
			}
			else
			{
				B=((~AddressL)&EEPROM_PageSize)+1;
			}
			if(ERROR==fnOperateNVRAM(Read,AddressH,AddressL,Temp_Pt,B,Repeat))			
			{ 
				return(ERROR);
			}
			Temp_Pt+=B;
			Src1+=B;
			DatLen1-=B;
		}
		AddressH=(u16)(Src1>>16);
		AddressL=(u16)Src1;
		if(ERROR==fnOperateNVRAM(Read,AddressH,AddressL,&B_Check,1,Repeat))			
		{	 
			return(ERROR);
		}
		Temp_Pt = Dst;
		if( B_Check != ChkNum( Temp_Pt,DatLen)) 
		{
			return ERROR;
		}
	}
#endif
	
#endif	
	return(SUCCESS);
}

//---------------------------------------------------
//函数功能：I2C存储器写入数据，在此实现跨页操作
//入口参数：Dst写入数据的目标地址，Src写数缓冲区源指针，DatLen要写的数据长度，Repeat失败重复次数
//出口参数：SUCCESS成功，ERROR失败
ErrorStatus fnFM24CXX_Write(u32 Dst , u8 *Src , u32 DatLen , u8 Repeat)
{
	
	unsigned char* Temp_Pt;
	unsigned long DatLen1,Dst1;	
	u16 AddressL,AddressH;
	u8 B;
	u16 AddingTimes=0;
#if 0
	unsigned char Buffer[MAX_TMP];
	Temp_Pt = Buffer;
		
  if (DatLen==0) return(ERROR);
	if ( EEPROM_MAXSize <= (Dst+DatLen))  return(ERROR);

	RAM_Write( Temp_Pt, Src, DatLen );
	
	*(Temp_Pt + DatLen ) = ChkNum( Temp_Pt, DatLen );
	DatLen += 1;
	DatLen1 = DatLen;
	Dst1 = Dst+E2P_PGLENRN8213;
		
		while (DatLen)
		{
			if(++AddingTimes>600)return(ERROR); //防止死循环
				
			AddressH=(u16)(Dst>>16);
			AddressL=(u16)Dst;
			if ((((~AddressL)&EEPROM_PageSize)+1)>=DatLen)/*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
			{B=DatLen;}
			else
			{B=((~AddressL)&EEPROM_PageSize)+1;}

//			if(ERROR==fnOperateNVRAM(Write,AddressH,AddressL,Src,B,Repeat))
			if(ERROR==fnOperateNVRAM(Write,AddressH,AddressL,Temp_Pt,B,Repeat))				
			{
				return(ERROR);
			}
			Dst+=B;
			Temp_Pt+=B;
			DatLen-=B;

		}

		Temp_Pt = Buffer;
		if((Dst1<Mon_Data_Addr)&&(Dst1>=E2P_PGLENRN8213))
			{
				while (DatLen1)
				{
					if(++AddingTimes>600)return(ERROR); //防止死循环
						
					AddressH=(u16)(Dst1>>16);
					AddressL=(u16)Dst1;
					if ((((~AddressL)&EEPROM_PageSize)+1)>=DatLen1)/*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
					{B=DatLen1;}
					else
					{B=((~AddressL)&EEPROM_PageSize)+1;}

		//			if(ERROR==fnOperateNVRAM(Write,AddressH,AddressL,Src,B,Repeat))
					if(ERROR==fnOperateNVRAM(Write,AddressH,AddressL,Temp_Pt,B,Repeat))				
					{
						return(ERROR);
					}
					Dst1+=B;
					Temp_Pt+=B;
					DatLen1-=B;

				}		
			}
#else
			u8 B_Check;	
			Temp_Pt=Src;
			if (DatLen==0) return(ERROR);
			if ( EEPROM_MAXSize <= (Dst+DatLen))  return(ERROR);
			B_Check = ChkNum( Temp_Pt, DatLen );
			DatLen1 = DatLen;
			//Dst1 = Dst+E2P_PGLENRN8213;
			Dst1 = Dst;
			while (DatLen1)
			{
				if(++AddingTimes>600)return(ERROR); //防止死循环
				AddressH=(u16)(Dst1>>16);
				AddressL=(u16)Dst1;
				if ((((~AddressL)&EEPROM_PageSize)+1)>=DatLen1)/*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
				{
						B=DatLen1;
				}
				else
				{
						B=((~AddressL)&EEPROM_PageSize)+1;
				}
				
				if(ERROR==fnOperateNVRAM(Write,AddressH,AddressL,Temp_Pt,B,Repeat))				
				{
					return(ERROR);
				}
				Dst1+=B;
				Temp_Pt+=B;
				DatLen1-=B;
			}
			AddressH=(u16)(Dst1>>16);
			AddressL=(u16)Dst1;
			if(ERROR==fnOperateNVRAM(Write,AddressH,AddressL,&B_Check,1,Repeat))
				return(ERROR);
			DatLen1 = DatLen;
			Dst1 = Dst+E2P_PGLENRN8213;
			while (DatLen1)
			{
				if(++AddingTimes>600)return(ERROR); //防止死循环
				AddressH=(u16)(Dst1>>16);
				AddressL=(u16)Dst1;
				if ((((~AddressL)&EEPROM_PageSize)+1)>=DatLen1)/*与运算其实相当于求模运算，该语句保证从NVRAM中每一页的任意点开始*/
				{
						B=DatLen1;
				}
				else
				{
						B=((~AddressL)&EEPROM_PageSize)+1;
				}
				
				if(ERROR==fnOperateNVRAM(Write,AddressH,AddressL,Temp_Pt,B,Repeat))				
				{
					return(ERROR);
				}
				Dst1+=B;
				Temp_Pt+=B;
				DatLen1-=B;
			}
			AddressH=(u16)(Dst1>>16);
			AddressL=(u16)Dst1;
			if(ERROR==fnOperateNVRAM(Write,AddressH,AddressL,&B_Check,1,Repeat))
				return(ERROR);
#endif
			
	return(SUCCESS);
}

//signed char E2PRead( unsigned char* RAM_Addr, unsigned int E2P_Addr, unsigned int Lenth, unsigned char Devads); 
//signed char E2Pwrite( unsigned int E2P_Addr, unsigned char* RAM_Addr, unsigned int Lenth,unsigned char Devads); 

/*
unsigned char ChkNum( unsigned char *Ptr,  int Len )
{
	unsigned char Num;
    Num = 0xA5;
   	while( Len > 0 )
   	{
    	Num += *Ptr++;
      	Len--;
   	}
   	return Num;
}
*/
unsigned short ChkWordNumAdd( unsigned char *Ptr, short Len )
{
	unsigned short Num = 0xA5A5;
   
   	while( Len > 0 )
   	{
    	Num += *Ptr++;
      	Len--;
   	}
   	return Num;
}


void i2cdelay(void)
{
//	nop();
//	nop();
//	nop();
//	nop();nop();nop();
//	nop();nop();nop();
//	nop();nop();nop();
//	nop();nop();nop();
//	nop();nop();nop();
//	nop();nop();nop();
//	nop();nop();nop();
//	nop();nop();nop();

	__NOP();
	__NOP();
	__NOP();
	__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();
}

void sdain(void)
{
	__disable_irq();
	 if((zuhe&0x02)==0)
	 	{
		if((zuhe&0x01)==0)			  
			sda1in		//00//		  
		else
			sda2in		//01//
		}	
	 else
		{
		if((zuhe&0x01)==0)
			sda3in	  	//10//
		else
			sda4in		//11//
		}	
	__enable_irq();		
}	 
	 
void sdaset(void)
{
	 __disable_irq();
	 if((zuhe&0x02)==0)
	 	{
		if((zuhe&0x01)==0)			  
			sda1hight		//00	//	  
		else
			sda2hight		//01//
		}	
	 else																				
		{
		if((zuhe&0x01)==0)
			sda3hight	  	//10//
		else
			sda4hight		//11//
		}		
	__enable_irq();		
}	 
void sdaclr(void)
{
	 __disable_irq();
	 if((zuhe&0x02)==0)
	 	{
		if((zuhe&0x01)==0)			  
			sda1low	//00//		  
		else
			sda2low	//01//
		}	
	 else
		{
		if((zuhe&0x01)==0)
			sda3low	  	//10//
		else
			sda4low		//11//
		}
	__enable_irq();				
}	 
//-----------
void sclset(void)	
{
	 __disable_irq();
	 if((zuhe&0x02)==0)
	 {
		if((zuhe&0x01)==0)			  
			scl1hight		//00//		  
		else
			scl2hight		//01//
	}	
	 else
	{
		if((zuhe&0x01)==0)
			scl3hight	  	//10//
		else
			scl4hight		//11//
	}	
	__enable_irq();	
}	 
	 
//-----------	 
void sclclr(void)
{
	 __disable_irq();
	 if((zuhe&0x02)==0)
	 	{
		if((zuhe&0x01)==0)			  
			scl1low		//00//		  
		else
			scl2low	//01//
		}	
	 else
		{
		if((zuhe&0x01)==0)
			scl3low	  	//10//
		else
			scl4low		//11//
		}
	__enable_irq();			
}

unsigned char getsda(void)
	 {
	 sdain();
	 i2cdelay();
	 if((zuhe&0x02)==0)
	 	 {
		 if((zuhe&0x01)==0)			  
		 	{	

		 		if(sda1equhigh) return 1;else return 0;}		//00//		  
		 else
		 	{
		 		if(sda2equhigh) return 1;else return 0;}		//01//
		 }	
	 else
		 {
		 if((zuhe&0x01)==0)
		 	{
		 		if(sda3equhigh) return 1;else return 0;}	  	//10//
		 else
		 	{
		 		if(sda4equhigh) return 1;else return 0;}		//11//
		 }
	 }	 
//----------------------------------------
void I2CStop(void)
{
	i2cdelay();
	sdaclr();
	i2cdelay();
	__NOP();
//	nop();
	sclset();
	i2cdelay();
	sdaset();
	i2cdelay();

}
/*
void I2CStopSTEROM(void)
{
    zuhe = 0;
	I2CStop();
	i2cdelay();
	zuhe = 1;
	I2CStop();

}
*/

signed char I2CErr(void)			//I2C总线发送1字节//	
{
	I2CStop();	
	return -1;	
}		 
//----------------------------------------	 
	 
void GetI2CPara( unsigned char Devads )	//获取该I2C接口芯片在CPU上的IO口配置//
{
	switch( Devads )
	{
		case DataEAds:
#if ( Threephase == YesCheck ) //三相					
		case ECDataEAds:
#endif	
			zuhe = 0x01;
			break;
		case AdjEAds:
			zuhe = 0x01;//zuhe = 0x00;//
			break;
		case FMAds:
			zuhe = 0x01;
			break;
		case RTCAds:
			zuhe = 0x00;
			break;
		default: 
			zuhe = 0x00;
			break;				
	}
}	

unsigned char I2CMtData(unsigned char SendData ) //small//			//I2C总线发送1字节//	
{
	unsigned char i,Temp;
	
	Temp=SendData;
	for( i=0;i<8;i++ )
	{
		i2cdelay();		
		if(Temp&0x80) sdaset();
		else sdaclr();
		i2cdelay();
		__NOP();
//		nop();
		sclset();
		__NOP();
//		nop();
		i2cdelay();
		sclclr();
		Temp = (Temp<<1);
	}
	i2cdelay();		
	sdain();
	i2cdelay();
	__NOP();
//	nop();
	sclset();
	i2cdelay();
	i=getsda(); //检测ACK信号//
	sclclr();
	i2cdelay();
	sdain();
	return i;	
}

unsigned char I2CStart( unsigned short E2P_Addr, unsigned char Devads ) //small	//I2C总线Start//
{
	unsigned short E2PAddr;
	unsigned char CtlByte; 
	
	E2PAddr = E2P_Addr;
	CtlByte = Devads;
	Devads &= ~0x01;					//去掉读标志位 //
 	if( Devads == AdjEAds )				//AT24C04//
	{
		if( E2PAddr >= 0x100 ) CtlByte |= 0x02;
	}
	//else if( Devads == FMAds )			//FM24CL16//
	else if( Devads == FMAds )
	{
		E2PAddr = ( E2PAddr / 128 ) & 0x0E ;
		CtlByte &= 0xF1;
		CtlByte |= E2PAddr;
	//	CtlByte &=~ 0x0E;
	}		
	sdaset();
	i2cdelay();
	__NOP();
//	nop();
	sclset();
	i2cdelay();
	sdaclr();
	i2cdelay();
	sclclr();
	i2cdelay();
	return I2CMtData( CtlByte );				
}



signed char I2CStartAddr( unsigned short E2P_Addr, unsigned char Devads ) //small//	//I2C总线Start+地址//
{
	unsigned char i;
	
	I2CErr();
	for( i=0;i<150;i++ )
	{
		i2cdelay();
		if( I2CStart( E2P_Addr, Devads ) == 0 ) break;	
	}	
	if( i == 150 ) 
		return I2CErr();

	if(( Devads == ECDataEAds )||( Devads == DataEAds )||( Devads == ProfEAds ))
	{
		if( I2CMtData( (unsigned char)(E2P_Addr/256) ) != 0 ) return I2CErr();			
	}	
	if( I2CMtData( (unsigned char)E2P_Addr ) != 0 ) return I2CErr();			
	
	return 0;
}	


/**********************************************************************
	Asm Subroutine
	Source File in Asms.s43
**********************************************************************/
//signed char E2PRead( unsigned char* RAM_Addr, unsigned int E2P_Addr, unsigned int Lenth, unsigned char Devads) //small//
short E2PRead( unsigned char* RAM_Addr, unsigned short E2P_Addr, unsigned short Lenth, unsigned short Devads)
{

//	unsigned char idata i,j,TempData;
	unsigned char  i,j,TempData;

//	I2CPara = (I2CPARA*)Buff;//
	GetI2CPara( Devads );				//获取该I2C接口芯片在CPU上的IO口配置//

	if(( I2CStartAddr( E2P_Addr, Devads )) != 0 ) return -1;  

//	*I2CPara->SCL_DIR &= ~I2CPara->SCL;//
	sdaset();
//	nop();
	__NOP();
	sclset();
	if( I2CStart( E2P_Addr, Devads+0x01 ) != 0 ) return I2CErr();		//读命令//
	
	for( i=0;i<Lenth;i++ )
	{
	//	*(RAM_Addr+i) = 0;//
		sdain();
		for( j=0;j<8;j++ )
		{
		//	*I2CPara->SCL_DIR &= ~I2CPara->SCL;//
//			nop();
			__NOP();
			sclset();
			TempData = (TempData<<1);
			i2cdelay();
			if(getsda()) TempData |= 0x01;	
		//	*I2CPara->SCL_DIR |= I2CPara->SCL;//
			sclclr();
			i2cdelay();
		}
		*(RAM_Addr+i) = TempData;	
		
		if(i == Lenth-1) //ack//
			sdaset();
		else 
			sdaclr();
		i2cdelay();	
		__NOP();
		sclset();
		i2cdelay();
		sclclr();		//ack//
	}
//	*I2CPara->SDA_DIR |= I2CPara->SDA;//		//STOP//
//	*I2CPara->SCL_DIR &= ~I2CPara->SCL;		//
//	Delay(5);
//	*I2CPara->SDA_DIR &= ~I2CPara->SDA;//		//STOP//
	I2CStop();
	return 0;	
}	 

//signed char E2Pwrite( unsigned int E2P_Addr, unsigned char* RAM_Addr, unsigned int Lenth,unsigned char Devads ) 
short E2Pwrite( unsigned short E2P_Addr, unsigned char* RAM_Addr, unsigned short Lenth,unsigned short Devads )
{
//	unsigned int Buff[10];//
//	I2CPARA* I2CPara;//
	unsigned char i;
	unsigned short Len,PageLen;
	
//	I2CPara = (I2CPARA*)Buff;//
	GetI2CPara( Devads );				//获取该I2C接口芯片在CPU上的IO口配置//
	switch( Devads )
	{
		case DataEAds:
		case ECDataEAds:
//		case ProfEAds://		
			PageLen = 32;						//页写的最大长度//
			break;
		case FMAds:
			PageLen = 16;
			break;
		default: PageLen = 8;
			break;				
	}

	while( Lenth > 0 )
	{
		Len = E2P_Addr % PageLen;
		if( Len != 0 ) Len = PageLen - Len;
		else Len = PageLen;
		if( Lenth < Len ) Len = Lenth;
		
		if(( I2CStartAddr( E2P_Addr, Devads )) != 0 ) return -1;  

		for( i=0;i<Len;i++ )
		{
			if( I2CMtData( *(RAM_Addr+i) ) != 0 ) return I2CErr();			
		}	
//		*I2CPara->SDA_DIR |= I2CPara->SDA;//		//STOP//
//		*I2CPara->SCL_DIR &= ~I2CPara->SCL;//
//		i2cdelay();//
//		*I2CPara->SDA_DIR &= ~I2CPara->SDA;//		//STOP//
		I2CStop();

		RAM_Addr += Len;
		Lenth -= Len;
		E2P_Addr += Len;
	}
    return 0;
}

/**********************************************************************
	Write E2PROM	
**********************************************************************/
//signed char E2P_Write( unsigned int E2P_Dest, unsigned char* RAM_Src,  int Lenth,unsigned char Dev_Ads )
short E2P_Write( unsigned short E2P_Dest, unsigned char* RAM_Src, short Lenth, short Dev_Ads )
{
	unsigned char Buffer[MAX_TMP];
	unsigned char* Temp_Pt;
	unsigned char i;
	short NextPage;
	unsigned char BakNum;
	
	Temp_Pt = Buffer;
//	ClearWDT();
	fnWDT_Restart();

	RAM_Write( Temp_Pt, RAM_Src, Lenth );
	*(Temp_Pt + Lenth ) = ChkNum( Temp_Pt, Lenth );
	for( i=0;i<4;i++)
	{
		if( E2PTab[i].DevAds == Dev_Ads )
		{
			BakNum = E2PTab[i].BakNum;
			NextPage = E2PTab[i].NextPage;	
			break;
		}				
	}		 
	
//	if(( Dev_Ads == DataEAds )&&( E2P_Dest >= (E2P_PGLEN * 2) )) BakNum = 1;//		//事件记录无备份//
	
	for( i=0;i<BakNum;i++)
	{
//		if( E2Pwrite( E2P_Dest, Temp_Pt, Lenth+1, Dev_Ads ) != 0) Flag.ErrFlg |= F_ErrE2P;//
//		else Flag.ErrFlg &= ~F_ErrE2P;

		if( E2Pwrite( E2P_Dest, Temp_Pt, Lenth+1, Dev_Ads ) != 0)
			{
				 Flag.AlarmFlg[0] |= F_AlarmE2P;
			 }
		else 
			{
				Flag.AlarmFlg[0] &= ~ F_AlarmE2P;
			 }
		E2P_Dest += NextPage;
	}
	return 0;
}

/**********************************************************************
	Read E2PROM	
**********************************************************************/
//signed char E2P_Read( unsigned char* RAM_Dest,unsigned int E2P_Src,  int Lenth,unsigned char Dev_Ads )
short E2P_Read( unsigned char* RAM_Dest,unsigned short E2P_Src, short Lenth, short Dev_Ads )
{
	unsigned char Buffer[MAX_TMP];
	unsigned char* Temp_Pt;
	unsigned char i;
	short NextPage;
	unsigned char BakNum;
	unsigned char CorrectMode;

	Temp_Pt = Buffer;
//	ClearWDT();
	fnWDT_Restart();

	for( i=0;i<4;i++)
	{
		if( E2PTab[i].DevAds == Dev_Ads )
		{
			BakNum = E2PTab[i].BakNum;
			NextPage = E2PTab[i].NextPage;	
			CorrectMode = E2PTab[i].CorrectMode;
			break;
		}				
	}		 
	
//	if(( Dev_Ads == DataEAds )&&( E2P_Src >= (E2P_PGLEN * 2) )) BakNum = 1;		//事件记录无备份//
	
	for( i=0;i<BakNum;i++ )
	{
		if( E2PRead( Temp_Pt, E2P_Src, Lenth+1, Dev_Ads ) != 0 )
		{
			Flag.AlarmFlg[0] |= F_AlarmE2P;
			E2P_Src += NextPage;
			continue;		
		}
		else		
			Flag.AlarmFlg[0] &= ~ F_AlarmE2P;
		
		if( *(Temp_Pt + Lenth ) != ChkNum( Temp_Pt, Lenth ) )
		{
			Flag.AlarmFlg[0] |= F_AlarmE2P;				
			E2P_Src += NextPage;
			continue;		
		}
		else
			Flag.AlarmFlg[0] &= ~ F_AlarmE2P;
		
		break;
	}
//	ClearWDT();
	fnWDT_Restart();

	if( i != 0) 
	{
		//for(;i>=0;i--)
		for(;i>0;i--)
		{
			if( i == BakNum )
			{
				if( CorrectMode == 1 ) 
				{
					//RAM_Fill( Temp_Pt, Lenth, 0x00);
					RAM_Fill( Temp_Pt, Lenth);	
					*(Temp_Pt + Lenth ) = 0xA5;			
				}	
				else break;
			}	
			//E2P_Write( E2P_Src - NextPage, Temp_Pt, Lenth, Dev_Ads );
			E2Pwrite( E2P_Src - ( NextPage * ( BakNum - i )), Temp_Pt, Lenth+1, Dev_Ads );
		//	E2Pwrite( E2P_Src - ( NextPage * i ), Temp_Pt, Lenth+1, Dev_Ads );
		}	
	}
	RAM_Write( RAM_Dest, Temp_Pt, Lenth );
	return	0;	
}


#if ( Threephase == YesCheck ) //三相		

short E2P_RData( unsigned char* RAM_Dest,unsigned short E2P_Src,  short Lenth )
{
//	if(( Flag.Power & F_PwrUp ) == 0 )
//	if((( Flag.Power & F_PwrUp ) == 0 )&&((SYSCTL->SYS_RST&0x40)==0))		
//	fnDl645RCClock_Init();	
//	E2P_Read( RAM_Dest, E2P_Src, Lenth, DataEAds );
//	if(( Flag.Power & F_PwrUp ) == 0 )
//	if((( Flag.Power & F_PwrUp ) == 0 )&&((SYSCTL->SYS_RST&0x40)==0))		
//	fnDl645SubClock_Init();		
//	fnMemory_Read(RAM_Dest , Dl645FileInfo[FileId].StartAddr + OffAddr , Len) ;
	
//	fnFM24CXX_Read(RAM_Dest , E2P_Src , Lenth , 3);

	eepromWakeup();
	if(fnFM24CXX_Read(RAM_Dest , E2P_Src , Lenth , 3) == ERROR)
	{
	//	RAM_Fill(RAM_Dest, Lenth);	
	}
	eepromStandby();   
	return 0;
}	
short E2P_WData( unsigned short E2P_Dest, unsigned char* RAM_Src,  short Lenth )
{
//	E2P_Write( E2P_Dest, RAM_Src, Lenth, DataEAds );

	 eepromWakeup();

	 fnFM24CXX_Write( E2P_Dest , RAM_Src , Lenth , 3);
	 
       eepromStandby();
	return	0;
}

short E2P_RECData( unsigned char* RAM_Dest,unsigned short E2P_Src,  short Lenth )
{
//	if(( Flag.Power & F_PwrUp ) == 0 )
//	if((( Flag.Power & F_PwrUp ) == 0 )&&((SYSCTL->SYS_RST&0x40)==0))		
//	fnDl645RCClock_Init();	
	E2P_Read( RAM_Dest, E2P_Src, Lenth, DataEAds );
//	if(( Flag.Power & F_PwrUp ) == 0 )
//	if((( Flag.Power & F_PwrUp ) == 0 )&&((SYSCTL->SYS_RST&0x40)==0))			
//	fnDl645SubClock_Init();		
	
	
//	fnMemory_Read(RAM_Dest , Dl645FileInfo[FileId].StartAddr + OffAddr , Len) ;
	
//	fnFM24CXX_Read(RAM_Dest , E2P_Src , Lenth , 3);
	
	return 0;
}	
short E2P_WECData( unsigned short E2P_Dest, unsigned char* RAM_Src,  short Lenth )
{
	E2P_Write( E2P_Dest, RAM_Src, Lenth, DataEAds );

//	 fnFM24CXX_Write( E2P_Dest , RAM_Src , Lenth , 3);

	return	0;
}

short E2P_RAdj( unsigned char* RAM_Dest,unsigned short E2P_Src,  short Lenth )
{
//	E2P_Read( RAM_Dest, E2P_Src, Lenth, AdjEAds );

	E2P_Read( RAM_Dest, E2P_Src, Lenth, DataEAds );
	if((Flag.AlarmFlg[0] & F_AlarmE2P)==F_AlarmE2P)
		{
				 eepromWakeup();
//		fnFM24CXX_Read(RAM_Dest , CalibrationRecord+E2P_Src-0x0FC0, Lenth , 3);	
			if(fnFM24CXX_Read(RAM_Dest , CalibrationRecord+E2P_Src-0x0FC0, Lenth , 3) == ERROR)	
				{
				RAM_Fill(RAM_Dest, Lenth);	
				}		
			       eepromStandby();
				   
		}
//	fnFM24CXX_Read(RAM_Dest , E2P_Src , Lenth , 3);
	return 0;
}	
short E2P_WAdj( unsigned short E2P_Dest, unsigned char* RAM_Src,  short Lenth )
{
//	E2P_Write( E2P_Dest, RAM_Src, Lenth, AdjEAds );
	E2P_Write( E2P_Dest, RAM_Src, Lenth, DataEAds );
//	fnFM24CXX_Write( E2P_Dest , RAM_Src , Lenth , 3);
	return 0;
}	


#elif ( SinglePhase == YesCheck )


short E2P_RECData( unsigned char* RAM_Dest,unsigned short E2P_Src,  short Lenth )
{

	E2P_Read( RAM_Dest, E2P_Src, Lenth, FMAds );
	
	return 0;
}	
short E2P_WECData( unsigned short E2P_Dest, unsigned char* RAM_Src,  short Lenth )
{

	E2P_Write( E2P_Dest, RAM_Src, Lenth, FMAds );

	return	0;
}

short E2P_RData( unsigned char* RAM_Dest,unsigned short E2P_Src,  short Lenth )
{
//	E2P_Read( RAM_Dest, E2P_Src, Lenth, DataEAds );
	
//	fnMemory_Read(RAM_Dest , Dl645FileInfo[FileId].StartAddr + OffAddr , Len) ;
	
	eepromWakeup();

//	fnFM24CXX_Read(RAM_Dest , E2P_Src , Lenth , 3);
	if(fnFM24CXX_Read(RAM_Dest , E2P_Src , Lenth , 3) == ERROR)	
		{
		   //RAM_Fill(RAM_Dest, Lenth);	
		}
	
       eepromStandby();	
	
	return 0;
}	
short E2P_WData( unsigned short E2P_Dest, unsigned char* RAM_Src,  short Lenth )
{
//	E2P_Write( E2P_Dest, RAM_Src, Lenth, DataEAds );

	eepromWakeup();

	 fnFM24CXX_Write( E2P_Dest , RAM_Src , Lenth , 3);
	 
       eepromStandby();	

	return	0;
}

/*
short E2P_RAdj( unsigned char* RAM_Dest,unsigned short E2P_Src,  short Lenth )
{
	E2P_Read( RAM_Dest, E2P_Src, Lenth, AdjEAds );
	return 0;
}	
short E2P_WAdj( unsigned short E2P_Dest, unsigned char* RAM_Src,  short Lenth )
{
	E2P_Write( E2P_Dest, RAM_Src, Lenth, AdjEAds );
	return 0;
}	
*/

short E2P_RAdj( unsigned char* RAM_Dest,unsigned short E2P_Src,  short Lenth )
{
	E2P_Read( RAM_Dest, E2P_Src, Lenth, FMAds );
	if((Flag.AlarmFlg[0] & F_AlarmE2P)==F_AlarmE2P)
		{
		eepromWakeup();
		
//		fnFM24CXX_Read(RAM_Dest , CalibrationRecord+E2P_Src-0x03D0, Lenth , 3);	
			if(fnFM24CXX_Read(RAM_Dest , CalibrationRecord+E2P_Src-0x03D0, Lenth , 3)== ERROR)	
				{
				RAM_Fill(RAM_Dest, Lenth);	
				}	
			
      		eepromStandby();			
		}
	
	return 0;
}	
short E2P_WAdj( unsigned short E2P_Dest, unsigned char* RAM_Src,  short Lenth )
{
	E2P_Write( E2P_Dest, RAM_Src, Lenth, FMAds );
	return 0;
}	
#endif



