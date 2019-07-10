
/*
TYPE  HEADER
NAME  type_io.h
PATH  ./lib/type_io.h
*/

#ifndef TRADE_MANAGER_SYSTEM_TYPE_IO_H
#define TRADE_MANAGER_SYSTEM_TYPE_IO_H

#include "basic_def.h"
#include "basic_io.h"
#include "checker.h"
#include "MD5.h"

void print_buy_records_list();
void print_my_goods_list();

void print_sell_records_list();

int  print_record(int order, int record_id);
int  print_goods(int order, int goods_id);
void print_search_item(int order, int goods_id);

void input_and_check_single(checker_sgl legal_check, char *str);
int  input_and_check_num(checker_num legal_check, char* str, int lower, int upper);

void circulate_confirm_name(char *str);
void circulate_confirm_password(unsigned *dest);


int print_record(int order, int record_id)
// 打印单条记录信息
{
    Record rec = record[record_id];
    Goods  gds = goods[rec.goods_num];

    printf("|%6d |%9d |%8d | %32s |%6d |%9d |%14d |%15d |\n", order,
            rec.number, rec.goods_num, gds.name, gds.price, rec.qnt, rec.buyer_num, rec.seller_num);

    return rec.qnt * gds.price;
}

void print_buy_records_list()
{
    printf(" ------------------------------------------------------------------------------------------------------------------- \n");
    printf("| order | recordID | goodsID |                       goods name | price | quantity | userID(buyer) | userID(seller) |\n");
    int fee = display_linkNode(user[id_num].record_head, print_record);
    printf(" ------------------------------------------------------------------------------------------------------------------- \n\n");
    printf(" Total consuming: %d\n\n", fee);
}

void print_sell_records_list()
{
    printf(" ------------------------------------------------------------------------------------------------------------------- \n");
    printf("| order | recordID | goodsID |                       goods name | price | quantity | userID(buyer) | userID(seller) |\n");
    int fee = display_linkNode(user[id_num].sell.record_head, print_record);
    printf(" ------------------------------------------------------------------------------------------------------------------- \n\n");
    printf(" Total turnover: %d\n\n", fee);
}

int print_goods(int order, int goods_id)
// 打印单条商品信息
{
    Goods cur = goods[goods_id];
    printf("|%6d |%8d | %32s |%6d |%8d |\n", order, cur.number, cur.name, cur.price, cur.stock_cnt);
    return 0;
}

void print_my_goods_list()
{
    printf(" ---------------------------------------------------------------------- \n");
    printf("| order | goodsID |                       goods name | price | storage |\n");
    display_linkNode(user[id_num].sell.goods_head, print_goods);
    printf(" ---------------------------------------------------------------------- \n\n");
}

void print_search_item(int order, int goods_id)
{
    Goods cur = goods[goods_id];
    printf("|%6d |%8d | %32s |%6d |%8d |%15d |\n", order,
            cur.number, cur.name, cur.price, cur.stock_cnt, cur.seller_num);
}

void input_and_check_single(checker_sgl legal_check, char* str)
// 用于单个参数输入和检查
{
    int input_ok = 0;
    while (!input_ok) {
        get_the_line(str, 1);

        if (legal_check(str)) {
            input_ok = 1;
        }
        else {
            print_error(0);
        }
    }
}

int input_and_check_num(checker_num legal_check, char* str, int lower, int upper)
// 用于单个整数输入和检查，返回输入的整数
{
    int input_ok = 0, ret = -1;
    while (!input_ok) {
        get_the_line(str, 1);
        ret = legal_check(str, lower, upper);
        if (ret != ERROR) {
            input_ok = 1;
        }
        else {
            print_error(0);
        }
    }
    return ret;
}

void circulate_confirm_name(char *str)
// cur_state = 11
{
    int feel_ok = 0;

    while (!feel_ok) {
        print_remind_message(1);
        input_and_check_single(legal_check_name, str);

        cur_state = 111;
        print_remind_message(1);

        char yes_or_no[input_max_length];
        input_and_check_single(legal_check_yon, yes_or_no);
        if (yes_or_no[0] == 'y' || yes_or_no[0] == 'Y') {
            feel_ok = 1;
        }

        cur_state = 11;
    }
}

void circulate_confirm_password(unsigned* dest)
// cur_state = 112
{
    char fir_pw[input_max_length];
    char cfm_pw[input_max_length];

    print_remind_message(1);

    while (1) {

        input_and_check_single(legal_check_pw, fir_pw);

        cur_state = 1121;           // 有效密码，要求再输一次确认
        print_remind_message(1);

        get_the_line(cfm_pw, 1);
        if (strcmp(fir_pw, cfm_pw) == 0) {
            break;
        }

        cur_state = 1120;          // 两次输入密码不匹配
        print_remind_message(1);
    }

    get_MD5(fir_pw, dest);
}

#endif //TRADE_MANAGER_SYSTEM_TYPE_IO_H
