#include <stdio.h>
#include <string.h>
#include "datastore.h"
#include <stdlib.h>

#define TABLE_SIZE 128
// #define MAX_ITEMS 200

// typedef struct{
//     char key[50];
//     char value[50];
// } KeyValue;

// KeyValue store[MAX_ITEMS];
// int count =0 ; 

// void set_key(const char*key , const char*val){
//     for(int i = 0 ; i<count ; i++){
//         if(strcmp(store[i].key,key)==0){
//             strcpy(store[i].value,val);
//             return ;
//         }
//     }
//     strcpy(store[count].key,key);
//     strcpy(store[count].value,val);
//     count++;
// }
// const char*get_key(const char*key){
//     for(int i = 0 ; i<count ; i++){
//         if(strcmp(store[i].key,key)==0){
//             return store[i].value;
//         }
//     }
//     return NULL;
// }
// void delete_key(const char*key){
//     for(int i = 0 ; i<count ; i++){
//         if(strcmp(store[i].key,key)==0){
//             store[i] = store[count-1];
//             count--;
//             return ;
//         }
//     }
// }

// void print_store(){
//     for(int i = 0 ; i<count ; i++){
//         printf("%s -> %s\n",store[i].key,store[i].value);
//     }
// }

typedef struct Entry{
    char* key;
    char*value;
    struct Entry* next;
} Entry;

static Entry* table[TABLE_SIZE];

static unsigned int hash(const char*key){
    unsigned int hash = 0 ;
    while(*key){
        hash = (hash*31)+ *key++;
    }
    return hash % TABLE_SIZE;   
}
void store_init(){
    for(int i = 0 ; i<TABLE_SIZE ; i++){
        table[i] = NULL;
    }
}

void store_set(const char*key , const char*value){
    unsigned int index = hash(key);
    Entry* curr = table[index];
    while(curr){
        if(strcmp(curr->key,key)==0){
            free(curr->value);
            curr->value = strdup(value);
            return ;
        }
        curr = curr->next ;
    }

    Entry* entry = malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    entry->next = table[index];
    table[index] = entry;
}

const char* store_get(const char*key){
    unsigned int index = hash(key);
    Entry* curr = table[index];

    while(curr){
        if(strcmp(curr->key,key) == 0){
            return curr->value;
        }
        curr = curr->next;
    }
    return NULL;
}

void store_delete(const char* key){
    unsigned int index = hash(key);
    Entry* curr = table[index];
    Entry* pre = NULL;

    while(curr){
        if(strcmp(curr->key,key) == 0){
            if(pre) pre->next = curr->next;
            else table[index] = curr->next;

            free(curr->key);
            free(curr->value);
            free(curr);
            return ;
        }
        pre = curr;
        curr = curr -> next;
    }
}

void store_print(){
    for(int i = 0 ; i<TABLE_SIZE ; i++){
        Entry* curr = table[i];
        while(curr){
            printf("%s -> %s\n",curr->key,curr->value);
            curr = curr->next;
        }
    }
}

void store_free(){
    for(int i = 0 ; i<TABLE_SIZE ; i++){
        Entry* curr = table[i];
        while(curr){
            Entry* temp = curr;
            curr = curr->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
}
