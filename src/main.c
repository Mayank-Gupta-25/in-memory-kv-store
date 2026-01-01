#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <datastore.h>

#define PORT 6379
#define BUFFER_SIZE 512

void handle_client(int client_fd){
    char buffer[BUFFER_SIZE];
    
    while(1){
        memset(buffer,0,BUFFER_SIZE);
        
        int bytes = recv(client_fd, buffer, BUFFER_SIZE-1, 0);
        if(bytes <= 0){
            break;
        }

        buffer[strcspn(buffer,"\n")]  = 0 ;
        char* command = strtok(buffer, " ");

        if(!command) continue;

        if(strcmp(command,"SET") == 0){
            char* key = strtok(NULL, " ");
            char* value = strtok(NULL, "");
        
            if(!key || !value){
                send(client_fd, "ERR\n", 4, 0);
                continue;
            }
        
            store_set(key, value);
            send(client_fd, "OK\n", 3, 0);
            
        }
        else if(strcmp(command,"GET")==0){
            char* key = strtok(NULL, " ");
            
            if(!key){
                send(client_fd,"ERR\n", 4, 0);
                continue;
            }
            
            const char* value = store_get(key);
            if(value){
                send(client_fd, value , strlen(value), 0);
                send(client_fd, "\n", 1, 0);
            }else{
                send(client_fd, "(nil)\n", 6, 0);
            }
        }
        else if(strcmp(command,"DEL") == 0){
            char* key = strtok(NULL, " ");
            if(!key){
                send(client_fd,"ERR\n", 4, 0);
                continue;
            }
            store_delete(key);
            send(client_fd, "OK\n", 3, 0);
        }
        else if(strcmp(command,"EXIT")==0){
            break;
        }
        else{
            send(client_fd, "ERR unknown command\n", 20, 0);
        }
    }
    close(client_fd);
}

int main(){

    int server_fd, client_fd;
    struct sockaddr_in address ;
    int addrlen = sizeof(address);
    
    store_init();

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind");
        exit(1);
    }


    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(1);
    }

    printf("KV Store listening on port %d...\n", PORT);

    client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (client_fd < 0) {
        perror("accept");
        exit(1);
    }

    printf("Client connected\n");
    handle_client(client_fd);

    close(server_fd);
    store_free();
    return 0;
}