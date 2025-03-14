#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#define S_ALLOC malloc
#define S_REALLOC realloc
#define S_FREE free

// @immutable
// @no_alloc
typedef struct String {
    char *c;
    uint32 length;
} String;

struct StringBuilder {
    String *s;
    uint32 size;
    uint32 capacity;
};

// effectively strlen; assume '\0'
uint32 CharLen(char *c);

void StringNewLen_(String *s, char *c, uint32 len);
String StringNewLen(char *c, uint32 len);

#endif // STRING_H

#define STRING_IMPLEMENTATION // DEBUG
#ifdef STRING_IMPLEMENTATION



#endif // STRING_IMPLEMENTATION
