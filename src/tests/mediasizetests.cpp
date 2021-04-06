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
    media_size size("na_letter_8.5x11in", 21590, 27940,
                508, 610, 915, 1016);
    string translatedName = size.get_translated_name();
    ASSERT_STREQ("Letter", translatedName.c_str());
}

// Test getTranslatedName for size with no translated name
TEST(MediaSizeTests, testMediaSizeNoTranslatedName)
{
    media_size size("no_translated_name", 21590, 27940,
                508, 610, 915, 1016);
    string translatedName = size.get_translated_name();
    ASSERT_STREQ("no_translated_name", translatedName.c_str());
}

// Test insertion operator
TEST(MediaSizeTests, testInsertionOperator)
{
    media_size letter("na_letter_8.5x11in", 21590, 27940,
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
    media_size letter("na_letter_8.5x11in_borderless", 21590, 27940,
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
    media_sizes sizes;
    sizes.push_back(media_size("na_letter_8.5x11in", 21590, 27940,
            508, 610, 915, 1016));
    sizes.push_back(media_size("na_letter_8.5x11in_borderless", 21590, 27940,
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
    media_sizes sizes;

    ss << sizes;

    ASSERT_STREQ("Media Sizes:\nNone\n",
        ss.str().c_str());
}

// Test find matching MediaSize
TEST(MediaSizesTests, testGetMediaSizeByNameAndBorder)
{
    media_sizes sizes;
    sizes.push_back(media_size("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(media_size("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(media_size("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(media_size("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    auto letterBordered =
        sizes.get_media_size_by_translated_name_and_border("Letter", false);
    auto a4Borderless =
        sizes.get_media_size_by_translated_name_and_border("A4", true);
    auto invalidSizeBordered =
        sizes.get_media_size_by_translated_name_and_border("Legal", false);
    auto invalidSizeBorderless =
        sizes.get_media_size_by_translated_name_and_border("Legal", true);

    ASSERT_EQ("Letter", letterBordered.value().get_translated_name());
    ASSERT_FALSE(letterBordered.value().is_borderless());
    ASSERT_EQ("A4", a4Borderless.value().get_translated_name());
    ASSERT_TRUE(a4Borderless.value().is_borderless());
    ASSERT_EQ(nullopt, invalidSizeBordered);
    ASSERT_EQ(nullopt, invalidSizeBorderless);
}

// Test MediaSizes::operator[]
TEST(MediaSizesTests, testAccessOperator)
{
    media_sizes sizes;
    sizes.push_back(media_size("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(media_size("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(media_size("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(media_size("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));
    
    const media_sizes cSizes = sizes;

    media_size& letter = sizes[0];
    ASSERT_EQ("Letter", letter.get_translated_name());
    auto letter_borderless = sizes[1];
    ASSERT_EQ("Letter", letter_borderless.get_translated_name());
    const media_size& a4 = cSizes[2];
    ASSERT_EQ("A4", a4.get_translated_name());
    const auto a4_borderless = cSizes[3];
    ASSERT_EQ("A4", a4_borderless.get_translated_name());
}

// Test MediaSizes::at
TEST(MediaSizesTests, testAt)
{
    media_sizes sizes;
    sizes.push_back(media_size("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(media_size("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(media_size("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(media_size("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    const media_sizes cSizes = sizes;

    media_size& letter = sizes.at(0);
    ASSERT_EQ("Letter", letter.get_translated_name());
    auto letter_borderless = sizes.at(1);
    ASSERT_EQ("Letter", letter_borderless.get_translated_name());
    const media_size& a4 = cSizes.at(2);
    ASSERT_EQ("A4", a4.get_translated_name());
    const auto a4_borderless = cSizes.at(3);
    ASSERT_EQ("A4", a4_borderless.get_translated_name());
}

// Test MediaSizes::at index out_of_range
TEST(MediaSizesTests, testAtOutOfRange)
{
    media_sizes sizes;
    sizes.push_back(media_size("na_letter_8.5x11in", 
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
        const media_size& ms = sizes.at(2);
        FAIL() << "Expected std::out_of_range";
        // the following line is never reached. It is added to prevent compile error.
        ms.get_bottom();
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

TEST(MediaSizesTests, testClear)
{
    media_sizes sizes;
    sizes.push_back(media_size("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(media_size("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(media_size("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(media_size("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    ASSERT_EQ(4, sizes.size());

    sizes.clear();
    ASSERT_EQ(0, sizes.size());
}

TEST(MediaSizesTests, testGetMediaSizeNames)
{
    media_sizes sizes;
    sizes.push_back(media_size("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318));
    sizes.push_back(media_size("na_letter_8.5x11in", 
                21590, 27940, 0, 0, 0, 0));
    sizes.push_back(media_size("iso_a4_210x297mm", 
                20990, 29704, 318, 318, 318, 318));
    sizes.push_back(media_size("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0));

    ASSERT_EQ("na_letter_8.5x11in", sizes[0].get_name());
    ASSERT_EQ("na_letter_8.5x11in", sizes[1].get_name());
    ASSERT_EQ("iso_a4_210x297mm", sizes[2].get_name());
    ASSERT_EQ("iso_a4_210x297mm", sizes[3].get_name());
}

TEST(MediaSizesTests, testGetMediaSizeIndex)
{
    media_size size1("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318);
    media_size size2("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0);
    media_size size3("custom_100x148mm",
                10000, 14800, 0, 0, 0, 0);

    media_sizes sizes;
    sizes.push_back(size1);
    sizes.push_back(size2);

    ASSERT_EQ(0, sizes.get_media_size_index(size1));
    ASSERT_EQ(1, sizes.get_media_size_index(size2));
    ASSERT_EQ(0, sizes.get_media_size_index(size3));
}

TEST(MediaSizesTests, testGetMediaSizeTranslatedNamesByBorder)
{
    media_size size1("na_letter_8.5x11in", 
                21590, 27940, 318, 318, 318, 318);
    media_size size2("iso_a4_210x297mm", 
                20990, 29704, 0, 0, 0, 0);
    media_size size3("custom_100x148mm",
                10000, 14800, 0, 0, 0, 0);

    media_sizes sizes;
    sizes.push_back(size1);
    sizes.push_back(size2);
    sizes.push_back(size3);
    auto bordered = sizes.get_media_size_translated_names_by_border(false);

    ASSERT_EQ(1, bordered.size());
    ASSERT_EQ(u8"Letter", bordered[0]);

    auto borderless = sizes.get_media_size_translated_names_by_border(true);

    ASSERT_EQ(2, borderless.size());
    ASSERT_EQ(u8"A4", borderless[0]);
    ASSERT_EQ(u8"custom_100x148mm", borderless[1]);
}