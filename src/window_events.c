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

static int	invert_bool(int bool)
{
	if (bool == 1)
		return (0);
	return (1);
}

static void	switch_option_state(t_env *env, int key)
{
	if (key == GLFW_KEY_1)
		env->render_opts->demo = invert_bool(env->render_opts->demo);
	if (key == GLFW_KEY_2)
	{
		env->render_opts->wireframe = invert_bool(env->render_opts->wireframe);
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
		env->render_opts->color = invert_bool(env->render_opts->color);
	if (key == GLFW_KEY_5)
		env->render_opts->gradient = invert_bool(env->render_opts->gradient);
	if (key == GLFW_KEY_6)
		env->render_opts->texture = invert_bool(env->render_opts->texture);
}

static void	change_ambient_light(t_env *env, int key)
{
	if (key == GLFW_KEY_KP_SUBTRACT
		&& env->render_opts->ambient_light > 0.0f)
		env->render_opts->ambient_light -= 0.02f;
	if (key == GLFW_KEY_KP_ADD
		&& env->render_opts->ambient_light < 4.0f)
		env->render_opts->ambient_light += 0.02f;
}

static void	reset_rendering(t_env *env)
{
	env->render_opts->demo = 0;
	env->render_opts->interpolate = 0;
	env->render_opts->wireframe = 0;
	env->render_opts->color = 0;
	env->render_opts->gradient = 0;
	env->render_opts->texture = 0;
	env->render_opts->ambient_light = 1.0f;
	env->mats->translate = m4_transl(new_m4(MAT_IDENTITY),
			new_v3(0, 0, (env->model->max_coord_interval * -1.75f)));
	env->mats->rotate = m4_rot(new_m4(MAT_IDENTITY), 0.75f, Y_AXIS);
	mvp_update(env->mats);
}

void	key_callback(GLFWwindow *win, int key, int scanc, int action)
{
	(void)scanc;
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
