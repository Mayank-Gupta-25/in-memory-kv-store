#ifndef DATASTORE_H
#define DATASTORE_H

// void set_key(const char* key, const char* value);
// const char* get_key(const char*key);
// void delete_key(const char*key);
// void print_store();

void store_init();
void store_set(const char* key, const char* value);
const char* store_get(const char* key);
void store_delete(const char*key);
void store_print();
void store_free();

#endif