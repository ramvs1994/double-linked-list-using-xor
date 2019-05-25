#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int ptr;
#define PTR_DIFF(x,y) ((ptr)(x) ^ (ptr)(y))
#define NXT_PTR(diff,prev) (dll_node *)(PTR_DIFF(diff,prev))
#define PREV_PTR(diff,nxt) (dll_node *)(PTR_DIFF(diff,nxt))

#define SUCCESS 1
#define FAIL 0

typedef struct dll_data {
    int value;
} dll_data;


typedef struct dll_node {
    struct dll_data data;
    void *ptrdiff;
} dll_node;

dll_node *dll_UnInit(dll_node *head)
{
    if (head) {
        free(head);
    }
    return NULL;
}    

bool dll_node_insert(dll_node **root, dll_data *data)
{
    dll_node *head = *root;
    if (head) {
        dll_node *curr = head; 
        dll_node *prev = NULL;
        dll_node *next = NXT_PTR(head->ptrdiff,prev);
        while (next) {
            prev = curr;
            curr = next;
            next = NXT_PTR(prev,curr->ptrdiff);
        }
	dll_node *new = calloc(1,sizeof(dll_node));
        if (!new) {
            return FAIL;
        }
        curr->ptrdiff = PTR_DIFF(prev,new);
        new->ptrdiff = PTR_DIFF(curr,0);
        new->data.value = data->value;
    } else {
        head = calloc(1,sizeof(dll_node));
        if (!head) {
            return FAIL; 
        }
        *root = head;
        head->data.value = data->value;
        head->ptrdiff = PTR_DIFF(0,0);
    }
    return SUCCESS;
}

void print_data(dll_node *root)
{
        int i;
        dll_node *curr = root; 
        dll_node *prev = NULL;
        dll_node *next = NXT_PTR(root->ptrdiff,prev);
        printf("____DATA____\n");
        for (i=0;next;i++) {
            printf("node : %d\t value : %d\n", i, curr->data.value);
            prev = curr;
            curr = next;
            next = NXT_PTR(prev,curr->ptrdiff);
        }
            printf("node : %d\t value : %d\n", i, curr->data.value);
}


int main()
{
        dll_node *head = NULL;
	dll_data data1 = {2};
	dll_data data2 = {4};
	dll_data data3 = {8};
	dll_node_insert(&head,&data1);
	dll_node_insert(&head,&data2);
	dll_node_insert(&head,&data3);
        print_data(head);
	return 0;
}
