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

void		draw_mandel(t_fdf *fdf)
{
	t_frcl tmp;

	tmp.iter = fdf->cam.iter;
	tmp.camx = fdf->cam.x;
	tmp.camy = fdf->cam.y;
	tmp.camz = fdf->cam.z;
	tmp.winsx = fdf->p_win.sx;
	tmp.winsy = fdf->p_win.sy;
	tmp.color = fdf->color;
	gpu_calcul(tmp, fdf, MANDELDRAWER);
}
