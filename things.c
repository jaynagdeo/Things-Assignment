#include<stdio.h>
#include<stdlib.h>
// #include "mbedtls/aes.h"

// mbedtls_aes_context aes;
//
// unsigned char key[32];
// unsigned char iv[16];
//
// unsigned char input [128];
// unsigned char output[128];
//
// size_t input_len = 40;
// size_t output_len = 0;


// mbedtls_aes_setkey_enc( &aes, key, 256 );
// mbedtls_aes_crypt_cbc( &aes, MBEDTLS_AES_ENCRYPT, 24, iv, input, output );

int main(int argc, unsigned char const *argv[]) {
  /* code */
char *p;
unsigned int i=0;
// char s= 0x01;
// printf("%d\n", argv[1]);
unsigned long int JoinNonce=0; // 3 chars
unsigned long int JoinEUI=0;  // 8 chars
unsigned long int DevNonce=0; // 2 chars
unsigned char iv[16];
unsigned char *tempJoinNonce;
unsigned char *tempJoinEUI;
unsigned char *tempDevNonce;
tempJoinNonce=&JoinNonce;
tempJoinEUI=&JoinEUI;
tempDevNonce=&DevNonce;
//*iv=argv[1];
//char *p;
//p=*argv[1];
// char const *i[] = 0102030405060708;
 //long int JoinEUI = atol(argv[1]);
//unsigned char *JoinEUI=argv[1];
JoinNonce=strtoul(argv[2], &p, 16);
JoinEUI=strtoul(argv[3], &p, 16);
DevNonce=strtoul(argv[4], &p, 16);


for (i=0;i<3;i++)
  {
    iv[i]=*(tempJoinNonce+i);
    printf("%x\n", iv[i]);
  }

  for (i=0;i<8;i++)
    {
      iv[i+3]=*(tempJoinEUI+i);
      printf("%x\n", iv[i+3]);
    }

    for (i=0;i<2;i++)
      {
        iv[i+3+8]=*(tempDevNonce+i);
        printf("%x\n", iv[i+3+8]);
      }

//  printf("%x\n", *(tempJoinNonce+1));



}
