/*!
 * @file main.c
 * @brief Hvac Click example
 *
 * # Description
 * This is an example that demonstrates the use of the HVAC Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - I2C, 
 * SCD40: perform factory reset, serial number, features, product type platform type, 
 * product version and
 * SPS30: perform start measurement mode, also write log.
 *
 * ## Application Task
 * This is an example which demonstrates the use of HVAC Click board.
 * HVAC Click board can be used to measure : 
 * Concentration of CO2 in air,
 * Temperature ( degree Celsius ),
 * Relative Humidity ( % ),
 * Mass Concentration of PM1.0, PM2.5, PM4.0, PM10 and
 * Number Concentration of PM0.5, PM1.0, PM2.5, PM4.0 and PM10.
 * All data logs write on USB uart changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "hvac.h"

static hvac_t hvac;
static log_t logger;
measuremen_data_t hvac_data;
feature_data_t version_data;
mass_and_num_cnt_data_t sps30_data;
uint16_t ser_num[ 3 ];

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hvac_cfg_t hvac_cfg;  /**< Click config object. */

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
    hvac_cfg_setup( &hvac_cfg );
    HVAC_MAP_MIKROBUS( hvac_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hvac_init( &hvac, &hvac_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 1000 );
    hvac_scd40_send_cmd( &hvac, HVAC_PERFORM_FACTORY_RESET );
    log_printf( &logger, "  Perform Factory Reset   \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 2000 );

    hvac_scd40_get_serial_number ( &hvac, ser_num );
    log_printf( &logger, "   SCD40 - Serial Number : %.4d-%.4d-%.4d \r\n", 
                ( uint16_t ) ser_num[ 0 ], ( uint16_t ) ser_num[ 1 ], ( uint16_t ) ser_num[ 2 ] );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
    hvac_scd40_get_feature_set_version( &hvac, &version_data );
    log_printf( &logger, "     SCD40 - Features     \r\n" );
    log_printf( &logger, " Product Type    : %d \r\n", ( uint16_t ) version_data.product_type );
    log_printf( &logger, " Platform Type   : %d \r\n", ( uint16_t ) version_data.platform_type );
    log_printf( &logger, " Product Version : %d.%d \r\n", 
                ( uint16_t ) version_data.product_major_version, 
                ( uint16_t ) version_data.product_minor_version );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
    
    hvac_sps30_start_measurement ( &hvac );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    hvac_scd40_send_cmd( &hvac, HVAC_MEASURE_SINGLE_SHOT );
    Delay_ms( 5000 );
    
    hvac_scd40_read_measurement( &hvac, &hvac_data );
    Delay_ms( 100 );

    log_printf( &logger, " CO2 Concent = %d \r\n ", hvac_data.co2_concent );

    log_printf( &logger, " Temperature = %.2f C \r\n", hvac_data.temperature );

    log_printf( &logger, " R. Humidity = %.2f %% \r\n", hvac_data.r_humidity );
    log_printf( &logger, "- - - - - - - - - - - - -  \r\n" );
        
    while ( HVAC_SPS30_NEW_DATA_IS_READY != hvac_sps30_get_ready_flag( &hvac ) );
    
    
    log_printf( &logger, "   Mass Concentration :   \r\n" );
    hvac_sps30_read_measured_data( &hvac, &sps30_data );
    Delay_ms( 100 );

    log_printf( &logger, " PM 1.0 = %.2f ug/m3 \r\n", sps30_data.mass_pm_1_0 );
    log_printf( &logger, " PM 2.5 = %.2f ug/m3 \r\n", sps30_data.mass_pm_2_5 );
    log_printf( &logger, " PM 4.0 = %.2f ug/m3 \r\n", sps30_data.mass_pm_4_0 );
    log_printf( &logger, " PM 10  = %.2f ug/m3 \r\n", sps30_data.mass_pm_10 );
    log_printf( &logger, "-   -   -   -   -   -   - \r\n" );

    log_printf( &logger, "  Number Concentration :  \r\n" );
    log_printf( &logger, " PM 0.5 = %.2f n/cm3 \r\n", sps30_data.num_pm_0_5 );
    log_printf( &logger, " PM 1.0 = %.2f n/cm3 \r\n", sps30_data.num_pm_1_0 );
    log_printf( &logger, " PM 2.5 = %.2f n/cm3 \r\n", sps30_data.num_pm_2_5 );
    log_printf( &logger, " PM 4.0 = %.2f n/cm3 \r\n", sps30_data.num_pm_4_0 );
    log_printf( &logger, " PM 10  = %.2f n/cm3 \r\n", sps30_data.num_pm_10 );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 2000 );
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
