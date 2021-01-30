#include <string>
#include <sstream>
#include <memory>
#include <optional>
#include "gtest/gtest.h"
#include "mediasize.h"
#include "mediasizes.h"

using namespace nanaprint;
using namespace std;

// Test getTranslatedName for na_letter_x.5x11in
TEST(MediaSizeTests, testMediaSizeTranslatedName)
{
    MediaSize size("na_letter_8.5x11in", 21590, 27940,
                508, 610, 915, 1016);
    string translatedName = size.getTranslatedName();
    ASSERT_STREQ("Letter", translatedName.c_str());
}

// Test getTranslatedName for size with no translated name
TEST(MediaSizeTests, testMediaSizeNoTranslatedName)
{
    MediaSize size("no_translated_name", 21590, 27940,
                508, 610, 915, 1016);
    string translatedName = size.getTranslatedName();
    ASSERT_STREQ("no_translated_name", translatedName.c_str());
}

// Test insertion operator
TEST(MediaSizeTests, testInsertionOperator)
{
    MediaSize letter("na_letter_8.5x11in", 21590, 27940,
            508, 610, 915, 1016);
    stringstream ss;
    ss << letter;

    ASSERT_STREQ("Letter\n    width = 21590, height = 27940,\n"
        "    top = 1016, bottom = 508,\n    left = 610, right = 915\n",
        ss.str().c_str());
}

// Test insertion operator for borderless media
TEST(MediaSizeTests, testInsertionOperatorBorderless)
{
    MediaSize letter("na_letter_8.5x11in_borderless", 21590, 27940,
            0, 0, 0, 0);
    stringstream ss;
    ss << letter;

    ASSERT_STREQ("Letter    Borderless\n    width = 21590, height = 27940,\n"
        "    top = 0, bottom = 0,\n    left = 0, right = 0\n",
        ss.str().c_str());
}

// Test insertion operator
TEST(MediaSizesTests, testInsertionOperator)
{
    stringstream ss;
    MediaSizes sizes;
    sizes.addSize(MediaSize("na_letter_8.5x11in", 21590, 27940,
            508, 610, 915, 1016));
    sizes.addSize(MediaSize("na_letter_8.5x11in_borderless", 21590, 27940,
            0, 0, 0, 0));

    ss << sizes;

    ASSERT_STREQ("Media Sizes:\nLetter\n    width = 21590, height = 27940,\n"
        "    top = 1016, bottom = 508,\n    left = 610, right = 915\n"
        "Letter    Borderless\n    width = 21590, height = 27940,\n"
        "    top = 0, bottom = 0,\n    left = 0, right = 0\n",
        ss.str().c_str());
}

// Test insertion operator, no sizes
TEST(MediaSizesTests, testInsertionOperatorNoSizes)
{
    stringstream ss;
    MediaSizes sizes;

    ss << sizes;

    ASSERT_STREQ("Media Sizes:\nNone\n",
        ss.str().c_str());
}

// Test find matching MediaSize
TEST(MediaSizesTests, testGetMediaSizeByNameAndBorder)
{
    MediaSizes sizes;
    sizes.addSize(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.addSize(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.addSize(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.addSize(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    auto letterBordered =
        sizes.getMediaSizeByTranslatedNameAndBorder("Letter", false);
    auto a4Borderless =
        sizes.getMediaSizeByTranslatedNameAndBorder("A4", true);
    auto invalidSizeBordered =
        sizes.getMediaSizeByTranslatedNameAndBorder("Legal", false);
    auto invalidSizeBorderless =
        sizes.getMediaSizeByTranslatedNameAndBorder("Legal", true);

    ASSERT_EQ("Letter", letterBordered.value().getTranslatedName());
    ASSERT_FALSE(letterBordered.value().isBorderless());
    ASSERT_EQ("A4", a4Borderless.value().getTranslatedName());
    ASSERT_TRUE(a4Borderless.value().isBorderless());
    ASSERT_EQ(nullopt, invalidSizeBordered);
    ASSERT_EQ(nullopt, invalidSizeBorderless);
}

// Test MediaSizes::operator[]
TEST(MediaSizesTests, testAccessOperator)
{
    MediaSizes sizes;
    sizes.addSize(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.addSize(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.addSize(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.addSize(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));
    
    const MediaSizes cSizes = sizes;

    MediaSize& letter = sizes[0];
    ASSERT_EQ("Letter", letter.getTranslatedName());
    auto letter_borderless = sizes[1];
    ASSERT_EQ("Letter", letter_borderless.getTranslatedName());
    const MediaSize& a4 = cSizes[2];
    ASSERT_EQ("A4", a4.getTranslatedName());
    const auto a4_borderless = cSizes[3];
    ASSERT_EQ("A4", a4_borderless.getTranslatedName());
}

// Test MediaSizes::at
TEST(MediaSizesTests, testAt)
{
    MediaSizes sizes;
    sizes.addSize(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.addSize(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.addSize(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.addSize(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    MediaSize& letter = sizes.at(0);
    ASSERT_EQ("Letter", letter.getTranslatedName());
    auto letter_borderless = sizes.at(1);
    ASSERT_EQ("Letter", letter_borderless.getTranslatedName());
    const MediaSize& a4 = sizes.at(2);
    ASSERT_EQ("A4", a4.getTranslatedName());
    const auto a4_borderless = sizes.at(3);
    ASSERT_EQ("A4", a4_borderless.getTranslatedName());
}

// Test MediaSizes::at index out_of_range
TEST(MediaSizesTests, testAtOutOfRange)
{
    MediaSizes sizes;
    sizes.addSize(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));

    try
    {
        auto ms = sizes.at(1);
        FAIL() << "Expected std::out_of_range";
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("Out of range"));
    }
    catch(...)
    {
        FAIL() << "Expected std::out_of_range";
    }
    try
    {
        const MediaSize& ms = sizes.at(2);
        FAIL() << "Expected std::out_of_range";
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("Out of range"));
    }
    catch(...)
    {
        FAIL() << "Expected std::out_of_range";
    }

    
}