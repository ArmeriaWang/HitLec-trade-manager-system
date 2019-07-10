
/*
TYPE  HEADER
NAME  basic_io.h
PATH  ./lib/basic_io.h
*/

#ifndef TRADE_MANAGER_SYSTEM_CUSTIO_H
#define TRADE_MANAGER_SYSTEM_CUSTIO_H

#include "basic_def.h"

void get_the_line(char *str, int need_all);

void print_waiting_chars();
void print_error(int error_id);
void print_remind_message(int need);

void get_the_line(char *str, int need_all)
// need_all = 1 表示不需要加工
{
    char c;
    char line[input_max_length];

    int cnt = 0;
    do {
        scanf("%c", &c);
        line[cnt] = c;
        cnt++;
    } while (c != '\n');
    line[--cnt] = '\0';

    printf("\n");

    if (need_all) {
        strcpy(str, line);
        return;
    }

    // 去空格，规范化用户输入
    int i = 0, j = 0;
    while (line[i] == ' ') {
        i++;
    }

    while (i < cnt) {
        while (line[i] != ' ' && i < cnt) {
            str[j++] = line[i++];
        }

        if (line[i] == ' ') {
            str[j++] = line[i++];
        }

        while (line[i] == ' ') {
            i++;
        }
    }

    if (str[j - 1] == ' ') {
        j--;
    }
    str[j] = '\0';
}

void print_waiting_chars()
{
    printf(">> ");
}

void wait_continue()
{
    printf("Press Enter to continue: ");
    getchar();
    printf("\n");
}


void print_error(int error_id)
{
    printf("Error %d: ", error_id);

    switch (error_id) {

        case 0:
            printf("Illegal input.\n");
            printf("Please try again.\n");
            print_waiting_chars();
            break;

        case 20:
            printf("Cannot load files!\n");
            printf("The system will reconstruct new empty ones.\n");
            break;

        default:
            printf("Fatal Error.\nAuto get back or exit.\n");
            break;
    }

}

