//#include "Drive_Lib.h"
#include "aes.h"
#include "RN8215.h"

extern void SystemDelay(unsigned short t);

/* For CMAC Calculation */
  unsigned char const_Rb[16] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87
  };
  unsigned char const_Zero[16] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
	/*uint8_t iv[16]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};*/
	
void xor_128(unsigned char *a, unsigned char *b, unsigned char *out)
{
	int i;
	for (i=0;i<16; i++)
	{
			out[i] = a[i] ^ b[i];
	}
}

void leftshift_onebit(unsigned char *input,unsigned char *output)
  {
      int         i;
      unsigned char overflow = 0;

      for ( i=15; i>=0; i-- ) {
          output[i] = input[i] << 1;
          output[i] |= overflow;
          overflow = (input[i] & 0x80)?1:0;
      }
      return;
  }

void m_SubKeyGenerate(uint8_t *Key,uint8_t K1[16],uint8_t K2[16])
{
	uint8_t L[16];
	unsigned char tmp[16];
	AES_128(Key,const_Zero,L);
	if ( (L[0] & 0x80) == 0 ) { /* If MSB(L) = 0, then K1 = L << 1 */
          leftshift_onebit(L,K1);
      } else {    /* Else K1 = ( L << 1 ) (+) Rb */
          leftshift_onebit(L,tmp);
          xor_128(tmp,const_Rb,K1);
      }
	if ( (K1[0] & 0x80) == 0 ) {
          leftshift_onebit(K1,K2);
      } else {
          leftshift_onebit(K1,tmp);
          xor_128(tmp,const_Rb,K2);
      }
      return;
}

void padding ( unsigned char *lastb, unsigned char *pad, int length )
	{
		int         j;
      /* original last block */
		for ( j=0; j<16; j++ ) {
			if ( j < length ) {
				pad[j] = lastb[j];
			} else if ( j == length ) {
              pad[j] = 0x80;
          } else {
              pad[j] = 0x00;
          }
      }
  }


void AES_CMAC ( unsigned char *key, unsigned char *input, int length,
                  unsigned char *mac )
  {
      unsigned char       X[16],Y[16], M_last[16], padded[16];
      unsigned char       K1[16], K2[16];
      int         n, i, flag;
     // generate_subkey(key,K1,K2);
			m_SubKeyGenerate(key,K1,K2);
      n = (length+15) / 16;       /* n is number of rounds */

      if ( n == 0 ) {
          n = 1;
          flag = 0;
      } else {
          if ( (length%16) == 0 ) { /* last block is a complete block */
              flag = 1;
          } else { /* last block is not complete block */
              flag = 0;
          }
			}

      if ( flag ) { /* last block is complete block */
          xor_128(&input[16*(n-1)],K1,M_last);
      } else {
          padding(&input[16*(n-1)],padded,length%16);
          xor_128(padded,K2,M_last);
      }

      for ( i=0; i<16; i++ ) X[i] = 0;
      for ( i=0; i<n-1; i++ ) {
          xor_128(X,&input[16*i],Y); /* Y := Mi (+) X  */
         AES_128(key,Y,X);      /* X := AES-128(KEY, Y); */
      }

      xor_128(X,M_last,Y);
      AES_128(key,Y,X);
			
      for ( i=0; i<16; i++ ) {
          mac[i] = X[i];
      }
  }

