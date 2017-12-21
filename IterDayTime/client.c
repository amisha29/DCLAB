#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>

int main()
{
    int sockfd;
    struct sockaddr_in client;
    char buff[50];
    clock_t start, end;

    printf("\nClient");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("\nSocket created");
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(5001);

    if(connect(sockfd, (struct sockaddr*) &client, sizeof(client)) < 0)
        printf("\nerror in connection");
    printf("\nsocket connected");
   
   start = clock();
   send(sockfd, "send time", 50, 0);
   recv(sockfd, buff, 50, 0);
   end = clock();
   printf("\ncurrent time : %s", buff);
   printf("\nround trip time : %f", ((double)end-start)/CLOCKS_PER_SEC);
   close(sockfd);
   return 0;
}