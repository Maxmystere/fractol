/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:00:19 by magrab            #+#    #+#             */
/*   Updated: 2019/02/24 16:07:00 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
** 18 : 1 key
** 19 : 2 key
** 20 : 3 key
** 21 : 4 key
** 53 : esc key
** 50 : key under esc
** 69 : plus numpad
** 78 : minus numpad
** 84 : num 2
** 91 : num 8
** 123 : left key
** 124 : right key
** 125 : down key
** 126 = up key
*/

void	change_color(t_fdf *fdf, int key)
{
	if (key == 18)
		fdf->color = (fdf->color == 0x0F0000 ? 0xF00000 : 0x0F0000);
	else if (key == 19)
		fdf->color = (fdf->color == 0x000F00 ? 0x00F000 : 0x000F00);
	else if (key == 20)
		fdf->color = (fdf->color == 0x00000F ? 0x0000F0 : 0x00000F);
	else if (key == 21)
		fdf->color = (fdf->color == 0x332211 ? 0x203040 : 0x332211);
	else if (key == 22)
		fdf->color = (fdf->color == 0x225745 ? 0x102030 : 0x225745);
	else if (key == 23)
		fdf->color = (fdf->color == 0x488920 ? 0x204080 : 0x488920);
}

t_cam	move_iso(t_fdf *fdf, int key)
{
	if (key == 69 || key == -4)
	{
		fdf->cam.x += fdf->cam.z / fdf->mouse.x;
		fdf->cam.y += fdf->cam.z / fdf->mouse.y;
		fdf->cam.z += ZOOMSPEED + fdf->cam.z / 50;
	}
	else if ((key == 78 || key == -5) && 10 < fdf->cam.z - 1)
	{
		fdf->cam.x -= fdf->cam.z / fdf->mouse.x;
		fdf->cam.y -= fdf->cam.z / fdf->mouse.y;
		fdf->cam.z -= ZOOMSPEED + fdf->cam.z / 50;
	}
	else if (key == 84 && 0 < fdf->cam.iter - 1)
		fdf->cam.iter--;
	else if (key == 91)
		fdf->cam.iter++;
	else if (key == 123)
		fdf->cam.x -= CAMSPEED;
	else if (key == 124)
		fdf->cam.x += CAMSPEED;
	else if (key == 125)
		fdf->cam.y += CAMSPEED;
	else if (key == 126)
		fdf->cam.y -= CAMSPEED;
	return (fdf->cam);
}
