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
	struct pollfd fds[2];//={{0,POLLIN},{nsfd,POLLIN}};
	fds[0].fd=0;
	fds[0].events=POLLIN;
	fds[1].fd=nsfd;
	fds[1].events=POLLIN;
	while(1)
	{
	int r=poll(fds,2,-1);
	if(r<0)
		perror(" Error using poll \n");
	else
	{
		if(fds[0].revents & POLLIN)
		{
			gets(buffer);
			send(nsfd,buffer,256,0);

		}
		if(fds[1].revents & POLLIN)
		{
			recv(nsfd,buffer1,256,0);
			printf("Reply : %s\n",buffer1 );

		}
	}
    }

	close(nsfd);
	close(sfd);

	return 0;
}