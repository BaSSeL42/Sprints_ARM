/********************************************************************************************************************
*												Standard Types LIB
********************************************************************************************************************/
//#include "LSTD_TYPES.h"

/*********************************************************************************************************************
*												Peripheral Files
********************************************************************************************************************/
#include "led.h"
#include "timerM_Interface.h" // for timer manager 
#include "button.h"
#include "car_control_interface.h"
#include "app.h"


/********************************************************************************************************************
*												Local APIs Prototype
********************************************************************************************************************/

/* todo: any local APIs prototype put here */
void btn_stop_cbf(void);
void timer_1_cbf(void);
void timer_2_cbf(void);
void APP_longSide(void);
void APP_shortSide(void);
void APP_stop(void);
void App_rotate(void);
void APP_startState(void);
void APP_stopState(void);
void APP_longSideLed(uint8_ u8_led_state);

/********************************************************************************************************************
*												MACROs
********************************************************************************************************************/

/* todo: this section for MACROs */

#define LED_NUMS			3
#define BTN_NUMS			2
#define TIMERS_USED		2

#define LED_ON				1
#define LED_OFF				0

#define BTN_START										0
#define BTN_STOP										1
#define LED_MOVING_FWD_LONG_SIDE		0
#define LED_MOVING_FWD_SHORT_SIDE		1
#define LED_MOVING_FWD_ROTATE				2
#define LED_MOVING_FWD_STOP					3
#define Timer0											GPT_CHANNEL_0
#define Timer1											GPT_CHANNEL_1

/********************************************************************************************************************
*												Global Variables
********************************************************************************************************************/

/* todo: any global / static variables put here in this section */
// Program state
static uint8_ u8_gs_v_progState = BTN_STOP;

// Delay Counter
uint8_ volatile u8_gv_delay = 0;

// PWM Counter
uint8_ volatile u8_gv_pwm = 0;

str_led_config_t arr_str_g_led_config[LED_NUMS] = {
	{.u8_led_id = LED_MOVING_FWD_SHORT_SIDE,
	 .enu_port = DIO_PORTF,
		.enu_pin = DIO_PIN_1
	},
	{.u8_led_id = LED_MOVING_FWD_ROTATE,
	 .enu_port = DIO_PORTF,
		.enu_pin = DIO_PIN_2},
	{.u8_led_id = LED_MOVING_FWD_STOP,
	 .enu_port = DIO_PORTF,
		.enu_pin = DIO_PIN_3}
};


button_str_btn_config_t arr_str_g_btn_config[BTN_NUMS] = {
	{.port_name = DIO_PORTF,
		.pin = DIO_PIN_0,
		.button_state = BUTTON_RELEASED,
		.button_active = BUTTON_ACTIVE_LOW
	},
	{.port_name = DIO_PORTF,
		.pin = DIO_PIN_4,
		.button_state = BUTTON_RELEASED,
		.button_active = BUTTON_ACTIVE_LOW
	}
};

const str_car_config_t str_gc_car_config = {
	.motor_1_config.port_name = DIO_PORTE,
	.motor_1_config.pin_1 = DIO_PIN_0,
	.motor_1_config.pin_2 = DIO_PIN_1,
	.motor_2_config.port_name = DIO_PORTE,
	.motor_2_config.pin_1 = DIO_PIN_2,
	.motor_2_config.pin_2 = DIO_PIN_3
};


st_gpt_timer_cfg_t arr_st_g_gpt_timer_cfg[TIMERS_USED] = {
	{
		.en_gpt_ch_id = GPT_CHANNEL_0,
		.en_gpt_mode = GPT_CH_MODE_PERIODIC,
		.en_gpt_stall = GPT_STALL_DISABLE,
		.en_gpt_time_x = GPT_TIME_MS,
		.u32_set_time = 2,
		.en_gpt_irq = GPT_IRQ_ENABLE,
		.ptr_func = timer_1_cbf
	},
		{
			.en_gpt_ch_id = GPT_CHANNEL_1,
			.en_gpt_mode = GPT_CH_MODE_PERIODIC,
			.en_gpt_stall = GPT_STALL_DISABLE,
			.en_gpt_time_x = GPT_TIME_MS,
			.u32_set_time = 500,
			.en_gpt_irq = GPT_IRQ_ENABLE,
			.ptr_func = timer_2_cbf
		}
};


