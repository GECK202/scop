/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:13:45 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/17 22:07:18 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void				read_bmp_file_data(t_tex *tex, const char *path)
{
	FILE				*fs;
	char				header[BMP_HEADER_SIZE];

	if (!(fs = fopen(path, "r")))
		exit_error(OPEN, path);
	if (fread(header, 1, BMP_HEADER_SIZE, fs) != BMP_HEADER_SIZE
	|| header[0] != 'B' || header[1] != 'M')
		exit_error(TEXTURE_LOAD, NULL);
	if (!(tex->data_offset = *(unsigned int*)&(header[10])))
		tex->data_offset = BMP_HEADER_SIZE;
	if (!(tex->width = *(int*)&(header[18])) ||
	!(tex->height = *(int*)&(header[22])))
		exit_error(TEXTURE_LOAD, NULL);
	if (!(tex->bpp = *(unsigned short*)&(header[28])))
		exit_error(TEXTURE_LOAD, NULL);
	tex->width < 0 ? tex->width = -tex->width : 0;
	tex->height < 0 ? tex->height = -tex->height : 0;
	tex->img_size = tex->width * tex->height * (tex->bpp / 8);
	if (!(tex->buff_data = (unsigned char*)malloc(sizeof(unsigned char) *
	tex->img_size)))
		exit_error(ALLOC, NULL);
	if ((fread(tex->buff_data, 1, tex->img_size, fs)) !=
	tex->img_size)
		exit_error(TEXTURE_LOAD, NULL);
	fclose(fs);
}

static unsigned char	*reverse_img_data(unsigned char *buff,
				unsigned int img_size, unsigned int line_size)
{
	unsigned int	h;
	unsigned int	j;
	unsigned char	*img_data;

	h = 0;
	if (!(img_data =
	(unsigned char*)malloc(sizeof(unsigned char) * img_size)))
		exit_error(ALLOC, NULL);
	while (img_size > 0)
	{
		img_size -= line_size;
		j = 0;
		while (j < line_size)
		{
			img_data[h + j] = buff[img_size + j + 2];
			img_data[h + j + 1] = buff[img_size + j + 1];
			img_data[h + j + 2] = buff[img_size + j];
			j += 3;
		}
		h += line_size;
	}
	return (img_data);
}

static void				get_tex_data(t_tex *tex,
				const char *file)
{
	char				*path;

	if (!(path = ft_strjoin("./textures/", file)))
		exit_error(ALLOC, NULL);
	read_bmp_file_data(tex, path);
	ft_strdel(&path);
	tex->img_data = reverse_img_data(tex->buff_data, tex->img_size,
	tex->width * (tex->bpp / 8));
	ft_strdel((char**)&tex->buff_data);
}

unsigned int					load_tex(const char *file)
{
	static int	tex_index = 0;
	t_tex	*tex;
	unsigned int		tex_id;

	if (!(tex = (t_tex*)malloc(sizeof(*tex))))
		exit_error(ALLOC, NULL);
	get_tex_data(tex, file);
	glGenTextures(1, &tex_id);
	glActiveTexture(GL_TEXTURE0 + tex_index);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->width, tex->height, 0,
	GL_RGB, GL_UNSIGNED_BYTE, tex->img_data);
	ft_strdel((char **)&tex->img_data);
	free(tex);
	tex_index++;
	return (tex_id);
}
