// test_clase1.cpp
#include <gtest/gtest.h>

#define UNIT_TEST
#include "../include/password.h"
#undef UNIT_TEST

#include "../include/exception.h"

TEST(PasswordTest, GeneratePassword)
{
    Password passwordObj;

    // Test for positive length
    EXPECT_FALSE(passwordObj.GenerateRandomPassword(10, 1).empty());

    // Test for zero length
    EXPECT_TRUE(passwordObj.GenerateRandomPassword(0, 1).empty());

    // Test for negative length
    EXPECT_TRUE(passwordObj.GenerateRandomPassword(-5, 1).empty());
    // Expect GenerateRandomPassword to throw Exception1 for negative length
    EXPECT_NO_THROW(passwordObj.GenerateRandomPassword(-5, 1));
    EXPECT_NO_THROW(passwordObj.GenerateRandomPassword(0, 1));
}

TEST(PasswordTest, ComputeSHA256)
{
    Password passwordObj;
    std::string input = "Hola, mundo!";
    std::string expectedHash = "364e7274165cf1ab6359155a5581126f2d3a47178a2d3599a5ba0f6c7bf84e3e";

    // Verify that no exception is thrown
    EXPECT_NO_THROW({
        std::string calculatedHash = passwordObj.computeSHA256(input);
        // Verify that the calculated hash is as expected
        EXPECT_EQ(calculatedHash, expectedHash);
    });
}

TEST(PasswordTest, GenerateRandomSalt)
{
    Password passwordObj;
    EXPECT_FALSE(passwordObj.generateRandomSalt().empty());
}

TEST(AESTest, EncryptionDecryption)
{
    Password passwordObj;
    const std::string key = "0123456789abcdef0123456789abcdef";
    const std::string plaintext = "Hello, this is an example of AES encryption.";

    // Generate a random IV
    const std::string iv = passwordObj.generateRandomIVForTesting();

    // Encrypt the text
    std::string ciphertext = passwordObj.encryptAES(plaintext, key, iv);

    // Decrypt the text
    std::string decryptedtext = passwordObj.decryptAES(ciphertext, key, iv);

    // Verify that the decrypted text is equal to the original text
    EXPECT_EQ(plaintext, decryptedtext);
}
