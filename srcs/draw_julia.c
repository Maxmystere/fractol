/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_julia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:46:57 by magrab            #+#    #+#             */
/*   Updated: 2019/03/04 19:46:59 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void				draw_julia(t_fdf *fdf)
{
	t_frcl tmp;

	tmp.iter = fdf->cam.iter;
	tmp.camx = fdf->cam.x;
	tmp.camy = fdf->cam.y;
	tmp.camz = fdf->cam.z;
	tmp.winsx = fdf->p_win.sx;
	tmp.winsy = fdf->p_win.sy;
	tmp.color = fdf->color;
	tmp.jx = fdf->cam.jx;
	tmp.jy = fdf->cam.jy;
	gpu_calcul(tmp, fdf, JULIADRAWER);
}
