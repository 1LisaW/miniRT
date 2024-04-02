/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:56:16 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/02 15:01:28 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Copies float vector.
// WARNING: assumes both src and dest are size 3
void	copy_f_vector(float *src, float *dest)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		dest[i] = src[i];
		i++;
	}
}
