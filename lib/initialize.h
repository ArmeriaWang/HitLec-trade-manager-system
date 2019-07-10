
/*
TYPE  HEADER
NAME  initialize.h
PATH  ./lib/initialize.h
*/

#ifndef TRADE_MANAGER_SYSTEM_INITIALIZE_H
#define TRADE_MANAGER_SYSTEM_INITIALIZE_H

#include "basic_def.h"
#include "basic_io.h"
#include "file_op.h"
#include "link_op.h"

int read_goods_id[max_goods_num];
int read_record_id[max_record_num];
int read_ok;

void initialize();
int  initialize_normal();
void initialize_file();
void initialize_version();
void recover_all();

void initialize()
{
    initialize_version();

    int load_ok = initialize_normal();
    if (load_ok == 0) {
        print_error(20);
        initialize_file();
        recover_all();
    }

    reset_modify_signs();

    printf("Successfully initialized!\n\n");

    wait_continue();
}

void initialize_version()
{
    strcpy(current_version.version_number, "1.0.0");
    strcpy(current_version.released_time,  "2018.11.11");
}

int initialize_normal()
{
    printf("\n-- Welcome to Armeria Trade Manager System --\n");
    printf("\n>> Made by Wang Hankun, HIT\n\n");

    printf("Loading Save files...\n");

    cur_state = 0;

    // 检查文件可读性
    read_ok = 1;
    read_ok &= check_file_write(path_basic);
    read_ok &= check_file_write(path_users);
    read_ok &= check_file_write(path_goods);
    read_ok &= check_file_write(path_records);
    read_ok &= check_file_write(path_links);
    EXIT_CHECK(read_ok);

    // 读取存档
    file_basic = fopen(path_basic, "r");
    read_ok = (fscanf(file_basic, "%d%d%d",
        &total_users_cnt, &total_goods_cnt, &total_records_cnt) == 3);
    EXIT_CHECK(read_ok);

    file_users = fopen(path_users, "r");
    read_ok = (fread(user + 1, sizeof(User),
        (unsigned)total_users_cnt, file_users) == total_users_cnt);
    EXIT_CHECK(read_ok);

    file_goods = fopen(path_goods, "r");
    read_ok = (fread(goods + 1, sizeof(Goods),
        (unsigned)total_goods_cnt, file_goods) == total_goods_cnt);
    EXIT_CHECK(read_ok);

    file_records = fopen(path_records, "r");
    read_ok = (fread(record + 1, sizeof(Record),
        (unsigned)total_records_cnt, file_records) == total_records_cnt);
    EXIT_CHECK(read_ok);

    file_links = fopen(path_links, "r");
    for (int i = 1; i <= total_users_cnt; i++) {
        read_ok = table_reconstruct(file_links,
            &user[i].record_head, &user[i].record_tail, user[i].record_cnt);
        EXIT_CHECK(read_ok);

        if (user[i].is_seller == 1) {
            read_ok = table_reconstruct(file_links,
                &user[i].sell.goods_head, &user[i].sell.goods_tail, user[i].sell.goods_cnt);
            EXIT_CHECK(read_ok);

            read_ok = table_reconstruct(file_links,
                &user[i].sell.record_head, &user[i].sell.record_tail, user[i].sell.record_cnt);
            EXIT_CHECK(read_ok);
        }
    }

    printf("Successfully loaded savings!\n");

    return 1;
}

void initialize_file()
{
    file_basic   = fopen(path_basic,   "w");
    file_users   = fopen(path_users,   "w");
    file_goods   = fopen(path_goods,   "w");
    file_records = fopen(path_records, "w");
    file_links   = fopen(path_links,   "w");

    fprintf(file_basic, "%d %d %d\n", 0, 0, 0);
    fflush(file_basic);
}

void recover_all()
{
    total_users_cnt   = 0;
    total_goods_cnt   = 0;
    total_records_cnt = 0;
}

#endif //TRADE_MANAGER_SYSTEM_INITIALIZE_H
