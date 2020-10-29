#include <string>
#include "gtest/gtest.h"
#include "mediasizestranslator.h"

using namespace nanaprint;
using namespace std;

// Test getTranslatedSize for oe_photo-l_3.5x5in
TEST(MediaSizesUnixTests, testMediaSizesTranslator3_5x5) {
    MediaSizesTranslator translator;
    string translatedSize = translator.getTranslatedSize("oe_photo-l_3.5x5in");
    ASSERT_STREQ("3.5x5in", translatedSize.c_str());
}

// Test getTranslatedSize for na_index_4x6in
TEST(MediaSizesUnixTests, testMediaSizesTranslator4x6) {
    MediaSizesTranslator translator;
    string translatedSize = translator.getTranslatedSize("na_index_4x6in");
    ASSERT_STREQ("4x6in", translatedSize.c_str());
}

// Test getTranslatedSize for media name that does not have a translated name
TEST(MediaSizesUnixTests, testMediaSizesTranslatorNoMatch) {
    MediaSizesTranslator translator;
    string translatedSize = translator.getTranslatedSize("invalid_size_name");
    ASSERT_STREQ("invalid_size_name", translatedSize.c_str());
}