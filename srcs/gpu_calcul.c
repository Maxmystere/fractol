/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_calcul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 23:39:17 by magrab            #+#    #+#             */
/*   Updated: 2019/03/07 23:39:18 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

#define N NULL

static void	lil_gpu(t_fdf *fdf, const char *src, t_frcl param)
{
	cl_mem					mem1;
	cl_mem					mem2;
	size_t					worksize;
	size_t					srcsize;

	srcsize = ft_strlen(src);
	worksize = param.winsx * param.winsy;
	fdf->g.prog = clCreateProgramWithSource(fdf->g.c, 1, &src, &srcsize, N);
	clBuildProgram(fdf->g.prog, 0, N, N, N, N);
	mem1 = clCreateBuffer(fdf->g.c, CL_MEM_READ_ONLY, sizeof(param), N, N);
	mem2 = clCreateBuffer(fdf->g.c, CL_MEM_WRITE_ONLY, worksize * sizeof(int),
																		N, N);
	fdf->g.k_color = clCreateKernel(fdf->g.prog, "color", N);
	clSetKernelArg(fdf->g.k_color, 0, sizeof(mem1), &mem1);
	clSetKernelArg(fdf->g.k_color, 1, sizeof(mem2), &mem2);
	clEnqueueWriteBuffer(fdf->g.cq, mem1, 0, 0, sizeof(param), &param, 0, N, N);
	clEnqueueNDRangeKernel(fdf->g.cq, fdf->g.k_color, 1, N, &worksize, N, 0,
																		N, N);
	clEnqueueReadBuffer(fdf->g.cq, mem2, 0, 0, worksize * sizeof(int),
														fdf->istr, 0, N, N);
	clFinish(fdf->g.cq);
	clReleaseKernel(fdf->g.k_color);
	clReleaseMemObject(mem1);
	clReleaseMemObject(mem2);
}

int			gpu_calcul(t_frcl param, t_fdf *fdf, const char *src)
{
	lil_gpu(fdf, src, param);
	clReleaseProgram(fdf->g.prog);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->istr, fdf->win, fdf->img, 0, 0);
	return (0);
}
