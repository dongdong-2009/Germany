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
	//UART0����RS485��1ͨѶ.
	UART5->BAUD = ClkDiv;
	UART5->CTRL = (1 << 0)	|   /* uart enable */
                  (3 << 5)	|	/* data bit: 8 */
//                  (2 << 5)	|	/* data bit: 7 */
                  (2 << 7);	/* even  */
	//GPIO->PCA0 |=0x02000000;		//GPIOѡ��UART0
	PinMode_DualRX(GPIO_MODE_IN);
	PinMode_DualTX(GPIO_MODE_OUT);
//	Comm8213.Ptr8213=0;

			UART5->CTRL &=0xfffd;		//���η����ж�
			UART5->STA = 0x02;		//�巢���жϱ�־
		
			UART5->CTRL |=0x0c; 	//��������ж�,������մ����ж�
			UART5->STA = 0x3d;		//������жϱ�־�����մ����־
	return;
}
#if 0
//����CCITT-CRC16.��ǰ��CRC-CCITT��ITU��ǰ����CCITT����//
//����ĳ�ֵ��0XFFFF������ú���0XFFFF���					//
//ͨ���н��յ�CRC	ֵ�ǵ���ǰ�����ں��,//
//��ֵ����ͨ��ʱ�ıȽ�ʱҪ��һ�£����ֽ�����ֽڣ�//
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
