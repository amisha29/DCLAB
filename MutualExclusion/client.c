#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;
    struct sockaddr_in client;
    char buff[50];

    printf("\nClient");

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(5000);

    while(1) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        printf("\nSocket created");
        if(connect(sockfd, (struct sockaddr*) &client, sizeof(client)) < 0)
            printf("\nerror in connection");
        printf("\nsocket connected");

        recv(sockfd, buff, 50, 0);
        if(strcmp(buff, "LOCKED") == 0) {
            printf("Could not attain Mutual Exclusion\nStatus:%s\n", buff );
            printf("Going to sleep\n");
            sleep(5);
        }
        else {
            printf("Mutual Exlusion\nStatus: %s\n", buff );
            printf("Enter message\n");
            scanf("%s", buff);
            send(sockfd, buff, 50, 0);
            recv(sockfd, buff, 50, 0);
            printf("Message from server: %s\n", buff);
            break;
        }
    }
    close(sockfd);
    return 0;
}