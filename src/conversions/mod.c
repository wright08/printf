#include "ft_printf.h"
#include <stdlib.h>

int     conv_mod(t_conv *conv, va_list ap)
{
    (void)ap;
	conv->str = ft_strdup("%");
    width(conv);
    return (print(conv));
}
