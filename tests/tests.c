#include <assert.h>
#include <stdio.h>
#include <hstr.h>

void test_hstr(void) {
    char *test_chars = "test";
    str_t *str = hstr(test_chars, strlen(test_chars));

    assert(str != NULL);
    assert(strcmp(str->chars, test_chars) == 0);
    assert(str->length == strlen(test_chars));

    hstr_free(str);
}

void test_hstr_free(void) {
    char *test_chars = "test";
    str_t *str = hstr(test_chars, strlen(test_chars));

    assert(hstr_free(str) == 0);
}

void test_hstr_ncopy(void) {
    char *test_chars = "test";
    str_t *src = hstr(test_chars, strlen(test_chars));
    str_t *dest = hstr_ncopy(src, 2);

    assert(dest != NULL);
    assert(strcmp(dest->chars, "te") == 0);
    assert(dest->length == 2);

    hstr_free(src);
    hstr_free(dest);
}

void test_hstr_copy(void) {
    char *test_chars = "test";
    str_t *src = hstr(test_chars, strlen(test_chars));
    str_t *dest = hstr_copy(src);

    assert(dest != NULL);
    assert(strcmp(dest->chars, src->chars) == 0);
    assert(dest->length == src->length);

    hstr_free(src);
    hstr_free(dest);
}

void test_hstr_ncompare(void) {
    char *test_chars1 = "test";
    char *test_chars2 = "tesa";
    str_t *str1 = hstr(test_chars1, strlen(test_chars1));
    str_t *str2 = hstr(test_chars2, strlen(test_chars2));

    assert(hstr_ncompare(str1, str2, 3) == 0);
    assert(hstr_ncompare(str1, str2, 4) > 0);

    hstr_free(str1);
    hstr_free(str2);
}

void test_hstr_compare(void) {
    char *test_chars1 = "test";
    char *test_chars2 = "tesa";
    str_t *str1 = hstr(test_chars1, strlen(test_chars1));
    str_t *str2 = hstr(test_chars2, strlen(test_chars2));

    assert(hstr_compare(str1, str2) > 0);

    hstr_free(str1);
    hstr_free(str2);
}

void test_hstr_tokenize(void) {
    char *test_chars = "test-tokenize-function";
    char *delimiter_chars = "-";
    str_t *str = hstr(test_chars, strlen(test_chars));
    str_t *delimiter = hstr(delimiter_chars, strlen(delimiter_chars));

    str_tokens_t *tokens = hstr_tokenize(str, delimiter);
    assert(tokens != NULL);

    assert(strcmp(tokens->tokens[0]->chars, "test") == 0);
    assert(tokens->tokens[0]->length == strlen("test"));

    assert(strcmp(tokens->tokens[1]->chars, "tokenize") == 0);
    assert(tokens->tokens[1]->length == strlen("tokenize"));

    assert(strcmp(tokens->tokens[2]->chars, "function") == 0);
    assert(tokens->tokens[2]->length == strlen("function"));

    hstr_free(str);
    hstr_free(delimiter);
    hstr_tokens_free(tokens);
}

int main(void) {
    test_hstr();
    test_hstr_free();
    test_hstr_ncopy();
    test_hstr_copy();
    test_hstr_ncompare();
    test_hstr_compare();
    test_hstr_tokenize();
    printf("All tests passed!\n");
    return 0;
}