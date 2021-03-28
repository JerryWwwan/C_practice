#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define TRUE  1
#define FALSE 0
#define HASHSIZE 251
#define CMD_MAX_LEN 30

typedef struct kvpair{
    char *key;
    char *val;
}hash_tab;

hash_tab *hash_table[HASHSIZE] = {0};

char cmd_signal[CMD_MAX_LEN];
char reply_table[5][30]={"Good","OK","Create","Delete","Perfect"};

unsigned char hasher31(char *str)
{
    unsigned long hashval = 5381;
    while (*str){
      hashval =  31 * hashval + *str++;
    }
    return hashval % HASHSIZE;
}

void* VirtualProcesser() {      //Simulate a virtual processor to reply data

    unsigned char hashval;
    char data_signal[CMD_MAX_LEN];
    char cmd_str[CMD_MAX_LEN];
    while (1)
    {
        if( cmd_signal[strlen(cmd_signal)-1] == '\r') {

            sscanf(cmd_signal,"%s\r",cmd_str);
            hashval = hasher31(cmd_str);
            strcpy(data_signal,reply_table[rand()%5]);
            hash_table[hashval]->val = strdup(data_signal);
        }
        sleep(1);
    }
    
  pthread_exit(NULL); 
}

int SendCommand ( char* pBuf,int Save2Dict)
{

    char cmd_str[CMD_MAX_LEN];
    unsigned char hashval=hasher31(pBuf);
    
    if(Save2Dict == TRUE){
        hash_table[hashval] = malloc(sizeof(hash_tab));
        hash_table[hashval]->key = strdup(pBuf);
        hash_table[hashval]->val = NULL;
    }

    snprintf(cmd_str,CMD_MAX_LEN,"%s\r",pBuf);
    strcpy(cmd_signal,cmd_str);

    return 0;
}


int GetCmdData(char* output, int size){
	
    unsigned char retry = 40;
    unsigned char hashval;
    char cmd_buf[CMD_MAX_LEN];

	while (retry)
	{
		sleep(1);
   
        sscanf(cmd_signal,"%s\r",cmd_buf);

        hashval = hasher31(cmd_buf);
        if(hash_table[hashval] == NULL){
            printf("hash_table[%d] is NULL\n",hashval );
            continue;
        }
        printf("hash_table[%d]->key:%s, cmd:%s\n",hashval,hash_table[hashval]->key,cmd_buf);
        if(strcmp(hash_table[hashval]->key,cmd_buf) == 0 && hash_table[hashval]->val != NULL){
            memcpy(output,hash_table[hashval]->val,size);
            hash_table[hashval]->key = NULL;
            hash_table[hashval]->val = NULL;
            free(hash_table[hashval]->key);
            free(hash_table[hashval]->val);            
            free(hash_table[hashval]);
            break;
        }

		retry--;
	}
	if( !retry ){
		printf("GetCmdData:%s Timeout expired\n",cmd_buf);		
		return -1;
	} 

	return 0; 
}



int main()
{
    char cmd[CMD_MAX_LEN];
	char output[300]={0};
    unsigned char hashval;

    pthread_t t; 
    pthread_create(&t, NULL, VirtualProcesser, NULL); 
    
    while (1)
    {
        printf("Simply enter your command to send :\n");
        scanf("%s", &cmd);
        printf("Your command: %s\n", cmd);

        srand( time(NULL) );

        SendCommand(cmd,TRUE);

        GetCmdData(output,300);

        printf("Response data: %s\n",output);
        printf("===============================\n")
    }

    return 0;
}