void AES_128(uint8_t * pkey,uint8_t *input,uint8_t *output)
{
	int16_t k,i,pcipher;
	uint32_t tmp_cix;
	AES_ENC->CTL=0;
	AES_ENC->CTL =0;
	for (i = 0; i < 8; i ++) 
	{
		if(i<4)
		{
			tmp_cix=pkey[i*4+3];
			tmp_cix |= (pkey[i*4+2]<<8);
			tmp_cix |= (pkey[i*4+1]<<16);
			tmp_cix |= (pkey[i*4]<<24);
			AES_ENC->KEY[3-i] = tmp_cix;
		}
		else
			AES_ENC->KEY[i] = 0;
  } 
	
  while(((AES_ENC->STA) & 2) != 0)
			WDT->EN = 0xbb;

	//AES_ENC->CTL = (1<<4)|0x3;//CBC
	//AES_ENC->CTL = 0x3;//EBC
	for(i=0;i<4;++i)
	{
		for(k=0,tmp_cix=0;(k<4);++k)
		{
				tmp_cix |= (input[i*4+k]<<((3-k)*8));
		}
		AES_ENC->PT[3-i] = tmp_cix;
		AES_ENC->IV[i] = 0;
	}  
	while(((AES_ENC->STA) & 2) != 0)
		WDT->EN = 0xbb;	
	//AES_ENC->CTL = (1<<4);	
	AES_ENC->CTL |= 0x1;//EBC
	SystemDelay(5);
	while((AES_ENC->STA&0x1)==0x0)
		WDT->EN = 0xbb;
	for (i = 0; i < 4; i ++) 
	{
		output[(3-i)*4+3] = AES_ENC->CT[i];
		output[(3-i)*4+2] = (AES_ENC->CT[i]>>8)&0xff;
		output[(3-i)*4+1] = (AES_ENC->CT[i]>>16)&0xff;	
		output[(3-i)*4] = (AES_ENC->CT[i]>>24)&0xff;					
	}
}
int16_t CmEnAES128(uint8_t * pkey,uint8_t *iv,uint8_t *pOutTag,uint8_t *data,uint16_t len,uint8_t *pOutCiphertext)
{
	int16_t ret;
	uint8_t i,k,b_padding;
	int16_t j,pcipher;
	uint32_t tmp_cix;
 
	AES_ENC->CTL=0;
	AES_ENC->CTL=0;
	pcipher=0;
	for (i = 0; i < 8; i ++) 
	{
		if(i<4)
		{
			tmp_cix=pkey[i*4+3];
			tmp_cix |= (pkey[i*4+2]<<8);
			tmp_cix |= (pkey[i*4+1]<<16);
			tmp_cix |= (pkey[i*4]<<24);
			AES_ENC->KEY[3-i] = tmp_cix;
		}
		else
			AES_ENC->KEY[i] = 0;
  } 
	
/*  for (i = 0; i < 4; i ++) 
	{
		if(iv)
		{
			tmp_cix=iv[i*4+3];
			tmp_cix |= (iv[i*4+2]<<8);
			tmp_cix |= (iv[i*4+1]<<16);
			tmp_cix |= (iv[i*4]<<24);
		}
		else
			tmp_cix=0;
    AES_ENC->IV[3-i] = tmp_cix;
  }	*/
//  while(((AES_ENC->STA) & 2) != 0)
	//		WDT->EN = 0xbb;

	AES_ENC->CTL = (1<<4)|0x3;//CBC
	//AES_ENC->CTL = 0x3;//EBC
	for (i = 0; i < 4; i ++) 
	{
		if(iv)
		{
			tmp_cix=iv[i*4+3];
			tmp_cix |= (iv[i*4+2]<<8);
			tmp_cix |= (iv[i*4+1]<<16);
			tmp_cix |= (iv[i*4]<<24);
		}
		else
			tmp_cix=0;
    AES_ENC->IV[3-i] = tmp_cix;
  }
	
	for(j=0;j<len;)
//	for(j=0;j<=len;)  //2017.2.14 modified
	{
		if(j>0)
		{
			for(i=0;i<4;++i)
			{
				AES_ENC->IV[i] = AES_ENC->CT[i];
			}
		}
		if((j+16)>len)
		{
			b_padding=j+16-len;
		}
	/*	if((j+15)>len)
		{
			b_padding=j+15-len;
		}*/
		for(i=0;i<4;++i)
		{
			for(k=0,tmp_cix=0;(k<4);++k)
			{
				if(j<len)
					tmp_cix |= (data[k+j]<<((3-k)*8));
				else
				{/*	tmp_cix |= (0<<((3-k)*8));*/
					/*if(b_padding==0)
					{
						 b_padding=16-(i*4+k);
					}*/
					tmp_cix |= (b_padding<<((3-k)*8));
				}
			}
			j+=4;
			AES_ENC->PT[3-i] = tmp_cix;
		}   

		SystemDelay(5);
		while((AES_ENC->STA&0x1)==0x0)
			WDT->EN = 0xbb;
		if(pOutCiphertext)
		{
			for (i = 0; i < 4; i ++) 
			{
				pOutCiphertext[pcipher++] = (AES_ENC->CT[3-i]>>24)&0xff;
				pOutCiphertext[pcipher++] = (AES_ENC->CT[3-i]>>16)&0xff;
				pOutCiphertext[pcipher++] = (AES_ENC->CT[3-i]>>8)&0xff;	
				pOutCiphertext[pcipher++] =  AES_ENC->CT[3-i];					
			}
		}
	}
	if(pOutTag)
	{
		for (i = 0; i < 4; i ++) 
		{	
			pOutTag[i*4] = (AES_ENC->CT[3-i]>>24)&0xff;
			pOutTag[i*4+1] = (AES_ENC->CT[3-i]>>16)&0xff;
			pOutTag[i*4+2] = 	(AES_ENC->CT[3-i]>>8)&0xff;
			pOutTag[i*4+3] = AES_ENC->CT[3-i];				
		}
	}
	ret=pcipher;
	return ret;
}


