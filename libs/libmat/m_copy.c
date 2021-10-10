/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_copy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:18:46 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/21 06:25:53 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"

t_m4	*m4_dup(t_m4 src)
{
	int		i;
	t_m4	*dst;

	i = -1;
	dst = (t_m4 *)malloc(sizeof(*dst));
	if (!dst)
		return (NULL);
	while (++i < 16)
		dst->m[i] = src.m[i];
	return (dst);
}
