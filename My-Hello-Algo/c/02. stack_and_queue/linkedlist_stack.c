/**
 * @FileName    :linkedlist_stack.c
 * @Date        :2024-08-22 21:35:38
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :基于链表实现栈（头插法）
 * @Description :获取栈的长度、判断栈是否为空、入栈、访问栈顶元素、出栈
 */

#include "../utils/common.h"

/* 基于链表实现的栈 */
typedef struct
{
    ListNode *top; // 将头节点作为栈顶
    int size;      // 栈的长度
} LinkedListStack;

/* 构造函数 */
LinkedListStack *newLinkedListStact() {
    LinkedListStack *s = malloc(sizeof(LinkedListStack));
    s->top = NULL;
    s->size = 0;
    return s;
}

/* 析构函数 */
void delLinkedListStack(LinkedListStack *s) {
    while (s->top) {
        ListNode *node = s->top->next;
        free(s->top);
        s->top = node;
    }
    free(s);
}

/* 获取栈的长度 */
int size(LinkedListStack *s) {
    return s->size;
}

/* 判断栈是否为空 */
bool isEmpty(LinkedListStack *s) {
    return size(s) == 0;
}
/* 入栈 */
void push(LinkedListStack *s, int num) {
    ListNode *node = newListNode(num);
    node->next = s->top;
    s->top = node;
    s->size++;
}
/* 访问栈顶元素 */
int peek(LinkedListStack *s) {
    if (s->size == 0) {
        printf("栈为空\n");
        return INT_MIN;
    }
    return s->top->val;
}
/* 出栈 */
int pop(LinkedListStack *s) {
    int val = peek(s);
    ListNode *temp = s->top;
    s->top = temp->next;
    free(temp);
    s->size--;
    return val;
}

/* Driver Code */
int main() {
    /* 初始化栈 */
    LinkedListStack *stack = newLinkedListStact();

    /* 元素入栈 */
    push(stack, 1);
    push(stack, 3);
    push(stack, 2);
    push(stack, 5);
    push(stack, 4);

    printf("栈 stack = ");
    printLinkedList(stack->top);

    /* 访问栈顶元素 */
    int val = peek(stack);
    printf("栈顶元素 top = %d\r\n", val);

    /* 元素出栈 */
    val = pop(stack);
    printf("出栈元素 pop = %d, 出栈后 stack =  ", val);
    printLinkedList(stack->top);

    /* 获取栈的长度 */
    printf("栈的长度 size = %d\n", size(stack));

    /* 判断是否为空 */
    bool empty = isEmpty(stack);
    printf("栈是否为空 = %s\n", empty ? "true" : "false");

    // 释放内存
    delLinkedListStack(stack);

    return 0;
}