int16_t CmDeAES128(uint8_t * pkey,uint8_t *iv,uint8_t *pOutTag,uint8_t *data,uint16_t len,uint8_t *ptx)
{
	int16_t ret;
	uint8_t i,k;
	int16_t j,pcipher;
	uint32_t tmp_cix;

	AES_DEC->CTRL=0;
	AES_DEC->CTRL=0;
	pcipher=0;
	for (i = 0; i < 8; i ++) 
	{
		if(i<4)
		{
			tmp_cix=pkey[i*4+3];
			tmp_cix |= (pkey[i*4+2]<<8);
			tmp_cix |= (pkey[i*4+1]<<16);
			tmp_cix |= (pkey[i*4]<<24);
			AES_DEC->KEY2[3-i] = tmp_cix;
		}
		else
			AES_DEC->KEY2[i] = 0;
  } 
  for (i = 0; i < 4; i ++) 
	{
		if(iv)
		{
			tmp_cix=iv[i*4+3];
			tmp_cix |= (iv[i*4+2]<<8);
			tmp_cix |= (iv[i*4+1]<<16);
			tmp_cix |= (iv[i*4]<<24);
		}
		else
			tmp_cix=0;
    AES_DEC->IV[3-i] = tmp_cix;
  }	
 // while(((AES_DEC->STAT) & 2) != 0)
	//		WDT->EN = 0xbb;

	AES_DEC->CTRL = (1<<4)| 0x3;//CBC
	//AES_DEC->CTRL = 0x3;//EBC
	for (i = 0; i < 4; i ++) 
	{
		if(iv)
		{
			tmp_cix=iv[i*4+3];
			tmp_cix |= (iv[i*4+2]<<8);
			tmp_cix |= (iv[i*4+1]<<16);
			tmp_cix |= (iv[i*4]<<24);
		}
		else
			tmp_cix=0;
    AES_DEC->IV[3-i] = tmp_cix;
  }	
	for(j=0;j<len;)
	{
		if(j>0)
		{
			for(i=0;i<4;++i)
			{
				AES_DEC->IV[i] = AES_DEC->PT[i];
			}
		}
		for(i=0;i<4;++i)
		{
			for(k=0,tmp_cix=0;(k<4);++k)
			{
				if(j<len)
					tmp_cix |= (data[j+k]<<((3-k)*8));
				else
					tmp_cix |= (0<<((3-k)*8));
			}
			j+=4;
			AES_DEC->CT[3-i] = tmp_cix;
		}
		
		SystemDelay(5);
		while((AES_DEC->STAT&0x1)==0x0)
			WDT->EN = 0xbb;
		if(ptx)
		{
			for (i = 0; i < 4; i ++) 
			{
				ptx[pcipher++] = (AES_DEC->PT[3-i]>>24)&0xff;
				ptx[pcipher++] = (AES_DEC->PT[3-i]>>16)&0xff;	
				ptx[pcipher++] = (AES_DEC->PT[3-i]>>8)&0xff;
				ptx[pcipher++] = AES_DEC->PT[3-i];
			}
		}
	}
	if(pOutTag)
	{
		for (i = 0; i < 4; i ++) 
		{
			pOutTag[i*4] = (AES_DEC->PT[3-i]>>24)&0xff;
			pOutTag[i*4+1] = (AES_DEC->PT[3-i]>>16)&0xff;	
			pOutTag[i*4+2] = (AES_DEC->PT[3-i]>>8)&0xff;
			pOutTag[i*4+3] = 	AES_DEC->PT[3-i];		
		}
	}
	ret=pcipher;
	return ret;
}

void CM_Mess2020_Key_Calculate(uint8_t *mk,uint8_t type,uint32_t C,uint8_t *m_Id,uint8_t *Key)
{
	uint8_t message[32];
	int i;
	message[0] = type;
	for(i=0;i<4;++i)
	{
		//message[i+1] = (C >> (i*8))&0xff;
		message[i+1] = (C >> ((3-i)*8))&0xff;
	}
#if 1
/*	for(i=0;i<10;++i)
	{
		message[i+5] = m_Id[9-i];
	}*/
	for(i=0;i<10;++i)
	{
		message[i+5] = m_Id[i];
	}
	message[15] = 0x01;
	AES_CMAC(mk,message,16,Key);
#else
/*	for(i=0;i<14;++i)
	{
		message[i+5] = m_Id[13-i];
	}*/
	
/*	for(i=0;i<4;++i)
	{
		message[i+5] = 0;
	}
	for(i=0;i<10;++i)
	{
		message[i+9] = m_Id[i];
	}*/
/*	for(i=0;i<14;++i)
	{
		message[i+5] = m_Id[i];
	}*/
	
	for(i=0;i<4;++i)
	{
		message[i+5] = 0;
	}
	for(i=0;i<10;++i)
	{
		message[i+9] = m_Id[9-i];
	}
	for(i=0;i<13;++i)
	{
		message[19+i] = 13;
	}
	AES_CMAC(mk,message,32,Key);
#endif
	
}