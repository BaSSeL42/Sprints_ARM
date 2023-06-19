
#include "LSTD_TYPES.h"
#include "mgpio_Interface.h"
#include "led.h"
#include "button.h"
#include "app.h"

#define RED							MGPIO_PINF_1
#define BLUE						MGPIO_PINF_2
#define GREEN						MGPIO_PINF_3
#define PUSH_BTN				MGPIO_PINF_4


static uint8_ u8_gs_btn_state = MGPIO_PIN_HIGH;
static uint8_ u8_gs_btn_prv_state = MGPIO_PIN_HIGH;
static uint8_ u8_gs_btn_press_counter = 4;
void APP_vidInit(void)
{
	HLed_Init(RED);				// RED
	HLed_Init(BLUE);			// BLUE
	HLed_Init(GREEN);			// GREEN
	
	
	
	HButton_Init(PUSH_BTN);			// Push button
	
	
	
	HLed_off(RED);			// RED OFF
	HLed_off(BLUE);			// BLUE	OFF
	HLed_off(GREEN);		// GREEN OFF
}


void APP_vidStart(void)
{
	HButton_getPinVal(PUSH_BTN,&u8_gs_btn_state);
	
	if(MGPIO_PIN_LOW == u8_gs_btn_state && MGPIO_PIN_HIGH == u8_gs_btn_prv_state)
	{
		if(4 == u8_gs_btn_press_counter)
		{
			u8_gs_btn_press_counter = 0;
		}
		else if(4 >  u8_gs_btn_press_counter)
		{
			u8_gs_btn_press_counter++;
		}
	}

	
	if(0 == u8_gs_btn_press_counter)
	{
		HLed_on(RED);			// RED On
		HLed_off(BLUE);			// BLUE	OFF
		HLed_off(GREEN);		// GREEN OFF
	}
	else if(1 == u8_gs_btn_press_counter)
	{
		HLed_off(RED);			// RED On
		HLed_off(BLUE);			// BLUE	OFF
		HLed_on(GREEN);		// GREEN OFF
	}
	else if(2 == u8_gs_btn_press_counter)
	{
		HLed_off(RED);			// RED On
		HLed_on(BLUE);			// BLUE	OFF
		HLed_off(GREEN);		// GREEN OFF
	}
	else if(3 == u8_gs_btn_press_counter)
	{
		HLed_on(RED);			// RED On
		HLed_on(BLUE);			// BLUE	OFF
		HLed_on(GREEN);		// GREEN OFF
	}
	else if(4 == u8_gs_btn_press_counter)
	{
		HLed_off(RED);			// RED On
		HLed_off(BLUE);			// BLUE	OFF
		HLed_off(GREEN);		// GREEN OFF
	}
	else{
		
	}
	
	u8_gs_btn_prv_state = u8_gs_btn_state;
}





















