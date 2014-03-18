#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h> 
int main(int argc, char const *argv[])
{
	int c=0;
	struct sockaddr_in server,client;
	char buffer[256];
	char buffer1[256];
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		printf("Could Not create socket");

	}
	puts("Socket Created");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(8889);
	if(bind(sfd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("bind Failed. Error");
		return 1;
	}
	puts("binds done");
	listen(sfd,5);
	int csize=sizeof(client);
	int nsfd=accept(sfd,(struct sockaddr *)&client , &csize);
	if(nsfd<0)
		perror(" Error on accept ");
	/*recv(nsfd,buffer,255,0);
	printf("Here is the message recieved: %s\n",buffer );
	send(nsfd,"I got you message",18,0);*/
	printf("Connected \n");
	fd_set read,errors;
	struct timeval thetimeout;
	FD_ZERO(&read);
	FD_ZERO(&errors);
	FD_SET(0,&read);
	FD_SET(nsfd,&read);
	FD_SET(0,&errors);
	FD_SET(nsfd,&errors);
	thetimeout.tv_sec=50;
	thetimeout.tv_usec=0;
	if(select(1,&read,NULL,&errors,&thetimeout)<0)
	{
		perror("Error: Select");
	    //return 1;
	}
	if(FD_ISSET(0,&read))
	{
		gets(buffer);
		send(nsfd,buffer,256,0);

	}
	if(FD_ISSET(nsfd,&read))
	{
		recv(nsfd,buffer,256,0);
	    //if(roll==0)
				//break;
		printf("Here is the reply recieved: %s\n",buffer );

	}
	close(nsfd);
	close(sfd);
}
