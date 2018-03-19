//------------------------------------------------------------------------------
// �� �� �� : main.h
// ������Ʈ : ez-jtag
// ��    �� : ���� ��ƾ
// �� �� �� : ����â(frog@falinux.com)
// �� �� �� : 2007�� 5�� 6��
// �� �� �� : 2008�� 9�� ������  Ÿ�̸� ���� �Լ��߰�
//            2010�� 3�� �׽�ũ ���� Ÿ�̸� ����
//                       �÷��� Ư������ ���� �Լ� �߰�   
// �� �� �� :
// ��    �� :
// ���̼��� : BSD
//------------------------------------------------------------------------------

#include <typedef.h>
#include <register.h>
#include <setup.h>

#include <irq.h>
#include <console.h>
#include <stdio.h>
#include <string.h>

#include <timer.h>
#include <xmodem.h>
#include <flash.h>
#include <mem_edit.h>
#include <main.h>

#include <module.h>
#include <usb_serial.h>

#include <crc16.h>

#define  VERSION_STRING         "1.62.1"
#define  WORK_AREASIZE          ( 32 * 1024 )

void *work_area = NULL;

s32 select_mode; 		//0�̸� EZ-load, 1�̸� EZ-module
usb_consol_mode_t	usb_serial_mode;



//------------------------------------------------------------------------------
// ���� : LED �� ���� ��Ų��.
//------------------------------------------------------------------------------
void reset( s32 argc, s8 **argv )
{
	//void (*func)(void) = 0x000000;
	//func();
	printf( "not implement\n" );
}

//------------------------------------------------------------------------------
// ���� : LED �� ���� ��Ų��.
//------------------------------------------------------------------------------
void leds_init( void )
{
	//	LED �ʱ�ȭ
	PIO_PER  = (LED_DS1);
	PIO_OER  = (LED_DS1);
	PIO_SODR = (LED_DS1);
}

void led_on( u32 led_value )
{
	PIO_CODR = led_value;
}

void led_off( u32 led_value )
{
	PIO_SODR = led_value;
}

void led_flash( void )
{
	u32 lp;

	led_on (LED_DS1); for( lp = 0; lp < 0x80000; lp++ ) ;
	led_off(LED_DS1); for( lp = 0; lp < 0x80000; lp++ ) ;
	led_on (LED_DS1); for( lp = 0; lp < 0x80000; lp++ ) ;
	led_off(LED_DS1); for( lp = 0; lp < 0x80000; lp++ ) ;

}

//------------------------------------------------------------------------------
// ���� : ���ɹ��ڸ� �� ��ū���� �и��Ͽ� ��ȯ�Ѵ�.
// �Ű� : cmdline : ���ɶ���
//        argv    : �и��� ��ū ���ڿ� �ּҰ� ������ �迭
// ��ȯ : ��ū��
// ���� :
//------------------------------------------------------------------------------
static const char *delim = " \f\n\r\t\v";
static s32 parse_args(s8 *cmdline, s8 **argv)
{
	s8 *tok;
	s32 argc = 0;

	argv[argc] = NULL;

	for (tok = (s8 *)strtok(cmdline, delim); tok; tok = (s8 *)strtok(NULL, delim))
	{
		argv[argc++] = tok;
	}

	return argc;
}

//------------------------------------------------------------------------------
// ���� : ������ ǥ��
//------------------------------------------------------------------------------
s32 help(s32 argc, s8 **argv )
{
	printf( "MRB 		: Memory read byte\n" );
	printf( "MRW 		: Memory read word\n" );
	printf( "MRL 		: Memory read long\n" );
	printf( "TST 		: Call the Test function \n" );
	printf( "XFM 		: Flash write to module by xmodem\n" );   
	printf( "GM  		: Jump module\n" );
	printf( "MODEL 		: return protocol model information\n" );
	printf( "BW  		: protocol buff write\n" );
	printf( "PROGRAM 	: protocol write page\n" );

	return 0;
}

