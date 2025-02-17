/* https://github.com/jojopipe/stutils */

#ifndef STUTILS_STUTILS_C
#define STUTILS_STUTILS_C

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//TODO: string builder (?)

struct stu_string {
    int length;
    char *s;
};

/**
 * returns the length of a zero-terminated string, excluding the end zero
 * @param s input string
 * @return length of string
 */
int stu_string_length(const char *s) {
    char curr;
    int c = 0;
    while (1) {
        curr = s[c++];
        if (curr == 0) break;
    }
    return c-1;
}

/**
 * checks whether c is contained in s.
 * \brief c contained in s?
 * \param c character to match
 * \param s string to check
 * \return 1, if c is contained in s
 * \return 0, else
 */
int stu_contains_char(char c, char *s) {
    char *end = &s[stu_string_length(s)];
    for (char *p = s; p < end; ++p) { //pointer magic
        if (*p == c) {
            return 1;
        }
    }
    return 0;
}

/**
 * \warning this function directly manipulates the input string!
 *
 * \brief takes a string and splits it by the passed character. split-strings are collected in output.
 * \param output output array, filled with sub-strings of input, needs to be allocated beforehand
 * \param outputc length of output array
 * \param input string to be splitted
 * \param split characters to split by
 * \returns (pseudo returns) output, outputc
 */
void stu_string_split(char **output, int *outputc, char *input, char split[]) {
    if (!input) return;
    int inputc = stu_string_length(input);
    *outputc = 0;
    output[*outputc] = input;
    for (int i = 1; i < inputc; ++i) {
        if (input[i] == '\0') break;
        if (stu_contains_char(input[i], split)) {
            input[i] = '\0';
            /* look for next non-split char / skip over every split char */
            for (int j = i + 1; j < inputc; ++j) {
                if (stu_contains_char(input[j], split)) continue;
                if (input[j] == '\0') break;
                output[++(*outputc)] = &input[j];
                i += (j - i - 1);
                break;
            }
        }
    }
    output[++(*outputc)] = NULL;
    /* ↑↑↑
     * increment once more, since, to this point,
     * outputc only represented the last index of the array
     * also add NULL as last element
     */
}

/**
 * converts s to an integer. assumes input string is in base 10
 * @param s input string
 * @return converted int
 */
int stu_string_to_int(const char *s) {
    int out = 0;
    char curr;
    int sign = 0;
    if (*s == '-') sign = -1;
    else if (*s == '+') sign = 1;
    for (int i = (sign ? 1 : 0); i < stu_string_length(s); ++i) {
        curr = s[i];
        if (!('0' <= curr && curr <= '9')) break;
        out *= 10;
        out += (int) curr - '0';
    }
    return out * (sign ? sign : 1);
}

/**
 * converts string s to an integer
 * @warning max base is 36
 * @param s string to be converted
 * @param end pointer to the first non-number char
 * @param base base to convert from
 * @return converted int
 */
int stu_string_to_int_ex(const char *s, char **end, int base) {
    assert(1 <= base && base <= 36);
    int out = 0;
    char curr;
    int sign = 0;
    if (*s == '-') sign = -1;
    else if (*s == '+') sign = 1;
    int i;
    for (i = (sign ? 1 : 0); i < stu_string_length(s); ++i) {
        curr = s[i];
        if ('0' <= curr && curr <= '0' + base-1) {
            out *= base;
            out += (int) curr - '0';
        }
        else if (base > 10 && 'a' <= curr && curr <= 'a' + base-11) {
            out *= base;
            out += (int) curr - 'a' + 10;
        }
        else if ('A' <= curr && curr <= 'A' + base-11) {
            out *= base;
            out += (int) curr - 'A' + 10;
        }
        else {
            break;
        }
    }
    *end = (char*) s+i;
    return out * (sign ? sign : 1);
}

/**
 * checks whether a zero-terminated string ends with pattern
 * @param s zero-terminated string to be checked
 * @param pattern pattern to be compared against, should also be zero-terminated
 * @return 1, if s ends with pattern
 * @return 0, else
 */
int stu_string_endswith(const char *s, const char *pattern) {
    int slen = stu_string_length(s)-1;
    int plen = stu_string_length(pattern)-1;
    char scurr;
    char pcurr;
    for (int i = 0; i < slen; ++i) {
        scurr = s[slen-i];
        pcurr = pattern[plen-i];
        if (scurr != pcurr) return 0;
        if (pattern == &pattern[plen-i]) break; //reached first char of pattern
    }
    return 1;
}

/**
 * reads file file_name and allocates a string, which the file content is written to
 * @warning the user is responsible to free the allocated memory
 * @param file_name file to read
 */
char *stu_from_file(const char *file_name) {
    FILE *file = fopen(file_name, "rb");
    if (!file) {
        printf("file could not be opened.");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);
    char *buffer = malloc(length + 1);
    if (!buffer) {
        printf("malloc failed.");
        exit(1);
    }
    if(!fread(buffer, 1, length, file)) {
        printf("fread failed.");
        exit(1);
    }
    buffer[length] = '\0';
    return buffer;
}

/**
 * replaces all characters r in zero-terminated string s with w
 * @param s string
 * @param r replaced character
 * @param w replacing character
 */
void stu_replace(char *s, char r, char w) {
    int len = stu_string_length(s);
    for (int i = 0; i < len; ++i) {
        if (s[i] == r)
            s[i] = w;
    }
}

#endif //STUTILS_STUTILS_C
