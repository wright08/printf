#include "ft_printf.h"
#include <stdlib.h>
#include <stdarg.h>

static unsigned long long arg(t_conv *conv, va_list ap)
{
    if (ft_strchr(conv->len_mod, 'z'))
        return ((size_t)va_arg(ap, size_t));
    if (ft_strchr(conv->len_mod, 'j'))
        return ((uintmax_t)va_arg(ap, uintmax_t));
    if (ft_strequ(conv->len_mod, "l"))
        return (va_arg(ap, unsigned long));
    if (ft_strequ(conv->len_mod, "ll"))
        return (va_arg(ap, unsigned long long));
    return (va_arg(ap, unsigned int));
}

static int  is_zero(t_conv *conv)
{
    char    *scan;

    scan = conv->str;
    while (*scan)
    {
        if (*scan != '0')
            break ;
        scan++;
    }
    return (!*scan);
}

/*
static void alternate(t_conv *conv)
{
    char    *alt;

    if (!ft_strchr(conv->flags, '#') || conv->type == 10)
        return ;
    alt = NULL;
    if (conv->type == 8 && *conv->str != '0')
        alt = "0";
    else if (is_zero(conv))
        ;
    else if (conv->type == 16)
        alt = "0x";
    else if (conv->type == 17)
        alt = "0X";
	conv->len += ft_strlen(alt);
    free_swap(conv, ft_strjoin(alt, conv->str));
}
*/

static void leader(t_conv *conv, char *lead)
{
    ft_bzero(lead, 3);
    if (!ft_strchr(conv->flags, '#') || conv->type == 10)
        return ;
    if (conv->type == 8 && *conv->str != '0')
        *lead = '0';
    else if (is_zero(conv))
        ;
    else if (conv->type == 16)
        ft_strcat(lead, "0x");
    else if (conv->type == 17)
		ft_strcat(lead, "0X");
}

static void build_num(t_conv *conv)
{
    conv->len = ft_strlen(conv->str);
	if (conv->precision == 0 && *conv->str == '0')
	{
		*conv->str = '\0';
		conv->len = 0;
	}
    zero(conv);
}

static void build_conv(t_conv *conv)
{
    char    lead[3];

	build_num(conv);
    leader(conv, lead);
	if (needs_zero_pad(conv))
	{
		conv->precision = conv->width - ft_strlen(lead);
        zero(conv);
    }
	free_swap(conv, ft_strjoin(lead, conv->str));
	conv->len += ft_strlen(lead);
    width(conv);
}

int     conv_uint(t_conv *conv, va_list ap)
{
    if (conv->type == 'o'|| conv->type == 'O')
    {
		conv->type = 8;
        if (conv->type == 'O')
            ft_memmove(conv->len_mod, "l", 2);
    }
    else if (conv->type == 'u')
    {
		conv->type = 10;
        if (conv->type == 'O')
            ft_memmove(conv->len_mod, "l", 2);
    }
    else if (conv->type == 'x')
		conv->type = 16;
    else
        conv->type = 17;
    conv->str = ft_ulltoa_base(arg(conv, ap), conv->type);
    build_conv(conv);
    return (print(conv));
}