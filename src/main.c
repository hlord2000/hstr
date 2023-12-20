#include <stdio.h>
#include <hstr.h>

int main(void) {
    str_t * a = hstr("Hello world!", strlen("Hello world!"));
    str_t * b = hstr(" ", 1);
    
    str_tokens_t *tokens = hstr_tokenize(a, b);

    PRINT_HSTR(a);
    PRINT_HSTR(b);

    for (int i = 0; i < tokens->num_tokens; i++) {
        printf("Index %d: ", i);
        str_t * c = tokens->tokens[i];
        PRINT_HSTR(c);
    }

    // Write some examples with different delimiters similar to the one above
    
    str_t * d = hstr("Aa..Bb..Cc..Dd..Ee", strlen("Aa..Bb..Cc..Dd..Ee"));
    str_t * e = hstr("..", 2);

    str_tokens_t *tokens2 = hstr_tokenize(d, e);

    PRINT_HSTR(d);
    PRINT_HSTR(e);

    for (int i = 0; i < tokens2->num_tokens; i++) {
        printf("Index %d: ", i);
        str_t * f = tokens2->tokens[i];
        PRINT_HSTR(f);
    }

    hstr_free(a);
    hstr_free(b);
    hstr_free(d);
    hstr_free(e);

    hstr_tokens_free(tokens);
    hstr_tokens_free(tokens2);

    return 0;
}
