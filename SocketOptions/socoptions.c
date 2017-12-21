#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/tcp.h>
#include<errno.h>

int sockfd, keepalive, sendbuf, rcvbuf, nodelay, status;
int optlen = sizeof(status);
struct linger linopt;

void get_options() {

    status = getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &keepalive, &optlen);
    if(status == 0)
        printf("\nSO_KEEPALIVE is set to %s", keepalive?"ON":"OFF");

    status = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuf, &optlen);
    if(status == 0)
        printf("\nSO_SNDBUF is set to %d", sendbuf);

    status = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &optlen);
    if(status == 0)
        printf("\nSO_RCVBUF is set to %d", rcvbuf);

    getsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &nodelay, &optlen);
    printf("\nTCP_NODELAY is set to %s", nodelay?"ON":"OFF");

    status = getsockopt(sockfd, SOL_SOCKET, SO_LINGER, &linopt, &optlen);
    if(status == 0)
        printf("\nSO_LINGER is set to %s with time to linger : %d", linopt.l_onoff?"ON":"OFF", linopt.l_linger);
}

int main() {

    printf("\ndefault socket oprions : ");
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    get_options();

    keepalive = !keepalive;
    status = setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &keepalive, optlen);

    nodelay = !nodelay;
    status = setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &nodelay, optlen);

    sendbuf = 1;
    status = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuf, optlen);

    rcvbuf = 1;
    status = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, optlen);

    optlen = sizeof(linopt);
    linopt.l_onoff = !linopt.l_onoff;
    linopt.l_linger = 10;
    status = setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &linopt, optlen);

    printf("\nAfter configuration, the socket options are: \n");
	
	get_options();
}