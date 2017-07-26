#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

sem_t custReady;
sem_t accessSeats;
sem_t barbReady;
sem_t complete;
int sleeping;
pthread_t tid;
int completed;
int seatcount;
time_t mytime;
int maxseatcount;
int n;
void * barber(void * param)
{
        while(1)
        {
                
                sem_wait(&accessSeats);
                if(seatcount==maxseatcount)
                {
                        sleeping =1;
                }
                sem_post(&accessSeats);
                if(sleeping==1)
                {
                    mytime = time(NULL);
                    printf("Barber sleeping time: %s\n",ctime(&mytime)); 
                        sem_wait(&complete);
                        if(completed==n)
                        completed++;
                        sem_post(&complete);   
                }
                sem_wait(&custReady);
                sem_wait(&accessSeats);
                seatcount++;
                sem_post(&barbReady);
                sem_post(&accessSeats);
                mytime = time(NULL);
                printf("Barber is cutting customers hair time: %s\n",ctime(&mytime));
                sleep(5);
                
                sem_wait(&complete);
                completed++;
                sem_post(&complete);
                
        }
}

void * customer(void * param)
{
        sem_wait(&accessSeats);
        if(seatcount>0)
        {
                if(sleeping!=1)
                {mytime = time(NULL);
                printf("Customer took a seat time: %s\n",ctime(&mytime));
                }
                else
                {
                        mytime = time(NULL);
                        printf("Customer Wokeup Barber time: %s\n",ctime(&mytime));
                        sleeping=0;
                }
                seatcount--;
                sem_post(&custReady);
                
                sem_post(&accessSeats);
        }
        else
        {       
                mytime = time(NULL);
                printf("Customer Left time: %s\n",ctime(&mytime));
                sem_post(&accessSeats);
                sem_wait(&complete);
                completed++;
                sem_post(&complete);
        }
        
}





int main()
{       int a[100][3];
        printf("Cutting time is 5 seconds\n");
        printf("Enter no of seats in waiting room\n");
        scanf("%d",&seatcount);
        sleeping =1;
        maxseatcount=seatcount;
        sem_init(&custReady,0,0);
        sem_init(&accessSeats,0,1);
        sem_init(&barbReady,0,0);
        sem_init(&complete,0,1);
        completed=0;
    int i;    
    printf("\nEnter the no of customer: ");
    scanf("%d",&n);
    printf("Enter arrival time for each customer:\n");
    for(i=0;i<n;i++)
         {
                scanf("%d",&a[i][0]);
         }
         int time=0; 
        
         pthread_create(&tid,NULL,barber,NULL);
    for(i=0;i<n;i++)
        {
         while(time<a[i][0])
         {
                
                time++;
                sleep(1);
         }
        
        pthread_create(&tid,NULL,customer,NULL);
        }
    while(completed<=n){sleep(1);}
    exit(0);
}
