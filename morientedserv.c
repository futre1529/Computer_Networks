#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
int main(int argc,char const *argv[])
{
	int c=0;
	struct sockaddr_in server,client;
	char buffer[256];
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	int usfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd == -1)
	{
		printf("Could Not create tcp socket");

	}
	if(usfd == -1)
	{
		printf("Could Not create udp socket");

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
	struct pollfd fds[2];
	fds[0].fd=sfd;
	fds[0].events=POLLIN;
	fds[1].fd=usfd;
	fds[1].events=POLLIN;
	for(;;)
	{
		int r=poll(fds,2,-1);
		if(r<0)
			perror("error using poll");
		else
		{
			if(fds[0].revents & POLLIN)
			{
				int nsfd=accept(sfd,(struct sockaddr *)&client,&clien);
				if(nsfd<0) perror(" Error on accept ");
				c=fork();
				if(c==0)
				{
					//child process
					int r=recv(nsfd,buffer,256,0);
					if(r<0) perror(" Error in recieving ");
					printf(" The client has sent:%s \n ",buffer);

					r=send(nsfd,"I have got the messgae",256,0);
					if(r<0)perror("Error in sending");	
			
				}

	 		}
			if(fds[1].revents & POLLIN)
			{
				int n;
				n=recvfrom(usfd,buffer,255,0,(struct sockaddr *)&client, &clien);
				if(n<0)error(" Error in recieving");

				//send
				n=sendto(usfd,"Got your message",255,0,(struct sockaddr *)&client , clien);
				if(n<0) error("error in sending");

				printf("Here is the reply recieved: %s\n",buffer );

			}
		}

		
	}
}