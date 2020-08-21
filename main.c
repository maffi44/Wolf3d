/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:28 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 06:29:24 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		mouse_release(int button, int x, int y, t_data *data)
{
	x = y;

	if (button == 2)
		((t_data *)data)->mouse_bool = 0;
	/*
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);

	if (button == 1)
		((t_data *)data)->mouse_bool = 0;

	*/
	return (0);
}

int		key_press(int key, t_data *data)
{
    if (key == 53)
        go_away(data);
    else if (key == 13)
        data->W_bool = 1;
    else if (key == 1)
        data->S_bool = 1;
    else if (key == 0)
        data->A_bool = 1;
    else if (key == 2)
        data->D_bool = 1;

    /*
	if (key == 53)
		go_away(data);
	else if (key == 15)
		data->r_bool = 1;
	else if (key == 12)
		data->q_bool = !(data->q_bool);
	else if (key == 4)
		data->h_bool = 1;
	else if (key == 3)
		data->f_bool = 1;
	else if (key == 24)
		data->disco++;
	else if (key == 27)
		if (data->disco > 1)
			data->disco--;
     */
    return (0);
}

int		mouse_move(int x, int y, t_data *data)
{
	if (!(data->mouse_bool))
	{
		data->camera.y_ang -= (float)(y - data->y) / 1000;
    	data->camera.x_ang += (float)(x - data->x) / 1000;
	}
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    render_frame(data->obj_inst, 1, data);
    ((t_data*)data)->x = x;
    ((t_data*)data)->y = y;
    /*
	if (((t_data*)data)->mouse_bool)
	{
		if (data->r_bool)
		{
			data->obj_inst->rotation = make_rotation_matrix(
					data->obj_inst->y_ang -= (float)(y - data->y) / 150,
					data->obj_inst->x_ang += (float)(x - data->x) / 150);
		}
		else
		{
			data->obj_inst->translate.elem[0][3] += (float)(x - data->x) / 50;
			data->obj_inst->translate.elem[1][3] += (float)(y - data->y) / 50;
		}
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		render_frame(data->obj_inst, 1, data);
		((t_data*)data)->x = x;
		((t_data*)data)->y = y;
	}*/
	return (0);
}

int		frame_loop(t_data *data)
{
	render_frame(data->obj_inst, 1, (void*)data);
	return (0);
}

t_matrix		make_translate_matrix()
{
    t_matrix translate;

    translate.elem[0][0] = 1;
    translate.elem[0][1] = 0;
    translate.elem[0][2] = 0;
    translate.elem[0][3] = 0;
    translate.elem[1][0] = 0;
    translate.elem[1][1] = 1;
    translate.elem[1][2] = 0;
    translate.elem[1][3] = 0;
    translate.elem[2][0] = 0;
    translate.elem[2][1] = 0;
    translate.elem[2][2] = 1;
    translate.elem[2][3] = 0;
    translate.elem[3][0] = 0;
    translate.elem[3][1] = 0;
    translate.elem[3][2] = 0;
    translate.elem[3][3] = 1;
    return (translate);
}

void	inicializate_data(t_data *data)
{
	if (!(data->mlx_ptr = mlx_init()))
		go_away(data);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HIEGHT, "FDF")))
		go_away(data);
	if (!(data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HIEGHT)))
		go_away(data);
	if (!(data->zbuff = (float*)ft_memalloc(sizeof(float) * WIDTH * HIEGHT)))
		go_away(data);
	bzero(data->zbuff, sizeof(float) * WIDTH * HIEGHT);
	data->camera.rotation = make_rotation_matrix(0, 0);
    data->camera.translation = make_translate_matrix();
	data->dir_light.elem[0] = 0;
	data->dir_light.elem[1] = 0;
	data->dir_light.elem[2] = 0;
	data->dir_light.elem[3] = 1;
	data->d = 1;
	data->mouse_bool = 0;
	data->r_bool = 0;
	data->f_bool = 0;
	data->h_bool = 0;
	data->disco = 1;
	data->img_data = mlx_get_data_addr(data->img_ptr, &(data->bpp),
			&(data->img_line), &(data->endian));
}

int		main(int argc, char **argv)
{
	t_data		*data;
	t_inst_obj	*insts;
	t_ref_obj	ref_objs;

	data = NULL;
	if (argc != 2)
		error(0, data, NULL);
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		go_away(data);
	inicializate_data(data);
	ref_objs = make_ref_obj(argv[1], data);
	insts = make_obj_inst(&ref_objs, 0.1f, 0.1f, 0.1f);
	data->obj_inst = insts;
	data->camera = initialize_camera(1);
	data->camera.rotation = make_rotation_matrix(0, 0);
    data->camera.translation = make_translate_matrix();
	((t_data*)data)->x = WIDTH / 2;
    ((t_data*)data)->y = HIEGHT / 2;
	mlx_hook(data->win_ptr, 2, 0, key_press, (void*)data);
	mlx_hook(data->win_ptr, 3, 0, key_release, (void*)data);
	mlx_hook(data->win_ptr, 4, 0, mouse_press, (void*)data);
	mlx_hook(data->win_ptr, 5, 0, mouse_release, (void*)data);
	mlx_hook(data->win_ptr, 6, 0, mouse_move, (void*)data);
//	render_frame(data->obj_inst, 1, (void*)data);
	mlx_loop_hook(data->mlx_ptr, frame_loop, data);
	mlx_hook(data->win_ptr, 17, 0, x_press, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
