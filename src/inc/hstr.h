#ifndef HSTR_H__
#define HSTR_H__

#include <stdlib.h>
#include <string.h>

typedef struct {
    char *chars;
    size_t length;
} str_t;

typedef struct {
    str_t **tokens;
    size_t num_tokens;
} str_tokens_t;

str_t * hstr(char *chars, size_t length);

int hstr_free(str_t *str);

str_t * hstr_ncopy(str_t *src, size_t n);

str_t * hstr_copy(str_t *src);

int hstr_nconcat(str_t *dest, str_t *src, size_t n);

int hstr_concat(str_t *dest, str_t *src);

int hstr_ncompare(str_t *s1, str_t *s2, size_t n);

int hstr_compare(str_t *s1, str_t *s2);

str_tokens_t * hstr_tokenize(str_t *str, str_t *delim);

int hstr_tokens_free(str_tokens_t *tokens);

#define PRINT_HSTR(hstr) for (int i = 0; i < (hstr)->length; i++) { printf("%c", (hstr)->chars[i]); } printf("\n");

#endif
