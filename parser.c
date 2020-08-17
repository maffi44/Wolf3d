/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 20:51:07 by majosue           #+#    #+#             */
/*   Updated: 2020/08/17 15:30:57 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "header.h"
#include "functions.h"
#include "structs.h"

/*
**	Return size of array, that ends with NULL
*/

int		ft_array_len(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/*
**	Free ft_strsplit created array
*/

void	ft_clean_array(char ***array)
{
	char **tmp;

	if (*array)
	{
		tmp = *array;
		while (**array)
		{
			free(**array);
			(*array)++;
		}
		free(tmp);
	}
}

/*
**	String to float
*/

double	ft_atof(char s[])
{
	int i;
	int sign;
	double n;
	double power;

	sign = 1;
	i = 0;
	n = 0.0;
	power = 1.0;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == '\v' || s[i] == '\f' ||
		   s[i] == '\r' || s[i] == ' ')
		i++;
	sign = (s[i] == '+' || s[i] == '-') ? 44 - s[i++] : 1;
	while (ft_isdigit(s[i]))
		n = n * 10.0 + s[i++] - '0';
	i += s[i] == '.' ? 1 : 0;
	while (ft_isdigit(s[i]))
	{
		n = n * 10.0 + s[i++] - '0';
		power *= 10.0;
	}
	return sign * n / power;
}

/*
**	Exit with error message
*/

void	ft_exit(char *str, char *str2)
{
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(str2, 2);
		exit(EXIT_FAILURE);
	}
	perror(NULL);
	exit(EXIT_FAILURE);
}

/*
**	Check args for files.obj and file.map
*/

void	ft_check_args(int argc, char *argv[])
{
	int i;
	int is_obj;
	int is_map;

	is_obj = 0;
	is_map = 0;
	i = 0;
	while (++i < argc)
	{
		is_obj += ft_strstr(argv[i], ".obj") &&
						  ft_strlen(ft_strstr(argv[i], ".obj")) == 4
					  ? 1
					  : 0;
		is_map += ft_strstr(argv[i], ".map") &&
						  ft_strlen(ft_strstr(argv[i], ".map")) == 4
					  ? 1
					  : 0;
	}
	if (!is_obj || !is_map || is_map != 1 || is_map + is_obj != argc - 1 ||
		!ft_strstr(argv[argc - 1], ".map"))
		ft_exit("usage: ./wolf3d file.obj [file2.obj] [...] file.map", "");
}

/*
**	Allocate memory 1 size bigger
**	than old_mem has
**	copy from old_mem to new
*/

void	*ft_grow_array(void *old_mem, int n, size_t size)
{
	void *new_mem;

	if (n <= 0)
		return NULL;
	if (!(new_mem = ft_memalloc(n * size)))
		ft_exit(NULL, NULL);
	if (n == 1)
		return (new_mem);
	ft_memmove(new_mem, old_mem, (n - 1) * size);
	free(old_mem);
	//ft_memdel(old_mem); //не работает
	return (new_mem);
}

/*
**	Read vertexes lines 
*/

void	ft_read_v(t_ref_obj *obj, char *line)
{
	int len;
	char **array;
	t_vec3 vertex;

	if (!(array = ft_strsplit(line + 2, ' ')))
		ft_exit(NULL, NULL);
	len = ft_array_len(array);
	if (len < 3 || len > 4)
		ft_exit("Error vertex line: ", line);
	vertex.elem[0] = ft_atof(array[0]);
	vertex.elem[1] = ft_atof(array[1]);
	vertex.elem[2] = ft_atof(array[2]);
	vertex.elem[3] = 1;
	vertex.color = 55;
	obj->num_of_pts++;
	obj->vertex = (t_vec3 *)ft_grow_array(obj->vertex, obj->num_of_pts, sizeof(vertex));
	ft_memmove((void *)&(obj->vertex[obj->num_of_pts - 1]), &vertex, sizeof(vertex));
	ft_clean_array(&array);
}

