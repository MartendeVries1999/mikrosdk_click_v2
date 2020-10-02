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

#include "thermostat4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define THERMOSTAT4_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermostat4_cfg_setup ( thermostat4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->oa = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->rly = HAL_PIN_NC;
    cfg->ob = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

THERMOSTAT4_RETVAL thermostat4_init ( thermostat4_t *ctx, thermostat4_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = THERMOSTAT4_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return THERMOSTAT4_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, THERMOSTAT4_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rly, cfg->rly );

    // Input pins

    digital_in_init( &ctx->oa, cfg->oa );
    digital_in_init( &ctx->ob, cfg->ob );


    spi_master_deselect_device( ctx->chip_select );
    digital_out_low( &ctx->rst );

    return THERMOSTAT4_OK;
}

void thermostat4_generic_transfer 
( 
    thermostat4_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void thermostat4_relay_ctrl ( thermostat4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rly, state );
}

void thermostat4_rst_pin_ctrl ( thermostat4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

uint8_t thermostat4_hot_alert_state ( thermostat4_t *ctx )
{
    return digital_in_read( &ctx->oa );
}

uint8_t thermostat4_warm_alert_state ( thermostat4_t *ctx )
{
    return digital_in_read( &ctx->ob );
}

void thermostat4_set_warm_hysteresis ( thermostat4_t *ctx, uint8_t hyst_data )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &hyst_data, 1 );
    spi_master_deselect_device( ctx->chip_select );      
}

void thermostat4_new_cfg_upload ( thermostat4_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

