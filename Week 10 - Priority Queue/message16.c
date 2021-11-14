#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
  int *data;
  int last_index;
} heap_t;

heap_t *init_heap(int m)
{
  heap_t *t = (heap_t *)malloc(sizeof(heap_t));
  int *d = (int *)malloc(sizeof(int) * m);
  t->data = d;
  t->last_index = -1;
  return t;
}

void bfs(heap_t *h)
{
  int i;
  for (i = -1; i < h->last_index + 1; i++)
  {
    if(*((h->data)+i) == 0)
      continue;
    printf("%d ", h->data[i]);
  }
  printf("\n");
}

int *swap(int *heap_data, int n, int m)
{
  int n_data = heap_data[n];
  int m_data = heap_data[m];
  heap_data[n] = m_data;
  heap_data[m] = n_data;
  return heap_data;
}

void insert(heap_t *h, int d)
{

  h->data[h->last_index + 1] = d;
  h->last_index = h->last_index + 1;

  int p_index;
  int c = h->last_index;
  while (1)
  {
    if (c % 2 == 0)
    {
      p_index = (c - 2) / 2;
    }
    else
    {
      p_index = (c - 1) / 2;
    }
    if (h->data[p_index] < h->data[c])
    {
      h->data = swap(h->data, p_index, c);
      c = p_index;
    }
    else
    {
      break;
    }
  }
   // bfs(h);
   // printf("last index %d\n",h->last_index);
}

void delete_max(heap_t *h)
{
  if (h->last_index == 0)
  {
    h->last_index = -1;
    return;
  }
  int k = h->data[h->last_index];
  h->data[0] = k;
  h->last_index--;

  if (h->last_index == 0)
  {
    return;
  }
  int p = 0;
  int cl_index, cr_index;
  while (1)
  {
    cl_index = 2 * p + 1;
    cr_index = 2 * p + 2;
    if (h->data[p] < h->data[cl_index])
    {
      h->data = swap(h->data, p, cl_index);
      p = cl_index;
    }
    else if (h->data[p] < h->data[cr_index])
    {
      h->data = swap(h->data, p, cr_index);
      p = cr_index;
    }
    else
    {
      break;
    }
  }
}

int find_max(heap_t *h)
{
  if (h->last_index <= -1)
  {
    return -1;
  }
  return h->data[0];
}

void update_key(heap_t *h, int o_k, int n_k)
{
  int n = h->data[0];
  int i = 0;
  while (n != o_k)
  {
    i++;
    n = h->data[i];
  }
  h->data[i] = n_k;
  int cl = 2 * i + 1;
  int cr = 2 * i + 2;
  if (n_k < h->data[cr] || n_k < h->data[cl])
  {
    int p = i;
    while (1)
    {
      cl = 2 * p + 1;
      cr = 2 * p + 2;
      if (h->data[p] < h->data[cl])
      {
        h->data = swap(h->data, p, cl);
        p = cl;
      }
      else if (h->data[p] < h->data[cr])
      {
        h->data = swap(h->data, p, cr);
        p = cr;
      }
      else
      {
        break;
      }
    }
  }
  else
  {
    int p_index;
    int c = i;
    while (1)
    {
      if (c % 2 == 0)
      {
        p_index = (c - 2) / 2;
      }
      else
      {
        p_index = (c - 1) / 2;
      }
      if (h->data[p_index] < h->data[c])
      {
        h->data = swap(h->data, p_index, c);
        c = p_index;
      }
      else
      {
        break;
      }
    }
  }
}

int main(void)
{
  heap_t *max_heap = NULL;
  int m, n, i;
  int command, data;
  int old_key, new_key;

  scanf("%d %d", &m, &n);
  max_heap = init_heap(m);
  for (i = 0; i < n; i++)
  {
    scanf("%d", &command);
    switch (command)
    {
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
        update_key(max_heap, old_key, new_key);
        break;
      case 5:
        bfs(max_heap);
        break;
    }
  }
  return 0;
}