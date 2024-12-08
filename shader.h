#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

 class shader
    {
    public:
        unsigned int shader_program;

        shader(const char* fragmentPath, const char* vertexPath, const char* geometryPath = nullptr)
        {
            std::string vertexCode; 
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;

            try 
            {
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;

                vShaderStream >> vShaderFile.rdbuf();
                fShaderStream >> fShaderFile.rdbuf();

                vShaderFile.close();
                fShaderFile.close();


                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();


            }
            catch (std::ifstream::failure e)
            {
                std::cout << "Error: Shader file(s) not successfully read." << std::endl;
            }


            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();

            unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
            unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
            int success;
            char infoLogv[512];

            // vertex shader 
            glShaderSource(vertex, 1, &vShaderCode, nullptr);
            glCompileShader(vertex);

            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertex, 512, NULL, infoLogv);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogv << std::endl;
            };
  

            char infologf[512];

            // fragment shader
            glShaderSource(fragment, 1, &fShaderCode, nullptr);
            glCompileShader(fragment);

            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(fragment, 512, NULL, infoLogf);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogf << std::endl;
            };
  

                // creating a program
            shader_program = glCreateProgram();

            // attaching shaders 
            glAttachShader(shader_program, vertex);
            glAttachShader(shader_program, fragment);

            // linking shaders to program
            glLinkProgram(shader_program);

            // deleting shaders as they are linked to the program and are no longer needed (optional)
            glDeleteShader(vertex);
            glDeleteShader(fragment);

        };

        void useShader() 
        {
            glUseProgram(shader_program);
        }


        // Uniform Setters
        void setBool(const std::string &name, bool value) const
        {         
            glUniform1i(glGetUniformLocation(shader_program, name.c_str()), (int)value); 
        }

        void setInt(const std::string &name, int value) const
        { 
            glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value); 
        }

        void setFloat(const std::string &name, float value) const
        { 
            glUniform1f(glGetUniformLocation(shader_program, name.c_str()), value); 
        } 
    };

#endif