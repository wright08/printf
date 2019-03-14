#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>

struct s_fmt
{
    char    flags[6 + 1];
    int     width;
    int     precision;
    char    len[2 + 1];
};

typedef int             (*t_conv)(struct s_fmt *fmt, va_list ap);

struct s_table
{
	const char *keys;
	const t_conv func;
};

typedef struct s_fmt    t_fmt;
typedef struct s_table  t_able;


int     ft_printf(const char *format, ...);

t_fmt   *parse_fmt(const char **format);

int     conv_char(t_fmt *fmt, va_list ap);
int     conv_int(t_fmt *fmt, va_list ap);
int     conv_pointer(t_fmt *fmt, va_list ap);
int     conv_string(t_fmt *fmt, va_list ap);
int     conv_uint(t_fmt *fmt, va_list ap);

int     print(t_fmt *fmt, char *str);

#endif