#include <stdio.h>
#include "stutils.h"

int main(void) {
    char s[] = "2147483647";
    char *end;
    int num = stu_string_to_int_ex(s, &end, 10);
    printf("%s = %d\n", s, num);
    printf("end: %s\n----------------------\n", end);
    printf("%s\n", stu_string_endswith("stutils/main.c", ".c") ? "true" : "false");
    return 0;
}
