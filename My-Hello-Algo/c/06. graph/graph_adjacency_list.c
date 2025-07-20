/**
 * @FileName    :graph_adjacency_list.c
 * @Date        :2024-09-09 11:10:21
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :基于邻接表的实现图
 * @Description :设无向图的顶点总数为 n 、边总数为 m ，则实现各种操作如下：
 *               添加边：在顶点对应链表的末尾添加边即可，使用 O(1) 时间。因为是无向图，所以需要同时添加两个方向的边。
 *               删除边：在顶点对应链表中查找并删除指定边，使用 O(m) 时间。在无向图中，需要同时删除两个方向的边。
 *               添加顶点：在邻接表中添加一个链表，并将新增顶点作为链表头节点，使用 O(1) 时间。
 *               删除顶点：需遍历整个邻接表，删除包含指定顶点的所有边，使用 O(n + m) 时间。
 *               初始化：在邻接表中创建 n 个顶点和 m 条边，使用 O(n + m) 时间。
 *
 *               可以采用以下方法进行优化，但是由于C语言没有内置哈希表和动态数组，仍然采用传统方法：
 *               为了方便添加与删除顶点，以及简化代码，我们使用列表（动态数组）来代替链表。
 *               使用哈希表来存储邻接表，key 为顶点实例，value 为该顶点的邻接顶点列表（链表）。
 *               在邻接表中使用 Vertex 类来表示顶点，避免删除顶点后移动其后的整个邻接表。
 */

#include "../utils/common.h"

// 假设节点最大数量为 100
#define MAX_SIZE 100

/* 节点结构体 */
typedef struct AdjListNode {
    Vertex *vertex;           // 顶点
    struct AdjListNode *next; // 后继节点
} AdjListNode;

/* 基于邻接表实现的无向图类 */
typedef struct
{
    AdjListNode *heads[MAX_SIZE]; // 节点数组
    int size;                     // 节点数量
} GraphAdjList;

/* 构造函数 */
GraphAdjList *newGraphAdjList() {
    GraphAdjList *graph = malloc(sizeof(GraphAdjList));
    graph->size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        graph->heads[i] = NULL;
    }
    return graph;
}

/* 析构函数 */
void delGraphAdjList(GraphAdjList *graph) {
    for (int i = 0; i < graph->size; i++) {
        AdjListNode *pre = graph->heads[i];
        AdjListNode *cur = pre->next;
        free(cur);
        graph->heads[i]->next = NULL;
        free(graph->heads[i]->vertex);
    }
    free(graph);
}

/* 查找顶点对应的节点 */
AdjListNode *findNode(GraphAdjList *graph, Vertex *vet) {
    for (int i = 0; i < graph->size; i++) {
        if (graph->heads[i]->vertex == vet) {
            return graph->heads[i];
        }
    }
    return NULL;
}

/* 添加边辅助函数 */
void addEdgeHelper(AdjListNode *head, Vertex *vet) {
    AdjListNode *node = malloc(sizeof(AdjListNode));
    node->vertex = vet;
    // 头插法
    node->next = head->next;
    head->next = node;
}

/* 添加边 */
void addEdge(GraphAdjList *graph, Vertex *v1, Vertex *v2) {
    AdjListNode *h1 = findNode(graph, v1);
    AdjListNode *h2 = findNode(graph, v2);
    if (h1 == NULL || h2 == NULL || h2 == h1) {
        printf("Vertex dose not exist, or v1 and v2 is same!\n");
        return;
    }
    // 添加边，无向图添加两条边
    addEdgeHelper(h1, v2);
    addEdgeHelper(h2, v1);
}

/* 删除边辅助函数 */
void removeEdgeHelper(AdjListNode *head, Vertex *vet) {
    AdjListNode *pre = head;
    AdjListNode *cur = pre->next;
    // 在链表中搜索 vet 对应节点
    while (cur != NULL && cur->vertex != vet) {
        pre = cur;
        cur = pre->next;
    }
    if (cur == NULL) {
        printf("Edge %d -- %d is not exitent!\n", head->vertex->val, vet->val);
        return;
    }
    // 将 vet 对应节点从链表中删除
    pre->next = cur->next;
    // 释放内存
    free(cur);
}

/* 删除边 */
void removeEdge(GraphAdjList *graph, Vertex *v1, Vertex *v2) {
    AdjListNode *h1 = findNode(graph, v1);
    AdjListNode *h2 = findNode(graph, v2);
    if (h1 == NULL || h2 == NULL || h1 == h2) {
        printf("Vertex dose not exist, or v1 and v2 is same!\n");
        return;
    }
    removeEdgeHelper(h1, v2);
    removeEdgeHelper(h2, v1);
}

/* 添加顶点 */
void addVertex(GraphAdjList *graph, Vertex *vet) {
    if (graph == NULL || graph->size >= MAX_SIZE) {
        printf("Graph is None or Full!\n");
    }
    AdjListNode *head = malloc(sizeof(AdjListNode));
    head->vertex = vet;
    head->next = NULL;
    // 在邻接表中添加一个新链表
    graph->heads[graph->size++] = head;
}

/* 删除顶点 */
void removeVertex(GraphAdjList *graph, Vertex *vet) {
    AdjListNode *node = findNode(graph, vet);
    if (node == NULL) {
        printf("Vertex is not existent!\n");
    }
    // 在邻接表中依次删除顶点 vet 对应的链表
    AdjListNode *cur = node, *pre = NULL;
    while (cur != NULL) {
        pre = cur;
        cur = cur->next;
        free(pre);
    }
    node->next = NULL;
    // 遍历其他顶点的链表，删除所有包含 vet 的边
    for (int i = 0; i < graph->size; i++) {
        cur = graph->heads[i];
        pre = NULL;
        while (cur != NULL) {
            pre = cur;
            cur = pre->next;
            if (cur != NULL && cur->vertex == vet) {
                pre->next = cur->next;
                free(cur);
                break;
            }
        }
    }
    // 将该顶点之后的顶点向前移动，以填补空缺
    int i = 0;
    for (i = 0; i < graph->size; i++) {
        if (graph->heads[i] == node) {
            break;
        }
    }
    for (int j = i; j < graph->size - 1; j++) {
        graph->heads[j] = graph->heads[j + 1];
    }
    graph->size--;
    free(vet);
}

/* 打印邻接表 */
void printGraph(const GraphAdjList *graph) {
    printf("邻接表 =\n");
    for (int i = 0; i < graph->size; ++i) {
        AdjListNode *node = graph->heads[i];
        printf("%d: [", node->vertex->val);
        node = node->next;
        while (node) {
            printf("%d, ", node->vertex->val);
            node = node->next;
        }
        printf("]\n");
    }
}
