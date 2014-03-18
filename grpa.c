#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(int argc, char const *argv[])
{
	int c=0;
	struct sockaddr_in server,server1;
	char buffer[256];
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		printf("Could Not create socket");

	}
	int sfd1=socket(AF_INET,SOCK_STREAM,0);
	if(sfd1 == -1)
	{
		printf("Could Not create socket");

	}
	puts("Socket Created");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(8889);
	if(connect(sfd,(struct sockaddr *)&server, sizeof(server))<0)
	{
		perror(" Connection Failed");
		return 1;
	}
	puts(" Connected \n");
	gets(buffer);
	send(sfd,buffer,256,0);
	recv(sfd,buffer,256,0);
	int portn=atoi(buffer);
	server1.sin_family=AF_INET;
	server1.sin_addr.s_addr=inet_addr("127.0.0.1");
	server1.sin_port=htons(portn);
	close(sfd);
	if(connect(sfd1,(struct sockaddr *)&server1, sizeof(server1))<0)
	{
		perror(" Connection Failed");
		return 1;
	}
	puts("Connected to grp b");
}