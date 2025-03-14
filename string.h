#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#define S_ALLOC malloc
#define S_REALLOC realloc
#define S_FREE free

#define S_MAX(a,b) (a) > (b) ? (a) : (b)

// @immutable
// @no_alloc
typedef struct String {
    char *c;
    uint32_t length;
} String;

// @mutable
// @alloc
typedef struct StringBuilder {
    char *s;
    uint32_t size;
    uint32_t capacity;
} StringBuilder;

// effectively strlen; assume '\0'
uint32_t CharLen(char *c);

void StringNewLen_(String *s, char *c, uint32_t len);
String StringNewLen(char *c, uint32_t len);

void StringNew_(String *s, char *c);
String StringNew(char *c);

/*static void StringBuilderAdjust(StringBuilder *sb, uint32_t len);*/
void StringBuilderAdd(StringBuilder *sb, char c);
void StringBuilderAppend(StringBuilder *sb, char *s);
void StringBuilderAppendArray(StringBuilder *sb, char *sep, char **s, uint32_t size);
void StringBuilderDump(StringBuilder *sb, String *dst);
void StringBuilderFree(StringBuilder *sb);

#define StringBuilderAppendMany(sb, sep, ...) \
    StringBuilderAppendArray((sb), sep, ((char*[]){__VA_ARGS__}), \
                             (uint32_t)(sizeof((char*[]){__VA_ARGS__})/sizeof(char*)))


#endif // STRING_H

#define STRING_IMPLEMENTATION // DEBUG
#ifdef STRING_IMPLEMENTATION

void MemoryCopy(void *dst, void *src, uint32_t size)
{
    char *cdst = dst;
    char *csrc = src;
    while (size--)
    {
        *(cdst--) = *(csrc--);
    }
}

uint32_t CharLen(char *c)
{
    uint32_t size = 0;

    while (*(c + size) != '\0')
    {
        size++;
    }

    return size;
}

void StringNewLen_(String *s, char *c, uint32_t len)
{
    s->c = (c) ? (c) : (char *)"\0";
    s->length = len;
}

String StringNewLen(char *c, uint32_t len)
{
    String result = {0};

    StringNewLen_(&result, c, len);

    return result;
}

void StringNew_(String *s, char *c)
{
    StringNewLen_(s, c, CharLen(c));
}

String StringNew(char *c)
{
    String result = {0};

    StringNewLen_(&result, c, CharLen(c));

    return result;
}

static void StringBuilderAdjust(StringBuilder *sb, uint32_t len)
{
    if (sb->size + len + 1 >= sb->capacity)
    {
        uint32_t newCap = (uint32_t)S_MAX(sb->capacity * 2, sb->size + len + 1);
        sb->s = S_REALLOC(sb->s, newCap);
        sb->capacity = newCap;
    }
}

void StringBuilderAdd(StringBuilder *sb, char c)
{
    StringBuilderAdjust(sb, 1);

    sb->s[sb->size++] = c;
    sb->s[sb->size] = '\0';
}

void StringBuilderAppend(StringBuilder *sb, char *s)
{
    uint32_t len = (uint32_t)CharLen(s);
    StringBuilderAdjust(sb, len);

    /*MemoryCopy((sb->s + sb->size), s, len);*/

    while (len--)
    {
        sb->s[sb->size] = *s++;
        sb->size += 1;
    }
    sb->s[sb->size] = '\0';
}

void StringBuilderAppendArray(StringBuilder *sb, char *sep, char **s, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        StringBuilderAppend(sb, s[i]);
        if (i + 1 < size)
        {
            StringBuilderAppend(sb, sep);
        }
    }
}

void StringBuilderDump(StringBuilder *sb, String *dst)
{
    dst->length = sb->size;
    MemoryCopy(dst->c, sb->s, sb->size);
}

void StringBuilderFree(StringBuilder *sb)
{
    if (sb->s)
    {
        S_FREE(sb->s);
    }
}

#endif // STRING_IMPLEMENTATION
