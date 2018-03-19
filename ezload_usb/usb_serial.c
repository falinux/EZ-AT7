//------------------------------------------------------------------------------
// 파 일 명 : usb_serial.c
// 프로젝트 : ez-jtag
// 설    명 : USB 를 다루는 루틴 
// 작 성 자 : 유영창(frog@falinux.com), 이덕형(elenyuri@empal.com)
// 작 성 일 : 2007년 6월 10일
// 수 정 일 :
// 수 정 일 :
// 주    의 :
// 라이센스 : BSD
//------------------------------------------------------------------------------

#include <typedef.h>
#include <register.h>
#include <setup.h>

#include <stdio.h>
#include <string.h>
#include <irq.h>
#include <timer.h>

#include <module.h>

#define _USB_SERIAL_VAR_
#include <usb_serial.h>

#include <main.h>
#include <console.h>
//
// _USB_DEBUG_ 옵션을 활성화 하려면 반드시 딥스위치의 시리얼 옵션 을 활성화 시킬것 !!!
//

// #define _USB_DEBUG_ 
#define _EVBOARD_MODE_ 

usb_serial_t	usb_serial;

const char dev_descriptor[] = 
{
	// device descriptor for atmel cdc -> garget serial 0525, A4A7
	0x12,	// b_length
	0x01, 	// b_sescriptor_type
	0x10, 	// bcd_usbl
	0x01, 	 
	0x02, 	// bDeviceClass :	 CDC class code
	0x00, 	// bDeviceSubclass : CDC class sub code 
	0x00, 	// bDeviceProtocol :	CDC Device protocol 
	0x08, 	// bMaxPacketSize0
	0x25,  	// idVendorL
	0x05,	
	0xA7,	// idProduckL
	0xA4,
	0x10, 	// bcdDeviceL
	0x01,
	0x00,	// iManufacturer // 0x01
	0x00,	// iProduct
	0x00,	// SerialNumber
	0x01	// bNumConfigs
};

const char cfg_descriptor[] = 
{
	// Configuration 1 descriptor 
	0x09,	// CbLength
	0x02,	// CbDescriptorType
	0x43,	// CwTotalLength 2 EP + Control
	0x00,	
	0x02,	// CbNumInterfaces
	0x01,	// CbConfigurationValue
	0x00,	// CiConfiguration
	0xC0,	// CbmAttributes 0xA0
	0x00,	// CMaxPower

	// Communication Class Interface Descriptor Requirement 
	0x09, 	// bLength
	0x04, 	// bDescriptorType
	0x00, 	// bInterfaceNumber
	0x00, 	// bAInternateSetting
	0x01, 	// bNumEndpoints
	0x02, 	// bInterfaceClass
	0x02, 	// bInterfaceSubClass
	0x00, 	// bInterfaceProtocol
	0x00, 	// iInterface

	// Header Function Descriptor
	0x05, 	// bFunction Length
	0x24, 	// bDescriptor type : CS_INTERFACE
	0x00, 	// bDescriptor subtype : Header Func Desc
	0x10, 	// bcdCDC : 1.1
	0x01, 

	// ACM(Abstract Control Model) Functional Descriptor 
	0x04,	// bFunctionLength
	0x24,	// bDescriptorType : CS_INTERFACE
	0x02,	// bDescriptor Subtype : ACM Func Desc
	0x00, 	// bmCapabilities
	
	// Union Fuctional Descriptor
	0x05,	// bFunctionLength
	0x24,	// bDescriptorType : CS_INTERFACE
	0x06,	// bDescriptor Subtype : Union Func Desc
	0x00,	// bMasterInterface : Communication Class Interface
	0x01,	// bSlaveInterface0 : Data Class Interface
	
	// Call Management Fuctional Descriptor
	0x05,	// bFunctionLength
	0x24,	// bDescriptor Type : CS_INTERFACE
	0x01,	// bDescriptor Subtype : Call Management Func Desc
	0x00,	// bmCapabilities : D1 + D0
	0x01,	// bDataInterface : Data Class Interface 1
	
	// Endpoint 3 descriptor : Host reads data from USB bus(or Device)
	0x07,	// bLength
	0x05,	// bDescriptorType
	0x80 + EP3_NUM,	// bEndpointAddress, Endpoint 03 - IN
	0x03,	// bmAttributes		INT
	0x08,	// wMaxPacketSize
	0x00,	
	0xFF,	// bInterval

	// Data Class Interface Descriptor Requirement
	0x09,	// bLength
	0x04,	// bDescriptorType
	0x01,	// bInterfaceNumber
	0x00,	// bAlternateSetting
	0x02,	// bNumEndpoints
	0x0A,	// bInterfaceClass
	0x00,	// bInterfaceSubclass
	0x00,	// bInterfaceProtocol
	0x00,	// iInterface
	
	// First alternate setting
	// Endpoint 1 descriptor : Device reads data from USB bus(or host)
	0x07,	// bLength
	0x05,	// bDescriptorType
	0x00 + EP1_NUM,	// bEndpointAddress, Endpoint 01 - OUT
	0x02,	// bmAttributes	BULK
	EP_OUT_SIZE,	// wMaxPacketSize
	0x00,
	0x00,	// bInterval

	// Endpoint 2 descriptor : Host reads data from USB bus(or device)
	0x07,	// bLength
	0x05,	// bDescriptorType
	0x80 + EP2_NUM,	// bEndpointAddress, Endpoint 02 - IN
	0x02,	// bmAttributes BULK
	EP_IN_SIZE,	// wMaxPacketSize
	0x00,
	0x00	// bInterval
};
  
