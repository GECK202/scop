/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:13:45 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/17 22:07:18 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	switch_option_state(t_env *env, int key)
{
	if (key == GLFW_KEY_1)
		env->render_opts->demo = env->render_opts->demo == 1 ? 0 : 1;
	if (key == GLFW_KEY_2)
	{
		env->render_opts->wireframe = env->render_opts->wireframe == 1 ? 0 : 1;
		if (env->render_opts->wireframe == 1)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (key == GLFW_KEY_3 && env->render_opts->interpolate == 1)
		env->render_opts->interpolate = 0;
	else if (key == GLFW_KEY_3 && env->render_opts->interpolate == 0)
		env->render_opts->interpolate = 1;
	if (key == GLFW_KEY_4)
		env->render_opts->color = env->render_opts->color == 1 ? 0 : 1;
	if (key == GLFW_KEY_5)
		env->render_opts->gradient = env->render_opts->gradient == 1 ? 0 : 1;
	if (key == GLFW_KEY_6)
	{
		if (env->render_opts->texture == 2)
			env->render_opts->texture = 0;
		else
			env->render_opts->texture++;
	}
}

static void	change_ambient_light(t_env *env, int key)
{
	if (key == GLFW_KEY_KP_SUBTRACT &&
	env->render_opts->ambient_light > 0.0f)
		env->render_opts->ambient_light -= 0.02f;
	if (key == GLFW_KEY_KP_ADD &&
	env->render_opts->ambient_light < 4.0f)
		env->render_opts->ambient_light += 0.02f;
}

static void	reset_rendering(t_env *env)
{
	env->render_opts->demo = 1;
	env->render_opts->interpolate = 0;
	env->render_opts->wireframe = 0;
	env->render_opts->color = 0;
	env->render_opts->gradient = 1;
	env->render_opts->texture = 0;
	env->render_opts->ambient_light = 1.0f;
	env->mats->translate = m4_transl(new_m4(MAT_IDENTITY),
	new_v3(0, 0, (env->model->max_coord_interval * -0.75f)));
	env->mats->rotate = new_m4(MAT_IDENTITY);
	mvp_update(env->mats);
}

void		key_callback(GLFWwindow *win, int key, int scanc, int action,
int mods)
{
	(void)scanc;
	(void)mods;
	if (action == GLFW_RELEASE)
		return ;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(win, 1);
		return ;
	}
	if (key >= GLFW_KEY_RIGHT && key <= GLFW_KEY_PAGE_DOWN)
		rotate(get_matrices(), key);
	if (key >= GLFW_KEY_A && key <= GLFW_KEY_W)
		translate(get_matrices(), key);
	if (key >= GLFW_KEY_1 && key <= GLFW_KEY_6)
		switch_option_state(get_env_struct(NULL), key);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		reset_rendering(get_env_struct(NULL));
	if (key == GLFW_KEY_KP_SUBTRACT || key == GLFW_KEY_KP_ADD)
		change_ambient_light(get_env_struct(NULL), key);
}