//------------------------------------------------------------------------------
// ���� : XMODEM ���������� �̿��Ͽ� �ٿ��ε� ���� ���� ���α׷���
//        �÷����� ����Ʈ �Ѵ�. 
// ���� : ������ �ٿ� ��ġ�� 0x00110000���� �����Ѵ�.
//------------------------------------------------------------------------------
s32 xmodem_flash_write_module(s32 argc, s8 **argv )
{
	s32 rx_size;

	// XMODEM ����Ÿ ����
	rx_size = xmodem_receive( (u8 *) work_area, WORK_AREASIZE );
	if( rx_size < 0 )
	{
		printf( "xmodem receive error!\n" );
		return -1;
	}

	printf( "xmodem receive ok\n" );
	printf( "address = %p\n", work_area );
	printf( "size    = %d\n", rx_size );

	// �÷��� ����Ʈ ��ƾ ȣ��
	flash_write_all(0x110000, rx_size, (u32 *)work_area);

	return 0;
}
//------------------------------------------------------------------------------
// ���� : XMODEM ���������� �̿��Ͽ� �ٿ��ε� ���� ����Ÿ��
//        �÷����� ����Ʈ �Ѵ�. 
// ���� : 
//------------------------------------------------------------------------------
s32 xmodem_flash_write(s32 argc, s8 **argv )
{
	s32 rx_size, dest_area;

	if ( argc < 2 )
	{
		printf( " XF [addr]\n" );
		return 0;	
	}
	dest_area = strtoul( argv[1], NULL, 0 );

	// XMODEM ����Ÿ ����
	rx_size = xmodem_receive( (u8 *) work_area, WORK_AREASIZE );
	if( rx_size < 0 )
	{
		printf( "xmodem receive error!\n" );
		return -1;
	}

	printf( "xmodem receive ok\n" );
	printf( "src-mem   = %p\n", work_area );
	printf( "dst-flash = %p\n", dest_area );
	printf( "size     = %d\n", rx_size );

	// �÷��� ����Ʈ ��ƾ ȣ��
	flash_write_all( dest_area, rx_size, (u32 *)work_area);

	return 0;
}

static void crc16_printf( char *send_str )
{
	unsigned short crc16;
	
	crc16 = crc16_ccitt( send_str, strlen(send_str) );
	printf( "<%04x>%s\n", crc16, send_str );
}

s32 mem_dump(s32 argc, s8 **argv )
{
	u32  addr, size, ofs;
	char str[64];

	if ( 3 > argc ) {
		printf( " mdump <addr> <size>\n");
		return 0;
	}

	addr = strtoul( argv[1], 0, 0 );
	size = strtoul( argv[2], 0, 0 );
	
	irq_disable();

	for ( ofs = 0; ofs<size; ofs+=16, addr+=16 ) {
		u32 *p = (u32 *)addr;
		sprintf( str,"@%04x %08x %08x %08x %08x", ofs, p[0], p[1], p[2], p[3] );	
		crc16_printf( str );

		udelay(6000);
	}

	crc16_printf( "@end" );

	irq_enable();

	return 0;
}

//------------------------------------------------------------------------------
// ���� : ���� �Լ� 
//------------------------------------------------------------------------------
s32 test(s32 argc, s8 **argv )
{
	return 0;
}

//------------------------------------------------------------------------------
// ���� : LED ����� ���� ���� ���¸� ���� �Լ�  
// �Ű� : ���� 
// ��ȯ : 0�̸� EZ-load, 1�̸� EZ-module
// ���� : ���� 
//------------------------------------------------------------------------------
s32 get_mode(void)
{
	return select_mode;
}

//------------------------------------------------------------------------------
// ���� : LED ����� ���� ���� ���¸� �����ϴ� �Լ�  
// �Ű� : ������ ���� ���� 
// ��ȯ : ������ ���� ����: 0�̸� EZ-load, 1�̸� EZ-module
// ���� : ���� 
//------------------------------------------------------------------------------
s32 set_mode(s32 ez_mode)
{
	select_mode = ez_mode;
	return select_mode;
}

