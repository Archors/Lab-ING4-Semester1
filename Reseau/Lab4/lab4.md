# Lab3: Computer Networks

[Subject](Reseau-lab3-subject.pdf)

* Running a file : `gcc -o labserver labserver.c`
* Then use `./execName` to run the server.

#### 1-  Objective

After this lab, the students will have skills using Wireshark and then add the tool to their CV.
1. Wireshark packet capture
2. HTTP get/response
3. DNS

#### 2-  Getting started

1. Is your browser running HTTP version 1.0 or 1.1? What version of HTTP is the server running?

My browser is running in 1.1
```
54	6.530792117	192.168.1.73	145.14.144.65	HTTP	576	GET /HTTP-wireshark-file1.html HTTP/1.1
```

2. What languages (if any) does your browser indicate that it can accept to the server?
```

```

3. What is the IP address of your computer? Of the 000webhostapp.com server?


4. What is the status code returned from the server to your browser?


5. When (hour and date) was the HTML file that you are retrieving has been received?


6. How many bytes of content are being returned to your browser?


7. By inspecting the raw data in the packet content window, do you see any headers within the data that are not displayed in the packet-listing window? If so, name one.

```
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
#include <fcntl.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)

int main()
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);
    printf("Creating socket...\n");
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family,
                           bind_address->ai_socktype,
                           bind_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_listen))
    {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    //Binding
    printf("Binding socket to local address...\n");
    if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen))
    {
        fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    int file;
    char buf[BUFSIZ];
    int size;

    while (1)
    {
        //Listening
        listen(socket_listen, 0);
        //Acceptance
        SOCKET socket_client = accept(socket_listen, NULL, NULL);
        if (!ISVALIDSOCKET(socket_client))
        {
            fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }
        size = read(socket_client, buf, BUFSIZ);
        write(1, buf, size);
        if ((file = open("index.html", O_RDONLY)) == -1)
        {
            printf("No existing file name `index.html`\n");
            return (1);
        }
        size = sprintf(buf, "HTTP/1.1 200 OK\n\n");
        size += read(file, buf + size, BUFSIZ);
        write(1, buf, size);
        write(socket_client, buf, size);
        close(socket_client);
        close(file);
    }
}
```
