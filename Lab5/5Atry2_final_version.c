#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

//static means this function can only be used in this file
static Node* make_node(int v) {   //create a seperate node and store the value in the node
    Node *p = (Node*)malloc(sizeof *p); //create a place to store p and return its address p
    p->data = v;  //store the value v in the node
    p->next = NULL;
    return p;
}
 //add a new node to the end of the list
static void push_back_tail(Node **head, Node **tail, int v){ 
                        //if we want to change the value of the pointer,we have to use double pointer
    Node *n = make_node(v);  //   n是一个新节点的内存地址     create the node first and then add it by change the pointer of the tail
    if(*head == NULL){  //if the list is empty,create the head as the flag of the list
        *head = n; 
        *tail = n;    //通过if和else，先创建头节点，然后再往头节点里面输入，并且判断是否是头节点
    }
    else {               //让之前链表的尾部节点的指向的内存由NULL变成新节点的为位置
        (*tail)->next = n;  //let n as the address the former Node point to which is tail at present 
        *tail = n;           // 更新链表的末尾的元素update the tail to the new node
    }//add the new node to the end of the list and update tail for the new one
}

void print_list_prefixed(const char *label, const Node *h) {  //input the name and the head of the list 
    printf("%s:", label);                                  
    for (const Node *p = h; p != NULL; p = p->next) {//通过for循环去遍历链表，初始条件是让循环挪动的指针指向链表的头，然后每循环一次更新一次指针，最后当指针指向空表示到了尾部                    using for loop to get the data of each node,and transmit the data to p
        printf(" %d", p->data);  //each time print the data of the node and the p point to the next node
    }
    printf("\n");
}

void free_list(Node *h) {
    while (h != NULL) {
        Node *t = h->next;  //store the address of the next node first 
        free(h);  //free one node each time,using point so h can represent the node
        h = t;    //let h point to the next node,so we can free the next node
    }
}

Node* merge_sorted_lists(const Node* a, const Node* b) {  //merge two sorted lists a and b
    Node *head = NULL;  //create the head(the new list)
    Node *tail = NULL; 

    while (a != NULL && b != NULL) {
        if (a->data <= b->data) {        
            push_back_tail(&head, &tail, a->data); //add the smaller one to the new list
            a = a->next;    //更新条件：将指针位置更新
        } else {
            push_back_tail(&head, &tail, b->data); 
            b = b->next;
        }
    }
    while (a != NULL) {  //if b is already NULL,add the rest of a to the new list
        push_back_tail(&head, &tail, a->data);
        a = a->next;
    }
    while (b != NULL) {
        push_back_tail(&head, &tail, b->data);
        b = b->next;
    }
    return head;
}

void unique_in_place(Node* head) {
    Node *p = head;  //using p so we won't change the head of the list
    while (p != NULL && p->next != NULL) {  
        if (p->data == p->next->data) {
            Node *t = p->next;  //store the address of the next node first and then skip it
            p->next = t->next;  //skip the next node
            free(t);
        } else {
            p = p->next;
        }
    }
}

Node* intersect_sorted_lists(const Node* a, const Node* b) {
    Node *head = NULL, *tail = NULL;   //create a new list
    const Node *pa = a, *pb = b;  //using pa and pb to represent a and b so we won't change a and b
    while (pa != NULL && pb != NULL) {        //move pa and pb until find the same data
        if (pa->data < pb->data) {
            pa = pa->next;
        } else if (pa->data > pb->data) {
            pb = pb->next;
        } else {  //else means pa->data == pb->data
            if (head == NULL || tail->data != pa->data) {  //to avoid adding the same data more than once  
                push_back_tail(&head, &tail, pa->data);  //add the same data to the new list
            }
            pa = pa->next;
            pb = pb->next;
        }
    }
    return head;
}

int main() {
    int n, m;
    Node *A = NULL, *At = NULL;  //head and tail of list A
    Node *B = NULL, *Bt = NULL;

    scanf("%d", &n);               //read the number of elements in list A
    for (int i = 0; i < n; i++) {  //using for loop to read the elements and add them to the list A
        int v; 
        scanf("%d", &v);
        push_back_tail(&A, &At, v);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int v; 
        scanf("%d", &v);
        push_back_tail(&B, &Bt, v);
    }

    Node *M = merge_sorted_lists(A, B);  //merge two sorted lists A and B
    unique_in_place(M);                  //remove the same elements in the new list M
    Node *I = intersect_sorted_lists(A, B);  //find the intersection of two sorted lists A and B

    print_list_prefixed("MERGE", M);
    print_list_prefixed("INTERSECTION", I); 
    free_list(A);
    free_list(B);
    free_list(M);
    free_list(I);

    return 0;
}