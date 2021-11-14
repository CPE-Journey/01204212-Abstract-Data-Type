#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  TEXTSIZE 21

typedef struct item {
  char   *text;
  struct item *next;
} item_t;

typedef struct hash {
  item_t **table;
  int    size;
  int    hash_key;
} hash_t;

hash_t *init_hashtable(int s,int prime){
  hash_t *hash = malloc(sizeof(hash_t)); 
  hash->table = malloc(sizeof(item_t*)*s);
  hash->size = s;
  hash->hash_key = prime;
  return hash;
}

unsigned int preHash_Recursion(char *text,int len,int key){
  if(len==0)
    return (int)text[0];
  return (key*preHash_Recursion(text,len-1,key))+(int)text[len];
}

unsigned int preHash(hash_t *h,char *text){
  return preHash_Recursion(text,strlen(text)-1,h->hash_key)%h->size;
}

void insert(hash_t *h,char *text){
  item_t *item = malloc(sizeof(item_t));
  unsigned int index = preHash(h,text);
  item->text = malloc(strlen(text));
  strcpy(item->text,text);
  item->next = NULL;
  if(h->table[index] == NULL){
    h->table[index] = item;
  }
  else{
    item_t *tmp = h->table[index];
    while(tmp->next != NULL)
      tmp = tmp->next;
    tmp->next = item;
  }
}

int search(hash_t *h,char *text){
  unsigned int index = preHash(h,text);
  if(h->table[index] != NULL){
    item_t *tmp = h->table[index];
    while(tmp != NULL){
      if(strcmp(tmp->text,text) == 0)
        return index;
      else
        tmp = tmp->next;
    }
  }
  return -1;
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