//#include <Drive_Lib.h>
#include "serial.h"
#include "RN8215.h"

#define MAX_UART_PORT     2

#define UART1_SERIAL_NO   0
#define UART5_SERIAL_NO   1

#define UART1_RTS_PORT	GPIO->PCA0
#define UART5_RTS_PORT  GPIO->PCB

#define UART1_RTS_PIN		(1<<25)
#define UART5_RTS_PIN  	(1<<11)

#define UART1_RTS_PORT_DIR	GPIO->PMA
#define UART5_RTS_PORT_DIR	GPIO->PMB

#define UART1_RTS_PIN_DIR		(1<<17)
#define UART5_RTS_PIN_DIR  	(1<<11)

#define UART1_RTS_PORT_VAL	GPIO->PA
#define UART5_RTS_PORT_VAL	GPIO->PB

#define UART1_RTS_PIN_VAL		(1<<17)
#define UART5_RTS_PIN_VAL  	(1<<11)

#define SET_UART1_RTS1 UART1_RTS_PORT_VAL |= UART1_RTS_PIN_VAL
#define SET_UART1_RTS0 UART1_RTS_PORT_VAL &= ~UART1_RTS_PIN_VAL

#define SET_UART5_RTS0 UART5_RTS_PORT_VAL |= UART5_RTS_PIN_VAL
#define SET_UART5_RTS1 UART5_RTS_PORT_VAL &= ~UART5_RTS_PIN_VAL

uint8_t ch0_tx_buf[16];
uint8_t ch0_rx_buf[SERIAL_CH0_LEN];
uint8_t ch1_rx_buf[SERIAL_CH1_LEN];

void Init_RTS1(void)
{
	UART1_RTS_PORT &= ~UART1_RTS_PIN;
  UART1_RTS_PORT_DIR &= ~UART1_RTS_PIN_DIR;
}

void Init_RTS5(void)
{
	UART5_RTS_PORT &= ~UART5_RTS_PIN;
	UART5_RTS_PORT_DIR &= ~UART5_RTS_PIN_DIR;
}

void Set_RTS1(uint8_t val)
{
	if(val)
	{
		UART1_RTS_PORT_VAL |= UART1_RTS_PIN_VAL;
	}
	else
	{
		UART1_RTS_PORT_VAL &= ~UART1_RTS_PIN_VAL;
	}
}

void Set_RTS5(uint8_t val)
{
	if(val)
	{
		UART5_RTS_PORT_VAL |= UART5_RTS_PIN_VAL;
	}
	else
	{
		UART5_RTS_PORT_VAL &= ~UART5_RTS_PIN_VAL;
	}
}

//struct S_Serial_ m_sserial[2];
struct S_Serial_ m_sserial1;
struct S_Serial_ m_sserial5;
static uint8_t *buf_pos;
void udelay(uint32_t us)
{
	uint32_t kk,i;
	for(i=0;i<us;++i)
	{
		for(kk=0;kk<20;++kk)
			__NOP();
		fnWDT_Restart();
	}
}
void DMA_Init(uint8_t ch)
{
	
	if(ch==0)
	{
		DMA->STA = DMA->STA;
		SYSCTL->SYS_PS = 0x82;
		SYSCTL->MOD1_EN |= (1);
		SYSCTL->SYS_PS = 0x00;
		DMA->C0CTRL |= (2<<3) |(3<<7);
	//	DMA->IE |= 1 | (1<<4) | (1<<8);
		DMA->IE |= (1<<4) | (1<<8);
	}
	else
	{
		SYSCTL->SYS_PS = 0x82;
		SYSCTL->MOD1_EN |= (1<<1);
		SYSCTL->SYS_PS = 0x00;
		DMA->C1CTRL |= (2<<3) |(28<<7);
	//	DMA->IE |= 2 | (2<<4) | (2<<8);
		DMA->IE |= (2<<4) | (2<<8);
	}
}

