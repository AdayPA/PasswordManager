// clase1.h
#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>

#pragma once

class Password {
public:
    Password();
    ~Password();
    std::string GenerateRandomPassword(int);
    std::string calcularSHA256(const std::string&);
};

#endif // CLASE1_H