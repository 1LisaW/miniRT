/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:50:20 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/23 00:11:32 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	convert_camera(t_mini_rt_data *data, char *coords_vp,
			char *v_3d_norm, char *fov)
{
	data->cam = malloc(sizeof(t_camera));
	if (!data->cam)
		handle_error(ERR_ALLOC_ERR, NULL, data);
	data->cam->coords = get_coords(coords_vp, data);
	data->cam->v_3d_orient = get_coords_with_range(v_3d_norm, data, -1, 1);
	if (!is_float(fov))
		handle_error(ERR_PARSE_DATA,
			"Camera: fov's format is not correct", data);
	data->cam->fov = ft_atof(fov);
	free(fov);
	if (!data->err_code && !is_float_in_range(data->cam->fov, 0, 180))
		handle_error(ERR_PARSE_DATA,
			"Camera: fov is out of range [0, 180]", data);
	data->cam->mtx = NULL;
	data->cam->tan_half_fov = 0;
}

void	ft_parse_camera(t_mini_rt_data *data, int *eol)
{
	char	*coords_vp;
	char	*v_3d_norm;
	char	*fov;
	char	*tmp;

	tmp = NULL;
	if (data->cam)
		handle_error(ERR_PARSE_DATA, "Camera (non-unique field)", data);
	if (data->err_code)
		return ;
	if (ft_read_token(&coords_vp, data, eol, "Camera: coord_vp")
		|| ft_read_token(&v_3d_norm, data, eol, "Camera: v_3d_norm"))
		return ;
	fov = ft_read_substr(data, eol);
	if (!fov)
	{
		handle_error(ERR_PARSE_DATA, "Camera: fov", data);
		return ;
	}
	if ((*eol) == 0)
		tmp = ft_read_substr(data, eol);
	if (tmp)
		handle_error(ERR_PARSE_DATA, "Camera: extra data", data);
	free(tmp);
	convert_camera(data, coords_vp, v_3d_norm, fov);
}

void	delete_camera(t_mini_rt_data *data)
{
	if (data && data->cam)
	{
		if (data->cam->coords)
			free(data->cam->coords);
		if (data->cam->v_3d_orient)
			free(data->cam->v_3d_orient);
		data->cam->coords = NULL;
		data->cam->v_3d_orient = NULL;
		data->cam->fov = 0;
		free(data->cam);
		data->cam = NULL;
	}
}
