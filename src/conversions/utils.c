#include "ft_printf.h"

int		print(t_fmt *fmt, char *str)
{
	int len;
	char *fix;

	len = fmt->width - ft_strlen(str);
	if (len > 0)
	{
		ft_memset((fix = ft_strnew(len)), ' ', len);
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