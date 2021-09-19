/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 21:31:48 by vkaron            #+#    #+#             */
/*   Updated: 2019/09/14 11:44:57 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *str;

	if (size + 1 <= 0)
		return (NULL);
	str = malloc((size));
	if (!str)
		return (NULL);
	ft_memset(str, 0, size);
	return (str);
}
