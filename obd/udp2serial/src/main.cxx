/* Main file
 *
 * Author:      Roice Luo 
 * Date:        2017.06.16
 */

#include <cmath>
#include <string.h>
/* Linux */
#include <pthread.h>
/* */
#include "config.h"
#include "udp_receive.h"
#include "thread_comm.h"

int main(int argc, char **argv)
{
    /* initialize settings */
    config_restore();

    /* get configs */
    config_t* configs = get_configs();

    // get thread communication handles
    thread_comm_t* tc = get_thread_comm();

    /* initialize UDP */
    udp_receive_init();

    /* loop */
    while (true)
    {
        pthread_cond_wait(&(tc->cond_udp_data), &(tc->lock_buffer));

        pthread_mutex_unlock(&(tc->lock_buffer));
    }

    /* terminate UDP */
    udp_receive_close();

    /* save settings */
    config_save();
    return 0;
}
