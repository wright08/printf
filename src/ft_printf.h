#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>

struct s_conv
{
	char	flags[6 + 1];
	int		width;
	int		precision;
	char	len_mod[2 + 1];
	char	type;
	char	*str;
	int		len;
	char	sign;
};
typedef struct s_conv	t_conv;
typedef int				(*t_convf)(t_conv *conv, va_list ap);
struct	s_table
{
	const char		*keys;
	const t_convf	func;
};
typedef struct s_table	t_able;


void	zero(int diff, t_conv *conv);
void	precision(t_conv *conv);
void	width(t_conv *conv);
int		print(t_conv *conv);

int		conv_char(t_conv *conv, va_list ap);
int		conv_int(t_conv *conv, va_list ap);
int		conv_mod(t_conv *conv, va_list ap);
int		conv_pointer(t_conv *conv, va_list ap);
int		conv_string(t_conv *conv, va_list ap);
int		conv_uint(t_conv *conv, va_list ap);

void	parse_fmt(t_conv *conv, const char **format);

void	free_swap(t_conv *conv, char *fix);
int		ft_printf(const char *format, ...);

#endif