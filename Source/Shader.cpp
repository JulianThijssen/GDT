#include "Shader.h"

#include "File.h"
#include "Vector3f.h"
#include "Matrix4f.h"

#include <sstream>

#ifdef GDT_NAMESPACE
namespace GDT
{
#endif
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

    Shader::Shader(ShaderType type) :
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

    bool Shader::loadFromSource(const char* source)
    {
        create();
        glShaderSource(_handle, 1, &source, nullptr);

        return true;
    }

    bool Shader::loadFromFile(std::string path)
    {
        std::string source = loadFile(path);
        const char* cSource = source.c_str();

        return loadFromSource(cSource);
    }

    void Shader::create()
    {
        GLenum glType;
        switch (_type)
        {
        case ShaderType::VERTEX: glType = GL_VERTEX_SHADER; break;
        case ShaderType::FRAGMENT: glType = GL_FRAGMENT_SHADER; break;
        case ShaderType::GEOMETRY: glType = GL_GEOMETRY_SHADER; break;
#ifdef GL_VERSION_4_3
        case ShaderType::COMPUTE: glType = GL_COMPUTE_SHADER; break;
#endif
        }

        _handle = glCreateShader(glType);

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
        case ShaderType::VERTEX: prefix = "Vertex shader info log:\n"; break;
        case ShaderType::GEOMETRY: prefix = "Geometry shader info log:\n"; break;
        case ShaderType::FRAGMENT: prefix = "Fragment shader info log:\n"; break;
#ifdef OPENGL_VERSION_4_3
        case COMPUTE: prefix = "Compute shader info log:\n"; break;
#endif
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

    void ShaderProgram::addShaderFromSource(ShaderType type, const char* source)
    {
        Shader shader(type);

        try
        {
            shader.loadFromSource(source);
        }
        catch (const FileNotFoundException& e)
        {
            throw ShaderLoadingException(e.what());
        }

        attach(shader);
    }

    void ShaderProgram::addShaderFromFile(ShaderType type, std::string path)
    {
        Shader shader(type);

        try
        {
            shader.loadFromFile(path);
        }
        catch (const FileNotFoundException& e)
        {
            throw ShaderLoadingException(e.what());
        }

        attach(shader);
    }

    void ShaderProgram::build()
    {
        if (!_isCreated)
            return;

        try
        {
            for (Shader& shader : _attachedShaders)
                shader.compile();

            link();
            validate();

            for (Shader& shader : _attachedShaders)
                shader.destroy();
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
        for (Shader& shader : _attachedShaders)
            shader.destroy();

        // Crashes for reasons unknown, probably because the shader is
        // being kept alive by the exception throwing
        //_attachedShaders.clear();

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
        for (Shader& shader : _attachedShaders)
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
        std::string stringLog = std::string(log.begin(), log.end());

        return stringLog;
    }

    GLint ShaderProgram::getUniformLocation(const char* name)
    {
        std::unordered_map<std::string, int>::const_iterator it = _locationMap.find(std::string(name));
        if (it != _locationMap.end()) {
            return it->second;
        }
        else {
            int location = glGetUniformLocation(_handle, name);
            _locationMap[std::string(name)] = location;
            return location;
        }
    }

    void ShaderProgram::uniform1i(const char* name, int i)
    {
        glUniform1i(getUniformLocation(name), i);
    }

    void ShaderProgram::uniform1ui(const char* name, unsigned int i)
    {
        glUniform1ui(getUniformLocation(name), i);
    }

    void ShaderProgram::uniform1iv(const char* name, int count, int* values)
    {
        glUniform1iv(getUniformLocation(name), count, (GLint*)values);
    }

    void ShaderProgram::uniform2i(const char* name, int v0, int v1)
    {
        glUniform2i(getUniformLocation(name), v0, v1);
    }

    void ShaderProgram::uniform2ui(const char* name, unsigned int v0, unsigned int v1)
    {
        glUniform2ui(getUniformLocation(name), v0, v1);
    }

    void ShaderProgram::uniform1f(const char* name, float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }

    void ShaderProgram::uniform1fv(const char* name, int count, float* values)
    {
        glUniform1fv(getUniformLocation(name), count, (GLfloat*)values);
    }

    void ShaderProgram::uniform2f(const char* name, float v0, float v1)
    {
        glUniform2f(getUniformLocation(name), v0, v1);
    }

    void ShaderProgram::uniform3f(const char* name, float v0, float v1, float v2)
    {
        glUniform3f(getUniformLocation(name), v0, v1, v2);
    }

    void ShaderProgram::uniform3f(const char* name, const Vector3f& v)
    {
        glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
    }

    void ShaderProgram::uniform3fv(const char* name, int count, Vector3f* values)
    {
        glUniform3fv(getUniformLocation(name), count, (GLfloat*)values);
    }

    void ShaderProgram::uniform4f(const char* name, float v0, float v1, float v2, float v3)
    {
        glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
    }

    void ShaderProgram::uniformMatrix4f(const char* name, const Matrix4f& m)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, false, m.toArray());
    }
#ifdef GDT_NAMESPACE
}
#endif
