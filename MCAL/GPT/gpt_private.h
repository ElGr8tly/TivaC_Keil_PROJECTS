#ifndef __GPT_PRIVATE_H__
#define __GPT_PRIVATE_H__

typedef	enum {
	GPTCFG		  = 0x000,
	GPTTAMR	  = 0x004,
	GPTTBMR	  = 0x008,
	GPTCTL		  = 0x00C,
	GPTSYNC	  = 0x010,
	GPTIMR		  = 0x018,
	GPTRIS		  = 0x01C,
	GPTMIS		  = 0x020,
	GPTICR		  = 0x024,
	GPTTAILR	  = 0x028,
	GPTTBILR	  = 0x02C,
	GPTTAMATCHR  = 0x030,
	GPTTBMATCHR  = 0x034,
	GPTTAPR	  = 0x038,
	GPTTBPR	  = 0x03C,
	GPTTAPMR	  = 0x040,
	GPTTBPMR	  = 0x044,
	GPTTAR		  = 0x048,
	GPTTBR		  = 0x04C,
	GPTTAV		  = 0x050,
	GPTTBV		  = 0x054,
	GPTRTCPD	  = 0x058,
	GPTTAPS	  = 0x05C,
	GPTTBPS	  = 0x060,
	GPTTAPV	  = 0x064,
	GPTTBPV	  = 0x068,
	GPTPP        = 0xFC0,
}enu_GPTREG_t;

#define GPT_REG_BASE( _BASE_ )			   (((_BASE_) < 8) ? (0x40030000 + (_BASE_) * 0x1000) : ((0x4004C000 + (_BASE_ - 8) * 0x1000)))
#define GPT_CONFIG(  _REG_ , _BASE_ )       (*((volatile uint32_t*) (GPT_REG_BASE(_BASE_) + (_REG_))))

#define TAEN                    0
#define TBEN                    8
#define GPT_BASE_MAX			   6
#define GPT_CLEAR                 0X00
#define GPT_MODE_MASK			0x000000FF
#define GPT_CONFIG_MASK			0x07000000
#define GPT_CONFIG_SHIFT          24
#define GPT_TIMB_SHIFT			  8
#define RCGCTIMER                   (*((volatile uint32_t*) 0x400FE604))
#define WAIT_CYCLES()               do{ __asm("nop"); __asm("nop"); __asm("nop"); }while(0)



#endif