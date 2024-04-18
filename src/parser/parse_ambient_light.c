/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:25:39 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/18 17:40:27 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	convert_ambient_light(t_mini_rt_data *data, char *a_l_r, char *rgb)
{
	data->a_l = malloc(sizeof(t_ambient_light));
	if (!data->a_l)
		handle_error(ERR_ALLOC_ERR, NULL, data);
	if (!is_float(a_l_r))
		handle_error(ERR_PARSE_DATA,
			"Ambient light: ratio's format is not correct", data);
	if (data->err_code)
		return ;
	data->a_l->ratio = ft_atof(a_l_r);
	free(a_l_r);
	if (!is_float_in_range(data->a_l->ratio, 0, 1.0))
		handle_error(ERR_PARSE_DATA,
			"Ambient light: ratio is out of range [0.0, 1.0]", data);
	if (data->err_code)
		return ;
	data->a_l->rgb = get_rgb_data(data, rgb);
}

void	ft_parse_ambient_light(t_mini_rt_data *data, int *eol)
{
	char	*ambient_light_ratio;
	char	*rgb;
	char	*tmp;

	if (data->a_l)
		handle_error(ERR_PARSE_DATA, "Ambient light (non-unique field)", data);
	if (data->err_code)
		return ;
	tmp = NULL;
	if (ft_read_token(&ambient_light_ratio, data, eol, "Ambient light: ratio"))
		return ;
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
	convert_ambient_light(data, ambient_light_ratio, rgb);
}

void	delete_ambient_light(t_mini_rt_data *data)
{
	if (data && data->a_l)
	{
		if (data->a_l->rgb)
			free(data->a_l->rgb);
		data->a_l->rgb = NULL;
		data->a_l->ratio = 0;
		free(data->a_l);
		data->a_l = NULL;
	}
}
