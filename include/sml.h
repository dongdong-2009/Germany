#ifndef __SML_H__
#define __SML_H__
#include <stdint.h>
typedef struct
{
	uint8_t LayerNum; //层数
	uint8_t Flag;//解析标识
	uint8_t AbortOnError;//中断错误标识
	uint8_t GroupNo;//数据包组数
	uint8_t record_num;
	uint16_t StartAdd;//起始地址
	uint16_t OrderAdd;//SML message (这一层前一层的位置)
	uint16_t OrderEndAdd;//SML message (这一层最后的位置)
	uint16_t EndAdd;//结束地址
	uint16_t SMLOrder;//命令
}SMLRECORD;

typedef struct
{
	uint16_t 		OLStartAdd;//命令层起始地址
	uint16_t	 	OLLength;//命令层长度
}ORDERRECORD;
//Flag;//解析标志//
#define	F_SOrR 			0x0001	//接收还是发送标志,0,接收,1发送//
#define	F_SendRequest 		0x0002	//request接收还是发送标志,0,接收,1发送//
#define	F_SendEvent 		0x0004	//事件发送标志位
#define	F_CRCEvent 		0x0008	//事件发送时总CRC标志位
#define	F_SendOpenClose		0x0010	//只发送OPEN CLOSE
#define	F_MCRC_Err 		0x0020	//事件发送时总CRC标志位
#define	F_AnalyseSML_OK		0x0040	//事件发送时总CRC标志位
#define	F_ClientAdd4		0x0080	//ClientID增加4位1B处理标志
#define	F_Client1BCRC		0x0100	//ClientID增加4位1B 后的crc处理标志
#define	F_Attention_Fall	0x0200	//事件发送时总CRC标志位
#define	F_Attention_Open	0x0400	//事件发送时总CRC标志位
#define	F_Attention_List	0x0800	//事件发送时总CRC标志位
#define	F_Attention_Only	0x1000	//只发送attention
#define	F_Attention_NotDoneGroup	0x2000	//同一个group都不响应
#define	F_Attention_NotDoneALL	0x4000	//后续的都不响应
#define	F_Attention_ERR17	0x8000	//ERR17
typedef struct
{
	uint32_t SendEventDataNum;//发送event数据个数
	uint32_t SendEventNum;//发送event条数
	uint8_t SLayerNumR;//当前记录的层数//
	uint8_t LayerNumR;//当前记录的层数//
	uint8_t LayerNumA;//当前解析的层数//
	uint8_t *RecBuf;//RecBuf[1048];//接收缓冲区//
	uint16_t RecLg;//接收长度//
	uint16_t RecLgA;//接收数据的已解析长度//
//	uint8_t SendBuf[1048];//发送缓冲区//
	uint8_t *SendBuf;
	uint16_t SendLg;//发送长度//
	uint16_t NeedSendLg;//需要发送长度//
	uint16_t SendPtr;//发送缓冲区的填写位置//
	uint16_t AnaOrderAd;//解析完一个命令后命令在缓冲区中的位置//
	uint16_t MSBSendLg;//MSB发送长度//
	
	uint16_t OpenClientID1BPrt;//client ID 1B 数据位置//
	
	uint16_t MSBNeedSendLg;//MSB需要发送长度//
	uint16_t Flag;//解析标志//
	uint16_t OpenFlag;//解析Open内数据状态标志//
	uint8_t MSBTime;//MSB时间//
	uint8_t	EndNum;
	uint8_t WrongTypeNum;
		
}SMLCOMM;


typedef struct
{
	uint16_t Order;// 通信命令//
	uint8_t DataLayer;//数据的层数//
		
}SMLORDER;


typedef struct
{
	uint8_t	OBIS0;
	uint8_t	OBIS1;
	uint8_t	OBIS2;
	uint8_t	OBIS3;
	uint8_t	OBIS4;
	uint8_t	OBIS5;
	
	uint8_t	Len;
	uint8_t	OBISType;
	uint32_t	Adder;
	uint16_t	State;
	uint16_t Class;
	uint8_t Scale;
	uint8_t Unit;
	uint8_t (*CallBefore)(unsigned char *input,unsigned char *ouput);
	uint8_t (*CallBack)(uint16_t Flag);
}SMLOBISTAB;

typedef struct
{
	uint8_t	OBIS0;
	uint8_t	OBIS1;
	uint8_t	OBIS2;
	uint8_t	OBIS3;
	uint8_t	OBIS4;
	uint8_t	OBIS5;
}SMLATTENTIONNUMBER;

