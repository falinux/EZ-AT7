//------------------------------------------------------------------------------
// �� �� �� : console.c
// ������Ʈ : 
// ��    �� : �ø��� ó�� 
// �� �� �� : ����â(frog@falinux.com)
// �� �� �� : 2007�� 5�� 6��
// �� �� �� : �����(freefrug@falinux.com) DMA �������� ����
// �� �� �� : 
// ��    �� : 
// ���̼��� : BSD
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
// ���� ���� ����
//------------------------------------------------------------------------------
static u8    rx_buf[RX_QUEUE_SIZE];
static u8    tx_buf[TX_SIZE];
static u32   rx_offset;

#if USE_DBGU_DMA

#else

static u32   rxq_head;
static u32   rxq_tail;

//------------------------------------------------------------------------------
// ���� : �ܼ� ��ġ�� ���� ���ͷ�Ʈ �ڵ鷯
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
// ���� : �ܼ� ��ġ�� �ʱ�ȭ �Ѵ�. 
// �Ű� : baudrate : ���ۼӵ�
// ���� : ������ �׻� none parity, 8 bit data, 1 stop �̴�. 
//------------------------------------------------------------------------------
void console_init( u32 baudrate )
{
	u32	baud_value;

	// ��������Ʈ ���	
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
	// rx-dma ����
	DBGU_RPR  = rx_buf;
	DBGU_RCR  = RX_QUEUE_SIZE;
	
	DBGU_RNPR = rx_buf; // + RX_QUEUE_SIZE;
	DBGU_RNCR = 0;

	DBGU_PTCR = PDC_RXTEN;
	
	rx_offset = 0;

#else
	// ���ͷ�Ʈ 	
	DBGU_IER    = US_RXRDY;
	
	// ���ͷ�Ʈ �ڵ鷯 ��� 
	irq_request( ID_SYS, AIC_SRCTYPE_INT_HIGH_LEVEL, console_irq_handler ); // ���ͷ�Ʈ �ڵ鷯 ���
	irq_active( ID_SYS );                   								// ���ͷ�Ʈ �㰡

	// rx ť ���� ���� �ʱ�ȭ 
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
// ���� : �ܼ� ��ġ�� USB �� ���ؼ� �� �ʱ�ȭ �Ѵ�. 
// �Ű� : baudrate : ���ۼӵ�
//        parity   : 0 NO_PARITY   
//                   1 ODD_PARITY  
//                   2 EVEN_PARITY 
//                   3 MARK_PARITY 
//                   4 SPACE_PARITY
//        stop     : 0 1_STOP_BITS  
//                   1 1_5_STOP_BITS
//                   2 2_STOP_BITS  
//        datasize 
// ���� : stop �ɼǰ� datasize �� ���õȴ�. 
//------------------------------------------------------------------------------
void console_init_by_usb( u32 baudrate, u32 parity, u32 stop, u32 datasize )
{
	u32	baud_value;
	u32	option_value;
	
	// ��������Ʈ ���	
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
// ���� : �ܼ� ��ġ�� �ѹ��ڸ� ���� �����Ѱ� üũ �Ѵ�.
// ��ȯ : 0 : ���� �Ұ��� 
//		0�� �ƴϸ� ���� ����
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
// ���� : �ܼ� ��ġ�� �ѹ��ڸ� �����Ѵ�.
// �Ű� : c : ������ ���� 
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
// ���� : ���ŵ� ���ڰ� �ִ°��� Ȯ���Ѵ�.
// ��ȯ : 0 : ���ŵ� ���ڰ� ����. 
//		0�� �ƴϸ� ���ŵ� ���ڰ� �ִ�
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
// ���� : ���ŵ� ���ڸ� ��´�. 
// ��ȯ : ���ŵ� ����
//------------------------------------------------------------------------------
u8  console_getc( void )
{
#if USE_DBGU_DMA
	u8  *ptr, rtn;
	
	while( DBGU_RCR == (RX_QUEUE_SIZE-rx_offset) );
	
	ptr = DBGU_RPR - (RX_QUEUE_SIZE - DBGU_RCR);
	rtn = ptr[rx_offset++];
	
	// ������ 1/2 �� �������ٸ�	
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
// ���� : �ø���� ��Ʈ���� �����Ѵ�.
// �Ű� : c : ������ ���� 
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
// ���� : �ø���� ��Ʈ���� �޴´�.
// �Ű� : c : ������ ���� 
//------------------------------------------------------------------------------
int console_gets( u8 *buf, int cnt )
{
	int  rc;
	u8  *ptr;
	
	if ( DBGU_RCR == RX_QUEUE_SIZE ) return 0;

	// dma �� ���߰�
	DBGU_PTCR = PDC_RXTDIS;

	// 2���� ������ ����Ÿ�� �����ϴ� ���۸� �O�´�.
	// ����Ÿ�� �������� �ʴ� ���۸� DMA �� �����Ѵ�.
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
	
	// dma �� ���۽�Ų��.
	DBGU_PTCR = PDC_RXTEN;

	// ���ۿ��� console_getc() �Լ��� ����Ÿ�� �������ٸ�
	rc  -= rx_offset;
	ptr += rx_offset;
	
	// ���ۿ� �����Ѵ�.
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

