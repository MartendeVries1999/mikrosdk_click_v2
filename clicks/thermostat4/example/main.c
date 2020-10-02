/*!
 * \file 
 * \brief Thermostat4 Click example
 * 
 * # Description
 * Thermostat 4 Click reads alert on the warm and hot channel, using standard SPI communication.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init, Relay test and
 * sets hysteresis on the WARM channel ( channel B ), after thet starts uploading new data.
 * 
 * ## Application Task  
 *  Reads Alert on the WARM and HOT channel.
 * 
 * *note:* 
 * The user has the option of adjusting the hysteresis for channel B via the SPI module 
 * while for channel A it is adjusted via the potentiometer.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermostat4.h"

// ------------------------------------------------------------------ VARIABLES

static thermostat4_t thermostat4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermostat4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    thermostat4_cfg_setup( &cfg );
    THERMOSTAT4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermostat4_init( &thermostat4, &cfg );

    log_printf( &logger, ">> R-E-L-A-Y  O-N <<\r\n" );
    thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    Delay_ms( 1000 );
    log_printf( &logger, ">> R-E-L-A-Y  O-F-F <<\r\n" );
    thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_OFF );
    Delay_ms( 500 );
    
    thermostat4_set_warm_hysteresis( &thermostat4, 0 );
    thermostat4_new_cfg_upload( &thermostat4 );
}

void application_task ( void )
{
    if ( thermostat4_hot_alert_state( &thermostat4 ) == THERMOSTAT4_HOT_ALERT )
    {
        log_printf( &logger, ">> H-O-T  A-L-E-R-T <<\r\n" );
        thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    }

    if ( thermostat4_warm_alert_state( &thermostat4 ) == THERMOSTAT4_WARM_ALERT )
    {
        log_printf( &logger, ">> W-A-R-M  A-L-E-R-T <<\r\n" );
        thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    }

    log_printf( &logger, ">> T-E-M-P-E-R-A-T-U-R-E  O-K <<\r\n" );
    thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_OFF );
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
