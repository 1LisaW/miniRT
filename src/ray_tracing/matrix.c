/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:06:05 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/26 00:56:41 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vect	compute_forward(float *mtx, float *vector)
{
	t_vect	forward_v;

	forward_v = fill_vector(vector[0], vector[1], vector[2]);
	mtx[8] = forward_v.x;
	mtx[9] = forward_v.y;
	mtx[10] = forward_v.z;
	return (forward_v);
}

t_vect	compute_right_left(float *mtx, t_vect forward, bool is_cy)
{
	t_vect	up;
	t_vect	left;

	if (ft_abs_f(forward.x) <= EPSILON && ft_abs_f(forward.z) <= EPSILON)
	{
		if (forward.y > 0)
			up = fill_vector(0, 0, -1);
		else
			up = fill_vector(0, 0, 1);
	}
	else
		up = fill_vector(0, 1, 0);
	if (is_cy && ft_abs_f(forward.y) >= 0.707)
	{
		up.x = 1;
		if (forward.y < 0)
			up.x = -1;
		up.y = 0;
		up.z = 0;
	}
	left = cross_product(up, forward);
	mtx[0] = left.x;
	mtx[1] = left.y;
	mtx[2] = left.z;
	return (left);
}

void	compute_up_down(float *mtx, t_vect forward, t_vect left)
{
	t_vect	up;

	up = cross_product(forward, left);
	mtx[4] = up.x;
	mtx[5] = up.y;
	mtx[6] = up.z;
}

// mtx [0 - 2] - right-left view
// mtx [4 - 6] - up-bottom view
// mtx [8 - 10] = forward view
// mtx [12 -14] - center of camera
void	create_camera_mtx(t_mini_rt_data *data)
{
	float	*mtx;
	t_vect	forward;
	t_vect	left;

	data->cam->mtx = (float *) malloc(sizeof(float) * 16);
	if (!data->cam->mtx)
		return ;
	mtx = data->cam->mtx;
	mtx[3] = 0;
	mtx[7] = 0;
	mtx[11] = 0;
	mtx[15] = 1;
	forward = compute_forward(mtx, data->cam->v_3d_orient);
	left = compute_right_left(mtx, forward, 0);
	compute_up_down(mtx, forward, left);
	mtx[12] = data->cam->coords[0];
	mtx[13] = data->cam->coords[1];
	mtx[14] = data->cam->coords[2];
}

void	create_cyl_mtx(t_g_objects *obj)
{
	float	*mtx;
	t_vect	forward;
	t_vect	left;

	obj->mtxs->dir_mtx = (float *) malloc(sizeof(float) * 16);
	if (!obj->mtxs->dir_mtx)
		return ;
	mtx = obj->mtxs->dir_mtx;
	mtx[3] = 0;
	mtx[7] = 0;
	mtx[11] = 0;
	mtx[15] = 1;
	forward = compute_forward(mtx, obj->v_3d_normal);
	left = compute_right_left(mtx, forward, 1);
	compute_up_down(mtx, forward, left);
	mtx[12] = obj->coords[0];
	mtx[13] = obj->coords[1];
	mtx[14] = obj->coords[2];
}