//------------------------------------------------------------------------------
// ���� : �Լ� ������ ���� ����ü�� �ʱ�ȭ �Ѵ�. 
//------------------------------------------------------------------------------
void init_module( void *call_head  )
{
	call_t *pcall;
	
	pcall = (call_t *) call_head;


	if ( !usb_serial_mode.printf_select_usb )
	{
		// console.h ==> 2007. 08. 18 dhLee
		pcall->_console_putc    = console_putc;
		pcall->_console_read_ok = console_read_ok;
		pcall->_console_getc    = console_getc;
		pcall->_console_puts    = console_puts; // fg
	}
	else
	{
		// usb_serial.h
		pcall->_console_putc    = usb_putc;
		pcall->_console_read_ok = usb_read_ok;
		pcall->_console_getc    = usb_getc;
	}
	// irq.h		
	pcall->_irq_enable    = irq_enable   ; 
	pcall->_irq_disable   = irq_disable  ; 
	pcall->_irq_restore   = irq_restore  ; 
	pcall->_irq_active    = irq_active   ; 
	pcall->_irq_deactive  = irq_deactive ; 
	pcall->_irq_clear     = irq_clear    ; 
	pcall->_irq_request   = irq_request  ; 
	pcall->_irq_free      = irq_free	 ; 

	// stdio.h	
	pcall->_vsprintf   = vsprintf ;
	pcall->_sprintf    = sprintf  ;
	pcall->_putc       = putc     ;
	pcall->_printf     = printf   ;
	pcall->_getc       = getc     ;
	pcall->_gets       = gets     ;
	pcall->_vsscanf    = vsscanf  ;
	pcall->_sscanf     = sscanf   ;

	// string.h
	pcall->_strpbrk    = strpbrk  ;
	pcall->_strtok     = strtok   ;
	pcall->_strsep     = strsep   ;
	pcall->_strspn     = strspn   ;
	pcall->_strcpy     = strcpy   ;
	pcall->_strncpy    = strncpy  ;
	pcall->_strcat     = strcat   ;
	pcall->_strncat    = strncat  ;
	pcall->_strcmp     = strcmp   ;
	pcall->_strncmp    = strncmp  ;
	pcall->_strnicmp   = strnicmp ;
	pcall->_strchr     = strchr   ;
	pcall->_strrchr    = strrchr  ;
	pcall->_strstr     = strstr   ;
	pcall->_strlen     = strlen   ;
	pcall->_strnlen    = strnlen  ;
	pcall->_memset     = memset   ;
	pcall->_memcpy     = memcpy   ;
	pcall->_memmove    = memmove  ;
	pcall->_memscan    = memscan  ;
	pcall->_memcmp     = memcmp   ;
	pcall->_memchr     = memchr   ;
	pcall->_strtoul    = strtoul  ;
	pcall->_upper_str  = upper_str;
	pcall->_lower_str  = lower_str;
	
	
	pcall->_timer_msec         = timer_msec        ;
	pcall->_timer_sec          = timer_sec         ;
	pcall->_timer_random       = timer_random      ;
	pcall->_timer_set_timeover = timer_set_timeover;
	pcall->_timer_is_timeover  = timer_is_timeover ;
	pcall->_mdelay             = mdelay            ;
	pcall->_udelay             = udelay            ;
	pcall->_timer_set_task     = timer_set_task    ;
	pcall->_timer_del_task     = timer_del_task    ;
	
	pcall->_flash_write_all    = flash_write_all   ;
	
//	printf( "Init_MODULE CALL\n" );

	set_mode(1);		//EZ-module Mode
	
}
//------------------------------------------------------------------------------
// ���� : 
//------------------------------------------------------------------------------
s32 get_module_func(s32 argc, s8 **argv )
{
	s8		*pfunc 	= (s8 *)0x10030;
	u32		*pmagic = (u32*)0x10010;
	s8      strbuff[64];
	
	
	
	if(*pmagic==0x2078)
	{	
		memcpy( strbuff, pfunc, sizeof( strbuff ) );
		strbuff[sizeof( strbuff )-1] = 0;
		printf("%FUNC %s\n", strbuff );	
	}
	else
	{	
		printf("%FUNC UNKONW\n");	
	}
	
	return 0;
}
//------------------------------------------------------------------------------
// ���� : ������ ǥ��
//------------------------------------------------------------------------------
s32 go_module(s32 argc, s8 **argv )
{
	void (*module_main)( void (*init_module)( void *call_head ) );
	
//	printf( "GO MODULE\n" );
	module_main = (void (*)( void (*)( void * ) ) ) 0x00010000;
	
//ez-module���� ���������� �����Ѵ�.

	__asm__ (" ldr r0, =_restore_point ");
	_boot_load_store();
	module_main( init_module );
	__asm__ (" _restore_point:");			//������ ��ġ�Դϴ�.
	return 0;
}

