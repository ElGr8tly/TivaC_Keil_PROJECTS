
#ifndef _BUTTON_INTERFACE_H_
#define _BUTTON_INTERFACE_H_
/************************************************************************/
/************************************************************************/
typedef void (ptr_Func_buttonsCallBack_t) (void);
/************************************************************************/
typedef enum 
{
	/************************************************************************/
	BUTTONS_OK   =   STATE_OK, /* STATE_OK From LIB  #include "error_check.h" */
	BUTTONS_WRONG_INPUT_VALUE,
	BUTTONS_WRONG_INPUT_NULL ,
  BUTTONS_NOT_INITIALIZED  ,
	/************************************************************************/
}enu_buttonsErrorState_t;
/************************************************************************/
typedef enum 
{
	/************************************************************************/
	BUTTONS_PORTA = 0,
	BUTTONS_PORTB	  ,
	BUTTONS_PORTC	  ,
	BUTTONS_PORTD	  ,
	BUTTONS_PORTE	  ,
	BUTTONS_PORTF	  ,
	/************************************************************************/
}enu_buttonsPort_t;
/************************************************************************/
typedef enum  /* You Can Use It To Choose Group Of BUTTONs = (BUTTON_P0 | BUTTON_P5 | BUTTON_P7 ) , Or Only One BUTTON  */
{
	/************************************************************************/
	BUTTON_NO_PIN_SELECTED = 0,
	/************************************************************************/
	BUTTON_P0 = 0b1,
	BUTTON_P1 = 0b10,
	BUTTON_P2 = 0b100,
	BUTTON_P3 = 0b1000,
	BUTTON_P4 = 0b10000,
	BUTTON_P5 = 0b100000,
	BUTTON_P6 = 0b1000000,
	BUTTON_P7 = 0b10000000,
	/************************************************************************/
	BUTTONS_ALL_PINS = 0xFF,
	BUTTONS_P0_TO_P3 = 0x0F,
	BUTTONS_P4_TO_P7 = 0xF0,
	/************************************************************************/
} enu_buttonPinOrButtonsGroup_t;
/************************************************************************/
typedef enum  /* You Can Read From Choosen BUTTONs Value From 0 to 255  or  Read Low or High State Form All Choosen BUTTONs */
{
	/************************************************************************/
	BUTTONS_PIN_STATUS_MAX_VALUE = 0x0FF,
	BUTTONS_PIN_STATUS_LOW       = 0x100,
	BUTTONS_PIN_STATUS_HIGH      = 0x101,
	/************************************************************************/
}enu_buttonsStatus_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
	BUTTONS_EXTERNAL_PULL_RES  = 0,
	BUTTONS_INTRTNAL_PULL_UP      ,
    BUTTONS_INTRTNAL_PULL_DOWN    ,
	/************************************************************************/
} enu_buttonsPullMode_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
	BUTTONS_NO_INTERRUPT    = 0,
	BUTTONS_CHANGE_RISING_EDGE ,
	BUTTONS_CHANGE_FALLING_EDGE,
	BUTTONS_CHANGE_BOTH_EDGES  ,
	/************************************************************************/
} enu_buttonsInterruptMode_t;
/************************************************************************/
/**********************      BUTTONS STRUCT       ***********************/
/************************************************************************/
typedef struct 
{
	/************************************************************************/
	enu_buttonsPort_t                enu_buttonsPort;
	enu_buttonPinOrButtonsGroup_t    enu_buttonsPinOrGroup;
	enu_buttonsPullMode_t            enu_buttonsPullMode;
  enu_buttonsInterruptMode_t       enu_buttonsInterruptMode;
	/************************************************************************/
}str_buttonsConfig_t;
/************************************************************************/
/***********************      BUTTONS FUNCTIONS      ***********************/
/************************************************************************/
enu_buttonsErrorState_t buttons_init(const str_buttonsConfig_t * str_ptr_buttonOrGroup);
enu_buttonsErrorState_t buttons_deinit(const str_buttonsConfig_t * str_ptr_buttonOrGroup);
/************************************************************************/
enu_buttonsErrorState_t buttons_callBackSingleButtonInterrupt(enu_buttonsPort_t enu_buttonsPort,enu_buttonPinOrButtonsGroup_t enu_buttonsPin,ptr_Func_buttonsCallBack_t*  ptr_func_interruptCallBack);
/************************************************************************/
enu_buttonsErrorState_t buttons_readStatus(const str_buttonsConfig_t * str_ptr_buttonOrGroup , enu_buttonsStatus_t * enu_buttonsStatus);
/************************************************************************/
enu_buttonsErrorState_t buttons_readSingleButtonStatus(enu_buttonsPort_t enu_buttonsPort,enu_buttonPinOrButtonsGroup_t enu_buttonsPin, enu_buttonsStatus_t * enu_buttonsStatus);
enu_buttonsErrorState_t buttons_readSingleButtonChange_Polling(enu_buttonsPort_t enu_buttonsPort,enu_buttonPinOrButtonsGroup_t enu_buttonsPin, enu_buttonsStatus_t * enu_buttonsStatus);
/************************************************************************/
/******************************   END   *********************************/
/************************************************************************/
#endif /* _BUTTON_INTERFACE_H_ */
