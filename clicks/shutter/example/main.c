/*!
 * @file main.c
 * @brief Shutter Click Example.
 *
 * # Description
 * This example demonstrates the use of Shutter click board by taking pictures
 * with and without auto focus function.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Swithes ON the auto focus function and triggers the shutter to take the picture, then
 * swithes OFF the auto focus and triggers the shutter. The shutter is triggered every 13 seconds
 * approximately. All data is being logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "shutter.h"

static shutter_t shutter;   /**< Shutter Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    shutter_cfg_t shutter_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    shutter_cfg_setup( &shutter_cfg );
    SHUTTER_MAP_MIKROBUS( shutter_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == shutter_init( &shutter, &shutter_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Take picture with auto focus\r\n\n" );
    shutter_take_picture ( &shutter, SHUTTER_STATE_ON );
    Delay_ms( 10000 );
    log_printf( &logger, " Take picture without auto focus\r\n\n" );
    shutter_take_picture ( &shutter, SHUTTER_STATE_OFF );
    Delay_ms( 10000 );
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
