
/*
TYPE  HEADER
NAME  info_op.h
PATH  ./lib/info_op.h
*/

#ifndef TRADE_MANAGER_SYSTEM_INFO_OP_H
#define TRADE_MANAGER_SYSTEM_INFO_OP_H

#include "basic_def.h"
#include "basic_io.h"
#include "file_op.h"
#include "link_op.h"

int add_ok;

void add_user(const char *user_name, const unsigned *reg_pw);  // pw为password缩写
void register_seller();

int  add_goods(const char *goods_name, int storage, int price);
void del_goods(int goods_id);
void mod_goods_stock(int goods_id, int qnt);    // qnt为quantity缩写

int  add_record(int goods_id, int seller_id, int qnt);

int  buy_goods(int goods_id, int qnt);


void add_user(const char *user_name, const unsigned *reg_pw)
{
    basic_modified = 1;
    links_modified = 1;

    total_users_cnt++;
    User *cur = &user[total_users_cnt];

    cur->number = total_users_cnt;

    strcpy(cur->name, user_name);

    for (int i = 1; i <= 4; i++)
        cur->encrypted[i] = reg_pw[i];

    cur->is_seller = 0;

    cur->record_cnt = 0;
    cur->record_head = NULL;
    cur->record_tail = NULL;

    file_users = fopen(path_users, "a");
    write_new_user(&user[total_users_cnt]);
}

void register_seller()
{
    users_modified = 1;

    User *cur = &user[id_num];
    cur->is_seller = 1;

    cur->sell.goods_cnt = 0;
    cur->sell.record_head = NULL;
    cur->sell.record_tail = NULL;

    cur->sell.record_cnt = 0;
    cur->sell.goods_head = NULL;
    cur->sell.goods_tail = NULL;
}

int add_goods(const char *goods_name, int storage, int price)
{
    basic_modified = 1;
    users_modified = 1;
    links_modified = 1;

    total_goods_cnt++;
    Goods *cur = &goods[total_goods_cnt];

    // 写入新商品信息
    cur->number = total_goods_cnt;
    strcpy(cur->name, goods_name);
    cur->stock_cnt = storage;
    cur->price = price;
    cur->seller_num = id_num;

    // 将新商品编号挂在当前用户商品链表上
    add_ok = table_append(&user[id_num].sell.goods_cnt,
                 &user[id_num].sell.goods_head, &user[id_num].sell.goods_tail, total_goods_cnt);

    EXIT_CHECK(add_ok);

    file_goods = fopen(path_goods, "a");
    write_new_goods(&goods[total_goods_cnt]);

    return 1;
}

void del_goods(int goods_id)
{
    links_modified = 1;
    basic_modified = 1;
    goods_modified = 1;
    users_modified = 1;

    goods[goods_id].deleted = 1;
    user[id_num].sell.goods_head =
        delete_linkNode(user[id_num].sell.goods_head, goods[goods_id].number);
    user[id_num].sell.goods_tail =
        get_tail_linkNode(user[id_num].sell.goods_head);

    user[id_num].sell.goods_cnt--;
}

void mod_goods_stock(int goods_id, int qnt)
{
    goods[goods_id].stock_cnt += qnt;
}

int add_record(int goods_id, int seller_id, int qnt)
{
    basic_modified = 1;
    records_modified = 1;
    users_modified = 1;

    total_records_cnt++;
    Record* cur = &record[total_records_cnt];

    cur->number = total_records_cnt;
    cur->goods_num = goods_id;
    cur->buyer_num = id_num;
    cur->seller_num = seller_id;
    cur->qnt = qnt;

    return 1;
}

int buy_goods(int goods_id, int qnt)
{
    basic_modified   = 1;
    goods_modified   = 1;
    users_modified   = 1;
    records_modified = 1;
    links_modified   = 1;

    Goods *cur = &goods[goods_id];
    cur->stock_cnt -= qnt;

    add_record(goods_id, cur->seller_num, qnt);

    int buy_id = id_num;
    int sel_id = goods[goods_id].seller_num;

    add_ok = table_append(&user[buy_id].record_cnt,
                 &user[buy_id].record_head, &user[buy_id].record_tail, total_records_cnt);

    EXIT_CHECK(add_ok);

    add_ok = table_append(&user[sel_id].sell.record_cnt,
                 &user[sel_id].sell.record_head, &user[sel_id].sell.record_tail, total_records_cnt);

    EXIT_CHECK(add_ok);

    return 1;
}

#endif //TRADE_MANAGER_SYSTEM_INFO_OP_H