typedef struct 
{
	u32 dw_dter_rate;
	u8 b_char_format;
	u8 b_parity_type;
	u8 b_data_bits;
} __attribute__ ((packed)) usbcom_comportsetting_t;

// b_char_format
#define USB_CDC_1_STOP_BITS                     0
#define USB_CDC_1_5_STOP_BITS                   1
#define USB_CDC_2_STOP_BITS                     2

// b_parity_type
#define USB_CDC_NO_PARITY                       0
#define USB_CDC_ODD_PARITY                      1
#define USB_CDC_EVEN_PARITY                     2
#define USB_CDC_MARK_PARITY                     3
#define USB_CDC_SPACE_PARITY                    4

usbcom_comportsetting_t  s_comportsetting = 
{
	115200L, USB_CDC_1_STOP_BITS, USB_CDC_NO_PARITY, 8
};

#define RX_QUEUE_SIZE   (256*2*2)
#define RX_QUEUE_MASK    0x3FF

u8  usb_rx_data[RX_QUEUE_SIZE];
// u32 usb_rx_count;
u32  usb_rx_head;
u32  usb_rx_tail;

#define USB_TX_FIFO_MAX 64
u8  usb_tx_fifo[USB_TX_FIFO_MAX];
u32 usb_tx_fifo_cnt;
u32 usb_tx_ing_flag;

static void  usbcom_usb_send_data( const char *pdata, u32 length);

//------------------------------------------------------------------------------
// 설명 : USB PORT 가 HOST 와 연결되도록 만든다. 
//------------------------------------------------------------------------------
void usb_port_connect( void )
{
	#ifdef _USB_DEBUG_
	printf("usb port connect\n");
	#endif
	
	// USB 디바이스를 활성화 시킨다. 
	CKGR_PLLR |= CKGR_USBDIV_1 ;   // Set the PLL USB Divider
	PMC_SCER = PMC_UDP;            // Enables the 48MHz USB clock UDPCK and System Peripheral USB Clock
	PMC_PCER = (1 << ID_UDP);

	// 풀업 저항 조절하여 HOST에게 포트가 연결되었음을 알린다.
	PMC_PCER = (1 << ID_PIOA); 

	#ifdef _EVBOARD_MODE_	
	PIO_PER  = PIO_PA16;          // Set in PIO mode
	PIO_OER  = PIO_PA16;          // Configure in Output
	PIO_CODR = PIO_PA16;
	#endif	
}


//----------------------------------------------------------------------------
// 설명 Stall 을 전송한다. 
//----------------------------------------------------------------------------
static void  usbcom_usb_send_stall(void)
{
	UDP_CSR0 |= UDP_FORCESTALL;
	while ( !(UDP_CSR0 & UDP_ISOERROR) );

	UDP_CSR0 &= ~(UDP_FORCESTALL | UDP_ISOERROR);
	while (UDP_CSR0 & (UDP_FORCESTALL | UDP_ISOERROR));
}

//----------------------------------------------------------------------------
// 설명 : 빈 팻킷을 전송한다.
// Send zero length packet through the control endpoint
//----------------------------------------------------------------------------
static void  usbcom_usb_send_zero_len_packet(void)
{
	u32 mcount;
	
	UDP_CSR0 |= UDP_TXPKTRDY;
	
	for( mcount = 0; mcount < 10000; mcount++ )
	{
		if( !(UDP_CSR0 & UDP_TXPKTRDY) ) break;

		#ifdef _USB_DEBUG_
		printf( "." );
		#endif
	}
	
}

