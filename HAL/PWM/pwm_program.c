/************************************************************************/
/*                         INCLUDE FROM LIB                             */
/************************************************************************/
#include "..\..\LIB\error_check.h"
/************************************************************************/
/*                         INCLUDE FROM GPIO                            */
/************************************************************************/
#include "..\..\MCAL\GPIO\gpio_interface.h"
/************************************************************************/
/*                         INCLUDE FROM GPT                             */
/************************************************************************/
#include "..\..\MCAL\GPT\gpt_interface.h"
/************************************************************************/
/*                         INCLUDE FROM PWM                             */
/************************************************************************/
#include "pwm_interface.h"
#include "pwm_private.h"
/************************************************************************/
enu_pwmErrorState_t pwm_init(const str_pwmCfg_t* ptr_str_l_config,uint8_t uint8_l_pwmPort ,uint8_t uint8_l_pwmPin , uint8_t uint8_l_pwmDutyCycle)
{
    enu_pwmErrorState_t  enu_l_tmuErrorState = PWM_OK;
    uint32_t uint32_l_loadVal;
    uint32_t uint32_l_MatchVal;
    if (!ERROR_CHECK(ptr_str_l_config != NULL) &&
        !ERROR_CHECK((uint8_t)ptr_str_l_config->enu_pwmIndx <= PWM_5B))
    {
        str_gs_pwmCtrl[ptr_str_l_config->enu_pwmIndx].enu_pwmPort = uint8_l_pwmPort;
        str_gs_pwmCtrl[ptr_str_l_config->enu_pwmIndx].enu_pwmPin = uint8_l_pwmPin;
        uint32_l_loadVal = SystemCoreClock / ptr_str_l_config->uint32_pwmFreq;
        uint32_l_MatchVal = (MAX_DUTY_CYCLE - (uint8_l_pwmDutyCycle % REPEATED_CYCLE)) * uint32_l_loadVal / MAX_DUTY_CYCLE;
        if (ptr_str_l_config->enu_pwmIndx & PWM_0B)
        {
            gpt_config((ptr_str_l_config->enu_pwmIndx - INDX_TO_BASE) >> INDX_TO_BASE, GPT_CFG_SPLIT_PAIR | GPT_CFG_B_PERIODIC);
            gpt_interruptClear( (ptr_str_l_config->enu_pwmIndx - INDX_TO_BASE) >> INDX_TO_BASE,  GPT_INT_B_TIMEOUT | GPT_INT_B_MATCH);
            gpt_interruptEnable((ptr_str_l_config->enu_pwmIndx - INDX_TO_BASE) >> INDX_TO_BASE,  GPT_INT_B_TIMEOUT | GPT_INT_B_MATCH);
            gpt_setLoad((ptr_str_l_config->enu_pwmIndx - INDX_TO_BASE) >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME), uint32_l_loadVal);
            gpt_setMatch((ptr_str_l_config->enu_pwmIndx - INDX_TO_BASE) >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME), uint32_l_MatchVal);
            gpt_interruptRegister((ptr_str_l_config->enu_pwmIndx - INDX_TO_BASE) >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME), str_gs_pwmCtrl[ptr_str_l_config->enu_pwmIndx].ptr_func_pwmCallback);
        }
        else
        {
            gpt_config(ptr_str_l_config->enu_pwmIndx >> INDX_TO_BASE, GPT_CFG_SPLIT_PAIR | GPT_CFG_A_PERIODIC);
            gpt_interruptClear( ptr_str_l_config->enu_pwmIndx >> INDX_TO_BASE,  GPT_INT_A_TIMEOUT | GPT_INT_A_MATCH);
            gpt_interruptEnable(ptr_str_l_config->enu_pwmIndx >> INDX_TO_BASE,  GPT_INT_A_TIMEOUT | GPT_INT_A_MATCH);
            gpt_setLoad(ptr_str_l_config->enu_pwmIndx >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME), uint32_l_loadVal);
            gpt_setMatch(ptr_str_l_config->enu_pwmIndx >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME), uint32_l_MatchVal);
            gpt_interruptRegister(ptr_str_l_config->enu_pwmIndx >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME), str_gs_pwmCtrl[ptr_str_l_config->enu_pwmIndx].ptr_func_pwmCallback);
        }
    }
    else
    {
        enu_l_tmuErrorState = PWM_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}
