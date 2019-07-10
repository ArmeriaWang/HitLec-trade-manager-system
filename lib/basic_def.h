
/*
TYPE  HEADER
NAME  basic_def.h
PATH  ./lib/basic_def.h
*/

#ifndef TRADE_MANAGER_SYSTEM_GLOBALS_H
#define TRADE_MANAGER_SYSTEM_GLOBALS_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define version_length 20
#define MD5_length     4 + 1

#define name_max_length   32
#define input_max_length  256
#define path_max_length   64

#define max_goods_num  10000
#define max_record_num 100000
#define max_user_num   10000

#define max_storage 1000000
#define max_price   1000000

#define ERROR (1<<30)-1         // 错误值
#define EXIT_CHECK(X)  if (X == 0) return 0         // return宏
#define BREAK_CHECK(X) if (X == 0) break            // break宏

int  cur_state;   // 当前命令行状态
char input_str[input_max_length];       // 用于储存输入字符串

int id_num;       // 当前登录的用户编号

int choice;       // 用户选择号

char path_basic[path_max_length]   = "../info/basic.info";
char path_users[path_max_length]   = "../info/users.info";
char path_goods[path_max_length]   = "../info/goods.info";
char path_records[path_max_length] = "../info/records.info";
char path_links[path_max_length]   = "../info/links.info";

int total_users_cnt;        // 总用户数
int total_goods_cnt;        // 总商品数
int total_records_cnt;      // 总记录数

// 修改标记
int basic_modified;
int users_modified;
int goods_modified;
int records_modified;
int links_modified;

// 五个文件指针
FILE* file_basic;
FILE* file_users;
FILE* file_goods;
FILE* file_records;
FILE* file_links;

// 三个函数指针
typedef int (*checker_sgl)(char*);
typedef int (*checker_num)(char*, int, int );
typedef int (*print_info)(int, int);

struct Version
{
    char version_number[version_length];    // 版本号
    char released_time[version_length];     // 释出时间
} current_version;

// 链表元素，值域为信息编号
typedef struct linkNode
{
    int val;
    struct linkNode* nxt;
} lnk;

// 编号用number、num，数量用count、cnt

typedef struct seller
{
    int  goods_cnt;              // 商品数量
    lnk* goods_head;             // 商品链表头
    lnk* goods_tail;             // 商品链表尾

    int  record_cnt;             // 记录数量
    lnk* record_head;            // 记录链表头
    lnk* record_tail;            // 记录链表尾
} Seller;

typedef struct user
{
    int number;                         // 用户编号
    unsigned encrypted[MD5_length];     // MD5加密后的4个16进制数

    char name[name_max_length];         // 用户名

    int  record_cnt;                    // 记录数量
    lnk* record_head;                   // 记录链表头
    lnk* record_tail;                   // 记录链表尾

    int is_seller;                      // 是否是商家用户

    Seller sell;
} User;
User user[max_user_num];

typedef struct goods
{
    int number;                     // 商品编号
    int seller_num;                 // 售卖者的用户编号
    int deleted;                    // 是否已被删除

    int price;                      // 价格
    int stock_cnt;                  // 库存量

    char name[name_max_length];     // 商品名

} Goods;
Goods goods[max_goods_num];

typedef struct record
{
    int number;                       // 记录编号

    int goods_num;                    // 交易商品编号
    int seller_num;                   // 售卖者的用户编号
    int buyer_num;                    // 购买者的用户编号

    int qnt;                          // 交易数量
} Record;
Record record[max_record_num];


#endif //TRADE_MANAGER_SYSTEM_GLOBALS_H
