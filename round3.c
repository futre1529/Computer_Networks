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
#define BUFLEN 100

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

int recv_fd(int sockfd) {
    struct msghdr msg;
    struct iovec iov[1];
    ssize_t n;
    char a;

    // align address
    union {
    struct cmsghdr cm;
    char control[CMSG_SPACE(sizeof(int))];
    } control_un;

    struct cmsghdr *cmptr;

    // link to cmsghdr
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);

    // dont worry about socket address for stream
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    // to hold data
    iov[0].iov_base = &a;
    iov[0].iov_len = 1;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    
    // read from socket
    if ((n = recvmsg(sockfd, &msg, 0)) <= 0) {
    return(n);
    }

    // retrieve file descriptor from control header
    if ((cmptr = CMSG_FIRSTHDR(&msg)) != NULL &&
    cmptr->cmsg_len == CMSG_LEN(sizeof(int))) {
    if (cmptr->cmsg_level == SOL_SOCKET && 
        cmptr->cmsg_type == SCM_RIGHTS) {
        return(*((int *)CMSG_DATA(cmptr)));
    }
    }
    return(-1);
}

int main(int argc, char * argv[]) {
    int sockfd,sockfd1, fd,  n;
    struct sockaddr_un addr;
    char buf[BUFLEN];

    if (argc != 2) {
    fprintf(stderr,"USAGE: %s pathname filename.\n", argv[0]);
    fprintf(stderr, "pathname: unix domain socket pathname\n");
    //fprintf(stderr, "pathname: unix domain socket pathname\n");
    exit(-1);
    }

    if ((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, argv[1], sizeof(addr.sun_path)-1);
    addr.sun_path[sizeof(addr.sun_path)-1] = '\0';

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("connect");
    exit(1);
    }
    printf(" connected to round2 \n" );
    //---------------------------
  /*  if ((sockfd1 = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
    }

    unlink(argv[2]);  // trying to remove the file 

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, argv[2], sizeof(addr.sun_path)-1);
    addr.sun_path[sizeof(addr.sun_path)-1] = '\0';

    if (bind(sockfd1, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(1);
    }

  
    if (listen(sockfd1, 5) < 0) {
    perror("listen");
    exit(1);
    }
    //int i;
    
    int rec_sock1 = accept(sockfd1, NULL, NULL);
*/
    //---------------------------
    struct sockaddr_in scoreserver;
    //char buffer[256];
    int sfd1=socket(AF_INET,SOCK_STREAM,0);
    if(sfd1 == -1)
    {
        printf("Could Not create socket");

    }
    puts("Socket Created");
    scoreserver.sin_family=AF_INET;
    scoreserver.sin_addr.s_addr=inet_addr("127.0.0.1");
    scoreserver.sin_port=htons(9999);
    if(connect(sfd1,(struct sockaddr *)&scoreserver, sizeof(scoreserver))<0)
    {
        perror(" Connection Failed");
        return 1;
    }
    puts(" Connected \n");

    //----------------------------

    fd = recv_fd(sockfd);
    send(fd,"\n Now connected to round 3",255,0);
    send(sfd1," Score sent of round3",255,0);
    //n = send_fd(rec_sock1, fd);
    //fprintf(stderr, "sent: %d\n", n);
    return 0;
}
