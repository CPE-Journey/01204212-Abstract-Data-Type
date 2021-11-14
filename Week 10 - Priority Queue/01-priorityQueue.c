#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
  int *data;
  int last_index;
} heap_t;

heap_t *init_heap(int size){
  heap_t *first = malloc(sizeof(heap_t));
  first->data = malloc(size*sizeof(int));
  first->last_index = 1;
  return first;
}

void percolations(heap_t *t,int ind){
  if(ind/2 == 0){
    return;
  }
  if(t->data[ind/2]<t->data[ind]){
    int tmp = t->data[ind];
    t->data[ind] = t->data[ind/2];
    t->data[ind/2] = tmp;
    percolations(t,ind/2);
  }
}

void reversePercolations(heap_t *t,int ind){
  if((ind*2)+1 >= t->last_index){
    return;
  }
  if(t->data[ind] < t->data[(2*ind)]){
    int tmp = t->data[(2*ind)];
    t->data[(2*ind)] = t->data[ind];
    t->data[ind] = tmp;
    reversePercolations(t,(2*ind));
  }
  else if(t->data[ind] < t->data[(2*ind)+1]){
    int tmp = t->data[(2*ind)+1];
    t->data[(2*ind)+1] = t->data[ind];
    t->data[ind] = tmp;
    reversePercolations(t,(2*ind)+1);
  }
}

void insert(heap_t *t,int value){
  t->data[t->last_index] = value;
  percolations(t,t->last_index);
  t->last_index += 1;
}

void delete_max(heap_t *t){
  if(t->last_index == 1){
    return;
  }
  t->last_index -= 1;
  t->data[1] = t->data[t->last_index];
  reversePercolations(t,1);
}

void update_key(heap_t *t,int old_value,int new_value){
  int i;
  for(i=1;i<t->last_index;i++){
    if(t->data[i] == old_value){
      t->data[i] = new_value;
      break;
    }
  }
  percolations(t,i);
  reversePercolations(t,i);
}

int find_max(heap_t *t){
  int i,max = -1;
  for(i=1;i<t->last_index;i++){
    if(t->data[i] > max){
      max = t->data[i];
    }
  }
  return max;
}

void bfs(heap_t *t){
  int i;
  for(i=1;i<t->last_index;i++){
    printf("%d ",t->data[i]);
  }
  printf("\n");
}

int main(void) {
  heap_t *max_heap = NULL;
  int    m, n, i;
  int    command, data;
  int    old_key, new_key;

  scanf("%d %d", &m, &n);
  max_heap = init_heap(m);
  for (i=0; i<n; i++) {
    scanf("%d", &command);
    switch (command) {
      case 1:
        scanf("%d", &data);
        insert(max_heap, data);
        break;
      case 2:
        delete_max(max_heap);
        break;
      case 3:
        printf("%d\n", find_max(max_heap));
        break;
      case 4:
        scanf("%d %d", &old_key, &new_key);
        update_key(max_heap, old_key,new_key);
        break;
      case 5:
        bfs(max_heap);
        break;
    }
  }
  return 0;
}