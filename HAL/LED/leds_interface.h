
#ifndef _LED_INTERFACE_H_
#define _LED_INTERFACE_H_
/************************************************************************/
/************************************************************************/
typedef enum 
{
	/************************************************************************/
	LEDS_OK   =   STATE_OK, /* STATE_OK From LIB  #include "error_check.h" */
	LEDS_WRONG_INPUT_VALUE,
	LEDS_WRONG_INPUT_NULL ,
  LEDS_NOT_INITIALIZED  ,
	/************************************************************************/
}enu_ledsErrorState_t;
/************************************************************************/
typedef enum 
{
	/************************************************************************/
	LEDS_PORTA = 0,
	LEDS_PORTB	  ,
	LEDS_PORTC	  ,
	LEDS_PORTD	  ,
	LEDS_PORTE	  ,
	LEDS_PORTF	  ,
	/************************************************************************/
}enu_ledsPort_t;
/************************************************************************/
typedef enum  /* You Can Use It To Choose Group Of LEDs = (LED_P0 | LED_P5 | LED_P7 ) , Or Only One Led  */
{
	/************************************************************************/
	LED_NO_PIN_SELECTED = 0,
	/************************************************************************/
	LED_P0 = 0b1,
	LED_P1 = 0b10,
	LED_P2 = 0b100,
	LED_P3 = 0b1000,
	LED_P4 = 0b10000,
	LED_P5 = 0b100000,
	LED_P6 = 0b1000000,
	LED_P7 = 0b10000000,
	/************************************************************************/
	LEDS_ALL_PINS = 0xFF,
	LEDS_P0_TO_P3 = 0x0F,
	LEDS_P4_TO_P7 = 0xF0,
	/************************************************************************/
} enu_ledPinOrLedsGroup_t;
/************************************************************************/
typedef enum  /* You Can Operate Choosen Leds with Value From 0 to 255  or  Use On or Off State For All Choosen Leds */
{
	/************************************************************************/
	LEDS_STATUS_MAX_VALUE = 0x0FF,
	LEDS_STATUS_OFF       = 0x100,
	LEDS_STATUS_ON        = 0x101,
	/************************************************************************/
}enu_ledsStatus_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
	LEDS_ACTIVE_LOW  = 0,
	LEDS_ACTIVE_HIGH    ,
	/************************************************************************/
} enu_ledsActiveState_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
	LEDS_OPERATING_CURRENT_2MA = 0, //Default as Output
	LEDS_OPERATING_CURRENT_4MA	 ,
	LEDS_OPERATING_CURRENT_8MA	 ,
	/************************************************************************/
} enu_ledsOperatingCurrent_t;
/************************************************************************/
/*************************      LEDS STRUCT       ***********************/
/************************************************************************/
typedef struct 
{
	/************************************************************************/
	enu_ledsPort_t             enu_ledsPort;
	enu_ledPinOrLedsGroup_t    enu_ledsPinOrGroup;
	enu_ledsActiveState_t      enu_ledsActiveState;
	enu_ledsOperatingCurrent_t enu_ledsOperatingCurrent;
	/************************************************************************/
}str_ledsConfig_t;
/************************************************************************/
/***********************      LEDS FUNCTIONS      ***********************/
/************************************************************************/
enu_ledsErrorState_t leds_init(const str_ledsConfig_t * str_ptr_ledOrGroup);
enu_ledsErrorState_t leds_deinit(const str_ledsConfig_t * str_ptr_ledOrGroup);
enu_ledsErrorState_t leds_changeStatus(const str_ledsConfig_t * str_ptr_ledOrGroup , enu_ledsStatus_t enu_newLedsStatus);
enu_ledsErrorState_t leds_toggle(const str_ledsConfig_t* str_ptr_ledOrGroup);
/************************************************************************/
enu_ledsErrorState_t leds_changeSingleLEDStatus(enu_ledsPort_t enu_ledPort, enu_ledPinOrLedsGroup_t enu_ledPin,
	                                            enu_ledsActiveState_t enu_ledActiveState, enu_ledsStatus_t enu_newLedStatus);
/************************************************************************/
/******************************   END   *********************************/
/************************************************************************/
#endif /* _LED_INTERFACE_H_ */
