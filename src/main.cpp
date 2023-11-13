// main.cpp
#include <iostream>
#include <stdexcept>

#include "../include/password.h"



int main() {

    Password psswd1;

    
    std::cout<< psswd1.GenerateRandomPassword(0) <<std::endl;
    std::cout<< psswd1.GenerateRandomPassword(20) <<std::endl;
    std::cout<< psswd1.GenerateRandomPassword(20) <<std::endl;
    std::cout<< psswd1.calcularSHA256("Hola, mundo!") <<std::endl;

    std::cout << psswd1.calcularSHA256("aasdasd")<< std::endl;

    return 0;
}
