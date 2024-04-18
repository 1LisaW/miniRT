/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_vector_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:19:16 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/18 13:41:08 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Add two vectors given their starting points and coordinates
void vector_add(float *vec_1, float *vec_2, float *result)
{
    result[0] = vec_1[0] + vec_2[0];
    result[1] = vec_1[1] + vec_2[1];
    result[2] = vec_1[2] + vec_2[2];
}

// Subtract two vectors
void vector_subtract(float *vec_1, float *vec_2, float *result)
{
		result[0] = vec_1[0] - vec_2[0];
		result[1] = vec_1[1] - vec_2[1];
		result[2] = vec_1[2] - vec_2[2];
}

// Multiply two vectors given their starting points and coordinates
// IMPORTANT:
// - this function performs element-wise multiplication
void	vector_multiply(float *vec_1, float *vec_2,	float *result)
{
	result[0] = (vec_1[0]) * (vec_2[0]);
	result[1] = (vec_1[1]) * (vec_2[1]);
	result[2] = (vec_1[2]) * (vec_2[2]);
}

void	get_cross_product(float *vec_1, float *vec_2, float *cross_P)
{
    cross_P[0] = vec_1[1] * vec_2[2] - vec_1[2] * vec_2[1];
    cross_P[1] = vec_1[2] * vec_2[0] - vec_1[0] * vec_2[2];
    cross_P[2] = vec_1[0] * vec_2[1] - vec_1[1] * vec_2[0];
}

// Multiply to vectors and get the dot product
float	get_dot_product(float *vec_1, float *vec_2)
{
	return ((vec_1[0] * vec_2[0])
		+ (vec_1[1] * vec_2[1])
		+ (vec_1[2] * vec_2[2]));
}

// Divides a vector
// IMPORTANT:
// - this function performs element-wise division
void	vector_divide(float *vec_1, float divider, float *result)
{
	if (vec_1[0] != 0)
		result[0] = (vec_1[0]) / divider;
	if (vec_1[1] != 0)
		result[1] = (vec_1[1]) / divider;
	if (vec_1[2] != 0)
		result[2] = (vec_1[2]) / divider;
}
