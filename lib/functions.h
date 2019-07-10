
/*
TYPE  HEADER
NAME  functions.h
PATH  ./lib/functions.h
*/

#ifndef TRADE_MANAGER_SYSTEM_FUNCTIONS_H
#define TRADE_MANAGER_SYSTEM_FUNCTIONS_H

#include "basic_def.h"

int is_number(char* str);
int get_max(int x, int y);

int is_number(char *str)
{   //判断当前字符串是否是纯数字
    int len = (int)strlen(str);
    EXIT_CHECK(len > 0);

    int start_pos;

    start_pos = ((str[0] == '-') | (str[0] == '+')) ? 1 : 0;
    int is_not_char = !((start_pos == 1) & (len == 1));
    EXIT_CHECK(is_not_char);

    for (int i = start_pos; i < len; i++) {
        EXIT_CHECK(isdigit(str[i]));
    }
    return 1;
}

int get_max(int x, int y)
{
    return x >= y ? x : y;
}

#endif //TRADE_MANAGER_SYSTEM_FUNCTIONS_H
