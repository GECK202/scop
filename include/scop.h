/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:18:46 by vkaron            #+#    #+#             */
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
# include "libmat.h"

# define FRAG_SHADER "shader.fs"
# define VTX_SHADER "shader.vs"

# define BMP_HEADER_SIZE 54

# define WIN_W 1600
# define WIN_H 1200 

typedef enum e_err
{
	NB_ARG,
	OPEN,
	READ,
	CLOSE,
	ALLOC,
	MODEL_DATA,
	UNSUPPORTED,
	GLFW_INIT,
	WIN_CREAT,
	SHADER_CREAT,
	UNIFORM_VAR,
	TEXTURE_LOAD
}	t_err;

typedef struct s_tex
{
	int				width;
	int				height;
	unsigned int	img_size;
	unsigned short	bpp;
	unsigned char	*buff_data;
	unsigned char	*img_data;
	unsigned int	data_offset;
}	t_tex;

typedef struct s_model
{
	unsigned int	nb_vtx;
	unsigned int	nb_face;
	t_v3			**v_array;
	unsigned int	**f_array;
	float			center_points[3];
	float			max_coord_interval;
	char			*name;
}	t_model;

typedef struct s_gl_objs
{
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	ebo;
	unsigned int	vtx_shader;
	unsigned int	frag_shader;
	unsigned int	shader_prog;
	unsigned int	nb_elems;
	GLuint			tex_id;
	GLint			mvp;
	GLint			interpolate;
	GLint			color;
	GLint			gradient;
	GLint			tex_loc;
	GLint			light_loc;
}	t_gl_objs;

typedef struct s_render_opts
{
	int				demo;
	int				interpolate;
	int				wireframe;
	int				color;
	int				gradient;
	int				texture;
	float			ambient_light;
}	t_render_opts;
typedef struct s_mats
{
	t_m4			translate;
	t_m4			rotate;
	t_m4			scale;
	t_m4			model;
	t_m4			view;
	t_m4			proj;
	t_m4			mvp;
	float			fov;
}	t_mats;

typedef struct s_env
{
	t_model			*model;
	t_gl_objs		*gl_objs;
	t_mats			*mats;
	GLFWwindow		*window;
	t_render_opts	*render_opts;
}	t_env;

void			framebuffer_size_callback(GLFWwindow *window, int width,
					int height);
void			processInput(GLFWwindow *window);
int				create_shader(const char *src, int shader_type);
int				create_shader_prog(int vert_shader, int frag_shader);
int				init_gl_window(GLFWwindow **window);
void			init_verticies(unsigned int *VBO, unsigned int *VAO,
					unsigned int *EBO);
void			render_cycle(GLFWwindow	*window, int shader_prog,
					unsigned int VAO);
void			free_buffers(unsigned int *VAO, unsigned int *VBO,
					unsigned int *EBO);

void			mvp_update(t_mats *mats);
void			rotate(t_mats *mats, int key);
void			translate(t_mats *mats, int key);

unsigned int	gen_shader(char *shader_file, int shader_type);

unsigned int	gen_shader_prog(unsigned int vert_shader,
					unsigned int frag_shader);

void			put_error(t_err err, const char *str);
void			exit_error(t_err err, const char *str);

unsigned int	load_tex(const char *file);

unsigned int	ft_strtoui(char *str);
t_mats			*get_matrices(void);
t_env			*get_env_struct(t_env *env);

void			key_callback(GLFWwindow *win, int key, int scanc, int action);

void			gl_objs_update(t_gl_objs *gl_objs,
					t_render_opts *render_opts, GLfloat *mvp_address);
t_gl_objs		*generate_gl_objs(t_model *model);

t_env			*init_env(void);
t_mats			*init_mats(float coord_interval);

void			init_window(GLFWwindow **win, char *model_name);

void			set_model_pos_infos(t_model *model);

void			store_vertex(char **data, t_v3 **array, unsigned int *nb_vtx);
void			store_face(char **data, unsigned int **array,
					unsigned int *nb_face);

void			handle_file(char *path, t_model *model);

#endif