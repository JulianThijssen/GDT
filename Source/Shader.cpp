#include "Shader.h"

#include "File.h"

#include <sstream>

struct ShaderCompilationException : public ErrorMessageException
{
    ShaderCompilationException(std::string error)
        : ErrorMessageException(error)
    { }
};

struct ShaderLinkageException : public ErrorMessageException
{
    ShaderLinkageException(std::string error)
        : ErrorMessageException(error)
    { }
};

struct ShaderValidationException : public ErrorMessageException
{
    ShaderValidationException(std::string error)
        : ErrorMessageException(error)
    { }
};

Shader::Shader(GLenum type) :
    _type(type),
    _isCreated(false),
    _isCompiled(false),
    _handle(0)
{

}

bool Shader::isCompiled() const
{
    return _isCompiled;
}

bool Shader::loadFromFile(std::string path)
{
    std::string source = loadFile(path);
    const char* cSource = source.c_str();

    create();
    glShaderSource(_handle, 1, &cSource, nullptr);

    return true;
}

void Shader::create()
{
    _handle = glCreateShader(_type);

    _isCreated = true;
    _isCompiled = false;
}

void Shader::compile()
{
    glCompileShader(_handle);

    GLint status;
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &status);

    _isCompiled = status == GL_TRUE;

    if (!_isCompiled)
    {
        std::string errorLog = getInfoLog();
        destroy();
        throw ShaderCompilationException(errorLog);
    }
}

void Shader::destroy()
{
    if (_handle != 0)
        glDeleteShader(_handle);

    _isCreated = false;
    _isCompiled = false;
}

std::string Shader::getInfoLog()
{
    std::string prefix;
    switch (_type)
    {
    case GL_VERTEX_SHADER: prefix = "Vertex shader info log:\n"; break;
    case GL_FRAGMENT_SHADER: prefix = "Fragment shader info log:\n"; break;
    }

    GLint logLength;
    glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &logLength);

    std::vector<GLchar> log(logLength);
    glGetShaderInfoLog(_handle, logLength, nullptr, log.data());
    return prefix + std::string(log.begin(), log.end());
}




ShaderProgram::ShaderProgram() :
    _isCreated(false),
    _isLinked(false),
    _isValidated(false),
    _handle(0)
{

}

void ShaderProgram::loadFromFile(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    try
    {
        create();

        Shader vertexShader(GL_VERTEX_SHADER);
        Shader fragmentShader(GL_FRAGMENT_SHADER);

        vertexShader.loadFromFile(vertexShaderPath);
        attach(vertexShader);
        fragmentShader.loadFromFile(fragmentShaderPath);
        attach(fragmentShader);

        vertexShader.compile();
        fragmentShader.compile();

        link();
        validate();

        vertexShader.destroy();
        fragmentShader.destroy();
    }
    catch (FileNotFoundException& e)
    {
        destroy();
        throw ShaderLoadingException(e);
    }
    catch (ErrorMessageException& e)
    {
        destroy();
        throw ShaderLoadingException(e);
    }
}

bool ShaderProgram::isLinked()
{
    return _isLinked;
}

bool ShaderProgram::isValidated()
{
    return _isValidated;
}

std::string ShaderProgram::getError()
{
    std::ostringstream ss;
    for (Shader& shader : _attachedShaders)
    {
        ss << shader.getInfoLog() << '\n';
    }
    ss << "Shader program info log:\n";
    ss << getInfoLog();

    return ss.str();
}

void ShaderProgram::create()
{
    if (_isCreated)
        destroy();

    _handle = glCreateProgram();

    _isCreated = true;
    _isLinked = false;
    _isValidated = false;
    _attachedShaders.clear();
}

void ShaderProgram::bind()
{
    glUseProgram(_handle);
}

void ShaderProgram::release()
{
    glUseProgram(0);
}

void ShaderProgram::destroy()
{
    for (Shader& shader: _attachedShaders)
        shader.destroy();

    _attachedShaders.clear();

    if (_handle != 0)
    {
        glDeleteProgram(_handle);
        _handle = 0;
    }

    _isCreated = false;
    _isLinked = false;
    _isValidated = false;
}

void ShaderProgram::link()
{
    glLinkProgram(_handle);

    GLint status = 0;
    glGetProgramiv(_handle, GL_LINK_STATUS, &status);

    _isLinked = status == GL_TRUE;

    if (!_isLinked) throw ShaderLinkageException(getInfoLog());
}

void ShaderProgram::validate()
{
    glValidateProgram(_handle);

    GLint status = 0;
    glGetProgramiv(_handle, GL_VALIDATE_STATUS, &status);

    _isValidated = status == GL_TRUE;
}

void ShaderProgram::attach(const Shader& shader)
{
    glAttachShader(_handle, shader._handle);
    _attachedShaders.push_back(shader);
}

void ShaderProgram::detachAll()
{
    for (Shader& shader: _attachedShaders)
    {
        glDetachShader(_handle, shader._handle);
    }
}

std::string ShaderProgram::getInfoLog()
{
    GLint logLength;
    glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &logLength);

    std::vector<GLchar> log(logLength);
    glGetProgramInfoLog(_handle, logLength, nullptr, log.data());
    return std::string(log.begin(), log.end());
}

void ShaderProgram::uniform1i(const char* location, int i)
{
    glUniform1i(glGetUniformLocation(_handle, location), i);
}
