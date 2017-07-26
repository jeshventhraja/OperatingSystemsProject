//FCFS
// O(N) complexity
#include"bits/stdc++.h"
using namespace std;

int A[100005];

int main()
{
	
	int N,i,j,k;
	
	printf("Enter the number of processes\n");
	scanf("%d",&N);
	
	printf("Enter the queue of processes\n");
	
	for(i=1;i<=N;i++)
	scanf("%d",&A[i]);
	
	int ans=0;
	int prev=A[1];
	for(i=2;i<=N;i++) //calculates the total seek time
	{
	ans+=abs(A[i]-prev);
		prev=A[i];
	}
	printf("Total seek time is %d\n",ans);
	return 0;
}