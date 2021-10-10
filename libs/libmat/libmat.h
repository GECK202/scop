/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmat.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:18:46 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/21 06:25:53 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMAT_H
# define LIBMAT_H

# include <math.h>
# include <stdlib.h>

# define PI_VALUE 3.14159265359
# define MAT_IDENTITY 0x7FFFFFFF

typedef enum e_axis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
}	t_axis;

typedef struct s_v3
{
	float		v[3];
}	t_v3;

typedef struct s_v4
{
	float		v[4];
}	t_v4;

typedef struct s_m4
{
	float		m[16];
}	t_m4;

t_v3	new_v3(float x, float y, float z);
t_v4	new_v4(float x, float y, float z, float w);

t_m4	new_m4(float f);
t_m4	*m4_dup(t_m4 src);
t_m4	new_proj_m4(float fov, float apect_ratio, float near,
			float far);

t_m4	m4_mul(t_m4 m1, t_m4 m2);
t_m4	m4_rot(t_m4 m, float angle, t_axis axis);
t_m4	m4_scale(t_m4 m, float coeff);
t_m4	m4_transl(t_m4 m, t_v3 vec);

#endif
