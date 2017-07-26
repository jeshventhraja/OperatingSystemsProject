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
char buffer[MAX],msg[MAX];
struct sockaddr_in address,address2;
socklen_t size,size2;
long t;
pthread_t thread1,thread2;
char temp;	
sem_t mutex;

void *reading(void *arg)
{
	while(1)
	{	
		recv(client2, buffer, sizeof(buffer) ,0);
		sem_wait(&mutex);
		printf("Message received : \"%s\"\n\n", buffer);
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
				
		printf("Enter your message to send to server.\n");
		scanf("%[^\n]s",msg);
		send(client, msg , strlen(msg),0);
		sem_post(&mutex);
		memset(msg,0,sizeof msg);
	}
}

int main()
{
	sem_init(&mutex,1,1);
	client = socket(AF_INET,SOCK_STREAM,0);
	client2 = socket(AF_INET,SOCK_STREAM,0);
	
	if( client < 0)
	{	
		printf("Error in socket creation\n");
		exit(0);
	}	
	if( client2 < 0)
	{	
		printf("Error in socket creation\n");
		exit(0);
	}

	address.sin_family = AF_INET;
	address.sin_port = htons(8006);
	inet_pton( AF_INET, "127.0.0.1" , &address.sin_addr);

	address2.sin_family = AF_INET;
	address2.sin_port = htons(8005);
	inet_pton( AF_INET, "127.0.0.1" , &address2.sin_addr);

	size = sizeof(address);
	size2 = sizeof (address2);

	if(connect( client, (struct sockaddr *)&address , size) < 0)
	{
	 	printf("Error in connection\n");
		exit(0);	
	}	

	if(connect( client2, (struct sockaddr *)&address2 , size2) < 0)
	{
	 	printf("Error in connection\n");
		exit(0);	
	}

	pthread_create(&thread1, NULL, reading,(void *)t);
	pthread_create(&thread2, NULL, writing,(void *)t);
   	pthread_join(thread2, NULL); 	
	pthread_join(thread1, NULL);
	close(client);
	
	return 0;
}
