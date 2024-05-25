/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:53:56 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/05/26 00:40:42 by tklimova         ###   ########.fr       */
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
	normalize_vect(tmp);
	copy_f_vector(tmp, ray.direction);
	return (ray);
}

void	is_closest_obj_in_light(t_closest_obj *cl_obj,
			t_closest_obj *cl_obj_to_light, t_ray *ray)
{
	float	ang_1;
	float	ang_2;
	float	v_from_l[3];
	float	v_from_cam[3];

	ang_1 = 0;
	ang_2 = 0;
	scale_vector(cl_obj->light_ray.direction, -1, v_from_l);
	scale_vector(ray->direction, -1, v_from_cam);
	if (!cl_obj->obj || cl_obj->obj != cl_obj_to_light->obj)
		return ;
	if ((cl_obj->point[0] - EPSILON <= cl_obj_to_light->point[0]
			&& cl_obj->point[0] + EPSILON >= cl_obj_to_light->point[0])
		&& (cl_obj->point[1] - EPSILON <= cl_obj_to_light->point[1]
			&& cl_obj->point[1] + EPSILON >= cl_obj_to_light->point[1])
		&& (cl_obj->point[2] - EPSILON <= cl_obj_to_light->point[2]
			&& cl_obj->point[2] + EPSILON >= cl_obj_to_light->point[2]))
		cl_obj->in_light = 1;
	if (cl_obj->obj->id == pl)
	{
		ang_1 = get_dot_product(cl_obj->obj->v_3d_normal, v_from_l);
		ang_2 = get_dot_product(cl_obj->obj->v_3d_normal, v_from_cam);
		if (ft_abs_f(ang_1 + ang_2) != ft_abs_f(ang_1) + ft_abs_f(ang_2))
			cl_obj->in_light = 0;
	}
}

void	ray_trace(t_mini_rt_data *data, int x, int y)
{
	t_ray			ray;
	t_closest_obj	cl_obj;
	t_closest_obj	cl_obj_to_l;
	int				color;

	ray = calc_ray(data, x, y);
	cl_obj = get_closest_obj(data, ray);
	if (data->l)
	{
		copy_f_vector(data->l->coords, cl_obj.light_ray.position);
		vector_subtract(cl_obj.point, data->l->coords,
			cl_obj.light_ray.direction);
		normalize_vect(cl_obj.light_ray.direction);
		cl_obj_to_l = get_closest_obj(data, cl_obj.light_ray);
		is_closest_obj_in_light(&cl_obj, &cl_obj_to_l, &ray);
		precompute_normal(&cl_obj);
	}
	else
		cl_obj.in_light = false;
	if (cl_obj.dist < FLT_MAX)
		compute_color(&(color), &cl_obj, data);
	else
		color = 0x87CEEB;
	custom_mlx_pixel_put(data->vars->img, x, y,
		color);
}

void	draw(t_mini_rt_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < data->vars->img_data->w_height)
	{
		while (i < data->vars->img_data->w_width)
		{
			if (!data->cam || (!data->a_l && !data->l))
				custom_mlx_pixel_put(data->vars->img, i, j,
					0x000000);
			else
				ray_trace(data, i, j);
			i++;
		}
		j++;
		i = 0;
	}
	apply_img_to_win(data);
}
