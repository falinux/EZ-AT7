/*==============================================================================================

  ȭ�ϸ� : start.S
  ��  �� : AT91SAM7S256 ���½� ȣ��Ǵ� ��ƾ

  �ۼ��� : �������̸�����(��)  ����â
  �ۼ��� : 2007�� 4�� 18��
  ��  �� :
  �ۼ��� :
  ��  �� :

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
//  ���ͷ�Ʈ  ���� ���̺�
//
//------------------------------------------------------------------------------------------------
.globl 		_start,_boot_load_store

_start:	b	reset		    		// MCU�� ���µ��� ����ȴ�.
		b	undefined_instruction	// ���ǵ��� �ʴ� ������ ���� �ν�Ʈ���Ϳ� ��ġ�Ǿ����� ����ȴ�.
		b	software_interrupt      // ����Ʈ�������� ���ͷ�Ʈ ����(SWI)�� ����Ǿ��� �� ����ȴ�.
		b	prefetch_abort			// ����Ÿ�� ���� ��ġ �Ҷ� ���� ������ �߻��ϸ� ����ȴ�.
		b	data_abort	        	// ����Ÿ ������ �߻��ϸ� ����ȴ�.
		b	not_used	        	// ������ �ʴ´�.
		b	IRQ		        		// IRQ ���ͷ�Ʈ�� �߻��Ǹ� ����ȴ�.
		b	FIQ						// IRQ ���ͷ�Ʈ���� �켱���� �ִ� ���ͷ�Ʈ�� �߻��Ǹ� ����ȴ�.

//------------------------------------------------------------------------------------------------
//
//  RESET�� �߻��ϰų� ������ ��� ������ �� ó�� ����Ǵ� ��ƾ�̴�.
//
//------------------------------------------------------------------------------------------------
reset:

		//
		// IRQ/FIQ �� �𽺿��̺� ��Ű�� IRQ ���� ��ȯ�Ѵ�.
		//
		mrs		r0, CPSR
		bic		r0, r0, #0x1F
		orr		r0, r0, #( ARM_MODE_IRQ | IRQ_DISABLE | FIRQ_DISABLE )
		msr		CPSR_c, r0

        //
        // IRQ ������ �����Ѵ�.
        //
		ldr		r1, =ADDR_STACK
		mov		sp,r1

		//
		// IRQ/FIQ �� �𽺿��̺� ��Ű�� ���۹����� ���� ��ȯ�Ѵ�.
		//
		mrs		r0, CPSR
		bic		r0, r0, #0x1F
		orr		r0, r0, #( ARM_MODE_SVC | IRQ_DISABLE | FIRQ_DISABLE )
		msr		CPSR_c, r0

        //
        // IRQ ������ �����Ѵ�.
        //
        sub     r1, r1, #IRQ_STACK_SIZE
		mov		sp,r1

		//
		// �÷��� �޸� ��� ���� ����
		//
		ldr		r0, =(MC_FMCN_VAL|MC_FWS_1FWS)						// �÷��� �޸� ��� ���� ����
		ldr		r1, =MC_FMR                                     	// 30 �Ǵ� 40 MHz �̻��� ��� 1 ����Ŭ �＼��
		str		r0, [r1]                                        	// ���� MCK �� 47923200 (MC_FMCN_VAL = 48) �̸� 1 ����ũ���� �� 50 ����Ŭ�� ������.

		//
		// ��ġ�� ������
		//
		ldr		r0, =(WDTC_WDDIS)									// ��ġ�� ������
		ldr		r1, =WDTC_WDMR
		str		r0, [r1]

		//
		// MCK Ŭ���� 47.923200 MHz ����
		//
		ldr		r0, =(CKGR_OSCOUNT_VAL|CKGR_MOSCEN)					// MCK Ŭ���� 47.923200 MHz ����
		ldr		r1, =PMC_MOR                                    	// ���� ���Ƿ����� �̳��̺�
		str		r0, [r1]                                        	// SCK = 1/32768 = 30.51 ����ũ����
    	                                                        	// ��ŸƮ�� Ÿ�� = 8 * 6 / SCK = 56 * 30.51 = 1,46484375 �̸���

		ldr		r1, =PMC_SR											// ���� OSC ���ÿ� ���� ����ȭ�� ���� ���
wait_osc_stable:
		ldr		r0,[r1]
		ands	r0,r0,#PMC_MOSCS
        beq		wait_osc_stable

		//
		// PLL ������ ���ֺ� ����
		//
		ldr		r0, =(CKGR_DIV_VAL|CKGR_PLLCOUNT_VAL|CKGR_MUL_VAL)    // PLL ������ ���ֺ� ����
		ldr		r1, =PMC_PLLR                                         // - div by 5 Fin = 3,6864 =(18,432 / 5)
		str		r0, [r1]                                              // - Mul 25+1: Fout =	95,8464 =(3,6864 *26)
                                                                      // 96 MHz ��� ������  0.16%
                                                                      // Field out NOT USED = 0
                                                                      // PLLCOUNT pll startup time estimate at : 0.844 ms
                                                                      // PLLCOUNT 28 = 0.000844 /(1/32768)

		ldr		r1, =PMC_SR											  // PLL LOCK �� ���� ����ȭ�� ���� ���
wait_lock_stable:
		ldr		r0,[r1]
		ands	r0,r0,#PMC_LOCK
        beq		wait_lock_stable

		ldr		r1, =PMC_SR											// MCK �� ���� ����ȭ�� ���� ��⸦  �Ѵ�.
wait_mck_stable1:
		ldr		r0,[r1]
		ands	r0,r0,#PMC_MCKRDY
        beq		wait_mck_stable1

		//
		// PLL Ŭ���� 2 ����
		//
		ldr		r0, =(PMC_PRES_CLK_2)								// PLL Ŭ���� 2 ����
		ldr		r1, =PMC_MCKR
		str		r0, [r1]

		ldr		r1, =PMC_SR											// MCK �� ���� ����ȭ�� ���� ���
wait_mck_stable2:
		ldr		r0,[r1]
		ands	r0,r0,#PMC_MCKRDY
        beq		wait_mck_stable2

		//
		// PCK �� ������ Ŭ������ ����
		//
		ldr		r0, =(PMC_PRES_CLK_2|PMC_CSS_PLL_CLK)				// PCK �� ������ Ŭ������ ����
		ldr		r1, =PMC_MCKR
		str		r0, [r1]

		ldr		r1, =PMC_SR											// MCK �� ���� ����ȭ�� ���� ��⸦  �Ѵ�.
wait_mck_stable3:
		ldr		r0,[r1]
		ands	r0,r0,#PMC_MCKRDY
        beq		wait_mck_stable3

        //
        // C ���α׷��� �ʱ�ȭ �����Ͱ� �ִ� ������ ����( .data )�� �ҿ��� ������ �����Ѵ�.
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
		// C ���α׷��� �� �ʱ�ȭ �����Ͱ� �ִ� ������ ����(.bss)�� Ŭ���� �Ѵ�.
		//
        mov		r0,#0
		ldr		r1,=_bss_start
		ldr		r2,=_bss_end
bss_clear_loop:
		cmp    r1, r2
        strlo   r0, [r1], #4
        blo     bss_clear_loop

//		//
//		// IRQ�� ���ͷ�Ʈ�� �㰡 �Ѵ�.
//		//
//		mrs		r0, CPSR
//		bic		r0, r0, #0x1F
//		orr		r0, r0, #( ARM_MODE_SVC | FIRQ_DISABLE )
//		msr		CPSR_c, r0

		//
		// C main �Լ��� �̵��Ѵ�.
		//

		ldr		lr,=exit
		ldr		r0,=main
		bx		r0

		//
		// ����� ���� �ȵȴ�.
		//

exit:
        b    .


_boot_load_store:

//		0x203ffc ������ sp�� �����Ѵ�.
//		0x203ff8 ������ bootload ������ ��ġ�� �����Ѵ�.	

//		ldr			r0, =0x203ff8
//		mov			r1, lr
//		add			r1, r1, #0x10	//lr + 10�� go_module�Լ��� return ��ġ�̴�.
//		str			r1, [r0]

		ldr			r1, =0x203ff8
		str			r0, [r1]

		ldr			r0, =0x203ffc
		str			sp, [r0]
		
		mov		pc, lr 

//------------------------------------------------------------------------------------------------
//  IRQ ���ͷ�Ʈ ó��
//------------------------------------------------------------------------------------------------
IRQ:
		sub         lr, lr, #4							// ���ͷ�Ʈ ó���� ������ ������ �ּҸ� ���ÿ� �����Ѵ�.
		stmfd       sp!, {lr}							// ���Ŀ��� lr �� r14 �������͸� ���Ƿ� ��밡���ϴ�.

		mrs         r14, SPSR							// ���ͷ�Ʈ ó���� ������ �����ؾ� �� ���¸� ���ÿ� �����Ѵ�.
		stmfd       sp!, {r14}

		stmfd       sp!, {r0}							// r0 �������͸� ����ϱ� ���ؼ� r0 �������͸� ���ÿ� �����Ѵ�.

//		mrs		r0, CPSR								// ���ͷ�Ʈ�� �㰡 ���� ��Ű�� IRQ ��忡�� ���۹����� ���� ��ȯ�Ѵ�.
//		bic		r0, r0, #0x1F							// �� ���� ���Ŀ��� ������ ���۹����� ������ ����Ѵ�.
//		orr		r0, r0, #( ARM_MODE_SVC | IRQ_DISABLE | FIRQ_DISABLE )
//		msr		CPSR_c, r0

		ldr         r14, =AIC_IVR						// ������ ���ͷ�Ʈ ���� �ڵ鷯 �ּҸ� r0 �� �����Ѵ�.
		ldr         r0 , [r14]
		str         r14, [r14]							// <-- �� ��ƾ�� �� �ʿ�����? �����ΰ�?


		msr         CPSR_c, #( ARM_MODE_SVC )

		stmfd       sp!, { r1-r3, r12, r14}				// ��� �������͸� ���ÿ� �����Ѵ�.

		mov         r14, pc								// �̰� �� �ʿ�����?
		bx          r0									// ���ͷ�Ʈ ���� ��ƾ���� �����Ѵ�.

		ldmia       sp!, { r1-r3, r12, r14}				// ���ÿ� ����Ǿ��� �������� ���� ��� �����Ѵ�.

//		mrs		r0, CPSR								// ���ͷ�Ʈ�� Ȱ��ȭ ��Ű�� ���۹����� ��忡�� IRQ ���� ��ȯ�Ѵ�.
//		bic		r0, r0, #0x1F							// �� ���� ���Ŀ��� ������ ���۹����� ������ ����Ѵ�.
//		orr		r0, r0, #( ARM_MODE_IRQ | IRQ_DISABLE | FIRQ_DISABLE )
//		msr		CPSR_c, r0

		msr         CPSR_c, #(IRQ_DISABLE | ARM_MODE_IRQ)

		ldr         r14, =AIC_EOICR						// ���ͷ�Ʈ�� ���� �Ǿ����� �˸���.
		str         r14, [r14]

		ldmia       sp!, {r0}							// R0 ���� ���� �Ѵ�.

		ldmia       sp!, {r14}							// SPSR ���� �����Ѵ�. ��ü (C,X,S,F) ����
		msr         SPSR_cxsf, r14

		ldmia       sp!, {pc}^							// ���ͷ�Ʈ ���� ��ġ�� �����Ѵ�.

//		ldr		r3, =(LED_DS2|LED_DS3)
//		b		error_led

//------------------------------------------------------------------------------------------------
//  Reset,IRQ �̿��� ���ͷ�Ʈ ó��
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

		//	LED �ʱ�ȭ
		ldr		r1, =(LED_DS1|LED_DS2|LED_DS3)
		ldr		r0, =PIO_PER
		str		r1, [r0]

		ldr		r0, =PIO_OER
		str		r1, [r0]

		ldr		r0, =PIO_SODR
		str		r1, [r0]

error_led3:
		ldr		r1, =(LED_DS1|LED_DS1|LED_DS2)

		// LED ����
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
