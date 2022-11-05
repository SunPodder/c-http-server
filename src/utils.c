#include <sys/stat.h>
#include <linux/stat.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

int strEndsWith(char *str, char *suffix){
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int isFile(char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

