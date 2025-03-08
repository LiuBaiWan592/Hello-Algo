/**
 * @FileName    :array_queue.c
 * @Date        :2024-08-26 14:06:18
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :基于环形数组实现的队列
 * @Description :获取队列的容量、获取队列的长度、判断队列是否为空、访问队首元素、获取队尾指针、入队、出队、打印数组队列
 */

#include "../utils/common.h"

/* 基于环形数组实现的队列 */
typedef struct
{
    int *nums;       // 用于存储队列元素的数组
    int front;       // 队首指针，指向队首元素
    int queSize;     // 队列长度，用于计算队尾指针
    int queCapacity; // 队列（数组）容量
} ArrayQueue;

/* 构造函数 */
ArrayQueue *newArrayQueue(int capacity) {
    ArrayQueue *queue = malloc(sizeof(ArrayQueue));
    // 初始化数组
    queue->queCapacity = capacity;
    queue->nums = malloc(sizeof(int) * queue->queCapacity);
    queue->front = queue->queSize = 0;
    return queue;
}

/* 析构函数 */
void delArrayQueue(ArrayQueue *queue) {
    free(queue->nums);
    free(queue);
}

/* 获取队列的容量 */
int capacity(ArrayQueue *queue) {
    return queue->queCapacity;
}

/* 获取队列的长度 */
int size(ArrayQueue *queue) {
    return queue->queSize;
}

/* 判断队列是否为空 */
bool isEmpty(ArrayQueue *queue) {
    return capacity(queue) == 0;
}

/* 访问队首元素 */
int peek(ArrayQueue *queue) {
    if (size(queue) == 0) {
        printf("队列为空\n");
        return INT_MAX;
    }
    return queue->nums[queue->front];
}

/* 获取队尾指针 */
int getRear(ArrayQueue *queue) {
    return (queue->front + queue->queSize) % queue->queCapacity;
}

/* 入队 */
void push(ArrayQueue *queue, int num) {
    if (size(queue) == capacity(queue)) {
        printf("队列已满\n");
        return;
    }
    // 计算队尾指针，指向队尾索引 + 1
    // 通过取余操作实现 rear 越过数组尾部后回到头部
    int rear = getRear(queue);
    queue->nums[rear] = num;
    queue->queSize++;
    return;
}

/* 出队 */
int pop(ArrayQueue *queue) {
    int num = peek(queue);
    // 队首指针向后移动一位，若越过尾部，则返回到数组头部
    queue->front = (queue->front + 1) % queue->queCapacity;
    queue->queSize--;
    return num;
}

/* 打印数组队列 */
void printArrayQueue(ArrayQueue *queue) {
    if (queue->nums == NULL || size(queue) == 0) {
        printf("[]");
        return;
    }
    printf("[");
    for (int i = queue->front; i < queue->front + size(queue) - 1; i++) {
        printf("%d, ", queue->nums[i % capacity(queue)]);
    }
    printf("%d]\n", queue->nums[(queue->front + size(queue) - 1) % capacity(queue)]);
}

/* Driver Code */
int main() {
    /* 初始化队列 */
    int capacity = 10;
    ArrayQueue *queue = newArrayQueue(capacity);

    /* 元素入队 */
    push(queue, 1);
    push(queue, 3);
    push(queue, 2);
    push(queue, 5);
    push(queue, 4);
    printf("队列 queue = ");
    printArrayQueue(queue);

    /* 访问队首元素 */
    int peekNum = peek(queue);
    printf("队首元素 peek = %d\r\n", peekNum);

    /* 元素出队 */
    peekNum = pop(queue);
    printf("出队元素 pop = %d ，出队后 queue = ", peekNum);
    printArrayQueue(queue);

    /* 获取队列的长度 */
    int queueSize = size(queue);
    printf("队列长度 size = %d\r\n", queueSize);

    /* 判断队列是否为空 */
    bool empty = isEmpty(queue);
    printf("队列是否为空 = %s\r\n", empty ? "true" : "false");

    /* 测试环形数组 */
    for (int i = 0; i < 10; i++) {
        push(queue, i);
        pop(queue);
        printf("第 %d 轮入队 + 出队后 queue = ", i);
        printArrayQueue(queue);
    }

    // 释放内存
    delArrayQueue(queue);

    return 0;
}
/*
1 3 2 5 4
1 3 2 5 4 0
1 3 2 5 4 0 1
1 3 2 5 4 0 1 2
1 3 2 5 4 0 1 2 3



*/