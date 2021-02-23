#include <sstream>
#include "gtest/gtest.h"
#include "colormode.h"

using namespace nanaprint;
using namespace std;

// Test constructors
TEST(ColorModeTests, testConstructor)
{
    color_mode mode;

    ASSERT_FALSE(mode.get_value());

    color_mode bw("Monochrome");
    ASSERT_EQ(std::string(u8"Monochrome"), bw.get_value().value().c_str());
} 

// Test insertion operator
TEST(ColorModeTests, testInsertionOperator)
{
    color_mode mode, mode2("color");


    stringstream ss, ss2;

    ss << mode;
    ss2 << mode2;

    ASSERT_STREQ(u8"    None\n", ss.str().c_str());
    ASSERT_STREQ(u8"    color\n", ss2.str().c_str());
} 

// Test constructors
TEST(ColorModesTests, testConstructor)
{
    color_modes modes;
    modes.push_back(color_mode("monochrome"));
    modes.push_back(color_mode("color"));

    auto cmodes = modes.get_values();

    ASSERT_EQ(2, cmodes.size());
    for (auto& mode: cmodes)
    {
        bool md = (mode.get_value() == u8"monochrome") ||
            (mode.get_value() == u8"color");
        ASSERT_TRUE(md);
    }
} 

// Test insertion operator
TEST(ColorModesTests, testInsertionOperator)
{
    color_modes modes;
    modes.push_back(color_mode("monochrome"));
    modes.push_back(color_mode("color"));

    stringstream ss;

    ss << modes;
    bool modesOk = (ss.str() == u8"Color Modes:\n    monochrome\n    color\n") ||
        (ss.str() == u8"Color Modes:\n    color\n    monochrome\n");

    ASSERT_TRUE(modesOk);
} 


TEST(ColorModeTests, testClear)
{
    color_modes modes;
    modes.push_back(color_mode("b&w"));
    modes.push_back(color_mode("color"));

    ASSERT_EQ(2, modes.size());

    modes.clear();
    ASSERT_EQ(0, modes.size());
}

TEST(ColorModesTests, testAccessOperator)
{
    color_modes modes;
    modes.push_back(color_mode("b&w"));
    modes.push_back(color_mode("color"));

    ASSERT_EQ("b&w", modes[0].get_value());
    ASSERT_EQ("color", modes[1].get_value());

    const color_modes cModes = modes;

    ASSERT_EQ("b&w", cModes[0].get_value());
    ASSERT_EQ("color", cModes[1].get_value());
}

TEST(ColorModesTests, testAt)
{
    color_modes modes;
    modes.push_back(color_mode("b&w"));
    modes.push_back(color_mode("color"));

    ASSERT_EQ("b&w", modes.at(0).get_value());
    ASSERT_EQ("color", modes.at(1).get_value());

    const color_modes cModes = modes;

    ASSERT_EQ("b&w", cModes.at(0).get_value());
    ASSERT_EQ("color", cModes.at(1).get_value());

    try
    {
        modes.at(2);
        FAIL() << "Didn't throw out_of_range exception";
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(std::string("Out of range"), e.what());
    }
    catch(...)
    {
        FAIL() << "Expected out_of_range exception";
    }
}
