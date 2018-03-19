//------------------------------------------------------------------------------
// 파 일 명 : typedef.h
// 프로젝트 : ez-jtag
// 설    명 : 타입 정의에 관한 헤더 팡리 
// 작 성 자 : 유영창(frog@falinux.com)
// 작 성 일 : 2007년 5월 6일
// 수 정 일 : 
// 수 정 일 : 
// 주    의 : 
// 라이센스 : BSD
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

