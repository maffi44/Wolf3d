/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:17:48 by mcamila           #+#    #+#             */
/*   Updated: 2020/08/22 19:00:37 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "header.h"
# include "matrix.h"

typedef	struct	s_texture
{
	void	*img;
	int		*data;
	int		w;
	int		h;
}				t_texture;

typedef struct	s_pt2
{
	float		x;
	float		y;
	float		z1;
	t_color		c;
	float		light;
	float		tex_coord[2];
}				t_pt2;

typedef struct	s_tri
{
	int	pt[3];
}				t_tri;

typedef	struct	s_normal
{
	t_vec3		nor[3];
}				t_normal;

typedef struct s_tex_coord
{
    float      coord[2];
}              t_tex_coord;

typedef struct	s_ref_obj
{
	t_vec3		*vertex;
	t_tri		*tri;
	t_vec3      *normals;
	t_tex_coord *tex_coords;
	int			num_of_pts;
	int			num_of_tris;
	int			num_of_tex_c;
	int			num_of_normals;
	t_texture   txtr;

}				t_ref_obj;

typedef struct	s_inst_obj
{
	t_ref_obj	*ref_obj;
	t_matrix	scale;
	t_matrix	rotation;
	t_matrix	translate;
	t_matrix	transform;
	float		x_ang;
	float		y_ang;
}				t_inst_obj;

typedef struct	s_camera
{
	t_matrix	transform;
	t_matrix	rotation;
	t_matrix	translation;
	t_matrix	projection;
	t_vec3		translate_vec;
    float		x_ang;
    float		y_ang;
	float		d;
}				t_camera;

typedef struct	s_maps
{
	char		**line;
	char		*big_line;
	char		*temp;
	char		***big_map;
	int			**map;
}				t_maps;

typedef struct	s_screen_tri
{
	t_pt2		pt1;
	t_pt2		pt2;
	t_pt2		pt3;
}				t_sc_tri;

typedef struct	s_space_tri
{
	t_vec3		normal;
	t_vec3		vertex1;
	t_vec3		vertex2;
	t_vec3		vertex3;
	t_vec3		light_vector1;
	t_vec3		light_vector2;
	t_vec3		light_vector3;
	t_vec3		edge1;
	t_vec3		edge2;
	char		bool;
}				t_sp_tri;

typedef struct	s_draw
{
	float		a1;
	float		a2;
	float		x1;
	float		x2;
	float		h1;
	float		h2;
	float		b1;
	float		b2;
	float		z1;
	float		z2;
	float		zb1;
	float		zb2;
	// float		c_r1;
	// float		c_g1;
	// float		c_b1;
	// float		c_r2;
	// float		c_g2;
	// float		c_b2;
	// float		cb_r1;
	// float		cb_g1;
	// float		cb_b1;
	// float		cb_r2;
	// float		cb_g2;
	// float		cb_b2;
	float		tu1;
	float		tu2;
	float		tw1;
	float		tw2;
	float		tu_b1;
	float		tu_b2;
	float		tw_b1;
	float		tw_b2;
	t_color		col1;
	t_color		col2;
	t_texture	txtr;
}				t_draw;

typedef struct	s_hln
{
	float		x;
	float		h;
	float		a;
	float		z0;
	float		zb;

	float		c_r;
	float		c_g;
	float		c_b;
	float		cb_r;
	float		cb_g;
	float		cb_b;

	float		tu1;
	float		tu2;
	float		tu_b;
	float		tw1;
	float		tw2;
	float		tw_b;
	t_color		col;
	t_texture	txtr;
}				t_hln;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	void		*img_data;
	float		*zbuff;
	int			img_line;
	int			bpp;
	int			endian;
	t_inst_obj	*obj_inst;
	int			num_of_inst_objects;
	float		d;
	t_camera	camera;
	t_vec3		dir_light;
	int			x;
	int			y;
	int			r_bool;
	int			mouse_bool;
	int			q_bool;
	int			h_bool;
	int			f_bool;
	int			disco;
	int			W_bool;
	int			S_bool;
	int			A_bool;
	int			D_bool;
	t_texture 	*txtre;
	int			nbr_txtres;
}				t_data;

#endif
