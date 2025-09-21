#ifndef	__LIB_SM2__
#define __LIB_SM2__

//����������ص����ݽṹ���������㺯��
//#define LITTLE_ENDIAN
#define SM2_MAX_MESSAGE_LEN		128
#define ECC_BIGINT32_MAXLEN 	32
#define SM3_DIGEST_LEN			32
#define HASH_IN_SIZE	(ECC_BIGINT32_MAXLEN*2+4)
#define HASH_OUT_SIZE	SM2_MAX_MESSAGE_LEN

typedef unsigned char   UINT8;
typedef signed   char   SINT8;
typedef unsigned short  UINT16;
typedef signed   short  SINT16;
typedef unsigned int    UINT32;
typedef signed 	 int    SINT32;

typedef UINT32 BIG_INT;
typedef UINT16 BIG_HALF_DIGIT;

#if !defined(NULL)
#define NULL 0
#endif

//���������32λ����ṹ
//auValue����ĵ�32λ��ַ��Ŵ����ĵ�32λ��Ч������32λ��ַ��Ŵ����ĸ�32λ��Ч��
typedef struct
{                         //32λ�����ʵ�ʳ���
	UINT8 auValue[ECC_BIGINT32_MAXLEN]; //32λ�����ֵ
}ECC_STU_BIGINT32;

typedef struct
{
	UINT8 auValue[48];
}ECC_STU_BIGINT48;

//����ECC�����ĸ�ʽ
typedef struct
{
	UINT32 uField;
	UINT32 uBytes;                               // ģ��P���ֽ���
	ECC_STU_BIGINT32  stuPrimeP;				// ģ��P
	ECC_STU_BIGINT32  stuCoefficientA;			// ��Բϵ��A
	ECC_STU_BIGINT32  stuCoefficientB;			// ��Բϵ��B
	ECC_STU_BIGINT32  stuGx;				    // ��Բ��������Gx
	ECC_STU_BIGINT32  stuGy;				    // ��Բ��������Gy
	ECC_STU_BIGINT32  stuPrimeN;				// ��Բ��������G�Ľ�
	ECC_STU_BIGINT32  stuCoefficientH;			// ��Բϵ��H
} ECC_STU_PRAMS;


//����ECC��Կ�ĸ�ʽ
typedef struct
{
	ECC_STU_BIGINT32  stuQx;			        // ��Կ����Qx
	ECC_STU_BIGINT32  stuQy;				    // ��Կ����Qy
} ECC_STU_PUBKEY;

typedef struct
{
	ECC_STU_BIGINT32  stuQx;			        // ��Կ����Qx
	ECC_STU_BIGINT32  stuQy;				    // ��Կ����Qy
	ECC_STU_BIGINT32  stuQz;
}ECC_STU_JACOBIAN;

//void SM2Init(ECC_STU_PRAMS *pstuEccPrams);
UINT8  EccGenerateKeyPair(ECC_STU_PRAMS *pstuEccPrams,
		ECC_STU_BIGINT32 *pstuPrivKey,
		ECC_STU_PUBKEY *pstuPubKey);
void SM2Encrypt(UINT8 *mes,
		UINT16 klen,
		ECC_STU_PUBKEY *pstuPubKey,
		ECC_STU_PRAMS *pstuEccPrams,
		UINT8 *cipher0,
		UINT8 *cipher1,
		UINT8 *cipher2);
UINT8 SM2Decrypt(UINT8 *cipher0,
		UINT8 *cipher1,
		UINT8 *cipher2,
		UINT16 klen,
		ECC_STU_BIGINT32 *stuPrivKey,
		ECC_STU_PRAMS *pstuEccPrams,
		UINT8 *mes);
void EccSignature(UINT8 *mes,
		UINT16 klen,
		ECC_STU_PRAMS *pstuEccPrams,
		ECC_STU_BIGINT32 *pstuPrivKey,
		ECC_STU_BIGINT32 *pSignatureR,
		ECC_STU_BIGINT32 *pSignatureS);
UINT8 EccVerification(UINT8 *mes,
		UINT16 klen,
		ECC_STU_PRAMS *pstuEccPrams,
		ECC_STU_PUBKEY *pstuPubKey,
		ECC_STU_BIGINT32 *pSignatureR,
		ECC_STU_BIGINT32 *pSignatureS);
void SM2SignatureWithIDA(UINT8 *mes,
		UINT16 klen,
		UINT8 *IDA,
		UINT16 entla,
		ECC_STU_PRAMS *pstuEccPrams,
		ECC_STU_PUBKEY *pstuPubKey,
		ECC_STU_BIGINT32 *pstuPrivKey,
		ECC_STU_BIGINT32 *pSignatureR,
		ECC_STU_BIGINT32 *pSignatureS);
UINT8 SM2VerificationWithIDA(UINT8 *mes,
		UINT16 klen,
		UINT8 *IDA,
		UINT16 entla,
		ECC_STU_PRAMS *pstuEccPrams,
		ECC_STU_PUBKEY *pstuPubKey,
		ECC_STU_BIGINT32 *pSignatureR,
		ECC_STU_BIGINT32 *pSignatureS);

