/************************************************************************/
/*                         INCLUDE FROM LIB                             */
/************************************************************************/
#include "..\LIB\error_check.h"
/************************************************************************/
/*                         INCLUDE FROM BUTTON                          */
/************************************************************************/
#include "..\HAL\BUTTON\button_interface.h"
/************************************************************************/
/*                         INCLUDE FROM LED                             */
/************************************************************************/
#include "..\HAL\PWM\pwm_interface.h"
/************************************************************************/
/************************************************************************/
#define  APP_SEQUENCE_NUM    4 
#define  APP_SEQ_0           0 
#define  APP_SEQ_1           1 
#define  APP_SEQ_2           2 
#define  APP_SEQ_3           3 
#define  RGB_ON_FREQ        5000
#define  RGB_GREEN_OFF_0_PERCENT   0
#define  RGB_GREEN_ON_30_PERCENT  30
#define  RGB_GREEN_ON_60_PERCENT  60
#define  RGB_GREEN_ON_90_PERCENT  90
/************************************************************************/
#define _ONE_SECOND_        1000
/************************************************************************/
static str_buttonsConfig_t str_gs_startButton =
{
 .enu_buttonsPort=BUTTONS_PORTF,
 .enu_buttonsPinOrGroup=BUTTON_P4,
 .enu_buttonsPullMode=BUTTONS_INTRTNAL_PULL_UP,
 .enu_buttonsInterruptMode=BUTTONS_CHANGE_FALLING_EDGE,
};
/************************************************************************/
static str_pwmCfg_t str_gs_ledControl = 
{
	.enu_pwmIndx = PWM_0A,
	.uint32_pwmFreq = RGB_ON_FREQ,
};
/************************************************************************/
static uint32_t enu_rgbBrightness[APP_SEQUENCE_NUM];
static uint8_t uint8_sequenceCounter ;
/************************************************************************/
/************************************************************************/
static void app_buttonPressed(void)
{/************************************************************************/
	if(uint8_sequenceCounter == APP_SEQ_3)
	{/************************************************************************/
		uint8_sequenceCounter = APP_SEQ_0 ;
	}/************************************************************************/
	else
	{/************************************************************************/
		uint8_sequenceCounter++;
	}/************************************************************************/
	pwm_setDutyCycle(&str_gs_ledControl, enu_rgbBrightness[uint8_sequenceCounter] );
	
}
/************************************************************************/
/************************************************************************/
void app3_rgbInit(void)
{
	/************************************************************************/
	while(ERROR_CHECK(!buttons_init(&str_gs_startButton)));
	while(ERROR_CHECK(!buttons_callBackSingleButtonInterrupt(BUTTONS_PORTF,BUTTON_P4,app_buttonPressed)));
	while(ERROR_CHECK(!rgb_init()));
	while(ERROR_CHECK(!(pwm_init(&str_gs_ledControl, str_gs_startButton.enu_buttonsPort , str_gs_startButton.enu_buttonsPinOrGroup,RGB_GREEN_OFF_0_PERCENT) || pwm_start(&str_gs_ledControl) )));

	/************************************************************************/
	enu_rgbBrightness[APP_SEQ_0]=RGB_GREEN_OFF_0_PERCENT;
	enu_rgbBrightness[APP_SEQ_1]=RGB_GREEN_ON_30_PERCENT;
	enu_rgbBrightness[APP_SEQ_2]=RGB_GREEN_ON_60_PERCENT;
	enu_rgbBrightness[APP_SEQ_3]=RGB_GREEN_ON_90_PERCENT;
	/************************************************************************/
}
/************************************************************************/
/************************************************************************/
void app3_rgbRoutine(void)
{
  //Do Nothing
}
/************************************************************************/
/************************************************************************/