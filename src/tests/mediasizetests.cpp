#include <string>
#include <sstream>
#include "gtest/gtest.h"
#include "mediasize.h"

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