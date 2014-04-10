#include <wmmintrin.h> 
 
inline __m128i AES_128_ASSIST (__m128i temp1, __m128i temp2) 
 { 
 __m128i temp3; 
 temp2 = _mm_shuffle_epi32 (temp2 ,0xff); 
 temp3 = _mm_slli_si128 (temp1, 0x4); 
 temp1 = _mm_xor_si128 (temp1, temp3); 
 temp3 = _mm_slli_si128 (temp3, 0x4); 
 temp1 = _mm_xor_si128 (temp1, temp3); 
 temp3 = _mm_slli_si128 (temp3, 0x4); 
 temp1 = _mm_xor_si128 (temp1, temp3); 
 temp1 = _mm_xor_si128 (temp1, temp2); 
 return temp1; 
 } 
 
void AES_128_Key_Expansion (const unsigned char *userkey, 
 unsigned char *key) 
 { 
 __m128i temp1, temp2; 
 __m128i *Key_Schedule = (__m128i*)key; 
 
 temp1 = _mm_loadu_si128((__m128i*)userkey); 
 Key_Schedule[0] = temp1; 
 temp2 = _mm_aeskeygenassist_si128 (temp1 ,0x1); 
 temp1 = AES_128_ASSIST(temp1, temp2); 
 Key_Schedule[1] = temp1; 
 temp2 = _mm_aeskeygenassist_si128 (temp1,0x2); 
 temp1 = AES_128_ASSIST(temp1, temp2); 
 Key_Schedule[2] = temp1; 
 temp2 = _mm_aeskeygenassist_si128 (temp1,0x4); 
 temp1 = AES_128_ASSIST(temp1, temp2); 
 Key_Schedule[3] = temp1; 
 temp2 = _mm_aeskeygenassist_si128 (temp1,0x8); 
 temp1 = AES_128_ASSIST(temp1, temp2); 
 Key_Schedule[4] = temp1; 
 temp2 = _mm_aeskeygenassist_si128 (temp1,0x10); 
 temp1 = AES_128_ASSIST(temp1, temp2); 
 Key_Schedule[5] = temp1;
 temp2 = _mm_aeskeygenassist_si128 (temp1,0x20); 
 temp1 = AES_128_ASSIST(temp1, temp2); 
 Key_Schedule[6] = temp1; 
 temp2 = _mm_aeskeygenassist_si128 (temp1,0x40); 
 temp1 = AES_128_ASSIST(temp1, temp2); 
 Key_Schedule[7] = temp1; 
 temp2 = _mm_aeskeygenassist_si128 (temp1,0x80); 
 temp1 = AES_128_ASSIST(temp1, temp2); 
 Key_Schedule[8] = temp1; 
 temp2 = _mm_aeskeygenassist_si128 (temp1,0x1b); 
 temp1 = AES_128_ASSIST(temp1, temp2); 
 Key_Schedule[9] = temp1; 
 temp2 = _mm_aeskeygenassist_si128 (temp1,0x36); 
 temp1 = AES_128_ASSIST(temp1, temp2); 
 Key_Schedule[10] = temp1; 
 } 

/* Note – the length of the output buffer is assumed to be a multiple of 16 bytes */ 
 
void AES_ECB_encrypt(const unsigned char *in, //pointer to the PLAINTEXT 
 unsigned char *out, //pointer to the CIPHERTEXT buffer 
 unsigned long length, //text length in bytes 
 const char *key, //pointer to the expanded key schedule 
 int number_of_rounds) //number of AES rounds 10,12 or 14 
 { 
 __m128i tmp; 
 int i,j; 
 
 if(length%16) 
 length = length/16+1; 
 else 
 length = length/16; 
 
 for(i=0; i < length; i++){ 
 tmp = _mm_loadu_si128 (&((__m128i*)in)[i]); 
 tmp = _mm_xor_si128 (tmp,((__m128i*)key)[0]); 
 for(j=1; j <number_of_rounds; j++){ 
 tmp = _mm_aesenc_si128 (tmp,((__m128i*)key)[j]); 
 } 
 tmp = _mm_aesenclast_si128 (tmp,((__m128i*)key)[j]); 
 _mm_storeu_si128 (&((__m128i*)out)[i],tmp); 
 } 
 } 
 
void AES_ECB_decrypt(const unsigned char *in, //pointer to the CIPHERTEXT 
 unsigned char *out, //pointer to the DECRYPTED TEXT buffer 
 unsigned long length, //text length in bytes 
 const char *key, //pointer to the expanded key schedule 
 int number_of_rounds) //number of AES rounds 10,12 or 14 
 { 
 __m128i tmp; 
 int i,j; 
 
 if(length%16) 
 length = length/16+1; 
 else 
 length = length/16; 
 
 for(i=0; i < length; i++){ 
 tmp = _mm_loadu_si128 (&((__m128i*)in)[i]); 
 tmp = _mm_xor_si128 (tmp,((__m128i*)key)[0]); 
 for(j=1; j <number_of_rounds; j++){ 
 tmp = _mm_aesdec_si128 (tmp,((__m128i*)key)[j]); 
 } 
 tmp = _mm_aesdeclast_si128 (tmp,((__m128i*)key)[j]); 
 _mm_storeu_si128 (&((__m128i*)out)[i],tmp); 
 } 
 } 



int Check_CPU_support_AES() 
 { 
 unsigned int a,b,c,d; 
_asm
 {
    mov eax,0x01
    cpuid
    mov a,eax
    mov b,ebx
    mov c,ecx
    mov d,edx
  }
 return (c & 0x2000000); 
 } 

void aes_test() {
if (Check_CPU_support_AES()==0)
  return ;
  //ECB
  unsigned char buf[16];
  unsigned char buf2[16];

  unsigned char userkey[16] = { 0xAF,0xAF,0xF0,0xBF,0x44,0xAF,0x55,0x34,0xA5,0xD3,0xAF,0x00,0x90,0x5F,0x48,0xAF, };
  unsigned char key[10][16];
  AES_128_Key_Expansion(userkey,key[0]);
  AES_ECB_encrypt((const unsigned char*)"ABCDEFGHIJKLMNOP",buf,16,(const char*)key[0],10);
  AES_ECB_decrypt(buf,buf2,16,(const char*)key[0],10);
}