//----------------------------------------------------------------------------
// 설명 : 현재 연결 상태를 설정한다. 
//----------------------------------------------------------------------------
static void usbcom_cdc_set_control_line_state( u16 wValue)
{
//	usb_serial.currentConnection = wValue;
	usbcom_usb_send_zero_len_packet();
	
	// 읽어오는 것이 있어야 한다.
	
	
	#ifdef _USB_DEBUG_
	printf("SET_CONTROL_LINE_STATE : send zero length pack.(wValue=%08x)\n", wValue);
	#endif
}

//----------------------------------------------------------------------------
// 설명 : LINE 상태를 전송한다. 
//----------------------------------------------------------------------------
static void usbcom_cdc_get_line_coding(u16 wLength)
{
	usbcom_usb_send_data( (char *) &s_comportsetting, min(sizeof(s_comportsetting), wLength) );

	#ifdef _USB_DEBUG_
	printf("GET_LINE_CODING : send data.(wLength=%08x)\n", wLength);
	#endif
}

//----------------------------------------------------------------------------
// 설명 : LINE 상태를 설정하기를 요구 받아 처리한다. 
//----------------------------------------------------------------------------
static void usbcom_cdc_set_line_coding( u16 wLength )
{
	u8 	*c;
	u32	i;
	
	#ifdef _USB_DEBUG_
	printf( "SIZE = %d:%d\n", wLength, sizeof( s_comportsetting ) );
	#endif                               

	// endpoint0가 들어올때까지 대기 
	while ( !(UDP_CSR0 & UDP_RX_DATA_BK0) );
	
	// FIFO 데이터를 읽어 온다. 
	c = (u8	*) &s_comportsetting;
	for ( i=0 ; i<wLength ; i++ ) c[i] = UDP_FDR0;

	// 콘솔 재 설정 
	if( usb_serial_mode.printf_select_usb )
	{	
	    console_init_by_usb( s_comportsetting.dw_dter_rate, 
	                         s_comportsetting.b_char_format,
	                         0, 8 );
	}    
	
	#ifdef _USB_DEBUG_
		printf( "CDC SET dw_dter_rate  = %08X \n", s_comportsetting.dw_dter_rate  );
		printf( "CDC SET b_char_format = %02X \n", s_comportsetting.b_char_format );
		printf( "CDC SET b_parity_type = %02X \n", s_comportsetting.b_parity_type );
		printf( "CDC SET b_data_bits   = %02X \n", s_comportsetting.b_data_bits   );
	#endif                               
                                         
	// endpoint0가 들어온것을 표시하는 UDP_CSR0에 표시 지우기
	UDP_CSR0 &= ~(UDP_RX_DATA_BK0);
	usbcom_usb_send_zero_len_packet();

	#ifdef _USB_DEBUG_
	printf("SET_LINE_CODING : send zero length pack.\n");
	#endif

}

//----------------------------------------------------------------------------
// 설명 : feature endpoint 를 클리어 한다. 
//----------------------------------------------------------------------------
static void usbcom_cdc_clear_feature_endpoint(u16 wIndex, u16 wValue)
{
	wIndex &= 0x0F;

	if ((wValue == 0) && wIndex && (wIndex <= 3)) 
	{	
		switch(wIndex)
		{
			case 1:	UDP_CSR1 = (UDP_EPEDS | UDP_EPTYPE_BULK_OUT); break;
			case 2:	UDP_CSR2 = (UDP_EPEDS | UDP_EPTYPE_BULK_IN);  break;
			case 3:	UDP_CSR3 = (UDP_EPEDS | UDP_EPTYPE_ISO_IN);	 break;
			default : break;
		}
		
				
		usbcom_usb_send_zero_len_packet();
		
		#ifdef _USB_DEBUG_
		printf("STD_CLEAR_FEATURE_ENDPOINT : send zero length pack.\n");
		#endif
	}
	else
	{
		usbcom_usb_send_stall();
	}
	#ifdef _USB_DEBUG_
	printf("STD_CLEAR_FEATURE_ENDPOINT : send all.\n");
	#endif
}

//----------------------------------------------------------------------------
// 설명 : feature interface 를 클리어 한다. 
//----------------------------------------------------------------------------
static void usbcom_cdc_clear_feature_interface(void)
{
	usbcom_usb_send_zero_len_packet();
	#ifdef _USB_DEBUG_
	printf("STD_CLEAR_FEATURE_INTERFACE : send zero length pack.\n");
	#endif
}



//----------------------------------------------------------------------------
// 설명 : feature zero 를 클리어 한다. 
//----------------------------------------------------------------------------
static void usbcom_cdc_clear_feature_zero(void)
{
	usbcom_usb_send_stall();
	#ifdef _USB_DEBUG_
	printf("STD_CLEAR_FEATURE_ZERO : send all.\n");
	#endif
}			
	
