#pragma once

#include <string>
#include <fstream>

#include <exception>

#ifdef GDT_NAMESPACE
namespace GDT
{
#endif
    struct FileNotFoundException : std::exception
    {
        FileNotFoundException(std::string filePath);

        const char* what() const throw();

    private:
        std::string _errorMessage;
    };

    std::string loadFile(std::string filePath);
#ifdef GDT_NAMESPACE
}
#endif
