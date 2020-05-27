#include <cstdio>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
using namespace glm;

const GLchar* vertexSource = R"glsl(
  #version 150 core
  in vec3 position;
  in vec3 color;
  in vec2 texcoord;
  out vec3 Color;
  out vec2 Texcoord;
  uniform mat4 model;
  uniform mat4 view;
  uniform mat4 proj;
  void main(){
    Color = color;
    Texcoord = texcoord;
    gl_Position = proj * view * model * vec4(position, 1.0);
  }
)glsl";

const GLchar* fragmentSource = R"glsl(
  #version 150 core
  in vec3 Color;
  in vec2 Texcoord;
  out vec4 outColor;
  uniform sampler2D texTerrain;
  void main(){
    outColor = vec4(Color, 1.0) * texture(texTerrain, Texcoord);
  }
)glsl";

GLFWwindow *window;

int main(int argc, char **argv){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  window = glfwCreateWindow(800, 600, "Labo", nullptr, nullptr);


  assert(window != nullptr);

  glfwMakeContextCurrent(window);
  gladLoadGL();
  fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

  // Init GLFW
  // Enable track_pad input
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Init OpenGL
  glEnable(GL_DEPTH_TEST);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);

  float tex_aspect = 1.0f / 16;

  GLfloat vertices[] = {
    // Position | Color | Texture Coordinate
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, 0.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, tex_aspect,
    0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, tex_aspect,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, tex_aspect,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, 0.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, tex_aspect,
    0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, tex_aspect,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, tex_aspect,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, tex_aspect,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, tex_aspect,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, tex_aspect,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, 0.0f,

    0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, 0.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, tex_aspect,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, tex_aspect,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, tex_aspect,
    0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, tex_aspect,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, tex_aspect,
    0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, 0.0f,
    0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, tex_aspect,

    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, tex_aspect,
    0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, tex_aspect,
    0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, 0.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, tex_aspect, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, tex_aspect
  };

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, nullptr);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
  glCompileShader(fragmentShader);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

  GLuint terrain;
  glGenTextures(1, &terrain);

  int width, height, nrChannels;

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, terrain);
  unsigned short *data;
  //unsigned short *data = stbi_load_16("/Users/ogiwara/Documents/Labo/res/texture/terrain.png", &width, &height, &nrChannels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT, data);
  //stbi_image_free(data);
  glUniform1i(glGetUniformLocation(shaderProgram, "texTerrain"), 0);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  GLuint uniModel = glGetUniformLocation(shaderProgram, "model");
  GLint uniView = glGetUniformLocation(shaderProgram, "view");
  GLint uniProj = glGetUniformLocation(shaderProgram, "proj");

  while(!glfwWindowShouldClose(window)){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
      glfwSetWindowShouldClose(window, true);
    }

    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4 view = mat4();
    mat4 proj = mat4();

    glUniformMatrix4fv(uniView, 1, GL_FALSE, value_ptr(view));

    glUniformMatrix4fv(uniProj, 1, GL_FALSE, value_ptr(proj));

    mat4 model = mat4(1.0f);

    glUniformMatrix4fv(uniModel, 1, GL_FALSE, value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteTextures(1, &terrain);

  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

  glDeleteBuffers(1, &vbo);

  glDeleteVertexArrays(1, &vao);

  glfwTerminate();

  return 0;
}