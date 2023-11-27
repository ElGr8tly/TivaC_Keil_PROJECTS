#include "..\..\LIB\error_check.h"
#include "..\..\LIB\bit_math.h"

#include "..\..\MCAL\SYSTICK\systick_interface.h"

#include "tmu_interface.h"
#include "tmu_private.h"

static uint64_t uint64_gs_systickMilliSeconds;
static ptr_func_systickCallBack_t * ptr_func_gs_systickCallBack;
static uint64_t uint64_gs_systickAbsoluteTimeMilliSeconds;

static void tmu_systickCallBack(void)
{
    static uint64_t uint64_ls_systickMilliSeconds = TMU_START ;
    if((uint64_ls_systickMilliSeconds == TMU_START) || (uint64_ls_systickMilliSeconds >= uint64_gs_systickMilliSeconds))
    {/****************************************************************************************/
        if( uint64_gs_systickMilliSeconds != TMU_START)
				{
					uint64_ls_systickMilliSeconds = uint64_gs_systickMilliSeconds - SYSTICK_ONE_TICK ;
				}
				else
				{
					uint64_ls_systickMilliSeconds = TMU_START;
				}
    }/****************************************************************************************/
    else
    {/****************************************************************************************/
        --uint64_ls_systickMilliSeconds;
    }/****************************************************************************************/
		if( uint64_gs_systickMilliSeconds != TMU_START)
			{
				if( (uint64_ls_systickMilliSeconds == TMU_START) && (ptr_func_gs_systickCallBack != NULL) )
				{/****************************************************************************************/
						ptr_func_gs_systickCallBack();
				}/****************************************************************************************/
				else
				{
					//do nothing
				}
				uint64_gs_systickAbsoluteTimeMilliSeconds++;
			}
		else
			{
					//do nothing
			}
    /****************************************************************************************/
    /****************************************************************************************/
}

enu_tmuErrorState_t tmu_init(enu_tmuSelecttimer_t enu_l_Selecttimer , uint64_t uint64_l_timeInMilliSeconds , ptr_func_tmuCallBack_t * ptr_func_l_systickCallBack )
{
    enu_tmuErrorState_t  enu_l_tmuErrorState = TMU_OK;
    /****************************************************************************************/
    if (!ERROR_CHECK( enu_l_Selecttimer < TMU_INVALID_TIMER ))
    {/****************************************************************************************/
        switch (enu_l_Selecttimer)
        {
        case TMU_SYSTICK_POLLING:
            {
                if (ERROR_CHECK(!systick_init(tmu_systickCallBack)))
                {
                    enu_l_tmuErrorState = TMU_NOK;
                }
                else
                {
                    uint64_gs_systickMilliSeconds = uint64_l_timeInMilliSeconds;
                }
            }
            break;
        case TMU_SYSTICK_INTERRUPT:
            {
                if(!ERROR_CHECK( ptr_func_l_systickCallBack != NULL))
                {
                    ptr_func_gs_systickCallBack   = ptr_func_l_systickCallBack;

                    if (ERROR_CHECK(!systick_init(tmu_systickCallBack)))
                    {
                       enu_l_tmuErrorState = TMU_NOK;
                    }
                    else
                    {
                      uint64_gs_systickMilliSeconds = uint64_l_timeInMilliSeconds;
                    }
                } 
                else
                {
                    enu_l_tmuErrorState = TMU_WRONG_INPUT_NULL;
                }
            }
            break;
        
        default:
            {
                enu_l_tmuErrorState = TMU_WRONG_INPUT_NULL;
            }
            break;
        }
    }/****************************************************************************************/
    else
    {/****************************************************************************************/
        enu_l_tmuErrorState = TMU_NOT_INITIALIZED;
    }/****************************************************************************************/
    return enu_l_tmuErrorState;
}

enu_tmuErrorState_t tmu_deinit(enu_tmuSelecttimer_t enu_l_Selecttimer )
{
    enu_tmuErrorState_t  enu_l_tmuErrorState = TMU_OK;
    /****************************************************************************************/
	
    if (!ERROR_CHECK( enu_l_Selecttimer < TMU_INVALID_TIMER ))
    {/****************************************************************************************/
        switch (enu_l_Selecttimer)
        {
        case TMU_SYSTICK_POLLING:
            {
                if (ERROR_CHECK(!systick_deinit()))
                {
                    enu_l_tmuErrorState = TMU_NOT_INITIALIZED;
                }
                else
                {
                    uint64_gs_systickAbsoluteTimeMilliSeconds = TMU_START;
                    uint64_gs_systickMilliSeconds = TMU_START;
                    ptr_func_gs_systickCallBack = NULL;
								  	tmu_systickCallBack();
                }
            }
            break;
        case TMU_SYSTICK_INTERRUPT:
            {
                if (ERROR_CHECK(!systick_deinit()))
                {
                    enu_l_tmuErrorState = TMU_NOT_INITIALIZED;
                }
                else
                {
                    uint64_gs_systickAbsoluteTimeMilliSeconds = TMU_START;
                    uint64_gs_systickMilliSeconds = TMU_START;
                    ptr_func_gs_systickCallBack = NULL;
									  tmu_systickCallBack();
                }
            }
            break;
        
        default:
            {
                enu_l_tmuErrorState = TMU_WRONG_INPUT_NULL;
            }
            break;
        }
    }/****************************************************************************************/
    else
    {/****************************************************************************************/
        enu_l_tmuErrorState = TMU_NOT_INITIALIZED;
    }/****************************************************************************************/
    return enu_l_tmuErrorState;
}

