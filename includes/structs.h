/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:41:36 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/15 19:58:42 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_img_data
{
	int		**colors_data;
	float	vp_upper_left[3];
	int		is_guide;
	int		w_width;
	int		w_height;
	int		y_coord_nb;
	int		x_coord_nb;
	int		z;
	int		img_step;
}				t_img_data;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img_data	*img_data; // check users and remove
}				t_vars;

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
	enum e_obj_ids		id;
	float				*coords; // float [3]
	float				diam;
	float				*v_3d_normal;	//float[3]
	float				height;
	int					*rgb;	// int[3]
	struct s_g_objects	*next;
}				t_g_objects;

typedef struct s_mini_rt_data
{
	int				err_code;
	int				fd;
	t_ambient_light	*a_l;
	t_camera		*cam;
	t_light			*l;
	t_g_objects		*objs;
	t_img_data		*img_data;
}			t_mini_rt_data;
