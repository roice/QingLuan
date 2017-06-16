/*
 * Configuration file of GPS Emulator
 *
 * The implementations of the classes, functions and data are written in 
 * file config.cxx.
 *
 * Author: Roice (LUO Bing)
 * Date: 2017-06-16 create this file
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>

/* configuration struct */
typedef struct {
    /* Serial port to output data */
    std::string serial_port_path;
} config_t;

void config_restore(void);
void config_save(void);
void config_init(void);
// get pointer of configuration data
config_t* get_configs(void);

#endif
