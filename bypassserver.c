#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(int argc, char const *argv[])
{
	int c=0;
	struct sockaddr_in server,client,server6;
	char buffer[256];
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		printf("Could Not create socket");

	}
	int tsfd=socket(AF_INET,SOCK_STREAM,0);
	if(tsfd == -1)
	{
		printf("Could Not create t socket");

	}
	puts("Sockets Created");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(8889);
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
	recv(nsfd,buffer,255,0);
	switch(buffer[0])
	{
		case '6':
		server6.sin_family=AF_INET;
		server6.sin_addr.s_addr=inet_addr("127.0.0.1");
		server6.sin_port=htons(9999);
		if(connect(tsfd,(struct sockaddr *)&server6, sizeof(server6))<0)
	    {
		    perror(" Connection Failed");
		    return 1;
	    }
	    puts(" Connected to 6 \n");
	    send(tsfd,"Connection going to be made",256,0);
	    send(nsfd,"9999",256,0);

	}
	close(nsfd);
	close(tsfd);
	close(sfd);
}