void DMA_SetLen(uint8_t ch,uint16_t Len)
{
	if(ch==0)
	{
		DMA->C0CTRL &= 0xffff;
		if(Len&0xff00)
		{
			DMA->C0CTRL |= (((Len>>8)-1)<<24) | ((255)<<16);
			m_sserial1.send_pos=(Len>>8)<<8;
		}
		else
		{
			DMA->C0CTRL |= ((Len-1)<<16);
			m_sserial1.send_pos=Len;
		}
		m_sserial1.send_len=Len;
	}
	else
	{
		DMA->C1CTRL &= 0xffff;
		if(Len&0xff00)
		{
			DMA->C1CTRL |= (((Len>>2))<<24) | ((3)<<16);
		}
		else
			DMA->C1CTRL |= ((Len)<<16);
		m_sserial5.send_len=Len;
	}
}

__inline void DMA_Start(uint8_t ch)
{
	if(ch==0)
		DMA->C0CTRL |= 1;
	else
		DMA->C1CTRL |= 1;
}
void DMA_Send(uint8_t ch,uint8_t  *dstbuf,uint8_t *srcbuf,uint16_t len)
{
	if(ch==0)
	{
		DMA->C0DST = (uint32_t)dstbuf;
		DMA->C0SRC = (uint32_t)srcbuf;
	}
	else
	{
		DMA->C1DST = (uint32_t)dstbuf;
		DMA->C1SRC = (uint32_t)srcbuf;
	}
	DMA_SetLen(ch,len);
	DMA_Start(ch);
}

void DMA_HANDLER(void)
{
	uint16_t sts;
	sts = DMA->STA;
	if((sts & 0x110)==0x110)
	{
		DMA->C0CTRL &= ~1;
		DMA->STA &=0x110;
		if(m_sserial1.send_pos!=m_sserial1.send_len)
		{
			DMA_Send(0,(uint8_t *)&(UART1->TXD),buf_pos+m_sserial1.send_pos, m_sserial1.send_len-m_sserial1.send_pos);
		}
		else
		{
			while((UART1->STA & 0x300)!=0x100) __NOP(); 
			while((UART1->STA&02)==0) __NOP();
			UART1->CTRL |=0x02;
		}
#if 0		
		udelay(2);
		m_sserial[0].send_len=0;
		UART1->STA |= 2;
		Set_RTS1(1);
#endif		
	}
	if((sts & 0x220)==0x220)
	{
		
		DMA->C1CTRL &= ~1;
		DMA->STA &=0x220;
		while((UART5->STA & 0x300)!=0x100) __NOP(); 
		while((UART5->STA&02)==0) __NOP();
		UART5->CTRL |=0x02;
#if 0			
		//udelay(100);
		m_sserial[1].send_len=0;
		UART5->STA |= 2;
		Set_RTS5(1);
#endif		
	}
	//DMA->STA = DMA->STA;
}

int8_t Serial_Open(uint8_t ch,uint32_t baud,uint8_t bits,uint8_t check)
{
	u32	ClkDiv;
	struct S_Serial_ *p_serial;
	if(ch>=MAX_UART_PORT)
		return 1;
	if(ch)
		p_serial = &m_sserial5;
	else
		p_serial = &m_sserial1;
	p_serial->send_pos=p_serial->rx_len=p_serial->rx_len=p_serial->rx_pos=0;
	ClkDiv = fnDl645MainClock_Get();
	ClkDiv=ClkDiv/(baud*16)-1;
	if(ch==0)
	{
		UART1->BAUD = ClkDiv;
		ClkDiv=1;
		if(bits==7)
			ClkDiv |= (2 << 5);
		else
			ClkDiv |= (3 << 5);
		ClkDiv |= (check<<7);
	//	ClkDiv |= (1 << 4);  //2 stopbits
		UART1->CTRL = ClkDiv;
	//	UART0->CTRL |=0x02;		//允许发送中断
		UART1->CTRL |=0x0c; 	//允许接收中断,允许接收错误中断
		UART1->STA = 0x02;		//清发送中断标志
	//	Init_RTS1();
		SET_UART1_RTS0;
		p_serial->serial_rx_buf = ch0_rx_buf;
		p_serial->serial_tx_buf = ch0_tx_buf;
	}
	else
	{
	//	NVIC_DisableIRQ(UART5_IRQn);
		UART5->BAUD = ClkDiv;
		ClkDiv=1;
		if(bits==7)
			ClkDiv |= (2 << 5);
		else
			ClkDiv |= (3 << 5);
		ClkDiv |= (check<<7);
	//	ClkDiv |= (1 << 4);  //2 stopbits
		UART5->CTRL = ClkDiv;
	//	UART0->CTRL |=0x02;		//允许发送中断
		UART5->CTRL |=0x0c; 	//允许接收中断,允许接收错误中断
		UART5->STA = 0x02;		//清发送中断标志
		Init_RTS5();
		SET_UART5_RTS0;
		p_serial->serial_rx_buf = ch1_rx_buf;
		p_serial->serial_tx_buf = 0;
	//	NVIC_EnableIRQ(UART5_IRQn);
	}
	DMA_Init(ch);
	return 0;
}

