/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:48:37 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/13 14:39:41 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Fill coordinates of the intersection, depending on the ray
// shot by the camera and the distance calculated beforehand.
void	get_intersection_point(t_ray *ray, float intersect_dist,
		float intersect_coords[3])
{
	float	vect[3];

	scale_vector(ray->direction, intersect_dist, vect);
	vector_add(ray->position, vect, intersect_coords);
}

void	intersect_sphere(t_g_objects *obj, t_ray ray, t_closest_obj *cl_obj)
{
	t_sphere_eq	sph_eq;

	vector_subtract(obj->coords, ray.position, sph_eq.oc);
	sph_eq.a = get_dot_product(ray.direction, ray.direction);
	sph_eq.b = get_dot_product(ray.direction, sph_eq.oc) * -2;
	sph_eq.c = get_dot_product(sph_eq.oc, sph_eq.oc) - 0.25
		* (obj->diam * obj->diam);
	sph_eq.discr = sph_eq.b * sph_eq.b - 4 * sph_eq.a * sph_eq.c;
	if (sph_eq.discr < 0)
		return ;
	sph_eq.root[0] = (-1 * sph_eq.b - sqrt(sph_eq.discr)) / (2 * sph_eq.a);
	sph_eq.root[1] = (-1 * sph_eq.b + sqrt(sph_eq.discr)) / (2 * sph_eq.a);
	if ((sph_eq.root[0] > 0 && cl_obj->dist > sph_eq.root[0])
		|| (sph_eq.root[1] > 0 && cl_obj->dist > sph_eq.root[1]))
		cl_obj->obj = obj;
	if (sph_eq.root[0] > 0 && cl_obj->dist > sph_eq.root[0])
		cl_obj->dist = sph_eq.root[0];
	else if (sph_eq.root[1] > 0 && cl_obj->dist > sph_eq.root[1])
		cl_obj->dist = sph_eq.root[1];
	if (cl_obj->obj == obj)
		get_intersection_point(&ray, cl_obj->dist, cl_obj->point);
}

void	intersect_plane(t_g_objects *obj, t_ray ray, t_closest_obj *cl_obj)
{
	float	denominator;
	float	root;
	float	vect[3];

	denominator = get_dot_product(obj->v_3d_normal, ray.direction);
	if (denominator < -1e-6 || denominator > 1e-6)
	{
		vector_subtract(obj->coords, ray.position, vect);
		root = get_dot_product(vect, obj->v_3d_normal) / denominator;
		if (root >= 0 && root < cl_obj->dist)
		{
			cl_obj->obj = obj;
			cl_obj->dist = root;
			get_intersection_point(&ray, cl_obj->dist, cl_obj->point);
		}
	}
}

t_closest_obj	get_closest_obj(t_mini_rt_data *data, t_ray ray)
{
	t_closest_obj	closest_obj;
	t_g_objects		*curr_obj;

	closest_obj.dist = FLT_MAX;
	closest_obj.obj = NULL;
	curr_obj = NULL;
	if (data)
		curr_obj = data->objs;
	while (curr_obj)
	{
		if (curr_obj->id == sp)
			intersect_sphere(curr_obj, ray, &closest_obj);
		else if (curr_obj->id == pl)
			intersect_plane(curr_obj, ray, &closest_obj);
		else if (curr_obj->id == cy)
			intersect_cylinder(curr_obj, ray, &closest_obj);
		curr_obj = curr_obj->next;
	}
	return (closest_obj);
}
