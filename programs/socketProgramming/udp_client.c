#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 1024

int client,client2;
char temp,buffer[MAX],msg[MAX];
struct sockaddr_in serverAddr,serverAddr2;
socklen_t addr_size,addr_size2;
long t;
pthread_t thread1,thread2;	
sem_t mutex;

void *reading(void *arg)
{
	while(1)
	{	
		recvfrom(client2,buffer,1024,0,(struct sockaddr *)&serverAddr2, &addr_size2);
		sem_wait(&mutex);
		printf("Message is : %s\n",buffer);
		sem_post(&mutex);
		memset(buffer, 0, sizeof buffer);
	}
}

void *writing(void *arg)
{
	while(1)
	{
		char k;
		scanf("%c",&k);
		scanf("%c",&k);
		
		sem_wait(&mutex);
				
		printf("Enter your message to send to client.\n");
      		scanf("%[^\n]s",msg);
      		sendto(client,msg,sizeof(msg),0,(struct sockaddr *)&serverAddr,addr_size);
		sem_post(&mutex);
		memset(msg,0,sizeof msg);
	}
}

int main()
{
	sem_init(&mutex,1,1);	
	client = socket(PF_INET, SOCK_DGRAM, 0);
	client2 = socket(PF_INET, SOCK_DGRAM, 0);
	if(client<0)
	{
		printf("Error in socket creation\n");
		exit(0);
	}

	if(client2<0)
	{
		printf("Error in socket creation\n");
		exit(0);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9000);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	serverAddr2.sin_family = AF_INET;
	serverAddr2.sin_port = htons(9001);
	serverAddr2.sin_addr.s_addr = inet_addr("127.0.0.1");
	 
	addr_size = sizeof serverAddr;
	addr_size2 = sizeof serverAddr2;

	pthread_create(&thread1, NULL, reading,(void *)t);
	pthread_create(&thread2, NULL, writing,(void *)t);
   	pthread_join(thread2, NULL); 	
	pthread_join(thread1, NULL);



	return 0;

}
