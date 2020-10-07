#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <netinet/in.h>
#include "../Common/BigNum.h"

int main() {

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_address.sin_port = htons(1234);

    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(server_sockfd, (struct sockaddr *) &server_address, sizeof(server_address));

    listen(server_sockfd, 5);

    while (true) {
        int client_sockfd = accept(server_sockfd, nullptr, nullptr);
        int msgLen;
        recv(client_sockfd, &msgLen, 1, 0);
        std::string s;
        s.resize(msgLen);
        recv(client_sockfd, const_cast<char*>(s.c_str()), msgLen, 0);
        BigNum ch(s);

        if (s.length() >= 2 && ch.isDivide()) {
            std::cout << "Received sum is OK: " << s << std::endl;
        } else {
            std::cout << "Sum not supports conditions: " << s << std::endl;
        }
        shutdown(client_sockfd, SHUT_RDWR);
        close(client_sockfd);
    }
}
