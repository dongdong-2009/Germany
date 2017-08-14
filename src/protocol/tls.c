#include <stdint.h>
#include <Drive_Lib.h>
#include "aes.h"
#include "tls.h"
#include "tlse.h"
#include "types.h"
#include "UECC.h"
#include "uECC.h"
#include "typeE2p.h"
#include "sym.h"
#include "sml.h"
#include "mbedtls/sha512.h"
#include "mbedtls/sha256.h"
#include "mbedtls/ecp.h"
#include "mbedtls/ecdsa.h"
#include "mbedtls/oid.h"
void __private_tls_prf(struct TLSContext *context,
                       unsigned char *output, unsigned int outlen, const unsigned char *secret, const unsigned int secret_len,
                       const unsigned char *label, unsigned int label_len, unsigned char *seed, unsigned int seed_len,
                       unsigned char *seed_b, unsigned int seed_b_len);
typedef enum {
    KEA_dhe_dss,
    KEA_dhe_rsa,
    KEA_dh_anon,
    KEA_rsa,
    KEA_dh_dss,
    KEA_dh_rsa,
    KEA_ec_diffie_hellman
} KeyExchangeAlgorithm;

typedef enum {
    rsa_sign = 1,
    dss_sign = 2,
    rsa_fixed_dh = 3,
    dss_fixed_dh = 4,
    rsa_ephemeral_dh_RESERVED = 5,
    dss_ephemeral_dh_RESERVED = 6,
    fortezza_dms_RESERVED = 20,
    ecdsa_sign = 64,
    rsa_fixed_ecdh = 65,
    ecdsa_fixed_ecdh = 66
} TLSClientCertificateType;

typedef enum {
    none = 0,
    md5 = 1,
    sha1 = 2,
    sha224 = 3,
    sha256 = 4,
    sha384 = 5,
    sha512 = 6,
    __md5_sha1 = 255
} TLSHashAlgorithm;

typedef enum {
    anonymous = 0,
    rsa = 1,
    dsa = 2,
    ecdsa = 3
} TLSSignatureAlgorithm;
//extern uint8_t b_lmn_cert[576];
//extern uint8_t b_lmn_cert[512];
//extern uint8_t b_gw_cert[256];
//#include "uECC_vli.h"
//#include "tlse.c"
#define __TLS_CLIENT_RANDOM_SIZE    32
#define __TLS_SERVER_RANDOM_SIZE    32
#define __TLS_MAX_SESSION_ID        32
#define TLS_CHANGE_CIPHER       0x14
#define TLS_ALERT               0x15
#define TLS_HANDSHAKE           0x16
#define TLS_APPLICATION_DATA    0x17
#define CHECK_SIZE(size, buf_size, err)  if (((int)size > (int)buf_size) || ((int)buf_size < 0)) return err;

#if 0
typedef struct SHA512_HashContext1 {
    uECC_HashContext uECC;
    mbedtls_sha512_context ctx;
} SHA512_HashContext;

void init_SHA512(uECC_HashContext *base) {
    SHA512_HashContext *context = (SHA512_HashContext *)base;
	 fnWDT_Restart();
    mbedtls_sha512_init(&context->ctx);
	 fnWDT_Restart();
		mbedtls_sha512_starts( &context->ctx,0);
}

void update_SHA512(uECC_HashContext *base,
                   const uint8_t *message,
                   unsigned message_size) {
    SHA512_HashContext *context = (SHA512_HashContext *)base;
										  fnWDT_Restart();
    mbedtls_sha512_update(&context->ctx, message, message_size);
										  fnWDT_Restart();
}

void finish_SHA512(uECC_HashContext *base, uint8_t *hash_result) {
    SHA512_HashContext *context = (SHA512_HashContext *)base;
	 fnWDT_Restart();
    mbedtls_sha512_finish(&context->ctx,hash_result);
	 fnWDT_Restart();
}

typedef struct SHA256_HashContext1 {
    uECC_HashContext uECC;
    mbedtls_sha256_context ctx;
} SHA256_HashContext;

void init_SHA256(uECC_HashContext *base) {
    SHA256_HashContext *context = (SHA256_HashContext *)base;
    mbedtls_sha256_init(&context->ctx);
}

void update_SHA256(uECC_HashContext *base,
                   const uint8_t *message,
                   unsigned message_size) {
    SHA256_HashContext *context = (SHA256_HashContext *)base;
										 fnWDT_Restart();
    mbedtls_sha256_update(&context->ctx, message, message_size);
										 fnWDT_Restart();
}

void finish_SHA256(uECC_HashContext *base, uint8_t *hash_result) {
    SHA256_HashContext *context = (SHA256_HashContext *)base;
	fnWDT_Restart();
    mbedtls_sha256_finish(&context->ctx,hash_result);
	fnWDT_Restart();
}

#endif

uint32_t htonl(uint32_t hostlong)
{
	uint32_t nlong;
	nlong=hostlong&0xff;
	nlong=(nlong<<8)+((hostlong>>8)&0xff);
	nlong=(nlong<<8)+((hostlong>>16)&0xff);
	nlong=(nlong<<8)+((hostlong>>24)&0xff);
	return nlong;
}
uint16_t htons(uint16_t hostshort)
{
	uint16_t nshort;
	if(hostshort==0)
		return 0;
	nshort=hostshort&0xff;
	nshort=(nshort<<8)+((hostshort>>8)&0xff);
	return nshort;
}
#define ntohl htonl
#define ntohs htons
#if 0
#ifndef htonll
#define htonll(x) ((1==ntohl(1)) ? (x) : ((uint64_t)ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32))
#endif
#endif


#ifndef ntohll
#define ntohll(x) ((1==ntohl(1)) ? (x) : ((uint64_t)ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32))
#endif
extern uint8_t Kenc[16],Kmac[16],Lenc[16],Lmac[16];
/**
 ****************************************************************************************
 * @brief 随机数生成函数
 * 
 ****************************************************************************************
 */
static int ecc_rng(unsigned char *dest, unsigned size)
{
    unsigned int i;
    for (i = 0; i < size; i++)
    {
        dest[i] = rand()%256;
    }

    return 1;
}
struct TLSContext {
    unsigned char remote_random[__TLS_CLIENT_RANDOM_SIZE];
    unsigned char local_random[__TLS_SERVER_RANDOM_SIZE];
		unsigned char session[__TLS_MAX_SESSION_ID];
		uint32_t session_size;
		uint32_t crypto_created;
		uint32_t crypto_time;
		unsigned char *message_buffer;
		unsigned int message_buffer_len;
		unsigned char priv[64];
		unsigned char ecc_priv[64];
		unsigned char public_key[64];
		unsigned char share_key[32];
		unsigned char aes_key[16];
		unsigned char master_key[48];
		unsigned char local_mac[32];
		unsigned char remote_mac[32];
		unsigned char clientkey[16];
		unsigned char clientiv[16];
		unsigned char serverkey[16];
		unsigned char serveriv[16];
		unsigned char server_verify_data[80];
		unsigned char client_verify_data[80];
		uint64_t	local_sequence_number;
		uint64_t  remote_sequence_number;
		unsigned int master_key_len;
		mbedtls_sha256_context sha256;
		uint8_t sha256_init;
		uint8_t tls_sml;
		mbedtls_ecp_group_id grp_id;
};

struct TLSPacket {
    unsigned char *buf;
    unsigned int len;
    unsigned int size;
    unsigned char broken;
    struct TLSContext *context;
};

//static struct TLSContext m_tlscontext;
struct TLSContext m_tlscontext;
const struct uECC_Curve_t * p_curve;
//#define TEST
//#define UECC_TEST
#ifdef TEST
uint8_t hash_test_buff[64]={0x7C,0x3E,0x88,0x3D,0xDC,0x8B,0xD6,0x88,0xF9,0x6E,0xAC,0x5E,0x93,0x24,0x22,0x2C,
0x8F,0x30,0xF9,0xD6,0xBB,0x59,0xE9,0xC5,0xF0,0x20,0xBD,0x39,0xBA,0x2B,0x83,0x77};
#if 1

#else
uint8_t ecsda_test[64]={0x72,0x14,0xBC,0x96,0x47,0x16,0x0B,0xBD,0x39,0xFF,0x2F,0x80,0x53,0x3F,0x5D,0xC6,
0xDD,0xD7,0x0D,0xDF,0x86,0xBB,0x81,0x56,0x61,0xE8,0x05,0xD5,0xD4,0xE6,0xF2,0x7C,
0x7D,0x1F,0xF9,0x61,0x98,0x0F,0x96,0x1B,0xDA,0xA3,0x23,0x3B,0x62,0x09,0xF4,0x01,
0x33,0x17,0xD3,0xE3,0xF9,0xE1,0x49,0x35,0x92,0xDB,0xEA,0xA1,0xAF,0x2B,0xC3,0x67};
#endif
#if 0
uint8_t compress_test[64]={0x02,0xFD,0xC9,0x1E,0xA7,0x46,0x75,0x8D,0x07,0x76,
														0x09,0x7C,0x49,0xE4,0x6D,0xDA,0x95,0x74,0xB9,0x3D, 
														0x03,0xF2,0x16,0xC3,0x13,0x18,0xB3,0x91,0x64,0x11, 
														0x5F,0xC5,0xD0};
uint8_t cl_random[32]={0x53,0x4D,0xD8,0x08,0xC6,0x8D,0x71,0x63,0x33,0xF0,0xAF,0x8B,0x4C,0xE2,0x47,0x29, 
												0x74,0xB5,0x83,0xAB,0x58,0xEC,0x41,0xA7,0x14,0x9A,0xF1,0xD5,0xE0,0x15,0x7A,0xDA};
uint8_t srv_random[32]={0x52,0x80,0xE2,0xF3,0xA2,0xA8,0xB1,0x41,0xB7,0xC0,0x15,0xD2,0x9A,0xDB,0x82,0xD7, 
												0x61,0x14,0xFC,0x0F,0xC2,0xB9,0xC0,0xDD,0x15,0xEE,0xA6,0x8D,0x9E,0x72,0xB7,0x38};
uint8_t decompress_test[64]={	
														0xC7,0xF3,0x38,0xC3,0x7B,0xC4,0x47,0xAB,0x8A,0x7E,0xEE,0xF0,0xFE,0x07,0x68,0x7F,
														0x7F,0x91,0x64,0xFC,0x08,0x3C,0x69,0xD9,0x26,0xB6,0x07,0x64,0x21,0xEF,0x16,0x0B,
														0x8D,0xC7,0x1B,0xEB,0x19,0xB9,0xEF,0xC4,0xA8,0x74,0x26,0xA9,0xE8,0xDA,0x4C,0xA3,
														0x69,0x30,0xEC,0xD9,0x9A,0xEB,0x8D,0xB8,0x72,0x03,0x35,0x53,0x3B,0x4A,0x7E,0xEC
};
uint8_t ecsda_test[64]={0xE3,0xD7,0x16,0x5E,0x9B,0x17,0xA0,0x28,0xD7,0x7E,
												0xD0,0xFC,0x3B,0x6F,0x14,0x24,0x11,0x43,0x6B,0xAC,
												0x4C,0xA6,0xC2,0x4E,0xCA,0xD6,0xBC,0x12,0x50,0xE2,
												0x58,0x8F,
												0x9D,0xB3,0xDE,0x7C,0xAF,0x61,0x44,0xA3,0xAD,0x4A, 
												0xA6,0x33,0xBD,0x6E,0x48,0x46,0x9D,0x2A,0xD3,0x55, 
												0xDF,0xA0,0x6F,0x07,0xEE,0x10,0xD1,0x0A,0x9A,0xF9, 
												0x10,0x7F};
