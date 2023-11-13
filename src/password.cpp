#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include <openssl/sha.h>
#include <openssl/evp.h>

#include "../include/password.h"
#include "../include/exception.h"

Password::Password()
{
}

Password::~Password() {}

std::string Password::GenerateRandomPassword(int longitud)
{
    try
    {
        std::random_device rd;
        std::default_random_engine generador(rd());
        std::uniform_int_distribution<int> distribucion(0, 255);
        generador.seed(rd());
        const std::string caracteres =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:'\",.<>/?";

        std::string contraseña;
        for (int i = 0; i < longitud; ++i)
        {
            contraseña += caracteres[rd() % caracteres.length()];
        }
        if (longitud <= 0)
        {
            throw Exception1();
            return "";
        }
        if (contraseña.length() <= 0)
        {
            throw Exception2();
            return "";
        }
        return contraseña;
    }
    catch (const Exception1 &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
    catch (const Exception2 &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
    return "1";
}

std::string Password::calcularSHA256(const std::string &entrada)
{
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();

    if (mdctx == nullptr)
    {
        // Manejar el error, por ejemplo, lanzar una excepción
        throw std::runtime_error("Error al inicializar el contexto de hash");
    }

    // Inicializar el contexto de hash para SHA-256
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1)
    {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Error al inicializar el hash SHA-256");
    }

    // Actualizar el hash con los datos de entrada
    if (EVP_DigestUpdate(mdctx, entrada.c_str(), entrada.length()) != 1)
    {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Error al actualizar el hash con los datos de entrada");
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hashLen = SHA256_DIGEST_LENGTH;

    // Finalizar el hash y obtener el resultado
    if (EVP_DigestFinal_ex(mdctx, hash, &hashLen) != 1)
    {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Error al finalizar el hash SHA-256");
    }

    EVP_MD_CTX_free(mdctx);

    // Convertir el hash binario a una cadena hexadecimal
    std::string resultado;
    for (unsigned int i = 0; i < hashLen; i++)
    {
        char parte[3];
        snprintf(parte, sizeof(parte), "%02x", hash[i]);
        resultado += parte;
    }

    return resultado;
}
