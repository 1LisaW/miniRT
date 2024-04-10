/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:14:43 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/10 16:22:29 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	convert_sphere(t_mini_rt_data *data, t_g_objects *obj, char *diam)
{
	if (data->err_code)
	{
		ft_free_4_str(diam, NULL, NULL, NULL);
		return (delete_obj(obj));
	}
	if (!is_float(diam))
		handle_error(ERR_PARSE_DATA,
			"Sphere: diam's format is not correct", data);
	obj->diam = ft_atof(diam);
	free(diam);
	if (!data->err_code && !is_float_in_range(obj->diam, 0, (float)INT_MAX))
		handle_error(ERR_PARSE_DATA,
			"Sphere: diam is out of range [0, INT_MAX]", data);
	if (!data->err_code)
		push_to_data_obj(data, obj);
	else
		delete_obj(obj);
}

void	init_sp_tmps(char **coords_c, char **diam, char **rgb,
			char **tmp)
{
	*coords_c = NULL;
	*diam = NULL;
	*rgb = NULL;
	*tmp = NULL;
}

void	ft_parse_sphere(t_mini_rt_data *data, int *eol, char *token)
{
	char		*coords_c;
	char		*diam;
	char		*rgb;
	char		*tmp;
	t_g_objects	*new_obj;

	init_sp_tmps(&coords_c, &diam, &rgb, &tmp);
	new_obj = NULL;
	if (data->err_code)
		return ;
	if (ft_read_token(&coords_c, data, eol, "Sphere: coord_c")
		|| ft_read_token(&diam, data, eol, "Sphere: diameter")
		|| ft_read_last_token(&rgb, data, eol, "Sphere: rgb"))
	{
		ft_free_4_str(coords_c, diam, rgb, NULL);
		return ;
	}
	if ((*eol) == 0)
		tmp = ft_read_substr(data, eol);
	if (tmp)
		handle_error(ERR_PARSE_DATA, "Sphere: extra data", data);
	free(tmp);
	new_obj = prefilled_obj(data, coords_c, rgb, token);
	convert_sphere(data, new_obj, diam);
}
