/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vec_lenght.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:17:49 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/01 15:24:46 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Get length of vector given two components in type float coordinates[x, y, z]
// It can also be thinked as the distance between two points in 3D space
float	get_vector_length(float *position1, float *position2)
{
	float	x_diff;
	float	y_diff;
	float	z_diff;

	x_diff = position2[0] - position1[0];
	y_diff = position2[1] - position1[1];
	z_diff = position2[2] - position1[2];
	return (sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff));
}
//
// // TESTING FUNCTION
// void	print_vector_f(float *vector)
// {
// 	printf("(%f %f %f)", vector[0], vector[1], vector[2]);
// }
//
// // TESTING FUNCTION
// void	print_vector_i(int *vector)
// {
// 	printf("(%d %d %d)", vector[0], vector[1], vector[2]);
// }
//
// // int	main(void)
// {
// 	float origin[3] = {0, 0 ,0};
// 	float v_1[3] = {2, 2 ,-1};
// 	float v_2[3] = {5, -3 ,2};
// 	printf("TEST VECTOR OPERATIONS\n");
// 	printf("starting vectors: ");
// 	print_vector_f(v_1);
// 	printf(" ");
// 	print_vector_f(v_2);
// 	printf("\n");
// 	printf("addition:\n");
// 	float *result;
// 	vector_add(origin, v_1, v_2, result);
// 	print_vector_f(result);
// 	printf("\n");
// 	printf("substraction:\n");
// 	vector_subtract(origin, v_1, v_2, result);
// 	print_vector_f(result);
// 	printf("\n");
// 	printf("element-wise multiplication:\n");
// 	vector_multiply(origin, v_1, v_2, result);
// 	print_vector_f(result);
// 	printf("\n");
// 	printf("dot product multiplication:\n");
// 	vector_multiply(origin, v_1, v_2, result);
// 	printf("%f", dot_product(v_1, v_2));
// 	printf("\n");
// 	printf("division:\n");
// 	vector_divide(origin, v_1, v_2, result);
// 	print_vector_f(result);
// 	printf("\n");
// 	return (0);
// }
