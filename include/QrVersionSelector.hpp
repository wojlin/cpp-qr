/*
The different sizes of QR codes are called versions. 
There are forty versions available. The smallest version is version 1,
and is 21 pixels by 21 pixels in size. Version 2 is 25 pixels by 25 pixels.
The largest version is version 40, and is 177 by 177 pixels in size.
Each version is 4 pixels larger than the previous version.
Each version has a maximum capacity, depending on the mode in use.
In addition, the error correction level restricts the capacity further
*/

#pragma once

#include <string>
#include <stdexcept>

#include "QrModeSelector.hpp"

/**
 * Enum representing the QR error correction levels available for data encoding.
 */
enum class QrErrorCorrectionLevel {
    LOW,        ///< Recovers 7% of data
    MEDIUM,     ///< Recovers 15% of data
    QUARTER,    ///< Recovers 25% of data
    HIGH        ///< Recovers 30% of data
};

/**
 * Exception thrown when the input message is too long to encode in given mode and correction level
 */
class TooLongMessageException : public std::invalid_argument {
public:
    /**
     * Constructs an TooLongMessageException with a specific error message.
     *
     * @param message The error message describing the invalid input.
     */
    explicit TooLongMessageException(const std::string& message);
};

/**
 * Utility class for selecting the appropriate QR version for a given input string length and encoding mode.
 */
class QrVersionSelector {
public:
    /**
     * Determines the QR version for the given input string, error corection level and encoding mode.
     *
     * @param input The input string to evaluate.
     * @param level The error correction level
     * @param mode The encoding mode
     * @return The appropriate version represented as intiger
     * @throws TooLongMessageException if the inpus string is too long to encode
     */
    static int getQrVersion(const std::string& input, QrErrorCorrectionLevel level, QrMode mode);

private:
    // Lookup table representing data capacities for each version, error correction level, and encoding mode
    static const int dataCapacities[40][4][4];

};