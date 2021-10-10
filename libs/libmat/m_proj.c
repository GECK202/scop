/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_proj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:18:46 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/21 06:25:53 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_m4	new_proj_m4(float fov, float aspect_ratio, float near, float far)
{
	t_m4			mat;
	static float	deg_to_rad = PI_VALUE / 180;
	float			x_scale;
	float			y_scale;

	mat = new_m4(0);
	y_scale = 1.0 / tan(deg_to_rad * fov / 2);
	x_scale = y_scale / aspect_ratio;
	mat.m[0] = x_scale;
	mat.m[5] = y_scale;
	mat.m[10] = (far + near) / (near - far);
	mat.m[11] = -1;
	mat.m[14] = 2 * far * near / (near - far);
	return (mat);
}
