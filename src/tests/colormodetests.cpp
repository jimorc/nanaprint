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
    modes.add_mode(color_mode("monochrome"));
    modes.add_mode(color_mode("color"));

    auto cmodes = modes.get_modes();

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
    modes.add_mode(color_mode("monochrome"));
    modes.add_mode(color_mode("color"));

    stringstream ss;

    ss << modes;
    bool modesOk = (ss.str() == u8"Color Modes:\n    monochrome\n    color\n") ||
        (ss.str() == u8"Color Modes:\n    color\n    monochrome\n");

    ASSERT_TRUE(modesOk);
} 


TEST(ColorModeTests, testClear)
{
    color_modes modes;
    modes.add_mode(color_mode("b&w"));
    modes.add_mode(color_mode("color"));

    ASSERT_EQ(2, modes.size());

    modes.clear();
    ASSERT_EQ(0, modes.size());
}

TEST(ColorModesTests, testAccessOperator)
{
    color_modes modes;
    modes.add_mode(color_mode("b&w"));
    modes.add_mode(color_mode("color"));

    ASSERT_EQ("b&w", modes[0].get_value());
    ASSERT_EQ("color", modes[1].get_value());

    const color_modes cModes = modes;

    ASSERT_EQ("b&w", cModes[0].get_value());
    ASSERT_EQ("color", cModes[1].get_value());
}

TEST(ColorModesTests, testAt)
{
    color_modes modes;
    modes.add_mode(color_mode("b&w"));
    modes.add_mode(color_mode("color"));

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
    
TEST(ColorModesTests, testIterator)
{
    color_modes modes;
    std::vector<color_mode> vModes;
    for (auto &mode: modes)
    {
        vModes.push_back(mode);
    }
    ASSERT_EQ(0, vModes.size());

    modes.add_mode(color_mode("b&w"));
    modes.add_mode(color_mode("color"));

    auto begin = modes.begin();
    ASSERT_EQ("b&w", begin->get_value());
    ASSERT_EQ("b&w", (*begin).get_value());

    for (auto &mode: modes)
    {
        vModes.push_back(mode);
    }
    ASSERT_EQ("b&w", vModes[0].get_value());
    ASSERT_EQ("color", vModes[1].get_value());
}

TEST(ColorModesTests, testConstIterator)
{
    color_modes modes;
    std::vector<color_mode> vModes;
    for (auto &mode: modes)
    {
        vModes.push_back(mode);
    }
    ASSERT_EQ(0, vModes.size());

    modes.add_mode(color_mode("b&w"));
    modes.add_mode(color_mode("color"));

    auto begin = modes.cbegin();
    ASSERT_EQ("b&w", begin->get_value());
    ASSERT_EQ("b&w", (*begin).get_value());

    const color_modes modes2 = modes;
    for (auto iter = modes2.cbegin(); iter != modes2.cend(); ++iter)
    {
        vModes.push_back(*iter);
    }
    ASSERT_EQ("b&w", vModes[0].get_value());
    ASSERT_EQ("color", vModes[1].get_value());
}

TEST(ColorModesTests, testReverseIterator)
{
    color_modes modes;
    std::vector<color_mode> vModes;
    for (auto &mode: modes)
    {
        vModes.push_back(mode);
    }
    ASSERT_EQ(0, vModes.size());

    modes.add_mode(color_mode("b&w"));
    modes.add_mode(color_mode("color"));

    auto begin = modes.rbegin();
    ASSERT_EQ("color", begin->get_value());
    ASSERT_EQ("color", (*begin).get_value());

    for (auto iter = modes.rbegin(); iter != modes.rend(); --iter)
    {
        vModes.push_back(*iter);
    }
    ASSERT_EQ("b&w", vModes[1].get_value());
    ASSERT_EQ("color", vModes[0].get_value());
}

TEST(ColorModesTests, testConstReverseIterator)
{
    color_modes modes;
    std::vector<color_mode> vModes;
    for (auto &mode: modes)
    {
        vModes.push_back(mode);
    }
    ASSERT_EQ(0, vModes.size());

    modes.add_mode(color_mode("b&w"));
    modes.add_mode(color_mode("color"));

    auto begin = modes.crbegin();
    ASSERT_EQ("color", begin->get_value());
    ASSERT_EQ("color", (*begin).get_value());

    const color_modes modes2 = modes;
    for (auto iter = modes2.crbegin(); iter != modes2.crend(); --iter)
    {
        vModes.push_back(*iter);
    }
    ASSERT_EQ("b&w", vModes[1].get_value());
    ASSERT_EQ("color", vModes[0].get_value());
}

TEST(ColorModesTests, testIteratorWithStdLib)
{
    color_modes modes;
    modes.add_mode(color_mode("b&w"));
    modes.add_mode(color_mode("color"));


    std::fill(modes.begin(), modes.end(), color_mode("b&w"));

    ASSERT_EQ("b&w", modes[0].get_value());
    ASSERT_EQ("b&w", modes[1].get_value());
   
    modes[1] = color_mode("color");
    color_modes modes2 = modes;
    std::fill(begin(modes2), end(modes2), color_mode(""));
    
    std::copy(modes.begin(), modes.end(), modes2.begin());
    
    ASSERT_EQ("b&w", modes2[0].get_value());
    ASSERT_EQ("color", modes2[1].get_value());
}