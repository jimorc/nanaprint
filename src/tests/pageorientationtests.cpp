#include <string>
#include <stdexcept>
#include "gtest/gtest.h"
#include "pageorientation.h"

using namespace nanaprint;
using namespace std;

// Test create
TEST(PageOrientaitionTests, testCreate)
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
TEST(PageOrientaitionTests, testCreateInvalidOrientation)
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