#define NDEBUG
#include <dbg.h>
#include <stdlib.h>
#include <stdio.h>


int test_check(char *file_name)
{
    FILE *input = NULL;
    char *block = NULL;

    block = malloc(100);
    check_mem(block); // should work

    input = fopen(file_name,"r");
    check(input, "Failed to open %s.", file_name);

    free(block);
    fclose(input);
    return 0;

error:
    if(block) free(block);
    if(input) fclose(input);
    return -1;
}

int
main()
{
    debug("Hello, I'm debuging now.");
    log_info("Hello, I'm debuging now.");
    log_info("There are %d people", 10);
    log_warn("Hello, I'm debuging now.");
    log_err("Hello, I'm debuging now.");
    test_check("ex3");
    test_check("abc.h");
}
