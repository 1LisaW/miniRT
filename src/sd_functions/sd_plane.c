/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sd_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:57:16 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/04 20:28:57 by jmigoya-         ###   ########.fr       */
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
		printf("sd at point %f %f %f is: %f\n",current_point[0], current_point[1], current_point[2], signed_distance);
		if (fabs(signed_distance) < 0.01) // TODO: remove magic number
		{
			// recover color
			printf("Intersection detected at (%f, %f, %f)\n", current_point[0], current_point[1], current_point[2]);
			result = 1;
		}
		curr_obj = curr_obj->next;
	}
	return (result);
}

void	print_f_vec(float *vec)
{
	printf("x: %f, y: %f, z: %f", vec[0], vec[1], vec[2]);
}

// Traces one ray from camera_pos towards vp_coords (viewport coordinates)
// starting with magnitude equal to distance between them.
// TODO: modify to return color
void	trace_ray(t_mini_rt_data *data, float *vp_coords)
{
	float	magnitude;
	float	scaled_vector[3];
	float	curr_point[3];

	magnitude = get_vector_length(data->cam->coords, vp_coords);
	while (magnitude <= RAY_MAX_LENGHT)
	{
		printf("magnitude: %f\n", magnitude);
		scale_vector(vp_coords, magnitude, scaled_vector);
		vector_add(data->cam->coords, scaled_vector, curr_point);
		// iterate over all objects to find matches and manage colors
		if (apply_sdf_to_objects(data, curr_point))
			return ;
		magnitude += RAY_MAX_LENGHT / 100;
	}
	printf("ray reached max, no match\n");
	// no match found, return background color
}
