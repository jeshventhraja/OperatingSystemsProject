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

int server,server2;
char temp,buffer[1024],msg[1024],k;
struct sockaddr_in serverAddr,serverAddr2;
struct sockaddr_storage serverStorage,serverStorage2;
socklen_t addr_size,addr_size2;
int i;
long t;
pthread_t thread1, thread2;
sem_t mutex;

void *reading(void *arg)
{
	while(1)
	{
		recvfrom(server,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
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
		scanf("%c",&k);
		scanf("%c",&k);
	
		sem_wait(&mutex);		
		printf("Enter your message to send to client.\n");
      		scanf("%[^\n]s",msg);
      		sendto(server2,msg,sizeof(msg),0,(struct sockaddr *)&serverStorage2,addr_size2);
    		sem_post(&mutex);
		memset(msg,0,sizeof msg);
	}
}

int main()
{
 	sem_init(&mutex,1,1);
	server = socket(PF_INET, SOCK_DGRAM, 0);
	if(server<0)
	{
		printf("Error in socket creation\n");
		exit(0);
	}	
	server2 = socket(PF_INET, SOCK_DGRAM, 0);
	if(server2<0)
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
   

	bind(server, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	addr_size = sizeof serverStorage;

	bind(server2, (struct sockaddr *) &serverAddr2, sizeof(serverAddr2));
	addr_size2 = sizeof serverStorage2;

	pthread_create(&thread1, NULL, writing,(void *)t);
	pthread_create(&thread2, NULL, reading,(void *)t);
    
 	pthread_join(thread1, NULL);
        pthread_join(thread2, NULL); 

	  
  return 0;
}
