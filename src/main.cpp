#include "../include/QrModeSelector.hpp"

#include <iostream>
#include <string>

int main()
{
    std::string inputMessage = "abc";
    QrMode mode = QrModeSelector::getQrMode(inputMessage);
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

    return 0;
}