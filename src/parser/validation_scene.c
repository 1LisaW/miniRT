/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:43:50 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/25 12:24:56 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	is_validate_extantion(char *str, char *extantion, t_mini_rt_data *data)
{
	int	idx_ext_start;
	int	ext_len;

	ext_len = ft_strlen(extantion);
	idx_ext_start = ft_strlen(str) - ext_len;
	if (idx_ext_start >= 0)
	{
		ext_len--;
		while (ext_len && str[idx_ext_start + ext_len] == extantion[ext_len])
			ext_len--;
		if (!ext_len)
			return (1);
	}
	handle_error(ERR_WRONG_FILE_EXT, NULL, data);
	data->err_code = ERR_WRONG_FILE_EXT;
	return (0);
}
