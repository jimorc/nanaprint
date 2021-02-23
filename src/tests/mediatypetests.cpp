
#include <sstream>
#include <cups/cups.h>
#include "gtest/gtest.h"
#include "mediatype.h"

using namespace nanaprint;
using namespace std;

// Test ctor
TEST(MediaTypeTests, testConstructor)
{
    media_type mediaType(CUPS_MEDIA_TYPE_LETTERHEAD);

    ASSERT_STREQ(CUPS_MEDIA_TYPE_LETTERHEAD, mediaType.get_value().c_str());
} 

// Test MediaType insertion operator
TEST(MediaTypeTests, testInsertionOperator)
{
    stringstream ss;
    media_type mediaType(CUPS_MEDIA_TYPE_LETTERHEAD);
    string let = "    " + string(CUPS_MEDIA_TYPE_LETTERHEAD) + '\n';

    ss << mediaType;

    ASSERT_STREQ(let.c_str(), ss.str().c_str());
} 

// Test MediaSources::addMediaType
TEST(MediaTypesTests, testAddMediaType)
{
    media_types mediaTypes;
    mediaTypes.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    mediaTypes.add_type(CUPS_MEDIA_TYPE_PLAIN);
    mediaTypes.add_type(CUPS_MEDIA_TYPE_ENVELOPE);

    auto types = mediaTypes.get_values();

    ASSERT_STREQ(CUPS_MEDIA_TYPE_LETTERHEAD, types[0].get_value().c_str());
    ASSERT_STREQ(CUPS_MEDIA_TYPE_PLAIN, types[1].get_value().c_str());
    ASSERT_STREQ(CUPS_MEDIA_TYPE_ENVELOPE, types[2].get_value().c_str());
}

// Test MediaTypes insertion operator
TEST(MediaTypesTests, testInsertionOperator)
{
    stringstream ss, ss2;
    media_types mediaTypes;

    ss2 << mediaTypes;

    mediaTypes.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    mediaTypes.add_type(CUPS_MEDIA_TYPE_PHOTO);
    string let = "Media Types:\n    " + string(CUPS_MEDIA_TYPE_LETTERHEAD) + '\n' +
        "    " + string(CUPS_MEDIA_TYPE_PHOTO) + '\n';

    ss << mediaTypes;

    ASSERT_STREQ("Media Types:\n    None\n", ss2.str().c_str());
    ASSERT_STREQ(let.c_str(), ss.str().c_str());
}