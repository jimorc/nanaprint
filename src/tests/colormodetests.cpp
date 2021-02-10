#include <sstream>
#include "gtest/gtest.h"
#include "colormode.h"

using namespace nanaprint;
using namespace std;

// Test constructors
TEST(ColorModeTests, testConstructor)
{
    ColorMode mode;

    ASSERT_STREQ(u8"None", mode.getColorMode().c_str());

    ColorMode bw("Monochrome");
    ASSERT_STREQ(u8"Monochrome", bw.getColorMode().c_str());
} 

// Test insertion operator
TEST(ColorModeTests, testInsertionOperator)
{
    ColorMode mode, mode2("color");


    stringstream ss, ss2;

    ss << mode;
    ss2 << mode2;

    ASSERT_STREQ(u8"    None\n", ss.str().c_str());
    ASSERT_STREQ(u8"    color\n", ss2.str().c_str());
} 

// Test constructors
TEST(ColorModesTests, testConstructor)
{
    ColorModes modes;
    modes.addColorMode("monochrome");
    modes.addColorMode("color");

    auto cmodes = modes.getColorModes();

    ASSERT_EQ(2, cmodes.size());
    for (auto& mode: cmodes)
    {
        bool md = (mode.getColorMode() == u8"monochrome") ||
            (mode.getColorMode() == u8"color");
        ASSERT_TRUE(md);
    }
} 

// Test insertion operator
TEST(ColorModesTests, testInsertionOperator)
{
    ColorModes modes;
    modes.addColorMode("monochrome");
    modes.addColorMode("color");

    stringstream ss;

    ss << modes;
    bool modesOk = (ss.str() == u8"Color Modes:\n    monochrome\n    color\n") ||
        (ss.str() == u8"Color Modes:\n    color\n    monochrome\n");

    ASSERT_TRUE(modesOk);
} 


TEST(ColorModeTests, testClear)
{
    ColorModes modes;
    modes.addColorMode("b&w");
    modes.addColorMode("color");

    ASSERT_EQ(2, modes.size());
}