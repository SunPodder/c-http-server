#include <string.h>
#include "mime.h"
#include "utils.h"
#include "hash-table.h"

ht_t* table;


void init_mime_table(){
    table = ht_create(10);

    ht_set(table, "html", "text/html");
    ht_set(table, "css", "text/css");
    ht_set(table, "js", "text/javascript");
    ht_set(table, "png", "image/png");
    ht_set(table, "jpg", "image/jpg");
    ht_set(table, "jpeg", "image/jpeg");
    ht_set(table, "ico", "image/vnd.microsoft");
    ht_set(table, "svg", "image/svg+xml");
    ht_set(table, "json", "application/json");
}

char* getMimeType(char *filename){
    
    char *extension = getFileExtension(filename);
    char* type = ht_get(table, extension);

    if(type == NULL){
        return "text/plain";
    }
    return type;
}


