/*------------------------------------------------------------------------------
 ȭ�ϸ� : timer.c
 ��  �� : ezload�� Timer ���� ��ƾ�̴�. 
 
 �ۼ��� : ����â �������̸�����(��) frog@falinux.com
 �ۼ��� : 2007�� 6�� 16��
 ��  �� : 2008-10-20 �����   �׽�ũ�� �����ϵ��� �����Ͽ���. (���/����/ȣ��)
              
 ��  �� : 
------------------------------------------------------------------------------*/

//******************************************************************************
//
// ��� ����
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
// ���� ���� ����
//******************************************************************************

u32 random_seed    = 0;	// ������ �߻��� ���� �� 
u32 mticks  	   = 0;	// 1mSec ���� ���� �ϴ� ƽ��
u32 time_over_end  = 0;	// �ð� �ʰ��� �����ϱ� ���� ����

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
// ���� ���� ����
//******************************************************************************

// static u8 led_mode_flag	= 1; // EZ-module ��忡�� LED ������ ���� �÷��� ���� 

//******************************************************************************
// �Լ� ����
//******************************************************************************

//------------------------------------------------------------------------------
// ���� :1m Sec ���� �����ϴ� Ÿ�̸� ���ͷ�Ʈ �ڵ鷯
// �Ű� : ���� 
// ��ȯ : ���� 
// ���� : ���� 
//------------------------------------------------------------------------------
void timer_irq_handler( void )
{
	u32 dummy;

	dummy = TC0_SR;		// Ÿ�̸� ���ͷ�Ʈ Ŭ����
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
			
			// ���� �׽�ũ�� �����Ѵ�.
			cur_task = cur_task->next;
			if ( cur_task == NULL ) cur_task = root_task.next;
		}
	}

	// USB ó���� callback�� ȣ���Ѵ�. 
	if( usb_call ) usb_call();
		
}

//------------------------------------------------------------------------------
// ���� : Ÿ�̸Ӹ� �ʱ�ȭ �Ѵ�. 
// �Ű� : ���� 
// ��ȯ : ���� 
// ���� : ���� 
//------------------------------------------------------------------------------
void timer_init(void)
{
	u32 dummy;

	random_seed    = 0;
	mticks         = 0;	    				// 1mSec ���� ���� �ϴ� ƽ��
	time_over_end  = 0;	         			// 1mSec ���� ���� �ϴ� ƽ��

	PMC_PCER = 1 << ID_TC0;    				// Ÿ�̸� Ŭ���� ���� ��Ų��.

	TC0_CCR = TC_CLKDIS;					// Ŭ���� ���ͷ�Ʈ�� ������ ��Ų��.
	TC0_IDR = 0xFFFFFFFF ;

	dummy = TC0_SR;						 	// ���� ��Ʈ�� Ŭ���� �Ѵ�.
	
	TC0_CMR = TC_CLKS_TIMER_DIV5_CLOCK | TC_CPCTRG | TC_WAVE | TC_EEVT_XC0;
	TC0_RC  = TICKS_PER_MSECOND;  //  1�ʴ� 800 Ŭ�� ���� 1Ŭ�� ����� �Ѵ�. (2013-07-25)

	TC0_CCR = TC_CLKEN ;					// Ŭ���� ���۽�Ų��.
	TC0_IER = TC_CPCS;  					// Ÿ�̸� ���ͷ�Ʈ �㰡 CPC ����

	irq_request( ID_TC0, AIC_SRCTYPE_INT_HIGH_LEVEL, timer_irq_handler ); // ���ͷ�Ʈ �ڵ鷯 ���
	irq_active( ID_TC0 );                   // Ÿ�̸� ���ͷ�Ʈ �㰡

	TC0_CCR = TC_SWTRG ;					// Ÿ�̸� ���� ����

	dummy = dummy;							// dummy ��� ������ ������ �ʾҴٴ� ������ ��� �����ϱ� ���� ����
	
	
	memset( task_pool, 0, sizeof(task_pool) );
	memset( &root_task, 0, sizeof(root_task) );
//	printf( "TIMER TICK = %d\n",  );
}

//------------------------------------------------------------------------------
// ���� : ������ �����ð��� msec �� ������ ���� �ش�.
// �Ű� : ���� 
// ��ȯ : ���� 
// ���� : ���� 
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
// ���� : ������ �����ð��� �� ������ ���� �ش�.
// �Ű� : ���� 
// ��ȯ : ���� 
// ���� : ���� 
//------------------------------------------------------------------------------
u32 timer_sec(void)
{
	return mticks / 1000;	
}

//------------------------------------------------------------------------------
// ���� : �������� ��ȯ�Ѵ�.
// �Ű� : ���� 
// ��ȯ : ���� 
// ���� : ���� 
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
// ���� : �и� ������ ���� ������ ���´�.
// �Ű� : ���� 
// ��ȯ : ���� 
// ���� : ???ms �̻��� ������ �������� �ʴ´�.
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
// ���� : �ʰ� �ð��� �����Ѵ�.
// �Ű� : msec : ������ �̸��� ���� �ð�
//------------------------------------------------------------------------------
void timer_set_timeover( u32 msec )
{
	time_over_end = timer_msec();
	time_over_end = time_over_end + msec;
}

//------------------------------------------------------------------------------
// ���� : ������ �ð� �ʰ��� �߻��ߴ°��� Ȯ���Ѵ�. 
// ��ȯ : Ÿ�ӿ���= 1, ���� = 0
// ���� : 
//------------------------------------------------------------------------------
u32   timer_is_timeover( void )
{
	u32 cur_msec;

	cur_msec = timer_msec();
	if( cur_msec < time_over_end ) return 0;
	return 1;
}

//------------------------------------------------------------------------------
// ���� : USB �� �۽� ó���� ���� �ݹ� ���� 
// ��ȯ : 
// ���� : 
//------------------------------------------------------------------------------
void timer_set_usb_callback( void (*call_func ) (void ) )
{
	usb_call = call_func;
}


//------------------------------------------------------------------------------
// ���� : ��Ȯ�� u-sec delay  
// ��ȯ : 
// ���� : 
//------------------------------------------------------------------------------
void udelay( u32 delay )
{
	delay = (delay * 6) - 2;
	
	do {} while(delay--);
}

//------------------------------------------------------------------------------
// ���� : last task
// ��ȯ : ��ϵ� �ε���
// ���� : 
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
// ���� : 1msec �ݹ� �Լ� ���
// ��ȯ : ��ϵ� �ε���
// ���� : 
//        ù��° task->prev = NULL �̴�.
//        ������ task->next = NULL �̴�.
//        1msec �� Ÿ�̸� �׽�ũ�� ����Ѵ�.                                           
//        msec_delay �ð���ŭ ���� �� ȣ���Ѵ�.                                        
//        �̹� �׽�Ʈ�� 3�� ��ϵ� ���¿��� 4��° �׽�ũ�� 2msec �������� ����Ͽ��ٸ� 3msec ���Ŀ� ȣ��ȴ�.                                                       
//        1msec �ð����ȿ��� �ϳ��� �׽�ũ ���� ȣ��ȴ�.                              
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
// ���� : �ݹ� �Լ� ����
// ��ȯ : ��ϵ� �ε���
// ���� : 
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


