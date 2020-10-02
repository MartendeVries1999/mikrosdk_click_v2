/*!
 * \file 
 * \brief HallCurrent3 Click example
 * 
 * # Description
 * The example starts off with the logger and click modules and then starts measuring and
 * displaying current values.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * Reads and displays current values every second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hallcurrent3.h"

// ------------------------------------------------------------------ VARIABLES

static hallcurrent3_t hallcurrent3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    hallcurrent3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hallcurrent3_cfg_setup( &cfg );
    HALLCURRENT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent3_init( &hallcurrent3, &cfg );
}

void application_task ( )
{
    float current_data;

    current_data = hallcurrent3_get_current( &hallcurrent3 );
    log_printf( &logger, "Current : %f mA\r\n" );

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
