// 避免重複引用此標頭檔
#ifndef _MYREGEX_H_
#define _MYREGEX_H_

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <regex.h>


void test();
void getdata(char* buf);
void getsampletext(char* buf);

#endif