//------------------------------------------------------------------------------
// �������� ���� �Լ��� 
// ���� : �Լ����� "protocol_"�� �����Ѵ�.
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// ���� : �𵨿� ���� ������ ��ȯ�Ѵ�.
//------------------------------------------------------------------------------
s32 protocol_model(s32 argc, s8 **argv )
{
	printf("%MODEL EZLOAD V0100\n");
	return 0;
}

//------------------------------------------------------------------------------
// ���� : ���ۿ� �����͸� �ִ´�.
//------------------------------------------------------------------------------
s32 protocol_buff_write(s32 argc, s8 **argv )
{
	u32 	cnt;
	u32 	size;
	u32 	address;
	s8 	   *pt;
	s8	    c;
	u8     *buff;
	
	buff = (u8 *) work_area; 

	if( argc != 4 )
	{
		printf( "BW [Address] [Count]\n");
        return -1;
	}
	
	size 		= (u32)strtoul( argv[2], NULL, 0);
    address 	= (u32)strtoul( argv[1], NULL, 0);
    pt          = argv[3];
	
	for(cnt=0;cnt<size;cnt++)
	{
		if ( (address+cnt) >= WORK_AREASIZE ) break;	// @@CS
		//if ( (address+cnt) < 0 ) break;	// @@CS
		
		//high
		c=*(pt++);
		if ((c >= '0') && (c <= '9')) 	{	buff[address+cnt] = ((c-'0') 		<<4); 	}
		else 							{	buff[address+cnt] = ((c-'A'+10) 	<<4); 	}

		//low
		c=*(pt++);
		if ((c >= '0') && (c <= '9')) 	{	buff[address+cnt] += (c-'0');				}
		else 							{	buff[address+cnt] += (c-'A'+10);			}

//		printf(" %x ",work_area[address+cnt]);
	}
	printf("%BR 0\n");					//���� �������� ����. ���� ���� �� ����
	printf("\n");
	return 0;
}

//------------------------------------------------------------------------------
// ���� : 
//------------------------------------------------------------------------------
s32 protocol_write_page(s32 argc, s8 **argv )
{
	u32 	address=0;
	
	if( argc >2 || argc==1)
	{
		printf( "PROGRAM [Address]\n");
        return -1;
	}
	
	address = (u32)strtoul( argv[1], NULL, 0);
	
	if( flash_page_write(0x110000 + address, 256, (u32 *)work_area) ) 
		{ printf( "%PROGRAM FAIL\n" ); }	//�������� �ǹ� ����.
	else									 
		{ printf( "%PROGRAM OK\n"   ); } 	//�׻� OK.

	return 0;
}

static void delay_msec( int delay )               
{
	int lp = delay*5000; 
	
	while(lp--) { asm( "nop" ); } 
}

