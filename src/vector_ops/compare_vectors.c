/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_vectors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:42:53 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/18 13:45:51 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	vec_are_equal(float *vec_1, float *vec_2)
{
	if (
		vec_1[0] == vec_2[0]
		&& vec_1[1] == vec_2[1]
		&& vec_1[2] == vec_2[2]
	)
	{
		return (true);
	}
	return (false);
}
