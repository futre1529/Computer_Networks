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
	server.sin_port=htons(9999);
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
	/*recv(nsfd,buffer,255,0);
	printf("Here is the message recieved: %s\n",buffer );
	send(nsfd,"I got you message",18,0);*/
	printf("Connected \n");
	c=fork();
	if(c>0)
	{
		//parent process
		while(1)
		{
			gets(buffer);
	        int roll1=send(nsfd,buffer,255,0);
	        if(roll1==0)
	        	break;

		}


	}
	else
	{
		while(1)
		{
			int roll=recv(nsfd,buffer,255,0);
			
			printf("Here is the reply recieved: %s\n",buffer );

		}

	}
	close(nsfd);
	close(sfd);

	return 0;
}