//------------------------------------------------------------------------------
// ���� : ���� ��ƾ
//------------------------------------------------------------------------------
int main(void)
{
	s8  	read_line[1024];
	s32   	argc;
	s8 	*argv[16];
	s8    work[WORK_AREASIZE];

	work_area = work;	// 32K ����Ʈ �۾����� Ȯ��

	leds_init();
	irq_init();			// IRQ ���ͷ�Ʈ ó�� �ʱ�ȭ
	timer_init();

	PMC_PCER = (1 << ID_PIOA);

	led_flash();
	set_mode(0);		//EZ-load Mode
	led_on(LED_DS1);
	
	//  DEBUG_CONSOLE �� �����Ǿ� ���� ������ USB �� �ַܼ� �����Ѵ�. 
	//if( PIO_PDSR & CONSOLE_SELECT_DEBUG_PIN ) usb_serial_mode.printf_select_usb = 1;
	//else                                      usb_serial_mode.printf_select_usb = 0;
    //
	//if ( PIO_PDSR & USB_TO_SERIAL_BRIDGE_PIN ) 	usb_serial_mode.usbtoserial_bridge = 0;
	//else										usb_serial_mode.usbtoserial_bridge = 1;
	usb_serial_mode.printf_select_usb  = 0;
	usb_serial_mode.usbtoserial_bridge = 0;
	
	// �����׿��� printf �� �ַܼ� ���µǴ°�?	
	if( !usb_serial_mode.printf_select_usb ) 
	{
		console_init( 115200 );	
		usbcom_init();
	}
	else
	{
		// �������� USB �ø��� ó�� ����
		if( !usb_serial_mode.usbtoserial_bridge )
		{
			usb_console_init( 115200 );
			usbcom_init();
		}	
		// USB �� �ø��� ���� ����( usb serial �긮�� ����)
		else
		{
			led_on(LED_DS3);
			console_init( 115200 );	
			usb_console_init( 115200 );
			usbcom_init();
			while( 1 )
			{
				if( console_read_ok() ) 
				{
					usb_putc( console_getc() );
				}	
				if( usb_read_ok() )
				{
					if( console_write_ok() )
					{	
					 	console_putc( usb_getc() );
					} 
				}	 
				
			}
		}
	}

//	 printf( "%08X\n", PIO_PDSR & USB_TO_SERIAL_BRIDGE_PIN );
	
	
	printf( "\n" );
	printf( "Welcome to the EZ-AT91SAM\n" );
	printf( "EZBootloader Ver %s\n", VERSION_STRING );	
	//printf( "Last Compile Date : %s\n",__DATE__ );

	if( usb_serial_mode.printf_select_usb )
	{
		printf( "USB CONSOLE\n" );
		led_on(LED_DS2);
	}
	else		
	{
		printf( "SERIAL CONSOLE\n" );
	}	
	
	if( usb_serial_mode.usbtoserial_bridge ) led_on(LED_DS3);	

	// goto module
	{
		unsigned int *fptr = (unsigned int *)0x110000;
		
		if ( 0xffffffff != *fptr ) 
		{
			int _loop_ = 10;
			
			while( _loop_-- )
			{
				if ( console_read_ok() && ( ' ' == console_getc() ) ) break;
				
				delay_msec( 100 );
				printf( "." );
			}
			
			if ( 0 >= _loop_ ) 
			{
				printf( "auto go module\n" );	
				go_module( 0, NULL );
			}
			printf( "\n" );
		}
		else
		{
			printf( "not exist module\n" );
		}	
	}


	while(1)
	{
		memset( read_line, 0 , sizeof( read_line ) );
		printf( "!EZLOAD>" );
		gets( (char *)read_line );
		printf( "\n");
		if( read_line[0] == ':' ) argc = parse_args( read_line+1, argv );
		else                      argc = parse_args( read_line  , argv ); 

		if(argc)
		{
			upper_str( argv[0] );

			if     ( !strcmp( argv[0], "HELP" ) ) { help                     ( argc, argv ); }
			else if( !strcmp( argv[0], "RST"  ) ) { reset                    ( argc, argv ); }
			else if( !strcmp( argv[0], "MRB"  ) ) { mem_read_byte            ( argc, argv ); }
			else if( !strcmp( argv[0], "MRW"  ) ) { mem_read_word            ( argc, argv ); }
			else if( !strcmp( argv[0], "MRL"  ) ) { mem_read_long            ( argc, argv ); }
			else if( !strcmp( argv[0], "XFM"  ) ) { xmodem_flash_write_module( argc, argv ); }
			else if( !strcmp( argv[0], "XF"  ) )  { xmodem_flash_write       ( argc, argv ); }
			else if( !strcmp( argv[0], "TST"  ) ) { test                     ( argc, argv ); }
			else if( !strcmp( argv[0], "FUNC" ) ) { get_module_func          ( argc, argv ); }
			else if( !strcmp( argv[0], "GM"   ) ) { go_module                ( argc, argv ); }
			else if( !strcmp( argv[0], "ERASEALL" ) ) { flash_erase_all(); }
			else if( !strcmp( argv[0], "LOCKINFO" ) ) { flash_lock_info        ( argc, argv ); }
			else if( !strcmp( argv[0], "MODEL"  ) ) { protocol_model           ( argc, argv ); }				
			else if( !strcmp( argv[0], "BW"     ) ) { protocol_buff_write      ( argc, argv ); }
			else if( !strcmp( argv[0], "PROGRAM") ) { protocol_write_page      ( argc, argv ); }				
			else if( !strcmp( argv[0], "MDUMP"  ) ) { mem_dump(argc, argv); }

		}
	}
	return 0;
}