/**********************************
define	the SML Order
***********************************/
#define Open_Req		0x0100
#define Open_Res		0x0101
#define Close_Req		0x0200
#define Close_Res		0x0201
#define GetProfP_Req		0x0300
#define GetProfP_Res		0x0301
#define GetProfL_Req		0x0400
#define GetProfL_Res		0x0401
#define GetPropP_Req		0x0500
#define GetPropP_Res		0x0501
#define SetPropP_Req		0x0600
#define SetPropP_Res		0x0601	
#define GetL_Req		0x0700
#define GetL_Res		0x0701	
#define Att_Res			0xff01


////////////////////////////////////
// 报文数据指针
#define	MSB_SecCNT		91//85//81
#define	MSB_180			154//148//142
#define	MSB_181			175//169//171//165//142
#define	MSB_182			196//190//194//188//165
#define	MSB_ABCPower		217//211//215//209//186

#define	MSB_StatusWord0		146//140//134
#define	MSB_StatusWord1		169//163//157//134
#define	MSB_StatusWord2		192//186//180//157
#define	MSB_StatusWord3		294//288//292//286//263

#define	MSB_ServerID1		35//35//398//374
#define	MSB_ServerID2		70//70//408//374
#define	MSB_ServerID3		126//120
#define	MSB_PublicKey		236//230//234//408//374
#define	MSB_SignatureData	323//317//321//408//374

#define	MSB_OpenCRC		48//48//46
#define	MSB_ListCRC		374//368//372//366//343
#define	MSB_CloseCRC		396//390//394//388//365
#define	MSB_EndCRC1		408//402//404//398//374
#define	MSB_EndCRC2		416//410//414//408//374

#define	MSB_MessageHead		95//89//85
#define	MSB_Message1_11_0	285//279//283//277//254		

#define	MSB_NeedSendNum1	407//403//405//399//375
#define	MSB_NeedSendNum2	323//315//321//315//289
////////////////////////////////////////

#define	Order0100 0x00
#define	OrderNot0100 0x01

#define	MaxOBISNum		90+20+4+5//0x07	//通讯命令数
#define	MaxOBISNumSet		8//0x03
#define	MaxAttentionNum		22//0x03



#define RAM_INTER_TYPE 0x60
#define RAM_TYPE 0x70
#define E2P_TYPE 0x80
#define FUN_TYPE 0x90


#define Unit_a   	1	        //a      	 	// 	时间             	年
#define Unit_mo  	2	       	//mo          	//	时间              	月
#define Unit_wk  	3	       	//wk       	   	//	时间              	周              7*24*60*60s
#define Unit_d   	4	       	//d            	//	时间              	日              24*60*60 s
#define Unit_h   	5	       	//h        	   	//	时间             	小时            60 *60 s
#define Unit_min	6	       	//min.     	   	//	时间              	分              60 s
#define Unit_s   	7	     	    //s       	   	//	时间(t)            	秒              s
#define Unit_deg	8	 	   	    //°          	//	(相)角             	度              rad*180/π
#define Unit_Cel	9	   	   	  //0C         	//	温度(Θ)          	摄氏度          K-273.15
#define Unit_m3_h	15	   	    //(15)	       m3/h  		//	流量                                m3 /（60*60s）
#define Unit_W   	27	       	//W          	//	有功功率 （P）     	瓦              W = J/s
#define Unit_VA  	28	    	  //VA         	//	视在功率（S）   	
#define Unit_var 	29	  		  //var         	//	无功功率（Q）
#define Unit_Wh  	30	        //Wh         	//	有功能量                            W*(60*60s) 
#define Unit_VAh 	31	        //VAh         	//	视在能量                            VA*(60*60s)
#define Unit_varh	32	        //varh      	//	无功能量                            var*(60*60s)
#define Unit_A   	33	        //A         	//	电流（I）           安培            A
#define Unit_V   	35	        //V         	//	电压（U）          	伏特            V 
#define Unit_Hz  	44	        //Hz        	//	频率               	赫兹            1 /s
#define Unit_Rac 	45         	//Rac         	//	有功能量表常数                      1/（Wh）
#define Unit_Rre 	46    	    //Rre         	//	无功能量表常数
#define Unit_Rap 	47         	//Rap       	//	视在能量表常数
#define Unit_V2_h	48         	//V2/h        	// 	伏特平方小时                   		V2(60*60s)
#define Unit_A2_h	49         	//A2/h   		// 	安培平方小时                   		A2(60*60s)
#define Unit_FF		255    		  //计数        	//	无单位，缺单位，计数

#define Len1	0x01
#define Len2	0x02
#define Len3	0x03
#define Len4	0x04
#define Len5	0x05
#define Len6	0x06
#define Len7	0x07
#define Len8	0x08
#define Len9	0x09
#define Len10	0x0A

