#include "ft_printf.h"
#include <stdio.h>

int     main(void)
{
    //ft_printf("'%'#4.X'", 12);
    char *str = "I am speed";
    printf("%p\n", str);
    ft_printf("%p", str);
}