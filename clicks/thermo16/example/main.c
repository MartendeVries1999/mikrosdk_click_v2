/*!
 * \file 
 * \brief Thermo16 Click example
 * 
 * # Description
 * This demo-app shows the temperature measurement procedure using Thermo 16 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * Reads ambient temperature data and this data logs to USBUART every 1500ms.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo16.h"

// ------------------------------------------------------------------ VARIABLES

static thermo16_t thermo16;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo16_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    
    //  Click initialization.

    thermo16_cfg_setup( &cfg );
    THERMO16_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo16_init( &thermo16, &cfg );
}

void application_task ( void )
{
    float temp;
    
    //  Task implementation.
    
    temp = thermo16_get_temperature ( &thermo16, THERMO16_TEMP_IN_CELSIUS );
    log_printf( &logger, "** Temperature : %f C \r\n", temp );
    
    Delay_ms( 1500 );
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
