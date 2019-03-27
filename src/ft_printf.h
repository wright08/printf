#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>

struct	s_fmt
{
	int		precision;
	int		width;
	char	flags[6 + 1];
	char	len[2 + 1];
	char	type;
};
typedef struct s_fmt	t_fmt;
typedef int				(*t_convf)(struct s_fmt *fmt, va_list ap);
struct	s_table
{
	const char		*keys;
	const t_convf	func;
};
typedef struct s_table	t_able;

struct s_conv
{
	t_fmt	fmt;
	char	*str;
	int		len;
	char	sign;
};
typedef struct s_conv	t_conv;

void	zero(int diff, char **str);
void	precision(t_fmt *fmt, char **str);
void	width(t_fmt *fmt, char **str);
int		print(char *str);

int		conv_char(t_fmt *fmt, va_list ap);
int		conv_int(t_fmt *fmt, va_list ap);
int		conv_mod(t_fmt *fmt, va_list ap);
int		conv_pointer(t_fmt *fmt, va_list ap);
int		conv_string(t_fmt *fmt, va_list ap);
int		conv_uint(t_fmt *fmt, va_list ap);

t_fmt	*parse_fmt(const char **format);

void	free_swap(char **str, char *fix);
int		ft_printf(const char *format, ...);

#endif