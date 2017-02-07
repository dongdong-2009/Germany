
/**********************************************************************
	Memory copy in RAM
**********************************************************************/
void RAM_Write( unsigned char *Dest, unsigned char *Src, short Len )
{
   while ( Len>0 ){
      *Dest = *Src;
      Dest++;
      Src++;
      Len--;
   }
}

void RAM_Write_Dev( unsigned char *Dest, unsigned char *Src, short Len )	//反过来复制
{
   while ( Len>0 ){
      *(Dest+ Len- 1) = *(Src+ Len- 1);
      Len--;
   }
}

///////数据倒过来搬运，高到低，低到高
void RAM_WriteInter( unsigned char *Dest, unsigned char *Src, short Len )
{
   Dest += (Len - 1);
   while ( Len>0 ){
      *Dest = *Src;
      Dest--;
      Src++;
      Len--;
   }
}

/**********************************************************************
	Fill a Data in RAM block
**********************************************************************/

void RAM_DataFill( unsigned char* Dest, short Len, unsigned char Data)
{
   while( Len>0 ){
      *Dest++ = Data;
      Len--;
   }
}

void RAM_Fill( unsigned char* Dest, short Len)
{
   while( Len>0 ){
      *Dest++ = 0;
      Len--;
   }
}

/**********************************************************************
	BCD Data Compare
**********************************************************************/
short Data_Comp(unsigned char *Data1, unsigned char *Data2, short Len)
{
   Data1+=Len-1;
   Data2+=Len-1;
   while( Len>0 ){
      if( (*Data1)>(*Data2) ) return 1;
      if( (*Data1)<(*Data2) ) return -1;
      Len--;
      Data1--;
      Data2--;
   }
   return 0;
}
