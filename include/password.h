// password.h
#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>

#pragma once

class Password
{
public:
    Password();
    ~Password();
    std::string GenerateRandomPassword(int, int);
    std::string computeSHA256(const std::string &);
    std::string encryptAES(const std::string &, const std::string &);
    std::string decryptAES(const std::string &, const std::string &);
    std::string generateRandomSalt(void);

private:
    std::string deriveKeyFromPassword(const std::string &, const std::string &);
};
#endif // password.h