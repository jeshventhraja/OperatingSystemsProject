//LOOK
//Complexity is O(Nlog(N))

#include<bits/stdc++.h>
using namespace std;

int A[100005],S[100005];
int ans;
int main()
{
	int N,i,j,k,M;
	
	printf("Enter the number of processses in the queue\n");
	scanf("%d",&N);
	
	printf("Enter the values of each process in the queue\n");
	for(i=1;i<=N;i++)
	{
		scanf("%d",&A[i]);
	}
	int head;
	printf("Enter the head value\n");
	scanf("%d",&head);
	int prev;
	printf("Enter the previous request \n");
	scanf("%d",&prev);
	
	sort(A+1,A+N+1);
	int indx,x=0;
	
	int maxi=A[N];
	int mini=A[1];
	int left_min,right_min;
	for(i=1;i<=N;i++)
	{
		if(A[i]>head)
		{
			right_min=A[i];
			left_min=A[i-1];
		}
	}
	
	if(prev-head>0)
	{
		ans+=head-mini+maxi-mini;
		
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
		ans+=maxi-head+maxi-mini;
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
	printf("The total seek time is %d\n",ans);
	
	printf("Movement of the disc is as follows\n");
	
	for(i=1;i<=x;i++)
	cout<<S[i]<<" ";
	return 0;
}