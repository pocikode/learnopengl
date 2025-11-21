#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>
#include <ostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

GLfloat vertices1[] = {
    -0.8f, -0.4f, 0.0f, //
    -0.4f, 0.4f,  0.0f, //
    0.0f,  -0.4f, 0.0f, //
};
GLfloat vertices2[] = {
    0.0f, -0.4f, 0.0f, //
    0.4f, 0.4f,  0.0f, //
    0.8f, -0.4f, 0.0f, //
};

GLuint VAOs[2], VBOs[2];
GLuint vertexShader, firstFragmentShader, firstShaderProgram;
GLuint secondFragmentShader, secondShaderProgram;

const char *vertex_shader_src = "#version 330 core \n"
                                "layout (location = 0) in vec3 aPos;\n"
                                "void main() {\n"
                                "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                "}";

const char *first_fragment_shader_src = "#version 330 core\n"
                                        "out vec4 FragColor;\n"
                                        "void main() {\n"
                                        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                        "}";

const char *second_fragment_shader_src = "#version 330 core\n"
                                         "out vec4 FragColor;\n"
                                         "void main() {\n"
                                         "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                         "}";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // create window
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int shaderStatus;
    char shaderLog[512];

    // compile first vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_src, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderStatus);
    if (!shaderStatus)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, shaderLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << shaderLog << std::endl;
        return -1;
    }

    // compile first fragment shader
    firstFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(firstFragmentShader, 1, &first_fragment_shader_src, NULL);
    glCompileShader(firstFragmentShader);
    glGetShaderiv(firstFragmentShader, GL_COMPILE_STATUS, &shaderStatus);
    if (!shaderStatus)
    {
        glGetShaderInfoLog(firstFragmentShader, 512, NULL, shaderLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << shaderLog << std::endl;
        return -1;
    }

    // compile second fragment shader (yellow)
    secondFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(secondFragmentShader, 1, &second_fragment_shader_src, NULL);
    glCompileShader(secondFragmentShader);
    glGetShaderiv(secondFragmentShader, GL_COMPILE_STATUS, &shaderStatus);
    if (!shaderStatus)
    {
        glGetShaderInfoLog(firstFragmentShader, 512, NULL, shaderLog);
        std::cout << "ERROR::SHADER::FRAGMENT_YELLOW::COMPILATION_FAILED\n" << shaderLog << std::endl;
        return -1;
    }

    // first shader program
    firstShaderProgram = glCreateProgram();
    glAttachShader(firstShaderProgram, vertexShader);
    glAttachShader(firstShaderProgram, firstFragmentShader);
    glLinkProgram(firstShaderProgram);
    glGetProgramiv(firstShaderProgram, GL_LINK_STATUS, &shaderStatus);
    if (!shaderStatus)
    {
        glGetProgramInfoLog(firstShaderProgram, 512, NULL, shaderLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << shaderLog << std::endl;
        return -1;
    }

    // second shader program
    secondShaderProgram = glCreateProgram();
    glAttachShader(secondShaderProgram, vertexShader);
    glAttachShader(secondShaderProgram, secondFragmentShader);
    glLinkProgram(secondShaderProgram);
    glGetProgramiv(secondShaderProgram, GL_LINK_STATUS, &shaderStatus);
    if (!shaderStatus)
    {
        glGetProgramInfoLog(firstShaderProgram, 512, NULL, shaderLog);
        std::cout << "ERROR::SHADER::PROGRAM_YELLOW::LINK_FAILED\n" << shaderLog << std::endl;
        return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(firstFragmentShader);
    glDeleteShader(secondFragmentShader);

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // first triangle
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    // second triangle
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(firstShaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(secondShaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(firstShaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
