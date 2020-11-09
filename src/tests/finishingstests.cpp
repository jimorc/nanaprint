#include <cups/cups.h>
#include "gtest/gtest.h"
#include "finishings.h"

using namespace nanaprint;
using namespace std;

// Test None
TEST(FinishingsTests, testNone)
{
    Finishings finishingsNone, finishingsNone2;
    finishingsNone.setFinishing(CUPS_FINISHINGS_NONE);

    finishingsNone2.setFinishing(CUPS_FINISHINGS_BIND);
    finishingsNone2.setFinishing(CUPS_FINISHINGS_COVER);
    finishingsNone2.setFinishing(CUPS_FINISHINGS_FOLD);
    finishingsNone2.setFinishing(CUPS_FINISHINGS_PUNCH);
    finishingsNone2.setFinishing(CUPS_FINISHINGS_STAPLE);
    finishingsNone2.setFinishing(CUPS_FINISHINGS_TRIM);
    finishingsNone2.setFinishing(CUPS_FINISHINGS_NONE);

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
    Finishings finishingsBind;
    finishingsBind.setFinishing(CUPS_FINISHINGS_BIND);

    ASSERT_TRUE(finishingsBind.getBind());
    ASSERT_FALSE(finishingsBind.getNone());
} 

// Test print cover
TEST(FinishingsTests, testPrintCover)
{
    Finishings finishingsCover;
    finishingsCover.setFinishing(CUPS_FINISHINGS_COVER);

    ASSERT_TRUE(finishingsCover.getPrintCover());
    ASSERT_FALSE(finishingsCover.getNone());
}

// Test fold
TEST(FinishingsTests, testFold)
{
    Finishings finishingsFold;
    finishingsFold.setFinishing(CUPS_FINISHINGS_FOLD);

    ASSERT_TRUE(finishingsFold.getFold());
    ASSERT_FALSE(finishingsFold.getNone());
}

// Test punch
TEST(FinishingsTests, testPunch)
{
    Finishings finishings;
    finishings.setFinishing(CUPS_FINISHINGS_PUNCH);

    ASSERT_TRUE(finishings.getPunch());
    ASSERT_FALSE(finishings.getNone());
}

// Test staple
TEST(FinishingsTests, testStaple)
{
    Finishings finishings;
    finishings.setFinishing(CUPS_FINISHINGS_STAPLE);

    ASSERT_TRUE(finishings.getStaple());
    ASSERT_FALSE(finishings.getNone());
}

// Test trim
TEST(FinishingsTests, testTrim)
{
    Finishings finishings;
    finishings.setFinishing(CUPS_FINISHINGS_TRIM);

    ASSERT_TRUE(finishings.getTrim());
    ASSERT_FALSE(finishings.getNone());
}