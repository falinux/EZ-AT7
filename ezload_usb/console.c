//------------------------------------------------------------------------------
// 파 일 명 : console.c
// 프로젝트 : 
// 설    명 : 시리얼 처리 
// 작 성 자 : 유영창(frog@falinux.com)
// 작 성 일 : 2007년 5월 6일
// 수 정 일 : 오재경(freefrug@falinux.com) DMA 지원으로 변경
// 수 정 일 : 
// 주    의 : 
// 라이센스 : BSD
//------------------------------------------------------------------------------

#include <typedef.h>
#include <register.h>
#include <setup.h>

#include <console.h>

#define RX_QUEUE_SIZE   (256)
#define RX_QUEUE_MASK   0xff 

#define TX_SIZE         (128)

#define USE_DBGU_DMA   1

//------------------------------------------------------------------------------
// 전역 변수 선언
//------------------------------------------------------------------------------
static u8    rx_buf[RX_QUEUE_SIZE];
static u8    tx_buf[TX_SIZE];
static u32   rx_offset;

#if USE_DBGU_DMA

#else

static u32   rxq_head;
static u32   rxq_tail;

//------------------------------------------------------------------------------
// 설명 : 콘솔 장치를 수신 인터럽트 핸들러
//------------------------------------------------------------------------------
void console_irq_handler(void )
{
	u8 c;
	
	c = DBGU_RHR;
	rx_buf[rxq_head] = c;
	rxq_head++;
	rxq_head &= RX_QUEUE_MASK;
}
#endif

//------------------------------------------------------------------------------
// 설명 : 콘솔 장치를 초기화 한다. 
// 매계 : baudrate : 전송속도
// 주의 : 설정은 항상 none parity, 8 bit data, 1 stop 이다. 
//------------------------------------------------------------------------------
void console_init( u32 baudrate )
{
	u32	baud_value;

	// 보오레이트 계산	
	baud_value = (10 * MCLK/(baudrate * 16));
	if((baud_value % 10) >= 5) baud_value = (baud_value / 10) + 1;
	else                       baud_value /= 10;
	
	// clock enable
	PMC_PCER = 1 << ID_SYS;
	
	PIO_PDR  = PA10_DTXD | PA9_DRXD;   // Disable PIO
	PIO_ASR  = PA10_DTXD | PA9_DRXD;   // Enable PeripherialA
	
	DBGU_CR	 	= US_RSTRX | US_RSTTX;
	DBGU_BRGR 	= baud_value;
	DBGU_MR   	= US_PAR_NONE | US_CHMODE_NORMAL;
	DBGU_CR   	= US_RXEN | US_TXEN;

#if USE_DBGU_DMA
	// rx-dma 설정
	DBGU_RPR  = rx_buf;
	DBGU_RCR  = RX_QUEUE_SIZE;
	
	DBGU_RNPR = rx_buf; // + RX_QUEUE_SIZE;
	DBGU_RNCR = 0;

	DBGU_PTCR = PDC_RXTEN;
	
	rx_offset = 0;

#else
	// 인터럽트 	
	DBGU_IER    = US_RXRDY;
	
	// 인터럽트 핸들러 등록 
	irq_request( ID_SYS, AIC_SRCTYPE_INT_HIGH_LEVEL, console_irq_handler ); // 인터럽트 핸들러 등록
	irq_active( ID_SYS );                   								// 인터럽트 허가

	// rx 큐 버퍼 버퍼 초기화 
	rxq_head  = 0;
	rxq_tail  = 0;
#endif
	
}

