
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

// Test MediaSources::addSource
TEST(MediaSourcesTests, testAddSource)
{
    MediaSources sources;
    sources.addSource(u8"Tray 1");
    sources.addSource(u8"Tray 2");
    sources.addSource(u8"Manual Feed Tray");

    auto srcs = sources.getSources();

    ASSERT_EQ(3, srcs.size());
    ASSERT_STREQ(u8"Tray 1", srcs[0]->getSource().c_str());
    ASSERT_STREQ(u8"Tray 2", srcs[1]->getSource().c_str());
    ASSERT_STREQ(u8"Manual Feed Tray", srcs[2]->getSource().c_str());
} 
