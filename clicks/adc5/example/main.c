/*!
 * \file 
 * \brief ADC5 Click example
 * 
 * # Description
 * This example showcases how to initialize and configure the logger and click modules and 
 * how to read and display ADC voltage data from the click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules. 
 * 
 * ## Application Task  
 * This function reads and displays ADC voltage data every second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adc5.h"

// ------------------------------------------------------------------ VARIABLES

static adc5_t adc5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    adc5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms( 100 );

    //  Click initialization.

    adc5_cfg_setup( &cfg );
    ADC5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc5_init( &adc5, &cfg );
}

void application_task ( )
{
    uint16_t adc_value;
    
    adc_value = adc5_get_voltage( &adc5 );
    log_printf( &logger, " * Voltage: %d mV * \r\n", adc_value );
    Delay_1sec( );
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
