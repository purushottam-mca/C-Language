#include <stdio.h>
#include <stdlib.h>

/* ======================================
   Low-level String Functions (_str*)
   ====================================== */

size_t _strlen(const char *s) {
    size_t len = 0;
    while (s[len] != '\0')
        len++;
    return len;
}

char *_strcpy(char *dest, const char *src) {
    char *start = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return start;
}

char *_strncpy(char *dest, const char *src, size_t n) {
    size_t i = 0;
    for (; i < n && src[i]; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}

int _strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

char *_strcat(char *dest, const char *src) {
    char *start = dest;
    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
    return start;
}

/* ======================================
   String Data Type
   ====================================== */

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} String;

/* ======================================
   Internal Helper
   ====================================== */

static void string_reserve(String *s, size_t new_capacity) {
    if (new_capacity <= s->capacity)
        return;

    char *new_data = (char *)realloc(s->data, new_capacity);
    if (!new_data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    s->data = new_data;
    s->capacity = new_capacity;
}

/* ======================================
   Core API
   ====================================== */

void string_init(String *s) {
    s->capacity = 16;
    s->length = 0;
    s->data = (char *)malloc(s->capacity);
    s->data[0] = '\0';
}

void string_from_cstr(String *s, const char *cstr) {
    s->length = _strlen(cstr);
    s->capacity = s->length + 1;
    s->data = (char *)malloc(s->capacity);
    _strcpy(s->data, cstr);
}

void string_free(String *s) {
    free(s->data);
    s->data = NULL;
    s->length = 0;
    s->capacity = 0;
}

size_t string_length(const String *s) {
    return s->length;
}

void string_clear(String *s) {
    s->length = 0;
    s->data[0] = '\0';
}

/* ======================================
   Append Operations
   ====================================== */

void string_append_cstr(String *s, const char *cstr) {
    size_t add_len = _strlen(cstr);
    size_t required = s->length + add_len + 1;

    if (required > s->capacity)
        string_reserve(s, required * 2);

    _strcat(s->data, cstr);
    s->length += add_len;
}

void string_append_char(String *s, char c) {
    if (s->length + 2 > s->capacity)
        string_reserve(s, s->capacity * 2);

    s->data[s->length++] = c;
    s->data[s->length] = '\0';
}

void string_append(String *dest, const String *src) {
    string_append_cstr(dest, src->data);
}

/* ======================================
   Copy & Compare
   ====================================== */

void string_copy(String *dest, const String *src) {
    string_reserve(dest, src->length + 1);
    _strcpy(dest->data, src->data);
    dest->length = src->length;
}

int string_compare(const String *a, const String *b) {
    return _strcmp(a->data, b->data);
}

/* ======================================
   Substring
   ====================================== */

String string_substring(const String *s, size_t start, size_t len) {
    String sub;
    string_init(&sub);

    if (start >= s->length)
        return sub;

    if (start + len > s->length)
        len = s->length - start;

    string_reserve(&sub, len + 1);
    _strncpy(sub.data, s->data + start, len);
    sub.data[len] = '\0';
    sub.length = len;

    return sub;
}

/* ======================================
   Debug / Print
   ====================================== */

void string_print(const String *s) {
    printf("%s\n", s->data);
}

void string_debug(const String *s) {
    printf("String(\"%s\") len=%zu cap=%zu\n",
           s->data, s->length, s->capacity);
}

/* ======================================
   Demo
   ====================================== */

int main() {
    String s1, s2, sub;

    string_init(&s1);
    string_from_cstr(&s2, "World");

    string_append_cstr(&s1, "Hello ");
    string_append(&s1, &s2);
    string_append_char(&s1, '!');

    string_print(&s1);       // Hello World!
    string_debug(&s1);

    sub = string_substring(&s1, 6, 5);
    string_print(&sub);      // World

    printf("Compare: %d\n", string_compare(&s1, &s2));

    string_free(&s1);
    string_free(&s2);
    string_free(&sub);

    return 0;
}
