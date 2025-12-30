#include <stdio.h>
#include <datastore.h>

int main(){
    set_key("name","Mayank");
    set_key("lang","C");

    printf("name = %s\n",get_key("name"));
    printf("lang = %s\n", get_key("lang"));

    delete_key("lang");
    print_store();

    return 0;
}