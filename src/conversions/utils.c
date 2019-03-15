#include "ft_printf.h"
#include <stdlib.h>

void	precision(t_fmt *fmt, char **str)
{
	char	*fix;
	int		diff;
	int		neg;

	if (fmt->precision <= 0 && **str == '0')
	{
		free(*str);
		(*str) = ft_strnew(0);
	}
	neg = (*str == '-');
	diff = fmt->precision - (ft_strlen(*str) - neg);
	if (diff > 0)
	{
		fix = ft_strnew(fmt->precision + neg);
		ft_memset(fix + neg, '0', diff);
		if (neg)
			*fix = '-';
		ft_strcat(fix, *str);
		free(*str);
		*str = fix;
	}
}

void	group(t_fmt *fmt, char **str)
{
	char	*fix;
	int		len;
	int		neg;
	int		i;

	if (!ft_strchr(fmt->flags, '\''))
		return ;
	neg = (**str == '-');
	len = ft_strlen(*str - neg) / 3;
	fix = ft_strnew(len + neg);
	i = 0;
	while (len--)
	{
		if (**str && **str % 3 == 0)
			fix[i + neg] = ',';
		else
			fix[i + neg] = *str[i - i / 3 + neg];
		i++;
	}
	if (neg)
		*fix = '-';
	free(*str);
	*str = fix;
}

int		width(t_fmt *fmt, char **str)
{
	char *fix;
	int diff;
	int len;

	len = ft_strlen(str);
	diff = fmt->width - len;
	if (diff <= 0)
		return (1);
	if (ft_strchr(fmt->flags, '0') && !ft_strchr(fmt->flags, '-'))
	{
		fmt->precision = fmt->width - len;
		return (0);
	}
	fix = ft_strnew(fmt->width);
	if (ft_strchr(fmt->flags, '-'))
	{
		ft_strcat(fix, str);
		ft_memset(fix + len, ' ', diff);
	}
	else
	{
		ft_memset(fix + len, ' ', diff);
		ft_memmove(fix, str, len);
	}
	free(*str);
	*str = fix;
}

int		print(t_fmt *fmt, char *str)
{
	int diff;
	char *fix;

	diff = fmt->width - ft_strlen(str);
	if (diff > 0)
	{
		ft_memset((fix = ft_strnew(diff)), ' ', diff);
		if (ft_strchr(fmt->flags, '-'))
		{
			ft_putstr(str);
			ft_putstr(fix);
		}
		else
		{
			ft_putstr(fix);
			ft_putstr(str);
		}
		free(fix);
		return (fmt->width);
	}
	ft_putstr(str);
	return (ft_strlen(str));
}