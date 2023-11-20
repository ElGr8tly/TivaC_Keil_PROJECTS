/************************************************************************/
#include "error_check.h"
/************************************************************************/
/************************************************************************/
#define FILE_NAME_SIZE                  255
/************************************************************************/
typedef struct 
{/************************************************************************/
    uint32_t uint32_line;
    uint8_t uint8_flieName[FILE_NAME_SIZE];
} str_errorDetected_t;
/************************************************************************/
enu_stdErrorState_t  ERROR_DETECTED(const uint8_t* uint8_l_flieName, uint32_t uint32_l_line)
{
    str_errorDetected_t str_l_errorCheck= {0};
    strncpy(str_l_errorCheck.uint8_flieName, uint8_l_flieName, FILE_NAME_SIZE);
    str_l_errorCheck.uint32_line = uint32_l_line;
    __asm("bkpt 1");
    return STATE_NOK;
}/************************************************************************/
/************************************************************************/