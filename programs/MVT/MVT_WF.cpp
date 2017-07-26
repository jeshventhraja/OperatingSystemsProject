#include <bits/stdc++.h>
using namespace std;

struct b
{
	int size,PID;
	bool isEmpty;
};
struct b block[1000];
int blockCount,processCount,totalFreeSize;

void allocateProcess(int ind,int pid,int reqSize)
{
	int remSize = block[ind].size - reqSize;
	block[ind].PID = pid;
	block[ind].isEmpty = false;
	block[ind].size = reqSize;
	if(remSize)
	{
		for(int i=blockCount;i>ind;i--)
			block[i+1] = block[i];
		
		block[ind+1].size = remSize;
		block[ind+1].isEmpty = true;
		blockCount++;
	}
	totalFreeSize -= reqSize;
}


void addProcess()
{
	processCount++;
	int currSize,ind,maxi=-1,flag=0;
	printf("Enter size\n");
	scanf("%d",&currSize);
	for(int i=1;i<=blockCount;i++)
	{
		if(block[i].isEmpty)
		{
			if(block[i].size >=currSize && maxi<block[i].size)
			{
				flag=1;
				maxi = block[i].size;
				ind = i;
			}
		}
	}

	if(flag)
		allocateProcess(ind,processCount,currSize);
	else
	{
		if(currSize>totalFreeSize)
			printf("Memory not available\n");
		else
			printf("External Fragmentation = %d\n",totalFreeSize);
	}
}

void mergeProcess(int ind)
{
	if(block[ind+1].isEmpty && block[ind].isEmpty)
	{
		block[ind].size += block[ind+1].size;
		for(int i=ind+1;i<blockCount;i++)
			block[i] = block[i+1];
		blockCount--;
	}
}

void removeProcess()
{
	int remPID,ind,flag=0;
	printf("Enter process num\n");
	scanf("%d",&remPID);

	for(int i=1;i<=blockCount;i++)
	{
		if(block[i].PID==remPID)
		{
			ind = i;
			flag = 1;
			break;
		}
	}

	if(flag==0)
	{
		printf("TRAP : No such process exists\n");
		return ;
	}

	block[ind].isEmpty = true;
	totalFreeSize += block[ind].size;
	mergeProcess(ind);
	mergeProcess(ind-1);
}

void initialise(int size)
{
	block[1].isEmpty = true;
	block[1].size = size;
	blockCount = 1;
}

int main()
{
	int choice;

	printf("Enter Total Free Size\n");
	scanf("%d",&totalFreeSize);

	initialise(totalFreeSize);
	
	while(1)
	{
		printf("Enter 1 to add 2 to remove 3 to exit\n");
		scanf("%d",&choice);

		if(choice==1)
			addProcess();
		else if(choice==2)
			removeProcess();
		else
			break;
	}


	return 0;
}