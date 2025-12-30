#ifndef DATASTORE_H
#define DATASTORE_H

void set_key(const char* key, const char* value);
const char* get_key(const char*key);
void delete_key(const char*key);
void print_store();

#endif