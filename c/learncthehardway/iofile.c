#include <stdio.h>
#include <string.h>
#include <dbg.h>


void
test_fgets()
{
    printf("Input you name? > ");
    char name[10] = {0};
    char *result = fgets(name, 10, stdin);
    check(result != NULL, "failed to fgets()");
    printf("Welcome, %s\n", name);

error:
    return;
}


void
test_fscanf()
{
    FILE *f = fopen("iofile.data", "r");
    char name[24] = {'H'};
    for (int i = 0; i < 24; ++i)
    {
        printf("name[%d] = '%c'[%d]\n", i, name[i], name[i]);
    }
    memset(name, 'X', 24);
    for (int i = 0; i < 24; ++i)
    {
        printf("name[%d] = '%c'[%d]\n", i, name[i], name[i]);
    }
    int age;
    char professional[24];
    fscanf(f, "%s %d %s", name, &age, professional);
    for (int i = 0; i < 24; ++i)
    {
        printf("name[%d] = '%c'[%d]\n", i, name[i], name[i]);
    }
    log_info("name: %s age: %d professional: %s", name, age, professional);
}


int
main()
{
    test_fgets();
    //test_fscanf();
}
