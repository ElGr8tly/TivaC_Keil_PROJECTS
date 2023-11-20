/**
 ** @file                   wdt.h
 ** @brief                  This is header file for watchdog timer HAL for TM4C123GH6PM
 ** @author                 Karim Osama
 ** @date                   Jan 23, 2023
 ** @version                0.1
 */

/*----------------------------------------------------------/
/- INCLUDES -----------------------------------------------/
/----------------------------------------------------------*/
#include "common.h"
#include "TM4C123.h"
/*----------------------------------------------------------/
/- PRIMITIVE TYPES ----------------------------------------/
/----------------------------------------------------------*/
typedef void(*tpf_wdt_cb)(void);
/*---------------------------------------------------------/
/- ENUM --------------------------------------------------/
/---------------------------------------------------------*/
typedef enum 
{
	WDT0 =0,
	WDT1   ,
	INVALID_WDn
}wdt_index_t;

typedef enum 
{
	USE_NORMAL_INT = 0,
	USE_NMI           ,
	DISABLE_INT       ,
	INVALID_INT_VALUE
}wdt_int_t;
/*----------------------------------------------------------/
/- STRUCTS AND UNIONS -------------------------------------/
/----------------------------------------------------------*/
typedef struct
{
	wdt_index_t wdt_index; 		/*Index of the WDT 0 or 1*/
	uint32_t timeout_ms;		/*Timeout in milliseconds*/
	bool use_test_mode; 		/*Pass true to run in test mode*/
	bool use_reset_mode; 		/*Pass true to enable restting mode*/
	wdt_int_t wdt_int;			/*Type of interrupt (NMI or Normal)*/
	tpf_wdt_cb pf_wdt_cb;		/*Callback to the app*/
}wdt_cfg_t;


/*---------------------------------------------------------/
/- APIs IMPLEMENTATION -----------------------------------/
/---------------------------------------------------------*/
int32_t wdt_init(wdt_cfg_t* pwdt_cfg);
void wdt_reset(wdt_index_t wdtn);
bool wdt_get_int_status(wdt_index_t wdtn);
void wdt_deinit(wdt_index_t wdtn);
