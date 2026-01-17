#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node * next;
} Node;

static Node* make_node(int v){  //input a number and put it into a newly created node
    Node *p = (Node*)malloc(sizeof *p);//creat a place to store p 
    p->data = v;
    p->next = NULL;
    return p;
}

static void push_back_tail(Node **head, Node **tail, int v){
    Node *n = make_node(v);
    if(!*head){ *head = n; *tail = n; }
    else { (*tail)->next = n; *tail = n; }//add the new node to the end of the list and update tail for the new one
}

void print_list_prefixed(const char *label, const Node *h){
    printf("%s", label);
    for(const Node *p = h; p != NULL ; p = p->next)  //using for loop to get the data of each node,and transmit the data to p
        printf(" %d", p->data);
    printf("\n");
}

void free_list(Node *h){
    while(h != NULL){
        Node *t = h->next;
        free(h);   //free one node each time
        h = t;
    }
}

Node* merge_sorted_lists(const Node* a, const Node* b){
    Node * head = NULL;

    while(a!= NULL && b!=NULL){
        if(a->data < b->data){
            push_back_tail(&head, &head, a->data);
            a = a->next;
        } else {
            push_back_tail(&head, &head, b->data);
            b = b->next;
        }
    }
    while(a != NULL){
        push_back_tail(&head, &head, a->data);
        a = a->next;
    }
    while(b != NULL){
        push_back_tail(&head, &head, b->data);
        b = b->next;
    }
    return head;
}

void unique_in_place(Node* head){
    Node *p = head;
    while(p!= NULL && p->next != NULL){
        if(p->data == p->next->data){
            Node *t = p->next;
            p->next = t->next;
            free(t);
        } else {
            p = p->next;
        }
    }
}

Node* intersect_sorted_lists(const Node* a, const Node* b){
    Node *head = NULL, *tail = NULL;
    const Node *pa = a, *pb = b;
    while(pa && pb){
        if(pa->data < pb->data){
            pa = pa->next;
        } else if(pa->data > pb->data){
            pb = pb->next;
        } else {
            if (head == NULL || tail->data != pa->data) {
                push_back_tail(&head, &tail, pa->data);
            }
            pa = pa->next;
            pb = pb->next;
        }
    }
    return head;
}

int main(){
    int n, m;
    Node *A = NULL, *At = NULL;
    Node *B = NULL, *Bt = NULL;

    for(int i = 0; i < n; i++){
        int v; scanf("%d", &v);
        push_back_tail(&A, &At, v);
    }

    scanf("%d",m);
    for(int i = 0; i < m; i++){
        int v; scanf("%d", &v);
        push_back_tail(&B, &Bt, v);
    }

    Node *M = merge_sorted_lists(A, B);
    unique_in_place(M);
    Node *I = intersect_sorted_lists(A, B);

    print_list_prefixed("MERGE", M);
    print_list_prefixed("INTERSECT", I);

    free_list(A);
    free_list(B);
    free_list(M);
    free_list(I);

    return 0;
}

