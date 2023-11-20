#ifndef __GPIO_PRIVATE_H__
#define __GPIO_PRIVATE_H__
/****************************************************************************************/
#include "gpio_config.h"
/****************************************************************************************/                   
#if     GPIO_BUS        ==       GPIO_AHB
#define GPIO_PORT_OFFSET(_PORT_)	( (0x40058000 + (_PORT_) * 0x1000) )
/****************************************************************************************/
#elif   GPIO_BUS        ==       GPIO_APB
/****************************************************************************************/
#define GPIO_PORT_OFFSET(_PORT_)	( (0x40004000 + (_PORT_) * 0x1000) )
#define GPIO_PORT_E_F_OFFSET                       28
/****************************************************************************************/
#else
#error  "WRONG GPIO BUS"
#endif
/****************************************************************************************/
#define GPIO_REG_OFFSET(_REG_)	            ( ( 0x3FC + (_REG_) * 4 ) )
#define GPIO_BAND_OFFSET(_PIN_GROUP_)	      ( ( (_PIN_GROUP_) * 4 ) )
#define RCGCGPIO_CONFIG                     (*(volatile uint32_t*) 0x400FE608)
/****************************************************************************************/
typedef enum{
GPIODATA_CONFIG  = 0,	
GPIODIR_CONFIG      ,	
GPIOIS_CONFIG       ,	
GPIOIBE_CONFIG      ,	
GPIOIEV_CONFIG      ,	
GPIOIM_CONFIG       ,	
GPIORIS_CONFIG      ,	
GPIOMIS_CONFIG      ,	
GPIOICR_CONFIG      ,	
GPIOAFSEL_CONFIG    ,
GPIODR2R_CONFIG = 65,
GPIODR4R_CONFIG     ,
GPIODR8R_CONFIG     ,
GPIOODR_CONFIG      ,
GPIOPUR_CONFIG      ,
GPIOPDR_CONFIG      ,
GPIODEN_CONFIG  = 72,
GPIOAMSEL_CONFIG= 75,
GPIOPCTL_CONFIG     ,
}enu_gpioREGConfig_t;
/****************************************************************************************/
#define GPIO_DATA_BIT_BAND(_PORT_ , _PIN_GROUP_ )	   (*(volatile uint32_t*) (GPIO_PORT_OFFSET(_PORT_) + GPIO_BAND_OFFSET(_PIN_GROUP_)))
#define GPIO_CONFIG(_PORT_ , _REG_ )		             (*(volatile uint32_t*) (GPIO_PORT_OFFSET(_PORT_) + GPIO_REG_OFFSET(_REG_)))
/****************************************************************************************/
#define GPIO_MAX_PORT_NUM            6	
#define GPIO_MAX_PIN_NUM             8	
/****************************************************************************************/	
typedef struct
{ /* For Digital Initialized PINS */
	enu_gpioPinDirection_t 	  enu_gpioPinsdirection;
  enu_gpioPinModeConfig_t   enu_gpioPinsDigitalMode;
  enu_gpioPinsLock_t        enu_gpioPinsLock;
} str_gpioDigitalInitializedPins_t;
/****************************************************************************************/
typedef enum{
PIN_0 = 0,
PIN_1    ,
PIN_2    ,
PIN_3    ,
PIN_4    ,
PIN_5    ,
PIN_6    ,
PIN_7    ,
}enu_gpioNormalPins_t;
/****************************************************************************************/
#endif