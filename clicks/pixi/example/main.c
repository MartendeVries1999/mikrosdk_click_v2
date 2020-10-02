/*!
 * \file 
 * \brief Pixi Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the Pixi click moduel. The click
 * features Maxim Integrated's versatile, proprietary PIXI™ technology - the industry's first
 * configurable 20-channel mixed-signal data converter. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click and logger modules. After the initial setup
 * a device id check is performed which will stop the module if the check fails. Additional con-
 * figurating is done in the default_cfg(...) function.
 * 
 * ## Application Task
 * This function sets the output signal on port 0 to different values every second. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pixi.h"

// ------------------------------------------------------------------ VARIABLES

static pixi_t pixi;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    pixi_cfg_t cfg;
    uint32_t res;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms( 100 );

    //  Click initialization.

    pixi_cfg_setup( &cfg );
    PIXI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pixi_init( &pixi, &cfg );

    //  Device ID check.

    pixi_read_reg( &pixi, PIXI_REG_DEVICE_ID, &res );
    if ( res != 1060 )
    {
        log_printf( &logger, "ERROR : WRONG DEVICE ID!\r\n" );
        for( ; ; );
    }
    else
    {
        log_printf( &logger, "Driver Init - DONE!\r\n" );
    }

    //  Default configuration.

    pixi_default_cfg( &pixi );
}

void application_task ( )
{
    pixi_write_reg( &pixi, PIXI_REG_GPO_DATA, 1 );
    Delay_ms( 1000 );
    pixi_write_reg( &pixi, PIXI_REG_GPO_DATA, 0 );
    Delay_ms( 1000 );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
