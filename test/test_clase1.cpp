// test_clase1.cpp
#include <gtest/gtest.h>
#include "../include/clase1.h"

// Prueba para el método metodo1 de Clase1
TEST(Clase1Test, Metodo1Test) {
    Clase1 c;
    EXPECT_EQ(c.metodo1(), 42);
}

// Puedes agregar más pruebas según sea necesario
