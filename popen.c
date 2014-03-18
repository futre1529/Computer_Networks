#include <stdio>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, struct char* argv[])
{
	FILE *read_fp;
	FILE *write_fp;
	char buffer[256];
	int chars_read;
	int read,i;
	char buffer1[20];
	memset(buffer1,'\0',sizeof(buffer));
	buffer1[0]=".";
	buffer1[1]="/";
	memcpy(buffer1+2,argv[1],strlen(argv[1]));
	memset(buffer1,'\0',sizeof(buffer));
	read_fp=popen(buffer1,"r");
	char_read=fread(buffer,sizeof(char),256,read_fp);
	pclose(read_fp);
	memset(buffer1,'\0',sizeof(buffer));
	buffer1[0]=".";
	buffer1[1]="/";
	memcpy(buffer1+2,argv[2],strlen(argv[1]));
	write_fp=popen(buffer1,"w");
	fwrite(buffer,sizeof(char),256,write_fp);
	pclose(write_fp);
	memset(buffer1,'\0',sizeof(buffer));
	buffer1[0]=".";
	buffer1[1]="/";
	memcpy(buffer1+2,argv[2],strlen(argv[1]));
	read_fp=popen(buffer1,"r");
	char_read=fread(buffer,sizeof(char),256,read_fp);
	pclose(read_fp);
	memset(buffer1,'\0',sizeof(buffer));
	buffer1[0]=".";
	buffer1[1]="/";
	memcpy(buffer1+2,argv[3],strlen(argv[1]));
	write_fp=popen(buffer1,"w");
	fwrite(buffer,sizeof(char),256,write_fp);
	pclose(write_fp);
	memset(buffer1,'\0',sizeof(buffer));
	buffer1[0]=".";
	buffer1[1]="/";
	memcpy(buffer1+2,argv[3],strlen(argv[1]));
	read_fp=popen(buffer1,"r");
	char_read=fread(buffer,sizeof(char),256,read_fp);
	pclose(read_fp);
	printf("%s\n",buffer );
	return 0;


} 