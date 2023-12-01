#ifndef __GPT_INTRFACE_H__

#define __GPT_INTRFACE_H__

typedef void (ptr_func_gptIRQCallBack_t)(void);

typedef enum
{
    GPT_OK = 0,
    GPT_WRONG_INPUT,
} enu_gptErrorState_t;


typedef enum
{
    GPT_BASE_0 = 0,
    GPT_BASE_1,
    GPT_BASE_2,
    GPT_BASE_3,
    GPT_BASE_4,
    GPT_BASE_5,
} enu_gptBase_t;


typedef enum
{
    GPT_CFG_ONE_SHOT    = 0x00000021,
    GPT_CFG_PERIODIC    = 0x00000022,
    GPT_CFG_SPLIT_PAIR  = 0x04000000,
    GPT_CFG_A_ONE_SHOT  = 0x00000021,
    GPT_CFG_A_PERIODIC  = 0x00000022,
    GPT_CFG_B_ONE_SHOT  = 0x00002100,
    GPT_CFG_B_PERIODIC  = 0x00002200,
} enu_gptConfig_t;

typedef enum
{
    GPT_INT_A_TIMEOUT   = 0x00000001,
    GPT_INT_A_MATCH     = 0x00000010,
    GPT_INT_B_TIMEOUT   = 0x00000100,
    GPT_INT_B_MATCH     = 0x00000800,
} enu_gptInterruptFlags_t;

typedef enum
{
    GPT_TIMER_A   ,
    GPT_TIMER_B   ,
    GPT_A_AND_B   ,
} enu_gptTimerName_t;

enu_gptErrorState_t gpt_config(enu_gptBase_t enu_l_gptBase, enu_gptConfig_t enu_l_gptConfig);
enu_gptErrorState_t gpt_disable(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName);
enu_gptErrorState_t gpt_enable(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName);
enu_gptErrorState_t gpt_setLoad(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName, uint32_t uint32_l_gptLoadVal);
enu_gptErrorState_t gpt_getLoad(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName, uint32_t* ptr_uint32_l_gptLoadVal);
enu_gptErrorState_t gpt_setMatch(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName, uint32_t uint32_l_gptMatchVal);
enu_gptErrorState_t gpt_getMatch(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName, uint32_t* ptr_uint32_l_gptMatchVal);
enu_gptErrorState_t gpt_getValue(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName, uint32_t* ptr_uint32_l_gptVal);
enu_gptErrorState_t gpt_interruptClear(enu_gptBase_t enu_l_gptBase, enu_gptInterruptFlags_t enu_l_intFlags );
enu_gptErrorState_t gpt_interruptDisable(enu_gptBase_t enu_l_gptBase, enu_gptInterruptFlags_t enu_l_intFlags );
enu_gptErrorState_t gpt_interruptEnable(enu_gptBase_t enu_l_gptBase, enu_gptInterruptFlags_t enu_l_intFlags );
enu_gptErrorState_t gpt_interruptRegister(enu_gptBase_t enu_l_gptBase, enu_gptTimerName_t enu_l_gptTimerName, ptr_func_gptIRQCallBack_t* ptr_func_l_handler);
enu_gptErrorState_t gpt_interruptStatus(enu_gptBase_t enu_l_gptBase, enu_gptInterruptFlags_t enu_l_intFlags, uint32_t* ptr_uint32_l_intStatus);


#endif//