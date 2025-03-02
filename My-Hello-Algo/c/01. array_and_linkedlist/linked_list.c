/**
 * @FileName    :linked_list.c
 * @Date        :2024-08-14 22:33:01
 * @Author      :LiuBaiWan-Runner
 * @Version     :V1.0.0
 * @Brief       :链表的基本操作
 * @Description :单链表结构体及其构造函数（list_node.h）、双向链表结构体及其构造函数、某节点后插入节点、删除某节点后一节点、
 *               根据index访问节点、根据目标值查找首个节点索引值、打印链表、释放分配给链表的内存空间
 */

#include "../utils/common.h"

/* 双向链表节点结构体 */
typedef struct DoubleListNode {
    int val;                     // 节点value
    struct DoubleListNode *next; // 指向后继节点的指针
    struct DoubleListNode *prev; // 指向前驱节点的指针
} DoubleListNode;

/* 构造函数 */
DoubleListNode *newDoubleListNode(int val) {
    DoubleListNode *node;
    node = (DoubleListNode *)malloc(sizeof(DoubleListNode));
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/* 在链表节点n0后插入节点p O(1) */
void insert(ListNode *n0, ListNode *p) {
    ListNode *n1 = n0->next;
    p->next = n1;
    n0->next = p;
}

/* 删除链表节点 O(1) */
void removeItem(ListNode *n0) {
    if (!n0->next) {
        return;
    }
    ListNode *p = n0->next;
    ListNode *n1 = p->next;
    n0->next = n1;
    free(p);
}

/* 访问链表中索引为 index 的节点 O(n) */
ListNode *access(ListNode *head, int index) {
    for (int i = 0; i < index; i++) {
        if (head == NULL) {
            return NULL;
        }
        head = head->next;
    }
    return head;
}

/* 在链表中查找值为 target 的首个节点 O(n) */
int find(ListNode *head, int target) {
    int index = 0;
    while (head) {
        if (head->val == target) {
            return index;
        }
        index++;
        head = head->next;
    }
    return -1;
}

/* Driver Code */
int main() {
    /* 初始化链表 */
    // 初始化各个节点
    ListNode *n0 = newListNode(1);
    ListNode *n1 = newListNode(3);
    ListNode *n2 = newListNode(2);
    ListNode *n3 = newListNode(5);
    ListNode *n4 = newListNode(4);
    // 构建节点之间的引用
    n0->next = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    printf("初始化的链表为\r\n");
    printLinkedList(n0);

    /* 插入节点 */
    insert(n0, newListNode(0));
    printf("插入节点后的链表为\r\n");
    printLinkedList(n0);

    /* 删除节点 */
    removeItem(n0);
    printf("删除节点后的链表为\r\n");
    printLinkedList(n0);

    /* 访问节点 */
    ListNode *node = access(n0, 3);
    printf("链表中索引 3 处的节点的值 = %d\r\n", node->val);

    /* 查找节点 */
    int index = find(n0, 2);
    printf("链表中值为 2 的节点的索引 = %d\r\n", index);

    // 释放内存
    freeMemoryLinkedList(n0);
    return 0;
}