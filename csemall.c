#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
int main(int argc, char const *argv[])
{
	int c=0;
	struct sockaddr_in server,server1,server2,client4,client1,client2,client3;
	int csize4=sizeof(client4);
	int csize1=sizeof(client1);
	int csize2=sizeof(client2);
	int csize3=sizeof(client3);
	char buffer[256];
	char buffer1[256];
	char buffer2[256];
	char buffer3[256];
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
	int psfd=socket(AF_INET,SOCK_STREAM,0);
	if(psfd == -1)
	{
		printf("Could Not create t socket");

	}
	int msfd=socket(AF_INET,SOCK_STREAM,0);
	if(msfd == -1)
	{
		printf("Could Not create t socket");

	}
	puts("Sockets Created");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(9996);
	if(bind(sfd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("bind Failed1. Error");
		return 1;
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(9997);
	if(bind(tsfd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("bind Failed2. Error");
		return 1;
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(9998);
	if(bind(psfd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("bind Failed3. Error");
		return 1;
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(9999);
	if(bind(msfd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("bind Failed4. Error");
		return 1;
	}
	puts("binds done");
	listen(sfd,50);
	listen(tsfd,50);
	listen(psfd,50);
	listen(msfd,50);
	struct pollfd fds[4];
	fds[0].fd=sfd;
	fds[0].events=POLLIN;
	fds[1].fd=tsfd;
	fds[1].events=POLLIN;
	fds[2].fd=psfd;
	fds[2].events=POLLIN;
	fds[3].fd=msfd;
	fds[3].events=POLLIN;
	while(1)
	{
	int r=poll(fds,3,-1);
	if (fds[0].revents & POLLIN)
	{
		int nsfd=accept(sfd,(struct sockaddr *)&client1 , &csize1);
		if(nsfd<0)
		perror(" Error on accept ");
		printf("Connected \n");
		int r=recv(nsfd,buffer,255,0);
		switch(buffer[0])
		{
			case 'c':
			send(nsfd,"1",20,0);
			send(nsfd,"8888",20,0);
			case 's':
			send(nsfd,"2",20,0);
			send(nsfd,"8889",20,0);
			case 'e':
			send(nsfd,"3",20,0);
			send(nsfd,"8890",20,0);

		}
	}
	if (fds[1].revents & POLLIN)
	{
		int ntsfd=accept(sfd,(struct sockaddr *)&client2 , &csize2);
		if(ntsfd<0)
		perror(" Error on accept ");
		printf("Connected \n");
		int r=recv(ntsfd,buffer1,255,0);
		switch(buffer1[0])
		{
			case 'c':
			send(ntsfd,"1",20,0);
			send(ntsfd,"8888",20,0);
			case 's':
			send(ntsfd,"2",20,0);
			send(ntsfd,"8889",20,0);
			case 'e':
			send(ntsfd,"3",20,0);
			send(ntsfd,"8890",20,0);
		}
	}
	if (fds[2].revents & POLLIN)
	{
		int npsfd=accept(sfd,(struct sockaddr *)&client3 , &csize3);
		if(npsfd<0)
		perror(" Error on accept ");
		printf("Connected \n");
		int r=recv(npsfd,buffer2,255,0);
		switch(buffer2[0])
		{
			case 'c':
			send(npsfd,"1",20,0);
			send(npsfd,"8888",20,0);
			case 's':
			send(npsfd,"2",20,0);
			send(npsfd,"8889",20,0);
			case 'e':
			send(npsfd,"3",20,0);
			send(npsfd,"8890",20,0);
		}
	}
	if (fds[3].revents & POLLIN)
	{
		int nmsfd=accept(sfd,(struct sockaddr *)&client4 , &csize4);
		if(nmsfd<0)
		perror(" Error on accept ");
		printf("Connected \n");
		int r=recv(nmsfd,buffer3,255,0);
		switch(buffer3[0])
		{
			case 'c':
			recv(nmsfd,buffer3,255,0);
			if(buffer3[0]=='1')
				send(nmsfd,"Allow",256,0);
			else
				send(nmsfd,"Don't Allow",256,0);
			
			case 's':
			recv(nmsfd,buffer3,255,0);
			if(buffer3[0]=='2')
				send(nmsfd,"Allow",256,0);
			else
				send(nmsfd,"Don't Allow",256,0);
			case 'e':
			recv(nmsfd,buffer3,255,0);
			if(buffer3[0]=='3')
				send(nmsfd,"Allow",256,0);
			else
				send(nmsfd,"Don't Allow",256,0);
		}
	}
}


}