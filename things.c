#include<stdio.h>
#include<stdlib.h>
//#include "aes.h"

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
  unsigned int i=0,ret=0, mode=0,n;
  // char s= 0x01;
  // printf("%d\n", argv[1]);
  unsigned long int NwkKey=0;

  unsigned long int NwkKey1=0;
  unsigned long int NwkKey2=0;
  // 0x01 // 1 chars
  unsigned long int JoinNonce=0; // 3 chars
  unsigned long int JoinEUI=0;  // 8 chars
  unsigned long int DevNonce=0; // 2 chars
  unsigned char iv[16];
  unsigned char *tempNwkKey;
  unsigned char *tempNwkKey1;
  unsigned char *tempNwkKey2;
  unsigned char *tempJoinNonce;
  unsigned char *tempJoinEUI;
  unsigned char *tempDevNonce;
  tempNwkKey=&NwkKey;
  tempNwkKey1=&NwkKey1;
  tempNwkKey2=&NwkKey2;
  tempJoinNonce=&JoinNonce;
  tempJoinEUI=&JoinEUI;
  tempDevNonce=&DevNonce;


//  mbedtls_aes_context aes;


  unsigned char longkey[32];
  unsigned char longkey1[16];
  unsigned char longkey2[16];
  unsigned char key[16];
  //unsigned char iv[16];
  unsigned char * lk1 = malloc(3 * sizeof(char));
  unsigned char * lk2 = malloc(3 * sizeof(char));

  unsigned char input [16];
  unsigned char output[16];


  // memset( longkey,    0, sizeof( longkey ) );
  // memset( longkey1,    0, sizeof( longkey1 ) );
  // memset( longkey2,    0, sizeof( longkey2 ) );

  // size_t input_len = 40;
  // size_t output_len = 0;
  //*iv=argv[1];
  //char *p;
  //p=*argv[1];
  // char const *i[] = 0102030405060708;
   //long int JoinEUI = atol(argv[1]);
  //unsigned char *JoinEUI=argv[1];
  NwkKey=strtoul(argv[1], &p, 16);
  JoinNonce=strtoul(argv[2], &p, 16);
  JoinEUI=strtoul(argv[3], &p, 16);
  DevNonce=strtoul(argv[4], &p, 16);

  //  printf("%lu\n", JoinEUI);

  memcpy( longkey, argv[1], 32 );

  printf("Longkey is: %s\n", longkey);

  memcpy( lk1, longkey, 16 );
  memcpy( lk2, (longkey+16), 16 );

  // for (i = 0; i < 16; i++) {
  //   /* code */
  //   longkey2[i]=longkey[i+16];
  // }

  printf("Longkey1 is: %s\n", lk1);
  printf("Longkey2 is: %s\n", lk2);
  //
  NwkKey1=strtoul(lk1, &p, 16);
  NwkKey2=strtoul(lk2, &p, 16);
  //
   printf("NwkKey1 : %x\n", NwkKey1);
   printf("NwkKey2 : %x\n", NwkKey2);






    //printf("%x\n", NwkKey);

  for (i=0;i<8;i++)
    {
      key[7-i]=*(tempNwkKey1+i);
      key[15-i]=*(tempNwkKey2+i);
    }
  printf("\n\n");
    for (i=0;i<16;i++)
      {
        printf("%x", key[i]);
      }
  printf("\n\n");



    // for (i=0;i<16;i++)
    //   {
    //     key[i]=*(tempNwkKey+i);
    //     printf("%c", key[i]);
    //   }
    //   printf("\n");
    input[0]=0x01;
  //
  for (i=0;i<3;i++)
    {
      input[3-i]=*(tempJoinNonce+i);
      //printf("%x", input[i]);
    }

    for (i=0;i<8;i++)
      {
        input[11-i]=*(tempJoinEUI+i);
      //  printf("%x\n", iv[i+3+1]);
      }
  //
      for (i=0;i<2;i++)
        {
          input[13-i]=*(tempDevNonce+i);
          //printf("%x\n", iv[i+3+8]);
        }
  input[14]=0;
  input[15]=0;   // zero padding

  printf("\n\n");
    for (i=0;i<16;i++)
      {
        printf("%x", input[i]);
      }
  printf("\n\n");

// int mbedtls_aes_crypt_ecb( mbedtls_aes_context *ctx,
//                     int mode,
//                     const unsigned char input[16],
//                     unsigned char output[16] );

}
