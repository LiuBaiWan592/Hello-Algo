/**
 * @FileName    :hash_map_open_addressing.c
 * @Date        :2024-08-31 10:46:33
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :懒删除的开放寻址（线性探测）哈希表
 * @Description :结构体：键值对 int->string、开放寻址哈希表
 *               哈希函数、负载因子计算、搜索key对应的桶索引、查询操作、添加操作、删除操作、扩容哈希表、打印哈希表
 */

#include "../utils/common.h"

/* 键值对 int->string */
typedef struct
{
    int key;
    char *value;
} Pair;

/* 开放寻址哈希表 */
typedef struct
{
    int size;         // 键值对数量
    int capacity;     // 哈希表容量
    double loadThres; // 触发扩容负载因子的阈值
    int extendRatio;  // 扩容倍数
    Pair **bucket;    // 数组桶
    Pair *TOMBSTONE;  // 删除标记
} HashMapOpenAddressing;

/* 构造函数 */
HashMapOpenAddressing *newHashMapOpenAddressing() {
    HashMapOpenAddressing *hashMap = malloc(sizeof(HashMapOpenAddressing));
    hashMap->size = 0;
    hashMap->capacity = 4;
    hashMap->loadThres = 2.0 / 3.0;
    hashMap->extendRatio = 2;
    hashMap->bucket = calloc(hashMap->capacity, sizeof(Pair *));
    hashMap->TOMBSTONE = malloc(sizeof(Pair));
    hashMap->TOMBSTONE->key = -1;
    hashMap->TOMBSTONE->value = "";
    return hashMap;
}

/* 析构函数 */
void delHashMapOpenAddressing(HashMapOpenAddressing *hashMap) {
    for (int i = 0; i < hashMap->capacity; i++) {
        Pair *pair = hashMap->bucket[i];
        if (pair != NULL && pair != hashMap->TOMBSTONE) {
            free(pair->value);
            free(pair);
        }
    }
    free(hashMap->bucket);
    free(hashMap->TOMBSTONE);
    free(hashMap);
}

/* 哈希函数 */
int hashFunc(const HashMapOpenAddressing *hashMap, const int key) {
    return key % hashMap->capacity;
}

/* 负载因子 */
double loadFactor(HashMapOpenAddressing *hashMap) {
    return (double)hashMap->size / (double)hashMap->capacity;
}

/* 扩容哈希表 */
void extend(HashMapOpenAddressing *hashMap);

/* 搜索 key 对应的桶索引 */
int findBucket(HashMapOpenAddressing *hashMap, const int key) {
    int index = hashFunc(hashMap, key);
    int firstTombstone = -1;
    // 线性探测，当遇到空桶时跳出
    while (hashMap->bucket[index]) {
        // 若遇到 key ，返回对应的桶索引
        if (hashMap->bucket[index]->key == key) {
            // 若之前遇到了删除标记，则将键值对移动至该索引处
            if (firstTombstone != -1) {
                hashMap->bucket[firstTombstone] = hashMap->bucket[index];
                hashMap->bucket[index] = hashMap->TOMBSTONE;
                return firstTombstone; // 返回移动后的桶索引
            }
            return index; // 返回查找到的桶索引
        }
        // 记录遇到的首个删除标记
        if (firstTombstone == -1 && hashMap->bucket[index] == hashMap->TOMBSTONE) {
            firstTombstone = index;
        }
        // 计算桶索引，越过尾部则返回头部
        index = (index + 1) % hashMap->capacity;
    }
    // 若 key 不存在，则返回添加点的索引
    return firstTombstone == -1 ? index : firstTombstone;
}

/* 查询操作 */
char *get(HashMapOpenAddressing *hashMap, const int key) {
    // 搜索 key 对应的桶索引
    int index = findBucket(hashMap, key);
    Pair *current = hashMap->bucket[index];
    // 若找到键值对，则返回对应 val
    // if (current != NULL && current != hashMap->TOMBSTONE)
    // {
    //     return current->value;
    // }
    if (current != NULL) {
        return current->value;
    }
    // 若键值对不存在，则返回空字符串
    return "";
}

