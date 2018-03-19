/*------------------------------------------------------------------------------
 화일명 : timer.c
 설  명 : ezload의 Timer 제어 루틴이다. 
 
 작성자 : 유영창 에프에이리눅스(주) frog@falinux.com
 작성일 : 2007년 6월 16일
 수  정 : 2008-10-20 오재경   테스크를 관리하도록 수정하였다. (등록/삭제/호출)
              
 주  의 : 
------------------------------------------------------------------------------*/

//******************************************************************************
//
// 헤더 정의
//
//******************************************************************************
#include <typedef.h>
#include <register.h>
#include <stdio.h>
#include <string.h>
#include <setup.h>
#include <irq.h>
#include <timer.h>
#include <main.h>

#include <stdio.h>

#define PCLK  				(47923200)
#define TICKS_PER_MSECOND	(PCLK/1024/1000)
#define TIMER_TASK_MAX      32

//******************************************************************************
// 광역 변수 정의
//******************************************************************************

u32 random_seed    = 0;	// 랜덤값 발생을 위한 값 
u32 mticks  	   = 0;	// 1mSec 마다 증가 하는 틱수
u32 time_over_end  = 0;	// 시간 초과를 연산하기 위한 변수

void (*usb_call ) (void ) = NULL;


struct timer_task {
	
	void (*func)(void *);
	void *id;
	
	struct timer_task *prev;
	struct timer_task *next;
	
	int  reload_cnt;
	int  delay_cnt;
	
};

static struct timer_task  task_pool[TIMER_TASK_MAX];

static struct timer_task  root_task;
static struct timer_task *cur_task = NULL;

static u32   timer_task_cnt = 0;


//******************************************************************************
// 정적 변수 정의
//******************************************************************************

// static u8 led_mode_flag	= 1; // EZ-module 모드에서 LED 점멸을 위한 플레그 변수 

//******************************************************************************
// 함수 정의
//******************************************************************************

//------------------------------------------------------------------------------
// 설명 :1m Sec 마다 동작하는 타이머 인터럽트 핸들러
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
void timer_irq_handler( void )
{
	u32 dummy;

	dummy = TC0_SR;		// 타이머 인터럽트 클리어
	dummy = dummy;

	mticks++;

	// time task _________________
	if ( 0 < timer_task_cnt )
	{
		if ( cur_task )
		{
			cur_task->delay_cnt -= timer_task_cnt;
			
			if ( 0 >= cur_task->delay_cnt )
			{
				if (cur_task->func) cur_task->func( cur_task->id );
				
				cur_task->delay_cnt = cur_task->reload_cnt;
			}
			
			// 다음 테스크를 지정한다.
			cur_task = cur_task->next;
			if ( cur_task == NULL ) cur_task = root_task.next;
		}
	}

	// USB 처리용 callback을 호출한다. 
	if( usb_call ) usb_call();
		
}

//------------------------------------------------------------------------------
// 설명 : 타이머를 초기화 한다. 
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
void timer_init(void)
{
	u32 dummy;

	random_seed    = 0;
	mticks         = 0;	    				// 1mSec 마다 증가 하는 틱수
	time_over_end  = 0;	         			// 1mSec 마다 증가 하는 틱수

	PMC_PCER = 1 << ID_TC0;    				// 타이머 클럭을 동작 시킨다.

	TC0_CCR = TC_CLKDIS;					// 클럭과 인터럽트를 디저블 시킨다.
	TC0_IDR = 0xFFFFFFFF ;

	dummy = TC0_SR;						 	// 상태 비트를 클리어 한다.
	
	TC0_CMR = TC_CLKS_TIMER_DIV5_CLOCK | TC_CPCTRG | TC_WAVE | TC_EEVT_XC0;
	TC0_RC  = TICKS_PER_MSECOND;  //  1초당 800 클럭 빨라 1클럭 더줘야 한다. (2013-07-25)

	TC0_CCR = TC_CLKEN ;					// 클럭을 동작시킨다.
	TC0_IER = TC_CPCS;  					// 타이머 인터럽트 허가 CPC 모드로

	irq_request( ID_TC0, AIC_SRCTYPE_INT_HIGH_LEVEL, timer_irq_handler ); // 인터럽트 핸들러 등록
	irq_active( ID_TC0 );                   // 타이머 인터럽트 허가

	TC0_CCR = TC_SWTRG ;					// 타이머 동작 시작

	dummy = dummy;							// dummy 라는 변수가 사용되지 않았다는 컴파일 경고를 방지하기 위한 구분
	
	
	memset( task_pool, 0, sizeof(task_pool) );
	memset( &root_task, 0, sizeof(root_task) );
//	printf( "TIMER TICK = %d\n",  );
}

