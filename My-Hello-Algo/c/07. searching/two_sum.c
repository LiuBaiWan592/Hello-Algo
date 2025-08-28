/**
 * @FileName    :two_sum.c
 * @Date        :2024-09-15 11:38:35
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :哈希优化策略解决两数之和问题
 * @Description :我们常通过将线性查找替换为哈希查找来降低算法的时间复杂度。
 *               给定一个整数数组 nums 和一个目标元素 target ，请在数组中搜索“和”为 target 的两个元素，
 *               并返回它们的数组索引。返回任意一个解即可。
 *
 *               方法一、线性查找：以时间换空间
 *               直接遍历所有可能的组合：开启一个两层循环，在每轮中判断两个整数的和是否为 target ，若是，则返回它们的索引。
 *
 *               方法二、哈希查找：以空间换时间
 *               借助一个哈希表，键值对分别为数组元素和元素索引。循环遍历数组:
 *               1. 判断数字 target - nums[i] 是否在哈希表中，若是，则直接返回这两个元素的索引。
 *               2. 将键值对 nums[i] 和索引 i 添加进哈希表。
 */

#include "../utils/common.h"

/* 方法一：暴力枚举 */
// 的时间复杂度为 O(n²) ，空间复杂度为 O(1)
int *twoSumBruteForce(int *nums, int numsSize, int target, int *returnSize) {
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                int *res = malloc(sizeof(int));
                res[0] = i;
                res[1] = j;
                *returnSize = 2;
                return res;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

/* 哈希表 */
typedef struct
{
    int key;
    int val;
    UT_hash_handle hh; // 基于 uthash.h 实现
} HashTable;

HashTable *table = NULL;

/* 哈希表查询 */
HashTable *find(int key) {
    HashTable *res;
    HASH_FIND_INT(table, &key, res);
    return res;
}

/* 哈希表元素插入 */
void insert(int key, int val) {
    HashTable *tmp = find(key);
    if (tmp == NULL) {
        HashTable *res = malloc(sizeof(HashTable));
        res->key = key;
        res->val = val;
        HASH_ADD_INT(table, key, res);
    } else {
        tmp->val = val;
    }
}

/* 方法二：辅助哈希表 */
// 时间复杂度O(n)， 空间复杂度O(n)
int *twoSumHashTable(int *nums, int numsSize, int target, int *returnSize) {
    for (int i = 0; i < numsSize; i++) {
        HashTable *tmp = find(target - nums[i]);
        if (tmp != NULL) {
            int *res = malloc(sizeof(int));
            res[0] = tmp->val;
            res[1] = i;
            *returnSize = 2;
            return res;
        }
        insert(nums[i], i); // 将键值对 nums[i](键) 和索引 i (值)添加进哈希表
    }
    *returnSize = 0;
    return NULL;
}

/* Driver Code */
int main() {
    // ======= Test Case =======
    int nums[] = {2, 7, 11, 15};
    int target = 13;
    // ====== Driver Code ======
    int returnSize;
    int *res = twoSumBruteForce(nums, sizeof(nums) / sizeof(int), target, &returnSize);
    // 方法一
    printf("方法一 res = ");
    printArray(res, returnSize);

    // 方法二
    res = twoSumHashTable(nums, sizeof(nums) / sizeof(int), target, &returnSize);
    printf("方法二 res = ");
    printArray(res, returnSize);

    return 0;
}
