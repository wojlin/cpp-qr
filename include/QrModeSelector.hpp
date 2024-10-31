/*
A QR code encodes a string of text. The QR code standard has four
modes for encoding text: numeric, alphanumeric, byte, and Kanji.
Each mode encodes the text as a string of bits (1s and 0s),
but each mode uses a different method for converting the text into bits.
Each method is optimized to generate the shortest possible string
of bits for that data type. This code identify which mode to use. 
*/


#pragma once

#include <string>
#include <stdexcept>

/**
 * Enum representing the QR encoding modes available for data encoding.
 */
enum class QrMode {
    NumericMode,        ///< Numeric encoding mode (0-9).
    AlphanumericMode,   ///< Alphanumeric encoding mode (0-9, A-Z, and specific symbols).
    ByteMode,           ///< Byte encoding mode for binary data.
    KanjiMode           ///< Kanji encoding mode for Shift JIS character encoding.
};

/**
 * Exception thrown when the input message is invalid for the specified QR mode.
 */
class InvalidInputMessageException : public std::invalid_argument {
public:
    /**
     * Constructs an InvalidInputMessageException with a specific error message.
     *
     * @param message The error message describing the invalid input.
     */
    explicit InvalidInputMessageException(const std::string& message);
};

/**
 * Exception thrown when the input message is empty.
 */
class EmptyInputMessageException : public std::invalid_argument {
public:
    /**
     * Constructs an EmptyInputMessageException with a specific error message.
     *
     * @param message The error message describing the empty input condition.
     */
    explicit EmptyInputMessageException(const std::string& message);
};

/**
 * Utility class for validating if a given string conforms to specific QR encoding modes.
 */
class QrModeValidator {
public:
    /**
     * Checks if a string conforms to the numeric mode (only 0-9).
     *
     * @param str The string to validate.
     * @return True if the string is numeric; false otherwise.
     */
    static bool isNumeric(const std::string& str);

    /**
     * Checks if a string conforms to the alphanumeric mode (0-9, A-Z, and symbols $%*+-./:).
     *
     * @param str The string to validate.
     * @return True if the string is alphanumeric; false otherwise.
     */
    static bool isAlphanumeric(const std::string& str);

    /**
     * Checks if a string conforms to byte mode (can contain any binary data).
     *
     * @param str The string to validate.
     * @return True if the string is valid for byte mode; false otherwise.
     */
    static bool isByte(const std::string& str);

    /**
     * Checks if a string conforms to the kanji mode (Shift JIS encoding).
     *
     * @param str The string to validate.
     * @return True if the string is valid for kanji mode; false otherwise.
     */
    static bool isKanji(const std::string& str);
};

/**
 * Utility class for selecting the appropriate QR mode for a given input string.
 */
class QrModeSelector {
public:
    /**
     * Determines the QR encoding mode for the given input string.
     *
     * @param input The input string to evaluate.
     * @return The appropriate QrMode for the input string.
     * @throws InvalidInputMessageException if the input does not match any QR mode.
     * @throws EmptyInputMessageException if the input string is empty.
     */
    static QrMode getQrMode(const std::string& input);
};
