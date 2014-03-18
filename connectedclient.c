#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include<poll.h>
int main(int argc, char *argv[])
{
	int sockfd = 0, n = 0;
	char recvBuff[1024];
	struct sockaddr_in serv_addr;  

	memset(recvBuff,'0',sizeof(recvBuff));
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	memset(&serv_addr,'0',sizeof(serv_addr)); 

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(5024); 

	inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr);
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	perror("zhb\n");
	struct pollfd p1[2];
	p1[0].fd=0;
	p1[0].events=POLLIN;        	
	p1[1].fd=sockfd;
	p1[1].events=POLLIN;        	

	while(1)
    	{
			int x=poll(p1,2,4);
			if(POLLIN & p1[0].revents)
			{
				scanf("%s",&recvBuff);
				send(sockfd,recvBuff,sizeof(recvBuff),0);
        	}
			if(POLLIN & p1[1].revents)
			{
				int n=recv(sockfd,recvBuff,sizeof(recvBuff),0);
        	    recvBuff[n]=0;
		
           		printf("%s\n",recvBuff);
			}
    	}	
	return 0;
}
