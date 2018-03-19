//------------------------------------------------------------------------------
// 화일명 : mem_edit.c
// 설  명 : ezload의 메모리에 관련 명령 처리 루틴이다. 
// 
// 작성자 : 유영창(frog@falinux.com) 
// 작성일 : 2007년 8월 18일
// 수 정 일 : 
// 주    의 : 
// 라이센스 : BSD
//-----------------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
// 헤더 정의
//
//------------------------------------------------------------------------------
#include <typedef.h>
#include <register.h>
#include <setup.h>

#include <console.h>
#include <stdio.h>
#include <string.h>

//------------------------------------------------------------------------------
//
// 광역 변수 정의
//
//------------------------------------------------------------------------------

static void *address = (void *) 0x0;

/*
//------------------------------------------------------------------------------
// 설명 : 메모리에 데이타 쓰기 ( 1 Byte )
// 매계 : argc    : 토큰 갯수 
//        argv    : 분리된 토큰 문자열 주소가 담겨질 배열 
// 반환 : 에러 -1  정상 0
// 주의 : 없음 
//------------------------------------------------------------------------------
int RamWriteChar (int argc, char **argv)
{

    unsigned char *ptrTo;
    int            lp;

    if( argc < 3 ) 
    {
        printf( "Argument Count Error!\n");
        return -1; 
    }

    // 써넣을 주소를 얻는다. 

    ptrTo = (unsigned char *)strtoul( argv[1], NULL, 0);

    for( lp = 2; lp < argc; lp++ )
       ptrTo[ lp - 2 ] = strtoul( argv[lp], NULL, 0);
    
   return 0;
}
//------------------------------------------------------------------------------
// 설명 : 메모리에 데이타 쓰기 ( 2 Byte ) 
// 매계 : argc    : 토큰 갯수 
//        argv    : 분리된 토큰 문자열 주소가 담겨질 배열 
// 반환 : 에러 -1  정상 0
// 주의 : 없음 
//------------------------------------------------------------------------------
int RamWriteWord (int argc, char **argv)
{
    unsigned short *ptrTo;
    int            lp;

    if( argc < 3 ) 
    {
        printf( "Argument Count Error!\n");
        return -1; 
    }

    // 써넣을 주소를 얻는다. 

    ptrTo = (unsigned short *)strtoul( argv[1], NULL, 0);

    for( lp = 2; lp < argc; lp++ )
       ptrTo[ lp - 2 ] = strtoul( argv[lp], NULL, 0);
   return 0;
}
//------------------------------------------------------------------------------
// 설명 : 메모리에 데이타 쓰기 ( 3 Byte ) 
// 매계 : argc    : 토큰 갯수 
//        argv    : 분리된 토큰 문자열 주소가 담겨질 배열 
// 반환 : 에러 -1  정상 0
// 주의 : 없음 
//------------------------------------------------------------------------------
int RamWriteLong (int argc, char **argv)
{

    unsigned long *ptrTo;
    int            lp;

    if( argc < 3 ) 
    {
        printf( "Argument Count Error!\n");
        return -1; 
    }

    // 써넣을 주소를 얻는다. 

    ptrTo = (unsigned long *)strtoul( argv[1], NULL, 0);

    for( lp = 2; lp < argc; lp++ )
       ptrTo[ lp - 2 ] = strtoul( argv[lp], NULL, 0);

   return 0;
}
*/


//------------------------------------------------------------------------------
// 설명 : 메모리 바이트 읽기 
// 매계 : argc    : 토큰 갯수 
//        argv    : 분리된 토큰 문자열 주소가 담겨질 배열 
// 반환 : 에러 -1  정상 0
// 주의 : 없음 
//------------------------------------------------------------------------------
//0000-0000 : 06 00 00 EA 40 00 00 EA 41 00 00 EA 42 00 00 EA | ....@...A...B...
//01234567890123456789012345678901234567890123456789012345678901234567890123456789
//          1         2         3         4         5         6         7
s32 mem_read_byte(s32 argc, s8 **argv )
{
	s32 	size;
    s32 	total, lp1;
    u8 		*ptr8;
    s8    line[80], *pline;
	
	if( argc > 3 ) 
	{
		printf( "MRB [Address] [Count]\n");
        return -1;
	}
	
	size    = 16;

    switch( argc )
    {
      case  3 : size = strtoul( argv[2], NULL, 0);    // 시작 주소와 카운트가 있을때 
                if( size < 0 ) size *= -1;
      case  2 : address = (void *) strtoul( argv[1], NULL, 0);      // 시작 주소만 주어 졌을때  
    } 

    if (address == -1)
    {
		printf( "MRB [Address] [Count]\n");
        return -1;
    }
    
    ptr8 = address;
    
    total = 0;
    pline = &line[0];
    
    while( total < size )
    {
    	if( total % 16 == 0 )
    	{
    		memset( line, ' ', sizeof( line ) );
    		pline = &line[0];
    		
        	pline += sprintf( pline, "%04X-%04X : ",  (((unsigned int)ptr8)>>16)&0xFFFF,
                                                       ((unsigned int)ptr8)     &0xFFFF  );
    	}
    	
        pline += sprintf( pline, "%02X ", *ptr8 );

        if      ( *ptr8 < ' ' ) line[62+(total%16)] = '.';
        else if ( *ptr8 > '~' ) line[62+(total%16)] = '.';
        else                    line[62+(total%16)] = *ptr8;

    	total++;
    	ptr8++;
    	
    	if( ( total % 16 == 0 ) || ( total >= size ) )
    	{
    		for( lp1 = 0; lp1 < sizeof( line ); lp1++ ) 
    			if( line[lp1] == 0 )  line[lp1] = ' ';
    		line[60] = '|';
    		line[79] = 0;
    		printf( "%s\n", line );
    	}	
    }

    address = (void *) ptr8;
    
	return 0;
}

