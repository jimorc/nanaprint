
#include <sstream>
#include <cups/cups.h>
#include "gtest/gtest.h"
#include "mediatype.h"

using namespace nanaprint;
using namespace std;

// Test ctor
TEST(MediaTypeTests, testConstructor)
{
    MediaType mediaType(CUPS_MEDIA_TYPE_LETTERHEAD);

    ASSERT_STREQ(CUPS_MEDIA_TYPE_LETTERHEAD, mediaType.getType().c_str());
} 

// Test MediaType insertion operator
TEST(MediaTypeTests, testInsertionOperator)
{
    stringstream ss;
    MediaType mediaType(CUPS_MEDIA_TYPE_LETTERHEAD);
    string let = "    " + string(CUPS_MEDIA_TYPE_LETTERHEAD) + '\n';

    ss << mediaType;

    ASSERT_STREQ(let.c_str(), ss.str().c_str());
} 

// Test MediaSources::addMediaType
TEST(MediaTypesTests, testAddMediaType)
{
    MediaTypes mediaTypes;
    mediaTypes.addMediaType(CUPS_MEDIA_TYPE_LETTERHEAD);
    mediaTypes.addMediaType(CUPS_MEDIA_TYPE_PLAIN);
    mediaTypes.addMediaType(CUPS_MEDIA_TYPE_ENVELOPE);

    auto types = mediaTypes.getMediaTypes();

    ASSERT_STREQ(CUPS_MEDIA_TYPE_LETTERHEAD, types[0].getType().c_str());
    ASSERT_STREQ(CUPS_MEDIA_TYPE_PLAIN, types[1].getType().c_str());
    ASSERT_STREQ(CUPS_MEDIA_TYPE_ENVELOPE, types[2].getType().c_str());
}

// Test MediaTypes insertion operator
TEST(MediaTypesTests, testInsertionOperator)
{
    stringstream ss, ss2;
    MediaTypes mediaTypes;

    ss2 << mediaTypes;

    mediaTypes.addMediaType(CUPS_MEDIA_TYPE_LETTERHEAD);
    mediaTypes.addMediaType(CUPS_MEDIA_TYPE_PHOTO);
    string let = "Media Types:\n    " + string(CUPS_MEDIA_TYPE_LETTERHEAD) + '\n' +
        "    " + string(CUPS_MEDIA_TYPE_PHOTO) + '\n';

    ss << mediaTypes;

    ASSERT_STREQ("Media Types:\n    None\n", ss2.str().c_str());
    ASSERT_STREQ(let.c_str(), ss.str().c_str());
} 

TEST(MediaTypesTests, testAccessOperator)
{
    MediaTypes types;
    types.addMediaType(CUPS_MEDIA_TYPE_LETTERHEAD);
    types.addMediaType(CUPS_MEDIA_TYPE_PHOTO);

    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, types[0].getType());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PHOTO, types[1].getType());

    const MediaTypes cTypes = types;

    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, cTypes[0].getType());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PHOTO, cTypes[1].getType());
 }

TEST(MediaTypesTests, testAt)
{
    MediaTypes types;
    types.addMediaType(CUPS_MEDIA_TYPE_LETTERHEAD);
    types.addMediaType(CUPS_MEDIA_TYPE_PHOTO);

    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, types.at(0).getType());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PHOTO, types.at(1).getType());

    const MediaTypes cTypes = types;

    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, cTypes.at(0).getType());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PHOTO, cTypes.at(1).getType());

    try
    {
        auto t = types.at(2);
        FAIL() << "Didn't throw out_of_range exception";
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("Out of range"));
    }
    catch(...)
    {
        FAIL() << "EXpected out_of_range exception";
    }
    
    try
    {
        auto t = cTypes.at(2);
        FAIL() << "Didn't throw out_of_range exception";
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("Out of range"));
    }
    catch(...)
    {
        FAIL() << "EXpected out_of_range exception";
    }
 }
