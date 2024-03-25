/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:38:28 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/25 14:32:39 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_run_token_logic(t_mini_rt_data *data, char *str, int *eol)
{
	if (!ft_strcmp(str, AMBIENT_LIGHTNING_TOKEN) && (*eol) == 0)
		ft_parse_ambient_light(data, eol);
	else
		printf("ELSE |%s|", str);
	return (1);
}

void	ft_read_str(t_mini_rt_data *data)
{
	char	*token;
	int		eol;

	eol = 0;
	token = ft_read_substr(data, &eol);
	if (token == NULL)
		return ;
	ft_run_token_logic(data, token, &eol);
}

void	ft_read_file(t_mini_rt_data *data)
{
	ft_read_str(data);
}
