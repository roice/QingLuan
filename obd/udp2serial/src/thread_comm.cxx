/* Thread communication among threads
 * 
 * Author:  Bing Luo
 * Date:    2017-6-16
 * */

#include <pthread.h>
#include "thread_comm.h"

thread_comm_t thread_comm;

void thread_comm_init(void)
{
    pthread_mutex_init(&(thread_comm.lock_buffer), NULL);
    pthread_cond_init(&(thread_comm.cond_udp_data), NULL);
}

thread_comm_t* get_thread_comm (void)
{
    return &thread_comm;
}
