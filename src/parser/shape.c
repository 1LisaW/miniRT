/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:32:08 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/27 15:00:27 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	push_to_data_obj(t_mini_rt_data *data, t_g_objects *obj)
{
	t_g_objects	*last_obj;

	last_obj = data->objs;
	while (last_obj && last_obj->next)
		last_obj = last_obj->next;
	if (last_obj)
		last_obj->next = obj;
	else
		data->objs = obj;
}

t_g_objects	*create_obj(t_mini_rt_data *data, char *token)
{
	t_g_objects	*new_obj;

	new_obj = malloc(sizeof(t_g_objects));
	if (!new_obj)
	{
		handle_error(ERR_ALLOC_ERR, NULL, data);
		return (NULL);
	}
	if (!ft_strcmp(token, PLANE_TOKEN))
		new_obj->id = pl;
	else if (!ft_strcmp(token, SPHERE_TOKEN))
		new_obj->id = sp;
	else if (!ft_strcmp(token, CYLINDER_TOKEN))
		new_obj->id = cy;
	new_obj->coords = NULL;
	new_obj->diam = 0;
	new_obj->height = 0;
	new_obj->rgb = NULL;
	new_obj->v_3d_normal = NULL;
	new_obj->next = 0;
	new_obj->mtxs = NULL;
	return (new_obj);
}

void	delete_obj(t_g_objects *obj)
{
	if (!obj)
		return ;
	if (obj->coords)
		free(obj->coords);
	if (obj->rgb)
		free(obj->rgb);
	if (obj->v_3d_normal)
		free(obj->v_3d_normal);
	if (obj->mtxs)
	{
		if (obj->mtxs->inv_mtx)
			free(obj->mtxs->inv_mtx);
		if (obj->mtxs->dir_mtx)
			free(obj->mtxs->dir_mtx);
		free(obj->mtxs);
	}
	obj->coords = NULL;
	obj->diam = 0;
	obj->height = 0;
	obj->rgb = NULL;
	obj->v_3d_normal = NULL;
	obj->next = NULL;
	free(obj);
	obj = NULL;
}

void	ft_free_4_str(char *str1, char *str2, char *str3,
			char *str4)
{
	if (str1)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2)
	{
		free(str2);
		str2 = NULL;
	}
	if (str3)
	{
		free(str3);
		str3 = NULL;
	}
	if (str4)
	{
		free(str4);
		str4 = NULL;
	}
}
