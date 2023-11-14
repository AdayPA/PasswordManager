#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/conf.h>
#include <openssl/err.h>

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
    catch (const Exception5 &e)
    {
        //
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
    catch (...)
    {
        // No standar error
        std::cerr << "Unknown error during SHA-256 calc" << std::endl;
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

std::string Password::generateRandomIV(void)
{
    const int ivSize = 16; // Tamaño del IV para AES-256-CBC
    std::string iv(ivSize, '\0');
    if (RAND_bytes(reinterpret_cast<unsigned char *>(&iv[0]), ivSize) != 1)
    {
        throw std::runtime_error("Error al generar el IV aleatorio.");
    }
    return iv;
}

std::string Password::encryptAES(const std::string &plaintext, const std::string &key, const std::string &iv)
{
    // AES-256-CBC
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    const EVP_CIPHER *cipher = EVP_aes_256_cbc();
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    try
    {
        if (!EVP_EncryptInit_ex(ctx, cipher, NULL, (const unsigned char *)key.c_str(), (const unsigned char *)iv.c_str()))
        {
            throw std::runtime_error("Error al inicializar el contexto de cifrado.");
        }

        std::string ciphertext(plaintext.size() + EVP_CIPHER_block_size(cipher), '\0');

        int len;
        if (!EVP_EncryptUpdate(ctx, (unsigned char *)&ciphertext[0], &len, (const unsigned char *)plaintext.c_str(), plaintext.size()))
        {
            throw std::runtime_error("Error al cifrar.");
        }

        int final_len;
        if (!EVP_EncryptFinal_ex(ctx, (unsigned char *)&ciphertext[len], &final_len))
        {
            throw std::runtime_error("Error al finalizar el cifrado.");
        }

        EVP_CIPHER_CTX_free(ctx);

        ciphertext.resize(len + final_len);
        return ciphertext;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Excepción en encryptAES: " << e.what() << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        throw;
    }
}

std::string Password::decryptAES(const std::string& ciphertext, const std::string& key, const std::string& iv) {
// Función para descifrar utilizando AES-256-CBC
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    const EVP_CIPHER* cipher = EVP_aes_256_cbc();
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    try {
        if (!EVP_DecryptInit_ex(ctx, cipher, NULL, (const unsigned char*)key.c_str(), (const unsigned char*)iv.c_str())) {
            throw std::runtime_error("Error al inicializar el contexto de descifrado.");
        }

        std::string decryptedtext(ciphertext.size(), '\0');

        int len;
        if (!EVP_DecryptUpdate(ctx, (unsigned char*)&decryptedtext[0], &len, (const unsigned char*)ciphertext.c_str(), ciphertext.size())) {
            throw std::runtime_error("Error al descifrar.");
        }

        int final_len;
        if (!EVP_DecryptFinal_ex(ctx, (unsigned char*)&decryptedtext[len], &final_len)) {
            throw std::runtime_error("Error al finalizar el descifrado.");
        }

        EVP_CIPHER_CTX_free(ctx);

        decryptedtext.resize(len + final_len);
        return decryptedtext;
    } catch (const std::exception& e) {
        std::cerr << "Excepción en decryptAES: " << e.what() << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        throw;
    }
}