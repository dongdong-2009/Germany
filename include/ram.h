#ifndef __RAM_H__
#define __RAM_H__
void RAM_Write( unsigned char *Dest, unsigned char *Src, short Len );
void RAM_Write_Dev( unsigned char *Dest, unsigned char *Src, short Len );	//反过来复制
void RAM_WriteInter( unsigned char *Dest, unsigned char *Src, short Len );
void RAM_DataFill( unsigned char* Dest, short Len, unsigned char Data);
void RAM_Fill( unsigned char* Dest, short Len);
short Data_Comp(unsigned char *Data1, unsigned char *Data2, short Len);

#endif
