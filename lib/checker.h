
/*
TYPE  HEADER
NAME  checker.h
PATH  ./lib/checker.h
*/

#ifndef TRADE_MANAGER_SYSTEM_CHECKER_H
#define TRADE_MANAGER_SYSTEM_CHECKER_H

#include "basic_def.h"
#include "functions.h"

int legal_check_return_num(char *str, int lower, int upper);
int legal_check_name(char *str);
int legal_check_pw(char* str);
int legal_check_keyword(char* str);
int legal_check_yon(char *str);
int check_MD5(const unsigned* a, const unsigned* b);

int legal_check_return_num(char *str, int lower, int upper)
{
    if (is_number(str) == 0) {
        return ERROR;
    }

    int ret = atoi(str);
    if (ret >= lower && ret <= upper) {
        return ret;
    }

    return ERROR;
}

int legal_check_name(char *str)
{
    int len = (int)strlen(str);
    if (len < 3 || len > name_max_length) return 0;
    for (int i = 0; i < len; i++) {
        char cur = str[i];
        int name_ok = 0;
        name_ok |= isdigit(cur);
        name_ok |= isupper(cur);
        name_ok |= islower(cur);
        name_ok |= (cur == '_');
        EXIT_CHECK(name_ok);
    }
    return 1;
}

int legal_check_pw(char* str)
{
    int len = (int)strlen(str);
    if (len < 8 || len > 16) return 0;

    int has_dg = 0;
    int has_lc = 0;
    int has_uc = 0;
    int has_sp = 0;

    for (int i = 0; i < len; i++) {
        char cur = str[i];
        if (cur < ' ' || cur > 126) {
            return 0;
        }
        has_dg |= isdigit(cur);
        has_lc |= islower(cur);
        has_uc |= isupper(cur);
        has_sp |= (has_dg | has_lc | has_uc | has_sp == 0);
    }

    if (has_dg + has_lc + has_uc + has_sp < 2) {
        return 0;
    }

    return 1;
}

int legal_check_keyword(char *str)
{
    int len = (int)strlen(str);
    if (len > name_max_length) return 0;
    for (int i = 0; i < len; i++) {
        char cur = str[i];
        int kw_ok = 0;
        kw_ok |= isdigit(cur);
        kw_ok |= isupper(cur);
        kw_ok |= islower(cur);
        kw_ok |= (cur == '_');
        kw_ok |= (cur == '?');
        kw_ok |= (cur == '*');
        EXIT_CHECK(kw_ok);
    }
    return 1;

}

int legal_check_yon(char *str)
{
    int len = (int)strlen(str);

    if (len < 1 || len > 3) {
        return 0;
    }

    if (len == 1) {
        if (str[0] == 'y' || str[0] == 'Y') return 1;
        if (str[0] == 'n' || str[0] == 'N') return 1;
    }
    else if (len == 2) {
        if (str[0] != 'n' && str[0] != 'N') return 0;
        if (str[1] != 'o' && str[1] != 'O') return 0;
        return 1;
    }
    else {
        if (str[0] != 'y' && str[0] != 'Y') return 0;
        if (str[1] != 'e' && str[1] != 'E') return 0;
        if (str[2] != 's' && str[2] != 'S') return 0;
        return 1;
    }

    return 0;
}

int check_MD5(const unsigned* a, const unsigned* b)
{
    for (int i = 1; i <= 4; i++) {
        EXIT_CHECK(a[i] == b[i]);
    }
    return 1;
}

#endif //TRADE_MANAGER_SYSTEM_CHECKER_H
