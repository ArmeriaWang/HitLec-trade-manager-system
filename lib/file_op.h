
/*
TYPE  HEADER
NAME  file_op.h
PATH  ./lib/file_op.h
*/

#ifndef TRADE_MANAGER_SYSTEM_FILE_OP_H
#define TRADE_MANAGER_SYSTEM_FILE_OP_H

#include "basic_def.h"
#include "basic_io.h"
#include "link_op.h"

int  check_file_open(const char* file_name);
int  check_file_write(const char* file_name);
void write_new_user(User *cur);
void write_new_goods(Goods *cur);
void reset_modify_signs();
void save_all();

int check_file_open(const char* file_name)
{
    return access(file_name, F_OK) == 0;
}

int check_file_write(const char* file_name)
{
    int open_ok = check_file_open(file_name);
    EXIT_CHECK(open_ok);
    return (access(file_name, W_OK) == 0);
}

void write_new_user(User *cur)
{
    fwrite(cur, sizeof(User), 1, file_users);
    fflush(file_users);
}

void write_new_goods(Goods *cur)
{
    fwrite(cur, sizeof(Goods), 1, file_goods);
    fflush(file_goods);
}

void reset_modify_signs()
{
    basic_modified   = 0;
    users_modified   = 0;
    goods_modified   = 0;
    records_modified = 0;
    links_modified   = 0;
}

void save_all()
// cur_state = 33
{
    cur_state = 331;
    print_remind_message(0);

    if (basic_modified == 1) {
        file_basic = fopen(path_basic, "w");
        fprintf(file_basic, "%d %d %d\n", total_users_cnt, total_goods_cnt,total_records_cnt);
        fflush(file_basic);     // 将缓冲区中的内容及时写入文件
    }
    if (users_modified == 1) {
        file_users = fopen(path_users, "w");
        fwrite(user + 1, sizeof(User), (unsigned)total_users_cnt, file_users);
        fflush(file_users);
    }
    if (goods_modified == 1) {
        file_goods = fopen(path_goods, "w");
        fwrite(goods + 1, sizeof(Goods), (unsigned)total_goods_cnt, file_goods);
        fflush(file_goods);
    }
    if (records_modified == 1) {
        file_records = fopen(path_records, "w");
        fwrite(record + 1, sizeof(Record), (unsigned)total_records_cnt, file_records);
        fflush(file_records);
    }
    if (links_modified == 1) {
        file_links = fopen(path_links, "w");
        for (int i = 1; i <= total_users_cnt; i++) {
            table_write(file_links, user[i].record_head);
            if (user[i].is_seller == 1) {
                table_write(file_links, user[i].sell.goods_head);
                table_write(file_links, user[i].sell.record_head);
            }
        }
    }

    reset_modify_signs();

    cur_state = 332;
    print_remind_message(0);

    cur_state = 3;
}

#endif //TRADE_MANAGER_SYSTEM_FILE_OP_H
