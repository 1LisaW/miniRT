/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:14:33 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/13 03:15:18 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	precompute_cylinder_normal(t_closest_obj *cl_obj)
{
	float	cy_tmp[3];
	float	cy_projection[3];

	cy_tmp[0] = 0;
	cy_tmp[1] = 0;
	cy_tmp[2] = cl_obj->cyl_z;
	vector_mtx_multy(cy_tmp, cl_obj->obj->mtxs->dir_mtx, cy_projection);
	cy_projection[0] += cl_obj->obj->mtxs->dir_mtx[12];
	cy_projection[1] += cl_obj->obj->mtxs->dir_mtx[13];
	cy_projection[2] += cl_obj->obj->mtxs->dir_mtx[14];
	vector_subtract(cl_obj->point, cy_projection, cl_obj->normal);
	normalize_vect(cl_obj->normal);
}

void	precompute_normal(t_closest_obj	*cl_obj)
{
	if (cl_obj->dist >= (float) INT_MAX || !cl_obj->in_light)
		return ;
	if (cl_obj->obj->id == pl)
		copy_f_vector(cl_obj->obj->v_3d_normal, cl_obj->normal);
	else if (cl_obj->obj->id == sp)
	{
		vector_subtract(cl_obj->point, cl_obj->obj->coords, cl_obj->normal);
		if (cl_obj->obj->diam / 2 > sqrtf(get_vector_length(cl_obj->point,
					cl_obj->obj->coords)))
			scale_vector(cl_obj->normal, -1, cl_obj->normal);
	}
	else if (cl_obj->obj->id == cy && cl_obj->surf_cy == 1)
		copy_f_vector(cl_obj->obj->v_3d_normal, cl_obj->normal);
	else if (cl_obj->obj->id == cy && cl_obj->surf_cy == -1)
		scale_vector(cl_obj->obj->v_3d_normal, -1, cl_obj->normal);
	else if (cl_obj->obj->id == cy)
		precompute_cylinder_normal(cl_obj);
}
