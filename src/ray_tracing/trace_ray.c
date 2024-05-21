/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:53:56 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/05/22 00:56:22 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	custom_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_ray	calc_ray(t_mini_rt_data *data, int x, int y)
{
	t_ray	ray;
	float	tmp[3];

	tmp[0] = 0;
	tmp[1] = 0;
	tmp[2] = 0;
	copy_f_vector(data->cam->coords, ray.position);
	ray.direction[0] = (2 * ((x + 0.5) / data->vars->img_data->w_width) - 1)
		* ((float)data->vars->img_data->w_width
			/ data->vars->img_data->w_height) * data->cam->tan_half_fov;
	ray.direction[1] = (1 - 2 * ((y + 0.5) / data->vars->img_data->w_height))
		* data->cam->tan_half_fov;
	ray.direction[2] = 1;
	vector_mtx_multy(ray.direction, data->cam->mtx, tmp);
	copy_f_vector(tmp, ray.direction);
	normalize_vect(ray.direction);
	return (ray);
}

void	is_closest_obj_in_light(t_closest_obj *cl_obj,
			t_closest_obj *cl_obj_to_light)
{
	if (!cl_obj->obj || cl_obj->obj != cl_obj_to_light->obj)
		return ;
	if ((cl_obj->point[0] - EPSILON <= cl_obj_to_light->point[0]
			&& cl_obj->point[0] + EPSILON >= cl_obj_to_light->point[0])
		&& (cl_obj->point[1] - EPSILON <= cl_obj_to_light->point[1]
			&& cl_obj->point[1] + EPSILON >= cl_obj_to_light->point[1])
		&& (cl_obj->point[2] - EPSILON <= cl_obj_to_light->point[2]
			&& cl_obj->point[2] + EPSILON >= cl_obj_to_light->point[2]))
		cl_obj->in_light = 1;
}

void	ray_trace(t_mini_rt_data *data, t_img_data *img_data, int x, int y)
{
	t_ray			ray;
	t_closest_obj	cl_obj;
	t_closest_obj	cl_obj_to_l;

	ray = calc_ray(data, x, y);
	cl_obj = get_closest_obj(data, ray);
	if (data->l)
	{
		copy_f_vector(data->l->coords, cl_obj.light_ray.position);
		vector_subtract(cl_obj.point, data->l->coords, cl_obj.light_ray.direction);
		normalize_vect(cl_obj.light_ray.direction);
		cl_obj_to_l = get_closest_obj(data, cl_obj.light_ray);
		is_closest_obj_in_light(&cl_obj, &cl_obj_to_l);
		precompute_normal(&cl_obj);
	}
	else
		cl_obj.in_light = false;
	if (cl_obj.dist < FLT_MAX)
		compute_color(&(img_data->colors_data[y][x]), &cl_obj, data);
	else
		img_data->colors_data[y][x] = 0x87CEEB;
	custom_mlx_pixel_put(data->vars->img, x, y,
		img_data->colors_data[y][x]);
}

void	draw(t_mini_rt_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	data->vars->img_data->colors_data = malloc((data->vars->img_data->w_height)
			* sizeof(int *));
	if (!data->vars->img_data->colors_data)
		return ;
	while (j < data->vars->img_data->w_height)
	{
		data->vars->img_data->colors_data[j] = NULL;
		data->vars->img_data->colors_data[j]
			= malloc(data->vars->img_data->w_width * sizeof(int));
		if (!data->vars->img_data->colors_data[j])
			break ;
		while (i < data->vars->img_data->w_width)
		{
			if (!data->cam)
				custom_mlx_pixel_put(data->vars->img, i, j,
					0x000000);
			else
				ray_trace(data, data->vars->img_data, i, j);
			i++;
		}
		j++;
		i = 0;
	}
	apply_img_to_win(data);
}
