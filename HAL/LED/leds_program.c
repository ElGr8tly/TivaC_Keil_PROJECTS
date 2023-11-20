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
#include "leds_interface.h"
/*************************************************************************************/
/*********************************   leds_init    ************************************/
/*************************************************************************************/
enu_ledsErrorState_t leds_init(const str_ledsConfig_t* str_ptr_ledOrGroup)
{
	/************************************************************************/
	enu_gpioErrorState_t enu_l_retFunction = LEDS_OK;
	str_gpioPinOrGroupOfPins_t str_l_gpioPinOrGroupOfPins = { 0 };
	/************************************************************************/
	if (ERROR_CHECK(str_ptr_ledOrGroup != NULL) == LEDS_OK)
	{
		/************************************************************************/
		if (!ERROR_CHECK((uint8_t)str_ptr_ledOrGroup->enu_ledsPort <= LEDS_PORTF                             )&&
			!ERROR_CHECK((uint8_t)str_ptr_ledOrGroup->enu_ledsPinOrGroup != LED_NO_PIN_SELECTED              )&&
			!ERROR_CHECK((uint8_t)str_ptr_ledOrGroup->enu_ledsOperatingCurrent <= LEDS_OPERATING_CURRENT_8MA ))
		{/************************************************************************/
			str_l_gpioPinOrGroupOfPins.enu_gpioPort       = str_ptr_ledOrGroup->enu_ledsPort;
			str_l_gpioPinOrGroupOfPins.enu_gpioPinOrGroup = str_ptr_ledOrGroup->enu_ledsPinOrGroup;
			str_l_gpioPinOrGroupOfPins.enu_modeConfig     = GPIO_MODE_DIGITAL;
			str_l_gpioPinOrGroupOfPins.enu_direction      = GPIO_DIRECTION_OUTPUT;
			str_l_gpioPinOrGroupOfPins.enu_pinDrive       = str_ptr_ledOrGroup->enu_ledsOperatingCurrent;
			str_l_gpioPinOrGroupOfPins.enu_pullMode       = GPIO_FLOATING;
			str_l_gpioPinOrGroupOfPins.enu_interruptMode  = GPIO_NO_INTERRUPT;
			/************************************************************************/
			enu_l_retFunction |= gpio_init(&str_l_gpioPinOrGroupOfPins, GPIO_UNLOCK);
		}/************************************************************************/
		else
		{/************************************************************************/
			enu_l_retFunction = LEDS_WRONG_INPUT_VALUE;
		}/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = LEDS_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/*******************************   leds_deinit    ************************************/
/*************************************************************************************/
enu_ledsErrorState_t leds_deinit(const str_ledsConfig_t * str_ptr_ledOrGroup)
{
	/************************************************************************/
	enu_gpioErrorState_t enu_l_retFunction = LEDS_OK;
	str_gpioPinOrGroupOfPins_t str_l_gpioPinOrGroupOfPins = { 0 };
	/************************************************************************/
	if (ERROR_CHECK(str_ptr_ledOrGroup != NULL) == LEDS_OK)
	{
		/************************************************************************/
		if (!ERROR_CHECK((uint8_t)str_ptr_ledOrGroup->enu_ledsPort <= LEDS_PORTF                             )&&
			!ERROR_CHECK((uint8_t)str_ptr_ledOrGroup->enu_ledsPinOrGroup != LED_NO_PIN_SELECTED              )&&
			!ERROR_CHECK((uint8_t)str_ptr_ledOrGroup->enu_ledsOperatingCurrent <= LEDS_OPERATING_CURRENT_8MA ))
		{/************************************************************************/
			str_l_gpioPinOrGroupOfPins.enu_gpioPort       = str_ptr_ledOrGroup->enu_ledsPort;
			str_l_gpioPinOrGroupOfPins.enu_gpioPinOrGroup = str_ptr_ledOrGroup->enu_ledsPinOrGroup;
			str_l_gpioPinOrGroupOfPins.enu_modeConfig     = GPIO_MODE_DIGITAL;
			str_l_gpioPinOrGroupOfPins.enu_direction      = GPIO_DIRECTION_OUTPUT;
			str_l_gpioPinOrGroupOfPins.enu_pinDrive       = str_ptr_ledOrGroup->enu_ledsOperatingCurrent;
			str_l_gpioPinOrGroupOfPins.enu_pullMode       = GPIO_FLOATING;
			str_l_gpioPinOrGroupOfPins.enu_interruptMode  = GPIO_NO_INTERRUPT;
			/************************************************************************/
			enu_l_retFunction |= gpio_deinit(&str_l_gpioPinOrGroupOfPins);
		}/************************************************************************/
		else
		{/************************************************************************/
			enu_l_retFunction = LEDS_WRONG_INPUT_VALUE;
		}/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = LEDS_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/*****************************   leds_changeStatus    ********************************/
/*************************************************************************************/
enu_ledsErrorState_t leds_changeStatus(const str_ledsConfig_t* str_ptr_ledOrGroup, enu_ledsStatus_t enu_newLedsStatus)
{
	/************************************************************************/
	enu_gpioErrorState_t enu_l_retFunction = LEDS_OK;
	str_gpioPinOrGroupOfPins_t str_l_gpioPinOrGroupOfPins = { 0 };
	/************************************************************************/
	if (ERROR_CHECK(str_ptr_ledOrGroup != NULL) == LEDS_OK)
	{
		/************************************************************************/
		if (!ERROR_CHECK((uint8_t)str_ptr_ledOrGroup->enu_ledsPort <= LEDS_PORTF                )&&
			!ERROR_CHECK((uint8_t)str_ptr_ledOrGroup->enu_ledsPinOrGroup != LED_NO_PIN_SELECTED )&&
			!ERROR_CHECK((uint8_t)str_ptr_ledOrGroup->enu_ledsActiveState <= LEDS_ACTIVE_HIGH   )&&
			!ERROR_CHECK((uint16_t)enu_newLedsStatus      <=          LEDS_STATUS_ON            ))
		{/************************************************************************/
			str_l_gpioPinOrGroupOfPins.enu_gpioPort       = str_ptr_ledOrGroup->enu_ledsPort;
			str_l_gpioPinOrGroupOfPins.enu_gpioPinOrGroup = str_ptr_ledOrGroup->enu_ledsPinOrGroup;
			str_l_gpioPinOrGroupOfPins.enu_modeConfig     = GPIO_MODE_DIGITAL;
			str_l_gpioPinOrGroupOfPins.enu_direction      = GPIO_DIRECTION_OUTPUT;
			str_l_gpioPinOrGroupOfPins.enu_pinDrive       = str_ptr_ledOrGroup->enu_ledsOperatingCurrent;
			str_l_gpioPinOrGroupOfPins.enu_pullMode       = GPIO_FLOATING;
			str_l_gpioPinOrGroupOfPins.enu_interruptMode  = GPIO_NO_INTERRUPT;
			/************************************************************************/
			switch (enu_newLedsStatus)
			{/************************************************************************/
			    case LEDS_STATUS_ON:
			    {/************************************************************************/
			    	if (str_ptr_ledOrGroup->enu_ledsActiveState == LEDS_ACTIVE_HIGH)
			    	{/************************************************************************/
			    		enu_l_retFunction |= gpio_write(&str_l_gpioPinOrGroupOfPins, LEDS_STATUS_ON );
			    	}/************************************************************************/
			    	else
			    	{/************************************************************************/
			    		enu_l_retFunction |= gpio_write(&str_l_gpioPinOrGroupOfPins, LEDS_STATUS_OFF);
			    	}/************************************************************************/
			    }/************************************************************************/
			    break;
			    case LEDS_STATUS_OFF:
			    {/************************************************************************/
			    	if (str_ptr_ledOrGroup->enu_ledsActiveState == LEDS_ACTIVE_HIGH)
			    	{/************************************************************************/
			    		enu_l_retFunction |= gpio_write(&str_l_gpioPinOrGroupOfPins, LEDS_STATUS_OFF);
			    	}/************************************************************************/
			    	else
			    	{/************************************************************************/
			    		enu_l_retFunction |= gpio_write(&str_l_gpioPinOrGroupOfPins, LEDS_STATUS_ON );
			    	}/************************************************************************/
			    }/************************************************************************/
			    break;
			    default:
			    {/************************************************************************/
			    	enu_l_retFunction |= gpio_write(&str_l_gpioPinOrGroupOfPins, enu_newLedsStatus);
			    }/************************************************************************/
			    break;
			}/************************************************************************/
		}/************************************************************************/
		else
		{/************************************************************************/
			enu_l_retFunction = LEDS_WRONG_INPUT_VALUE;
		}/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = LEDS_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/********************************   leds_toggle    ***********************************/
/*************************************************************************************/
enu_ledsErrorState_t leds_toggle(const str_ledsConfig_t* str_ptr_ledOrGroup)
{
	/************************************************************************/
	enu_gpioErrorState_t enu_l_retFunction = LEDS_OK;
	str_gpioPinOrGroupOfPins_t str_l_gpioPinOrGroupOfPins = { 0 };
	/************************************************************************/
	if (ERROR_CHECK(str_ptr_ledOrGroup != NULL) == LEDS_OK)
	{
		/************************************************************************/
		if (!ERROR_CHECK((uint8_t)str_ptr_ledOrGroup->enu_ledsPort <= LEDS_PORTF                )&&
			!ERROR_CHECK((uint8_t)str_ptr_ledOrGroup->enu_ledsPinOrGroup != LED_NO_PIN_SELECTED ))
		{/************************************************************************/
			str_l_gpioPinOrGroupOfPins.enu_gpioPort       = str_ptr_ledOrGroup->enu_ledsPort;
			str_l_gpioPinOrGroupOfPins.enu_gpioPinOrGroup = str_ptr_ledOrGroup->enu_ledsPinOrGroup;
			str_l_gpioPinOrGroupOfPins.enu_modeConfig     = GPIO_MODE_DIGITAL;
			str_l_gpioPinOrGroupOfPins.enu_direction      = GPIO_DIRECTION_OUTPUT;
			str_l_gpioPinOrGroupOfPins.enu_pinDrive       = str_ptr_ledOrGroup->enu_ledsOperatingCurrent;
			str_l_gpioPinOrGroupOfPins.enu_pullMode       = GPIO_FLOATING;
			str_l_gpioPinOrGroupOfPins.enu_interruptMode  = GPIO_NO_INTERRUPT;
			/************************************************************************/
			enu_l_retFunction |= gpio_toggle(&str_l_gpioPinOrGroupOfPins);
		}/************************************************************************/
		else
		{/************************************************************************/
			enu_l_retFunction = LEDS_WRONG_INPUT_VALUE;
		}/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = LEDS_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/************************************************************************/
/*************************************************************************************/
/************************    leds_changeSingleLEDStatus    ***************************/
/*************************************************************************************/
enu_ledsErrorState_t leds_changeSingleLEDStatus(enu_ledsPort_t enu_ledPort, enu_ledPinOrLedsGroup_t enu_ledPin, enu_ledsActiveState_t enu_ledActiveState, enu_ledsStatus_t enu_newLedStatus)
{
	/************************************************************************/
	enu_gpioErrorState_t enu_l_retFunction = LEDS_OK;
	str_gpioPinOrGroupOfPins_t str_l_gpioPinOrGroupOfPins = { 0 };
	/************************************************************************/
/************************************************************************/
		if (!ERROR_CHECK((uint8_t)enu_ledPort <= LEDS_PORTF              )&&
			!ERROR_CHECK((uint8_t)enu_ledActiveState <= LEDS_ACTIVE_HIGH )&&
			!ERROR_CHECK((uint16_t)enu_newLedStatus <= LEDS_STATUS_ON       ))
		{/************************************************************************/
			switch (enu_ledPin)
			{
			case LED_P0: {/* Do Nothing */}
			case LED_P1: {/* Do Nothing */}
			case LED_P2: {/* Do Nothing */}
			case LED_P3: {/* Do Nothing */}
			case LED_P4: {/* Do Nothing */}
			case LED_P5: {/* Do Nothing */}
			case LED_P6: {/* Do Nothing */}
			case LED_P7:
			{/************************************************************************/
				str_l_gpioPinOrGroupOfPins.enu_gpioPort       = enu_ledPort;
				str_l_gpioPinOrGroupOfPins.enu_gpioPinOrGroup = enu_ledPin;
				str_l_gpioPinOrGroupOfPins.enu_modeConfig     = GPIO_MODE_DIGITAL;
				str_l_gpioPinOrGroupOfPins.enu_direction      = GPIO_DIRECTION_OUTPUT;
				str_l_gpioPinOrGroupOfPins.enu_pinDrive       = LEDS_OPERATING_CURRENT_2MA;
				str_l_gpioPinOrGroupOfPins.enu_pullMode       = GPIO_FLOATING;
				str_l_gpioPinOrGroupOfPins.enu_interruptMode  = GPIO_NO_INTERRUPT;
				/************************************************************************/
				switch (enu_newLedStatus)
				{/************************************************************************/
				case LEDS_STATUS_ON:
				{/************************************************************************/
					if (enu_ledActiveState == LEDS_ACTIVE_HIGH)
					{/************************************************************************/
						enu_l_retFunction |= gpio_write(&str_l_gpioPinOrGroupOfPins, LEDS_STATUS_ON);
					}/************************************************************************/
					else
					{/************************************************************************/
						enu_l_retFunction |= gpio_write(&str_l_gpioPinOrGroupOfPins, LEDS_STATUS_OFF);
					}/************************************************************************/
				}/************************************************************************/
				break;
				case LEDS_STATUS_OFF:
				{/************************************************************************/
					if (enu_ledActiveState == LEDS_ACTIVE_HIGH)
					{/************************************************************************/
						enu_l_retFunction |= gpio_write(&str_l_gpioPinOrGroupOfPins, LEDS_STATUS_OFF);
					}/************************************************************************/
					else
					{/************************************************************************/
						enu_l_retFunction |= gpio_write(&str_l_gpioPinOrGroupOfPins, LEDS_STATUS_ON);
					}/************************************************************************/
				}/************************************************************************/
				break;
				default:
				{/************************************************************************/
					enu_l_retFunction |= gpio_write(&str_l_gpioPinOrGroupOfPins, enu_newLedStatus);
				}/************************************************************************/
				break;
				}/************************************************************************/
			}/************************************************************************/
			break;
			default: /* This Value mean Not Single LED */
			{/************************************************************************/
				enu_l_retFunction = ERROR_CHECK(FALSE); /* LEDS_WRONG_INPUT_VALUE */
			}/************************************************************************/
			break;
			}/************************************************************************/
		}/************************************************************************/
		else
		{/************************************************************************/
			enu_l_retFunction = LEDS_WRONG_INPUT_VALUE;
		}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}