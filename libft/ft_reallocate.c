/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reallocate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:50:40 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/26 13:21:26 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_reallocate(char *str, int plus_size)
{
	char	*new_str;
	int		i;

	new_str = NULL;
	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + plus_size));
	if (!new_str)
		return (NULL);
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	new_str[i + 1] = 0;
	free(str);
	return (new_str);
}
