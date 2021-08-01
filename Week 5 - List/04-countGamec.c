#include <stdio.h>
#include <stdlib.h>

typedef struct Player{
    int limit;
    int id;
    struct Player *next;
}Player;

Player *add(Player *player,int num,int uid,int last_one){
    Player *p = player;
    Player *first = player;

    Player *new_player = malloc(sizeof(Player));
    new_player->limit = num;
    new_player->id = uid;
    new_player->next = NULL;
    if(!last_one){
        new_player->next = first;
    }
    if(player==NULL){
        player = new_player;
    }    
    else{
        while(p->next!=NULL){
            p = p->next;
        }
        p->next = new_player;
    }
    return player;
}

Player *out(Player *player,int index){
    Player *p = player;
    Player *start = NULL;
    Player *prev = NULL;

    while(p->next != start){
        start = player;
        p = p->next;
    }
    prev = p;
    
    p = player;
    while(index>0){
        prev = p;
        p = p->next;
        index--;
    }

    prev->next = p->next;
    free(p);
    
    // printf("%d",prev->limit);
    return prev->next;
}

void show(Player *player){
    int i=0;
    while(i<10){
        printf("%d ",player->limit);
        player = player->next;
        i++;
    }
}

int inDigit(int digit,int num){
    while(digit != 0){
        if(num==digit%10){
            return 1;
        }
        digit = digit/10;
    }
    return 0;
}

int main(){
    int n,k,i,lim,count=1;
    Player *player = NULL;

    scanf("%d %d",&n,&k);
    for(i=0;i<n;i++){
        scanf("%d",&lim);
        player = add(player,lim,i+1,(i+1)%n);
    }
    
    i = 0;
    while(n > 1){
        if(count%k==0 || inDigit(count,k)){
            player->limit -= 1;
        }
        if(player->limit == -1){
            player = out(player,0);
            n -= 1;
        }
        else{
            player = player->next;
        }
        count++;
    }
    printf("%d\n",player->id);

}