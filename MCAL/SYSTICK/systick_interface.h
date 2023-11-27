#ifndef __SYSTICk_INTERFACE_H__
#define __SYSTICk_INTERFACE_H__
/************************************************************************/
/************************************************************************/
typedef void (ptr_func_systickCallBack_t) (void);
/************************************************************************/
typedef enum
{
	/************************************************************************/
	SYSTICK_OK = STATE_OK      ,  /* STATE_OK From LIB  #include "error_check.h" */
	SYSTICK_WRONG_INPUT_NULL   ,
	SYSTICK_NOT_INITIALIZED    ,
	/************************************************************************/
} enu_systickErrorState_t;

/************************************************************************/
/*********************      SYSTICK FUNCTIONS      **********************/
/************************************************************************/
enu_systickErrorState_t systick_init(ptr_func_systickCallBack_t* ptr_func_l_systickCallBack);
enu_systickErrorState_t systick_deinit(void);
enu_systickErrorState_t systick_setCallBackIntrruptMode(ptr_func_systickCallBack_t* ptr_func_l_systickCallBack);
enu_systickErrorState_t systick_stop(void);
enu_systickErrorState_t systick_resume(void);
enu_systickErrorState_t systick_enableIRQ(void);
enu_systickErrorState_t systick_disableIRQ(void);
/************************************************************************/
/******************************   END   *********************************/
/************************************************************************/
#endif