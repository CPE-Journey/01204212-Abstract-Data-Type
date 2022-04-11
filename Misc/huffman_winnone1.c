#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct huffmantree{
  char data[15];
  int freq;
  struct huffmantree *left;
  struct huffmantree *right;
} hm_t;

typedef struct priorityqueue_maxheap{
  int last_index;
  hm_t **ar;
} pq_mh;

hm_t *newtree(int f,char text[]){
	hm_t *newnode = malloc(sizeof(hm_t));
	strcpy(newnode->data,text);
	newnode->freq=f;
	newnode->left=NULL;
	newnode->right=NULL;
	return newnode;
}

pq_mh *createqueue(int n){
	pq_mh *q = malloc(sizeof(pq_mh));
	q->ar = malloc(sizeof(hm_t)*n);
	q->last_index=0;
	return q;
}

void insertqueue (pq_mh *q,hm_t *t){
	q->last_index++;
	q->ar[q->last_index]=t;
	int k = q->last_index;
	while((k/2!=0) && (q->ar[k]->freq) < (q->ar[k/2]->freq)){
		hm_t *tmp=q->ar[k];
		q->ar[k] = q->ar[k/2];
		q->ar[k/2] = tmp;
		k=k/2;
	}	
}

void deletemin(pq_mh *q){
	q->ar[1]=q->ar[q->last_index];
	q->ar[q->last_index]=NULL;
	q->last_index--;
	hm_t *tmp = NULL;
	int k=1,max;
	while(q->last_index>1) {
		if(2*k<=q->last_index && 2*k+1<=q->last_index){
			if(q->ar[k]->freq>q->ar[2*k]->freq && q->ar[k]->freq<=q->ar[2*k+1]->freq )
				{max = 2*k;}
			else if(q->ar[k]->freq<=q->ar[2*k]->freq && q->ar[k]->freq>q->ar[2*k+1]->freq)
				{max = 2*k+1;}
			else if(q->ar[k]->freq>q->ar[2*k]->freq && q->ar[k]->freq>q->ar[2*k+1]->freq){
				if (q->ar[2*k]->freq<q->ar[2*k+1]->freq)
					{max = 2*k;}
				else if (q->ar[2*k]->freq>q->ar[2*k+1]->freq)
					{max = 2*k+1;}
				else
					{max = 2*k;}
			}
			else
				{break;}
		}
		else if (2*k<=q->last_index){
			if(q->ar[k]->freq>q->ar[2*k]->freq)
				{max = 2*k;}
			else
				{break;}
		}
		else if(2*k+1<=q->last_index){
			if(q->ar[k]->freq>q->ar[2*k+1]->freq)
				{max = 2*k+1;}
			else
				{break;}
		}
		else
			{break;}
			
		tmp=q->ar[max];
		q->ar[max] = q->ar[k];
		q->ar[k]=tmp;
		k=max;	
	}
}

void perform (pq_mh *q){
	hm_t *tmp1 = NULL; 
	hm_t *tmp2 =NULL;
	
	if (q->last_index > 1){
		tmp1 = q->ar[1];
		deletemin(q);
	}
	if (q->last_index > 0){
		tmp2 = q->ar[1];
		deletemin(q);
	}
	
	hm_t *mergetree = (hm_t*)malloc(sizeof(hm_t));
	mergetree->freq=tmp1->freq+tmp2->freq;
	mergetree->left=tmp1;
	mergetree->right=tmp2;
	
	insertqueue(q,mergetree);
}

void printcode(int code[],int index){
    int i;
    for (i=0;i<index;i++) 
        printf("%d",code[i]);
    printf("\n");
}

void dfs(hm_t *t,int code[],int index) {
    if (t->left) {
        code[index] = 0;
        dfs(t->left,code,index+1);
    }
    if (t->right) {
        code[index] = 1;
        dfs(t->right,code,index+1);
    }
    if (t->left == NULL && t->right == NULL) {
        printf("%s: ",t->data);
        printcode(code,index);
    }
}

int main(void) {
  int n,i,f,code[1000],index=0;
  char text[15];
  scanf("%d",&n);
  pq_mh *mh = NULL;
  mh = createqueue(n);
  for(i=0;i<n;i++){
	printf("A\n");
	scanf("%s %d",text,&f);
	printf("A\n");
	hm_t *tmp = newtree(f,text);
	printf("A\n");
	insertqueue(mh,tmp);
  }
  while(mh->last_index>1){
  	perform(mh);
  }
  dfs(mh->ar[mh->last_index],code,index);
}