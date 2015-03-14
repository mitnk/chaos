#include <stdarg.h>
#include <stdio.h>
#include <dbg.h>

int add(int count, ...)
{
    int sum = 0;
    va_list ap;
    int b;
    va_start(ap, count);

    for (int i = 0; i < count; ++i)
    {
        b = va_arg(ap, int);
        sum += b;
    }

    va_end(ap);
    return sum;
}

int
main()
{
    log_info("add(1) = %d", add(1));  // is there a way to determine this is a wrong call?
    log_info("add(1, 1) = %d", add(1, 1));
    log_info("add(2, 1, 2) = %d", add(2, 1, 2));
    log_info("add(3, 1, 2, 3) = %d", add(3, 1, 2, 3));
    log_info("add(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10) = %d", add(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    return 0;
}
