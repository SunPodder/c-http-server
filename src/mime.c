#include <string.h>
#include "mime.h"


char *getFileExtension(const char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

char* getMimeType(char *filename){
    
    char *extension = getFileExtension(filename);

    char *extensions[] = {
        "html",
        "css",
        "js",
        "png",
        "jpg",
        "jpeg",
        "ico",
        "svg",
        "json",
        ""
    };

    char *types[] = {
        "text/html",
        "text/css",
        "text/javascript",
        "image/png",
        "image/jpeg",
        "image/jpeg",
        "image/vnd.microsoft",
        "image/svg+xml",
        "application/json",
        "text/plain"
    };


    int count = sizeof(types)/sizeof(types[0]);
    int i;
    for(i = 0; i <= count; i++){
        if(strcmp(extensions[i], extension) == 0){
            break;
        }
        if(i == count) break;
    }
    return types[i];
}


