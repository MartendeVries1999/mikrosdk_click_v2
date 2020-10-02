/*!
 * \file 
 * \brief Magneticlinear Click example
 * 
 * # Description
 * This app reads magnetics linear data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device.
 * 
 * ## Application Task  
 * Reads Magnetics linear data and this data logs to USBUART every 200ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "magneticlinear.h"

// ------------------------------------------------------------------ VARIABLES

static magneticlinear_t magneticlinear;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneticlinear_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    magneticlinear_cfg_setup( &cfg );
    MAGNETICLINEAR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneticlinear_init( &magneticlinear, &cfg );
}

void application_task ( void )
{
    uint16_t magnetic_data;
    
    magnetic_data = magneticlinear_read_data( &magneticlinear );

    log_printf( &logger, " Magnetic Linear data : %u\r\n", magnetic_data );
    log_printf( &logger, "_______________________\r\n", magnetic_data );
    Delay_ms( 200 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
