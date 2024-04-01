/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDF_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:57:16 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/01 19:26:58 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Adjust point 'p' relative to the ray's camera_pos
// Calculate dot product of adjustedP and normal vector 'n' plus distance 'h'
float	sdf_plane(float *p, float *n, float h, float *camera_pos)
{
	float	adjusted_p[3];

	adjusted_p[0] = p[0] - camera_pos[0];
	adjusted_p[1] = p[1] - camera_pos[1];
	adjusted_p[2] = p[2] - camera_pos[2];
	return (get_dot_product(adjusted_p, n) + h);
}

int main() {
    // Camera position
    float camera_pos[3] = {1.0, 2.0, 1.0};
    // Viewport coordinates (array of arrays)
	float viewport_coords[4][3] = {
    {1.0, 1.0, 2.0},  // Lower-left corner
    {1.0, 3.0, 2.0},  // Upper-left corner
    {3.0, 1.0, 2.0},  // Lower-right corner
    {3.0, 3.0, 2.0}   // Upper-right corner
	};
    int num_viewport_coords = sizeof(viewport_coords) / sizeof(viewport_coords[0]);

    // Plane parameters
    float plane_normal[3] = {1.0, 0.0, 1.0};  // Normal vector of the plane (y-axis)
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

        // Iterate over steps
        while (magnitude <= 100.0) {  // Maximum distance to trace the ray
            // Calculate signed distance to the plane
            float signed_distance = sdf_plane(current_point, plane_normal, plane_distance, camera_pos);

            // Check if point is on or near the plane
            if (fabs(signed_distance) < 0.01) {  // Adjust epsilon as needed
                // Point is on or close to the plane
                // Perform further processing, such as shading, lighting, etc.
                // Assign color to the corresponding pixel
                printf("Intersection detected at (%f, %f, %f)\n", current_point[0], current_point[1], current_point[2]);
				printf("Corresponding with viewport coordinate (%f, %f)\n", viewport_coords[i][0], viewport_coords[i][1]);
                break;  // Exit the loop
            }

            // Update current point along the ray
            for (int j = 0; j < 3; ++j) {
                current_point[j] += direction[j] * step_size;
            }

            // Increment magnitude for the next step
            magnitude += step_size;
        }
    }

    return 0;
}

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
