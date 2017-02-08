#include <stdint.h>
#include <Drive_Lib.h>
#include "aes.h"
#include "tls.h"
#include "tlse.h"
#include "types.h"
#include "uECC.h"
#include "typeE2p.h"
#include "sym.h"
#include "mbedtls/sha512.h"
#include "mbedtls/sha256.h"

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
	nshort=hostshort&0xff;
	nshort=(nshort<<8)+((hostshort>>8)&0xff);
	return nshort;
}
#define ntohl htonl
#define ntohs htons
#ifndef htonll
#define htonll(x) ((1==ntohl(1)) ? (x) : ((uint64_t)ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32))
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
		unsigned char session_size;
		unsigned char *message_buffer;
		unsigned int message_buffer_len;
		unsigned char priv[32];
		unsigned char  ecc_priv[48];
};

struct TLSPacket {
    unsigned char *buf;
    unsigned int len;
    unsigned int size;
    unsigned char broken;
    struct TLSContext *context;
};

static struct TLSContext m_tlscontext;
const struct uECC_Curve_t * p_curve;
#if 1
uint8_t hash_test_buff[64];
uint8_t ecsda_test[64]={0xE3,0xD7,0x16,0x5E,0x9B,0x17,0xA0,0x28,0xD7,0x7E,
												0xD0,0xFC,0x3B,0x6F,0x14,0x24,0x11,0x43,0x6B,0xAC,
												0x4C,0xA6,0xC2,0x4E,0xCA,0xD6,0xBC,0x12,0x50,0xE2,
												0x58,0x8F,
												0x9D,0xB3,0xDE,0x7C,0xAF,0x61,0x44,0xA3,0xAD,0x4A, 
												0xA6,0x33,0xBD,0x6E,0x48,0x46,0x9D,0x2A,0xD3,0x55, 
												0xDF,0xA0,0x6F,0x07,0xEE,0x10,0xD1,0x0A,0x9A,0xF9, 
												0x10,0x7F};
uint8_t compress_test[64]={0x02,0xFD,0xC9,0x1E,0xA7,0x46,0x75,0x8D,0x07,0x76,
														0x09,0x7C,0x49,0xE4,0x6D,0xDA,0x95,0x74,0xB9,0x3D, 
														0x03,0xF2,0x16,0xC3,0x13,0x18,0xB3,0x91,0x64,0x11, 
														0x5F,0xC5,0xD0};
uint8_t cl_random[32]={0x53,0x4D,0xD8,0x08,0xC6,0x8D,0x71,0x63,0x33,0xF0,0xAF,0x8B,0x4C,0xE2,0x47,0x29, 
												0x74,0xB5,0x83,0xAB,0x58,0xEC,0x41,0xA7,0x14,0x9A,0xF1,0xD5,0xE0,0x15,0x7A,0xDA};
uint8_t srv_random[32]={0x52,0x80,0xE2,0xF3,0xA2,0xA8,0xB1,0x41,0xB7,0xC0,0x15,0xD2,0x9A,0xDB,0x82,0xD7, 
												0x61,0x14,0xFC,0x0F,0xC2,0xB9,0xC0,0xDD,0x15,0xEE,0xA6,0x8D,0x9E,0x72,0xB7,0x38};
