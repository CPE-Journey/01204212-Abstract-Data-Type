#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
  int *data;
  int last_index;
} heap_t;

heap_t *init_heap(int m){
    heap_t *node = (heap_t *)malloc(sizeof(heap_t));
    int *array = (int *)malloc(sizeof(int)*m);
    node->data = array;
    node->last_index = 0;
    return node;
}

void swap_maxmin(heap_t *max_heap,int range) {
    int tmp;
    int parent = (range)/2,children = range;
    while (max_heap->data[parent] < max_heap->data[children]){
        tmp = max_heap->data[parent];
        max_heap->data[parent] = max_heap->data[children];
        max_heap->data[children] = tmp;
        children = parent;
        parent = children/2;
    }
}

void insert(heap_t *max_heap, int value){
    max_heap->last_index++;
    max_heap->data[max_heap->last_index] = value;
    swap_maxmin(max_heap,max_heap->last_index); 
}

int find_max(heap_t *max_heap){
    if (max_heap->last_index == 0) {
        return -1;
    }else {
        return max_heap->data[1];
    }
}

void swap_delete(heap_t *max_heap) {
    int tmp;
    int parent = 1,children;
    if (max_heap->data[2*parent] > max_heap->data[2*parent+1] || 2*parent+1 > max_heap->last_index) {
        children = 2*parent;
    }else if (max_heap->data[2*parent] < max_heap->data[2*parent+1] || 2*parent > max_heap->last_index){
        children = 2*parent+1;
    }
    while (max_heap->data[parent] < max_heap->data[children]){
        tmp = max_heap->data[parent];
        max_heap->data[parent] = max_heap->data[children];
        max_heap->data[children] = tmp;
        parent++;
        if (parent > max_heap->last_index) {
            break;
        }
        if (max_heap->data[2*parent] > max_heap->data[2*parent+1] || 2*parent+1 > max_heap->last_index) {
            children = 2*parent;
        }else if (max_heap->data[2*parent] < max_heap->data[2*parent+1] || 2*parent > max_heap->last_index){
            children = 2*parent+1;
        }
        
    }
}

void *delete_max(heap_t *max_heap){
    if (max_heap->last_index > 0) {
        max_heap->data[1] = max_heap->data[max_heap->last_index];
        max_heap->last_index--;
        swap_delete(max_heap); 
    }
}

void bfs(heap_t *max_heap) {
    int i;
    for (i=1;i<=max_heap->last_index;i++) {
        printf("%d ",max_heap->data[i]);
    }
    printf("\n");
}

int find_index(heap_t *max_heap,int value){
    int i,range_arr = max_heap->last_index,index;
    for (i = 1;i<=range_arr;i++) {
        if (max_heap->data[i] == value) {
            index = i;
            break;    
        }
    }
    return index;
}

void update_key(heap_t *max_heap,int old_key,int new_key){
    int index;
    index= find_index(max_heap,old_key);
    max_heap->data[index] = new_key;
    swap_maxmin(max_heap,index);
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
        update_key(max_heap, old_key,
                   new_key);
        break;
      case 5:
        bfs(max_heap);
        break;
    }
  }
  return 0;
}