#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char *data;
    int feq;
    int height;
    struct node *next;
    struct node *left;
    struct node *right;
}Heap;

typedef struct{
    Heap *list;
    int len;
}HeapList;

void DFS(Heap *h,int depth){
    // printf("Hello\n");
    if(h==NULL){
        return;
    }
    for(int i=0;i<depth;i++){
        printf("    ");
    }
    printf("%s(%d)[%d]\n",h->data,h->feq,h->height);
    DFS(h->left,depth+1);
    DFS(h->right,depth+1);
}

int len(char *word){
    int l = 0;
    while(*word){
        l++;
        word++;
    }
    return l;
}

char *copyText(char *word){
    char *tmp = malloc(len(word));
    sprintf(tmp,"%s",word);
    return tmp;
}

HeapList *createHeapLinkedList(int size){
    HeapList *new_arr = malloc(sizeof(HeapList));
    new_arr->list = malloc(sizeof(Heap));
    new_arr->list->data = NULL;
    new_arr->list->feq = -1;
    new_arr->list->next = NULL;
    new_arr->list->left = NULL;
    new_arr->list->right = NULL;
    new_arr->len = 1;
    return new_arr;
}

Heap *createHeap(char *word,int f){
    Heap *new_heap = malloc(sizeof(Heap));
    new_heap->data = malloc(len(word));
    sprintf(new_heap->data,"%s",word);
    new_heap->feq = f;
    new_heap->height = 0;
    new_heap->next = NULL;
    new_heap->left = NULL;
    new_heap->right = NULL;
    return new_heap;
}

Heap *index(HeapList *hl,int ind){
    int i;
    Heap *tmp = hl->list->next;
    for(i=1;i<ind;i++){
        tmp = tmp->next;
    }
    return tmp;
}

void hList_print(HeapList *hl){
    Heap *tmp = hl->list->next;
    while(tmp != NULL){
        if(tmp->left != NULL || tmp->right != NULL){
            printf("%s(%d)v ",tmp->data,tmp->feq);
        }
        else{
            printf("%s(%d) ",tmp->data,tmp->feq);
        }
        tmp = tmp->next;
    }
    printf("\n");
}

void hList_swapHeapX(HeapList *hl,int pos1,int pos2){
    if(pos1 == pos2){return;}
    Heap *tmp = hl->list;

    Heap *p1 = index(hl,pos1);
    char *p1_word = malloc(len(p1->data));
    p1_word = p1->data;
    int p1_feq = p1->feq;

    Heap *p2 = index(hl,pos2);
    char *p2_word = malloc(len(p2->data));
    p2_word = p2->data;
    int p2_feq = p2->feq;

    int i = 0;
    while(i!=pos1){
        tmp = tmp->next;
        i++;
    }
    tmp->data = p2_word;
    tmp->feq = p2_feq;

    tmp = tmp->next;
    i++;
    while(i!=pos2){
        tmp = tmp->next;
        i++;
    }
    tmp->data = p1_word;
    tmp->feq = p1_feq;

}

void hList_swapHeap(HeapList *hl,int pos1,int pos2){
    if(pos1 == pos2){return;}

    Heap *p1_prev = NULL;
    if(pos1-1 == 0){
        p1_prev = hl->list;
    }
    else{
        p1_prev = index(hl,pos1-1);
    }

    Heap *p1_crnt = index(hl,pos1);
    Heap *p1_next = index(hl,pos1+1);
    Heap *p2_prev = index(hl,pos2-1);
    Heap *p2_crnt = index(hl,pos2);

    Heap *p2_next = NULL;
    if(pos2+1 < hl->len){
        p2_next = index(hl,pos2+1);
    }
    
    if(pos2-pos1 == 1){
        p1_prev->next = p2_crnt;
        p1_next = p1_crnt;
        p1_crnt->next = p2_next;
    }
    else{
        p1_prev->next = p2_crnt;
        p2_crnt->next = p1_next;
        
        p2_prev->next = p1_crnt;
        p1_crnt->next = p2_next;
    }
    
}

void hList_percolation(HeapList *hl,int idx){
    if(idx/2 == 0){
        return;
    }
    if(index(hl,idx/2)->feq > index(hl,idx)->feq){
        hList_swapHeap(hl,idx/2,idx);
        hList_percolation(hl,idx/2);
    }
}

