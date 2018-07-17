#pragma once

#include <exception>

#include <string>

struct ErrorMessageException : public std::exception
{
    ErrorMessageException(std::string error)
        : _error(error)
    { }

    ErrorMessageException(const std::exception& e)
        : _error(e.what())
    { }

    const char* what() const throw()
    {
        return _error.c_str();
    }

private:
    std::string _error;
};
