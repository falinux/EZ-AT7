//------------------------------------------------------------------------------
// �� �� �� : flash.h
// ������Ʈ : ez-jtag
// ��    �� : flash ��� ����
// �� �� �� : �̿���(minmin20@naver.com)
// �� �� �� : 2007�� 5�� 25��
// �� �� �� : 
// �� �� �� : 
// ��    �� : 
// ���̼��� : BSD
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
