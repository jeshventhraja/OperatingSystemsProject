//SSTF
//Complexity O(N^2)
#include<bits/stdc++.h>
using namespace std;

int A[100005],visit[100005],S[100005];
int ans;
int main()
{
	int N,i,j,k;
	
	printf("Enter total numbers of cylinders\n");
	scanf("%d",&N);
	
	printf("Enter the values of each process\n");
	
	for(i=1;i<=N;i++)
	scanf("%d",&A[i]);
	
	int head;
	printf("Enter the head value\n");
	scanf("%d",&head);
	int x=0;
	int count=N;
	int indx;
	while(count--)
	{
		int mini=99999;
											
		for(i=1;i<=N;i++)
		{
			if(abs(head-A[i])<mini && !visit[i])
			{
				mini=abs(head-A[i]);
				indx=i;
			}
		}
			visit[indx]=1;
			S[++x]=indx;
			ans+=mini;
			head=A[indx];
	}
	
	printf("Total seek time is %d \n",ans);
	
	printf("The sequence order is \n");
	
	for(i=1;i<=N;i++)
	{
		printf("%d ",S[i]);
	}
	
	return 0;
}