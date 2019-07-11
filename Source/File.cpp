#include "File.h"

namespace GDT
{
    FileNotFoundException::FileNotFoundException(std::string filePath) :
        _errorMessage(std::string("Failed to find file: ") + filePath)
    {

    }

    const char* FileNotFoundException::what() const throw()
    {
        return _errorMessage.c_str();
    }

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
}
