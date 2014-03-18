#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#define MAXBUF 100

int send_fd(int sockfd, int fd_to_send) {
    struct msghdr msg;
    struct iovec iov[1];

    // align address
    union {
	struct cmsghdr cm;
	char control[CMSG_SPACE(sizeof(int))];
    } control_un;

    struct cmsghdr *cmptr;

    // pointing to cmsghdr
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);

    // insert file descriptor to send
    cmptr = CMSG_FIRSTHDR(&msg);
    cmptr->cmsg_len = CMSG_LEN(sizeof(int));
    cmptr->cmsg_level = SOL_SOCKET;
    cmptr->cmsg_type = SCM_RIGHTS; // for sending descriptors
    *((int *)CMSG_DATA(cmptr)) = fd_to_send;

    printf("fd = %d\n", fd_to_send);

    // using stream, we do not need to worry about address
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    // we need to send at least one byte in data
    iov[0].iov_base = "";
    iov[0].iov_len = 1;
    
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    
    return(sendmsg(sockfd, &msg, 0));
    
}

int main(int argc, char *argv[]) {
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
	server.sin_port=htons(8889);
	if(bind(sfd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("bind Failed. Error");
		return 1;
	}
	puts("binds done");
	
//-----------------------------------------------------------
    int sockfd, rec_sock;
    struct sockaddr_un addr;

    if (argc != 2) {
	fprintf(stderr, "%s pathname\n", argv[0]);
	exit(1);
    }

    if ((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
	perror("socket");
	exit(1);
    }

    unlink(argv[1]);  /* trying to remove the file */

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, argv[1], sizeof(addr.sun_path)-1);
    addr.sun_path[sizeof(addr.sun_path)-1] = '\0';

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
	perror("bind");
	exit(1);
    }

  
    if (listen(sockfd, 5) < 0) {
	perror("listen");
	exit(1);
    }
    rec_sock = accept(sockfd, NULL, NULL);


	/*if (fork() == 0) { // Child 
	    close(sockfd);
	    process_request(rec_sock);
	    close(rec_sock);
	    exit(0);
	} 
	else { // Parent   
	    close(rec_sock); 
	} */
//---------------------------------------------------------
		
    listen(sfd,50);
	int csize=sizeof(client);
	int nsfd=accept(sfd,(struct sockaddr *)&client , &csize);
	if(nsfd<0)
		perror(" Error on accept ");
	printf("Connected \n");
	send(nsfd,"Connected to main server",18,0);
	int n = send_fd(rec_sock, nsfd);
    fprintf(stderr, "sent: %d\n", n);
    return 0;
}