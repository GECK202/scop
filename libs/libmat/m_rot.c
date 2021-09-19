/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_rot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:18:46 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/21 06:25:53 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

static t_m4	get_x_rot_m4(float theta)
{
	t_m4	mat;

	mat = new_m4(MAT_IDENTITY);
	mat.m[5] = cos(theta);
	mat.m[6] = -sin(theta);
	mat.m[9] = sin(theta);
	mat.m[10] = cos(theta);
	return (mat);
}

static t_m4	get_y_rot_m4(float theta)
{
	t_m4	mat;

	mat = new_m4(MAT_IDENTITY);
	mat.m[0] = cos(theta);
	mat.m[2] = sin(theta);
	mat.m[8] = -sin(theta);
	mat.m[10] = cos(theta);
	return (mat);
}

static t_m4	get_z_rot_m4(float theta)
{
	t_m4	mat;

	mat = new_m4(MAT_IDENTITY);
	mat.m[0] = cos(theta);
	mat.m[1] = -sin(theta);
	mat.m[4] = sin(theta);
	mat.m[5] = cos(theta);
	return (mat);
}

t_m4			m4_rot(t_m4 m, float angle, t_axis axis)
{
	t_m4	mat;

	if (axis == X_AXIS)
		mat = m4_mul(m, get_x_rot_m4(angle));
	else if (axis == Y_AXIS)
		mat = m4_mul(m, get_y_rot_m4(angle));
	else if (axis == Z_AXIS)
		mat = m4_mul(m, get_z_rot_m4(angle));
	else
		mat = m;
	return (mat);
}
