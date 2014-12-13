/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

// ============================================================================
#define BACKLIGHT_LED_RCC			RCC_APB2Periph_GPIOC
#define BACKLIGHT_LED_PORT		GPIOC
#define BACKLIGHT_LED_PIN			9

#define BACKLIGHT_LED_OFF   	GPIO_SetBits(BACKLIGHT_LED_PORT, BACKLIGHT_LED_PIN)
#define BACKLIGHT_LED_ON    	GPIO_ResetBits(BACKLIGHT_LED_PORT, BACKLIGHT_LED_PIN)
// ============================================================================
#define KS0108_CONTRAST_RCC		RCC_APB2Periph_GPIOC
#define KS0108_CONTRAST_PORT	GPIOC
#define KS0108_CONTRAST_PIN0	6
#define KS0108_CONTRAST_PIN1	7
#define KS0108_CONTRAST_PIN2	8

#define KS0108_PORT_DATA			GPIOA
#define KS0108_PORT_CTRL			GPIOC

#define KS0108_RST						1
#define KS0108_RS							3	//RS = D/I
#define KS0108_RW							2
#define KS0108_E							4

#define KS0108_CS1						0
#define KS0108_CS2						1

#define KS0108_CHIPS_LIST			KS0108_CS1, KS0108_CS2
// ============================================================================
#define KS0108_CLR_RST				GPIO_SetBits(KS0108_PORT_CTRL, KS0108_RST)
#define KS0108_SET_RST				GPIO_ResetBits(KS0108_PORT_CTRL, KS0108_RST)

#define KS0108_RW_H						GPIO_SetBits(KS0108_PORT_CTRL, KS0108_RW)
#define KS0108_RW_L						GPIO_ResetBits(KS0108_PORT_CTRL, KS0108_RW)

#define KS0108_E_H						GPIO_SetBits(KS0108_PORT_CTRL, KS0108_E)
#define KS0108_E_L						GPIO_ResetBits(KS0108_PORT_CTRL, KS0108_E)

#define KS0108_RS_H						GPIO_SetBits(KS0108_PORT_CTRL, KS0108_RS)
#define KS0108_RS_L						GPIO_ResetBits(KS0108_PORT_CTRL, KS0108_RS)

#define SET_READ_STATUS   		KS0108_RS_L KS0108_RW_H
#define SET_WRITE_DATA    		KS0108_RS_H KS0108_RW_L
#define SET_READ_DATA     		KS0108_RS_H KS0108_RW_H
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
		SET_RST;
	} else {
		CLR_RST;
	}
}

static inline void acquire_bus(GDisplay *g) {
	(void) g;
}

static inline void release_bus(GDisplay *g) {
	(void) g;
}

static inline void write_cmd(GDisplay *g, uint8_t cmd) {
	(void) g;
	(void) cmd;
}

static inline void write_data(GDisplay *g, uint8_t* data, uint16_t length) {
	(void) g;
	(void) data;
	(void) length;

	SET_WRITE_DATA;
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
	//===========================================================
	if ( contrast & BIT_2_MASK ) {
		GPIO_SetBits ( CONTRAST_PORT, CONTRAST_PIN2 );
	}	else {
		GPIO_ResetBits ( CONTRAST_PORT, CONTRAST_PIN2 );
	}
	//===========================================================
	if ( contrast & BIT_1_MASK ) {
		GPIO_SetBits ( CONTRAST_PORT, CONTRAST_PIN1 );
	} else {
		GPIO_ResetBits ( CONTRAST_PORT, CONTRAST_PIN1 );
	}
	//===========================================================
	if ( contrast & BIT_0_MASK ) {
		GPIO_SetBits ( CONTRAST_PORT, CONTRAST_PIN0 );
	} else {
		GPIO_ResetBits ( CONTRAST_PORT, CONTRAST_PIN0 );
	}
	//===========================================================
}

#endif /* _GDISP_LLD_BOARD_H */
