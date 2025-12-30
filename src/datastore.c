#include <stdio.h>
#include <string.h>
#include "datastore.h"

#define MAX_ITEMS 200

typedef struct{
    char key[50];
    char value[50];
} KeyValue;

KeyValue store[MAX_ITEMS];
int count =0 ; 

void set_key(const char*key , const char*val){
    for(int i = 0 ; i<count ; i++){
        if(strcmp(store[i].key,key)==0){
            strcpy(store[i].value,val);
            return ;
        }
    }
    strcpy(store[count].key,key);
    strcpy(store[count].value,val);
    count++;
}
const char*get_key(const char*key){
    for(int i = 0 ; i<count ; i++){
        if(strcmp(store[i].key,key)==0){
            return store[i].value;
        }
    }
    return NULL;
}
void delete_key(const char*key){
    for(int i = 0 ; i<count ; i++){
        if(strcmp(store[i].key,key)==0){
            store[i] = store[count-1];
            count--;
            return ;
        }
    }
}

void print_store(){
    for(int i = 0 ; i<count ; i++){
        printf("%s -> %s\n",store[i].key,store[i].value);
    }
}

