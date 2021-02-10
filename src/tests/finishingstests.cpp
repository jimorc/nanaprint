
#include <sstream>
#include <cups/cups.h>
#include "gtest/gtest.h"
#include "finishings.h"

using namespace nanaprint;
using namespace std;

// Test None
TEST(FinishingsTests, testNone)
{
    finishings finishingsNone, finishingsNone2;
    finishingsNone.set_finishing(CUPS_FINISHINGS_NONE);

    finishingsNone2.set_finishing(CUPS_FINISHINGS_BIND);
    finishingsNone2.set_finishing(CUPS_FINISHINGS_COVER);
    finishingsNone2.set_finishing(CUPS_FINISHINGS_FOLD);
    finishingsNone2.set_finishing(CUPS_FINISHINGS_PUNCH);
    finishingsNone2.set_finishing(CUPS_FINISHINGS_STAPLE);
    finishingsNone2.set_finishing(CUPS_FINISHINGS_TRIM);
    finishingsNone2.set_finishing(CUPS_FINISHINGS_NONE);

    ASSERT_TRUE(finishingsNone.getNone());
    ASSERT_TRUE(finishingsNone2.getNone());
    ASSERT_FALSE(finishingsNone2.getBind());
    ASSERT_FALSE(finishingsNone2.getPrintCover());
    ASSERT_FALSE(finishingsNone2.getFold());
    ASSERT_FALSE(finishingsNone2.getPunch());
    ASSERT_FALSE(finishingsNone2.getStaple());
    ASSERT_FALSE(finishingsNone2.getTrim());
} 

// Test Bind
TEST(FinishingsTests, testBind)
{
    finishings finishingsBind;
    finishingsBind.set_finishing(CUPS_FINISHINGS_BIND);

    ASSERT_TRUE(finishingsBind.getBind());
    ASSERT_FALSE(finishingsBind.getNone());
} 

// Test print cover
TEST(FinishingsTests, testPrintCover)
{
    finishings finishingsCover;
    finishingsCover.set_finishing(CUPS_FINISHINGS_COVER);

    ASSERT_TRUE(finishingsCover.getPrintCover());
    ASSERT_FALSE(finishingsCover.getNone());
}

// Test fold
TEST(FinishingsTests, testFold)
{
    finishings finishingsFold;
    finishingsFold.set_finishing(CUPS_FINISHINGS_FOLD);

    ASSERT_TRUE(finishingsFold.getFold());
    ASSERT_FALSE(finishingsFold.getNone());
}

// Test punch
TEST(FinishingsTests, testPunch)
{
    finishings finishings;
    finishings.set_finishing(CUPS_FINISHINGS_PUNCH);

    ASSERT_TRUE(finishings.getPunch());
    ASSERT_FALSE(finishings.getNone());
}

// Test staple
TEST(FinishingsTests, testStaple)
{
    finishings finishings;
    finishings.set_finishing(CUPS_FINISHINGS_STAPLE);

    ASSERT_TRUE(finishings.getStaple());
    ASSERT_FALSE(finishings.getNone());
}

// Test trim
TEST(FinishingsTests, testTrim)
{
    finishings finishings;
    finishings.set_finishing(CUPS_FINISHINGS_TRIM);

    ASSERT_TRUE(finishings.getTrim());
    ASSERT_FALSE(finishings.getNone());
}

// Test insertion operator
TEST(FinishingsTests, testInsertionOperator)
{
    finishings trimFinishings, noFinishings, allFinishings;
    trimFinishings.set_finishing(CUPS_FINISHINGS_TRIM);
    noFinishings.set_finishing(CUPS_FINISHINGS_NONE);
    allFinishings.set_finishing(CUPS_FINISHINGS_BIND);
    allFinishings.set_finishing(CUPS_FINISHINGS_COVER);
    allFinishings.set_finishing(CUPS_FINISHINGS_FOLD);
    allFinishings.set_finishing(CUPS_FINISHINGS_PUNCH);
    allFinishings.set_finishing(CUPS_FINISHINGS_STAPLE);
    allFinishings.set_finishing(CUPS_FINISHINGS_TRIM);

    stringstream ssTrim, ssNone, ssAll;
    ssTrim << trimFinishings;
    ssNone << noFinishings;
    ssAll << allFinishings;

    ASSERT_STREQ("Finishings:\n    Trim\n", ssTrim.str().c_str());
    ASSERT_STREQ("Finishings:\n    None\n", ssNone.str().c_str());
    ASSERT_STREQ("Finishings:\n    Bind\n    Cover\n    Fold\n    Punch\n"
        "    Staple\n    Trim\n", ssAll.str().c_str());
}