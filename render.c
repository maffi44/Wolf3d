/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:55:37 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 06:29:02 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline t_vec3	seek_tri_center(t_vec3 vertex1, t_vec3 vertex2, t_vec3 vertex3)
{
	t_vec3 tri_center;

	tri_center.elem[0] = (vertex1.elem[0]
			+ vertex2.elem[0] + vertex3.elem[0]) / 3;
	tri_center.elem[1] = (vertex1.elem[1]
			+ vertex2.elem[1] + vertex3.elem[1]) / 3;
	tri_center.elem[2] = (vertex1.elem[2]
			+ vertex2.elem[2] + vertex3.elem[2]) / 3;
	tri_center.elem[3] = (vertex1.elem[3]
			+ vertex2.elem[3] + vertex3.elem[3]) / 3;
	return (tri_center);
}

inline t_sp_tri	make_tri_in_space(t_inst_obj obj, t_tri tri, float d)
{
	t_sp_tri	tr;
	t_vec3		tri_center;

	// //printf("%f\n", tr.vertex1.elem[3]);

	// //printf("%f\n", (tr.vertex1 = vec3_transform(
	// 		obj.transform,
	// 		obj.ref_obj->vertex[tri.pt[0]]))
	// 		.elem[2] / tr.vertex1.elem[3]);

	tr.bool = 1;
	if ((((tr.vertex1 = vec3_transform(
			obj.transform,
			obj.ref_obj->vertex[tri.pt[0]]))
			.elem[2] / tr.vertex1.elem[3]) < d) ||
			(((tr.vertex2 = vec3_transform(
					obj.transform,
					obj.ref_obj->vertex[tri.pt[1]]))
					.elem[2] / tr.vertex2.elem[3]) < d) ||
					(((tr.vertex3 = vec3_transform(
							obj.transform,
							obj.ref_obj->vertex[tri.pt[2]]))
							.elem[2] / tr.vertex3.elem[3]) < d))
		return (tr);

	tr.edge1 = vec_divide(tr.vertex1, tr.vertex2);
	tr.edge2 = vec_divide(tr.vertex1, tr.vertex3);
	tr.normal = vec_mult(tr.edge1, tr.edge2);
	tri_center = seek_tri_center(tr.vertex1, tr.vertex2, tr.vertex3);
	if (vec_scalar_mult(tr.normal, tri_center) <= 0)
		return (tr);

	tr.bool = 0;
	// tr.light_vector1 = normalize_vec(obj.ref_obj->normals[tri.pt[0]]);
	// tr.light_vector2 = normalize_vec(obj.ref_obj->normals[tri.pt[1]]);
	// tr.light_vector3 = normalize_vec(obj.ref_obj->normals[tri.pt[2]]);

	return (tr);
}

