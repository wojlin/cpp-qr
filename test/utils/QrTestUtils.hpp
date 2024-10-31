#pragma once

#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>

/**
 * Generates a random numeric string of the specified length.
 *
 * @param length Length of the desired numeric string.
 * @return Random numeric string consisting of digits 0-9.
 */
std::string generateRandomNumericString(size_t length) 
{
    const std::string characters = "0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[distribution(generator)];
    }
    return randomString;
}

/**
 * Generates a random alphanumeric string with special characters of the specified length.
 *
 * @param length Length of the desired alphanumeric string.
 * @return Random alphanumeric string with characters including A-Z, 0-9, and special characters.
 */
std::string generateRandomAlphanumericString(size_t length) 
{
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ$%*+-./:";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[distribution(generator)];
    }
    randomString += 'A'; // Add a letter to ensure at least one alphabetic character
    return randomString;
}

/**
 * Generates a random UTF-8 encoded byte string of the specified length.
 *
 * The function supports characters ranging from 1-byte to 4-byte sequences and
 * avoids invalid surrogate pairs for UTF-16.
 *
 * @param length Length of the desired byte string.
 * @return Random byte string in UTF-8 encoding.
 */
std::string generateRandomByteString(size_t length) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0x0000, 0x10FFFF);

    std::ostringstream oss;
    size_t generatedLength = 0;
    while (generatedLength < length) {
        int codePoint = distribution(generator);

        // Skip surrogate pair range (for UTF-16, which is invalid in UTF-8)
        if (codePoint >= 0xD800 && codePoint <= 0xDFFF) continue;

        if (codePoint <= 0x7F) { // 1-byte sequence
            oss << static_cast<char>(codePoint);
            ++generatedLength;
        }
        else if (codePoint <= 0x7FF) { // 2-byte sequence
            oss << static_cast<char>(0xC0 | ((codePoint >> 6) & 0x1F));
            oss << static_cast<char>(0x80 | (codePoint & 0x3F));
            generatedLength += 2;
        }
        else if (codePoint <= 0xFFFF) { // 3-byte sequence
            oss << static_cast<char>(0xE0 | ((codePoint >> 12) & 0x0F));
            oss << static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F));
            oss << static_cast<char>(0x80 | (codePoint & 0x3F));
            generatedLength += 3;
        }
        else if (codePoint <= 0x10FFFF) { // 4-byte sequence
            oss << static_cast<char>(0xF0 | ((codePoint >> 18) & 0x07));
            oss << static_cast<char>(0x80 | ((codePoint >> 12) & 0x3F));
            oss << static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F));
            oss << static_cast<char>(0x80 | (codePoint & 0x3F));
            generatedLength += 4;
        }
    }
    oss << "©"; // Add a copyright symbol at the end for illustration
    return oss.str();
}

/**
 * Generates a random Kanji string using Shift-JIS encoding of the specified length.
 *
 * The characters are constructed with valid Shift-JIS first and second bytes to represent
 * Kanji characters.
 *
 * @param length Length of the desired Kanji string.
 * @return Random Kanji string in Shift-JIS encoding.
 */
std::string generateRandomKanjiString(size_t length) {
    std::string input;

    // Seed the randomness
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate the string with length x based on valid Shift JIS characters
    for (size_t i = 0; i < length; ++i) {
        // Randomly choose a first byte from 0x81 to 0xFC
        uint8_t first_byte = 0x81 + std::rand() % (0xFC - 0x81 + 1);
        // Randomly choose a second byte from 0x40 to 0x4F
        uint8_t second_byte = 0x40 + std::rand() % (0x4F - 0x40 + 1);
        
        // Append the selected bytes to the input string
        input += static_cast<char>(first_byte);
        input += static_cast<char>(second_byte);
    }
    return input;
}
