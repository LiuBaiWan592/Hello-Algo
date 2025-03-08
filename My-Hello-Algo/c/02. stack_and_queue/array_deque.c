/**
 * @FileName    :array_deque.c
 * @Date        :2024-08-28 11:31:02
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :基于环形数组实现的双向队列
 * @Description :获取双向队列的容量、获取双向队列的长度、判断双向队列是否为空、计算环形数组索引、
 *               元素入队（队首入队，队尾入队）、获取队首/队尾元素、元素出队（队首出队、队尾出队）
 *               打印数组双向队列
 */

#include "../utils/common.h"

/* 基于环形数组实现的双向队列 */
typedef struct
{
    int *nums;       // 用于存储队列元素的数组；
    int front;       // 队首指针，指向队首元素
    int queSize;     // 队列大小，计算队尾指针rear = front + queSize
    int queCapacity; // 队列容量
} ArrayDeque;

/* 构造函数 */
ArrayDeque *newArrayDeque(int capacity) {
    ArrayDeque *deque = malloc(sizeof(ArrayDeque));
    // 初始化数组
    deque->queCapacity = capacity;
    deque->nums = malloc(sizeof(int) * deque->queCapacity);
    deque->front = deque->queSize = 0;
    return deque;
}
/* 析构函数 */
void delArrayDeque(ArrayDeque *deque) {
    free(deque->nums);
    free(deque);
    return;
}
/* 获取双向队列的容量 */
int capacity(ArrayDeque *deque) {
    return deque->queCapacity;
}
/* 获取双向队列的长度 */
int size(ArrayDeque *deque) {
    return deque->queSize;
}
/* 判断双向队列是否为空 */
bool empty(ArrayDeque *deque) {
    return size(deque) == 0;
}
/* 计算环形数组索引 */
int dequeIndex(ArrayDeque *deque, int i) {
    // 通过取余操作实现数组首尾相连
    // 当 i 越过数组尾部时，回到头部
    // 当 i 越过数组头部后，回到尾部
    return (i + capacity(deque)) % capacity(deque);
}
/* 队首入队 */
void pushFirst(ArrayDeque *deque, int num) {
    if (size(deque) == capacity(deque)) {
        printf("双向队列已满\n");
        return;
    }
    // 队首指针向左移动一位
    // 通过取余操作实现 front 越过数组头部回到尾部
    deque->front = dequeIndex(deque, deque->front - 1);
    // 将 num 添加到队首
    deque->nums[deque->front] = num;
    deque->queSize++;
    return;
}

/* 队尾入队 */
void pushLast(ArrayDeque *deque, int num) {
    if (size(deque) == capacity(deque)) {
        printf("双向队列已满\n");
        return;
    }
    // 计算队尾指针，指向队尾索引 + 1
    int rear = dequeIndex(deque, deque->front + deque->queSize);
    // 将 num 添加至队尾
    deque->nums[rear] = num;
    deque->queSize++;
    return;
}
/* 访问队首元素 */
int peekFirst(ArrayDeque *deque) {
    if (empty(deque)) {
        printf("双向队列为空\n");
        return INT_MAX;
    }
    return deque->nums[deque->front];
}
/* 访问队尾元素 */
int peekLast(ArrayDeque *deque) {
    if (empty(deque)) {
        printf("双向队列为空\n");
        return INT_MAX;
    }
    int last = dequeIndex(deque, deque->front + deque->queSize - 1);
    return deque->nums[last];
}
/* 队首出队 */
int popFirst(ArrayDeque *deque) {
    int num = peekFirst(deque);
    deque->front = dequeIndex(deque, deque->front + 1);
    deque->queSize--;
    return num;
}
/* 队尾出队 */
int popLast(ArrayDeque *deque) {
    int num = peekLast(deque);
    deque->queSize--;
    return num;
}

/* 打印数组双向队列 */
void printArrayQueue(ArrayDeque *deque) {
    if (deque->nums == NULL || empty(deque)) {
        printf("[]");
        return;
    }
    printf("[");
    for (int i = 0; i < size(deque) - 1; i++) {
        printf("%d, ", deque->nums[dequeIndex(deque, deque->front + i)]);
    }
    printf("%d]\n", deque->nums[dequeIndex(deque, deque->front + size(deque) - 1)]);
}

/* Driver Code */
int main() {
    /* 初始化队列 */
    int capacity = 10;
    ArrayDeque *deque = newArrayDeque(capacity);
    pushLast(deque, 3);
    pushLast(deque, 2);
    pushLast(deque, 5);
    printf("双向队列 deque = ");
    printArrayQueue(deque);

    /* 访问元素 */
    int peekFirstNum = peekFirst(deque);
    printf("队首元素 peekFirst = %d\r\n", peekFirstNum);
    int peekLastNum = peekLast(deque);
    printf("队尾元素 peekLast = %d\r\n", peekLastNum);

    /* 元素入队 */
    pushLast(deque, 4);
    printf("元素 4 队尾入队后 deque = ");
    printArrayQueue(deque);
    pushFirst(deque, 1);
    printf("元素 1 队首入队后 deque = ");
    printArrayQueue(deque);

    /* 元素出队 */
    int popLastNum = popLast(deque);
    printf("队尾出队元素 = %d ，队尾出队后 deque= ", popLastNum);
    printArrayQueue(deque);
    int popFirstNum = popFirst(deque);
    printf("队首出队元素 = %d ，队首出队后 deque= ", popFirstNum);
    printArrayQueue(deque);

    /* 获取队列的长度 */
    int dequeSize = size(deque);
    printf("双向队列长度 size = %d\r\n", dequeSize);

    /* 判断队列是否为空 */
    bool isEmpty = empty(deque);
    printf("队列是否为空 = %s\r\n", isEmpty ? "true" : "false");

    // 释放内存
    delArrayDeque(deque);

    return 0;
}
