//------------------------------------------------------------------------------
// 파 일 명 : printf.c
// 프로젝트 : ez-jtag
// 설    명 : printf 처리 
// 작 성 자 : 유영창(frog@falinux.com)
// 작 성 일 : 2007년 5월 6일
// 수 정 일 : 
// 수 정 일 : 
// 주    의 : 
// 라이센스 : BSD
//------------------------------------------------------------------------------
#include <typedef.h>
#include <register.h>
#include <setup.h>

#include <console.h>
#include <usb_serial.h>
#include <main.h>

#include <stdio.h>
#include <string.h>

//------------------------------------------------------------------------------
// 설명 : 한문자를 출력한다. 
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 캐리지 리턴의 변화를 처리한다. 
//------------------------------------------------------------------------------
int putc(char c)
{
	if( usb_serial_mode.printf_select_usb )
	{
		usb_putc( c );
		if(c == '\n') usb_putc( '\r' );
		
	}
	else
	{
		console_putc( c );
		if(c == '\n') console_putc('\r');
	}	
			
	return 1;
}
//------------------------------------------------------------------------------
// 설명 : 한문자를 출력한다. 
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
int putx(char c)
{
	if( usb_serial_mode.printf_select_usb ) usb_putc( (const char) c );
	else			        console_putc( (const char) c );
	return 1;
}

//------------------------------------------------------------------------------
// 설명 : 문자열을 출력한다. 
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 캐리지 리턴의 변화를 처리한다. 
//------------------------------------------------------------------------------
int puts( char *str, int size )
{
#ifdef console_puts
	console_puts( str, size );
#else
	
	int	lp ;
	for (lp=0;lp<size;lp++) putc(str[lp]);
	
#endif
	return 1;
}

//------------------------------------------------------------------------------
// 설명 : 포맷형 문자열을 출력한다. 
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
int printf(const char *fmt, ...)
{
	char buffer[1024];
	va_list ap;
	int len;

	va_start(ap, fmt);
	len = vsprintf(buffer, fmt, ap);
	va_end(ap);
  	puts(buffer, len);

	return len;
}

//------------------------------------------------------------------------------
// 설명 : 한문자의 입력을 얻는다. 
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
int getc(void)
{
	unsigned int lp = 0;
	int c;

	if( usb_serial_mode.printf_select_usb )
	{
		// 한문자 대기 
		while( !usb_read_ok() ) 
    		{
			lp++;
    		}
    		c = usb_getc() & 0xFF;
	}
	else
	{	
		// 한문자 대기 
		while( !console_read_ok() ) 
    		{
			lp++;
    		}
    		c = console_getc() & 0xFF;
	}
	
	return c;
}
//------------------------------------------------------------------------------
// 설명 : 문자열 입력을 받는다. ( CR이 입력될때까지 )
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
int gets(char *s)
{
     int cnt = 0;
     char  c;

     //while((c = getc()) != CR)
     while(1)
     {
          c = (char )(getc() & 0xff);
          if ( c == CR ) break;

          if(c != BS) 
          {  
          	cnt++;
            *s++ = c;
            printf("%c",c );
          }
          else 
          {
               if(cnt > 0) 
               { cnt--; *s-- = ' '; 
                 printf("\b \b");  
               } 
          }
     }
     *s = 0;
   
     return(cnt);
}

