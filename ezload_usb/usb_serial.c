//------------------------------------------------------------------------------
// �� �� �� : usb_serial.c
// ������Ʈ : ez-jtag
// ��    �� : USB �� �ٷ�� ��ƾ 
// �� �� �� : ����â(frog@falinux.com), �̴���(elenyuri@empal.com)
// �� �� �� : 2007�� 6�� 10��
// �� �� �� :
// �� �� �� :
// ��    �� :
// ���̼��� : BSD
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
// _USB_DEBUG_ �ɼ��� Ȱ��ȭ �Ϸ��� �ݵ�� ������ġ�� �ø��� �ɼ� �� Ȱ��ȭ ��ų�� !!!
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
// ���� : USB PORT �� HOST �� ����ǵ��� �����. 
//------------------------------------------------------------------------------
void usb_port_connect( void )
{
	#ifdef _USB_DEBUG_
	printf("usb port connect\n");
	#endif
	
	// USB ����̽��� Ȱ��ȭ ��Ų��. 
	CKGR_PLLR |= CKGR_USBDIV_1 ;   // Set the PLL USB Divider
	PMC_SCER = PMC_UDP;            // Enables the 48MHz USB clock UDPCK and System Peripheral USB Clock
	PMC_PCER = (1 << ID_UDP);

	// Ǯ�� ���� �����Ͽ� HOST���� ��Ʈ�� ����Ǿ����� �˸���.
	PMC_PCER = (1 << ID_PIOA); 

	#ifdef _EVBOARD_MODE_	
	PIO_PER  = PIO_PA16;          // Set in PIO mode
	PIO_OER  = PIO_PA16;          // Configure in Output
	PIO_CODR = PIO_PA16;
	#endif	
}


//----------------------------------------------------------------------------
// ���� Stall �� �����Ѵ�. 
//----------------------------------------------------------------------------
static void  usbcom_usb_send_stall(void)
{
	UDP_CSR0 |= UDP_FORCESTALL;
	while ( !(UDP_CSR0 & UDP_ISOERROR) );

	UDP_CSR0 &= ~(UDP_FORCESTALL | UDP_ISOERROR);
	while (UDP_CSR0 & (UDP_FORCESTALL | UDP_ISOERROR));
}

//----------------------------------------------------------------------------
// ���� : �� ��Ŷ�� �����Ѵ�.
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
// ���� : ���� ���� ���¸� �����Ѵ�. 
//----------------------------------------------------------------------------
static void usbcom_cdc_set_control_line_state( u16 wValue)
{
//	usb_serial.currentConnection = wValue;
	usbcom_usb_send_zero_len_packet();
	
	// �о���� ���� �־�� �Ѵ�.
	
	
	#ifdef _USB_DEBUG_
	printf("SET_CONTROL_LINE_STATE : send zero length pack.(wValue=%08x)\n", wValue);
	#endif
}

//----------------------------------------------------------------------------
// ���� : LINE ���¸� �����Ѵ�. 
//----------------------------------------------------------------------------
static void usbcom_cdc_get_line_coding(u16 wLength)
{
	usbcom_usb_send_data( (char *) &s_comportsetting, min(sizeof(s_comportsetting), wLength) );

	#ifdef _USB_DEBUG_
	printf("GET_LINE_CODING : send data.(wLength=%08x)\n", wLength);
	#endif
}

//----------------------------------------------------------------------------
// ���� : LINE ���¸� �����ϱ⸦ �䱸 �޾� ó���Ѵ�. 
//----------------------------------------------------------------------------
static void usbcom_cdc_set_line_coding( u16 wLength )
{
	u8 	*c;
	u32	i;
	
	#ifdef _USB_DEBUG_
	printf( "SIZE = %d:%d\n", wLength, sizeof( s_comportsetting ) );
	#endif                               

	// endpoint0�� ���ö����� ��� 
	while ( !(UDP_CSR0 & UDP_RX_DATA_BK0) );
	
	// FIFO �����͸� �о� �´�. 
	c = (u8	*) &s_comportsetting;
	for ( i=0 ; i<wLength ; i++ ) c[i] = UDP_FDR0;

	// �ܼ� �� ���� 
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
                                         
	// endpoint0�� ���°��� ǥ���ϴ� UDP_CSR0�� ǥ�� �����
	UDP_CSR0 &= ~(UDP_RX_DATA_BK0);
	usbcom_usb_send_zero_len_packet();

	#ifdef _USB_DEBUG_
	printf("SET_LINE_CODING : send zero length pack.\n");
	#endif

}

//----------------------------------------------------------------------------
// ���� : feature endpoint �� Ŭ���� �Ѵ�. 
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
// ���� : feature interface �� Ŭ���� �Ѵ�. 
//----------------------------------------------------------------------------
static void usbcom_cdc_clear_feature_interface(void)
{
	usbcom_usb_send_zero_len_packet();
	#ifdef _USB_DEBUG_
	printf("STD_CLEAR_FEATURE_INTERFACE : send zero length pack.\n");
	#endif
}