UINT8 SM2_KeyExchange_HT(ECC_STU_PRAMS *pstuEccPrams,  // ECC������
                       ECC_STU_BIGINT32 *pSelfPrikey,   // ����˽Կ
                       ECC_STU_PUBKEY *pSelfTempPubkey, // ������ʱ��Կ��
                       ECC_STU_BIGINT32 *pSelfTempPrikey,   // ������ʱ˽Կ��
                       ECC_STU_PUBKEY *pOtherPubkey,      // �Է���Կ
                       ECC_STU_PUBKEY *pOtherTempPubkey,  // �Է���ʱ��Կ��
                       UINT32 *za,            // ����Zֵ
                       UINT32 *zb,           // �Է�Zֵ
                       UINT32 *pAgreedKey,        // Э����Կ��
                    UINT32 AgreedKeyLen,       // Э����Կ����
                    UINT32 *sA,               // SA����S2����
                    UINT32 *sB,               // SB����S1����
                       UINT32 Mode);              // 0��ʾ����ΪA����1��ʾ����ΪB��

int SM2Init(ECC_STU_PRAMS *pstuEccPrams);

int  EccGenerateKeyPairDpa(ECC_STU_PRAMS *pstuEccPrams,
		ECC_STU_BIGINT32 *pstuPrivKey,
		ECC_STU_PUBKEY *pstuPubKey);

int SM2EncryptDpa(UINT8 *mes,
		UINT16 klen,
		ECC_STU_PUBKEY *pstuPubKey,
		ECC_STU_PRAMS *pstuEccPrams,
		UINT8 *cipher0,
		UINT8 *cipher1,
		UINT8 *cipher2);

int SM2DecryptDpa(UINT8 *cipher0,
		UINT8 *cipher1,
		UINT8 *cipher2,
		UINT16 klen,
		ECC_STU_BIGINT32 *stuPrivKey,
		ECC_STU_PRAMS *pstuEccPrams,
		UINT8 *mes);

int EccSignatureDpa(UINT8 *mes,
		UINT16 klen,
		ECC_STU_PRAMS *pstuEccPrams,
		ECC_STU_BIGINT32 *pstuPrivKey,
		ECC_STU_BIGINT32 *pSignatureR,
		ECC_STU_BIGINT32 *pSignatureS);

int EccVerificationDpa(UINT8 *mes,
		UINT16 klen,
		ECC_STU_PRAMS *pstuEccPrams,
		ECC_STU_PUBKEY *pstuPubKey,
		ECC_STU_BIGINT32 *pSignatureR,
		ECC_STU_BIGINT32 *pSignatureS);

int SM2SignatureWithIDADpa(UINT8 *mes,
		UINT16 klen,
		UINT8 *IDA,
		UINT16 entla,
		ECC_STU_PRAMS *pstuEccPrams,
		ECC_STU_PUBKEY *pstuPubKey,
		ECC_STU_BIGINT32 *pstuPrivKey,
		ECC_STU_BIGINT32 *pSignatureR,
		ECC_STU_BIGINT32 *pSignatureS);
int SM2VerificationWithIDADpa(UINT8 *mes,
		UINT16 klen,
		UINT8 *IDA,
		UINT16 entla,
		ECC_STU_PRAMS *pstuEccPrams,
		ECC_STU_PUBKEY *pstuPubKey,
		ECC_STU_BIGINT32 *pSignatureR,
		ECC_STU_BIGINT32 *pSignatureS);

int SM2KeyExchangeDpa(ECC_STU_PRAMS *pstuEccPrams,  // ECC������
                       ECC_STU_BIGINT32 *pSelfPrikey,   // ����˽Կ
                       ECC_STU_PUBKEY *pSelfTempPubkey, // ������ʱ��Կ��
                       ECC_STU_BIGINT32 *pSelfTempPrikey,   // ������ʱ˽Կ��
                       ECC_STU_PUBKEY *pOtherPubkey,      // �Է���Կ
                       ECC_STU_PUBKEY *pOtherTempPubkey,  // �Է���ʱ��Կ��
                       UINT32 *za,            // ����Zֵ
                       UINT32 *zb,           // �Է�Zֵ
                       UINT32 *pAgreedKey,        // Э����Կ��
                    UINT32 AgreedKeyLen,       // Э����Կ����
                    UINT32 *sA,               // SA����S2����
                    UINT32 *sB,               // SB����S1����
                       UINT32 Mode);              // 0��ʾ����ΪA����1��ʾ����ΪB��



#define JR0_BASE	(0xeb500000+0x1000)
#define JR0_IRBARH   (JR0_BASE+0x00)
#define JR0_IRBARL   (JR0_BASE+0x04)
#define JR0_IRSR     (JR0_BASE+0x0C)
#define JR0_IRSAR    (JR0_BASE+0x14)
#define JR0_IRJAR    (JR0_BASE+0x1C)
#define JR0_ORBARH   (JR0_BASE+0x20)
#define JR0_ORBARL   (JR0_BASE+0x24)
#define JR0_ORSR     (JR0_BASE+0x2C)
#define JR0_ORJRR    (JR0_BASE+0x34)
#define JR0_ORSFR    (JR0_BASE+0x3C)
#define JR0_JRSTAR   (JR0_BASE+0x44)
#define JR0_JRINTR   (JR0_BASE+0x4C)
#define JR0_JRCFGRH  (JR0_BASE+0x50)
#define JR0_JRCFGRL  (JR0_BASE+0x54)
#define JR0_IRRIR    (JR0_BASE+0x5C)
#define JR0_ORWIR    (JR0_BASE+0x64)
#define JR0_JRCR     (JR0_BASE+0x6C)

#define AXIRAM_UPADDR	(0x00000004)
#define AXIRAM_LADDR	(0xe00c0000)

#endif






