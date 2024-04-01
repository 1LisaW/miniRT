/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:50:47 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/26 13:28:30 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_atof_cycle(char *str, int *i, float *decimal_factor, float *result)
{
	while (str && str[*i] != '\0')
	{
		if (str[*i] == '.')
		{
			(*i)++;
			while (str[*i] && str[*i] != '\0')
			{
				*result += (str[*i] - '0') * *decimal_factor;
				*decimal_factor *= 0.1;
				(*i)++;
			}
		}
		else if (str[*i])
		{
			*result = *result * 10 + (str[*i] - '0');
			(*i)++;
		}
	}
}

float	ft_atof(char *str)
{
	float	result;
	float	decimal_factor;
	int		sign;
	int		i;

	result = 0.0;
	decimal_factor = 0.1;
	sign = 1;
	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	ft_atof_cycle(str, &i, &decimal_factor, &result);
	return (sign * result);
}
