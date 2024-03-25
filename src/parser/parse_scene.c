/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:38:28 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/25 12:27:51 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_run_token_logic(t_mini_rt_data *data, char *str)
{
	// int	is_eol;
	// is_eol = 0;
	if (!ft_strcmp(str, AMBIENT_LIGHTNING_TOKEN)
		&& str[ft_strlen(str) - 1] != 10)
		ft_parse_ambient_light(data);
	else
		printf("ELSE %s", str);
	return (1);
}

void	ft_read_str(t_mini_rt_data *data)
{
	char	*token;

	token = ft_read_substr(data);
	if (token == NULL)
		return ;
	ft_run_token_logic(data, token);
}

void	ft_read_file(t_mini_rt_data *data)
{
	ft_read_str(data);
}
