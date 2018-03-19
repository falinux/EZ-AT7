//------------------------------------------------------------------------------
// 파 일 명 : timer.h
// 설    명 : ezboot에서 사용하는 timer 처리에 관련된 헤더 
// 작 성 자 : 유영창
// 작 성 일 : 2007년 6월 16일
// 수 정 일 : 
//------------------------------------------------------------------------------

#ifndef _TIMER_HEADER_
#define _TIMER_HEADER_


#ifndef __MODULE__

extern void		timer_init	( void );             	// 타이머 초기화 
extern u32   	timer_msec	( void );       		// 현재 타이머 틱값을 반환한다.
extern u32   	timer_sec	( void );              	// 부팅 후 지난 시간을 초 단위로 구한다. 

extern u32   	timer_random( void );       	    // 랜덤값을 반환한다.

extern void 	timer_set_timeover( u32 msec );		// 초과 시간을 설정한다.
extern u32   	timer_is_timeover( void );			// 설정된 시간 초과가 발생했는가를 확인한다. 

extern void		mdelay		( u32  msec );   		// 밀리세컨드 단위시간동안 대기 한다. 
extern void     udelay      ( u32  delay);          // usec 단위시간동안 대기 한다. 
extern void 	timer_set_usb_callback( void (*call_func ) (void ) ); 

extern void     timer_del_task( int idx                                         ); // 테스크에서 제거한다.
extern int      timer_set_task( void (*task )(void *), void *id, int msec_delay ); // 1msec 의 타이머 테스크에 등록한다.
                                                                                   // msec_delay 시간만큼 지연 후 호출한다.
                                                                                   // 이미 테스트가 3개 등록된 상태에서 4번째 테스크를 2msec 지연으로 등록하였다면
                                                                                   // 3msec 이후에 호출된다.
                                                                                   // 1msec 시간동안에는 하나의 테스크 만이 호출된다.


#else


#define timer_msec          call._timer_msec        
#define timer_sec           call._timer_sec         
#define timer_random        call._timer_random      
#define timer_set_timeover  call._timer_set_timeover
#define timer_is_timeover   call._timer_is_timeover 
#define mdelay              call._mdelay            
#define udelay              call._udelay            
#define timer_set_task      call._timer_set_task
#define timer_del_task      call._timer_del_task

#endif


#endif //_TIMER_HEADER_

