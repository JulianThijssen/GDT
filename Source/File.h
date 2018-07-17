#pragma once

#include <string>
#include <fstream>

#include <exception>

struct FileNotFoundException : std::exception
{
    FileNotFoundException(std::string filePath)
        : _errorMessage(std::string("Failed to find file: ") + filePath)
    { }

    const char* what() const throw()
    {
        return _errorMessage.c_str();
    }

private:
    std::string _errorMessage;
};

std::string loadFile(std::string filePath)
{
    std::ifstream file(filePath);
    if (file.fail() || !file.is_open())
    {
        throw FileNotFoundException(filePath);
    }

    std::string source;
    std::string line;

    while (getline(file, line))
    {
        source.append(line + '\n');
    }
    return source;
}
