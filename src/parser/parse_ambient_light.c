/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:25:39 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/25 12:31:33 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"



void	ft_parse_ambient_light(t_mini_rt_data *data)
{
	char	*ambient_light_ratio;
	char	*rgb;
	char	*tmp;

	ambient_light_ratio = ft_read_substr(data);
	if (!ambient_light_ratio
		|| ambient_light_ratio[ft_strlen(ambient_light_ratio) - 1] == 10)
	{
		handle_error(ERR_PARSE_DATA, "Ambient light: ratio", data);
		return ;
	}
	rgb = ft_read_substr(data);
	if (!rgb)
	{
		handle_error(ERR_PARSE_DATA, "Ambient light: rgb", data);
		return ;
	}
	if (rgb[ft_strlen(rgb) - 1] != 10)
		tmp = ft_read_substr(data);
	if (tmp)
		handle_error(ERR_PARSE_DATA, "Ambient light: extra data", data);
	printf("!!!!!!%s %s %s", ambient_light_ratio, rgb, tmp);
}
