//------------------------------------------------------------------------------
// ȭ�ϸ� main.h
// ��  �� : mode�� ���� LED ���¸� ��ȭ��Ű�� �Լ��� ���� �Ѵ�.   
// 
// �ۼ��� : �̴���(elenyuri@empal.com)
// �ۼ��� : 2007�� 08�� 18��
// ���۱� : 
// ��  �� : 
// ���̼��� : BSD
//------------------------------------------------------------------------------

#ifndef _MEM_MAIN_HEADER_
#define _MEM_MAIN_HEADER_

// ���� ����
#define CONSOLE_SELECT_DEBUG_PIN  ( 1 << 25 ) 		// PA25
#define USB_TO_SERIAL_BRIDGE_PIN  ( 1 << 24 ) 		// PA24

typedef struct
{
	u32 printf_select_usb;   // 0 �̸� console, 1 �̸� usb
	u32 usbtoserial_bridge;	// 0 �̸� usb printf, 1�̸� usb to serial bridge mode
}usb_consol_mode_t;

extern usb_consol_mode_t	usb_serial_mode;

// ���� �Լ� ���� 
extern s32 get_mode(void);
extern void led_on( u32 led_value );
extern void led_off( u32 led_value );

#endif  // _MEM_MAIN_HEADER_

