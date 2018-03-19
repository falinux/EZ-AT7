//------------------------------------------------------------------------------
// �� �� �� : typedef.h
// ������Ʈ : ez-jtag
// ��    �� : Ÿ�� ���ǿ� ���� ��� �θ� 
// �� �� �� : ����â(frog@falinux.com)
// �� �� �� : 2007�� 5�� 6��
// �� �� �� : 
// �� �� �� : 
// ��    �� : 
// ���̼��� : BSD
//------------------------------------------------------------------------------

#ifndef _TYPEDEF_HEADER_
#define _TYPEDEF_HEADER_

typedef unsigned char  u8;
typedef   signed char  s8;
typedef unsigned short u16;
typedef   signed short s16;
typedef unsigned long  u32;
typedef   signed long  s32;

//typedef unsigned char bool;

typedef enum
{
	FALSE = 0,
	TRUE = 1
}bool;

#define RAMFUNC __attribute__ ((long_call, section (".fastrun")))

#endif  // _TYPEDEF_HEADER_

