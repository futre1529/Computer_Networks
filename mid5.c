#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
void* runner(void *arg)
{
		int sfdt=*((int*)arg); 
		struct sockaddr_in client;
		int csize=sizeof(client);
		int nsfd=accept(sfdt,(struct sockaddr *)&client , &csize);
		if(nsfd<0)
			perror(" Error on accept ");
		puts("connected \n");

}
int main(int argc, char const *argv[])
{
	int c=0;
	int pid=0;
	struct sockaddr_in server;
	char buffer[256];
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
	listen(sfd,50);
	int i;
	for(i=0;i<5;i++)
	{
		pid=fork();
		if(pid==0)
			break;
	}
	if(pid==0)
	{
		pthread_t pid[5];
		for(i=0;i<5;i++)
		{
			pthread_create(&pid[i],NULL,runner,(void*)sfd);

		}
		//pthread_creat(&); 
		


	}
	while(1)
	{

	}
	return 0;
}