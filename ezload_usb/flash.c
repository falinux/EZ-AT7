//------------------------------------------------------------------------------
// 화일명 : flash.c
// 설  명 : ezload의 flash메모리에 관련 명령 처리 루틴이다.
//
// 작성자 : 이영민
// 작성일 : 2007년 5월 25일
// 저작권 :
// 주  의 : 수정 오재경
//------------------------------------------------------------------------------

#include <typedef.h>
#include <register.h>
#include <setup.h>

#include <console.h>
//#include <usb_console.h>
#include <stdio.h>
#include <string.h>
#include <irq.h>
#include <flash.h>

RAMFUNC void flash_init( void )
{
	MC_FMR = MC_FMCN_VAL72 | MC_FWS_1FWS ;
}

RAMFUNC s32 flash_ready(void)
{
	u32 status = 0;

	// Wait the end of command
	while ( ( status & MC_FRDY ) != MC_FRDY )		
	{
		status = MC_FSR;
	}

	return (s32)status;
}

#define LOCK_REGION_PAGES	(64)
#define LOCK_PAGE(p)		( ((p)/LOCK_REGION_PAGES)*LOCK_REGION_PAGES )

RAMFUNC s32 flash_page_write(u32 flash_dest_addr, s32 size, u32 * src)
{
	u32 i, page, status;
	u32 * pflash;
	u32   irq_state;

	pflash = (u32*)flash_dest_addr;

	flash_init();

	// Get the Flash page number
	page = ((flash_dest_addr - (unsigned int)ADDR_FLASH ) /FLASH_PAGE_SIZE_BYTE);

	// unlock
#if 1
	irq_state = irq_disable();
	  MC_FCR = WRITE_PROTECTION_KEY | (MC_PAGEN & ( LOCK_PAGE(page) <<8))| MC_FCMD_UNLOCK ;  //* Write the unlock page command
	  status = flash_ready();		// Wait the end of command
	irq_restore( irq_state );
	if ( status & MC_LOCKE ) {
		printf("status error MC_FSR=%08x\n", status );
	}
#endif
	//printf( "page=%d (%d) ofs=0x%04x\n", page,  LOCK_PAGE(page), flash_dest_addr - (unsigned int)ADDR_FLASH );

	// copy the new value
	for(i=0; (i < FLASH_PAGE_SIZE_BYTE) & (size > 0); i++, pflash++,src++,size-=4)
	{
		*pflash=*src;
	}
	// programming
	irq_state = irq_disable();
	  MC_FCR = WRITE_PROTECTION_KEY | (MC_PAGEN & (page <<8))| MC_FCMD_START_PROG ;  //* Write the prog page command
	  status = flash_ready();		// Wait the end of command
	irq_restore( irq_state );

	// Check the result
	if ( (status & ( MC_PROGE | MC_LOCKE ))!=0)		// 
	{
		printf("status error MC_FSR=%08x\n", status );
		return -1;
	}
	return 0;
}

RAMFUNC s32 flash_write_all(u32 flash_dest_addr, s32 size, u32 * pbuff)
{
	s32	next, status;
	u32	dest, page;
	u32	*psrc;

	printf( " 1) MC_FSR=%08x\n", MC_FSR );
	printf( " flash write start " );

	dest = flash_dest_addr;
	psrc = pbuff;
	status = 0;	

	//while((status == 0) && (size > 0))
	while( size > 0 )
	{
		//* Check the size
		if(size <= FLASH_PAGE_SIZE_BYTE)
			next = size;
		else
			next = FLASH_PAGE_SIZE_BYTE;
		page = (dest - (unsigned int)ADDR_FLASH ) / FLASH_PAGE_SIZE_BYTE;

		//* Write page and get status
		status = flash_page_write(dest, next, psrc);
		// * get next page param
		size -= next;
		psrc += FLASH_PAGE_SIZE_BYTE/4;
		dest +=  FLASH_PAGE_SIZE_BYTE;
		printf("." );

		if (status) break;
	}
	
	printf( " flash write end\n" );
	printf( " 2) MC_FSR=%08x\n", MC_FSR );
	return status;
}

#if 0
RAMFUNC s32 flash_erase_all( void )
{
	u32   irq_state;
	u32   page, status;

	flash_init(0);
	printf( "erase-all start " );
	irq_state = irq_disable();

	for (page=0; page<1024; page+=64) {
		
		MC_FCR = WRITE_PROTECTION_KEY | (MC_PAGEN & (LOCK_PAGE(page)<<8))| MC_FCMD_UNLOCK ;
		status = flash_ready();		// Wait the end of command

		if ( status & MC_LOCKE ) 
			 printf("status error page=%d MC_FSR=%08x\n", page, status );		
		
		else printf( "." );
	}

	MC_FCR = WRITE_PROTECTION_KEY | MC_FCMD_ERASE_ALL ;
	status = flash_ready();		// Wait the end of command

	irq_restore( irq_state );

	if ( status & MC_LOCKE ) 
		printf("status error erase-all MC_FSR=%08x\n", status );		

	printf( "\nerase-all end\n" );
	return 0;
}
#else
RAMFUNC s32 flash_erase_all( void )
{
	printf( "..not included\n" );
}
#endif

RAMFUNC s32 flash_lock_info( s32 argc, s8 **argv )
{
	u32   addr, lock_region, page, fsr;

	addr = ADDR_FLASH;
	page = 0;
	fsr  = MC_FSR;
	
	printf( "\n MC_FSR=0x%08x\n", fsr );
	fsr >>= 16;

	if( argc == 1 )
	{
		for ( lock_region=0; lock_region<16; lock_region++ ) {
			printf( " %2d:0x%06x page=%3d:%3d lock=%d\n", lock_region, addr, page, page+63, fsr&0x1 );
			addr += (64*256);
			page += 64;
			fsr >>= 1;
		}
	}

	if( argc >= 3 )
	{
		u32 irq_state, cmd;
		u32 lock_region = strtoul( argv[2], NULL, 0 );

		flash_init();

		if( 0 == strcmp( argv[1], "unlock" ) ) {
			printf( " >> unlock %d ", lock_region );
			cmd = WRITE_PROTECTION_KEY | (MC_PAGEN & ( (lock_region*LOCK_REGION_PAGES)<<8))| MC_FCMD_UNLOCK ;
		}
		else if( 0 == strcmp( argv[1], "lock" ) ) {
			printf( " >> lock %d ", lock_region );
			cmd = WRITE_PROTECTION_KEY | (MC_PAGEN & ( (lock_region*LOCK_REGION_PAGES)<<8))| MC_FCMD_LOCK ;
		} else {
			return 0;
		}

		irq_state = irq_disable();
		  MC_FCR = cmd;
		  flash_ready();
		irq_restore( irq_state );
	}

	printf ("\n\n");
	return 0;
}

