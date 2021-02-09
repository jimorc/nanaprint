
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

    ASSERT_STREQ(u8"Tray 1", source.get_source().c_str());
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
    sources.add_source(u8"Tray 1");
    sources.add_source(u8"Tray 2");
    sources.add_source(u8"Manual Feed Tray");

    auto srcs = sources.getSources();

    ASSERT_EQ(3, srcs.size());
    ASSERT_STREQ(u8"Tray 1", srcs[0].get_source().c_str());
    ASSERT_STREQ(u8"Tray 2", srcs[1].get_source().c_str());
    ASSERT_STREQ(u8"Manual Feed Tray", srcs[2].get_source().c_str());
} 

// Test MediaSources insertion operator
TEST(MediaSourcesTests, testInsertionOperator)
{
    MediaSources sources, sources2;
    sources.add_source(u8"Tray 1");
    sources.add_source(u8"Tray 2");
    sources.add_source(u8"Manual Feed Tray");

    stringstream ss, ss2;
    ss << sources;
    ss2 << sources2;

    ASSERT_STREQ(u8"Media Sources:\n    Tray 1\n    Tray 2\n    Manual Feed Tray\n",
        ss.str().c_str());
    ASSERT_STREQ(u8"Media Sources:\n    None\n", ss2.str().c_str());
} 

TEST(MediaSourcesTests, testAccessOperator)
{
    MediaSources sources;
    sources.add_source(u8"Tray 1");
    sources.add_source(u8"Tray 2");
    sources.add_source(u8"Manual Feed Tray");

    ASSERT_EQ(u8"Tray 1", sources[0].get_source());
    ASSERT_EQ(u8"Tray 2", sources[1].get_source());
    ASSERT_EQ(u8"Manual Feed Tray", sources[2].get_source());

    const MediaSources cSources = sources;

    ASSERT_EQ(u8"Tray 1", cSources[0].get_source());
    ASSERT_EQ(u8"Tray 2", cSources[1].get_source());
    ASSERT_EQ(u8"Manual Feed Tray", cSources[2].get_source());
}

TEST(MediaSourcesTests, testAt)
{
    MediaSources sources;
    sources.add_source(u8"Tray 1");
    sources.add_source(u8"Tray 2");
    sources.add_source(u8"Manual Feed Tray");

    ASSERT_EQ(u8"Tray 1", sources.at(0).get_source());
    ASSERT_EQ(u8"Tray 2", sources.at(1).get_source());
    ASSERT_EQ(u8"Manual Feed Tray", sources.at(2).get_source());

    const MediaSources cSources = sources;

    ASSERT_EQ(u8"Tray 1", cSources.at(0).get_source());
    ASSERT_EQ(u8"Tray 2", cSources.at(1).get_source());
    ASSERT_EQ(u8"Manual Feed Tray", cSources.at(2).get_source());
}

TEST(MediaSourcesTests, testAtOutOfRange)
{
    MediaSources sources;
    sources.add_source(u8"Tray 1");

    try
    {
        auto& source = sources.at(1);
        FAIL() << "Expected std::out_of_range";
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("Out of range"));
    }
    catch(...)
    {
        FAIL() << "Expected std::out_of_range, but threw a different exception";
    }

    const MediaSources cSources = sources;

    try
    {
        auto& source = cSources.at(1);
        FAIL() << "Expected std::out_of_range";
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("Out of range"));
    }
    catch(...)
    {
        FAIL() << "Expected std::out_of_range, but threw a different exception";
    }    
}

TEST(MediaSourcesTests, testIterator)
{
    MediaSources sources;
    std::vector<MediaSource> mSources;
    for (auto source: sources)
    {
        mSources.push_back(source);
    }
    ASSERT_EQ(0, mSources.size());

    sources.add_source(u8"Tray 1");
    sources.add_source(u8"Tray 2");
    sources.add_source(u8"Manual Feed Tray");

    auto begin = sources.begin();
    ASSERT_EQ(u8"Tray 1", begin->get_source());
    ASSERT_EQ(u8"Tray 1", (*begin).get_source());

    for (auto &source: sources)
    {
        mSources.push_back(source);
    }
    ASSERT_EQ(u8"Tray 1", mSources[0].get_source());
    ASSERT_EQ(u8"Tray 2", mSources[1].get_source());
    ASSERT_EQ(u8"Manual Feed Tray", mSources[2].get_source());
}

TEST(MediaSourcesTests, testConstIterator)
{
    MediaSources sources;
    std::vector<MediaSource> mSources;
    sources.add_source(u8"Tray 1");
    sources.add_source(u8"Tray 2");
    sources.add_source(u8"Manual Feed Tray");

    const MediaSources cSources = sources;

    auto begin = sources.cbegin();
    ASSERT_EQ(u8"Tray 1", begin->get_source());
    ASSERT_EQ(u8"Tray 1", (*begin).get_source());

    for (auto iter = sources.cbegin(); iter != sources.cend(); ++iter)
    {
        mSources.push_back(*iter);
    }
    ASSERT_EQ(u8"Tray 1", mSources[0].get_source());
    ASSERT_EQ(u8"Tray 2", mSources[1].get_source());
    ASSERT_EQ(u8"Manual Feed Tray", mSources[2].get_source());
}

TEST(MediaSourcesTests, testReverseIterator)
{
    MediaSources sources;
    std::vector<MediaSource> mSources;

    sources.add_source(u8"Tray 1");
    sources.add_source(u8"Tray 2");
    sources.add_source(u8"Manual Feed Tray");

    auto begin = sources.rbegin();
    ASSERT_EQ(u8"Manual Feed Tray", begin->get_source());
    ASSERT_EQ(u8"Manual Feed Tray", (*begin).get_source());

    for (auto iter = sources.rbegin(); iter != sources.rend(); --iter)
    {
        mSources.push_back(*iter);
    }
    ASSERT_EQ(u8"Tray 1", mSources[2].get_source());
    ASSERT_EQ(u8"Tray 2", mSources[1].get_source());
    ASSERT_EQ(u8"Manual Feed Tray", mSources[0].get_source());
}


TEST(MediaSourcesTests, testConstReverseIterator)
{
    MediaSources sources;
    std::vector<MediaSource> mSources;

    sources.add_source(u8"Tray 1");
    sources.add_source(u8"Tray 2");
    sources.add_source(u8"Manual Feed Tray");

    auto begin = sources.crbegin();
    ASSERT_EQ(u8"Manual Feed Tray", begin->get_source());
    ASSERT_EQ(u8"Manual Feed Tray", (*begin).get_source());

    for (auto iter = sources.crbegin(); iter != sources.crend(); --iter)
    {
        mSources.push_back(*iter);
    }
    ASSERT_EQ(u8"Tray 1", mSources[2].get_source());
    ASSERT_EQ(u8"Tray 2", mSources[1].get_source());
    ASSERT_EQ(u8"Manual Feed Tray", mSources[0].get_source());
}
