/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:53:56 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/23 11:09:59 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Applies SD function to all objects from current point. If match,
// returns 1
int	apply_sdf_to_objects(t_mini_rt_data *data, float *current_point)
{
	t_g_objects	*curr_obj;
	float		signed_distance;
	int			result;

	result = 0;
	curr_obj = data->objs;
	while (curr_obj)
	{
		signed_distance = sd_selector(current_point, data, *curr_obj);
		if (fabs(signed_distance) < 0.01) // TODO: remove magic number
		{
			// recover color
			printf("** Intersection detected at (%f, %f, %f) **\n", current_point[0], current_point[1], current_point[2]);
			result = 1;
		}
		curr_obj = curr_obj->next;
	}
	return (result);
}

// Traces one ray from camera_pos towards vp_coords (viewport coordinates)
// starting with magnitude equal to distance between them.
// TODO: modify to return color
// TODO remove magic numbers
void	trace_ray(t_mini_rt_data *data, float *vp_coords)
{
	float	magnitude;
	float	scaled_vector[3];

	copy_f_vector(vp_coords, scaled_vector);
	normalize_vector(scaled_vector);
	magnitude = 0;
	while (magnitude <= RAY_MAX_LENGHT)
	{
		if (apply_sdf_to_objects(data, scaled_vector))
			return ;
		magnitude += 0.5;
		scale_vector(vp_coords, magnitude, scaled_vector);
	}
}
