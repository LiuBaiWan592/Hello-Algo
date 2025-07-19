/**
 * @FileName    :min_heap.c
 * @Date        :2024-09-06 11:37:02
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :堆的实现(根据大顶堆实现小顶堆)
 * @Description :将大顶堆的所有大小逻辑判断进行逆转
 */

#include "../utils/common.h"

#define MAX_SIZE 5000

/* 小顶堆 */
typedef struct
{
    // size 代表的是实际元素的个数
    int size;
    // 使用预先分配内存的数组，避免扩容
    int data[MAX_SIZE];
} MinHeap;

// 函数声明
void siftDown(MinHeap *minHeap, int i); // 从节点 i 开始，从【顶】至【底】堆化
void siftUp(MinHeap *minHeap, int i);   // 从节点 i 开始，从【底】至【顶】堆化
int parent(int i);                      // 向下取整获取父节点的索引

/* 构造函数，根据切片建堆 时间复杂度为 O(n) */
// 1. 将列表所有元素原封不动地添加到堆中，此时堆的性质尚未得到满足。
// 2. 倒序遍历堆（层序遍历的倒序），依次对每个非叶节点执行“从顶至底堆化”。
MinHeap *newMinHeap(int *nums, int size) {
    // 所有元素入堆
    MinHeap *minHeap = malloc(sizeof(MinHeap));
    minHeap->size = size;
    memcpy(minHeap->data, nums, size * sizeof(int));
    // 自底向上堆化除叶节点以外的其他所有节点
    for (int i = parent(size - 1); i >= 0; i--) {
        siftDown(minHeap, i);
    }
    return minHeap;
}

/* 析构函数 */
void delMinHeap(MinHeap *minHeap) {
    // 释放内存
    free(minHeap);
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
void swap(MinHeap *minHeap, int i, int j) {
    int temp = minHeap->data[i];
    minHeap->data[i] = minHeap->data[j];
    minHeap->data[j] = temp;
}
/* 获取堆大小 */
int size(MinHeap *minHeap) {
    return minHeap->size;
}

/* 判断堆是否为空 */
bool isEmpty(MinHeap *minHeap) {
    return size(minHeap) <= 0;
}

/* 访问堆顶元素 */
int peek(MinHeap *minHeap) {
    return minHeap->data[0];
}

/* 元素入堆 */
void push(MinHeap *minHeap, int val) {
    // 默认情况下，不应该添加这么多节点
    if (minHeap->size == MAX_SIZE) {
        printf("Heap is full!");
        return;
    }
    // 添加节点
    minHeap->data[minHeap->size] = val;
    minHeap->size++;

    // 从底至顶堆化
    siftUp(minHeap, minHeap->size - 1);
}

/* 从节点 i 开始，从底至顶堆化 */
void siftUp(MinHeap *minHeap, int i) {
    while (true) {
        // 获取节点 i 的父节点
        int p = parent(i);
        // 当“越过根节点”或“节点无须修复”时，结束堆化
        if (i < 0 || minHeap->data[i] >= minHeap->data[p]) {
            break;
        }
        // 否则，交换两节点
        swap(minHeap, i, p);
        // 循环向上堆化
        i = p;
    }
}

/* 元素出堆 */
int pop(MinHeap *minHeap) {
    // 判空处理
    if (isEmpty(minHeap)) {
        printf("Heap is empty!");
        return INT_MAX;
    }
    // 交换根节点与最右叶节点（交换首元素与尾元素）
    swap(minHeap, 0, size(minHeap) - 1);
    // 删除节点
    int val = minHeap->data[size(minHeap) - 1];
    minHeap->size--;
    // 从顶至底堆化
    siftDown(minHeap, 0);
    // 返回堆顶元素(交换到堆尾被删除的为原来的堆顶元素)
    return val;
}

/* 从节点 i 开始，从顶至底堆化 */
void siftDown(MinHeap *minHeap, int i) {
    while (true) {
        int s = size(minHeap);
        // 判断节点 i, l, r 中值最小的节点，记为 min
        int l = left(i);
        int r = right(i);
        int min = i;
        // 若节点 i 最大或索引 l, r 越界，则无须继续堆化，跳出
        if (l < s && minHeap->data[l] < minHeap->data[min]) {
            min = l;
        }
        if (r < s && minHeap->data[r] < minHeap->data[min]) {
            min = r;
        }
        if (min == i) {
            break;
        }
        // 交换两节点
        swap(minHeap, i, min);
        // 循环向下堆化
        i = min;
    }
}