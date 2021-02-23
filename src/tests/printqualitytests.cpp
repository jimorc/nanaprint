#include <string>
#include <stdexcept>
#include "gtest/gtest.h"
#include "printquality.h"

using namespace nanaprint;
using namespace std;

// Test constructor
TEST(PrintQualityTests, testCtor)
{
    print_quality plainNormal(PLAIN_NORMAL);
    print_quality fast(FAST);
    print_quality normal(NORMAL);
    print_quality high(HIGH);
    print_quality photo(PHOTO);

    ASSERT_STREQ(u8"Plain Normal", plainNormal.get_value().c_str());
    ASSERT_STREQ(u8"Fast", fast.get_value().c_str());
    ASSERT_STREQ(u8"Normal", normal.get_value().c_str());
    ASSERT_STREQ(u8"High", high.get_value().c_str());
    ASSERT_STREQ(u8"Photo", photo.get_value().c_str());
}

// Test create with invalid orientation argument
TEST(PrintQualityTests, testCreateInvalidQuality)
{
    try
    {
        print_quality quality(1);
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
    print_quality plainQual(PLAIN_NORMAL);
    print_quality fastQual(FAST);
    print_quality normalQual(NORMAL);
    print_quality highQual(HIGH);
    print_quality photoQual(PHOTO);
    
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
// Test the insertion operator
TEST(PrintQualitiesTests, testInsertionOperator)
{
    print_qualities qualities;
    qualities.push_back(print_quality(FAST));
    qualities.push_back(print_quality(NORMAL));
    qualities.push_back(print_quality(PLAIN_NORMAL));
    qualities.push_back(print_quality(PHOTO));
    qualities.push_back(print_quality(HIGH));
    
    stringstream ss;
    ss << qualities;
    ASSERT_STREQ(u8"Print Qualities:\n    Fast\n    Normal\n    Plain Normal\n"
        "    Photo\n    High\n", ss.str().c_str());

    print_qualities q2;
    stringstream ss2;
    ss2 << q2;
    ASSERT_STREQ(u8"Print Qualities:\n    None\n", ss2.str().c_str());
}
