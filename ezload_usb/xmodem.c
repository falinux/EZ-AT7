//------------------------------------------------------------------------------
// 화일명 : main.c
// 설  명 : ezboot에서 사용하는 crc 처리 함수 선언
//
// 작성자 : 
// 작성일 : 
// 저작권 : 
// 수정자 :	
// 수정일 : 
// 주  의 :
//------------------------------------------------------------------------------

/*
	Copyright 2001, 2002 Georges Menie (www.menie.org)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* this code needs standard functions memcpy() and memset()
   and input/output functions getc_timeover() and select_console_putc().

   the prototypes of the input/output functions are:
     int getc_timeover(unsigned short timeout); // msec timeout
     void select_console_putc(int c);

 */

#include <typedef.h>
#include <register.h>
#include <setup.h>

#include <console.h>
#include <stdio.h>
#include <string.h>
#include <timer.h>
#include <usb_serial.h>
#include <main.h>

#include <xmodem.h>
#include <crc16.h>

#define 	SOH  			0x01
#define 	STX  			0x02
#define 	EOT  			0x04
#define 	ACK  			0x06
#define 	NAK  			0x15
#define 	CAN  			0x18
#define 	CTRLZ 			0x1A
        	
#define 	DLY_1S 			1000
#define 	MAXRETRANS 		25

u8 select_console_getc( void )
{
	if( usb_serial_mode.printf_select_usb ) return usb_getc();
	return console_getc();	
}


u32 select_console_read_ok( void )
{
	if( usb_serial_mode.printf_select_usb ) return usb_read_ok();
	return console_read_ok();	
}

RAMFUNC void select_console_putc( const u8 c )
{
	if( usb_serial_mode.printf_select_usb )  usb_putc( c );
	else 					 console_putc( c );
}




static s32 getc_timeover( u32 msec )
{
	timer_set_timeover( msec );
	while( !select_console_read_ok() )
	{
		if( timer_is_timeover() )  return -2;
	}
	return select_console_getc();
}

static s32 check( s32 crc, const u8 *buf, s32 sz)
{
	if(crc) 
	{
		unsigned short crc = crc16_ccitt(buf, sz);
		unsigned short tcrc = (buf[sz]<<8)+buf[sz+1];
		if (crc == tcrc) return 1;
	}
	else 
	{
		int i;
		unsigned char cks = 0;

		for (i = 0; i < sz; ++i) cks += buf[i]; 
		if (cks == buf[sz])		return 1;
	}

	return 0;
}

static void flushinput(void)
{
	while( getc_timeover( (u32) (((DLY_1S)*3)>>1) ) >= 0 ) 	;
}

s32 xmodem_receive( u8 *dest, s32 destsz )
{
	u8 		xbuff[1030]; // 1024 for XModem 1k + 3 head chars + 2 crc + nul 
	u8 		*p;
	s32 	bufsz, crc = 0;
	u8 		trychar = 'C';
	u8 		packetno = 1;
	s32 	i, c, len = 0;
	s32 	retry, retrans = MAXRETRANS;

	while(1)
	{
		for( retry = 0; retry < 16; ++retry) 
		{
			if (trychar) select_console_putc(trychar);
			if ((c = getc_timeover((DLY_1S)<<1)) >= 0) 
			{
				switch (c) 
				{
				case SOH:
					bufsz = 128;
					goto start_recv;
				case STX:
					bufsz = 1024;
					goto start_recv;
				case EOT:
					flushinput();
					select_console_putc(ACK);
					return len; /* normal end */
				case CAN:
					if ((c = getc_timeover(DLY_1S)) == CAN) 
					{
						flushinput();
						select_console_putc(ACK);
						return -1; /* canceled by remote */
					}
					break;
				default:
					break;
				}
			}
		}
		if (trychar == 'C') { trychar = NAK; continue; }
		flushinput();
		select_console_putc(CAN);
		select_console_putc(CAN);
		select_console_putc(CAN);
		return -2; /* sync error */

	start_recv:

		if (trychar == 'C') crc = 1;
		trychar = 0;
		p = xbuff;
		*p++ = c;
		for (i = 0;  i < (bufsz+(crc?1:0)+3); ++i) 
		{
			if ((c = getc_timeover(DLY_1S)) < 0) goto reject;
			*p++ = c;
		}

		if  (xbuff[1] == (u8)(~xbuff[2]) 
		&& 	(xbuff[1] == packetno || xbuff[1] == (u8)packetno-1) 
		&&	check(crc, &xbuff[3], bufsz) ) 
		{
			if (xbuff[1] == packetno)	
			{
				register int count = destsz - len;
				if (count > bufsz) count = bufsz;
				if (count > 0) 
				{
					memcpy (&dest[len], &xbuff[3], count);
					len += count;
				}
				++packetno;
				retrans = MAXRETRANS+1;
			}
			if (--retrans <= 0) 
			{
				flushinput();
				select_console_putc(CAN);
				select_console_putc(CAN);
				select_console_putc(CAN);
				return -3; /* too many retry error */
			}
			select_console_putc(ACK);
			continue;
		}
	reject:
		flushinput();
		select_console_putc(NAK);
	}
}