#if 1
uint8_t decompress_test[64]={	
	0xC7,0xF3,0x38,0xC3,0x7B,0xC4,0x47,0xAB,0x8A,0x7E,0xEE,0xF0,0xFE,0x07, 
														0x68,0x7F,0x7F,0x91,0x64,0xFC,0x08,0x3C,0x69,0xD9,0x26,0xB6,0x07,0x64,0x21,0xEF, 
														0x16,0x0B,0x8D,0xC7,0x1B,0xEB,0x19,0xB9,0xEF,0xC4,0xA8,0x74,0x26,0xA9,0xE8,0xDA, 
														0x4C,0xA3,0x69,0x30,0xEC,0xD9,0x9A,0xEB,0x8D,0xB8,0x72,0x03,0x35,0x53,0x3B,0x4A, 
														0x7E,0xEC
};
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
//uint8_t tmp[64 + 64 + 128];
uint8_t sign_out[64];
int tls_Init(void)
{
	unsigned char *privateK;
 // uECC_word_t publicK[8 * 2];
   /*unsigned char b_pri[32]={0x70,0xa1,0x2c,0x2d,0xb1,0x68,0x45,0xed,0x56,0xff,0x68,0xcf,0xc2,0x1a,0x47,0x2b,
														 0x3f,0x04,0xd7,0xd6,0x85,0x1b,0xf6,0x34,0x9f,0x2d,0x7d,0x5b,0x34,0x52,0xb3,0x8a};*/
	// SHA512_HashContext ctx;
//	SHA256_HashContext ctx;
	 unsigned char b_pri[32]={0x9D,0xEB,0xC6,0xDE,0x97,0x57,0xDE,0x9D,0x99,0x4E,0x45,0xFC,0xD8,0x5D,0x47,0x62,
0xB0,0x28,0xFC,0x24,0x0D,0x14,0xA5,0xA0,0x2A,0x35,0x00,0x6E,0x59,0xDC,0xFD,0x07};
		uint8_t publicK[64];
		uint8_t *b_lmn_cert;
		b_lmn_cert=Get_LMN_Cert();

		uECC_set_rng(ecc_rng);
		p_curve = uECC_secp256r1();
		
#if 1		
	//	Cm_Ram_Inter(cl_random,32);	
	//	Cm_Ram_Inter(srv_random,32);	
#if 1
		memcpy(b_lmn_cert,cl_random,32);
		memcpy(b_lmn_cert+32,srv_random,32);
		b_lmn_cert[64]=0x03;
		b_lmn_cert[65]=0x00;b_lmn_cert[66]=0x17;
		b_lmn_cert[67]=0x21;
    memcpy(b_lmn_cert+68,compress_test,33);

		fnWDT_Restart();
		//Cm_Ram_Inter(b_lmn_cert,101);
		mbedtls_sha512(b_lmn_cert,101,hash_test_buff,0);	
#else
		b_lmn_cert[0]=0x03;
		b_lmn_cert[1]=0x00;b_lmn_cert[2]=0x17;
		b_lmn_cert[3]=0x21;
    memcpy(b_lmn_cert+4,compress_test,33);

		fnWDT_Restart();
		//Cm_Ram_Inter(b_lmn_cert,101);
		mbedtls_sha512(b_lmn_cert,37,hash_test_buff,0);
#endif
		Cm_Ram_Inter(ecsda_test,32);
		Cm_Ram_Inter(ecsda_test+32,32);
		
#if 0
		//private verify
		Cm_Ram_Inter(b_pri,32);
		memcpy(m_tlscontext.ecc_priv,b_pri,32);
		uECC_compute_public_key(b_pri,(uint8_t *)publicK,p_curve);
		uECC_sign(b_pri,hash_test_buff,64,ecsda_test,p_curve);
		//private verify end
#endif		
		//public verify
		Cm_Ram_Inter(compress_test+1,32);
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
		
		uECC_verify(decompress_test,hash_test_buff,32,ecsda_test,p_curve);	
		fnWDT_Restart();
		uECC_verify(publicK,hash_test_buff,32,ecsda_test,p_curve);	
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
		if (1 == uECC_make_key((unsigned char *)publicK,(unsigned char *)privateK,p_curve))
		{
		}
		fnWDT_Restart();
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
  unsigned char publicK[64];
	//struct uECC_HashContext m_hash_context;
	unsigned char *buf;
	
 // SHA512_HashContext ctx;
//	SHA256_HashContext ctx;
    
	privateK = context->priv;
	
	uECC_compute_public_key(privateK,publicK,p_curve);

	packet.buf = context->message_buffer+context->message_buffer_len;
	buf = packet.buf+256;
	
	packet.len=packet.size=0;
	tls_head(&packet);
	tls_packet_uint16(&packet, 0x75);
	tls_packet_uint8(&packet, 0x0C);
	tls_packet_uint24(&packet, 0x71);
	tls_packet_uint8(&packet, 0x03);
	tls_packet_uint16(&packet,0x17);//ecc256r1
	tls_packet_uint8(&packet,0x21);  //not product
	fnWDT_Restart();
	uECC_compress(publicK,packet.buf+packet.len,p_curve);
	fnWDT_Restart();
	Cm_Ram_Inter(packet.buf+packet.len+1,32);
	packet.len +=0x21;
	memcpy(buf,context->remote_random,__TLS_CLIENT_RANDOM_SIZE);
//	Cm_Ram_Inter(buf,32);
	memcpy(buf+__TLS_CLIENT_RANDOM_SIZE,context->local_random, __TLS_SERVER_RANDOM_SIZE);
	//Cm_Ram_Inter(buf+32,32);
	memcpy(buf+__TLS_CLIENT_RANDOM_SIZE+__TLS_SERVER_RANDOM_SIZE, packet.buf + 9, packet.len-9);
#if 0
#if   0 //def _USE_SHA_512
	ctx.uECC.init_hash = init_SHA512;
	ctx.uECC.update_hash = update_SHA512;
	ctx.uECC.finish_hash = finish_SHA512;
	ctx.uECC.block_size = 128;
	ctx.uECC.result_size = 64;
#else
	ctx.uECC.init_hash = init_SHA256;
	ctx.uECC.update_hash = update_SHA256;
	ctx.uECC.finish_hash = finish_SHA256;
	ctx.uECC.block_size = 64;
	ctx.uECC.result_size = 32;
#endif
	ctx.uECC.tmp = tmp;
	fnWDT_Restart();
	uECC_sign_deterministic(context->ecc_priv, buf,__TLS_CLIENT_RANDOM_SIZE+__TLS_CLIENT_RANDOM_SIZE+packet.len-9,&ctx.uECC, sign_out,p_curve);
	fnWDT_Restart();
	//Cm_Ram_Inter(sign_out,32);
	//Cm_Ram_Inter(sign_out+32,32);
	
	//uECC_sign_deterministic(privateK, buf,__TLS_CLIENT_RANDOM_SIZE+__TLS_CLIENT_RANDOM_SIZE+packet.len-9,&ctx.uECC, packet.buf+packet.len+4,p_curve);
	//uECC_sign(privateK,buf,__TLS_CLIENT_RANDOM_SIZE+__TLS_CLIENT_RANDOM_SIZE+packet.len-9,packet.buf+packet.len+4,p_curve);
	//mbedtls_sha512( buf, __TLS_CLIENT_RANDOM_SIZE+__TLS_CLIENT_RANDOM_SIZE+packet.len-9, packet.buf+packet.len+4, 0 );
#endif
		fnWDT_Restart();
		mbedtls_sha512(buf,__TLS_CLIENT_RANDOM_SIZE+__TLS_CLIENT_RANDOM_SIZE+packet.len-9,publicK,0);	
	//	Cm_Ram_Inter(publicK,64);
		fnWDT_Restart();
		uECC_sign(context->ecc_priv,publicK,64,sign_out,p_curve);
		//uECC_sign(privateK,publicK,64,sign_out,p_curve);
		fnWDT_Restart();
		tls_packet_uint8(&packet,sha512);
	//tls_packet_uint8(&packet,sha256);
	tls_packet_uint8(&packet,ecdsa);
	tls_packet_uint16(&packet,0x48);//ecdsa len
	tls_packet_uint16(&packet,0x3046);
	tls_packet_uint16(&packet,0x0221);
	tls_packet_uint8(&packet,0x00);
	//Cm_Ram_Inter(sign_out,32);
	tls_packet_append(&packet,sign_out, 32);
	tls_packet_uint16(&packet,0x0221);
	tls_packet_uint8(&packet,0x00);
	//Cm_Ram_Inter(sign_out+32,32);
	tls_packet_append(&packet,sign_out+32, 32);
	context->message_buffer_len += packet.len;
	return &packet;
}

