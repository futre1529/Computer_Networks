#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <poll.h>
struct node{
       int vis;
       int count;
       /*node()
       {
             vis=0;
       }*/
};
int n,**a,**b,k=0;
int l=0;
struct node *g;
void dft(int j)
{
     g[j].vis=1;
     g[j].count=++k;
     int i;
     for(i=0;i<n;i++)
     {
     if(g[i].vis==0 && a[j][i]==1)
     {
        dft(i);}
    }
}     
void dft1(int j)
{
    b[l][j]=1;
     //cout<<j<<" ";
     g[j].vis=0;
     int i;
     for(i=0;i<n;i++)
     if(g[i].vis==1 && a[j][i]==1)
     {dft1(i);
      break;}
}
void strong()
{
  g=(struct node*) malloc(n*sizeof(struct node));
  int i;
  for(i=0;i<n;i++)
  {
    g[i].vis=0;
  }
  //printf("abcd\n");
  while(k<n-1)
    {
              //printf("abcd\n");
               int x=k;
               for(i=0;i<n;i++)
               {//printf("abcd\n");
                       if(g[i].vis==0)
                       {
                          dft(i);
                          break;
                       }
               }
             //  printf("abcd\n");
               for(i=0;i<n;i++)
               if(g[i].vis==1)
               if(g[i].count>x)
               g[i].count=k-g[i].count+x+1;
    }
    while(1)
    {
               int x=17,y;
               for(i=0;i<n;i++)
               if(g[i].count<=x && g[i].vis==1)
               {
                                y=i;
                                x=g[i].count;
               }
               if(x!=17)
               {
                       
                       dft1(y);
                       l++;
               }
               else break;
    }
}     

int main(int argc, char *argv[])
{
    int sfd=0;
    struct sockaddr_in serv_addr,client; 
    char Buff[1025];
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr,'0',sizeof(serv_addr));
    memset(Buff,'0',sizeof(Buff)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5024); 
    if(bind(sfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
      perror("dyg\n");
    listen(sfd,10);
    scanf("%d",&n);
    int i,j,nsfd[n];
    a=(int **) malloc(n*sizeof(int**));
    b=(int **) malloc(n*sizeof(int**));
    for(i=0;i<n;i++)
        a[i]=(int *)malloc(n*sizeof(int *));
    for(i=0;i<n;i++)
        b[i]=(int *)malloc(n*sizeof(int *));
    for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    {
        a[i][j]=0;
        b[i][j]=0;
    }
    
    
    while(1)
    {
        int *length;
        for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);         
            
        }
        strong();
        //printf("abcd\n");
        printf("\n\n\n\n");
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                printf("%d ",b[i][j]);
            }
            printf("\n");
        }
        for(i=0;i<n;i++)
        {     
            nsfd[i]=accept(sfd,0,0);
            printf("connected\n"); 
        }
        break;
    }
   // printf("l is %d\n",l);
    struct pollfd p1[10];
    for(i=0;i<n;i++)
    {
        p1[i].fd=nsfd[i];
        p1[i].events=POLLIN;
    }  
    while(1)
    {
        int v=poll(p1,n,0);
        for(i=0;i<n;i++)
        if(POLLIN & p1[i].revents)
        {
            printf("poll\n");
            int x=recv(nsfd[i],Buff,sizeof(Buff),0);
            Buff[x]=0;
        
            printf("Data recieved from %d %s\n",i,Buff);;
            int data;
            for(j=0;j<l;j++)
            {
                if(b[j][i]==1)
                    data=j;
            }
            for(j=0;j<n;j++)
            {
                if(j!=i)
                if(b[data][j]==1)
                {
                    printf(" Send to %d ,",j);
                    send(nsfd[j],Buff,sizeof(Buff),0);
                }
            }
            printf("\n");
        }
    }
}

