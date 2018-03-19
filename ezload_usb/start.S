/*==============================================================================================

  화일명 : start.S
  설  명 : AT91SAM7S256 리셋시 호출되는 루틴

  작성자 : 에프에이리눅스(주)  유영창
  작성일 : 2007년 4월 18일
  수  정 :
  작성일 :
  비  고 :

================================================================================================*/

#include <register.h>
#include <setup.h>

#define 	  	IRQ_STACK_SIZE    	(3*8*4)

#define       	ARM_MODE_FIQ       	0x11
#define       	ARM_MODE_IRQ       	0x12
#define       	ARM_MODE_SVC       	0x13

#define         IRQ_DISABLE      	0x80
#define         FIRQ_DISABLE     	0x40

.text

//------------------------------------------------------------------------------------------------
//
//  인터럽트  벡터 테이블
//
//------------------------------------------------------------------------------------------------
.globl 		_start,_boot_load_store

_start:	b	reset		    		// MCU가 리셋된후 실행된다.
		b	undefined_instruction	// 정의되지 않는 명령이 명령 인스트럭터에 패치되었을때 실행된다.
		b	software_interrupt      // 소프트웨어적인 인터럽트 명령(SWI)가 수행되었을 때 실행된다.
		b	prefetch_abort			// 데이타를 프리 패치 할때 버스 에러가 발생하면 실행된다.
		b	data_abort	        	// 데이타 에러가 발생하면 실행된다.
		b	not_used	        	// 사용되지 않는다.
		b	IRQ		        		// IRQ 인터럽트가 발생되면 실행된다.
		b	FIQ						// IRQ 인터럽트보다 우선권이 있는 인터럽트가 발생되면 실행된다.

//------------------------------------------------------------------------------------------------
//
//  RESET이 발생하거나 전원이 들어 왔을때 맨 처음 수행되는 루틴이다.
//
//------------------------------------------------------------------------------------------------
reset:

		//
		// IRQ/FIQ 를 디스에이블 시키고 IRQ 모드로 전환한다.
		//
		mrs		r0, CPSR
		bic		r0, r0, #0x1F
		orr		r0, r0, #( ARM_MODE_IRQ | IRQ_DISABLE | FIRQ_DISABLE )
		msr		CPSR_c, r0

        //
        // IRQ 스택을 설정한다.
        //
		ldr		r1, =ADDR_STACK
		mov		sp,r1

		//
		// IRQ/FIQ 를 디스에이블 시키고 수퍼바이저 모드로 전환한다.
		//
		mrs		r0, CPSR
		bic		r0, r0, #0x1F
		orr		r0, r0, #( ARM_MODE_SVC | IRQ_DISABLE | FIRQ_DISABLE )
		msr		CPSR_c, r0

        //
        // IRQ 스택을 설정한다.
        //
        sub     r1, r1, #IRQ_STACK_SIZE
		mov		sp,r1

		//
		// 플래쉬 메모리 대기 상태 설정
		//
		ldr		r0, =(MC_FMCN_VAL|MC_FWS_1FWS)						// 플래쉬 메모리 대기 상태 설정
		ldr		r1, =MC_FMR                                     	// 30 또는 40 MHz 이상일 경우 1 사이클 억세스
		str		r0, [r1]                                        	// 만약 MCK 가 47923200 (MC_FMCN_VAL = 48) 이면 1 마이크로초 당 50 사이클을 가진다.

		//
		// 워치독 디저블
		//
		ldr		r0, =(WDTC_WDDIS)									// 워치독 디저블
		ldr		r1, =WDTC_WDMR
		str		r0, [r1]

		//
		// MCK 클럭을 47.923200 MHz 설정
		//
		ldr		r0, =(CKGR_OSCOUNT_VAL|CKGR_MOSCEN)					// MCK 클럭을 47.923200 MHz 설정
		ldr		r1, =PMC_MOR                                    	// 메인 오실레이터 이네이블
		str		r0, [r1]                                        	// SCK = 1/32768 = 30.51 마이크로초
    	                                                        	// 스타트업 타임 = 8 * 6 / SCK = 56 * 30.51 = 1,46484375 미리초

		ldr		r1, =PMC_SR											// 메인 OSC 선택에 대한 안정화를 위한 대기