int16_t Serial_Write(uint8_t ch,uint8_t *buf,uint16_t len)
{
	struct S_Serial_ *p_serial;
	if(len==0)
		return 0;
	if(ch)
		p_serial = &m_sserial5;
	else
		p_serial = &m_sserial1;
	while(0!=p_serial->send_len) 
		//__NOP(); 
		udelay(1);

	if(ch)
		SET_UART5_RTS1;
	else
		SET_UART1_RTS1;
	p_serial->send_len=len;
	//udelay(10); //ok
	//udelay(100); //ok
	if(ch==0)
	{
		UART1->CTRL &=~(0x02);
		DMA_Send(0,(uint8_t *)&(UART1->TXD),buf, len);
		buf_pos = buf;
		m_sserial1.pre_len=0;	
		m_sserial1.rx_pos=0;
		m_sserial1.rx_len=0;
	}
	else
	{
		UART5->CTRL &=~(0x02);
		DMA_Send(1,(uint8_t *)&(UART5->TXD),buf, len);
	}
	return len;
}
uint16_t Serial_Read(uint8_t ch,uint8_t *buf,uint16_t len)
{
	uint16_t i;
	uint16_t buf_len;
	struct S_Serial_ *p_serial;
	i=0;
	if(ch)
	{
		p_serial = &m_sserial5;
		buf_len=SERIAL_CH1_LEN;
	}
	else
	{
		p_serial = &m_sserial1;
		buf_len = SERIAL_CH0_LEN;
	}
	while(p_serial->rx_len!=p_serial->rx_pos)
	{
		buf[i]=p_serial->serial_rx_buf[p_serial->rx_pos];
		p_serial->rx_pos++;
		p_serial->rx_pos%=buf_len;
		i++;
		if(i>=len || buf[i-1]==0x7e)
			break;
#pragma GCC push_options
#pragma GCC optimize ("O0")			
		if(p_serial->rx_len==p_serial->rx_pos)
			udelay(10);
#pragma GCC pop_options
	}
	len=i;
	return len;
}
uint16_t Serial_Status(uint8_t ch)
{
	if(ch)
		return m_sserial5.send_len;
	else
		return m_sserial1.send_len;
}
#if 0
void UART0_HANDLER(void)
{
	u32  status;
	status = UART0->STA;
	UART0->STA &= 0x3d;
	if(status&1)
//	while(UART0->STA&1)
	{		
		m_sserial.serial_rx_buf[m_sserial.rx_len]=UART0->RXD;
		UART0->STA |=1;
		m_sserial.rx_len++;
		m_sserial.rx_len%=SERIAL_BUFFER_LEN;
	}
	#if 0
	if(status&2)
	{	
		if(m_sserial.send_pos!=m_sserial.send_len)
		{
			UART0->TXD = m_sserial.serial_tx_buf[m_sserial.send_pos];
			m_sserial.send_pos++;
		}
		else
		{
			m_sserial.send_pos=0;
			m_sserial.send_len=0;
			GPIO->PBSET |= (1<<3);
		}			
	}
	#endif
	//UART0->STA = UART0->STA;
	return;
}
#endif
extern uint8_t mcu_busy;
extern uint32_t ms_count;
extern uint8_t i_Meter_Addr;
extern void HDLC_Send_RNR(void);
extern void HDLC_Send_UI(void);
void  HDLC_FAST_Rep(void)
{
		if(mcu_busy)
		{
			if(m_sserial1.pre_len>=10)
			{
				if(m_sserial1.serial_tx_buf[2]==9)
				{
					HDLC_Send_RNR();
				}
				if(m_sserial1.pre_len>=m_sserial1.serial_tx_buf[2])
				{
					HDLC_Send_UI();
				}
			}
		}
}
void UART1_HANDLER(void)
{
	u32  status;
	status = UART1->STA;
//	UART1->STA &= 0x3d;
	UART1->STA = UART1->STA;
	if(status&1)
//	while(UART0->STA&1)
	{
		//if(!mcu_busy)
		{	
			ms_count=0;
			m_sserial1.serial_rx_buf[m_sserial1.rx_len]=UART1->RXD;
		//UART1->STA |=1;
			m_sserial1.rx_len++;
			m_sserial1.rx_len%=SERIAL_CH0_LEN;
		}
	//	else
		if(mcu_busy)
		{
			if(m_sserial1.serial_tx_buf[0]!=0x7e)
			{
				m_sserial1.pre_len=0;
			}
			m_sserial1.serial_tx_buf[m_sserial1.pre_len]=UART1->RXD;
#if 0			
			if(m_sserial1.pre_len==3)
			{
				if((m_sserial1.serial_tx_buf[0]!=0x7e) || (m_sserial1.serial_tx_buf[1]!=0xa0) || (m_sserial1.serial_tx_buf[2]!=9))
				{
					m_sserial1.pre_len=0;
				}
			}
#endif			
			m_sserial1.pre_len++;
			m_sserial1.pre_len%=64;
#if 1		
			if(m_sserial1.pre_len>=10)
			{
				if(m_sserial1.serial_tx_buf[2]==9 && ((m_sserial1.serial_tx_buf[3]>>1)==i_Meter_Addr))
				{
					HDLC_Send_RNR();
					m_sserial1.pre_len=0;	
					m_sserial1.rx_pos=m_sserial1.rx_len;
				}
#if 0				
				if(m_sserial1.serial_tx_buf[2]==43 && (m_sserial1.pre_len>40))
				{
					HDLC_Send_UI();
					m_sserial1.pre_len=0;
				}
#endif				
#if 0				
				if(m_sserial1.serial_tx_buf[10]==0x7e)
				{
					m_sserial1.rx_pos=m_sserial1.rx_len;
					m_sserial1.pre_len=0;	
				}
				else
				{
					if(m_sserial1.pre_len>40)
					{
						HDLC_Send_UI();
						m_sserial1.pre_len=0;
					}
				}
#endif				
			}
#endif			
		}
#if 0		
		else
		{
			m_sserial1.pre_len=0;
		}
#endif
	}
	if(status&2)
	{	
		//UART1->STA |= 2;
		udelay(1);
		m_sserial1.send_len=0;
		SET_UART1_RTS0;
	}
	return;
}

void UART5_HANDLER(void)
{
	u32  status;
	status = UART5->STA;
//	UART5->STA &= 0x3d;
	UART5->STA = UART5->STA;
	if(status&1)
//	while(UART0->STA&1)
	{		
		m_sserial5.serial_rx_buf[m_sserial5.rx_len]=UART5->RXD;
		//UART5->STA |=1;
		m_sserial5.rx_len++;
		m_sserial5.rx_len%=SERIAL_CH1_LEN;
	}
	if(status&2)
	{	
		m_sserial5.send_len=0;
	//	UART5->STA |= 2;
		SET_UART5_RTS0;
	}
	return;
}
