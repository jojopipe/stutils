#include <stdio.h>
#include "stutils.h"

int main(void) {
    char s[] = "2147483647";
    char *end;
    int num = stu_string_to_int_ex(s, &end, 10);
    printf("%s = %d\n", s, num);
    printf("end: %s\n", end);
    return 0;
}
