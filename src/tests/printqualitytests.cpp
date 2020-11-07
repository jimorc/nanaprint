#include <string>
#include <stdexcept>
#include "gtest/gtest.h"
#include "printquality.h"

using namespace nanaprint;
using namespace std;

// Test create
TEST(PrintQualityTests, testCreate)
{
    auto plainNormal = PrintQuality::create(PLAIN_NORMAL);
    auto fast = PrintQuality::create(FAST);
    auto normal = PrintQuality::create(NORMAL);
    auto high = PrintQuality::create(HIGH);
    auto photo = PrintQuality::create(PHOTO);

    ASSERT_STREQ(u8"Plain Normal", plainNormal->getPrintQuality().c_str());
    ASSERT_STREQ(u8"Fast", fast->getPrintQuality().c_str());
    ASSERT_STREQ(u8"Normal", normal->getPrintQuality().c_str());
    ASSERT_STREQ(u8"High", high->getPrintQuality().c_str());
    ASSERT_STREQ(u8"Photo", photo->getPrintQuality().c_str());
}
