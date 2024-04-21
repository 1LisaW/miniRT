/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_vector_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:19:16 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/21 23:12:14 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Add two vectors given their starting points and coordinates
// IMPORTANT: this function assumes common origin for inputed vectors
void	vector_add(float *vec_1, float *vec_2, float *result)
{
	result[0] = vec_1[0] + vec_2[0];
	result[1] = vec_1[1] + vec_2[1];
	result[2] = vec_1[2] + vec_2[2];
}

// Subtract two vectors
// IMPORTANT: this function assumes common origin for inputed vectors
void	vector_subtract(float *vec_1, float *vec_2, float *result)
{
	result[0] = vec_1[0] - vec_2[0];
	result[1] = vec_1[1] - vec_2[1];
	result[2] = vec_1[2] - vec_2[2];
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
float	get_dot_product(float *vector_1, float *vector_2)
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
