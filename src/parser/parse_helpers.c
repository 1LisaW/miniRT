/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:27:39 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/10 16:12:14 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_read_isspaces(t_mini_rt_data *data, char *buff, int *i)
{
	*i = 0;
	buff[0] = 0;
	if (data->err_code)
		return ;
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

int	ft_read(t_mini_rt_data *data, int i, char *buff)
{
	int	b_size;

	b_size = read(data->fd, buff + i, 1);
	if (!b_size)
		close(data->fd);
	return (b_size);
}

char	*ft_read_substr(t_mini_rt_data *data, int *eol)
{
	char	*buff;
	int		i;

	buff = malloc(3 * sizeof(char));
	if (!buff)
		handle_error(ERR_ALLOC_ERR, NULL, data);
	ft_read_isspaces(data, buff, &i);
	while (!data->err_code && buff && ft_read(data, i, buff) && buff[i]
		&& !ft_isspace(buff[i]))
	{
		buff[++i] = 0;
		if (!ft_isspace(buff[i - 1]) && i + 1 >= ft_strlen(buff))
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

int	ft_read_token(char **substr, t_mini_rt_data *data, int *eol, char *err_msg)
{
	*substr = ft_read_substr(data, eol);
	if (data->err_code)
		return (1);
	if (!(*substr) || (*eol) == 1)
	{
		handle_error(ERR_PARSE_DATA, err_msg, data);
		return (1);
	}
	return (0);
}

int	ft_read_last_token(char **substr, t_mini_rt_data *data, int *eol,
		char *err_msg)
{
	*substr = ft_read_substr(data, eol);
	if (data->err_code)
		return (1);
	if (!(*substr))
	{
		handle_error(ERR_PARSE_DATA, err_msg, data);
		return (1);
	}
	return (0);
}
