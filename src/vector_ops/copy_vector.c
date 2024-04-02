/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:56:16 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/02 19:10:09 by jmigoya-         ###   ########.fr       */
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
