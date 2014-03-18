#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int p;
int num_proc;

int dfs(int n, int cur, int vi[n], int mat[n][n])
{
	int i,j,val=1;
	
	if (vi[cur] == 1)
	{
		printf("DEADLOCK detected !!\n");
		printf("Process %d being terminated\n", cur+1);
		
		memset(mat[cur], 0, sizeof(int) * n);
		for (i=0;i<n;i++)
		{
			mat[i][cur]=0;
		}
		return 0;
	}
	else
		vi[cur] = 1;
		
	for (i=0;i<n;i++)
	{
		if (mat[cur][i] == 1)
		{
			j=dfs(n, i, vi, mat);
			if (val != 0)
				val = j;
		}
	}
	return val;
}

void chk_cycle(int n, int mat[n][n])
{
	int vi[num_proc], i;
	
	for (i=0;i<num_proc;i++)
	{
		memset(vi, 0, num_proc * sizeof(int));
		dfs(num_proc, i, vi, mat);
	}
}
int main(int argc, char const *argv[])
{
	int c=0;
	struct sockaddr_in server,client;
	char buffer[256];
	memset(buffer,'\0',255);
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		printf("Could Not create socket");

	}
	puts("Socket Created");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(15000);
	if(bind(sfd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("bind Failed. Error");
		return 1;
	}
	puts("binds done");
	listen(sfd,50);
	int csize=sizeof(client);
	int nsfd=accept(sfd,(struct sockaddr *)&client , &csize);
	if(nsfd<0)
		perror(" Error on accept ");
	//gets(buffer);
	int roll1=send(nsfd,"Enter no of processess",255,0);
	int roll=recv(nsfd,buffer,255,0);
	p=atoi(buffer);
	num_proc=p;
	int arr[p][p];
	roll1=send(nsfd,"Enter graph row wise",255,0);
	int i=0;int j=0;
	for(i=0;i<p;i++)
		for(j=0;j<p;j++)
		{
			roll=recv(nsfd,buffer,255,0);
			int h=atoi(buffer);
			arr[i][j]=h;
			memset(buffer,'\0',255);
		}

	
	
	for (i=0;i<num_proc;i++)
	{
		for (j=0;j<num_proc;j++)
		{
			printf("%d	",arr[i][j]);
		}
		printf("\n");
	}
	chk_cycle(p, arr);	


	//	
	for (i=0;i<num_proc;i++)
	{
		for (j=0;j<num_proc;j++)
		{
			printf("%d	",arr[i][j]);
		}
		printf("\n");
	}
}
	












}	