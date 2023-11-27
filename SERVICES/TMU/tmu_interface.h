#ifndef __TMU_INTERFACE_H__
#define __TMU_INTERFACE_H__

typedef void (ptr_func_tmuCallBack_t) (void);

typedef enum
{
	/************************************************************************/
	TMU_OK = STATE_OK      ,  /* STATE_OK From LIB  #include "error_check.h" */
	TMU_WRONG_INPUT_NULL   , 
	TMU_NOT_INITIALIZED    ,
    TMU_NOK                ,
	/************************************************************************/
} enu_tmuErrorState_t;

typedef enum
{
	/************************************************************************/
	TMU_SYSTICK_POLLING = 0,
    TMU_SYSTICK_INTERRUPT  , 
    // to do
    TMU_INVALID_TIMER      ,                
	/************************************************************************/
} enu_tmuSelecttimer_t;

/************************************************************************/
/*********************      TMU FUNCTIONS      **********************/
/************************************************************************/
enu_tmuErrorState_t tmu_init(enu_tmuSelecttimer_t enu_l_Selecttimer , uint64_t uint64_l_timeInMilliSeconds , ptr_func_tmuCallBack_t * ptr_func_l_systickCallBack );
enu_tmuErrorState_t tmu_deinit(enu_tmuSelecttimer_t enu_l_Selecttimer );
enu_tmuErrorState_t tmu_getAbsoluteTimeMilliSeconds(enu_tmuSelecttimer_t enu_l_Selecttimer ,uint32_t  * uint64_ptr_l_absoluteTimeMilliSeconds);
enu_tmuErrorState_t tmu_stop(enu_tmuSelecttimer_t enu_l_Selecttimer );
enu_tmuErrorState_t tmu_resume(enu_tmuSelecttimer_t enu_l_Selecttimer );
enu_tmuErrorState_t tmu_clearAbsoluteTime(enu_tmuSelecttimer_t enu_l_Selecttimer );
/************************************************************************/
/******************************   END   *********************************/
/************************************************************************/
#endif