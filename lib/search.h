
/*
TYPE  HEADER
NAME  search.h
PATH  ./lib/search.h
*/

#ifndef TRADE_MANAGER_SYSTEM_SEARCH_H
#define TRADE_MANAGER_SYSTEM_SEARCH_H

#include "basic_def.h"
#include "functions.h"

int  has_wildcard;               // 是否含有通配符
int  ord[max_goods_num];
char inp[name_max_length];
char low_name[name_max_length];  // 全改为小写的商品名
int  inp_fail[name_max_length];  // fail数组
int  d[name_max_length][name_max_length];  // 递推数组
double simity[max_goods_num];    // similarity 相似度

int  cmp_by_sim(const void* a, const void* b);
void convert_to_lower(char*dest, const char* src);
void get_fail(char *P, int *f);
int  KMP(char *T, char *P, int *f);
int  LCS(char* a, char* b);
int  wild_match(char* a, char* b);
int  main_search(char* ori_inp, int start_ord, int kw_num, int* result);

int cmp_by_sim(const void* a, const void* b)
{
    double delta = (simity[*(int*)b] - simity[*(int*)a]);
    return delta > 0 ? 1 : -1;
}

void convert_to_lower(char*dest, const char* src)
{
    int len = (int)strlen(src);
    for (int i = 0; i < len; i++) {
        dest[i] = isupper(src[i]) ? (char)(src[i] - 'A' + 'a') : src[i];
    }
    dest[len] = '\0';
}

void get_fail(char *P, int *f)
{
    int m = (int)strlen(P);
    f[0] = 0, f[1] = 0;
    for (int i = 1; i < m - 1; i++) {
        int j = f[i];
        while (j && P[i] != P[j]) {
            j = f[j];
        }
        f[i + 1] = P[i] == P[j] ? j + 1 : 0;
    }
}

int KMP(char *T, char *P, int *f)
{
    int n = (int)strlen(T), m = (int)strlen(P);
    if (n < m) {
        return 0;
    }

    get_fail(P, f);

    int j = 0, res = 0;
    for (int i = 0; i < n; i++) {
        while (j && P[j] != T[i]) {
            j = f[j];
        }
        if (P[j] == T[i]) {
            j++;
        }
        if (j == m) {
            res++;
        }
    }

    return res;
}

int LCS(char* a, char* b)
{
    int len_a = (int)strlen(a), len_b = (int)strlen(b);

    memset(d, 0, sizeof(d));
    if (a[0] == b[0]) {
        d[0][0] = 1;
    }

    if (len_a > 1 && a[1] == b[0]) {
        d[1][0] = 1;
    }
    if (len_b > 1 && a[0] == b[1]) {
        d[0][1] = 1;
    }

    for (int i = 1; i < len_a; i++) {
        for (int j = 1; j < len_b; j++) {
            d[i][j] = get_max(d[i - 1][j], d[i][j - 1]);
            if (a[i] == b[j]) {
                d[i][j] = get_max(d[i][j], d[i - 1][j - 1] + 1);
            }
        }
    }

    return d[len_a - 1][len_b - 1];
}

int wild_match(char* a, char* b) {      // a为含有通配符* ?的串
    int len_a = (int)strlen(a), len_b = (int)strlen(b);

    for (int i = 0; i <= len_b; i++)
        d[0][i] = 1;
    for (int i = 0; a[i] == '*'; i++)
        d[i + 1][0] = 1;

    for (int i = 0; i < len_a; i++)
        for (int j = 0; j < len_b; j++)
            if (a[i] == '*')
                d[i + 1][j + 1] = d[i][j + 1] | d[i][j] | d[i + 1][j];
            else if (a[i] == '?')
                d[i + 1][j + 1] = d[i][j];
            else
                d[i + 1][j + 1] = d[i][j] & (a[i] == b[j]);
    
    for (int i = 1; i <= len_b; i++) {
        if (d[len_a][i])
            return 1;
    }

    return 0;
}

int main_search(char* ori_inp, int start_ord, int kw_num, int* result)
{
    int len_inp = (int)strlen(ori_inp);

    convert_to_lower(inp, ori_inp);

    has_wildcard = 0;
    for (int i = 0; i < len_inp; i++) {
        if (inp[i] == '*' || inp[i] == '?') {
            has_wildcard = 1;
            break;
        }
    }

    if (has_wildcard == 0) {
        get_fail(inp, inp_fail);
    }

    for (int i = 1; i <= total_goods_cnt; i++) {

        if (start_ord == 1 && i == kw_num) {
            continue;
        }
        if (goods[i].deleted == 1) {
            continue;
        }

        convert_to_lower(low_name, goods[i].name);
        int len_str = (int)strlen(low_name);
        simity[i] = 0;
        if (has_wildcard == 0) {		// 不含有通配符
            int kmp_res = KMP(low_name, inp, inp_fail);
            if (kmp_res == 0) {
                int match_lcs = LCS(inp, low_name);
                simity[i] = match_lcs * 0.8 / len_inp;
            }
            else {
                simity[i] = 0.9;
                simity[i] += ((double)kmp_res / 100);
                simity[i] -= (double)(len_str - len_inp) / (len_str * 500);
                simity[i] = (simity[i] > 1.0 ? 1.0 : simity[i]);
            }
        }
        else {                   // 含有通配符
            simity[i] = wild_match(inp, low_name);
        }

        if (goods[i].stock_cnt <= 0 && simity[i] >= 0.3) {
            simity[i] = 0.3;
        }
    }

    for (int i = 1; i <= total_goods_cnt; i++) {
        ord[i] = i;
    }

    qsort(ord + 1, (unsigned)total_goods_cnt, sizeof(int), cmp_by_sim);

    int j = start_ord + 1;
    int res_cnt = 0;

    for (int i = 1; i <= total_goods_cnt; i++, j++) {

        int cur = ord[i];
        if (simity[cur] < 0.25) {   // 若相似度过低，则忽略
            break;
        }

        print_search_item(j, cur);
        res_cnt++;
    }

    for (int i = 1; i <= res_cnt; i++) {
        result[i] = ord[i];
    }

    return res_cnt;
}

#endif //TRADE_MANAGER_SYSTEM_SEARCH_H
