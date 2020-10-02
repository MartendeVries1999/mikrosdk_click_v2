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
 * \brief This file contains API for PWR Meter 2 Click driver.
 *
 * \addtogroup pwrmeter2 PWR Meter 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PWRMETER2_H
#define PWRMETER2_H

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

#define PWRMETER2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.md1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.md0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.dr = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PWRMETER2_RETVAL  uint8_t

#define PWRMETER2_OK           0x00
#define PWRMETER2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define PWRMETER2_CH0_ADC_DATA_REG      0x00
#define PWRMETER2_CH1_ADC_DATA_REG      0x01
#define PWRMETER2_MODUL_OUTPUT_REG      0x08
#define PWRMETER2_PHASE_CONFIG_REG      0x0A
#define PWRMETER2_GAIN_CONFIG_REG       0x0B
#define PWRMETER2_STATUS_COMM_REG       0x0C
#define PWRMETER2_CONFIG0_REG           0x0D
#define PWRMETER2_CONFIG1_REG           0x0E
#define PWRMETER2_OFFCAL_CH0_REG        0x0F
#define PWRMETER2_GAINCAL_CH0_REG       0x10
#define PWRMETER2_OFFCAL_CH1_REG        0x11
#define PWRMETER2_GAINCAL_CH1_REG       0x12
#define PWRMETER2_LOCK_CRC_REG          0x1F
/** \} */

/**
 * \defgroup ch_gain Ch Gain
 * \{
 */
#define PWRMETER2_CH0_GAIN1             0x000000
#define PWRMETER2_CH0_GAIN2             0x000001
#define PWRMETER2_CH0_GAIN4             0x000002
#define PWRMETER2_CH0_GAIN8             0x000003
#define PWRMETER2_CH0_GAIN16            0x000004
#define PWRMETER2_CH0_GAIN32            0x000005
#define PWRMETER2_CH1_GAIN1             0x000000
#define PWRMETER2_CH1_GAIN2             0x000008
#define PWRMETER2_CH1_GAIN4             0x000010
#define PWRMETER2_CH1_GAIN8             0x000018
#define PWRMETER2_CH1_GAIN16            0x000020
#define PWRMETER2_CH1_GAIN32            0x000028
/** \} */

/**
 * \defgroup data_width Data Width
 * \{
 */
#define PWRMETER2_READ_SAME_SINGLE_REG          0x000000
#define PWRMETER2_READ_REG_GROUPS               0x400000
#define PWRMETER2_READ_REG_TYPES                0x800000
#define PWRMETER2_READ_ENTIRE_REG_MAP           0xC00000
#define PWRMETER2_ADDR_COUNT_NOT_INCR_WRITE     0x000000
#define PWRMETER2_ADDR_COUNT_INCR_WRITE         0x200000
#define PWRMETER2_DR_PIN_HIGH_IMP_NOT_READY     0x000000
#define PWRMETER2_DR_PIN_LOGIC_HIGH_NOT_READY   0x100000
#define PWRMETER2_DATA_READY_LINK_DIS           0x000000
#define PWRMETER2_DATA_READY_LINK_EN            0x080000
#define PWRMETER2_CRC_WIDTH_16_BIT              0x000000
#define PWRMETER2_CRC_WIDTH_32_BIT              0x040000
#define PWRMETER2_DATA_WIDTH_16_BIT             0x000000
#define PWRMETER2_DATA_WIDTH_24_BIT             0x010000
#define PWRMETER2_DATA_WIDTH_32_BIT_WITH_ZEROS  0x020000
#define PWRMETER2_DATA_WIDTH_32_BIT_WITH_SIGN   0x030000
#define PWRMETER2_CRC_DIS                       0x000000
#define PWRMETER2_CRC_EN                        0x008000
#define PWRMETER2_CRCREG_INTERR_DIS             0x000000
#define PWRMETER2_CRCREG_INTERR_EN              0x004000
#define PWRMETER2_MODUL_OUTPUT_DIS              0x000000
#define PWRMETER2_MODUL_OUTPUT_EN               0x000800
/** \} */

/**
 * \defgroup osc Osc
 * \{
 */
#define PWRMETER2_OFFCAL_DIS                 0x000000
#define PWRMETER2_OFFCAL_EN                  0x800000
#define PWRMETER2_GAINCAL_DIS                0x000000
#define PWRMETER2_GAINCAL_EN                 0x400000
#define PWRMETER2_DITHERING_OFF              0x000000
#define PWRMETER2_DITHERING_STRENGTH_MIN     0x100000
#define PWRMETER2_DITHERING_STRENGTH_MED     0x200000
#define PWRMETER2_DITHERING_STRENGTH_MAX     0x300000
#define PWRMETER2_CURRENT_X_0_5              0x000000
#define PWRMETER2_CURRENT_X_0_66             0x040000
#define PWRMETER2_CURRENT_X_1                0x080000
#define PWRMETER2_CURRENT_X_2                0x0C0000
#define PWRMETER2_AMCLK_MCLK                 0x000000
#define PWRMETER2_AMCLK_MCLK_PER_2           0x010000
#define PWRMETER2_AMCLK_MCLK_PER_4           0x020000
#define PWRMETER2_AMCLK_MCLK_PER_8           0x030000
#define PWRMETER2_OSR_32                     0x000000
#define PWRMETER2_OSR_64                     0x002000
#define PWRMETER2_OSR_128                    0x004000
#define PWRMETER2_OSR_256                    0x006000
#define PWRMETER2_OSR_512                    0x008000
#define PWRMETER2_OSR_1024                   0x00A000
#define PWRMETER2_OSR_2048                   0x00C000
#define PWRMETER2_OSR_4096                   0x00E000
/** \} */

