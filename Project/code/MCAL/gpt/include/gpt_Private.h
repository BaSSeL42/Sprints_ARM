#ifndef GPT_PRIVATE_H_
#define GPT_PRIVATE_H_


#define MGPT_OFFSET(X)		( ((X) < 8)? ((0x40030000) + ( (X)*(0x1000) )) :((0x4004C000) + ( ((X)-8)*(0x1000)) ) ) 

#define GPTMCFG_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x000)))
#define GPTMTAMR_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x004)))
#define GPTMTBMR_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x008)))

#define GPTMCTL_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x00C)))
#define GPTMSYNC _REG(x)				(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x010)))
#define GPTMIMR_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x018)))

#define GPTMRIS_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x01C)))
#define GPTMMIS_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x020)))
#define GPTMICR_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x024)))

#define GPTMTAILR_REG(x)				(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x028)))
#define GPTMTBILR_REG(x)				(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x02C)))
#define GPTMTAMATCHR_REG(x)			(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x030)))

#define GPTMTBMATCHR_REG(x)			(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x034)))
#define GPTMTAPR_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x038)))
#define GPTMTBPR_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x03C)))

#define GPTMTAPMR_REG(x)				(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x040)))
#define GPTMTBPMR_REG(x)				(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x044)))
#define GPTMTAR_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x048)))

#define GPTMTBR_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x04C)))
#define GPTMTAV_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x050)))
#define GPTMTBV_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x054)))

#define GPTMRTCPD_REG(x)				(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x058)))
#define GPTMTAPS_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x05C)))
#define GPTMTBPS_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x060)))

#define GPTMTAPV_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x064)))
#define GPTMTBPV_REG(x)					(*((volatile uint32_*)(MGPT_OFFSET(x) + 0x068)))
#define GPTMPP_REG(x)						(*((volatile uint32_*)(MGPT_OFFSET(x) + 0xFC0)))


#ifndef CLOCK_BASE_ADDRESS
#define CLOCK_BASE_ADDRESS  0x400FE000
#endif

#define RCGCWTIMER_REG			(*((volatile uint32_*)(CLOCK_BASE_ADDRESS + 0x65C )))	
#define RCGCTIMER_REG				(*((volatile uint32_*)(CLOCK_BASE_ADDRESS + 0x604 )))	



#define TAEN_IDX			(0U)
#define TATOIM_IDX		(0U)
#define TATOCINT_IDX	(0U)
#define TATORIS_IDX		(0U)
#define TASTALL_IDX		(1U)
#define CAMIM_IDX			(1U)
#define CAMCINT_IDX		(1U)
#define TAEVENT_IDX		(2U)
#define CAECINT_IDX		(2U)
#define TAAMS_IDX			(3U)
#define TACDIR_IDX		(4U)
#define TAPWML_IDX		(6U)
#define TAILD_IDX			(8U)
#define TAPWMIE_IDX		(9U)
#endif /*GPT_PRIVATE_H_*/
