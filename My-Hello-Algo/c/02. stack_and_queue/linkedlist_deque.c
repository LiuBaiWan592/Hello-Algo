/**
 * @FileName    :linkenlist_deque.c
 * @Date        :2024-08-27 21:34:43
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :基于链表实现双向队列
 * @Description :双向链表结构体、基于双向链表的双向队列结构体、获取队列长度、判断队列是否为空、
 *               元素入队（队首入队，队尾入队）、获取队首/队尾元素、元素出队（队首出队、队尾出队）
 *               打印双向链表
 */

#include "../utils/common.h"

/* 双向链表节点 */
typedef struct DoublyListNode {
    int val;                     // 节点值
    struct DoublyListNode *next; // 后继节点
    struct DoublyListNode *prev; // 前驱节点
} DoublyListNode;

/* 构造函数 */
DoublyListNode *newDoublyListNode(int num) {
    DoublyListNode *node = malloc(sizeof(DoublyListNode));
    node->val = num;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/* 析构函数 */
void delDoublyListNode(DoublyListNode *node) {
    free(node);
}

/* 基于双向链表实现的双向队列 */
typedef struct
{
    DoublyListNode *front, *rear; // 头节点 front  尾节点 rear
    int queSize;                  // 双向队列的长度
} LinkedListDeque;

/* 构造函数 */
LinkedListDeque *newLinkedListDeque() {
    LinkedListDeque *deque = malloc(sizeof(LinkedListDeque));
    deque->front = NULL;
    deque->rear = NULL;
    deque->queSize = 0;
    return deque;
}

/* 析构函数 */
void delLinkedListDeque(LinkedListDeque *deque) {
    while (deque->front) {
        DoublyListNode *temp = deque->front;
        deque->front = temp->next;
        free(temp);
    }
    free(deque);
    return;
}

/* 获取队列的长度 */
int size(LinkedListDeque *deque) {
    return deque->queSize;
}

/* 判断队列是否为空 */
bool empty(LinkedListDeque *deque) {
    return size(deque) == 0;
}

/* 入队 */
void push(LinkedListDeque *deque, int num, bool isFront) {
    DoublyListNode *node = newDoublyListNode(num);
    // 若链表为空，则令 front 和 rear 都指向node
    if (empty(deque)) {
        deque->front = deque->rear = node;
    }
    // 队首入队操作
    if (isFront) {
        // 将 node 添加至链表头部
        deque->front->prev = node;
        node->next = deque->front;
        deque->front = node;
    }
    // 队尾入队操作
    else {
        // 将 node 添加至链表尾部
        deque->rear->next = node;
        node->prev = deque->rear;
        deque->rear = node;
    }
    deque->queSize++;
    return;
}
/* 队首入队 */
void pushFirst(LinkedListDeque *deque, int num) {
    push(deque, num, true);
    return;
}
/* 队尾入队 */
void pushLast(LinkedListDeque *deque, int num) {
    push(deque, num, false);
    return;
}
/* 访问队首元素 */
int peekFirst(LinkedListDeque *deque) {
    if (empty(deque) || deque->front == NULL) {
        printf("队列为空\n");
        return INT_MAX;
    }
    return deque->front->val;
}
/* 访问队尾元素 */
int peekLast(LinkedListDeque *deque) {
    if (empty(deque) || deque->rear == NULL) {
        printf("队列为空\n");
        return INT_MAX;
    }
    return deque->rear->val;
}
/* 出队 */
int pop(LinkedListDeque *deque, bool isFront) {
    if (empty(deque)) {
        printf("队列为空\n");
        return INT_MAX;
    }
    int val;
    // 队首出队操作
    if (isFront) {
        val = peekFirst(deque);
        DoublyListNode *frontNext = deque->front->next;
        if (frontNext) {
            frontNext->prev = NULL;
            deque->front->next = NULL;
        }
        delDoublyListNode(deque->front);
        deque->front = frontNext; // 更新头节点
    }
    // 队尾出队操作
    else {
        val = peekLast(deque);
        DoublyListNode *rearPrev = deque->rear->prev;
        if (rearPrev) {
            rearPrev->next = NULL;
            deque->rear->prev = NULL;
        }
        delDoublyListNode(deque->rear);
        deque->rear = rearPrev; // 更新尾节点
    }
    deque->queSize--;
    return val;
}
/* 队首出队 */
int popFirst(LinkedListDeque *deque) {
    pop(deque, true);
}
/* 队尾出队 */
int popLast(LinkedListDeque *deque) {
    pop(deque, false);
}
/* 打印队列 */
void printLinkedListDeque(LinkedListDeque *deque) {
    int *array = malloc(sizeof(int) * size(deque));
    // 拷贝链表中的数据到数组
    int i;
    DoublyListNode *node;
    for (i = 0, node = deque->front; i < size(deque); i++) {
        array[i] = node->val;
        node = node->next;
    }
    printArray(array, size(deque));
    return;
}

/* Driver Code */
int main() {
    /* 初始化双向队列 */
    LinkedListDeque *deque = newLinkedListDeque();
    pushLast(deque, 3);
    pushLast(deque, 2);
    pushLast(deque, 5);
    printf("双向队列 deque = ");
    printLinkedListDeque(deque);

    /* 访问元素 */
    int peekFirstNum = peekFirst(deque);
    printf("队首元素 peekFirst = %d\r\n", peekFirstNum);
    int peekLastNum = peekLast(deque);
    printf("队首元素 peekLast = %d\r\n", peekLastNum);

    /* 元素入队 */
    pushLast(deque, 4);
    printf("元素 4 队尾入队后 deque =");
    printLinkedListDeque(deque);
    pushFirst(deque, 1);
    printf("元素 1 队首入队后 deque =");
    printLinkedListDeque(deque);

    /* 元素出队 */
    int popLastNum = popLast(deque);
    printf("队尾出队元素 popLast = %d ，队尾出队后 deque = ", popLastNum);
    printLinkedListDeque(deque);
    int popFirstNum = popFirst(deque);
    printf("队首出队元素 popFirst = %d ，队首出队后 deque = ", popFirstNum);
    printLinkedListDeque(deque);

    /* 获取队列的长度 */
    int dequeSize = size(deque);
    printf("双向队列长度 size = %d\r\n", dequeSize);

    /* 判断队列是否为空 */
    bool isEmpty = empty(deque);
    printf("双向队列是否为空 = %s\r\n", isEmpty ? "true" : "false");

    // 释放内存
    delLinkedListDeque(deque);

    return 0;
}
