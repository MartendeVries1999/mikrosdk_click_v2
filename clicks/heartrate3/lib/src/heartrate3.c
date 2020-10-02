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
 */

#include "heartrate3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void heartrate3_cfg_setup ( heartrate3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

     cfg->rst = HAL_PIN_NC;
     cfg->clk = HAL_PIN_NC;
     cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = HEARTRATE3_SLAVE_ADDR;
}

HEARTRATE3_RETVAL heartrate3_init ( heartrate3_t *ctx, heartrate3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HEARTRATE3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->clk, cfg->clk );

    // Input pins

    digital_in_init( &ctx->rdy, cfg->rdy );

    return HEARTRATE3_OK;
}

void heartrate3_default_cfg ( heartrate3_t *ctx )
{
    // Click default configuration
    heartrate3_write_data( ctx, HEARTRATE3_CONTROL0, 
                           HEARTRATE3_CONTROL0_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED2STC, 
                           HEARTRATE3_LED2STC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED2ENDC, 
                           HEARTRATE3_LED2ENDC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED1LEDSTC, 
                           HEARTRATE3_LED1LEDSTC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED1LEDENDC, 
                           HEARTRATE3_LED1LEDENDC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ALED2STC, 
                           HEARTRATE3_ALED2STC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ALED2ENDC, 
                           HEARTRATE3_ALED2ENDC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED1STC, 
                           HEARTRATE3_LED1STC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED1ENDC, 
                           HEARTRATE3_LED1ENDC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED2LEDSTC, 
                           HEARTRATE3_LED2LEDSTC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED2LEDENDC, 
                           HEARTRATE3_LED2LEDENDC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ALED1STC, 
                           HEARTRATE3_ALED1STC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ALED1ENDC, 
                           HEARTRATE3_ALED1ENDC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED2CONVST, 
                           HEARTRATE3_LED2CONVST_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED2CONVEND, 
                           HEARTRATE3_LED2CONVEND_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ALED2CONVST, 
                           HEARTRATE3_ALED2CONVST_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ALED2CONVEND, 
                           HEARTRATE3_ALED2CONVEND_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED1CONVST, 
                           HEARTRATE3_LED1CONVST_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED1CONVEND, 
                           HEARTRATE3_LED1CONVEND_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ALED1CONVST, 
                           HEARTRATE3_ALED1CONVST_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ALED1CONVEND, 
                           HEARTRATE3_ALED1CONVEND_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ADCRSTSTCT0, 
                           HEARTRATE3_ADCRSTSTCT0_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ADCRSTENDCT0, 
                           HEARTRATE3_ADCRSTENDCT0_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ADCRSTSTCT1, 
                           HEARTRATE3_ADCRSTSTCT1_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ADCRSTENDCT1, 
                           HEARTRATE3_ADCRSTENDCT1_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ADCRSTSTCT2, 
                           HEARTRATE3_ADCRSTSTCT2_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ADCRSTENDCT2, 
                           HEARTRATE3_ADCRSTENDCT2_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ADCRSTSTCT3, 
                           HEARTRATE3_ADCRSTSTCT3_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ADCRSTENDCT3, 
                           HEARTRATE3_ADCRSTENDCT3_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_PRPCOUNT, 
                           HEARTRATE3_PRPCOUNT_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_CONTROL1, 
                           HEARTRATE3_CONTROL1_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_TIA_GAIN_SEP, 
                           HEARTRATE3_TIA_GAIN_SEP_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_TIA_GAIN, 
                           HEARTRATE3_TIA_GAIN_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LEDCNTRL, 
                           HEARTRATE3_LEDCNTRL_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_CONTROL2, 
                           HEARTRATE3_CONTROL2_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_ALARM, 
                           HEARTRATE3_ALARM_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_CONTROL3, 
                           HEARTRATE3_CONTROL3_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_PDNCYCLESTC, 
                           HEARTRATE3_PDNCYCLESTC_CMD  );
    heartrate3_write_data( ctx, HEARTRATE3_PDNCYCLEENDC, 
                           HEARTRATE3_PDNCYCLEENDC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_PROG_TG_STC, 
                           HEARTRATE3_PROG_TG_STC_CMD  );
    heartrate3_write_data( ctx, HEARTRATE3_PROG_TG_ENDC, 
                           HEARTRATE3_PROG_TG_ENDC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED3LEDSTC, 
                           HEARTRATE3_LED3LEDSTC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_LED3LEDENDC, 
                           HEARTRATE3_LED3LEDENDC_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_CLKDIV_PRF, 
                           HEARTRATE3_CLKDIV_PRF_CMD );
    heartrate3_write_data( ctx, HEARTRATE3_OFFDAC, 
                           HEARTRATE3_OFFDAC_CMD );
}

void heartrate3_generic_write ( heartrate3_t *ctx, uint8_t reg, 
                                uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
}

void heartrate3_generic_read ( heartrate3_t *ctx, uint8_t reg, 
                               uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void heartrate3_write_data ( heartrate3_t *ctx, uint8_t reg_adr, 
                             uint32_t wr_data )
{
    uint8_t tx_buf[ 3 ];
    tx_buf[ 0 ] = wr_data >> 16;
    tx_buf[ 1 ] = wr_data >> 8;
    tx_buf[ 2 ] = wr_data;

    heartrate3_generic_write( ctx, reg_adr, tx_buf, 3 );
}

uint32_t heartrate3_read_u32 ( heartrate3_t *ctx, uint8_t reg_adr )
{
    uint32_t result;
    uint8_t rx_buf[ 3 ]; 

    heartrate3_generic_read( ctx, reg_adr, rx_buf, 3 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 2 ];

    return result;
}

uint16_t heartrate3_read_u16 ( heartrate3_t *ctx, uint8_t reg_adr )
{
    uint8_t rx_buf[ 2 ];
    uint16_t result;

    heartrate3_generic_read( ctx, reg_adr, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

void heartrate3_rst_state ( heartrate3_t *ctx, uint8_t state )
{
    if ( state == HEARTRATE3_PIN_STATE_HIGH )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void heartrate3_clk_state ( heartrate3_t *ctx, uint8_t state )
{
    if ( state == HEARTRATE3_PIN_STATE_HIGH )
    {
        digital_out_high( &ctx->clk );
    }
    else
    {
        digital_out_low( &ctx->clk );
    }
}

uint8_t heartrate3_check_data_ready ( heartrate3_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

// ------------------------------------------------------------------------- END

