/************************************************************************/
/*                         INCLUDE FROM LIB                             */
/************************************************************************/
#include "..\..\LIB\error_check.h"
/************************************************************************/
/*                         INCLUDE FROM GPIO                            */
/************************************************************************/
#include "..\..\MCAL\GPIO\gpio_interface.h"
/************************************************************************/
/*                         INCLUDE FROM LED                             */
/************************************************************************/
#include "button_interface.h"
/*************************************************************************************/
/*******************************   buttons_init    ***********************************/
/*************************************************************************************/
enu_buttonsErrorState_t buttons_init(const str_buttonsConfig_t * str_ptr_buttonOrGroup)
{
	/************************************************************************/
	enu_buttonsErrorState_t enu_l_retFunction = BUTTONS_OK;
	str_gpioPinOrGroupOfPins_t str_l_gpioPinOrGroupOfPins = { 0 };
	/************************************************************************/
	if (ERROR_CHECK(str_ptr_buttonOrGroup != NULL) == BUTTONS_OK)
	{
		/************************************************************************/
		if (!ERROR_CHECK((uint8_t)str_ptr_buttonOrGroup->enu_buttonsPort <= BUTTONS_PORTF                          )&&
			  !ERROR_CHECK((uint8_t)str_ptr_buttonOrGroup->enu_buttonsPinOrGroup != BUTTON_NO_PIN_SELECTED           )&&
			  !ERROR_CHECK((uint8_t)str_ptr_buttonOrGroup->enu_buttonsPullMode <= BUTTONS_INTRTNAL_PULL_DOWN         )&&
        !ERROR_CHECK((uint8_t)str_ptr_buttonOrGroup->enu_buttonsInterruptMode <= BUTTONS_CHANGE_BOTH_EDGES     ))
		{/************************************************************************/
			str_l_gpioPinOrGroupOfPins.enu_gpioPort       = str_ptr_buttonOrGroup->enu_buttonsPort;
			str_l_gpioPinOrGroupOfPins.enu_gpioPinOrGroup = str_ptr_buttonOrGroup->enu_buttonsPinOrGroup;
			str_l_gpioPinOrGroupOfPins.enu_modeConfig     = GPIO_MODE_DIGITAL;
			str_l_gpioPinOrGroupOfPins.enu_direction      = GPIO_DIRECTION_INPUT;
			str_l_gpioPinOrGroupOfPins.enu_pinDrive       = GPIO_INPUT_NO_DRIVE;
			str_l_gpioPinOrGroupOfPins.enu_pullMode       = str_ptr_buttonOrGroup->enu_buttonsPullMode;
			str_l_gpioPinOrGroupOfPins.enu_interruptMode  = str_ptr_buttonOrGroup->enu_buttonsInterruptMode;
			/************************************************************************/
			enu_l_retFunction |= gpio_init(&str_l_gpioPinOrGroupOfPins, GPIO_UNLOCK);
		}/************************************************************************/
		else
		{/************************************************************************/
			enu_l_retFunction = BUTTONS_WRONG_INPUT_VALUE;
		}/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = BUTTONS_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/*******************************   buttons_deinit    ************************************/
/*************************************************************************************/
enu_buttonsErrorState_t buttons_deinit(const str_buttonsConfig_t * str_ptr_buttonOrGroup)
{
	/************************************************************************/
	enu_buttonsErrorState_t enu_l_retFunction = BUTTONS_OK;
	str_gpioPinOrGroupOfPins_t str_l_gpioPinOrGroupOfPins = { 0 };
	/************************************************************************/
	if (ERROR_CHECK(str_ptr_buttonOrGroup != NULL) == BUTTONS_OK)
	{
		/************************************************************************/
		if (!ERROR_CHECK((uint8_t)str_ptr_buttonOrGroup->enu_buttonsPort <= BUTTONS_PORTF                          )&&
			!ERROR_CHECK((uint8_t)str_ptr_buttonOrGroup->enu_buttonsPinOrGroup != BUTTON_NO_PIN_SELECTED           )&&
			!ERROR_CHECK((uint8_t)str_ptr_buttonOrGroup->enu_buttonsPullMode <= BUTTONS_INTRTNAL_PULL_DOWN         )&&
            !ERROR_CHECK((uint8_t)str_ptr_buttonOrGroup->enu_buttonsInterruptMode <= BUTTONS_CHANGE_BOTH_EDGES     ))
		{/************************************************************************/
			str_l_gpioPinOrGroupOfPins.enu_gpioPort       = str_ptr_buttonOrGroup->enu_buttonsPort;
			str_l_gpioPinOrGroupOfPins.enu_gpioPinOrGroup = str_ptr_buttonOrGroup->enu_buttonsPinOrGroup;
			str_l_gpioPinOrGroupOfPins.enu_modeConfig     = GPIO_MODE_DIGITAL;
			str_l_gpioPinOrGroupOfPins.enu_direction      = GPIO_DIRECTION_INPUT;
			str_l_gpioPinOrGroupOfPins.enu_pinDrive       = GPIO_INPUT_NO_DRIVE;
			str_l_gpioPinOrGroupOfPins.enu_pullMode       = str_ptr_buttonOrGroup->enu_buttonsPullMode;
			str_l_gpioPinOrGroupOfPins.enu_interruptMode  = str_ptr_buttonOrGroup->enu_buttonsInterruptMode;
			/************************************************************************/
			enu_l_retFunction |= gpio_deinit(&str_l_gpioPinOrGroupOfPins);
		}/************************************************************************/
		else
		{/************************************************************************/
			enu_l_retFunction = BUTTONS_WRONG_INPUT_VALUE;
		}/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = BUTTONS_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/******************   buttons_callBackSingleButtonInterrupt   ************************/
/*************************************************************************************/
enu_buttonsErrorState_t buttons_callBackSingleButtonInterrupt(enu_buttonsPort_t enu_buttonsPort,enu_buttonPinOrButtonsGroup_t enu_buttonsPin,ptr_Func_buttonsCallBack_t*  ptr_func_interruptCallBack)
{
    	/************************************************************************/
	enu_buttonsErrorState_t enu_l_retFunction = BUTTONS_OK;
	str_gpioPinOrGroupOfPins_t str_l_gpioPinOrGroupOfPins = { 0 };
	/************************************************************************/
	if (ERROR_CHECK(ptr_func_interruptCallBack != NULL) == BUTTONS_OK)
	{
		/************************************************************************/
		if (!ERROR_CHECK((uint8_t)enu_buttonsPort <= BUTTONS_PORTF))
            {
                switch (enu_buttonsPin)
                {
                    case BUTTON_P0:{/* Do Nothing */}
                    case BUTTON_P1:{/* Do Nothing */}   
                    case BUTTON_P2:{/* Do Nothing */}
                    case BUTTON_P3:{/* Do Nothing */}
                    case BUTTON_P4:{/* Do Nothing */}
                    case BUTTON_P5:{/* Do Nothing */}
                    case BUTTON_P6:{/* Do Nothing */}
                    case BUTTON_P7:
                    {/************************************************************************/
                        gpio_callBackSinglePinInterrupt(enu_buttonsPort,enu_buttonsPin,ptr_func_interruptCallBack);
                    }/************************************************************************/
                    break;           
                    default: /* This Value mean Not Single Button */
                    {/************************************************************************/
                        enu_l_retFunction = ERROR_CHECK(FALSE); /* BUTTONS_WRONG_INPUT_VALUE */
                    }/************************************************************************/
                    break;
                }/************************************************************************/
            }
		    else
		    {/************************************************************************/
			    enu_l_retFunction = BUTTONS_WRONG_INPUT_VALUE;
		    }/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = BUTTONS_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/*****************************   buttons_readStatus   ********************************/
/*************************************************************************************/
enu_buttonsErrorState_t buttons_readStatus(const str_buttonsConfig_t * str_ptr_buttonOrGroup , enu_buttonsStatus_t * enu_buttonsStatus)
{
	/************************************************************************/
	enu_buttonsErrorState_t enu_l_retFunction = BUTTONS_OK;
	str_gpioPinOrGroupOfPins_t str_l_gpioPinOrGroupOfPins = { 0 };
	/************************************************************************/
	if (ERROR_CHECK((str_ptr_buttonOrGroup != NULL)&&(enu_buttonsStatus != NULL)) == BUTTONS_OK)
	{
		/************************************************************************/
		if (!ERROR_CHECK((uint8_t)str_ptr_buttonOrGroup->enu_buttonsPort <= BUTTONS_PORTF                )&&
			!ERROR_CHECK((uint8_t)str_ptr_buttonOrGroup->enu_buttonsPinOrGroup != BUTTON_NO_PIN_SELECTED ))
		{/************************************************************************/
			str_l_gpioPinOrGroupOfPins.enu_gpioPort       = str_ptr_buttonOrGroup->enu_buttonsPort;
			str_l_gpioPinOrGroupOfPins.enu_gpioPinOrGroup = str_ptr_buttonOrGroup->enu_buttonsPinOrGroup;
			str_l_gpioPinOrGroupOfPins.enu_modeConfig     = GPIO_MODE_DIGITAL;
			str_l_gpioPinOrGroupOfPins.enu_direction      = GPIO_DIRECTION_INPUT;
			str_l_gpioPinOrGroupOfPins.enu_pinDrive       = GPIO_INPUT_NO_DRIVE;
			str_l_gpioPinOrGroupOfPins.enu_pullMode       = str_ptr_buttonOrGroup->enu_buttonsPullMode;
			str_l_gpioPinOrGroupOfPins.enu_interruptMode  = str_ptr_buttonOrGroup->enu_buttonsInterruptMode;
			/************************************************************************/
			enu_l_retFunction |= gpio_read(&str_l_gpioPinOrGroupOfPins, enu_buttonsStatus);
		}/************************************************************************/
		else
		{/************************************************************************/
			enu_l_retFunction = BUTTONS_WRONG_INPUT_VALUE;
		}/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = BUTTONS_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/*********************   buttons_readSingleButtonStatus   ****************************/
/*************************************************************************************/
enu_buttonsErrorState_t buttons_readSingleButtonStatus(enu_buttonsPort_t enu_buttonsPort,enu_buttonPinOrButtonsGroup_t enu_buttonsPin, enu_buttonsStatus_t * enu_buttonsStatus)
{
	/************************************************************************/
	enu_buttonsErrorState_t enu_l_retFunction = BUTTONS_OK;
	str_gpioPinOrGroupOfPins_t str_l_gpioPinOrGroupOfPins = { 0 };
	/************************************************************************/
	if (ERROR_CHECK((enu_buttonsStatus != NULL)) == BUTTONS_OK)
	{
		/************************************************************************/
		if (!ERROR_CHECK((uint8_t)enu_buttonsPort <= BUTTONS_PORTF ))
		{/************************************************************************/
            switch (enu_buttonsPin)
            {
                case BUTTON_P0:{/* Do Nothing */}
                case BUTTON_P1:{/* Do Nothing */}   
                case BUTTON_P2:{/* Do Nothing */}
                case BUTTON_P3:{/* Do Nothing */}
                case BUTTON_P4:{/* Do Nothing */}
                case BUTTON_P5:{/* Do Nothing */}
                case BUTTON_P6:{/* Do Nothing */}
                case BUTTON_P7:
                {/************************************************************************/
			        str_l_gpioPinOrGroupOfPins.enu_gpioPort       = enu_buttonsPort;
			        str_l_gpioPinOrGroupOfPins.enu_gpioPinOrGroup = enu_buttonsPin;
			        str_l_gpioPinOrGroupOfPins.enu_modeConfig     = GPIO_MODE_DIGITAL;
			        str_l_gpioPinOrGroupOfPins.enu_direction      = GPIO_DIRECTION_INPUT;
			        str_l_gpioPinOrGroupOfPins.enu_pinDrive       = GPIO_INPUT_NO_DRIVE;
			        str_l_gpioPinOrGroupOfPins.enu_pullMode       = BUTTONS_EXTERNAL_PULL_RES;
			        str_l_gpioPinOrGroupOfPins.enu_interruptMode  = BUTTONS_NO_INTERRUPT;
			        /************************************************************************/
			        enu_l_retFunction |= gpio_read(&str_l_gpioPinOrGroupOfPins, enu_buttonsStatus);
                }/************************************************************************/
                break;           
                default: /* This Value mean Not Single Button */
                {/************************************************************************/
                    enu_l_retFunction = ERROR_CHECK(FALSE); /* BUTTONS_WRONG_INPUT_VALUE */
                }/************************************************************************/
                break;
            }/************************************************************************/
		}/************************************************************************/
		else
		{/************************************************************************/
			enu_l_retFunction = BUTTONS_WRONG_INPUT_VALUE;
		}/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = BUTTONS_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/*****************   buttons_readSingleButtonChange_Polling   ************************/
/*************************************************************************************/
enu_buttonsErrorState_t buttons_readSingleButtonChange_Polling(enu_buttonsPort_t enu_buttonsPort,enu_buttonPinOrButtonsGroup_t enu_buttonsPin, enu_buttonsStatus_t * enu_buttonsStatus)
{
	/************************************************************************/
	enu_buttonsErrorState_t enu_l_retFunction = BUTTONS_OK;
    enu_buttonsStatus_t enu_buttonsStatusTemp = 0 ;
	str_gpioPinOrGroupOfPins_t str_l_gpioPinOrGroupOfPins = { 0 };
	/************************************************************************/
	if (ERROR_CHECK((enu_buttonsStatus != NULL)) == BUTTONS_OK)
	{
		/************************************************************************/
		if (!ERROR_CHECK((uint8_t)enu_buttonsPort <= BUTTONS_PORTF ))
		{/************************************************************************/
            switch (enu_buttonsPin)
            {
                case BUTTON_P0:{/* Do Nothing */}
                case BUTTON_P1:{/* Do Nothing */}   
                case BUTTON_P2:{/* Do Nothing */}
                case BUTTON_P3:{/* Do Nothing */}
                case BUTTON_P4:{/* Do Nothing */}
                case BUTTON_P5:{/* Do Nothing */}
                case BUTTON_P6:{/* Do Nothing */}
                case BUTTON_P7:
                {/************************************************************************/
			        str_l_gpioPinOrGroupOfPins.enu_gpioPort       = enu_buttonsPort;
			        str_l_gpioPinOrGroupOfPins.enu_gpioPinOrGroup = enu_buttonsPin;
			        str_l_gpioPinOrGroupOfPins.enu_modeConfig     = GPIO_MODE_DIGITAL;
			        str_l_gpioPinOrGroupOfPins.enu_direction      = GPIO_DIRECTION_INPUT;
			        str_l_gpioPinOrGroupOfPins.enu_pinDrive       = GPIO_INPUT_NO_DRIVE;
			        str_l_gpioPinOrGroupOfPins.enu_pullMode       = BUTTONS_EXTERNAL_PULL_RES;
			        str_l_gpioPinOrGroupOfPins.enu_interruptMode  = BUTTONS_NO_INTERRUPT;
			        /************************************************************************/
			        enu_l_retFunction |= gpio_read(&str_l_gpioPinOrGroupOfPins, &enu_buttonsStatusTemp);
                    /************************************************************************/
                    if(enu_l_retFunction != BUTTONS_OK)
                    {/************************************************************************/
                        *enu_buttonsStatus = enu_buttonsStatusTemp;
                        /************************************************************************/
                        while(*enu_buttonsStatus == enu_buttonsStatusTemp)
                        {/************************************************************************/
                            gpio_read(&str_l_gpioPinOrGroupOfPins, &enu_buttonsStatusTemp);
                        }/************************************************************************/
                        *enu_buttonsStatus = enu_buttonsStatusTemp;
                    }/************************************************************************/
                    else
                    {/************************************************************************/
                        /* Do Nothing */
                    }/************************************************************************/
                }/************************************************************************/
                break;           
                default: /* Not Single Button*/
                {/************************************************************************/
                    enu_l_retFunction = ERROR_CHECK(FALSE); /* BUTTONS_WRONG_INPUT_VALUE */
                }/************************************************************************/
                break;
            }/************************************************************************/
		}/************************************************************************/
		else
		{/************************************************************************/
			enu_l_retFunction = BUTTONS_WRONG_INPUT_VALUE;
		}/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = BUTTONS_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/