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

hash_t* init_hashtable(int m, int hash_key){
    hash_t* hash  = (hash_t*)malloc(sizeof(hash_t));
    hash->size = m;
    hash->hash_key = hash_key;
    hash->table = (item_t**)malloc(sizeof(item_t*) * (m+2));
    int i;
    for(int i=0;i<m+2;i++){
        hash->table[i] = NULL;
    }
    return hash;
}
unsigned int func(hash_t* hash,char* str,int i){
    if (i==0){
        return (int)str[i];
    }
    return (hash->hash_key*func(hash,str,i-1)) + (int)str[i];
}
unsigned int hashed(hash_t* hash,char* str){
    return func(hash,str,strlen(str)-1) % (hash->size);
}
void insert(hash_t* hash,char text[]){
    unsigned int ind  = hashed(hash,text);
    item_t* temp = (item_t*)malloc(sizeof(item_t));
    temp->text = (char*)malloc(sizeof(char)*TEXTSIZE);
    strcpy(temp->text,text);
    temp->next = NULL;
    if (hash->table[ind] == NULL){
        hash->table[ind] = temp;
    }
    else{
        item_t* head = hash->table[ind];
        while(head->next!=NULL)
            head = head->next;
        head->next = temp;
    }
}
int search(hash_t* hash,char text[]){
    unsigned int ind = hashed(hash,text);
    if (hash->table[ind] == NULL){
        return -1;
    }
        
    item_t* head = hash->table[ind];
    while(head!=NULL){
        if (strcmp(head->text,text)==0)
            return ind;
        head = head->next;
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