//------------------------------------------------------------------------------
// 설명 : 부팅후 지난시간을 msec 초 단위로 돌려 준다.
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
u32 timer_msec(void)
{
/*
	u32 old_flag;
	u32 ret_msec;

	old_flag = irq_disable();
	ret_msec = mticks;
	irq_restore( old_flag );
	
	return ret_msec;	
*/
	return 	mticks;
}

//------------------------------------------------------------------------------
// 설명 : 부팅후 지난시간을 초 단위로 돌려 준다.
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
u32 timer_sec(void)
{
	return mticks / 1000;	
}

//------------------------------------------------------------------------------
// 설명 : 랜덤값을 반환한다.
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
u32 timer_random( void )
{
	u32 next;
  	u32 result;

	if( random_seed == 0 ) random_seed = (unsigned long ) timer_msec();
	next = random_seed;

  	next *= 1103515245;
  	next += 12345;
  	result = (unsigned int) (next / 65536) % 2048;

  	next *= 1103515245;
  	next += 12345;
  	result <<= 10;
  	result ^= (unsigned int) (next / 65536) % 1024;

  	next *= 1103515245;
  	next += 12345;
  	result <<= 10;
  	result ^= (unsigned int) (next / 65536) % 1024;

  	random_seed = next;

  	return result;
}

//------------------------------------------------------------------------------
// 설명 : 밀리 세컨드 동안 지연을 갇는다.
// 매계 : 없음 
// 반환 : 없음 
// 주의 : ???ms 이상의 지연은 지원하지 않는다.
//------------------------------------------------------------------------------
void mdelay(u32 msec)
{
	u32 end_msec;
	u32 cur_msec;

	cur_msec = timer_msec();
	end_msec = cur_msec + msec;

	while( 1 )
	{
		cur_msec = timer_msec();
		if( cur_msec >= end_msec ) break;
	}
}

//------------------------------------------------------------------------------
// 설명 : 초과 시간을 설정한다.
// 매계 : msec : 설정한 미리초 단위 시간
//------------------------------------------------------------------------------
void timer_set_timeover( u32 msec )
{
	time_over_end = timer_msec();
	time_over_end = time_over_end + msec;
}

//------------------------------------------------------------------------------
// 설명 : 설정된 시간 초과가 발생했는가를 확인한다. 
// 반환 : 타임오버= 1, 정상 = 0
// 주의 : 
//------------------------------------------------------------------------------
u32   timer_is_timeover( void )
{
	u32 cur_msec;

	cur_msec = timer_msec();
	if( cur_msec < time_over_end ) return 0;
	return 1;
}

//------------------------------------------------------------------------------
// 설명 : USB 를 송신 처리를 위한 콜백 설정 
// 반환 : 
// 주의 : 
//------------------------------------------------------------------------------
void timer_set_usb_callback( void (*call_func ) (void ) )
{
	usb_call = call_func;
}


//------------------------------------------------------------------------------
// 설명 : 정확한 u-sec delay  
// 반환 : 
// 주의 : 
//------------------------------------------------------------------------------
void udelay( u32 delay )
{
	delay = (delay * 6) - 2;
	
	do {} while(delay--);
}