//----------------------------------------------------------------------------
// 설명 : endpoint 상태에 따라서 레지스터를 조정한다. 
//----------------------------------------------------------------------------
static void usbcom_udp_endpoint_status(u16 wStatus, u16 wIndex)
{
	switch (wIndex)
	{
		case 0: wStatus = (UDP_CSR0 & UDP_EPEDS) ? 0 : 1; break;
		case 1: wStatus = (UDP_CSR1 & UDP_EPEDS) ? 0 : 1; break;
		case 2: wStatus = (UDP_CSR2 & UDP_EPEDS) ? 0 : 1; break;						
		case 3: wStatus = (UDP_CSR3 & UDP_EPEDS) ? 0 : 1; break;
		default : break;
	}
}


//----------------------------------------------------------------------------
// 설명 : endpoint status 를 전송한다. 
//----------------------------------------------------------------------------
static void usbcom_cdc_get_status_endpoint(u16 wStatus, u16 wIndex)
{
	wStatus = 0;
	wIndex &= 0x0F;
			
	if ( (UDP_GLBSTATE & UDP_CONFG) && (wIndex <= 3) ) 
	{
		usbcom_udp_endpoint_status(wStatus, wIndex);
		usbcom_usb_send_data( (char *) &wStatus, sizeof(wStatus) );
		#ifdef _USB_DEBUG_
		printf("STD_GET_STATUS_ENDPOINT : send config\n");
		#endif
	}

	else if ( (UDP_GLBSTATE & UDP_FADDEN) && (wIndex == 0) ) 
	{
		usbcom_udp_endpoint_status(wStatus, wIndex);
		usbcom_usb_send_data( (char *) &wStatus, sizeof(wStatus) );
		#ifdef _USB_DEBUG_
		printf("STD_GET_STATUS_ENDPOINT : send address\n");
		#endif
	}
	else	
	{
		usbcom_usb_send_stall();
	}
	#ifdef _USB_DEBUG_
	printf("\n STD_GET_STATUS_ENDPOINT : send all");
	#endif
}


//----------------------------------------------------------------------------
// 설명 : status interface 를 전송한다. 
//----------------------------------------------------------------------------
static void usbcom_cdc_get_status_interface(u16 wStatus)
{
	wStatus = 0;
	usbcom_usb_send_data( (char *) &wStatus, sizeof(wStatus) );
	#ifdef _USB_DEBUG_
	printf("STD_GET_STATUS_INTERFACE\n");
	#endif
}

//----------------------------------------------------------------------------
// 설명 : status zero 를 전송한다. 
//----------------------------------------------------------------------------
static void usbcom_cdc_get_status_zero(u16 wStatus)
{
	wStatus = 0;
	usbcom_usb_send_data( (char *) &wStatus, sizeof(wStatus) );
	#ifdef _USB_DEBUG_
	printf("STD_GET_STATUS_ZERO\n");
	#endif
}

//----------------------------------------------------------------------------
// 설명 : configureationn을 전송한다. 
//----------------------------------------------------------------------------
static void usbcom_cdc_get_configuration( void )
{
	usbcom_usb_send_data( (char *) &(usb_serial.currentConfiguration), sizeof(usb_serial.currentConfiguration) );
	#ifdef _USB_DEBUG_
	printf("STD_GET_CONFIGURATION >> usb_serial.currentConfiguration[%d]\n", usb_serial.currentConfiguration);	
	#endif
}



//------------------------------------------------------------------------------
// 설명 : 디스크립터를 전달한다. 
//------------------------------------------------------------------------------
static void usbcom_cdc_get_desctiptor(u16 wValue, u16 wLength)
{
	switch ( wValue )
	{
		case 0x100 : 
			// Return Device Descriptor
			usbcom_usb_send_data( dev_descriptor, min( sizeof(dev_descriptor), wLength ) );
			#ifdef _USB_DEBUG_
			printf("STD_GET_DESCRIPTOR DEVICE\n");
			#endif
			break;
					
		case 0x200 :
			// Return Configuration Descriptor
			usbcom_usb_send_data(cfg_descriptor, min(sizeof(cfg_descriptor), wLength));
			#ifdef _USB_DEBUG_
			printf("STD_GET_DESCRIPTOR CONFIGURE \n");
			#endif
			break;

		default :
			usbcom_usb_send_stall();
			#ifdef _USB_DEBUG_
			printf("\n STD_GET_DESCRIPTOR : Stall\n");
			#endif
			break;
	}
}

