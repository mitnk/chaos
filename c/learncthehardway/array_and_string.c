#include <stdio.h>

int
main()
{
    int area[] = {10, 12, 13, 14, 20};
    printf("size of area: %ld second item: %d\n", sizeof(area) / sizeof(int), area[1]);
    return 0;
}