inline t_sc_tri	mk_sc_tri(t_sp_tri sp, t_data *data, t_inst_obj obj, t_tri tri)
{
	t_sc_tri sc;

	sp.light_vector1 = vec_divide(data->dir_light, sp.vertex1);
	sp.light_vector1 = normalize_vec(sp.light_vector1);
	sp.light_vector2 = vec_divide(data->dir_light, sp.vertex2);
	sp.light_vector2 = normalize_vec(sp.light_vector2);
	sp.light_vector3 = vec_divide(data->dir_light, sp.vertex3);
	sp.light_vector3 = normalize_vec(sp.light_vector3);
	sp.normal = normalize_vec(sp.normal);
	sc.pt1 = make_pt2_from_v3(sp.vertex1, data->d);
	sc.pt2 = make_pt2_from_v3(sp.vertex2, data->d);
	sc.pt3 = make_pt2_from_v3(sp.vertex3, data->d);
	sc.pt1.light = vec_scalar_mult(sp.normal, sp.light_vector1) * 0.95f;
	sc.pt2.light = vec_scalar_mult(sp.normal, sp.light_vector2) * 0.95f;
	sc.pt3.light = vec_scalar_mult(sp.normal, sp.light_vector3) * 0.95f;
	// sc.pt1.c.argb = obj.ref_obj->vertex[tri.pt[0]].color;
	// sc.pt2.c.argb = obj.ref_obj->vertex[tri.pt[1]].color;
	// sc.pt3.c.argb = obj.ref_obj->vertex[tri.pt[2]].color;
	sc.pt1.tex_coord[0] = (obj.ref_obj->tex_coords[tri.pt[0]]).coord[0] / sp.vertex1.elem[2];
	sc.pt1.tex_coord[1] = (obj.ref_obj->tex_coords[tri.pt[0]]).coord[1] / sp.vertex1.elem[2];
	sc.pt2.tex_coord[0] = (obj.ref_obj->tex_coords[tri.pt[1]]).coord[0] / sp.vertex2.elem[2];
	sc.pt2.tex_coord[1] = (obj.ref_obj->tex_coords[tri.pt[1]]).coord[1] / sp.vertex2.elem[2];
	sc.pt3.tex_coord[0] = (obj.ref_obj->tex_coords[tri.pt[2]]).coord[0] / sp.vertex3.elem[2];
	sc.pt3.tex_coord[1] = (obj.ref_obj->tex_coords[tri.pt[2]]).coord[1] / sp.vertex3.elem[2];

	// printf("%f  ", sc.pt1.tex_coord[0]);
	// printf("%f\n", sc.pt1.tex_coord[1]);
	return (sc);
}

void			draw_triangle(t_inst_obj obj, t_tri tri, t_data *data)
{
	t_sp_tri	space_tri;
	t_sc_tri	screen_tri;


	if ((space_tri = make_tri_in_space(obj, tri, data->camera.d)).bool)
		return ;

	screen_tri = mk_sc_tri(space_tri, data, obj, tri);
	draw_tri(screen_tri.pt1, screen_tri.pt2, screen_tri.pt3, data, obj.ref_obj->txtr);
}

t_matrix		make_cam_rot_matrix(float x_rot, float y_rot)
{
	t_matrix	mat;

	mat.elem[0][0] = cosf(y_rot);
	mat.elem[0][1] = 0;
	mat.elem[0][2] = sinf(y_rot);
	mat.elem[0][3] = 0;
	mat.elem[1][0] = (cosf(x_rot + y_rot) - cos(x_rot - y_rot)) / 2;
	mat.elem[1][1] = cosf(x_rot);
	mat.elem[1][2] = (-sinf(x_rot + y_rot) - sinf(x_rot - y_rot)) / 2;
	mat.elem[1][3] = 0;
	mat.elem[2][0] =(sinf(x_rot + y_rot) - sinf(x_rot - y_rot)) / 2;;
	mat.elem[2][1] = sinf(x_rot);
	mat.elem[2][2] = (cosf(x_rot + y_rot) + cos(x_rot - y_rot)) / 2;
	mat.elem[2][3] = 0;
	mat.elem[3][0] = 0;
	mat.elem[3][1] = 0;
	mat.elem[3][2] = 0;
	mat.elem[3][3] = 1;
	return (mat);
}

t_matrix		make_translation_matrix(t_matrix transltion, t_camera *camera, t_vec3 vector)
{
	vector = vec3_transform(make_rotation_matrix(-(camera->y_ang), -(camera->x_ang)), vector);
	transltion.elem[0][3] += vector.elem[0];
	transltion.elem[1][3] += vector.elem[1];
	transltion.elem[2][3] += vector.elem[2];
	return (transltion);
}

