#ifndef __PWM_PRIVATE_H__
#define __PWM_PRIVATE_H__


extern uint32_t SystemCoreClock;

typedef struct
{
    enu_gpioPort_t             enu_pwmPort;
    enu_gpioPins_t             enu_pwmPin;
    ptr_func_gptIRQCallBack_t* ptr_func_pwmCallback;
} str_pwmCtrl_t;
                         
#define INDX_TO_BASE                        1
#define INDX_TO_TIMER_NAME                  2
#define MAX_DUTY_CYCLE                     100
#define REPEATED_CYCLE                     101
#define PWM_NOT_INITIALIZED                255


static void pwm_callback_0A(void);
static void pwm_callback_0B(void);
static void pwm_callback_1A(void);
static void pwm_callback_1B(void);
static void pwm_callback_2A(void);
static void pwm_callback_2B(void);
static void pwm_callback_3A(void);
static void pwm_callback_3B(void);
static void pwm_callback_4A(void);
static void pwm_callback_4B(void);
static void pwm_callback_5A(void);
static void pwm_callback_5B(void);

static str_pwmCtrl_t str_gs_pwmCtrl[] =
{
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_0A
    },
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_0B
    },
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_1A
    },
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_1B
    },
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_2A
    },
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_2B
    },
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_3A
    },
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_3B
    },
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_4A
    },
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_4B
    },
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_5A
    },
    {
        .enu_pwmPort = PWM_NOT_INITIALIZED,
        .enu_pwmPin = PWM_NOT_INITIALIZED,
        .ptr_func_pwmCallback = &pwm_callback_5B
    },
};

#endif