#include "../include/QrModeSelector.hpp"
#include "../include/QrVersionSelector.hpp"

#include <iostream>
#include <string>

void printSelectedMode(QrMode mode)
{
    if(mode == QrMode::NumericMode)
    {
        std::cout << "deteced numeric mode" << std::endl;
    }
    else if(mode == QrMode::AlphanumericMode)
    {
        std::cout << "deteced alphanumeric mode" << std::endl;
    }
    else if(mode == QrMode::ByteMode)
    {
        std::cout << "deteced byte mode" << std::endl;
    }
    else if(mode == QrMode::KanjiMode)
    {
        std::cout << "deteced kanji mode" << std::endl;
    }
}

void printSelectedErrorCorrectionLevel(QrErrorCorrectionLevel level)
{
    if(level == QrErrorCorrectionLevel::LOW)
    {
        std::cout << "using low error correction level (7%)" << std::endl;
    }
    else if(level == QrErrorCorrectionLevel::MEDIUM)
    {
        std::cout << "using medium error correction level (15%)" << std::endl;
    }
    else if(level == QrErrorCorrectionLevel::QUARTER)
    {
        std::cout << "using quarter error correction level (25%)" << std::endl;
    }
    else if(level == QrErrorCorrectionLevel::HIGH)
    {
        std::cout << "using high error correction level (30%)" << std::endl;
    }
}

void printSelectedVersion(int version)
{
    std::cout << "using qr version " << version << std::endl;
}

int main()
{
    std::string inputMessage = "HELLO WORLD";
    QrErrorCorrectionLevel level = QrErrorCorrectionLevel::MEDIUM;

    // STEP 1 - data analisys //
    QrMode mode = QrModeSelector::getQrMode(inputMessage);
    int version = QrVersionSelector::getQrVersion(inputMessage, level, mode);
    printSelectedMode(mode);
    printSelectedErrorCorrectionLevel(level);
    printSelectedVersion(version);

    // STEP 2 - data encoding //

    return 0;
}