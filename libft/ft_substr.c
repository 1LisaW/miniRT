/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:28:52 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/25 11:29:09 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, int len)
{
	char	*sub;
	int		i;

	i = 0;
	sub = NULL;
	if (start >= (unsigned int)ft_strlen(s))
	{
		sub = malloc(sizeof(char));
		if (sub == NULL)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = malloc((len * sizeof(char)) + 1);
	if (sub == NULL)
		return (NULL);
	while (i < len && s[start] != '\0')
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
