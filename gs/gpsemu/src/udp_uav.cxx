/*
 * Send udp frames to the UAV
 *
 * Written by Roice, Luo
 *
 * Date: 2017.06.16 create this file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
/* socket */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/* thread */
#include <pthread.h>

#define MAX_PACKETSIZE			4096	// max size of packet (actual packet size is dynamic)
#define PORT_DATA  			    7070

static int fd_sock;
static struct sockaddr_in addr;

bool udp_send_init(const char* local_address)
{
    // create UDP socket
    fd_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd_sock < 0)
        return false;
    
    memset((char *)&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(local_address);
    addr.sin_port = htons(PORT_DATA);

    return true;
}

void udp_send_str(const char* buf)
{
    if (sendto(fd_sock, buf, strlen(buf)>1024?1024:strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        printf("Send command to UAV via UDP failed.\n");
}

void udp_send_close(void)
{
    // close socket
    close(fd_sock);
    printf("UAV UDP send terminated\n");
}
