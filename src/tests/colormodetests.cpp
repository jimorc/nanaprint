#include "gtest/gtest.h"
#include "colormode.h"

using namespace nanaprint;
using namespace std;

// Test None
TEST(ColorModeTests, testConstructor)
{
    ColorMode mode;

    ASSERT_STREQ(u8"None", mode.getColorMode().c_str());

    ColorMode bw("Monochrome");
    ASSERT_STREQ(u8"Monochrome", bw.getColorMode().c_str());
} 