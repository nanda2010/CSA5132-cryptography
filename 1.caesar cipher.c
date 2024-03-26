#include<stdio.h>
#include<string.h>
int main(){
	int i,k,j,z;
	char msg[10];
	char d;
	char ct;
	printf("enter a message:");
	scanf("%s",&msg);
	printf("enter the key:");
	scanf("%d",&k);
	char al[] = "abcdefghijklmnopqrstuvwxyz";
	for(i=0;i<strlen(msg);i++)
	{
		for(j=0;j<strlen(al);j++)
		{
			if(al[j]==msg[i])
			{
			  z=(j+k)%26;
			  ct=al[z];
			  printf("%c ",ct);
			}
		}
	}
	return 0;
}
