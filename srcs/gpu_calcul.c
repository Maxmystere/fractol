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

const char color_cl[] = "\
\
typedef struct  s_frcl{\
    double  camx;\
    double  camy;\
    double  camz;\
    int     winsx;\
    int     winsy;\
	int		iter;\
    int		color;\
}               t_frcl;\
\
__kernel void color(__global const t_frcl *in, __global unsigned int *out)\
{\
	const uint index = get_global_id(0);\
	const double x = index % in->winsx;\
	const double y = index / in->winsx;\
	const double pr = x / in->camz - (in->camx + in->winsx / 4)/ (in->camz * 2);\
	const double pi = y / in->camz - (in->camy + in->winsy / 4)/ (in->camz * 2);\
\
	double	new_r;\
	double	new_i;\
	double	old_r;\
	double	old_i;\
	int		i;\
\
	new_r = 0;\
	new_i = 0;\
	i = 0;\
	while ((new_r * new_r + new_i * new_i) < 4.0 && i < in->iter)\
	{\
		old_r = new_r;\
		old_i = new_i;\
		new_r = old_r * old_r - old_i * old_i + pr;\
		new_i = 2.0 * old_r * old_i + pi;\
		i++;\
	}\
	out[index] = i * in->color;\
}\
";

int		gpu_calcul(t_frcl param, void *mlx, void *win)
{
	t_gpu tcl;
	int bpp = 32;
	int s_l = 1000 * 4;
	int endian = 0;

	void *img = mlx_new_image(mlx, param.winsx, param.winsy);
	unsigned int *istr = (unsigned int *)mlx_get_data_addr(img, &(bpp), &(s_l), &(endian));

	// Setup GPU
	// Fetch the Platform and Device IDs; we only want one.
	tcl.err = clGetPlatformIDs(1, &tcl.ptm, &tcl.ptms);
	//ft_printf("Err clGetPlatformIDs? :\t\t%d\n", tcl.err);
	tcl.err = clGetDeviceIDs(tcl.ptm, CL_DEVICE_TYPE_ALL, 1, &tcl.dvc, &tcl.dvcs);
	//ft_printf("Err clGetDeviceIDs? :\t\t%d\n", tcl.err);
	cl_context_properties properties[] = {
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)tcl.ptm,
		0
	};
	// Note that nVidia's OpenCL requires the platform property
	cl_context context = clCreateContext(properties, 1, &tcl.dvc, NULL, NULL, &tcl.err);
	//ft_printf("Err clCreateContext? :\t\t%d\n", tcl.err);
	cl_command_queue cq = clCreateCommandQueue(context, tcl.dvc, 0, &tcl.err);
	//ft_printf("Err clCreateCommandQueue? :\t%d\n", tcl.err);

	const char *src = color_cl;
	size_t srcsize = strlen(src);

	// Submit the source code of the rot13 kernel to OpenCL
	cl_program prog = clCreateProgramWithSource(context, 1, &src, &srcsize, &tcl.err);
	//ft_printf("Err clCreateProgramWithSource? :%d\n", tcl.err);
	// and compile it (after this we could extract the compiled version)
	tcl.err = clBuildProgram(prog, 0, NULL, "", NULL, NULL);
	//ft_printf("Err clBuildProgram? :\t\t%d\n", tcl.err);

	// Allocate memory for the kernel to work with
	cl_mem mem1, mem2;
	// Worksize should be the size of your window (in pixel)
	size_t worksize = param.winsx * param.winsy;
	mem1 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(param), NULL, &tcl.err);
	//ft_printf("Err clCreateBuffer? :\t\t%d\n", tcl.err);
	mem2 = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, worksize, istr, &tcl.err);
	//ft_printf("Err clCreateBuffer? :\t\t%d\n", tcl.err);

	// get a handle and map parameters for the kernel
	cl_kernel k_color = clCreateKernel(prog, "color", &tcl.err);
	clSetKernelArg(k_color, 0, sizeof(mem1), &mem1);
	clSetKernelArg(k_color, 1, sizeof(mem2), &mem2);

	// Send input data to OpenCL (async, don't alter the buffer!)
	tcl.err = clEnqueueWriteBuffer(cq, mem1, CL_FALSE, 0, sizeof(param), &param, 0, NULL, NULL);
	//ft_printf("Err clEnqueueWriteBuffer? :\t%d\n", tcl.err);
	// Perform the operation
	tcl.err = clEnqueueNDRangeKernel(cq, k_color, 1, NULL, &worksize, NULL, 0, NULL, NULL);
	//ft_printf("Err clEnqueueNDRangeKernel? :\t%d\n", tcl.err);
	// Read the result back into buf2
	
	tcl.err = clEnqueueReadBuffer(cq, mem2, CL_FALSE, 0, worksize, istr, 0, NULL, NULL);
	//ft_printf("Err clEnqueueReadBuffer? :\t%d\n", tcl.err);
	// Await completion of all the above
	tcl.err = clFinish(cq);
	//ft_printf("Err clFinish? :\t\t\t%d\n", tcl.err);

	// End GPU

	mlx_put_image_to_window(istr, win, img, 0, 0);
	mlx_destroy_image(mlx, img);

	return (0);
}
