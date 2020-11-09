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

// Test create with invalid orientation argument
TEST(PrintQualityTests, testCreateInvalidOrientation)
{
    try
    {
        auto quality = PrintQuality::create(1);
        FAIL() << "Should have thrown exception because of bad input value to PrintQuality::create\n";
    }
    catch (invalid_argument& ex)
    {
        ASSERT_STREQ(ex.what(), "Invalid argument value input to PrintQuality::create");
    }
    catch(...)
    {
        FAIL() << "Unexpected Exception thrown: " << std::current_exception << endl;
    }
}

// Test the insertion operator
TEST(PrintQualityTests, testInsertionOperator)
{
    auto pPlainQual = PrintQuality::create(PLAIN_NORMAL);
    auto pFastQual = PrintQuality::create(FAST);
    auto pNormalQual = PrintQuality::create(NORMAL);
    auto pHighQual = PrintQuality::create(HIGH);
    auto pPhotoQual = PrintQuality::create(PHOTO);
    
    stringstream ssPlQual, ssFast, ssNormal, ssHigh, ssPhoto;
    ssPlQual << *pPlainQual;
    ssFast << *pFastQual;
    ssNormal << *pNormalQual;
    ssHigh << *pHighQual;
    ssPhoto << *pPhotoQual;

    ASSERT_STREQ(u8"Plain Normal", ssPlQual.str().c_str());
    ASSERT_STREQ(u8"Fast", ssFast.str().c_str());
    ASSERT_STREQ(u8"Normal", ssNormal.str().c_str());
    ASSERT_STREQ(u8"High", ssHigh.str().c_str());
    ASSERT_STREQ(u8"Photo", ssPhoto.str().c_str());
}

// Test PrintQualities::addPrintQuality
TEST(PrintQualitiesTests, testAddPrintQuality)
{
    PrintQualities qualities;
    qualities.addPrintQuality(FAST);
    qualities.addPrintQuality(NORMAL);

    ASSERT_TRUE(qualities.containsPrintQuality(u8"Fast"));
    ASSERT_TRUE(qualities.containsPrintQuality(u8"Normal"));

    qualities.addPrintQuality(HIGH);

    ASSERT_TRUE(qualities.containsPrintQuality(u8"High"));
    ASSERT_TRUE(qualities.containsPrintQuality(u8"Normal"));
    ASSERT_TRUE(qualities.containsPrintQuality(u8"Fast"));
}
