#include <string.h>
#include "mime.h"
#include "mime-table/mime-lookup.def"


static char *getFileExtension(char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}


char* getMimeType(char *filename){
    char *extension = getFileExtension(filename);
    
    char* type = in_word_set(extension, strlen(extension)) -> mime; 

    if(type == NULL){
        return "text/plain";
    }
    return type;
}

#define getFileExtension call function