/**
 * \defgroup ch_mode Ch Mode
 * \{
 */
#define PWRMETER2_CH0_NORMAL_MODE            0x000000
#define PWRMETER2_CH1_NORMAL_MODE            0x000000
#define PWRMETER2_CH0_SOFT_RESET_MODE        0x010000
#define PWRMETER2_CH1_SOFT_RESET_MODE        0x020000
#define PWRMETER2_CH0_SHUTDOWN_MODE          0x000100
#define PWRMETER2_CH1_SHUTDOWN_MODE          0x000200
#define PWRMETER2_INTERNAL_VOL_REF_EN        0x000000
#define PWRMETER2_INTERNAL_VOL_REF_DIS       0x000080
#define PWRMETER2_INTERNAL_CLOCK_EN          0x000000
#define PWRMETER2_INTERNAL_CLOCK_DIS         0x000040
/** \} */

/**
 * \defgroup ch_check Ch Check
 * \{
 */
#define PWRMETER2_CH0_CHECK_DIS              0x00
#define PWRMETER2_CH1_CHECK_DIS              0x00
#define PWRMETER2_CH0_CHECK_EN               0x01
#define PWRMETER2_CH1_CHECK_EN               0x02
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

    digital_out_t rst;
    digital_out_t cs;

    // Input pins 

    digital_in_t md1;
    digital_in_t md0;
    digital_in_t dr;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;
    uint8_t dr_link;

} pwrmeter2_t;

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

    pin_name_t md1;
    pin_name_t rst;
    pin_name_t md0;
    pin_name_t dr;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} pwrmeter2_cfg_t;

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
void pwrmeter2_cfg_setup ( pwrmeter2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param pwrmeter2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PWRMETER2_RETVAL pwrmeter2_init ( pwrmeter2_t *ctx, pwrmeter2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for PWR Meter 2 click.
 */
void pwrmeter2_default_cfg ( pwrmeter2_t *ctx );

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
void pwrmeter2_generic_transfer 
( 
    pwrmeter2_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Generic Write function.
 *
 * @param ctx               Click object.
 * @param register_address  Address where data be written.
 * @param transfer_data     Data to be written.
 *
 * @description This function writes 24-bit data to the register.
 */
uint8_t pwrmeter2_write_reg ( pwrmeter2_t *ctx, uint8_t register_address, uint32_t transfer_data );

/**
 * @brief Generic Read function.
 *
 * @param ctx               Click object.
 * @param register_address  Address which from data be read.
 * @param data_out          Number of data to be read.
 * @param n_data            Buffer where data be stored.
 *
 * @description This function reads the desired number of 24-bit data from the register/registers.
 */
uint8_t pwrmeter2_read_reg ( pwrmeter2_t *ctx, uint8_t register_address, uint32_t *data_out, uint8_t n_data );

/**
 * @brief Data Ready Check function.
 *
 * @param ctx        Click object.
 * @param sel_chann  Determines which channel be checked.
 *
 * @description This function waits until conversion, for the desired channel, is finished and returns information about data width.
 */
uint8_t pwrmeter2_check_data_ready ( pwrmeter2_t *ctx, uint8_t sel_chann );

/**
 * @brief Read Converted Data function.
 *
 * @param ctx        Click object.
 * @param data_ch_0  Buffer where the converted data from channel 0 register be stored.
 * @param data_ch_1  Buffer where the converted data from channel 1 register be stored.
 *
 * @description This function reads the converted data from both channels when conversion is finished.
 */
uint8_t pwrmeter2_read_conv_data ( pwrmeter2_t *ctx, uint32_t *data_ch_0, uint32_t *data_ch_1 );

/**
 * @brief Data Get function.
 *
 * @param ctx           Click object.
 * @param voltage_data  Stores the voltage data in mV.
 * @param current_data  Stores the current data in mA.
 * @param power_data    tores the power data in mW.
 *
 * @description This function gets the calculated voltage( mV ), current( mA ) and power( mW ) data.
 */
void pwrmeter2_get_data ( pwrmeter2_t *ctx, int32_t *voltage_data, int32_t *current_data, uint32_t *power_data );

/**
 * @brief Reset function.
 *
 * @param ctx           Click object.
 *
 * @description This function performs the hardware reset and puts the device back to the normal operation mode after 1.2 seconds.
 */
void pwrmeter2_reset( pwrmeter2_t *ctx );

/**
 * @brief Modulator 1 Get function.
 *
 * @param ctx           Click object.
 *
 * @description This function returns the state of the modulator output for the channel 1.
 */
uint8_t pwrmeter2_get_modulator_1 ( pwrmeter2_t *ctx );

/**
 * @brief Modulator 0 Get function.
 *
 * @param ctx           Click object.
 *
 * @description This function returns the state of the modulator output for the channel 0.
 */
uint8_t pwrmeter2_get_modulator_0 ( pwrmeter2_t *ctx );

/**
 * @brief Ready Pin Check function.
 *
 * @param ctx           Click object.
 *
 * @description This function returns the state of the Data Ready ( DR ) pin.
 */
uint8_t pwrmeter2_check_ready_pin ( pwrmeter2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PWRMETER2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
