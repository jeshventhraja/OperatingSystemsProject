// Bankers and Resource Request 

#include<stdio.h>
#include<stdlib.h>

int max[100][100],need[100][100],available[100]; // declaring all the required matrixes
int allocation[100][100];
int n,r,i,j;
int finish[100];

int bankers()
	{
	int k=0;	
	int curr=1;
	int avail[100];
	for(i=1;i<=r;++i){
		avail[i]=available[i];
	}
	printf("order of execution:");
	int count=0;
	for(i=1;i<=n;++i)
		finish[i]=0;
		
		while(k<n) //checks for all the processes whether they are completed or not
	{
		if(finish[curr]==1){
			++curr;
			if(curr>n)curr=1;continue;
		}
		int flag=0;
		for(i=1;i<=r;++i){
			if(need[curr][i]>available[i]) //need must be graeter than available 
			{
				flag=1;++count;
				if(count==(n-k)) //checks if process is in deadlock
				{
					return 0;
				}
				break;
			}
		}
		if(flag==1){
			++curr;
			if(curr>n)curr=1;
			continue;
		}
		count=0;
		finish[curr]=1;
		for(i=1;i<=r;++i) // if process is allocated
		{
			available[i]=available[i]+allocation[curr][i];
		}
		++k;
		printf("%d ",curr);
		++curr;if(curr>n)curr=1;
	}
	for(i=1;i<=r;++i) //process is allocated
		available[i]=avail[i];
	return 1;
}
int main()
{	
	printf("enter no of processes:");
	scanf("%d",&n);
	printf("enter no of resources:");
	scanf("%d",&r);
	printf("enter allocation and max for each process:\n");	
	for(i=1;i<=n;++i){
		printf("Process %d:\n",i);
		for(j=1;j<=r;++j){

			scanf("%d",&allocation[i][j]);	
		}
		for(j=1;j<=r;++j){
			scanf("%d",&max[i][j]);
			need[i][j]=max[i][j]-allocation[i][j];	
		}
	}
	printf("enter available for first process:");
	for(i=1;i<=r;++i){
		scanf("%d",&available[i]);
	}
	int temp=bankers();
	if(temp)
		printf("System Currently in Safe state\n");
	else
		printf("System in unsafe state\n");
	int request[100];
	while(1){	
		printf("enter process number:");
		int pid;
		scanf("%d",&pid);
		printf("enter request :");
		for(i=1;i<=r;++i){
			scanf("%d",&request[i]);
		}
		int flag=0;		
		for(i=1;i<=r && flag==0;++i){
			if(request[i]>need[pid][i] || request[i]>available[i]) // checks the condition for resource whether it should be granted or not
			{
				printf("Request not granted\n");
				flag=1;
			}
		}
		if(flag)
			continue;
		
		int avail[100];
		for(i=1;i<=r;++i)
		{
			avail[i]=available[i];
		}
		for(i=1;i<=r;++i) // if request is granted than available is decreased and allocation is also changed
		{
			available[i]-=request[i];
			allocation[pid][i]+=request[i];
			need[pid][i]-=request[i];
		}
		
		if(bankers()==1){
			printf("System in safe state\n");
		}
		else{
			printf("System in unsafe state...returning to last state\n");
			for(i=1;i<=r;++i){
				available[i]=avail[i];
			}
		}	
	}
}