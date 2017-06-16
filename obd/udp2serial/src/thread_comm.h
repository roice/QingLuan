/* Thread communication among threads
 * 
 * Author:  Bing Luo
 * Date:    2017-06-16
 * */

#ifndef THREAD_COMM_H
#define THREAD_COMM_H

typedef struct {
    pthread_mutex_t lock_buffer;
    pthread_cond_t cond_udp_data; // cond for sync of udp_receive.cxx and main.cxx
} thread_comm_t;

void thread_comm_init(void);
thread_comm_t* get_thread_comm(void);

#endif
