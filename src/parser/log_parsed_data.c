/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_parsed_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:05:10 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/23 23:21:17 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_print_objects(t_mini_rt_data *data)
{
	t_g_objects	*obj;

	obj = data->objs;
	printf("\nOBJECTS:\n");
	while (obj)
	{
		if (obj->id == pl)
			printf("\nPlane:\n");
		else if (obj->id == sp)
			printf("\nSphere:\n");
		else
			printf("\nCylinder:\n");
		printf("%25s %5.2f %5.2f %5.2f\n", "coordinates:", obj->coords[0],
			obj->coords[1], obj->coords[2]);
		if (obj->v_3d_normal)
			printf("%25s %5.2f %5.2f %5.2f\n", "3d norm. v.:",
				obj->v_3d_normal[0], obj->v_3d_normal[1], obj->v_3d_normal[2]);
		if (obj->id == sp || obj->id == cy)
			printf("%25s %17.2f\n", "diameter:", obj->diam);
		if (obj->id == cy)
			printf("%25s %17.2f\n", "height:", obj->height);
		printf("%25s %5i %5i %5i\n", "rgb:", obj->rgb[0], obj->rgb[1],
			obj->rgb[0]);
		obj = obj->next;
	}
}

void	ft_print_light(t_mini_rt_data *data)
{
	if (data->a_l)
	{
		printf("\nAmbient light:\n");
		printf("%25s %17.2f\n", "ratio:", data->a_l->ratio);
		printf("%25s %5i %5i %5i\n", "rgb:", data->a_l->rgb[0],
			data->a_l->rgb[1], data->a_l->rgb[0]);
	}
	if (!data->l)
		return ;
	printf("\nLight:\n");
	printf("%25s %5.2f %5.2f %5.2f\n", "coordinates:", data->l->coords[0],
		data->l->coords[1], data->l->coords[2]);
	printf("%25s %17.2f\n", "brightness:", data->l->l_brightness);
	printf("%25s %5i %5i %5i\n", "rgb:", data->l->rgb[0], data->l->rgb[1],
		data->l->rgb[0]);
}

void	ft_print_camera(t_mini_rt_data *data)
{
	if (!data->cam)
		return ;
	printf("\nCamera:\n");
	printf("%25s %5.2f %5.2f %5.2f\n", "coordinates:", data->cam->coords[0],
		data->cam->coords[1], data->cam->coords[2]);
	printf("%25s %5.2f %5.2f %5.2f\n", "norm. orientation v:",
		data->cam->v_3d_orient[0], data->cam->v_3d_orient[1],
		data->cam->v_3d_orient[2]);
	printf("%25s %17.2i\n", "fov:", data->cam->fov);
}

void	ft_print_data(t_mini_rt_data *data)
{
	ft_print_light(data);
	ft_print_camera(data);
	ft_print_objects(data);
}
