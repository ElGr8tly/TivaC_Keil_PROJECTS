#ifndef _ERROR_CHECK_H_
#define _ERROR_CHECK_H_
/************************************************************************/
#include "std_types.h"
/************************************************************************/
/*                  ERROR STATE Type Declarations                       */
/************************************************************************/
typedef enum
{
    STATE_OK = 0,
    STATE_NOK   ,
} enu_stdErrorState_t;
/************************************************************************/
enu_stdErrorState_t ERROR_DETECTED(const uint8_t* uint8_l_flieName, uint32_t uint32_l_line);
/************************************************************************/
#define ERROR_CHECK( _TRUE_OR_FALSE_ )    (((_TRUE_OR_FALSE_) == TRUE) ? STATE_OK : ERROR_DETECTED(__FILE__, __LINE__))
/************************************************************************/
#endif