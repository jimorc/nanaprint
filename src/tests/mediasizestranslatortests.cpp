#include <string>
#include "gtest/gtest.h"
#include "mediasizestranslator.h"

using namespace nanaprint;
using namespace std;
TEST(MediaSizesUnixTests, testMediaSizesTranslator3_5x5) {
    MediaSizesTranslator translator;
    string translatedSize = translator.getTranslatedSize("oe_photo-l_3.5x5in");
    ASSERT_STREQ("3.5x5in", translatedSize.c_str());
}