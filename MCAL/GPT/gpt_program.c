#include "TM4C123.h"
#include "core_cm4.h"

#include "..\..\LIB\error_check.h"
#include "..\..\LIB\bit_math.h"

#include "gpt_interface.h"
#include "gpt_private.h"


static const uint32_t gpt_interruptID[] = 
{
    TIMER0A_IRQn, TIMER1A_IRQn, TIMER2A_IRQn, TIMER3A_IRQn, TIMER4A_IRQn, TIMER5A_IRQn,
};

static ptr_func_gptIRQCallBack_t* ptr_func_gptIRQsCallBack[GPT_BASE_MAX][GPT_A_AND_B];


enu_gptErrorState_t gpt_config(enu_gptBase_t enu_l_gptBase, enu_gptConfig_t enu_l_gptConfig)
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;

    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX))
    {
        SET_BIT(RCGCTIMER, enu_l_gptBase);
        /* Wait for three cycles */
        WAIT_CYCLES();
        /* Disable GPT */
        CLR_BIT(GPT_CONFIG(GPTCTL, enu_l_gptBase), TAEN);
        CLR_BIT(GPT_CONFIG(GPTCTL, enu_l_gptBase), TBEN);
        GPT_CONFIG(GPTCFG, enu_l_gptBase) = enu_l_gptConfig >> GPT_CONFIG_SHIFT;
        /* Reset gpt mode registers A & B */
        GPT_CONFIG(GPTTAMR, enu_l_gptBase) = GPT_CLEAR;
        GPT_CONFIG(GPTTBMR, enu_l_gptBase) = GPT_CLEAR;
        /* Set gpt A Mode */
        WRITE_BITS_VLAUE(GPT_CONFIG(GPTTAMR, enu_l_gptBase), GPT_MODE_MASK, enu_l_gptConfig , GPT_CLEAR);
        if (( enu_l_gptConfig & GPT_CFG_SPLIT_PAIR) == GPT_CFG_SPLIT_PAIR)
        {
            WRITE_BITS_VLAUE(GPT_CONFIG(GPTTBMR, enu_l_gptBase), GPT_MODE_MASK, enu_l_gptConfig >> GPT_TIMB_SHIFT , GPT_CLEAR);
        }
        else
        {
            //Do Noting
        }
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}

enu_gptErrorState_t gpt_disable(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName)
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX) &&
        !ERROR_CHECK((uint8_t)enu_l_gptTimerName <= GPT_A_AND_B))
    {
        if (enu_l_gptTimerName == GPT_TIMER_A)
        {
            CLR_BIT(GPT_CONFIG(GPTCTL, enu_l_gptBase), TAEN);
        }
        else if (enu_l_gptTimerName == GPT_TIMER_B)
        {
            CLR_BIT(GPT_CONFIG(GPTCTL, enu_l_gptBase), TBEN);
        }
        else
        {
            CLR_BIT(GPT_CONFIG(GPTCTL, enu_l_gptBase), TAEN);
            CLR_BIT(GPT_CONFIG(GPTCTL, enu_l_gptBase), TBEN);
        }
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}


enu_gptErrorState_t gpt_enable(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName)
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX) &&
        !ERROR_CHECK((uint8_t)enu_l_gptTimerName <= GPT_A_AND_B))
    {
        if (enu_l_gptTimerName == GPT_TIMER_A)
        {
            SET_BIT(GPT_CONFIG(GPTCTL, enu_l_gptBase), TAEN);
        }
        else if (enu_l_gptTimerName == GPT_TIMER_B)
        {
            SET_BIT(GPT_CONFIG(GPTCTL, enu_l_gptBase), TBEN);
        }
        else
        {
            SET_BIT(GPT_CONFIG(GPTCTL, enu_l_gptBase), TAEN);
            SET_BIT(GPT_CONFIG(GPTCTL, enu_l_gptBase), TBEN);
        }
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}


enu_gptErrorState_t gpt_setLoad(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName, uint32_t uint32_l_gptLoadVal)
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX) &&
        !ERROR_CHECK((uint8_t)enu_l_gptTimerName <= GPT_A_AND_B))
    {
         if (enu_l_gptTimerName == GPT_TIMER_B)
        {
             GPT_CONFIG(GPTTBILR, enu_l_gptBase) = uint32_l_gptLoadVal;
        }
        else
        {
            GPT_CONFIG(GPTTAILR, enu_l_gptBase) = uint32_l_gptLoadVal;
        }
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}


enu_gptErrorState_t gpt_getLoad(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName , uint32_t* ptr_uint32_l_gptLoadVal)
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX) &&
        !ERROR_CHECK((uint8_t)enu_l_gptTimerName <= GPT_A_AND_B) &&
        !ERROR_CHECK(ptr_uint32_l_gptLoadVal !=  NULL))
    {
        if (enu_l_gptTimerName == GPT_TIMER_B)
        {
            *ptr_uint32_l_gptLoadVal = GPT_CONFIG(GPTTBILR, enu_l_gptBase);
        }
        else
        {
            *ptr_uint32_l_gptLoadVal = GPT_CONFIG(GPTTAILR, enu_l_gptBase);
        }
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}


enu_gptErrorState_t gpt_setMatch(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName, uint32_t uint32_l_gptMatchVal)
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX) &&
        !ERROR_CHECK((uint8_t)enu_l_gptTimerName <= GPT_A_AND_B))
    {
        if (enu_l_gptTimerName == GPT_TIMER_B)
        {
            GPT_CONFIG(GPTTBMATCHR, enu_l_gptBase) = uint32_l_gptMatchVal;
        }
        else
        {
            GPT_CONFIG(GPTTAMATCHR, enu_l_gptBase) = uint32_l_gptMatchVal;
        }
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}

