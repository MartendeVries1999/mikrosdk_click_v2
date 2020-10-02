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

#include "mux2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mux2_cfg_setup ( mux2_cfg_t *cfg )
{
    // Additional gpio pins

   //cfg->an   = HAL_PIN_NC;
    cfg->a0 = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->a1 = HAL_PIN_NC;
    cfg->a2 = HAL_PIN_NC;
}

MUX2_RETVAL mux2_init ( mux2_t *ctx, mux2_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->a0, cfg->a0 );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->a1, cfg->a1 );
    digital_out_init( &ctx->a2, cfg->a2 );

    return MUX2_OK;
}

void mux2_device_enable ( mux2_t *ctx )
{
    digital_out_high( &ctx->en );
}

void mux2_device_disable ( mux2_t *ctx )
{
    digital_out_low( &ctx->en );
}

void mux2_active_mux_channel (  mux2_t *ctx, uint8_t sel_ch )
{
    switch ( sel_ch )
    {
        case MUX2_CHANNEL_S1:
        {
            digital_out_low( &ctx->a2 );
            digital_out_low( &ctx->a1 );
            digital_out_low( &ctx->a0 );
            break;
        }
        case MUX2_CHANNEL_S2:
        {
            digital_out_low( &ctx->a2 );
            digital_out_low( &ctx->a1 );
            digital_out_high( &ctx->a0 );
            break;
        }
        case MUX2_CHANNEL_S3:
        {
            digital_out_low( &ctx->a2 );
            digital_out_high( &ctx->a1 );
            digital_out_low( &ctx->a0 );
            break;
        }
        case MUX2_CHANNEL_S4:
        {
            digital_out_low( &ctx->a2 );
            digital_out_high( &ctx->a1 );
            digital_out_high( &ctx->a0 );
            break;
        }
        case MUX2_CHANNEL_S5:
        {
            digital_out_high( &ctx->a2 );
            digital_out_low( &ctx->a1 );
            digital_out_low( &ctx->a0 );
            break;
        }
        case MUX2_CHANNEL_S6:
        {
            digital_out_high( &ctx->a2 );
            digital_out_low( &ctx->a1 );
            digital_out_high( &ctx->a0 );
            break;
        }
        case MUX2_CHANNEL_S7:
        {
            digital_out_high( &ctx->a2 );
            digital_out_high( &ctx->a1 );
            digital_out_low( &ctx->a0 );
            break;
        }
        case MUX2_CHANNEL_S8:
        {
            digital_out_high( &ctx->a2 );
            digital_out_high( &ctx->a1 );
            digital_out_high( &ctx->a0 );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END

