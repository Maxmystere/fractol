/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ship.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:47:03 by magrab            #+#    #+#             */
/*   Updated: 2019/03/04 19:47:04 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void		draw_ship(t_fdf *fdf)
{
	t_frcl	tmp;
	char	draw[792];

	ft_strcpy(draw, "typedef struct s_frcl{double camx;double camy;double camz;\
double jx;double jy;int winsx;int winsy;int iter;int color;}t_frcl;\
__kernel void color(__global const t_frcl *in, __global unsigned int *out)\
{const uint index = get_global_id(0);const double x = index % in->winsx;\
const double y = index / in->winsx;\
const double pr = x / in->camz - (in->camx * 4.0 + in->winsx)/ (in->camz * 2);\
const double pi = y / in->camz - (in->camy * 4.0 + in->winsy)/ (in->camz * 2);\
double new_r;double new_i;double old_r;double old_i;int i;new_r = 0;new_i = 0;\
i = 0;while ((new_r * new_r + new_i * new_i) < 4.0 && i < in->iter){\
old_r = (new_r < 0 ? -new_r : new_r);old_i = (new_i < 0 ? -new_i : new_i);\
new_r = old_r * old_r - old_i * old_i + pr;\
new_i = 2.0 * old_r * old_i + pi;i++;}out[index] = i * in->color;}");
	tmp.iter = fdf->cam.iter;
	tmp.camx = fdf->cam.x;
	tmp.camy = fdf->cam.y;
	tmp.camz = fdf->cam.z;
	tmp.winsx = fdf->p_win.sx;
	tmp.winsy = fdf->p_win.sy;
	tmp.color = fdf->color;
	gpu_calcul(tmp, fdf, draw);
}
