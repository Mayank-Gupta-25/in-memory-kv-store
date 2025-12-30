#include <stdio.h>
#include <datastore.h>

int main(){

    store_init();

    store_set("name", "Mayank");
    store_set("lang", "C");
    store_set("project", "KV Store");

    printf("name = %s\n", store_get("name"));
    printf("lang = %s\n", store_get("lang"));

    store_delete("lang");

    store_print();
    store_free();

    return 0;
}