//------------------------------------------------------------------------------
// 설명 : 어드레스를 보낼 준비를 한다. 
//------------------------------------------------------------------------------
static void  usbcom_cdc_set_address(u16 wValue)
{
	usbcom_usb_send_zero_len_packet();
	UDP_FADDR = (UDP_FEN | wValue);
	UDP_GLBSTATE  = (wValue) ? UDP_FADDEN : 0;
	#ifdef _USB_DEBUG_
	printf("STD_SET_ADDRESS : FADDR %08X, GLB_STATE %08X\n", UDP_FADDR, UDP_GLBSTATE);
	#endif
}

//------------------------------------------------------------------------------
// 설명 : 어드레스를 보낼 준비를 한다. 
//------------------------------------------------------------------------------
static void usbcom_cdc_set_configuration( u16 wValue)
{
	usb_serial.currentConfiguration = wValue;

	usbcom_usb_send_zero_len_packet();

	UDP_GLBSTATE  |= (wValue) ? UDP_CONFG : UDP_FADDEN;


	// Endpoint 3
	UDP_CSR1 |= (wValue) ? (UDP_EPEDS | UDP_EPTYPE_BULK_OUT) : 0;	// Added
	UDP_CSR2 |= (wValue) ? (UDP_EPEDS | UDP_EPTYPE_BULK_IN)  : 0;	// Added
	UDP_CSR3 |= (wValue) ? (UDP_EPEDS | UDP_EPTYPE_ISO_IN)   : 0;	// Added

	#ifdef _USB_DEBUG_
	printf("STD_SET_CONFIGURATION >> GLB_STATE %08X\n", UDP_GLBSTATE );
	#endif
}


//----------------------------------------------------------------------------
// 설명 : USB 디바이스가 호스트에 열거되기 위한 처리 
//----------------------------------------------------------------------------	
static void usbcom_cdc_enumerate( void )
{
	u8 	bmRequestType;
	u8 	bRequest;
	u16 wValue, wIndex, wLength, wStatus;

	bmRequestType		=	UDP_FDR0;
	bRequest				=	UDP_FDR0;
	wValue				=	(UDP_FDR0 & 0xFF);
	wValue			 	|=	(UDP_FDR0 << 8);
	wIndex				=	(UDP_FDR0 & 0xFF);
	wIndex			 	|=	(UDP_FDR0 << 8);
	wLength				=	(UDP_FDR0 & 0xFF);
	wLength			 	|=	(UDP_FDR0 << 8);

	if(bmRequestType & 0x80) 
	{
		//UDP_CSR0 = UDP_DIR;
		UDP_CSR0 |= UDP_DIR;
		while ( !(UDP_CSR0 & UDP_DIR) );
	}
	
	UDP_CSR0 &= ~(UDP_RXSETUP);
	while ( (UDP_CSR0  & UDP_RXSETUP)  );

	// 표준 디바이스 리퀘스트에 관한 헨들러 처리 루틴 ( USB 스펙 테이블 9-3 )
	switch ( (bRequest << 8) | bmRequestType) 
	{
		case std_get_descriptor :
			usbcom_cdc_get_desctiptor(wValue, wLength);
			break;

		case std_set_address :
			usbcom_cdc_set_address(wValue); 
			break;
			
		case std_set_configuration :
			usbcom_cdc_set_configuration( wValue);
			break;
			
		case std_get_configuration :
			usbcom_cdc_get_configuration();
			break;
	
		case std_get_status_zero :
			usbcom_cdc_get_status_zero(wStatus);
			break;
			
		case std_get_status_interface :
			usbcom_cdc_get_status_interface(wStatus);
			break;

		case std_get_status_endpoint :
			usbcom_cdc_get_status_endpoint(wStatus, wIndex);
			break;

		case std_clear_feature_zero :
			usbcom_cdc_clear_feature_zero();
			break;

		case std_clear_feature_interface :
			usbcom_cdc_clear_feature_interface();
			break;
			
		case std_clear_feature_endpoint :
			usbcom_cdc_clear_feature_endpoint(wIndex, wValue);
			break;

		// handle CDC class requests
		case set_line_coding :
			usbcom_cdc_set_line_coding( wLength );
			break;
		
		case get_line_coding :
			usbcom_cdc_get_line_coding(wLength);
			break;
					
		case set_control_line_state :
			usbcom_cdc_set_control_line_state( wValue );
			break;;
			
		default:
			usbcom_usb_send_stall();
			#ifdef _USB_DEBUG_
			printf("Default \n");
			#endif
		    break;
	}
}

