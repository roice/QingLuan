/*
 * Receive udp frames
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
/* */
#include "thread_comm.h"

#define MAX_PACKETSIZE			1024	// max size of packet (actual packet size is dynamic)
#define PORT_DATA  			    7070

char udp_buff[MAX_PACKETSIZE];

static int fd_sock;
static struct sockaddr_in si_me, si_other;
static pthread_t udp_receive_thread_handle;
static bool exit_udp_receive_thread = false;
static void* udp_receive_loop(void* exit);

bool udp_receive_init(void)
{
    struct ip_mreq mreq;

    // create UDP socket
    fd_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd_sock < 0)
        return false;
    
    memset((char *)&si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    si_me.sin_port = htons(PORT_DATA);

    if (bind(fd_sock, (struct sockaddr *) &si_me, sizeof(si_me)) < 0)
        return false;

    /* create thread to receive data */
    exit_udp_receive_thread = false;
    if (pthread_create(&udp_receive_thread_handle, NULL, &udp_receive_loop, (void*)&exit_udp_receive_thread) != 0)
        return false;

    return true;
}

static void* udp_receive_loop(void* exit)
{
    int slen = sizeof(si_other), cnt;

    thread_comm_t* tc = get_thread_comm();
    static int rcv_count = 0;

    while (!*((bool*)exit))
    {
        cnt = recvfrom(fd_sock, udp_buff, MAX_PACKETSIZE, 0, (struct sockaddr *) &si_other, (socklen_t *) &slen);
        if (cnt > 0) // normal receiving
        { 
            pthread_cond_signal(&(tc->cond_udp_data));
        }
        else if (cnt == 0) { // link is terminated
            break;
        }
        else    // timeout error
        {
            //printf("timeout\n");
        }
    }
}

void udp_receive_close(void)
{
    if (!exit_udp_receive_thread) // if still running
    {
        // exit udp receive thread
        exit_udp_receive_thread = true;
        pthread_join(udp_receive_thread_handle, NULL);
        // close socket
        close(fd_sock);
        printf("UDP receive thread terminated\n");
    }
}
