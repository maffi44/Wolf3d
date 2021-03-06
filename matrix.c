/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:09:24 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 05:34:07 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline t_matrix		matrix_mult(t_matrix a, t_matrix b)
{
	t_matrix	c;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			c.elem[i][j] = a.elem[i][0] * b.elem[0][j]
					+ a.elem[i][1] * b.elem[1][j]
					+ a.elem[i][2] * b.elem[2][j]
					+ a.elem[i][3] * b.elem[3][j];
			j++;
		}
		i++;
	}
	return (c);
}

t_vec3		make_vec(float x, float y, float z)
{
	t_vec3 vec;

	vec.elem[0] = x;
	vec.elem[1] = y;
	vec.elem[2] = z;
	vec.elem[3] = 1;
	return (vec);
}

inline t_vec3		vec3_transform(t_matrix matrix, t_vec3 vec)
{
	t_vec3	new_vec;
	int		i;

	i = 0;
	while (i < 4)
	{
		new_vec.elem[i] = vec.elem[0] * matrix.elem[i][0]
				+ vec.elem[1] * matrix.elem[i][1]
				+ vec.elem[2] * matrix.elem[i][2]
				+ vec.elem[3] * matrix.elem[i][3];
		i++;
	}
	return (new_vec);
}

inline t_vec3		vec_divide(t_vec3 from, t_vec3 to)
{
	t_vec3 res;
/*
	if (to.elem[3] != 1 || to.elem[3] != 0)
	{
		to.elem[0] = to.elem[0] / to.elem[3];
		to.elem[1] = to.elem[1] / to.elem[3];
		to.elem[2] = to.elem[2] / to.elem[3];
	}
	if (from.elem[3] != 1 || from.elem[3] != 0)
	{
		from.elem[0] = from.elem[0] / from.elem[3];
		from.elem[1] = from.elem[1] / from.elem[3];
		from.elem[2] = from.elem[2] / from.elem[3];
	}*/
	res.elem[0] = to.elem[0] - from.elem[0];
	res.elem[1] = to.elem[1] - from.elem[1];
	res.elem[2] = to.elem[2] - from.elem[2];
	res.elem[3] = 1;
	return (res);
}

inline float		vec_length(t_vec3 vec)
{
	vec.elem[3] = 1;
	return (sqrtf(vec.elem[0] * vec.elem[0]
	+ vec.elem[1] * vec.elem[1]
	+ vec.elem[2] * vec.elem[2]));
}

inline t_vec3		normalize_vec(t_vec3 vec)
{
	float len;
/*
	if (vec.elem[3] != 1 || vec.elem[3] != 0)
	{
		vec.elem[0] = vec.elem[0] / vec.elem[3];
		vec.elem[1] = vec.elem[1] / vec.elem[3];
		vec.elem[2] = vec.elem[2] / vec.elem[3];
	}*/
	len = vec_length(vec);
	vec.elem[0] = vec.elem[0] / len;
	vec.elem[1] = vec.elem[1] / len;
	vec.elem[2] = vec.elem[2] / len;
	vec.elem[3] = 1;
	return (vec);
}

t_matrix	make_matrix_x_rot(float a)
{
	t_matrix mat;

	mat.elem[0][0] = 1;
	mat.elem[0][1] = 0;
	mat.elem[0][2] = 0;
	mat.elem[0][3] = 0;
	mat.elem[1][0] = 0;
	mat.elem[1][1] = cosf(a);
	mat.elem[1][2] = -sinf(a);
	mat.elem[1][3] = 0;
	mat.elem[2][0] = 0;
	mat.elem[2][1] = sinf(a);
	mat.elem[2][2] = cosf(a);
	mat.elem[2][3] = 0;
	mat.elem[3][0] = 0;
	mat.elem[3][1] = 0;
	mat.elem[3][2] = 0;
	mat.elem[3][3] = 1;
	return (mat);
}

t_matrix	make_matrix_y_rot(float a)
{
	t_matrix mat;

	mat.elem[0][0] = cosf(a);
	mat.elem[0][1] = 0;
	mat.elem[0][2] = sinf(a);
	mat.elem[0][3] = 0;
	mat.elem[1][0] = 0;
	mat.elem[1][1] = 1;
	mat.elem[1][2] = 0;
	mat.elem[1][3] = 0;
	mat.elem[2][0] = -sinf(a);
	mat.elem[2][1] = 0;
	mat.elem[2][2] = cosf(a);
	mat.elem[2][3] = 0;
	mat.elem[3][0] = 0;
	mat.elem[3][1] = 0;
	mat.elem[3][2] = 0;
	mat.elem[3][3] = 1;
	return (mat);
}
