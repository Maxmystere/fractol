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

static void	lil_gpu(t_fdf *fdf, const char *src, t_gpu tcl, t_frcl param)
{
	cl_mem					mem1;
	cl_mem					mem2;
	size_t					worksize;
	cl_command_queue		cq;
	cl_context				context;

	tcl.properties[0] = CL_CONTEXT_PLATFORM;
	tcl.properties[1] = (cl_context_properties)tcl.ptm;
	tcl.properties[2] = 0;
	context = clCreateContext(tcl.properties, 1, &tcl.dvc, N, N, N);
	cq = clCreateCommandQueue(context, tcl.dvc, 0, N);
	tcl.srcsize = ft_strlen(src);
	worksize = param.winsx * param.winsy;
	tcl.prog = clCreateProgramWithSource(context, 1, &src, &(tcl.srcsize), N);
	clBuildProgram(tcl.prog, 0, N, "", N, N);
	mem1 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(param), N, N);
	mem2 = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, worksize, fdf->istr, N);
	tcl.k_color = clCreateKernel(tcl.prog, "color", N);
	clSetKernelArg(tcl.k_color, 0, sizeof(mem1), &mem1);
	clSetKernelArg(tcl.k_color, 1, sizeof(mem2), &mem2);
	clEnqueueWriteBuffer(cq, mem1, CL_FALSE, 0, sizeof(param), &param, 0, N, N);
	clEnqueueNDRangeKernel(cq, tcl.k_color, 1, N, &worksize, N, 0, N, N);
	clEnqueueReadBuffer(cq, mem2, CL_FALSE, 0, worksize, fdf->istr, 0, N, N);
	clFinish(cq);
}

int			gpu_calcul(t_frcl param, t_fdf *fdf, const char *src)
{
	t_gpu	tcl;

	clGetPlatformIDs(1, &tcl.ptm, &tcl.ptms);
	clGetDeviceIDs(tcl.ptm, CL_DEVICE_TYPE_ALL, 1, &tcl.dvc, &tcl.dvcs);
	lil_gpu(fdf, src, tcl, param);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->istr, fdf->win, fdf->img, 0, 0);
	return (0);
}
