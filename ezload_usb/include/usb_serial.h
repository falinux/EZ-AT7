//------------------------------------------------------------------------------
// 파 일 명 : usb_serial.h
// 프로젝트 : ez-jtag
// 설    명 : USB 시리얼을 처리하기 위한 헤더파일
// 작 성 자 : 유영창(frog@falinux.com), 이덕형(elenyuri@empal.com)
// 작 성 일 : 2007년 6월 10일
// 수 정 일 : 
// 수 정 일 : 
// 주    의 : 
// 라이센스 : BSD
//------------------------------------------------------------------------------

#ifndef _USB_SERIAL_HEADER_
#define _USB_SERIAL_HEADER_

#define PULLUP            	PIO_PA16
#define ID_PULLUP         	ID_PIOA
	
#define message_size 					1024
#define EP1_NUM 							1
#define EP2_NUM		 						2
#define EP3_NUM		 						3

#define EP_IN									2
#define EP_OUT 								1
#define EP_IN_SIZE 						0x40	// 64Byte
#define EP_OUT_SIZE 					0x40	// 64Byte


// usb standard request code
#define std_get_status_zero					0x0080
#define std_get_status_interface		0x0081
#define std_get_status_endpoint			0x0082

#define std_clear_feature_zero			0x0100
#define std_clear_feature_interface	0x0101
#define std_clear_feature_endpoint	0x0102

#define std_set_feature_zero				0x0300
#define std_set_feature_interface		0x0301
#define std_set_feature_endpoint		0x0302

#define std_set_address							0x0500
#define std_get_descriptor					0x0680
#define std_set_descriptor					0x0700
#define std_get_configuration				0x0880
#define std_set_configuration				0x0900
#define std_get_interface						0x0A81
#define std_set_interface						0x0B01
#define std_synch_frame							0x0C82

// cdc class specific request code
#define get_line_coding							0x21A1
#define set_line_coding							0x2021
#define set_control_line_state			0x2221

#define min(a,b) (( (a) < (b) ) ? (a) : (b) )

typedef struct 
{
	// Private menbers
	u8 currentConfiguration;
	u8 currentConnection;
	u8 currentRcvBank;
	
	//Public methods:
	//	u8	(*pfn_usbcom_isconfigured)	( void  );
	u32 (*pfn_usbcom_write)			( u8 *pdata, u32 bytes_remaining);
	u32 (*pfn_usbcom_read)			( u8 *pdata, u32 essential_pkt );

} usb_serial_t;

//extern usb_serial_t		usb_serial;

#ifndef _USB_SERIAL_VAR_

#endif


// External fuction description
extern void usbcom_init( void );
extern void usb_console_init( u32 baudrate );

extern RAMFUNC void usb_putc( const u8 c );
extern RAMFUNC u32 usb_read_ok( void );
extern u8  usb_getc( void );

#endif  // _USB_SERIAL_HEADER_

