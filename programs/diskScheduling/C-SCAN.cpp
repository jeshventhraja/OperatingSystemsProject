//C-SCAN
//Complexity is O(Nlog(N))
#include<bits/stdc++.h>
using namespace std;

int A[100005],S[1000005];

int main()
{
	int N,i,j,k,M;
	
	
	printf("Enter total number of process in queue \n");
	scanf("%d",&N);
	
	printf("Enter the values of process \n");
	
	for(i=1;i<=N;i++)
	scanf("%d",&A[i]);
	
	printf("Enter the maximum  value of track \n");
	scanf("%d",&M);
	
	int ans=0;
	int head;
	printf("Enter the head value\n");
	scanf("%d",&head);
	
	int prev;
	
	printf("Enter the previous request\n");
	scanf("%d",&prev);
	
	sort(A,A+N);
	
	int left_min,right_min;
	
	for(i=1;i<=N;i++)
	{
		if(A[i]>head)
		{
			left_min=A[i-1];
			right_min=A[i];
			break;
		}
	}
	
	int indx;
	int x=0;
	
	if(prev-head>0)
	{
		ans+=head+(M-right_min);
		
		for(i=1;i<=N;i++)
		{
			if(A[i]==left_min)
			{
				indx=i;
				break;
			}
		}
		
		for(i=indx;i>=1;i--)
		S[++x]=A[i];
		for(i=indx+1;i<=N;i++)
		S[++x]=A[i];
	}
	
	else 
	{
		ans+=M-head+left_min;
		
		for(i=1;i<=N;i++)
		{
			if(A[i]==right_min)
			{
				indx=i;
				break;
			}
		}
		for(i=indx;i<=N;i++)
		S[++x]=A[i];
		for(i=indx-1;i>=1;i--)
		S[++x]=A[i];
	}
	
	printf("Total seek time is %d \n",ans);
	printf("Movement of the dis is in the following order\n");
	for(i=1;i<=x;i++)
	cout<<S[i]<<" ";
	return 0;
}