/*
void console_exit( void )
{
	PMC_PCDR = 1 << ID_US0;

#if USE_DBGU_DMA

	DBGU_PTCR = PDC_TXTDIS | PDC_RXTDIS;

#else
	irq_free( ID_US0 );
	
#endif
}
*/
//------------------------------------------------------------------------------
// 설명 : 콘솔 장치를 USB 에 의해서 재 초기화 한다. 
// 매계 : baudrate : 전송속도
//        parity   : 0 NO_PARITY   
//                   1 ODD_PARITY  
//                   2 EVEN_PARITY 
//                   3 MARK_PARITY 
//                   4 SPACE_PARITY
//        stop     : 0 1_STOP_BITS  
//                   1 1_5_STOP_BITS
//                   2 2_STOP_BITS  
//        datasize 
// 주의 : stop 옵션과 datasize 는 무시된다. 
//------------------------------------------------------------------------------
void console_init_by_usb( u32 baudrate, u32 parity, u32 stop, u32 datasize )
{
	u32	baud_value;
	u32	option_value;
	
	// 보오레이트 계산	
	baud_value = (10 * MCLK/(baudrate * 16));
	if((baud_value % 10) >= 5) baud_value = (baud_value / 10) + 1;
	else                       baud_value /= 10;

	DBGU_BRGR 	= baud_value;
	
	option_value = US_CHMODE_NORMAL;
	
	// PARITY
	switch( parity )
	{
	case 0  : option_value |= US_PAR_NONE;  break; // NO_PARITY   
	case 1  : option_value |= US_PAR_ODD;   break; // ODD_PARITY  
	case 2  : option_value |= US_PAR_EVEN;  break; // EVEN_PARITY 
	case 3  : option_value |= US_PAR_MARK;  break; // MARK_PARITY 
	case 4  : option_value |= US_PAR_SPACE; break; // SPACE_PARITY
	}
	
	DBGU_MR   	= option_value;
	
	stop     = stop;
	datasize = datasize;

}

//------------------------------------------------------------------------------
// 설명 : 콘솔 장치로 한문자를 전송 가능한가 체크 한다.
// 반환 : 0 : 전송 불가능 
//		0이 아니면 전송 가능
//------------------------------------------------------------------------------
u32 console_write_ok( void )
{
#if USE_DBGU_DMA

	if ( DBGU_TCR == 0 ) return 1;
	return 0;
	
#else

    return DBGU_CSR & US_TXRDY;
#endif	
}

//------------------------------------------------------------------------------
// 설명 : 콘솔 장치로 한문자를 전송한다.
// 매계 : c : 전송할 문자 
//------------------------------------------------------------------------------
RAMFUNC void console_putc( const u8 c )
{
#if USE_DBGU_DMA
	while( DBGU_TCR != 0 );
#endif	

	while((DBGU_CSR & US_TXRDY) == 0);
	DBGU_THR = c;	
}

//------------------------------------------------------------------------------
// 설명 : 수신된 문자가 있는가를 확인한다.
// 반환 : 0 : 수신된 문자가 없다. 
//		0이 아니면 수신된 문자가 있다
//------------------------------------------------------------------------------
u32  console_read_ok( void )
{
#if USE_DBGU_DMA
	
	if ( DBGU_RCR == (RX_QUEUE_SIZE-rx_offset) ) return 0;
	return 1;
		
#else

	return rxq_head != rxq_tail;
	
#endif	
}

//------------------------------------------------------------------------------
// 설명 : 수신된 문자를 얻는다. 
// 반환 : 수신된 문자
//------------------------------------------------------------------------------
u8  console_getc( void )
{
#if USE_DBGU_DMA
	u8  *ptr, rtn;
	
	while( DBGU_RCR == (RX_QUEUE_SIZE-rx_offset) );
	
	ptr = DBGU_RPR - (RX_QUEUE_SIZE - DBGU_RCR);
	rtn = ptr[rx_offset++];
	
	// 버퍼의 1/2 를 가져갔다면	
	if ( rx_offset > (RX_QUEUE_SIZE/2) )
	{
		if ( DBGU_RCR == (RX_QUEUE_SIZE-rx_offset) )
		{
			// dma stop
			DBGU_PTCR = PDC_RXTDIS;
			
			DBGU_RPR  = rx_buf;
			DBGU_RCR  = RX_QUEUE_SIZE;
			
			// dma run
			DBGU_PTCR = PDC_RXTEN;
			
			rx_offset = 0;
		}
	}
	
	return rtn;
	
#else

	u8 c;
	
	c = rxq_buff[rxq_tail];
	rxq_tail++;
	rxq_tail &= RX_QUEUE_MASK;
	
	return c;
	
#endif	
}