/************************************************************************/
enu_pwmErrorState_t pwm_start(const str_pwmCfg_t* ptr_str_l_config)
{
    enu_pwmErrorState_t  enu_l_tmuErrorState = PWM_OK;
    if (!ERROR_CHECK(ptr_str_l_config != NULL) &&
        !ERROR_CHECK((uint8_t)ptr_str_l_config->enu_pwmIndx <= PWM_5B)&&
        !ERROR_CHECK(str_gs_pwmCtrl[ptr_str_l_config->enu_pwmIndx].enu_pwmPort != PWM_NOT_INITIALIZED ))
    {

        if (ptr_str_l_config->enu_pwmIndx & PWM_0B)
        {
            gpt_enable((ptr_str_l_config->enu_pwmIndx - INDX_TO_BASE) >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME));
        }
        else
        {
            gpt_enable(ptr_str_l_config->enu_pwmIndx >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME));
        }
    }
    else
    {
        enu_l_tmuErrorState = PWM_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}
/************************************************************************/
enu_pwmErrorState_t pwm_stop(const str_pwmCfg_t* ptr_str_l_config)
{
    enu_pwmErrorState_t  enu_l_tmuErrorState = PWM_OK;
    if (!ERROR_CHECK(ptr_str_l_config != NULL) &&
        !ERROR_CHECK((uint8_t)ptr_str_l_config->enu_pwmIndx <= PWM_5B) &&
        str_gs_pwmCtrl[ptr_str_l_config->enu_pwmIndx].enu_pwmPort != PWM_NOT_INITIALIZED)
    {

        if (ptr_str_l_config->enu_pwmIndx & PWM_0B)
        {
            gpt_disable((ptr_str_l_config->enu_pwmIndx - INDX_TO_BASE) >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME));
        }
        else
        {
            gpt_disable(ptr_str_l_config->enu_pwmIndx >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME));
        }
    }
    else
    {
        enu_l_tmuErrorState = PWM_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}
/************************************************************************/
enu_pwmErrorState_t pwm_setDutyCycle(const str_pwmCfg_t* ptr_str_l_config , uint8_t uint8_l_pwmDutyCycle)
{
    enu_pwmErrorState_t  enu_l_tmuErrorState = PWM_OK;
    uint32_t uint32_l_loadVal;
    uint32_t uint32_l_MatchVal;

    if (!ERROR_CHECK(ptr_str_l_config != NULL) &&
        !ERROR_CHECK((uint8_t)ptr_str_l_config->enu_pwmIndx <= PWM_5B) &&
        str_gs_pwmCtrl[ptr_str_l_config->enu_pwmIndx].enu_pwmPort != PWM_NOT_INITIALIZED)
    {
        if (ptr_str_l_config->enu_pwmIndx & PWM_0B)
        {
            gpt_getLoad((ptr_str_l_config->enu_pwmIndx - INDX_TO_BASE) >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME), &uint32_l_loadVal);
            uint32_l_MatchVal = (MAX_DUTY_CYCLE - (uint8_l_pwmDutyCycle % REPEATED_CYCLE)) * uint32_l_loadVal / MAX_DUTY_CYCLE;
            gpt_setMatch((ptr_str_l_config->enu_pwmIndx - INDX_TO_BASE) >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME), uint32_l_MatchVal);
        }
        else
        {
            gpt_getLoad(ptr_str_l_config->enu_pwmIndx >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME), &uint32_l_loadVal);
            uint32_l_MatchVal = (MAX_DUTY_CYCLE - (uint8_l_pwmDutyCycle % REPEATED_CYCLE)) * uint32_l_loadVal / MAX_DUTY_CYCLE;
            gpt_setMatch(ptr_str_l_config->enu_pwmIndx >> INDX_TO_BASE, (ptr_str_l_config->enu_pwmIndx % INDX_TO_TIMER_NAME), uint32_l_MatchVal);
        }
    }
    else
    {
        enu_l_tmuErrorState = PWM_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}
