
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

// Test MediaSource insertion operator
TEST(MediaSourceTests, testInsertionOperator)
{
    MediaSource source(u8"Tray 1");
    stringstream ss1;
    ss1 << source;

    ASSERT_STREQ(u8"    Tray 1\n", ss1.str().c_str());
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

// Test MediaSources insertion operator
TEST(MediaSourcesTests, testInsertionOperator)
{
    MediaSources sources;
    sources.addSource(u8"Tray 1");
    sources.addSource(u8"Tray 2");
    sources.addSource(u8"Manual Feed Tray");

    stringstream ss;
    ss << sources;

    ASSERT_STREQ(u8"Media Sources:\n    Tray 1\n    Tray 2\n    Manual Feed Tray\n",
        ss.str().c_str());
} 
