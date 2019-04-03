#include "ft_printf.h"
#include <stdlib.h>

int     conv_mod(t_conv *conv, va_list ap)
{
    (void)ap;
	conv->str = ft_strdup("%");
    conv->len = 1;
    if (needs_zero_pad(conv))
    {
        conv->precision = conv->width;
        zero(conv);
    }
    width(conv);
    return (print(conv));
}

