#include "../utils/QrTestUtils.hpp"
#include "../../include/QrModeSelector.hpp"
#include <gtest/gtest.h>

/**
 * @brief Test fixture for QrModeSelector. Provides utility methods for testing QR modes.
 */
class QrModeSelectorTest : public ::testing::Test {
protected:
    /**
     * @brief Checks if the input string is correctly identified as expectedMode.
     * @param expectedMode Expected QR mode for the input.
     * @param input Input string to be tested.
     */
    void checkValidMode(QrMode expectedMode, const std::string& input) {
        QrMode receivedMode = QrModeSelector::getQrMode(input);
        ASSERT_EQ(receivedMode, expectedMode) << "testing \"" << input << "\" which should be valid input";
    }

    /**
     * @brief Checks if the input string is not identified as expectedMode.
     * @param expectedMode Expected QR mode that the input should not match.
     * @param input Input string to be tested.
     */
    void checkInvalidMode(QrMode expectedMode, const std::string& input) {
        QrMode receivedMode = QrModeSelector::getQrMode(input);
        ASSERT_NE(receivedMode, expectedMode) << "testing \"" << input << "\" which should be invalid input";
    }

    /**
     * @brief Generates random input strings and validates if each matches the expected QR mode.
     * @param amount Number of random strings to generate.
     * @param minLength Minimum length of generated strings.
     * @param maxLength Maximum length of generated strings.
     * @param charsetGenerator Function to generate random characters for the string.
     * @param expectedMode Expected QR mode for the generated strings.
     */
    void generateRandomInputStrings(unsigned int amount, int minLength, int maxLength, std::function<std::string(size_t)> charsetGenerator, QrMode expectedMode) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> distr(minLength, maxLength);

        for (int x = 0; x <= amount; ++x) {
            int length = distr(eng);
            std::string inputString = charsetGenerator(length);
            checkValidMode(expectedMode, inputString);
        }
    }
};

// Test cases for each QR mode with both fixed and random inputs.

TEST_F(QrModeSelectorTest, TestNumericModeFixed) { 
    for (int x = 0; x <= 1000000; ++x) {
        checkValidMode(QrMode::NumericMode, std::to_string(x));
    }
    for (int x = -1000000; x <= -1; ++x) {
        checkInvalidMode(QrMode::NumericMode, std::to_string(x));
    }
    checkInvalidMode(QrMode::NumericMode, "abcdefg");
    checkInvalidMode(QrMode::NumericMode, "ABCDEFG");
    EXPECT_THROW(QrModeSelector::getQrMode(""), EmptyInputMessageException);
}

TEST_F(QrModeSelectorTest, TestNumericModeRandom) { 
    generateRandomInputStrings(10000, 10, 100, generateRandomNumericString, QrMode::NumericMode);
}

TEST_F(QrModeSelectorTest, TestAlphanumericModeFixed) { 
    for (char x = 'A'; x <= 'Z'; ++x) {
        checkValidMode(QrMode::AlphanumericMode, std::string() + x);
    }
    checkValidMode(QrMode::AlphanumericMode, "HTTPS://GOOGLE.COM");
    checkInvalidMode(QrMode::AlphanumericMode, "abcdefg");
    checkInvalidMode(QrMode::AlphanumericMode, "https://google.com");
    EXPECT_THROW(QrModeSelector::getQrMode(""), EmptyInputMessageException);
}

TEST_F(QrModeSelectorTest, TestAlphanumericModeRandom) { 
    generateRandomInputStrings(10000, 10, 100, generateRandomAlphanumericString, QrMode::AlphanumericMode);
}

TEST_F(QrModeSelectorTest, TestByteModeFixed) { 
    for (char x = 'a'; x <= 'z'; ++x) {
        checkValidMode(QrMode::ByteMode, std::string() + x);
    }
    checkValidMode(QrMode::ByteMode, "https://google.com");
    checkInvalidMode(QrMode::ByteMode, "HTTPS://GOOGLE.COM");
    EXPECT_THROW(QrModeSelector::getQrMode(""), EmptyInputMessageException);
}

TEST_F(QrModeSelectorTest, TestByteModeRandom) {  
    generateRandomInputStrings(10000, 10, 100, generateRandomByteString, QrMode::ByteMode);
}

TEST_F(QrModeSelectorTest, TestKanjiModeFixed) { 
    for (uint8_t first_byte = 0x81; first_byte <= 0xFC; ++first_byte) {
        for (uint8_t second_byte = 0x40; second_byte <= 0x4F; ++second_byte) {
            std::string input = {static_cast<char>(first_byte), static_cast<char>(second_byte)};
            checkValidMode(QrMode::KanjiMode, input);
        }
    }
    checkInvalidMode(QrMode::KanjiMode, "\xF0\x9F\x98\x81");
    checkInvalidMode(QrMode::KanjiMode, "abcdefgh");
    EXPECT_THROW(QrModeSelector::getQrMode(""), EmptyInputMessageException);
}

TEST_F(QrModeSelectorTest, TestKanjiModeRandom) {  
    generateRandomInputStrings(10000, 10, 100, generateRandomKanjiString, QrMode::KanjiMode);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
