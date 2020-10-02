/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for CAN FD4 Click driver.
 *
 * \addtogroup canfd4 CAN FD4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CANFD4_H
#define CANFD4_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define CANFD4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CANFD4_RETVAL  uint8_t

#define CANFD4_OK           0x00
#define CANFD4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define CANFD4_NEMA_GPGGA 1
#define CANFD4_NEMA_GPGLL 3
#define CANFD4_NEMA_GPGGA_NUM_ELEMENT 15
#define CANFD4_NEMA_GPGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define CANFD4_GPGGA_TIME                      1 
#define CANFD4_GPGGA_LATITUDE                  2
#define CANFD4_GPGGA_LATITUDE_SIDE             3
#define CANFD4_GPGGA_LONGITUDE                 4
#define CANFD4_GPGGA_LONGITUDE_SIDE            5
#define CANFD4_GPGGA_QUALITY_INDICATOR         6
#define CANFD4_GPGGA_NUMBER_OF_SATELLITES      7
#define CANFD4_GPGGA_H_DILUTION_OF_POS         8
#define CANFD4_GPGGA_ALTITUDE                  9
#define CANFD4_GPGGA_ALTITUDE_UNIT             10
#define CANFD4_GPGGA_GEOIDAL_SEPARATION        11
#define CANFD4_GPGGA_GEOIDAL_SEPARATION_UNIT   12
#define CANFD4_GPGGA_TIME_SINCE_LAST_DGPS      13
#define CANFD4_GPGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define CANFD4_GPGLL_LATITUDE                  1
#define CANFD4_GPGLL_LATITUDE_SIDE             2
#define CANFD4_GPGLL_LONGITUDE                 3
#define CANFD4_GPGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define CANFD4_ERROR_COMMAND_OR_ELEMENT   0xFF
#define CANFD4_ERROR_START_OR_END_COMMAND 0x8F
#define CANFD4_ERROR_NEXT_ELEMENT         0x4F
#define CANFD4_ERROR_CURRENT_ELEMENT      0x2F
#define CANFD4_NO_ERROR                   0x00
/** \} */

/**
 * \defgroup canfd4_mode CAN FD 4 Mode 
 * \{
 */
#define CANFD4_NORMAL_MODE                0
#define CANFD4_STANDBY_MODE               1
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t cs;

    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} canfd4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t cs;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} canfd4_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t canfd4_error_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void canfd4_cfg_setup ( canfd4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CANFD4_RETVAL canfd4_init ( canfd4_t *ctx, canfd4_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void canfd4_generic_write ( canfd4_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return length of read data.
 */
int16_t canfd4_generic_read ( canfd4_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Set mode function.
 * @param ctx Click object.
 * @param mode Mode selection.
 */
void canfd4_set_dev_mode ( canfd4_t *ctx, uint8_t mode );

/**
 * @brief Send command function.
 * @param ctx Click object.
 * @param command Byte to be sent.
 */
void canfd4_send_command ( canfd4_t *ctx, char *command );


#ifdef __cplusplus
}
#endif
#endif  // _CANFD4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
