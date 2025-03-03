/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:52:47 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/27 14:43:50 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

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

bool	check_norm_vectors(t_mini_rt_data *data)
{
	t_g_objects	*tmp;
	float		length;

	tmp = data->objs;
	if (!data->cam)
		return (true);
	length = get_vector_length(NULL, data->cam->v_3d_orient);
	if (1 - length > EPSILON * 10)
		return (false);
	while (tmp)
	{
		if (tmp->id == pl || tmp->id == cy)
		{
			length = get_vector_length(NULL, tmp->v_3d_normal);
			if (1 - length > EPSILON * 10)
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}
