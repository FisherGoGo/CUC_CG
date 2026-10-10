#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
 


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. 从文件路径中获取顶点/片段着色器，ifstream 是C++标准库中的输入文件流类，用于从文件读取数据。
    //stringstream 是字符串流类，用于在内存中构建和操作字符串
   ifstream vertexFile; //vertexFile 用于读取顶点着色器文件
   ifstream fragmentFile; //fragmentFile 用于读取片段着色器文件
   stringstream vertexSStream;  //用于临时存储从文件中读取的着色器代码
   stringstream fragmentSStream;

   vertexFile.open(vertexPath);
   fragmentFile.open(fragmentPath);
   // 保证ifstream对象可以抛出异常：ifstream::failbit 表示当流操作失败时设置（例如，尝试打开不存在的文件）。
   //ifstream::badbit 表示当流发生不可恢复的错误时设置（例如，文件读取过程中发生硬件故障）。
   vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
   fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);

   try
   {
       // 打开文件
       if (!vertexFile.is_open()||!fragmentFile.is_open())
           throw exception("open file error");
       // 将整个文件内容一次性读取到字符串流中
       vertexSStream << vertexFile.rdbuf();
       fragmentSStream << fragmentFile.rdbuf();
       // 关闭文件处理器
       vertexFile.close();
       fragmentFile.close();
       // 将字符串流中的内容转换为标准的C++字符串（std::string）
       vertexString = vertexSStream.str();
       fragmentString = fragmentSStream.str();
       //std::string::c_str() 方法返回一个指向字符串内部字符数组的指针（C风格字符串，以空字符'\0'结尾）。
       //OpenGL的着色器编译函数（如glShaderSource()）通常需要C风格字符串作为参数
       vertexSource = vertexString.c_str();
       fragmentSource = fragmentString.c_str();

       //将GLSL源代码字符串转换为GPU可以理解和执行的二进制格式
       unsigned int vertex, fragment;
       vertex = glCreateShader(GL_VERTEX_SHADER);
       glShaderSource(vertex, 1, &vertexSource, NULL);
       glCompileShader(vertex); //从源代码转成二进制
       checkCompileErrors(vertex, "VERTEX");


       fragment = glCreateShader(GL_FRAGMENT_SHADER);
       glShaderSource(fragment, 1, &fragmentSource, NULL);
       glCompileShader(fragment); //从源代码转成二进制
       checkCompileErrors(fragment, "FRAGMENT");


       // 着色器程序
       ID = glCreateProgram();
       glAttachShader(ID, vertex);
       glAttachShader(ID, fragment);
       glLinkProgram(ID); //编译把两个二进制代码链接起来
       checkCompileErrors(ID, "PROGRAM");

       glDeleteShader(vertex);
       glDeleteShader(fragment);



   }
   catch (const std::exception& ex)
   {
       printf(ex.what());

   }

}

void Shader::use()
{
    glUseProgram(ID);
}

//用于检查OpenGL着色器编译和程序链接错误的工具函数。
void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
    int success;
    char infoLog[512];
    if (type != "PROGRAM")
    {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(ID, 512, NULL, infoLog);
            std::cout << "shader compile error: " << infoLog <<endl;
        }
    }
    else
    {
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "program link error " << infoLog << endl;
        }
    }
}

 