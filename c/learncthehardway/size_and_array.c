#include <stdio.h>

int
main()
{
    int area[4] = {0};
    for (int i=0; i < 4; ++i)
        printf("area[%d] = %d\n", i, area[i]);
    char name[4] = {'a'};
    for (int i=0; i < 4; ++i)
        printf("name[%d] = %c\n", i, name[i]);
    printf("\n");
    return 0;
}
