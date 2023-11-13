// test_clase1.cpp
#include <gtest/gtest.h>
#include "../include/password.h"

// Prueba para el método metodo1 de Clase1
TEST(Clase1Test, Metodo1Test) {
    Password c;
    EXPECT_EQ(c.metodo1(), 42);
}

// Puedes agregar más pruebas según sea necesario
