#ifndef __SML_H__
#define __SML_H__
#include <stdint.h>
typedef struct
{
	uint8_t LayerNum; //����
	uint8_t Flag;//������ʶ
	uint8_t AbortOnError;//�жϴ����ʶ
	uint8_t GroupNo;//���ݰ�����
	uint8_t record_num;
	uint16_t StartAdd;//��ʼ��ַ
	uint16_t OrderAdd;//SML message (��һ��ǰһ���λ��)
	uint16_t OrderEndAdd;//SML message (��һ������λ��)
	uint16_t EndAdd;//������ַ
	uint16_t SMLOrder;//����
}SMLRECORD;

typedef struct
{
	uint16_t 		OLStartAdd;//�������ʼ��ַ
	uint16_t	 	OLLength;//����㳤��
}ORDERRECORD;
//Flag;//������־//
#define	F_SOrR 			0x0001	//���ջ��Ƿ��ͱ�־,0,����,1����//
#define	F_SendRequest 		0x0002	//request���ջ��Ƿ��ͱ�־,0,����,1����//
#define	F_SendEvent 		0x0004	//�¼����ͱ�־λ
#define	F_CRCEvent 		0x0008	//�¼�����ʱ��CRC��־λ
#define	F_SendOpenClose		0x0010	//ֻ����OPEN CLOSE
#define	F_MCRC_Err 		0x0020	//�¼�����ʱ��CRC��־λ
#define	F_AnalyseSML_OK		0x0040	//�¼�����ʱ��CRC��־λ
#define	F_ClientAdd4		0x0080	//ClientID����4λ1B�����־
#define	F_Client1BCRC		0x0100	//ClientID����4λ1B ���crc�����־
#define	F_Attention_Fall	0x0200	//�¼�����ʱ��CRC��־λ
#define	F_Attention_Open	0x0400	//�¼�����ʱ��CRC��־λ
#define	F_Attention_List	0x0800	//�¼�����ʱ��CRC��־λ
#define	F_Attention_Only	0x1000	//ֻ����attention
#define	F_Attention_NotDoneGroup	0x2000	//ͬһ��group������Ӧ
#define	F_Attention_NotDoneALL	0x4000	//�����Ķ�����Ӧ
#define	F_Attention_ERR17	0x8000	//ERR17
typedef struct
{
	uint32_t SendEventDataNum;//����event���ݸ���
	uint32_t SendEventNum;//����event����
	uint8_t SLayerNumR;//��ǰ��¼�Ĳ���//
	uint8_t LayerNumR;//��ǰ��¼�Ĳ���//
	uint8_t LayerNumA;//��ǰ�����Ĳ���//
	uint8_t *RecBuf;//RecBuf[1048];//���ջ�����//
	uint16_t RecLg;//���ճ���//
	uint16_t RecLgA;//�������ݵ��ѽ�������//
//	uint8_t SendBuf[1048];//���ͻ�����//
	uint8_t *SendBuf;
	uint16_t SendLg;//���ͳ���//
	uint16_t NeedSendLg;//��Ҫ���ͳ���//
	uint16_t SendPtr;//���ͻ���������дλ��//
	uint16_t AnaOrderAd;//������һ������������ڻ������е�λ��//
	uint16_t MSBSendLg;//MSB���ͳ���//
	
	uint16_t OpenClientID1BPrt;//client ID 1B ����λ��//
	
	uint16_t MSBNeedSendLg;//MSB��Ҫ���ͳ���//
	uint16_t Flag;//������־//
	uint16_t OpenFlag;//����Open������״̬��־//
	uint8_t MSBTime;//MSBʱ��//
	uint8_t	EndNum;
	uint8_t WrongTypeNum;
		
}SMLCOMM;


