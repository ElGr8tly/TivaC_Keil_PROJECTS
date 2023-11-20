#ifndef _GPIO_INTERFACE_H__
#define _GPIO_INTERFACE_H__
/************************************************************************/
/************************************************************************/
typedef void (ptr_Func_gpioCallBack_t) (void);
/************************************************************************/
typedef enum
{
	/************************************************************************/
	GPIO_OK = STATE_OK      ,  /* STATE_OK From LIB  #include "error_check.h" */
	GPIO_WRONG_INPUT_VALUE  ,
	GPIO_WRONG_INPUT_NULL   ,
	GPIO_NOT_INITIALIZED_OR_LOCKED,
	/************************************************************************/
} enu_gpioErrorState_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
	GPIO_UNLOCK ,
	GPIO_LOCK   ,
	/************************************************************************/
} enu_gpioPinsLock_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
	GPIO_DIRECTION_INPUT = 0,
	GPIO_DIRECTION_OUTPUT   ,
	/************************************************************************/
} enu_gpioPinDirection_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
	GPIO_INPUT_NO_DRIVE   = 0,
	/************************************************************************/
	GPIO_OUTPUT_DRIVE_2MA = 1, //Default as Output
	GPIO_OUTPUT_DRIVE_4MA    ,
	GPIO_OUTPUT_DRIVE_8MA    ,
	/************************************************************************/
} enu_gpioPinDrive_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
	GPIO_FLOATING = 0 ,
	GPIO_PULLUP       , 
	GPIO_PULLDOWN     ,
	/************************************************************************/
} enu_gpioPullMode_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
	GPIO_MODE_DIGITAL = 0,
	GPIO_MODE_ANALOG     ,
	GPIO_MODE_AF         ,
	/************************************************************************/
} enu_gpioPinModeConfig_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
	GPIO_NO_INTERRUPT = 0,
	GPIO_RISING_EDGE     ,
	GPIO_FALLING_EDGE    ,
	GPIO_BOTH_EDGES      ,
	/************************************************************************/
} enu_gpioInterruptMode_t;
/************************************************************************/
typedef enum
{
	/************************************************************************/
	GPIO_PORTA = 0,
	GPIO_PORTB    ,
	GPIO_PORTC    ,
	GPIO_PORTD    ,
	GPIO_PORTE    ,
	GPIO_PORTF    ,
	/************************************************************************/
} enu_gpioPort_t;
/************************************************************************/
typedef enum  /* You Can Use It As Group Of Pins = (GPIO_PIN_0 | GPIO_PIN_5 | GPIO_PIN_6) And So On */
{
	/************************************************************************/
	GPIO_NO_PIN     = 0,
	/************************************************************************/
	GPIO_PIN_0      = 0b1,
	GPIO_PIN_1      = 0b10,
	GPIO_PIN_2      = 0b100,
	GPIO_PIN_3      = 0b1000,
	GPIO_PIN_4      = 0b10000,
	GPIO_PIN_5      = 0b100000,
	GPIO_PIN_6      = 0b1000000,
	GPIO_PIN_7      = 0b10000000,
	/************************************************************************/
	GPIO_ALL_PINS   = 0xFF,
	GPIO_P0_TO_P3   = 0x0F,
	GPIO_P4_TO_P7   = 0xF0,
	/************************************************************************/
} enu_gpioPins_t;
/************************************************************************/
typedef enum  /* You Can Use Value From 0 to 255 For Chosen Pins and Can Use Low or High Level For All Chosen Pins */
{
	/************************************************************************/
	GPIO_MAX_VALUE  = 0x0FF,
	GPIO_LOW_LEVEL  = 0x100,
	GPIO_HIGH_LEVEL = 0x101,
	/************************************************************************/
} enu_gpioLevelOrValue_t;
/************************************************************************/
/*************************      GPIO STRUCT       ***********************/
/************************************************************************/
typedef struct
{/************************************************************************/
	enu_gpioPort_t 			  enu_gpioPort;
	enu_gpioPins_t 			  enu_gpioPinOrGroup;
	enu_gpioPinModeConfig_t   enu_modeConfig;
	enu_gpioPinDirection_t 	  enu_direction;
	enu_gpioPinDrive_t 		  enu_pinDrive;
	enu_gpioPullMode_t 		  enu_pullMode;
	enu_gpioInterruptMode_t   enu_interruptMode;
} str_gpioPinOrGroupOfPins_t;
/************************************************************************/
/***********************      GPIO FUNCTIONS      ***********************/
/************************************************************************/
enu_gpioErrorState_t gpio_init(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup , enu_gpioPinsLock_t enu_gpioPinsLock );
enu_gpioErrorState_t gpio_deinit(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup );
/************************************************************************/
enu_gpioErrorState_t gpio_lockAndUnlockPins(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup , enu_gpioPinsLock_t enu_gpioPinsLock );
enu_gpioErrorState_t gpio_callBackSinglePinInterrupt(enu_gpioPort_t enu_gpioPort,enu_gpioPins_t enu_gpioPin,ptr_Func_gpioCallBack_t*  ptr_func_interruptCallBack);
/************************************************************************/
enu_gpioErrorState_t gpio_write(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup , enu_gpioLevelOrValue_t  enu_gpioLevelOrValue);
enu_gpioErrorState_t gpio_read(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup , enu_gpioLevelOrValue_t  * enu_gpioLevelOrValue);
enu_gpioErrorState_t gpio_toggle(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup);
/************************************************************************/
/******************************   END   *********************************/
/************************************************************************/
#endif