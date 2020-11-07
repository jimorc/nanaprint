#include <string>
#include <stdexcept>
#include "gtest/gtest.h"
#include "pageorientation.h"

using namespace nanaprint;
using namespace std;

// Test create
TEST(PageOrientationTests, testCreate)
{
    auto portrait = PageOrientation::create(PORTRAIT);
    auto landscape = PageOrientation::create(LANDSCAPE);
    auto revLandscape = PageOrientation::create(REVERSE_LANDSCAPE);
    auto revPortrait = PageOrientation::create(REVERSE_PORTRAIT);
    ASSERT_STREQ(u8"Portrait", portrait->getOrientation().c_str());
    ASSERT_STREQ(u8"Landscape", landscape->getOrientation().c_str());
    ASSERT_STREQ(u8"Reverse Landscape", revLandscape->getOrientation().c_str());
    ASSERT_STREQ(u8"Reverse Portrait", revPortrait->getOrientation().c_str());
}

// Test create with invalid orientation argument
TEST(PageOrientationTests, testCreateInvalidOrientation)
{
    try
    {
        auto orientation = PageOrientation::create(7);
        FAIL() << "Should have thrown exception because of bad input value to PageOrientation::create\n";
    }
    catch (invalid_argument& ex)
    {
        ASSERT_STREQ(ex.what(), "Invalid argument value to PageOrientation::create");
    }
    catch(...)
    {
        FAIL() << "Unexpected Excetion thrown: " << std::current_exception << endl;
    }
}

// Test the insertion operator
TEST(PageOrientationTests, testInsertionOperator)
{
    shared_ptr<PageOrientation> pPortOr = PageOrientation::create(PORTRAIT);
    shared_ptr<PageOrientation> pLandOr = PageOrientation::create(LANDSCAPE);
    shared_ptr<PageOrientation> pRevLandOr = PageOrientation::create(REVERSE_LANDSCAPE);
    shared_ptr<PageOrientation> pRevPortOr = PageOrientation::create(REVERSE_PORTRAIT);
    stringstream ssPort, ssLand, ssRevLand, ssRevPort;
    ssPort << *pPortOr;
    ssLand << *pLandOr;
    ssRevLand << *pRevLandOr;
    ssRevPort << *pRevPortOr;
    ASSERT_STREQ(u8"Portrait", ssPort.str().c_str());
    ASSERT_STREQ(u8"Landscape", ssLand.str().c_str());
    ASSERT_STREQ(u8"Reverse Landscape", ssRevLand.str().c_str());
    ASSERT_STREQ(u8"Reverse Portrait", ssRevPort.str().c_str());
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