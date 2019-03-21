#include "ft_printf.h"
#include <stdlib.h>

int     conv_mod(t_fmt *fmt, va_list ap)
{
    char    *ret;

    (void)ap;
    ret = ft_strnew(1);
    ret[0] = '%';
    width(fmt, &ret);
    return (print(ret));
}

