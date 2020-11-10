
#include <sstream>
#include <cups/cups.h>
#include "gtest/gtest.h"
#include "mediasource.h"

using namespace nanaprint;
using namespace std;

// Test ctor
TEST(MediaSourceTests, testConstructor)
{
    MediaSource source(u8"Tray 1");

    ASSERT_STREQ(u8"Tray 1", source.getSource().c_str());
} 
