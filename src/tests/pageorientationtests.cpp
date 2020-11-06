#include <string>
#include "gtest/gtest.h"
#include "pageorientation.h"

using namespace nanaprint;
using namespace std;

// Test create
TEST(PageOrientaitionTests, testCreate)
{
    auto portrait = PageOrientation::create(PORTRAIT);
    auto landscape = PageOrientation::create(LANDSCAPE);
    ASSERT_STREQ(u8"Portrait", portrait->getOrientation().c_str());
    ASSERT_STREQ(u8"Landscape", landscape->getOrientation().c_str());
}