void            make_camera_transform(t_camera *camera, t_data *data)
{
	t_vec3 vector;
	t_matrix	x_rot;
	t_matrix	y_rot;

	if (data->W_bool == data->S_bool)
		vector.elem[2] = 0;
	else if (data->W_bool)
		vector.elem[2] = -0.5f;
	else
		vector.elem[2] = 0.5f;

	if (data->A_bool == data->D_bool)
		vector.elem[0] = 0;
	else if (data->A_bool)
		vector.elem[0] = 0.5f;
	else
		vector.elem[0] = -0.5f;
	
	x_rot = make_matrix_x_rot(camera->y_ang);
	y_rot = make_matrix_y_rot(camera->x_ang);

    camera->rotation = matrix_mult(x_rot, y_rot);
	camera->translation = make_translation_matrix(
	camera->translation, camera, vector);
    camera->transform = matrix_mult(camera->rotation, camera->translation);
}

void			print_matrix(t_matrix mat)
{
	//printf("%.2f   ", mat.elem[0][0]);
	//printf("%.2f   ", mat.elem[0][1]);
	//printf("%.2f   ", mat.elem[0][2]);
	//printf("%.2f   \n", mat.elem[0][3]);
	//printf("%.2f   ", mat.elem[1][0]);
	//printf("%.2f   ", mat.elem[1][1]);
	//printf("%.2f   ", mat.elem[1][2]);
	//printf("%.2f   \n", mat.elem[1][3]);
	//printf("%.2f   ", mat.elem[2][0]);
	//printf("%.2f   ", mat.elem[2][1]);
	//printf("%.2f   ", mat.elem[2][2]);
	//printf("%.2f   \n", mat.elem[2][3]);
	//printf("%.2f   ", mat.elem[3][0]);
	//printf("%.2f   ", mat.elem[3][1]);
	//printf("%.2f   ", mat.elem[3][2]);
	//printf("%.2f   \n", mat.elem[3][3]);
	//printf("\n");
}

inline t_matrix		make_transform_matrix(t_inst_obj obj, t_camera camera)
{
	t_matrix transform;

	// //printf("origin rotation matrix: \n");
	// //print_matrix(obj.rotation);
	// //printf("origin scale matrix: \n");
	// //print_matrix(obj.scale);
	// //printf("origin translation matrix: \n");
	// //print_matrix(obj.translate);
	// transform = matrix_mult(obj.rotation, obj.scale);
	// //printf("Transform matrix after Rot^scale: \n");
	// //print_matrix(transform);
	// transform = matrix_mult(transform, obj.translate);
	// //printf("Transform matrix after Rot^scale^translate: \n");
	// //print_matrix(transform);
	// //printf("origin camera translate matrix: \n");
	// //print_matrix(camera.translation);
	// transform = matrix_mult(transform, camera.translation);
	// //printf("Transform matrix after Rot^scale^translate^camTranslate: \n");
	// //print_matrix(transform);

	//printf("origin rotation matrix: \n");
	//print_matrix(obj.rotation);
	//printf("origin scale matrix: \n");
	//print_matrix(obj.scale);
	//printf("origin translation matrix: \n");
	//print_matrix(obj.translate);
	transform = matrix_mult(obj.rotation, obj.scale);
	//printf("Transform matrix after Rot^scale: \n");
	//print_matrix(transform);
	transform = matrix_mult(obj.translate, transform);
	//printf("Transform matrix after Rot^scale^translate: \n");
	//print_matrix(transform);
	//printf("origin camera translate matrix: \n");
	//print_matrix(camera.translation);
	transform = matrix_mult(camera.transform, transform);
	//printf("Transform matrix after Rot^scale^translate^camTranslate: \n");
	//print_matrix(transform);
	return (transform);
}

void			render_frame(t_inst_obj *objects, int num_of_obj, t_data *data)
{
	int i;
	int j;

	ft_bzero(data->img_data, WIDTH * HIEGHT * 4);
	ft_bzero(data->zbuff, sizeof(float) * WIDTH * HIEGHT);
	make_camera_transform(&(data->camera), data);
	i = 0;
	while (i < num_of_obj)
	{
		objects[i].transform = make_transform_matrix(objects[i], data->camera);
		j = -1;

		while (++j < objects[i].ref_obj->num_of_tris)
			draw_triangle(objects[i],
					objects[i].ref_obj->tri[j], data);
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}
