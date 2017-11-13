#include<stdio.h>
#include<stdlib.h>
#include "mbedtls/config.h"
#include "mbedtls/aes.h"
#include <string.h>

int main(int argc, unsigned char const *argv[]) {

char *p;
unsigned int i=0,mode=1;

unsigned long int NwkKey1=0;
unsigned long int NwkKey2=0;
// 0x01 // 1 byte
unsigned long int JoinNonce=0; // 3 bytes
unsigned long int JoinEUI=0;  // 8 bytes
unsigned long int DevNonce=0; // 2 bytes

// using character pointers to access bytes from a long integer
unsigned char *tempNwkKey1;
unsigned char *tempNwkKey2;
tempNwkKey1=(unsigned char*)&NwkKey1;
tempNwkKey2=(unsigned char*)&NwkKey2;

mbedtls_aes_context aes;

unsigned char key[16]; // NwkKey

unsigned char * lk1 = malloc(16 * sizeof(char));
unsigned char * lk2 = malloc(16 * sizeof(char));

unsigned char input [16]; //JoinNonce+JoinEUI+DevNonce
unsigned char output[16]; // Output of encryption

mbedtls_aes_init( &aes );

JoinNonce=strtoul(argv[2], &p, 16); //converting to HEX
JoinEUI=strtoul(argv[3], &p, 16);
DevNonce=strtoul(argv[4], &p, 16);

//splitting the NwkKey into two parts
memcpy( lk1, argv[1], 16 );
memcpy( lk2, (argv[1]+16), 16 );

NwkKey1=strtoul(lk1, &p, 16); //converting to HEX
NwkKey2=strtoul(lk2, &p, 16);

for (i=0;i<8;i++)
  {
    //merging the results from two strtoul functions into one
    key[7-i]=*(tempNwkKey1+i);
    key[15-i]=*(tempNwkKey2+i);
  }

printf("\n\n");
printf("The NwkKey is: ");
  for (i=0;i<16;i++)
    {
      printf("%02X", key[i]);
    }
printf("\n\n");

input[0]=0x01; // for FNwkSIntKey

memcpy( input + 1, &JoinNonce, 3 );
memcpy( input + 4, &JoinEUI, 8 );
memcpy( input + 12, &DevNonce, 2 );
input[14]=0x00; //zero padding
input[15]=0x00;

printf("The input is: ");
  for (i=0;i<16;i++)
    {
      printf("%02X", input[i]);
    }
printf("\n\n");


mbedtls_aes_setkey_enc( &aes, key, 128 );

//AES encryption
mbedtls_aes_crypt_ecb( &aes, mode, input, output);


printf("FNwkSIntKey: ");
 for (i=0;i<16;i++)
   printf("%02X", output[i]);
printf("\n\n");

input[0]=0x03; //For SNwkSIntKey, rest of the data is same

//AES encryption
mbedtls_aes_crypt_ecb( &aes, mode, input, output);

printf("SNwkSIntKey: ");
 for (i=0;i<16;i++)
   printf("%02X", output[i]);
printf("\n\n");

mbedtls_aes_free( &aes );
}
