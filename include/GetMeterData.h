#ifndef _GETMETERDATA_H
#define _GETMETERDATA_H

extern void SynData1s (void);
extern int ID_Read( unsigned char* RAM_Dest,unsigned int ID_Src, int Lenth );
extern int ID_Write( unsigned int ID_Dest, unsigned char* RAM_Src, int Lenth);

#endif
