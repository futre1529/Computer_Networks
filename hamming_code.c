/**
    Hamming's code for single-bit error correction..
**/
#include<stdio.h>
#include<math.h>

int msg_len, num_parity, send_length;
int message[10000];
char msg[10000];

int  calcNumParity(int length)
{
    int par = 0, rhs = 1, lhs = length + par;
    while(rhs <= lhs)
    {
        //printf("rhs: %d\n", rhs);
        par += 1;
        rhs = rhs<<1;
        lhs += 1;
    }
    return par;
}

void formatMessage(char msg[], int msg_len)
{
    int l = 0, index = 1, curPar = 1;
    while(l < msg_len)
    {
        if(index != curPar)
        {
            message[index++] = msg[l++] - '0';
        }
        else
        {
            curPar = curPar<<1;
            index += 1;
        }
    }
    send_length = index - 1;
}

void insertParity(int num_parity)
{
    int k = 0, curPar = 1;
    while(k < num_parity)
    {
        printf("\nparity: %d\n", curPar);
        int l = curPar + 1, ans = 0;
        while(l <= send_length)
        {
            if((l & curPar) > 0)
            {
                printf("\tadd: %d", l);
                ans = ans^message[l];
            }
            l++;
        }
        message[curPar] = ans;
        k++;
        curPar = curPar<<1;
    }
}

int calcErrorBit(int message[])
{
    int bit = 0, curPar = 1;
    while(curPar <= send_length)
    {
        int ans = 0, l = curPar;
        while(l <= send_length)
        {
            if((l & curPar) > 0)
            {
                ans = ans^message[l];
            }
            l++;
        }
        if(ans & 1)     //if not of even parity
        {
            bit += curPar;
        }
        curPar = curPar<<1;
    }
    return bit;
}

int main()
{
    printf("Enter the length of the message:\n");
    scanf("%d", &msg_len);
    num_parity = calcNumParity(msg_len);
    printf("Enter the message in binary form\n");
    scanf("%s", msg);
    printf("The message requires %d parity bits\n", num_parity);
    int i;
    formatMessage(msg, msg_len);
    printf("Message to be sent is of length: %d\n", send_length);
    insertParity(num_parity);
    printf("\nMessage to be sent is : ");
    for(i = 1; i<=send_length; i++)
    {
        printf("%d", message[i]);
    }
    while(1)
    {
        printf("\nEnter another message of length %d with a single-bit error:\n", send_length);
        scanf("%s", msg);
        for(i=1; i<=send_length; i++)
        {
            message[i] = msg[i-1] - '0';
        }
        printf("\nThe bit with the error is: %d\n", calcErrorBit(message));
    }
}
