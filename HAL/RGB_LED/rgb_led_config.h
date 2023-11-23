#ifndef _RGB_CONFIG_H_
#define _RGB_CONFIG_H_
/************************************************************************/
/*                         INCLUDE FROM LED                             */
/************************************************************************/
#include "..\LED\leds_interface.h"
/************************************************************************/
/*                         Choose Any From                              */
/*LEDS_PORTA, LEDS_PORTB, LEDS_PORTC, LEDS_PORTD, LEDS_PORTE, LEDS_PORTF*/
/************************************************************************/
#define RGB_PORT                    LEDS_PORTF     	
/************************************************************************/
/*                         Choose Any From                              */
/*    LED_P0, LED_P1, LED_P2, LED_P3, LED_P4, LED_P5, LED_P6, LED_P7    */
/************************************************************************/
#define RED_PIN                      LED_P1     
#define BLUE_PIN                    LED_P2
#define GREEN_PIN                     LED_P3	
/************************************************************************/
/*                         Choose Any From                              */
/*       LEDS_OPERATING_CURRENT_2MA, LEDS_OPERATING_CURRENT_4MA         */
/*                    LEDS_OPERATING_CURRENT_8MA                        */
/************************************************************************/
#define RGB_OPERATING_CURRENT LEDS_OPERATING_CURRENT_2MA
/************************************************************************/
/*                         Choose Any From                              */
/*                LEDS_ACTIVE_HIGH, LEDS_ACTIVE_LOW                     */
/************************************************************************/
#define RGB_ACTIVE_STATE         LEDS_ACTIVE_HIGH
/************************************************************************/
#endif /* _RGB_CONFIG_H_ */
