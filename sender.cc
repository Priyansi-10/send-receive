#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <string>

int main(int argc, char *argv[]) {
    int sock, rval;
    struct addrinfo hints, *results, *ptr;

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <destination_host> <destination_port> <-4 or -6>" << std::endl;
        return 1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = (strcmp(argv[3], "-6") == 0) ? AF_INET6 : AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    if ((rval = getaddrinfo(argv[1], argv[2], &hints, &results)) != 0) {
        std::cerr << "Error getting the destination address: " << gai_strerror(rval) << std::endl;
        return 2;
    }

    for (ptr = results; ptr != NULL; ptr = ptr->ai_next) {
        if ((sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) != -1) {
            break;  // socket successful, no need to search further
        }
    }

    if (ptr == NULL) {
        std::cerr << "Failed to open socket" << std::endl;
        return 3;
    }

    freeaddrinfo(results);

    std::string message;
    std::cout << "Enter a message: ";
    std::getline(std::cin, message);

    sendto(sock, message.c_str(), message.size(), 0, ptr->ai_addr, ptr->ai_addrlen);

    char buffer[1024];
    ssize_t bytes_received;

    bytes_received = recvfrom(sock, buffer, 1024, 0, nullptr, nullptr);

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        std::cout << "Received: " << buffer << std::endl;
    }

    close(sock);

    return 0;
}