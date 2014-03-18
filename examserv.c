#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
int maxo(int a,int b,int c,int d)
{
	int m=a;
	if(b>m)
		m=b;
	if(c>m)
		m=c;
	if(d>m)
		m=d;
	return m;
}
int main(int argc,char const *argv[])
{
	int c=0;
	//char buffer[256];
	struct sockaddr_in server1,server2,server3,server4,client1,client2,client3,client4;
	char buffer[256];
	int sfd1=socket(AF_INET,SOCK_STREAM,0);
	if(sfd1 == -1)
	{
		printf("Could Not create tcp socket");

	}
	int sfd2=socket(AF_INET,SOCK_STREAM,0);
	if(sfd2 == -1)
	{
		printf("Could Not create tcp socket");

	}
	int sfd3=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd3 == -1)
	{
		printf("Could Not create udp socket");

	}
	int sfd4=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd4 == -1)
	{
		printf("Could Not create udp socket");

	}
	
	puts("Socket Created");
	server1.sin_family=AF_INET;
	server1.sin_addr.s_addr=INADDR_ANY;
	server1.sin_port=htons(8886);

	server2.sin_family=AF_INET;
	server2.sin_addr.s_addr=INADDR_ANY;
	server2.sin_port=htons(8887);

	server3.sin_family=AF_INET;
	server3.sin_addr.s_addr=INADDR_ANY;
	server3.sin_port=htons(8888);

	server4.sin_family=AF_INET;
	server4.sin_addr.s_addr=INADDR_ANY;
	server4.sin_port=htons(8889);
	
	if(bind(sfd1,(struct sockaddr *)&server1,sizeof(server1))<0)
	{
		perror("bind Failed. Error");
		return 1;
	}
	//puts("binds done");
	if(bind(sfd2,(struct sockaddr *)&server2,sizeof(server2))<0)
	{
		perror("bind Failed. Error");
		return 1;
	}
	if(bind(sfd3,(struct sockaddr *)&server3,sizeof(server2))<0)
	{
		perror("bind Failed. Error");
		return 1;
	}
	if(bind(sfd4,(struct sockaddr *)&server4,sizeof(server2))<0)
	{
		perror("bind Failed. Error");
		return 1;
	}
	int clien1=sizeof(client1);
	int clien2=sizeof(client2);
	int clien3=sizeof(client3);
	int clien4=sizeof(client4);
	puts("binds done");
	listen(sfd1,50);
	listen(sfd2,50);
	fd_set read;
	struct timeval thetimeout;
	FD_ZERO(&read);
	FD_SET(sfd1,&read);
	FD_SET(sfd2,&read);
	FD_SET(sfd3,&read);
	FD_SET(sfd4,&read);
	thetimeout.tv_sec=50;
	thetimeout.tv_usec=0;
	while(1)
	{
		int max=maxo(sfd1,sfd2,sfd3,sfd4);
		if(select(max,&read,NULL,NULL,&thetimeout)<0)
		{
			perror("Error: Select");
	    	//return 1;
		}
		if(FD_ISSET(sfd1,&read))
		{
			int nsfd1=accept(sfd1,(struct sockaddr *)&client1, &clien1);
			c=fork();
			if(c>0)
			{
			//parent process
				close(nsfd1);	

			}
			else
			{
			//child process
			
			int r=send(nsfd1,"Connnected to service 1",256,0);
			if(r<0)perror("Error in sending");	

			}

		}
		if(FD_ISSET(sfd2,&read))
		{
			int nsfd2=accept(sfd2,(struct sockaddr *)&client2, &clien2);
			c=fork();
			if(c>0)
			{
			//parent process
				close(nsfd2);

			}
			else
			{
			//child process
			

			int r=send(nsfd2,"Connnected to service 1",256,0);
			if(r<0)perror("Error in sending");	

			}

		}
		if(FD_ISSET(sfd3,&read))
		{
			int n=recvfrom(sfd3,buffer,255,0,(struct sockaddr *)&client3, &clien3);
			if(n<0)perror(" Error in recieving");
			n=sendto(sfd3,"GYou are now connected to service3",255,0,(struct sockaddr *)&client3 , clien3);
			if(n<0) perror("error in sending");
		
			

		}
		if(FD_ISSET(sfd4,&read))
		{
			int n=recvfrom(sfd4,buffer,255,0,(struct sockaddr *)&client4, &clien4);
			if(n<0)perror(" Error in recieving");
		    n=sendto(sfd4,"GYou are now connected to service3",255,0,(struct sockaddr *)&client4 , clien4);
			if(n<0) perror("error in sending");

		}
	FD_SET(sfd1,&read);
	FD_SET(sfd2,&read);
	FD_SET(sfd3,&read);
	FD_SET(sfd4,&read);
	}
}



















