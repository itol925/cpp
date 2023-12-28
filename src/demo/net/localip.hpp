#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace demo {
    namespace ip {
        int get_local_ip() {
            struct ifaddrs *ifap, *ifa;
            struct sockaddr_in6 *sa_v6;
            char addrbuf_v6[INET6_ADDRSTRLEN];

            struct sockaddr_in *sa;
            char addrbuf[INET_ADDRSTRLEN];

            if (getifaddrs(&ifap) != 0) {
                perror("getifaddrs");
                exit(EXIT_FAILURE);
            }

            for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
                if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET6) {
                    sa_v6 = (struct sockaddr_in6 *) ifa->ifa_addr;
                    inet_ntop(AF_INET6, &(sa_v6->sin6_addr), addrbuf_v6, INET6_ADDRSTRLEN);
                    printf("Interface v6: %s\tAddress: %s\n", ifa->ifa_name, addrbuf_v6);
                }

                if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
                    sa = (struct sockaddr_in *) ifa->ifa_addr;
                    inet_ntop(AF_INET, &(sa->sin_addr), addrbuf, INET_ADDRSTRLEN);
                    printf("Interface v4: %s\tAddress: %s\n", ifa->ifa_name, addrbuf);
                }
            }

            freeifaddrs(ifap);
            return 0;
        }
    }
}
