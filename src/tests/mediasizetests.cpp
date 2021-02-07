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
    sizes.push_back(MediaSize("na_letter_8.5x11in", 21590, 27940,
            508, 610, 915, 1016));
    sizes.push_back(MediaSize("na_letter_8.5x11in_borderless", 21590, 27940,
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
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    auto letterBordered =
        sizes.get_media_size_by_translated_name_and_border("Letter", false);
    auto a4Borderless =
        sizes.get_media_size_by_translated_name_and_border("A4", true);
    auto invalidSizeBordered =
        sizes.get_media_size_by_translated_name_and_border("Legal", false);
    auto invalidSizeBorderless =
        sizes.get_media_size_by_translated_name_and_border("Legal", true);

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
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
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
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    const MediaSizes cSizes = sizes;

    MediaSize& letter = sizes.at(0);
    ASSERT_EQ("Letter", letter.getTranslatedName());
    auto letter_borderless = sizes.at(1);
    ASSERT_EQ("Letter", letter_borderless.getTranslatedName());
    const MediaSize& a4 = cSizes.at(2);
    ASSERT_EQ("A4", a4.getTranslatedName());
    const auto a4_borderless = cSizes.at(3);
    ASSERT_EQ("A4", a4_borderless.getTranslatedName());
}

// Test MediaSizes::at index out_of_range
TEST(MediaSizesTests, testAtOutOfRange)
{
    MediaSizes sizes;
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
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

TEST(MediaSizesTests, testIterator)
{
    MediaSizes sizes;
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    auto begin = sizes.begin();
    ASSERT_EQ("Letter", begin->getTranslatedName());
    ASSERT_EQ("Letter", (*begin).getTranslatedName());

    std::vector<MediaSize> mSizes;
    for (auto &size: sizes)
    {
        mSizes.push_back(size);
    }
    ASSERT_EQ("Letter", mSizes[0].getTranslatedName());
    ASSERT_EQ("Letter", mSizes[1].getTranslatedName());
    ASSERT_EQ("A4", mSizes[2].getTranslatedName());
    ASSERT_EQ("A4", mSizes[3].getTranslatedName());

    std::vector<MediaSize> mSizes2;
    MediaSizes sizes2;
    for (auto size: sizes2)
    {
        mSizes2.push_back(size);
    }
    ASSERT_EQ(0, mSizes2.size());
}

TEST(MediaSizesTests, testConstIterator)
{
    MediaSizes sizes;
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    const MediaSizes cSizes = sizes;
    std::vector<MediaSize> mSizes;
    for (const auto &size: sizes)
    {
        mSizes.push_back(size);
    }
    ASSERT_EQ("Letter", mSizes[0].getTranslatedName());
    ASSERT_EQ("Letter", mSizes[1].getTranslatedName());
    ASSERT_EQ("A4", mSizes[2].getTranslatedName());
    ASSERT_EQ("A4", mSizes[3].getTranslatedName());
}

TEST(MediaSizesTests, testReverseIterator)
{
    MediaSizes sizes;
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    auto begin = sizes.rbegin();
    ASSERT_EQ("iso_a4_210x297mm", begin->getMediaName());
    ASSERT_EQ("iso_a4_210x297mm", (*begin).getMediaName());

    std::vector<MediaSize> sizeVector;
    for (auto iter = sizes.rbegin(); iter != sizes.rend(); --iter)
    {
        sizeVector.push_back(*iter);
    }

    ASSERT_EQ("iso_a4_210x297mm", sizeVector[0].getMediaName());
    ASSERT_EQ("iso_a4_210x297mm", sizeVector[1].getMediaName());
    ASSERT_EQ("na_letter_8.5x11in", sizeVector[2].getMediaName());
    ASSERT_EQ("na_letter_8.5x11in", sizeVector[3].getMediaName());
}

TEST(MediaSizesTests, testConstReverseIterator)
{
    MediaSizes sizes;
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    auto begin = sizes.crbegin();
    ASSERT_EQ("iso_a4_210x297mm", begin->getMediaName());
    ASSERT_EQ("iso_a4_210x297mm", (*begin).getMediaName());

    std::vector<MediaSize> sizeVector;
    for (auto iter = sizes.crbegin(); iter != sizes.crend(); --iter)
    {
        sizeVector.push_back(*iter);
    }

    ASSERT_EQ("iso_a4_210x297mm", sizeVector[0].getMediaName());
    ASSERT_EQ("iso_a4_210x297mm", sizeVector[1].getMediaName());
    ASSERT_EQ("na_letter_8.5x11in", sizeVector[2].getMediaName());
    ASSERT_EQ("na_letter_8.5x11in", sizeVector[3].getMediaName());
}

TEST(MediaSizesTests, testIteratorWithStdLib)
{
    MediaSizes sizes;
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    MediaSizes sizes2 = sizes;      // sizes2 is used later. This saves extra initialization

    std::fill(sizes.begin(), sizes.end(), MediaSize("na_govt-letter_8x10in_borderless",
                19560, 14168, 0, 0, 0, 0));

    ASSERT_EQ("na_govt-letter_8x10in_borderless", sizes[0].getMediaName());
    ASSERT_EQ("na_govt-letter_8x10in_borderless", sizes[1].getMediaName());
    ASSERT_EQ("na_govt-letter_8x10in_borderless", sizes[2].getMediaName());
    ASSERT_EQ("na_govt-letter_8x10in_borderless", sizes[3].getMediaName());
    
    std::fill(begin(sizes), end(sizes), MediaSize("jis_b5_182x257mm_borderless",
                18200, 25700, 0, 0, 0, 0));
    
    ASSERT_EQ("jis_b5_182x257mm_borderless", sizes[0].getMediaName());
    ASSERT_EQ("jis_b5_182x257mm_borderless", sizes[1].getMediaName());
    ASSERT_EQ("jis_b5_182x257mm_borderless", sizes[2].getMediaName());
    ASSERT_EQ("jis_b5_182x257mm_borderless", sizes[3].getMediaName());

    std::copy(sizes.begin(), sizes.end(), sizes2.begin());
    
    ASSERT_EQ("jis_b5_182x257mm_borderless", sizes2[0].getMediaName());
    ASSERT_EQ("jis_b5_182x257mm_borderless", sizes2[1].getMediaName());
    ASSERT_EQ("jis_b5_182x257mm_borderless", sizes2[2].getMediaName());
    ASSERT_EQ("jis_b5_182x257mm_borderless", sizes2[3].getMediaName());
}

TEST(MediaSizesTests, testClear)
{
    MediaSizes sizes;
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    ASSERT_EQ(4, sizes.size());

    sizes.clear();
    ASSERT_EQ(0, sizes.size());
}

TEST(MediaSizesTests, testGetMediaSizeNames)
{
    MediaSizes sizes;
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(MediaSize("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(MediaSize("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    ASSERT_EQ("na_letter_8.5x11in", sizes[0].getMediaName());
    ASSERT_EQ("na_letter_8.5x11in", sizes[1].getMediaName());
    ASSERT_EQ("iso_a4_210x297mm", sizes[2].getMediaName());
    ASSERT_EQ("iso_a4_210x297mm", sizes[3].getMediaName());
}

TEST(MediaSizesTests, testGetMediaSizeNumber)
{
    MediaSize size1("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318);
    MediaSize size2("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0);
    MediaSize size3("custom_100x148mm",
                10000, 14800, 0, 0, 0, 0);

    MediaSizes sizes;
    sizes.push_back(size1);
    sizes.push_back(size2);

    ASSERT_EQ(0, sizes.getMediaSizeNumber(size1));
    ASSERT_EQ(1, sizes.getMediaSizeNumber(size2));
    ASSERT_EQ(0, sizes.getMediaSizeNumber(size3));
}