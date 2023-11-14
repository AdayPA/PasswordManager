#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

class Exception1 : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Invalid password type";
    }
};

class Exception2 : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Invalid password size";
    }
};

class Exception3: public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Can't generate password";
    }
};

class Exception4: public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Can't generate Salt";
    }
};

class Exception5: public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Can not encrypt using AES";
    }
};

class Exception6: public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Can not encrypt using AES";
    }
};


#endif // MIS_EXCEPCIONES_H