//------------------------------------------------------------------------------
// 설명 : 시리얼로 스트림을 전송한다.
// 매계 : c : 전송할 문자 
//------------------------------------------------------------------------------
int console_puts( const u8 *buf, int cnt )
{
#if USE_DBGU_DMA

	while( DBGU_TCR != 0 );
	
	if ( cnt > TX_SIZE ) cnt = TX_SIZE;
	memcpy( tx_buf, buf, cnt );
	
	DBGU_TPR  = tx_buf;
	DBGU_TCR  = cnt;
	
	DBGU_TNPR = tx_buf;
	DBGU_TNCR = 0;
	
	DBGU_PTCR = PDC_TXTEN;
	
	return cnt;
#else

	int	lp ;
	for (lp=0;lp<cnt;lp++) putc(buf[lp]);

	return cnt;
#endif	
}
/*
//------------------------------------------------------------------------------
// 설명 : 시리얼로 스트림을 받는다.
// 매계 : c : 전송할 문자 
//------------------------------------------------------------------------------
int console_gets( u8 *buf, int cnt )
{
	int  rc;
	u8  *ptr;
	
	if ( DBGU_RCR == RX_QUEUE_SIZE ) return 0;

	// dma 를 멈추고
	DBGU_PTCR = PDC_RXTDIS;

	// 2개의 버퍼중 데이타가 존재하는 버퍼를 찿는다.
	// 데이타가 존재하지 않는 버퍼를 DMA 에 연결한다.
	rc  = RX_QUEUE_SIZE - DBGU_RCR;
	ptr = DBGU_RPR - rc;

	DBGU_RCR = RX_QUEUE_SIZE;
	if ( ptr == rx_buf )
	{
		DBGU_RPR = ptr + RX_QUEUE_SIZE;
	}
	else
	{
		DBGU_RPR = ptr;
	}
	
	// dma 를 동작시킨다.
	DBGU_PTCR = PDC_RXTEN;

	// 버퍼에서 console_getc() 함수로 데이타를 가져갔다면
	rc  -= rx_offset;
	ptr += rx_offset;
	
	// 버퍼에 복사한다.
	if ( cnt < rc ) rc = cnt;
	memcpy( buf, ptr, rc );
	
	rx_offset = 0;
	return rc;
}
*/


/*

#define US_RXRDY        				( 0x1 		<<  0) 				// (DBGU) RXRDY Interrupt
#define US_TXRDY        				( 0x1 		<<  1) 				// (DBGU) TXRDY Interrupt
#define US_ENDRX        				( 0x1 		<<  3) 				// (DBGU) End of Receive Transfer Interrupt
#define US_ENDTX        				( 0x1 		<<  4) 				// (DBGU) End of Transmit Interrupt
#define US_OVRE         				( 0x1 		<<  5) 				// (DBGU) Overrun Interrupt
#define US_FRAME        				( 0x1 		<<  6) 				// (DBGU) Framing Error Interrupt
#define US_PARE         				( 0x1 		<<  7) 				// (DBGU) Parity Error Interrupt
#define US_TXEMPTY      				( 0x1 		<<  9) 				// (DBGU) TXEMPTY Interrupt
#define US_TXBUFE       				( 0x1 		<< 11) 				// (DBGU) TXBUFE Interrupt
#define US_RXBUFF       				( 0x1 		<< 12) 				// (DBGU) RXBUFF Interrupt
#define US_COMM_TX      				( 0x1 		<< 30) 				// (DBGU) COMM_TX Interrupt
#define US_COMM_RX      				( 0x1 		<< 31) 				// (DBGU) COMM_RX Interrupt



#define DBGU_RPR 			__REG(0xFFFC0100)		// Receive Pointer Register
#define DBGU_RCR 			__REG(0xFFFC0104)		// Receive Counter Register
#define DBGU_TPR 			__REG(0xFFFC0108)		// Transmit Pointer Register
#define DBGU_TCR 			__REG(0xFFFC010C)		// Transmit Counter Register
#define DBGU_RNPR 			__REG(0xFFFC0110)		// Receive Next Pointer Register
#define DBGU_RNCR 			__REG(0xFFFC0114)		// Receive Next Counter Register
#define DBGU_TNPR 			__REG(0xFFFC0118)		// Transmit Next Pointer Register
#define DBGU_TNCR 			__REG(0xFFFC011C)		// Transmit Next Counter Register
#define DBGU_PTCR 			__REG(0xFFFC0120)		// PDC Transfer Control Register
#define DBGU_PTSR 			__REG(0xFFFC0124)		// PDC Transfer Status Register
*/

