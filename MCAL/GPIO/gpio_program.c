/************************************************************************/
/*				           INCLUDE ARM LIB                              */
/************************************************************************/
#include "TM4C123.h"
#include "core_cm4.h"
/************************************************************************/
/*                         INCLUDE FROM LIB                             */
/************************************************************************/
#include "..\..\LIB\error_check.h"
#include "..\..\LIB\bit_math.h"
/************************************************************************/
/*                         INCLUDE FROM GPIO                            */
/************************************************************************/
#include "gpio_interface.h"
#include "gpio_private.h"
/************************************************************************/
static ptr_Func_gpioCallBack_t* ptr_func_gpioInterruptCallBack[GPIO_MAX_PORT_NUM][GPIO_MAX_PIN_NUM];
static str_gpioDigitalInitializedPins_t str_gs_gpioPortsHistory[GPIO_MAX_PORT_NUM];
/*************************************************************************************/
/*********************************   gpio_init    ************************************/
/*************************************************************************************/
enu_gpioErrorState_t gpio_init(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup , enu_gpioPinsLock_t enu_gpioPinsLock )
{
	/************************************************************************/
	enu_gpioErrorState_t enu_l_retFunction = GPIO_OK;
	enu_gpioPort_t       enu_l_port;
	/************************************************************************/
    if(ERROR_CHECK(str_ptr_pinOrGroup != NULL) == GPIO_OK)
	{
		/************************************************************************/
       if(!ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPort <= GPIO_PORTF				)&&
	      !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup != GPIO_NO_PIN	    )&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_modeConfig <= GPIO_MODE_AF			)&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_direction <= GPIO_DIRECTION_OUTPUT	)&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_pinDrive <= GPIO_OUTPUT_DRIVE_8MA 	)&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_pullMode <= GPIO_PULLDOWN 			)&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_interruptMode <= GPIO_BOTH_EDGES	))
	   {/************************************************************************/
		  enu_l_port = str_ptr_pinOrGroup->enu_gpioPort;
		  /************************************************************************/
		  #if  GPIO_BUS        ==       GPIO_APB
		  /************************************************************************/
			if(enu_l_port > GPIO_PORTD)
			{
				enu_l_port += GPIO_PORT_E_F_OFFSET;
			}
		  /************************************************************************/
		  #endif
		  /************************************************************************/
		  SET_BIT( RCGCGPIO_CONFIG , str_ptr_pinOrGroup->enu_gpioPort );			//Enable GPIO Clock
		  /************************************************************************/
		  switch (str_ptr_pinOrGroup->enu_modeConfig)
		  {/************************************************************************/
			case GPIO_MODE_DIGITAL:
			{/************************************************************************/
				CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOAMSEL_CONFIG) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
				CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOAFSEL_CONFIG) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
				SET_BITS(GPIO_CONFIG(enu_l_port,GPIODEN_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
				/* Save In History Choosen PINS */
				SET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsDigitalMode, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);	
			}/************************************************************************/
			break;
			/************************************************************************/
			case GPIO_MODE_ANALOG:
			{/************************************************************************/
				/* TO DO code */

				/* Save In History Choosen PINS */
				CLR_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsDigitalMode, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
			}/************************************************************************/
			break;
		    case GPIO_MODE_AF:
		    {/************************************************************************/
				/* TO DO code */

				/* Save In History Choosen PINS */
				CLR_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsDigitalMode, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
			}/************************************************************************/
			break;
		  }/************************************************************************/
		  /************************************************************************/
		  switch (str_ptr_pinOrGroup->enu_direction)
		  {/************************************************************************/
		    case GPIO_DIRECTION_OUTPUT:
		    {/************************************************************************/
			    SET_BITS(GPIO_CONFIG(enu_l_port,GPIODIR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
			    /* Save In History Choosen PINS */
				SET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsdirection, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
			    /************************************************************************/
				GPIO_DATA_BIT_BAND(enu_l_port , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup ) = (uint8_t)GPIO_LOW_LEVEL;
				/************************************************************************/
				switch (str_ptr_pinOrGroup->enu_pinDrive)
				{/************************************************************************/
				    case GPIO_OUTPUT_DRIVE_4MA:
					{/************************************************************************/
						SET_BITS(GPIO_CONFIG(enu_l_port,GPIODR4R_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
					}/************************************************************************/
					break;
					case GPIO_OUTPUT_DRIVE_8MA:
					{/************************************************************************/
						SET_BITS(GPIO_CONFIG(enu_l_port,GPIODR8R_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
					}/************************************************************************/
					break;
				    default: /* GPIO_OUTPUT_DRIVE_2MA */
				    {/************************************************************************/
						SET_BITS(GPIO_CONFIG(enu_l_port,GPIODR2R_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
				    }/************************************************************************/
					break;
				}/************************************************************************/
		    }/************************************************************************/
			break;
		    case GPIO_DIRECTION_INPUT:
		    {/************************************************************************/
			    CLR_BITS(GPIO_CONFIG(enu_l_port,GPIODIR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
				/* Mask interrupt to avoid unexepected interrupt trigger or if interrupt mode is not configured */
				CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOIM_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
			    /* Save In History Choosen PINS */
				CLR_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsdirection, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
			    /************************************************************************/
			    switch (str_ptr_pinOrGroup->enu_pullMode)
                {/************************************************************************/
                    case GPIO_PULLDOWN:
                     {/************************************************************************/
						CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOPUR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
						SET_BITS(GPIO_CONFIG(enu_l_port,GPIOPDR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
					 }/************************************************************************/
					 break;
                    case GPIO_PULLUP:
                     {/************************************************************************/
						CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOPDR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
						SET_BITS(GPIO_CONFIG(enu_l_port,GPIOPUR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
					 }/************************************************************************/
					 break;
                    default: /* GPIO_FLOATING */
                     {/************************************************************************/
						CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOPDR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
						CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOPUR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
					 }/************************************************************************/
                     break;
                }/************************************************************************/
				/************************************************************************/
				if (str_ptr_pinOrGroup->enu_interruptMode != GPIO_NO_INTERRUPT)
			    {/************************************************************************/
		            if(str_ptr_pinOrGroup->enu_gpioPort != GPIO_PORTF)
					{/************************************************************************/
						NVIC_EnableIRQ(str_ptr_pinOrGroup->enu_gpioPort);
					}/************************************************************************/
					else
					{/************************************************************************/
						NVIC_EnableIRQ(GPIOF_IRQn);
					}/************************************************************************/
					__enable_irq();
          /* Edge-trggered interrupt */
					CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOIS_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
					switch (str_ptr_pinOrGroup->enu_interruptMode)
					{/************************************************************************/
					    case GPIO_RISING_EDGE:
						{/************************************************************************/
							CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOIBE_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
							SET_BITS(GPIO_CONFIG(enu_l_port,GPIOIEV_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
						}/************************************************************************/
					    break;
					    case GPIO_FALLING_EDGE:
						{/************************************************************************/
							CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOIBE_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
							CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOIEV_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
						}/************************************************************************/
					    break;
					    case GPIO_BOTH_EDGES:
						{/************************************************************************/
							SET_BITS(GPIO_CONFIG(enu_l_port,GPIOIBE_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
						}/************************************************************************/
						break;
					}/************************************************************************/
					CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOICR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );/* Clear interrupt status bit */
					SET_BITS(GPIO_CONFIG(enu_l_port,GPIOIM_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup ); /* Unmask interrupt */
			    }/************************************************************************/
				else
				{/************************************************************************/
					//Do Nothing
				}/************************************************************************/
		    }/************************************************************************/
		    break;
		  }/************************************************************************/
		  if(enu_gpioPinsLock == GPIO_LOCK)
		  {/************************************************************************/
			SET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsLock, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
		  }/************************************************************************/
		  else
		  {/************************************************************************/
			CLR_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsLock, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
		  }/************************************************************************/
	   }/************************************************************************/
	   else
	   {/************************************************************************/
		   enu_l_retFunction = GPIO_WRONG_INPUT_VALUE;
	   }/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = GPIO_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/********************************   gpio_deinit   ************************************/
/*************************************************************************************/
enu_gpioErrorState_t gpio_deinit(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup )
{
	/************************************************************************/
	enu_gpioErrorState_t enu_l_retFunction = GPIO_OK;
	enu_gpioPort_t       enu_l_port;
	/************************************************************************/
    if(ERROR_CHECK(str_ptr_pinOrGroup != NULL) == GPIO_OK)
	{
		/************************************************************************/
       if(!ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPort <= GPIO_PORTF				)&&
	      !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup != GPIO_NO_PIN	    )&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_modeConfig <= GPIO_MODE_AF			)&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_direction <= GPIO_DIRECTION_OUTPUT	)&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_pinDrive <= GPIO_OUTPUT_DRIVE_8MA 	)&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_pullMode <= GPIO_PULLDOWN 			)&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_interruptMode <= GPIO_BOTH_EDGES	))
	    {/************************************************************************/
		  enu_l_port = str_ptr_pinOrGroup->enu_gpioPort;
		  /************************************************************************/
		  #if  GPIO_BUS        ==       GPIO_APB
		  /************************************************************************/
			if(enu_l_port > GPIO_PORTD)
			{
				enu_l_port += GPIO_PORT_E_F_OFFSET;
			}
		  /************************************************************************/
		  #endif
		  /************************************************************************/
		  if(!ERROR_CHECK(gpio_lockAndUnlockPins(str_ptr_pinOrGroup , GPIO_UNLOCK )))
		  {
		    switch (str_ptr_pinOrGroup->enu_modeConfig)
		    {/************************************************************************/
		    	case GPIO_MODE_DIGITAL:
		    	{/************************************************************************/
		    		CLR_BITS(GPIO_CONFIG(enu_l_port,GPIODEN_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
		    		/* Save In History Choosen PINS */
		    		CLR_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsDigitalMode, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);	
					CLR_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsdirection, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
		    	}/************************************************************************/
		    	break;
		    	/************************************************************************/
		    	case GPIO_MODE_ANALOG:
		    	{/************************************************************************/
		    		/* TO DO code */

		    		/* Save In History Choosen PINS */
		    		CLR_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsDigitalMode, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
		    	}/************************************************************************/
		    	break;
		        case GPIO_MODE_AF:
		        {/************************************************************************/
		    		/* TO DO code */

		    		/* Save In History Choosen PINS */
		    		CLR_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsDigitalMode, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
		    	}/************************************************************************/
		    	break;
		    }/************************************************************************/
		    CLR_BITS(GPIO_CONFIG(enu_l_port,GPIODIR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );/* Input */
			/************************************************************************/
			CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOICR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );/* Clear interrupt status bit */
		    /* Mask interrupt to avoid unexepected interrupt trigger or if interrupt mode is not configured */
		    CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOIM_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
		    /************************************************************************/
			/* PULL Down*/
		    CLR_BITS(GPIO_CONFIG(enu_l_port,GPIOPUR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
		    SET_BITS(GPIO_CONFIG(enu_l_port,GPIOPDR_CONFIG  ) , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup );
		  }/************************************************************************/
		  else
		  {/************************************************************************/
				enu_l_retFunction = GPIO_NOT_INITIALIZED_OR_LOCKED;
		  }/************************************************************************/
	   }/************************************************************************/
	   else
	   {/************************************************************************/
		   enu_l_retFunction = GPIO_WRONG_INPUT_VALUE;
	   }/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = GPIO_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/*********************************   gpio_write   ************************************/
/*************************************************************************************/
enu_gpioErrorState_t gpio_write(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup , enu_gpioLevelOrValue_t  enu_gpioLevelOrValue)
{
	/************************************************************************/
	enu_gpioErrorState_t enu_l_retFunction = GPIO_OK;
	enu_gpioPort_t       enu_l_port;
	/************************************************************************/
    if(ERROR_CHECK(str_ptr_pinOrGroup != NULL) == GPIO_OK)
	{
		/************************************************************************/
       if(!ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPort <= GPIO_PORTF			  )&&
	      !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup != GPIO_NO_PIN	  )&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_modeConfig == GPIO_MODE_DIGITAL	  )&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_direction == GPIO_DIRECTION_OUTPUT)&&
		  !ERROR_CHECK((uint16_t)enu_gpioLevelOrValue        <=       GPIO_HIGH_LEVEL     ))
	   {/************************************************************************/
		  enu_l_port = str_ptr_pinOrGroup->enu_gpioPort;
		  /************************************************************************/
		  #if  GPIO_BUS        ==       GPIO_APB
		  /************************************************************************/
			if(enu_l_port > GPIO_PORTD)
			{
				enu_l_port += GPIO_PORT_E_F_OFFSET;
			}
		  /************************************************************************/
		  #endif
		  /************************************************************************/
		  if(!ERROR_CHECK(GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsLock,
		     (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) ==                  GPIO_UNLOCK                    )&&
			!ERROR_CHECK(GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsdirection,
		     (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) == (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup )&&
			 !ERROR_CHECK(GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsDigitalMode,
		     (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) == (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup )) 
			 {/************************************************************************/
			    switch (enu_gpioLevelOrValue)
			    {/************************************************************************/
				    case GPIO_LOW_LEVEL:
				    {/************************************************************************/
				    	GPIO_DATA_BIT_BAND(enu_l_port , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup ) = (uint8_t)GPIO_LOW_LEVEL; 
				    }/************************************************************************/
				    break;
				    case GPIO_HIGH_LEVEL:
				    {/************************************************************************/
				    	GPIO_DATA_BIT_BAND(enu_l_port , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup ) = (uint8_t)GPIO_MAX_VALUE; 
				    }/************************************************************************/
				    break;
				    default:
				    {/************************************************************************/
				    	GPIO_DATA_BIT_BAND(enu_l_port , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup ) = (uint8_t)enu_gpioLevelOrValue;
				    }/************************************************************************/
			        break;
			    }/************************************************************************/
			 }/************************************************************************/
			 else
			 {/************************************************************************/
				enu_l_retFunction = GPIO_NOT_INITIALIZED_OR_LOCKED;
			 }/************************************************************************/
	   }
	   else
	   {/************************************************************************/
		   enu_l_retFunction = GPIO_WRONG_INPUT_VALUE;
	   }/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = GPIO_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/*********************************   gpio_read    ************************************/
/*************************************************************************************/
enu_gpioErrorState_t gpio_read(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup , enu_gpioLevelOrValue_t  * enu_gpioLevelOrValue)
{
	/************************************************************************/
	enu_gpioErrorState_t   enu_l_retFunction = GPIO_OK;
	enu_gpioPort_t         enu_l_port;
	enu_gpioLevelOrValue_t enu_l_pinsLevelOrValue;
	/************************************************************************/
    if(ERROR_CHECK(((str_ptr_pinOrGroup != NULL) && (enu_gpioLevelOrValue != NULL))) == GPIO_OK)
	{
		/************************************************************************/
       if(!ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPort <= GPIO_PORTF			 )&&
	      !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup != GPIO_NO_PIN	 )&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_modeConfig == GPIO_MODE_DIGITAL	 )&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_direction == GPIO_DIRECTION_INPUT))
	   {/************************************************************************/
		  enu_l_port = str_ptr_pinOrGroup->enu_gpioPort;
		  /************************************************************************/
		  #if  GPIO_BUS        ==       GPIO_APB
		  /************************************************************************/
			if(enu_l_port > GPIO_PORTD)
			{
				enu_l_port += GPIO_PORT_E_F_OFFSET;
			}
		  /************************************************************************/
		  #endif
		  /************************************************************************/
		  if(!ERROR_CHECK(GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsdirection,
		     (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) ==               GPIO_DIRECTION_INPUT              )&&
			 !ERROR_CHECK(GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsDigitalMode,
		     (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) == (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup )) 
			 {/************************************************************************/
				enu_l_pinsLevelOrValue = (uint8_t)GPIO_DATA_BIT_BAND(enu_l_port , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
				/************************************************************************/
				if(enu_l_pinsLevelOrValue == (uint8_t)GPIO_LOW_LEVEL)
			    {/************************************************************************/
					*enu_gpioLevelOrValue = GPIO_LOW_LEVEL;
				}/************************************************************************/
				else if (enu_l_pinsLevelOrValue == str_ptr_pinOrGroup->enu_gpioPinOrGroup)
				{/************************************************************************/
					*enu_gpioLevelOrValue = GPIO_HIGH_LEVEL;
				}/************************************************************************/
				else
				{/************************************************************************/
					*enu_gpioLevelOrValue = enu_l_pinsLevelOrValue ;
				}/************************************************************************/
			 }/************************************************************************/
			 else
			 {/************************************************************************/
				enu_l_retFunction = GPIO_NOT_INITIALIZED_OR_LOCKED;
			 }/************************************************************************/
	   }
	   else
	   {/************************************************************************/
		   enu_l_retFunction = GPIO_WRONG_INPUT_VALUE;
	   }/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = GPIO_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/******************************     gpio_toggle     **********************************/
/*************************************************************************************/
enu_gpioErrorState_t gpio_toggle(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup)
{
	/************************************************************************/
	enu_gpioErrorState_t enu_l_retFunction = GPIO_OK;
	enu_gpioPort_t       enu_l_port;
	enu_gpioLevelOrValue_t enu_l_pinsLevelOrValue;
	/************************************************************************/
    if(ERROR_CHECK(str_ptr_pinOrGroup != NULL) == GPIO_OK)
	{
		/************************************************************************/
       if(!ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPort <= GPIO_PORTF				)&&
	      !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup != GPIO_NO_PIN	    )&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_modeConfig == GPIO_MODE_DIGITAL		)&&
		  !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_direction == GPIO_DIRECTION_OUTPUT	))
	   {/************************************************************************/
		  enu_l_port = str_ptr_pinOrGroup->enu_gpioPort;
		  /************************************************************************/
		  #if  GPIO_BUS        ==       GPIO_APB
		  /************************************************************************/
			if(enu_l_port > GPIO_PORTD)
			{
				enu_l_port += GPIO_PORT_E_F_OFFSET;
			}
		  /************************************************************************/
		  #endif
		  /************************************************************************/
		  if(!ERROR_CHECK(GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsLock,
		     (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) ==                  GPIO_UNLOCK                    )&&
			 !ERROR_CHECK(GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsdirection,
		     (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) == (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup )&&
			 !ERROR_CHECK(GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsDigitalMode,
		     (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) == (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup )) 
			 {/************************************************************************/
			    enu_l_pinsLevelOrValue = (uint8_t)GPIO_DATA_BIT_BAND(enu_l_port , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
				/************************************************************************/
				TOG_BITS( enu_l_pinsLevelOrValue,(uint8_t)GPIO_MAX_VALUE);
				GPIO_DATA_BIT_BAND(enu_l_port , (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup ) = (uint8_t)enu_l_pinsLevelOrValue;
			 }/************************************************************************/
			 else
			 {/************************************************************************/
				enu_l_retFunction = GPIO_NOT_INITIALIZED_OR_LOCKED;
			 }/************************************************************************/
	   }
	   else
	   {/************************************************************************/
		   enu_l_retFunction = GPIO_WRONG_INPUT_VALUE;
	   }/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = GPIO_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/*************************  gpio_lockAndUnlockPins  **********************************/
/*************************************************************************************/
enu_gpioErrorState_t gpio_lockAndUnlockPins(const str_gpioPinOrGroupOfPins_t* str_ptr_pinOrGroup , enu_gpioPinsLock_t enu_gpioPinsLock )
{
	/************************************************************************/
	enu_gpioErrorState_t enu_l_retFunction = GPIO_OK;
	/************************************************************************/
    if(ERROR_CHECK(str_ptr_pinOrGroup != NULL) == GPIO_OK)
	{
		/************************************************************************/
       if(!ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPort <= GPIO_PORTF				)&&
	      !ERROR_CHECK((uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup != GPIO_NO_PIN	    ))
	   {/************************************************************************/
		  if((!ERROR_CHECK(((GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsdirection,
		      (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) == (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup )||
			  (GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsdirection,
			  (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) == GPIO_DIRECTION_INPUT))                          )&&
			  !ERROR_CHECK(((GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsDigitalMode,
		      (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) == (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup )||
			  (GET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsDigitalMode,
			  (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup) == GPIO_MODE_DIGITAL)))                            )) 
			 {/************************************************************************/
		        if(enu_gpioPinsLock == GPIO_LOCK)
		        {/************************************************************************/
		    		SET_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsLock, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
		        }/************************************************************************/
		        else
		        {/************************************************************************/
		    		CLR_BITS(str_gs_gpioPortsHistory[str_ptr_pinOrGroup->enu_gpioPort].enu_gpioPinsLock, (uint8_t)str_ptr_pinOrGroup->enu_gpioPinOrGroup);
		        }/************************************************************************/
			 }/************************************************************************/
			 else
			 {/************************************************************************/
				enu_l_retFunction = GPIO_NOT_INITIALIZED_OR_LOCKED;
			 }/************************************************************************/
	   }
	   else
	   {/************************************************************************/
		   enu_l_retFunction = GPIO_WRONG_INPUT_VALUE;
	   }/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = GPIO_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/******************     gpio_callBackSinglePinInterrupt     **************************/
/*************************************************************************************/
enu_gpioErrorState_t gpio_callBackSinglePinInterrupt(enu_gpioPort_t enu_gpioPort,enu_gpioPins_t enu_gpioPin,ptr_Func_gpioCallBack_t* ptr_func_interruptCallBack)
{
	/************************************************************************/
	enu_gpioErrorState_t enu_l_retFunction = GPIO_OK;
	/************************************************************************/
    if(ERROR_CHECK(ptr_func_interruptCallBack != NULL) == GPIO_OK)
	{
		/************************************************************************/
       if(!ERROR_CHECK((uint8_t)enu_gpioPort <= GPIO_PORTF))
	   {/************************************************************************/
			switch ((uint8_t)enu_gpioPin)
			{/************************************************************************/
			    case GPIO_PIN_0:
			    {/************************************************************************/
			    	ptr_func_gpioInterruptCallBack[enu_gpioPort][PIN_0] = ptr_func_interruptCallBack ;
			    }/************************************************************************/
			    break;
			    case GPIO_PIN_1:
			    {/************************************************************************/
			    	ptr_func_gpioInterruptCallBack[enu_gpioPort][PIN_1] = ptr_func_interruptCallBack ;
			    }/************************************************************************/
				break;
			    case GPIO_PIN_2:
			    {/************************************************************************/
			    	ptr_func_gpioInterruptCallBack[enu_gpioPort][PIN_2] = ptr_func_interruptCallBack ;
			    }/************************************************************************/
				break;
			    case GPIO_PIN_3:
			    {
			    	ptr_func_gpioInterruptCallBack[enu_gpioPort][PIN_3] = ptr_func_interruptCallBack ;
			    }/************************************************************************/
				break;
			    case GPIO_PIN_4:
			    {/************************************************************************/
			    	ptr_func_gpioInterruptCallBack[enu_gpioPort][PIN_4] = ptr_func_interruptCallBack ;
			    }/************************************************************************/
				break;
			    case GPIO_PIN_5:
			    {/************************************************************************/
			    	ptr_func_gpioInterruptCallBack[enu_gpioPort][PIN_5] = ptr_func_interruptCallBack ;
			    }/************************************************************************/
				break;
			    case GPIO_PIN_6:
			    {/************************************************************************/
			    	ptr_func_gpioInterruptCallBack[enu_gpioPort][PIN_6] = ptr_func_interruptCallBack ;
			    }/************************************************************************/
				break;
			    case GPIO_PIN_7:
			    {/************************************************************************/
			    	ptr_func_gpioInterruptCallBack[enu_gpioPort][PIN_7] = ptr_func_interruptCallBack ;
			    }/************************************************************************/
			    break;
			    default:
			    {/************************************************************************/
			    	enu_l_retFunction = ERROR_CHECK(FALSE); /* GPIO_WRONG_INPUT_VALUE */
			    }/************************************************************************/
			    break;
			}/************************************************************************/
	   }
	   else
	   {/************************************************************************/
		   enu_l_retFunction = GPIO_WRONG_INPUT_VALUE;
	   }/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		enu_l_retFunction = GPIO_WRONG_INPUT_NULL;
	}/************************************************************************/
	return enu_l_retFunction;
	/************************************************************************/
}
/*************************************************************************************/
/**************************     gpio_irqHandler     **********************************/
/*************************************************************************************/
static void gpio_irqHandler(enu_gpioPort_t enu_l_port)
{
	uint8_t uint8_l_pinCounter = GPIO_NO_PIN;
	uint8_t uint8_l_pinMask    = GPIO_NO_PIN;
	enu_gpioPort_t enu_l_portConfig = enu_l_port;
	/************************************************************************/
	#if  GPIO_BUS        ==       GPIO_APB
	/************************************************************************/
	if(enu_l_port > GPIO_PORTD)
	{
		enu_l_portConfig += GPIO_PORT_E_F_OFFSET;
	}
	/************************************************************************/
	#endif
	/************************************************************************/
	 uint8_l_pinMask = GPIO_CONFIG(enu_l_portConfig,GPIOMIS_CONFIG);
    /************************************************************************/
	if(!ERROR_CHECK((uint8_t)enu_l_port <= GPIO_PORTF))
	{/************************************************************************/
		while(uint8_l_pinMask != GPIO_NO_PIN)
		{/************************************************************************/
			if(uint8_l_pinMask & TRUE)
			{/************************************************************************/
				SET_BIT(GPIO_CONFIG(enu_l_portConfig,GPIOICR_CONFIG  ) , uint8_l_pinCounter );
				/************************************************************************/
				if(!ERROR_CHECK(ptr_func_gpioInterruptCallBack[enu_l_port][uint8_l_pinCounter] != NULL))
				{/************************************************************************/
					ptr_func_gpioInterruptCallBack[enu_l_port][uint8_l_pinCounter]();
				}/************************************************************************/
				else
				{/************************************************************************/
					//NULL Detected in Interrupt Call Back Function
				}/************************************************************************/
			}/************************************************************************/
			uint8_l_pinMask >>= SHIFT_ONE_TIME;
			uint8_l_pinCounter++;
			/************************************************************************/
		}/************************************************************************/
	}/************************************************************************/
	else
	{/************************************************************************/
		//Wrong Input in Interrupt Call
	}/************************************************************************/
}/************************************************************************/
/*****************GPIO Handler FUNCTION DECLARATIONS*********************/
/************************************************************************/
void GPIOA_Handler(void)
{/************************************************************************/
	gpio_irqHandler(GPIO_PORTA);
}/************************************************************************/
/************************************************************************/
void GPIOB_Handler(void)
{/************************************************************************/
	gpio_irqHandler(GPIO_PORTB);
}/************************************************************************/
/************************************************************************/
void GPIOC_Handler(void)
{/************************************************************************/
	gpio_irqHandler(GPIO_PORTC);
}/************************************************************************/
/************************************************************************/
void GPIOD_Handler(void)
{/************************************************************************/
	gpio_irqHandler(GPIO_PORTD);
}/************************************************************************/
/************************************************************************/
void GPIOE_Handler(void)
{/************************************************************************/
	gpio_irqHandler(GPIO_PORTE);
}/************************************************************************/
/************************************************************************/
void GPIOF_Handler(void)
{/************************************************************************/
	gpio_irqHandler(GPIO_PORTF);
}/************************************************************************/
/************************************************************************/