//----------------------------------------------------------------------------
// UDP_Read (User Datagram Protocol)
// Read available data from Endpoint OUT
//----------------------------------------------------------------------------
static u32  usbcom_udp_read( u8 *pdata, u32 essential_pkt)
{
	u32 		packet_size;
	u32  	    cur_recv_bank;

	// 현재의 수신 뱅크를 읽어 온다 .
	cur_recv_bank = usb_serial.currentRcvBank;

	// 여기서의 length는 패킷의 크기 단위로서 64바이트가 최소 패킷 단위 이다.. 
	packet_size = min( UDP_CSR1 >> 16, 64 );
	while(packet_size)
	{
		usb_rx_data[usb_rx_head] = UDP_FDR1; 
		usb_rx_head++;
		usb_rx_head &= RX_QUEUE_MASK;
		packet_size--;
	}
	
	// 현재의 사용한 수신 뱅크를 초기화 시킨다.
	UDP_CSR1 &= ~(cur_recv_bank);

	// 현재 사용중인 뱅크가 어떤 것인지 확인하고 
	// 다른 뱅크를 사용하도록 한다.
	if (cur_recv_bank == UDP_RX_DATA_BK0)
	{	
		cur_recv_bank = UDP_RX_DATA_BK1;
	}
	else	
	{
		cur_recv_bank = UDP_RX_DATA_BK0;
	}
	usb_serial.currentRcvBank = cur_recv_bank;

}


static u8   up0_send_data[1024];       // EP0 송신 데이터 버퍼 
static u8  *up0_send_ptr = NULL;       // 송신 위치 포인터
static s32  up0_send_data_length = 0;  // 남은 송신 데이터 크기 

//----------------------------------------------------------------------------
// 설명 : 컨트롤 엔드포인트를 통해 데이터를 전송한다.
//----------------------------------------------------------------------------
static void  usbcom_usb_send_data( const char *pdata, u32 length)
{
	u32 packet_length;

	up0_send_data_length = length;
	up0_send_ptr         = &up0_send_data[0];
	if( pdata ) memcpy( up0_send_ptr, pdata, length );
	
	packet_length = min(up0_send_data_length, 8);
	up0_send_data_length -= packet_length;
	
	while (packet_length--)	UDP_FDR0 = *up0_send_ptr++;
	
	UDP_CSR0 |= UDP_TXPKTRDY;
	
}


//------------------------------------------------------------------------------
// 설명 : cdc를 통해 호스트쪽으로 데이터를 전송한다.
//------------------------------------------------------------------------------
void usbcom_cdc_transfer( void )
{
	u32 packet_length;
	
	if( up0_send_ptr )
	{	
		
		if( up0_send_data_length )// 전송할 데이터가 있는 경우 
		{
			
			packet_length = min(up0_send_data_length, 8);
			up0_send_data_length -= packet_length;
			
			while (packet_length--)	UDP_FDR0 = *up0_send_ptr++;
			
			UDP_CSR0 |= UDP_TXPKTRDY;
			
		}
		else	// 전송할 데이터가 없는 경우 
		{
			up0_send_ptr = NULL;
		}
	}
		
	// 송신이 끝났음을 알리는 인터럽트 상태 플라그를 지운다. 
	if (UDP_CSR0 & UDP_TXCOMP) 
	{
		UDP_CSR0 &= ~(UDP_TXCOMP);
		while (UDP_CSR0 & UDP_TXCOMP);
	}
}


