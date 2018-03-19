//------------------------------------------------------------------------------
// 화일명 : mem_edit.h
// 설  명 : ezload의 메모리에 관련 명령 처리 루틴이다. 
// 
// 작성자 : 이덕형(elenyuri@empal.com)
// 작성일 : 2007년 08월 18일
// 저작권 : 
// 주  의 : 
// 라이센스 : BSD
//------------------------------------------------------------------------------

#ifndef _MEM_EDIT_HEADER_
#define _MEM_EDIT_HEADER_

// External fuction description
extern s32 mem_read_byte(s32 argc, s8 **argv );
extern s32 mem_read_word(s32 argc, s8 **argv );
extern s32 mem_read_long(s32 argc, s8 **argv );

#endif  // _MEM_EDIT_HEADER_