//----------------------------------------------------------------------------
// ���� : feature zero �� Ŭ���� �Ѵ�. 
//----------------------------------------------------------------------------
static void usbcom_cdc_clear_feature_zero(void)
{
	usbcom_usb_send_stall();
	#ifdef _USB_DEBUG_
	printf("STD_CLEAR_FEATURE_ZERO : send all.\n");
	#endif
}			
	
//----------------------------------------------------------------------------
// ���� : endpoint ���¿� ���� �������͸� �����Ѵ�. 
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
// ���� : endpoint status �� �����Ѵ�. 
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
// ���� : status interface �� �����Ѵ�. 
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
// ���� : status zero �� �����Ѵ�. 
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
// ���� : configureationn�� �����Ѵ�. 
//----------------------------------------------------------------------------
static void usbcom_cdc_get_configuration( void )
{
	usbcom_usb_send_data( (char *) &(usb_serial.currentConfiguration), sizeof(usb_serial.currentConfiguration) );
	#ifdef _USB_DEBUG_
	printf("STD_GET_CONFIGURATION >> usb_serial.currentConfiguration[%d]\n", usb_serial.currentConfiguration);	
	#endif
}



//------------------------------------------------------------------------------
// ���� : ��ũ���͸� �����Ѵ�. 
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
// ���� : ��巹���� ���� �غ� �Ѵ�. 
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
// ���� : ��巹���� ���� �غ� �Ѵ�. 
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
// ���� : USB ����̽��� ȣ��Ʈ�� ���ŵǱ� ���� ó�� 
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

	// ǥ�� ����̽� ������Ʈ�� ���� ��鷯 ó�� ��ƾ ( USB ���� ���̺� 9-3 )
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

	// ������ ���� ��ũ�� �о� �´� .
	cur_recv_bank = usb_serial.currentRcvBank;

	// ���⼭�� length�� ��Ŷ�� ũ�� �����μ� 64����Ʈ�� �ּ� ��Ŷ ���� �̴�.. 
	packet_size = min( UDP_CSR1 >> 16, 64 );
	while(packet_size)
	{
		usb_rx_data[usb_rx_head] = UDP_FDR1; 
		usb_rx_head++;
		usb_rx_head &= RX_QUEUE_MASK;
		packet_size--;
	}
	
	// ������ ����� ���� ��ũ�� �ʱ�ȭ ��Ų��.
	UDP_CSR1 &= ~(cur_recv_bank);

	// ���� ������� ��ũ�� � ������ Ȯ���ϰ� 
	// �ٸ� ��ũ�� ����ϵ��� �Ѵ�.
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


static u8   up0_send_data[1024];       // EP0 �۽� ������ ���� 
static u8  *up0_send_ptr = NULL;       // �۽� ��ġ ������
static s32  up0_send_data_length = 0;  // ���� �۽� ������ ũ�� 

//----------------------------------------------------------------------------
// ���� : ��Ʈ�� ��������Ʈ�� ���� �����͸� �����Ѵ�.
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
// ���� : cdc�� ���� ȣ��Ʈ������ �����͸� �����Ѵ�.
//------------------------------------------------------------------------------
void usbcom_cdc_transfer( void )
{
	u32 packet_length;
	
	if( up0_send_ptr )
	{	
		
		if( up0_send_data_length )// ������ �����Ͱ� �ִ� ��� 
		{
			
			packet_length = min(up0_send_data_length, 8);
			up0_send_data_length -= packet_length;
			
			while (packet_length--)	UDP_FDR0 = *up0_send_ptr++;
			
			UDP_CSR0 |= UDP_TXPKTRDY;
			
		}
		else	// ������ �����Ͱ� ���� ��� 
		{
			up0_send_ptr = NULL;
		}
	}
		
	// �۽��� �������� �˸��� ���ͷ�Ʈ ���� �ö�׸� �����. 
	if (UDP_CSR0 & UDP_TXCOMP) 
	{
		UDP_CSR0 &= ~(UDP_TXCOMP);
		while (UDP_CSR0 & UDP_TXCOMP);
	}
}