enu_tmuErrorState_t tmu_getAbsoluteTimeMilliSeconds(enu_tmuSelecttimer_t enu_l_Selecttimer ,uint64_t  * uint64_ptr_l_absoluteTimeMilliSeconds)
{
				enu_tmuErrorState_t  enu_l_tmuErrorState = TMU_OK;
        if ( uint64_ptr_l_absoluteTimeMilliSeconds != NULL )
        {
         switch (enu_l_Selecttimer)
         {
          case TMU_SYSTICK_POLLING:
             {
							  if(uint64_gs_systickMilliSeconds != TMU_START )
								{
									*uint64_ptr_l_absoluteTimeMilliSeconds = uint64_gs_systickAbsoluteTimeMilliSeconds;
								}

								else
								{
										enu_l_tmuErrorState = TMU_NOT_INITIALIZED;
								}
             }
            break;
          case TMU_SYSTICK_INTERRUPT:
            {
							  if(uint64_gs_systickMilliSeconds != TMU_START )
								{
									*uint64_ptr_l_absoluteTimeMilliSeconds = uint64_gs_systickAbsoluteTimeMilliSeconds;
								}

								else
								{
										enu_l_tmuErrorState = TMU_NOT_INITIALIZED;
								}
            }
            break;
          default:
            {
                enu_l_tmuErrorState = TMU_WRONG_INPUT_NULL;
            }
            break;
        }  
        }
        else
        {
            enu_l_tmuErrorState = TMU_WRONG_INPUT_NULL;
        }       

    return enu_l_tmuErrorState;
}

enu_tmuErrorState_t tmu_stop(enu_tmuSelecttimer_t enu_l_Selecttimer )
{
    enu_tmuErrorState_t  enu_l_tmuErrorState = TMU_OK;
    if(uint64_gs_systickMilliSeconds != TMU_START )
    {
        switch (enu_l_Selecttimer)
        {
        case TMU_SYSTICK_POLLING:
            {
                systick_stop();
            }
            break;
        case TMU_SYSTICK_INTERRUPT:
            {
                systick_stop();
            }
            break;
        default:
            {
                enu_l_tmuErrorState = TMU_WRONG_INPUT_NULL;
            }
            break;
        }  
    }
    else
    {
        enu_l_tmuErrorState = TMU_NOT_INITIALIZED;
    }
    return enu_l_tmuErrorState;
}

enu_tmuErrorState_t tmu_stopAndClearStartedInterval(enu_tmuSelecttimer_t enu_l_Selecttimer )
{
    enu_tmuErrorState_t  enu_l_tmuErrorState = TMU_OK;
	  uint64_t uint64_l_systickMilliSeconds = TMU_START;
    if(uint64_gs_systickMilliSeconds != TMU_START )
    {
        switch (enu_l_Selecttimer)
        {
        case TMU_SYSTICK_POLLING:
            {
							  uint64_l_systickMilliSeconds = uint64_gs_systickMilliSeconds;
                systick_stop();
							  uint64_gs_systickMilliSeconds = TMU_START;
							  tmu_systickCallBack();
							  uint64_gs_systickMilliSeconds = uint64_l_systickMilliSeconds;
            }
            break;
        case TMU_SYSTICK_INTERRUPT:
            {
							  uint64_l_systickMilliSeconds = uint64_gs_systickMilliSeconds;
                systick_stop();
							  uint64_gs_systickMilliSeconds = TMU_START;
							  tmu_systickCallBack();
							  uint64_gs_systickMilliSeconds = uint64_l_systickMilliSeconds;
            }
            break;
        default:
            {
                enu_l_tmuErrorState = TMU_WRONG_INPUT_NULL;
            }
            break;
        }  
    }
    else
    {
        enu_l_tmuErrorState = TMU_NOT_INITIALIZED;
    }
    return enu_l_tmuErrorState;
}

enu_tmuErrorState_t tmu_resume(enu_tmuSelecttimer_t enu_l_Selecttimer )
{
    enu_tmuErrorState_t  enu_l_tmuErrorState = TMU_OK;
    if(uint64_gs_systickMilliSeconds != TMU_START )
    {
        switch (enu_l_Selecttimer)
        {
        case TMU_SYSTICK_POLLING:
            {
                systick_resume();
            }
            break;
        case TMU_SYSTICK_INTERRUPT:
            {
                systick_resume();
            }
            break;
        default:
            {
                enu_l_tmuErrorState = TMU_WRONG_INPUT_NULL;
            }
            break;
        }  
    }
    else
    {
        enu_l_tmuErrorState = TMU_NOT_INITIALIZED;
    }
    return enu_l_tmuErrorState;
}

enu_tmuErrorState_t tmu_clearAbsoluteTime(enu_tmuSelecttimer_t enu_l_Selecttimer )
{
    enu_tmuErrorState_t  enu_l_tmuErrorState = TMU_OK;
    if(uint64_gs_systickMilliSeconds != TMU_START )
    {
        switch (enu_l_Selecttimer)
        {
        case TMU_SYSTICK_POLLING:
            {
                uint64_gs_systickAbsoluteTimeMilliSeconds = 0;
            }
            break;
        case TMU_SYSTICK_INTERRUPT:
            {
                uint64_gs_systickAbsoluteTimeMilliSeconds = 0;
            }
            break;
        default:
            {
                enu_l_tmuErrorState = TMU_WRONG_INPUT_NULL;
            }
            break;
        }  
    }
    else
    {
        enu_l_tmuErrorState = TMU_NOT_INITIALIZED;
    }
    return enu_l_tmuErrorState;
}