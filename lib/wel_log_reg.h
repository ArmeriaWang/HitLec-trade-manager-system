
/*
TYPE  HEADER
NAME  wel_log_reg.h
PATH  ./lib/wel_log_reg.h
*/

#ifndef TRADE_MANAGER_SYSTEM_WEL_LOG_REG_H
#define TRADE_MANAGER_SYSTEM_WEL_LOG_REG_H

#include "basic_def.h"
#include "basic_io.h"
#include "type_io.h"
#include "checker.h"
#include "info_op.h"
#include "file_op.h"

char reg_user_name[name_max_length];

void show_welcome();
void show_register();
void show_login();

void show_welcome()
// cur_state = 0
{
    print_remind_message(1);

    choice = input_and_check_num(legal_check_return_num, input_str, 0, 2);

    switch (choice) {

        case 0:
            cur_state = -1;
            return;

        case 1:
            cur_state = 1;
            break;

        case 2:
            cur_state = 2;
            break;

        default:
            break;
    }
}

void show_register()
// cur_state = 1
{
    if (total_users_cnt >= max_user_num) {
        print_error(10);
        cur_state = 1;
        return;
    }

    cur_state = 11;
    circulate_confirm_name(reg_user_name);

    unsigned reg_user_pw_MD5[5];
    cur_state = 112;
    circulate_confirm_password(reg_user_pw_MD5);

    cur_state = 11201;
    add_user(reg_user_name, reg_user_pw_MD5);
    print_remind_message(0);

    cur_state = 0;
}

void show_login()
// cur_state = 2
{
    cur_state = 21;
    print_remind_message(1);
    id_num = input_and_check_num(legal_check_return_num, str, 0, total_users_cnt);

    if (id_num == 0) {
        cur_state = 0;
        return;
    }

    cur_state = 22;
    int rest_try = 3;   // 剩余密码尝试次数
    char inp_pw[input_max_length];
    unsigned inp_pw_MD5[MD5_length];

    while (rest_try--) {
        print_remind_message(1);
        get_the_line(inp_pw, 1);
        get_MD5(inp_pw, inp_pw_MD5);

        if (check_MD5(inp_pw_MD5, user[id_num].encrypted)) {
            cur_state = 221;
            print_remind_message(0);
            break;
        }
        else {
            cur_state = 220 * 10 + rest_try;
            if (rest_try) {
                print_remind_message(1);
            }
            else {
                print_remind_message(0);
                cur_state = 0;
                return;
            }
        }
    }
    printf("\nWelcome, %s!\n", user[id_num].name);
    wait_continue();

    cur_state = 3;
}

#endif //TRADE_MANAGER_SYSTEM_WEL_LOG_REG_H