//------------------------------------------------------------------------------
// ���� : USB ���ͷ�Ʈ �ڵ鷯 
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

		if( udp_state & UDP_RXSUSP) // SUSPEND �����ϴ�.
		{
			UDP_ICR = UDP_RXSUSP;	
			#ifdef _USB_DEBUG_
			printf( "UDP_RXSUSP\n" );
			#endif
			continue;
		}	

		if( (udp_state & UDP_RXRSM) || (udp_state & UDP_WAKEUP) ) // RESUME �ٽ� �����ϴ�.
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
		
			UDP_RSTEP = (u32)-1; // ��� ��������Ʈ�� ����
			UDP_RSTEP = 0;
			
			UDP_FADDR     = UDP_FEN; // ����� �ο��̺��Ѵ�.
			UDP_GLBSTATE  = 0;
    	
			UDP_CSR0 = (UDP_EPEDS | UDP_EPTYPE_CTRL); // ��������Ʈ Ÿ���� ��Ʈ�� ��������Ʈ(endpoint 0)�� �����Ѵ�.

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
			// EP0 ���ͷ�Ʈ 
			#ifdef _USB_DEBUG_
			printf( "EP0 ENTER\n" );
			#endif
		
			if(      UDP_CSR0 & UDP_TXCOMP      ) { usbcom_cdc_transfer();  } // ȣ��Ʈ������  ���� ó��
			else if( UDP_CSR0 & UDP_RXSETUP     ) { usbcom_cdc_enumerate(); } // ���ŵ� �¾� ��Ŷ ó�� 
			else if( UDP_CSR0 & UDP_RX_DATA_BK0 ) // DATA0 ��Ŷ ����
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
		{// EP1 ���ͷ�Ʈ
			UDP_ICR = UDP_EPINT1;	
			#ifdef _USB_DEBUG_
			printf( "CALL EP1 INT UDP_CSR1 : %08X\n", UDP_CSR1 );
			#endif

			// ������ �����ʹ� ���δ� FIFO�� �� �ִ� ���� �̴� ..
			// �׷��� ������ � FIFO������ Ȯ���ؼ� read�Լ��� ���� �ȴ�. �� ����
			usbcom_udp_read( (u8 *)&data[0], message_size );

//			if ( UDP_CSR1 & UDP_RX_DATA_BK0 )
//			{
//				// ������ ���� ��ũ�� ���� �Ѵ�.
//				usb_serial.currentRcvBank = UDP_RX_DATA_BK0;
//			}
//			else if ( UDP_CSR1 & UDP_RX_DATA_BK1  )
//			{
//				// ������ ���� ��ũ�� ���� �Ѵ�.
//				usb_serial.currentRcvBank = UDP_RX_DATA_BK1;
//			}

		}

		if( udp_state & UDP_EPINT2)
		{// EP2 ���ͷ�Ʈ

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
		{// EP3 ���ͷ�Ʈ
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
// ���� : USB �ʱ� ���� ó���� ���� ����ü �ʱ�ȭ 
//------------------------------------------------------------------------------
void usbcom_cdc_configure_init( void )
{
	usb_serial.currentConfiguration	= 0;
	usb_serial.currentRcvBank		= UDP_RX_DATA_BK0;
}


//------------------------------------------------------------------------------
// ���� : �ܼ� ��ġ�� �ѹ��ڸ� �����Ѵ�.
// �Ű� : c : ������ ���� 
//------------------------------------------------------------------------------
RAMFUNC void usb_putc( const u8 c )
{
//	s32 lp;
	u32 irq_old_state;

	while( usb_tx_fifo_cnt >= USB_TX_FIFO_MAX );	// FIFO  �����Ͱ� �Ҹ�ɶ����� ��� �Ѵ�. 

	irq_old_state = irq_disable();
	usb_tx_fifo[usb_tx_fifo_cnt] = c;
	usb_tx_fifo_cnt++;
	irq_restore( irq_old_state );

}

//------------------------------------------------------------------------------
// ���� : ���ŵ� ���ڰ� �ִ°��� Ȯ���Ѵ�.
// ��ȯ : 0 : ���ŵ� ���ڰ� ����. 
//		  0   �� �ƴϸ� ���ŵ� ���ڰ� �ִ�
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
// ���� : ���ŵ� ���ڸ� ��´�. 
// ��ȯ : ���ŵ� ����
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
// ���� : USB �ֱ��� ȣ�� �Լ� 
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
// ���� : USB ��ġ �ʱ�ȭ 
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
	
	usb_port_connect();  			// USB �� ����Ȱ�ó�� �����.
	usbcom_cdc_configure_init(); 	// USB �ʱ� ���� ó���� ���� ����ü �ʱ�ȭ 
	
	UDP_IER = ( UDP_EPINT0 | UDP_EPINT1 | UDP_EPINT2 | UDP_EPINT3);
	UDP_IDR = ( UDP_RXSUSP | UDP_RXRSM  | UDP_SOFINT );
	UDP_ICR = UDP_RXRSM;

	#ifdef _USB_DEBUG_
	printf( "UDP_IMR = %08X\n", UDP_IMR );
	#endif
	
	irq_request( ID_UDP, AIC_SRCTYPE_INT_HIGH_LEVEL, usb_irq_handler ); // ���ͷ�Ʈ �ڵ鷯 ���
	irq_active ( ID_UDP ); // USB ���ͷ�Ʈ �㰡
	
	timer_set_usb_callback( usb_callback );

}

//------------------------------------------------------------------------------
// ���� : USB SERIAL COMPORT�� �����Ѵ�. 
//------------------------------------------------------------------------------
void usb_console_init( u32 baudrate )
{

	s_comportsetting.dw_dter_rate 	= 115200;
	
	s_comportsetting.dw_dter_rate 	= baudrate;
	s_comportsetting.b_char_format 	= 0;
	s_comportsetting.b_parity_type 	= 0;
	s_comportsetting.b_data_bits	= 8;
}
