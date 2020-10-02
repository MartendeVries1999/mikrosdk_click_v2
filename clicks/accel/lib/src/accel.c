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

#include "accel.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ACCEL_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void accel_i2c_write ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel_i2c_read ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel_spi_write ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel_spi_read ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel_cfg_setup ( accel_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ACCEL_I2C_ADR_VCC;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = 3;
    cfg->sel = ACCEL_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ACCEL_RETVAL accel_init ( accel_t *ctx, accel_cfg_t *cfg )
{
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == ACCEL_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return ACCEL_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f =  accel_i2c_read;
        ctx->write_f =  accel_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        //spi_cfg.mode        = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) != SPI_MASTER_SUCCESS )
        {
            return  ACCEL_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, ACCEL_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->read_f =  accel_spi_read;
        ctx->write_f =  accel_spi_write;

    }

        digital_in_init( &ctx->int_pin, cfg->int_pin );

    return ACCEL_OK;
}

void accel_default_cfg ( accel_t *ctx )
{   
    uint8_t tx_buf;        

    tx_buf = ACCEL_POWER_CTL_WAKEUP_1;
    accel_generic_write( ctx, ACCEL_REG_POWER_CTL, &tx_buf, 1 );
    
    tx_buf = ACCEL_DATA_FORMAT_FULL_RES | ACCEL_DATA_FORMAT_RANGE_16;
    accel_generic_write( ctx, ACCEL_REG_DATA_FORMAT , &tx_buf, 1 );
    
    tx_buf = ACCEL_BW_RATE_50;
    accel_generic_write( ctx, ACCEL_REG_BW_RATE, &tx_buf, 1 );
    
    tx_buf = ACCEL_FIFO_CTL_FIFO_MODE_STREAM;
    accel_generic_write( ctx, ACCEL_REG_FIFO_CTL, &tx_buf, 1 );
    
    tx_buf = ACCEL_POWER_CTL_MEASURE;
    accel_generic_write( ctx, ACCEL_REG_POWER_CTL, &tx_buf, 1 );
}

void accel_generic_write ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void accel_generic_read ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

int16_t accel_read_x_axis ( accel_t *ctx )
{
    int16_t out_x;
    uint8_t buf[ 2 ];
    
    accel_generic_read( ctx, ACCEL_REG_DATA_X_LSB, buf, 2 );

    out_x = buf[ 1 ];
    out_x <<= 8;
    out_x |= buf[ 0 ];
    
    return out_x;
}

int16_t accel_read_y_axis ( accel_t *ctx )
{
    int16_t out_y;
    uint8_t buf[ 2 ];

    accel_generic_read( ctx, ACCEL_REG_DATA_Y_LSB, buf, 2 );

    out_y = buf[ 1 ];
    out_y <<= 8;
    out_y |= buf[ 0 ];


    return out_y;
}

int16_t accel_read_z_axis ( accel_t *ctx )
{
    int16_t out_z;
    uint8_t buf[ 2 ];

    accel_generic_read( ctx, ACCEL_REG_DATA_Z_LSB, buf, 2 );

    out_z = buf[ 1 ];
    out_z <<= 8;
    out_z |= buf[ 0 ];

    return out_z;
}

uint8_t accel_check_int_pin ( accel_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void accel_i2c_write ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel_i2c_read ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void accel_spi_write ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );     
}

static void accel_spi_read ( accel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt + 1];
    }
}

// ------------------------------------------------------------------------- END