enu_gptErrorState_t gpt_getMatch(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName, uint32_t * ptr_uint32_l_gptMatchVal)
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX) &&
        !ERROR_CHECK((uint8_t)enu_l_gptTimerName <= GPT_A_AND_B) &&
        !ERROR_CHECK(ptr_uint32_l_gptMatchVal != NULL))
    {
        if (enu_l_gptTimerName == GPT_TIMER_B)
        {
            *ptr_uint32_l_gptMatchVal = GPT_CONFIG(GPTTBMATCHR, enu_l_gptBase);
        }
        else
        {
            *ptr_uint32_l_gptMatchVal = GPT_CONFIG(GPTTAMATCHR, enu_l_gptBase);
        }
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}

enu_gptErrorState_t gpt_getValue(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName , uint32_t * ptr_uint32_l_gptVal)
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX) &&
        !ERROR_CHECK((uint8_t)enu_l_gptTimerName <= GPT_A_AND_B) &&
        !ERROR_CHECK(ptr_uint32_l_gptVal != NULL))
    {
        if (enu_l_gptTimerName == GPT_TIMER_B)
        {
            *ptr_uint32_l_gptVal = GPT_CONFIG(GPTTBMATCHR, enu_l_gptBase);
        }
        else
        {
            *ptr_uint32_l_gptVal = GPT_CONFIG(GPTTBR, enu_l_gptBase);
        }
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}



enu_gptErrorState_t gpt_interruptClear(enu_gptBase_t enu_l_gptBase, enu_gptInterruptFlags_t enu_l_intFlags )
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX))
    {
        GPT_CONFIG(GPTICR, enu_l_gptBase) = enu_l_intFlags ;
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}


enu_gptErrorState_t gpt_interruptDisable(enu_gptBase_t enu_l_gptBase, enu_gptInterruptFlags_t enu_l_intFlags )
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX))
    {
        GPT_CONFIG(GPTIMR, enu_l_gptBase) &= ~enu_l_intFlags ;
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}


enu_gptErrorState_t gpt_interruptEnable(enu_gptBase_t enu_l_gptBase, enu_gptInterruptFlags_t enu_l_intFlags )
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX))
    {
        GPT_CONFIG(GPTIMR, enu_l_gptBase) |= enu_l_intFlags ;
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}


enu_gptErrorState_t gpt_interruptRegister(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName, ptr_func_gptIRQCallBack_t* ptr_func_l_handler)
{
    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX) &&
        !ERROR_CHECK((uint8_t)enu_l_gptTimerName <= GPT_A_AND_B)&&
        !ERROR_CHECK(ptr_func_l_handler != NULL))
    {
        if (enu_l_gptTimerName == GPT_TIMER_B)
        {
            ptr_func_gptIRQsCallBack[enu_l_gptBase][GPT_TIMER_B] = ptr_func_l_handler;
            NVIC_EnableIRQ(gpt_interruptID[enu_l_gptBase] + 1);
            __enable_irq();
        }
        else
        {
            ptr_func_gptIRQsCallBack[enu_l_gptBase][GPT_TIMER_A] = ptr_func_l_handler;
            NVIC_EnableIRQ(gpt_interruptID[enu_l_gptBase]);
            __enable_irq();
        }
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}

enu_gptErrorState_t gpt_interruptStatus(enu_gptBase_t enu_l_gptBase, enu_gptInterruptFlags_t enu_l_intFlags, uint32_t * ptr_uint32_l_intStatus)
{

    enu_gptErrorState_t  enu_l_tmuErrorState = GPT_OK;
    if (!ERROR_CHECK((uint8_t)enu_l_gptBase < GPT_BASE_MAX)&&
        !ERROR_CHECK(ptr_uint32_l_intStatus != NULL))
    {
        *ptr_uint32_l_intStatus = ( GPT_CONFIG(GPTMIS, enu_l_gptBase) & enu_l_intFlags);
    }
    else
    {
        enu_l_tmuErrorState = GPT_WRONG_INPUT;
    }
    return enu_l_tmuErrorState;
}


void TIMER0A_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_0][GPT_TIMER_A] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_0][GPT_TIMER_A]();
    }
}

void TIMER0B_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_0][GPT_TIMER_B] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_0][GPT_TIMER_B]();
    }
}

void TIMER1A_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_1][GPT_TIMER_A] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_1][GPT_TIMER_A]();
    }
}

void TIMER1B_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_1][GPT_TIMER_B] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_1][GPT_TIMER_B]();
    }
}

void TIMER2A_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_2][GPT_TIMER_A] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_2][GPT_TIMER_A]();
    }
}

void TIMER2B_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_2][GPT_TIMER_B] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_2][GPT_TIMER_B]();
    }
}

void TIMER3A_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_3][GPT_TIMER_A] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_3][GPT_TIMER_A]();
    }
}

void TIMER3B_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_3][GPT_TIMER_B] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_3][GPT_TIMER_B]();
    }
}

void TIMER4A_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_4][GPT_TIMER_A] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_4][GPT_TIMER_A]();
    }
}

void TIMER4B_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_4][GPT_TIMER_B] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_4][GPT_TIMER_B]();
    }
}

void TIMER5A_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_5][GPT_TIMER_A] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_5][GPT_TIMER_A]();
    }
}

void TIMER5B_Handler(void)
{
    if (ptr_func_gptIRQsCallBack[GPT_BASE_5][GPT_TIMER_B] != NULL)
    {
        ptr_func_gptIRQsCallBack[GPT_BASE_5][GPT_TIMER_B]();
    }
}


