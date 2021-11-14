#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct item {
  char   *text;;
  struct item *next;
} item_t;

typedef struct hash {
  item_t **table;
  int    index;
  int    size;
} hash_t;

hash_t* init_hashtable(int m){
    int i;
    hash_t* h = (hash_t*)malloc(sizeof(hash_t));
    h->table = (item_t**)malloc(sizeof(item_t*)*m);
    for(i=0;i<m;i++){
      h->table[i] = NULL ;
    }
    h->size = m;
    h->index = 0;
    return h;
}

char* sort_char(char word[]){
    int new_word[100];
    int i ,j ,tmp ;
    char sorted_word[strlen(word)];
    static char final_word[100];
    for(i=0;i<strlen(word);i++){
        new_word[i] = word[i];
    }
    for(i=1;i<strlen(word);i++){
        j = i;
        while (j != 0 && new_word[j]<new_word[j-1])
        {
            tmp = new_word[j];
            new_word[j] = new_word[j-1];
            new_word[j-1] = tmp;
            //printf("----%d %d %d\n", new_word[j] ,new_word[j-1] , tmp);
            j--;
        }
    }
    for(i=0;i<strlen(word);i++){
        sorted_word[i] = new_word[i];
        //printf("%c ", sorted_word[i]);
    }
    strcpy(final_word,sorted_word);
    //printf("    %s\n",final_word);
    return final_word;
}

int search(hash_t* h,char* text){
    int i;
    for(i=0;i<h->index;i++){
        //printf("i %d \n", i);
        if(h->table[i] != NULL){
            /*printf("Yo --- i %d ", i);
            printf("%s ", text);
            printf("%s \n", h->table[i]->text);*/
            if(strcmp(h->table[i]->text,text) == 0){
                //printf("yes ");
                //printf("i = %d ", i);
                //printf("%s ", h->table[i]->text);
                //printf("%s ", text);
                return i;
            }
        }
    }
    return -1;
}

int main(void){
    hash_t *h1 = NULL;
    hash_t *h2 = NULL;
    int n , m ,i ,j ,k ,idx;
    scanf("%d %d",&n , &m);
    char word[100];
    char wordo[100];
    char *sorted_word;
    char s_word[100];
    h1 = init_hashtable(n);
    h2 = init_hashtable(n);
    for(i=0;i<n;i++){
        scanf("%s", &word);
        //printf("err ->%s\n", sort_char(word));
        sorted_word = sort_char(word);
        //if(h2->table[0] != NULL) printf("err ->%s ", h2->table[0]->text);
        for(j=0;j<strlen(word);j++){
            //printf("%c ", *(sorted_word+j));
            wordo[j] = word[j];
            s_word[j] = *(sorted_word+j);
            //printf("%c ", s_word[j]);
        }
        //if(h2->table[0] != NULL) printf("err ->%s ", h2->table[0]->text);
        idx = search(h2, s_word);
        item_t* t1 = (item_t*)malloc(sizeof(item_t));
        item_t* t2 = (item_t*)malloc(sizeof(item_t));
        t1->text = (char*)malloc(sizeof(char)*strlen(word));
        t2->text = (char*)malloc(sizeof(char)*strlen(word));
        t1->next = NULL;
        t2->next = NULL;
        strcpy(t1->text , word);
        if(idx == -1){
            //t1->text = word;
            //t2->text = sorted_word;
            //strcpy(t2->text , s_word);
            /*for(j=0;j<strlen(word);j++){
                t2->text[j] = s_word[j];
            }
            for(j=0;j<strlen(word);j++){
                t1->text[j] = wordo[j];
            }*/
            strcpy(t2->text , s_word);
            /*printf("1 %s \n", t1->text);
            printf("2 %s \n", t2->text);
            printf("3 %s \n", wordo);
            printf("4 %s \n", sorted_word);*/
            h1->table[h1->index++] = t1;
            h2->table[h2->index++] = t2;
            /*printf("index %d \n", h1->index);
            printf("------> %s\n",h1->table[h1->index++]->text );
            printf("------> %s\n",h2->table[h2->index++]->text );*/
        }else{
            item_t* tmp = h1->table[idx];
            while(tmp->next != NULL){
                tmp = tmp->next;
            }
            tmp->next = t1;
        }
    }
    for(i=0;i<m;i++){
        scanf("%s", &word);
        sorted_word = sort_char(word);
        //printf("err ->%s\n", sort_char(word));
        idx = search(h2, sorted_word);
        //printf("idx %d \n", idx);
        if(idx == -1){
            printf("\n");
            continue;
        }else{
            item_t* tmp = h1->table[idx];
            //printf("-----------%s \n",h1->table[idx]->text);
            while(tmp->next != NULL){
                printf("%s ",tmp->text);
                tmp = tmp->next;
            }
            printf("%s\n",tmp->text);
        }
        
    }
    /* for(i=0;i<h1->index;i++){
        printf("i %d \n", i);
        if(h1->table[i] != NULL){
            printf("Hii --- i %d ", i);
            printf("%s \n", h1->table[i]->text);
        }
    } */
    return 0;
}