//------------------------------------------------------------------------------
// 파 일 명 : module.h
// 프로젝트 : ez-jtag
// 설    명 : 모듈 처리를 위한 헤더파일
// 작 성 자 : 유영창(frog@falinux.com)
// 작 성 일 : 2007년 6월 2일
// 수 정 일 : 
// 수 정 일 : 
// 주    의 : 
// 라이센스 : BSD
//------------------------------------------------------------------------------

#ifndef _MODULE_HEADER_
#define _MODULE_HEADER_

typedef struct
{
	// console.h
	void  			(*_console_putc)( const u8 c );
	u32  			(*_console_read_ok)( void );
	u8  			(*_console_getc)( void );
	int             (*_console_puts)( const u8 *buf, int cnt );
	
	// irq.h	
	u32				(*_irq_enable)	(void);
	u32 			(*_irq_disable)	(void);
	u32 			(*_irq_restore)	( u32 oldCPSR );
	
	void 			(*_irq_active)	( u32 irq );
	void 			(*_irq_deactive)( u32 irq );
	void 			(*_irq_clear)	( u32 irq );
	
	void 			(*_irq_request) ( u32 irq, u32 type, void (*irq_func ) (void ) );
	void 			(*_irq_free)	( u32 irq );
	
	// stdio.h
	int 			(*_vsprintf)	(char *buf, const char *fmt, va_list args);
	int 			(*_sprintf)		(char * buf, const char *fmt, ...);
	int 			(*_putc)		(char c);
	int 			(*_printf)		(const char *fmt, ...);
	int 			(*_getc)		(void);
	int 			(*_gets)		(char *s);
	int 			(*_vsscanf)		(char *s, const char *fmt, va_list args);
	int 			(*_sscanf)		(char *s, const char *fmt, ...);

	// string.h
	char * 			(*_strpbrk)		(const char *,const char *);
	char * 			(*_strtok)		(char *,const char *);
	char * 			(*_strsep)		(char **,const char *);
	__kernel_size_t (*_strspn)		(const char *,const char *);
	char * 			(*_strcpy)		(char *,const char *);
	char * 			(*_strncpy)		(char *,const char *, __kernel_size_t);
	char * 			(*_strcat)		(char *, const char *);
	char * 			(*_strncat)		(char *, const char *, __kernel_size_t);
	int 			(*_strcmp)		(const char *,const char *);
	int 			(*_strncmp)		(const char *,const char *,__kernel_size_t);
	int 			(*_strnicmp)	(const char *, const char *, __kernel_size_t);
	char * 			(*_strchr)		(const char *,int);
	char * 			(*_strrchr)		(const char *,int);
	char * 			(*_strstr)		(const char *,const char *);
	__kernel_size_t (*_strlen)		(const char *);
	__kernel_size_t (*_strnlen)		(const char *,__kernel_size_t);
	void * 			(*_memset)		(void *,int,__kernel_size_t);
	void * 			(*_memcpy)		(void *,const void *,__kernel_size_t);
	void * 			(*_memmove)		(void *,const void *,__kernel_size_t);
	void * 			(*_memscan)		(void *,int,__kernel_size_t);
	int 			(*_memcmp)		(const void *,const void *,__kernel_size_t);
	void * 			(*_memchr)		(const void *,int,__kernel_size_t);
	unsigned long 	(*_strtoul)		(const char *p, char **out_p, int base);
	void 			(*_upper_str)	( char *Str );
	void 			(*_lower_str)	( char *Str );
	
	// timer.h
	u32   			(*_timer_msec)	( void );       		// 현재 타이머 틱값을 반환한다.
	u32   			(*_timer_sec)	( void );              	// 부팅 후 지난 시간을 초 단위로 구한다. 
	u32   			(*_timer_random)( void );       	    // 랜덤값을 반환한다.
	void 			(*_timer_set_timeover)( u32 msec );		// 초과 시간을 설정한다.
	u32   			(*_timer_is_timeover)( void );			// 설정된 시간 초과가 발생했는가를 확인한다. 
	void			(*_mdelay)		( u32  msec );   		// 밀리세컨드 단위시간동안 대기 한다. 
	void			(*_udelay)		( u32  delay);   		// usec 단위시간동안 대기 한다. 
	int 			(*_timer_set_task)( void (*task )(void *), void *id, int msec_delay );    // 테스크 등록
	void			(*_timer_del_task)( int idx );          // 


	// flash.h
	s32             (*_flash_write_all)(u32 flash_dest_addr, s32 size, u32 * pbuff);  // 플래시 쓰기

} call_t;

#ifndef _MODULE_VAR_
	extern call_t call;
#endif

#endif  // _MODULE_HEADER_

