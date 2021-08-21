/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:18:46 by fkoehler          #+#    #+#             */
/*   Updated: 2021/08/21 06:25:53 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

# define VSH "\
#version 410\n\
layout (location = 0) in vec3 aPos;\
out vec4 vertexColor;\
void main()\
{\
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\
   vertexColor = vec4(0.8, gl_Position.zxy);\
}\0"
# define FSH "\
#version 410\n\
out vec4 FragColor;\
in vec4 vertexColor;\
void main()\
{\
   FragColor = vertexColor;\
}\0"

# define WIN_W 1600
# define WIN_H 1200 

void	framebuffer_size_callback(GLFWwindow* window, int width, int height);
void	processInput(GLFWwindow *window);
int		create_shader(const char* src, int shader_type);
int		create_shader_prog(int vert_shader, int frag_shader);
int		init_gl_window(GLFWwindow **window);
void	init_verticies(unsigned int *VBO, unsigned int *VAO, unsigned int *EBO);
void	render_cycle(GLFWwindow	*window, int shader_prog, unsigned int VAO);
void	free_buffers(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO);

#endif