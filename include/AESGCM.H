//
//int Decrypt_ByteData(unsigned char* pKey/*��Կ*/,unsigned char* pIV /*��ʼ������*/,unsigned char* pHDR/*ͷ-��������*/,int nHdrLen,unsigned char* pCiphertext /*����*/,int *nCtextLen,unsigned char* pTag /*��֤ʶ����*/,unsigned char* pOutPlaintext/*����*/);
//int Encrypt_ByteData(unsigned char* pKey/*��Կ*/,int nKeyLen,unsigned char* pIV/*��ʼ������*/,int nIVLen,unsigned char* pHDR,int nHdrLen,unsigned char* pPlaintext/*����*/,int nPtextLen,unsigned char* pOutCiphertext/*����*/,unsigned char* pOutTag/*��֤ʶ����*/);

int Decrypt_OR_Encrypt(int COM_No,unsigned char* Ciphertext,int *nCtextLen,unsigned char use_crypt);   //�жϽ������ͣ������ͱ�ʶ����ӽ�������,use_crypt:0--���루�п������ж��Ƿ���Ҫ���ܣ���1--�������..

int Decrypt_ByteData(unsigned char* key/*��Կ*/,unsigned char* iv /*��ʼ������*/,unsigned char* hdr/*ͷ-��������*/,int hdr_len,unsigned char* ctx /*����*/,int ctx_len,unsigned char* pTag /*��֤ʶ����*/,unsigned char* pOutPlaintext/*����*/);
int Encrypt_ByteData(unsigned char* key/*��Կ*/,int key_len,unsigned char* iv/*��ʼ������*/,int iv_len,unsigned char* hdr,int hdr_len,unsigned char* ptx/*����*/,int ptx_len,unsigned char* pOutCiphertext/*����*/,unsigned char* pOutTag/*��֤ʶ����*/);
