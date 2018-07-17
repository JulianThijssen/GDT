#pragma once

#include "Exception.h"

#include <glad/glad.h>

#include <string>
#include <vector>

struct ShaderLoadingException : public ErrorMessageException
{
    using ErrorMessageException::ErrorMessageException;
};

class Shader
{
    friend class ShaderProgram;

public:
    Shader(GLenum type);

    bool isCompiled() const;

    bool loadFromFile(std::string path);
    void compile();
    void destroy();

    std::string getInfoLog();
private:
    void create();

    GLenum _type;

    bool _isCreated;
    bool _isCompiled;

    GLuint _handle;
};

class ShaderProgram
{
public:
    ShaderProgram();
    void loadFromFile(std::string vertexShaderPath, std::string fragmentShaderPath);
    std::string getError();

    bool isLinked();
    bool isValidated();

    void bind();
    void release();
    void destroy();

    void uniform1i(const char* location, int i);

private:
    void create();
    void link();
    void validate();
    void attach(const Shader& shader);
    void detachAll();

    std::string getInfoLog();

private:
    bool _isCreated;
    bool _isLinked;
    bool _isValidated;

    std::vector<std::string> errorLog;
    std::vector<Shader> _attachedShaders;

    GLuint _handle;
};
