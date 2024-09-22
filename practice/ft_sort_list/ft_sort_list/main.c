#include <stdio.h>
#include <stdlib.h>

// 链表节点的结构定义
typedef struct s_list {
	int data;
	struct s_list *next;
} t_list;

// 链表排序函数
t_list *sort_list(t_list *lst, int (*cmp)(int, int)) {
	int swap;
	t_list *ret_lst;
	
	if (!lst || !cmp)
		return (NULL);
	ret_lst = lst;
	
	while (lst != NULL && lst->next != NULL) {
		if ((*cmp)(lst->data, lst->next->data) == 0) { // 根据cmp的规则进行比较
			swap = lst->data;
			lst->data = lst->next->data;
			lst->next->data = swap;
			lst = ret_lst; // 重新从链表头开始
		} else {
			lst = lst->next;
		}
	}
	return (ret_lst);
}

// 比较函数：返回0表示需要交换，非0表示顺序正确
int cmp(int a, int b) {
	return (a <= b); // 返回1表示正确顺序，0表示需要交换
}

// 创建新的链表节点
t_list *create_node(int data) {
	t_list *new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return NULL;
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

// 打印链表
void print_list(t_list *lst) {
	while (lst) {
		printf("%d -> ", lst->data);
		lst = lst->next;
	}
	printf("NULL\n");
}

// 主函数：测试链表排序
int main() {
	// 创建链表：4 -> 3 -> 2 -> 1
	t_list *head = create_node(4);
	head->next = create_node(3);
	head->next->next = create_node(2);
	head->next->next->next = create_node(1);
	
	printf("Original list:\n");
	print_list(head);
	
	// 调用排序函数
	head = sort_list(head, cmp);
	
	printf("Sorted list:\n");
	print_list(head);
	
	// 释放链表内存
	t_list *tmp;
	while (head) {
		tmp = head;
		head = head->next;
		free(tmp);
	}
	
	return 0;
}