#else
uint8_t compress_test[64]={
	0x03,0x67,0x44,0x22,0x36,0x35,0x94,0x23,0xA0,0x2B,0x13,0x3D,0xA2,0x13,0xF0,0x6F,
0xCC,0x85,0xEB,0x85,0x75,0x3D,0xDC,0x66,0xF2,0xE4,0xD7,0xBE,0x80,0xE4,0xBE,0x14,
0xCD
};
uint8_t cl_random[32]={0x1C,0x19,0x4E,0xE4,0xE8,0xE5,0xEC,0xEB,0xDC,0x9D,0x9F,0x0B,0x7C,0x67,0x2C,0x55,
0xEB,0xE9,0xC0,0x62,0xAC,0x87,0xE9,0x86,0x9F,0x77,0xAD,0x08,0xF8,0xEE,0x20,0x6B};
uint8_t srv_random[32]={
0x29,0xC8,0x44,0x47,0x57,0x5E,0x22,0xCD,0x65,0x54,0xE0,0xB3,0x53,0xAA,0x7E,0xF9,
0x21,0x60,0xFC,0x9F,0xCF,0x76,0x5A,0xA5,0x5D,0xEC,0x98,0x0B,0xCB,0xC2,0xB6,0xD1
};

uint8_t decompress_test[68]={
#ifndef UECC_TEST//for embedtls
0x04,
#endif	
0x89,0xC4,0xFA,0x5A,0xB6,0xEF,0x71,0xEF,0xE2,0x2B,0x4F,0x6F,0xB0,0xBB,0x90,0xBF,
0x5A,0x2D,0x9E,0x73,0xF6,0xF4,0xF6,0x19,0xE2,0xE5,0x96,0xEF,0xA5,0x9C,0x26,0xB1,
0x77,0xB0,0xFF,0xCF,0x2E,0x21,0x4A,0x5D,0x93,0x6D,0xD0,0xC1,0x14,0xEE,0x0C,0x19,
0xCD,0x1F,0xF9,0xAE,0x2C,0x4A,0xF6,0x79,0x64,0xFA,0xE7,0x7D,0x6D,0x14,0x11,0x03
};
uint8_t public_key_for_share[64]={
0xE3,0x16,0x61,0x42,0xD5,0x85,0x5D,0xFF,0x17,0x55,0x82,0x04,0x78,0x6E,0x66,0xC6,
0x3E,0xE3,0x64,0x5F,0x1B,0x80,0x55,0xC3,0xD1,0x75,0xCB,0xC8,0x6A,0x37,0xEF,0xCA,
0x16,0x41,0xC0,0x2E,0x2F,0xDF,0x60,0x39,0x20,0x5A,0xF4,0x04,0xC4,0xCD,0xC3,0xF3,
0xF0,0x91,0x21,0x3B,0x80,0xAA,0xF2,0x57,0x68,0xD5,0xEE,0x66,0x73,0x6E,0x77,0xAD
};
uint8_t ecsda_test[64]={
0xE9,0x1F,0xCD,0xB1,0xBB,0x15,0xEA,0x30,0xD1,0x56,0x4B,0xE8,0x3C,0x58,0x66,0xE6,
0xF4,0xC4,0x0A,0x68,0x06,0x3B,0x7E,0x63,0x25,0x39,0xB8,0x3B,0x92,0x5B,0x82,0x21,
0x1C,0x6F,0x21,0x70,0x4E,0x35,0xAD,0xCE,0xCE,0x37,0x6C,0x2A,0xAE,0xA6,0x61,0x71,
0xFE,0x4F,0xE2,0x5C,0x53,0xAF,0x6F,0x07,0x3B,0xBE,0xCA,0x74,0xED,0x8A,0x62,0x85
};
#endif
#if 1

#else
uint8_t decompress_test[64]={0x1E,0xFE,0xE3,0x76,0xD8,0x79,0x71,0x43,0xCB,0x94,0x21,0xE2,0x88,0x50,0x33,0xFE, 
															0x84,0xE4,0x6D,0x12,0x5C,0x78,0x7E,0x4C,0x7D,0xDA,0xAB,0xD7,0xC5,0x93,0x79,0x09, 
															0x94,0xA4,0xB1,0x77,0x83,0xFF,0xBE,0x47,0xFA,0xCD,0xE3,0x08,0x82,0x4C,0x95,0xC3, 
															0x1B,0x41,0xD0,0x31,0x80,0x78,0xC4,0x8D,0xA4,0x64,0xA2,0x7B,0xC0,0xEC,0x0C,0x30};														
#endif
#endif
uint8_t *Cm_Get_ECC_Addr(void)
{
	return m_tlscontext.ecc_priv;
}

void Cm_Make_Public_Key(void)
{
#if 0	
	uECC_compute_public_key(m_tlscontext.ecc_priv,m_tlscontext.public_key,p_curve);
	Cm_Ram_Inter(m_tlscontext.public_key,32);
	Cm_Ram_Inter(m_tlscontext.public_key+32,32);
	E2P_WData(PublicKey_Y,m_tlscontext.public_key,64);
#endif	
	return;
}

const uint8_t initKey[16]={0xA4,0x45,0x7D,0x73,0xF3,0xA8,0xED,0x56,0xB7,0x22,0x68,0xD9,0xB5,0x23,0x0F,0x7A};
//const uint8_t initKey[16]={0x88,0x1e,0xa0,0x8c,0x49,0x5f,0x18,0x9d,0xcb,0x8e,0xfb,0x15,0xe6,0x15,0x90,0xfc};
int ResetCryto(void)
{
	uint8_t *b_lmn_cert; 
	//if((!m_tlscontext.tls_sml) || m_tlscontext.crypto_time)
	//if((m_tlscontext.crypto_created&&m_tlscontext.crypto_time))
	if(m_tlscontext.crypto_time)
	{
		b_lmn_cert=Get_LMN_Cert();
		memset(b_lmn_cert,0,64);
		memcpy(m_tlscontext.aes_key,initKey,16);
		m_tlscontext.crypto_created=0;
		E2P_WData(E2P_SymmetricalKey,m_tlscontext.aes_key,16);
		return 0;
	}
	return 1;
}
#define __TLS_MAX_KEY_EXPANSION_SIZE 192
uint8_t sign_out[__TLS_MAX_KEY_EXPANSION_SIZE];
extern uint8_t Z1_M[16];
void SetKeyTime(int timesec)
{
	//if(!m_tlscontext.tls_sml)
	{
		m_tlscontext.crypto_time=timesec;
	}
}
void Generate_New_Key(void)
{
	if(m_tlscontext.tls_sml)
	{
		AES_CMAC(m_tlscontext.aes_key,Z1_M,16,sign_out+16);
		memcpy(m_tlscontext.aes_key,sign_out+16,16);
		E2P_WData(E2P_SymmetricalKey,m_tlscontext.aes_key,16);
		SetKeyTime(120);
	}
}
uint8_t *GetMKey(void)
{
	return m_tlscontext.aes_key;
}

void Close_tls(void)
{
	m_tlscontext.crypto_created=0;
}

uint32_t GetTlsTime(void)
{
	return m_tlscontext.crypto_time;
}

void Judge_Cryto(void)
{
	if(m_tlscontext.crypto_time)
	{
		m_tlscontext.crypto_time--;
		if(m_tlscontext.crypto_time==0)
		{
		//	memcpy(m_tlscontext.aes_key,initKey,16);//ResetCryto();
		}
	}
}

int __private_tls_update_hash(struct TLSContext *context, const unsigned char *in, unsigned int len)
{
	if(context->sha256_init==0)
	{
		mbedtls_sha256_init(&(context->sha256));
		fnWDT_Restart();
    mbedtls_sha256_starts( &(context->sha256), 0 );
		context->sha256_init=1;
	}
	fnWDT_Restart();
	mbedtls_sha256_update( &(context->sha256), in, len );
	return 0;
}

int __private_tls_get_hash(struct TLSContext *context, unsigned char *hout)
{
	mbedtls_sha256_context pre;
	if(context->sha256_init)
	{
		memcpy(&pre,&(context->sha256),sizeof(context->sha256));
		mbedtls_sha256_finish(&pre,hout);
		return 32;
	}
	return 0;
}

int __private_tls_done_hash(struct TLSContext *context, unsigned char *hout) 
{
	if(context->sha256_init)
	{
		mbedtls_sha256_finish(&(context->sha256), hout);
		context->sha256_init=0;
		return 32;
	}
	return 0;
}
//uint8_t test_Message[]={"Example of ECDSA with P-256"};
void Cm_Ram_Inter(uint8_t *buf,uint16_t Len)
{
	uint16_t i;
	uint8_t tmp;
	if(Len<2)
		return;
	for(i=0;i<Len/2;++i)
	{
		tmp = buf[i];
		buf[i] = buf[Len-1-i];
		buf[Len-1-i]=tmp;
	}
}		

uint64_t htonll(uint64_t x)
{
	Cm_Ram_Inter((uint8_t *)&x,8);
	return x;
}
//uint8_t tmp[64 + 64 + 128];

