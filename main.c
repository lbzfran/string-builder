
#include "string.h"
#include <stdio.h>

int main(void)
{
    String test = StringNew("Howdy!");

    printf("words: %s\n", test.c);

    StringBuilder sb = {0};

    StringBuilderAppendMany(&sb, ", ", "wow", "that's", "magical!");

    printf("built words: %s\n", sb.s);

    StringBuilderFree(&sb);
    return 0;
}
