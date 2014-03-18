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
	server.sin_port=htons(8889);
	int n;
	int len=sizeof(server);
	n=sendto(sfd,"Serve me 3",256,0,(struct sockaddr *)&server, len);
		if(n<0)error(" Error in sending");

		//recieve
	n=recvfrom(sfd,buffer,256,0,(struct sockaddr *)&server, &len);
	if(n<0)error(" Error in recieving");
		printf("%s\n",buffer );
	close(sfd);
	return 0;
}