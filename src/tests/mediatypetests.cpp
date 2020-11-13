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