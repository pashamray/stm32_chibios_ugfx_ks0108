/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#define GDISP_SCREEN_WIDTH  		128
#define GDISP_SCREEN_HEIGHT 		64

#define GDISP_CHIP_WIDTH 				64
#define GDISP_SCREEN_CHIPS 			(GDISP_SCREEN_WIDTH / GDISP_CHIP_WIDTH)

// ============================================================================
#define bitset(port, bit) 			GPIO_SetBits(port, bit)
#define bitclr(port, bit) 			GPIO_ResetBits(port, bit)
// ============================================================================
#define BACKLIGHT_LED_RCC				RCC_APB2Periph_GPIOC
#define BACKLIGHT_LED_PORT			GPIOC
#define BACKLIGHT_LED_PIN				9

#define BACKLIGHT_LED_OFF   		bitset(BACKLIGHT_LED_PORT, BACKLIGHT_LED_PIN)
#define BACKLIGHT_LED_ON    		bitclr(BACKLIGHT_LED_PORT, BACKLIGHT_LED_PIN)
// ============================================================================
#define KS0108_CONTRAST_RCC			RCC_APB2Periph_GPIOC
#define KS0108_CONTRAST_PORT		GPIOC
#define KS0108_CONTRAST_PIN0		6
#define KS0108_CONTRAST_PIN1		7
#define KS0108_CONTRAST_PIN2		8

#define KS0108_PORT_DATA				GPIOA
#define KS0108_PORT_CTRL				GPIOC

#define KS0108_RST							1
#define KS0108_RS								3	//RS = D/I
#define KS0108_RW								2
#define KS0108_EN								4

#define KS0108_CS1							0
#define KS0108_CS2							1
#define KS0108_CS3							2

#define KS0108_SET_CS1					bitset(KS0108_PORT_CTRL, KS0108_CS1)
#define KS0108_CLR_CS1					bitclr(KS0108_PORT_CTRL, KS0108_CS1)

#define KS0108_SET_CS2					bitset(KS0108_PORT_CTRL, KS0108_CS2)
#define KS0108_CLR_CS2					bitclr(KS0108_PORT_CTRL, KS0108_CS2)

#define KS0108_SET_CS3					bitset(KS0108_PORT_CTRL, KS0108_CS3)
#define KS0108_CLR_CS3					bitclr(KS0108_PORT_CTRL, KS0108_CS3)

#define KS0108_CLR_ALL_CS				KS0108_CLR_CS1; KS0108_CLR_CS2; KS0108_CLR_CS3;
// ============================================================================
#define KS0108_CLR_RST					bitset(KS0108_PORT_CTRL, KS0108_RST)
#define KS0108_SET_RST					bitclr(KS0108_PORT_CTRL, KS0108_RST)

#define KS0108_SET_RW						bitset(KS0108_PORT_CTRL, KS0108_RW)
#define KS0108_CLR_RW						bitclr(KS0108_PORT_CTRL, KS0108_RW)

#define KS0108_SET_EN						bitset(KS0108_PORT_CTRL, KS0108_EN)
#define KS0108_CLR_EN						bitclr(KS0108_PORT_CTRL, KS0108_EN)

#define KS0108_SET_RS						bitset(KS0108_PORT_CTRL, KS0108_RS)
#define KS0108_CLR_RS						bitclr(KS0108_PORT_CTRL, KS0108_RS)

#define KS0108_SET_READ_STATUS	KS0108_CLR_RS; KS0108_SET_RW;
#define KS0108_SET_READ_DATA    KS0108_SET_RS; KS0108_SET_RW;
#define KS0108_SET_WRITE_DATA   KS0108_SET_RS; KS0108_CLR_RW;
#define KS0108_SET_WRITE_CMD    KS0108_CLR_RS; KS0108_CLR_RW;
// ============================================================================

static inline void init_board(GDisplay *g) {
	(void) g;
}

static inline void post_init_board(GDisplay *g) {
	(void) g;
}

static inline void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;

	if(state) {
		KS0108_SET_RST;
	} else {
		KS0108_CLR_RST;
	}
}

static inline void acquire_bus(GDisplay *g) {
	(void) g;
	KS0108_SET_EN;
}

static inline void release_bus(GDisplay *g) {
	(void) g;
	KS0108_CLR_EN;
}

static inline void write_cmd(GDisplay *g, uint8_t cmd) {
	(void) g;
	(void) cmd;
	KS0108_SET_WRITE_CMD;
}

static inline void write_data(GDisplay *g, uint8_t* data, uint16_t length) {
	(void) g;
	KS0108_SET_WRITE_DATA;

	for(uint8_t i = 0; i < length; i++)
	{
		switch(i % GDISP_CHIP_WIDTH) {
			case 0:
				KS0108_SET_CS1;
				break;
			case 1:
				KS0108_SET_CS2;
				break;
			case 2:
				KS0108_SET_CS3;
				break;
		}
		KS0108_PORT_DATA = data[i];
		KS0108_CLR_ALL_CS;
	}
}

static inline void read_data(GDisplay *g, uint8_t* data, uint16_t length) {
	(void) g;
	(void) data;
	(void) length;
}

static inline void read_status(GDisplay *g, uint8_t* data, uint16_t length) {
	(void) g;
	(void) data;
	(void) length;
}

static inline void set_backlight(GDisplay *g, uint8_t procent) {
	(void) g;
	if(procent == 100) {
		BACKLIGHT_LED_ON;
	} else {
		BACKLIGHT_LED_OFF;
	}
}

static inline void set_contrast(GDisplay *g, uint8_t procent) {
	(void) g;
	KS0108_CONTRAST_PORT &= ~(procent >> 3);
}

#endif /* _GDISP_LLD_BOARD_H */
