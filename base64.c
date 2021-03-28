#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

// #define DEBUG
char* base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// char* encode_str = "Base64 is a group of binary-to-text encoding schemes that represent binary data in an ASCII string format by translating the data into a radix-64 representation.";
char  encode_str[1024];
char  output[1024+2];

int main(void) 
{

    int i ,j = 0;
    int rest = 0;
    int rest_pos = 0;
    int encode_len ;
    
    printf("Simply enter your data you wanna encode:\n");
    scanf("%s", &encode_str);
    printf("Your data: %s\n", encode_str);

    encode_len = strlen(encode_str);
    if(encode_len%3){
        encode_len = encode_len+(3-encode_len%3);
    }

    char* dest = malloc(encode_len);
    strcpy(dest,encode_str);
#ifdef DEBUG
    for ( i = 0; i < encode_len; i++)
    {
        printf("%d\t",dest[i]);
    }
    printf("\nencode_len:%d , str_len:%d\n",encode_len,strlen(dest));
#endif

    for ( i = 0; i <= encode_len; i++)
    {
        if(i > strlen(dest)){
            output[j++] = '=';
            continue;
        }

        rest_pos = (8 + rest_pos - 6) % 8;

        if (rest_pos) {
            rest = (rest << 8) + dest[i];
        }else{
            i = i -1;
        }

        output[j++] = base64_table[(rest >> rest_pos) & 0x3f];
        rest = dest[i] & (int) (pow(2,rest_pos)-1);
#ifdef DEBUG
        printf("i:%d, rest_pos:%d, rest = %d\n",i,rest_pos, rest);
        printf("output = %d\n",output[j-1]);
#endif
    }

    printf("Base64 encode output: %s\n",output);
    return 0;
}
