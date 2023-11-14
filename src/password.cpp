#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#ifdef __linux__
#include <libsecret/secret.h>
#elif defined(_WIN32)
#include <Windows.h>
#include <Wincrypt.h>
#else
#error "Plataforma no soportada"
#endif

#include "../include/password.h"
#include "../include/exception.h"

Password::Password()
{
}

Password::~Password() {}

std::string Password::GenerateRandomPassword(int size, int type)
{
    try
    {
        // Generate Seed
        std::random_device rd;
        std::default_random_engine generador(rd());
        std::uniform_int_distribution<int> distribucion(0, 255);
        generador.seed(rd());
        const std::string all_characters =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:'\",.<>/?";

        const std::string numeric_characters =
            "0123456789";

        const std::string alpha_characters =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

        const std::string capital_alpha_characters =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        const std::string no_capital_alpha_characters =
            "abcdefghijklmnopqrstuvwxyz";

        const std::string symbol_characters =
            "!@#$%^&*()-_=+[]{}|;:'\",.<>/?";

        std::string password;

        const std::string *charSet = nullptr;
        // Build passwod with the selected type
        switch (type)
        {
        case 1:
            charSet = &all_characters;
            break;
        case 2:
            charSet = &numeric_characters;
            break;
        case 3:
            charSet = &alpha_characters;
            break;
        case 4:
            charSet = &capital_alpha_characters;
            break;
        case 5:
            charSet = &no_capital_alpha_characters;
            break;
        case 6:
            charSet = &symbol_characters;
            break;
        default:
            throw Exception1();
            std::cerr << "Tipo de contraseña no válido." << std::endl;
            return "";
        }
        for (int i = 0; i < size; ++i)
        {
            password += (*charSet)[rd() % charSet->length()];
        }
        if (size <= 0)
        {
            throw Exception2();
            return "";
        }
        if (password.length() <= 0)
        {
            throw Exception3();
            return "";
        }
        return password;
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

std::string Password::computeSHA256(const std::string &entrada)
{
    try
    {
        EVP_MD_CTX *mdctx = EVP_MD_CTX_new();

        if (mdctx == nullptr)
        {
            throw std::runtime_error("Error: cant initialize hash context");
        }

        // Inicializar el contexto de hash para SHA-256
        if (EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1)
        {
            throw std::runtime_error("Error: cant initialize SHA-256 hash");
        }

        // Actualizar el hash con los datos de entrada
        if (EVP_DigestUpdate(mdctx, entrada.c_str(), entrada.length()) != 1)
        {
            throw std::runtime_error("Error: cant update hash with input data");
        }

        unsigned char hash[SHA256_DIGEST_LENGTH];
        unsigned int hashLen = SHA256_DIGEST_LENGTH;

        // Finalizar el hash y obtener el resultado
        if (EVP_DigestFinal_ex(mdctx, hash, &hashLen) != 1)
        {
            throw std::runtime_error("Error: cant end SHA-256 hash");
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
    catch (const std::exception &e)
    {
        // Manejar cualquier excepción estándar aquí
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
    catch (...)
    {
        // Capturar cualquier otra excepción no estándar
        std::cerr << "Error desconocido durante el cálculo de SHA-256" << std::endl;
        return "";
    }
}

std::string Password::generateRandomSalt(void)
{
    try
    {
        const int saltSize = 16;
        unsigned char salt[saltSize];
        if (RAND_bytes(salt, sizeof(salt)) != 1)
        {
            throw Exception4();
            return "";
        }

        // Convertir el salt a una cadena hexadecimal
        std::string saltStr;
        char hexChar[3];
        for (int i = 0; i < saltSize; ++i)
        {
            snprintf(hexChar, sizeof(hexChar), "%02x", salt[i]);
            saltStr += hexChar;
        }

        return saltStr;
    }
    catch (const Exception4 &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
}