struct TLSPacket *tls_certificate_request(struct TLSContext *context) 
{
	struct TLSPacket packet;
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
	tls_packet_uint16(&packet, 0x4a);
	tls_packet_uint16(&packet, 0x48);
#if 0	
	E2P_RData(packet.buf+packet.len,E2P_SMGW_Certi+140,0x48);
	packet.len=packet.size=packet.len+0x48;
#else	
	smgw_cert = Get_SMGW_Cert();
	tls_packet_append(&packet,smgw_cert+140,0x48);
#endif	
	context->message_buffer_len += packet.len;
	return &packet;
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
		context->message_buffer_len += packet->len;
    return packet;
}

int16_t tls_back_fun(void)
{
	m_tlscontext.message_buffer_len=0;
	fnWDT_Restart();
	tls_build_server_key_exchange(&m_tlscontext,1);
	fnWDT_Restart();
	tls_certificate_request(&m_tlscontext);
	fnWDT_Restart();
	tls_build_done(&m_tlscontext);
	fnWDT_Restart();
	return m_tlscontext.message_buffer_len;
}

struct TLSPacket *tls_build_hello(struct TLSContext *context) 
{
	struct TLSPacket *packet;
	unsigned char dummy[3];
	unsigned char *privateK;
 // unsigned char publicK[64];
	
