/*
 * Configuration file of GPS Emulator
 *
 * This file contains configuration data and methods of GPS Emulator
 * The declarations of the classes, functions and data are written in 
 * file config.h, which is included by main.cxx
 *
 * Author: Roice (LUO Bing)
 * Date: 2017-06-15 create this file
 */

#include "config.h"
// for .ini file reading
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/ini_parser.hpp>

/* Configuration data */
static config_t settings;

/* Restore settings from configuration file */
void config_restore(void)
{
    char name[256];

    /* check if there exists a config file */
    if(access("settings.ini", 0))
    {// config file not exist
        config_init(); // load default config
        // create new config file
        FILE *fp;
        fp = fopen("settings.ini", "w+");
        fclose(fp);
    }
    else // config file exist
    {
        /* read configuration files */
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini("settings.ini", pt);
        /* restore configs */
        settings.addr_netcard_mocap = pt.get<std::string>("IP_address.NetCard_Motion_Capture");
        settings.addr_uav = pt.get<std::string>("IP_address.UAV");
    }
}

/* Save settings to configuration file */
void config_save(void)
{
    /* prepare to write configuration files */
    boost::property_tree::ptree pt;
    // arena size
    pt.put("IP_address.NetCard_Motion_Capture", settings.addr_netcard_mocap);
    pt.put("IP_address.UAV", settings.addr_uav);
    /* write */
    boost::property_tree::ini_parser::write_ini("settings.ini", pt);
}

/* init settings */
void config_init(void)
{
    settings.addr_netcard_mocap = "192.168.20.102";
    settings.addr_uav = "192.168.30.101";
}

/* get pointer of config data */
config_t* get_configs(void)
{
    return &settings;
}
