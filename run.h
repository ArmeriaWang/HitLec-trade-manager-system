
/*
TYPE  HEADER
NAME  run.h
PATH  ./run.h
*/

#ifndef TRADE_MANAGER_SYSTEM_RUN_H
#define TRADE_MANAGER_SYSTEM_RUN_H

#include "lib.h"

void run_manager();

void run_manager()
{
    initialize();

    while (cur_state != -1) {

        switch (cur_state) {

            case 0:
                show_welcome();
                break;

            case 1:
                show_register();
                break;

            case 2:
                show_login();
                break;

            case 3:
                show_main_menu();
                break;

            case 31:
                show_personal_menu();
                break;

            case 312:
                show_seller_menu();
                break;

            case 32:
                show_shopping_menu();
                break;
                
            case 33:
                save_all();

            case -1:
                break;

            default:
                break;
        }
        // break to here
    }

    save_all();

    cur_state = -11;
    print_remind_message(0);

}

#endif //TRADE_MANAGER_SYSTEM_RUN_H