//------------------------------------------------------------------------------
// 설명 : USB 인터럽트 핸들러 
//------------------------------------------------------------------------------
void usb_irq_handler( void )
{
	u32 udp_state;
	u8  data[message_size];
//	u32 lp;

	#ifdef _USB_DEBUG_
//	printf( "USB Interrupt CALL UDP_ISR = %08X \n", UDP_ISR );
//	printf( "[" );
	#endif

	while(1)
	{	
		udp_state = UDP_ISR;

		#ifdef _USB_DEBUG_
//		printf( "(S:%08X)", udp_state );	
//		printf( "UDP_IMR = %08X\n", UDP_IMR );
		#endif
	
		if( !udp_state ) break;

		if( udp_state & UDP_SOFINT ) 
		{
			UDP_ICR = UDP_SOFINT;
			UDP_GLBSTATE &= ~(UDP_RMWUPE);
			#ifdef _USB_DEBUG_
//			printf( "UDP_SOFINT [%08X]", UDP_GLBSTATE );
			#endif
	
			continue;
		}	

		if( udp_state & UDP_RXSUSP) // SUSPEND 중지하다.
		{
			UDP_ICR = UDP_RXSUSP;	
			#ifdef _USB_DEBUG_
			printf( "UDP_RXSUSP\n" );
			#endif
			continue;
		}	

		if( (udp_state & UDP_RXRSM) || (udp_state & UDP_WAKEUP) ) // RESUME 다시 시작하다.
		{
			UDP_ICR = UDP_RXRSM | UDP_WAKEUP | UDP_RXSUSP;	
			UDP_IDR = UDP_RXRSM | UDP_WAKEUP;

			#ifdef _USB_DEBUG_
			printf( "UDP_RXRSM or UDP_WAKEUP\n" );
			#endif
			continue;
		}	

		if( udp_state & UDP_ENDBUSRES ) 
		{
			UDP_TXVC  = 0; // UDP_TXVDIS
		
			UDP_RSTEP = (u32)-1; // 모든 엔드포인트를 리셋
			UDP_RSTEP = 0;
			
			UDP_FADDR     = UDP_FEN; // 펑션을 인에이블한다.
			UDP_GLBSTATE  = 0;
    	
			UDP_CSR0 = (UDP_EPEDS | UDP_EPTYPE_CTRL); // 엔드포인트 타입을 컨트롤 엔드포인트(endpoint 0)로 설정한다.

			UDP_ICR = UDP_RXRSM | UDP_WAKEUP | UDP_RXSUSP;	
			UDP_ICR = UDP_ENDBUSRES;

			UDP_IER |= ( UDP_EPINT0 | UDP_EPINT1 | UDP_EPINT2 | UDP_EPINT3);
			#ifdef _USB_DEBUG_
			printf( "ENDBUSRE\n" );
			#endif
			continue;
		}

		if( udp_state & UDP_EPINT0)
		{
			// EP0 인터럽트 
			#ifdef _USB_DEBUG_
			printf( "EP0 ENTER\n" );
			#endif
		
			if(      UDP_CSR0 & UDP_TXCOMP      ) { usbcom_cdc_transfer();  } // 호스트쪽으로  전송 처리
			else if( UDP_CSR0 & UDP_RXSETUP     ) { usbcom_cdc_enumerate(); } // 수신된 셋업 패킷 처리 
			else if( UDP_CSR0 & UDP_RX_DATA_BK0 ) // DATA0 패킷 수신
			{ 
			UDP_CSR0 &= ~(UDP_RX_DATA_BK0);
			}
			#ifdef _USB_DEBUG_ 
			else
			{
				printf( "WHAT %08X\n", UDP_CSR0 );
			}
			#endif
		
			UDP_ICR = UDP_EPINT0;	
		}

		if( udp_state & UDP_EPINT1 )
		{// EP1 인터럽트
			UDP_ICR = UDP_EPINT1;	
			#ifdef _USB_DEBUG_
			printf( "CALL EP1 INT UDP_CSR1 : %08X\n", UDP_CSR1 );
			#endif

			// 현재의 데이터는 전부다 FIFO에 들어가 있는 상태 이다 ..
			// 그렇기 때문에 어떤 FIFO인지만 확인해서 read함수를 쓰면 된다. 내 생각
			usbcom_udp_read( (u8 *)&data[0], message_size );

//			if ( UDP_CSR1 & UDP_RX_DATA_BK0 )
//			{
//				// 현재의 수신 뱅크를 지정 한다.
//				usb_serial.currentRcvBank = UDP_RX_DATA_BK0;
//			}
//			else if ( UDP_CSR1 & UDP_RX_DATA_BK1  )
//			{
//				// 현재의 수신 뱅크를 지정 한다.
//				usb_serial.currentRcvBank = UDP_RX_DATA_BK1;
//			}

		}

		if( udp_state & UDP_EPINT2)
		{// EP2 인터럽트

			led_on( LED_DS3 );			

			if( UDP_CSR2 & UDP_TXCOMP ) 
			{ 
				UDP_CSR2 &= ~(UDP_TXCOMP);
				while (UDP_CSR2 & UDP_TXCOMP);
			}

			usb_tx_ing_flag = 0;

			UDP_ICR = UDP_EPINT2;	
			#ifdef _USB_DEBUG_
			//printf("CALL EP2 INT\n" );
			#endif
		}
		
		if( udp_state & UDP_EPINT3)
		{// EP3 인터럽트
			UDP_ICR = UDP_EPINT3;
			#ifdef _USB_DEBUG_
			printf( "CALL EP3 INT\n" );
			#endif
		}
		#ifdef _USB_DEBUG_
//		printf( "]" );	
		#endif
	
		return;
	}
}

//------------------------------------------------------------------------------
// 설명 : USB 초기 설정 처리를 위한 구조체 초기화 
//------------------------------------------------------------------------------
void usbcom_cdc_configure_init( void )
{
	usb_serial.currentConfiguration	= 0;
	usb_serial.currentRcvBank		= UDP_RX_DATA_BK0;
}


