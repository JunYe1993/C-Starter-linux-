#include <stdio.h>
#include <stdlib.h>
#include "myPthread.h"

int main()
{
    int ret;
    char str[5];
    ret = snprintf(str, 5, "ABCDEF");
    printf("%s\n", str);
    printf("%d\n", ret);
    return 0;
}