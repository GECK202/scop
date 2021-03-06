/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:18:46 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/21 06:25:53 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_m4	m4_mul(t_m4 m1, t_m4 m2)
{
	int		x;
	int		y;
	int		z;
	t_m4	mat;

	x = -1;
	while (++x < 4)
	{
		y = -1;
		while (++y < 4)
		{
			mat.m[x * 4 + y] = 0;
			z = -1;
			while (++z < 4)
				mat.m[x * 4 + y] += m1.m[x * 4 + z] * m2.m[z * 4 + y];
		}
	}
	return (mat);
}
