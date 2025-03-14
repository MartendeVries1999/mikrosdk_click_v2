/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file c3gaa.h
 * @brief This file contains API for 3G-AA Click Driver.
 */

#ifndef C3GAA_H
#define C3GAA_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup c3gaa 3G-AA Click Driver
 * @brief API for configuring and manipulating 3G-AA Click driver.
 * @{
 */

/**
 * @defgroup c3gaa_set 3G-AA Device Settings
 * @brief Settings for registers of 3G-AA Click driver.
 */

/**
 * @addtogroup c3gaa_set
 * @{
 */

/**
 * @brief 3G-AA control commands.
 * @details Specified setting for control commands of 3G-AA Click driver.
 */
#define C3GAA_CMD_AT                            "AT"
#define C3GAA_CMD_ATI                           "ATI"
#define C3GAA_CMD_CFUN                          "AT+CFUN"
#define C3GAA_CMD_CREG                          "AT+CREG"
#define C3GAA_CMD_CGDCONT                       "AT+CGDCONT"
#define C3GAA_CMD_CSQ                           "AT+CSQ"
#define C3GAA_CMD_COPS                          "AT+COPS"
#define C3GAA_CMD_CMGS                          "AT+CMGS"
#define C3GAA_CMD_CMGF                          "AT+CMGF"
#define C3GAA_CMD_QIACT                         "AT+QIACT"
#define C3GAA_CMD_QIOPEN                        "AT+QIOPEN"
#define C3GAA_CMD_QICLOSE                       "AT+QICLOSE"
#define C3GAA_CMD_QISEND                        "AT+QISEND"
#define C3GAA_CMD_QIRD                          "AT+QIRD"

/**
 * @brief 3G-AA device response for AT commands.
 * @details Device response after commands.
 */
#define C3GAA_RSP_OK                            "OK"
#define C3GAA_RSP_ERROR                         "ERROR"

/**
 * @brief 3G-AA driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define C3GAA_RX_DRV_BUFFER_SIZE                256
#define C3GAA_TX_DRV_BUFFER_SIZE                256

/*! @} */ // c3gaa_set

/**
 * @defgroup c3gaa_map 3G-AA MikroBUS Map
 * @brief MikroBUS pin mapping of 3G-AA Click driver.
 */

/**
 * @addtogroup c3gaa_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3G-AA Click to the selected MikroBUS.
 */
#define C3GAA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sta = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pwk = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c3gaa_map
/*! @} */ // c3gaa

/**
 * @brief 3G-AA Click context object.
 * @details Context object definition of 3G-AA Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwk;      /**< Power-up module. */
    digital_out_t rts;      /**< UART Request to Send. */

    // Input pins
    digital_in_t sta;       /**< Module status. */
    digital_in_t ring;      /**< Ring indicator. */
    digital_in_t cts;       /**< UART Clear to Send. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ C3GAA_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    char uart_tx_buffer[ C3GAA_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */

} c3gaa_t;

/**
 * @brief 3G-AA Click configuration object.
 * @details Configuration object definition of 3G-AA Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t sta;         /**< Module status. */
    pin_name_t pwk;         /**< Power-up module. */ 
    pin_name_t rts;         /**< UART Request to Send. */
    pin_name_t ring;        /**< Ring indicator. */
    pin_name_t cts;         /**< UART Clear to Send. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} c3gaa_cfg_t;

/**
 * @brief 3G-AA Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3GAA_OK = 0,
    C3GAA_ERROR = -1,
    C3GAA_ERROR_TIMEOUT = -2,
    C3GAA_ERROR_CMD = -3,
    C3GAA_ERROR_UNKNOWN = -4

} c3gaa_return_value_t;

/*!
 * @addtogroup c3gaa 3G-AA Click Driver
 * @brief API for configuring and manipulating 3G-AA Click driver.
 * @{
 */

/**
 * @brief 3G-AA configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3gaa_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c3gaa_cfg_setup ( c3gaa_cfg_t *cfg );

/**
 * @brief 3G-AA initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3gaa_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3gaa_init ( c3gaa_t *ctx, c3gaa_cfg_t *cfg );

/**
 * @brief 3G-AA data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3gaa_generic_write ( c3gaa_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief 3G-AA data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3gaa_generic_read ( c3gaa_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief 3G-AA set rts pin function.
 * @details This function sets the Request to Send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c3gaa_set_rts_pin ( c3gaa_t *ctx, uint8_t state );

/**
 * @brief 3G-AA set pwk pin function.
 * @details This function sets the PWRKEY pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c3gaa_set_pwk_pin ( c3gaa_t *ctx, uint8_t state );

/**
 * @brief 3G-AA get cts pin function.
 * @details This function returns the Clear to Send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3gaa_get_cts_pin ( c3gaa_t *ctx );

/**
 * @brief 3G-AA get sta pin function.
 * @details This function returns the status (STA) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3gaa_get_sta_pin ( c3gaa_t *ctx );

/**
 * @brief 3G-AA get ring pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3gaa_get_ring_pin ( c3gaa_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 * @note None.
 */
void c3gaa_send_cmd ( c3gaa_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void c3gaa_send_cmd_with_par ( c3gaa_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void c3gaa_send_cmd_check ( c3gaa_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void c3gaa_send_cmd_par_check ( c3gaa_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void c3gaa_set_sim_apn ( c3gaa_t *ctx, uint8_t *sim_apn );

/**
 * @brief 3G-AA send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void c3gaa_send_sms_text ( c3gaa_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief 3G-AA send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #c3gaa_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3gaa_send_sms_pdu ( c3gaa_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // C3GAA_H

/*! @} */ // c3gaa

// ------------------------------------------------------------------------ END
