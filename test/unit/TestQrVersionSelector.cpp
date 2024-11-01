#include "../utils/QrTestUtils.hpp"
#include "../../include/QrModeSelector.hpp"
#include "../../include/QrVersionSelector.hpp"
#include <gtest/gtest.h>

class QrVersionSelectorTest : public ::testing::Test {
protected:
    std::string createTestString(int length)
    {
        return std::string(length, '0');
    }

    void checkVersion(int stringLength, QrErrorCorrectionLevel level, QrMode mode, int expectedVersion, bool shouldThrow)
    {   
        if(shouldThrow)
        {
            EXPECT_THROW(QrVersionSelector::getQrVersion(createTestString(stringLength), level, mode), TooLongMessageException);
        }
        else
        {
            int version;
            EXPECT_NO_THROW({version = QrVersionSelector::getQrVersion(createTestString(stringLength), level, mode);});
            ASSERT_EQ(version, expectedVersion) 
            << "expected version: " << expectedVersion 
            << " actual: " << version 
            << " for string of length: " << stringLength 
            << " with error correction: " << (int) level
            << " and mode: " << (int) mode;
        } 
    }
};


TEST_F(QrVersionSelectorTest, TestMessageMinimumInputLength) {
    checkVersion(1, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 1, false); // 1 character for Numeric
    checkVersion(1, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 1, false); // 1 character for Alphanumeric
    checkVersion(1, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 1, false); // 1 byte for Byte
    checkVersion(1, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 1, false); // 1 character for Kanji
}


TEST_F(QrVersionSelectorTest, TestVersion1) {
    checkVersion(41, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 1, false);
    checkVersion(25, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 1, false); 
    checkVersion(17, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 1, false);
    checkVersion(10, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 1, false);

    checkVersion(34, QrErrorCorrectionLevel::MEDIUM, QrMode::NumericMode, 1, false);
    checkVersion(20, QrErrorCorrectionLevel::MEDIUM, QrMode::AlphanumericMode, 1, false); 
    checkVersion(14, QrErrorCorrectionLevel::MEDIUM, QrMode::ByteMode, 1, false);
    checkVersion(8, QrErrorCorrectionLevel::MEDIUM, QrMode::KanjiMode, 1, false);

    checkVersion(27, QrErrorCorrectionLevel::QUARTER, QrMode::NumericMode, 1, false);
    checkVersion(16, QrErrorCorrectionLevel::QUARTER, QrMode::AlphanumericMode, 1, false); 
    checkVersion(11, QrErrorCorrectionLevel::QUARTER, QrMode::ByteMode, 1, false);
    checkVersion(7, QrErrorCorrectionLevel::QUARTER, QrMode::KanjiMode, 1, false);

    checkVersion(17, QrErrorCorrectionLevel::HIGH, QrMode::NumericMode, 1, false);
    checkVersion(10, QrErrorCorrectionLevel::HIGH, QrMode::AlphanumericMode, 1, false); 
    checkVersion(7, QrErrorCorrectionLevel::HIGH, QrMode::ByteMode, 1, false);
    checkVersion(4, QrErrorCorrectionLevel::HIGH, QrMode::KanjiMode, 1, false);
}

TEST_F(QrVersionSelectorTest, TestVersion2) {
    checkVersion(77, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 2, false);
    checkVersion(47, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 2, false); 
    checkVersion(32, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 2, false);
    checkVersion(20, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 2, false);

    checkVersion(63, QrErrorCorrectionLevel::MEDIUM, QrMode::NumericMode, 2, false);
    checkVersion(38, QrErrorCorrectionLevel::MEDIUM, QrMode::AlphanumericMode, 2, false); 
    checkVersion(26, QrErrorCorrectionLevel::MEDIUM, QrMode::ByteMode, 2, false);
    checkVersion(16, QrErrorCorrectionLevel::MEDIUM, QrMode::KanjiMode, 2, false);

    checkVersion(48, QrErrorCorrectionLevel::QUARTER, QrMode::NumericMode, 2, false);
    checkVersion(29, QrErrorCorrectionLevel::QUARTER, QrMode::AlphanumericMode, 2, false); 
    checkVersion(20, QrErrorCorrectionLevel::QUARTER, QrMode::ByteMode, 2, false);
    checkVersion(12, QrErrorCorrectionLevel::QUARTER, QrMode::KanjiMode, 2, false);

    checkVersion(34, QrErrorCorrectionLevel::HIGH, QrMode::NumericMode, 2, false);
    checkVersion(20, QrErrorCorrectionLevel::HIGH, QrMode::AlphanumericMode, 2, false); 
    checkVersion(14, QrErrorCorrectionLevel::HIGH, QrMode::ByteMode, 2, false);
    checkVersion(8, QrErrorCorrectionLevel::HIGH, QrMode::KanjiMode, 2, false);
}

