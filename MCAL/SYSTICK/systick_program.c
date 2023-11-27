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
#include "systick_interface.h"
#include "systick_private.h"
/************************************************************************/

static ptr_func_systickCallBack_t* ptr_func_gs_systickCallBack;
static uint8_t uint8_gs_systickInitHistory;
static uint32_t uint32_gs_reload = ((uint32_t)TICKS_FOR_ONE_MICRO_SECOND * (uint32_t)SYSTICK_TICKS_MICRO_SECOND) - _ONE_TICK_; // Clock Freqency
/****************************************************************************************/
enu_systickErrorState_t systick_init(ptr_func_systickCallBack_t* ptr_func_l_systickCallBack)
{
    /****************************************************************************************/
	enu_systickErrorState_t  enu_l_systickErrorState = SYSTICK_OK;
    /****************************************************************************************/
    SYSTICK_CONFIG(STRELOAD_CONFIG) = uint32_gs_reload ;
		SYSTICK_CONFIG(STCURRENT_CONFIG)= uint32_gs_reload;
    WRITE_STCTRL_REG( CLK_SOURCE_BIT , _AHB_CLOCK_ );
	  WRITE_STCTRL_REG( ENABLE_SYSTICK_BIT , _ENABLE_ );
    uint8_gs_systickInitHistory = _ENABLE_ ;
    /****************************************************************************************/
#if     SYSTICK_ENABLE_INTERRUPT        ==       _INTERRUPT_MODE_
    /****************************************************************************************/
	  
	if( ptr_func_l_systickCallBack != NULL )
	{
    ptr_func_gs_systickCallBack = ptr_func_l_systickCallBack;
		WRITE_STCTRL_REG( INT_ENABLE_BIT , _INTERRUPT_MODE_ );
		NVIC_EnableIRQ(SysTick_IRQn);
    __enable_irq();
	}
	else
	{
		enu_l_systickErrorState = SYSTICK_WRONG_INPUT_NULL;
	}

    /****************************************************************************************/
#elif   SYSTICK_ENABLE_INTERRUPT        ==       _POLLING_MODE_
    /****************************************************************************************/
    WRITE_STCTRL_REG( INT_ENABLE_BIT , _POLLING_MODE_ );
    /****************************************************************************************/
#else
    #error  "WRONG SYSTICK MODE"
#endif
    /****************************************************************************************/

    /****************************************************************************************/
    return enu_l_systickErrorState;
    /****************************************************************************************/
}
/****************************************************************************************/
enu_systickErrorState_t systick_deinit(void)
{
    enu_systickErrorState_t  enu_l_systickErrorState = SYSTICK_OK;
    if(!ERROR_CHECK(uint8_gs_systickInitHistory == _ENABLE_	))
    {/****************************************************************************************/
        uint8_gs_systickInitHistory = _DISABLE_ ;
			/****************************************************************************************/
        WRITE_STCTRL_REG( ENABLE_SYSTICK_BIT , _DISABLE_);
        WRITE_STCTRL_REG( INT_ENABLE_BIT , _POLLING_MODE_ );
        NVIC_DisableIRQ(SysTick_IRQn);
			/****************************************************************************************/
    }
    else
    {/****************************************************************************************/
        enu_l_systickErrorState = SYSTICK_NOT_INITIALIZED;
    }/****************************************************************************************/
    return enu_l_systickErrorState;
}
/****************************************************************************************/
enu_systickErrorState_t systick_setCallBackIntrruptMode(ptr_func_systickCallBack_t * ptr_func_l_systickCallBack)
{
    enu_systickErrorState_t  enu_l_systickErrorState = SYSTICK_OK;
    /****************************************************************************************/
    if (!ERROR_CHECK(uint8_gs_systickInitHistory == _ENABLE_))
    {/****************************************************************************************/
        if (!ERROR_CHECK(ptr_func_l_systickCallBack != NULL))
        {/****************************************************************************************/
            ptr_func_gs_systickCallBack = ptr_func_l_systickCallBack;
        }/****************************************************************************************/
        else
        {/****************************************************************************************/
            enu_l_systickErrorState = SYSTICK_WRONG_INPUT_NULL;
        }/****************************************************************************************/
    }/****************************************************************************************/
    else
    {/****************************************************************************************/
        enu_l_systickErrorState = SYSTICK_NOT_INITIALIZED;
    }/****************************************************************************************/
    return enu_l_systickErrorState;
}
enu_systickErrorState_t systick_resume(void)
{/****************************************************************************************/
    enu_systickErrorState_t  enu_l_systickErrorState = SYSTICK_OK;
	/****************************************************************************************/
    if(!ERROR_CHECK(uint8_gs_systickInitHistory == _ENABLE_	))
    {/****************************************************************************************/
        WRITE_STCTRL_REG( ENABLE_SYSTICK_BIT , _ENABLE_);
    }/****************************************************************************************/
    else
    {/****************************************************************************************/
        enu_l_systickErrorState = SYSTICK_NOT_INITIALIZED;
    }/****************************************************************************************/
    return enu_l_systickErrorState;
}
/****************************************************************************************/
enu_systickErrorState_t systick_stop(void)
{/****************************************************************************************/
    enu_systickErrorState_t  enu_l_systickErrorState = SYSTICK_OK;
    if(!ERROR_CHECK(uint8_gs_systickInitHistory == _ENABLE_	))
    {/****************************************************************************************/
      SYSTICK_CONFIG(STCURRENT_CONFIG)= uint32_gs_reload;  
			WRITE_STCTRL_REG( ENABLE_SYSTICK_BIT , _DISABLE_);
    }/****************************************************************************************/
    else
    {/****************************************************************************************/
        enu_l_systickErrorState = SYSTICK_NOT_INITIALIZED;
    }/****************************************************************************************/
    return enu_l_systickErrorState;
}
/****************************************************************************************/
enu_systickErrorState_t systick_enableIRQ(void)
{/****************************************************************************************/
    enu_systickErrorState_t  enu_l_systickErrorState = SYSTICK_OK;
    if(!ERROR_CHECK(uint8_gs_systickInitHistory == _ENABLE_	))
    {/****************************************************************************************/
        NVIC_EnableIRQ(SysTick_IRQn);
        __enable_irq();
        WRITE_STCTRL_REG( INT_ENABLE_BIT , _INTERRUPT_MODE_ );
    }/****************************************************************************************/
    else
    {/****************************************************************************************/
        enu_l_systickErrorState = SYSTICK_NOT_INITIALIZED;
    }/****************************************************************************************/
    return enu_l_systickErrorState;
}
/****************************************************************************************/
enu_systickErrorState_t systick_disableIRQ(void)
{/****************************************************************************************/
    enu_systickErrorState_t  enu_l_systickErrorState = SYSTICK_OK;
    if(!ERROR_CHECK(uint8_gs_systickInitHistory == _ENABLE_	))
    {/****************************************************************************************/
        WRITE_STCTRL_REG( INT_ENABLE_BIT , _POLLING_MODE_ );
        NVIC_DisableIRQ(SysTick_IRQn);
    }/****************************************************************************************/
    else
    {/****************************************************************************************/
        enu_l_systickErrorState = SYSTICK_NOT_INITIALIZED;
    }/****************************************************************************************/
    return enu_l_systickErrorState;
}
/****************************************************************************************/
void SysTick_Handler(void)
{/****************************************************************************************/
    if(!ERROR_CHECK(ptr_func_gs_systickCallBack != NULL))
    {/****************************************************************************************/
        ptr_func_gs_systickCallBack();
    }/****************************************************************************************/
		READ_STCTRL_REG( COUNT_FLAG_BIT );
}
/****************************************************************************************/