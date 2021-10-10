/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:13:45 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/17 22:07:18 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	parse_data(FILE *fs, t_model *model)
{
	char	**split;
	char	*buf;
	size_t	buf_cap;
	ssize_t	buf_len;

	buf = NULL;
	buf_cap = 0;
	buf_len = getline(&buf, &buf_cap, fs);
	while (buf_len > 0)
	{
		if (buf_len > 1 && buf[0] == 'v' && buf[1] == ' ')
		{
			split = ft_strsplit(buf, ' ');
			store_vertex(split, model->v_array, &(model->nb_vtx));
			ft_free_tab(split);
		}
		else if (buf_len > 1 && buf[0] == 'f' && buf[1] == ' ')
		{
			split = ft_strsplit(buf, ' ');
			store_face(split, model->f_array, &(model->nb_face));
			ft_free_tab(split);
		}
		buf_len = getline(&buf, &buf_cap, fs);
	}
	free(buf);
}

static int	parse_file_line(char *line)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_strsplit(line, ' ');
	if (!split)
		exit_error(ALLOC, NULL);
	while (split[i])
		i++;
	ft_free_tab(split);
	if (i == 4)
		return (1);
	if (i == 5)
		return (2);
	return (0);
}

static void	parse_file(FILE *fs, unsigned int *nb_vtx, unsigned int *nb_face)
{
	char	*buf;
	size_t	buf_cap;
	ssize_t	buf_len;

	buf = NULL;
	buf_cap = 0;
	buf_len = getline(&buf, &buf_cap, fs);
	while (buf_len > 0)
	{
		if (buf_len > 1 && buf[0] == 'v' && buf[1] == ' ')
			(*nb_vtx)++;
		else if (buf_len > 1 && buf[0] == 'f' && buf[1] == ' ')
			(*nb_face) += parse_file_line(buf);
		buf_len = getline(&buf, &buf_cap, fs);
	}
	free(buf);
	if (*nb_vtx < 3 || *nb_face == 0)
		exit_error(MODEL_DATA, NULL);
}

void	handle_file(char *path, t_model *model)
{
	FILE	*fs;

	fs = fopen(path, "r");
	if (!fs)
		exit_error(OPEN, path);
	parse_file(fs, &(model->nb_vtx), &(model->nb_face));
	model->name = "model";
	model->v_array = (t_v3 **)malloc(sizeof(t_v3 *) * model->nb_vtx);
	if (!model->v_array)
		exit_error(ALLOC, NULL);
	model->f_array = (unsigned int **)malloc(sizeof(unsigned int *)
			* model->nb_face);
	if (!model->f_array)
		exit_error(ALLOC, NULL);
	if (!model->v_array || !model->f_array)
	{
		fclose(fs);
		exit_error(ALLOC, NULL);
	}
	rewind(fs);
	parse_data(fs, model);
	fclose(fs);
}
