#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<unistd.h>
time_t mytime;
time_t metime;
sem_t x;
sem_t wsem;
pthread_t tid;
int readcount;

int complete=0;

void * reader (int * burst)
{
    int waittime;
    waittime = *burst;
    mytime = time(NULL);
	
    printf("Reader is trying to enter time:%s\n",ctime(&mytime));

    sem_wait(&x);
    readcount++;
    if(readcount==1)
        {
                sem_wait(&wsem);
        }
    mytime = time(NULL);
    printf("%d Reader inside time:%s\n",readcount,ctime(&mytime));
    sem_post(&x);
    sleep(waittime);
    
    sem_wait(&x);
    readcount--;
    if(readcount==0)
        {
                sem_post(&wsem);
        }

    sem_post(&x);
    mytime = time(NULL);
    printf("Reader is Leaving time:%s\n",ctime(&mytime));
    complete++;
}   

void * writer (int * burst)
{
    int waittime;
    waittime=*burst;
    mytime = time(NULL);
    printf("Writer is trying to enter time:%s\n",ctime(&mytime));

    sem_wait(&wsem);
    mytime = time(NULL);
    printf("Write has entered time:%s\n",ctime(&mytime));
    sleep(waittime);
 
    sem_post(&wsem);    
    mytime = time(NULL);
    printf("Writer is leaving%s\n",ctime(&mytime));
    complete++;
}

int main()
{       int a[100][3];
        readcount=0;
        time(&metime);
        sem_init(&x,0,1);
        //printf("hi\n");
        
        sem_init(&wsem,0,1);
    int n1,n2,i;    
    printf("\nEnter the no of users: ");
    scanf("%d",&n1);
    printf("Enter arrival and burst time and type (0.reader,1.writer) for each user:\n");
    for(i=0;i<n1;i++)
         {
                scanf("%d%d%d",&a[i][0],&a[i][2],&a[i][1]);
         }
         int time=0;
         
         //printf("hi\n");
         //pthread_create(&tid,NULL,time_keeper,NULL); 

    for(i=0;i<n1;i++)
        {
         while(time<a[i][0])
         {
                
                time++;
                sleep(1);
         }
        if(a[i][1]==1)
        pthread_create(&tid,NULL,writer,&a[i][2]);
        else
        pthread_create(&tid,NULL,reader,&a[i][2]);
        }
    while(complete<n1)sleep(1);
    exit(0);
}
