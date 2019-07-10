
/*
TYPE  HEADER
NAME  surface.h
PATH  ./lib/surface.h
*/

#ifndef TRADE_MANAGER_SYSTEM_SHOW_MAIN_SURFACE_H
#define TRADE_MANAGER_SYSTEM_SHOW_MAIN_SURFACE_H

#include "basic_def.h"
#include "checker.h"
#include "basic_io.h"
#include "type_io.h"
#include "info_op.h"
#include "search.h"
#include "functions.h"

char tmp_name[name_max_length];
int  tmp_storage;
int  tmp_price;
int  id;
int  mod_qnt;       // 修改量
int  upper;         // 修改量上界
int  lower;         // 修改量下界

char kw[name_max_length];    // kw为keyword缩写
int kw_num;
int result[max_goods_num];   // 搜索结果编号
int buy_qnt;
int result_cnt;
int start_ord;  // start_ord = 1 时，表示存在goodsID与用户输入符合的商品
int chose_id;

int op_ok;

void show_main_menu();
void show_personal_menu();
void show_seller_menu();
void show_shopping_menu();

void show_main_menu()
// cur_state = 3
{
    print_remind_message(1);

    choice = input_and_check_num(legal_check_return_num, input_str, 0, 3);

    switch (choice) {

        case 0:
            cur_state = 0;
            id_num = 0;
            return;

        case 1:
            cur_state = 31;
            break;

        case 2:
            cur_state = 32;
            break;

        case 3:
            cur_state = 33;
            break;

        default:
            break;
    }
}

void show_personal_menu()
// cur_state = 31
{
    print_remind_message(1);

    choice = input_and_check_num(legal_check_return_num, input_str, 0, 2);

    switch (choice) {

        // 返回上级菜单
        case 0:
            cur_state = 3;
            return;

        // 显示购买记录
        case 1:
            print_buy_records_list();
            wait_continue();
            break;

        // 注册商家用户，或进入商家菜单
        case 2:
            if (user[id_num].is_seller == 0) {
                register_seller();
                cur_state = 3121;
                print_remind_message(0);
                break;
            }
            else {
                cur_state = 312;
                return;
            }
            
        default:
            break;
    }

    cur_state = 31;
}

void show_seller_menu()
// cur_state = 312
{
    print_remind_message(1);

    choice = input_and_check_num(legal_check_return_num, input_str, 0, 5);

    switch (choice) {

        // 返回上级菜单
        case 0:
            cur_state = 31;
            return;

        // 显示自己的商品列表
        case 1:
            print_my_goods_list();
            wait_continue();
            break;

        // 显示售卖记录
        case 2:
            print_sell_records_list();
            wait_continue();
            break;

        // 增加商品
        case 3:
            if (total_goods_cnt >= max_goods_num) {
                print_error(10);
                break;
            }

            cur_state = 31231;
            print_remind_message(1);
            input_and_check_single(legal_check_name, input_str);
            strncpy(tmp_name, input_str, name_max_length);

            cur_state = 31232;
            print_remind_message(1);
            tmp_storage = input_and_check_num(legal_check_return_num, input_str, 0, max_storage);

            cur_state = 31233;
            print_remind_message(1);
            tmp_price = input_and_check_num(legal_check_return_num, input_str, 0, max_price);

            op_ok = add_goods(tmp_name, tmp_storage, tmp_price);
            BREAK_CHECK(op_ok);

            cur_state = 31234;
            print_remind_message(0);

            break;

        // 删除商品
        case 4:
            print_my_goods_list();

            cur_state = 31241;
            print_remind_message(1);
            id = input_and_check_num(legal_check_return_num, input_str, 1, total_goods_cnt);
            del_goods(id);

            cur_state = 31242;
            print_remind_message(0);

            break;

        // 更改库存量
        case 5:
            print_my_goods_list();

            cur_state = 31251;
            print_remind_message(1);
            id = input_and_check_num(legal_check_return_num, input_str, 1, total_goods_cnt);
            if (goods[id].seller_num != id_num || goods[id].deleted == 1) {
                print_error(11);
                break;
            }

            cur_state = 31252;
            print_remind_message(1);
            upper = max_storage - goods[id].stock_cnt;
            lower = -goods[id].stock_cnt;
            mod_qnt = input_and_check_num(legal_check_return_num, input_str, lower, upper);

            mod_goods_stock(id, mod_qnt);

            cur_state = 31253;
            print_remind_message(0);

            break;

        default:
            break;
    }
    cur_state = 312;
}

void show_shopping_menu()
// cur_state = 32
{
    print_remind_message(1);

    choice = input_and_check_num(legal_check_return_num, input_str, 0, 5);

    switch (choice) {

        // 返回上级菜单
        case 0:
            cur_state = 3;
            return;

        // 搜索
        case 1:
            cur_state = 321;
            print_remind_message(1);

            start_ord = 0;
            input_and_check_single(legal_check_keyword, input_str);
            strncpy(kw, input_str, name_max_length);

            system("clear");
            printf(" --------------------------------------------------------------------------------------- \n");
            printf("| order | goodsID |                       goods name | price | storage | userID(seller) |\n");

            if (is_number(kw)) {
                kw_num = atoi(kw);
                if (kw_num > 0 && kw_num <= total_goods_cnt) {
                    print_search_item(1, kw_num);
                    start_ord = 1;
                }
            }

            memset(result, 0, sizeof(result));
            result_cnt = main_search(kw, start_ord, kw_num, result);

            printf(" --------------------------------------------------------------------------------------- \n\n");

            result_cnt += start_ord;
            if (result_cnt == 0) {
                printf("No results.\n");
                wait_continue();
                break;
            }

            // 读取用户选择的商品序号
            cur_state = 3211;
            print_remind_message(1);
            choice = input_and_check_num(legal_check_return_num, input_str, 0, result_cnt);
            BREAK_CHECK(choice);

            if (start_ord == 1 && choice == 1) {
                chose_id = kw_num;
            }
            else {
                chose_id = ord[choice - start_ord];
            }

            // 读取用户购买量
            cur_state = 3212;
            print_remind_message(1);
            buy_qnt = input_and_check_num(legal_check_return_num, input_str, 0, goods[chose_id].stock_cnt);
            BREAK_CHECK(buy_qnt);

            op_ok = buy_goods(chose_id, buy_qnt);
            BREAK_CHECK(op_ok);

            cur_state = 3213;
            print_remind_message(0);
            wait_continue();

        default:
            break;
    }

    cur_state = 32;
}

#endif //TRADE_MANAGER_SYSTEM_SHOW_MAIN_SURFACE_H
