/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:41:19 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/27 14:42:39 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_mini_rt_data(t_mini_rt_data *data)
{
	data->fd = -1;
	data->err_code = 0;
	data->a_l = NULL;
	data->cam = NULL;
	data->l = NULL;
	data->objs = NULL;
	data->vars = NULL;
	data->light_on = false;
	if (data->l)
		data->light_on = true;
	data->active_obj = camera;
	data->active_axis_idx = 0;
}

void	delete_mini_rt_data(t_mini_rt_data *data)
{
	delete_ambient_light(data);
	delete_camera(data);
	delete_light(data);
	delete_shapes(data);
	if (data && data->vars && data->vars->img_data)
		free(data->vars->img_data);
	if (data && data->vars)
		free(data->vars);
	if (data)
		free(data);
}
