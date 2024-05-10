/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:45:49 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/10 15:31:48 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


bool	intersect_cy_surf(t_g_objects *obj, t_ray *cy_ray,
			t_closest_obj *cl_obj, t_ray *cy_surf)
{
	float	denominator;
	float	to_surf_c_ray[3];
	float	surf_ray[3];
	float	root;
	float	intersect_point[3];

	denominator = get_dot_product(cy_surf->direction, cy_ray->direction);
	if (denominator > EPSILON || denominator < -EPSILON)
	{
		vector_subtract(cy_surf->position, cy_ray->position, to_surf_c_ray);
		root = get_dot_product(to_surf_c_ray, cy_surf->direction) / denominator;
		if (root > 0 && root < cl_obj->dist)
		{
			get_intersection_point(cy_ray, root, intersect_point);
			vector_subtract(intersect_point, cy_surf->position, surf_ray);
			denominator = get_dot_product(surf_ray, surf_ray);
			if (get_dot_product(surf_ray, surf_ray) < (pow(obj->diam, 2) / 4))
			{
				cl_obj->obj = obj;
				cl_obj->dist = root;
				copy_f_vector(intersect_point, cl_obj->point);
				return (true);
			}
		}
	}
	return (false);
}

bool	intersect_cy_side(t_g_objects *obj, t_ray *cy_ray,
			t_closest_obj *cl_obj)
{
	t_sphere_eq	sph_eq;
	float		intersect_coords[3];

	sph_eq.a = pow(cy_ray->direction[0], 2) + pow(cy_ray->direction[1], 2);
	sph_eq.b = 2 * (cy_ray->position[0] * cy_ray->direction[0]
			+ cy_ray->position[1] * cy_ray->direction[1]);
	sph_eq.c = pow(cy_ray->position[0], 2) + pow(cy_ray->position[1], 2)
		- (pow(obj->diam, 2) / 4);
	sph_eq.discr = sph_eq.b * sph_eq.b - 4 * sph_eq.a * sph_eq.c;
	if (sph_eq.discr < 0)
		return (false);
	sph_eq.root[0] = (-1 * sph_eq.b - sqrt(sph_eq.discr)) / (2 * sph_eq.a);
	sph_eq.root[1] = (-1 * sph_eq.b + sqrt(sph_eq.discr)) / (2 * sph_eq.a);
	if ((sph_eq.root[0] < 0 || cl_obj->dist <= sph_eq.root[0])
		&& (sph_eq.root[1] < 0 || cl_obj->dist <= sph_eq.root[1]))
		return (false);
	if (sph_eq.root[0] < 0 || (sph_eq.root[1] > 0
			&& sph_eq.root[0] > sph_eq.root[1]))
		sph_eq.root[0] = sph_eq.root[1];
	get_intersection_point(cy_ray, sph_eq.root[0], intersect_coords);
	if (!(intersect_coords[2] >= obj->height / -2
			&& intersect_coords[2] <= obj->height / 2))
		return (false);
	cl_obj->dist = sph_eq.root[0];
	cl_obj->obj = obj;
	copy_f_vector(intersect_coords, cl_obj->point);
	return (true);
}

void	intersect_cylinder(t_g_objects *obj, t_ray ray, t_closest_obj *cl_obj)
{
	t_ray	cy_ray;

	vector_mtx_multy(ray.position, obj->mtxs->inv_mtx, cy_ray.position);
	vector_mtx_multy(ray.direction, obj->mtxs->inv_mtx, cy_ray.direction);
	cy_ray.position[0] += obj->mtxs->inv_mtx[12];
	cy_ray.position[1] += obj->mtxs->inv_mtx[13];
	cy_ray.position[2] += obj->mtxs->inv_mtx[14];
	normalize_vect(cy_ray.direction);
	if (intersect_cy_surf(obj, &cy_ray, cl_obj, &(obj->mtxs->top_surf)))
		cl_obj->surf_cy = 1;
	if (intersect_cy_surf(obj, &cy_ray, cl_obj, &(obj->mtxs->bot_surf)))
		cl_obj->surf_cy = -1;
	if (intersect_cy_side(obj, &cy_ray, cl_obj))
		cl_obj->surf_cy = 0;
	if (cl_obj->obj == obj)
	{
		vector_mtx_multy(cl_obj->point, obj->mtxs->dir_mtx, cl_obj->point);
		cl_obj->point[0] += obj->mtxs->dir_mtx[12];
		cl_obj->point[1] += obj->mtxs->dir_mtx[13];
		cl_obj->point[2] += obj->mtxs->dir_mtx[14];
	}
}
