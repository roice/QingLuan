/*
 * Receive udp frames
 *
 * Written by Roice, Luo
 *
 * Date: 2017.06.16 create this file
 */

#ifndef UDP_RECEIVE_H
#define UDP_RECEIVE_H

extern char udp_buff[];

bool udp_receive_init(void);
void udp_receive_close(void);

#endif