void print_remind_message(int need)
{
    switch (cur_state) {

        case 0:     // 欢迎界面
            system("clear");  // Windows + cmd运行需要改为 system("cls")
            printf("\n ------------- Welcome Menu ------------- \n");
            printf(  "|                                        |\n");
            printf(  "|                                        |\n");
            printf(  "|            0 Save and quit             |\n");
            printf(  "|                                        |\n");
            printf(  "|            1 Register                  |\n");
            printf(  "|                                        |\n");
            printf(  "|            2 Login                     |\n");
            printf(  "|                                        |\n");
            printf(  "|                                        |\n");
            printf(  " ---------------------------------------- \n\n");
            break;

        case 11:     // 注册，输入用户名
            printf("Please enter your user name.\nYour name should:\n");
            printf("- Contain at least 3 characters and no more than %d characters.\n", name_max_length);
            printf("- Only letters, digits and '_' are allowed.\n");
            break;

        case 111:
            printf("Valid user name.\nAccept it? [y/n]\n");
            break;

        case 112:    // 注册，输入密码
            printf("Please enter your password.\nYour password should:\n");
            printf("- No less than 8 characters and no more than 16 characters.\n");
            printf("- CanNOT only contain upper letters, lower letters, digits or special characters.\n");
            break;

        case 1121:
            printf("Valid password.\nPlease enter it again to verify.\n");
            break;

        case 1120:
            printf("InValid password!\nPlease try again.\n");

        case 11201:
            printf("Successfully Registered!\n");
            printf("Your userID: %d\n", total_users_cnt);
            break;

        case 21:
            printf("Please enter your userID, or enter '0' to get back.\n");
            break;

        case 22:
            printf("Please enter your password.\n");
            printf("You can try no more than 3 times.\n");
            break;

        case 2202:
            printf("You can try no more than 2 times.\n");
            break;

        case 2201:
            printf("You can try no more than 1 times.\n");
            break;

        case 2200:
            printf("Login Failed!\nAuto get back to Welcome menu.\n");
            break;

        case 221:
            printf("Successfully login!\n");
            break;

        case 3:     // 主菜单
            system("clear");
            printf("\n ------------ Main Menu ------------ \n");
            printf(  "|                                   |\n");
            printf(  "|                                   |\n");
            printf(  "|            0 Logout               |\n");
            printf(  "|                                   |\n");
            printf(  "|            1 Personal             |\n");
            printf(  "|                                   |\n");
            printf(  "|            2 Shopping             |\n");
            printf(  "|                                   |\n");
            printf(  "|                                   |\n");
            printf(  " ----------------------------------- \n\n");
            break;

        case 31:    // 个人菜单
            system("clear");
            printf("\n ---------------- Personal Menu ---------------- \n");
            printf(  "|                                               |\n");
            printf(  "|                                               |\n");
            printf(  "|        0 Back to superior menu                |\n");
            printf(  "|                                               |\n");
            printf(  "|        1 Check my trade record (buy)          |\n");
            printf(  "|                                               |\n");
            if (user[id_num].is_seller == 0) {
            printf(  "|        2 Apply for seller qualification       |\n"); }
            else {
            printf(  "|        2 Seller's Menu                        |\n"); }
            printf(  "|                                               |\n");
            printf(  "|                                               |\n");
            printf(  " ----------------------------------------------- \n\n");
            break;

        case 3121:
            printf("Successfully applied!\n");
            break;

        case 312:      // 商家菜单
            system("clear");
            printf("\n ------------------- Seller Menu ------------------- \n");
            printf(  "|                                                   |\n");
            printf(  "|                                                   |\n");
            printf(  "|            0 Back to superior menu                |\n");
            printf(  "|                                                   |\n");
            printf(  "|            1 Check my goods list                  |\n");
            printf(  "|                                                   |\n");
            printf(  "|            2 Check my trade record (sell)         |\n");
            printf(  "|                                                   |\n");
            printf(  "|            3 Add goods                            |\n");
            printf(  "|                                                   |\n");
            printf(  "|            4 Delete goods                         |\n");
            printf(  "|                                                   |\n");
            printf(  "|            5 Modify storage                       |\n");
            printf(  "|                                                   |\n");
            printf(  "|                                                   |\n");
            printf(  " -------------------------------------------------- \n\n");
            break;

        // 添加商品
        case 31231:
            printf("Please enter the goods name.\nThe name should:\n");
            printf("- Contain at least 3 characters and no more than %d characters.\n", name_max_length);
            printf("- Only letters, digits and '_' are allowed.\n");
            break;

        case 31232:
            printf("Please enter the storage.\n");
            printf("The number should be no more than %d.\n", max_storage);
            break;

        case 31233:
            printf("Please enter the price.\n");
            printf("The number should be no more than %d.\n", max_price);
            break;

        case 31234:
            printf("Successfully added!\n");
            printf("The goodsID: %d\n", total_goods_cnt);
            break;

        // 删除商品
        case 31241:
            printf("Please enter the goodsID.\n");
            break;

        case 31242:
            printf("Successfully deleted!\n");
            break;

        // 更改商品库存量
        case 31251:
            printf("Please enter the goodsID.\n");
            break;

        case 31252:
            printf("Please enter the quantity you want to modify.\nThe number should:\n");
            printf("- After modified, the storage should be no more than %d.\n", max_storage);
            printf("- After modified, the storage should be no less than 0.\n");
            break;

        case 31253:
            printf("Successfully modified!\n");
            break;

        case 32:        // 购物菜单
            system("clear");
            printf("\n ------------------ Shopping Menu -------------------- \n");
            printf(  "|                                                     |\n");
            printf(  "|                                                     |\n");
            printf(  "|         0 Back to superior menu                     |\n");
            printf(  "|                                                     |\n");
            printf(  "|         1 Search (support wildcard '*' and '?')     |\n");
            printf(  "|                                                     |\n");
            printf(  "|                                                     |\n");
            printf(  " ----------------------------------------------------- \n\n");
            break;

        // 搜索界面
        case 321:
            printf("Please input the keyword.\nThe keyword should:\n");
            printf("- No more than %d characters.\n", name_max_length);
            printf("- Only letters, digits, '_', '?', '*' are allowed.\n");
            break;

        case 3210:
            printf("No results.\n");
            break;

        case 3211:
            printf("Please enter the order of your intended goods.\n");
            printf("Enter '0' to get back.\n");
            break;

        case 3212:
            printf("Please enter the quantity you want to buy.\n");
            printf("Enter '0' to get back.\n");
            break;

        case 3213:
            printf("Successfully traded!\n");
            break;

        case 331:
            printf("Saving...\n");
            break;

        case 332:
            printf("Successfully saved!\n");
            break;

        case -10:
            printf("Saving and quitting...\n");
            break;

        case -11:
            printf("\nSee you.\n");
            break;

        default:
            // printf("state = %d: Unfinished.\n", cur_state);
            break;

    }
    if (need == 1) {
        print_waiting_chars();
    }
}

#endif //TRADE_MANAGER_SYSTEM_CUSTIO_H
