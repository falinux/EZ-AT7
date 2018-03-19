//------------------------------------------------------------------------------
// 화일명 main.h
// 설  명 : mode에 따라서 LED 상태를 변화시키는 함수를 정의 한다.   
// 
// 작성자 : 이덕형(elenyuri@empal.com)
// 작성일 : 2007년 08월 18일
// 저작권 : 
// 주  의 : 
// 라이센스 : BSD
//------------------------------------------------------------------------------

#ifndef _MEM_MAIN_HEADER_
#define _MEM_MAIN_HEADER_

// 광역 정의
#define CONSOLE_SELECT_DEBUG_PIN  ( 1 << 25 ) 		// PA25
#define USB_TO_SERIAL_BRIDGE_PIN  ( 1 << 24 ) 		// PA24

typedef struct
{
	u32 printf_select_usb;   // 0 이면 console, 1 이면 usb
	u32 usbtoserial_bridge;	// 0 이면 usb printf, 1이면 usb to serial bridge mode
}usb_consol_mode_t;

extern usb_consol_mode_t	usb_serial_mode;

// 광역 함수 정의 
extern s32 get_mode(void);
extern void led_on( u32 led_value );
extern void led_off( u32 led_value );

#endif  // _MEM_MAIN_HEADER_

