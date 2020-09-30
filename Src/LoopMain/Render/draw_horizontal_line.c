/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 01:14:36 by mcamila           #+#    #+#             */
/*   Updated: 2020/02/22 06:30:43 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline void		initializate_ln(t_hln *ln, t_draw *s)
{
	ln->x = (s->x1);
	ln->h = (s->h1);
	ln->a = ((s->h2) - (s->h1)) / ((s->x2) - (s->x1));
	ln->z0 = (s->z1);
	ln->zb = ((s->z2 - (s->z1)) / ((s->x2) - (s->x1)));
	ln->tu1 = s->tu1;
	ln->tw1 = s->tw1;
	ln->tu_b = ((s->tu2 - (s->tu1)) / ((s->x2) - (s->x1)));
	ln->tw_b = ((s->tw2 - (s->tw1)) / ((s->x2) - (s->x1)));
	ln->txtr = s->txtr;

	// printf("tu1: %f   tu2: %f  tu_b: %f\n", s->tu1, s->tu2, ln->tu_b);
	// printf("tw1: %f   tw2: %f  tw_b: %f\n\n", s->tw1, s->tw2, ln->tw_b);

	// ln->col.argb = 0;
	// ln->c_r = s->col1.colors[2];
	// ln->c_g = s->col1.colors[1];
	// ln->c_b = s->col1.colors[0];
	// ln->cb_r = (float)(s->col2.colors[2] - s->col1.colors[2])
	// 		/ ((s->x2) - (s->x1));
	// ln->cb_g = (float)(s->col2.colors[1] - s->col1.colors[1])
	// 		/ ((s->x2) - (s->x1));
	// ln->cb_b = (float)(s->col2.colors[0] - s->col1.colors[0])
	// 		/ ((s->x2) - (s->x1));
}

inline void		draw_pixel(int y, t_data *data, t_hln *ln)
{
	t_color col;

	data->zbuff[((int)ln->x + (y * (WIDTH))) - 1] = ln->z0;
	// col.argb = (ln->txtr.data[
	// 	(int)(((ln->txtr.w * (ln->tu1 / ln->z0)) +
	// 	(ln->txtr.h * (ln->tw1 / ln->z0) *
	// 	ln->txtr.w)) - 1)]);
	
	col.argb = 0x00cccccc;
	// printf("print: tu1: %f   tw1: %f\n", ln->tu1, ln->tw1);
	// ln->col.colors[2] = (char)(ln->c_r * data->disco);
	// ln->col.colors[1] = (char)(ln->c_g * data->disco);
	// ln->col.colors[0] = (char)(ln->c_b * data->disco);
	col.colors[2] = (char)(col.colors[2] * ln->h);
	col.colors[1] = (char)(col.colors[1] * ln->h);
	col.colors[0] = (char)(col.colors[0] * ln->h);
	put_pixel((int)ln->x, y, col.argb, data);
}

void			draw_hor_line(t_draw s, int y, t_data *data)
{
	t_hln	ln;

	if ((s.x1) == (s.x2))
		return ;
	if ((s.x1) > (s.x2))
	{
		swap_f(&(s.x1), &(s.x2));
		swap_f(&(s.h1), &(s.h2));
		swap_f(&(s.z1), &(s.z2));
		swap_f(&(s.tu1), &(s.tu2));
		swap_f(&(s.tw1), &(s.tw2));
		//swap_colors(&s.col1, &s.col2);
	}
	initializate_ln(&ln, &s);
	while (ln.x <= (s.x2))
	{
		if ((ln.x >= 0 && (int)ln.x < WIDTH) && (y >= 0 && y < HIEGHT)
			&& (ln.z0 >= data->zbuff[((int)ln.x + (y * WIDTH)) - 1]))
			draw_pixel(y, data, &ln);
		// ln.c_r += ln.cb_r;
		// ln.c_g += ln.cb_g;
		// ln.c_b += ln.cb_b;

		//printf("%f   %f\n", ln.tu1, ln.tw1);

		ln.h += ln.a;
		ln.x++;
		ln.z0 += ln.zb;
		ln.tu1 += ln.tu_b;
		ln.tw1 += ln.tw_b;
	}
}
