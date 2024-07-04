/******************************************************************************
 * echo_client.c                                                               *
 *                                                                             *
 * Description: This file contains the C source code for an echo client.  The  *
 *              client connects to an arbitrary <host,port> and sends input    *
 *              from stdin.                                                    *
 *                                                                             *
 * Authors: Athula Balachandran <abalacha@cs.cmu.edu>,                         *
 *          Wolf Richter <wolf@cs.cmu.edu>                                     *
 *                                                                             *
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <fcntl.h>

#define ECHO_PORT 9999
#define BUF_SIZE 4096 * 50
struct addrinfo *servinfo; // will point to the results

int iniClient(char *server_ip, char *port)
{
    fprintf(stdout, "----------------Liso Client----------------\n");
    int status, clientSock;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if ((status = getaddrinfo(server_ip, port, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s \n", gai_strerror(status));
        return EXIT_FAILURE;
    }

    if ((clientSock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1)
    {
        fprintf(stderr, "Socket failed");
        return EXIT_FAILURE;
    }

    return clientSock;
}
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "usage: %s <server-ip> <port> <file>", argv[0]);
        return EXIT_FAILURE;
    }

    char buf[BUF_SIZE];
    int sock = 0;
    sock = iniClient(argv[1], argv[2]);
    if (connect(sock, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        fprintf(stderr, "Connect");
        return EXIT_FAILURE;
    }

    char msg[BUF_SIZE];
    int fd_in = open(argv[3], O_RDONLY); // 读文件
    // fgets(msg, BUF_SIZE, stdin);
    if (fd_in < 0)
    {
        printf("Failed to open the file\n");
        return 0;
    }
    read(fd_in, msg, BUF_SIZE);

    fprintf(stdout, "-------------Sending-----------\n%s", msg);
    int bytes_received = 0;
    send(sock, msg, strlen(msg), 0);
    while (1) //(bytes_received = recv(sock, buf, BUF_SIZE, 0)) > 1)
    {
        bytes_received = recv(sock, buf, BUF_SIZE, 0);
        if (bytes_received == 0)
            break;
        buf[bytes_received] = '\0';
        fprintf(stdout, "-------------Received-----------\n%s", buf);
    }
    printf("daole");
    freeaddrinfo(servinfo);
    close(sock);
    return EXIT_SUCCESS;
}
