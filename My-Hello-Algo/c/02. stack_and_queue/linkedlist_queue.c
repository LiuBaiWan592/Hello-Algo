/**
 * @FileName    :linkedlist_queue.c
 * @Date        :2024-08-25 15:29:14
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :基于链表实现的队列
 * @Description :获取队列长度、判断队列是否为空、元素入队、访问队首元素、元素出队，打印队列
 */

#include "../utils/common.h"

/* 基于链表实现的队列 */
typedef struct
{
    ListNode *front, *rear;
    int queSize;
} LinkedListQueue;

/* 构造函数 */
LinkedListQueue *newLinkedListQueue() {
    LinkedListQueue *queue = malloc(sizeof(LinkedListQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->queSize = 0;
    return queue;
}

/* 析构函数 */
void delLinkedListQueue(LinkedListQueue *queue) {
    // 释放所有节点
    while (queue->front) {
        ListNode *temp = queue->front;
        queue->front = temp->next;
        free(temp);
    }
    // 释放 queue 结构体
    free(queue);
}

/* 获取队列的长度 */
int size(LinkedListQueue *queue) {
    return queue->queSize;
}

/* 判断队列是否为空 */
bool isEmpty(LinkedListQueue *queue) {
    return size(queue) == 0;
}

/* 入队 */
void push(LinkedListQueue *queue, int num) {
    // 尾节点处添加 node
    ListNode *node = newListNode(num);
    // 如果队列为空，则令头、尾节点都指向该节点
    if (isEmpty(queue)) {
        queue->front = node;
        queue->rear = node;
    }
    // 如果队列不为空，则将该节点添加到尾节点后
    else {
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->queSize++;
}

/* 访问队首元素 */
int peek(LinkedListQueue *queue) {
    if (isEmpty(queue)) {
        printf("队列为空\n");
        return INT_MAX;
    }
    return queue->front->val;
}

/* 出队 */
int pop(LinkedListQueue *queue) {
    int value = peek(queue);
    ListNode *temp = queue->front;
    queue->front = temp->next;
    free(temp);
    queue->queSize--;
    return value;
}

/* 打印队列 */
void printLinkedListQueue(LinkedListQueue *queue) {
    int size = queue->queSize;
    int *array = malloc(sizeof(int) * size);
    // 拷贝链表中的数据到数组
    int i;
    ListNode *node;
    for (i = 0, node = queue->front; i < size; i++) {
        array[i] = node->val;
        node = node->next;
    }
    printArray(array, size);
    free(array);
}

/* Driver Code */
int main() {
    /* 初始化队列 */
    LinkedListQueue *queue = newLinkedListQueue();

    /* 元素入队 */
    push(queue, 1);
    push(queue, 3);
    push(queue, 2);
    push(queue, 5);
    push(queue, 4);
    printf("队列 queue = ");
    printLinkedListQueue(queue);

    /* 访问队首元素 */
    int peekNum = peek(queue);
    printf("队首元素 peek = %d\r\n", peekNum);

    /* 元素出队 */
    peekNum = pop(queue);
    printf("出队元素 pop = %d ，出队后 queue = ", peekNum);
    printLinkedListQueue(queue);

    /* 获取队列的长度 */
    int queueSize = size(queue);
    printf("队列长度 size = %d\r\n", queueSize);

    /* 判断队列是否为空 */
    bool empty = isEmpty(queue);
    printf("队列是否为空 = %s\r\n", empty ? "true" : "false");

    // 释放内存
    delLinkedListQueue(queue);

    return 0;
}
