/************************************************************************/
/*                         INCLUDE FROM LIB                             */
/************************************************************************/
#include "..\..\LIB\error_check.h"
/************************************************************************/
typedef enum 
{
	SYSTICK_POLLING_MODE = 0,
	SYSTICK_INTERRUPT_MODE,
}enu_systickmode_t;

typedef struct 
{
	uint32_t uint32_systickTicksMicroScond ;
	enu_systickmode_t enu_systickMode ;
}str_systickConfig_t;

const str_systickConfig_t str_systickLinkingConfig =
{
	.uint32_systickTicksMicroScond = 1000,
	.enu_systickMode = SYSTICK_INTERRUPT_MODE
};
/************************************************************************/