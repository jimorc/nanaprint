#include <cups/cups.h>
#include "gtest/gtest.h"
#include "finishings.h"

using namespace nanaprint;
using namespace std;

// Test create
TEST(FinishingsTests, testCreate)
{
    Finishings finishings;
    finishings.setFinishing(CUPS_FINISHINGS_NONE);

    ASSERT_TRUE(finishings.getNone());
} 
