//------------------------------------------------------------------------------
// 파 일 명 : irq.h
// 프로젝트 : ez-jtag
// 설    명 : irq 처리와 관련한 파일
// 작 성 자 : 유영창(frog@falinux.com)
// 작 성 일 : 2007년 5월 26일
// 수 정 일 : 
// 수 정 일 : 
// 주    의 : 
// 라이센스 : BSD
//------------------------------------------------------------------------------

#ifndef _IRQ_HEADER_
#define _IRQ_HEADER_

#ifndef __MODULE__


extern void irq_init( void );

extern RAMFUNC u32 irq_enable(void);
extern RAMFUNC u32 irq_disable(void);
extern RAMFUNC u32 irq_restore( u32 oldCPSR );

extern void RAMFUNC irq_active( u32 irq );
extern void RAMFUNC irq_deactive( u32 irq );
extern void RAMFUNC irq_clear( u32 irq );

extern void irq_request ( u32 irq, u32 type, void (*irq_func ) (void ) );
extern void irq_free( u32 irq );

#else

#define irq_enable      call._irq_enable    
#define irq_disable     call._irq_disable   
#define irq_restore     call._irq_restore   

#define irq_active      call._irq_active    
#define irq_deactive    call._irq_deactive  
#define irq_clear       call._irq_clear     

#define irq_request     call._irq_request   
#define irq_free        call._irq_free      

#endif

#endif  // _IRQ_HEADER_

