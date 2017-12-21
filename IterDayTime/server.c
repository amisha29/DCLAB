#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>

int main()
{
    int sockfd, cs;
    struct sockaddr_in client, server;
    char buff[50];
    time_t currtime;

    printf("\nServer");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("\nSocket created");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5001);

    if(bind(sockfd, (struct sockaddr*) &server, sizeof(server)) < 0)
        printf("\nerror in binding");
    printf("\nBinding done");

    listen(sockfd, 5);
    printf("\nlistening");

    while(1) {
        int len = sizeof(client);
        cs = accept(sockfd, (struct sockaddr*) &client, &len);
        if(cs < 0)
            printf("\nerror in accepting");
        printf("\nCLient Request accepted");
        recv(cs, buff, 50, 0);
        printf("\nmsg from client : %s\n", buff);
        sleep(2);
        time(&currtime);
        send(cs, ctime(&currtime), 50, 0);
        close(cs);
        exit(0);
    
        close(cs);
    }
    close(sockfd);
    return 0;
}