wait_osc_stable:
		ldr		r0,[r1]
		ands	r0,r0,#PMC_MOSCS
        beq		wait_osc_stable

		//
		// PLL 설정및 분주비 설정
		//
		ldr		r0, =(CKGR_DIV_VAL|CKGR_PLLCOUNT_VAL|CKGR_MUL_VAL)    // PLL 설정및 분주비 설정
		ldr		r1, =PMC_PLLR                                         // - div by 5 Fin = 3,6864 =(18,432 / 5)
		str		r0, [r1]                                              // - Mul 25+1: Fout =	95,8464 =(3,6864 *26)
                                                                      // 96 MHz 경우 오차율  0.16%
                                                                      // Field out NOT USED = 0
                                                                      // PLLCOUNT pll startup time estimate at : 0.844 ms
                                                                      // PLLCOUNT 28 = 0.000844 /(1/32768)

		ldr		r1, =PMC_SR											  // PLL LOCK 에 대한 안정화를 위한 대기
wait_lock_stable:
		ldr		r0,[r1]
		ands	r0,r0,#PMC_LOCK
        beq		wait_lock_stable

		ldr		r1, =PMC_SR											// MCK 에 대한 안정화를 위한 대기를  한다.
wait_mck_stable1:
		ldr		r0,[r1]
		ands	r0,r0,#PMC_MCKRDY
        beq		wait_mck_stable1

		//
		// PLL 클럭을 2 분주
		//
		ldr		r0, =(PMC_PRES_CLK_2)								// PLL 클럭을 2 분주
		ldr		r1, =PMC_MCKR
		str		r0, [r1]

		ldr		r1, =PMC_SR											// MCK 에 대한 안정화를 위한 대기
wait_mck_stable2:
		ldr		r0,[r1]
		ands	r0,r0,#PMC_MCKRDY
        beq		wait_mck_stable2

		//
		// PCK 를 마스터 클럭으로 설정
		//
		ldr		r0, =(PMC_PRES_CLK_2|PMC_CSS_PLL_CLK)				// PCK 를 마스터 클럭으로 설정
		ldr		r1, =PMC_MCKR
		str		r0, [r1]

		ldr		r1, =PMC_SR											// MCK 에 대한 안정화를 위한 대기를  한다.
wait_mck_stable3:
		ldr		r0,[r1]
		ands	r0,r0,#PMC_MCKRDY
        beq		wait_mck_stable3

        //
        // C 프로그램의 초기화 데이터가 있는 데이터 영역( .data )를 롬에서 램으로 복사한다.
        //
		ldr		r1,	=_data_read_start
        ldr		r2, =_data_write_start
        ldr     r3, =_data_write_end
realloc_data_loop:
		cmp     r2,r3
        ldrlo   r0, [r1], #4
        strlo   r0, [r2], #4
        blo     realloc_data_loop

		//
		// C 프로그램의 비 초기화 데이터가 있는 데이터 영역(.bss)을 클리어 한다.
		//
        mov		r0,#0
		ldr		r1,=_bss_start
		ldr		r2,=_bss_end
bss_clear_loop:
		cmp    r1, r2
        strlo   r0, [r1], #4
        blo     bss_clear_loop

//		//
//		// IRQ를 인터럽트를 허가 한다.
//		//
//		mrs		r0, CPSR
//		bic		r0, r0, #0x1F
//		orr		r0, r0, #( ARM_MODE_SVC | FIRQ_DISABLE )
//		msr		CPSR_c, r0

		//
		// C main 함수로 이동한다.
		//

		ldr		lr,=exit
		ldr		r0,=main
		bx		r0

		//
		// 여기로 오면 안된다.
		//

exit:
        b    .


_boot_load_store:

//		0x203ffc 번지에 sp를 저장한다.
//		0x203ff8 번지에 bootload 재진입 위치를 저장한다.	

//		ldr			r0, =0x203ff8
//		mov			r1, lr
//		add			r1, r1, #0x10	//lr + 10은 go_module함수의 return 위치이다.
//		str			r1, [r0]

		ldr			r1, =0x203ff8
		str			r0, [r1]

		ldr			r0, =0x203ffc
		str			sp, [r0]
		
		mov		pc, lr 

