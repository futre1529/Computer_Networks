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
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd == -1)
	{
		printf("Could Not create socket");

	}
	puts("Socket Created");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(8890);
	int n;
	int len=sizeof(server);
	n=sendto(sfd,"How are you",256,0,(struct sockaddr *)&server, len);
		if(n<0)error(" Error in sending");

		//recieve
	n=recvfrom(sfd,buffer,256,0,(struct sockaddr *)&server, &len);
	if(n<0)error(" Error in recieving");
		printf("%s\n",buffer );
	c=fork();
	if(c>0)
	{
		//parent process
		while(1)
		{
			gets(buffer);
	        n=sendto(sfd,buffer,256,0,(struct sockaddr *)&server, len);
		      if(n<0)error(" Error in sending");

		}


	}
	else
	{
		while(1)
		{
			n=recvfrom(sfd,buffer,256,0,(struct sockaddr *)&server, &len);
	            if(n<0)error(" Error in recieving");
			
			printf("Here is the reply recieved: %s\n",buffer );

		}

	}
	//while(1)
	//{
		//send
		
	//}
		close(sfd);
		return 0;
}