	struct TLSPacket s_packet;
	
	packet=&s_packet;
	
	privateK = context->priv;
	
	//uECC_compute_public_key(privateK,publicK,p_curve);
	//memcpy(context->local_random,publicK,__TLS_SERVER_RANDOM_SIZE);
///	memcpy(context->session,publicK+32,__TLS_MAX_SESSION_ID);
	ecc_rng(context->local_random,32);
	ecc_rng(context->session,32);
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
		context->message_buffer_len = packet->len;
		return packet;
}
struct TLSPacket *tls_build_certificate(struct TLSContext *context) 
{
	struct TLSPacket *packet;
	int rd_len,rd_ptr;
	int rd_length;
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
	for(rd_ptr=0,rd_len=0x197;rd_ptr<30;++rd_ptr)
	{
		if(b_lmn_cert[rd_ptr]==0x82)
		{
			rd_len=(b_lmn_cert[rd_ptr+1]<<8)|b_lmn_cert[rd_ptr+2];
			rd_len +=4;
			break;
		}
	}
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
	if(rd_ptr>0)
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
	context->message_buffer_len +=packet->len;
	return packet;
}
int tls_parse_payload(struct TLSContext *context, const unsigned char *buf, int buf_len, Hdlc_back_function *back_fun) 
{
	int payload_res = 0;
	while(buf_len>=4)
	{
		unsigned char type = buf[0];
		unsigned int payload_size = buf[1] * 0x10000 + buf[2] * 0x100 + buf[3] + 3;
		unsigned int write_packets = 0;
    unsigned int dtls_cookie_verified = 0;
		switch (type) {
			case 0x01:
				payload_res = tls_parse_hello(context, buf + 1, payload_size, &write_packets, &dtls_cookie_verified);
				break;
			case 0x0b:
				break;
		}
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
		}
		payload_size++;
		buf += payload_size;
    buf_len -= payload_size;
		write_packets=0;
	}
	payload_res=context->message_buffer_len;
	return payload_res;
}

int tls_parse_message(struct TLSContext *context, unsigned char *buf, int buf_len, Hdlc_back_function *back_fun)
{
	unsigned char type = *buf;
//	unsigned char *pt = 0;
	int buf_pos = 5;
	const unsigned char *ptr = buf + buf_pos;
	int payload_res = 0;
	unsigned int length = (buf[3]<<8)|buf[4];//ntohs(*(unsigned short *)(buf+3));
	switch (type) {
            // application data
        case TLS_APPLICATION_DATA:
						break;
				case TLS_CHANGE_CIPHER:
						break;
				case TLS_HANDSHAKE:
            payload_res = tls_parse_payload(context, ptr, length, back_fun);
            break;
	}
	return payload_res;
}
int16_t  Cm_Tls_Analys(uint8_t *buf,uint16_t len,uint8_t *back,Hdlc_back_function *back_fun)
{
	int16_t ret;
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

