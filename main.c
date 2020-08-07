#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myPthread.h"

typedef void (* CALLBACK) (int);

int main()
{
    char * ptr;
    //char ptr[4];
    char * data = "123456789";
    //ptr = calloc(sizeof(data), sizeof(char));
    memcpy(ptr, data, 10);
    printf("%s\n", ptr);
    return 0;
}