TEST_F(QrVersionSelectorTest, TestVersion3) {
    checkVersion(127, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 3, false);
    checkVersion(77, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 3, false); 
    checkVersion(53, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 3, false);
    checkVersion(32, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 3, false);

    checkVersion(101, QrErrorCorrectionLevel::MEDIUM, QrMode::NumericMode, 3, false);
    checkVersion(61, QrErrorCorrectionLevel::MEDIUM, QrMode::AlphanumericMode, 3, false); 
    checkVersion(42, QrErrorCorrectionLevel::MEDIUM, QrMode::ByteMode, 3, false);
    checkVersion(26, QrErrorCorrectionLevel::MEDIUM, QrMode::KanjiMode, 3, false);

    checkVersion(77, QrErrorCorrectionLevel::QUARTER, QrMode::NumericMode, 3, false);
    checkVersion(47, QrErrorCorrectionLevel::QUARTER, QrMode::AlphanumericMode, 3, false); 
    checkVersion(32, QrErrorCorrectionLevel::QUARTER, QrMode::ByteMode, 3, false);
    checkVersion(20, QrErrorCorrectionLevel::QUARTER, QrMode::KanjiMode, 3, false);

    checkVersion(58, QrErrorCorrectionLevel::HIGH, QrMode::NumericMode, 3, false);
    checkVersion(35, QrErrorCorrectionLevel::HIGH, QrMode::AlphanumericMode, 3, false); 
    checkVersion(24, QrErrorCorrectionLevel::HIGH, QrMode::ByteMode, 3, false);
    checkVersion(15, QrErrorCorrectionLevel::HIGH, QrMode::KanjiMode, 3, false);
}

TEST_F(QrVersionSelectorTest, TestVersion4) {
    checkVersion(187, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 4, false);
    checkVersion(114, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 4, false); 
    checkVersion(78, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 4, false);
    checkVersion(48, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 4, false);

    checkVersion(149, QrErrorCorrectionLevel::MEDIUM, QrMode::NumericMode, 4, false);
    checkVersion(90, QrErrorCorrectionLevel::MEDIUM, QrMode::AlphanumericMode, 4, false); 
    checkVersion(62, QrErrorCorrectionLevel::MEDIUM, QrMode::ByteMode, 4, false);
    checkVersion(38, QrErrorCorrectionLevel::MEDIUM, QrMode::KanjiMode, 4, false);

    checkVersion(111, QrErrorCorrectionLevel::QUARTER, QrMode::NumericMode, 4, false);
    checkVersion(67, QrErrorCorrectionLevel::QUARTER, QrMode::AlphanumericMode, 4, false); 
    checkVersion(46, QrErrorCorrectionLevel::QUARTER, QrMode::ByteMode, 4, false);
    checkVersion(28, QrErrorCorrectionLevel::QUARTER, QrMode::KanjiMode, 4, false);

    checkVersion(82, QrErrorCorrectionLevel::HIGH, QrMode::NumericMode, 4, false);
    checkVersion(50, QrErrorCorrectionLevel::HIGH, QrMode::AlphanumericMode, 4, false); 
    checkVersion(34, QrErrorCorrectionLevel::HIGH, QrMode::ByteMode, 4, false);
    checkVersion(21, QrErrorCorrectionLevel::HIGH, QrMode::KanjiMode, 4, false);
}

TEST_F(QrVersionSelectorTest, TestVersion5) {
    checkVersion(255, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 5, false);
    checkVersion(154, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 5, false); 
    checkVersion(106, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 5, false);
    checkVersion(65, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 5, false);

    checkVersion(202, QrErrorCorrectionLevel::MEDIUM, QrMode::NumericMode, 5, false);
    checkVersion(122, QrErrorCorrectionLevel::MEDIUM, QrMode::AlphanumericMode, 5, false); 
    checkVersion(84, QrErrorCorrectionLevel::MEDIUM, QrMode::ByteMode, 5, false);
    checkVersion(52, QrErrorCorrectionLevel::MEDIUM, QrMode::KanjiMode, 5, false);

    checkVersion(144, QrErrorCorrectionLevel::QUARTER, QrMode::NumericMode, 5, false);
    checkVersion(87, QrErrorCorrectionLevel::QUARTER, QrMode::AlphanumericMode, 5, false); 
    checkVersion(60, QrErrorCorrectionLevel::QUARTER, QrMode::ByteMode, 5, false);
    checkVersion(37, QrErrorCorrectionLevel::QUARTER, QrMode::KanjiMode, 5, false);

    checkVersion(106, QrErrorCorrectionLevel::HIGH, QrMode::NumericMode, 5, false);
    checkVersion(64, QrErrorCorrectionLevel::HIGH, QrMode::AlphanumericMode, 5, false); 
    checkVersion(44, QrErrorCorrectionLevel::HIGH, QrMode::ByteMode, 5, false);
    checkVersion(27, QrErrorCorrectionLevel::HIGH, QrMode::KanjiMode, 5, false);
}

