#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include <bits/socket.h>

int main()
{
    int Ser_Socket,Cli_Sock;
    struct sockaddr_in Ser_addr,Cli_addr;
    // int Cli_Sock2;
    // struct sockaddr_in Cli_addr2;

    Ser_Socket = socket(AF_INET,SOCK_STREAM,0);
    if (Ser_Socket == -1)
    {
        printf("Socket Creation Failed\n");
        // exit(0);
    }

    Ser_addr.sin_family = AF_INET;
    Ser_addr.sin_addr.s_addr = INADDR_ANY;
    Ser_addr.sin_port = htons(1234);

    if (bind(Ser_Socket,(struct sockaddr*)&Ser_addr,sizeof(Ser_addr)) == -1)
    {
        printf("Binding Failed\n");
        close(Ser_Socket);
        // exit(0);
    }

    printf("Socket Create Success\n");

    listen(Ser_Socket,5);

    socklen_t Cli_len = sizeof(Cli_addr);
    // socklen_t Cli_len2 = sizeof(Cli_addr2);
    Cli_Sock = accept(Ser_Socket,(struct sockaddr*)&Cli_addr,&Cli_len);
    // Cli_Sock2 = accept(Ser_Socket,(struct sockaddr*)&Cli_addr2,&Cli_len2);
    if (Cli_Sock == -1)
    {
        printf("accept Failed\n");
        close(Ser_Socket);
        // exit(0);
    } else{
        printf("accept Success\n");
    }

    char buffer[100];
    while (1)
    {
        //读取数据
        memset(buffer, 0, sizeof(buffer));
        ssize_t n = read(Cli_Sock,buffer,100);
        if (n > 0)
        {
            printf("receive:%s\n",buffer);
        } else{
            printf("read failed\n");
            break;
        }
        
        //写入数据
        // char send_buffer[] = {"Hello Client"};
        // write(Cli_Sock,send_buffer,sizeof(send_buffer));

    }

    close(Cli_Sock);
    // close(Cli_Sock2);
    
    
}