/************************************************************************/
static void pwm_callback_0A(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin = 
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_0A].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_0A].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_0, (GPT_INT_A_TIMEOUT | GPT_INT_A_MATCH), &uint32_l_flags );
    gpt_interruptClear( GPT_BASE_0 , uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_A_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_A_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }

}
/************************************************************************/
static void pwm_callback_0B(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin =
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_0B].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_0B].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_0, (GPT_INT_B_TIMEOUT | GPT_INT_B_MATCH), &uint32_l_flags);
    gpt_interruptClear(GPT_BASE_0, uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_B_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_B_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
}
/************************************************************************/
static void pwm_callback_1A(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin =
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_1A].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_1A].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_1, (GPT_INT_A_TIMEOUT | GPT_INT_A_MATCH), &uint32_l_flags);
    gpt_interruptClear(GPT_BASE_1, uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_A_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_A_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }

}
/************************************************************************/
static void pwm_callback_1B(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin =
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_1B].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_1B].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_1, (GPT_INT_B_TIMEOUT | GPT_INT_B_MATCH), &uint32_l_flags);
    gpt_interruptClear(GPT_BASE_1, uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_B_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_B_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
}
/************************************************************************/
static void pwm_callback_2A(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin =
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_2A].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_2A].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_2, (GPT_INT_A_TIMEOUT | GPT_INT_A_MATCH), &uint32_l_flags);
    gpt_interruptClear(GPT_BASE_2, uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_A_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_A_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }

}
/************************************************************************/
static void pwm_callback_2B(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin =
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_2B].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_2B].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_2, (GPT_INT_B_TIMEOUT | GPT_INT_B_MATCH), &uint32_l_flags);
    gpt_interruptClear(GPT_BASE_2, uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_B_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_B_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
}
/************************************************************************/
static void pwm_callback_3A(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin =
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_3A].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_3A].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_3, (GPT_INT_A_TIMEOUT | GPT_INT_A_MATCH), &uint32_l_flags);
    gpt_interruptClear(GPT_BASE_3, uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_A_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_A_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }

}
/************************************************************************/
static void pwm_callback_3B(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin =
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_3B].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_3B].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_3, (GPT_INT_B_TIMEOUT | GPT_INT_B_MATCH), &uint32_l_flags);
    gpt_interruptClear(GPT_BASE_3, uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_B_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_B_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
}
/************************************************************************/
static void pwm_callback_4A(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin =
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_4A].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_4A].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_4, (GPT_INT_A_TIMEOUT | GPT_INT_A_MATCH), &uint32_l_flags);
    gpt_interruptClear(GPT_BASE_4, uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_A_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_A_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }

}
/************************************************************************/
static void pwm_callback_4B(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin =
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_4B].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_4B].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_4, (GPT_INT_B_TIMEOUT | GPT_INT_B_MATCH), &uint32_l_flags);
    gpt_interruptClear(GPT_BASE_4, uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_B_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_B_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
}
/************************************************************************/
static void pwm_callback_5A(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin =
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_5A].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_5A].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_5, (GPT_INT_A_TIMEOUT | GPT_INT_A_MATCH), &uint32_l_flags);
    gpt_interruptClear(GPT_BASE_5, uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_A_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_A_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }

}
/************************************************************************/
static void pwm_callback_5B(void)
{
    uint32_t uint32_l_flags;
    str_gpioPinOrGroupOfPins_t  str_l_gpioPin =
    {
    .enu_gpioPort = str_gs_pwmCtrl[PWM_5B].enu_pwmPort,
    .enu_gpioPinOrGroup = str_gs_pwmCtrl[PWM_5B].enu_pwmPin,
    .enu_modeConfig = GPIO_MODE_DIGITAL,
    .enu_direction = GPIO_DIRECTION_OUTPUT,
    .enu_pinDrive = GPIO_OUTPUT_DRIVE_4MA,
    .enu_pullMode = GPIO_FLOATING,
    .enu_interruptMode = GPIO_NO_INTERRUPT,
    };

    gpt_interruptStatus(GPT_BASE_5, (GPT_INT_B_TIMEOUT | GPT_INT_B_MATCH), &uint32_l_flags);
    gpt_interruptClear(GPT_BASE_5, uint32_l_flags);
    if ((uint32_l_flags & GPT_INT_B_TIMEOUT))
    {
        gpio_write(&str_l_gpioPin, GPIO_HIGH_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
    if ((uint32_l_flags & GPT_INT_B_MATCH))
    {
        gpio_write(&str_l_gpioPin, GPIO_LOW_LEVEL);
    }
    else
    {
        //DO NOTHING
    }
}
/************************************************************************/
