#pragma once
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <iostream>

std::string readFile(const char *filePath) {
  std::string content;
  std::ifstream fileStream(filePath, std::ios::in);
  if (!fileStream.is_open()) {
    std::cerr << "Nie udalo sie otworzyc pliku: " << filePath << std::endl;
    return "";
  }
  std::stringstream sstr;
  sstr << fileStream.rdbuf();
  content = sstr.str();
  fileStream.close();
  return content;
}

unsigned int createShaderProgram(const char *vertexPath, const char *fragmentPath) {
  // 1. Wczytaj kod z plików
  std::string vertexCode = readFile(vertexPath);
  std::string fragmentCode = readFile(fragmentPath);
  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  // 2. Skompiluj Vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  // Sprawdź błędy (BARDZO WAŻNE!)
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // 3. Skompiluj Fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // 4. Linkowanie Programu
  unsigned int ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  // Sprawdź błędy linkowania
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return ID;
}

struct ShaderManager {
  unsigned int program;

  ShaderManager(const char *vertexPath, const char *fragmentPath) {
    program = createShaderProgram(vertexPath, fragmentPath);
  }

  void use() const { glUseProgram(program); }

  void setUniform1f(const char *name, float value) const { glUniform1f(glGetUniformLocation(program, name), value); }

  void setUniform1i(const char *name, int value) const { glUniform1i(glGetUniformLocation(program, name), value); }

  ~ShaderManager() { glDeleteProgram(program); }
};