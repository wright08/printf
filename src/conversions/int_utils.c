#include "ft_printf.h"
#include <stdlib.h>

void leader(t_conv *conv)
{
    char	*fix;
    char	*leader;

	leader = NULL;
	if (ft_strchr(conv->flags, '+'))
		leader = "+";
	else if (ft_strchr(conv->flags, ' '))
		leader = " ";
    if (*conv->str == '-' || !leader)
        return ;
    fix = ft_strjoin(leader, conv->str);
    free_swap(conv->str, fix);
}