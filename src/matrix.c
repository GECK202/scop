/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:13:45 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/17 22:07:18 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	mvp_update(t_mats *mats)
{
	mats->model = m4_mul(mats->scale, m4_mul(mats->rotate, mats->translate));
	mats->mvp = m4_mul(mats->model, m4_mul(mats->view, mats->proj));
}

void	rotate(t_mats *mats, int key)
{
	if (key == GLFW_KEY_UP)
		mats->rotate = m4_rot(mats->rotate, 0.025f, X_AXIS);
	if (key == GLFW_KEY_DOWN)
		mats->rotate = m4_rot(mats->rotate, -0.025f, X_AXIS);
	if (key == GLFW_KEY_LEFT)
		mats->rotate = m4_rot(mats->rotate, 0.025f, Y_AXIS);
	if (key == GLFW_KEY_RIGHT)
		mats->rotate = m4_rot(mats->rotate, -0.025f, Y_AXIS);
	if (key == GLFW_KEY_PAGE_UP)
		mats->rotate = m4_rot(mats->rotate, 0.025f, Z_AXIS);
	if (key == GLFW_KEY_PAGE_DOWN)
		mats->rotate = m4_rot(mats->rotate, -0.025f, Z_AXIS);
	mvp_update(mats);
}

void	translate(t_mats *mats, int key)
{
	if (key == GLFW_KEY_A)
		mats->translate = m4_transl(mats->translate, new_v3(-0.07f, 0, 0));
	if (key == GLFW_KEY_D)
		mats->translate = m4_transl(mats->translate, new_v3(0.07f, 0, 0));
	if (key == GLFW_KEY_W)
		mats->translate = m4_transl(mats->translate, new_v3(0, 0.07f, 0));
	if (key == GLFW_KEY_S)
		mats->translate = m4_transl(mats->translate, new_v3(0, -0.07f, 0));
	if (key == GLFW_KEY_Q)
		mats->translate = m4_transl(mats->translate, new_v3(0, 0, 0.07f));
	if (key == GLFW_KEY_E)
		mats->translate = m4_transl(mats->translate, new_v3(0, 0, -0.07f));
	mvp_update(mats);
}