//------------------------------------------------------------------------------
// 설명 : 콘솔 장치로 한문자를 전송한다.
// 매계 : c : 전송할 문자 
//------------------------------------------------------------------------------
RAMFUNC void usb_putc( const u8 c )
{
//	s32 lp;
	u32 irq_old_state;

	while( usb_tx_fifo_cnt >= USB_TX_FIFO_MAX );	// FIFO  데이터가 소모될때까지 대기 한다. 

	irq_old_state = irq_disable();
	usb_tx_fifo[usb_tx_fifo_cnt] = c;
	usb_tx_fifo_cnt++;
	irq_restore( irq_old_state );

}

//------------------------------------------------------------------------------
// 설명 : 수신된 문자가 있는가를 확인한다.
// 반환 : 0 : 수신된 문자가 없다. 
//		  0   이 아니면 수신된 문자가 있다
//------------------------------------------------------------------------------
RAMFUNC u32 usb_read_ok( void )
{
	s32 state;
	u32 irq_old_state;
	
	irq_old_state = irq_disable();
	state = usb_rx_head == usb_rx_tail;
	irq_restore( irq_old_state );
	
	if( !(state) ) return 1;
	return 0;
}

//------------------------------------------------------------------------------
// 설명 : 수신된 문자를 얻는다. 
// 반환 : 수신된 문자
//------------------------------------------------------------------------------
u8  usb_getc( void )
{
	u8 ret_c;
	u32 irq_old_state;
	
	irq_old_state = irq_disable();
	ret_c = usb_rx_data[usb_rx_tail]; 
	usb_rx_tail++;
	usb_rx_tail &= RX_QUEUE_MASK;

	irq_restore( irq_old_state );
	
	return ret_c;
}

//------------------------------------------------------------------------------
// 설명 : USB 주기적 호출 함수 
//------------------------------------------------------------------------------
void usb_callback( void )
{
	u32 tx_cnt;
	u32 lp,idx;
	
	if( UDP_CSR2 & UDP_TXPKTRDY ) return;
	if( !usb_tx_fifo_cnt        ) return;
		
	tx_cnt = usb_tx_fifo_cnt;	
	
	for( lp = 0; lp < USB_TX_FIFO_MAX; lp++ )
	{
		if( UDP_CSR2 & UDP_TXPKTRDY ) break;
		if( usb_tx_fifo_cnt <= lp   ) break;
		UDP_FDR2 = usb_tx_fifo[lp];
		tx_cnt--;
	}
	
	idx = 0;
	for( ; lp < usb_tx_fifo_cnt; lp++ )
	{
		usb_tx_fifo[idx] = usb_tx_fifo[lp];
		idx++;
	}
	
	usb_tx_fifo_cnt = tx_cnt;
	
	UDP_CSR2 |= UDP_TXPKTRDY;
	
}

//------------------------------------------------------------------------------
// 설명 : USB 장치 초기화 
//------------------------------------------------------------------------------
void usbcom_init(void)
{
	#ifdef _USB_DEBUG_
	printf("\n Init USB Device start\n");
	#endif
	
//	usb_rx_count 	= 0;
	usb_rx_head 	= 0;
	usb_rx_tail 	= 0;
	
	usb_tx_fifo_cnt = 0;
	usb_tx_ing_flag = 0;
	
	usb_port_connect();  			// USB 가 연결된것처럼 만든다.
	usbcom_cdc_configure_init(); 	// USB 초기 설정 처리를 위한 구조체 초기화 
	
	UDP_IER = ( UDP_EPINT0 | UDP_EPINT1 | UDP_EPINT2 | UDP_EPINT3);
	UDP_IDR = ( UDP_RXSUSP | UDP_RXRSM  | UDP_SOFINT );
	UDP_ICR = UDP_RXRSM;

	#ifdef _USB_DEBUG_
	printf( "UDP_IMR = %08X\n", UDP_IMR );
	#endif
	
	irq_request( ID_UDP, AIC_SRCTYPE_INT_HIGH_LEVEL, usb_irq_handler ); // 인터럽트 핸들러 등록
	irq_active ( ID_UDP ); // USB 인터럽트 허가
	
	timer_set_usb_callback( usb_callback );

}

//------------------------------------------------------------------------------
// 설명 : USB SERIAL COMPORT를 셋팅한다. 
//------------------------------------------------------------------------------
void usb_console_init( u32 baudrate )
{

	s_comportsetting.dw_dter_rate 	= 115200;
	
	s_comportsetting.dw_dter_rate 	= baudrate;
	s_comportsetting.b_char_format 	= 0;
	s_comportsetting.b_parity_type 	= 0;
	s_comportsetting.b_data_bits	= 8;
}
