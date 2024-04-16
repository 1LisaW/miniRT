/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vector_length.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:44:28 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/16 15:50:58 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Returns the magnitude of a vector
float	get_vector_length(float *vec)
{
	float	sum;

	sum = (vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]);
	return (sqrt(sum));
}
