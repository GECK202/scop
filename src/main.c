/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:13:45 by vkaron            #+#    #+#             */
/*   Updated: 2021/08/21 06:25:59 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

// Константы
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* vert_shader_src = VSH;
const char* frag_shader_src = FSH;

int main()
{
	GLFWwindow		*window;
	int				vert_shader;
	int				frag_shader;
	int				shader_prog;
	unsigned int	VAO;
	unsigned int	VBO;
	unsigned int	EBO;

	if (!init_gl_window(&window))
		return (-1);
	if (!(vert_shader = create_shader(vert_shader_src, GL_VERTEX_SHADER)))
		return (-1);
	if (!(frag_shader = create_shader(frag_shader_src, GL_FRAGMENT_SHADER)))
		return (-1);
	if (!(shader_prog = create_shader_prog(vert_shader, frag_shader)))
		return (-1);	
	init_verticies(&VBO, &VAO, &EBO);
	render_cycle(window, shader_prog, VAO);
 	free_buffers(&VAO, &VBO, &EBO);
	return 0;
}

void	free_buffers(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO)
{
	glDeleteVertexArrays(1, VAO);
	glDeleteBuffers(1, VBO);
	glDeleteBuffers(1, EBO);

	// glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
	glfwTerminate();
}

void	render_cycle(GLFWwindow	*window, int shader_prog, unsigned int VAO)
{
		// Цикл рендеринга
	while (!glfwWindowShouldClose(window))
	{
		//write(1, "0k\n", 3);
		// Обработка ввода
		processInput(window);
		
		// Выполнение рендеринга
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Рисуем наш первый треугольник
		glUseProgram(shader_prog);
		glBindVertexArray(VAO); // поскольку у нас есть только один VAO, то нет необходимости связывать его каждый раз (но мы сделаем это, чтобы всё было немного организованнее)
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// glBindVertexArray(0); // не нужно каждый раз его отвязывать
 
		// glfw: обмен содержимым front- и back-буферов. Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void	load_verticies_data(float *vertices, unsigned int *indices)
{
	vertices[0] = 0.5f;
	vertices[1] = 0.5f;
	vertices[2] = 0.2f;

	vertices[3] = 0.5f;
	vertices[4] = -0.5f;
	vertices[5] = 0.4f;

	vertices[6] = -0.5f;
	vertices[7] = -0.5f;
	vertices[8] = 0.6f;

	vertices[9] = -0.5f;
	vertices[10] = 0.5f;
	vertices[11] = 0.7f;

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 3;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;
}

void	init_verticies(unsigned int *VBO, unsigned int *VAO, unsigned int *EBO)
{
	float			vertices[12];
	unsigned int	indices[6];

	load_verticies_data(vertices, indices);
 
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);
 
	// Сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы)
	glBindVertexArray(*VAO);
 
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
 
	// Обратите внимание, что данное действие разрешено, вызов glVertexAttribPointer() зарегистрировал VBO как привязанный вершинный буферный объект для вершинного атрибута, так что после этого мы можем спокойно выполнить отвязку
	glBindBuffer(GL_ARRAY_BUFFER, 0);
 
	// Вы можете отменить привязку VAO после этого, чтобы другие вызовы VAO случайно не изменили этот VAO (но подобное довольно редко случается).
	// Модификация других VAO требует вызова glBindVertexArray(), поэтому мы обычно не снимаем привязку VAO (или VBO), когда это не требуется напрямую
	glBindVertexArray(0);
}

int init_gl_window(GLFWwindow **window)
{
	//*
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//*/
	;
	if (!(*window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL)))
	{
		write(1, "Failed to create GLFW window\n", 29);
		glfwTerminate();
		return (0);
	}
	glfwMakeContextCurrent(*window);
	glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		write(1, "Failed to initialize GLAD\n", 26);
		return (0);
	}
	return (1);
}

int create_shader(const char* src, int shader_type)
{
	int		shader;
	int		success;
	char	info_log[512];

	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		if (shader_type == GL_VERTEX_SHADER)
			write(1, "ERROR VERTEX SHADER COMPILATION FAILED\n", 39);
		else
			write(1, "ERROR FRAGMENT SHADER COMPILATION FAILED\n", 41);
		return (0);
	}
	return (shader);
}

int create_shader_prog(int vert_shader, int frag_shader)
{
	int		shader_prog;
	int		success;
	char	info_log[512];

	shader_prog = glCreateProgram();
	glAttachShader(shader_prog, vert_shader);
	glAttachShader(shader_prog, frag_shader);
	glLinkProgram(shader_prog);
	glGetProgramiv(shader_prog, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_prog, 512, NULL, info_log);
		write(1, "ERROR SHADER PROGRAM LINKING FAILED\n", 36);
	}
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
	return (shader_prog);
}


// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре в данном кадре и соответствующая обработка данных событий
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}
 
// glfw: всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Убеждаемся, что окно просмотра соответствует новым размерам окна. 
	// Обратите внимание, высота окна на Retina-дисплеях будет значительно больше, чем указано в программе
	glViewport(0, 0, width, height);
}

