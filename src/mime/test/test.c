#include <stdio.h>
#include <string.h>
#include "../mime.h"

int main(){

    char* html = getMimeType("index.html");
    char* png = getMimeType("image.png");
    char* wmz = getMimeType("file.wmz");
    char* sub = getMimeType("file.sub");

    if(strcmp(png, "image/png")){
        printf("%s\n", png);
        return -1;
    }

    if(strcmp(html, "text/html")){
        printf("%s\n", html);
        return -1;
    }

    if(strcmp(sub, "image/vnd.dvb.subtitle")){
        printf("%s", sub);
        return -1;
    }

    if(strcmp(wmz, "application/x-ms-wmz")){
        printf("%s", wmz);
        return -1;
    }

    printf("Passed! ✅");

    return 0;
}
