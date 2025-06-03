#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/fcntl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <net/pfvar.h>
#include <err.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u_int32_t
read_address(const char *s)
{
    int a, b, c, d;
    sscanf(s, "%i.%i.%i.%i",    &a, &b,    &c, &d);
    return htonl(a << 24 | b    << 16 |    c << 8 | d);
    }

void
print_address(u_int32_t a)
{
    a = ntohl(a);
    printf("%d.%d.%d.%d", a >> 24 & 255, a >> 16 & 255, a >> 8 & 255, a & 255);
}

int
main(int argc, char *argv[])
{
    struct pfioc_natlook nl;
    int dev;

    if (argc != 5) {
        printf("%s <gwy addr> <gwy port> <ext addr> <ext port>\n", argv[0]);
        return 1;
    }

    dev = open("/dev/pf", O_RDWR);
    if (dev == -1)
        err(1, "open(\"/dev/pf\") failed");

    memset(&nl, 0, sizeof(struct pfioc_natlook));
    nl.saddr.v4.s_addr = read_address(argv[1]);
    nl.sport = htons(atoi(argv[2]));
    nl.daddr.v4.s_addr = read_address(argv[3]);
    nl.dport = htons(atoi(argv[4]));
    nl.af = AF_INET;
    nl.proto = IPPROTO_TCP;
    nl.direction = PF_OUT;

    if (ioctl(dev, DIOCNATLOOK, &nl) != 0) {
        if (errno == ENOENT) {
            nl.direction = PF_IN; // required to redirect local packets
            printf("PF_IN\n");
            if (ioctl(dev, DIOCNATLOOK, &nl) != 0) {
                err(1, "DIOCNATLOOK");
            }
        }
        else {
            err(1, "DIOCNATLOOK");
        }
    }

    printf("internal host ");
    print_address(nl.rsaddr.v4.s_addr);
    printf(":%u\n", ntohs(nl.rsport));
    print_address(nl.rdaddr.v4.s_addr);
    printf(":%u\n", ntohs(nl.rdport));
    return 0;
}