TEST_F(QrVersionSelectorTest, TestVersion6) {
    checkVersion(322, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 6, false);
    checkVersion(195, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 6, false); 
    checkVersion(134, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 6, false);
    checkVersion(82, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 6, false);

    checkVersion(255, QrErrorCorrectionLevel::MEDIUM, QrMode::NumericMode, 6, false);
    checkVersion(154, QrErrorCorrectionLevel::MEDIUM, QrMode::AlphanumericMode, 6, false); 
    checkVersion(106, QrErrorCorrectionLevel::MEDIUM, QrMode::ByteMode, 6, false);
    checkVersion(65, QrErrorCorrectionLevel::MEDIUM, QrMode::KanjiMode, 6, false);

    checkVersion(178, QrErrorCorrectionLevel::QUARTER, QrMode::NumericMode, 6, false);
    checkVersion(108, QrErrorCorrectionLevel::QUARTER, QrMode::AlphanumericMode, 6, false); 
    checkVersion(74, QrErrorCorrectionLevel::QUARTER, QrMode::ByteMode, 6, false);
    checkVersion(45, QrErrorCorrectionLevel::QUARTER, QrMode::KanjiMode, 6, false);

    checkVersion(139, QrErrorCorrectionLevel::HIGH, QrMode::NumericMode, 6, false);
    checkVersion(84, QrErrorCorrectionLevel::HIGH, QrMode::AlphanumericMode, 6, false); 
    checkVersion(58, QrErrorCorrectionLevel::HIGH, QrMode::ByteMode, 6, false);
    checkVersion(36, QrErrorCorrectionLevel::HIGH, QrMode::KanjiMode, 6, false);
}

TEST_F(QrVersionSelectorTest, TestVersion7) {
    checkVersion(370, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 7, false);
    checkVersion(224, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 7, false); 
    checkVersion(154, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 7, false);
    checkVersion(95, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 7, false);

    checkVersion(293, QrErrorCorrectionLevel::MEDIUM, QrMode::NumericMode, 7, false);
    checkVersion(178, QrErrorCorrectionLevel::MEDIUM, QrMode::AlphanumericMode, 7, false); 
    checkVersion(122, QrErrorCorrectionLevel::MEDIUM, QrMode::ByteMode, 7, false);
    checkVersion(75, QrErrorCorrectionLevel::MEDIUM, QrMode::KanjiMode, 7, false);

    checkVersion(207, QrErrorCorrectionLevel::QUARTER, QrMode::NumericMode, 7, false);
    checkVersion(125, QrErrorCorrectionLevel::QUARTER, QrMode::AlphanumericMode, 7, false); 
    checkVersion(86, QrErrorCorrectionLevel::QUARTER, QrMode::ByteMode, 7, false);
    checkVersion(53, QrErrorCorrectionLevel::QUARTER, QrMode::KanjiMode, 7, false);

    checkVersion(154, QrErrorCorrectionLevel::HIGH, QrMode::NumericMode, 7, false);
    checkVersion(93, QrErrorCorrectionLevel::HIGH, QrMode::AlphanumericMode, 7, false); 
    checkVersion(64, QrErrorCorrectionLevel::HIGH, QrMode::ByteMode, 7, false);
    checkVersion(39, QrErrorCorrectionLevel::HIGH, QrMode::KanjiMode, 7, false);
}

TEST_F(QrVersionSelectorTest, TestVersion8) {
    checkVersion(461, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 8, false);
    checkVersion(279, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 8, false); 
    checkVersion(192, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 8, false);
    checkVersion(118, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 8, false);

    checkVersion(365, QrErrorCorrectionLevel::MEDIUM, QrMode::NumericMode, 8, false);
    checkVersion(221, QrErrorCorrectionLevel::MEDIUM, QrMode::AlphanumericMode, 8, false); 
    checkVersion(152, QrErrorCorrectionLevel::MEDIUM,  QrMode::ByteMode, 8, false);
    checkVersion(93, QrErrorCorrectionLevel::MEDIUM, QrMode::KanjiMode, 8, false);

    checkVersion(259, QrErrorCorrectionLevel::QUARTER, QrMode::NumericMode, 8, false);
    checkVersion(157, QrErrorCorrectionLevel::QUARTER, QrMode::AlphanumericMode, 8, false); 
    checkVersion(108, QrErrorCorrectionLevel::QUARTER, QrMode::ByteMode, 8, false);
    checkVersion(66, QrErrorCorrectionLevel::QUARTER, QrMode::KanjiMode, 8, false);

    checkVersion(202, QrErrorCorrectionLevel::HIGH, QrMode::NumericMode, 8, false);
    checkVersion(122, QrErrorCorrectionLevel::HIGH, QrMode::AlphanumericMode, 8, false); 
    checkVersion(84, QrErrorCorrectionLevel::HIGH, QrMode::ByteMode, 8, false);
    checkVersion(52, QrErrorCorrectionLevel::HIGH, QrMode::KanjiMode, 8, false);
}

