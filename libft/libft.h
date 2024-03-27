/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:49:22 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/26 18:51:45 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_split_next
{
	size_t	start;
	size_t	length;
}	t_split_next;

int		ft_strlen(char *str);

int		ft_str_arr_len(char **str);

int		ft_isspace(int c);

char	*ft_reallocate(char *str, int i);

int		ft_strcmp(char *str1, char *str2);

float	ft_atof(char *str);

int		ft_issign(char c);

int		ft_isdigit(int c);

int		ft_atoi(const char *str);

char	*ft_substr(char *s, unsigned int start, int len);

void	*ft_free_all_split_alloc(char **split, size_t elts);

char	**ft_split(char *s, char c);

#endif
