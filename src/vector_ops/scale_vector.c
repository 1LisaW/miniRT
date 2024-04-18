/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:06:59 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/18 11:28:22 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Scale a vector by a scalar factor
void scale_vector(float *vector, float scalar, float *result)
{
	if ((int)vector[0] != 0)
		result[0] = vector[0] * scalar;
	if ((int)vector[1] != 0)
		result[1] = vector[1] * scalar;
	if ((int)vector[2] != 0)
		result[2] = vector[2] * scalar;
}
