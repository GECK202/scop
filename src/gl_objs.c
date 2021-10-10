/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_objs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:13:45 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/17 22:07:18 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	gl_objs_update(t_gl_objs *gl_objs,
t_render_opts *render_opts, GLfloat *mvp_address)
{
	glUniformMatrix4fv(gl_objs->mvp, 1, GL_FALSE, mvp_address);
	glUniform1i(gl_objs->interpolate, render_opts->interpolate);
	glUniform1i(gl_objs->color, render_opts->color);
	glUniform1i(gl_objs->gradient, render_opts->gradient);
	glUniform1i(gl_objs->tex_loc, render_opts->texture);
	glUniform1f(gl_objs->light_loc, render_opts->ambient_light);
}

static void	bind_uniform_locations(t_gl_objs *gl_objs)
{
	gl_objs->mvp = glGetUniformLocation(gl_objs->shader_prog, "mvp");
	if (gl_objs->mvp == -1)
		exit_error(UNIFORM_VAR, NULL);
	gl_objs->interpolate = glGetUniformLocation(gl_objs->shader_prog,
			"interpolate");
	if (gl_objs->interpolate == -1)
		exit_error(UNIFORM_VAR, NULL);
	gl_objs->color = glGetUniformLocation(gl_objs->shader_prog, "color");
	if (gl_objs->color == -1)
		exit_error(UNIFORM_VAR, NULL);
	gl_objs->gradient = glGetUniformLocation(gl_objs->shader_prog, "gradient");
	if (gl_objs->gradient == -1)
		exit_error(UNIFORM_VAR, NULL);
	gl_objs->tex_loc = glGetUniformLocation(gl_objs->shader_prog, "texturing");
	if (gl_objs->tex_loc == -1)
		exit_error(UNIFORM_VAR, NULL);
	gl_objs->light_loc = glGetUniformLocation(gl_objs->shader_prog,
			"ambient_light");
	if (gl_objs->light_loc == -1)
		exit_error(UNIFORM_VAR, NULL);
	glUniform1i(glGetUniformLocation(gl_objs->shader_prog,
			"textur"), 0);
}

static unsigned int	generate_ebo(unsigned int **faces, unsigned int nb_faces)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	unsigned int	ebo;
	unsigned int	*indices;

	i = 0;
	j = 0;
	indices = (unsigned int *)malloc(sizeof(unsigned int) * nb_faces * 3);
	while (i < nb_faces)
	{
		k = -1;
		while (++k < 3)
		{
			indices[j] = faces[i][k];
			j++;
		}
		i++;
	}
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * nb_faces * 3,
		indices, GL_DYNAMIC_DRAW);
	free(indices);
	return (ebo);
}

static unsigned int	generate_vbo(t_v3 **vec, unsigned int nb_vtx)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	unsigned int	vbo;
	float			*vertices;

	i = 0;
	j = 0;
	vertices = (float *)malloc(sizeof(float) * nb_vtx * 3);
	while (i < nb_vtx)
	{
		k = -1;
		while (++k < 3)
		{
			vertices[j] = vec[i]->v[k];
			j++;
		}
		i++;
	}
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nb_vtx * 3,
		vertices, GL_DYNAMIC_DRAW);
	free(vertices);
	return (vbo);
}

t_gl_objs	*generate_gl_objs(t_model *model)
{
	t_gl_objs	*gl_objs;

	gl_objs = (t_gl_objs *)malloc(sizeof(*gl_objs));
	if (!gl_objs)
		exit_error(ALLOC, NULL);
	glGenVertexArrays(1, &(gl_objs->vao));
	glBindVertexArray(gl_objs->vao);
	gl_objs->vbo = generate_vbo(model->v_array, model->nb_vtx);
	gl_objs->ebo = generate_ebo(model->f_array, model->nb_face);
	gl_objs->vtx_shader = gen_shader(VTX_SHADER, GL_VERTEX_SHADER);
	gl_objs->frag_shader = gen_shader(FRAG_SHADER, GL_FRAGMENT_SHADER);
	gl_objs->shader_prog = gen_shader_prog(gl_objs->vtx_shader,
			gl_objs->frag_shader);
	gl_objs->vtx_shader = 0;
	gl_objs->frag_shader = 0;
	gl_objs->tex_id = load_tex("texture.bmp");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glUseProgram(gl_objs->shader_prog);
	bind_uniform_locations(gl_objs);
	return (gl_objs);
}
