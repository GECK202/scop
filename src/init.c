/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:13:45 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/17 22:07:18 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_render_opts	*init_render_opts(void)
{
	t_render_opts	*render_opts;

	render_opts = (t_render_opts *)malloc(sizeof(*render_opts));
	if (!render_opts)
		exit_error(ALLOC, NULL);
	render_opts->demo = 0;
	render_opts->interpolate = 0;
	render_opts->wireframe = 0;
	render_opts->color = 0;
	render_opts->gradient = 0;
	render_opts->texture = 0;
	render_opts->ambient_light = 1.0f;
	return (render_opts);
}

static t_model	*init_model(void)
{
	t_model	*model;

	model = (t_model *)malloc(sizeof(*model));
	if (!model)
		exit_error(ALLOC, NULL);
	model->nb_vtx = 0;
	model->nb_face = 0;
	model->v_array = NULL;
	model->f_array = NULL;
	model->name = NULL;
	model->center_points[0] = 0.0f;
	model->center_points[1] = 0.0f;
	model->center_points[2] = 0.0f;
	model->max_coord_interval = 0.0f;
	return (model);
}

t_env	*init_env(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(*env));
	if (!env)
		exit_error(ALLOC, NULL);
	get_env_struct(env);
	env->model = init_model();
	env->render_opts = init_render_opts();
	return (env);
}

t_mats	*init_mats(float coord_interval)
{
	t_mats	*mats;

	mats = (t_mats *)malloc(sizeof(*mats));
	if (!mats)
		exit_error(ALLOC, NULL);
	mats->fov = 70.0f;
	mats->view = new_m4(MAT_IDENTITY);
	mats->translate = m4_transl(new_m4(MAT_IDENTITY),
			new_v3(0, 0, (coord_interval * -1.75f)));
	mats->rotate = new_m4(MAT_IDENTITY);
	mats->scale = new_m4(MAT_IDENTITY);
	mats->proj = new_proj_m4(mats->fov,
			(float)WIN_W / (float)WIN_H, 0.1f, 100.0f);
	mats->rotate = m4_rot(mats->rotate, 0.75f, Y_AXIS);
	mvp_update(mats);
	return (mats);
}

void	init_window(GLFWwindow **win, char *model_name)
{
	if (!glfwInit())
		exit_error(GLFW_INIT, NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	*win = glfwCreateWindow(WIN_W, WIN_H, model_name, NULL, NULL);
	if (!(*win))
		exit_error(WIN_CREAT, NULL);
	glfwSetKeyCallback(*win, (GLFWkeyfun)(&key_callback));
	glfwSwapInterval(1);
	glfwMakeContextCurrent(*win);
	glfwGetFramebufferSize(*win, NULL, NULL);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		write(1, "Failed to initialize GLAD\n", 26);
		exit_error(WIN_CREAT, NULL);
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}
