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
    finishingsNone2.setFinishing(CUPS_FINISHINGS_NONE);

    ASSERT_TRUE(finishingsNone.getNone());
    ASSERT_TRUE(finishingsNone2.getNone());
    ASSERT_FALSE(finishingsNone2.getBind());
} 

// Test Bind
TEST(FinishingsTests, testBind)
{
    Finishings finishingsBind;
    finishingsBind.setFinishing(CUPS_FINISHINGS_BIND);

    ASSERT_TRUE(finishingsBind.getBind());
    ASSERT_FALSE(finishingsBind.getNone());
} 