#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

void error (const char *msg)
{
    printf("Error : %s\n", msg);
    exit(1);
}

/**
 * Creates a TCP socket.
 *
 * @return - The file descriptor of the created socket.
 */
int create_socket()
{
    // Create a TCP socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        error("Unable to create a socket");

    printf("Socket created\n");

    return fd;
}

/**
 * Creates a socket address structure for the given port number.
 *
 * @param port_num - The port number to use.
 * @return - A sockaddr_in structure representing the server address.
 */
struct sockaddr_in create_address(int port_num)
{
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port_num);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    printf("Address created\n");

    return serveraddr;
}

/**
 * Binds a socket to the given address.
 *
 * @param fd - The file descriptor of the socket.
 * @param serveraddr - The sockaddr_in structure representing the server address.
 */
 void bind_address_to_socket(int fd, struct sockaddr_in serveraddr)
 {
    int ret = bind(fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (ret == -1)
        error("Unable to bind socket to address\n");

    printf("Bind successful\n");
 }

/**
 * Listens for incoming connections on a socket.
 *
 * @param fd - The file descriptor of the socket.
 */
void listen_for_incoming_connection(int fd)
{
    if (listen(fd, SOMAXCONN) < 0)
        error("Unable to listen for incoming connection\n");

    printf("Listen successful\n");
} 

/**
 * Entry point of the server program.
 */
int main()
{
    int fd = create_socket();

    // Create a bind server address to the socket
    struct sockaddr_in serveraddr = create_address(23456);
    bind_address_to_socket(fd, serveraddr);

    listen_for_incoming_connection(fd);
    // Main loop to handle client connections
    while (1) {

    }
}