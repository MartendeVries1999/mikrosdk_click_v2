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
 * \brief This file contains API for Ambient 3 Click driver.
 *
 * \addtogroup ambient3 Ambient 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AMBIENT3_H
#define AMBIENT3_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define AMBIENT3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMBIENT3_RETVAL  uint8_t

#define AMBIENT3_OK           0x00
#define AMBIENT3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address
 * \{
 */
#define AMBIENT3_DEVICE_SLAVE_ADDRESS              0x49          
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define AMBIENT3_REG_HW_VERSION_MSB                0x00
#define AMBIENT3_REG_HW_VERSION_LSB                0x01
#define AMBIENT3_REG_FW_VERSION_MSB                0x02
#define AMBIENT3_REG_FW_VERSION_LSB                0x03
#define AMBIENT3_REG_CONV_CONTROL                  0x04
#define AMBIENT3_REG_INTEGRATION_TIME              0x05
#define AMBIENT3_REG_DEVICE_TEMP                   0x06
#define AMBIENT3_REG_LED_STRING_INIT               0x08
#define AMBIENT3_REG_DIR_CONTROL                   0x64
#define AMBIENT3_REG_DIR_SETUP                     0x65
#define AMBIENT3_REG_DIR_CH_1_LSB                  0x50
#define AMBIENT3_REG_DIR_CH_1_MSB                  0x51
#define AMBIENT3_REG_DIR_CH_2_LSB                  0x52
#define AMBIENT3_REG_DIR_CH_2_MSB                  0x53
#define AMBIENT3_REG_DIR_CCTT_LSB                  0x60
#define AMBIENT3_REG_DIR_CCTT_MSB                  0x61
#define AMBIENT3_REG_DIR_LUXT_LSB                  0x62
#define AMBIENT3_REG_DIR_LUXT_MSB                  0x63
#define AMBIENT3_REG_DIR_LUX_MAX_LSB               0x66
#define AMBIENT3_REG_DIR_LUX_MAX_MSB               0x67
/** \} */

/**
* \defgroup xyz_scale_registers XYZ Scale Registers
 * \{
 */
#define AMBIENT3_REG_X_SCALE_B1                    0x44
#define AMBIENT3_REG_X_SCALE_B2                    0x45
#define AMBIENT3_REG_X_SCALE_B3                    0x46
#define AMBIENT3_REG_X_SCALE_B4                    0x47
#define AMBIENT3_REG_Y_SCALE_B1                    0x48
#define AMBIENT3_REG_Y_SCALE_B2                    0x49
#define AMBIENT3_REG_Y_SCALE_B3                    0x4A
#define AMBIENT3_REG_Y_SCALE_B4                    0x4B
#define AMBIENT3_REG_Z_SCALE_B1                    0x4C
#define AMBIENT3_REG_Z_SCALE_B2                    0x4D
#define AMBIENT3_REG_Z_SCALE_B3                    0x4E
#define AMBIENT3_REG_Z_SCALE_B4                    0x4F
/** \} */

/**
 * \defgroup xyz_iffuser_scale_registers XYZ Diffuser Scale Registers
 * \{
 */
#define AMBIENT3_REG_X_D_SCALE_B1                  0x70
#define AMBIENT3_REG_X_D_SCALE_B2                  0x71
#define AMBIENT3_REG_X_D_SCALE_B3                  0x72
#define AMBIENT3_REG_X_D_SCALE_B4                  0x73
#define AMBIENT3_REG_Y_D_SCALE_B1                  0x74
#define AMBIENT3_REG_Y_D_SCALE_B2                  0x75
#define AMBIENT3_REG_Y_D_SCALE_B3                  0x76
#define AMBIENT3_REG_Y_D_SCALE_B4                  0x77
#define AMBIENT3_REG_Z_D_SCALE_B1                  0x78
#define AMBIENT3_REG_Z_D_SCALE_B2                  0x79
#define AMBIENT3_REG_Z_D_SCALE_B3                  0x7A
#define AMBIENT3_REG_Z_D_SCALE_B4                  0x7B
/** \} */

/**
 * \defgroup calibrated_xyz_result_registers Calibrated XYZ Result Registers 
 * \{
 */
#define AMBIENT3_REG_X_CALIBRATED_B1               0x14
#define AMBIENT3_REG_X_CALIBRATED_B2               0x15
#define AMBIENT3_REG_X_CALIBRATED_B3               0x16
#define AMBIENT3_REG_X_CALIBRATED_B4               0x17
#define AMBIENT3_REG_Y_CALIBRATED_B1               0x18
#define AMBIENT3_REG_Y_CALIBRATED_B2               0x19
#define AMBIENT3_REG_Y_CALIBRATED_B3               0x1A
#define AMBIENT3_REG_Y_CALIBRATED_B4               0x1B
#define AMBIENT3_REG_Z_CALIBRATED_B1               0x1C
#define AMBIENT3_REG_Z_CALIBRATED_B2               0x1D
#define AMBIENT3_REG_Z_CALIBRATED_B3               0x1E
#define AMBIENT3_REG_Z_CALIBRATED_B4               0x1F
/** \} */

/**
 * \defgroup x_and_y_result_registers Calibrated CIE 1931 x and y Result Registers
 * \{
 */
#define AMBIENT3_REG_CIE1931_X_CALIBRATED_B1       0x20
#define AMBIENT3_REG_CIE1931_X_CALIBRATED_B2       0x21
#define AMBIENT3_REG_CIE1931_X_CALIBRATED_B3       0x22
#define AMBIENT3_REG_CIE1931_X_CALIBRATED_B4       0x23
#define AMBIENT3_REG_CIE1931_Y_CALIBRATED_B1       0x24
#define AMBIENT3_REG_CIE1931_Y_CALIBRATED_B2       0x25
#define AMBIENT3_REG_CIE1931_Y_CALIBRATED_B3       0x26
#define AMBIENT3_REG_CIE1931_Y_CALIBRATED_B4       0x27
/** \} */

/**
 * \defgroup u_and_v_result_registers Calibrated CIE 1976 u�, v�, u and v Result Registers
 * \{
 */
#define AMBIENT3_REG_U_PRI_CALIBRATED_B1           0x28
#define AMBIENT3_REG_U_PRI_CALIBRATED_B2           0x29
#define AMBIENT3_REG_U_PRI_CALIBRATED_B3           0x2A
#define AMBIENT3_REG_U_PRI_CALIBRATED_B4           0x2B
#define AMBIENT3_REG_V_PRI_CALIBRATED_B1           0x2C
#define AMBIENT3_REG_V_PRI_CALIBRATED_B2           0x2D
#define AMBIENT3_REG_V_PRI_CALIBRATED_B3           0x2E
#define AMBIENT3_REG_V_PRI_CALIBRATED_B4           0x2F
#define AMBIENT3_REG_U_CALIBRATED_B1               0x30
#define AMBIENT3_REG_U_CALIBRATED_B2               0x31
#define AMBIENT3_REG_U_CALIBRATED_B3               0x32
#define AMBIENT3_REG_U_CALIBRATED_B4               0x33
#define AMBIENT3_REG_V_CALIBRATED_B1               0x34
#define AMBIENT3_REG_V_CALIBRATED_B2               0x35
#define AMBIENT3_REG_V_CALIBRATED_B3               0x36
#define AMBIENT3_REG_V_CALIBRATED_B4               0x37
/** \} */

/**
 * \defgroup   calibrate_DUV_result_register Calibrated DUV Result Register
 * \{
 */
#define AMBIENT3_REG_DUV_CALIBRATED_B1             0x38
#define AMBIENT3_REG_DUV_CALIBRATED_B2             0x39
#define AMBIENT3_REG_DUV_CALIBRATED_B3             0x3A
#define AMBIENT3_REG_DUV_CALIBRATED_B4             0x3B
/** \} */

/**
 * \defgroup calibrated_LUX_result_registers Calibrated LUX Result Registers
 * \{
 */
#define AMBIENT3_REG_CAL_LUX_LSB                   0x3C
#define AMBIENT3_REG_CAL_LUX_MSB                   0x3D
#define AMBIENT3_REG_CAL_CCT_LSB                   0x3E
#define AMBIENT3_REG_CAL_CCT_MSB                   0x3F
/** \} */

/**
 * \defgroup conv_control_register CONV Control Register
 * \{
 */
#define AMBIENT3_CC_RDY_TO_INT                     0x40
#define AMBIENT3_CC_GAIN_x1                        0x00
#define AMBIENT3_CC_GAIN_x3_7                      0x10
#define AMBIENT3_CC_GAIN_x16                       0x20
#define AMBIENT3_CC_GAIN_x64                       0x30
#define AMBIENT3_CC_SOFTWARE_RESET                 0x01
/** \} */

/**
 * \defgroup dir_control DIR Control
 * \{
 */

#define AMBIENT3_DIRC_NUM_CH_2_CHANNELS            0x40
#define AMBIENT3_DIRC_NUM_CH_1_CHANNELS            0x20
#define AMBIENT3_DIRC_PWM_RDY_TO_INT               0x10
#define AMBIENT3_DIRC_COLOR_TUNING_ENABLED         0x08
#define AMBIENT3_DIRC_COLOR_TUNING_DISABLED        0x00
#define AMBIENT3_DIRC_DAYLIGHTING_ENABLED          0x04
#define AMBIENT3_DIRC_DAYLIGHTING_DISABLED         0x00
#define AMBIENT3_DIRC_MCU_RDY_FOR_START            0x02
#define AMBIENT3_DIRC_NEW_PWM_RDY                  0x01
/** \} */

/**
 * \defgroup dir_setup DIR_setup
 * \{
 */
#define AMBIENT3_DIRS_COLOR_TUNING_WITH_PWM2       0x80
#define AMBIENT3_DIRS_COLOR_TUNING_WITH_PWM1       0x40
#define AMBIENT3_DIRS_SET_CCT_TUNING_MODE          0x00
/** \} */

/**
 * \defgroup rp_egister RP register
 * \{
 */
#define AMBIENT3_FP_REG_X_SCALE                    0x44
#define AMBIENT3_FP_REG_Y_SCALE                    0x48
#define AMBIENT3_FP_REG_Z_SCALE                    0x4C
#define AMBIENT3_FP_REG_X_D_SCALE                  0x70
#define AMBIENT3_FP_REG_Y_D_SCALE                  0x74
#define AMBIENT3_FP_REG_Z_D_SCALE                  0x78
#define AMBIENT3_FP_REG_X_CALIBRATED               0x14
#define AMBIENT3_FP_REG_Y_CALIBRATED               0x18
#define AMBIENT3_FP_REG_Z_CALIBRATED               0x1C
#define AMBIENT3_FP_REG_CIE1931_X_CALIBRATED       0x20
#define AMBIENT3_FP_REG_CIE1931_Y_CALIBRATED       0x24
#define AMBIENT3_FP_REG_U_PRI_CALIBRATED           0x28
#define AMBIENT3_FP_REG_V_PRI_CALIBRATED           0x2C
#define AMBIENT3_FP_REG_U_CALIBRATED               0x30
#define AMBIENT3_FP_REG_V_CALIBRATED               0x34
#define AMBIENT3_FP_REG_DUV_CALIBRATED             0x38
#define AMBIENT3_FP_REG_LUX_CALIBRATED             0x3C
#define AMBIENT3_FP_REG_CCT_CALIBRATED             0x3E
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

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} ambient3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} ambient3_cfg_t;

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
void ambient3_cfg_setup ( ambient3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AMBIENT3_RETVAL ambient3_init ( ambient3_t *ctx, ambient3_cfg_t *cfg );

/**
 * @brief Default Config Initialization function.
 *
 * @param ctx  Click object.
 *
 * @description This function initializes click configuration structure to init state.
 */
void ambient3_default_cfg ( ambient3_t *ctx );

/**
 * @brief Write function.
 *
 * @param ctx          Click object.
 * @param virtual_reg  Register address.
 * @param data_buf     Data buf to be written.
 *
 * @description This function writes one byte to the desired register.
 */
void ambient3_write_byte ( ambient3_t *ctx, uint8_t virtual_reg, uint8_t data_buf);

/**
 * @brief Read function.
 * 
 * @param ctx          Click object.
 * @param virtual_reg  Register address.
 * @returns            Read byte.
 *
 * @description This function reads byte from the desired register.
 */
uint8_t ambient3_read_byte ( ambient3_t *ctx, uint8_t virtual_reg);

/**
 * @brief Hardware reset function.
 * 
 * @param ctx          Click object.
 *
 * @description This function sets rst_pin to high.
 */
void ambient3_hardware_reset ( ambient3_t *ctx );

/**
 * @brief Getting temperature function.
 * 
 * @param ctx          Click object.
 * @returns            Device temperature in Celsius.
 *
 * @description This function reads device temperature.
 */
uint8_t ambient3_get_device_temperature ( ambient3_t *ctx );

/**
 * @brief Data in LUX function.
 * 
 * @param ctx          Click object.
 * @returns            Light data in the LUX.
 *
 * @description This function reads data in LUX value.
 */
float ambient3_get_data_in_lux ( ambient3_t *ctx );

/**
 * @brief Read floating point register.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @returns            Read data from desired register.
 *
 * @description This function reads floating point register.
 */
float ambient3_read_floating_point_register ( ambient3_t *ctx, uint8_t reg );

/**
 * @brief Function for reads CCT data in K
 * 
 * @param ctx          Click object.
 * @returns            Value for sensed CCT in Kelvin.
 *
 * @description This function create a 16 bit integer value for sensed CCT (Kelvin).
 */
float ambient3_get_CCT_data ( ambient3_t *ctx );

/**
 * @brief Function for reads interrupt state.
 * 
 * @param ctx          Click object.
 * @returns            State INT pins.
 *
 * @description This function reads interrupt state.
 */
uint8_t ambient3_get_interrupt ( ambient3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AMBIENT3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
