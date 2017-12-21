#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
    int sockfd, recv_len;
    struct sockaddr_in client, server;
    char buff[50];
    pid_t pid;

    printf("\nServer");
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    printf("\nSocket created");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(6001);

    if(bind(sockfd, (struct sockaddr*) &server, sizeof(server)) < 0)
        printf("\nerror in binding");
    printf("\nBinding done");

    while(1) {
        int len = sizeof(client);
        recv_len = recvfrom(sockfd, buff, 50, 0,  (struct sockaddr*) &client, &len);
        if(recv_len != -1) {
            printf("\nCLient Request accepted");
            if((pid = fork()) == 0) {
                printf("\nchild process created");
                printf("\nmsg from client : %s", buff);
                sendto(sockfd, buff, 50, 0, (struct sockaddr* ) &client, len);
                exit(0);
            }
        }
    }
    close(sockfd);

    return 0;
}