/* 添加操作 */
void put(HashMapOpenAddressing *hashMap, const int key, const char *value) {
    // 当负载因子超过阈值时，执行扩容
    if (loadFactor(hashMap) > hashMap->loadThres) {
        extend(hashMap);
    }
    // 搜索 key 对应的桶索引以及相应的键值对
    int index = findBucket(hashMap, key);
    Pair *const current = hashMap->bucket[index];
    // 若找到键值对，则覆盖 val 并返回
    if (current != NULL && current != hashMap->TOMBSTONE) {
        free(current->value);
        current->value = malloc(sizeof(strlen(value) + 1));
        strcpy(current->value, value);
        current->value[strlen(value)] = '\0';
        return;
    }
    // 若键值对不存在，则添加该键值对
    Pair *pair = malloc(sizeof(Pair));
    pair->key = key;
    pair->value = malloc(sizeof(value) + 1);
    strcpy(pair->value, value);
    pair->value[strlen(value)] = '\0';

    hashMap->bucket[index] = pair;
    hashMap->size++;
}

/* 删除操作 */
void removeItem(HashMapOpenAddressing *hashMap, const int key) {
    // 搜索 key 对应的桶索引
    int index = findBucket(hashMap, key);
    Pair *current = hashMap->bucket[index];
    // 若找到键值对，则用删除标记覆盖它
    if (current != NULL && current != hashMap->TOMBSTONE) {
        Pair *temp = current;
        free(temp->value);
        free(temp);
        hashMap->bucket[index] = hashMap->TOMBSTONE;
        hashMap->size--;
    }
}

/* 扩容哈希表 */
void extend(HashMapOpenAddressing *hashMap) {
    // 暂存原哈希表
    Pair **tempBucket = hashMap->bucket;
    int oldCapacity = hashMap->capacity;
    // 初始化扩容后的新哈希表
    hashMap->capacity *= hashMap->extendRatio;
    hashMap->bucket = calloc(hashMap->capacity, sizeof(Pair *));
    hashMap->size = 0;
    // 将键值对从原哈希表搬运至新哈希表
    for (int i = 0; i < oldCapacity; i++) {
        Pair *pair = tempBucket[i];
        if (pair != NULL && pair != hashMap->TOMBSTONE) {
            put(hashMap, pair->key, pair->value);
            free(pair->value);
            free(pair);
        }
    }
    free(tempBucket);
}

/* 打印哈希表 */
void printHashMapOpenAddressing(HashMapOpenAddressing *hashMap) {
    for (int i = 0; i < hashMap->capacity; i++) {
        Pair *pair = hashMap->bucket[i];
        if (pair == NULL) {
            printf("NULL\n");
        } else if (pair == hashMap->TOMBSTONE) {
            printf("TOMBSTONE\n");
        } else {
            printf("%d -> %s\n", pair->key, pair->value);
        }
    }
}

/* Driver Code */
int main() {
    // 初始化哈希表
    HashMapOpenAddressing *hashmap = newHashMapOpenAddressing();

    // 添加操作
    // 在哈希表中添加键值对 (key, val)
    put(hashmap, 12836, "小哈");
    put(hashmap, 15937, "小啰");
    put(hashmap, 16750, "小算");
    put(hashmap, 13276, "小法");
    put(hashmap, 10583, "小鸭");
    printf("\n添加完成后，哈希表为\nKey -> Value\n");
    printHashMapOpenAddressing(hashmap);

    // 查询操作
    // 向哈希表中输入键 key ，得到值 val
    char *name = get(hashmap, 13276);
    printf("\n输入学号 13276 ，查询到姓名 %s\n", name);

    // 删除操作
    // 在哈希表中删除键值对 (key, val)
    removeItem(hashmap, 16750);
    printf("\n删除 16750 后，哈希表为\nKey -> Value\n");
    printHashMapOpenAddressing(hashmap);

    // 销毁哈希表
    delHashMapOpenAddressing(hashmap);
    return 0;
}
