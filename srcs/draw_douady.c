/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 15:57:12 by magrab            #+#    #+#             */
/*   Updated: 2019/03/03 15:57:14 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void		draw_douady(t_fdf *fdf)
{
	t_frcl	tmp;
	char	draw[754];

	ft_strcpy(draw, "typedef struct s_frcl{double camx;double camy;\
double camz;double jx;double jy;int winsx;int winsy;int iter;int color;}t_frcl;\
__kernel void color(__global const t_frcl *in, __global unsigned int *out)\
{const uint index = get_global_id(0);const double x = index % in->winsx;\
const double y = index / in->winsx;\
const double pr = -0.123;const double pi = 0.74;double new_r;double new_i;\
double old_r;double old_i;int i;\
new_r = x / in->camz - (in->camx * 4.0 + in->winsx)/ (in->camz * 2);\
new_i = y / in->camz - (in->camy * 4.0 + in->winsy)/ (in->camz * 2);\
i = 0;while ((new_r * new_r + new_i * new_i) < 4.0 && i < in->iter){\
old_r = new_r;old_i = new_i;new_r = old_r * old_r - old_i * old_i + pr;\
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
