/**
 * @FileName    :array.c
 * @Date        :2024-07-25 18:27:03
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :数组的基本操作
 * @Description :数组的初始化创建、元素随机访问、元素的插入删除、遍历求和、查找指定元素的索引、扩展数组长度
 */

#include "../utils/common.h"

/* 随机访问元素 O(1) */
int randomAccess(int *nums, int size) {
    // 初始化随机数，当前时间戳作为随机种子
    srand((unsigned int)time(0));
    // 初始化随机数，当前当前进程Pid作为随机种子
    // srand((unsigned int)getpid());
    // 在区间 [0, size) 中随机抽取一个数字
    int randomIndex = rand() % size;
    // 获取并返回随机元素
    return nums[randomIndex];
}

/* 在数组的索引 index 处插入元素 num O(n)*/
void insert(int *nums, int size, int num, int index) {
    // 把索引 index 以及之后的所有元素向后移动一位
    for (int i = size - 1; i > index; i--) {
        nums[i] = nums[i - 1];
    }
    // 将 num 赋给 index 处的元素
    nums[index] = num;
}

/* 删除索引 index 处的元素 O(n)*/
// 注意：stdio.h 占用了 remove 关键词
void removeItem(int *nums, int size, int index) {
    // 把索引 index 之后的所有元素向前移动一位
    for (int i = index; i < size - 1; i++) {
        nums[i] = nums[i + 1];
    }
    // 将最后的空缺元素置为0
    nums[size - 1] = 0;
}

/* 遍历数组求元素和 O(n)*/
int traverse(int *nums, int size) {
    int count = 0;
    // 通过索引遍历数组，并计算元素和
    for (int i = 0; i < size; i++) {
        count += nums[i];
    }
    return count;
}

/* 在数组中查找指定元素的索引 O(n)*/
int find(int *nums, int size, int targer) {
    // 遍历数组查找首个与目标值相同的元素索引
    for (int i = 0; i < size; i++) {
        if (nums[i] == targer)
            return i;
    }
    // 没有找到则返回索引 -1
    return -1;
}

/* 扩展数组长度 */
int *extend(int *nums, int size, int enlarge) {
    // 初始化一个扩展长度后的数组
    int *res = (int *)malloc(sizeof(int) * (size + enlarge));
    // 将原数组中的所有元素复制到新数组
    for (int i = 0; i < size; i++) {
        res[i] = nums[i];
    }
    // 初始化扩展后的空间
    for (int i = size; i < size + enlarge; i++) {
        res[i] = 0;
    }
    // 返回扩展后的新数组
    return res;
}

int main() {
    /* 初始化数组 */
    int arr[5] = {0}; // { 0, 0, 0, 0, 0 }
    int nums[5] = {1, 3, 2, 5, 4};

    /* 获取数组长度 */
    int size = sizeof(nums) / sizeof(nums[0]);
    printf("数组 nums = ");
    printArray(nums, size);

    /* 随机访问 */
    int randomNum = randomAccess(nums, size);
    printf("在 nums 中获取随机元素为 =  %d\n", randomNum);

    /* 插入元素 */
    insert(nums, size, 6, 3);
    printf("在索引 3 处插入数字 6 ，得到 nums = ");
    printArray(nums, size);

    /* 删除元素 */
    removeItem(nums, size, 2);
    printf("删除索引 2 处的元素，得到 nums = ");
    printArray(nums, size);

    /* 遍历求和 */
    int count = traverse(nums, size);
    printf("遍历数组 nums 求和结果 = %d\n", count);

    /* 线性查找指定元素*/
    int index = find(nums, size, 3);
    printf("在 nums 中查找元素 3 的索引 = %d\n", index);

    /* 扩容数组 */
    int enlarge = 3;
    int *res = extend(nums, size, enlarge);
    size += enlarge;
    printf("将数组长度扩展至 8 ，得到 nums = ");
    printArray(res, size);

    return 0;
}