#if 0
uint8_t ecc256_r1_p[32]={0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint8_t ecc256_r1_qx[32]={0x6B,0x17,0xD1,0xF2,0xE1,0x2C,0x42,0x47,0xF8,0xBC,0xE6,0xE5,0x63,0xA4,0x40,0xF2,
0x77,0x03,0x7D,0x81,0x2D,0xEB,0x33,0xA0,0xF4,0xA1,0x39,0x45,0xD8,0x98,0xC2,0x96};
uint8_t ecc256_r1_qy[32]={0x4F,0xE3,0x42,0xE2,0xFE,0x1A,0x7F,0x9B,0x8E,0xE7,0xEB,0x4A,0x7C,0x0F,0x9E,0x16,
0x2B,0xCE,0x33,0x57,0x6B,0x31,0x5E,0xCE,0xCB,0xB6,0x40,0x68,0x37,0xBF,0x51,0xF5
};
uint8_t ddd[8]={0x00,0x11,0x22,0x33,0x44,0x55};
#endif
#if  0
uint8_t m_serverkey[16]={0x73,0x7A,0x74,0xEC,0xB9,0x14,0x7C,0xAD,0xAE,0x5F,0x5F,0xDC,0x30,0xF6,0x56,0x8A};
uint8_t m_serveriv[16]={0x38,0xEB,0xA2,0x2E,0x2E,0x28,0x6E,0xCB,0xBE,0x84,0x00,0x76,0x69,0x2C,0x1B,0xE3};
uint8_t m_cipher[80]={0xB0,0xDA,0xBC,0x89,0xE6,0x54,0x01,0x11,0xE4,0x75,0xCF,0xE6,0x0A,0x27,0x35,0x1E,
0x90,0x31,0xF5,0x2B,0x41,0xDF,0xF4,0x3C,0x3E,0x7B,0xEB,0x89,0xD9,0xC6,0xA5,0x39,
0x7F,0x25,0xF1,0x64,0x5C,0x23,0x66,0x1A,0x95,0xED,0xD6,0xC0,0x08,0xD5,0x0B,0x44,
0x5A,0xB4,0x58,0x09,0x61,0x71,0x32,0x97,0x29,0x7B,0x41,0xC8,0x66,0x76,0x9B,0xA6,
0x5A,0x84,0x2C,0x46,0x6B,0xE8,0x1D,0xBD,0x50,0x8A,0x52,0x50,0xD0,0x46,0x15,0x86};
#endif


int Gen_Random(void *n, unsigned char *buf, size_t Len)
{
	int i;
	for (i = 0; i < Len; i++)
	{
		buf[i] = rand()%256;
	}
	return 0;
}
//#pragma pack (4) 
const unsigned char b_pri[32]={0x9D,0xEB,0xC6,0xDE,0x97,0x57,0xDE,0x9D,0x99,0x4E,0x45,0xFC,0xD8,0x5D,0x47,0x62,
0xB0,0x28,0xFC,0x24,0x0D,0x14,0xA5,0xA0,0x2A,0x35,0x00,0x6E,0x59,0xDC,0xFD,0x07};
//mbedtls_mpi_uint pri_key[8];
mbedtls_mpi m;
mbedtls_ecp_point R;
mbedtls_ecp_group grp;
mbedtls_mpi r;
mbedtls_mpi s;
int mbedTls_Test(mbedtls_ecp_group_id grpid)
{

	int ret,i;
	ret=mbedtls_ecp_group_load( &grp, grpid);
//	m.p=pri_key;
 // m.n=8;
	mbedtls_mpi_read_binary(&m,b_pri,32);
	ret=mbedtls_ecp_check_privkey(&grp,&m);
	ret=mbedtls_ecp_mul(&grp,&R,&m, &grp.G, Gen_Random,NULL);//生成公钥
	mbedtls_ecp_point_write_binary(&grp,&R,MBEDTLS_ECP_PF_COMPRESSED,&i,m_tlscontext.public_key,64);
	mbedtls_ecp_group_free( &grp );
  mbedtls_ecp_point_free( &R );
  mbedtls_mpi_free( &m );
	return ret;
}

void Cm_Signature(const uint8_t *pri,uint8_t *in,uint32_t Len,uint8_t *out)
{
	mbedtls_sha256(in,Len,sign_out,0);
#ifdef UECC_TEST	
	uECC_sign(pri,sign_out,32,out,p_curve);
#else
	if(grp.id!=MBEDTLS_ECP_DP_ANSIP256R1)
	{
		mbedtls_ecp_group_load( &grp, MBEDTLS_ECP_DP_ANSIP256R1);
	}
	mbedtls_mpi_read_binary(&m,pri,32);
	mbedtls_ecdsa_sign(&grp,&r, &s,&m,sign_out,32,Gen_Random,NULL);
	mbedtls_mpi_write_binary(&r,out,32);
	mbedtls_mpi_write_binary(&s,out+32,32);
#endif	
/*	uECC_compute_public_key(pri,m_tlscontext.public_key,p_curve);
	Cm_Ram_Inter(m_tlscontext.public_key,32);
	Cm_Ram_Inter(m_tlscontext.public_key+32,32);
	E2P_WData(PublicKey_Y,m_tlscontext.public_key,64);*/
}

int tls_Init(void)
{
	unsigned char *privateK;
 // uECC_word_t publicK[8 * 2];
   /*unsigned char b_pri[32]={0x70,0xa1,0x2c,0x2d,0xb1,0x68,0x45,0xed,0x56,0xff,0x68,0xcf,0xc2,0x1a,0x47,0x2b,
														 0x3f,0x04,0xd7,0xd6,0x85,0x1b,0xf6,0x34,0x9f,0x2d,0x7d,0x5b,0x34,0x52,0xb3,0x8a};*/
	// SHA512_HashContext ctx;
//	SHA256_HashContext ctx;
	 //unsigned char b_pri[32]={0x9D,0xEB,0xC6,0xDE,0x97,0x57,0xDE,0x9D,0x99,0x4E,0x45,0xFC,0xD8,0x5D,0x47,0x62,
//0xB0,0x28,0xFC,0x24,0x0D,0x14,0xA5,0xA0,0x2A,0x35,0x00,0x6E,0x59,0xDC,0xFD,0x07};
#if 0	
		unsigned char b_pri[32]={0x70,0xA1,0x2C,0x2D,0xB1,0x68,0x45,0xED,0x56,0xFF,0x68,0xCF,0xC2,0x1A,0x47,0x2B,
0x3F,0x04,0xD7,0xD6,0x85,0x1B,0xF6,0x34,0x9F,0x2D,0x7D,0x5B,0x34,0x52,0xB3,0x8A};
#endif	
#ifdef TEST
		uint8_t publicK[64];
		int i;
#endif
		uint8_t *ptr;
		
		uint8_t *b_lmn_cert;
		uint64_t squence_number;
		uint64_t result;
		squence_number = 0x14890;
		result = htonll(squence_number);
//		result=mbedTls_Test(MBEDTLS_ECP_DP_SECP256R1);
//		unsigned int i;
		b_lmn_cert=Get_LMN_Cert();

		E2P_RData(m_tlscontext.aes_key,E2P_SymmetricalKey,16);
		if((m_tlscontext.aes_key[0]==0) && (m_tlscontext.aes_key[1]==0))
			memcpy(m_tlscontext.aes_key,initKey,16);
		
		uECC_set_rng(ecc_rng);
		p_curve = uECC_secp256r1();
		memcpy(sign_out,b_pri,32);
		Cm_Ram_Inter(sign_out,32);
		uECC_compute_public_key(sign_out,m_tlscontext.public_key,p_curve);
		Cm_Ram_Inter(m_tlscontext.public_key,32);
		Cm_Ram_Inter(m_tlscontext.public_key+32,32);
		E2P_WData(PublicKey_Y,m_tlscontext.public_key,64);
//		CmDeAES128(m_serverkey,m_serveriv,0,m_cipher,80,sign_out);
#ifdef TEST
		
#if 1
#if 1
		memcpy(b_lmn_cert,cl_random,32);
		memcpy(b_lmn_cert+32,srv_random,32);
		i=64;
#if 0 //USE P AND G
		ptr = ecc256_r1_p;
		memcpy(b_lmn_cert+i,ptr,32);
		i+=32;
		memcpy(b_lmn_cert+i,ecc256_r1_qx,32);
		i+=32;
		memcpy(b_lmn_cert+i,ecc256_r1_qy,32);
		i+=32;
#endif
#if 1
		b_lmn_cert[i++]=0x03;
		b_lmn_cert[i++]=0x00;b_lmn_cert[i++]=0x17;
		b_lmn_cert[i++]=0x21;
    memcpy(b_lmn_cert+i,compress_test,33);
		i += 33;
#else
		uECC_decompress(compress_test,b_lmn_cert+i,p_curve);
		Cm_Ram_Inter(b_lmn_cert+i,32);
		Cm_Ram_Inter(b_lmn_cert+i+32,32);
		i+=64;
#endif
		fnWDT_Restart();
		Cm_Ram_Inter(compress_test+1,32);
#if 1		
	//	mbedtls_sha512(b_lmn_cert,101,hash_test_buff,0);
		mbedtls_sha512(b_lmn_cert,i,hash_test_buff,0);
		fnWDT_Restart();
#ifdef UECC_TEST //for uEcc		
		Cm_Ram_Inter(hash_test_buff,32);
		Cm_Ram_Inter(hash_test_buff+32,32);
#endif		
#else
		mbedtls_sha256(b_lmn_cert,101,hash_test_buff,0);
		Cm_Ram_Inter(hash_test_buff,32);
#endif
		fnWDT_Restart();
	//	mbedtls_sha512(b_lmn_cert,128,hash_test_buff,0);
#ifdef UECC_TEST //for uEcc	
		//use signature public_key
		Cm_Ram_Inter(decompress_test,32);
		Cm_Ram_Inter(decompress_test+32,32);
#else   //for embedtls
		mbedtls_ecp_group_load( &grp, MBEDTLS_ECP_DP_SECP256R1);
		result=mbedtls_ecp_point_read_binary(&grp,&R,decompress_test,65);
#endif
		
#if 0 	//use share public_key	
		fnWDT_Restart();
		uECC_decompress(compress_test,(uint8_t *)decompress_test,p_curve);
#endif

		fnWDT_Restart();
#ifdef UECC_TEST //for uEcc
		Cm_Ram_Inter(ecsda_test,32);
		fnWDT_Restart();
		Cm_Ram_Inter(ecsda_test+32,32);
#else  //for embedtls
		mbedtls_mpi_read_binary(&r,ecsda_test,32);
		mbedtls_mpi_read_binary(&s,ecsda_test+32,32);
#endif		
		fnWDT_Restart();
#if 1
#ifdef UECC_TEST //for uEcc
		result=uECC_verify(decompress_test,hash_test_buff,64,ecsda_test,p_curve);
#else
		result=mbedtls_ecdsa_verify(&grp,hash_test_buff,64,&R,&r,&s);
		//自己生成签名自己解签
		//mbedtls_ecp_group_free( &grp );
		mbedtls_ecp_point_free( &R );
		mbedtls_mpi_free( &m );
		mbedtls_mpi_free( &r);
		mbedtls_mpi_free( &s );
		mbedtls_mpi_read_binary(&m,b_pri,32);
		fnWDT_Restart();
		mbedtls_ecp_mul(&grp,&R,&m, &grp.G, Gen_Random,NULL);//生成公钥
		fnWDT_Restart();
		//mbedtls_ecdsa_sign_det(&grp,&r, &s,&m,b_lmn_cert,i,MBEDTLS_MD_SHA512);
		mbedtls_ecdsa_sign(&grp,&r, &s,&m,hash_test_buff,64,Gen_Random,NULL);
		mbedtls_mpi_write_binary(&r,sign_out,32);
		mbedtls_mpi_write_binary(&s,sign_out+32,32);
		mbedtls_mpi_free( &r);
		mbedtls_mpi_free( &s );
		mbedtls_mpi_read_binary(&r,sign_out,32);
		mbedtls_mpi_read_binary(&s,sign_out+32,32);
		fnWDT_Restart();
		result=mbedtls_ecdsa_verify(&grp,hash_test_buff,64,&R,&r,&s);
		fnWDT_Restart();
		mbedtls_ecp_point_free( &R );
		mbedtls_mpi_free( &m );
		mbedtls_mpi_free( &r);
		mbedtls_mpi_free( &s );
#endif
#else
		result=uECC_verify(decompress_test,hash_test_buff,32,ecsda_test,p_curve);
		
#endif
		fnWDT_Restart();
#else
		b_lmn_cert[0]=0x03;
		b_lmn_cert[1]=0x00;b_lmn_cert[2]=0x17;
		b_lmn_cert[3]=0x21;
    memcpy(b_lmn_cert+4,compress_test,33);

		fnWDT_Restart();
		//Cm_Ram_Inter(b_lmn_cert,101);
		mbedtls_sha512(b_lmn_cert,37,hash_test_buff,0);
#endif
	//	Cm_Ram_Inter(ecsda_test,64);
#endif		
		
		
#if 0
		//private verify
		Cm_Ram_Inter(b_pri,32);
		memcpy(m_tlscontext.ecc_priv,b_pri,32);
		uECC_compute_public_key(b_pri,(uint8_t *)publicK,p_curve);
		Cm_Ram_Inter(hash_test_buff,32);
		uECC_verify(publicK,hash_test_buff,32,ecsda_test,p_curve);
	//	uECC_sign(b_pri,hash_test_buff,64,ecsda_test,p_curve);
		//private verify end
#endif		
		//public verify
		uECC_decompress(compress_test,(uint8_t *)publicK,p_curve);
		uECC_valid_public_key(publicK,p_curve);
    //public verify end
		
		//public verify		
		fnWDT_Restart();	
		Cm_Ram_Inter(decompress_test,32);  //ok
		Cm_Ram_Inter(decompress_test+32,32);	//ok
		uECC_valid_public_key(decompress_test,p_curve);
		//public verify end
		
		//Cm_Ram_Inter(hash_test_buff,64);
		
		uECC_verify(decompress_test,hash_test_buff,64,ecsda_test,p_curve);	
		fnWDT_Restart();
		uECC_verify(publicK,hash_test_buff,64,ecsda_test,p_curve);	
		fnWDT_Restart();
#if 0	
	ctx.uECC.tmp = tmp;
	uECC_sign_deterministic(b_pri, b_lmn_cert,101,&ctx.uECC, sign_out,p_curve);
	fnWDT_Restart();
	uECC_verify(decompress_test,hash_test_buff,64,sign_out,p_curve);
														 
		uECC_compute_public_key(b_pri,(uint8_t *)publicK,p_curve);											 
		mbedtls_sha256(b_pri,32,hash_test_buff,0);
		uECC_sign(b_pri,hash_test_buff,32,ecsda_test,p_curve);
		uECC_verify((uint8_t *)publicK,hash_test_buff,32,ecsda_test,p_curve);
		uECC_compress((uint8_t *)publicK,compress_test,p_curve);
		
		uECC_decompress(compress_test,(uint8_t *)decompress_test,p_curve);
#endif
#endif
	//	Cm_Ram_Inter(b_pri,32);
	//	uECC_compute_public_key(b_pri,(uint8_t *)publicK,p_curve);
		privateK = m_tlscontext.priv;
		fnWDT_Restart();
#if 0		
		if (1 == uECC_make_key((unsigned char *)publicK,(unsigned char *)privateK,p_curve))
		{
		}
		
		E2P_WData(E2P_PrivateKey,privateK,32);
		Cm_Ram_Inter(publicK,32);
		Cm_Ram_Inter(publicK+32,32);
		E2P_WData(PublicKey_Y,publicK,32);
#else		
		E2P_RData(m_tlscontext.ecc_priv,E2P_PrivateKey,32);
#if 0		
		uECC_compute_public_key(m_tlscontext.ecc_priv,(uint8_t *)publicK,p_curve);
#endif		
//		Cm_Make_Public_Key();
		E2P_RData(b_lmn_cert,E2P_LMN_Certi,511);
		b_lmn_cert=Get_SMGW_Cert();
		E2P_RData(b_lmn_cert,E2P_SMGW_Certi,255);
		
#endif		
		fnWDT_Restart();
		m_tlscontext.sha256_init=0;
		m_tlscontext.crypto_created=0;
		m_tlscontext.tls_sml=0;
#if 0	
		__private_tls_prf(&m_tlscontext,publicK,48,cl_random,32,srv_random,32,compress_test,33,decompress_test,64);
		fnWDT_Restart();
		__private_tls_update_hash(&m_tlscontext,cl_random,32);
		__private_tls_update_hash(&m_tlscontext,srv_random,32);
		__private_tls_update_hash(&m_tlscontext,compress_test,33);
		__private_tls_update_hash(&m_tlscontext,decompress_test,64);
		__private_tls_get_hash(&m_tlscontext,sign_out);
		__private_tls_done_hash(&m_tlscontext,publicK);
		fnWDT_Restart();
		Cm_Ram_Inter(public_key_for_share,32);  
		Cm_Ram_Inter(public_key_for_share+32,32);
		uECC_valid_public_key(public_key_for_share,p_curve);
#endif
#if 0 //共享密钥测试
		if (1 == uECC_make_key((unsigned char *)m_tlscontext.public_key,(unsigned char *)privateK,p_curve))
		{
		}
		
		mbedtls_ecp_group_load( &grp, MBEDTLS_ECP_DP_SECP256R1);
		mbedtls_ecp_gen_keypair(&grp,&m,&R,Gen_Random,NULL);
		
		mbedtls_ecp_point_write_binary(&grp,&R,MBEDTLS_ECP_PF_UNCOMPRESSED,(size_t*)&result,sign_out,80);
		mbedtls_ecp_point_free(&R);
		
		memcpy(m_tlscontext.server_verify_data+1,m_tlscontext.public_key,64);
		m_tlscontext.server_verify_data[0]=0x04;
		memcpy(m_tlscontext.public_key,sign_out+1,64);
		
		Cm_Ram_Inter(m_tlscontext.public_key,32);
		Cm_Ram_Inter(m_tlscontext.public_key+32,32);
		
		Cm_Ram_Inter(m_tlscontext.server_verify_data+1,32);
		Cm_Ram_Inter(m_tlscontext.server_verify_data+33,32);
		mbedtls_ecp_point_read_binary(&grp,&R,m_tlscontext.server_verify_data,65);
		
		uECC_shared_secret(m_tlscontext.public_key,m_tlscontext.priv,m_tlscontext.share_key,p_curve);
		mbedtls_ecdh_compute_shared(&grp,&r,&R,&m,Gen_Random,NULL);
		mbedtls_mpi_write_binary(&r,sign_out,32);
		fnWDT_Restart();
		mbedtls_ecp_point_free( &R );
		mbedtls_mpi_free( &m );
		mbedtls_mpi_free( &r);
		mbedtls_mpi_free( &s );
		mbedtls_ecp_group_free(&grp);
		
		result=mbedtls_ecp_group_load( &grp, MBEDTLS_ECP_DP_ANSIP256R1);
	//	result=mbedtls_ecp_gen_keypair(&grp,&m,&R,Gen_Random,NULL);
		mbedtls_mpi_read_binary(&m,b_pri,32);
		result=mbedtls_ecp_check_privkey(&grp,&m);
		result=mbedtls_ecp_mul(&grp,&R,&m, &grp.G, Gen_Random,NULL);//生成公钥
		mbedtls_ecp_point_write_binary(&grp,&R,MBEDTLS_ECP_PF_UNCOMPRESSED,(size_t*)&result,m_tlscontext.server_verify_data,80);
		//mbedtls_ecdsa_sign(&grp,&r, &s,&m,hash_test_buff,64,Gen_Random,NULL);
#endif		
	//	m_tlscontext.grp_id=MBEDTLS_ECP_DP_SECP256R1;
		m_tlscontext.grp_id=MBEDTLS_ECP_DP_BP256R1;
		m_tlscontext.crypto_time=120;
		return 0;
}
/*
void Cm_Ram_Inter(uint8_t *buf,uint16_t Len)
{
	uint16_t i;
	uint8_t tmp;
	if(Len<2)
		return;
	for(i=0;i<Len/2;++i)
	{
		tmp = buf[i];
		buf[i] = buf[Len-1-i];
		buf[Len-1-i]=tmp;
	}
}*/

int tls_packet_append(struct TLSPacket *packet, unsigned char *buf, unsigned int len) 
{
	unsigned int new_len;
	if ((!packet))
		return -1;
    // if (!len)
   //     return 0;
		new_len = packet->len + len;
    packet->size = new_len;
		memcpy(packet->buf + packet->len, buf, len);
    packet->len = new_len;
    return new_len;
}

int tls_packet_uint8(struct TLSPacket *packet, unsigned char i) {
    return tls_packet_append(packet, &i, 1);
}

int tls_packet_uint16(struct TLSPacket *packet, unsigned short i) {
    unsigned short ni = htons(i);
    return tls_packet_append(packet, (unsigned char *)&ni, 2);
}

int tls_packet_uint32(struct TLSPacket *packet, unsigned int i) {
    unsigned int ni = htonl(i);
    return tls_packet_append(packet, (unsigned char *)&ni, 4);
}

int tls_packet_uint24(struct TLSPacket *packet, unsigned int i) {
    unsigned char buf[3];
    buf[0] = i / 0x10000;
    i %= 0x10000;
    buf[1] = i / 0x100;
    i %= 0x100;
    buf[2] = i;
    
    return tls_packet_append(packet, buf, 3);
}

int tls_parse_hello(struct TLSContext *context, const unsigned char *buf, int buf_len, unsigned int *write_packets, unsigned int *dtls_verified) 
{
	int res = 5;
	unsigned char session_len;
	unsigned short cipher_len;
	
  *write_packets = 0;
  *dtls_verified = 0;      	
	//memcpy(context->remote_random,(const void *)buf[res],__TLS_CLIENT_RANDOM_SIZE);
	memcpy(context->remote_random,(const void *)&buf[res],__TLS_CLIENT_RANDOM_SIZE);
	res += __TLS_CLIENT_RANDOM_SIZE;
	session_len = buf[res++];
	if(session_len)
	{
		res += session_len;
	}
	
	cipher_len = ntohs(*(unsigned short *)&buf[res]);
	if (cipher_len & 1)
		return 0;
	res += cipher_len;
	res += 2;
	
	cipher_len=buf[res++];
	res += cipher_len;//comparsion len
	
	//extension len
	if (res > 2) {
        cipher_len = ntohs(*(unsigned short *)&buf[res]);
        res += 2;
	}
	*write_packets = 2;
	return res;
}
void tls_head(struct TLSPacket *packet)
{
	tls_packet_uint8(packet, 0x16);
	tls_packet_uint16(packet,0x0303);
}

struct TLSPacket *tls_build_server_key_exchange(struct TLSContext *context, int method) 
{
	struct TLSPacket packet;
	unsigned char *privateK;
	unsigned char *publicK;
	unsigned char *buf;
	int i;
	privateK = context->priv;
	publicK = context->public_key;
#ifdef UECC_TEST
//#if 1	
	uECC_make_key((unsigned char *)context->public_key,(unsigned char *)privateK,p_curve);
#else
#if 0	
	fnWDT_Restart();
	memcpy(sign_out,privateK,32);
	Cm_Ram_Inter(sign_out,32);
	mbedtls_mpi_read_binary(&m,sign_out,32);
#endif	
	//mbedtls_mpi_read_binary(&m,b_pri,32);
	if(context->grp_id != grp.id)
	{
	//	mbedtls_ecp_group_free(&grp);
		mbedtls_ecp_group_load( &grp, context->grp_id);
	}
//	mbedtls_ecp_mul(&grp,&R,&m, &grp.G, Gen_Random,NULL);//生成公钥
	mbedtls_ecp_gen_keypair(&grp,&m,&R,Gen_Random,NULL);
	//mbedtls_mpi_write_binary(&R.X,publicK,32);
//	mbedtls_mpi_write_binary(&R.Y,publicK+32,32);
	mbedtls_mpi_write_binary(&m,context->priv,m.n*4);
	fnWDT_Restart();
#endif	

	packet.buf = context->message_buffer+context->message_buffer_len;
	//buf = packet.buf+160;
	buf = sign_out;
	packet.len=packet.size=0;
	tls_head(&packet);
	tls_packet_uint16(&packet, 0x75);
	tls_packet_uint8(&packet, 0x0C);
	tls_packet_uint24(&packet, 0x71);
	tls_packet_uint8(&packet, 0x03);
	if(m_tlscontext.grp_id==MBEDTLS_ECP_DP_BP256R1)
	{
		tls_packet_uint16(&packet,0x1a);//brainpool256r1
	}
	else if(m_tlscontext.grp_id==MBEDTLS_ECP_DP_BP384R1)
	{
		tls_packet_uint16(&packet,0x1b);//brainpool384r1
	}
	else if(m_tlscontext.grp_id==MBEDTLS_ECP_DP_SECP384R1)
	{
		tls_packet_uint16(&packet,0x18);//SECP384r1
	}
	else
	{
		tls_packet_uint16(&packet,0x17);//ecc256r1
	}
	//tls_packet_uint8(&packet,0x21);  //not product
	tls_packet_uint8(&packet,R.X.n*2+1);
	fnWDT_Restart();
#ifdef UECC_TEST	
//#if 1	
	uECC_compress(publicK,packet.buf+packet.len,p_curve);
	fnWDT_Restart();
	Cm_Ram_Inter(packet.buf+packet.len+1,32);
	packet.len +=0x21;
#else
	mbedtls_ecp_point_write_binary(&grp,&R,MBEDTLS_ECP_PF_COMPRESSED,&i,packet.buf+packet.len,128);
	packet.len +=i;
#endif
		
	memcpy(buf,context->remote_random,__TLS_CLIENT_RANDOM_SIZE);
	memcpy(buf+__TLS_CLIENT_RANDOM_SIZE,context->local_random, __TLS_SERVER_RANDOM_SIZE);
	memcpy(buf+__TLS_CLIENT_RANDOM_SIZE+__TLS_SERVER_RANDOM_SIZE, packet.buf + 9, packet.len-9);

	fnWDT_Restart();
	mbedtls_sha512(buf,__TLS_CLIENT_RANDOM_SIZE+__TLS_SERVER_RANDOM_SIZE+packet.len-9,publicK,0);	
#ifdef UECC_TEST
	Cm_Ram_Inter(publicK,32);
	fnWDT_Restart();
	Cm_Ram_Inter(publicK+32,32);
	fnWDT_Restart();	
	uECC_sign(context->ecc_priv,publicK,64,sign_out,p_curve);
#else
	if(context->grp_id != grp.id)
	{
	//	mbedtls_ecp_group_free(&grp);
		mbedtls_ecp_group_load( &grp, context->grp_id);
	}
#if 0	
	memcpy(sign_out,context->ecc_priv,32);
	Cm_Ram_Inter(sign_out,32);  
	mbedtls_mpi_read_binary(&m,sign_out,32);
#else
	if((m_tlscontext.grp_id==MBEDTLS_ECP_DP_BP384R1)|| (m_tlscontext.grp_id==MBEDTLS_ECP_DP_SECP384R1))
		mbedtls_mpi_read_binary(&m,context->ecc_priv,48);	
	else
		mbedtls_mpi_read_binary(&m,context->ecc_priv,32);	
#endif	
	//fnWDT_Restart();
	//	mbedtls_ecp_mul(&grp,&R,&m, &grp.G, Gen_Random,NULL);//生成公钥
	fnWDT_Restart();
	mbedtls_mpi_free( &r);
	mbedtls_mpi_free( &s );
	mbedtls_ecdsa_sign(&grp,&r, &s,&m,publicK,64,Gen_Random,NULL);
	//memcpy(sign_out,r.p,32);
	//memcpy(sign_out,s.p,32);
	mbedtls_mpi_write_binary(&r,sign_out,r.n*4);
	mbedtls_mpi_write_binary(&s,sign_out+32,r.n*4);
	mbedtls_mpi_free( &m );
	//mbedtls_mpi_free( &r);
	//mbedtls_mpi_free( &s );
	mbedtls_ecp_point_free( &R );
//	mbedtls_ecp_group_free( &grp );
	fnWDT_Restart();
#endif
	fnWDT_Restart();
		//for test
#if 0		
		fnWDT_Restart();
		if(uECC_compute_public_key(context->ecc_priv,context->public_key,p_curve))
		{
			fnWDT_Restart();
			uECC_verify((uint8_t *)context->public_key,publicK,64,sign_out,p_curve);
		}
		fnWDT_Restart();
#endif		
		//test end
	
#if 1		
	tls_packet_uint8(&packet,sha512);
	tls_packet_uint8(&packet,ecdsa);
#endif
#if 0			
#if 1	
	tls_packet_uint16(&packet,0x48);//ecdsa len
	tls_packet_uint16(&packet,0x3046);
	tls_packet_uint16(&packet,0x0221);
	tls_packet_uint8(&packet,0x00);
#else
	tls_packet_uint16(&packet,0x46);//ecdsa len
	tls_packet_uint16(&packet,0x3044);
	tls_packet_uint16(&packet,0x0220);
#endif

	Cm_Ram_Inter(sign_out,32);
	fnWDT_Restart();
	Cm_Ram_Inter(sign_out+32,32);
	tls_packet_append(&packet,sign_out, 32);
#if 1	
	tls_packet_uint16(&packet,0x0221);
	tls_packet_uint8(&packet,0x00);
#else
	tls_packet_uint16(&packet,0x0220);
#endif
#else
#ifdef UECC_TEST
	Cm_Ram_Inter(sign_out,32);
	fnWDT_Restart();
	Cm_Ram_Inter(sign_out+32,32);
#endif	
	i=0;
	if(sign_out[0]&0x80)
		i++;
	if(sign_out[32]&0x80)
		i++;
#if 0	
	tls_packet_uint16(&packet,0x46+i);//ecdsa len
	tls_packet_uint16(&packet,0x3044+i);
	if(sign_out[0]&0x80)
	{
		tls_packet_uint16(&packet,0x0221);
		tls_packet_uint8(&packet,0x00);
	}
	else
	{
		tls_packet_uint16(&packet,0x0220);
	}
	tls_packet_append(&packet,sign_out, 32);
	if(sign_out[32]&0x80)
	{
		tls_packet_uint16(&packet,0x0221);
		tls_packet_uint8(&packet,0x00);
	}
	else
	{
		tls_packet_uint16(&packet,0x0220);
	}
#else
	tls_packet_uint16(&packet,r.n*8+6+i);//ecdsa len
	tls_packet_uint16(&packet,0x3000+r.n*8+4+i);
	if(sign_out[0]&0x80)
	{
		tls_packet_uint16(&packet,0x0200+r.n*4+1);
		tls_packet_uint8(&packet,0x00);
	}
	else
	{
		tls_packet_uint16(&packet,0x0200+r.n*4);
	}
	mbedtls_mpi_write_binary(&r,packet.buf+packet.len,r.n*4);
	packet.len +=r.n*4;

	if(sign_out[32]&0x80)
	{
		tls_packet_uint16(&packet,0x0200+r.n*4+1);
		tls_packet_uint8(&packet,0x00);
	}
	else
	{
		tls_packet_uint16(&packet,0x0200+r.n*4);
	}
	mbedtls_mpi_write_binary(&s,packet.buf+packet.len,r.n*4);
	packet.len +=r.n*4;
#endif	
#endif
//	tls_packet_append(&packet,sign_out+32, 32);
	packet.buf[3]=((packet.len-5)>>8)&0xff;
	packet.buf[4]=((packet.len-5))&0xff;
	packet.buf[6]=((packet.len-9)>>16)&0xff;
	packet.buf[7]=((packet.len-9)>>8)&0xff;
	packet.buf[8]=((packet.len-9))&0xff;
	__private_tls_update_hash(context,packet.buf+5, packet.len-5);
	context->message_buffer_len += packet.len;
	//return &packet;
	return NULL;
}

struct TLSPacket *tls_certificate_request(struct TLSContext *context) 
{
	struct TLSPacket packet;
	uint16_t rd_ptr,len,type;
	uint8_t *smgw_cert;
	packet.buf = context->message_buffer+context->message_buffer_len;
	packet.len=packet.size=0;
	tls_head(&packet);
	tls_packet_uint16(&packet, 0x56);
	tls_packet_uint8(&packet, 0x0D);
	tls_packet_uint24(&packet, 0x52);
	tls_packet_uint8(&packet, 0x01);
	tls_packet_uint8(&packet, ecdsa_sign); //ecdsa_sign
	tls_packet_uint16(&packet, 0x02); //
	tls_packet_uint8(&packet, sha256);  //
	tls_packet_uint8(&packet, sha224);
#if 0	
	tls_packet_uint16(&packet, 0x4a);
	tls_packet_uint16(&packet, 0x48);
#endif	
#if 0	
	E2P_RData(packet.buf+packet.len,E2P_SMGW_Certi+140,0x48);
	packet.len=packet.size=packet.len+0x48;
#else	
	smgw_cert = Get_SMGW_Cert();
		for(rd_ptr=8,type=0;(rd_ptr<240) && type<5;type++)
		{
			if(smgw_cert[rd_ptr+1]&0x80)
			{
				len=smgw_cert[rd_ptr+2]<<8|smgw_cert[rd_ptr+3];
				len +=3;
			}
			else
			{
				len=smgw_cert[rd_ptr+1];
				len+=2;
			}
			rd_ptr +=len;
		}
		
		if(type==5)
		{	
			tls_packet_uint16(&packet, smgw_cert[rd_ptr+1]+4);
			tls_packet_uint16(&packet, smgw_cert[rd_ptr+1]+2);
			tls_packet_append(&packet,smgw_cert+rd_ptr,smgw_cert[rd_ptr+1]+2);
		}
//	tls_packet_append(&packet,smgw_cert+140,0x48);
#endif
	packet.buf[3]=((packet.len-5)>>8)&0xff;
	packet.buf[4]=((packet.len-5))&0xff;
	packet.buf[6]=((packet.len-9)>>16)&0xff;
	packet.buf[7]=((packet.len-9)>>8)&0xff;
	packet.buf[8]=((packet.len-9))&0xff;	
	__private_tls_update_hash(context,packet.buf+5, packet.len-5);
	context->message_buffer_len += packet.len;
	//return &packet;
	return NULL;
}

struct TLSPacket *tls_build_done(struct TLSContext *context) {
    struct TLSPacket *packet;
	  struct TLSPacket s_packet;
		packet=&s_packet;
		packet->len=packet->size=0;
		packet->buf = context->message_buffer+context->message_buffer_len;
		tls_head(packet);
		tls_packet_uint16(packet, 0x04);
    tls_packet_uint8(packet, 0x0E);
    tls_packet_uint24(packet, 0);
		__private_tls_update_hash(context,packet->buf+5, packet->len-5);
		context->message_buffer_len += packet->len;
    //return packet;
	return NULL;
}

int16_t tls_back_fun(uint8_t *buf)
{
	m_tlscontext.message_buffer_len=0;
	m_tlscontext.message_buffer=buf;
	fnWDT_Restart();
#if 1	
	tls_build_server_key_exchange(&m_tlscontext,1);
	fnWDT_Restart();
	tls_certificate_request(&m_tlscontext);
#else
	tls_certificate_request(&m_tlscontext);
	fnWDT_Restart();
	tls_build_server_key_exchange(&m_tlscontext,1);
#endif	
	fnWDT_Restart();
	tls_build_done(&m_tlscontext);
	fnWDT_Restart();
	return m_tlscontext.message_buffer_len;
}
uint32_t sec;
struct TLSPacket *tls_build_hello(struct TLSContext *context) 
{
	struct TLSPacket *packet;
//	unsigned char dummy[3];
//	unsigned char *privateK;
 // unsigned char publicK[64];
	
	struct TLSPacket s_packet;
	
	packet=&s_packet;
	
	//privateK = context->priv;
	
	//uECC_compute_public_key(privateK,publicK,p_curve);
	//memcpy(context->local_random,publicK,__TLS_SERVER_RANDOM_SIZE);
///	memcpy(context->session,publicK+32,__TLS_MAX_SESSION_ID);
	ecc_rng(context->local_random,32);
	ecc_rng(context->session,32);
	//memcpy(context->local_random,context->remote_random,4);
	//context->local_random[3]+=46;
	/*if (1 == uECC_make_key((unsigned char *)publicK,(unsigned char *)privateK,p_curve))
	{
	}*/
	
	packet->buf = context->message_buffer;
	packet->len=packet->size=0;
	tls_packet_uint8(packet, 0x16);
	tls_packet_uint16(packet, 0x0303);
	tls_packet_uint16(packet, 0x57);
	tls_packet_uint8(packet, 0x02);
	//tls_packet_append(packet, dummy, 3);
	tls_packet_uint24(packet,0x53);
	tls_packet_uint16(packet, 0x0303);
	tls_packet_append(packet, context->local_random, __TLS_SERVER_RANDOM_SIZE);
	// session size
	context->session_size = __TLS_MAX_SESSION_ID;
	/*context->session[0]=0x02;
	context->session[1]=0xF0;
	context->session[2]=0xBA;
	context->session[3]=0xCC;*/
	//memcpy(context->session,&sec,4);
	//Cm_Ram_Inter(context->session,4);
	tls_packet_uint8(packet, context->session_size);
	//ecc_rng(context->session,context->session_size);
	tls_packet_append(packet, context->session, context->session_size);
	tls_packet_uint16(packet, 0xc023);
	// no compression
  tls_packet_uint8(packet, 0);
	
	// extensions size
		tls_packet_uint16(packet, 5 + 6);
   // secure renegotation
   // advertise it, but refuse renegotiation
		tls_packet_uint16(packet, 0xff01);
		tls_packet_uint16(packet, 1);
		tls_packet_uint8(packet, 0);
		tls_packet_uint32(packet, 0x000b0002);
		tls_packet_uint16(packet, 0x0100);
		__private_tls_update_hash(context,packet->buf+5, packet->len-5);
		context->message_buffer_len = packet->len;
		return packet;
}
extern uint16_t Get_LMN_Cert_Len(uint8_t *recvbuf,uint16_t ret);
struct TLSPacket *tls_build_certificate(struct TLSContext *context) 
{
	struct TLSPacket *packet;
	int rd_len,rd_ptr;
	char type;
	int len;
//	int rd_length;
	uint8_t *b_lmn_cert;
	struct TLSPacket s_packet;
	packet=&s_packet;
	packet->buf = context->message_buffer+context->message_buffer_len;
	packet->context = context;
	packet->len=packet->size=0;
	b_lmn_cert = Get_LMN_Cert();
	tls_packet_uint8(packet, 0x16);
	tls_packet_uint16(packet, 0x0303);
//	tls_packet_uint16(packet, 0x01a0);
//	tls_packet_uint8(packet, 0x0B);
#if 0	
	E2P_RData(packet->buf+packet->len,E2P_LMN_Certi,32);
	for(rd_ptr=0,rd_len=0x197;rd_ptr<30;++rd_ptr)
	{
		//if(packet->buf[packet->len+rd_ptr]&0x80)
		if(packet->buf[packet->len+rd_ptr]==0x82)
		{
			rd_len=(packet->buf[packet->len+rd_ptr+1]<<8)|packet->buf[packet->len+rd_ptr+2];
			//rd_len+=rd_ptr+3;
			rd_len +=4;
			break;
		}
	}
#else
	/*
	for(rd_ptr=0,rd_len=0x197;rd_ptr<30;++rd_ptr)
	{
		if(b_lmn_cert[rd_ptr]==0x82)
		{
			rd_len=(b_lmn_cert[rd_ptr+1]<<8)|b_lmn_cert[rd_ptr+2];
			rd_len +=4;
			break;
		}
	}*/
	rd_len=(b_lmn_cert[2]<<8)|b_lmn_cert[3];
	if(rd_len>500)
	{
			rd_len=Get_LMN_Cert_Len(b_lmn_cert+4,rd_len);
	}
	rd_len+=4;
#endif	
	tls_packet_uint16(packet,rd_len+10);
	tls_packet_uint8(packet, 0x0B);
	tls_packet_uint24(packet, rd_len+6);
	tls_packet_uint24(packet, rd_len+3);
	tls_packet_uint24(packet, rd_len);
	/*tls_packet_uint24(packet, 0x019c);
	tls_packet_uint24(packet, 0x0199);
	tls_packet_uint24(packet, rd_len);*/
	//rd_ptr=0;
	//while(rd_len)
/*	for(rd_ptr=0,rd_length=0;rd_len;)
	{
		WDT->EN = 0xbb;
		if(rd_len>128)
			rd_length=128;
		else
			rd_length=rd_len;
		E2P_RData(packet->buf+packet->len+rd_ptr,E2P_LMN_Certi+rd_ptr,rd_length);
		rd_len -= rd_length;
		rd_ptr += rd_length;
	}*/
//	if(rd_ptr>0)
	{
#if 0		
		//E2P_RData(packet->buf+packet->len,E2P_LMN_Certi+rd_ptr-1,rd_len);
		E2P_RData(packet->buf+packet->len,E2P_LMN_Certi,rd_len);
		fnWDT_Restart();
		//E2P_RData(context->ecc_priv,E2P_LMN_Certi+rd_len+rd_ptr+6,32);
		E2P_RData(context->ecc_priv,E2P_LMN_Certi+rd_len+7,32);
		fnWDT_Restart();
		Cm_Ram_Inter(context->ecc_priv,32);
#else
		memcpy(packet->buf+packet->len,b_lmn_cert,rd_len);
#endif		
	}
	//memcpy(packet->buf+packet->len,b_lmn_cert,rd_len);
	packet->len=packet->size=packet->len+rd_len;
	__private_tls_update_hash(context,packet->buf+5, packet->len-5);
	context->message_buffer_len +=packet->len;
	
	for(rd_ptr=8,type=0;(rd_ptr<rd_len) && type<7;type++)
	{
		if(b_lmn_cert[rd_ptr+1]&0x80)
		{
			len=b_lmn_cert[rd_ptr+2]<<8|b_lmn_cert[rd_ptr+3];
			len +=3;
		}
		else
		{
			len=b_lmn_cert[rd_ptr+1];
      len+=2;
		}
		rd_ptr +=len;
	}
	if(type==7)
	{	
		rd_ptr-=len;
		rd_ptr +=4;
		rd_ptr += b_lmn_cert[rd_ptr+1]+2;
		if(memcmp(b_lmn_cert+rd_ptr+2,MBEDTLS_OID_EC_GRP_SECP256R1,b_lmn_cert[rd_ptr+1])==0)
		{
			m_tlscontext.grp_id=MBEDTLS_ECP_DP_SECP256R1;
		}
		else if(memcmp(b_lmn_cert+rd_ptr+2,MBEDTLS_OID_EC_GRP_BP256R1,b_lmn_cert[rd_ptr+1])==0)
		{
			m_tlscontext.grp_id=MBEDTLS_ECP_DP_BP256R1;
		} 
		else if(memcmp(b_lmn_cert+rd_ptr+2,MBEDTLS_OID_EC_GRP_SECP384R1,b_lmn_cert[rd_ptr+1])==0)
		{
			m_tlscontext.grp_id=MBEDTLS_ECP_DP_SECP384R1;
		}
		else if(memcmp(b_lmn_cert+rd_ptr+2,MBEDTLS_OID_EC_GRP_BP384R1,b_lmn_cert[rd_ptr+1])==0)
		{
			m_tlscontext.grp_id=MBEDTLS_ECP_DP_BP384R1;
		} 
	}
	return packet;
}

#define LTC_HMAC_BLOCKSIZE 64
#define __TLS_MAX_HASH_LEN 32
typedef union Hash_state {
  //  char                   dummy[1];
    mbedtls_sha256_context sha256;
  //  void                   *data;
} hash_state;
typedef struct Hmac_state {
  //  hash_state    md;
//    int           hash;
		mbedtls_sha256_context sha256;
    unsigned char key[LTC_HMAC_BLOCKSIZE];
} hmac_state;
int hash_memory(int hash, const unsigned char *in, unsigned long inlen, unsigned char *out, unsigned long *outlen)
{
	//hash_state md;
	
	mbedtls_sha256(in,inlen,out,0);
	*outlen = 32;
	return 0;
}
static uint8_t buf1[LTC_HMAC_BLOCKSIZE];
int hmac_init(hmac_state *hmac, int hash, const unsigned char *key, unsigned long keylen)
{
  //uint8_t buf[LTC_HMAC_BLOCKSIZE];
	unsigned int z;
	int i;
	if(keylen > LTC_HMAC_BLOCKSIZE) {
        z = LTC_HMAC_BLOCKSIZE;
				hash_memory(hash,key,keylen,hmac->key,&z); 
				keylen = 32;
	}
	else
	{
			memcpy(hmac->key,key,keylen);
	}
	if(keylen<LTC_HMAC_BLOCKSIZE)
	{
		for(i=keylen;i<LTC_HMAC_BLOCKSIZE;++i)
		{
			hmac->key[i]=0;
		}
	}
	for(i=0; i < LTC_HMAC_BLOCKSIZE; i++) {
       buf1[i] = hmac->key[i] ^ 0x36;
    }
	mbedtls_sha256_init(&(hmac->sha256));
	mbedtls_sha256_starts(&(hmac->sha256),0);
	mbedtls_sha256_update(&(hmac->sha256),buf1,LTC_HMAC_BLOCKSIZE);
	return 0;
}
int hmac_process(hmac_state *hmac, const unsigned char *in, unsigned long inlen)
{
	fnWDT_Restart();
	mbedtls_sha256_update(&(hmac->sha256),in,inlen);
	return 0;
}
int hmac_done(hmac_state *hmac, unsigned char *out, unsigned long *outlen)
{
	//uint8_t  buf[LTC_HMAC_BLOCKSIZE];
	//uint8_t *buf;
	uint8_t  isha[32];
	int i;
	//buf=sign_out;
	mbedtls_sha256_finish( &(hmac->sha256), isha );
	for(i=0; i < LTC_HMAC_BLOCKSIZE; i++) {
        buf1[i] = hmac->key[i] ^ 0x5C;
    }
	mbedtls_sha256_init(&(hmac->sha256));
	//fnWDT_Restart();
	mbedtls_sha256_starts(&(hmac->sha256),0);
	fnWDT_Restart();
	mbedtls_sha256_update(&(hmac->sha256),buf1,LTC_HMAC_BLOCKSIZE);
	//fnWDT_Restart();
	mbedtls_sha256_update(&(hmac->sha256),isha,32);
	fnWDT_Restart();
	mbedtls_sha256_finish(&(hmac->sha256), out);
	fnWDT_Restart();
	*outlen=32;
	return 0;	
}
#if 0
void __private_tls_prf_helper(  int hash_idx, unsigned char *output, unsigned int outlen, const unsigned char *secret, const unsigned int secret_len,
                              const unsigned char *label, unsigned int label_len, unsigned char *seed, unsigned int seed_len,
                              unsigned char *seed_b, unsigned int seed_b_len) {
    unsigned char digest_out0[__TLS_MAX_HASH_LEN];
    unsigned char digest_out1[__TLS_MAX_HASH_LEN];
    unsigned long dlen = 32;
    unsigned int i;
		unsigned int copylen;
		int idx;
    hmac_state hmac;
    
    hmac_init(&hmac, hash_idx, secret, secret_len);
    hmac_process(&hmac, label, label_len);
    
    hmac_process(&hmac, seed, seed_len);
    if ((seed_b) && (seed_b_len))
        hmac_process(&hmac, seed_b, seed_b_len);
    hmac_done(&hmac, digest_out0, &dlen);
    idx = 0;
    while (outlen) {
        hmac_init(&hmac, hash_idx, secret, secret_len);
        hmac_process(&hmac, digest_out0, dlen);
        hmac_process(&hmac, label, label_len);
        hmac_process(&hmac, seed, seed_len);
        if ((seed_b) && (seed_b_len))
            hmac_process(&hmac, seed_b, seed_b_len);
        hmac_done(&hmac, digest_out1, &dlen);
        
       copylen = outlen;
        if (copylen > dlen)
            copylen = dlen;
        
        for (i = 0; i < copylen; i++) {
            output[idx++] ^= digest_out1[i];
            outlen--;
        }
        
        if (!outlen)
            break;
        
        hmac_init(&hmac, hash_idx, secret, secret_len);
        hmac_process(&hmac, digest_out0, dlen);
        hmac_done(&hmac, digest_out0, &dlen);
    }
}
#endif

void __private_tls_prf(struct TLSContext *context,
                       unsigned char *output, unsigned int outlen, const unsigned char *secret, const unsigned int secret_len,
                       const unsigned char *label, unsigned int label_len, unsigned char *seed, unsigned int seed_len,
                       unsigned char *seed_b, unsigned int seed_b_len)
{
		hmac_state hmac;
    int hash_idx;
		unsigned char digest_out0[__TLS_MAX_HASH_LEN];
    unsigned char digest_out1[__TLS_MAX_HASH_LEN];	
	//	unsigned char *digest_out0;
	//	unsigned char *digest_out1;
		unsigned long dlen = 32;
		int i,copylen,idx;
	//	digest_out0=sign_out+64;
	//	digest_out1=digest_out0+__TLS_MAX_HASH_LEN;
		hmac_init(&hmac, hash_idx, secret, secret_len);
    hmac_process(&hmac, label, label_len);
		hmac_process(&hmac, seed, seed_len);
		if ((seed_b) && (seed_b_len))
			hmac_process(&hmac, seed_b, seed_b_len);
		hmac_done(&hmac, digest_out0, &dlen);
		idx=0;
		while (outlen) {
            hmac_init(&hmac, hash_idx, secret, secret_len);
            hmac_process(&hmac, digest_out0, dlen);
            hmac_process(&hmac, label, label_len);
            hmac_process(&hmac, seed, seed_len);
            if ((seed_b) && (seed_b_len))
                hmac_process(&hmac, seed_b, seed_b_len);
            hmac_done(&hmac, digest_out1, &dlen);
            
            copylen = outlen;
            if (copylen > dlen)
                copylen = (unsigned int)dlen;
            
            for (i = 0; i < copylen; i++) {
                output[idx++] = digest_out1[i];
                outlen--;
            }
            
            if (!outlen)
                break;
            
            hmac_init(&hmac, hash_idx, secret, secret_len);
            hmac_process(&hmac, digest_out0, dlen);
            hmac_done(&hmac, digest_out0, &dlen);
        }
		return;
}
int __private_tls_crypto_create(struct TLSContext *context, int key_length, int iv_length, unsigned char *localkey, unsigned char *localiv, unsigned char *remotekey, unsigned char *remoteiv)
{
	return 0;
}
//#define __TLS_MAX_KEY_EXPANSION_SIZE 192
int __private_tls_expand_key(struct TLSContext *context) 
{
//	int key_length =16;
//	int mac_length = 32;
	//unsigned char key[__TLS_MAX_KEY_EXPANSION_SIZE];
	__private_tls_prf(context, sign_out, __TLS_MAX_KEY_EXPANSION_SIZE, context->master_key, context->master_key_len, (unsigned char *)"key expansion", 13, context->local_random, __TLS_SERVER_RANDOM_SIZE, context->remote_random, __TLS_CLIENT_RANDOM_SIZE);
	memcpy(context->remote_mac,sign_out,32);
	memcpy(context->local_mac,sign_out+32,32);
	memcpy(context->clientkey,sign_out+64,16);
	memcpy(context->serverkey,sign_out+80,16);
	memcpy(context->clientiv,sign_out+96,16);
	memcpy(context->serveriv,sign_out+112,16);
	CmEnAES128(context->serverkey,context->serveriv,0,0,0,0);
	CmDeAES128(context->clientkey,context->clientiv,0,0,0,0);
	return 0;
}

const unsigned char master_secret_label[] = "master secret";
int tls_parse_client_key_exchange(struct TLSContext *context, const unsigned char *buf, int buf_len) 
{
	//int res;
	unsigned int size = buf[0] * 0x10000 + buf[1] * 0x100 + buf[2];
//	unsigned char publicK[64];
	
	//res=3;
#ifdef UECC_TEST
	if(size==0x42)
	{
		memcpy(context->public_key,buf+5,64);	
		Cm_Ram_Inter(context->public_key,32);
		Cm_Ram_Inter(context->public_key+32,32);
		
	}
	else
	{		
		Cm_Ram_Inter((uint8_t *)buf+6,32);	
		uECC_decompress(buf+5,(uint8_t *)context->public_key,p_curve);
	}	
	uECC_shared_secret(context->public_key,context->priv,context->share_key,p_curve);
	Cm_Ram_Inter(context->share_key,32);
#else
	if(context->grp_id != grp.id)
	{
	//	mbedtls_ecp_group_free(&grp);
		mbedtls_ecp_group_load( &grp, context->grp_id);
	}
	mbedtls_ecp_point_read_binary(&grp,&R,buf+4,size-1);
	memcpy(context->master_key,context->priv,32);
//	Cm_Ram_Inter(context->master_key,32);
	mbedtls_mpi_read_binary(&m,context->master_key,32);
	mbedtls_ecdh_compute_shared(&grp,&r,&R,&m,Gen_Random,NULL);
	mbedtls_mpi_write_binary(&r,context->share_key,32);
	mbedtls_mpi_free(&r);
	mbedtls_mpi_free(&m);
	mbedtls_ecp_point_free(&R);
#endif	
	context->master_key_len=48;
	__private_tls_prf(context,
                              context->master_key, context->master_key_len,
                              context->share_key, 32,
                              master_secret_label, 13,
                              context->remote_random, __TLS_CLIENT_RANDOM_SIZE,
                              context->local_random, __TLS_SERVER_RANDOM_SIZE);
	__private_tls_expand_key(context);
	return 0;
}

struct TLSPacket *tls_build_change_cipher(struct TLSContext *context) {
    struct TLSPacket *packet;
	  struct TLSPacket s_packet;
		packet=&s_packet;
		packet->len=packet->size=0;
		packet->buf = context->message_buffer+context->message_buffer_len;
		tls_packet_uint8(packet, TLS_CHANGE_CIPHER);
    tls_packet_uint16(packet, 0x0303);
    tls_packet_uint24(packet, 0x0101);
		context->local_sequence_number = 0;
		context->message_buffer_len += packet->len;
    return packet;
}
unsigned int __private_tls_hmac_message(unsigned char local, struct TLSContext *context, const unsigned char *buf, int buf_len, const unsigned char *buf2, int buf_len2, unsigned char *out, unsigned int outlen, uint64_t remote_sequence_number) 
{
//	int mac_size = outlen;
	hmac_state m_hmac;
	uint64_t squence_number;
	unsigned long ref_outlen = outlen;
	if (hmac_init(&m_hmac, 0, local ? context->local_mac : context->remote_mac, 32))
        return 0;
	if (local)
		squence_number = htonll(context->local_sequence_number);
	else
		squence_number = htonll(context->remote_sequence_number);
	if (hmac_process(&m_hmac, (unsigned char *)&squence_number, 8))
		return 0;
    
	if (hmac_process(&m_hmac, buf, buf_len))
		return 0;
	if ((buf2) && (buf_len2)) {
		if (hmac_process(&m_hmac, buf2, buf_len2))
			return 0;
	}
	if (hmac_done(&m_hmac, out, &ref_outlen))
		return 0;
	return (unsigned int)ref_outlen;
}
#define __TLS_MIN_FINISHED_OPAQUE_LEN 12
//uint8_t server_str[]={"server finished"};
struct TLSPacket *tls_build_serverfinished(struct TLSContext *context) {
    struct TLSPacket *packet;
	  struct TLSPacket s_packet;
//		uint32_t pos,pos1;
		unsigned char hash[32],out[__TLS_MIN_FINISHED_OPAQUE_LEN];
		packet=&s_packet;
		packet->len=packet->size=0;
		packet->buf = context->message_buffer+context->message_buffer_len;
		tls_head(packet);
		tls_packet_uint16(packet, 16);  //len
		tls_packet_uint8(packet, 0x14);  //type
		tls_packet_uint24(packet, __TLS_MIN_FINISHED_OPAQUE_LEN);
		__private_tls_done_hash(context, hash);
		__private_tls_prf(context, out, __TLS_MIN_FINISHED_OPAQUE_LEN, context->master_key, context->master_key_len, (unsigned char *)"server finished", 15, hash, 32, NULL, 0);
		tls_packet_append(packet, out, __TLS_MIN_FINISHED_OPAQUE_LEN);
		__private_tls_hmac_message(1, context, packet->buf,packet->len, NULL, 0,context->server_verify_data, 32, 0);
		
		packet->buf[3]=0x0; //len
		packet->buf[4]=0x50; 
		ecc_rng(packet->buf+5,16);
		tls_packet_uint8(packet, 0x14);  //type
		tls_packet_uint24(packet, __TLS_MIN_FINISHED_OPAQUE_LEN);
		tls_packet_append(packet, out, __TLS_MIN_FINISHED_OPAQUE_LEN);
		tls_packet_append(packet,context->server_verify_data,32);
	  //packet->len +=32;  //hmac_message
		//memcpy(context->server_verify_data, out, __TLS_MIN_FINISHED_OPAQUE_LEN);
		memcpy(context->public_key,context->server_verify_data,32);
		hash[0] = 16 - ((packet->len-5) % 16);
		memset(packet->buf+packet->len, hash[0] - 1, hash[0]);
		packet->len+=hash[0];
		//packet->len=CmEnAES128(context->serverkey,context->serveriv,context->serveriv,packet->buf+5,packet->len-5,packet->buf+5);
		packet->len=CmEnAES128(context->serverkey,0,0,packet->buf+5,packet->len-5,packet->buf+5);
	//	CmDeAES128(context->serverkey,context->serveriv,0,packet->buf+5,packet->len,context->server_verify_data);
		packet->len +=5;
		context->message_buffer_len += packet->len;
		context->local_sequence_number++;
    return packet;
}

int tls_parse_payload(struct TLSContext *context, unsigned char *buf, int buf_len, Hdlc_back_function *back_fun) 
{
	int payload_res = 0;
#if 0	
	if(buf_len==0x50 && buf[0]!=0x0f)
	{
		unsigned char hash[32];
		__private_tls_get_hash(context, hash);
		CmDeAES128(context->clientkey,context->clientiv,0,(uint8_t *)buf,buf_len,(uint8_t*)buf);
		__private_tls_prf(context, context->client_verify_data, __TLS_MIN_FINISHED_OPAQUE_LEN, context->master_key, context->master_key_len, (unsigned char *)"client finished", 15, hash, 32, NULL, 0);
		__private_tls_prf(context, sign_out+64, __TLS_MIN_FINISHED_OPAQUE_LEN, context->master_key, context->master_key_len, (unsigned char *)"server finished", 15, hash, 32, NULL, 0);
	//	memcpy(context->client_verify_data,hash,32);
		buf[11]=0x16;buf[12]=0x03;buf[13]=0x03;buf[14]=0;buf[15]=16;
		__private_tls_hmac_message(0,context,buf+11,__TLS_MIN_FINISHED_OPAQUE_LEN+4+5,0,0,context->client_verify_data+32,32,0);
		tls_build_change_cipher(context);
		tls_build_serverfinished(context);
		payload_res=context->message_buffer_len;
		return payload_res;
	}
#endif	
	while(buf_len>=4)
	{
		unsigned char type = buf[0];
		unsigned char update_hash;
		unsigned int payload_size = buf[1] * 0x10000 + buf[2] * 0x100 + buf[3] + 3;
		unsigned int write_packets = 0;
    unsigned int dtls_cookie_verified = 0;
		update_hash = 1;
		switch (type) {
			case 0x0: // hello request
					update_hash=0;
					context->crypto_created = 0;
					tls_build_hello(context);
					payload_res=context->message_buffer_len;
					return payload_res;
					break;
			case 0x01: //tls_hello
				payload_res = tls_parse_hello(context, buf + 1, payload_size, &write_packets, &dtls_cookie_verified);
				context->sha256_init=0;
				break;
			case 0x03:// hello verify request
				update_hash=0;
				break;
			case 0x0b: //tls_certificate
				break;
			case 0x10: //client_key change
				tls_parse_client_key_exchange(context,buf+1,payload_size);
				break;
			case 0x0f: //certificat verify
				break;
			case 0x14: //finished
				write_packets=1;
				break;
			default:
				break;
		}
		if ((type != 0x00) && (update_hash))
			__private_tls_update_hash(context,buf, payload_size + 1);
		switch (write_packets) {
			case 2:
				fnWDT_Restart();
				tls_build_hello(context);
				fnWDT_Restart();
				tls_build_certificate(context);
				//fnWDT_Restart();
				*back_fun = tls_back_fun;
			//	tls_back_fun();
				break;
			case 1:
				tls_build_change_cipher(context);
				tls_build_serverfinished(context);
				break;
			default:
				break;
		}
		payload_size++;
		buf += payload_size;
		write_packets=0;
		if(buf_len<=payload_size)
			break;
    buf_len -= payload_size;
	}
	payload_res=context->message_buffer_len;
	return payload_res;
}

int tls_parse_message(struct TLSContext *context, unsigned char *buf, int buf_len, Hdlc_back_function *back_fun)
{
	unsigned char type;
//	unsigned char *pt = 0;
	unsigned int padding;
	int buf_pos;
	unsigned char *ptr;
	int payload_res;
	unsigned int length,ppp;
	while(buf_len>6)
	{	
		buf_pos = 5;
		type = *buf;
		ptr = buf + 5;
		payload_res = 0;
		length = (buf[3]<<8)|buf[4];
		ppp=length;
		if(context->crypto_created || (TLS_APPLICATION_DATA==type))
		{
		//	unsigned char hash[32];
		//	__private_tls_get_hash(context, hash);
			//CmDeAES128(context->clientkey,context->clientiv,context->clientiv,(uint8_t *)ptr,length,(uint8_t*)ptr);
			CmDeAES128(context->clientkey,0,0,(uint8_t *)ptr,length,(uint8_t*)ptr);
			memcpy(ptr,ptr+16,length-16);
			length -=16;
			padding=ptr[length-1];
			length=length-padding-1;
			length-=32;
			buf[3]=(length>>8)&0xff;
			buf[4]=(length)&0xff;
			__private_tls_hmac_message(0, context, buf,length+5, NULL, 0,context->client_verify_data, 32, 0);
			if(memcmp(context->client_verify_data,ptr+length,32))
				return 0;
		//	__private_tls_prf(context, context->client_verify_data, __TLS_MIN_FINISHED_OPAQUE_LEN, context->master_key, context->master_key_len, (unsigned char *)"client finished", 15, hash, 32, NULL, 0);
	//	memcpy(context->client_verify_data,hash,32);
		//buf[11]=0x16;buf[12]=0x03;buf[13]=0x03;buf[14]=0;buf[15]=16;
		//__private_tls_hmac_message(0,context,buf+11,__TLS_MIN_FINISHED_OPAQUE_LEN+4+5,0,0,context->client_verify_data+32,32,0);
		//tls_build_change_cipher(context);
		//tls_build_serverfinished(context);
	//	payload_res=context->message_buffer_len;
	//	return payload_res;
		}
		context->remote_sequence_number++;
		switch (type) {
            // application data
        case TLS_APPLICATION_DATA:
						m_tlscontext.tls_sml=1;
						CmSet_SML_Recevie_Buf((uint8_t *)ptr,length);
						AnalyseSML(m_tlscontext.message_buffer+21);
						length=CmGet_SML_Send_Buf(m_tlscontext.message_buffer+21);
						m_tlscontext.tls_sml=0;
						if(length)
						{
							m_tlscontext.message_buffer[0]=0x17;
							m_tlscontext.message_buffer[1]=0x03;
							m_tlscontext.message_buffer[2]=0x03;
							m_tlscontext.message_buffer[16]=0x17;
							m_tlscontext.message_buffer[17]=0x03;
							m_tlscontext.message_buffer[18]=0x03;
							m_tlscontext.message_buffer[19]=(length>>8)&0xff;
							m_tlscontext.message_buffer[20]=length&0xff;
							__private_tls_hmac_message(1, context, m_tlscontext.message_buffer+16,length+5, NULL, 0,context->server_verify_data, 32, 0);
							ecc_rng(m_tlscontext.message_buffer+5,16);
							memcpy(m_tlscontext.message_buffer+21+length,context->server_verify_data,32);
							length +=48; //16random 32mac
							padding = 16 - ((length) % 16);
							memset(m_tlscontext.message_buffer+5+length, padding - 1, padding);
							length+=padding;
							//length=CmEnAES128(context->serverkey,context->serveriv,context->serveriv,m_tlscontext.message_buffer+5,length,m_tlscontext.message_buffer+5);
							length=CmEnAES128(context->serverkey,0,0,m_tlscontext.message_buffer+5,length,m_tlscontext.message_buffer+5);
							context->local_sequence_number++;
						}
						
						m_tlscontext.message_buffer[3]=(length>>8)&0xff;
						m_tlscontext.message_buffer[4]=length&0xff;
						m_tlscontext.message_buffer_len = length+5;
						break;
				case TLS_CHANGE_CIPHER:
					  context->crypto_created=1;
						context->remote_sequence_number=0;
					//	context->crypto_time = 120;
						break;
				case TLS_HANDSHAKE:
            payload_res = tls_parse_payload(context, ptr, length, back_fun);
            break;
				case TLS_ALERT:
						if(length>5)
						{
							//CmDeAES128(context->clientkey,context->clientiv,0,(uint8_t *)ptr,length,(uint8_t*)ptr);
							CmDeAES128(context->clientkey,0,0,(uint8_t *)ptr,length,(uint8_t*)ptr);
							m_tlscontext.message_buffer[0]=0x15;
							m_tlscontext.message_buffer[1]=0x03;
							m_tlscontext.message_buffer[2]=0x03;
							m_tlscontext.message_buffer[3]=0x00;
							m_tlscontext.message_buffer[4]=0x40;
							memcpy(m_tlscontext.message_buffer+5,ptr,length);
							//length=CmEnAES128(context->serverkey,context->serveriv,0,m_tlscontext.message_buffer+5,length,m_tlscontext.message_buffer+5);
							//length=CmEnAES128(context->serverkey,0,0,m_tlscontext.message_buffer+5,length,m_tlscontext.message_buffer+5);
							m_tlscontext.message_buffer[4]=length;
						//	m_tlscontext.message_buffer_len = length+5;
							//CmDeAES128(context->serverkey,context->serveriv,0,m_tlscontext.message_buffer+5,length,sign_out);
						}
						else
						{
							m_tlscontext.message_buffer[0]=0x15;
							m_tlscontext.message_buffer[1]=0x03;
							m_tlscontext.message_buffer[2]=0x03;
							m_tlscontext.message_buffer[3]=0x00;
							m_tlscontext.message_buffer[4]=0x02;
							m_tlscontext.message_buffer[5]=0x01;
							m_tlscontext.message_buffer[6]=0x00;
					//		m_tlscontext.message_buffer_len = 7;
						}
						break;
				default:
					break;
		}
		buf = ptr+ppp;
		buf_len -=(ppp+5);
	}
	return payload_res;
}
uint16_t  Cm_Tls_Analys(uint8_t *buf,uint16_t len,uint8_t *back,Hdlc_back_function *back_fun)
{
	uint16_t ret;
	m_tlscontext.message_buffer=back;
	m_tlscontext.message_buffer_len=0;
	tls_parse_message(&m_tlscontext,buf,len,back_fun);
	ret=m_tlscontext.message_buffer_len;
	return ret;
}

int16_t  Cm_Tls_En(uint8_t *buf,uint16_t len,uint8_t *back)
{
	int16_t ret;
	ret=CmEnAES128(Kenc,0,0,buf,len,back);
	return ret;
}

