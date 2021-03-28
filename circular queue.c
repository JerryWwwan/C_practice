#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include "type.h"
#include <limits.h>

#define Q_size 5
#define D_size 40

typedef struct
{
	char queue[Q_size][D_size];
	uint8 front;
	uint8 rear;
}QueueADT;

QueueADT CreateQ(){
	QueueADT NewQueue;
	NewQueue.front = 0;
	NewQueue.rear = 0;
	return NewQueue;
}

void addQ(QueueADT *Q,char *item){
	Q->rear = (Q->rear+1)%Q_size;
	if (Q->front==Q->rear)
	{
		printf("Queue is full\n");
		exit(1);
	}
	else 
	{
		strcpy(Q->queue[Q->rear], item);
	}
}
char *getQ(QueueADT *Q){
	if (Q->front==Q->rear)
	{
		printf("Queue is empty\n");
		exit(1);
	}
	else
	{
		Q->front = (Q->front+1)%Q_size;
		return Q->queue[Q->front];
	}
	
}

int main(void)
{    
	QueueADT QQ;
	QQ=CreateQ();
	char *Data;

	addQ(&QQ,"test");
	addQ(&QQ,"123");
	Data = getQ(&QQ);
	printf("Data = %s\n",Data);
	Data = getQ(&QQ);
	printf("Data = %s\n",Data);
	// Data = getQ(&QQ);
	// printf("Data = %s\n",Data);
	addQ(&QQ,"test");
	addQ(&QQ,"test");
	addQ(&QQ,"test");
	addQ(&QQ,"test");
	

	
	return 0;

}