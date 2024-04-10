/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:23:48 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/10 16:06:36 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	convert_plane(t_mini_rt_data *data, t_g_objects *obj, char *v_3d_norm)
{
	if (data->err_code)
	{
		delete_obj(obj);
		return (ft_free_4_str(v_3d_norm, NULL, NULL, NULL));
	}
	obj->v_3d_normal = get_coords_with_range(v_3d_norm, data, -1, 1);
	if (!data->err_code)
		push_to_data_obj(data, obj);
	else
		delete_obj(obj);
}

void	ft_parse_plane(t_mini_rt_data *data, int *eol, char *token)
{
	char		*coords_p;
	char		*v_3d_norm;
	char		*rgb;
	char		*tmp;
	t_g_objects	*new_obj;

	coords_p = NULL;
	v_3d_norm = NULL;
	rgb = NULL;
	tmp = NULL;
	new_obj = NULL;
	if (data->err_code)
		return ;
	if (ft_read_token(&coords_p, data, eol, "Plane: coord_c")
		|| ft_read_token(&v_3d_norm, data, eol, "Plane: diameter")
		|| ft_read_last_token(&rgb, data, eol, "Plane: rgb"))
		return (ft_free_4_str(coords_p, v_3d_norm, rgb, NULL));
	if ((*eol) == 0)
		tmp = ft_read_substr(data, eol);
	if (tmp)
		handle_error(ERR_PARSE_DATA, "Plane: extra data", data);
	free(tmp);
	new_obj = prefilled_obj(data, coords_p, rgb, token);
	convert_plane(data, new_obj, v_3d_norm);
}
