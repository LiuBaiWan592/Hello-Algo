/**
 * @FileName    :hash_map_chaining.c
 * @Date        :2024-08-30 11:09:34
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :链式地址解决哈希冲突实现哈希表
 * @Description :结构体：键值对 int->string（Pair)、链表节点（PairNode）、链式地址哈希表（HashMapCahining）
 *               哈希函数、负载因子计算、查询操作、添加操作、扩容哈希表、删除操作、打印哈希表
 */

#include "../utils/common.h"

#define MAX_SIZE 100

/* 键值对 int->string */
typedef struct
{
    int key;
    char value[MAX_SIZE];
} Pair;

/* 链表节点 */
typedef struct PairNode {
    Pair *pair;
    struct PairNode *next;
} PairNode;

/* 链式地址哈希表 */
typedef struct
{
    PairNode **buckets; // 桶数组，每个数组元素是指向链表节点的指针
    int size;           // 键值对数量
    int capacity;       // 哈希表容量
    double loadThres;   // 触发扩容的负载因子阈值
    int extendRatio;    // 扩容倍数
} HashMapChaining;

/* 构造函数 */
HashMapChaining *newHashMapChaining() {
    HashMapChaining *hashMap = malloc(sizeof(HashMapChaining));
    hashMap->size = 0;
    hashMap->capacity = 4;
    hashMap->loadThres = 2.0 / 3.0;
    hashMap->extendRatio = 2;
    hashMap->buckets = malloc(sizeof(PairNode *) * hashMap->capacity);
    for (int i = 0; i < hashMap->capacity; i++) {
        hashMap->buckets[i] = NULL;
    }
    return hashMap;
}

/* 析构函数 */
void delHashMapChaining(HashMapChaining *hashMap) {
    for (int i = 0; i < hashMap->capacity; i++) {
        PairNode *current = hashMap->buckets[i];
        while (current) {
            PairNode *temp = current;
            current = temp->next;
            free(temp->pair);
            free(temp);
        }
    }
    free(hashMap->buckets);
    free(hashMap);
}

/* 哈希函数 */
int hashFunc(const HashMapChaining *hashMap, const int key) {
    return key % hashMap->capacity;
}

/* 负载因子 */
double loadFactor(const HashMapChaining *hashMap) {
    return (double)hashMap->size / (double)hashMap->capacity;
}

/* 查询操作 */
char *get(const HashMapChaining *hashMap, const int key) {
    int index = hashFunc(hashMap, key);
    // 遍历桶，若找到 key ，则返回对应 val
    PairNode *current = hashMap->buckets[index];
    while (current) {
        if (current->pair->key == key) {
            return current->pair->value;
        }
        current = current->next;
    }
    return ""; // 若未找到 key ，则返回空字符串
}

/* 添加操作声明 */
void put(HashMapChaining *hashMap, const int key, const char *value);

/* 扩容哈希表 */
void extend(HashMapChaining *hashMap) {
    // 暂存原哈希表
    int oldCapacity = hashMap->capacity;
    PairNode **oldBuckets = hashMap->buckets;
    // 初始化扩容后的新哈希表
    hashMap->capacity *= hashMap->extendRatio;
    hashMap->buckets = malloc(sizeof(PairNode *) * hashMap->capacity);
    for (int i = 0; i < hashMap->capacity; i++) {
        hashMap->buckets[i] = NULL;
    }
    hashMap->size = 0;
    // 将键值对从原哈希表搬运至新哈希表
    for (int i = 0; i < oldCapacity; i++) {
        PairNode *current = oldBuckets[i];
        while (current) {
            put(hashMap, current->pair->key, current->pair->value);
            PairNode *temp = current;
            current = current->next;
            free(temp->pair);
            free(temp);
        }
    }
    free(oldBuckets);
}

/* 添加操作 */
void put(HashMapChaining *hashMap, const int key, const char *value) {
    // 当负载因子超过阈值时，执行扩容
    if (loadFactor(hashMap) > hashMap->loadThres) {
        extend(hashMap);
    }
    int index = hashFunc(hashMap, key);
    // 遍历桶，若遇到指定 key ，则更新对应 val 并返回
    PairNode *current = hashMap->buckets[index];
    while (current) {
        // 若遇到指定 key ，则更新对应 val 并返回
        if (current->pair->key == key) {
            strcpy(current->pair->value, value);
            return;
        }
        current = current->next;
    }
    // 若无该 key ，则将键值对添加至链表头部
    Pair *newPair = malloc(sizeof(Pair));
    newPair->key = key;
    strcpy(newPair->value, value);

    PairNode *newPairNode = malloc(sizeof(PairNode));
    newPairNode->pair = newPair;
    newPairNode->next = hashMap->buckets[index];
    hashMap->buckets[index] = newPairNode;
    hashMap->size++;
    return;
}

/* 删除操作 */
void removeItem(HashMapChaining *hashMap, const int key) {
    int index = hashFunc(hashMap, key);
    PairNode *current = hashMap->buckets[index];
    PairNode *pre = NULL;
    while (current) {
        if (current->pair->key == key) {
            if (pre) {
                pre->next = current->next;
            } else {
                hashMap->buckets[index] = current->next;
            }
            // 释放内存
            free(current->pair);
            free(current);
            return;
        }
        pre = current;
        current = current->next;
    }
}

/* 打印哈希表 */
void printHashMapChaining(HashMapChaining *hashMap) {
    for (int i = 0; i < hashMap->capacity; i++) {
        PairNode *current = hashMap->buckets[i];
        printf("[");
        while (current) {
            printf("%d -> %s, ", current->pair->key, current->pair->value);
            current = current->next;
        }
        printf("]\n");
    }
}

/* Driver Code */
int main() {
    /* 初始化哈希表 */
    HashMapChaining *hashMap = newHashMapChaining();

    /* 添加操作 */
    // 在哈希表中添加键值对 (key, value)
    put(hashMap, 12836, "小哈");
    put(hashMap, 15937, "小啰");
    put(hashMap, 16750, "小算");
    put(hashMap, 13276, "小法");
    put(hashMap, 10583, "小鸭");
    printf("\n添加完成后，哈希表为\nKey -> Value\n");
    printHashMapChaining(hashMap);

    /* 查询操作 */
    // 向哈希表中输入键 key ，得到值 value
    char *name = get(hashMap, 13276);
    printf("\n输入学号 13276 ，查询到姓名 %s\n", name);

    /* 删除操作 */
    // 在哈希表中删除键值对 (key, value)
    removeItem(hashMap, 12836);
    printf("\n删除学号 12836 后，哈希表为\nKey -> Value\n");
    printHashMapChaining(hashMap);

    /* 释放哈希表空间 */
    delHashMapChaining(hashMap);

    return 0;
}
