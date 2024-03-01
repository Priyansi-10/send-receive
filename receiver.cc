#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sock, rval;
    struct addrinfo hints, *results, *ptr;
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_received;

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <-4 or -6>" << std::endl;
        return 1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = (strcmp(argv[2], "-6") == 0) ? AF_INET6 : AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rval = getaddrinfo(NULL, argv[1], &hints, &results)) != 0) {
        std::cerr << "Error getting address info: " << gai_strerror(rval) << std::endl;
        return 2;
    }

    for (ptr = results; ptr != NULL; ptr = ptr->ai_next) {
        if ((sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) != -1) {
            if (bind(sock, ptr->ai_addr, ptr->ai_addrlen) == 0) {
                break;  // socket and bind successful
            }
            close(sock);
        }
    }

    if (ptr == NULL) {
        std::cerr << "Failed to bind socket" << std::endl;
        return 3;
    }

    freeaddrinfo(results);

    std::cout << "Receiver is ready to receive messages." << std::endl;

    while (true) {
        struct sockaddr_storage sender_addr;
        socklen_t sender_addr_len = sizeof(sender_addr);

        bytes_received = recvfrom(sock, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&sender_addr, &sender_addr_len);

        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            std::cout << "Received: " << buffer << std::endl;
            sendto(sock, buffer, bytes_received, 0, (struct sockaddr *)&sender_addr, sender_addr_len);
        }
    }

    close(sock);

    return 0;
}