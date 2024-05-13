/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vec_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:17:49 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/05/13 14:23:31 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Get length of vector
float	get_vector_length(float *vec)
{
	float	len;

	len = sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2));
	return (len);
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
