#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
    int sockfd, len;
    struct sockaddr_in client;
    char buff[50];

    printf("\nClient");
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    printf("\nSocket created");
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(6001);

    printf("\nEnter msg to send : ");
    scanf("%s", buff);
    len = sizeof(client);
    sendto(sockfd, buff, 50, 0, (struct sockaddr*) &client, len);
    recvfrom(sockfd, buff, 50, 0, (struct sockaddr*) &client, &len);
    printf("\nmessage received from server : %s", buff);
    close(sockfd);
    return 0;
}