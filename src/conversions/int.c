#include "ft_printf.h"
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

static long long conv_arg(t_fmt *fmt, va_list ap)
{
    if (ft_strchr(fmt->len, 'z'))
        return ((ssize_t)va_arg(ap, ssize_t));
    if (ft_strchr(fmt->len, 'j'))
        return ((intmax_t)va_arg(ap, intmax_t));
    if (ft_strequ(fmt->len, "hh"))
        return ((char)va_arg(ap, int));
    if (ft_strequ(fmt->len, "h"))
        return ((short)va_arg(ap, int));
    if (ft_strequ(fmt->len, "l"))
        return ((long)va_arg(ap, long));
    if (ft_strequ(fmt->len, "ll"))
        return (va_arg(ap, long long));
    return ((int)va_arg(ap, int));
}

static void leader(t_fmt *fmt, char **str)
{
    char	*fix;
    char	leader;

	leader = 0;
	if (ft_strchr(fmt->flags, '+'))
		leader = '+';
	else if (ft_strchr(fmt->flags, ' '))
		leader = ' ';
    if (!leader || **str == '-')
        return ;
    if (!(fix = ft_strnew(ft_strlen(*str) + 1)))
        exit(1);
    *fix = leader;
    ft_strcat(fix, *str);
    free(*str);
    *str = fix;
}

static int negative(char **str)
{
    char *fix;

    if (**str == '-')
    {
        fix = ft_strdup(*str + 1);
        free(*str);
        *str = fix;
        return (1);
    }
    return (0);
}

static void build_conv(t_fmt *fmt, char **str)
{
	char	*copy;
	int		len;
    int     neg;

    neg = negative(**str);
	copy = ft_strdup(*str);
    precision(fmt, str);
	leader(fmt, str);
	len = (int)ft_strlen(*str);
	if (len < fmt->width && ft_strchr(fmt->flags, '0') && !ft_strchr(fmt->flags, '-'))
	{
		fmt->precision = fmt->width - len + ft_strlen(copy);
        precision(fmt, str);
        leader(fmt, str);
        free(*str);
        *str = copy;
    }
	else
		free(copy);
    if (neg)
    {
        copy = ft_strnew(ft_strlen(*str) + 1);
        *copy = '-';
        ft_strcat(copy, *str);
        free (*str);
        *str = copy;
    }
    width(fmt, str);
}

int     conv_int(t_fmt *fmt, va_list ap)
{
    char    *ret;

    ret = ft_lltoa(conv_arg(fmt, ap));
    build_conv(fmt, &ret);
    return (print(ret));
}