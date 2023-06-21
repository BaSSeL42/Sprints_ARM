
#include "LSTD_TYPES.h"
//#include "mgpio_Interface.h"
#include "led.h"
#include "button.h"
#include "app.h"
#include "gpt_manager.h"
//#include "systick_Interface.h"

//#define RED							MGPIO_PINF_1
//#define BLUE						MGPIO_PINF_2
#define GREEN						MGPIO_PINF_3
#define PUSH_BTN				MGPIO_PINF_4

//void v_systick_cbf(void);
static void APP_vidCBK(void);
static uint8_ u8_gs_btn_state = MGPIO_PIN_HIGH;
static uint8_ u8_gs_btn_prv_state = MGPIO_PIN_HIGH;
const uint8_ u8_gc_arr_duty_cycles[5] = {0,30,60,90};
static uint8_ u8_gs_btn_press_counter = 0;
static uint8_ u8_gs_current_duty_cycle = 0;
static uint8_ u8_gs_duty_counter = 0;
uint64_ p_u64_int_cur_val;


void APP_vidInit(void)
{
	HLed_Init(GREEN);			// GREEN
	
	
	
	HButton_Init(PUSH_BTN);			// Push button
	
	
	st_gpt_timer_cfg_t st_gpt_timer_cfg = {
	
		.en_gpt_ch_id = GPT_CHANNEL_0,
		.en_gpt_mode = GPT_CH_MODE_PERIODIC,
		.en_gpt_stall = GPT_STALL_DISABLE,
		.en_gpt_time_x = GPT_TIME_MS,
		.u32_set_time = 50,
		.en_gpt_irq = GPT_IRQ_ENABLE,
		.ptr_func = APP_vidCBK
	};
	
	GPT_MANAGER_u8Init(&st_gpt_timer_cfg);
	
	//GPT_MANAGER_u8DutyCycle(40);
	GPT_MANAGER_u8Start();
	
	HLed_off(GREEN);		// GREEN OFF
}

void duty(uint8_ duty )
{
	if(((duty/10) > u8_gs_duty_counter) && (0<= u8_gs_duty_counter))
	{
		HLed_on(GREEN);
	}
	else if (((duty/10) <= u8_gs_duty_counter) && (10> u8_gs_duty_counter))
	{
		HLed_off(GREEN);
	}
	else
	{
		u8_gs_duty_counter = 0;
	}
}

void APP_vidStart(void)
{
	HButton_getPinVal(PUSH_BTN,&u8_gs_btn_state);
	
	if(MGPIO_PIN_LOW == u8_gs_btn_state && MGPIO_PIN_HIGH == u8_gs_btn_prv_state)
	{
		if(3 == u8_gs_btn_press_counter)
		{
			u8_gs_btn_press_counter = 0;
			u8_gs_current_duty_cycle = u8_gc_arr_duty_cycles[0];
		}
		else if(3 >  u8_gs_btn_press_counter)
		{
			u8_gs_btn_press_counter++;
			u8_gs_current_duty_cycle = u8_gc_arr_duty_cycles[u8_gs_btn_press_counter];
		}
		else{
			/* do nothing */
		}
	}
	duty(u8_gs_current_duty_cycle);

	
	u8_gs_btn_prv_state = u8_gs_btn_state;
}




static void APP_vidCBK(void)
{
	u8_gs_duty_counter++;
	/*static boolean flag = FALSE;

	if(flag == FALSE)
	{
		(void) HLed_off(GREEN);
		GPT_u8DutyCycle(gs_u32_duty_cycle_val);
		flag = TRUE;
	}
	else if (flag == TRUE)
	{
		(void) HLed_on(GREEN);
		GPT_u8DutyCycle(gs_u32_duty_cycle_flag);
		flag = FALSE;
	}*/
}














