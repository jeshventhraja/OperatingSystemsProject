#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#define MAX 1024

int server,server2,recvsock,recvsock2,receive;
char buffer[MAX],msg[MAX];
struct sockaddr_in address,address2;
socklen_t size,size2;
long t;
pthread_t thread1, thread2;
char temp;
sem_t mutex;

void *reading(void *arg)
{
	while(1)
	{
		receive = recv(recvsock, buffer, sizeof(buffer) ,0);
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
		printf("Enter your message to send to client.\n");
		scanf("%[^\n]s",msg);
		send(recvsock2, msg , strlen(msg),0);		
		sem_post(&mutex);
		memset(msg,0,sizeof msg);
	}
}

int main()
{
	sem_init(&mutex,1,1);
	server = socket(AF_INET,SOCK_STREAM,0);
	server2 = socket(AF_INET,SOCK_STREAM,0);
	if(server < 0)
	{	
		printf("Error in socket creation\n");
		exit(0);
	}	
	if(server2 < 0)
	{
		printf("Error in socket creation.\n");
		exit(0);
	}

	address.sin_family = AF_INET;
	address.sin_port = htons(8006);
	inet_pton( AF_INET, "127.0.0.1" , &address.sin_addr);

	address2.sin_family = AF_INET;
	address2.sin_port = htons(8005);
	inet_pton( AF_INET, "127.0.0.1" , &address2.sin_addr);


	size = sizeof(address);
	size2 = sizeof(address2);

	if (bind(server, (struct sockaddr *)&address, size)<0)
	{
		printf("Error in Binding\n");
		exit(0);
	}
	

	if( listen(server,10) < 0)
	{
		printf("Error in listening\n");
		exit(0);
	}
	

	if (bind(server2, (struct sockaddr *)&address2, size2)<0)
	{
		printf("Error in Binding\n");
		exit(0);
	}
	
	if( listen(server2,10) < 0)
	{
		printf("Error in listening\n");
		exit(0);
	}
	else
		printf("Listening (Connection Established)\n");


	recvsock = accept( server, (struct sockaddr *)&address, &size);
	if(recvsock < 0)
	{
		printf("Error in accepting\n");
		exit(0);
	}

	recvsock2 = accept(server2,(struct sockaddr *)&address2,&size2);
	if(recvsock2 < 0)
	{
		printf("Error in accepting\n");
		exit(0);
	}

	pthread_create(&thread1, NULL, writing,(void *)t);
	pthread_create(&thread2, NULL, reading,(void *)t);
    
 	pthread_join(thread1, NULL);
        pthread_join(thread2, NULL); 	
    
	close(server);
	close(recvsock);
	close(receive);

	return 0;
}
