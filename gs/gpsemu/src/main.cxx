/* Main file of GPS Emulator
 *
 * Author:      Roice Luo 
 * Date:        2017.06.15 
 */

#include <stdio.h>
#include <cmath>
#include <string.h>
/* Linux Network */
#include <ifaddrs.h>
#include <sys/socket.h>
#include <arpa/inet.h>
/* GPSEmu */
#include "config.h"
#include "packet_client.h"
#include "rtklib.h"
#include "udp_uav.h"

#define DEG2RAD     (M_PI/180.0)

// local lat/lon/h of ENU
double llh_local[3] = {37.*DEG2RAD, 118.*DEG2RAD, 100.};

// NMEA GPGGA buffer
unsigned char buff[1024];

int main(int argc, char **argv)
{
    /* initialize settings */
    config_restore();

    /* save settings */
    config_save();

    /* get configs */
    config_t* configs = get_configs();

    /* initialize motion capture packet decoder */
    mocap_client_init(configs->addr_netcard_mocap.c_str());

    /* initialize UDP */
    udp_send_init(configs->addr_uav.c_str());

    /* loop */
    MocapData_t* mocap_data = mocap_get_data();
    struct timespec req, rem;
    req.tv_sec = 0;
    req.tv_nsec = 100000000L; // 100 ms
    double enu[3];
    sol_t sol = {0};
    double ecef_local[3] = {0};
    double enu_local[3] = {0};
    pos2ecef(llh_local, ecef_local);
    ecef2enu(llh_local, ecef_local, enu_local);
    while (true)
    {
        // retrieve position (horizontal)
        enu[0] = mocap_data->robot[0].enu[0] + enu_local[0];
        enu[1] = mocap_data->robot[0].enu[1] + enu_local[1];
        enu[2] = mocap_data->robot[0].enu[2] + enu_local[2];

        printf("Local ENU: %2.2f, %2.2f, %2.2f\n", enu[0], enu[1], enu[2]);

        // convert it to GPS coordinate
        memset(sol.rr, 0, sizeof(sol.rr));
        enu2ecef(llh_local, enu, sol.rr);

        printf("ECEF: %.2f, %.2f, %.2f\n", sol.rr[0], sol.rr[1], sol.rr[2]);

        // implement NMEA packets (GPGGA)
        sol.time = utc2gpst(timeget());
        sol.stat = SOLQ_FIX;
        sol.ns = 6; // cleanflight requires >5 satellites to enable GPS_HOLD
        outnmea_gga(buff, &sol);

        // send it to the UAV
        udp_send_str(reinterpret_cast<const char*>(buff));

        // 10 Hz
        nanosleep(&req, &rem); // 100 ms
    }

    /* terminate UDP */
    udp_send_close();

    /* terminate motion capture packet decoder */
    mocap_client_close();
 
    return 0;
}
