#include "server.h"

/*
 * A simple server that reponds on port 8080
 * with message
 *
 * Either with webbrowser localhost:8080
 * or telnet localhost 8080
 */

/*
 * SERVER
 * socket()
 * bind()
 * listen()
 * accept()
 * recv()
 * send()
 * close()
 */

/*
 * CLIENT
 * socket()
 * connect()
 * send/recv()
 */

#define PORT 8080

int main(int argc, char const* argv[])
{
    int server_fd, new_socket; 
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };

    char* message = "Request received\n";
    int bytes_read = 0;

    Initsock(&server_fd, PORT, &address);

    //while(1){
    //    Accept(&new_socket, &server_fd, &address, addrlen);
    //    bytes_read = read(new_socket, buffer, 1024);

    //    printf("bytes read: %d\n", bytes_read);
    //    puts(buffer);


    //    send(new_socket, message, strlen(message), 0);
    //    memset(buffer, 0, sizeof(buffer));

    //    // closing the connected socket
    //    close(new_socket);
    //}

    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
