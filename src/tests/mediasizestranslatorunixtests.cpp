#include <string>
#include "gtest/gtest.h"
#include "mediasizestranslator.h"

using namespace nanaprint;
using namespace std;

// Test getTranslatedSize for oe_photo-l_3.5x5in
TEST(MediaSizesTranslatorUnixTests, testMediaSizesTranslatorMatch)
{
    MediaSizesTranslator translator;
    ASSERT_STREQ("3.5x5in", translator.getTranslatedSize("oe_photo-l_3.5x5in").c_str());
    ASSERT_STREQ("4x6in", translator.getTranslatedSize("na_index-4x6_4x6in").c_str());
    ASSERT_STREQ("JIS B5", translator.getTranslatedSize("jis_b5_182x257mm").c_str());
}

// Test getTranslatedSize for media name that does not have a translated name
TEST(MediaSizesTranslatorUnixTests, testMediaSizesTranslatorNoMatch) {
    MediaSizesTranslator translator;
    string translatedSize = translator.getTranslatedSize("invalid_size_name");
    ASSERT_STREQ("invalid_size_name", translatedSize.c_str());
}