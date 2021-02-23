#include <sstream>
#include <cups/cups.h>
#include "gtest/gtest.h"
#include "side.h"

using namespace nanaprint;
using namespace std;

// Test ctor
TEST(SideTests, testConstructor)
{
    side oneSide(CUPS_SIDES_ONE_SIDED);
    side twoSidesP(CUPS_SIDES_TWO_SIDED_PORTRAIT);
    side twoSidesL(CUPS_SIDES_TWO_SIDED_LANDSCAPE);

    ASSERT_STREQ(CUPS_SIDES_ONE_SIDED, oneSide.get_value().c_str());
    ASSERT_STREQ(CUPS_SIDES_TWO_SIDED_PORTRAIT, twoSidesP.get_value().c_str());
    ASSERT_STREQ(CUPS_SIDES_TWO_SIDED_LANDSCAPE, twoSidesL.get_value().c_str());
} 

// Test insertion operator
TEST(SideTests, testInsertionOperator)
{
    side oneSide(CUPS_SIDES_ONE_SIDED);
    side twoSidesP(CUPS_SIDES_TWO_SIDED_PORTRAIT);
    stringstream ss1, ss2;

    ss1 << oneSide;
    ss2 << twoSidesP;

    ASSERT_STREQ(u8"one-sided", ss1.str().c_str());
    ASSERT_STREQ(u8"two-sided-long-edge", ss2.str().c_str());
}

// Test addSide
TEST(SidesTests, testAddSide)
{
    sides side;
    side.addSide(CUPS_SIDES_ONE_SIDED);
    side.addSide(CUPS_SIDES_TWO_SIDED_PORTRAIT);
    side.addSide(CUPS_SIDES_TWO_SIDED_LANDSCAPE);

    auto mySides = side.get_values();
    ASSERT_STREQ(CUPS_SIDES_ONE_SIDED, mySides[0].get_value().c_str());
    ASSERT_STREQ(CUPS_SIDES_TWO_SIDED_PORTRAIT, mySides[1].get_value().c_str());
    ASSERT_STREQ(CUPS_SIDES_TWO_SIDED_LANDSCAPE, mySides[2].get_value().c_str());
}

// Test insertion operator
TEST(SidesTests, testInsertionOperator)
{
    sides sides1, sides2;
    sides2.addSide(CUPS_SIDES_ONE_SIDED);
    sides2.addSide(CUPS_SIDES_TWO_SIDED_PORTRAIT);

    stringstream ss1, ss2;
    ss1 << sides1;
    ss2 << sides2;

    ASSERT_STREQ("Sides:\n    None\n", ss1.str().c_str());
    ASSERT_STREQ("Sides:\n    one-sided\n    two-sided-long-edge\n", ss2.str().c_str());
}
