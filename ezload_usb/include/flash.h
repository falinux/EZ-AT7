//------------------------------------------------------------------------------
// 파 일 명 : flash.h
// 프로젝트 : ez-jtag
// 설    명 : flash 헤더 파일
// 작 성 자 : 이영민(minmin20@naver.com)
// 작 성 일 : 2007년 5월 25일
// 수 정 일 : 
// 수 정 일 : 
// 주    의 : 
// 라이센스 : BSD
//------------------------------------------------------------------------------

#ifndef _FLASH_HEADER_
#define _FLASH_HEADER_

//AT91SSAM7256 Embedded Flash Define
#define FLASH_PAGE_SIZE_BYTE 	256
#define WRITE_PROTECTION_KEY  ((unsigned int) 0x5A << 24)


#ifndef __MODULE__

RAMFUNC s32 flash_page_write(u32 Flash_Address, s32 size, u32 * buff);
RAMFUNC s32 flash_write_all(u32 flash_dest_addr, s32 size, u32 * pbuff);

#else

#define flash_write_all     call._flash_write_all

#endif


#endif  // _TYPEDEF_HEADER_
