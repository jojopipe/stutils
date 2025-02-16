#include <stdio.h>
#include "stutils.h"

int main(void) {
    char *s = stu_from_file("C:\\Users\\pappr\\programming\\stutils\\LICENSE");
    printf("from file:\n%s\n", s);
    return 0;
}
