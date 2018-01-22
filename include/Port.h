/************************************************************
	Port Define
************************************************************/
/************************************************************
	Port Define
************************************************************/

// UART5
#define PinMode_DualRX(x) 		( (x == GPIO_MODE_OUT) ? (GPIO->PMB &= 0xffffefff) : (GPIO->PMB |= 0x00001000) )	// P54
#define PinMode_DualTX(x) 		( (x == GPIO_MODE_OUT) ? (GPIO->PMB &= 0xffffdfff) : (GPIO->PMB |= 0x00002000) )	// P55
#if ( Threephase == YesCheck ) //ИэПа				
//Port 0
#define		P_APHS		0x01
#define		P_BPHS		0x02
#define		P_CPHS		0x04
#define 		P_LOWPOW	0x08
//#define		P_KEYPR	0x10

#define		PIN_APHS		GPIO->PA
#define		PIN_BPHS 		GPIO->PA
#define		PIN_CPHS		GPIO->PA
#define		PIN_LOWPOW	GPIO->PA
#define		PIN_KEYPR		GPIO->PA

//Port 1
//#define		P_KEYSF	 	0x0100
#define		P_KEYXF		0x0100
#define		P_KEYPR		0x0200

#define		PIN_KEYSF		GPIO->PA
#define		PIN_KEYXF 		GPIO->PA

//Port 2
#define		P_RXD485		0x010000
#define		P_TXD485		0x020000
#define		P_RXDHW		0x040000
#define 		P_TXDHW		0x080000

#define		P_RXD			0x400000
#define		P_TXD			0x800000

//Port 3
#define		P_KDJC			0x40000000   //131029
#define		P_KGJC			0x80000000	//131029

#define		PIN_KDJC		GPIO->PA
#define		PIN_KGJC		GPIO->PA


//Port 4
#define 		P_SETEN		0x01
#define 		P_CCJC			0x02		
#define		P_FLQH			0x04
#define		P_BKLED	 	0x08
#define		P_FlsCS			0x10
#define		P_FlsSCK		0x20
#define		P_FlsSDO		0x40
#define 		P_FlsSDI		0x80


#define		PIN_SETEN		GPIO->PB
#define		PIN_CCJC		GPIO->PB
#define		PIN_FLQH		GPIO->PB
#define		PDIR_BKLED		GPIO->PMB
#define		POUT_BKLED		GPIO->PB

#define    	 DF_CS		GPIO->PMB
#define		DF_SCK 		GPIO->PMB
#define		DF_SDO		GPIO->PB
#define		DF_SDI	 	GPIO->PMB

//Port 5
//#define		P_WGOUT		0x0100
//#define		P_YGOUT		0x0200

#define		P_SCL	 		0x0400
#define		P_SDA			0x0800
#define 	P_RELAY1OFF		0x1000
#define 	P_RELAY1ON			0x2000	

#define		P_YGOUT		0x4000
#define		P_YGLED		0x8000

#define		PDIR_SCL		GPIO->PMB	
#define		PDIR_SDA		GPIO->PMB
#define		PIN_SDA		GPIO->PB
#define		PDIR_RELAY1OFF	GPIO->PMB
#define		PDIR_RELAY1ON		GPIO->PMB
#define		POUT_RELAY1OFF	GPIO->PB
#define		POUT_RELAY1ON		GPIO->PB

//#define		PIN_YGOUT		GPIO->PB
//#define		PIN_WGOUT		GPIO->PB

#define		PDIR_YGOUT		GPIO->PMB	
#define		PDIR_YGLED		GPIO->PMB	

#else
//Port 0
//#define		P_APHS		0x01
//#define		P_BPHS		0x02
//#define		P_CPHS		0x04
#define 		P_LOWPOW	0x08
//#define		P_KEYPR	0x10

//#define		PIN_APHS		GPIO->PA
//#define		PIN_BPHS 		GPIO->PA
//#define		PIN_CPHS		GPIO->PA
#define		PIN_LOWPOW	GPIO->PA
//#define		PIN_KEYPR		GPIO->PA

//Port 1
#define		P_KEYXF	 	0x0100
#define		P_KEYPR		0x0200

#define		PIN_KEYXF		GPIO->PA
#define		PIN_KEYPR 		GPIO->PA

//Port 2
#define		P_RXD485		0x010000
#define		P_TXD485		0x020000
#define		P_RXDHW		0x040000
#define 		P_TXDHW		0x080000

//#define		P_RXD			0x400000
//#define		P_TXD			0x800000

//Port 3
#define		P_KDJC			0x40000000   //131029
#define		P_KGJC			0x80000000	//131029

#define		PIN_KDJC		GPIO->PA
#define		PIN_KGJC		GPIO->PA


//Port 4
#define 		P_SETEN		0x01
#define 		P_CCJC			0x02		
#define		P_FLQH			0x04
#define		P_BKLED	 	0x08
#define		P_FlsCS			0x10
#define		P_FlsSCK		0x20
#define		P_FlsSDO		0x40
#define 	P_FlsSDI		0x80


#define		PIN_SETEN		GPIO->PB
#define		PIN_CCJC		GPIO->PB
#define		PIN_FLQH		GPIO->PB
#define		PDIR_BKLED		GPIO->PMB
#define		POUT_BKLED		GPIO->PB

#define    	 DF_CS		GPIO->PMB
#define		DF_SCK 		GPIO->PMB
#define		DF_SDO		GPIO->PB
#define		DF_SDI	 	GPIO->PMB

//Port 5
//#define		P_YGOUT		0x0100
//#define		P_WGOUT		0x0200

#define		P_YGLED		0x0100
#define		P_SCL	 		0x0400
#define		P_SDA			0x0800
#define 	P_RELAY1OFF		0x1000
#define 	P_RELAY1ON			0x2000	
//#define		P_KDJC			0x8000

#define		P_YGOUT			0x4000
//#define		P_YGLED			0x8000


#define		PDIR_SCL		GPIO->PMB	
#define		PDIR_SDA		GPIO->PMB
#define		PIN_SDA		GPIO->PB
#define		PDIR_RELAY1OFF	GPIO->PMB
#define		PDIR_RELAY1ON		GPIO->PMB
#define		POUT_RELAY1OFF	GPIO->PB
#define		POUT_RELAY1ON		GPIO->PB
//#define		PIN_KDJC		GPIO->PB

//#define		PIN_YGOUT		GPIO->PB
//#define		PIN_WGOUT		GPIO->PB		

#define		PDIR_YGOUT		GPIO->PMB	
#define		PDIR_YGLED		GPIO->PMB	
#endif	

