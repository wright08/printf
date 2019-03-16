#include "ft_printf.h"
#include <stdlib.h>
#include <stdarg.h>

static long long conv_arg(t_fmt *fmt, va_list ap)
{
    if (ft_strequ(fmt->len, "l"))
        return (va_arg(ap, long));
    else if (ft_strequ(fmt->len, "ll"))
        return (va_arg(ap, long long));
    return (va_arg(ap, int));
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
    if (leader && **str == '-')
        return ;
    if (!(fix = ft_strnew(ft_strlen(*str) + 1)))
        exit(1);
    *fix = leader;
    ft_strcat(fix, *str);
    free(*str);
    *str = fix;
}

static void build_num(t_fmt *fmt, char **str)
{
    precision(fmt, str);
	leader(fmt, str);
}

static void build_conv(t_fmt *fmt, char **str)
{
	char	*copy;
	int		len;

	copy = ft_strdup(*str);
	build_num(fmt, str);
	len = (int)ft_strlen(*str);
	if (len < fmt->width && ft_strchr(fmt->flags, '0') && !ft_strchr(fmt->flags, '-'))
	{
		fmt->precision = fmt->width - len;
		build_num(fmt, &copy);
        free(*str);
        *str = copy;
    }
	else
		free(copy);
    width(fmt, str);
}

int     conv_int(t_fmt *fmt, va_list ap)
{
    char    *ret;

    ret = ft_lltoa(conv_arg(fmt, ap));
    build_conv(fmt, &ret);
    return (print(ret));
}