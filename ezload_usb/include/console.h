//------------------------------------------------------------------------------
// �� �� �� : console.h
// ������Ʈ : ez-jtag
// ��    �� : �ܼ� ��� ����
// �� �� �� : ����â(frog@falinux.com)
// �� �� �� : 2007�� 5�� 6��
// �� �� �� : 
// �� �� �� : 
// ��    �� : 
// ���̼��� : BSD
//------------------------------------------------------------------------------

#ifndef _CONSOLE_HEADER_
#define _CONSOLE_HEADER_

#ifndef __MODULE__

extern void 		console_init( u32 baudrate );
extern void 		console_init_by_usb( u32 baudrate, u32 parity, u32 stop, u32 datasize );


extern u32  		console_write_ok( void );
extern RAMFUNC void console_putc( const u8 c );
extern u32  		console_read_ok( void );
extern u8  			console_getc( void );
extern int          console_puts( const u8 *buf, int cnt );

#else

#define console_putc     	call._console_putc
#define console_read_ok     call._console_read_ok
#define console_getc        call._console_getc
#define console_puts        call._console_puts

#endif

#endif  // _TYPEDEF_HEADER_

