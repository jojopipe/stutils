/* https://github.com/jojopipe/stutils */

#ifndef STUTILS_STUTILS_H
#define STUTILS_STUTILS_H

#include <stdlib.h>

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
 * compares c against s.
 * \brief is c contained in s?
 * \param c
 * \param s
 * \return 1 if c is contained in s
 * \return 0, else
 */
int stu_char_match(char c, char *s) {
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
        if (stu_char_match(input[i], split)) {
            input[i] = '\0';
            /* look for next non-split char / skip over every split char */
            for (int j = i + 1; j < inputc; ++j) {
                if (stu_char_match(input[j], split)) continue;
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

int stu_string_to_int_ex(const char *s, char **end, int base) {
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

#endif //STUTILS_STUTILS_H
