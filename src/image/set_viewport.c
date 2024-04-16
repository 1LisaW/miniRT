/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_viewport.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:48:25 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/16 13:29:42 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Calculates the legth of the side AC (see set_viewport), which corresponds
// to the distance from the camera to the center of the viewport.
float	get_dist_to_vp(t_mini_rt_data *data)
{
	float	half_width;
	float	half_fov;
	float	side_AC;
	float	side_AB;

	half_width = (float)data->img_data->w_width / 2.0;
	half_fov = (float)data->cam->fov / 2.0;
	printf("half fov rad: %f\n", (half_fov * (M_PI / 180.0)));
	printf("cos half fov: %f\n", cos(
		half_fov * (M_PI / 180.0)
		)
	);
	side_AC = half_width * (cos(half_fov * (M_PI / 180.0)));

	side_AB = sqrt(
		pow(half_width, 2) - pow(side_AC, 2)
	);
	printf("w_width: %d, fov: %d, side_AC: %f, side_AB: %f\n",
		data->img_data->w_width,
		data->cam->fov,
		side_AC,
		side_AB
	);
	return 0;
}

// Assuming a triangle ABC, where A is the camera, C the 90 degree angle formed
// at the intersction of the center of the viewport and the vector orientation
// of the camera and B the angle formed at the edge of the viewport at half its
// height, this function calculates the upper left coordinates of the viewport.
//                        B 
//                      --- 
//                 ---    │ 
//              ---       │ 
//           ---          │ <- half viewport 
//       ---              │ 
//    ---                 │ 
// A -────────────────────-C
void	set_viewport(t_mini_rt_data *data)
{
	float	vp_dist;
	float	vp_center[3];

	vp_dist = get_dist_to_vp(data);
	vp_center[0] = data->cam->coords[0] + (vp_dist * data->cam->v_3d_orient[0]);
	vp_center[1] = data->cam->coords[1] + (vp_dist * data->cam->v_3d_orient[1]);
	vp_center[2] = data->cam->coords[2] + (vp_dist * data->cam->v_3d_orient[2]);
	printf("vp_dist %f\n", vp_dist);
	printf("vp_center: %f %f %f\n", vp_center[0], vp_center[1], vp_center[2]);
	data->img_data->vp_upper_left[0] = vp_center[0]
		- (((float)data->img_data->w_width / 2));
	data->img_data->vp_upper_left[1] = vp_center[1]
		+ (((float)data->img_data->w_width / 2));
	data->img_data->vp_upper_left[2] = vp_center[2];
}