//------------------------------------------------------------------------------------------------
//  IRQ 인터럽트 처리
//------------------------------------------------------------------------------------------------
IRQ:
		sub         lr, lr, #4							// 인터럽트 처리가 끝난후 복귀할 주소를 스택에 저장한다.
		stmfd       sp!, {lr}							// 이후에는 lr 즉 r14 레지스터를 임의로 사용가능하다.

		mrs         r14, SPSR							// 인터럽트 처리가 끝나후 복구해야 할 상태를 스택에 저장한다.
		stmfd       sp!, {r14}

		stmfd       sp!, {r0}							// r0 레지스터를 사용하기 위해서 r0 레지스터를 스택에 저장한다.

//		mrs		r0, CPSR								// 인터럽트를 허가 금지 시키고 IRQ 모드에서 수퍼바이저 모드로 전환한다.
//		bic		r0, r0, #0x1F							// 이 명령 이후에는 스택은 수퍼바이저 스택을 사용한다.
//		orr		r0, r0, #( ARM_MODE_SVC | IRQ_DISABLE | FIRQ_DISABLE )
//		msr		CPSR_c, r0

		ldr         r14, =AIC_IVR						// 설정된 인터럽트 백터 핸들러 주소를 r0 에 저장한다.
		ldr         r0 , [r14]
		str         r14, [r14]							// <-- 이 루틴이 왜 필요하지? 버그인가?


		msr         CPSR_c, #( ARM_MODE_SVC )

		stmfd       sp!, { r1-r3, r12, r14}				// 모든 레지스터를 스택에 저장한다.

		mov         r14, pc								// 이게 왜 필요하지?
		bx          r0									// 인터럽트 서비스 루틴으로 진입한다.

		ldmia       sp!, { r1-r3, r12, r14}				// 스택에 저장되었던 레지스터 값을 모두 복구한다.

//		mrs		r0, CPSR								// 인터럽트를 활성화 시키고 수퍼바이저 모드에서 IRQ 모드로 전환한다.
//		bic		r0, r0, #0x1F							// 이 명령 이후에는 스택은 수퍼바이저 스택을 사용한다.
//		orr		r0, r0, #( ARM_MODE_IRQ | IRQ_DISABLE | FIRQ_DISABLE )
//		msr		CPSR_c, r0

		msr         CPSR_c, #(IRQ_DISABLE | ARM_MODE_IRQ)

		ldr         r14, =AIC_EOICR						// 인터럽트가 종료 되었음을 알린다.
		str         r14, [r14]

		ldmia       sp!, {r0}							// R0 값을 복구 한다.

		ldmia       sp!, {r14}							// SPSR 값을 복구한다. 전체 (C,X,S,F) 상태
		msr         SPSR_cxsf, r14

		ldmia       sp!, {pc}^							// 인터럽트 이전 위치로 복귀한다.

//		ldr		r3, =(LED_DS2|LED_DS3)
//		b		error_led

//------------------------------------------------------------------------------------------------
//  Reset,IRQ 이외의 인터럽트 처리
//------------------------------------------------------------------------------------------------
data_abort:
		ldr		r3, =(LED_DS1)
		b		error_led

undefined_instruction:
		ldr		r3, =(LED_DS2)
		b		error_led

software_interrupt:
		ldr		r3, =(LED_DS1|LED_DS2)
		b		error_led

prefetch_abort:
		ldr		r3, =(LED_DS3)
		b		error_led

not_used:
		ldr		r3, =(LED_DS1|LED_DS3)
		b		error_led


FIQ:
		ldr		r3, =(LED_DS1|LED_DS2|LED_DS3)
		b		error_led

error_led:

		//	LED 초기화
		ldr		r1, =(LED_DS1|LED_DS2|LED_DS3)
		ldr		r0, =PIO_PER
		str		r1, [r0]

		ldr		r0, =PIO_OER
		str		r1, [r0]

		ldr		r0, =PIO_SODR
		str		r1, [r0]

error_led3:
		ldr		r1, =(LED_DS1|LED_DS1|LED_DS2)

		// LED 점멸
		ldr		r0, =PIO_SODR
		str		r1, [r0]

		ldr     r2,=0x400
error_led1:
		subs    r2,r2,#1
		bne     error_led1

		ldr		r0, =PIO_CODR
		str		r3, [r0]

		ldr     r2,=0x400
error_led2:
		subs    r2,r2,#1
		bne     error_led2

		b		error_led3

