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
 * @file brushless9.c
 * @brief Brushless 9 Click Driver.
 */

#include "brushless9.h"

void brushless9_cfg_setup ( brushless9_cfg_t *cfg ) 
{
    // Communication gpio pins

    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins

    cfg->fg   = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->brk   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->dev_pwm_freq = BRUSHLESS9_DEF_FREQ;
}

err_t brushless9_init ( brushless9_t *ctx, brushless9_cfg_t *cfg ) 
{
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->brk, cfg->brk );

    // Input pins
    digital_in_init( &ctx->fg, cfg->fg );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PWM_SUCCESS;
}

err_t brushless9_set_duty_cycle ( brushless9_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless9_pwm_stop ( brushless9_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless9_pwm_start ( brushless9_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void brushless9_set_dir ( brushless9_t *ctx, uint8_t state )
{
    if ( state > 0 )
    {
        digital_out_high( &ctx->dir );
    }
    else
    {
        digital_out_low( &ctx->dir );
    }
}

void brushless9_set_brk ( brushless9_t *ctx, uint8_t state )
{
    if ( state > 0 )
    {
        digital_out_high( &ctx->brk );
    }
    else
    {
        digital_out_low( &ctx->brk );
    }    
}

uint8_t brushless9_get_fg ( brushless9_t *ctx )
{
    return digital_in_read( &ctx->fg );
}

uint8_t brushless9_get_int_pin ( brushless9_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
