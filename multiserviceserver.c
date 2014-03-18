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
	    	case '1':
	    	send(nsfd,"6666",20,0);

	    	case '2':
	    	send(nsfd,"7777",20,0);

	    	case '3':
	    	send(nsfd,"9999",20,0);
    }
    close(nsfd);
    close(sfd);
    return 0;
}