//////////////////////////////////
/// error numbers
//////////////////////////////////
#define ReturnERR00	0x00
#define ReturnERR01	0x01
#define ReturnOK		0x02
#define ReturnERR03	0x03	//fail
#define ReturnERR04	0x04	//attention
#define ReturnERR05	0x05
#define ReturnERR06	0x06
#define ReturnERR07	0x07
#define ReturnERR08	0x08
#define ReturnERR09	0x09
#define ReturnERR10	0x0A
#define ReturnERR11	0x0B
#define ReturnERR12	0x0C
#define ReturnERR13	0x0D
#define ReturnERR14	0x0E
#define ReturnERR15	0x0F	//not done
#define ReturnERR16	0x10
#define ReturnERR17	0x11
#define ReturnERR18	0x12
#define ReturnERR19	0x13
#define ReturnERR20	0x14
#define ReturnERR21	0x15
#define ReturnERR22	0x16
#define ReturnERR23	0x17


#define SML_STR_CODE 	0x00
#define SML_BOOL_CODE 0x40
#define SML_INT_CODE  0x50
#define SML_UINT_CODE 0x60
#define SML_LIST_CODE 0x70

//OpenFlag
#define	F_ServerID_No		0x0001	//open中的serverID 为空//
#define	F_Username_No		0x0002	//open中的Username为空//
#define	F_Password_No		0x0004	//open中的Password为空//

void CmSet_SML_Recevie_Buf(uint8_t *buf,uint16_t len);
uint16_t CmGet_SML_Send_Buf(uint8_t *buf);
//收到命令后的解析命令,入口:表格指针,长度,出口:长度不全返回0,出错返回-1,正确返回1//
signed AnalyseOrder(uint16_t BufAd,uint16_t DataLg,uint8_t LayerNo);
//解析一个SML,MESSAGE结构入口:表格指针,数据长度,层号(当前处理到的SML MESSAGE)//
//出口:长度不全返回0,出错返回-1,正确返回1//
signed AnalyseSMLMes(uint16_t BufAd,uint16_t DataLg,uint8_t LayerNo);
uint16_t DoCrc16(uint16_t RegInit, uint8_t *message, uint16_t len);
//CRC16返回两字节的结果，按通信的顺序//
void DoCrc161(uint8_t *Dest,uint16_t RegInit, uint8_t *message, uint16_t len);
//只是解析数据，不填写发送数据//
void AnalyseSMLData(void);
//解析当上次解析与本次解析中间没有数据进来时退出//
//当总的接收数据小于接收到第一个SML MESSAGE的76时退出//
void AnalyseSML(uint8_t *sendbuf);
//SML通信的初始化//
void	SMLCommInit(void);
//发送缓冲区中的头的填写//
void	WriteSendBufStr(void);
void	WriteSendBufEnd(uint8_t Num0);
//根据命令准备数据//
void GetSendData(void);
void	OpenRes(void);
void	CloseRes(void);
void	GetProfPRes(void);
void	GetProfLRes(void);
void	GetPropPRes(void);
void SetPropPRes(void);
void GetLRes(void);
//解析一个命令，返回命令的层数，//
//每一层的数据的启始地址与数据长度在OrderRecord[]中//
//当层数有嵌套时,层数会加上嵌套的层数//
uint8_t 	AnaOrderData(uint16_t StartAdd,uint8_t OrerType);
//搜查找表得出OBIS的类型号//
uint8_t SearchOBIS(uint8_t *POBIS);
//填写GETlist事件数据//
void DoProPListOBIS(void);
uint8_t DoDeviceIdentification(void);
//根据OBIS码的类型填写SET数据//
uint8_t DoProSOBIS(uint8_t OBISNo);
//对设置返回一个正确的响应//
void	ReturnSetOK(uint8_t Number);
//attention number//
void ReturnAttentionNumber(uint8_t Number);
uint8_t DoProPOBIS(uint8_t OBISNo);
#ifdef __cplusplus
extern "C"
{
#endif
typedef uint8_t (*sml_function)(uint16_t Flag);
typedef uint8_t (*sml_beforefun)(unsigned char *input,unsigned char *ouput);
#ifdef __cplusplus
} /* end of extern "C" */
#endif

short E2P_RData( unsigned char* RAM_Dest,unsigned short E2P_Src,  short Lenth );
short E2P_WData( unsigned short E2P_Dest, unsigned char* RAM_Src,  short Lenth );
void InitPara(void);
void RAM_Write( unsigned char *Dest, unsigned char *Src, short Len );
void RAM_DataFill( unsigned char* Dest, short Len, unsigned char Data);
void RAM_WriteInter( unsigned char *Dest, unsigned char *Src, short Len );
short Data_Comp(unsigned char *Data1, unsigned char *Data2, short Len);
#endif
