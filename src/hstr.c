#include <hstr.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

str_t * hstr(char *chars, size_t length) {
    str_t *str = calloc(1, sizeof(str_t));
    if (str == NULL) {
        return NULL;
    }

    str->chars = calloc(1, length);
    if (str->chars == NULL) {
        free(str);
        return NULL;
    }

    memcpy(str->chars, chars, length);
    str->length = length;
    return str;
}

int hstr_free(str_t *str) {
    if (str == NULL) {
        return EINVAL;
    }

    free(str->chars);
    free(str);
    return 0;
}

str_t * hstr_ncopy(str_t *src, size_t n) {
    str_t *dest = calloc(1, sizeof(str_t));
    if (dest == NULL) {
        return NULL;
    }

    dest->chars = calloc(1, n);
    if (dest->chars == NULL) {
        free(dest);
        return NULL;
    }
    
    dest->length = n;
    memcpy(dest->chars, src->chars, n);

    return dest;
}

str_t * hstr_copy(str_t *src) {
    return hstr_ncopy(src, src->length);
}

int hstr_nconcat(str_t *dest, str_t *src, size_t n) {
    char *temp = calloc(1, dest->length + n);
    if (dest == NULL) {
        return ENOMEM;
    }
    
    memcpy(temp, dest->chars, dest->length);
    memcpy(temp + dest->length, src->chars, n);

    free(dest->chars);
    dest->chars = temp;
    dest->length += n;
    return 0;
}

int hstr_concat(str_t *dest, str_t *src) {
    return hstr_nconcat(dest, src, src->length);
}

int hstr_ncompare(str_t *s1, str_t *s2, size_t n) {
    if (s1->length < n || s2->length < n) {
        return EINVAL;
    }
    
    return memcmp(s1->chars, s2->chars, n);
}

int hstr_compare(str_t *s1, str_t *s2) {
    return hstr_ncompare(s1, s2, s1->length < s2->length ? s1->length : s2->length);
}

str_t * hstr_substring(str_t *str, int start, int end) {
    if (start > end || end > str->length) {
        return NULL;
    }
    
    str_t temp = { .chars = str->chars + start, .length = end - start };
    return hstr_copy(&temp);
}

str_tokens_t * hstr_tokenize(str_t *str, str_t *delim) {
    /* Allocate str token struct */
    str_tokens_t *tokens = calloc(1, sizeof(str_tokens_t));
    if (tokens == NULL) {
        return NULL;
    }

    /* Set pointer to substring head */
    int substring_head = 0;  
    /* Iterate through string. Since the delimiter may be longer than
     * one character, we can save some loops by only iterating through
     * string length - delimiter length */
    for (int i = 0; i < str->length - delim->length; i++) {
        /* Create a temporary string to compare with delimiter */
        str_t *temp = hstr_substring(str, i, i + delim->length);
        if (temp == NULL) {
            return NULL;
        }

        /* If the temp string is == delimiter, copy to new string
         * and add to tokens struct */
        if (hstr_compare(temp, delim) == 0) {
            /* Extend tokens array */
            tokens->tokens = realloc(tokens->tokens, sizeof(str_t *) * (tokens->num_tokens + 1));
            if (tokens->tokens == NULL) {
                return NULL;
            }

            /* Copy substring to tokens array */
            tokens->tokens[tokens->num_tokens] = hstr_substring(str, substring_head, i);
            if (tokens->tokens[tokens->num_tokens] == NULL) {
                return NULL;
            }

            tokens->num_tokens++;
            /* Move substring head to next character */
            substring_head = i + delim->length;
        }
        
        /* If we are at the end of the string and have found no delimiter,
         * copy to the tokens array. Gets the end of the string. */
        if (i == str->length - delim->length - 1) {
            /* Extend tokens array */
            tokens->tokens = realloc(tokens->tokens, sizeof(str_t *) * (tokens->num_tokens + 1));
            if (tokens->tokens == NULL) {
                return NULL;
            }
            
            /* Copy substring to tokens array */
            tokens->tokens[tokens->num_tokens] = hstr_substring(str, substring_head, str->length);
            if (tokens->tokens[tokens->num_tokens] == NULL) {
                return NULL;
            }

            tokens->num_tokens++;
        }

        hstr_free(temp);
    }
    return tokens;
}

int hstr_tokens_free(str_tokens_t *tokens) {
    if (tokens == NULL) {
        return EINVAL;
    }

    for (int i = 0; i < tokens->num_tokens; i++) {
        hstr_free(tokens->tokens[i]);
    }

    free(tokens->tokens);
    free(tokens);
    return 0;
}