typedef struct
{
	uint16_t Order;// ͨ������//
	uint8_t DataLayer;//���ݵĲ���//
		
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
// ��������ָ��
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

#define	MaxOBISNum		90+20+4+5//0x07	//ͨѶ������
#define	MaxOBISNumSet		8//0x03
#define	MaxAttentionNum		22//0x03



#define RAM_INTER_TYPE 0x60
#define RAM_TYPE 0x70
#define E2P_TYPE 0x80
#define FUN_TYPE 0x90


#define Unit_a   	1	        //a      	 	// 	ʱ��             	��
#define Unit_mo  	2	       	//mo          	//	ʱ��              	��
#define Unit_wk  	3	       	//wk       	   	//	ʱ��              	��              7*24*60*60s
#define Unit_d   	4	       	//d            	//	ʱ��              	��              24*60*60 s
#define Unit_h   	5	       	//h        	   	//	ʱ��             	Сʱ            60 *60 s
#define Unit_min	6	       	//min.     	   	//	ʱ��              	��              60 s
#define Unit_s   	7	     	    //s       	   	//	ʱ��(t)            	��              s
#define Unit_deg	8	 	   	    //��          	//	(��)��             	��              rad*180/��
#define Unit_Cel	9	   	   	  //0C         	//	�¶�(��)          	���϶�          K-273.15
#define Unit_m3_h	15	   	    //(15)	       m3/h  		//	����                                m3 /��60*60s��
#define Unit_W   	27	       	//W          	//	�й����� ��P��     	��              W = J/s
#define Unit_VA  	28	    	  //VA         	//	���ڹ��ʣ�S��   	
#define Unit_var 	29	  		  //var         	//	�޹����ʣ�Q��
#define Unit_Wh  	30	        //Wh         	//	�й�����                            W*(60*60s) 
#define Unit_VAh 	31	        //VAh         	//	��������                            VA*(60*60s)
#define Unit_varh	32	        //varh      	//	�޹�����                            var*(60*60s)
#define Unit_A   	33	        //A         	//	������I��           ����            A
#define Unit_V   	35	        //V         	//	��ѹ��U��          	����            V 
#define Unit_Hz  	44	        //Hz        	//	Ƶ��               	����            1 /s
#define Unit_Rac 	45         	//Rac         	//	�й���������                      1/��Wh��
#define Unit_Rre 	46    	    //Rre         	//	�޹���������
#define Unit_Rap 	47         	//Rap       	//	������������
#define Unit_V2_h	48         	//V2/h        	// 	����ƽ��Сʱ                   		V2(60*60s)
#define Unit_A2_h	49         	//A2/h   		// 	����ƽ��Сʱ                   		A2(60*60s)
#define Unit_FF		255    		  //����        	//	�޵�λ��ȱ��λ������

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
#define	F_ServerID_No		0x0001	//open�е�serverID Ϊ��//
#define	F_Username_No		0x0002	//open�е�UsernameΪ��//
#define	F_Password_No		0x0004	//open�е�PasswordΪ��//

void CmSet_SML_Recevie_Buf(uint8_t *buf,uint16_t len);
uint16_t CmGet_SML_Send_Buf(uint8_t *buf);
//�յ������Ľ�������,���:���ָ��,����,����:���Ȳ�ȫ����0,������-1,��ȷ����1//
signed AnalyseOrder(uint16_t BufAd,uint16_t DataLg,uint8_t LayerNo);
//����һ��SML,MESSAGE�ṹ���:���ָ��,���ݳ���,���(��ǰ������SML MESSAGE)//
//����:���Ȳ�ȫ����0,������-1,��ȷ����1//
signed AnalyseSMLMes(uint16_t BufAd,uint16_t DataLg,uint8_t LayerNo);
uint16_t DoCrc16(uint16_t RegInit, uint8_t *message, uint16_t len);
//CRC16�������ֽڵĽ������ͨ�ŵ�˳��//
void DoCrc161(uint8_t *Dest,uint16_t RegInit, uint8_t *message, uint16_t len);
//ֻ�ǽ������ݣ�����д��������//
void AnalyseSMLData(void);
//�������ϴν����뱾�ν����м�û�����ݽ���ʱ�˳�//
//���ܵĽ�������С�ڽ��յ���һ��SML MESSAGE��76ʱ�˳�//
void AnalyseSML(uint8_t *sendbuf);
//SMLͨ�ŵĳ�ʼ��//
void	SMLCommInit(void);
//���ͻ������е�ͷ����д//
void	WriteSendBufStr(void);
void	WriteSendBufEnd(uint8_t Num0);
//��������׼������//
void GetSendData(void);
void	OpenRes(void);
void	CloseRes(void);
void	GetProfPRes(void);
void	GetProfLRes(void);
void	GetPropPRes(void);
void SetPropPRes(void);
void GetLRes(void);
//����һ�������������Ĳ�����//
//ÿһ������ݵ���ʼ��ַ�����ݳ�����OrderRecord[]��//
//��������Ƕ��ʱ,���������Ƕ�׵Ĳ���//
uint8_t 	AnaOrderData(uint16_t StartAdd,uint8_t OrerType);
//�Ѳ��ұ�ó�OBIS�����ͺ�//
uint8_t SearchOBIS(uint8_t *POBIS);
//��дGETlist�¼�����//
void DoProPListOBIS(void);
uint8_t DoDeviceIdentification(void);
//����OBIS���������дSET����//
uint8_t DoProSOBIS(uint8_t OBISNo);
//�����÷���һ����ȷ����Ӧ//
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
