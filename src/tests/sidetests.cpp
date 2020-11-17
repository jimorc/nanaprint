#include <sstream>
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

// Test insertion operator
TEST(SideTests, testInsertionOperator)
{
    Side oneSide(CUPS_SIDES_ONE_SIDED);
    Side twoSidesP(CUPS_SIDES_TWO_SIDED_PORTRAIT);
    stringstream ss1, ss2;

    ss1 << oneSide;
    ss2 << twoSidesP;

    ASSERT_STREQ(u8"one-sided", ss1.str().c_str());
    ASSERT_STREQ(u8"two-sided-long-edge", ss2.str().c_str());
}

// Test addSide
TEST(SidesTests, testAddSide)
{
    Sides sides;
    sides.addSide(CUPS_SIDES_ONE_SIDED);
    sides.addSide(CUPS_SIDES_TWO_SIDED_PORTRAIT);
    sides.addSide(CUPS_SIDES_TWO_SIDED_LANDSCAPE);

    auto mySides = sides.getSides();
    ASSERT_STREQ(CUPS_SIDES_ONE_SIDED, mySides[0]->getSide().c_str());
    ASSERT_STREQ(CUPS_SIDES_TWO_SIDED_PORTRAIT, mySides[1]->getSide().c_str());
    ASSERT_STREQ(CUPS_SIDES_TWO_SIDED_LANDSCAPE, mySides[2]->getSide().c_str());
}