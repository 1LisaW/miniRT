/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sd_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:57:16 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/02 19:12:02 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <stdlib.h>

// Returns distance from p to plane's surface
float	sd_plane(float *p, float *n, float h, float *camera_pos)
{
	float	adjusted_p[3];

	adjusted_p[0] = p[0] - camera_pos[0];
	adjusted_p[1] = p[1] - camera_pos[1];
	adjusted_p[2] = p[2] - camera_pos[2];
	return (get_dot_product(adjusted_p, n) + h);
}

// Traces one ray from camera_pos towards vp_coords (Viewport coordinates)
// starting with magnitude equal to distance between them.
void	trace_ray(t_mini_rt_data *data, float *vp_coords)
{
	float		current_point[3];
	float		*camera_pos;
	float		magnitude;
	t_g_objects	*curr_obj;
    float step_size = 0.1; // TODO: move to header?

	camera_pos = malloc(sizeof(float) * 3);
	copy_f_vector(data->cam->coords, camera_pos);
    vector_add(camera_pos, vp_coords, current_point);
	magnitude = get_vector_length(camera_pos, vp_coords); // magnitude start at distance to viewport
	curr_obj = data->objs;
	while (magnitude <= 100.0) //  TODO: remove magic number
	{
		float	signed_distance = sd_selector(current_point, data, *curr_obj);
		if (fabs(signed_distance) < 0.01) // TODO: remove magic number
		{
			// recover color
			printf("Intersection detected at (%f, %f, %f)\n", current_point[0], current_point[1], current_point[2]);
			printf("Corresponding with viewport coordinate (%f, %f)\n", vp_coords[0], vp_coords[1]);
		}
		curr_obj = curr_obj->next;
		if (curr_obj == NULL)
			break;
		// Update current point along the ray
		for (int j = 0; j < 3; ++j) {
			current_point[j] += vp_coords[j] * step_size;
		}
        magnitude += step_size;
	}
}

int main(void) {
	t_mini_rt_data	*data;
	t_g_objects		*objs;
	t_camera		*cam;

	data = malloc(sizeof(t_mini_rt_data));
	objs = malloc(sizeof(t_g_objects));
	cam = malloc(sizeof(t_camera));
	data->cam = cam;
	data->objs = objs;

	if (!data || !objs)
		return 1;
    // Camera position
	data->cam->coords = malloc(sizeof(float) * 3);
    float camera_pos[3] = {0.0, 0.0, 0.0};
	data->cam->coords[0] = 0.0;
	data->cam->coords[1] = 0.0;
	data->cam->coords[1] = 0.0;

    // Viewport coordinates (array of arrays)
	float viewport_coords[4][3] = {
    {1.0, 1.0, 2.0},  // Lower-left corner
    {1.0, 3.0, 2.0},  // Upper-left corner
    {3.0, 1.0, 2.0},  // Lower-right corner
    {3.0, 3.0, 2.0}   // Upper-right corner
	};
    int num_viewport_coords = sizeof(viewport_coords) / sizeof(viewport_coords[0]);

    // Plane parameters
    float plane_normal[3] = {0.0, 1.0, 0.0};  // Normal vector of the plane (y-axis)
    float plane_distance = 4.0;  // Distance from origin to the plane

    // Define step size
    float step_size = 0.1;

    // Iterate over viewport coordinates
    for (int i = 0; i < num_viewport_coords; ++i) {
        // Calculate direction vector
        float direction[3];
        vector_subtract(viewport_coords[i], camera_pos, direction);

        // Normalize the direction vector
        normalize_vector(camera_pos, direction);

        // Initialize magnitude and current point
        float magnitude = 0.0;
        float current_point[3];
        vector_add(camera_pos, viewport_coords[i], current_point);
		trace_ray(data, current_point);
	}

    return 0;
}

    //     // Iterate over steps
    //     while (magnitude <= 100.0) {  // Maximum distance to trace the ray
    //         // Calculate signed distance to the plane
    //         float signed_distance = sdf_plane(current_point, plane_normal, plane_distance, camera_pos);
				//
    //         // Check if point is on or near the plane
    //         if (fabs(signed_distance) < 0.01) {  // Adjust epsilon as needed
    //             // Point is on or close to the plane
    //             // Perform further processing, such as shading, lighting, etc.
    //             // Assign color to the corresponding pixel
    //             printf("Intersection detected at (%f, %f, %f)\n", current_point[0], current_point[1], current_point[2]);
				// printf("Corresponding with viewport coordinate (%f, %f)\n", viewport_coords[i][0], viewport_coords[i][1]);
    //             break;  // Exit the loop
    //         }
				//
    //         // Update current point along the ray
    //         for (int j = 0; j < 3; ++j) {
    //             current_point[j] += direction[j] * step_size;
    //         }
				//
    //         // Increment magnitude for the next step
    //         magnitude += step_size;
    //     }
    // }

// int main() {
// 		// Camera position
// 	float camera_pos[3] = {0.0, 0.0, 0.0}; // Example camera position
//
// 	// Test Case 1: Point is on the plane
// 	float p1[3] = {1.8, 1.3, 1.1};
// 	float n1[3] = {0.0, 1.0, 0.0}; // Plane with normal pointing upwards
// 	float h1 = 1.6; // Plane distance to origin
// 	float *origin1 = camera_pos; // Use camera position as origin
//
// 	float result1 = sdf_plane(p1, n1, h1, origin1);
// 	printf("Result for Test Case 1: %f\n", result1);
//
// 	// Test Case 2: Point is above the plane
// 	float p2[3] = {1.0, 2.0, 1.0};
// 	float n2[3] = {0.0, 1.0, 0.0}; // Plane with normal pointing upwards
// 	float h2 = 1.0; // Plane distance to origin
// 	float *origin2 = camera_pos; // Use camera position as origin
//
// 	float result2 = sdf_plane(p2, n2, h2, origin2);
// 	printf("Result for Test Case 2: %f\n", result2);
//
// 	// Test Case 3: Point is on the plane
// 	float p3[3] = {0.0, 0.0, 0.0};
// 	float n3[3] = {0.0, 1.0, 0.0}; // Plane with normal pointing upwards
// 	float h3 = 2.0; // Plane at origin
// 	float *origin3 = camera_pos; // Use camera position as origin
//
// 	float result3 = sdf_plane(p3, n3, h3, origin3);
// 	printf("Result for Test Case 3: %f\n", result3);
//     return 0;
// }
