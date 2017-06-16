/*
 * Send udp frames to the UAV
 *
 * Written by Roice, Luo
 *
 * Date: 2017.06.16 create this file
 */

#ifndef UDP_UAV_SEND_H
#define UDP_UAV_SEND_H

bool udp_send_init(const char* local_address);
void udp_send_str(const char*);
void udp_send_close(void);

#endif
