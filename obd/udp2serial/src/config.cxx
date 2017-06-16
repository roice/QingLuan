/*
 * Configuration file
 *
 *
 * Author: Roice (LUO Bing)
 * Date: 2017-06-16 create this file
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
        settings.serial_port_path = pt.get<std::string>("Serial.Port_Path");
    }
}

/* Save settings to configuration file */
void config_save(void)
{
    /* prepare to write configuration files */
    boost::property_tree::ptree pt;
    // arena size
    pt.put("Serial.Port_Path", settings.serial_port_path);
    /* write */
    boost::property_tree::ini_parser::write_ini("settings.ini", pt);
}

/* init settings */
void config_init(void)
{
    settings.serial_port_path = "/dev/ttyUSB0";
}

/* get pointer of config data */
config_t* get_configs(void)
{
    return &settings;
}
