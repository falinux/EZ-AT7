//------------------------------------------------------------------------------
// �� �� �� : timer.h
// ��    �� : ezboot���� ����ϴ� timer ó���� ���õ� ��� 
// �� �� �� : ����â
// �� �� �� : 2007�� 6�� 16��
// �� �� �� : 
//------------------------------------------------------------------------------

#ifndef _TIMER_HEADER_
#define _TIMER_HEADER_


#ifndef __MODULE__

extern void		timer_init	( void );             	// Ÿ�̸� �ʱ�ȭ 
extern u32   	timer_msec	( void );       		// ���� Ÿ�̸� ƽ���� ��ȯ�Ѵ�.
extern u32   	timer_sec	( void );              	// ���� �� ���� �ð��� �� ������ ���Ѵ�. 

extern u32   	timer_random( void );       	    // �������� ��ȯ�Ѵ�.

extern void 	timer_set_timeover( u32 msec );		// �ʰ� �ð��� �����Ѵ�.
extern u32   	timer_is_timeover( void );			// ������ �ð� �ʰ��� �߻��ߴ°��� Ȯ���Ѵ�. 

extern void		mdelay		( u32  msec );   		// �и������� �����ð����� ��� �Ѵ�. 
extern void     udelay      ( u32  delay);          // usec �����ð����� ��� �Ѵ�. 
extern void 	timer_set_usb_callback( void (*call_func ) (void ) ); 

extern void     timer_del_task( int idx                                         ); // �׽�ũ���� �����Ѵ�.
extern int      timer_set_task( void (*task )(void *), void *id, int msec_delay ); // 1msec �� Ÿ�̸� �׽�ũ�� ����Ѵ�.
                                                                                   // msec_delay �ð���ŭ ���� �� ȣ���Ѵ�.
                                                                                   // �̹� �׽�Ʈ�� 3�� ��ϵ� ���¿��� 4��° �׽�ũ�� 2msec �������� ����Ͽ��ٸ�
                                                                                   // 3msec ���Ŀ� ȣ��ȴ�.
                                                                                   // 1msec �ð����ȿ��� �ϳ��� �׽�ũ ���� ȣ��ȴ�.


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

