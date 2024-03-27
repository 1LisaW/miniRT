/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:12:51 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/27 21:48:46 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_g_objects	*prefilled_obj(t_mini_rt_data *data,
	char *coords, char *rgb, char *token)
{
	t_g_objects	*new_obj;

	new_obj = create_obj(data, token);
	if (new_obj)
	{
		new_obj->coords = get_coords(coords, data);
		new_obj->rgb = get_rgb_data(data, rgb);
	}
	return (new_obj);
}

void	delete_shapes(t_mini_rt_data *data)
{
	t_g_objects	*obj;

	if (!data)
		return ;
	obj = data->objs;
	while (data->objs)
	{
		obj = data->objs;
		data->objs = data->objs->next;
		delete_obj(obj);
	}
	if (data->objs)
		free(data->objs);
	data->objs = NULL;
}
