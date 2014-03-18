#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(int argc, char const *argv[])
{
	int c=0;
	struct sockaddr_in server,client;
	char buffer[256];
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
	puts("Enter the number of Clients");
	int pr;
	scanf("%d",pr);
	int nsfd[pr];
	int csize=sizeof(client);
	int i;
	for(i=0;i<pr;i++)
	{
		nsfd[i]=accept(sfd,(struct sockaddr *)&client , &csize);
		if(nsfd<0)
		perror(" Error on accept ");
	}
	printf("Connected \n");
	int k=0;
	int j;
	int flag=0;
	while(1)
	{
		j=((k++)%pr);
		struct pollfd fds[1];//={{0,POLLIN},{nsfd,POLLIN}};
		fds[0].fd=nsfd[j];
		fds[0].events=POLLIN;
		int r=poll(fds,1,10);
		if(r<0)
			perror(" Error using poll \n");
		else
		{
			if(fds[0].revents & POLLIN)
			{
				recv(nsfd[j],buffer,256,0);
				int l=atoi(buffer);
				flag=1;
			}
		}	
		if(flag==1)
		{
			if(j==l)
			{
				send(nsfd[j,"Your message delieverd",256,0);
					flag=0;
			}
		}
		
	}