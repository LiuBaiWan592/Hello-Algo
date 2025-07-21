/**
 * @FileName    :graph_bfs.c
 * @Date        :2024-09-10 15:41:08
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :图的广度优先遍历（BFS）
 * @Description :广度优先遍历是一种由近及远的遍历方式，从某个节点出发，始终优先访问距离最近的顶点，并一层层向外扩张。
 *               BFS 通常借助队列来实现，队列具有“先入先出”的性质，这与 BFS 的“由近及远”的思想异曲同工。
 *               1. 将遍历起始顶点 startVet 加入队列，并开启循环。
 *               2. 在循环的每轮迭代中，弹出队首顶点并记录访问，然后将该顶点的所有邻接顶点加入到队列尾部。
 *               3. 循环步骤 2. ，直到所有顶点被访问完毕后结束。
 *               为了防止重复遍历顶点，我们需要借助一个哈希集合 visited 来记录哪些节点已被访问。
 *              （C语言无内置哈希表，故使用循环从序列已访问中查找节点是否已经被访问）
 *               哈希集合可以看作一个只存储 key 而不存储 value 的哈希表，它可以在 O（1）时间复杂度下进行 key 的增删查改操作。根据 key 的唯一性，哈希集合通常用于数据去重等场景。
 */

#include "graph_adjacency_list.c"

// 假设节点最大数量为 100
#define MAX_SIZE 100

/* 节点队列结构体 */
typedef struct
{
    Vertex *vertices[MAX_SIZE]; // 数组实现节点队列
    int front, rear, size;      // 队首指针、队尾指针、队列长度
} Queue;

/* 构造函数 */
Queue *newQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->size = 0;
    queue->front = queue->rear = 0;
    return queue;
}

/* 判断队列是否为空 */
bool isEmpty(Queue *queue) {
    return queue->size == 0;
}

/* 入队操作 */
void pushQueue(Queue *queue, Vertex *vet) {
    queue->vertices[queue->rear] = vet;
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->size++;
}

/* 出队操作 */
Vertex *pop(Queue *queue) {
    Vertex *vet = queue->vertices[queue->front];
    queue->front = (queue->front + 1) % MAX_SIZE;
    queue->size--;
    return vet;
}

/* 检查顶点是否已被访问 */
bool isVisited(Vertex **visited, int visitedSize, Vertex *vet) {
    // 遍历查找节点，使用 O(n) 时间
    for (int i = 0; i < visitedSize; i++) {
        if (visited[i] == vet) {
            return true;
        }
    }
    return false;
}

/**
 * @brief  广度优先遍历
 * @param  graph        图
 * @param  startVet     遍历起始节点
 * @param  result       遍历结果序列
 * @param  resSize      结果序列大小，同时控制元素添加位置
 * @param  visited      已访问过的节点数组
 * @param  visitedSize  已访问过的节点数组大小
 * @retval Vertex **result 遍历结果序列
 * @note   使用邻接表来表示图，以便获取指定顶点的所有邻接顶点
 */
void graphBFS(GraphAdjList *graph, Vertex *startVet,
              Vertex **result, int *resSize,
              Vertex **visited, int *visitedSize) {
    // 队列用于实现 BFS
    Queue *queue = newQueue();
    pushQueue(queue, startVet);
    visited[(*visitedSize)++] = startVet;
    // 以顶点 vet 为起点，循环直至访问完所有顶点
    while (!isEmpty(queue)) {
        Vertex *vet = pop(queue);   // 队首顶点出队
        result[(*resSize)++] = vet; // 记录访问顶点
        // 遍历该顶点的所有邻接顶点
        AdjListNode *node = findNode(graph, vet)->next;
        while (node != NULL) {
            if (!isVisited(visited, *visitedSize, node->vertex)) {
                pushQueue(queue, node->vertex);
                visited[(*visitedSize)++] = node->vertex;
            }
            node = node->next;
        }
    }
    free(queue);
}

/* Driver Code */
int main() {
    // 初始化无向图
    int vals[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(vals) / sizeof(vals[0]);
    Vertex **v = valsToVets(vals, size);
    Vertex *edges[][2] = {{v[0], v[1]}, {v[0], v[3]}, {v[1], v[2]}, {v[1], v[4]}, {v[2], v[5]}, {v[3], v[4]}, {v[3], v[6]}, {v[4], v[5]}, {v[4], v[7]}, {v[5], v[8]}, {v[6], v[7]}, {v[7], v[8]}};
    int egdeSize = sizeof(edges) / sizeof(edges[0]);
    GraphAdjList *graph = newGraphAdjList();
    // 添加所有顶点和边
    for (int i = 0; i < size; i++) {
        addVertex(graph, v[i]);
    }
    for (int i = 0; i < egdeSize; i++) {
        addEdge(graph, edges[i][0], edges[i][1]);
    }
    printf("\n初始化后，图为\n");
    printGraph(graph);

    // 广度优先遍历
    // 顶点遍历序列
    Vertex *res[MAX_SIZE];
    int resSize = 0;
    // 用于记录已被访问过的顶点
    Vertex *visited[MAX_SIZE];
    int visitedSize = 0;
    graphBFS(graph, v[0], res, &resSize, visited, &visitedSize);
    printf("\n广度优先遍历（BFS）顶点序列为\n");
    printArray(vetsToVals(res, resSize), resSize);

    // 释放内存
    delGraphAdjList(graph);
    free(v);
    return 0;
}
