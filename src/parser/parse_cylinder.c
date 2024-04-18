/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:36:33 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/18 17:41:30 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	convert_cylinder(t_mini_rt_data *data, t_g_objects *obj,
			char *v_3d_norm, char **d_h_and_tmp)
{
	if (data->err_code)
	{
		delete_obj(obj);
		return (ft_free_4_str(v_3d_norm, d_h_and_tmp[0], d_h_and_tmp[1], NULL));
	}
	obj->v_3d_normal = get_coords_with_range(v_3d_norm, data, -1, 1);
	obj->diam = ft_atof(d_h_and_tmp[0]);
	free(d_h_and_tmp[0]);
	if (!data->err_code && !is_float_in_range(obj->diam, 0, INT_MAX))
		handle_error(ERR_PARSE_DATA,
			"Plane: diam is out of range [0, INT_MAX]", data);
	obj->height = ft_atof(d_h_and_tmp[1]);
	free(d_h_and_tmp[1]);
	if (!data->err_code)
		push_to_data_obj(data, obj);
	else
		delete_obj(obj);
}

void	ft_parse_cylinder(t_mini_rt_data *data, int *eol, char *token)
{
	char		*coords_c;
	char		*v_3d_norm;
	char		*d_h_and_tmp[3];
	char		*rgb;
	t_g_objects	*new_obj;

	d_h_and_tmp[2] = NULL;
	if (data->err_code)
		return ;
	if (ft_read_token(&coords_c, data, eol, "Cylinder: coord_c")
		|| ft_read_token(&v_3d_norm, data, eol, "Cylinder: v_3d_norm")
		|| ft_read_token(&(d_h_and_tmp[0]), data, eol, "Cylinder: diameter")
		|| ft_read_token(&(d_h_and_tmp[1]), data, eol, "Cylinder: height")
		|| ft_read_last_token(&rgb, data, eol, "Cylinder: rgb"))
	{
		ft_free_4_str(coords_c, v_3d_norm, d_h_and_tmp[0], d_h_and_tmp[1]);
		return (ft_free_4_str(rgb, NULL, NULL, NULL));
	}
	if ((*eol) == 0)
		d_h_and_tmp[2] = ft_read_substr(data, eol);
	if (d_h_and_tmp[2])
		handle_error(ERR_PARSE_DATA, "Plane: extra data", data);
	free(d_h_and_tmp[2]);
	new_obj = prefilled_obj(data, coords_c, rgb, token);
	convert_cylinder(data, new_obj, v_3d_norm, d_h_and_tmp);
}
