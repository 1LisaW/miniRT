/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:25:39 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/25 14:36:11 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_parse_ambient_light(t_mini_rt_data *data, int *eol)
{
	char	*ambient_light_ratio;
	char	*rgb;
	char	*tmp;

	ambient_light_ratio = ft_read_substr(data, eol);
	tmp = NULL;
	if (!ambient_light_ratio || (*eol) == 1)
	{
		handle_error(ERR_PARSE_DATA, "Ambient light: ratio", data);
		return ;
	}
	rgb = ft_read_substr(data, eol);
	if (!rgb)
	{
		handle_error(ERR_PARSE_DATA, "Ambient light: rgb", data);
		return ;
	}
	if ((*eol) == 0)
		tmp = ft_read_substr(data, eol);
	if (tmp)
		handle_error(ERR_PARSE_DATA, "Ambient light: extra data", data);
	free(tmp);
	printf("!!!!!!%s %s %s", ambient_light_ratio, rgb, tmp);
}
