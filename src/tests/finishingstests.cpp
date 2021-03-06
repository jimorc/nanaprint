
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

    ASSERT_TRUE(finishingsNone.get_none());
    ASSERT_TRUE(finishingsNone2.get_none());
    ASSERT_FALSE(finishingsNone2.get_bind());
    ASSERT_FALSE(finishingsNone2.get_print_cover());
    ASSERT_FALSE(finishingsNone2.get_fold());
    ASSERT_FALSE(finishingsNone2.get_punch());
    ASSERT_FALSE(finishingsNone2.get_staple());
    ASSERT_FALSE(finishingsNone2.get_trim());
} 

// Test Bind
TEST(FinishingsTests, testBind)
{
    finishings finishingsBind;
    finishingsBind.set_finishing(CUPS_FINISHINGS_BIND);

    ASSERT_TRUE(finishingsBind.get_bind());
    ASSERT_FALSE(finishingsBind.get_none());
} 

// Test print cover
TEST(FinishingsTests, testPrintCover)
{
    finishings finishingsCover;
    finishingsCover.set_finishing(CUPS_FINISHINGS_COVER);

    ASSERT_TRUE(finishingsCover.get_print_cover());
    ASSERT_FALSE(finishingsCover.get_none());
}

// Test fold
TEST(FinishingsTests, testFold)
{
    finishings finishingsFold;
    finishingsFold.set_finishing(CUPS_FINISHINGS_FOLD);

    ASSERT_TRUE(finishingsFold.get_fold());
    ASSERT_FALSE(finishingsFold.get_none());
}

// Test punch
TEST(FinishingsTests, testPunch)
{
    finishings finishings;
    finishings.set_finishing(CUPS_FINISHINGS_PUNCH);

    ASSERT_TRUE(finishings.get_punch());
    ASSERT_FALSE(finishings.get_none());
}

// Test staple
TEST(FinishingsTests, testStaple)
{
    finishings finishings;
    finishings.set_finishing(CUPS_FINISHINGS_STAPLE);

    ASSERT_TRUE(finishings.get_staple());
    ASSERT_FALSE(finishings.get_none());
}

// Test trim
TEST(FinishingsTests, testTrim)
{
    finishings finishings;
    finishings.set_finishing(CUPS_FINISHINGS_TRIM);

    ASSERT_TRUE(finishings.get_trim());
    ASSERT_FALSE(finishings.get_none());
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