/********************************************************************************************************************
*												main APIs Implementation
********************************************************************************************************************/
void APP_vidInit(void)
{
	// Initialize all LEDs
	for(uint8_ u8_index = 0 ; u8_index < LED_NUMS ; u8_index++)
	{
		HLED_Init(&arr_str_g_led_config[u8_index]);
	}
	
	// Initialize all buttons
	HButton_Init(&arr_str_g_btn_config[BTN_START]);
	HButton_initializa_with_int(&arr_str_g_btn_config[BTN_STOP] ,btn_stop_cbf );
	__enable_irq();
	
	// Initialize car module
	//car_init(&str_gc_car_config);
	
	// Initialize Timer 1
	TIMM_u8Init(&arr_st_g_gpt_timer_cfg[Timer0]);
	
	
	// Initialize Timer 2
	TIMM_u8Init(&arr_st_g_gpt_timer_cfg[Timer1]);
	
	
	
}


void APP_vidStart(void)
{
	while(1)
	{	
		while (u8_gs_v_progState == BTN_STOP)
		{
			// Perform stop state routine 
			APP_stopState();
		}
		while (u8_gs_v_progState == BTN_START)
		{
			// Perform start state routine
			APP_startState();
		}
	}
}




/********************************************************************************************************************
*												Local APIs Implementation
********************************************************************************************************************/

/* todo: any local APIs Implementation put here */

void btn_stop_cbf(void)
{
	// Set Delay counter and PWM Counter to zero
	u8_gv_delay = 0;
	u8_gv_pwm = 0 ;
	
	// Change program state to stop 
	u8_gs_v_progState = BTN_STOP;
}

void timer_1_cbf(void)
{
	// Increment PWM counter
	u8_gv_pwm++;
}

void timer_2_cbf(void)
{
	// Increment Delay counter
	u8_gv_delay++;
}







void APP_longSide(void)
{
	// Turn all LEDs off and turn long side LED on
//	HLED_off(LED_MOVING_FWD_SHORT_SIDE);
//	HLED_off(LED_MOVING_FWD_ROTATE);
//	HLED_off(LED_MOVING_FWD_STOP);
//	APP_longSideLed(LED_ON);

	
	
	// car move forward with 50% speed
	
	u8_gv_pwm = 0;
	TIMM_u8Start(Timer0);							// start timer 0
	while (u8_gv_pwm <= 5)						// 10 ms ON
	{
//		car_move(&str_gc_car_config,CAR_FORWARD);
		APP_longSideLed(LED_ON);
	}
	while (u8_gv_pwm > 5 && u8_gv_pwm <= 10)	// 10 ms OFF
	{
//		car_stop(&str_gc_car_config);
		APP_longSideLed(LED_OFF);
	}
	TIMM_vidStop(Timer0);										// stop timer 0
	u8_gv_pwm = 0;
}

void APP_shortSide(void)
{
	// Turn all LEDs off and turn short side LED on
//	HLED_on(LED_MOVING_FWD_SHORT_SIDE);
	//HLED_off(LED_MOVING_FWD_LONG_SIDE);
	HLED_off(LED_MOVING_FWD_ROTATE);
	HLED_off(LED_MOVING_FWD_STOP);
	
	
	// move forward with 30% speed
	
	u8_gv_pwm = 0;
	TIMM_u8Start(Timer0);									// start timer 0
	while (u8_gv_pwm <= 3)							// 6 ms ON
	{
//		car_move(&str_gc_car_config,CAR_FORWARD);
		HLED_on(LED_MOVING_FWD_SHORT_SIDE);
	}
	while (u8_gv_pwm > 3 && u8_gv_pwm <= 10)		// 14 ms OFF
	{
//		car_stop(&str_gc_car_config);
		HLED_off(LED_MOVING_FWD_SHORT_SIDE);
	}
	TIMM_vidStop(Timer0);										// stop timer 0
	u8_gv_pwm = 0;
}

