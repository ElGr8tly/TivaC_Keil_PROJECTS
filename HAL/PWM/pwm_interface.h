#ifndef __PWM_INTERFACE_H__
#define __PWM_INTERFACE_H__
/************************************************************************/
typedef enum
{
    /************************************************************************/
    PWM_OK = STATE_OK, /* STATE_OK From LIB  #include "error_check.h" */
    PWM_WRONG_INPUT,
    /************************************************************************/
}enu_pwmErrorState_t;

typedef enum
{/************************************************************************/
    PWM_0A,
    PWM_0B,
    PWM_1A,
    PWM_1B,
    PWM_2A,
    PWM_2B,
    PWM_3A,
    PWM_3B,
    PWM_4A,
    PWM_4B,
    PWM_5A,
    PWM_5B,
    /************************************************************************/
} enu_pwmIndx_t;

typedef struct
{/************************************************************************/
    enu_pwmIndx_t               enu_pwmIndx;
    uint32_t                    uint32_pwmFreq;
    /************************************************************************/
} str_pwmCfg_t;
/************************************************************************/
/***********************      PWM FUNCTIONS      ***********************/
/************************************************************************/
enu_pwmErrorState_t pwm_init(const str_pwmCfg_t* ptr_str_l_config, uint8_t enu_pwmPort, uint8_t enu_pwmPin, uint8_t uint8_l_pwmDutyCycle);
enu_pwmErrorState_t pwm_start(const str_pwmCfg_t* ptr_str_l_config);
enu_pwmErrorState_t pwm_stop(const str_pwmCfg_t* ptr_str_l_config);
enu_pwmErrorState_t pwm_setDutyCycle(const str_pwmCfg_t* ptr_str_l_config, uint8_t uint8_l_pwmDutyCycle);
/************************************************************************/
/******************************   END   *********************************/
/************************************************************************/
#endif