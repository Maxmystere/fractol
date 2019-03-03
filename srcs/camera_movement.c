/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:00:19 by magrab            #+#    #+#             */
/*   Updated: 2019/02/24 16:07:00 by tferrieu         ###   ########.fr       */
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

t_cam	move_iso(t_fdf *fdf, int key)
{
	if (key == 69)
		fdf->cam.z += ZOOMSPEED;
	else if (key == 78)
		fdf->cam.z -= ZOOMSPEED;
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
