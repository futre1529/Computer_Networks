#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
	int c=0;
	struct sockaddr_in server,client[2],clienttemp;
	int clientem=sizeof(clienttemp);
	int m=2;
	int clien[2];
	char buffer[256];
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
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
	int j;
	for(j=0;j<m;j++)
		clien[j]=sizeof(client[j]);

	int n;

	
		//recieve
		for(j=0;j<m;j++)
		{
			n=recvfrom(sfd,buffer,255,0,(struct sockaddr *)&client[j], &clien[j]);
			if(n<0)perror(" Error in recieving");

			//send
			n=sendto(sfd,"GYou are now connected to server",255,0,(struct sockaddr *)&client[j] , clien[j]);
			if(n<0) perror("error in sending");
		}
		
		while(1)
		{
			n=recvfrom(sfd,buffer,255,0,(struct sockaddr *)&clienttemp, &clientem);
			if(n<0)perror(" Error in recieving");

			for(j=0;j<m;j++)
			{

			n=sendto(sfd,buffer,255,0,(struct sockaddr *)&client[j] , clien[j]);
			if(n<0) perror("error in sending");

			}

		}


		//printf("Here is the reply recieved: %s\n",buffer );

	
	close(sfd);
	return 0;
}