//------------------------------------------------------------------------------
// 설명 : last task
// 반환 : 등록된 인덱스
// 주의 : 
//------------------------------------------------------------------------------
static struct timer_task *get_last_task( void )
{
	struct timer_task *ptask = root_task.next;
		
	if ( NULL == ptask ) return NULL;
		
	while( 1 )
	{
		if ( ptask->next == NULL )
		{
			return 	ptask;
		}
		
		ptask = ptask->next;
	}

	return NULL;	
}

//------------------------------------------------------------------------------
// 설명 : 1msec 콜백 함수 등록
// 반환 : 등록된 인덱스
// 주의 : 
//        첫번째 task->prev = NULL 이다.
//        마지막 task->next = NULL 이다.
//        1msec 의 타이머 테스크에 등록한다.                                           
//        msec_delay 시간만큼 지연 후 호출한다.                                        
//        이미 테스트가 3개 등록된 상태에서 4번째 테스크를 2msec 지연으로 등록하였다면 3msec 이후에 호출된다.                                                       
//        1msec 시간동안에는 하나의 테스크 만이 호출된다.                              
//------------------------------------------------------------------------------
int timer_set_task( void (*task )(void *), void *id, int msec_delay )
{
	struct timer_task *last, *ptask = NULL;
	int idx;
	u32 flag;

	if ( NULL == task ) return -1;
	
	for (idx=0; idx<TIMER_TASK_MAX; idx++)
	{
		if ( NULL == task_pool[idx].func )
		{
			ptask = &task_pool[idx];
			break;
		}
	}
	
	if ( ptask )
	{
		flag = irq_disable();

		timer_task_cnt ++;
		ptask->func  = task;
		ptask->id    = id;
		ptask->reload_cnt = msec_delay;
	  	ptask->delay_cnt  = msec_delay;
		
		if ( root_task.next == NULL )
		{
			cur_task = ptask;
			
			cur_task->prev = NULL;
			cur_task->next = NULL;
			
			root_task.next = ptask;
		}
		else
		{
			last = get_last_task();
			
			ptask->next = last->next;
			last->next  = ptask;
			ptask->prev = last;
		}
		
		irq_restore( flag );
		
		printf( "add task %d  (taskcnt=%d)\n", idx, timer_task_cnt );
		
		return idx;
	}
	
	return -1;
	
}
//------------------------------------------------------------------------------
// 설명 : 콜백 함수 제거
// 반환 : 등록된 인덱스
// 주의 : 
//------------------------------------------------------------------------------
void timer_del_task( int idx )
{
	u32 flag;
	
	if ( (0 <= idx ) && ( idx <= TIMER_TASK_MAX ) )
	{
		struct timer_task  *ptask = &task_pool[idx];
		void *sv_prev, *sv_next;
	
		if ( ptask->func )
		{
			//printf( " -1) ptask->prev=%p  ptask->next=%p cur=%p\n", ptask->prev, ptask->next, cur_task );

			flag = irq_disable();
			
			timer_task_cnt --;
			ptask->func = NULL;
			ptask->id   = NULL;
			
			sv_prev = ptask->prev;
			sv_next = ptask->next;

			if ( NULL == ptask->prev )
			{
				root_task.next = ptask->next;
			}

			if ( cur_task == ptask	)
			{
				cur_task = ptask->next;
			}

			if ( ptask->next ) ptask->next->prev = sv_prev;
			if ( ptask->prev ) ptask->prev->next = sv_next;

			
			irq_restore( flag );
			
			//printf( " -2) ptask->prev=%p  ptask->next=%p cur=%p\n", ptask->prev, ptask->next, cur_task );
			
			printf( "del task %d  (taskcnt=%d)\n", idx, timer_task_cnt );
		}
	}
}


