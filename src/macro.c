/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwright <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 22:41:01 by rwright           #+#    #+#             */
/*   Updated: 2019/04/18 22:43:02 by rwright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

int		main(void)
{
	int		class;
	float	test;

	test = 3.14159f;
	class = fpclassify(test);
	if (class == FP_NORMAL)
		printf("Ladies and gentlemn, we got 'em");
	return (0);
}
