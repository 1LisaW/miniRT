/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_viewport.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:48:25 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/16 17:04:34 by jmigoya-         ###   ########.fr       */
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

	half_width = (float)data->img_data->w_width / 2.0;
	half_fov = (float)data->cam->fov / 2.0;
	side_AC = 400 / (sin(half_fov * (M_PI / 180.0)));
	return (side_AC);
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
	t_vp	*vp;
	float	vp_dist;
	float	displacement_vec[3];

	vp = &data->img_data->vp;
	vp->vp_up[0] = 0;
	vp->vp_up[1] = 1;
	vp->vp_up[2] = 0;
	vp_dist = get_dist_to_vp(data);
	scale_vector(data->cam->v_3d_orient, vp_dist, displacement_vec);
	vector_add(data->cam->coords, displacement_vec, vp->vp_center);
	vector_subtract(data->cam->coords, vp->vp_center, vp->vp_w);
	normalize_vector(vp->vp_w);
	get_cross_product(vp->vp_up, vp->vp_w, vp->vp_u);
	get_cross_product(vp->vp_w, vp->vp_u, vp->vp_v);
	scale_vector(vp->vp_u, ((float)data->img_data->w_width), vp->vp_horizontal_vec);
	scale_vector(vp->vp_u, -1 * ((float)data->img_data->w_height), vp->vp_vertical_vec);

	printf("displacement vector:\n");
	print_vector(displacement_vec);
	printf("vp center:\n");
	print_vector(vp->vp_center);
}
