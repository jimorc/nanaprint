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
