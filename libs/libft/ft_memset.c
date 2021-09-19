/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 21:31:48 by vkaron            #+#    #+#             */
/*   Updated: 2019/09/14 11:44:57 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int n, size_t size)
{
	char *str;

	str = (char *)dest;
	while (size > 0)
	{
		str[size - 1] = (char)n;
		size--;
	}
	return (dest);
}
