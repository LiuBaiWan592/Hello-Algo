/**
 * @FileName    :avl_tree.c
 * @Date        :2024-09-04 15:18:49
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :平衡二叉搜索树（balanced binary search tree）
 * @Description :“节点高度”是指从该节点到它的最远叶节点的距离，即所经过的“边”的数量。规定叶节点的高度为 0 ，而空节点的高度为 -1
 */

#include "../utils/common.h"

/* AVL 树结构体 */
typedef struct
{
    TreeNode *root;
} AVLTree;

/* 构造函数 */
AVLTree *newAVLTree() {
    AVLTree *avl = malloc(sizeof(AVLTree));
    avl->root = NULL;
    return avl;
}

/* 析构函数 */
void delAVLTree(AVLTree *avl) {
    free(avl->root);
    free(avl);
}

/* 获取节点高度 */
int height(TreeNode *node) {
    // 空节点高度为 -1 ，叶节点高度为 0
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

/* 更新节点高度 */
void updateHeight(TreeNode *node) {
    int lh = height(node->left);
    int rh = height(node->right);
    if (lh > rh) {
        node->height = lh + 1;
    } else {
        node->height = rh + 1;
    }
}

/* 获取平衡因子 */
int balanceFactor(TreeNode *node) {
    // 空节点平衡因子为 0
    if (node == NULL) {
        return 0;
    }
    // 节点平衡因子 = 左子树高度 - 右子树高度
    return height(node->left) - height(node->right);
}

/* 右旋操作 */
TreeNode *rightRotator(TreeNode *node) {
    TreeNode *child, *grandchild;
    child = node->left;
    grandchild = child->right;
    // 以 child 为原点，将 node 向右旋转
    child->right = node;
    node->left = grandchild;
    // 更新节点高度
    updateHeight(node);
    updateHeight(child);
    // 返回旋转后子树的根节点
    return child;
}

/* 左旋操作 */
TreeNode *leftRotate(TreeNode *node) {
    TreeNode *child, *grandchild;
    child = node->right;
    grandchild = child->left;
    // 以 child 为原点，将 node 向左旋转
    child->left = node;
    node->right = grandchild;
    // 更新节点高度
    updateHeight(node);
    updateHeight(child);
    // 返回旋转后子树的根节点
    return child;
}

/* 执行旋转操作，使该子树重新恢复平衡 */
TreeNode *rotate(TreeNode *node) {
    // 获取节点 node 的平衡因子
    int bf = balanceFactor(node);
    // 左偏树
    if (bf > 1) {
        if (balanceFactor(node->left) >= 0) {
            // 右旋
            return rightRotator(node);
        } else {
            // 先左旋再右旋
            node->left = leftRotate(node->left);
            return rightRotator(node);
        }
    }
    // 右偏树
    if (bf < -1) {
        if (balanceFactor(node->right) <= 0) {
            // 左旋
            return leftRotate(node);
        } else {
            // 先右旋再左旋
            node->right = rightRotator(node->right);
            return leftRotate(node);
        }
    }
    // 平衡树，无须旋转，直接返回
    return node;
}

/* 递归插入节点（辅助函数） */
// 从插入节点开始，自底向上执行旋转操作，使所有失衡节点恢复平衡（递归实现）
TreeNode *insertHelper(TreeNode *node, int val) {
    if (node == NULL) {
        return newTreeNode(val);
    }
    /* 1. 查找插入位置并插入节点 */
    if (node->val > val) {
        node->left = insertHelper(node->left, val);
    } else if (node->val < val) {
        node->right = insertHelper(node->right, val);
    } else {
        // 重复节点不插入，直接返回
        return node;
    }
    // 更新节点高度
    updateHeight(node);
    /* 2. 执行旋转操作，使该子树重新恢复平衡 */
    node = rotate(node);
    // 返回子树的根节点
    return node;
}

/* 插入节点 */
void insert(AVLTree *avl, int val) {
    avl->root = insertHelper(avl->root, val);
}

/* 递归删除节点（辅助函数） */
// 从底至顶执行旋转操作，使所有失衡节点恢复平衡
TreeNode *removeHelper(TreeNode *node, int val) {
    if (node == NULL) {
        return NULL;
    }
    TreeNode *child, *grandchild;
    /* 1. 查找节点并删除 */
    if (node->val > val) {
        node->left = removeHelper(node->left, val);
    } else if (node->val < val) {
        node->right = removeHelper(node->right, val);
    } else if (node->left == NULL || node->right == NULL) {
        child = node->left;
        if (node->right != NULL) {
            child = node->right;
        }
        // 子节点数量 = 0 ，直接删除 node 并返回
        if (child == NULL) {
            return NULL;
        } else {
            // 子节点数量 = 1 ，直接删除 node
            node = child;
        }
    } else {
        // 子节点数量 = 2 ，则将中序遍历的下个节点删除，并用该节点替换当前节点
        TreeNode *temp = node->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        int tempVal = temp->val;
        node->right = removeHelper(node->right, temp->val);
        node->val = tempVal;
    }
    // 更新节点高度
    updateHeight(node);
    /* 2. 执行旋转操作，使该子树重新恢复平衡 */
    node = rotate(node);
    // 返回子树的根节点
    return node;
}

/* 删除节点 */
void removeItem(AVLTree *avl, int val) {
    avl->root = removeHelper(avl->root, val);
}

/* 查找节点 */
TreeNode *search(AVLTree *tree, int val) {
    TreeNode *cur = tree->root;
    // 循环查找，越过叶节点后跳出
    while (cur != NULL) {
        if (cur->val < val) {
            // 目标节点在 cur 的右子树中
            cur = cur->right;
        } else if (cur->val > val) {
            // 目标节点在 cur 的左子树中
            cur = cur->left;
        } else {
            // 找到目标节点，跳出循环
            break;
        }
    }
    // 找到目标节点，跳出循环
    return cur;
}

void testInsert(AVLTree *tree, int val) {
    insert(tree, val);
    printf("\n插入节点 %d 后，AVL 树为 \n", val);
    printTree(tree->root);
}

void testRemove(AVLTree *tree, int val) {
    removeItem(tree, val);
    printf("\n删除节点 %d 后，AVL 树为 \n", val);
    printTree(tree->root);
}

/* Driver Code */
int main() {
    /* 初始化空 AVL 树 */
    AVLTree *tree = (AVLTree *)newAVLTree();
    /* 插入节点 */
    // 请关注插入节点后，AVL 树是如何保持平衡的
    testInsert(tree, 1);
    testInsert(tree, 2);
    testInsert(tree, 3);
    testInsert(tree, 4);
    testInsert(tree, 5);
    testInsert(tree, 8);
    testInsert(tree, 7);
    testInsert(tree, 9);
    testInsert(tree, 10);
    testInsert(tree, 6);

    /* 插入重复节点 */
    testInsert(tree, 7);

    /* 删除节点 */
    // 请关注删除节点后，AVL 树是如何保持平衡的
    testRemove(tree, 8); // 删除度为 0 的节点
    testRemove(tree, 5); // 删除度为 1 的节点
    testRemove(tree, 4); // 删除度为 2 的节点

    /* 查询节点 */
    TreeNode *node = search(tree, 7);
    printf("\n查找到的节点对象节点值 = %d \n", node->val);

    // 释放内存
    delAVLTree(tree);
    return 0;
}
