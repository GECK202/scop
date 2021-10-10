/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:13:45 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/17 22:07:18 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	get_min_max(t_v3 **v_array, unsigned int nb_vtx,
float *min_max, unsigned int i)
{
	unsigned int	j;

	j = 0;
	min_max[0] = v_array[0]->v[i];
	min_max[1] = v_array[0]->v[i];
	while (j < nb_vtx)
	{
		if (v_array[j]->v[i] < min_max[0])
			min_max[0] = v_array[j]->v[i];
		else if (v_array[j]->v[i] > min_max[1])
			min_max[1] = v_array[j]->v[i];
		j++;
	}
}

static void	set_interval_and_center_point(float *min_max,
float *center_point, float *max_interval)
{
	float	interval;

	if (min_max[0] <= 0.0f && min_max[1] <= 0.0f)
	{
		interval = min_max[0] - min_max[1];
		*center_point = min_max[1] + (interval / 2);
	}
	else
	{
		interval = min_max[1] - min_max[0];
		*center_point = min_max[0] + (interval / 2);
	}
	if (interval < 0.0f)
		interval = -interval;
	if (interval > *max_interval)
		*max_interval = interval;
}

void	set_model_pos_infos(t_model *model)
{
	unsigned int	i;
	unsigned int	axis_idx;
	float			min_max[2];

	i = 0;
	axis_idx = 0;
	while (axis_idx < 3)
	{
		get_min_max(model->v_array, model->nb_vtx, min_max, axis_idx);
		set_interval_and_center_point(min_max,
			&(model->center_points[axis_idx]), &(model->max_coord_interval));
		axis_idx++;
	}
	while (i < model->nb_vtx)
	{
		axis_idx = 0;
		while (axis_idx < 3)
		{
			model->v_array[i]->v[axis_idx] -= model->center_points[axis_idx];
			axis_idx++;
		}
		i++;
	}
}
