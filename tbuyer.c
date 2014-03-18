#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(int argc, char const *argv[])
{
	int c=0;
	struct sockaddr_in server;
	char buffer[256];

	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		printf("Could Not create socket");

	}
	puts("Socket Created");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(argv[1]=='a')
	{
		server.sin_port=htons(9997);

	}
	if(argv[1]=='b')
	{
		server.sin_port=htons(9998);
		
	}
	if(argv[1]=='c')
	{
		server.sin_port=htons(9999);
		
	}
	
	if(connect(sfd,(struct sockaddr *)&server, sizeof(server))<0)
	{
		perror(" Connection Failed");
		return 1;
	}
	puts(" Connected \n");
	gets(buffer);
	send(sfd,buffer,255,0);
	int roll=recv(sfd,buffer,255,0);
	int key=atoi(buffer);
	roll=recv(sfd,buffer,255,0);
	int addr=atoi(buffer);
	