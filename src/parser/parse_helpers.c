/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:27:39 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/25 12:28:18 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

char	*ft_read_substr(t_mini_rt_data *data)
{
	char	*buff;
	int		i;

	i = 0;
	buff = malloc(2 * sizeof(char));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	while (buff && read(data->fd, buff + i, 1) && buff[i]
		&& (!ft_isspace(buff[i]) || i == 0))
	{
		while (ft_isspace(buff[i]))
			read(data->fd, buff + i, 1);
		i++;
		buff[i] = 0;
		if (i == ft_strlen(buff))
			buff = ft_reallocate(buff, 2);
	}
	if (!buff[0] || buff[0] == 10)
	{
		free(buff);
		buff = NULL;
	}
	return (buff);
}
