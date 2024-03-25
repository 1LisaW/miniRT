/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:49:49 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/25 13:16:28 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define ERR_WRONG_ARG 1
# define ERR_WRONG_FILE_EXT 2
# define ERR_READ_FILE 3
# define ERR_PARSE_DATA 4

# define AMBIENT_LIGHTNING_TOKEN "A"
# define CAMERA_TOKEN "C"
# define LIGHT_TOKEN "L"
# define SPHERE_TOKEN "sp"
# define PLANE_TOKEN "pl"
# define CYLINDER_TOKEN "cy"

# define SEPARATOR ","

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_ambient_light
{
	float	ratio;
	int		*rgb;	// int[3]
}				t_ambient_light;

typedef struct s_camera
{
	float	*coords; // float [3]
	float	*v_3d_orient;	//float[3]
	int		fov;
}				t_camera;

typedef struct s_light
{
	float	*coords; // float [3]
	float	l_brightness;
	int		*rgb;	// int[3]
}				t_light;

enum	e_obj_ids
{
	pl,
	sp,
	cy,
};

typedef struct s_g_objects
{
	enum e_obj_ids	id;
	float			*coords; // float [3]
	float			diam;
	float			*v_3d_mormal;	//float[3]
	float			height;
	int				*rgb;	// int[3]
}				t_g_objects;

typedef struct s_mini_rt_data
{
	int				err_code;
	int				fd;
	t_ambient_light	*a_l;
	t_camera		*cam;
	t_light			*l;
	t_g_objects		*objs;
}			t_mini_rt_data;

int		is_validate_extantion(char *str, char *extantion, t_mini_rt_data *data);

void	handle_error(int err_no, char *text, t_mini_rt_data *data);

void	init_mini_rt_data(t_mini_rt_data *data);

void	ft_read_file(t_mini_rt_data *data);

char	*ft_read_substr(t_mini_rt_data *data);

void	ft_parse_ambient_light(t_mini_rt_data *data);

#endif
