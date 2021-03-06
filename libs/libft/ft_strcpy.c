/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:10:49 by vkaron            #+#    #+#             */
/*   Updated: 2020/01/11 22:12:55 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, char *src)
{
	char	*tmp;

	tmp = dst;
	while (*src)
	{
		*tmp++ = *src++;
	}
	*tmp = 0;
	return (dst);
}
