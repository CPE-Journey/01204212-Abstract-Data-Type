#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  TEXTSIZE 21

typedef char* item_t;

typedef struct hash {
  item_t *table;
  int    size;
  int    hash_key;
} hash_t;

hash_t *init_hashtable(int size,int key){
  hash_t *h = malloc(sizeof(hash_t));
  h->table = malloc(sizeof(hash_t*)*size);
  h->size = size;
  h->hash_key = key;
  return h;
}

unsigned int hash_Recusion(char *text,int len,int key){
  if(len == 0)
    return (int)text[0];
  return (key*hash_Recusion(text,len-1,key))+(int)text[len];
}

unsigned int hash(hash_t *h,char *text){
  return hash_Recusion(text,strlen(text)-1,h->hash_key)%h->size;
}

void insert(hash_t *h,char *text){
  // Shifting
  unsigned int index = hash(h,text);
  int i = 1,shift=index;
  while(1){
    if(h->table[shift] == NULL){
      break;
    }
    shift = (index + ((i + (i*i))/2))%(h->size);
    i++;
  }
  // Inserting
  char *item = malloc(sizeof(item));
  strcpy(item,text);
  h->table[shift] = item;
}

int search(hash_t *h,char *text){
  unsigned int index = hash(h,text);
  int i = 1,shift = index;
  while(1){
    if(h->table[shift] == NULL)
      return -1;
    else if(strcmp(h->table[shift],text) == 0)
      return shift;
    shift = (index + ((i + (i*i))/2))%(h->size);
    i++;
  }
}

int main(void) {
  hash_t *hashtable = NULL;
  char   *text = NULL;
  int    m, n, i, hash_key;
  int    command;

  scanf("%d %d %d", &m, &n, &hash_key);
  hashtable = init_hashtable(m, hash_key);
  text = (char *)malloc(sizeof(char)*TEXTSIZE);
  for (i=0; i<n; i++) {
    scanf("%d %s", &command, text);
    switch (command) {
      case 1:
        insert(hashtable, text);
        break;
      case 2:
        printf("%d\n", search(hashtable, text));
        break;
      }
  }
  return 0;
}