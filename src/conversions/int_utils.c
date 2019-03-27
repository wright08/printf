#include "ft_printf.h"
#include <stdlib.h>

void leader(t_fmt *fmt, char **str)
{
    char	*fix;
    char	*leader;

	leader = NULL;
	if (ft_strchr(fmt->flags, '+'))
		leader = "+";
	else if (ft_strchr(fmt->flags, ' '))
		leader = " ";
    if (**str == '-' || !leader)
        return ;
    if (!(fix = ft_strjoin(leader, *str)))
        exit(1);
    free_swap(str, fix);
}