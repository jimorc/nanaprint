#include <string>
#include <stdexcept>
#include "gtest/gtest.h"
#include "pageorientation.h"

using namespace nanaprint;
using namespace std;

// Test create
TEST(PageOrientationTests, testCreate)
{
    auto portrait = page_orientation(PORTRAIT);
    auto landscape = page_orientation(LANDSCAPE);
    auto revLandscape = page_orientation(REVERSE_LANDSCAPE);
    auto revPortrait = page_orientation(REVERSE_PORTRAIT);
    ASSERT_TRUE(portrait.get_orientation());
    ASSERT_STREQ(u8"Portrait", portrait.get_orientation().value().c_str());
    ASSERT_TRUE(landscape.get_orientation());
    ASSERT_STREQ(u8"Landscape", landscape.get_orientation().value().c_str());
    ASSERT_TRUE(revLandscape.get_orientation());
    ASSERT_STREQ(u8"Reverse Landscape", revLandscape.get_orientation().value().c_str());
    ASSERT_TRUE(revPortrait.get_orientation());
    ASSERT_STREQ(u8"Reverse Portrait", revPortrait.get_orientation().value().c_str());
}

// Test create with invalid orientation argument
TEST(PageOrientationTests, testCreateInvalidOrientation)
{
    page_orientation orientation;
    page_orientation badValue(7);

    ASSERT_FALSE(orientation.get_orientation());
    ASSERT_FALSE(badValue.get_orientation());
}

// Test the insertion operator
TEST(PageOrientationTests, testInsertionOperator)
{
    page_orientation pPortOr(PORTRAIT);
    page_orientation pLandOr(LANDSCAPE);
    page_orientation pRevLandOr(REVERSE_LANDSCAPE);
    page_orientation pRevPortOr(REVERSE_PORTRAIT);
    stringstream ssPort, ssLand, ssRevLand, ssRevPort;
    ssPort << pPortOr;
    ssLand << pLandOr;
    ssRevLand << pRevLandOr;
    ssRevPort << pRevPortOr;
    ASSERT_STREQ(u8"    Portrait\n", ssPort.str().c_str());
    ASSERT_STREQ(u8"    Landscape\n", ssLand.str().c_str());
    ASSERT_STREQ(u8"    Reverse Landscape\n", ssRevLand.str().c_str());
    ASSERT_STREQ(u8"    Reverse Portrait\n", ssRevPort.str().c_str());
}

// Test PageOrientations::addOrientation
TEST(PageOrientationTests, testaddOrientation)
{
    page_orientations orientations;
    orientations.add_orientation(LANDSCAPE);
    orientations.add_orientation(PORTRAIT);
    ASSERT_TRUE(orientations.contains_orientation(u8"Portrait"));
    ASSERT_TRUE(orientations.contains_orientation(u8"Landscape"));
    ASSERT_FALSE(orientations.contains_orientation(u8"ReverseLandscape"));
}

// Test PageOrientations insertion operator
TEST(PageOrientationTests, testPageOrientationsInserterOperator)
{
    page_orientations orientations;
    orientations.add_orientation(LANDSCAPE);
    orientations.add_orientation(PORTRAIT);
    stringstream ss, ss2;
    ss << orientations;
    string s = ss.str();
    bool ori = (ss.str() == u8"PageOrientations:\n    Portrait\n    Landscape\n") ||
        (ss.str() == u8"Page Orientations:\n    Landscape\n    Portrait\n");
    ASSERT_TRUE(ori);
}

TEST(PageOrientationsTests, testAccessOperator)
{
    page_orientations orientations;
    orientations.add_orientation(LANDSCAPE);
    orientations.add_orientation(PORTRAIT);

    ASSERT_EQ("Landscape", orientations[0].get_orientation().value());
    ASSERT_EQ("Portrait", orientations[1].get_orientation().value());

    const page_orientations or2 = orientations;

    ASSERT_EQ("Landscape", or2[0].get_orientation().value());
    ASSERT_EQ("Portrait", or2[1].get_orientation().value());
}

TEST(PageOrientationsTests, testAt)
{
    page_orientations orientations;
    orientations.add_orientation(LANDSCAPE);
    orientations.add_orientation(PORTRAIT);

    ASSERT_EQ("Landscape", orientations.at(0).get_orientation().value());
    ASSERT_EQ("Portrait", orientations.at(1).get_orientation().value());

    const page_orientations or2 = orientations;

    ASSERT_EQ("Landscape", or2.at(0).get_orientation().value());
    ASSERT_EQ("Portrait", or2.at(1).get_orientation().value());

    try
    {
        auto or1 = orientations.at(2);
        FAIL() << "Expected std::out_of_range";
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("Out of range"));
    }
    catch(...)
    {
        FAIL() << "Expected std::out_of_range, but threw a different exception";
    }
    
    try
    {
        auto or1 = or2.at(2);
        FAIL() << "Expected std::out_of_range";
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("Out of range"));
    }
    catch(...)
    {
        FAIL() << "Expected std::out_of_range, but threw a different exception";
    }
}