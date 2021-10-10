/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:13:45 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/17 22:07:18 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static char	*close_return(char *final_path, char *shader_src, FILE *fs)
{
	if (fclose(fs) != 0)
		put_error(CLOSE, final_path);
	free(final_path);
	return (shader_src);
}

static char	*get_shader_src(char *src_file)
{
	FILE				*fs;
	long				size;
	static const char	shader_dir[] = "./shaders/";
	char				*final_path;
	char				*shader_src;

	final_path = ft_strjoin(shader_dir, src_file);
	if (!final_path)
		exit_error(ALLOC, NULL);
	fs = fopen(final_path, "r");
	if (!fs)
		exit_error(OPEN, final_path);
	fseek(fs, 0, SEEK_END);
	size = ftell(fs);
	if (size < 0)
		exit_error(READ, final_path);
	shader_src = (char *)malloc(sizeof(*shader_src) * size + 1);
	if (!shader_src)
		exit_error(ALLOC, NULL);
	rewind(fs);
	if (fread(shader_src, size, 1, fs) != 1)
		exit_error(READ, final_path);
	shader_src[size] = '\0';
	return (close_return(final_path, shader_src, fs));
}

unsigned int	gen_shader(char *shader_file, int shader_type)
{
	unsigned int	shader_id;
	int				sh_compil_ok;
	char			err_log[512];
	const GLchar	*shader_src;

	shader_src = get_shader_src(shader_file);
	shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, &shader_src, NULL);
	glCompileShader(shader_id);
	free((void *)shader_src);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &sh_compil_ok);
	if (!(sh_compil_ok))
	{
		glGetShaderInfoLog(shader_id, 512, NULL, err_log);
		exit_error(SHADER_CREAT, err_log);
	}
	return (shader_id);
}

unsigned int	gen_shader_prog(unsigned int vert_shader,
								unsigned int frag_shader)
{
	int				shader_link_ok;
	char			err_log[512];
	unsigned int	shader_prog_id;

	shader_prog_id = glCreateProgram();
	glAttachShader(shader_prog_id, vert_shader);
	glAttachShader(shader_prog_id, frag_shader);
	glLinkProgram(shader_prog_id);
	glGetProgramiv(shader_prog_id, GL_LINK_STATUS, &shader_link_ok);
	if (!(shader_link_ok))
	{
		glGetProgramInfoLog(shader_prog_id, 512, NULL, err_log);
		exit_error(SHADER_CREAT, err_log);
	}
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
	return (shader_prog_id);
}