void APP_stop(void)
{
	// Turn all LEDs off and turn stop LED on
	HLED_off(LED_MOVING_FWD_SHORT_SIDE);
	//HLED_off(LED_MOVING_FWD_LONG_SIDE);
	HLED_off(LED_MOVING_FWD_ROTATE);
	HLED_on(LED_MOVING_FWD_STOP);
	
	
	// Here We Will STOP motors
	//car_stop(&str_gc_car_config);
}
void App_rotate(void)
{
	// Turn all LEDs off and turn rotate LED on
	HLED_off(LED_MOVING_FWD_SHORT_SIDE);
	//HLED_off(LED_MOVING_FWD_LONG_SIDE);
//	HLED_on(LED_MOVING_FWD_ROTATE);
	HLED_off(LED_MOVING_FWD_STOP);
	
	
	
	// rotate to right with 50% speed for 0.5 s to achieve 90 degree rotate to side
	u8_gv_pwm = 0;
	TIMM_u8Start(Timer0);									// start timer 0
	while (u8_gv_pwm <= 5)							// 10 ms ON
	{
//		car_move(&str_gc_car_config,CAR_RIGHT);
		HLED_on(LED_MOVING_FWD_ROTATE);
	}
	while (u8_gv_pwm > 5 && u8_gv_pwm <= 10)		// 10 ms OFF
	{
//		car_stop(&str_gc_car_config);
		HLED_off(LED_MOVING_FWD_ROTATE);
	}
	TIMM_vidStop(Timer0);										// stop timer 0
	u8_gv_pwm = 0;
}


void APP_startState(void)
{
	
	HButton_enable_INT(&arr_str_g_btn_config[BTN_STOP]);											// Enable External on stop btn
	TIMM_u8Start(Timer1);						// start timer 1
	if (u8_gv_delay>= 2)										// 1s delay
	{
		if (u8_gv_delay <= 8 )									// longest side for 3s with speed 50%
		{
			APP_longSide();
		}
		else if (u8_gv_delay>8 && u8_gv_delay <=9)				// stop for 0.5
		{
			APP_stop();
			
		}
		else if (u8_gv_delay >9 && u8_gv_delay <=10)			// rotate 90 degree to right
		{
			App_rotate();
		}
		else if (u8_gv_delay > 10 && u8_gv_delay <=11)			// Stop the car for 0.5 s
		{
			APP_stop();
		}
		else if (u8_gv_delay > 11 && u8_gv_delay <= 15)				// short size for 2 s with speed 30%
		{
			APP_shortSide();
		}
		else if (u8_gv_delay>15 && u8_gv_delay <=16)				// stop for 0.5 s
		{
			APP_stop();
			
			
		}
		else if (u8_gv_delay >16 && u8_gv_delay <=17)			// rotate 90 degree to right
		{
			App_rotate();
		}
		else if (u8_gv_delay > 17 && u8_gv_delay <=18)			// Stop the car for 0.5 s
		{
			APP_stop();
			
		}
		else{
			u8_gv_delay = 2;
		}
		
	}
}
void APP_stopState(void)
{
	btn_enu_btn_state_t btnState = BUTTON_RELEASED;
	
	
	HButton_disable_INT(&arr_str_g_btn_config[BTN_STOP]);						// Disable External on stop btn
	
	TIMM_vidStop(Timer1);				// stop timer 1
	
	
	
	
	APP_stop();							
	
	
	// Read Start Button state
	HButton_getPinVal(&arr_str_g_btn_config[BTN_START],&btnState);
	
	if (btnState == BUTTON_PRESSED)
	{
		TIMM_vidSynchDelay_ms(GPT_CHANNEL_2, 25);
		if (btnState == BUTTON_PRESSED)
		{
			u8_gs_v_progState = BTN_START;
		}	
	}
	u8_gv_delay = 0;
}




void APP_longSideLed(uint8_ u8_led_state)
{
		if (u8_led_state == LED_ON)
		{
			HLED_on(LED_MOVING_FWD_SHORT_SIDE);
			HLED_on(LED_MOVING_FWD_ROTATE);
			HLED_on(LED_MOVING_FWD_STOP);
		}
		else if(u8_led_state == LED_OFF)
		{
			HLED_off(LED_MOVING_FWD_SHORT_SIDE);
			HLED_off(LED_MOVING_FWD_ROTATE);
			HLED_off(LED_MOVING_FWD_STOP);			
		}
		else 
		{
			/*do nothing */
		}
	
}

