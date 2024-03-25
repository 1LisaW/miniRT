/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:27:39 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/25 16:08:25 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_read_isspaces(t_mini_rt_data *data, char *buff, int *i)
{
	*i = 0;
	if (data->err_code)
		return ;
	buff[0] = 0;
	while (buff && read(data->fd, buff + *i, 1) && buff[*i])
	{
		if (!ft_isspace(buff[*i]))
		{
			*i += 1;
			buff[*i] = 0;
			break ;
		}
	}
}

char	*ft_read_substr(t_mini_rt_data *data, int *eol)
{
	char	*buff;
	int		i;

	buff = malloc(2 * sizeof(char));
	if (!buff)
		handle_error(ERR_ALLOC_ERR, NULL, data);
	ft_read_isspaces(data, buff, &i);
	while (!data->err_code && buff && read(data->fd, buff + i, 1) && buff[i]
		&& !ft_isspace(buff[i]))
	{
		buff[++i] = 0;
		if (!ft_isspace(buff[i - 1]) && i == ft_strlen(buff))
			buff = ft_reallocate(buff, 2);
	}
	if (i > 0 && buff[i] == 10)
		*eol = 1;
	if (i > 0 && ft_isspace(buff[i]))
		buff[i] = 0;
	if (buff && (!buff[0] || ft_isspace(buff[0])))
	{
		free(buff);
		buff = NULL;
	}
	return (buff);
}
