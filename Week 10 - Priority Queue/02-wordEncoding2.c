#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char *data;
    int feq;
    int height;
    struct node *left;
    struct node *right;
}Heap;

typedef struct{
    Heap **arr;
    int len;
}HeapArr;

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
        word++;
        l++;
    }
    return l;
}

char *copyText(char *text){
    char *tmp = malloc(len(text));
    sprintf(tmp,"%s",text);
    return tmp;
}

HeapArr *createHeapArray(int size){
    HeapArr *new_arr = malloc(sizeof(HeapArr));
    new_arr->arr = malloc(sizeof(Heap)*size);
    new_arr->len = 1;
    return new_arr;
}

Heap *createHeap(char *text,int feq){
    Heap *new_h = malloc(sizeof(Heap));
    new_h->data = malloc(len(text));
    new_h->data = copyText(text);
    new_h->height = 0;
    new_h->feq = feq;
    new_h->left = NULL;
    new_h->right = NULL;
    return new_h;
}

void HA_swap(HeapArr *ha,int pos1,int pos2){
    Heap *tmp = ha->arr[pos1];
    ha->arr[pos1] = ha->arr[pos2];
    ha->arr[pos2] = tmp;
}

int fq(HeapArr *ha,int i){
    return ha->arr[i]->feq;
}

void HA_percolation(HeapArr *ha,int idx){
    if(idx/2 == 0){
        return;
    }
    if(fq(ha,idx/2) > fq(ha,idx)){
        HA_swap(ha,idx/2,idx);
        HA_percolation(ha,idx/2);
    }
    
}

void HA_revPercolation(HeapArr *ha,int idx){
    if((idx*2)+1 < ha->len){
        if(fq(ha,2*idx) > fq(ha,(2*idx)+1) && fq(ha,idx) > fq(ha,(2*idx)+1)){
            HA_swap(ha,idx,(idx*2)+1);
            HA_revPercolation(ha,(idx*2)+1);
        }
        else if(fq(ha,idx) > fq(ha,(2*idx))){
            HA_swap(ha,idx,(idx*2));
            HA_revPercolation(ha,(idx*2));
        }
    }
    else if((idx*2) < ha->len && fq(ha,idx) > fq(ha,(2*idx))){
        HA_swap(ha,idx,(idx*2));
        HA_revPercolation(ha,(idx*2));
    }
}

void HA_insert(HeapArr *ha,char *text,int feq){
    Heap *new_h = createHeap(text,feq);
    ha->arr[ha->len] = new_h;
    HA_percolation(ha,ha->len);
    ha->len += 1;
}

void HA_insertTree(HeapArr *ha,Heap *h){
    ha->arr[ha->len] = h;
    HA_percolation(ha,ha->len);
    ha->len += 1;
}

void HA_print(HeapArr *ha){
    int i;
    for(i=1;i<ha->len;i++){
        printf("%s(%d) ",ha->arr[i]->data,ha->arr[i]->feq);
    }
    printf("\n");
}

Heap *HA_deleteMin(HeapArr *ha){
    ha->len -= 1;
    HA_swap(ha,1,ha->len);
    HA_revPercolation(ha,1);
    return ha->arr[ha->len];
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

Heap *HP_insert(Heap *h,Heap *s){
    if(h==NULL){
        return s;
    }
    int b = balance(h);
    if(b == 0){
        h->left = HP_insert(h->left,s);
    }
    else{
        h->right = HP_insert(h->right,s);
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

char *addChar(char *word,char c){
    char *tmp = malloc(len(word));
    sprintf(tmp,"%s%c",word,c);
    return tmp;
}

void HuffmanEncoding(Heap *h,char *code){
    if(h==NULL){
        return;
    }
    if(h->height == 0){
        printf("%s: %s\n",h->data,code);
    }
    char *recode1 = addChar(code,'0');
    HuffmanEncoding(h->left,recode1);
    char *recode2 = addChar(code,'1');
    HuffmanEncoding(h->right,recode2);
}

int main(){
    int a,n,feq,per_dir;
    char text[15];
    HeapArr *ha = NULL;

    scanf("%d",&n);
    ha = createHeapArray(n);

    for(a=0;a<n;a++){
        scanf("%s %d",text,&feq);
        HA_insert(ha,text,feq);
    }
    Heap *head = NULL,*p1 = NULL,*p2 = NULL;
    while(ha->len > 2){
        p1 = HA_deleteMin(ha);
        p2 = HA_deleteMin(ha);
        head = createHeap("<tmp>",p1->feq+p2->feq);
        head = HP_insert(head,p1);
        head = HP_insert(head,p2);
        HA_insertTree(ha,head);
    }

    Heap *HuffmanTree = ha->arr[1];
    HuffmanEncoding(HuffmanTree->left,"0");
    HuffmanEncoding(HuffmanTree->right,"1");
}