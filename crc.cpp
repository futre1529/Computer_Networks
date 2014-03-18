#include <iostream>
#include <cstring>
using namespace std;
char message[1000];
char tempmsg[1000];
char divi[1000];
char rmsg[1000];
int main()
{
	cout<<"Enter divisor : ";
	cin>>divi;
	char* di=divi;
	while(di[0]=='0') di++;
	cout<<"Enter message : ";
	cin>>message;
	for(int i=1;i<strlen(di);i++)
	{
		int l=strlen(message);
		message[l]='0';
		message[l+1]='\0';
	}
	strcpy(tempmsg,message);
	for(int i=0;i<=(strlen(tempmsg)-strlen(di));i++)
	{
		if(tempmsg[i]=='0') continue;
		for(int j=0;j<strlen(di);j++)
		{
			if(tempmsg[i+j]==di[j]) tempmsg[i+j]='0';
			else tempmsg[i+j]='1';
		}
	}
	int l=strlen(message);
	int lt=strlen(tempmsg);
	for(int i=1;i<(strlen(di));i++) {message[l-i]=tempmsg[lt-i];}
	cout<<"Sent message  : "<<message<<endl;
	return 0;
}