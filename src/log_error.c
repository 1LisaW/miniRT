/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:44:38 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/27 21:57:50 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	handle_error(int err_no, char *text, t_mini_rt_data *data)
{
	if (data->err_code)
		return ;
	printf("Error\n");
	if (err_no == ERR_WRONG_ARG)
		printf("%s %s", "⚠️   Programm requares exact one argument in a format",
			" <scene>.rt\n");
	else if (err_no == ERR_WRONG_FILE_EXT)
		printf("⚠️   Programm could accept scenes only in format <scene>.rt\n");
	else if (err_no == ERR_READ_FILE)
		printf("%s %s %s", "⛔   File", text, "can not be open\n");
	else if (err_no == ERR_PARSE_DATA)
		printf("%s %s %s", "⛔   ", text, "has incorrect data in file\n");
	else if (err_no == ERR_ALLOC_ERR)
		printf("⛔   Programm crashed because memory couldn't be allocated\n");
	data->err_code = err_no;
}
