#ifndef _RGB_INTERFACE_H_
#define _RGB_INTERFACE_H_
/************************************************************************/
/*                         INCLUDE FROM RGB                             */
/************************************************************************/
#include "rgb_led_config.h"
/************************************************************************/
typedef enum 
{
	/************************************************************************/
	RGB_OK   =   STATE_OK, /* STATE_OK From LIB  #include "error_check.h" */
	RGB_WRONG_INPUT_VALUE,
	RGB_WRONG_INPUT_NULL , /* Not USED */
  RGB_NOT_INITIALIZED  ,
	/************************************************************************/
}enu_rgbErrorState_t;
/************************************************************************/
typedef enum  
{
	/************************************************************************/
	RGB_TURN_OFF       = 0,
	RGB_RED_ON         = RED_PIN,
	RGB_GREEN_ON       = GREEN_PIN,
	RGB_BLUE_ON        = BLUE_PIN,                                    
	RGB_RED_GREEN_ON   = RGB_RED_ON|RGB_GREEN_ON        ,
  RGB_RED_BLUE_ON    = RGB_RED_ON|RGB_BLUE_ON        ,
  RGB_GREEN_BLUE_ON  = RGB_GREEN_ON|RGB_BLUE_ON      ,
  RGB_RED_GREEN_BLUE_ON = RGB_RED_ON|RGB_GREEN_ON|RGB_BLUE_ON,
	/************************************************************************/
}enu_rgbColorON_t;
/************************************************************************/

/************************************************************************/
/***********************      rgb FUNCTIONS      ***********************/
/************************************************************************/
enu_rgbErrorState_t rgb_init(void);
enu_rgbErrorState_t rgb_deinit(void);
enu_rgbErrorState_t rgb_changeColor(enu_rgbColorON_t enu_rgbColorON);
/************************************************************************/
/******************************   END   *********************************/
/************************************************************************/
#endif /* _RGB_INTERFACE_H_ */
