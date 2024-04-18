/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:54:08 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/18 17:42:35 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	convert_light(t_mini_rt_data *data, char *coords_lp,
			char *l_b_ratio, char *rgb)
{
	data->l = malloc(sizeof(t_light));
	if (!data->l)
		handle_error(ERR_ALLOC_ERR, NULL, data);
	data->l->coords = get_coords(coords_lp, data);
	data->l->rgb = get_rgb_data(data, rgb);
	if (!is_float(l_b_ratio))
		handle_error(ERR_PARSE_DATA,
			"Light: l_b_ratio's format is not correct", data);
	data->l->l_brightness = ft_atof(l_b_ratio);
	free(l_b_ratio);
	if (!data->err_code && !is_float_in_range(data->l->l_brightness, 0, 1))
		handle_error(ERR_PARSE_DATA,
			"Light: l_b_ratio is out of range [0, 1]", data);
}

void	ft_parse_light(t_mini_rt_data *data, int *eol)
{
	char	*coords_lp;
	char	*rgb;
	char	*l_b_ratio;
	char	*tmp;

	tmp = NULL;
	if (data->l)
		handle_error(ERR_PARSE_DATA, "Light (non-unique field)", data);
	if (data->err_code)
		return ;
	if (ft_read_token(&coords_lp, data, eol, "Light: coord_lp")
		|| ft_read_token(&l_b_ratio, data, eol,
			"Light: light brightness ratio"))
		return ;
	rgb = ft_read_substr(data, eol);
	if (!rgb)
	{
		handle_error(ERR_PARSE_DATA, "Light: rgb", data);
		return ;
	}
	if ((*eol) == 0)
		tmp = ft_read_substr(data, eol);
	if (tmp)
		handle_error(ERR_PARSE_DATA, "Light: extra data", data);
	free(tmp);
	convert_light(data, coords_lp, l_b_ratio, rgb);
}

void	delete_light(t_mini_rt_data *data)
{
	if (data && data->l)
	{
		if (data->l->coords)
			free(data->l->coords);
		if (data->l->rgb)
			free(data->l->rgb);
		data->l->coords = NULL;
		data->l->rgb = NULL;
		data->l->l_brightness = 0;
		free(data->l);
		data->l = NULL;
	}
}
