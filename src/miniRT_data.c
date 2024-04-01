/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:41:19 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/27 19:29:54 by tklimova         ###   ########.fr       */
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
}

void	delete_mini_rt_data(t_mini_rt_data *data)
{
	delete_ambient_light(data);
	delete_camera(data);
	delete_light(data);
	delete_shapes(data);
	if (data)
		free(data);
}
