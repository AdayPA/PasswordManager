#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

class Exception1 : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Invalid password size";
    }
};

class Exception2 : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Can't generate password";
    }
};

// Agrega más clases de excepción según sea necesario

#endif // MIS_EXCEPCIONES_H
