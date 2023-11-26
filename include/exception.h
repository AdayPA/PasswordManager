#pragma once
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

class Exception7: public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Could not close the connection properly";
    }
};

class Exception8: public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Connection not established";
    }
};