/*
//------------------------------------------------------------------------------
// 설명 : 함수로 점프한다. 
// 매계 : argc    : 토큰 갯수 
//        argv    : 분리된 토큰 문자열 주소가 담겨질 배열 
// 반환 : 에러 -1  정상 0
// 주의 : 없음 
//------------------------------------------------------------------------------
int xmodem_memory(int argc, char **argv)
{
	u32  download_address;
	s32  download_size;

	if ( argc < 2 )	return -1;

	download_address = strtoul( argv[1], NULL, 0 );
	download_address = 0x31000000;

	printf( "resive address = 0x%08X:0x%08X\n", download_address, BOOT_WORK_START );
	download_size = xmodem_receive( (u8 *) download_address, 64*1024*1024 );

	if( download_size >= 0 ) printf( "XMODEM receive ok size = %d\n", download_size );
	else                     printf( "XMODEM receive error = %d\n", download_size ); 
	
	return 0;
}
*/


/*
int xmodem_transmit(unsigned char *src, int srcsz)
{
	unsigned char xbuff[1030]; // 1024 for XModem 1k + 3 head chars + 2 crc + nul 
	int bufsz, crc = -1;
	unsigned char packetno = 1;
	int i, c, len = 0;
	int retry;

	for(;;) {
		for( retry = 0; retry < 16; ++retry) {
			if ((c = getc_timeover((DLY_1S)<<1)) >= 0) {
				switch (c) {
				case 'C':
					crc = 1;
					goto start_trans;
				case NAK:
					crc = 0;
					goto start_trans;
				case CAN:
					if ((c = getc_timeover(DLY_1S)) == CAN) {
						select_console_putc(ACK);
						flushinput();
						return -1; // canceled by remote 
					}
					break;
				default:
					break;
				}
			}
		}
		select_console_putc(CAN);
		select_console_putc(CAN);
		select_console_putc(CAN);
		flushinput();
		return -2; // no sync 

		for(;;) {
		start_trans:
			xbuff[0] = SOH; bufsz = 128;
			xbuff[1] = packetno;
			xbuff[2] = ~packetno;
			c = srcsz - len;
			if (c > bufsz) c = bufsz;
			if (c >= 0) {
				memset (&xbuff[3], 0, bufsz);
				if (c == 0) {
					xbuff[3] = CTRLZ;
				}
				else {
					memcpy (&xbuff[3], &src[len], c);
					if (c < bufsz) xbuff[3+c] = CTRLZ;
				}
				if (crc) {
					unsigned short ccrc = crc16_ccitt(&xbuff[3], bufsz);
					xbuff[bufsz+3] = (ccrc>>8) & 0xFF;
					xbuff[bufsz+4] = ccrc & 0xFF;
				}
				else {
					unsigned char ccks = 0;
					for (i = 3; i < bufsz+3; ++i) {
						ccks += xbuff[i];
					}
					xbuff[bufsz+3] = ccks;
				}
				for (retry = 0; retry < MAXRETRANS; ++retry) {
					for (i = 0; i < bufsz+4+(crc?1:0); ++i) {
						select_console_putc(xbuff[i]);
					}
					if ((c = getc_timeover(DLY_1S)) >= 0 ) {
						switch (c) {
						case ACK:
							++packetno;
							len += bufsz;
							goto start_trans;
						case CAN:
							if ((c = getc_timeover(DLY_1S)) == CAN) {
								select_console_putc(ACK);
								flushinput();
								return -1; // canceled by remote 
							}
							break;
						case NAK:
						default:
							break;
						}
					}
				}
				select_console_putc(CAN);
				select_console_putc(CAN);
				select_console_putc(CAN);
				flushinput();
				return -4; // xmit error 
			}
			else {
				for (retry = 0; retry < 10; ++retry) {
					select_console_putc(EOT);
					if ((c = getc_timeover((DLY_1S)<<1)) == ACK) break;
				}
				flushinput();
				return (c == ACK)?len:-5;
			}
		}
	}
}
*/

/*
#ifdef TEST_XMODEM_RECEIVE
int main(void)
{
	int st;

	printf ("Send data using the xmodem protocol from your terminal emulator now...\n");
	// the following should be changed for your environment:
	//   0x30000 is the download address,
	//   65536 is the maximum size to be written at this address
	//
	st = xmodemReceive((char *)0x30000, 65536);
	if (st < 0) {
		printf ("Xmodem receive error: status: %d\n", st);
	}
	else  {
		printf ("Xmodem successfully received %d bytes\n", st);
	}

	return 0;
}
#endif
#ifdef TEST_XMODEM_SEND
int main(void)
{
	int st;

	printf ("Prepare your terminal emulator to receive data now...\n");
	// the following should be changed for your environment:
	//   0x30000 is the download address,
	//   12000 is the maximum size to be send from this address
	//
	st = xmodemTransmit((char *)0x30000, 12000);
	if (st < 0) {
		printf ("Xmodem transmit error: status: %d\n", st);
	}
	else  {
		printf ("Xmodem successfully transmitted %d bytes\n", st);
	}

	return 0;
}
#endif

*/   

