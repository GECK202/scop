/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_v.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:18:46 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/21 06:25:53 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_v3		new_v3(float x, float y, float z)
{
	t_v3	vec;

	vec.v[0] = x;
	vec.v[1] = y;
	vec.v[2] = z;
	return (vec);
}

t_v4		new_v4(float x, float y, float z, float w)
{
	t_v4	vec;

	vec.v[0] = x;
	vec.v[1] = y;
	vec.v[2] = z;
	vec.v[3] = w;
	return (vec);
}
