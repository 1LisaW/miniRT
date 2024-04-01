/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:52:47 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/26 22:18:57 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	is_float(char *str)
{
	int	is_dot;

	is_dot = 0;
	if (str && (*str == '+' || *str == '-'))
		str++;
	while (str && *str)
	{
		if (str && *str == '.')
			is_dot++;
		if (is_dot > 1 || (!ft_isdigit(*str) && *str != '.'))
			return (false);
		str++;
	}
	return (true);
}

bool	is_int_in_range(int nb, int min, int max)
{
	if (nb >= min && nb <= max)
		return (true);
	return (false);
}

bool	is_float_in_range(float nb, float min, float max)
{
	if (nb >= min && nb <= max)
		return (true);
	return (false);
}
