#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc,char const *argv[])
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
	server.sin_port=htons(8890);
	if(bind(sfd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("bind Failed. Error");
		return 1;
	}
	puts("binds done");
	listen(sfd,50);
	int clien=sizeof(client);
	int nsfd;
	for(;;)
	{
		nsfd=accept(sfd,(struct sockaddr *)&client, &clien);
		c=fork();
		if(c>0)
		{
			//parent process


		}
		else
		{
			//child process
			int r=recv(nsfd,buffer,256,0);
			if(r<0) perror(" Error in recieving ");
			printf(" The client has sent:%s \n ",buffer);

			r=send(nsfd,"I have got the messgae",256,0);
			if(r<0)perror("Error in sending");	

		}
	}
	close(sfd);
	close(nsfd);
	return 0;
}
