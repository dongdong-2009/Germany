
#ifndef  _DRIVE_LIB_H
#define  _DRIVE_LIB_H

#ifdef   _DRIVE_LIB_GLOBALS
	#define  DRIVE_LIB_EXT
#else
	#define  DRIVE_LIB_EXT  extern 
#endif
#define DL645SOFT_DEBUG		0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <RN8215.h>
#include <Dat_Types.h>
#include <Dl645_Types.h>

#include <MyMath.h>
#include <sysctrl.h>
#include <rtc.h>
#include <nvm.h>
#include <SystemInit.h>
//#include <Uart.h>
#include <Drive_Clock.h>

#include <Drive_AllINT.h>

#include <Fm24Cxx.h>
#include <RTCDrive.h>

#include <Key.h>
#include <LcdDrive.h>

//===引用的全局变量声明================================
extern u16					SysStamp;				//在Dl645_Globals.h中定义。


#endif	//_DRIVE_LIB_H