TEST_F(QrVersionSelectorTest, TestVersion9) {
    checkVersion(552, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 9, false);
    checkVersion(335, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 9, false); 
    checkVersion(230, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 9, false);
    checkVersion(141, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 9, false);

    checkVersion(432, QrErrorCorrectionLevel::MEDIUM, QrMode::NumericMode, 9, false);
    checkVersion(262, QrErrorCorrectionLevel::MEDIUM, QrMode::AlphanumericMode, 9, false); 
    checkVersion(180, QrErrorCorrectionLevel::MEDIUM, QrMode::ByteMode, 9, false);
    checkVersion(111, QrErrorCorrectionLevel::MEDIUM, QrMode::KanjiMode, 9, false);

    checkVersion(312, QrErrorCorrectionLevel::QUARTER, QrMode::NumericMode, 9, false);
    checkVersion(189, QrErrorCorrectionLevel::QUARTER, QrMode::AlphanumericMode, 9, false); 
    checkVersion(130, QrErrorCorrectionLevel::QUARTER, QrMode::ByteMode, 9, false);
    checkVersion(80, QrErrorCorrectionLevel::QUARTER, QrMode::KanjiMode, 9, false);

    checkVersion(235, QrErrorCorrectionLevel::HIGH, QrMode::NumericMode, 9, false);
    checkVersion(143, QrErrorCorrectionLevel::HIGH, QrMode::AlphanumericMode, 9, false); 
    checkVersion(98, QrErrorCorrectionLevel::HIGH, QrMode::ByteMode, 9, false);
    checkVersion(60, QrErrorCorrectionLevel::HIGH, QrMode::KanjiMode, 9, false);
}

TEST_F(QrVersionSelectorTest, TestVersion10) {
    checkVersion(652, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 10, false);
    checkVersion(395, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 10, false); 
    checkVersion(271, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 10, false);
    checkVersion(167, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 10, false);

    checkVersion(513, QrErrorCorrectionLevel::MEDIUM, QrMode::NumericMode, 10, false);
    checkVersion(311, QrErrorCorrectionLevel::MEDIUM, QrMode::AlphanumericMode, 10, false); 
    checkVersion(213, QrErrorCorrectionLevel::MEDIUM, QrMode::ByteMode, 10, false);
    checkVersion(131, QrErrorCorrectionLevel::MEDIUM, QrMode::KanjiMode, 10, false);

    checkVersion(364, QrErrorCorrectionLevel::QUARTER, QrMode::NumericMode, 10, false);
    checkVersion(221, QrErrorCorrectionLevel::QUARTER, QrMode::AlphanumericMode, 10, false); 
    checkVersion(151, QrErrorCorrectionLevel::QUARTER, QrMode::ByteMode, 10, false);
    checkVersion(93, QrErrorCorrectionLevel::QUARTER, QrMode::KanjiMode, 10, false);

    checkVersion(288, QrErrorCorrectionLevel::HIGH, QrMode::NumericMode, 10, false);
    checkVersion(174, QrErrorCorrectionLevel::HIGH, QrMode::AlphanumericMode, 10, false); 
    checkVersion(119, QrErrorCorrectionLevel::HIGH, QrMode::ByteMode, 10, false);
    checkVersion(74, QrErrorCorrectionLevel::HIGH, QrMode::KanjiMode, 10, false);
}


TEST_F(QrVersionSelectorTest, TestMessageMaxInputLength) { 

    // biggest version for numeric mode and low quality error correction
    checkVersion(7089, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 40, false);

    // biggest version for alphanumeric mode and low quality error correction
    checkVersion(4296, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 40, false);

    // biggest version for byte mode and low quality error correction
    checkVersion(2953, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 40, false);

    // biggest version for kanji mode and low quality error correction
    checkVersion(1817, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 40, false);



    // no version for numeric mode and low quality error correction
    checkVersion(7090, QrErrorCorrectionLevel::LOW, QrMode::NumericMode, 0, true);

    //no version for alphanumeric mode and low quality error correction
    checkVersion(4297, QrErrorCorrectionLevel::LOW, QrMode::AlphanumericMode, 0, true);

    // no version for byte mode and low quality error correction
    checkVersion(2954, QrErrorCorrectionLevel::LOW, QrMode::ByteMode, 0, true);

    // no version for kanji mode and low quality error correction
    checkVersion(1818, QrErrorCorrectionLevel::LOW, QrMode::KanjiMode, 0, true);



}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}