void hList_revPercolation(HeapList *hl,int idx){
    if((idx*2)+1 < hl->len){
        if(index(hl,2*idx)->feq > index(hl,(2*idx)+1)->feq && index(hl,idx)->feq > index(hl,(2*idx)+1)->feq){
            hList_swapHeap(hl,idx,(idx*2)+1);
            hList_revPercolation(hl,(idx*2)+1);
        }
        else if(index(hl,idx)->feq > index(hl,(2*idx))->feq){
            hList_swapHeap(hl,idx,(idx*2));
            hList_revPercolation(hl,(idx*2));
        }
    }
    else if((idx*2) < hl->len && index(hl,idx)->feq > index(hl,(2*idx))->feq){
        hList_swapHeap(hl,idx,(idx*2));
        hList_revPercolation(hl,(idx*2));
    }
}

void hList_insert(HeapList *hl,char *word,int f){
    Heap *new = createHeap(word,f);
    Heap *tmp = hl->list;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = new;
    hList_percolation(hl,hl->len);
    hl->len += 1;
}

void hList_insertTree(HeapList *hl,Heap *h){
    Heap *tmp = hl->list;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = h;
    hList_percolation(hl,hl->len);
    hl->len += 1;
}

void hList_delete_min(HeapList *hl,int *rf){
    // printf("Wc %d\n",hl->len);
    if(hl->len == 1){
        return;
    }
    // Heap *rtn = index(hl,1);
    // char *rt = copyText(rtn->data);
    // *rf = rtn->feq;

    hl->len -= 1;
    hList_swapHeap(hl,1,hl->len);
    hList_revPercolation(hl,1);

    Heap *last = index(hl,hl->len-1);
    last->next = NULL;
    // return rt;
}

int heap_fequency(Heap *h){
    if(h==NULL){return 0;}
    return h->feq;
}

int getHeight(Heap *h){
    if(h==NULL){
        return -1;
    }
    return h->height;
}

int reHeight(Heap *h){
    int lh = getHeight(h->left), rh = getHeight(h->right);
    if(lh>rh){
        return lh+1;
    }
    return rh+1;
}

int balance(Heap *h){
    int gh = getHeight(h->left)-getHeight(h->right);
    return gh*gh;
}

Heap *heap_insert(Heap *h,Heap *s){
    if(h==NULL){
        return s;
    }
    int b = balance(h);
    if(b == 0){
        h->left = heap_insert(h->left,s);
    }
    else{
        h->right = heap_insert(h->right,s);
    }

    h->height = reHeight(h);

    int tmp;
    char *text1,*text2;

    if(h->left && h->left->feq > h->feq){
        tmp = h->left->feq;
        h->left->feq = h->feq;
        h->feq = tmp;

        text1 = copyText(h->data);
        text2 = copyText(h->left->data);
        h->left->data = text1;
        h->data = text2;
    }
    if(h->right && h->right->feq > h->feq){
        tmp = h->right->feq;
        h->right->feq = h->feq;
        h->feq = tmp;

        text1 = copyText(h->data);
        text2 = copyText(h->right->data);
        h->right->data = text1;
        h->data = text2;
    }

    return h;
}

Heap *pop_heap(HeapList *hl){
    if(hl->len == 1){
        return;
    }
    Heap *rtn = index(hl,1);
    // printf("%s\n",rtn->data);

    hl->len -= 1;
    hList_swapHeap(hl,1,hl->len);
    // hList_print(hl);
    hList_revPercolation(hl,1);
    hList_print(hl);

    Heap *last = index(hl,hl->len-1);
    last->next = NULL;
    // printf("%s\n",rtn->data);
    return rtn;
}

int main(){
    int a,n,feq,per_dir;
    char text[100000];
    HeapList *hl = NULL;

    scanf("%d",&n);
    hl = createHeapLinkedList(n);
    for(a=0;a<n;a++){
        scanf("%s %d",text,&feq);
        hList_insert(hl,text,feq);
    }
    hList_print(hl);
    printf("%d\n",hl->len);
    
    Heap *head = NULL;
    Heap *p1 = NULL;
    Heap *p2 = NULL;
    printf("Yay\n");
    while(hl->len > 3){
        p1 = pop_heap(hl);
        hList_print(hl);
        break;
        p2 = pop_heap(hl);
        // printf("%s %s",p1->data,p2->data);
        // dir = 1;
        // f1 = -1;
        // f2 = -1;
        // w1 = hList_delete_min(hl,&f1);
        // w2 = hList_delete_min(hl,&f2);
        // printf("Out: %s %s\n",w1,w2);
        head = createHeap("<tmp>",p1->feq+p2->feq);
        // if(f1 != -1)
        head = heap_insert(head,p1);
        // if(f2 != -1)
        head = heap_insert(head,p2);
        hList_insertTree(hl,head);
        hList_print(hl);
        // // break;
        // i+=1;
        // break;
    }
    // Heap *huffman = index(hl,2);
    // DFS(huffman,0);
}