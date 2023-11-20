#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdint.h>

#ifndef NULL
#define NULL						((void*) 0)
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef bool
#define bool    uint8_t
#endif

typedef enum
{
    RET_OK = 0,
    RET_FAILED = -1
} error_t;

#define BIT(n)      (1UL << (n))
#define REG_GET_BIT(_REG_,_BIT_) ((_REG_) & _BIT_)
#define REG_SET_BIT(_REG_,_BIT_) ((_REG_) = (_REG_) | _BIT_)
#define REG_CLR_BIT(_REG_,_BIT_) ((_REG_) = (_REG_) & (~_BIT_))

#endif