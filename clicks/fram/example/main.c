/*!
 * \file 
 * \brief Fram Click example
 * 
 * # Description
 * This app writing data to click memory.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device.
 * 
 * ## Application Task  
 * Writing data to click memory and displaying the read data via UART. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fram.h"

// ------------------------------------------------------------------ VARIABLES

static fram_t fram;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fram_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    fram_cfg_setup( &cfg );
    FRAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fram_init( &fram, &cfg );
    fram_erase_all( &fram );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    char wr_data[ 10 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
    char rd_data[ 20 ] = { 0 };
    uint8_t i = 0;

    log_printf( &logger, "Writing MikroE to  Fram memory, from address 0x0150: \r\n" );
    fram_write( &fram, 0x0150, &wr_data[ 0 ], 9 );
    Delay_ms( 1000 );
    log_printf( &logger, "Reading 9 bytes of Fram memory, from address 0x0150: \r\n" );
    fram_read( &fram, 0x0150, &rd_data[ 0 ], 9 );
    log_printf( &logger, "Data read: %s \r\n", rd_data );
    
    Delay_ms( 1000 );
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
