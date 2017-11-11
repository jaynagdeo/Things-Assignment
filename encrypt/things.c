#include<stdio.h>
#include<stdlib.h>
#include "mbedtls/config.h"
#include "mbedtls/aes.h"


int main(int argc, unsigned char const *argv[]) {
  /* code */
char *p;
unsigned int i=0,ret=0, mode=0,n;

unsigned long int NwkKey=0;

unsigned long int NwkKey1=0;
unsigned long int NwkKey2=0;
// 0x01 // 1 char
unsigned long int JoinNonce=0; // 3 chars
unsigned long int JoinEUI=0;  // 8 chars
unsigned long int DevNonce=0; // 2 chars
unsigned char iv[16];
unsigned char *tempNwkKey;  // using character pointers to access bytes from a long integer
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


mbedtls_aes_context aes;


unsigned char longkey[32];
unsigned char longkey1[16];
unsigned char longkey2[16];
unsigned char key[16];

unsigned char * lk1 = malloc(3 * sizeof(char));
unsigned char * lk2 = malloc(3 * sizeof(char));

unsigned char input [16];

unsigned char output[16];

mbedtls_aes_init( &aes );

JoinNonce=strtoul(argv[2], &p, 16);
JoinEUI=strtoul(argv[3], &p, 16);
DevNonce=strtoul(argv[4], &p, 16);

memcpy( longkey, argv[1], 32 );

// printf("Longkey is: %s\n", longkey);



memcpy( lk1, longkey, 16 ); //splitting the key into two parts as the strtoul function is not able to process more than 8 bytes
memcpy( lk2, (longkey+16), 16 );


// printf("Longkey1 is: %s\n", lk1);
// printf("Longkey2 is: %s\n", lk2);

NwkKey1=strtoul(lk1, &p, 16);
NwkKey2=strtoul(lk2, &p, 16);


for (i=0;i<8;i++)
  {
    key[7-i]=*(tempNwkKey1+i);   //merging the results from two strtoul functions into one
    key[15-i]=*(tempNwkKey2+i);
  }
printf("\n\n");
printf("The NwkKey is: ");
  for (i=0;i<16;i++)
    {
      printf("%x", key[i]);
    }
printf("\n\n");

input[0]=0x01;

memcpy( input + 1, &JoinNonce, 3 );
memcpy( input + 4, &JoinEUI, 8 );
memcpy( input + 12, &DevNonce, 2 );
input[14]=0x00;
input[15]=0x00;

  // for (i=0;i<16;i++)
  //   {
  //     key[i]=*(tempNwkKey+i);
  //     printf("%c", key[i]);
  //   }
  //   printf("\n");
/*
  input[0]=0x03;
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

printf("\n\n");*/

printf("The input is: ");
  for (i=0;i<16;i++)
    {
      printf("%x", input[i]);
    }
printf("\n\n");


ret = mbedtls_aes_setkey_enc( &aes, key, 128 );

// // int mbedtls_aes_crypt_ecb( mbedtls_aes_context *ctx,
// //                     int mode,
// //                     const unsigned char input[16],
// //                     unsigned char output[16] );
//
mbedtls_aes_crypt_ecb( &aes, mode, input, output);


printf("FNwkSIntKey: ");
 for (i=0;i<16;i++)
   printf("%x", output[i]);
printf("\n\n");

input[0]=0x03;

mbedtls_aes_crypt_ecb( &aes, mode, input, output);

printf("SNwkSIntKey: ");
 for (i=0;i<16;i++)
   printf("%x", output[i]);
printf("\n\n");

mbedtls_aes_free( &aes );
}
