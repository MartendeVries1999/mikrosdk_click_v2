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
 * @file digipot14.c
 * @brief DIGI POT 14 Click Driver.
 */

#include "digipot14.h"

void digipot14_cfg_setup ( digipot14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DIGIPOT14_DEVICE_ADDRESS_000;
}

err_t digipot14_init ( digipot14_t *ctx, digipot14_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t digipot14_default_cfg ( digipot14_t *ctx ) 
{
    err_t error_flag = DIGIPOT14_OK;
    
    error_flag |= digipot14_reg_write( ctx, DIGIPOT14_VOLATILE_REG_ACR, DIGIPOT14_VOLATILE_REG_WRITE | DIGIPOT14_DISABLE_SHUT_DOWN );
    error_flag |= digipot14_set_pot_a_wiper( ctx, 0 );
    error_flag |= digipot14_set_pot_b_wiper( ctx, 0 );

    return error_flag;
}

err_t digipot14_generic_write ( digipot14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t digipot14_generic_read ( digipot14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t digipot14_reg_write ( digipot14_t *ctx, uint8_t reg, uint8_t data_in )
{
    return digipot14_generic_write( ctx, reg, &data_in, 1 );
}

err_t digipot14_reg_read ( digipot14_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return digipot14_generic_read( ctx, reg, data_out, 1 );
}

err_t digipot14_set_pot_a_wiper ( digipot14_t *ctx, uint8_t wiper_pos )
{
    err_t error_flag = DIGIPOT14_OK;
    
    error_flag |= digipot14_reg_write( ctx, DIGIPOT14_VOLATILE_REG_WRA, wiper_pos );

    return error_flag;
}

err_t digipot14_set_pot_b_wiper ( digipot14_t *ctx, uint8_t wiper_pos )
{
    err_t error_flag = DIGIPOT14_OK;
    
    error_flag |= digipot14_reg_write( ctx, DIGIPOT14_VOLATILE_REG_WRB, wiper_pos );

    return error_flag;
}


// ------------------------------------------------------------------------- END
