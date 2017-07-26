//Translation Look-Aside Buffer

#include <bits/stdc++.h>
using namespace std;

/*
TLB :-
	   Logical      Physical
ASID   PageNum      FrameNum      V/I     RWX
4bits   20bits       20bits       1 bit    3bits
ASID = 16     =>Max 16 processes
PageNum = 20  =>Max size of process is 4GB
FrameNum = 20 =>Max size of Main Memory is 4GB
V/I = 1       =>Valid Page 
Assumption - Only one user and he is the owner 
Page Size = 4KB
Total process size should not exceed 4GB
Frames are allocated continously
*/

#define pageSize 4

int totalPageTableEntry;
struct entry
{
	int asid,pageNum,frameNum,VorI,RWX;
};

vector <pair<int, pair<int, int> > >process;
vector<pair<int, int> >request;
struct entry TLB[256],pageTable[1000000];
//Page Table Size = 4GB/4KB = 1000000
int TLBCount[256],totalTLBEntries;

void createPageTable(int noOfProcesses)
{
	int i,j,temp,currPageNum=0,overallPageNum=0;

	for(i=1;i<=noOfProcesses;i++)
	{
		currPageNum = 0;
		temp = process[i-1].second.first;
		while(temp>0)
		{
			pageTable[overallPageNum].asid = process[i-1].first;
			pageTable[overallPageNum].pageNum = currPageNum;
			pageTable[overallPageNum].frameNum = overallPageNum;
			pageTable[overallPageNum].VorI = 1;
			pageTable[overallPageNum].RWX = process[i-1].second.second;
			temp/=pageSize;
			currPageNum++;
			overallPageNum++;
		}
	}
	totalPageTableEntry = overallPageNum;
}

bool findInTLB(int processNum,int reqMemory)
{
	int reqPageNum = (reqMemory/pageSize),flag=0;
	for(int i=0;i<totalTLBEntries;i++)
	{
		if(TLB[i].asid == processNum && TLB[i].pageNum == reqPageNum )
		{
			printf("Entry Found at TLB index = %d\n",i);
			//printf("Logical address = %d\nPhysical address =%d\n",);
			TLBCount[i] = 0;
			flag = 1;
		}
		else
			TLBCount[i]++;
	}
	if(flag)
		return true;

	return false;
}

int getPageTableIndexNum(int processNum,int reqPageNum)
{
	for(int i=0;i<totalPageTableEntry;i++)
	{
		if(pageTable[i].asid == processNum && pageTable[i].pageNum == reqPageNum)
		{
			return i;
		}
	}
}

void replaceTLB(int processNum,int reqMemory)
{
	int ind,maxi=-1;
	for(int i=0;i<totalTLBEntries;i++)
	{
		if(TLBCount[i]>maxi)
		{
			maxi = TLBCount[i];
			ind = i;
		}
	}

	printf("Entry not found\n");
	printf("Entry replaced at index %d\n",ind);

	TLBCount[ind] = 0;
	TLB[ind].asid = processNum;
	TLB[ind].pageNum = (reqMemory/pageSize);
	ind = getPageTableIndexNum(processNum,TLB[ind].pageNum);
	TLB[ind].frameNum = pageTable[ind].frameNum;//Find from PageTable
	TLB[ind].VorI = 1;
	TLB[ind].RWX = pageTable[ind].RWX;
}

int getRequest(int processNum,int reqMemory,int noOfProcesses)
{
	//Process number checking
	if ( !(processNum>0 && processNum<=noOfProcesses) )
		return -1;
	//Memory bound checking
	if( !(reqMemory>=0 && reqMemory<process[processNum].second.first) )
		return -1;

	if(findInTLB(processNum,reqMemory))
		return 1;
	
	
	replaceTLB(processNum,reqMemory);
	return 2;
	
}

void simulate_TLB(int tTS,int nP,int nR,int mMAT,int TLBAT)
{
	int noOfMiss=0,noOfHits=0,noOfProcesses,noOfRequests,result,mainMemAccessTime,TLBAccessTime;
	double hitPercentage,missPercentage,effectiveMemoryAccessTime;
	totalTLBEntries = tTS;
	noOfProcesses = nP;
	noOfRequests = nR;
	mainMemAccessTime = mMAT;
	TLBAccessTime = TLBAT;
	for(int i=0;i<noOfRequests;i++)
	{
		printf("\n");
		result = getRequest(request[i].first,request[i].second,noOfProcesses);
		if(result==-1){
			printf("TRAP\n");
		}
		else if(result==0){
			noOfMiss++;
		}
		else if(result==1){
			noOfHits++;
		}
		printf("\n");
	}

	hitPercentage = (noOfHits/noOfRequests);
	missPercentage = (noOfMiss/noOfRequests);
	effectiveMemoryAccessTime = ( (hitPercentage*TLBAccessTime) + (missPercentage*mainMemAccessTime) );

	printf("Total access time with TLB = %d\n",((mainMemAccessTime*noOfMiss) + (TLBAccessTime*noOfHits) ) );
	printf("Total access time without TLB = %d\n",(mainMemAccessTime*noOfRequests));
	printf("Effective Memory Access Time = %lf\n",effectiveMemoryAccessTime);
}

int main()
{
	int totalTLBSize,oneTLBEntrySize,mainMemAccessTime,TLBAccessTime,noOfProcesses,type,sizeOfProcess;

	oneTLBEntrySize = (4+20+20+1+3);
	totalTLBSize = (oneTLBEntrySize)*(totalTLBEntries);


	printf("Enter the amount of time it takes to access main memory and TLB\n");
	scanf("%d%d",&mainMemAccessTime,&TLBAccessTime);

	printf("Enter no of processes\n");
	scanf("%d",&noOfProcesses);

	printf("Enter Process Size (in KB) and Type(RWX)\n");
	for(int i=0;i<noOfProcesses;i++)
	{
		scanf("%d%d",&sizeOfProcess,&type);
		process.push_back(make_pair(i+1,make_pair(sizeOfProcess,type)));
	}

	//Create Page Table
	createPageTable(noOfProcesses);

	int noOfRequests,processNum,reqMemory,result;
	printf("Enter no of requests\n");
	scanf("%d",&noOfRequests);

	printf("enter process number and required memory\n");
	for(int i=0;i<noOfRequests;i++)
	{
		scanf("%d%d",&processNum,&reqMemory);
		//printf("Logical Address = %d\n",);
		request.push_back(make_pair(processNum,reqMemory));
	}

	//simulate_TLB(128,noOfProcesses,noOfRequests,mainMemAccessTime,TLBAccessTime);
	//simulate_TLB(256,noOfProcesses,noOfRequests,mainMemAccessTime,TLBAccessTime);
	simulate_TLB(4,noOfProcesses,noOfRequests,mainMemAccessTime,TLBAccessTime);
	// for(int i=0;i<noOfRequests;i++)
	// {
	// 	result = getRequest(processNum,reqMemory,noOfProcesses);
	// 	if(result==-1){
	// 		printf("TRAP\n");
	// 	}
	// 	else if(result==0){
	// 		noOfMiss++;
	// 	}
	// 	else if(result==1){
	// 		noOfHits++;
	// 	}
	// }

	// printf("Total access time with TLB = %d\n",((mainMemAccessTime*noOfMiss) + (TLBAccessTime*noOfHits) ) );
	// printf("Total access time without TLB = %d\n",(mainMemAccessTime*noOfRequests));

	
	return 0;
}
