#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

typedef struct thread_data {
    int clientid;
    int status;
}thread_data;

void *handler (void *t_data) {
    thread_data* data = (thread_data*) t_data;
    int clientid = data->clientid;
    char buff[50];
    char unlockMessage[50] = "UNLOCKED";
    char lockMessage[50] = "LOCKED";

    if(!data->status) {
        send(clientid, unlockMessage, 50, 0);
        data->status = 1;
        printf("\nMUTEX locked\nconnecgted to client");
        recv(clientid, buff, 50, 0);
        printf("\nmsg received from client : %s", buff);
        printf("\nenter msg to send : ");
        scanf("%s", buff);
        send(clientid, buff, 50, 0);
        close(clientid);
        data->status=0;
        printf("\nMUTEX unlocked\ndisconnecgted from client\n");
    }
    else {
        send(clientid, lockMessage, 50, 0);
        close(clientid);
    }
}

int main()
{
    int sockfd, cs;
    struct sockaddr_in client, server;
    char buff[50];
    pthread_t thread;
    int lock = 0;

    printf("\nServer");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("\nSocket created");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5000);

    if(bind(sockfd, (struct sockaddr*) &server, sizeof(server)) < 0)
        printf("\nerror in binding");
    printf("\nBinding done");

    listen(sockfd, 5);
    printf("\nlistening");

    thread_data data;
    data.status = lock;

    while(1) {
        int len = sizeof(client);
        cs = accept(sockfd, (struct sockaddr*) &client, &len);
        if(cs < 0)
            printf("\nerror in accepting");
        data.clientid = cs;
        pthread_create(&thread, NULL, handler, (void *)&data);
    }
    close(sockfd);
    pthread_exit(NULL);
    return 0;
}