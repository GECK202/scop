/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:13:45 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/17 22:07:18 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

unsigned int	ft_strtoui(char *str)
{
	int				i;
	unsigned long	val;

	i = 0;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '-'))
		i++;
	val = strtoul(&(str[i]), NULL, 10);
	return ((unsigned int)val);
}

t_mats		*get_matrices(void)
{
	t_env	*env;

	if (!(env = get_env_struct(NULL)))
		return (NULL);
	return (env->mats);
}

t_env			*get_env_struct(t_env *env)
{
	static t_env	*save = NULL;

	if (env != NULL)
		save = env;
	return (save);
}
