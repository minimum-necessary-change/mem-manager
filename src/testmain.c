#include "MemoryManager.h"
#include<string.h>
#include<stdio.h>

char * getCopy(MemoryManager *mm, char *input) {
    // compute the size of the result -- the lesser of the specified maximum
    // and the length of the input string.
    size_t len = strlen(input);

    // allocate space for the result (including NUL terminator).
    char *buffer = (char *) mm->malloc(mm, sizeof(char) * (len+1));

    if (buffer) {
        // if the allocation succeeded, copy the specified number of
        // characters to the destination.
        strncpy(buffer, input, len);
        // and NUL terminate the result.
        buffer[len] = '\0';
    }
    // if we copied the string, return it; otherwise, return the null pointer
    // to indicate failure.
    return buffer;
}

void strcopy(char * dest, char * src, int length){
    strncpy(dest, src, length);
    dest[length] = '\0';
}

int main(int argc, char *argv[]){
    MemoryManager *mm = NULL;
    char *str = NULL;
    int length;

    if (argc < 3){
        printf("Syntax : %s <argument 1> <argument 2> <argument 3>\n", argv[0]);
        return 0;
    }
    mm = (MemoryManager *)getMemoryManager();

    length = strlen(argv[2]);
    str = mm->malloc(mm, (length + 1) * sizeof(char));
    strcopy(str, argv[2], length);
    printf("%s\n", str);
    mm->free(mm, str);

    str = getCopy(mm, argv[1]);
    printf("%s\n", str);


    length = strlen(argv[2]);
    str = mm->calloc(mm, length + 1, sizeof(char));
    strcopy(str, argv[2], length);
    printf("%s\n", str);

    length = strlen(argv[3]);
    str = mm->realloc(mm, str, sizeof(char) * (length + 1));
    strcopy(str, argv[3], length);
    printf("%s\n", str);

    mm->cleanup(mm);
    return 0;
}
