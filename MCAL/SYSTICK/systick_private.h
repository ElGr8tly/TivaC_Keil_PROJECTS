#ifndef __SYSTICK_PERIPH_H__

#define __SYSTICK_PERIPH_H__
/************************************************************************/
/************************************************************************/
#include "systick_config.h" 
/************************************************************************/
#define TICKS_FOR_ONE_MICRO_SECOND         4
#define _ONE_TICK_                         1
#define _START_TICK_                       1
/************************************************************************/
#if !defined(_DISABLE_)
#define _DISABLE_                          0
#endif
/************************************************************************/
#if !defined(_ENABLE_)
#define _ENABLE_                           1
#endif
/************************************************************************/
#define _AHB_CLOCK_                        0
#define _APB_CLOCK_                        1
/************************************************************************/
#define _POLLING_MODE_                     0
#define _INTERRUPT_MODE_                   1
/************************************************************************/
typedef enum
{	
	/************************************************************************/
   ENABLE_SYSTICK_BIT = 0 ,	
   INT_ENABLE_BIT         ,
   CLK_SOURCE_BIT         ,	
   COUNT_FLAG_BIT     = 16,	
	/************************************************************************/
}enu_systickSTCTRLBits_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
   STCTRL_CONFIG  = 0,	
   STRELOAD_CONFIG   ,	
   STCURRENT_CONFIG  ,	
	/************************************************************************/
}enu_systickREG_t;
/************************************************************************/
#define SYSTICK_CONFIG( _REG_ )	            ( *((volatile uint32_t*)( 0xE000E010 + ((_REG_) * 4U) )) )
#define READ_STCTRL_REG( _BIT_ )            ( GET_BIT(SYSTICK_CONFIG(STCTRL_CONFIG) , _BIT_ ) )
#define READ_STCURRENT_REG()                (SYSTICK_CONFIG(STCURRENT_CONFIG))
/************************************************************************/
#define WRITE_STCTRL_REG( _BIT_ ,_VAL_)     (WRITE_BIT_VLAUE(SYSTICK_CONFIG(STCTRL_CONFIG) , _VAL_ , _BIT_ ) )
#define WRITE_STRELOAD_REG( _VAL_ )         (WRITE_BITS_VLAUE(SYSTICK_CONFIG(STRELOAD_CONFIG),0x00FFFFFF, _VAL_ , 0U ))
#define WRITE_STCURRENT_REG( _VAL_ )        (WRITE_BITS_VLAUE(SYSTICK_CONFIG(STCURRENT_CONFIG),0x00FFFFFF, _VAL_ , 0U ))
/************************************************************************/
/************************************************************************/
#endif