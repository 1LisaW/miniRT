/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:22:02 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/25 11:24:35 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	n;
	int		is_negative;

	n = 0;
	is_negative = 1;
	while (ft_isspace(*str))
		str++;
	if (ft_issign(*str))
	{
		if (*str == '-')
			is_negative = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		n = (n * 10) + (*str - '0');
		if (n < 0 && is_negative == -1)
			return (0);
		else if (n < 0 && is_negative == 1)
			return (-1);
		str++;
	}
	return (n * is_negative);
}
