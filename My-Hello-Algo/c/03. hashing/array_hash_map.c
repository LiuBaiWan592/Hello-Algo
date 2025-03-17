/**
 * @FileName    :array_hash_map.c
 * @Date        :2024-08-29 11:06:28
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :基于数组实现的哈希表
 * @Description :结构体：键值对 int->string（Pair)、键值对的集合（MapSet）、基于数组实现的哈希表（ArrayHashMap）
 *               哈希函数、查询操作、添加操作、删除操作
 *               获取所有键值对、获取所有键、获取所有值
 */

#include "../utils/common.h"

/* 哈希表默认大小 */
#define MAX_SIZE 100

/* 键值对 int->string */
typedef struct
{
    int key;
    char *value;
} Pair;

/* 键值对的集合 */
typedef struct
{
    void *set;
    int len;
} MapSet;

/* 基于数组实现的哈希表 */
typedef struct
{
    Pair *bucket[MAX_SIZE];
} ArrayHashMap;

/* 构造函数 */
ArrayHashMap *newArrayHashMap() {
    ArrayHashMap *hmap = malloc(sizeof(ArrayHashMap));
    for (int i = 0; i < MAX_SIZE; i++) {
        hmap->bucket[i] = NULL;
    }
    return hmap;
}

/* 析构函数 */
void delArrayHashMap(ArrayHashMap *hmap) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (hmap->bucket[i] != NULL) {
            free(hmap->bucket[i]->value);
            free(hmap->bucket[i]);
        }
    }
    free(hmap);
}

/* 哈希函数 */
int hashFunc(int key) {
    return key % MAX_SIZE;
}

/* 查询操作 */
const char *get(const ArrayHashMap *hmap, const int key) {
    int index = hashFunc(key);
    const Pair *pair = hmap->bucket[index];
    if (pair == NULL) {
        return NULL;
    }
    return pair->value;
}

/* 添加操作 */
void put(ArrayHashMap *hmap, const int key, const char *value) {
    Pair *pair = malloc(sizeof(pair));
    pair->key = key;
    pair->value = malloc(strlen(value) + 1);
    strcpy(pair->value, value);

    int index = hashFunc(key);
    hmap->bucket[index] = pair;
}

/* 删除操作 */
void removeItem(ArrayHashMap *hmap, const int key) {
    int index = hashFunc(key);
    free(hmap->bucket[index]->value);
    free(hmap->bucket[index]);
    hmap->bucket[index] = NULL;
}

/* 获取所有键值对 */
void pairSet(const ArrayHashMap *hmap, MapSet *set) {
    Pair *entries;
    int i = 0;
    int index = 0;
    int total = 0;
    /* 统计有效键值对数量 */
    for (i = 0; i < MAX_SIZE; i++) {
        if (hmap->bucket[i] != NULL) {
            total++;
        }
    }
    entries = malloc(sizeof(Pair) * total);
    for (i = 0; i < MAX_SIZE; i++) {
        if (hmap->bucket[i] != NULL) {
            entries[index].key = hmap->bucket[i]->key;
            entries[index].value = malloc(strlen(hmap->bucket[i]->value) + 1);
            strcpy(entries[index].value, hmap->bucket[i]->value);
            index++;
        }
    }
    set->set = entries;
    set->len = total;
}

/* 获取所有键 */
void keySet(const ArrayHashMap *hmap, MapSet *set) {
    int *keys;
    int i = 0;
    int index = 0;
    int total = 0;
    /* 统计有效键值对数量 */
    for (i = 0; i < MAX_SIZE; i++) {
        if (hmap->bucket[i] != NULL) {
            total++;
        }
    }
    keys = malloc(sizeof(int) * total);
    for (i = 0; i < MAX_SIZE; i++) {
        if (hmap->bucket[i] != NULL) {
            keys[index] = hmap->bucket[i]->key;
            index++;
        }
    }
    set->set = keys;
    set->len = total;
}

/* 获取所有值 */
void valueSet(const ArrayHashMap *hmap, MapSet *set) {
    char **values;
    int i = 0;
    int index = 0;
    int total;
    for (i = 0; i < MAX_SIZE; i++) {
        if (hmap->bucket[i] != NULL) {
            total++;
        }
    }
    values = malloc(sizeof(char *) * total);
    for (i = 0; i < MAX_SIZE; i++) {
        if (hmap->bucket[i] != NULL) {
            values[index] = hmap->bucket[i]->value;
            index++;
        }
    }
    set->set = values;
    set->len = total;
}

/* 打印哈希表 */
void printArrayHashMap(ArrayHashMap *hmap) {
    MapSet set;
    pairSet(hmap, &set);
    Pair *entries = (Pair *)set.set;
    for (int i = 0; i < set.len; i++) {
        printf("%d -> %s\n", entries[i].key, entries[i].value);
    }
    free(set.set);
}

/* Driver Code */
int main() {
    /* 初始化哈希表 */
    ArrayHashMap *hmap = newArrayHashMap();

    /* 添加操作 */
    // 在哈希表中添加键值对 (key, value)
    put(hmap, 12836, "小哈");
    put(hmap, 15937, "小啰");
    put(hmap, 16750, "小算");
    put(hmap, 13276, "小法");
    put(hmap, 10583, "小鸭");
    printf("\n添加完成后，哈希表为\nKey -> Value\n");
    printArrayHashMap(hmap);

    /* 查询操作 */
    // 向哈希表中输入键 key ，得到值 value
    const char *name = get(hmap, 15937);
    printf("\n输入学号 15937 ，查询到姓名 %s\n", name);

    /* 删除操作 */
    // 在哈希表中删除键值对 (key, value)
    removeItem(hmap, 10583);
    printf("\n删除 10583 后，哈希表为\nKey -> Value\n");
    printArrayHashMap(hmap);

    /* 遍历哈希表 */
    int i;

    printf("\n遍历键值对 Key->Value\n");
    printArrayHashMap(hmap);

    MapSet set;

    keySet(hmap, &set);
    int *keys = (int *)set.set;
    printf("\n单独遍历键 Key\n");
    for (i = 0; i < set.len; i++) {
        printf("%d\n", keys[i]);
    }
    free(set.set);

    valueSet(hmap, &set);
    char **vals = (char **)set.set;
    printf("\n单独遍历键 Value\n");
    for (i = 0; i < set.len; i++) {
        printf("%s\n", vals[i]);
    }
    free(set.set);

    delArrayHashMap(hmap);
    return 0;
}
