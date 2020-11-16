#include <string>
#include <stdexcept>
#include "gtest/gtest.h"
#include "printquality.h"

using namespace nanaprint;
using namespace std;

// Test constructor
TEST(PrintQualityTests, testCtor)
{
    PrintQuality none;

    PrintQuality plainNormal(PLAIN_NORMAL);
    PrintQuality fast(FAST);
    PrintQuality normal(NORMAL);
    PrintQuality high(HIGH);
    PrintQuality photo(PHOTO);

    ASSERT_STREQ(u8"None", none.getPrintQuality().c_str());
    ASSERT_STREQ(u8"Plain Normal", plainNormal.getPrintQuality().c_str());
    ASSERT_STREQ(u8"Fast", fast.getPrintQuality().c_str());
    ASSERT_STREQ(u8"Normal", normal.getPrintQuality().c_str());
    ASSERT_STREQ(u8"High", high.getPrintQuality().c_str());
    ASSERT_STREQ(u8"Photo", photo.getPrintQuality().c_str());
}

// Test create with invalid orientation argument
TEST(PrintQualityTests, testCreateInvalidQuality)
{
    try
    {
        PrintQuality quality(1);
        FAIL() << "Should have thrown exception because of bad value input to PrintQuality constructor\n";
    }
    catch (invalid_argument& ex)
    {
        ASSERT_STREQ(ex.what(), "Invalid argument value input to PrintQuality constructor");
    }
    catch(...)
    {
        FAIL() << "Unexpected Exception thrown: " << std::current_exception << endl;
    }
}

// Test the insertion operator
TEST(PrintQualityTests, testInsertionOperator)
{
    PrintQuality plainQual(PLAIN_NORMAL);
    PrintQuality fastQual(FAST);
    PrintQuality normalQual(NORMAL);
    PrintQuality highQual(HIGH);
    PrintQuality photoQual(PHOTO);
    
    stringstream ssPlQual, ssFast, ssNormal, ssHigh, ssPhoto;
    ssPlQual << plainQual;
    ssFast << fastQual;
    ssNormal << normalQual;
    ssHigh << highQual;
    ssPhoto << photoQual;

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

// Test the insertion operator
TEST(PrintQualitiesTests, testInsertionOperator)
{
    PrintQualities qualities;
    qualities.addPrintQuality(FAST);
    qualities.addPrintQuality(NORMAL);
    qualities.addPrintQuality(PLAIN_NORMAL);
    qualities.addPrintQuality(PHOTO);
    qualities.addPrintQuality(HIGH);
    
    stringstream ss;
    ss << qualities;
    ASSERT_STREQ(u8"Print Qualities:\n    Plain Normal\n    Fast\n    Normal\n"
        "    High\n    Photo\n", ss.str().c_str());
}
