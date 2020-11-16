#include <cups/cups.h>
#include "gtest/gtest.h"
#include "side.h"

using namespace nanaprint;
using namespace std;

// Test ctor
TEST(SideTests, testConstructor)
{
    Side oneSide(CUPS_SIDES_ONE_SIDED);
    Side twoSidesP(CUPS_SIDES_TWO_SIDED_PORTRAIT);
    Side twoSidesL(CUPS_SIDES_TWO_SIDED_LANDSCAPE);

    ASSERT_STREQ(CUPS_SIDES_ONE_SIDED, oneSide.getSide().c_str());
    ASSERT_STREQ(CUPS_SIDES_TWO_SIDED_PORTRAIT, twoSidesP.getSide().c_str());
    ASSERT_STREQ(CUPS_SIDES_TWO_SIDED_LANDSCAPE, twoSidesL.getSide().c_str());
} 
