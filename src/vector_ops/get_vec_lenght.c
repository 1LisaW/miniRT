/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vec_lenght.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:17:49 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/03/28 19:07:07 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Get length of vector given two components in type float coordinates[x, y, z]
float	vector_length(float *position1, float *position2)
{
	float	x_diff;
	float	y_diff;
	float	z_diff;

	x_diff = position2[0] - position1[0];
	y_diff = position2[1] - position1[1];
	z_diff = position2[2] - position1[2];
	return (sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff));
}

void	normalize_vector(float *origin, float *vector)
{
	float	length;

	length = vector_length(origin, vector);
	if (length != 0)
	{
		vector[0] = (vector[0] - origin[0]) / length;
		vector[1] = (vector[1] - origin[1]) / length;
		vector[2] = (vector[2] - origin[2]) / length;
		return ;
	}
	else
	{
		vector[0] = 0.0;
		vector[1] = 0.0;
		vector[2] = 0.0;
	}
}

// Add two vectors given their starting points and coordinates
// IMPORTANT: this function assumes common origin for inputed vectors
void	vector_add(float *origin, float *vector1, float *vector2,
	float *result)
{
	result[0] = (vector1[0] - origin[0]) + (vector2[0] - origin[0]);
	result[1] = (vector1[1] - origin[1]) + (vector2[1] - origin[1]);
	result[2] = (vector1[2] - origin[2]) + (vector2[2] - origin[2]);
}

// Subtract two vectors given their starting points and coordinates
void	vector_subtract(float *origin, float *vector1, float *vector2,
	float *result)
{
	result[0] = (vector1[0] - origin[0]) - (vector2[0] - origin[0]);
	result[1] = (vector1[1] - origin[1]) - (vector2[1] - origin[1]);
	result[2] = (vector1[2] - origin[2]) - (vector2[2] - origin[2]);
}

// Multiply two vectors given their starting points and coordinates
// IMPORTANT:
// - this function performs element-wise multiplication
// - this function assumes common origin for inputed vectors
void	vector_multiply(float *origin, float *vector1, float *vector2,
	float *result)
{
	result[0] = (vector1[0] - origin[0]) * (vector2[0] - origin[0]);
	result[1] = (vector1[1] - origin[1]) * (vector2[1] - origin[1]);
	result[2] = (vector1[2] - origin[2]) * (vector2[2] - origin[2]);
}

// Multiply to vectors and get the dot product
float	dot_product(float *vector_1, float *vector_2)
{
	return ((vector_1[0] * vector_2[0])
		+ (vector_1[1] * vector_2[1])
		+ (vector_1[2] * vector_2[2]));
}

// Divide two vectors element-wise given their starting points and coordinates
// IMPORTANT:
// - this function performs element-wise division
// - this function assumes common origin for inputed vectors
void	vector_divide(float *origin, float *vector1, float *vector2,
	float *result)
{
	result[0] = (vector1[0] - origin[0]) / (vector2[0] - origin[0]);
	result[1] = (vector1[1] - origin[1]) / (vector2[1] - origin[1]);
	result[2] = (vector1[2] - origin[2]) / (vector2[2] - origin[2]);
}

// TESTING FUNCTION
void	print_vector_f(float *vector)
{
	printf("(%f %f %f)", vector[0], vector[1], vector[2]);
}

// TESTING FUNCTION
void	print_vector_i(int *vector)
{
	printf("(%d %d %d)", vector[0], vector[1], vector[2]);
}

int	main(void)
{
	float origin[3] = {0, 0 ,0};
	float v_1[3] = {2, 2 ,-1};
	float v_2[3] = {5, -3 ,2};
	printf("TEST VECTOR OPERATIONS\n");
	printf("starting vectors: ");
	print_vector_f(v_1);
	printf(" ");
	print_vector_f(v_2);
	printf("\n");
	printf("addition:\n");
	float *result;
	vector_add(origin, v_1, v_2, result);
	print_vector_f(result);
	printf("\n");
	printf("substraction:\n");
	vector_subtract(origin, v_1, v_2, result);
	print_vector_f(result);
	printf("\n");
	printf("element-wise multiplication:\n");
	vector_multiply(origin, v_1, v_2, result);
	print_vector_f(result);
	printf("\n");
	printf("dot product multiplication:\n");
	vector_multiply(origin, v_1, v_2, result);
	printf("%f", dot_product(v_1, v_2));
	printf("\n");
	printf("division:\n");
	vector_divide(origin, v_1, v_2, result);
	print_vector_f(result);
	printf("\n");
	return (0);
}
