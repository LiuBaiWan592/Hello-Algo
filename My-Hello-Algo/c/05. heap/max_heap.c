/**
 * @FileName    :my_heap.c
 * @Date        :2024-09-05 15:02:58
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :堆的实现(以大顶堆为例)
 * @Description :堆（heap）是一种满足特定条件的完全二叉树，主要可分为两种类型：
 *                  小顶堆（min heap）：任意节点的值 <= 其子节点的值。
 *                  大顶堆（max heap）：任意节点的值 >= 其子节点的值。
 *               堆通常用于实现优先队列（priority queue），大顶堆相当于元素按从大到小的顺序出队的优先队列。
 *               本文件实现的是大顶堆。若要将其转换为小顶堆，只需将所有大小逻辑判断进行逆转（例如，将 >= 替换为 <= ）。
 */
#include "../utils/common.h"

#define MAX_SIZE 5000

/* 大顶堆 */
typedef struct
{
    // size 代表的是实际元素的个数
    int size;
    // 使用预先分配内存的数组，避免扩容
    int data[MAX_SIZE];
} MaxHeap;

// 函数声明
void siftDown(MaxHeap *maxHeap, int i); // 从节点 i 开始，从【顶】至【底】堆化
void siftUp(MaxHeap *maxHeap, int i);   // 从节点 i 开始，从【底】至【顶】堆化
int parent(int i);                      // 向下取整获取父节点的索引

/* 构造函数，根据切片建堆 时间复杂度为 O(n) */
// 1. 将列表所有元素原封不动地添加到堆中，此时堆的性质尚未得到满足。
// 2. 倒序遍历堆（层序遍历的倒序），依次对每个非叶节点执行“从顶至底堆化”。
MaxHeap *newMaxHeap(int *nums, int size) {
    // 所有元素入堆
    MaxHeap *maxHeap = malloc(sizeof(MaxHeap));
    maxHeap->size = size;
    memcpy(maxHeap->data, nums, size * sizeof(int));
    // 自底向上堆化除叶节点以外的其他所有节点
    for (int i = parent(size - 1); i >= 0; i--) {
        siftDown(maxHeap, i);
    }
    return maxHeap;
}

/* 析构函数 */
void delMaxHeap(MaxHeap *maxHeap) {
    // 释放内存
    free(maxHeap);
}

/* 获取左子节点的索引 */
int left(int i) {
    return (2 * i + 1);
}

/* 获取右子节点的索引 */
int right(int i) {
    return (2 * i + 2);
}

/* 获取父节点的索引 */
int parent(int i) {
    return (i - 1) / 2; // 向下取整
}

/* 交换元素 */
void swap(MaxHeap *maxHeap, int i, int j) {
    int temp = maxHeap->data[i];
    maxHeap->data[i] = maxHeap->data[j];
    maxHeap->data[j] = temp;
}
/* 获取堆大小 */
int size(MaxHeap *maxHeap) {
    return maxHeap->size;
}

/* 判断堆是否为空 */
bool isEmpty(MaxHeap *maxHeap) {
    return size(maxHeap) <= 0;
}

/* 访问堆顶元素 */
int peek(MaxHeap *maxHeap) {
    return maxHeap->data[0];
}

/* 元素入堆 */
void push(MaxHeap *maxHeap, int val) {
    // 默认情况下，不应该添加这么多节点
    if (maxHeap->size == MAX_SIZE) {
        printf("Heap is full!");
        return;
    }
    // 添加节点
    maxHeap->data[maxHeap->size] = val;
    maxHeap->size++;

    // 从底至顶堆化
    siftUp(maxHeap, maxHeap->size - 1);
}

/* 从节点 i 开始，从底至顶堆化 */
void siftUp(MaxHeap *maxHeap, int i) {
    while (true) {
        // 获取节点 i 的父节点
        int p = parent(i);
        // 当“越过根节点”或“节点无须修复”时，结束堆化
        if (i < 0 || maxHeap->data[i] <= maxHeap->data[p]) {
            break;
        }
        // 否则，交换两节点
        swap(maxHeap, i, p);
        // 循环向上堆化
        i = p;
    }
}

/* 元素出堆 */
int pop(MaxHeap *maxHeap) {
    // 判空处理
    if (isEmpty(maxHeap)) {
        printf("Heap is empty!");
        return INT_MAX;
    }
    // 交换根节点与最右叶节点（交换首元素与尾元素）
    swap(maxHeap, 0, size(maxHeap) - 1);
    // 删除节点
    int val = maxHeap->data[size(maxHeap) - 1];
    maxHeap->size--;
    // 从顶至底堆化
    siftDown(maxHeap, 0);
    // 返回堆顶元素(交换到堆尾被删除的为原来的堆顶元素)
    return val;
}

/* 从节点 i 开始，从顶至底堆化 */
void siftDown(MaxHeap *maxHeap, int i) {
    while (true) {
        int s = size(maxHeap);
        // 判断节点 i, l, r 中值最大的节点，记为 max
        int l = left(i);
        int r = right(i);
        int max = i;
        // 若节点 i 最大或索引 l, r 越界，则无须继续堆化，跳出
        if (l < s && maxHeap->data[l] > maxHeap->data[max]) {
            max = l;
        }
        if (r < s && maxHeap->data[r] > maxHeap->data[max]) {
            max = r;
        }
        if (max == i) {
            break;
        }
        // 交换两节点
        swap(maxHeap, i, max);
        // 循环向下堆化
        i = max;
    }
}