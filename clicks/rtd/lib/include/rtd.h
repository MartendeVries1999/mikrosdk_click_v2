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
 * \brief This file contains API for RTD Click driver.
 *
 * \addtogroup rtd RTD Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RTD_H
#define RTD_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define RTD_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.drdy = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RTD_RETVAL  uint8_t

#define RTD_OK           0x00
#define RTD_INIT_ERROR   0xFF
#define RTD_ERR          1 
/** \} */

/**
 * \defgroup resistor_value Resistor Value
 * \{
 */
#define RTD_REF_RESISTANCE_470  470 
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define RTD_CONFIGURATION       0x00
#define RTD_RTD_MSB             0x01
#define RTD_RTD_LSB             0x02
#define RTD_HI_FLT_THRHLD_MSB   0x03
#define RTD_HI_FLT_THRHLD_LSB   0x04
#define RTD_LO_FLT_THRHLD_MSB   0x05
#define RTD_LO_FLT_THRHLD_LSB   0x06
#define RTD_FLT_STATUS          0x07
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
    digital_out_t cs;

    // Input pins 

    digital_in_t drdy;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} rtd_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t drdy;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} rtd_cfg_t;

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
void rtd_cfg_setup ( rtd_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param rtd Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RTD_RETVAL rtd_init ( rtd_t *ctx, rtd_cfg_t *cfg );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void rtd_generic_transfer 
( 
    rtd_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Write to Register function.
 * 
 * @param rtd         Click object.
 * @param reg_address Address to write to.
 * @param write_data  Data to write.
 * 
 * @description This function writes the input data into the chosen register.
 * 
 * @note
 * This function automaticaly adds write bit as needed by this device.
 */
void rtd_write_register ( rtd_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Read from Register function.
 * 
 * @param rtd         Click object.
 * @param reg_address Address to read from.
 * 
 * @description This function reads data from the chosen register.
 */
uint8_t rtd_read_register ( rtd_t *ctx, uint8_t reg_address );

/**
 * @brief Read Temperature function.
 * 
 * @param rtd         Click object.
 * 
 * @description This function reads data from temperature registers.
 */
uint16_t rtd_read_temperature ( rtd_t *ctx );

/**
 * @brief Convert Temperature function.
 * 
 * @param rtd                    Click object.
 * @param input_data             Unconverted input data.
 * @param referent_resistance    Value of external referent resistance in Ohms.
 * 
 * @description This function convert data from temperature registers.
 * 
 * @note
 * Referent resistance on the click board can be changed to better match the
 * sensor in use. Input the value of the resistor used in Ohms to get correct
 * data. 
 */
float rtd_convert_temperature ( rtd_t *ctx, uint16_t input_data, uint16_t referent_resistance );

#ifdef __cplusplus
}
#endif
#endif  // _RTD_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
