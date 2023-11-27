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
#include "..\HAL\RGB_LED\rgb_led_interface.h"
/************************************************************************/
/************************************************************************/
#define  APP_SEQUENCE_NUM    5 
#define  APP_SEQ_0           0 
#define  APP_SEQ_1           1 
#define  APP_SEQ_2           2 
#define  APP_SEQ_3           3 
#define  APP_SEQ_4           4 
/************************************************************************/
/************************************************************************/
static str_buttonsConfig_t str_gl_startButton =
{
 .enu_buttonsPort=BUTTONS_PORTF,
 .enu_buttonsPinOrGroup=BUTTON_P4,
 .enu_buttonsPullMode=BUTTONS_INTRTNAL_PULL_UP,
 .enu_buttonsInterruptMode=BUTTONS_CHANGE_FALLING_EDGE,
};
/************************************************************************/
/************************************************************************/
static enu_rgbColorON_t enu_rgbColors[APP_SEQUENCE_NUM];
static uint8_t uint8_sequenceCounter ;
/************************************************************************/
/************************************************************************/
static void app_buttonPressed(void)
{/************************************************************************/
	if(uint8_sequenceCounter == APP_SEQ_4)
	{/************************************************************************/
		uint8_sequenceCounter = APP_SEQ_0 ;
	}/************************************************************************/
	else
	{/************************************************************************/
		uint8_sequenceCounter++;
	}/************************************************************************/
}
/************************************************************************/
/************************************************************************/
void app1_rgbInit(void)
{
	/************************************************************************/
	while(ERROR_CHECK(!buttons_init(&str_gl_startButton)));
	while(ERROR_CHECK(!buttons_callBackSingleButtonInterrupt(BUTTONS_PORTF,BUTTON_P4,app_buttonPressed)));
	while(ERROR_CHECK(!rgb_init()));
	/************************************************************************/
	enu_rgbColors[APP_SEQ_0]=RGB_TURN_OFF;
	enu_rgbColors[APP_SEQ_1]=RGB_RED_ON;
	enu_rgbColors[APP_SEQ_2]=RGB_GREEN_ON;
	enu_rgbColors[APP_SEQ_3]=RGB_BLUE_ON;
	enu_rgbColors[APP_SEQ_4]=RGB_RED_GREEN_BLUE_ON;
	/************************************************************************/
}
/************************************************************************/
/************************************************************************/
void app1_rgbRoutine(void)
{
	/************************************************************************/
  while(ERROR_CHECK(!rgb_changeColor(enu_rgbColors[uint8_sequenceCounter])));
	/************************************************************************/
}
/************************************************************************/
/************************************************************************/