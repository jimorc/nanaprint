
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

    ASSERT_STREQ(CUPS_MEDIA_TYPE_LETTERHEAD, types[0]->getType().c_str());
    ASSERT_STREQ(CUPS_MEDIA_TYPE_PLAIN, types[1]->getType().c_str());
    ASSERT_STREQ(CUPS_MEDIA_TYPE_ENVELOPE, types[2]->getType().c_str());
}

// Test MediaTypes insertion operator
TEST(MediaTypesTests, testInsertionOperator)
{
    stringstream ss;
    MediaTypes mediaTypes;
    mediaTypes.addMediaType(CUPS_MEDIA_TYPE_LETTERHEAD);
    mediaTypes.addMediaType(CUPS_MEDIA_TYPE_PHOTO);
    string let = "Media Types:\n    " + string(CUPS_MEDIA_TYPE_LETTERHEAD) + '\n' +
        "    " + string(CUPS_MEDIA_TYPE_PHOTO) + '\n';

    ss << mediaTypes;

    ASSERT_STREQ(let.c_str(), ss.str().c_str());
} 