//------------------------------------------------------------------------------
// 설명 : 메모리 워드 읽기 
// 매계 : argc    : 토큰 갯수 
//        argv    : 분리된 토큰 문자열 주소가 담겨질 배열 
// 반환 : 에러 -1  정상 0
// 주의 : 없음 
//------------------------------------------------------------------------------
s32 mem_read_word(s32 argc, s8 **argv )
{
	s32 	size;
    s32 	total, lp1;
    u8 		*ptr8;
    u16		*ptr16;
    s8    line[80], *pline;
	
	if( argc > 3 ) 
	{
		printf( "MRB [Address] [Count]\n");
        return -1;
	}
	
	size    = 16;

    switch( argc )
    {
      case  3 : size = strtoul( argv[2], NULL, 0);    // 시작 주소와 카운트가 있을때 
      			size = size * 2;
                if( size < 0 ) size *= -1;
      case  2 : address = (void *) strtoul( argv[1], NULL, 0);      // 시작 주소만 주어 졌을때  
    } 

    if (address == -1)
    {
		printf( "MRB [Address] [Count]\n");
        return -1;
    }
    
    ptr8  = address;
    ptr16 = address;
    
    total = 0;
    pline = &line[0];
    
    while( total < size )
    {
    	if( total % 16 == 0 )
    	{
    		memset( line, ' ', sizeof( line ) );
    		pline = &line[0];
    		
        	pline += sprintf( pline, "%04X-%04X : ",  (((unsigned int)ptr8)>>16)&0xFFFE,
                                                       ((unsigned int)ptr8)     &0xFFFE  );
    	}
    	
    	if( total % 2 == 0 )
    	{	
        	pline += sprintf( pline, "%04X ", *ptr16 );
        	ptr16++;
		}
		
        if      ( *ptr8 < ' ' ) line[62+(total%16)] = '.';
        else if ( *ptr8 > '~' ) line[62+(total%16)] = '.';
        else                    line[62+(total%16)] = *ptr8;

    	total++;
    	ptr8++;
    	
    	if( ( total % 16 == 0 ) || ( total >= size ) )
    	{
    		for( lp1 = 0; lp1 < sizeof( line ); lp1++ ) 
    			if( line[lp1] == 0 )  line[lp1] = ' ';
    		line[60] = '|';
    		line[79] = 0;
    		printf( "%s\n", line );
    	}	
    }

    address = (void *) ptr8;
    
	return 0;
	
}

//------------------------------------------------------------------------------
// 설명 : 메모리 롱 읽기 
// 매계 : argc    : 토큰 갯수 
//        argv    : 분리된 토큰 문자열 주소가 담겨질 배열 
// 반환 : 에러 -1  정상 0
// 주의 : 없음 
//------------------------------------------------------------------------------
s32 mem_read_long(s32 argc, s8 **argv )
{
	s32 	size;
    s32 	total, lp1;
    u8 		*ptr8;
    u32		*ptr32;
    s8    line[80], *pline;
	
	if( argc > 3 ) 
	{
		printf( "MRB [Address] [Count]\n");
        return -1;
	}
	
	size    = 16;

    switch( argc )
    {
      case  3 : size = strtoul( argv[2], NULL, 0);    // 시작 주소와 카운트가 있을때 
      			size = size * 4;
                if( size < 0 ) size *= -1;
      case  2 : address = (void *) strtoul( argv[1], NULL, 0);      // 시작 주소만 주어 졌을때  
    } 
    
    if (address == -1)
    {
		printf( "MRB [Address] [Count]\n");
        return -1;
    }

    ptr8  = address;
    ptr32 = address;
    
    total = 0;
    pline = &line[0];
    
    while( total < size )
    {
    	if( total % 16 == 0 )
    	{
    		memset( line, ' ', sizeof( line ) );
    		pline = &line[0];
    		
        	pline += sprintf( pline, "%04X-%04X : ",  (((unsigned int)ptr8)>>16)&0xFFFE,
                                                       ((unsigned int)ptr8)     &0xFFFE  );
    	}
    	
    	if( total % 4 == 0 )
    	{	
        	pline += sprintf( pline, "%08X ", *ptr32 );
        	ptr32++;
		}
		
        if      ( *ptr8 < ' ' ) line[62+(total%16)] = '.';
        else if ( *ptr8 > '~' ) line[62+(total%16)] = '.';
        else                    line[62+(total%16)] = *ptr8;

    	total++;
    	ptr8++;
    	
    	if( ( total % 16 == 0 ) || ( total >= size ) )
    	{
    		for( lp1 = 0; lp1 < sizeof( line ); lp1++ ) 
    			if( line[lp1] == 0 )  line[lp1] = ' ';
    		line[60] = '|';
    		line[79] = 0;
    		printf( "%s\n", line );
    	}	
    }

    address = (void *) ptr8;
    
	return 0;
}

