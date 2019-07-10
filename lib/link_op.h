
/*
TYPE  HEADER
NAME  link_op.h
PATH  ./lib/link_op.h
*/

#ifndef TRADE_MANAGER_SYSTEM_LINK_OP_H
#define TRADE_MANAGER_SYSTEM_LINK_OP_H

#include "basic_def.h"
#include "basic_io.h"

lnk* append_linkNode(lnk* prev, int id);
int  display_linkNode(lnk* frst, print_info printer);
lnk* delete_linkNode(lnk* head, int node_val);
lnk* get_tail_linkNode(lnk* head);

int  table_reconstruct(FILE* fp, lnk** pHead, lnk** pHail, int len);
int  table_append(int* len, lnk** pHead, lnk** pTail, int val);
void table_write(FILE* fp, lnk* pHead);

lnk* append_linkNode(lnk* prev, int id)
// 向链表尾添加节点，这里是从指定节点prev而不是head开始往后找
// prev往往传入的是链表尾，这样可以提高查找效率
// 这个函数无法向空链表中加入头结点，外部调用时应先调用table_append
{
    lnk* p = NULL;
    lnk* pr = prev;

    p = (lnk*)malloc(sizeof(lnk));
    if (p == NULL) {
        print_error(21);
        return NULL;
    }
    if (prev == NULL) {
        prev = p;
    }
    else {
        while (pr->nxt != NULL) {
            pr = pr->nxt;
        }
        pr->nxt = p;
    }
    p->val = id;
    p->nxt = NULL;

    return prev;
}

int display_linkNode(lnk* frst, print_info printer)
{
    lnk* p = frst;
    int  j = 1;
    int  ret = 0;

    while (p != NULL) {
        ret += printer(j, p->val);
        p = p->nxt;
        j++;
    }

    return ret;
}

lnk* delete_linkNode(lnk* head, int node_val)
{
    lnk* p = head;
    lnk* pr = head;
    if (head == NULL) {
        print_error(30);
        return head;
    }

    while (node_val != p->val && p->nxt != NULL) {
        // 找到待删除节点p的前驱节点pr
        pr = p;
        p = p->nxt;
    }

    if (node_val == p->val) {
        if (p == head) {
            head = p->nxt;
        }
        else {
            pr->nxt = p->nxt;
        }
        free(p);
    }
    else {
        print_error(31);
        return head;
    }

    return head;
}

lnk* get_tail_linkNode(lnk* head)
{
    lnk* p = head;
    if (p == NULL) {
        return NULL;
    }

    while (p->nxt != NULL) {
        p = p->nxt;
    }

    return p;
}

int table_reconstruct(FILE* fp, lnk** pHead, lnk** pHail, int len)
{
    lnk* head = NULL;
    lnk* tail = NULL;

    int read_ok;
    int cur_len = 0;
    int val;
    for (int i = 1; i <= len; i++) {
        read_ok = fscanf(fp, "%d", &val);
        EXIT_CHECK(read_ok);
        table_append(&cur_len, &head, &tail, val);
    }

    (*pHead) = head;
    (*pHail) = tail;

    return 1;
}

int table_append(int* len, lnk** pHead, lnk** pTail, int val)
// 拥有完备接口的向链表尾添加元素的函数
{
    lnk* head = *pHead;
    lnk* tail = *pTail;

    if (*len == 0) {   // 若为空链表
        lnk* res = append_linkNode(head, val);
        EXIT_CHECK(res != NULL);
        head = res;
        tail = head;
    }
    else {
        lnk* res = append_linkNode(tail, val);
        EXIT_CHECK(res != NULL);
        tail = res->nxt;
    }


    (*len)++;

   *pHead = head;
   *pTail = tail;

   return 1;
}

void table_write(FILE* fp, lnk* head)
{
    lnk* p = head;
    while (p != NULL) {
        fprintf(fp, "%d ", p->val);
        p = p->nxt;
    }
}

#endif //TRADE_MANAGER_SYSTEM_LINK_OP_H
