#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_LEN 100

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
 * Receives a message from a client into the provided buffer.
 *
 * @param client_fd - The file descriptor of the client socket.
 * @param buffer - A pointer to the buffer where the received message will be stored.
 * @return - The number of bytes received, or -1 if an error occurs.
 */
char receive_client_message(int client_fd, char* buffer)
{
    // Receive the message from the client
    ssize_t bytes_received = recv(client_fd, buffer, BUFFER_LEN, 0);

    // Check if the message was successfully received
    if (bytes_received < 0)
        error("Unable to receive client message\n");

    return bytes_received;
}

/**
 * Sends a message to a client.
 *
 * @param client_fd - The file descriptor of the client socket.
 */
void send_message_to_client(int client_fd, char msg[])
{
    ssize_t bytes_sent = send(client_fd, msg, strlen(msg), 0);

    // Check if the message was successfuly sent
    if (bytes_sent < 0)
        error("Unable to send message to client\n");
}

/**
 * Reverses a given string in place.
 *
 * @param str - The string to be reversed;
 * @return - The reversed string.
 */
char* reverse_string(char str[])
{
    int length = strlen(str);

    // Iterate through the first half of the string
    for (int i = 0; i < length / 2; i++) {
        // Swap characters from the beginning and end
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }

    return str;
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
        int client_fd = accept_client_connection(fd);

        // Fork a child process
        pid_t pid = fork();

        if (pid == -1) { // Fork failed
            close(client_fd);
        }
        else if (pid == 0) { // Child process
            close(fd); // Close listening socket in child process

            // Retrieve the client's request
            char buffer[BUFFER_LEN];
            receive_client_message(client_fd, buffer);

            char * reversed_buffer = reverse_string(buffer);
        }
    }
}