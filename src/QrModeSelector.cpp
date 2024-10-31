#include "../include/QrModeSelector.hpp"
#include <algorithm>
#include <cctype>

/**
 * Constructs an InvalidInputMessageException with a specific error message.
 *
 * @param message The error message indicating the invalid input.
 */
InvalidInputMessageException::InvalidInputMessageException(const std::string& message)
    : std::invalid_argument(message) {}

/**
 * Constructs an EmptyInputMessageException with a specific error message.
 *
 * @param message The error message indicating an empty input condition.
 */
EmptyInputMessageException::EmptyInputMessageException(const std::string& message)
    : std::invalid_argument(message) {}

/**
 * Determines the QR encoding mode for the provided input string.
 *
 * @param input The string for which the QR encoding mode is determined.
 * @return The appropriate QrMode for the input string.
 * @throws EmptyInputMessageException if the input is empty.
 * @throws InvalidInputMessageException if the input cannot be encoded in any supported QR mode.
 */
QrMode QrModeSelector::getQrMode(const std::string& input) {

    if(input.empty()) {
        throw EmptyInputMessageException("Encoded message cannot be empty");
    }

    if (QrModeValidator::isNumeric(input)) {
        return QrMode::NumericMode;
    } 
    else if (QrModeValidator::isAlphanumeric(input)) {
        return QrMode::AlphanumericMode;
    }
    else if (QrModeValidator::isByte(input)) {
        return QrMode::ByteMode;
    } 
    else if (QrModeValidator::isKanji(input)) {
        return QrMode::KanjiMode;
    } 

    throw InvalidInputMessageException("Input \"" + input + "\" cannot be encoded in any supported QR mode");
}

/**
 * Checks if a given string contains only numeric characters (0-9).
 *
 * @param str The string to validate as numeric.
 * @return True if the string is numeric; false otherwise.
 */
bool QrModeValidator::isNumeric(const std::string& str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

/**
 * Checks if a given string is alphanumeric, containing characters 0-9, A-Z, and allowed symbols.
 *
 * @param str The string to validate as alphanumeric.
 * @return True if the string is alphanumeric; false otherwise.
 */
bool QrModeValidator::isAlphanumeric(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::isdigit(c) || (c >= 'A' && c <= 'Z') || std::isspace(c) ||
               c == '$' || c == '%' || c == '*' || c == '+' || c == '-' || 
               c == '.' || c == '/' || c == ':';
    });
}

/**
 * Checks if a given string is valid for byte encoding, supporting UTF-8 characters.
 *
 * @param str The string to validate as a byte-encoded string.
 * @return True if the string is a valid UTF-8 byte sequence; false otherwise.
 */
bool QrModeValidator::isByte(const std::string& str) {
    int numBytes = 0;

    for (unsigned char c : str) {
        if (numBytes == 0) {
            if ((c >> 7) == 0) { // 1-byte character
                continue;
            } else if ((c >> 5) == 0b110) { // 2-byte character
                numBytes = 1;
            } else if ((c >> 4) == 0b1110) { // 3-byte character
                numBytes = 2;
            } else if ((c >> 3) == 0b11110) { // 4-byte character
                numBytes = 3;
            } else {
                return false; // Invalid UTF-8 start byte
            }
        } else {
            if ((c >> 6) != 0b10) { // Continuation byte
                return false;
            }
            numBytes--;
        }
    }
    return numBytes == 0; // Ensure all bytes were consumed
}

/**
 * Checks if a given string is valid for Kanji encoding (Shift JIS character encoding).
 *
 * @param str The string to validate as a Kanji-encoded string.
 * @return True if the string is valid for Kanji encoding; false otherwise.
 */
bool QrModeValidator::isKanji(const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        unsigned char c = static_cast<unsigned char>(str[i]);
        
        // Single-byte character (ASCII or Katakana)
        if (c < 0x80 || (c >= 0xa0 && c <= 0xff)) {
            continue;
        }
        
        // Multi-byte character
        if ((c >= 0x81 && c <= 0x9F) || (c >= 0xe0 && c <= 0xef)) {
            // Next byte must be in the valid range for multi-byte characters
            if (i + 1 < str.length()) {
                unsigned char nextByte = static_cast<unsigned char>(str[i + 1]);
                if (!(nextByte >= 0x40 && nextByte <= 0xFC && nextByte != 0x7F)) {
                    return false; // Invalid second byte
                }
                i++; // Skip the next byte
            } else {
                return false; // Incomplete multi-byte character
            }
        } else {
            return false; // Invalid byte
        }
    }
    return true;
}