void	ft_read_vt(t_ref_obj *obj, char *line)
{
	int len;
	char **array;
	t_tex_coord tex;

	if (!(array = ft_strsplit(line + 2, ' ')))
		ft_exit(NULL, NULL);
	len = ft_array_len(array);
	if (len < 2 || len > 3)
		ft_exit("Error tex cor line: ", line);
	tex.coord[0] = ft_atof(array[0]);
	tex.coord[1] = ft_atof(array[1]);
	obj->num_of_tex_c++;
	obj->tex_coords = (t_tex_coord *)ft_grow_array(obj->tex_coords, obj->num_of_tex_c, sizeof(tex));
	ft_memmove((void *)&(obj->tex_coords[obj->num_of_tex_c - 1]), &tex, sizeof(tex));
	ft_clean_array(&array);
}

void	ft_read_vn(t_ref_obj *obj, char *line)
{
	int len;
	char **array;
	t_vec3 normal;

	if (!(array = ft_strsplit(line + 2, ' ')))
		ft_exit(NULL, NULL);
	len = ft_array_len(array);
	if (len < 3 || len > 4)
		ft_exit("Error normal line: ", line);
	normal.elem[0] = ft_atof(array[0]);
	normal.elem[1] = ft_atof(array[1]);
	normal.elem[2] = ft_atof(array[2]);
	normal.elem[3] = 1;
	obj->num_of_normals++;
	obj->normals = (t_vec3 *)ft_grow_array(obj->normals, obj->num_of_normals, sizeof(normal));
	ft_memmove((void *)&(obj->normals[obj->num_of_normals - 1]), &normal, sizeof(normal));
	ft_clean_array(&array);
}

/*
**	Read faces (index in obj begin from 1)
*/

void	ft_read_f(t_ref_obj *obj, char *line)
{
	int len;
	char **array;
	t_tri tri;

	if (!(array = ft_strsplit(line + 2, ' ')))
		ft_exit(NULL, NULL);
	len = ft_array_len(array);
	if (len < 3)
		ft_exit("Error f line: ", line);
	if ((tri.pt[0] = ft_atoi(array[0]) - 1) >= obj->num_of_pts ||
		(tri.pt[1] = ft_atoi(array[1]) - 1) >= obj->num_of_pts ||
		(tri.pt[2] = ft_atoi(array[2]) - 1) >= obj->num_of_pts)
		ft_exit("Error in face def line", "");
	obj->num_of_tris++;
	obj->tri = (t_tri *)ft_grow_array(obj->tri, obj->num_of_tris, sizeof(tri));
	ft_memmove((void *)&(obj->tri[obj->num_of_tris - 1]), &tri, sizeof(tri));
	ft_clean_array(&array);
}

void	ft_load_obj(t_ref_obj *obj, int fd)
{

	char *line;
	int error;

	obj->num_of_pts = 0;
	obj->num_of_normals = 0;
	obj->num_of_tex_c = 0;
	obj->num_of_tris = 0;
	obj->vertex = NULL;
	while ((error = get_next_line(fd, &line)) > 0)
	{
		if (ft_strnstr(line, "v ", 2))
			ft_read_v(obj, line);
		if (ft_strnstr(line, "vt ", 3))
			ft_read_vt(obj, line);
		if (ft_strnstr(line, "vn ", 3))
			ft_read_vn(obj, line);
		if (ft_strnstr(line, "f ", 2))
			ft_read_f(obj, line);
		ft_strdel(&line);
	}
}

t_ref_obj	*ft_read_files(int argc, char *argv[])
{
	int fd;
	int i;
	t_ref_obj *objs;

	ft_check_args(argc, argv);
	i = 0;
	if (!(objs = malloc(sizeof(*objs) * argc - 2)))
		ft_exit(NULL, NULL);
	while (++i < argc - 1) // не читаем последний аргумент карту
	{
		if ((fd = open(argv[i], O_RDONLY)) < 0)
			ft_exit(NULL, NULL);
		ft_load_obj(&(objs[i - 1]), fd);
		close(fd);
	}
	// тут прочтем карту надо придумать формат
	/*  if ((fd = open(argv[argc - 1], O_RDONLY)) < 0)
            ft_exit(NULL, NULL);
        ft_load_map();
        close(fd);  */
	return (objs);
}