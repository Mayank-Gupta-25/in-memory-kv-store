#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <datastore.h>

#define MAX_INPUT 256

int main(){

    char input[MAX_INPUT];
    store_init();

    printf("In-Memory KV Store (type EXIT to quit)\n");

    while(1){
        printf("> ");
        if(!fgets(input,MAX_INPUT,stdin)){
            break;
        }

        input[strcspn(input,"\n")] = 0;
        if(strlen(input) == 0) continue;

        char* command = strtok(input, " ");

        if(strcmp(command,"SET") == 0){
            char* key = strtok(NULL, " ");
            char* value = strtok(NULL, "");

            if(!key || !value){
                printf("ERR usage : SET key value\n");
                continue;
            }

            store_set(key, value);
            printf("OK\n");

        }
        else if(strcmp(command,"GET")==0){
            char* key = strtok(NULL, " ");

            if(!key){
                printf("ERR usage: GET key value\n");
                continue;
            }

            const char* value = store_get(key);
            if(value){
                printf("%s\n",value);
            }else{
                printf("(nil)\n");
            }
        }
        else if(strcmp(command,"DEL") == 0){
            char* key = strtok(NULL, " ");
            if(!key){
                printf("ERR usage: DEL key value\n");
                continue;
            }
            store_delete(key);
            printf("OK\n");
        }
        else if(strcmp(command,"EXIT")==0){
            break;
        }
        else{
            printf("ERR unknown command\n");
        }
    }
    store_free();
    return 0;
}