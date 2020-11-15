#include <string>
#include <stdexcept>
#include "gtest/gtest.h"
#include "pageorientation.h"

using namespace nanaprint;
using namespace std;

// Test create
TEST(PageOrientationTests, testCreate)
{
    auto portrait = PageOrientation(PORTRAIT);
    auto landscape = PageOrientation(LANDSCAPE);
    auto revLandscape = PageOrientation(REVERSE_LANDSCAPE);
    auto revPortrait = PageOrientation(REVERSE_PORTRAIT);
    ASSERT_STREQ(u8"Portrait", portrait.getOrientation().c_str());
    ASSERT_STREQ(u8"Landscape", landscape.getOrientation().c_str());
    ASSERT_STREQ(u8"Reverse Landscape", revLandscape.getOrientation().c_str());
    ASSERT_STREQ(u8"Reverse Portrait", revPortrait.getOrientation().c_str());
}

// Test create with invalid orientation argument
TEST(PageOrientationTests, testCreateInvalidOrientation)
{
    try
    {
        auto orientation = PageOrientation(7);
        FAIL() << "Should have thrown exception because of bad input value to PageOrientation::create\n";
    }
    catch (invalid_argument& ex)
    {
        ASSERT_STREQ(ex.what(), "Invalid argument value to PageOrientation constructor");
    }
    catch(...)
    {
        FAIL() << "Unexpected Excetion thrown: " << std::current_exception << endl;
    }
}

// Test the insertion operator
TEST(PageOrientationTests, testInsertionOperator)
{
    PageOrientation pPortOr(PORTRAIT);
    PageOrientation pLandOr(LANDSCAPE);
    PageOrientation pRevLandOr(REVERSE_LANDSCAPE);
    PageOrientation pRevPortOr(REVERSE_PORTRAIT);
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
    PageOrientations orientations;
    orientations.addOrientation(LANDSCAPE);
    orientations.addOrientation(PORTRAIT);
    ASSERT_TRUE(orientations.containsOrientation(u8"Portrait"));
    ASSERT_TRUE(orientations.containsOrientation(u8"Landscape"));
    ASSERT_FALSE(orientations.containsOrientation(u8"ReverseLandscape"));
}

// Test PageOrientations insertion operator
TEST(PageOrientationTests, testPageOrientationsInserterOperator)
{
    PageOrientations orientations;
    orientations.addOrientation(LANDSCAPE);
    orientations.addOrientation(PORTRAIT);
    stringstream ss, ss2;
    ss << orientations;
    string s = ss.str();
    bool ori = (ss.str() == u8"PageOrientations:\n    Portrait\n    Landscape\n") ||
        (ss.str() == u8"Page Orientations:\n    Landscape\n    Portrait\n");
    ASSERT_TRUE(ori);
}