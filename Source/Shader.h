#pragma once

#include "Exception.h"

#include <glad/glad.h>

#include <string>
#include <vector>

struct ShaderLoadingException : public ErrorMessageException
{
    using ErrorMessageException::ErrorMessageException;
};

class Vector3f;
class Matrix4f;

enum ShaderType
{
    VERTEX, FRAGMENT, GEOMETRY
};

class Shader
{
    friend class ShaderProgram;

public:
    /**
     * Creates a new shader object of the given type
     *
     * @param type The type this shader should be
     */
    Shader(ShaderType type);

    bool isCompiled() const;

    bool loadFromFile(std::string path);
    void compile();
    void destroy();

    std::string getInfoLog();
private:
    void create();

    ShaderType _type;

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

    void uniform1i(const char* name, int i);
    void uniform1iv(const char* name, int count, int* values);
    void uniform2i(const char* name, int v0, int v1);
    void uniform1f(const char* name, float value);
    void uniform1fv(const char* name, int count, float* values);
    void uniform2f(const char* name, float v0, float v1);
    void uniform3f(const char* name, float v0, float v1, float v2);
    void uniform3f(const char* name, Vector3f& v);
    void uniform3fv(const char* name, int count, Vector3f* values);
    void uniformMatrix4f(const char* name, Matrix4f& m);


private:
    void create();
    void link();
    void validate();
    void attach(const Shader& shader);
    void detachAll();

    std::string getInfoLog();
    GLint getUniformLocation(const char* name);

private:
    bool _isCreated;
    bool _isLinked;
    bool _isValidated;

    std::vector<std::string> errorLog;
    std::vector<Shader> _attachedShaders;

    GLuint _handle;
};
