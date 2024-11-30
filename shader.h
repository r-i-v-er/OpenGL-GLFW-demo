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

        unsigned int programID;

        shader(const char* fragmentPath, const char* vertexPath)
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

                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();

                vShaderFile.close();
                fShaderFile.close();

            }
            catch (std::ifstream::failure e)
            {
                std::cout << "Error: Shader file(s) not successfully read." << std::endl;
            }


            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();


        };

        void useShader() 
        {
            
        }




        ~shader();
    };

#endif