#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

//Connect to the server with ./TCPClient 127.0.0.1 8080
//Define Macros to maninpulate sockets
#define ISVALIDSOCKET(s) ((s) >= 0) // Check and return 1 if the socket is valid
#define CLOSESOCKET(s) close(s)     // Close a socket
#define SOCKET int                  // initialize the socket
#define GETSOCKETERRNO() (errno)    //Manage errors try the command "$ man errno" to learn more

int main(int argc, char *argv[])
{
    // argc contains the number of argument values available in the execution command
    // The actual values themselves are stored in argv[]
    if (argc < 3)
    {
        fprintf(stderr, "usage: tcp_client hostname port\n");
        return 1;
    }
    printf("Configuring remote address...\n");
    struct addrinfo hints;            //similar to how we called getaddrinfo() in the server part
    memset(&hints, 0, sizeof(hints)); // whereas this time, we want it to configure a remote address
    hints.ai_socktype = SOCK_STREAM;  //we want a TCP connection
    struct addrinfo *peer_address;
    //the hostname and port are two arguments passed directly in from the command line
    // If everything goes well, then our remote address is in the peer_address variable.
    if (getaddrinfo(argv[1], argv[2], &hints, &peer_address))
    {
        fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO()); //else manage error
        return 1;
    }
    printf("Creating socket...\n");
    SOCKET socket_peer; //This call to socket() is done in exactly the same way as it was in the server
    socket_peer = socket(peer_address->ai_family, peer_address->ai_socktype, peer_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_peer))
    {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    printf("Connecting...\n");
    //connect() takes three arguments—the socket, the remote address, and the remote address length.
    if (connect(socket_peer, peer_address->ai_addr, peer_address->ai_addrlen))
    {
        fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(peer_address); //free the memory for peer_address.
    printf("To send data, enter text followed by enter.\n");
    while (1)
    {                 //We begin our loop and set up the call to select()
        fd_set reads; //to store our socket set.
        FD_SET(socket_peer, &reads);
        FD_SET(0, &reads); //We then zero the "reads". Use "man 2 FD_ZERO to learn more"
        //we use select() to monitor for terminal input.
        if (select(socket_peer + 1, &reads, 0, 0, NULL) < 0)
        {
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }
        if (FD_ISSET(socket_peer, &reads))
        { //check to see whether our socket is set in reads.
            char read[4096];
            int bytes_received = recv(socket_peer, read, 4096, 0); //call recv() to read the new data.
            if (bytes_received < 1)
            {
                printf("Connection closed by peer.\n");
                break;
            }
            printf("Received (%d bytes): %.*s", bytes_received, bytes_received, read);
        }
        if (FD_ISSET(0, &reads))
        { //send request
            char read[4096];
            if (!fgets(read, 4096, stdin))
                break; //includes the newline character from the input.
            printf("Sending: %s", read);
            int bytes_sent = send(socket_peer, read, strlen(read), 0);
            printf("Sent %d bytes.\n", bytes_sent);
        }
    } //end while(1)
    printf("Closing socket...\n");
    CLOSESOCKET(socket_peer);
    printf("Finished.\n");
    return 0;
} // end of main